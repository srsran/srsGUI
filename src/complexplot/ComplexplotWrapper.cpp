#include "ComplexplotWrapper.h"

#include "ComplexWidget.h"
#include "srsgui/common/Events.h"
#include <qapplication.h>
#include <QThread>
#include <QGridLayout>

using namespace std;


ComplexplotWrapper::ComplexplotWrapper()
    :widget_(NULL)
    ,destroyed_(true)
{
  if(QCoreApplication::instance() == NULL)
    return; //TODO: throw exception here in Iris

  if(qApp->thread() == QThread::currentThread())
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

ComplexplotWrapper::~ComplexplotWrapper()
{
  if(destroyed_)
    emit destroyWidgetSignal();
  else
    emit destroyWidgetSignalBlocking();
}

void ComplexplotWrapper::createWidgetSlot()
{
  widget_ = new ComplexWidget;

  destroyed_ = false;
  widget_->setAttribute(Qt::WA_DeleteOnClose, true);
  connect(widget_, SIGNAL( destroyed() ),
          this, SLOT( widgetDestroyed() ));
  connect(this, SIGNAL(addToWindowSignal(QString, int, int)),
          this, SLOT(addToWindowSlot(QString, int, int)));
  connect(this, SIGNAL(setWidgetTitle(QString)),
          widget_, SLOT(setWidgetTitle(QString)));
  connect(this, SIGNAL(setWidgetXAxisScale(int,double,double)),
          widget_, SLOT(setWidgetXAxisScale(int,double,double)));
  connect(this, SIGNAL(setWidgetYAxisScale(int,double,double)),
          widget_, SLOT(setWidgetYAxisScale(int,double,double)));
  connect(this, SIGNAL(setWidgetXAxisAutoScale(int,bool)),
          widget_, SLOT(setWidgetXAxisAutoScale(int,bool)));
  connect(this, SIGNAL(setWidgetYAxisAutoScale(int,bool)),
          widget_, SLOT(setWidgetYAxisAutoScale(int,bool)));
  connect(this, SIGNAL(setWidgetXAxisRange(double,double)),
          widget_, SLOT(setWidgetXAxisRange(double,double)));

  widget_->resize( 800, 600 );
  widget_->show();
}

void ComplexplotWrapper::destroyWidgetSlot()
{
  if(widget_)
    delete widget_;
  widget_ = NULL;
}

void ComplexplotWrapper::widgetDestroyed()
{
  destroyed_ = true;
}

void ComplexplotWrapper::addToWindow(std::string window, int row, int column)
{
  emit addToWindowSignal(QString::fromStdString(window), row, column);
}

void ComplexplotWrapper::addToWindowSlot(QString window, int row, int column)
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

void ComplexplotWrapper::setNewData(complex<double>* data, int numPoints)
{
  if(destroyed_)
    return;
  qApp->postEvent(widget_, new ComplexDataEvent(data, numPoints));
}

void ComplexplotWrapper::setNewData(complex<float>* data, int numPoints)
{
  if(destroyed_)
    return;
  qApp->postEvent(widget_, new ComplexDataEvent(data, numPoints));
}

void ComplexplotWrapper::setTitle(std::string title)
{
  if(destroyed_)
    return;
  QString str = QString::fromUtf8(title.c_str());
  emit setWidgetTitle(str);
}

void ComplexplotWrapper::setXAxisAutoScale(int id, bool on=true)
{
  if(destroyed_)
    return;
  emit setWidgetXAxisAutoScale(id, on);
}

void ComplexplotWrapper::setYAxisAutoScale(int id, bool on=true)
{
  if(destroyed_)
    return;
  emit setWidgetYAxisAutoScale(id, on);
}

void ComplexplotWrapper::setXAxisScale(int id, double xMin, double xMax)
{
  if(destroyed_)
    return;
  emit setWidgetXAxisScale(id, xMin, xMax);
}

void ComplexplotWrapper::setYAxisScale(int id, double yMin, double yMax)
{
  if(destroyed_)
    return;
  emit setWidgetYAxisScale(id, yMin, yMax);
}

void ComplexplotWrapper::setXAxisRange(double xMin, double xMax)
{
  if(destroyed_)
    return;
  emit setWidgetXAxisRange(xMin, xMax);
}

