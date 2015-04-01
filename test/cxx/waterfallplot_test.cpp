#define BOOST_TEST_MODULE Waterfallplot_Test

#include "srsgui/srsgui++.h"

#include <boost/scoped_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/progress.hpp>
#include <boost/bind.hpp>
#include <cstdlib>
#include <vector>
#include <boost/test/unit_test.hpp>

#define PI     3.14159265358979323846

using namespace std;

void threadMain1()
{
  int n=2048;
  Waterfallplot plot(n,n);
  plot.setTitle("Float");

  float step = 1.0*PI/n;
  float* data = new float[n*2];
  for(int i=0;i<n*2;i++)
    data[i] = sinf(step*i);

  for(int i=0;i<n;i++)
  {
    plot.appendNewData(data+i, n);
    boost::this_thread::sleep(boost::posix_time::milliseconds(1));
  }
}

void threadMain2()
{
  int n=2048;
  Waterfallplot plot(n,n);
  plot.setTitle("Double");

  double step = 2.0*PI/n;
  double* data = new double[n*2];
  for(int i=0;i<n*2;i++)
    data[i] = sin(step*i);

  for(int i=0;i<n;i++)
  {
    plot.appendNewData(data+i, n);
    boost::this_thread::sleep(boost::posix_time::milliseconds(1));
  }
}

void threadMain3()
{
  int n=2048;
  Waterfallplot plot(n,n);
  plot.setTitle("FloatVec");

  double step = 2.0*PI/n;
  std::vector<float> data;
  data.resize(n*2);
  for(int i=0;i<n*2;i++)
    data[i] = sin(step*i);

  for(int i=0;i<n;i++)
  {
    plot.appendNewData(data.begin()+i, data.begin()+i+n);
    boost::this_thread::sleep(boost::posix_time::milliseconds(1));
  }
}

BOOST_AUTO_TEST_SUITE (Waterfallplot_Test)

BOOST_AUTO_TEST_CASE(Waterfallplot_Init_Test)
{
  sdrgui_init();

  boost::scoped_ptr< boost::thread > thread1_;
  boost::scoped_ptr< boost::thread > thread2_;
  boost::scoped_ptr< boost::thread > thread3_;

  thread1_.reset( new boost::thread( &threadMain1 ) );
  thread2_.reset( new boost::thread( &threadMain2 ) );
  thread3_.reset( new boost::thread( &threadMain3 ) );

  thread1_->join();
  thread2_->join();
  thread3_->join();

  sdrgui_exit();
}

BOOST_AUTO_TEST_SUITE_END()
