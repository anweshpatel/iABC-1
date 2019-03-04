
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

void setup() {
    pinMode(LED_BUILTIN, OUTPUT); //Initialise the board LED
    
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
    WiFiMulti.addAP("Nokia 6.1", "conv0142");

}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http; //new client object created

        USE_SERIAL.print("[HTTP] begin...\n");
        
        // configure server and url
        //http.begin("http://api.thingspeak.com/channels/565397/fields/1.json?api_key=P8R8KTQ6DQ5UO117&results=1"); //HTTP
        http.begin("http://192.168.43.218:8080/iot?reqtype=fetch");
        
        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        //If no errors, we can retrieve the information and work on it
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();//Extract JSON file
                USE_SERIAL.println(payload);

                int index = payload.indexOf("LED");
                USE_SERIAL.println(index);
                //Extract the value for LED
                String newpl = payload.substring(index+6);
                USE_SERIAL.println(newpl);
                String fin = newpl.substring(0, newpl.indexOf("\""));
                USE_SERIAL.println(fin);
                int finnum = fin.toInt();
                //extracted value
                USE_SERIAL.println(finnum);

                //We have now extracted the field value
                //Use this value finnum to control LED

                if(finnum == 0){
                    digitalWrite(LED_BUILTIN, HIGH);
                    delay(2000);
                }

                else if(finnum == 1){
                    digitalWrite(LED_BUILTIN, LOW);
                    delay(2000);
                 }
            }
        } 
        else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(1000);
}
