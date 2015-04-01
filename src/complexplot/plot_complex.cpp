#include "srsgui/plot/plot_complex.h"
#include "srsgui/plot/Complexplot.h"
#include <complex>


int plot_complex_init(plot_complex_t *h) {
	*h = (void*) new Complexplot();
	return (*h != NULL)?0:-1;
}

void plot_complex_setTitle(plot_complex_t *h, char *title) {
	Complexplot *plot = static_cast<Complexplot*>(*h);
	plot->setTitle(title);
}

void plot_complex_setNewData(plot_complex_t *h, _Complex float *data,
		int num_points) {
	Complexplot *plot = static_cast<Complexplot*>(*h);
	plot->setNewData(reinterpret_cast<std::complex<float>*> (data), num_points);
}


void plot_complex_setXAxisAutoScale(plot_complex_t *h, plot_complex_id_t id, bool on) {
	Complexplot *plot = static_cast<Complexplot*>(*h);
	plot->setXAxisAutoScale(static_cast<Complexplot::PlotId> (id), on);
}

void plot_complex_setYAxisAutoScale(plot_complex_t *h, plot_complex_id_t id, bool on) {
	Complexplot *plot = static_cast<Complexplot*>(*h);
	plot->setYAxisAutoScale(static_cast<Complexplot::PlotId> (id), on);
}

void plot_complex_setXAxisScale(plot_complex_t *h, plot_complex_id_t id, double xMin, double xMax) {
	Complexplot *plot = static_cast<Complexplot*>(*h);
	plot->setXAxisScale(static_cast<Complexplot::PlotId> (id), xMin, xMax);
}

void plot_complex_setYAxisScale(plot_complex_t *h, plot_complex_id_t id, double yMin, double yMax) {
	Complexplot *plot = static_cast<Complexplot*>(*h);
	plot->setYAxisScale(static_cast<Complexplot::PlotId> (id), yMin, yMax);
}

void plot_complex_setXAxisRange(plot_complex_t *h, double xMin, double xMax) {
	Complexplot *plot = static_cast<Complexplot*>(*h);
	plot->setXAxisRange(xMin, xMax);
}

void plot_complex_addToWindow(plot_complex_t *h, char *window){
  Complexplot *plot = static_cast<Complexplot*>(*h);
  plot->addToWindow(window);
}

void plot_complex_addToWindowGrid(plot_complex_t *h, char *window, int row, int column){
  Complexplot *plot = static_cast<Complexplot*>(*h);
  plot->addToWindow(window, row, column);
}
