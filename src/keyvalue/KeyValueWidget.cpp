#include "KeyValueWidget.h"
#include "srsgui/common/Events.h"

#include <qlayout.h>
#include <algorithm>
#include <boost/lambda/lambda.hpp>

using namespace std;
namespace bl = boost::lambda;

KeyValueWidget::KeyValueWidget(QWidget *parent)
:QFrame(parent)
{
  setFrameStyle(QFrame::Box | QFrame::Sunken);

  // create actual widget and title label
  key_label = new QLabel();
  value_label = new QLabel();

  // place both widgets in layout
  QHBoxLayout* hLayout1 = new QHBoxLayout(this);
  hLayout1->setAlignment(Qt::AlignHCenter);
  hLayout1->addWidget(key_label);
  hLayout1->addWidget(value_label);

  key_label->setText("Hyper Frame Number:");
  value_label->setText("654");

  // configure labels
  QFont font("Sant Serif", 14, QFont::Bold);
  key_label->setFont(font);
  font.setBold(false);
  font.setPointSize(14);
  value_label->setFont(font);
}

KeyValueWidget::~KeyValueWidget()
{
  delete key_label;
  delete value_label;
}

void KeyValueWidget::setKeyText(const QString& text)
{
  key_label->setText(text);
}

void KeyValueWidget::setValueText(const QString& text)
{
  value_label->setText(text);
}
