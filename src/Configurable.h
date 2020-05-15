#ifndef CONFIGURABLE_H
#define CONFIGURABLE_H

#include <vector>
#include <memory>

#include "ConfigItem.h"
#include <ArduinoJson.h>

using namespace std;
    
class Configurable
{

private:
bool running = false;

protected:

vector<shared_ptr<ConfigItem>> *configItems;

public:
    Configurable(/* args */);
    ~Configurable();

/**
 * @brief if config is null or fails, create default
 * 
 * Don't forget to call Start()
 */
virtual void LoadConfigFromJSON(const DynamicJsonDocument &jsonDoc) =0;

/**
 * @brief Update stored config based on ConfigItems
 * 
 */
virtual void SaveConfigAsJSON(DynamicJsonDocument &jsonDoc) const =0;



/* 
*   Return the current configuration as a reference to vector of shared pointers to ConfigItems.
*   We use a vector, so the number of items can be dynamic at runtime.
*   shared_ptr because we expect these items to be added to another vector (e.g. used in a set of UI widgets...) but 
*   don't want them destroyed/invalidated before we have the chance to update our internal configuration.
*/
virtual vector<shared_ptr<ConfigItem>> &GetConfig() =0;


/**
 * @brief commit the config to the instance- should call stop/start and free the ConfigItems
 * 
 */
virtual void SetConfig() =0;

/**
 * @brief start the service
 * 
 */
virtual void Start();

/**
 * @brief stop the service
 * 
 */
virtual void Stop();



protected:


};

#endif
