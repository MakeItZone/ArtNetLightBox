#ifndef ARTNETINTERFACE_H
#define ARTNETINTERFACE_H

#include <Artnet.h>

class ArtNetInterface
{
private:
    /* data */
    ArtnetReceiver artnet;

    char universeChar[6];
    uint16_t universe; //artnet universe
    uint32_t universe2;

public:
    ArtNetInterface(/* args */);

    void artNetCallback(uint8_t* data, uint16_t size);

    ~ArtNetInterface();
};

#endif
