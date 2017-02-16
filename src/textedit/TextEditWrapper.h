#ifndef TEXTEDITWRAPPER_H
#define TEXTEDITWRAPPER_H

#include <qapplication.h>

class TextEditWidget;

class TextEditWrapper
    : QObject
{
  Q_OBJECT

public:
  TextEditWrapper();
  ~TextEditWrapper();

  void addToWindow(std::string window, int row=-1, int column=-1);

  void appendText(std::string message);
  void setText(std::string message);

  void setTitle(std::string title);

public slots:
  void createWidgetSlot();
  void destroyWidgetSlot();
  void widgetDestroyed();
  void addToWindowSlot(QString window, int row, int column);

signals:
  void appendPlainText(QString message);
  void setPlainText(QString message);
  void setWidgetTitle(QString title);
  void createWidgetSignal();
  void destroyWidgetSignal();
  void destroyWidgetSignalBlocking();
  void addToWindowSignal(QString window, int row, int column);

private:
  TextEditWidget* widget_;
  bool destroyed_;
};

#endif // TEXTEDITWRAPPER_H
