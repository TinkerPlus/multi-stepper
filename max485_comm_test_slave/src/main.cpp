#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial Slave(10, 11);
char val;
String msgString;
int DE_RE=2;

void setup() {
  Serial.begin(38400);
  Serial.println("Slave is ready!");
  Slave.begin(38400);
  pinMode(DE_RE,OUTPUT);
  digitalWrite(DE_RE,LOW);
}

void loop() {
  if (Slave.available()){
    //val = Slave.read();
    msgString = Slave.readString();
    //Serial.write(val);
    Serial.println(msgString);
    Serial.println(msgString.toInt() * 1000);
 }
}
