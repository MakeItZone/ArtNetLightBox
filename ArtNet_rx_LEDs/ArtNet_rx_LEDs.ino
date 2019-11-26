#include <SoftwareSerial.h>
#include <Artnet.h>

const int ledOnboard = 0;
const int Rled = 12; // red led pin
const int Rin = 2; //red intake channel
const int Gled = 13; // green led pin
const int Gin = 3; //green intake channel
const int Bled = 14; // blue led pin
const int Bin = 4; //blue intake channel

// WiFi stuff
const char* ssid = "MakeItZone";
const char* pwd = "26EBF7gv5tfV";
const IPAddress ip(192, 168, 1, 201); //the ip that this is using
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

ArtnetReceiver artnet;
const uint32_t universe1 = 1;
//const uint32_t universe2 = 2;

void callback(uint8_t* data, uint16_t size)
{
    // you can also use pre-defined callbacks
}

void setup()
{
    pinMode (ledOnboard, OUTPUT); //led output declarations
    pinMode (Rled, OUTPUT);
    pinMode (Gled, OUTPUT);
    pinMode (Bled, OUTPUT);
    analogWriteRange(255);
    
    Serial.begin(115200);

    // WiFi stuffs
    WiFi.begin(ssid, pwd);
    WiFi.config(ip, gateway, subnet);
    while (WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(500); }
    Serial.print("WiFi connected, IP = "); Serial.println(WiFi.localIP());

    artnet.begin();

    // if Artnet packet comes to this universe, this function (lambda) is called
    artnet.subscribe(universe1, [&](uint8_t* data, uint16_t size)
    {
        Serial.print("lambda : artnet data (universe : ");
        Serial.print(universe1);
        Serial.println(") = ");
        
        analogWrite(ledOnboard, data[0]); //write to LEDs
        analogWrite(Rled, data[1]);
        analogWrite(Gled, data[2]);
        analogWrite(Bled, data[3]);
        
        for (size_t i = 0; i < 4; ++i)
        {
            Serial.print(i); Serial.print(","); Serial.print(data[i]); Serial.print(",");
        }
        Serial.println();
    });

    // you can also use pre-defined callbacks
    //artnet.subscribe(universe2, callback);
}

void loop()
{
    artnet.parse(); // check if artnet packet has come and execute callback
}
