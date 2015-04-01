#include "RealplotWrapper.h"

#include "RealWidget.h"
#include "srsgui/common/Events.h"
#include <qapplication.h>
#include <QThread>
#include <QGridLayout>

RealplotWrapper::RealplotWrapper()
    :widget_(NULL)
    ,destroyed_(true)
{
  if(QCoreApplication::instance() == NULL)
    return; //TODO: throw exception here in Iris
  if(QCoreApplication::instance()->thread() == QThread::currentThread())
  {
    connect( this, SIGNAL( createWidgetSignal() ),
             this, SLOT(createWidgetSlot()) );
    connect( this, SIGNAL( destroyWidgetSignal() ),
             this, SLOT(destroyWidgetSlot()) );
    connect( this, SIGNAL( destroyWidgetSignalBlocking() ),
             this, SLOT(destroyWidgetSlot()) );
  }
  else
  {
    connect( this, SIGNAL( createWidgetSignal() ),
             this, SLOT(createWidgetSlot()),
             Qt::BlockingQueuedConnection );
    connect( this, SIGNAL( destroyWidgetSignal() ),
             this, SLOT(destroyWidgetSlot()) );
    connect( this, SIGNAL( destroyWidgetSignalBlocking() ),
             this, SLOT(destroyWidgetSlot()),
             Qt::BlockingQueuedConnection );
    moveToThread(QCoreApplication::instance()->thread());
  }
  emit createWidgetSignal();
}

RealplotWrapper::~RealplotWrapper()
{
  if(destroyed_)
    emit destroyWidgetSignal();
  else
    emit destroyWidgetSignalBlocking();
}

void RealplotWrapper::createWidgetSlot()
{
  widget_ = new RealWidget;

  destroyed_ = false;
  widget_->setAttribute(Qt::WA_DeleteOnClose, true);
  connect(widget_, SIGNAL( destroyed() ),
          this, SLOT( widgetDestroyed() ));
  connect(this, SIGNAL(addToWindowSignal(QString, int, int)),
          this, SLOT(addToWindowSlot(QString, int, int)));
  connect(this, SIGNAL(setWidgetTitle(QString)),
          widget_, SLOT(setWidgetTitle(QString)));
  connect(this, SIGNAL(setWidgetAxisLabels(QString, QString)),
          widget_, SLOT(setWidgetAxisLabels(QString, QString)));
  connect(this, SIGNAL(setWidgetXAxisScale(double,double)),
          widget_, SLOT(setWidgetXAxisScale(double,double)));
  connect(this, SIGNAL(setWidgetYAxisScale(double,double)),
          widget_, SLOT(setWidgetYAxisScale(double,double)));
  connect(this, SIGNAL(setWidgetXAxisAutoScale(bool)),
          widget_, SLOT(setWidgetXAxisAutoScale(bool)));
  connect(this, SIGNAL(setWidgetYAxisAutoScale(bool)),
          widget_, SLOT(setWidgetYAxisAutoScale(bool)));
  connect(this, SIGNAL(setWidgetXAxisRange(double,double)),
          widget_, SLOT(setWidgetXAxisRange(double,double)));

  widget_->resize( 800, 600 );
  widget_->show();
}

void RealplotWrapper::destroyWidgetSlot()
{
  delete widget_;
}

void RealplotWrapper::widgetDestroyed()
{
  destroyed_ = true;
}

void RealplotWrapper::addToWindow(std::string window, int row, int column)
{
  emit addToWindowSignal(QString::fromStdString(window), row, column);
}

void RealplotWrapper::addToWindowSlot(QString window, int row, int column)
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

void RealplotWrapper::setNewData(double* data, int numPoints)
{
  if(destroyed_)
    return;
  qApp->postEvent(widget_, new RealDataEvent(data, numPoints));
}

void RealplotWrapper::setNewData(float* data, int numPoints)
{
  if(destroyed_)
    return;
  qApp->postEvent(widget_, new RealDataEvent(data, numPoints));
}

void RealplotWrapper::setTitle(std::string title)
{
  if(destroyed_)
    return;
  QString str = QString::fromUtf8(title.c_str());
  emit setWidgetTitle(str);
}

void RealplotWrapper::setAxisLabels(std::string xLabel, std::string yLabel)
{
  if(destroyed_)
    return;
  QString xStr = QString::fromUtf8(xLabel.c_str());
  QString yStr = QString::fromUtf8(yLabel.c_str());
  emit setWidgetAxisLabels(xStr, yStr);
}

void RealplotWrapper::setXAxisScale(double xMin, double xMax)
{
  if(destroyed_)
    return;
  emit setWidgetXAxisScale(xMin, xMax);
}

void RealplotWrapper::setYAxisScale(double yMin, double yMax)
{
  if(destroyed_)
    return;
  emit setWidgetYAxisScale(yMin, yMax);
}

void RealplotWrapper::setXAxisAutoScale(bool on=true)
{
  if(destroyed_)
    return;
  emit setWidgetXAxisAutoScale(on);
}

void RealplotWrapper::setYAxisAutoScale(bool on=true)
{
  if(destroyed_)
    return;
  emit setWidgetYAxisAutoScale(on);
}

void RealplotWrapper::setXAxisRange(double xMin, double xMax)
{
  if(destroyed_)
    return;
  emit setWidgetXAxisRange(xMin, xMax);
}
