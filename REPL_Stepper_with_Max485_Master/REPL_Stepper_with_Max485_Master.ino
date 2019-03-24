#include <SoftwareSerial.h>

//#define BOUND_RATE=38400； //有待测试115200

SoftwareSerial mySerial(10, 11); // RX, TX; RX->RO, TX->DI
char msgChar="";
String msgString="";
void setup() {
    Serial.begin(38400);
    mySerial.begin(38400);
    Serial.println("Master Ready!");
}

void loop() {
    if (Serial.available()) {
      msgChar = Serial.read();
      msgString = Serial.readString();
      mySerial.write(msgChar);
      //mySerial.print(msgString);
      Serial.print("send:");
      Serial.println(msgChar);
      //Serial.println(msgString);
    }
    delay(50);
}
