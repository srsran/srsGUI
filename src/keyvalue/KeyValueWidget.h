#ifndef KEYVALUEWIDGET_H
#define KEYVALUEWIDGET_H

#include <qapplication.h>
#include <qwidget.h>
#include <qframe.h>
#include <complex>
#include <QtWidgets/qplaintextedit.h>
#include <QtWidgets/qlabel.h>

class KeyValueWidget
  : public QFrame
{
  Q_OBJECT

public:
  KeyValueWidget(QWidget* parent = 0);
  virtual ~KeyValueWidget();

public slots:
  void setKeyText(const QString& text);
  void setValueText(const QString& text);

protected:

private:
  QLabel* key_label;
  QLabel *value_label;
};

#endif // KEYVALUEWIDGET_H
