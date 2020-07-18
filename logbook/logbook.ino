#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <SPI.h>
#include <MFRC522.h>


// Replace with your network credentials
const char* ssid     = "ATL";
const char* password = "Airtel@123";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://kiitatlprojects.000webhostapp.com/post-esp-data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";





String id;
#define SS_PIN D4
#define RST_PIN D2

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());


  
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
 
id = "";
     if (rfid.PICC_IsNewCardPresent()){
    if (rfid.PICC_ReadCardSerial()){
      Serial.print("Tag ID: ");
      for(byte i = 0; i < rfid.uid.size; i++){
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
        id += String(rfid.uid.uidByte[i]);
        HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&id=" + id + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    
    int httpResponseCode = http.POST(httpRequestData);
     
   
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
        } 
 }

      Serial.println();
      rfid.PICC_HaltA();
    }

   
    
  delay(1000);
  
}
