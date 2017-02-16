#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <string>

class TextEditWrapper;

class TextEdit
{
public:
  TextEdit();
  ~TextEdit();

  void addToWindow(std::string window, int row=-1, int column=-1);
  void appendMessage(std::string message);
  void setMessage(std::string message);
  void setTitle(std::string title);

private:
  TextEditWrapper* plot_;
};

#endif // TEXTEDIT_H
