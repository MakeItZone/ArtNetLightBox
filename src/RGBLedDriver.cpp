#include "RGBLedDriver.h"

RGBLedDriver::RGBLedDriver(/* args */)
{
    pwmMax = 255;
    ledOnboard = 0; //onboard LED pin
    ledOnboardChar[0]='\n';
    ledOnboardIn = 0; //onboard LED intake channel
    ledOnboardInChar[0]='\n';
    Rled = 12; //red led pin
    RledChar[0]='\n';
    Rin = 1; //red intake channel
    RinChar[0]='\n';
    Gled = 13; //green led pin
    GledChar[0]='\n';
    Gin = 2; //green intake channel
    GinChar[0]='\n';
    Bled = 14; //blue led pin
    BledChar[0]='\n';
    Bin = 3; //blue intake channel
    BinChar[0]='\n';

}

void RGBLedDriver::LoadConfigFromJSON(const DynamicJsonDocument &jsonDoc){

}

void RGBLedDriver::SaveConfigAsJSON(DynamicJsonDocument &jsonDoc) const {

}
vector<shared_ptr<ConfigItem>> & RGBLedDriver::GetConfig(){
    configItems = new vector<shared_ptr<ConfigItem>>;
    configItems->push_back( make_shared<ConfigItem>("pwm_max", "255", "Maximum PWM values", "255", 3));
    configItems->push_back( make_shared<ConfigItem>("onboard_led_pin", "0", "Pin for Onboard (diagnostic) LED", "0", 3));
    configItems->push_back( make_shared<ConfigItem>("red_channel_pin", "12", "Pin for red PWM output", "12", 3));
    configItems->push_back( make_shared<ConfigItem>("red_channel", "1", "ArtNET address for red channel", "1", 3));


    return *configItems;
}


void RGBLedDriver::SetConfig() {

}


RGBLedDriver::~RGBLedDriver()
{
}
