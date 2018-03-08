#include <BlynkSimpleEsp8266.h>
#include <FirebaseArduino.h>
#include "DHT.h"
#include  <ESP8266WiFi.h>
#define BLYNK_PRINT Serial
char ssid[] = "TP-LINK_3880";
char pass[] = "sid123456";
char auth[] = "d1c6834bcb7241c990c50e85127c0a24";
//DHT
#define DHTPIN 0    // Data Pin of DHT 11 , for NodeMCU D5 GPIO no. is 14

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
//range
const int trigPin = 15;
const int echoPin = 13;
//air
int th=500; 
int air = 14;
int water = 12;
// defines variables
long duration;
int distance;
float t, h;
int inputPin = 5;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
BlynkTimer timer;


#define FIREBASE_HOST "aquaponics-7796.firebaseio.com"
#define FIREBASE_AUTH "b8IeSWlnOeg1XiUjCxE0gpWMP3uRcnyLosyXDRzH"
#define WIFI_SSID "TP-LINK_3880"
#define WIFI_PASSWORD "sid123456"
int sensor;
int n = 0;
String pirsensor;
void myTimerEvent(){
  
  Blynk.virtualWrite(V0,distance);
   Blynk.virtualWrite(V4,sensor);
 // Blynk.virtualWrite(V1,pirsensor);
  Blynk.virtualWrite(V3,h);
  Blynk.virtualWrite(V2,t);
  Serial.println("Timer Event Executed");
  }

BLYNK_READ(V1) {
  Blynk.virtualWrite(V1, pirsensor);
}

BLYNK_READ(V5) {
  Blynk.virtualWrite(V5, millis());
}
void setup(){
  Serial.begin(9600);     // Communication started with 9600 baud
  //Serial.println ("WiFi Connected!");
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(air, OUTPUT);
pinMode(water, OUTPUT);

Blynk.begin(auth,ssid,pass);
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
   timer.setInterval(1000L,myTimerEvent);
}
void loop(){//water_sensor
  digitalWrite(water,HIGH);
 sensor=analogRead(A0); // Incoming analog signal read and appointed sensor
 digitalWrite(water,LOW);
//Serial.println(sensor);   //Wrote serial port
Firebase.setFloat ("Sensor",sensor);
//pir_sensor
val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    //digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) { 
      // we have just turned on
      Firebase.setString("message", "Motion Started");
      pirsensor = "Motion Started";
      // We only want to print on the output change, not state
      pirState = HIGH;
      Serial.print("BC");
    }
  } else {
    //digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Firebase.setString("message", "Motion Ended");
      pirsensor = "Motion Ended";
      // We only want to print on the output change, not state
      pirState = LOW;
      Serial.print("MC");
    }
  }
  //air_sensor 
  digitalWrite(air,HIGH);
  Serial.println(analogRead(A0));
if(analogRead(A0)>th)
{
//digitalWrite(output,HIGH);
Serial.println("HIGH");
}
else
{
//digitalWrite(output,LOW);
Serial.println("LOW");
}
digitalWrite(air,LOW);
//delay(500);

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
 h = dht.readHumidity();
  
   t = dht.readTemperature();  // Reading temperature as Celsius (the default)
  Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
  Firebase.setFloat ("Temp",t);
  Firebase.setFloat ("Humidity",h);
  
  //delay(200);
delay(1000);
// append a new value to /logs
  String name = Firebase.pushInt("logs", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(1000);
  Blynk.run();
  timer.run();
}
