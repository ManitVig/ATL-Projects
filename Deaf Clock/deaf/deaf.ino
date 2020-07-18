
Conversation opened. 2 messages. All messages read.

Skip to content
Using Gmail with screen readers
2 of 19
CodeFor Clock.
Inbox
  x
Kunal Sharma <kunal3122001@gmail.com>
  
AttachmentsWed, Nov 21, 2018, 12:56 PM
  
to subhamsand, subham.sand

Attachments area
Subham Sand <subham.sand@stemrobo.in>
  
AttachmentsThu, Nov 22, 2018, 11:50 AM
  
to me
I am attaching Library and code please firstly try to work on UNO. 


---- On Wed, 21 Nov 2018 12:56:55 +0530 Kunal Sharma <kunal3122001@gmail.com> wrote ----





2 Attachments
  
Ok, I will do it.
Thanks, I will.
Thanks a lot.
  
  

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <DS3231.h>
#include <Servo.h> 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

DS3231 rtc(SDA,SCL);

const byte ROWS = 4; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {22, 24, 26, 28}; 
byte colPins[COLS] = {30, 32, 34}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char hours[2], minutes[2];
int q=0, relayl=36, relayf=38;

Servo myservo;

byte a1[8]={
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
  };

byte a2[8]={
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000
  };

byte a3[8]={
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100
  };

byte a4[8]={
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110
  };

byte a5[8]={
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
    
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  rtc.begin();
  lcd.createChar(4, a5);
  lcd.createChar(3, a4);
  lcd.createChar(2, a3);
  lcd.createChar(1, a2);
  lcd.createChar(0, a1); 
  pinMode(relayl, OUTPUT);
  pinMode(relayf, OUTPUT);
  digitalWrite(relayl, LOW);
  digitalWrite(relayf, LOW);
  myservo.attach(9);
}



void loop() {
    char key = keypad.getKey();
    
    lcd.setCursor(0,0);
    lcd.print("Time:  ");
    Serial.println("Time");
    lcd.print(rtc.getTimeStr());
     Serial.println(rtc.getTimeStr());
        Serial.println("rtc.getTimeStr()");
    lcd.setCursor(0,1);
    lcd.print("type * for alarm");
       Serial.println("type * for alarm");
    
    if(key=='*')setAlarm();
    
    while(Alarm() && q!=1){
      int key1 = keypad.getKey();
      if(key1=='#')
      {
        q=1;
        digitalWrite(relayf, LOW);
      for(int i=90; i<=0;i--)
      {
        myservo.write(i);delay(5);
      }
      }
      
      if(q==0)
      {
      digitalWrite(relayl, HIGH);
      digitalWrite(relayf, HIGH);
      }
      
      for(int i=0; i<90;i++)
      {
        myservo.write(i);delay(5);
      }
      for(int i=90; i<=0; i++)
      {
        myservo.write(i);delay(5);
      }
      Serial.println("Wake up");
      }
}

void setAlarm(){
  char x1, x2, x3;

  lcd.setCursor(0,0);
  lcd.print("     LOADING    ");
  lcd.setCursor(0,1);
  lcd.print("                 ");
  for(int i=0;i<16;++i) for(int j=0; j<5;j++){
    lcd.setCursor(i,1);
    lcd.write(j);
    delay(20);
    }
    
  x:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("      ALARM       ");

  x1 = NO_KEY;
  x2 = NO_KEY;
  x3 = NO_KEY;
 
  while(1){
    x1 = keypad.getKey();
    delay(100);
    if(x1 != NO_KEY){
      lcd.setCursor(0,1);
      lcd.print(x1);
      Serial.print(x1);
      while(x2==NO_KEY)x2= keypad.getKey();
      }
    if(x2 != NO_KEY){
      lcd.setCursor(1,1);
      lcd.print(x2);
       Serial.print(x1);
      while(x3!='#' )x3= keypad.getKey();
    }
    if(x1 != NO_KEY && x2 != NO_KEY && x3=='#'){
      lcd.setCursor(2,1);
      lcd.print(":");
       Serial.print(":");
      break;
  }
  }
   int n = ((x1-48)*10)+x2-48;
  if(n>0 && n<=24){
   hours[0]=x1;
   hours[1]=x2;
  }else {
          lcd.setCursor(0,1);
lcd.print("Error");
delay(1000);
    goto x;}

  y:
  
  x1 = NO_KEY;
  x2 = NO_KEY;
  x3 = NO_KEY;
  
  while(1){
    x1 = keypad.getKey();
    delay(100);
    if(x1 != NO_KEY){
      lcd.setCursor(3,1);
      lcd.print(x1);
      while(x2==NO_KEY)x2= keypad.getKey();
      }
    if(x2 != NO_KEY){
      lcd.setCursor(4,1);
      lcd.print(x2);
      while(x3!='#')x3= keypad.getKey();
    }
    if(x1 != NO_KEY && x2 != NO_KEY && x3=='#')break;
  }

  int p = ((x1-48)*10)+x2-48;
  if(p>0 && p<=60){
   minutes[0]=x1;
   minutes[1]=x2;
  }else {
          lcd.setCursor(7,1);
          lcd.print("Error");
          delay("500");
          lcd.setCursor(7,1);
          lcd.print("      ");
                lcd.setCursor(3,1);
                lcd.print("  ");
                delay("500");
    goto y;
    }
  
  
  minutes[0]=x1;
  minutes[1]=x2;
  q=0;
  lcd.setCursor(7,1);
  lcd.print("DONE");
  delay(1000);
  lcd.clear();  
  delay(500);
}



int Alarm(){
  char* curtime;
  curtime = rtc.getTimeStr();
  if(curtime[0]==hours[0] && curtime[1]==hours[1] && curtime[3]==minutes[0] && curtime[4]==minutes[1]) 
  {
    return 1;
  }
  else{ 
    return 0;
  }
  }

Deaf Clock Corrected.txt
Displaying Deaf Clock Corrected.txt.
