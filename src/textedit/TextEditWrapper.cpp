#include "TextEditWrapper.h"

#include "TextEditWidget.h"
#include "srsgui/common/Events.h"
#include <qapplication.h>
#include <QThread>
#include <QGridLayout>
#include <iostream>

TextEditWrapper::TextEditWrapper()
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

TextEditWrapper::~TextEditWrapper()
{
  if(destroyed_)
    emit destroyWidgetSignal();
  else
    emit destroyWidgetSignalBlocking();
}


void TextEditWrapper::createWidgetSlot()
{
  widget_ = new TextEditWidget;

  destroyed_ = false;
  widget_->setAttribute(Qt::WA_DeleteOnClose, true);
  connect(widget_, SIGNAL( destroyed() ),
          this, SLOT( widgetDestroyed() ));
  connect(this, SIGNAL(addToWindowSignal(QString, int, int)),
          this, SLOT(addToWindowSlot(QString, int, int)));
  connect(this, SIGNAL(setWidgetTitle(QString)),
          widget_, SLOT(setWidgetTitle(QString)));
  connect(this, SIGNAL(appendPlainText(QString)),
          widget_, SLOT(appendPlainText(QString)));

  connect(this, SIGNAL(setPlainText(QString)),
          widget_, SLOT(setPlainText(QString)));

  widget_->resize( 100, 100 );
  widget_->show();
}

void TextEditWrapper::destroyWidgetSlot()
{
  delete widget_;
}

void TextEditWrapper::widgetDestroyed()
{
  destroyed_ = true;
}

void TextEditWrapper::addToWindow(std::string window, int row, int column)
{
  emit addToWindowSignal(QString::fromStdString(window), row, column);
}

void TextEditWrapper::addToWindowSlot(QString window, int row, int column)
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

void TextEditWrapper::appendText(std::string message)
{
  QString str = QString::fromUtf8(message.c_str());
  emit appendPlainText(str);
}

void TextEditWrapper::setText(std::string message)
{
  QString str = QString::fromUtf8(message.c_str());
  emit setPlainText(str);
}

void TextEditWrapper::setTitle(std::string title)
{
  if(destroyed_)
    return;
  QString str = QString::fromUtf8(title.c_str());
  emit setWidgetTitle(str);
}
