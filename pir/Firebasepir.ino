#include <FirebaseArduino.h>
//#include "DHT.h"
//int ledPin = 10;                // choose the pin for the LED
int inputPin = 13;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
#include  <ESP8266WiFi.h>

#define FIREBASE_HOST "nodemcupir.firebaseio.com"
#define FIREBASE_AUTH "1TheXTgjPcbxFv8Akmjmld6rcFm5l3yxbaiBIsnG"
#define WIFI_SSID "TP-LINK_3880"
#define WIFI_PASSWORD "sid123456"

//#define DHTPIN 14    // Data Pin of DHT 11 , for NodeMCU D5 GPIO no. is 14

//#define DHTTYPE DHT11   // DHT 11
//DHT dht(DHTPIN, DHTTYPE);

void setup() {
  
//pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // dht.begin();
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  
}

 

void loop() {
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    //digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) { 
      // we have just turned on
      Firebase.setString("message", "hello world");
      // We only want to print on the output change, not state
      pirState = HIGH;
      Serial.print("BC");
    }
  } else {
    //digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Firebase.setString("message", "motion ended");
      // We only want to print on the output change, not state
      pirState = LOW;
      Serial.print("MC");
    }
  }
 // float h = dht.readHumidity();
    
  //float t = dht.readTemperature();  // Reading temperature as Celsius (the default)
  //Firebase.setFloat ("Temp",t);
  //Firebase.setFloat ("Humidity",h);
 /* long state = digitalRead(inputPin);
    if(state == HIGH) {
     // digitalWrite (Status, HIGH);
      Firebase.setString("message", "motion detected");
      delay(1000);
      Serial.print("BC ");
    }
    else {
     // digitalWrite (Status, LOW);
      Firebase.setString("message", "motion ended");
      delay(1000);
      }
  delay(200);
  
*/
delay(200);}
