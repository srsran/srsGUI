#include "TextEditWidget.h"
#include "srsgui/common/Lineplot.h"
#include "srsgui/common/Events.h"

#include <qlayout.h>
#include <algorithm>
#include <boost/lambda/lambda.hpp>

using namespace std;
namespace bl = boost::lambda;

TextEditWidget::TextEditWidget(QWidget *parent)
:QFrame(parent)
{
  setFrameStyle(QFrame::Box | QFrame::Sunken);

  // create actual widget and title label
  widget = new QPlainTextEdit();
  label = new QLabel();

  // place both widgets in layout
  QVBoxLayout* vLayout1 = new QVBoxLayout(this);
  vLayout1->addWidget(label);
  vLayout1->addWidget(widget);

  // configure label
  QFont font("Sant Serif", 14, QFont::Bold);
  label->setFont(font);
  label->setAlignment(Qt::AlignHCenter);

  font.setPointSize(12);
  font.setBold(false);
  widget->setFont(font);
}

TextEditWidget::~TextEditWidget()
{
  delete widget;
  delete label;
}

void TextEditWidget::setWidgetTitle(const QString& text)
{
  label->setText(text);
}

void TextEditWidget::appendPlainText(const QString& text)
{
  widget->appendPlainText(text);
}

void TextEditWidget::setPlainText(const QString& text)
{
  widget->setPlainText(text);
}
