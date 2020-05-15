#include "ConfigItem.h"

ConfigItem::ConfigItem(const string &id, const string &placeholder, const string &label, const string &defaultValue, const int valueLength, const string &customHTML) : 
  _id(id), _placeholder(placeholder), _label(label), _value(defaultValue), _value_length(valueLength), _customHTML(customHTML) 
  {}

ConfigItem::ConfigItem(const string &id, const string &placeholder, const string &label, const string &defaultValue, const int valueLength) : 
  _id(id), _placeholder(placeholder), _label(label), _value(defaultValue), _value_length(valueLength), _customHTML() 
  {}

ConfigItem::~ConfigItem() {
}

const string & ConfigItem::GetValue() {
  return _value;
}
const string & ConfigItem::GetID() {
  return _id;
}
const string & ConfigItem::GetPlaceholder() {
  return _placeholder;
}

const string & ConfigItem::GetLabel() {
  return _label;
}

int ConfigItem::GetValueLength() {
  return _value_length;
}

const string & ConfigItem::GetCustomHTML() {
  return _customHTML;
}
