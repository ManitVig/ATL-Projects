#include <AFMotor.h>
int temp;
#include<SoftwareSerial.h>

SoftwareSerial serial1(9,10);  //RX /TX
AF_DCMotor M1(1,MOTOR12_8KHZ);
AF_DCMotor M2(2,MOTOR12_8KHZ);
AF_DCMotor M3(3);
AF_DCMotor M4(4);
char data;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
serial1.begin(9600);
M1.setSpeed(150);
M2.setSpeed(150);
M3.setSpeed(100);
M4.setSpeed(100);
M1.run(RELEASE);
M2.run(RELEASE);
M3.run(RELEASE);
M4.run(RELEASE);
pinMode(A5,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
if(serial1.available()>0)
{
data=serial1.read();
Serial.println(data);

}
switch(data)
{

  case 'F':
  case 'f': M1.run(FORWARD);
            M2.run(FORWARD);
            break;
  case 'B':
  case 'b': M1.run(BACKWARD);
            M2.run(BACKWARD); 
            break;
  case 'R':
  case 'r': M1.run(RELEASE);
            M2.run(FORWARD);
            break;
  case 'L':
  case 'l': M1.run(FORWARD);
            M2.run(RELEASE);
            break;
  case 'S':
  case 's': M1.run(RELEASE);
            M2.run(RELEASE);
            break; 
  case 'Z':
  case 'z':   M3.run(FORWARD);
            analogWrite(A5,255);
            delay(2250);
            M3.run(RELEASE);
             analogWrite(A5,0);
            break;       
  case 'Y':
  case 'y':  M4.run(FORWARD);
             analogWrite(A5,255);
            delay(2600);
            M4.run(RELEASE);
            analogWrite(A5,0);
            break;   

}
} 
