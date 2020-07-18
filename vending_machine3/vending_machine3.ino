#include <Servo.h>
#define trigPin 7
#define echoPin 6
#define pump 11
Servo servo;
int sound = 250;
void setup() {
Serial.begin (9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(5, OUTPUT);
pinMode(4, OUTPUT);
pinMode(11, OUTPUT);
servo.attach(9);
servo.write(1);
}
void loop() 
{
long duration,distance;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
digitalWrite(trigPin, LOW);
  do
  {
    long distance2,distance3;
    digitalWrite(2)==HIGH;
    delay(500);
    digitalWrite(2)==HIGH;
    delay(500);
     
  }
  
  }
}
