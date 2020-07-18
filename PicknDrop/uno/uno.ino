#include <Servo.h>

Servo hand1;
Servo hand2;

char cmd;

void setup() {
  Serial.begin(9600);
  hand1.attach(6);
  hand2.attach(9);
}

void loop() {
  cmd = Serial.read();
  if (cmd == '1'){
    hand1.write(70);
    hand2.write(110);
  }else if (cmd == '0'){
    hand1.write(0);
    hand2.write(0);
  }

}
