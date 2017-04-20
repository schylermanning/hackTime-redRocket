/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//#ifndef Pins_Arduino_h
//#define Pins_Arduino_h
//
//#include "../generic/common.h"
//
//#define PIN_WIRE_SDA (4)
//#define PIN_WIRE_SCL (5)
//
//static const uint8_t SDA = PIN_WIRE_SDA;
//static const uint8_t SCL = PIN_WIRE_SCL;
//
//static const uint8_t LED_BUILTIN = 2;//new ESP-12E GPIO2
//static const uint8_t BUILTIN_LED = 2;//new ESP-12E GPIO2
//
//static const uint8_t D0   = 3;
//static const uint8_t D1   = 1;
//static const uint8_t D2   = 16;
//static const uint8_t D3   = 5;
//static const uint8_t D4   = 4;
//static const uint8_t D5   = 14;
//static const uint8_t D6   = 12;
//static const uint8_t D7   = 13;
//static const uint8_t D8   = 0;
//static const uint8_t D9   = 2;
//static const uint8_t D10  = 15;
//static const uint8_t D11  = 13;
//static const uint8_t D12  = 12;
//static const uint8_t D13  = 14;
//static const uint8_t D14  = 4;
//static const uint8_t D15  = 5;

const char *ssid = "ALPublic";
const char *password = "listlover";

//reverse
int dirMotorA = 12; //13
int speedMotorA = 5;
int brakeMotorA = 2;

//with dirMotorA and dirMotorB below it goes forward
//Need to figure out the correct turning pin and go from there
int dirMotorB = 14;
int speedMotorB = 13;
int brakeMotorB = 0;

ESP8266WebServer server ( 81 );

//switch (var) {
//    case 1:
//      //do something when var equals 1
//      break;
//    case 2:
//      //do something when var equals 2
//      break;
//    default:
//      // if nothing else matches, do the default
//      // default is optional
//    break;
//  }

const char *controlForm =
"<table>"
"<tr>"
"<td><form action='/'><input type='submit' value='FL' name='direction'> </form></td>"
"<td><form action='/'><input type='submit' value='F' name='direction'> </form></td>"
"<td><form action='/'><input type='submit' value='FR' name='direction'> </form></td>"
"</tr>"
"<tr>"
"<td></td><td><form action='/'><input type='submit' value='S' name='direction'> </form></td><td></td>"
"</tr>"
"<tr>"
"<td><form action='/'><input type='submit' value='BL' name='direction'> </form></td>"
"<td><form action='/'><input type='submit' value='B' name='direction'> </form></td>"
"<td><form action='/'><input type='submit' value='BR' name='direction'> </form></td>"
"</tr></table>";


//int direction = atoi(server.arg("direction"));

//String direction = server.arg("direction");

void handleRoot() {
   if (server.arg("direction") == "FL") {
     digitalWrite(dirMotorA, HIGH);
     digitalWrite(brakeMotorA, LOW);
     digitalWrite(speedMotorA, 255);
     digitalWrite(dirMotorB, HIGH);
     digitalWrite(brakeMotorB, LOW);
     digitalWrite(speedMotorB, HIGH);
  }
  else if (server.arg("direction") == "F") {
     digitalWrite(dirMotorA, HIGH);
     digitalWrite(brakeMotorA, LOW);
     digitalWrite(speedMotorA, 255);
     digitalWrite(dirMotorB, HIGH);
     digitalWrite(brakeMotorB, HIGH);
  }
  else if (server.arg("direction") == "FR") {
     digitalWrite(dirMotorA, HIGH);
     digitalWrite(brakeMotorA, LOW);
     digitalWrite(speedMotorA, 255);
     digitalWrite(dirMotorB, LOW);
     digitalWrite(brakeMotorB, LOW);
     digitalWrite(speedMotorB, HIGH);
  }
  else if (server.arg("direction") == "BL") {
      digitalWrite(dirMotorA, LOW);
      digitalWrite(brakeMotorA, LOW);
      digitalWrite(speedMotorA, 255);
      digitalWrite(dirMotorB, HIGH);
      digitalWrite(brakeMotorB, LOW);
      digitalWrite(speedMotorB, HIGH);
  }
  else if (server.arg("direction") == "B") {
      digitalWrite(dirMotorA, LOW);
      digitalWrite(brakeMotorA, LOW);
      digitalWrite(speedMotorA, 255);
      digitalWrite(dirMotorB, LOW);
      digitalWrite(brakeMotorB, HIGH);
  }
  else if (server.arg("direction") == "BR") {
      digitalWrite(dirMotorA, LOW);
      digitalWrite(brakeMotorA, LOW);
      digitalWrite(speedMotorA, 255);
      digitalWrite(dirMotorB, LOW);
      digitalWrite(brakeMotorB, LOW);
      digitalWrite(speedMotorB, HIGH);
  }
  else{
      digitalWrite(brakeMotorA, HIGH);
  }
  server.send(200, "text/html",  controlForm);
 }


//
//  if (server.arg("backward") == "backward")
//  {
//    digitalWrite(dirMotorA, LOW);
//    digitalWrite(brakeMotorA, LOW);
//    digitalWrite(speedMotorA, 255);
//
//    digitalWrite(dirMotorB, LOW);
//    digitalWrite(brakeMotorB, LOW);
//    digitalWrite(speedMotorB, 255);
//
//    server.send(200, "text/html", controlForm);
//  }
//  else if (server.arg("forward") == "forward")
//  {
//     digitalWrite(dirMotorA, HIGH);
//     digitalWrite(brakeMotorA, LOW);
//     digitalWrite(speedMotorA, 255);
//
//     digitalWrite(dirMotorB, HIGH);
//     digitalWrite(brakeMotorB, HIGH);
////     digitalWrite(speedMotorB, 255);
//
//    server.send(200, "text/html", controlForm);
//  }
//  else if (server.arg("stop") == "stop")
//  {
//    digitalWrite(brakeMotorA, HIGH);
//    server.send(200, "text/html",  controlForm);
//  }
//  else {
//    server.send(200, "text/html",  controlForm);
//  }
//}

void handleNotFound() {
  //digitalWrite ( led, 1 );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
}

void setup ( void ) {

//  pinMode(5, OUTPUT);
//  pinMode(LED_BUILTIN, OUTPUT);

   pinMode(dirMotorA, OUTPUT);
   pinMode(brakeMotorA, OUTPUT);
   pinMode(speedMotorA, OUTPUT);
   pinMode(dirMotorB, OUTPUT);
   pinMode(brakeMotorB, OUTPUT);
   pinMode(speedMotorB, OUTPUT);

  Serial.begin ( 9600 );
  WiFi.begin ( ssid, password );
  Serial.println ( "" );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  if ( MDNS.begin ( "esp8266" ) ) {
    Serial.println ( "MDNS responder started" );
  }

  server.on ( "/", handleRoot );
  server.on ( "/inline", []() {
    server.send ( 200, "text/plain", "this works as well" );
  } );
  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "HTTP server started" );
}

void loop ( void ) {
  server.handleClient();
}
