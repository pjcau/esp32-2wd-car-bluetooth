# Esp32 2WD Car Bluetooth
Esp32 2WD Car with Bluetooth Remote Control is an project that can avoid obstacles and learn with your son. This is a second project for build a car. This way we can replace the old main logic from a old toy car.


## Components Details  

- **[ESP32C3](https://www.waveshare.com/wiki/ESP32-S3-Zero)**: For development purposes, we use this board.  

- **MINI L298N(MX1508) Motor Driver**: It controlled the motors with Bridge H circuit. 

- **Switch ON/OFF** It is used for turn on/off the power on circuit.

- **DC-DC SteUp Boost Module**: You can use a TP4056 Kit to reach this result.
  
- **Bluetooth GamePad**: It's used to remote command the car.

- **2 18650 Battery (Rechargeable)**: It is used for providing voltage the circuit. Please put those in series. We aspect around 8.4 V.
  
- **Jumper Wires**: Male-to-male and male-to-female connectors for the circuit (any normal wires can be used, though male-to-female connectors are necessary for connecting with esp).

- **Breadboard**: For connection the wires with others components we used this board.

- **Hot glued**: For connection the wires/devices/motors with others components we used this project.
- **Soldering iron**: For connection the wires with others components we used this board.

## Following Hardware Steps

1. I had an old toy car. We connected them using the screw provided with the chassis. Glue gun can be used to attach the motors to the base.

<table>
  <tr>
    <td>
      <img src="./assets/IMG_4705.jpg" height="250" alt="A small two-wheel-drive toy car chassis with visible motors mounted on the base, connected by screws. The car is placed on a tabletop with scattered electronic components and tools in the background, suggesting an active workspace. The scene conveys a hands-on, educational atmosphere.">
    </td>
    <td>
      <img src="./assets/IMG_4706.jpg" height="250" alt="Close-up of the toy car chassis showing detailed wiring and connections to the motors. Jumper wires and a motor driver are attached, with the workspace containing additional parts and tools. The environment is focused and creative, highlighting the process of assembling the car.">
    </td>
  </tr>
</table>

2. Uncover the top of the car, take a look on the main board and isolate the power and cable from the motors



3. And repeated the process for the right motors and connected them to "out3" and "out4" of the motor driver.

4. After that we connected the battery with the motor driver. Positive terminal to 12V marked port. We marged the ground of the battery with the ESP32 ground connector to and connected it with the GND marked port. Lastly we connected the 5v from our ESP32 with the 5V maked port beside the GND of the driver so that the ESP32 board can take power from the motor driver.

5. We connected the ENA, IN1, IN2, IN3, IN4, ENB ports with the ESP32's D32, D26, D27, D13, D12 & D33 no pin respectively.

6. We removed both of the ENA and ENB jumpers so that we can control the speed of the motors using PWM. If anyone doesn't want to control the speed of the motors then they should leave the jumper on the board.

7. Install the Ultrasonic Sensor connect the GND to esp32 GND, VCC to 5V esp32, trig to D5 on esp32 and trigP to D18 on esp32.

8.  Install the Led 5V device with GND to esp32 GND, VCC  to D19 on esp32.
9. 


## Circuit Diagram
<table>
  <tr valign="middle">
    <td halign="center">
      <img src="./assets/draft.jpeg" alt="circuite_idea" height="450">
    </td>
    <td halign="center">
      <img src="./assets/circuite_idea.png" alt="circuite_idea" height="450">
    </td>
  </tr>
</table>

<table>
  <tr valign="middle">
    <td halign="center">
      <img src="./assets/diagram_circuit.png" alt="diagram_circuite" height="450">
      <div>
        <a href="https://app.cirkitdesigner.com/project/4d7fd9ed-47f0-43c8-8ef2-58eadbf371e6">circuit scheme link</a>
      </div>
    </td>
     
  </tr>
</table>

## Internal Control

- The bluetooth car app sends different characters for different functions and the ESP receives them and controls the motors using the L298N motor driver module. 
    - Basic Action :
Up → Up  
Down → Down  
Left → ‘Left’  
Right → ‘Right’

  - Features Action:
B button → 'B'


- Pressed the B Button, stop the car.




## Following Software Steps

1. Download the [Arduino Ide](https://www.arduino.cc/en/software/) and begin to write a simple code to learn how turn on/off a simple build led inside the esp32. You can compile and upload the binary on esp32.
2. After it, follow this [steps](https://www.waveshare.com/wiki/ESP32-S3-Zero#Arduino). Install those libraries on arduino for esp32 and bluetooth controller, in this followint list
 - https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json
 - https://espressif.github.io/arduino-esp32/package_esp32_index.json
3. If you want test the RGB Led, please add the library "[Adafruit_NeoPXL8](https://github.com/adafruit/Adafruit_NeoPXL8)", you find in the library. In the case use, in the folder "code", choose the file named "test_RGB_led.ino"
3. In the end, yuo can retrieve the my code and setup the number of pin and command from your BL remote control.


## Pictures and Videos
