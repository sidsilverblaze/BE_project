#include <FirebaseArduino.h>
#include "DHT.h"
#include  <ESP8266WiFi.h>
//DHT
#define DHTPIN 0    // Data Pin of DHT 11 , for NodeMCU D5 GPIO no. is 14

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
//range
const int trigPin = 15;
const int echoPin = 13;
// defines variables
long duration;
int distance;

int inputPin = 5;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status


#define FIREBASE_HOST "nodemcupir.firebaseio.com"
#define FIREBASE_AUTH "1TheXTgjPcbxFv8Akmjmld6rcFm5l3yxbaiBIsnG"
#define WIFI_SSID "TP-LINK_3880"
#define WIFI_PASSWORD "sid123456"


void setup(){
  Serial.begin(9600);     // Communication started with 9600 baud
  //Serial.println ("WiFi Connected!");
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
 pinMode(inputPin, INPUT);     // declare sensor as input
  //Serial.begin(9600);
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
  }
  dht.begin();
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  //Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
   
}
void loop(){//water_sensor
int sensor=analogRead(A0); // Incoming analog signal read and appointed sensor
//Serial.println(sensor);   //Wrote serial port
Firebase.setFloat ("Sensor",sensor);
//pir_sensor
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
  //range_sensor
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
Serial.print("Distance: ");
Serial.println(distance);
Firebase.setFloat ("Distance",distance);
 
//delay(200);}
float h = dht.readHumidity();
  
  float t = dht.readTemperature();  // Reading temperature as Celsius (the default)
  Firebase.setFloat ("Temp",t);
  Firebase.setFloat ("Humidity",h);
  Serial.println(t);
  Serial.println(h);
  //delay(200);
delay(1000);

}
