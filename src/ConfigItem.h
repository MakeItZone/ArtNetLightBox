#ifndef CONFIGITEM_H
#define CONFIGITEM_H

#include <string>

using namespace std;

/**
 * @brief Holds the details of a setting
 * 
 * This is based on `ArduinoJSON::ConfigItem`, modified to include a label.
 * 
 * Note that all parameters are references- ownership (memory management) is left to the caller.
 * (Don't delete them before ConfigItems referencing them are deleted!)
 * 
 * Only #_value is created and owned by ConfigItem; this must be copied out before deletion.
 *
 */
class ConfigItem
{
  private:
    const string _id; // unique name of data element
    const string _placeholder; // descriptive text that goes in UI fields
    const string _label; // descriptive text to go near UI input field
    string _value;
    const int _value_length;
    const string _customHTML;

  public:
    ConfigItem() = delete; // disallow default constructor
    ConfigItem(const string &id, const string &placeholder, const string &label, const string &defaultValue, const int valueLength);
    ConfigItem(const string &id, const string &placeholder, const string &label, const string &defaultValue, const int valueLength, const string &customHTML);
    ~ConfigItem();

    const string & GetID();
    const string & GetValue();
    const string & GetPlaceholder();
    const string & GetLabel();
    int GetValueLength();
    const string &GetCustomHTML();

};

#endif
