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

## Explicaciones

- [https://techtutorialsx.com/2017/12/17/esp32-arduino-http-server-getting-query-parameters/](https://techtutorialsx.com/2017/12/17/esp32-arduino-http-server-getting-query-parameters/)

**server.on *method***

```objc
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
- About [fenced block in MD](https://www.w3schools.io/file/markdown-code-fence-blocks/)

 **send *method***

send back a response to the client, we just need to call the send 
method of the AsyncWebServerRequest object that we receive 
on our handling function.
```objc
request->send(SPIFFS, "/index.html", String(), false, processor);
```

- This method receives as first input the HTTP return code, 
which will be 200 (OK) for our example.
- Second argument, it receives the content-type
- Third argument we will pass the actual content to be returned to the client.


**¿Qué pedo con String processor(const String& var, int pin, String& pinState)?**
[Respuesta](https://stackoverflow.com/questions/1943276/what-does-do-in-a-c-declaration)
The "&" denotes a reference instead of a pointer to an object (In your case a constant reference). 

[REspuesta 2](https://stackoverflow.com/questions/59575326/passing-a-function-as-a-parameter-within-a-class)

[Respuesta 3](https://community.platformio.org/t/how-data-is-passed-in-the-send-methods-of-espasyncwebserver-when-a-query-is-made/31113/2)
the last argument is indeed a function reference / pointer to a “processor”; taking in a constant String reference and returning a String.

**What is a class method?**

Pendiente




In C++,

    A::B means B is an identifier within either namespace or class type A, 

### Definiciones

- [TCP](https://www.hostinger.es/tutoriales/protocolo-tcp): El Protocolo de Control de Transmisión (Transmission Control Protocol en inglés o TCP) es el método de comunicación de datos por defecto entre distintos dispositivos, a través de una red.

## Pendientes

- [X] Reparar lo que ocurre al presiona el GPIO 23
- [ ] Agregar estilo y clases en *css*  para las imagenes
- [ ] Fix placeholder for each output
