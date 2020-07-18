/*
  Mifare RC522 Basic test program
  Prints out the tag id when in range
  
  PINOUT:

   RC522 MODULE    UNO     MEGA
   SDA(SS)         D10     D53
   SCK             D13     D52
   MOSI            D11     D51
   MISO            D12     D50
   PQ              Not Connected
   GND             GND     GND
   RST             D9      D9
   3.3V            3.3V    3.3V

*/

#include <SPI.h>
#include <MFRC522.h>
#include<Servo.h>
#define RFID_SS  10
#define RFID_RST 9
 Servo myservo1,myservo2;
MFRC522 rfid( RFID_SS, RFID_RST );

void setup() {
  SPI.begin();
  Serial.begin(115200);
  rfid.begin();
  myservo1.attach(9);
  myservo2.attach(10);
  myservo1.write(0);
  myservo2.write(0);
}

void loop() {
  int c1=0,c2=0;
  byte data[MAX_LEN];
  byte uid[5];
  int uid1[5]={96,196,142,43,1};
  int uid2[5]={96,196,142,54,1};
  if ( rfid.requestTag( MF1_REQIDL, data ) == MI_OK ) {
    if ( rfid.antiCollision( data ) == MI_OK ) {
      memcpy( uid, data, 5 );
      for ( int i = 0; i < 5; i++ ) {
        Serial.print( uid[i] );
        if(uid[i]==uid1[i])
        c1++;
        else if(uid[i]==uid2[i])
        c2++;
      }
      if(c1==4)
      {
      myservo1.write(90);
      myservo2.write(0);
      Serial.println("Access granted 1");
      }
      else if(c2==4)
      {
      myservo1.write(0);
      myservo2.write(90); 
      Serial.println("Access granted 2");
      }
      c1=0;
      c2=0;//Serial.println("//");
    }
  }
}
