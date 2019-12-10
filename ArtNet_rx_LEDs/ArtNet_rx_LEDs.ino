#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include <SoftwareSerial.h>
#include <EEPROM.h>

#include <Artnet.h>

const int ledOnboard = 0; //onboard LED pin
const int ledOnboardIn = 1; //onboard LED intake channel
const int Rled = 12; //red led pin
const int Rin = 2; //red intake channel
const int Gled = 13; //green led pin
const int Gin = 3; //green intake channel
const int Bled = 14; //blue led pin
const int Bin = 4; //blue intake channel

const int resetSwitch = 5;

// IP stuffs
IPAddress ip;

ArtnetReceiver artnet;
const uint32_t universe1 = 1;
//const uint32_t universe2 = 2;

void callback(uint8_t* data, uint16_t size)
{
    // you can also use pre-defined callbacks
}

void setup()
{
    pinMode (resetSwitch, INPUT_PULLUP);
    pinMode (ledOnboard, OUTPUT); //led output declarations
    pinMode (Rled, OUTPUT);
    pinMode (Gled, OUTPUT);
    pinMode (Bled, OUTPUT);
    analogWriteRange(255);
    
    Serial.begin(115200);
    Serial.println();

    // WiFi stuffs
    WiFiManager wifiManager;
    
    if(digitalRead(resetSwitch) == LOW) { //reset
      bool ledState = true;
      Serial.println("resetting wifi...");
      for(int i = 0; i < 10; i++) {
        digitalWrite(Gled, ledState);
        ledState = !ledState;
        delay(500);
      }
      wifiManager.resetSettings();
    }
    
    wifiManager.autoConnect();
    ip = WiFi.localIP();
    Serial.println(ip);

    artnet.begin();

    // if Artnet packet comes to this universe, this function (lambda) is called
    artnet.subscribe(universe1, [&](uint8_t* data, uint16_t size)
    {
        Serial.print("lambda : artnet data (universe : ");
        Serial.print(universe1);
        Serial.println(") = ");
        
        analogWrite(ledOnboard, data[ledOnboardIn]); //write to LEDs
        analogWrite(Rled, data[Rin]);
        analogWrite(Gled, data[Gin]);
        analogWrite(Bled, data[Bin]);
        
        for (size_t i = 0; i < 4; ++i) //the 4 on this line is how many channels are sent to the serial monitor, you can change it to be whatever you want, but if it is too big everything will grind to a halt.
        {
            Serial.print(i); Serial.print(","); Serial.print(data[i]); Serial.print(",");
        }
        Serial.println();
    });

    //you can also use pre-defined callbacks
    //artnet.subscribe(universe2, callback);
}

void loop()
{
    artnet.parse(); // check if artnet packet has come and execute callback
}
