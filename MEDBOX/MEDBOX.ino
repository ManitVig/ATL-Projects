    /* MEDBOX */
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <require_cpp11.h>
#include <MFRC522.h>
#include <deprecated.h>

#include <SPI.h>
#define RFID_SS  10
#define RFID_RST 9
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid( RFID_SS, RFID_RST );

void setup() 
{
  Serial.begin(9600);
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  SPI.begin();
  Serial.begin(9600);
  MFRC522.begin();
  lcd.begin();
  lcd.backlight();
  lcd.print("MEDBOX");
  delay(5000);
  lcd.clear();
}

void loop() 
{

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      return;
    }

  if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      return;
    }
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
  if (content.substring(1) == "04 96 2F AA BD 61 80")
  {
      Serial.println("PATIENT 1");
      Serial.println();
      lcd.clear();
      lcd.print("PATIENT 1");
      lcd.setCursor(0,1);
      lcd.print("Welcome");
      delay(1500);
      lcd.clear();
      digitalWrite(0,HIGH); 
      digitalWrite(1,HIGH); 
      digitalWrite(2,HIGH);
      delay(3000);
      digitalWrite(0,LOW); 
      digitalWrite(1,LOW); 
      digitalWrite(2,LOW);   
  }
  if (content.substring(1) == "86 60 F6 06")
  {
      Serial.println("PATIENT 2");
      Serial.println();
      lcd.clear();
      lcd.print("PATIENT 2");
      lcd.setCursor(0,1);
      lcd.print("Welcome");
      delay(1500);
      lcd.clear();
      digitalWrite(3,HIGH); 
      digitalWrite(4,HIGH); 
      digitalWrite(5,HIGH);
      delay(3000);
      digitalWrite(3,LOW); 
      digitalWrite(4,LOW); 
      digitalWrite(5,LOW);   
  }
 
 else   
  {
    Serial.println("INVALID CARD");
    lcd.clear();
    lcd.print("INVALID CARD");
    delay(1000);
  }
}
