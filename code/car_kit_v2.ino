#include <Bluepad32.h>
#include <ESP32MX1508.h>


#define RF 13
#define LF 26
#define RB 12
#define LB 27


#define PINA 9
#define PINB 10
#define CH1 0 // 16 Channels (0-15) are availible
#define CH2 1 // Make sure each pin is a different channel and not in use by other PWM devices (servos, LED's, etc)

// Optional Parameters
#define RES 8 // Resolution in bits: 8 (0-255), 12 (0-4095), or 16 (0-65535)
#define FREQ 5000 // PWM Frequency in Hz

//MX1508 motorA(PINA,PINB, CH1, CH2); // Default- 8 bit resoluion at 2500 Hz
MX1508 motorA(PINA,PINB, CH1, CH2, RES); // Specify resolution
MX1508 motorB(PINA,PINB, CH1, CH2, RES, FREQ); // Specify resolution and frequency
  


int incoming;
int speed = 200;
long duration;
float distanceCm;
bool lightIsTurnOn = false;

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.
void onConnectedController(ControllerPtr ctl) {
    bool foundEmptySlot = false;
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            Serial.printf("CALLBACK: Controller is connected, index=%d\n", i);
            // Additionally, you can get certain gamepad properties like:
            // Model, VID, PID, BTAddr, flags, etc.
            ControllerProperties properties = ctl->getProperties();
            Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id,
                           properties.product_id);
            myControllers[i] = ctl;
            foundEmptySlot = true;
            break;
        }
    }
    if (!foundEmptySlot) {
        Serial.println("CALLBACK: Controller connected, but could not found empty slot");
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    bool foundController = false;

    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            Serial.printf("CALLBACK: Controller disconnected from index=%d\n", i);
            myControllers[i] = nullptr;
            foundController = true;
            break;
        }
    }

    if (!foundController) {
        Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
    }
}


void processGamepad(ControllerPtr ctl) {
    // There are different ways to query whether a button is pressed.
    // By query each button individually:
    //  a(), b(), x(), y(), l1(), etc...
    if (ctl->a()) {
      Serial.println("BUtton A pressed");
    }

    if (ctl->b()) {
      Serial.println("BUTTON B pressed");
    }

    if (ctl->x()) {
     Serial.println("Button X pressed");      
    }
  
    if(ctl->dpad()  == 0X01) {
       Serial.println("Button UP pressed");
    }

    if(ctl->dpad() == 0X02) {
       Serial.println("Button DOWN pressed");
    }

    if(ctl->dpad() == 0X04) {
       Serial.println("Button RIGHT pressed");
    }

    if(ctl->dpad() == 0X08) {
       Serial.println("Button LEFT pressed");
    }
}

void processControllers() {
    for (auto myController : myControllers) {
        if (myController && myController->isConnected() && myController->hasData()) {
            if (myController->isGamepad()) {
                processGamepad(myController);
            } else {
                Serial.println("Unsupported controller");
            }
        }
    }
}


// Arduino setup function. Runs in CPU 1
void setupBL() {
    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

    // Setup the Bluepad32 callbacks
    BP32.setup(&onConnectedController, &onDisconnectedController);
}

// Arduino loop function. Runs in CPU 1.
void loopBL() {
    // This call fetches all the controllers' data.
    // Call this function in your main loop.
    bool dataUpdated = BP32.update();
    if (dataUpdated)
        processControllers();

    delay(150);
}

void stopC(){
 motorA.motorBrake();
 motorB.motorBrake();                    
}


void setup(){
  Serial.begin(115200);

  setupBL();
}

void loop(){
  loopBL();
  
  ControllerPtr ctl = myControllers[0];
  if(ctl != nullptr){

     float dis = calDistance();
     Serial.println(dis); 
    
      if(ctl->b()){  // stop all
        motorA.motorBrake();  
        motorB.motorBrake();  
      }

      if(ctl->dpad() == 0X01) { //UP
         motorA.motorGo(255);
      }

       if(ctl-> dpad() == 0X02) { // BACK
        motorA.motorRev(255);                 
      }
      
      if(ctl->dpad()  == 0X08) { // LEFT
         motorB.motorRev(200);           
      }
     
      if(ctl->dpad()  == 0X04) { // RIGHT
         motorB.motorGO(200);                     
      }
           
  }
    fflush(stdin);
}