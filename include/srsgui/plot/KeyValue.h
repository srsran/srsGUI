#ifndef KEYVALUE_H
#define KEYVALUE_H

#include <string>

class KeyValueWrapper;

class KeyValue
{
public:
  KeyValue();
  ~KeyValue();

  void addToWindow(std::string window, int row=-1, int column=-1);
  void setKeyText(std::string txt);
  void setValueText(std::string txt);

private:
  KeyValueWrapper* plot_;
};

#endif // KEYVALUE_H
