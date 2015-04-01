#include "srsgui/srsgui.h"
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#define N      1024

int main(int argc, char **argv) {
  float data[N];
  int i,j;

  sdrgui_init();

  plot_real_t p;
  plot_real_init(&p);
  plot_real_setTitle(&p, "Float");

  for(i=0; i<N; i++)
  {
    for(j=0;j<N;j++)
      data[j] = 10*((float)rand()/RAND_MAX);
    plot_real_setNewData(&p, data, N);
    usleep(1000);
  }

  sdrgui_exit();
}
