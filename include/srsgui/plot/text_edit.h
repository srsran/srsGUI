#ifndef _text_edit_h
#define _text_edit_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef void* text_edit_t;

int text_edit_init(text_edit_t *h);
void text_edit_appendMessage(text_edit_t *h, char *message);
void text_edit_setMessage(text_edit_t *h, char *message);
void text_edit_addToWindowGrid(text_edit_t *h, char *window, int row, int column);
void text_edit_addToWindow(text_edit_t *h, char *window);
void text_edit_setTitle(text_edit_t *h, char *title);

#ifdef __cplusplus
}
#endif

#endif
