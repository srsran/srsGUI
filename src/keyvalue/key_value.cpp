#include "srsgui/plot/key_value.h"
#include "srsgui/plot/KeyValue.h"


int key_value_init(key_value_t *h) {
	*h = (void*) new KeyValue();
	return (*h != NULL)?0:-1;
}

void key_value_addToWindowGrid(key_value_t *h, char *window, int row, int column){
  KeyValue *plot = static_cast<KeyValue*>(*h);
  plot->addToWindow(window, row, column);
}

void key_value_addToWindow(key_value_t *h, char *window){
  KeyValue *plot = static_cast<KeyValue*>(*h);
  plot->addToWindow(window);
}

void key_value_setKeyText(key_value_t *h, char *txt)
{
  KeyValue *plot = static_cast<KeyValue*>(*h);
  plot->setKeyText(txt);
}

void key_value_setValueText(key_value_t *h, char *txt)
{
  KeyValue *plot = static_cast<KeyValue*>(*h);
  plot->setValueText(txt);
}
