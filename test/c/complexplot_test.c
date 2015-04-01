#include "srsgui/srsgui.h"
#include <unistd.h>
#include <complex.h>
#include <math.h>

#define PI     3.14159265358979323846
#define N      1024

int main(int argc, char **argv) {
  _Complex float data[N];
  _Complex float temp[N];
  int i,j;

  sdrgui_init();

  plot_complex_t p;
  plot_complex_init(&p);
  plot_complex_setTitle(&p, "Float");
  plot_complex_setXAxisRange(&p,0,2);
  plot_complex_setYAxisScale(&p,Magnitude, 0.9, 1.1);

  float step = 2.0*PI/N;
  for(i=0; i<N; i++)
    data[i] = cos(step*i) + sin(step*i)*_Complex_I;

  plot_complex_setNewData(&p, data, N);

  for(i=0; i<N; i++)
  {
    for(j=0; j<N; j++)
      temp[(j-i+N)%N] = data[j];
    plot_complex_setNewData(&p, temp, N);
    usleep(1000);
  }

  sdrgui_exit();
}
