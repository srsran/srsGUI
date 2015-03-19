#ifndef _libsdrgui_h
#define _libsdrgui_h

#ifdef __cplusplus
extern "C" {
#endif

#include "libsdrgui/plot/plot_real.h"
#include "libsdrgui/plot/plot_scatter.h"
#include "libsdrgui/plot/plot_complex.h"
#include "libsdrgui/plot/plot_waterfall.h"

int  sdrgui_init();
void sdrgui_exit();

#ifdef __cplusplus
}
#endif

#endif
