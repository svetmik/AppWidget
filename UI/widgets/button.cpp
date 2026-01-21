#include "button.h"

Button::Button(QWidget *parent)
    : AbstractButton(parent)
{
}

Button::Button(const QString &title, QWidget *parent)
    : AbstractButton(parent)
{
    this->setText(title);
}
