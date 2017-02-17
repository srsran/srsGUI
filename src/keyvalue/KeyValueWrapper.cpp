#include "KeyValueWrapper.h"

#include "KeyValueWidget.h"
#include "srsgui/common/Events.h"
#include <qapplication.h>
#include <QThread>
#include <QGridLayout>
#include <iostream>

KeyValueWrapper::KeyValueWrapper()
    :widget_(NULL)
    ,destroyed_(true)
{
  if(QCoreApplication::instance() == NULL)
    return;
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

KeyValueWrapper::~KeyValueWrapper()
{
  if(destroyed_)
    emit destroyWidgetSignal();
  else
    emit destroyWidgetSignalBlocking();
}


void KeyValueWrapper::createWidgetSlot()
{
  widget_ = new KeyValueWidget;

  destroyed_ = false;
  widget_->setAttribute(Qt::WA_DeleteOnClose, true);
  connect(widget_, SIGNAL( destroyed() ),
          this, SLOT( widgetDestroyed() ));
  connect(this, SIGNAL(addToWindowSignal(QString, int, int)),
          this, SLOT(addToWindowSlot(QString, int, int)));
  connect(this, SIGNAL(setValueText(QString)),
          widget_, SLOT(setValueText(QString)));
  connect(this, SIGNAL(setKeyText(QString)),
          widget_, SLOT(setKeyText(QString)));

  widget_->resize( 100, 100 );
  widget_->show();
}

void KeyValueWrapper::destroyWidgetSlot()
{
  delete widget_;
}

void KeyValueWrapper::widgetDestroyed()
{
  destroyed_ = true;
}

void KeyValueWrapper::addToWindow(std::string window, int row, int column)
{
  emit addToWindowSignal(QString::fromStdString(window), row, column);
}

void KeyValueWrapper::addToWindowSlot(QString window, int row, int column)
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

void KeyValueWrapper::setKeyText(std::string text)
{
  QString str = QString::fromUtf8(text.c_str());
  emit setKeyText(str);
}

void KeyValueWrapper::setValueText(std::string text)
{
  QString str = QString::fromUtf8(text.c_str());
  emit setValueText(str);
}
