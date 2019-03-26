/*
 * 作用：在master中输入一个数值作为圈数，比如123，Slave转动该圈数。
 *
 * 安装：使用了第三方库 StepperDriver，可以在"库管理器"中下载，也可以在
 * https://github.com/laurb9/StepperDriver 查看相关信息
 *
 * 硬件：
 * - Max485模块接线
 * 需要两块便宜版本的Max485模块，接线图参考
 * https://www.arduino.cn/thread-47862-1-1.html
 * 根据这篇文章，采用了相同的软件串口代替硬件串口的方式，方便程序调试。
 * 在此基础上直接将主机的DE、RE两个引脚接高电平，表示只发不收；
 * 从机的DE、RE两个引脚接低电平，表示只接收不发送。
 *
 * - A4988模块接线
 * 主要参考这篇文章https://howtomechatronics.com/tutorials/arduino/how-to-control-stepper-motor-with-a4988-driver-and-arduino/
 * 程序部分使用StepperDriver的例程BasicStepperDriver
 */

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

String msgString = "";

SoftwareSerial Slave(10, 11); // RX, TX
void setup() {
    Serial.begin(38400);
    Slave.begin(38400);
    Serial.println("Slave is ready!");
    stepper.begin(RPM, MICROSTEPS);
}

void loop() {
    if (Slave.available()) {
      msgString = Slave.readString();
      Serial.println(msgString.toInt()*100);
      stepper.rotate(360 * msgString.toInt());
    }
}
