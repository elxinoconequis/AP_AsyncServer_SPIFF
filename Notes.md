# Notes

[About HTTP Requests](https://randomnerdtutorials.com/esp32-http-get-post-arduino/)

El programa se rompe cuando camioo de esado ell GPIO 23, pero no el 2

>
    Async Web Server
    The ESPAsyncWebServer library allows us to configure 
    the routes where the server will be listening for incoming 
    HTTP requests and execute functions when a request is received 
    on that route. For that, use the on() method on the server object as follows:
> 
    When the server receives a request on the root “/” URL, it will send the index.html file to the client. The last argument of the send() function is the processor, so that we are able to replace the placeholder for the value we want – in this case the ledState.

## Pendientes:

- [ ] Reparar lo que ocurre al presiona el GPIO 23
- [ ] Agregar estilo y clases en *css*  para las imagenes