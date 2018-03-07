int input = A0;
int output = 7;
int th=500; // Set threshold level.
void setup()
{
Serial.begin(9600);
//pinMode(output,OUTPUT);
//digitalWrite(output,LOW);

}
void loop()
{
Serial.println(analogRead(input));
if(analogRead(input)>th)
{
//digitalWrite(output,HIGH);
Serial.println("HIGH");
}
else
{
//digitalWrite(output,LOW);
Serial.println("LOW");
}
delay(500);
}
