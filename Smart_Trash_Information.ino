
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>
int lcdColumns = 16;
int lcdRows = 2;
// Set these to run example.
#define FIREBASE_HOST "trashinformationbaseiot.firebaseio.com"
#define FIREBASE_AUTH "WS1UPFOwJFTXq0L1jOK0f4Mpqbk1aQK4nLnXJ3OB"
#define WIFI_SSID "q"
#define WIFI_PASSWORD "12345678"
//defines pins numbers
const int trigPin = 2;  //D4
const int echoPin = 0;  //D3
// defines variables
long duration;
int distance;
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows); 
void setup() { 
  lcd.init();                    
  lcd.backlight();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  lcd.setCursor(0, 0);
  lcd.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
   lcd.print(".");
    delay(500);
  }
  lcd.clear();
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  delay(500);
  lcd.setCursor(0,0);
  lcd.print(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}

void loop() {
 lcd.clear();
 String a = Firebase.getString("message/satu");
 Firebase.setString("lokasi", "TPS MASJID"); //set Lokasi
 lcd.setCursor(0, 0);
 lcd.print(a);
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
if(distance<=3){
  Serial.print("Blind spot");
  }
  else{
//Serial.print("Distance: ");
Serial.println(distance);
  }
delay(2000);
  
  if (distance>=0  && distance<=5 ){
    Firebase.setFloat("status", 2);
    Serial.println("A");
    }  
  else if(distance>=6 && distance <=9){
    Firebase.setFloat("status", 1);
    Serial.println("B");    
    }
    
    else{
      Firebase.setFloat("status", 0);
      Serial.println("C");
      }


}
