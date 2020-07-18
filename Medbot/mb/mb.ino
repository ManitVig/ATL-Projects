#include <Servo.h  >                                                                                                         \>
#include<MFRC522.h>
#include<SPI.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define M1P 1                          //conn3) digitalpin 
#define M2P 2

#define SS_PIN 7
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo1,myservo2;
void setup() 
{
  pinMode(M1P,OUTPUT);
  pinMode(M2P,OUTPUT);
  pinMode(A0,OUTPUT);

  SPI.begin(); 
  mfrc522.PCD_Init();
  Serial.begin(9600);
  Serial.println("DATABASE");
  Serial.println("PLEASE PUT YOUR PATIENT CARD");
  myservo1.attach(6);
  myservo2.attach(5);
  lcd.begin();
  lcd.backlight();
  mainscreen();
}
void mainscreen()
{
  lcd.setCursor(0,0);
  lcd.print("....HI....");
  lcd.setCursor(0,1);
  lcd.print("..I AM MEDBOT..");
  delay(5000);
    lcd.setCursor(0,0);
  lcd.print("..MEDICINE..");
  lcd.setCursor(0,1);
  lcd.print(".....TIME.....");
  delay(5000);

}

void loop()
{  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      return;
    }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      return;
    }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
     {
       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       Serial.print(mfrc522.uid.uidByte[i], HEX);
       content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       content.concat(String(mfrc522.uid.uidByte[i], HEX));
     }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "67 26 72 1C") //change here the UID of the card/cards that you want to give access
  {
      Serial.println("Authorized access");
      Serial.println();
      lcd.clear();
      lcd.print("PATIENT 1");
      lcd.setCursor(0,1);
      lcd.print("M1=PARACETAMOL");     
        digitalWrite(M1P,HIGH);
        delay(1000);
        for(int pos = 30; pos <=90;pos+= 1)// goes from 0 degrees to 180 degrees 
          {                                  // in steps of 1 degree 
            myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
            delay(30);                       // waits 15ms for the servo to reach the position 
          } 
      
          delay(5000);
         digitalWrite(M1P,LOW);
        for(int pos = 90; pos>=30; pos-=1)     // goes from 180 degrees to 0 degrees 
          {                                
            myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
            delay(30);                       // waits 15ms for the servo to reach the position 
          }

  }
 
 else if (content.substring(1) == "F6 5B 31 07") //change here the UID of the card/cards that you want to give access
  {
      Serial.println("Authorized access");
      Serial.println();
      lcd.clear();
      lcd.print("PATIENT 2");
      lcd.setCursor(0,1);
      lcd.print("M2=PANTOCID");
      delay(1000);
 
  
        digitalWrite(M2P,HIGH);
        delay(1000);
        for(int pos = 30; pos <=110;pos+= 1)// goes from 0 degrees to 180 degrees 
          {                                  // in steps of 1 degree 
            myservo2.write(pos);              // tell servo to go to position in variable 'pos' 
            delay(30);                       // waits 15ms for the servo to reach the position 
          } 
      
          delay(5000);
         digitalWrite(M2P,HIGH);
        for(int pos = 110; pos>=130; pos-=1)     // goes from 180 degrees to 0 degrees 
          {                                
            myservo2.write(pos);              // tell servo to go to position in variable 'pos' 
            delay(30);                       // waits 15ms for the servo to reach the position 
          }
 
}
mainscreen();
}
