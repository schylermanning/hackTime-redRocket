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

// map Arduino Motor Shield R3 to WeMo D1
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

const char *ssid = "WiFi SSID HERE";
const char *password = "WiFi Password HERE";

// Controller A
int dirMotorA = 12;
int speedMotorA = 5;
int brakeMotorA = 2;

// Controller B
int dirMotorB = 14;
int speedMotorB = 13;
int brakeMotorB = 0;
int fireAll = 4;

// HTTP Port
// (i) This might need changed with some firewalls.
ESP8266WebServer server ( 80 );


const char *controlForm =
"<table>"
"<tr>"
"<td></td><td><form action='/'><input type='submit' value='MF' name='action'> </form></td><td></td>"
"</tr>"
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
  else if (server.arg("action") == "MF") {
    digitalWrite(fireAll, HIGH);
  }
  else{
    digitalWrite(fireAll, LOW);
    digitalWrite(brakeMotorA, HIGH);
  }
  server.send(200, "text/html",  controlForm);
 }



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


   // pinMode(LED_BUILTIN, OUTPUT);

   pinMode(dirMotorA, OUTPUT);
   pinMode(brakeMotorA, OUTPUT);
   pinMode(speedMotorA, OUTPUT);
   pinMode(dirMotorB, OUTPUT);
   pinMode(brakeMotorB, OUTPUT);
   pinMode(speedMotorB, OUTPUT);
   pinMode(fireAll, OUTPUT);

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