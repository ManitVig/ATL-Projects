#include<DS3231.h>
#include<Keypad.h>

const int motor1[2]{4,5};
const int motor2[2]{6,7};

DS3231 rtc(SDA, SCL);

const byte ROWS = 4; 
const byte COLS = 4; 

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0',':','D'}
};
byte rowPins[ROWS] = {36, 34, 32, 30};
byte colPins[COLS] = {28, 26, 24, 22}; 


Keypad kypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String lfrhour = "";
String lfrmin = "";
String intime = "";
String realtime;
bool medtime = false;

#define ir1 2
#define ir2 3

void setup() {
  rtc.begin();
  pinMode(motor1, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);

}
void lfr(){
    while(digitalRead(ir1) == LOW && digitalRead(ir2)==LOW){
    digitalWrite(motor1[0], LOW);
    digitalWrite(motor1[1], HIGH);
    digitalWrite(motor2[0], LOW);
    digitalWrite(motor2[1], HIGH);
  }
  while(digitalRead(ir1) == HIGH && digitalRead(ir2)==LOW){
    digitalWrite(motor1[0], HIGH);
    digitalWrite(motor1[1], LOW);
    digitalWrite(motor2[0], LOW);
    digitalWrite(motor2[1], HIGH);
  }
  while(digitalRead(ir1) == LOW && digitalRead(ir2)==HIGH){
    digitalWrite(motor1[0], LOW);
    digitalWrite(motor1[1], HIGH);
    digitalWrite(motor2[0], HIGH);
    digitalWrite(motor2[1], LOW);
  }
}

void setmedtime(){
  char key = kypad.getKey();
  if(key){
    if (key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*'){
      intime = intime + key;
      Serial.println(intime);
    }else if (key == 'A'){
      lfrhour = intime.substring(0,1);
      lfrmin = intime.substring(3,4);
      return;
    }
  }
}
void loop() {
     realtime = rtc.getTimeStr();
     if (lfrhour == realtime.substring(0,1) && lfrmin == realtime.substring(3,4)){
      Serial.println(lfrhour);
      Serial.println(lfrmin);
      medtime = true;
     }else{
      medtime = false;
     }
    if(medtime == false){
      char key = kypad.getKey();
     if (key){
      if (key == '*'){
        Serial.println("Set Medicine Time");
        setmedtime();
      }else{
      }
     }else{
      }
    }else if(medtime == true){
      lfr();
    }

}
