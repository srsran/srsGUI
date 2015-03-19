#ifndef _plot_scatter_h
#define _plot_scatter_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef void* plot_scatter_t;

int plot_scatter_init(plot_scatter_t *h);
void plot_scatter_setTitle(plot_scatter_t *h, char *title);
void plot_scatter_setNewData(plot_scatter_t *h, _Complex float *data, int num_points);
void plot_scatter_setXAxisAutoScale(plot_scatter_t *h, bool on);
void plot_scatter_setYAxisAutoScale(plot_scatter_t *h, bool on);
void plot_scatter_setXAxisScale(plot_scatter_t *h, double xMin, double xMax);
void plot_scatter_setYAxisScale(plot_scatter_t *h, double yMin, double yMax);
void plot_scatter_setAxisLabels(plot_scatter_t *h, char *xLabel, char *yLabel);
void plot_scatter_addToWindow(plot_scatter_t *h, char *window);
void plot_scatter_addToWindowGrid(plot_scatter_t *h, char *window, int row, int column);

#ifdef __cplusplus
}
#endif

#endif
