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
  //server.begin(); // podría estar al final, quiza. Esta linea viene de cuando hichimos el AP sencillo 

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
  /*
  // This is from the normal Acces point code
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /23/on") >= 0) 
            {

              //(string object method 'indexOf':  
              // * Locates a character or String within another String. By default, 
              //searches from the beginning of the String, but can also start from a given index, 
              //allowing for the locating of all instances of the character or String.
              
              Serial.println("GPIO 23 on");
              output23State = "on";
              digitalWrite(output23, HIGH);

            } else if (header.indexOf("GET /23/off") >= 0) {
              Serial.println("GPIO 23 off");
              output23State = "off";
              digitalWrite(output23, LOW);

            } else if (header.indexOf("GET /22/on") >= 0) {
              Serial.println("GPIO 22 on");
              output22State = "on";
              digitalWrite(output22, HIGH);

            } else if (header.indexOf("GET /22/off") >= 0) {
              Serial.println("GPIO 22 off");
              output22State = "off";
              digitalWrite(output22, LOW);

            } else if (header.indexOf("GET /21/on") >= 0){
              Serial.println("GPIO 21 on");
              output21State = "on";
              digitalWrite(output21,HIGH);

            } else if (header.indexOf("GET /21/off") >= 0){
              Serial.println("GPIO 21 off");
              output21State = "off";
              digitalWrite(output21, LOW);

            } else if (header.indexOf("GET /19/on") >= 0){
              Serial.println("GPIO 19 on");
              output19State = "on";
              digitalWrite(output19, HIGH);

            } else if (header.indexOf("GET /19/off") >= 0){
              Serial.println("GPIO 19 off");
              output19State = "off";
              digitalWrite(output19, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1> Universidad Autonoma de Aguascalientes</h1>");
            client.println("<h2>ESP32 Web Server</h2>");
            client.println("<h2> Ingenieria en Energias Renovables</h2>");

            
            // Display current state, and ON/OFF buttons for GPIO 23  
              client.println("<p>GPIO 23 - State " + output23State + "</p>");
              // If the output23State is off, it displays the ON button       
              if (output23State == "off") 
              {
                // ¿ PARA QUE SIRVE EL SIMBOLO '\' en este contexto?
                client.println("<p><a href=\"/23/on\"><button class=\"button\">ON</button></a></p>");
              } 
              else 
              {
                client.println("<p><a href=\"/23/off\"><button class=\"button button2\">OFF</button></a></p>");
              } 
               
            // Display current state, and ON/OFF buttons for GPIO 22  
              client.println("<p>GPIO 22 - State " + output22State + "</p>");
              // If the output27State is off, it displays the ON button       
              if (output22State =="off") 
              {
                client.println("<p><a href=\"/22/on\"><button class=\"button\">ON</button></a></p>");
              } 
              else 
              {
                client.println("<p><a href=\"/22/off\"><button class=\"button button2\">OFF</button></a></p>");
              }
            
            // Display current state, and ON/OFF buttons for GPIO 21  
              client.println("<p>GPIO 21 - State " + output21State + "</p>");
              // If the output27State is off, it displays the ON button       
              if (output21State == "off") 
              {
                client.println("<p><a href=\"/21/on\"><button class=\"button\">ON</button></a></p>");
              } 
              else 
              {
                client.println("<p><a href=\"/21/off\"><button class=\"button button2\">OFF</button></a></p>");
              }

            // Display current state, and ON/OFF buttons for GPIO 19
              client.println("<p>GPIO 19 - State " + output19State + "</p>");
              // If the output27State is off, it displays the ON button       
              if (output19State == "off") 
              {
                client.println("<p><a href=\"/19/on\"><button class=\"button\">ON</button></a></p>");
              } 
              else 
              {
                client.println("<p><a href=\"/19/off\"><button class=\"button button2\">OFF</button></a></p>");
              }
            
            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  */
}
