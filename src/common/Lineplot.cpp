#include "srsgui/common/Lineplot.h"
#include <algorithm>

template<class T>
T& deref(T* p) { return *p; }

template<class T>
T& deref(T& r) { return r; }

class MyZoomer: public QwtPlotZoomer
{
public:
    MyZoomer(QwtPlotCanvas *canvas):
        QwtPlotZoomer(canvas, true)
    {
        setTrackerMode(AlwaysOn);
    }

    virtual QwtText trackerTextF(const QPointF &pos) const
    {
        QColor bg(Qt::white);
        bg.setAlpha(200);

        QwtText text = QwtPlotZoomer::trackerTextF(pos);
        text.setBackgroundBrush( QBrush( bg ));
        return text;
    }
};

Lineplot::Lineplot(QWidget *parent)
  :QwtPlot(parent)
  ,xMin_(0)
  ,xMax_(0)
{
  counter_ = 0;
  numPoints_ = 1;
  indexPoints_ = new double[numPoints_];
  dataPoints_ = new double[numPoints_];

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QPalette palette;
  palette.setColor(canvas()->backgroundRole(), QColor("black"));
  canvas()->setPalette(palette);

  curve_ = new QwtPlotCurve("Curve");
  curve_->setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  curve_->setStyle(QwtPlotCurve::Lines);
  curve_->setRawSamples(indexPoints_, dataPoints_, numPoints_);
  curve_->setYAxis(QwtPlot::yLeft);
  curve_->attach(this);

  memset(dataPoints_, 0x0, numPoints_*sizeof(double));
  for(int i=0;i<numPoints_;i++)
    indexPoints_[i] = i;

  enableAxis(QwtPlot::yRight);
  QwtScaleWidget *leftAxis = axisWidget(QwtPlot::yLeft);
  connect(leftAxis, SIGNAL(scaleDivChanged()), this, SLOT(linkScales()));

  setAxisScaleEngine(QwtPlot::xBottom, new QwtLinearScaleEngine);
  setAxisScaleEngine(QwtPlot::yLeft, new QwtLinearScaleEngine);
  setAxisScaleEngine(QwtPlot::yRight, new QwtLinearScaleEngine);

  axisScaleEngine(QwtPlot::xBottom)->setAttribute(QwtScaleEngine::Floating,true);
  axisScaleEngine(QwtPlot::yLeft)->setAttribute(QwtScaleEngine::Floating,true);
  axisScaleEngine(QwtPlot::yRight)->setAttribute(QwtScaleEngine::Floating,true);

  zoomer_ = new MyZoomer(qobject_cast<QwtPlotCanvas*>(canvas()));
  zoomer_->setMousePattern(QwtEventPattern::MouseSelect1, Qt::LeftButton);
  zoomer_->setMousePattern(QwtEventPattern::MouseSelect2, Qt::LeftButton,
                           Qt::ControlModifier);

  panner_ = new QwtPlotPanner(canvas());
  panner_->setMouseButton(Qt::RightButton);

  magnifier_ = new QwtPlotMagnifier(canvas());
  magnifier_->setMouseButton(Qt::NoButton);

}

Lineplot::~Lineplot()
{
  delete[] indexPoints_;
  delete[] dataPoints_;
}

void Lineplot::setData(double* data, int n)
{
  if(numPoints_ != n)
  {
    numPoints_ = n;
    delete[] indexPoints_;
    delete[] dataPoints_;
    indexPoints_ = new double[numPoints_];
    dataPoints_ = new double[numPoints_];
    if(xMin_==xMax_)
    {
      for(int i=0;i<numPoints_;i++)
        indexPoints_[i] = i;
    }
    else
    {
      double step = (xMax_-xMin_)/numPoints_;
      double val = xMin_;
      for(int i=0;i<numPoints_;i++,val+=step)
        indexPoints_[i] = val;
    }
  }

  memcpy(dataPoints_, data, numPoints_*sizeof(double));
  //Need to setRawSamples again for autoscaling to work
  curve_->setRawSamples(indexPoints_, dataPoints_, numPoints_);
  resetZoom();
}

void Lineplot::setXAxisRange(double xMin, double xMax)
{
  xMin_ = xMin;
  xMax_ = xMax;
  double step = (xMax_-xMin_)/numPoints_;
  double val = xMin_;
  for(int i=0;i<numPoints_;i++,val+=step)
    indexPoints_[i] = val;
  curve_->setRawSamples(indexPoints_, dataPoints_, numPoints_);
}

void Lineplot::resetZoom()
{
  zoomer_->setZoomBase(curve_->boundingRect());
}

void Lineplot::linkScales()
{
  setAxisScaleDiv(QwtPlot::yRight, deref(axisScaleDiv(QwtPlot::yLeft)));
}
