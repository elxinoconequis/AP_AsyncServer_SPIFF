/*********
  Based on Rui Santos project
  Modified by Joaquín 17/02/2024
*********/

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Replace with your network credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

// Set LED GPIO
const int ledPin = 2;

// Stores LED state
String ledState;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output23State = "off"; // Yellow
String output22State = "off"; // Red
String output21State = "off"; // Green
String output19State = "off"; // Blue

// Assign output variables to GPIO pins
const int output23 = 23;
const int output22 = 22;
const int output21 = 21;
const int output19 = 19;


// Replaces placeholder with LED state value
// TODO: Add argument to switch GPIO 
String processor(const String& var)
{
  Serial.println(var);
  if( var == "STATE")
  {
    if(digitalRead(ledPin))
    {
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }
  return String();
}
 
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(output23, OUTPUT);
  pinMode(output22, OUTPUT);
  pinMode(output21, OUTPUT);
  pinMode(output19, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output23, LOW);
  digitalWrite(output22, LOW);
  digitalWrite(output21, LOW);
  digitalWrite(output19, LOW);
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  // Initialize SPIFFS
  if(!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return; 
  }

  Serial.println("Local IP Adress");
  Serial.println(WiFi.localIP());

  // Route for root / web page from 'AsyncWebServer' *request is pointer
  server.on("/", // server.on sirve para ver si hacemos un POST, GET U otro
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              // Esta expresión sirve como una función lambda
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

  // Note: The member access operators . and -> are used to refer to members of struct, union, and class types.
  // https://www.geeksforgeeks.org/arrow-operator-in-c-c-with-examples/
  
  
  // Route to load style.css file
  server.on("/style.css", 
            HTTP_GET,
            [](AsyncWebServerRequest *request)
            {
              request->send(SPIFFS, "/style.css", "text/css");
            }
            );

  // Route to set GPIO  (LED 2) to HIGH
  server.on("/on", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(ledPin, HIGH);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );
  
  // Route to set GPIO (LED 2) to LOW
  server.on("/off", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(ledPin, LOW);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

  //TODO: Add functions for pins 23,22,21,19,18,5,17,16
  // Route to set GPIO  23 to HIGH
  server.on("/23/on", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output23, HIGH);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );
  
  // Route to set GPIO 23 to LOW
  server.on("/23/off", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output23, LOW);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );


  // Start server
  server.begin(); // este debería ser el bueno
}
 // ---------------------------------------------------------------
void loop(){
}
