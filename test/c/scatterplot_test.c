#include "srsgui/srsgui.h"
#include <unistd.h>
#include <complex.h>
#include <stdlib.h>

#define N      1024

int main(int argc, char **argv) {
  _Complex float data[N];
  int i,j;

  sdrgui_init();

  plot_scatter_t p;
  plot_scatter_init(&p);
  plot_scatter_setTitle(&p, "Float");
  plot_scatter_addToWindow(&p, "parent");

  plot_scatter_t p2;
  plot_scatter_init(&p2);
  plot_scatter_setTitle(&p2, "Float");
  plot_scatter_addToWindow(&p2, "parent");

  for(i=0; i<N; i++)
  {
    for(j=0;j<N;j++)
    {
      float r = 2*((double)rand()/RAND_MAX)-1;
      float i = 2*((double)rand()/RAND_MAX)-1;
      data[j] = r+i*_Complex_I;
    }
    plot_scatter_setNewData(&p, data, N);
    plot_scatter_setNewData(&p2, data, N);
    usleep(1000);
  }

  sdrgui_exit();
}

