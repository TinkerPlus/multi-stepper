#include <Arduino.h>
#include "BasicStepperDriver.h"
#include <SoftwareSerial.h>

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 120

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// All the wires needed for full functionality
#define DIR 4
#define STEP 3
//Uncomment line to use enable/disable functionality
//#define SLEEP 13

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

//Uncomment line to use enable/disable functionality
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);


String msgString = "";
String msgChar = "";

SoftwareSerial Slave(10, 11); // RX, TX
void setup() {
    Serial.begin(38400);
    Slave.begin(38400);
    Serial.println("Slave is ready!");
    stepper.begin(RPM, MICROSTEPS);
}

void loop() {   
    if (Slave.available()) {
      //msgChar = mySerial.read();
      msgString = Slave.readString();  //有待测试readString 
      Serial.println(msgString.toInt()*100);
      stepper.rotate(360 * msgString.toInt());
    }
}
