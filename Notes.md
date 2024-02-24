# Notes

[About HTTP Requests](https://randomnerdtutorials.com/esp32-http-get-post-arduino/)

El programa se rompe cuando camioo de esado ell GPIO 23, pero no el 2

> Async Web Server
The ESPAsyncWebServer library allows us to configure
the routes where the server will be listening for incoming
HTTP requests and execute functions when a request is received
on that route. For that, use the on() method on the server object as follows:

Ver código

>When the server receives a request on the root “/” URL, it will send the index.html file to the client. The last argument of the send() function is the processor, so that we are able to replace the placeholder for the value we want – in this case the ledState.

**Explicaciones**

- [https://techtutorialsx.com/2017/12/17/esp32-arduino-http-server-getting-query-parameters/](https://techtutorialsx.com/2017/12/17/esp32-arduino-http-server-getting-query-parameters/)


**server.on *method***

```
server.on("/on", 
            HTTP_GET, 
            [](AsyncWebServerRequest *request)
            {
              digitalWrite(ledPin, HIGH);    
              request->send(SPIFFS, "/index.html", String(), false, processor);
            }
            );
```
- first input of this method, we pass a string with the route where the server will be listening for incoming requests
-  we need to pass an enumerated value which indicates the HTTP methods allowed on the route
- As third and final argument, the on method 
receives the handling function that will be executed upon 
receiving the request. This function needs to follow a 
fixed signature, more precisely, it needs to return void
and receive as input a pointer to an object of class AsyncWebServerRequest.

 **send *method***
 
send back a response to the client, we just need to call the send 
method of the AsyncWebServerRequest object that we receive 
on our handling function.
```
request->send(SPIFFS, "/index.html", String(), false, processor);
```
- This method receives as first input the HTTP return code, 
which will be 200 (OK) for our example.
- Second argument, it receives the content-type
- Third argument we will pass the actual content to be returned to the client.


## Pendientes

- [ ] Reparar lo que ocurre al presiona el GPIO 23
- [ ] Agregar estilo y clases en *css*  para las imagenes
