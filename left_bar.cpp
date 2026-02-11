#include "left_bar.h"

left_bar::left_bar(QWidget *parent)
    : ui::uiWidget{parent}
{
    this->setAutoFillBackground(true);
    this->setStyleSheet("background-color: #3b4353;");
    this->setFixedSize(70,this->maximumHeight());
}

