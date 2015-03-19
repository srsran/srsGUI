#ifndef _plot_scatter_h
#define _plot_scatter_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "libsdrgui/common/config.h"

typedef void* plot_scatter_t;

LIBSDRGUI_API int plot_scatter_init(plot_scatter_t *h);
LIBSDRGUI_API void plot_scatter_setTitle(plot_scatter_t *h, char *title);
LIBSDRGUI_API void plot_scatter_setNewData(plot_scatter_t *h, _Complex float *data, int num_points);
LIBSDRGUI_API void plot_scatter_setXAxisAutoScale(plot_scatter_t *h, bool on);
LIBSDRGUI_API void plot_scatter_setYAxisAutoScale(plot_scatter_t *h, bool on);
LIBSDRGUI_API void plot_scatter_setXAxisScale(plot_scatter_t *h, double xMin, double xMax);
LIBSDRGUI_API void plot_scatter_setYAxisScale(plot_scatter_t *h, double yMin, double yMax);
LIBSDRGUI_API void plot_scatter_setAxisLabels(plot_scatter_t *h, char *xLabel, char *yLabel);
LIBSDRGUI_API void plot_scatter_addToWindow(plot_scatter_t *h, char *window);
LIBSDRGUI_API void plot_scatter_addToWindowGrid(plot_scatter_t *h, char *window, int row, int column);

#ifdef __cplusplus
}
#endif

#endif
