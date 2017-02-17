#include "srsgui/plot/KeyValue.h"
#include "KeyValueWrapper.h"

KeyValue::KeyValue()
{
  plot_ = new KeyValueWrapper();
}

KeyValue::~KeyValue()
{
  delete plot_;
}

void KeyValue::addToWindow(std::string window, int row, int column)
{
  plot_->addToWindow(window, row, column);
}

void KeyValue::setKeyText(std::string text)
{
  plot_->setKeyText(text);
}

void KeyValue::setValueText(std::string text)
{
  plot_->setValueText(text);
}
