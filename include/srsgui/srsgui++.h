#ifndef _srsguixx_h
#define _srsguixx_h

#include "srsgui/plot/Realplot.h"
#include "srsgui/plot/Scatterplot.h"
#include "srsgui/plot/Complexplot.h"
#include "srsgui/plot/Waterfallplot.h"
#include "srsgui/plot/TextEdit.h"
#include "srsgui/plot/KeyValue.h"

int  sdrgui_init();
int  sdrgui_init_title(const char *window_title);
void sdrgui_exit();

#endif
