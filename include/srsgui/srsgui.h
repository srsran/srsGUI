#ifndef _srsgui_h
#define _srsgui_h

#ifdef __cplusplus
extern "C" {
#endif

#include "srsgui/plot/plot_real.h"
#include "srsgui/plot/plot_scatter.h"
#include "srsgui/plot/plot_complex.h"
#include "srsgui/plot/plot_waterfall.h"
#include "srsgui/plot/text_edit.h"
#include "srsgui/plot/key_value.h"

int  sdrgui_init();
int  sdrgui_init_title(const char *window_title);
void sdrgui_exit();

#ifdef __cplusplus
}
#endif

#endif
