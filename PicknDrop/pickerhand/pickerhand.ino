#include<Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

Servo elbow;
Servo arm1;
Servo arm2;


String dataIn;
int elbowPos;

void setup() {
   elbow.attach(3);
   arm1.attach(5);
   arm2.attach(6);
   Serial.begin(9600);
   BTSerial.begin(9600);
 }

void loop() {
   // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available()){
    
    dataIn = BTSerial.readString();
    Serial.println(dataIn);
        if (dataIn.startsWith("ar")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      elbowPos = dataInS.toInt();
      elbow.write(elbowPos);
      Serial.println(elbowPos);  
  }else if(dataIn.startsWith("PICK")){
    arm1.write(70);
    arm2.write(110);
  }
  else if(dataIn.startsWith("DROP")){
    arm1.write(0);
    arm2.write(0);
  }
  
  }
  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available()){
    BTSerial.write(Serial.read());
  }
 }
