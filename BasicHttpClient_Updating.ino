/**
 * BasicHTTPClient.ino
 *
 *  Created on: 29.08.2018
 *  
 *  Anwesh Anjan Patel
 *  
 *  GET data from the server and turn the LED on/off
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

int var = 0;

void setup() {
    
    USE_SERIAL.begin(115200);
   // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("<ssid>", "<psk>");

}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {
        var += 1; //increament the counter
        if(var == 10){
            var = 0;
        }
        
        HTTPClient http; //new client object created

        //String UP_url = "http://api.thingspeak.com/update?api_key=K2MVSQ0PEVITCK98&field2=";
        //String url = UP_url + var;
        //String url = "<ip_addr>:8080/iot?";
        USE_SERIAL.print("[HTTP] begin...\n");
        
        // configure server and url
        http.begin(url); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        //If no errors, we can retrieve the information and work on it
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } 
        else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(5000);
}
