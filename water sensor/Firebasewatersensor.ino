#include <LiquidCrystal.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "nodemcupir.firebaseio.com"
#define FIREBASE_AUTH "1TheXTgjPcbxFv8Akmjmld6rcFm5l3yxbaiBIsnG"
#define WIFI_SSID "TP-LINK_3880"
#define WIFI_PASSWORD "sid123456"


void setup(){
  Serial.begin(9600);     // Communication started with 9600 baud
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  
}
void loop(){
int sensor=analogRead(A0); // Incoming analog signal read and appointed sensor
//Serial.println(sensor);   //Wrote serial port
Firebase.setFloat ("Sensor",sensor);


delay(1000);

}
