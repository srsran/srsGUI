#include "srsgui/plot/text_edit.h"
#include "srsgui/plot/TextEdit.h"


int text_edit_init(text_edit_t *h) {
	*h = (void*) new TextEdit();
	return (*h != NULL)?0:-1;
}

void text_edit_addToWindowGrid(text_edit_t *h, char *window, int row, int column){
  TextEdit *plot = static_cast<TextEdit*>(*h);
  plot->addToWindow(window, row, column);
}

void text_edit_addToWindow(text_edit_t *h, char *window){
  TextEdit *plot = static_cast<TextEdit*>(*h);
  plot->addToWindow(window);
}

void text_edit_appendMessage(text_edit_t *h, char *message)
{
  TextEdit *plot = static_cast<TextEdit*>(*h);
  plot->appendMessage(message);
}

void text_edit_setMessage(text_edit_t *h, char *message)
{
  TextEdit *plot = static_cast<TextEdit*>(*h);
  plot->setMessage(message);
}

void text_edit_setTitle(text_edit_t *h, char *title)
{
  TextEdit *plot = static_cast<TextEdit*>(*h);
  plot->setTitle(title);
}
