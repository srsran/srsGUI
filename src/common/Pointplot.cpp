#include "srsgui/common/Pointplot.h"
#include <algorithm>

using namespace std;

class MyZoomer: public QwtPlotZoomer
{
public:
    MyZoomer(QwtPlotCanvas *canvas):
        QwtPlotZoomer(canvas)
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

Pointplot::Pointplot(QWidget *parent)
  :QwtPlot(parent)
{
  counter_ = 0;
  numPoints_ = 1;
  realPoints_ = new double[numPoints_];
  imagPoints_ = new double[numPoints_];

  QPalette palette;
  palette.setColor(canvas()->backgroundRole(), QColor("black"));
  canvas()->setPalette(palette);

  setAxisScaleEngine(QwtPlot::xBottom, new QwtLinearScaleEngine);
  setAxisTitle(QwtPlot::xBottom, "In-phase");

  setAxisScaleEngine(QwtPlot::yLeft, new QwtLinearScaleEngine);
  setAxisTitle(QwtPlot::yLeft, "Quadrature");

  curve_ = new QwtPlotCurve("Constellation Points");
  curve_->attach(this);
  curve_->setPen(QPen(Qt::green, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  curve_->setStyle(QwtPlotCurve::Dots);
  curve_->setRawSamples(realPoints_, imagPoints_, numPoints_);

  memset(realPoints_, 0x0, numPoints_*sizeof(double));
  memset(imagPoints_, 0x0, numPoints_*sizeof(double));

  zoomer_ = new MyZoomer(qobject_cast<QwtPlotCanvas*>(canvas()));
  zoomer_->setMousePattern(QwtEventPattern::MouseSelect1, Qt::LeftButton);
  zoomer_->setMousePattern(QwtEventPattern::MouseSelect2, Qt::LeftButton,
                           Qt::ControlModifier);

  panner_ = new QwtPlotPanner(canvas());
  panner_->setMouseButton(Qt::RightButton);

  magnifier_ = new QwtPlotMagnifier(canvas());
  magnifier_->setMouseButton(Qt::NoButton);

}

Pointplot::~Pointplot()
{
  delete[] realPoints_;
  delete[] imagPoints_;
}

void Pointplot::setData(double* iData, double* qData, int n)
{
  if(numPoints_ != n)
  {
    numPoints_ = n;
    delete[] realPoints_;
    delete[] imagPoints_;
    realPoints_ = new double[numPoints_];
    imagPoints_ = new double[numPoints_];
  }

  copy(iData, iData+n, realPoints_);
  copy(qData, qData+n, imagPoints_);
  //Need to setRawSamples again for autoscaling to work
  curve_->setRawSamples(realPoints_, imagPoints_, numPoints_);
  zoomer_->setZoomBase(curve_->boundingRect());
}
