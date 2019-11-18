#include <SoftwareSerial.h>
#include <Artnet.h>
#include <RingBuffer.h>

// declarations for Ethernet/WiFi

int universe = 1;
uint8_t data [4] = {50, 25, 10, 89};
uint8_t size = 4;

const char* ssid = "MakeItZone";
const char* pwd = "26EBF7gv5tfV";
const IPAddress ip(192, 168, 1, 200);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

ArtnetSender artnet;

void setup()
{
    Serial.begin(9600);
    // setup Ethernet/WiFi...

    //wifi stuffs
        WiFi.begin(ssid, pwd);
    WiFi.config(ip, gateway, subnet);
    while (WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(500); }
    Serial.print("WiFi connected, IP = "); Serial.println(WiFi.localIP());

    artnet.begin("192.168.1.180"); //destination ip
    Serial.println("enter value for transmission");
}

void loop()
{
    // change send data as you want
    uint8_t data [4] = {Serial.read(), 25, 10, 89};

    artnet.set(universe, data, size);
    artnet.streaming(); // automatically send set data in 40fps
}
