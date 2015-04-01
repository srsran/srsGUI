#ifndef _plot_waterfall_h
#define _plot_waterfall_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef void* plot_waterfall_t;

int plot_waterfall_init(plot_waterfall_t *h, int numDataPoints, int numRows);
void plot_waterfall_setTitle(plot_waterfall_t *h, char *title);
void plot_waterfall_appendNewData(plot_waterfall_t *h, float *data, int num_points);
void plot_complex_setPlotXLabel(plot_waterfall_t *h, char *xLabel);
void plot_complex_setPlotYLabel(plot_waterfall_t *h, char *yLabel);
void plot_waterfall_setPlotXAxisRange(plot_waterfall_t *h, double xMin, double xMax);
void plot_waterfall_setPlotXAxisScale(plot_waterfall_t *h, double xMin, double xMax);
void plot_waterfall_setPlotYAxisScale(plot_waterfall_t *h, double yMin, double yMax);
void plot_waterfall_setSpectrogramXLabel(plot_waterfall_t *h, char* xLabel);
void plot_waterfall_setSpectrogramYLabel(plot_waterfall_t *h, char* yLabel);
void plot_waterfall_setSpectrogramXAxisRange(plot_waterfall_t *h, double xMin, double xMax);
void plot_waterfall_setSpectrogramYAxisRange(plot_waterfall_t *h, double yMin, double yMax);
void plot_waterfall_setSpectrogramZAxisScale(plot_waterfall_t *h, double zMin, double zMax);
void plot_waterfall_addToWindow(plot_waterfall_t *h, char *window);
void plot_waterfall_addToWindowGrid(plot_waterfall_t *h, char *window, int row, int column);


#ifdef __cplusplus
}
#endif

#endif
