#include <SoftwareSerial.h>
SoftwareSerial Master(10, 11); //RX, TX ; 10--RO,11--DI
char message = '1';
String msgString = "";
int DE_RE=2;

void setup() {
  Serial.begin(38400);
  Serial.println("Master is ready!");
  Master.begin(38400);
  pinMode(DE_RE,OUTPUT);
  digitalWrite(DE_RE,LOW);  //DE_RE LOW 打开接收功能，关闭发射功能
                            //DE_RE HIGH 打开发射功能 关闭接收功能
}

void loop() {
  //val = '1';
  //Master.write(val);
  while (Serial.available()){
    //message = Serial.read();
    msgString = Serial.readString();
    //Serial.print("Send: ");
    //Serial.println(message);
    //Serial.println(msgString);
    //Master.write(message);
    Master.print(msgString);
  }
  //delay(50);
}
