#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

int dirMotorA = 12; //
int speedMotorA = 5; //3 //ours: 5
int brakeMotorA = 2; //9 //our: 2

//with dirMotorA and dirMotorB below it goes forward
//Need to figure out the correct turning pin and go from there
int dirMotorB = 14;
// int speedMotorB = 13;
int brakeMotorB = 0;
//int fireAll = 4;

void setup() {
  // put your setup code here, to run once:
  
  //Setup Channel A
   pinMode(brakeMotorA, OUTPUT); //Initiates Brake Channel A pin
   pinMode(dirMotorA, OUTPUT); //Initiates Motor Channel A pin
   pinMode(speedMotorA, OUTPUT);

   digitalWrite(brakeMotorA, LOW);
   // analogWrite(speedMotorA, 127); 
   digitalWrite(dirMotorA, HIGH);
   digitalWrite(brakeMotorA, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
//forward @ full speed
  digitalWrite(brakeMotorA, LOW);   //Disengage the Brake for Channel A
  digitalWrite(dirMotorA, HIGH); //Establishes forward direction of Channel A
  analogWrite(speedMotorA, 127);   //Spins the motor on Channel A at full speed
  
  delay(3000);

  digitalWrite(brakeMotorA, LOW);   //Disengage the Brake for Channel A
  digitalWrite(dirMotorA, LOW); //Establishes reverse direction of Channel A
  analogWrite(speedMotorA, 127);   //Spins the motor on Channel A at full speed
    
  delay(3000);
  analogWrite(speedMotorA, 0);
  digitalWrite(brakeMotorA, HIGH); //Eengage the Brake for Channel A

  delay(3000);
}
