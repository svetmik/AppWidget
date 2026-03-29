#include "button.h"
#include "QFont"


Button::Button(QWidget *parent)
    : AbstractButton(parent)
{


}

Button::Button(const QString &title, QWidget *parent)
    : AbstractButton(parent)
{
    this->setText(title);

}


Button::Button(const QString &title, const FlagText &flag, QWidget *parent)
    : AbstractButton(parent)
{
    this->setText(title);
    this->setAlignText(flag);

}

LinkButton::LinkButton(QWidget *parent)
    : AbstractButton{parent}
{
    this->defaultStyles();
};


LinkButton::LinkButton(const QString &title, QWidget *parent, const FlagText flag)
    : AbstractButton{parent}
{
    this->defaultStyles();
    setText(title);
    setAlignText(flag);
    setPaddingsWidth(25,25);
};


void LinkButton::defaultStyles() {

    const QColor bgColor(255,255,255);
    const QColor hoverBgColor(235, 235, 235);
    const QColor textColor(0,0,0);

    setBackgroundColor(bgColor);
    setHoverBackgroundColor(hoverBgColor);
    setColorText(textColor);
}

