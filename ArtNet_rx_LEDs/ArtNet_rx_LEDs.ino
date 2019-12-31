#include <FS.h>
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include <SoftwareSerial.h>
#include <EEPROM.h>

#include <Artnet.h>

const int pwmMax = 255;

const int ledOnboard = 0; //onboard LED pin
const int ledOnboardIn = 0; //onboard LED intake channel
const int Rled = 12; //red led pin
const int Rin = 1; //red intake channel
const int Gled = 13; //green led pin
const int Gin = 2; //green intake channel
const int Bled = 14; //blue led pin
const int Bin = 3; //blue intake channel

const int resetSwitch = 5;

bool shouldSaveConfig = false; //flag for saving data

// IP stuffs
IPAddress ip;

ArtnetReceiver artnet;
char universeChar[6] = "1";
uint16_t universe = 1; //artnet universe
//const uint32_t universe2 = 2;

void artNetCallback(uint8_t* data, uint16_t size)
{
    // you can also use pre-defined callbacks
}

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void readConfigFile() {
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");
          strcpy(universeChar, json["universe"]);
          universe = atoi(universeChar);
        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read
}

void setup()
{
    pinMode (resetSwitch, INPUT_PULLUP);
    pinMode (ledOnboard, OUTPUT); //led output declarations
    pinMode (Rled, OUTPUT);
    pinMode (Gled, OUTPUT);
    pinMode (Bled, OUTPUT);
    analogWriteRange(pwmMax);
    
    Serial.begin(115200);
    Serial.println();

    readConfigFile();

    // WiFi stuffs
    WiFiManagerParameter artNetUniverse("universe", "artnet universe", universeChar, 6);
    WiFiManagerParameter artNetUniverseLabel("<p>Art-Net universe</p>");
    WiFiManager wifiManager;
    wifiManager.setSaveConfigCallback(saveConfigCallback);
    wifiManager.addParameter(&artNetUniverseLabel);
    wifiManager.addParameter(&artNetUniverse);

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

    String apName = String("lightbox" + String(ESP.getChipId()));
    Serial.println("apName = " + apName);
    wifiManager.autoConnect(apName.c_str());

    strcpy(universeChar, artNetUniverse.getValue());
    if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["universe"] = universeChar;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  }
    
    ip = WiFi.localIP();
    Serial.println(ip);

    artnet.begin();

    // if Artnet packet comes to this universe, this function (lambda) is called
    artnet.subscribe(universe, [&](uint8_t* data, uint16_t size)
    {
        Serial.print("lambda : artnet data (universe : ");
        Serial.print(universe);
        Serial.println(") = ");
        
        analogWrite(ledOnboard, pwmMax - data[ledOnboardIn]); //write to LEDs
        analogWrite(Rled, data[Rin]);
        analogWrite(Gled, data[Gin]);
        analogWrite(Bled, data[Bin]);
        
        for (size_t i = 0; i < 4; ++i) //the 4 on this line is how many channels are sent to the serial monitor, you can change it to be whatever you want, but if it is too big everything will grind to a halt.
        {
            //Serial.print(i); Serial.print(","); Serial.print(data[i]); Serial.print(",");
        }
        //Serial.println();
    });

    //you can also use pre-defined callbacks
    //artnet.subscribe(universe2, artNetCallback);
}

void loop()
{
    artnet.parse(); // check if artnet packet has come and execute callback
}
