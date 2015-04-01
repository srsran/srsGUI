#include "srsgui/srsgui.h"
#include <unistd.h>
#include <math.h>

#define PI     3.14159265358979323846
#define N      1024

int main(int argc, char **argv) {
  float data[N*2];
  int i,j;
  double step;

  step = 2.0*PI/N;
  for(i=0;i<N*2;i++)
    data[i] = sin(step*i);

  sdrgui_init();

  plot_waterfall_t p;
  plot_waterfall_init(&p, N, N);
  plot_waterfall_setTitle(&p, "Float");

  for(i=0; i<N; i++)
  {
    plot_waterfall_appendNewData(&p, data+i, N);
    usleep(1000);
  }

  sdrgui_exit();
}
