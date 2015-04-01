#include "ScatterplotWrapper.h"

#include "ScatterWidget.h"
#include "srsgui/common/Events.h"
#include <qapplication.h>
#include <QThread>
#include <QGridLayout>
#include <complex>

using namespace std;


ScatterplotWrapper::ScatterplotWrapper()
    :widget_(NULL)
    ,destroyed_(true)
{
  if(QCoreApplication::instance() == NULL)
    return; //TODO: throw exception here in Iris
  if(QCoreApplication::instance()->thread() == QThread::currentThread())
  {
    connect( this, SIGNAL(createWidgetSignal()),
             this, SLOT(createWidgetSlot()) );
    connect( this, SIGNAL(destroyWidgetSignal()),
             this, SLOT(destroyWidgetSlot()) );
    connect( this, SIGNAL( destroyWidgetSignalBlocking() ),
             this, SLOT(destroyWidgetSlot()) );
  }
  else
  {
    connect( this, SIGNAL(createWidgetSignal()),
             this, SLOT(createWidgetSlot()),
             Qt::BlockingQueuedConnection );
    connect( this, SIGNAL(destroyWidgetSignal()),
             this, SLOT(destroyWidgetSlot()) );
    connect( this, SIGNAL( destroyWidgetSignalBlocking() ),
             this, SLOT(destroyWidgetSlot()),
             Qt::BlockingQueuedConnection );
    moveToThread(QCoreApplication::instance()->thread());
  }
  emit createWidgetSignal();
}

ScatterplotWrapper::~ScatterplotWrapper()
{
  if(destroyed_)
    emit destroyWidgetSignal();
  else
    emit destroyWidgetSignalBlocking();
}

void ScatterplotWrapper::createWidgetSlot()
{
  widget_ = new ScatterWidget;

  destroyed_ = false;
  widget_->setAttribute(Qt::WA_DeleteOnClose, true);
  connect(widget_, SIGNAL( destroyed() ),
          this, SLOT( widgetDestroyed() ));
  connect(this, SIGNAL(addToWindowSignal(QString, int, int)),
          this, SLOT(addToWindowSlot(QString, int, int)));
  connect(this, SIGNAL(setWidgetXAxisScale(double,double)),
          widget_, SLOT(setWidgetXAxisScale(double,double)));
  connect(this, SIGNAL(setWidgetYAxisScale(double,double)),
          widget_, SLOT(setWidgetYAxisScale(double,double)));
  connect(this, SIGNAL(setWidgetXAxisAutoScale(bool)),
          widget_, SLOT(setWidgetXAxisAutoScale(bool)));
  connect(this, SIGNAL(setWidgetYAxisAutoScale(bool)),
          widget_, SLOT(setWidgetYAxisAutoScale(bool)));
  connect(this, SIGNAL(setWidgetTitle(QString)),
          widget_, SLOT(setWidgetTitle(QString)));
  connect(this, SIGNAL(setWidgetAxisLabels(QString, QString)),
          widget_, SLOT(setWidgetAxisLabels(QString, QString)));

  widget_->resize( 800, 600 );
  widget_->show();
}

void ScatterplotWrapper::destroyWidgetSlot()
{
  delete widget_;
}

void ScatterplotWrapper::widgetDestroyed()
{
  destroyed_ = true;
}

void ScatterplotWrapper::addToWindow(std::string window, int row, int column)
{
  emit addToWindowSignal(QString::fromStdString(window), row, column);
}

void ScatterplotWrapper::addToWindowSlot(QString window, int row, int column)
{
  if(destroyed_)
    return;
  if(window != "")
  {
    QWidgetList widgets = qApp->topLevelWidgets();
    for(QWidgetList::iterator i = widgets.begin(); i != widgets.end(); ++i)
    {
      if ((*i)->objectName() == window)
      {
        QGridLayout *l = (QGridLayout*)(*i)->layout();
        if(row<0)    row    = l->count()/3;
        if(column<0) column = l->count()%3;
        l->addWidget(widget_, row, column);
        return;
      }
    }

    QWidget *p = new QWidget();
    p->setObjectName(window);
    QGridLayout *layout = new QGridLayout();
    p->setLayout(layout);
    if(row<0)    row    = 0;
    if(column<0) column = 0;
    layout->addWidget(widget_, row, column);
    p->show();
  }
}

void ScatterplotWrapper::setNewData(complex<double>* data, int numPoints)
{
  if(destroyed_)
    return;
  qApp->postEvent(widget_, new ComplexDataEvent(data, numPoints));
}

void ScatterplotWrapper::setNewData(complex<float>* data, int numPoints)
{
  if(destroyed_)
    return;
  qApp->postEvent(widget_, new ComplexDataEvent(data, numPoints));
}

void ScatterplotWrapper::setTitle(std::string title)
{
  if(destroyed_)
    return;
  QString str = QString::fromUtf8(title.c_str());
  emit setWidgetTitle(str);
}

void ScatterplotWrapper::setXAxisScale(double xMin, double xMax)
{
  if(destroyed_)
    return;
  emit setWidgetXAxisScale(xMin, xMax);
}

void ScatterplotWrapper::setYAxisScale(double yMin, double yMax)
{
  if(destroyed_)
    return;
  emit setWidgetYAxisScale(yMin, yMax);
}

void ScatterplotWrapper::setXAxisAutoScale(bool on=true)
{
  if(destroyed_)
    return;
  emit setWidgetXAxisAutoScale(on);
}

void ScatterplotWrapper::setYAxisAutoScale(bool on=true)
{
  if(destroyed_)
    return;
  emit setWidgetYAxisAutoScale(on);
}

void ScatterplotWrapper::setAxisLabels(std::string xLabel, std::string yLabel)
{
  if(destroyed_)
    return;
  QString xStr = QString::fromUtf8(xLabel.c_str());
  QString yStr = QString::fromUtf8(yLabel.c_str());
  emit setWidgetAxisLabels(xStr, yStr);
}

