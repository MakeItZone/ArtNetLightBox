#include <SoftwareSerial.h>
#include <Artnet.h>
#include <RingBuffer.h>

// declarations for Ethernet/WiFi

uint32_t universe = 1;
const uint16_t size = 512;
uint8_t data [size];// = {50, 25, 10, 89};
uint8_t value = 0;

const char* ssid = "MakeItZone";
const char* pwd = "26EBF7gv5tfV";
const IPAddress ip(192, 168, 1, 102);
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
    value = millis()%256;
    memset(data, value, size);
    // change send data as you want
    //data[1]++; //= data[1] + 1;
    Serial.println(data[1]);

    artnet.set(universe, data, size);
    artnet.streaming(); // automatically send set data in 40fps
}
