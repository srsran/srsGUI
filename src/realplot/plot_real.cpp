#include "srsgui/plot/plot_real.h"
#include "srsgui/plot/Realplot.h"
#include <complex.h>


int plot_real_init(plot_real_t *h) {
	*h = (void*) new Realplot();
	return (*h != NULL)?0:-1;
}

void plot_real_setTitle(plot_real_t *h, char *title) {
	Realplot *plot = static_cast<Realplot*>(*h);
	plot->setTitle(title);
}
void plot_real_setNewData(plot_real_t *h, float *data,
		int num_points) {
	Realplot *plot = static_cast<Realplot*>(*h);
	plot->setNewData(data, num_points);

}

void plot_real_setXAxisAutoScale(plot_real_t *h, bool on) {
	Realplot *plot = static_cast<Realplot*>(*h);
	plot->setXAxisAutoScale(on);
}

void plot_real_setYAxisAutoScale(plot_real_t *h, bool on) {
	Realplot *plot = static_cast<Realplot*>(*h);
	plot->setYAxisAutoScale(on);
}

void plot_real_setXAxisScale(plot_real_t *h, double xMin, double xMax) {
	Realplot *plot = static_cast<Realplot*>(*h);
	plot->setXAxisScale(xMin, xMax);
}

void plot_real_setYAxisScale(plot_real_t *h, double yMin, double yMax) {
	Realplot *plot = static_cast<Realplot*>(*h);
	plot->setYAxisScale(yMin, yMax);
}

void plot_real_setXAxisRange(plot_real_t *h, double xMin, double xMax) {
	Realplot *plot = static_cast<Realplot*>(*h);
	plot->setXAxisRange(xMin, xMax);
}

void plot_real_setLabels(plot_real_t *h, char *xLabel, char *yLabel) {
	Realplot *plot = static_cast<Realplot*>(*h);
	plot->setLabels(xLabel, yLabel);
}

void plot_real_addToWindow(plot_real_t *h, char *window){
  Realplot *plot = static_cast<Realplot*>(*h);
  plot->addToWindow(window);
}

void plot_real_addToWindowGrid(plot_real_t *h, char *window, int row, int column){
  Realplot *plot = static_cast<Realplot*>(*h);
  plot->addToWindow(window, row, column);
}
