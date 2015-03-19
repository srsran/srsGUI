#ifndef _plot_complex_h
#define _plot_complex_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "libsdrgui/common/config.h"

typedef enum {
  Ip, Q, Magnitude, Phase
} plot_complex_id_t;

typedef void* plot_complex_t;

LIBSDRGUI_API int  plot_complex_init(plot_complex_t *h);
LIBSDRGUI_API void plot_complex_setTitle(plot_complex_t *h, char *title);
LIBSDRGUI_API void plot_complex_setNewData(plot_complex_t *h, _Complex float *data, int num_points);
LIBSDRGUI_API void plot_complex_setXAxisAutoScale(plot_complex_t *h, plot_complex_id_t id, bool on);
LIBSDRGUI_API void plot_complex_setYAxisAutoScale(plot_complex_t *h, plot_complex_id_t id, bool on);
LIBSDRGUI_API void plot_complex_setXAxisScale(plot_complex_t *h, plot_complex_id_t id, double xMin, double xMax);
LIBSDRGUI_API void plot_complex_setYAxisScale(plot_complex_t *h, plot_complex_id_t id, double yMin, double yMax);
LIBSDRGUI_API void plot_complex_setXAxisRange(plot_complex_t *h, double xMin, double xMax);
LIBSDRGUI_API void plot_complex_addToWindow(plot_complex_t *h, char *window);
LIBSDRGUI_API void plot_complex_addToWindowGrid(plot_complex_t *h, char *window, int row, int column);

#ifdef __cplusplus
}
#endif

#endif
