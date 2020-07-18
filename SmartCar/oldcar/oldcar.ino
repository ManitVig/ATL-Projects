#include<MFRC522.h>
#include<SPI.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
int buttonstate = 0;
int buttoncount=0;
int avg=0;
int value=0;
int count=0;


MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  pinMode(2,OUTPUT);   //for left motors
  pinMode(3,OUTPUT); 
  pinMode(4, OUTPUT);//for right motors
  pinMode(5, OUTPUT);
  pinMode(8,INPUT);    //for on /off switch
  pinMode(A1,OUTPUT);   //for green LED
  pinMode(A2,OUTPUT);   //for red LED

  SPI.begin(); 
  mfrc522.PCD_Init();
  Serial.begin(9600);
  Serial.println("WELCOME TO CBSE Regionals");
  Serial.println("PLEASE PUT YOUR DRIVING LISCENCE");
  lcd.begin();
  lcd.backlight();
  mainscreen();
}
void mainscreen()
{
  lcd.setCursor(0,0);
  lcd.print("Welcome");
  lcd.setCursor(0,1);
  lcd.print("");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PUT YOUR");
  lcd.setCursor(0,1);
  lcd.print("....LICENSE....");
}
void scan()
{
  if(count==1)               //after license being authorised 
   {
     if(buttonstate == 0)                  //if car is not started yet
       {
         while(digitalRead(8)==0)             //waiting for start button to be pressed
           {
           }
     buttonstate=1;  //storing status of button
     buttoncount=1;  //count for on,off           
  
       }
   if((buttonstate==1)&&(buttoncount==1))  //car getting started 
    {
      Serial.println("Alcohol Testing");
      avg=0;
        for(int j=0;j<10;j++)
             {
               {
                 value = analogRead(A0);
                 Serial.println(value);
                 avg+=value;
                 delay(800);
               }
             }
             value= avg/10;
             lcd.clear();
             lcd.setCursor(0,0);
             lcd.print("Alcohol Testing");//alcohol testing message
             lcd.setCursor(0,1);
             lcd.print("Get Ready..");
             delay(2500);
             
             if(value>550)               //if alcohol is detected
               {
                 analogWrite(A2,160);            //red led on
                 analogWrite(A1,0);            //green led off
                 lcd.clear();
                 lcd.setCursor(0,0);
                 lcd.print("Driver is Drunk");
                 lcd.setCursor(0,1);
                 lcd.print("Can't Drive");
                 delay(2500);
                 count=0;                         //reinitialising variables
                 buttonstate=0;
                 buttoncount=0;
                 lcd.clear();
                 lcd.setCursor(0,0);
                 lcd.print("Show Your");
                 lcd.setCursor(0,1); 
                 lcd.print("License");
               }
  
             else
               { 
                 lcd.clear();
                 lcd.setCursor(0,0);
                 lcd.print("Starting Engine");
                 Serial.print("Starting Engine");
                 lcd.setCursor(0,1);
                 lcd.print("Get Ready..");
                 Serial.print("Get Ready..");
                 delay(2500);
                 digitalWrite(2,HIGH);           //motors on
                 digitalWrite(3,HIGH);            //motors on
                 analogWrite(A1,160);            //green led on
                 analogWrite(A2,0);            //red led off
                 lcd.clear();
                   /*while(buttoncount!=0)
                     { 
                        if(digitalRead(8)==1)
                          {
                             buttoncount=0;
                             count=0;
                             buttonstate=0;

                             lcd.clear();
                             lcd.setCursor(0,0);
                             lcd.print("Stopping the car");
                             delay(2500);
                             digitalWrite(2,LOW);           //motors off
                             digitalWrite(3,LOW);            //motors off
                             analogWrite(A2,0);            //green led off
                             analogWrite(A1,0);             //red led off
                             lcd.clear();
                             lcd.setCursor(0,0);
                             lcd.print("Show Your");
                             lcd.setCursor(0,1);
                             lcd.print("License");
                             break;
                           }*/
                  value=analogRead(A0);
                  Serial.println(value);
                       if(value<=150)
                           {
                             lcd.setCursor(0,0);
                             lcd.print("Alcohol Val");
                             lcd.setCursor(12,0);
                             lcd.print(" ");
                             lcd.setCursor(12,0);
                             lcd.print(value);
                             delay(1500);
                           }
                       else if(value>150)
                           {
                            lcd.clear();
                            lcd.setCursor(0,0);
                            lcd.print("Driver is Drunk");
                            Serial.print("Driver is Drunk");
                            
                            lcd.setCursor(0,1);
                            lcd.print("Can't Drive");
        
                            digitalWrite(2,LOW);           //motors off
                            digitalWrite(3,LOW);            //motors off
                            analogWrite(A1,0);            //green led off
                            analogWrite(A2,160);           //red led on
                            count=0;
                            buttonstate=0;
                            buttoncount=0;
                            delay(2500);
                            lcd.clear(); 
                            lcd.setCursor(0,0);
                            lcd.print("Show Your");
                            lcd.setCursor(0,1);
                            lcd.print("License");
                            //break;
                           }
                    }

               } 

            }
   }
 //}
 
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
  if (content.substring(1) == "F6 5B 31 07") //change here the UID of the card/cards that you want to give access
  {
      Serial.println("Authorized access");
      Serial.println();
      count=1;
      lcd.clear();
      lcd.print("Authorized Driver");
      lcd.setCursor(0,1);
      lcd.print("Welcome");
      delay(1500);
      lcd.clear();
            scan();
  }
 
 else   
  {
    Serial.println(" Access denied");
    lcd.clear();
    lcd.print(" Access denied");
    delay(1000);
    mainscreen();
  }
}
