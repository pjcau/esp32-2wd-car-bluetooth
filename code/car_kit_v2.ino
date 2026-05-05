#include <Bluepad32.h>
#include <ESP32MX1508.h>

// ESP32-C3 Super Mini — pin sul lato di GPIO21 (opposto a 5V/GND).
// Evitiamo GPIO8 (LED integrato, strapping) e GPIO9 (BOOT, strapping).

// Motor A (Front) pins
#define FRONT_FWD  5
#define FRONT_BWD  6

// Motor B (Rear) pins
#define REAR_FWD 7
#define REAR_BWD 10

// PWM channels (each pin needs its own channel)
#define CH_LF 0
#define CH_LB 1
#define CH_RF 2
#define CH_RB 3

#define RES 8      // Resolution: 8 bit (0-255)
#define FREQ 5000  // PWM Frequency in Hz

MX1508 motorFront(FRONT_FWD, FRONT_BWD, CH_LF, CH_LB, RES, FREQ);
MX1508 motorRear(REAR_FWD, REAR_BWD, CH_RF, CH_RB, RES, FREQ);

int speed = 200;

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

void onConnectedController(ControllerPtr ctl) {
    bool foundEmptySlot = false;
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            Serial.printf("CALLBACK: Controller is connected, index=%d\n", i);
            ControllerProperties properties = ctl->getProperties();
            Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n",
                           ctl->getModelName().c_str(), properties.vendor_id, properties.product_id);
            myControllers[i] = ctl;
            foundEmptySlot = true;
            break;
        }
    }
    if (!foundEmptySlot) {
        Serial.println("CALLBACK: Controller connected, but could not find empty slot");
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            Serial.printf("CALLBACK: Controller disconnected from index=%d\n", i);
            myControllers[i] = nullptr;
            break;
        }
    }
}

void stopAll() {
    motorFront.motorBrake();
    motorRear.motorBrake();
}

void goForward(int spd) {
    motorFront.motorGo(spd);
    motorRear.motorGo(spd);
}

void goBackward(int spd) {
    motorFront.motorRev(spd);
    motorRear.motorRev(spd);
}

void turnLeft(int spd) {
    motorFront.motorRev(spd);
    motorRear.motorGo(spd);
}

void turnRight(int spd) {
    motorFront.motorGo(spd);
    motorRear.motorRev(spd);
}

void setupBL() {
    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n",
                   addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
    BP32.setup(&onConnectedController, &onDisconnectedController);
}

void setup() {
    Serial.begin(115200);
    setupBL();
}

void loop() {
    bool dataUpdated = BP32.update();
    if (!dataUpdated)
        return;

    ControllerPtr ctl = myControllers[0];
    if (ctl == nullptr)
        return;

    if (ctl->b()) {
        stopAll();
        Serial.println("STOP");
    } else if (ctl->dpad() == 0x01) {
        goForward(speed);
        Serial.println("FORWARD");
    } else if (ctl->dpad() == 0x02) {
        goBackward(speed);
        Serial.println("BACKWARD");
    } else if (ctl->dpad() == 0x08) {
        turnLeft(speed);
        Serial.println("LEFT");
    } else if (ctl->dpad() == 0x04) {
        turnRight(speed);
        Serial.println("RIGHT");
    } else if (ctl->dpad() == 0x00) {
        stopAll();
    }

    delay(150);
}
