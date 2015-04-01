#include "srsgui/plot/plot_scatter.h"
#include "srsgui/plot/Scatterplot.h"
#include <complex>



int plot_scatter_init(plot_scatter_t *h) {
	*h = (void*) new Scatterplot();
	return (*h != NULL)?0:-1;
}

void plot_scatter_setTitle(plot_scatter_t *h, char *title) {
	Scatterplot *plot = static_cast<Scatterplot*>(*h);
	plot->setTitle(title);
}
void plot_scatter_setNewData(plot_scatter_t *h, _Complex float *data,
		int num_points) {
	Scatterplot *plot = static_cast<Scatterplot*>(*h);
	plot->setNewData(reinterpret_cast<std::complex<float>*> (data), num_points);

}

void plot_scatter_setXAxisAutoScale(plot_scatter_t *h, bool on) {
	Scatterplot *plot = static_cast<Scatterplot*>(*h);
	plot->setXAxisAutoScale(on);
}

void plot_scatter_setYAxisAutoScale(plot_scatter_t *h, bool on) {
	Scatterplot *plot = static_cast<Scatterplot*>(*h);
	plot->setYAxisAutoScale(on);
}

void plot_scatter_setXAxisScale(plot_scatter_t *h, double xMin, double xMax) {
	Scatterplot *plot = static_cast<Scatterplot*>(*h);
	plot->setXAxisScale(xMin, xMax);
}

void plot_scatter_setYAxisScale(plot_scatter_t *h, double yMin, double yMax) {
	Scatterplot *plot = static_cast<Scatterplot*>(*h);
	plot->setYAxisScale(yMin, yMax);
}

void plot_scatter_setAxisLabels(plot_scatter_t *h, char *xLabel, char *yLabel) {
	Scatterplot *plot = static_cast<Scatterplot*>(*h);
	plot->setAxisLabels(xLabel, yLabel);
}

void plot_scatter_addToWindow(plot_scatter_t *h, char *window){
  Scatterplot *plot = static_cast<Scatterplot*>(*h);
  plot->addToWindow(window);
}

void plot_scatter_addToWindowGrid(plot_scatter_t *h, char *window, int row, int column){
  Scatterplot *plot = static_cast<Scatterplot*>(*h);
  plot->addToWindow(window, row, column);
}
