#ifndef TEXTEDITWIDGET_H
#define TEXTEDITWIDGET_H

#include <qapplication.h>
#include <qwidget.h>
#include <qframe.h>
#include <complex>
#include <QtWidgets/qplaintextedit.h>
#include <QtWidgets/qlabel.h>

class TextEditWidget
  : public QFrame
{
  Q_OBJECT

public:
  TextEditWidget(QWidget* parent = 0);
  virtual ~TextEditWidget();

public slots:
  void appendPlainText(const QString& text);
  void setPlainText(const QString& text);
  void setWidgetTitle(const QString& text);

protected:

private:
  QPlainTextEdit* widget;
  QLabel *label;
};

#endif // TEXTEDITWIDGET_H
