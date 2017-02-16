#include "srsgui/plot/TextEdit.h"
#include "TextEditWrapper.h"

TextEdit::TextEdit()
{
  plot_ = new TextEditWrapper();
}

TextEdit::~TextEdit()
{
  delete plot_;
}

void TextEdit::addToWindow(std::string window, int row, int column)
{
  plot_->addToWindow(window, row, column);
}

void TextEdit::appendMessage(std::string message)
{
  plot_->appendText(message);
}

void TextEdit::setMessage(std::string message)
{
  plot_->setText(message);
}

void TextEdit::setTitle(std::string title)
{
  plot_->setTitle(title);
}
