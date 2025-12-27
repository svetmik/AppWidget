#include "left_bar.h"

left_bar::left_bar(QWidget *parent)
    : QWidget{parent}
{
    this->setAutoFillBackground(true);
    this->setStyleSheet("background-color: #3b4353;");
    this->setFixedSize(70,this->maximumHeight());
}


// draw custom styleSheet this widget
void left_bar::paintEvent(QPaintEvent *event) {

    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
