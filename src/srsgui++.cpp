#include "srsgui/srsgui++.h"
#include <stdio.h>
#include <QApplication>
#include <unistd.h>

pthread_t threadxx;
static int sdrgui_initiatedxx=0;

void *qt_threadxx(void *arg)
{
  int argc = 1;
  char* argv[] = { const_cast<char *>((char*) arg), NULL };
  QApplication app(argc, argv);
  app.exec();
  pthread_exit(NULL);
}

int sdrgui_init() {
  return sdrgui_init_title("Software Radio Systems, Ltd");
}

int sdrgui_init_title(const char *window_title) {
  if (!window_title) {
    window_title="Software Radio Systems, Ltd";
  }
  if(!sdrgui_initiatedxx)
  {
    /** FIXME: Set attributes to detachable */
    if (pthread_create(&threadxx, NULL, qt_threadxx, (void*) window_title))
    {
      perror("phtread_create");
      return -1;
    }
    usleep(100000);
    sdrgui_initiatedxx=1;
	}
	return 0;
}

void sdrgui_exit() {
  if(sdrgui_initiatedxx)
  {
    usleep(100000);
    pthread_cancel(threadxx);
    pthread_join(threadxx, NULL);
	}
  sdrgui_initiatedxx=0;
}
