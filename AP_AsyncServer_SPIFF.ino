/*********
  Based on Rui Santos project
  Modified by Joaquín 17/02/2024
*********/

// Import required libraries
#include <Arduino.h>
#include <AsyncTCP.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Replace with your network credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String ledState = "off"; // Stores LED state
String output23State = "off"; // Yellow
String output22State = "off"; // Red
String output21State = "off"; // Green
String output19State = "off"; // Blue
String output18State = "off"; // X
String output5State = "off"; // Y
String output17State = "off"; // Z
String output16State = "off"; // something

// Assign output variables to GPIO pins
const int ledPin = 2; // Set LED GPIO
const int output23 = 23;
const int output22 = 22;
const int output21 = 21;
const int output19 = 19;
const int output18 = 18;
const int output5 = 5;
const int output17 = 17;
const int output16 = 16;


// Replaces placeholder with LED state value
String processor(const String& var) // toma lo que esta en el placedolder , es decir %STATE%
{
  Serial.print("\n--------------\n");
  Serial.print("processor()\n");
  Serial.println(var);
  Serial.print("\n");
  if( var == "STATE2")
  {
    if(digitalRead(ledPin))
    {
      ledState = "ON";
    }
    else
    {
      ledState = "OFF";
    }
      Serial.print("\nledState:\n");
      Serial.print(ledState);
      Serial.print("\n");
      return ledState;
  }
else if (var == "STATE23")
{
      if (digitalRead(output23))
      {
        output23State = "ON";
      }
      else
      {
        output23State = "OFF";
      }
    Serial.print("\noutput23State:\t");
    Serial.print(output23State);
    Serial.print("\n");
    return output23State;
}
else if (var == "STATE22")
{
  if (digitalRead(output22))
  {
    output22State = "ON";
  }
  else
  {
    output22State = "OFF";
  }
  Serial.print("\noutput22State:\t");
  Serial.print(output22State);
  Serial.print("\n");
  return output22State;
}

else if (var == "STATE21")
{
  if (digitalRead(output21))
  {
    output21State = "ON";
  }
  else
  {
    output21State = "OFF";
  }
  Serial.print("\noutput21State:\t");
  Serial.print(output21State);
  Serial.print("\n");
  return output21State;
}
else if (var == "STATE19")
{
  if (digitalRead(output19))
  {
    output19State = "ON";
  }
  else
  {
    output19State = "OFF";
  }
  Serial.print("\noutput19State:\t");
  Serial.print(output19State);
  Serial.print("\n");
  return output19State;
}
else if (var == "STATE18")
{
  if (digitalRead(output18))
  {
    output18State = "ON";
  }
  else
  {
    output18State = "OFF";
  }
  Serial.print("\noutput18State:\t");
  Serial.print(output18State);
  Serial.print("\n");
  return output18State;
}
else if (var == "STATE5")
{
  if (digitalRead(output5))
  {
    output5State = "ON";
  }
  else
  {
    output5State = "OFF";
  }
  Serial.print("\noutput5State:\t");
  Serial.print(output5State);
  Serial.print("\n");
  return output5State;
}
else if (var == "STATE17")
{
  if (digitalRead(output17))
  {
    output17State = "ON";
  }
  else
  {
    output17State = "OFF";
  }
  Serial.print("\noutput17State:\t");
  Serial.print(output17State);
  Serial.print("\n");
  return output17State;
}
else if (var == "STATE16")
{
  if (digitalRead(output16))
  {
    output16State = "ON";
  }
  else
  {
    output16State = "OFF";
  }
  Serial.print("\noutput16State:\t");
  Serial.print(output16State);
  Serial.print("\n");
  return output16State;
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
  pinMode(output18,OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output17, OUTPUT);
  pinMode(output16, OUTPUT);

  // Set outputs to LOW
  digitalWrite(output23, LOW);
  digitalWrite(output22, LOW);
  digitalWrite(output21, LOW);
  digitalWrite(output19, LOW);
  digitalWrite(output18, LOW);
  digitalWrite(output5, LOW);
  digitalWrite(output17, LOW);
  digitalWrite(output16, LOW);
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("...Setting AP (Access Point)...");
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

  // Route to load style.css file
  server.on("/style.css", 
            HTTP_GET,
            [](AsyncWebServerRequest *request)
            {
              request->send(SPIFFS, "/style.css", "text/css");
            }
            );
            
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

// Route to load image
/* explicación de estas líneas:
https://techtutorialsx.com/2018/01/01/esp8266-arduino-asynchronous-http-web-server/
*/
server.on("/uaa-logo.jpg", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              // Esta expresión sirve como una función lambda, 'handling function'
              request->send(SPIFFS, "/uaa-logo.jpg", "image/jpg");
            }
            );
server.on("/casa-inteligente.jpg", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              // Esta expresión sirve como una función lambda, 'handling function'
              request->send(SPIFFS, "/casa-inteligente.jpg", "image/jpg");
            }
            );

  // Route to set GPIO  (LED 2) to HIGH
  server.on("/2on", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
                
              digitalWrite(ledPin, HIGH);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
              //                                                     processor - is the "AwsTemplateProcessor"
              // The lambda here is taking a const String &var as parameter such as the AwsTemplateProcessor, and we precise the return type of the AwsTemplateProcessor function by writing -> String after the lambda prototype. By precising the parameters and the return type correctly the send method can relate the lambda to the std::function (AwsTemplateProcessor).
            }
            );
  
  // Route to set GPIO (LED 2) to LOW
  server.on("/2off", // 
            HTTP_GET, //
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(ledPin, LOW);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

  // Route to set GPIO  23 to HIGH
  server.on("/23on", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              // listen on Serial monitor
              int paramsNr = request->params();
              Serial.println(paramsNr);
              for(int i=0;i<paramsNr;i++){
                  AsyncWebParameter* p = request->getParam(i);
                  Serial.print("Param name: ");
                  Serial.println(p->name());
                  Serial.print("Param value: ");
                  Serial.println(p->value());
                  Serial.println("------");
              }
              digitalWrite(output23, HIGH);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );
  
  // Route to set GPIO 23 to LOW
  server.on("/23off", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output23, LOW);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

  // Route to set GPIO 22 to HIGH
  server.on("/22on", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output22, HIGH);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

  // Route to set GPIO 22 to LOW
  server.on("/22off", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output22, LOW);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );
  // Route to set GPIO 21 to HIGH
  server.on("/21on", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output21, HIGH);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

  // Route to set GPIO 21 to LOW
  server.on("/21off", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output21, LOW);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

  // Route to set GPIO 19 to HIGH
  server.on("/19on", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output19, HIGH);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

  // Route to set GPIO 19 to LOW
  server.on("/19off", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output19, LOW);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

  // Route to set GPIO 18 to HIGH
  server.on("/18on", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output18, HIGH);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

  // Route to set GPIO 18 to LOW
  server.on("/18off", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output18, LOW);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );
  // Route to set GPIO 5 to HIGH
  server.on("/5on", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output5, HIGH);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

  // Route to set GPIO 5 to LOW
  server.on("/5off", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output5, LOW);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

// Route to set GPIO 17 to HIGH
  server.on("/17on", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output17, HIGH);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

  // Route to set GPIO 17 to LOW
  server.on("/17off", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output17, LOW);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );
// Route to set GPIO 16 to HIGH
  server.on("/16on", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output16, HIGH);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

  // Route to set GPIO 16 to LOW
  server.on("/16off", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(output16, LOW);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );

  // Start server
  server.begin(); // este debería ser el bueno
}

void loop(){}
