#include "srsgui/common/Events.h"

using namespace std;

const QEvent::Type RealDataEvent::type = static_cast<QEvent::Type>(10000);

RealDataEvent::RealDataEvent(double* dataPoints, int numPoints)
  : QEvent(QEvent::Type(type))
{
  dataPoints_ = new double[numPoints];
  numPoints_ = numPoints;
  memcpy(dataPoints_, dataPoints, numPoints*sizeof(double));
}

RealDataEvent::RealDataEvent(float* dataPoints, int numPoints)
  : QEvent(QEvent::Type(type))
{
  dataPoints_ = new double[numPoints];
  numPoints_ = numPoints;

  for(int i=0;i<numPoints_;i++)
  {
    dataPoints_[i] = (double)(dataPoints[i]);
  }
}

RealDataEvent::~RealDataEvent()
{
  delete[] dataPoints_;
}


const QEvent::Type ComplexDataEvent::type = static_cast<QEvent::Type>(10001);

ComplexDataEvent::ComplexDataEvent(complex<double>* dataPoints,
                                   int numPoints)
  : QEvent(QEvent::Type(type))
{
  dataPoints_ = new complex<double>[numPoints];
  numPoints_ = numPoints;
  memcpy(dataPoints_, dataPoints, numPoints*sizeof(complex<double>));
}

ComplexDataEvent::ComplexDataEvent(complex<float>* dataPoints,
                                   int numPoints)
  : QEvent(QEvent::Type(type))
{
  dataPoints_ = new complex<double>[numPoints];
  numPoints_ = numPoints;

  for(int i=0;i<numPoints_;i++)
  {
    dataPoints_[i] = complex<double>(dataPoints[i].real(),
                                     dataPoints[i].imag());
  }
}

ComplexDataEvent::~ComplexDataEvent()
{
  delete[] dataPoints_;
}
