//#include <ArduinoMotorShieldR3.h>

/*************************************************************
Motor Shield 1-Channel DC Motor Demo
by Randy Sarafan

For more information see:
https://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/

*************************************************************/
// #ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include "../generic/common.h"

#define PIN_WIRE_SDA (4)
#define PIN_WIRE_SCL (5)

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

static const uint8_t LED_BUILTIN = 2;//new ESP-12E GPIO2
static const uint8_t BUILTIN_LED = 2;//new ESP-12E GPIO2

static const uint8_t D0   = 3;
static const uint8_t D1   = 1;
static const uint8_t D2   = 16;
static const uint8_t D3   = 5;
static const uint8_t D4   = 4;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 0;
static const uint8_t D9   = 2;
static const uint8_t D10  = 15;
static const uint8_t D11  = 13;
static const uint8_t D12  = 12;
static const uint8_t D13  = 14;
static const uint8_t D14  = 4;
static const uint8_t D15  = 5;
void setup() {
  
  
  //Setup Channel A
  pinMode(D9, OUTPUT); //Initiates Brake Channel A pin
  pinMode(D12, OUTPUT); //Initiates Motor Channel A pin
}

void loop(){
  
  //forward @ full speed
  digitalWrite(D12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(D9, LOW);   //Disengage the Brake for Channel A
  digitalWrite(D3, 180);   //Spins the motor on Channel A at full speed
  
  delay(3000);
  
  digitalWrite(D9, HIGH); //Eengage the Brake for Channel A

  delay(1000);
  
  //backward @ half speed
  digitalWrite(D12, LOW); //Establishes backward direction of Channel A
  digitalWrite(D9, LOW);   //Disengage the Brake for Channel A
  digitalWrite(D3, 123);   //Spins the motor on Channel A at half speed
  
  delay(3000);
  
  digitalWrite(D9, HIGH); //Eengage the Brake for Channel A
  
  delay(1000);
  
}

