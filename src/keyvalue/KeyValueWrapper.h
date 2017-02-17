#ifndef KEYVALUEWRAPPER_H
#define KEYVALUEWRAPPER_H

#include <qapplication.h>

class KeyValueWidget;

class KeyValueWrapper
    : QObject
{
  Q_OBJECT

public:
  KeyValueWrapper();
  ~KeyValueWrapper();

  void addToWindow(std::string window, int row=-1, int column=-1);

  void setKeyText(std::string tetxt);
  void setValueText(std::string text);

public slots:
  void createWidgetSlot();
  void destroyWidgetSlot();
  void widgetDestroyed();
  void addToWindowSlot(QString window, int row, int column);

signals:
  void appendPlainText(QString message);
  void setKeyText(QString txt);
  void setValueText(QString txt);
  void createWidgetSignal();
  void destroyWidgetSignal();
  void destroyWidgetSignalBlocking();
  void addToWindowSignal(QString window, int row, int column);

private:
  KeyValueWidget* widget_;
  bool destroyed_;
};

#endif // KEYVALUEWRAPPER_H
