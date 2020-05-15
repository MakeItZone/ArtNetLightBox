#include "ArtNetInterface.h"

ArtNetInterface::ArtNetInterface(/* args */)
{
     strcpy(universeChar, "1");
    universe = 1; //artnet universe
    universe2 = 2;

}

void ArtNetInterface::artNetCallback(uint8_t* data, uint16_t size)
{
    // you can also use pre-defined callbacks
}

ArtNetInterface::~ArtNetInterface()
{
}
