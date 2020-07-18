#include<SoftwareSerial.h>

#include <Servo.h>

SoftwareSerial BTSerial(10,11); //RX,TX

Servo hand1;
Servo hand2;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

String dataIn;

int handposR;

void setup() {
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  hand1.attach(5);
  hand2.attach(6);
  BTSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
   // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available()){
    dataIn = BTSerial.readString();
    Serial.println(dataIn);
    if (dataIn.startsWith("arm")){
      digitalWrite(4, HIGH);
      delay(2000);
      digitalWrite(4, LOW);
    }else if(dataIn.startsWith("hn")){
      String dataInS = dataIn.substring(2, dataIn.length());
    Serial.println(dataInS);
    handposR = dataInS.toInt();
    hand1.write(handposR);
    hand2.write(180-handposR);
    }
  }
  if (Serial.available()){
    BTSerial.write(Serial.read());
  }
  }
  
 
