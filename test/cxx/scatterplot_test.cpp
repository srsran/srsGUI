#define BOOST_TEST_MODULE Scatterplot_Test

#include "srsgui/srsgui++.h"

#include <boost/scoped_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/progress.hpp>
#include <boost/bind.hpp>
#include <cstdlib>
#include <complex>
#include <vector>
#include <boost/test/unit_test.hpp>

typedef std::complex<float> Cplx;
typedef std::vector<Cplx>   CplxVec;

template<class T>
void getPoints(std::complex<T>* data, int numPoints)
{
  for(int i=0;i<numPoints;i++)
  {
    data[i] = std::complex<T>(2*((T)rand()/RAND_MAX)-1,
                              2*((T)rand()/RAND_MAX)-1);
  }
}

template<class Iterator>
void getPoints(Iterator begin, Iterator end)
{
  for(;begin!=end;begin++)
  {
    float r = 2*((double)rand()/RAND_MAX)-1;
    float i = 2*((double)rand()/RAND_MAX)-1;
    *begin = Cplx(r,i);
  }
}

void threadMain1()
{
  Scatterplot plot;
  std::complex<float> data[1024];

  for(int i=0;i<10;i++)
  {
    getPoints(data, 1024);
    plot.setNewData(data, 1024);
    boost::this_thread::sleep(boost::posix_time::milliseconds(100));
  }
}

void threadMain2()
{
  Scatterplot plot;
  std::complex<double> data[1024];

  for(int i=0;i<10;i++)
  {
    getPoints(data, 1024);
    plot.setNewData(data, 1024);
    boost::this_thread::sleep(boost::posix_time::milliseconds(100));
  }
}

void threadMain3()
{
  Scatterplot plot;
  CplxVec v(1024);

  for(int i=0;i<10;i++)
  {
    getPoints(v.begin(), v.end());
    plot.setNewData(v.begin(), v.end());
    boost::this_thread::sleep(boost::posix_time::milliseconds(100));
  }
}

BOOST_AUTO_TEST_SUITE (Scatterplot_Test)

BOOST_AUTO_TEST_CASE(Scatterplot_Basic_Test)
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
