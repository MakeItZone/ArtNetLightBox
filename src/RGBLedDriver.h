#ifndef RGBLEDDRIVER_H
#define RGBLEDDRIVER_H

#include "ConfigItem.h"
#include "Configurable.h"

class RGBLedDriver:Configurable
{
private:
    // these are all allocated as part of an instance of this class
    // unless they are STATIC - in which case there is one copy for the CLASS, ie shared by all instances.
    int pwmMax;
    int ledOnboard; //onboard LED pin
    char ledOnboardChar[4]; //ditto char
    int ledOnboardIn; //onboard LED intake channel
    char ledOnboardInChar[4];
    int Rled; //red led pin
    char RledChar[4];
    int Rin; //red intake channel
    char RinChar[4];
    int Gled; //green led pin
    char GledChar[4];
    int Gin; //green intake channel
    char GinChar[4];
    int Bled; //blue led pin
    char BledChar[4];
    int Bin; //blue intake channel
    char BinChar[4];
    
public:
    RGBLedDriver(/* args */);

    ~RGBLedDriver();

    void LoadConfigFromJSON(const DynamicJsonDocument &jsonDoc) override;
    void SaveConfigAsJSON(DynamicJsonDocument &jsonDoc) const override;

    vector<shared_ptr<ConfigItem>> &GetConfig() override;
    void SetConfig() override;

    void Start();
    void Stop();

};

#endif
