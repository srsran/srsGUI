#ifndef _key_value_h
#define _key_value_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef void* key_value_t;

int key_value_init(key_value_t *h);
void key_value_setKeyText(key_value_t *h, char *txt);
void key_value_setValueText(key_value_t *h, char *txt);
void key_value_addToWindowGrid(key_value_t *h, char *window, int row, int column);
void key_value_addToWindow(key_value_t *h, char *window);

#ifdef __cplusplus
}
#endif

#endif
