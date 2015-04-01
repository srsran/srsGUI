#include "srsgui/plot/plot_waterfall.h"
#include "srsgui/plot/Waterfallplot.h"
#include <complex.h>


int plot_waterfall_init(plot_waterfall_t *h, int numDataPoints, int numRows) {
	*h = (void*) new Waterfallplot(numDataPoints, numRows);
	return (*h != NULL)?0:-1;
}

void plot_waterfall_setTitle(plot_waterfall_t *h, char *title) {
	Waterfallplot *plot = static_cast<Waterfallplot*>(*h);
	plot->setTitle(title);
}

void plot_waterfall_appendNewData(plot_waterfall_t *h, float *data,
		int num_points) {
	Waterfallplot *plot = static_cast<Waterfallplot*>(*h);
	plot->appendNewData(data, num_points);
}

void plot_complex_setPlotXLabel(plot_waterfall_t *h, char *xLabel) {
	Waterfallplot *plot = static_cast<Waterfallplot*>(*h);
	plot->setPlotXLabel(xLabel);
}

void plot_complex_setPlotYLabel(plot_waterfall_t *h, char *yLabel) {
	Waterfallplot *plot = static_cast<Waterfallplot*>(*h);
	plot->setPlotXLabel(yLabel);
}

void plot_waterfall_setPlotXAxisRange(plot_waterfall_t *h, double xMin, double xMax) {
	Waterfallplot *plot = static_cast<Waterfallplot*>(*h);
	plot->setPlotXAxisRange(xMin, xMax);
}

void plot_waterfall_setPlotXAxisScale(plot_waterfall_t *h, double xMin, double xMax) {
	Waterfallplot *plot = static_cast<Waterfallplot*>(*h);
	plot->setPlotXAxisScale(xMin, xMax);
}

void plot_waterfall_setPlotYAxisScale(plot_waterfall_t *h, double yMin, double yMax) {
	Waterfallplot *plot = static_cast<Waterfallplot*>(*h);
	plot->setPlotYAxisScale(yMin, yMax);
}


void plot_waterfall_setSpectrogramXLabel(plot_waterfall_t *h, char* xLabel) {
	Waterfallplot *plot = static_cast<Waterfallplot*>(*h);
	plot->setSpectrogramXLabel(xLabel);
}

void plot_waterfall_setSpectrogramYLabel(plot_waterfall_t *h, char* yLabel) {
	Waterfallplot *plot = static_cast<Waterfallplot*>(*h);
	plot->setSpectrogramYLabel(yLabel);
}

void plot_waterfall_setSpectrogramXAxisRange(plot_waterfall_t *h, double xMin, double xMax) {
	Waterfallplot *plot = static_cast<Waterfallplot*>(*h);
	plot->setSpectrogramXAxisRange(xMin, xMax);
}

void plot_waterfall_setSpectrogramYAxisRange(plot_waterfall_t *h, double yMin, double yMax) {
	Waterfallplot *plot = static_cast<Waterfallplot*>(*h);
	plot->setSpectrogramYAxisRange(yMin, yMax);
}

void plot_waterfall_setSpectrogramZAxisScale(plot_waterfall_t *h, double zMin, double zMax) {
	Waterfallplot *plot = static_cast<Waterfallplot*>(*h);
	plot->setSpectrogramZAxisScale(zMin, zMax);
}

void plot_waterfall_addToWindow(plot_waterfall_t *h, char *window){
  Waterfallplot *plot = static_cast<Waterfallplot*>(*h);
  plot->addToWindow(window);
}

void plot_waterfall_addToWindowGrid(plot_waterfall_t *h, char *window, int row, int column){
  Waterfallplot *plot = static_cast<Waterfallplot*>(*h);
  plot->addToWindow(window, row, column);
}
