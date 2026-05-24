#include "widget.h"
#include <QtWidgets>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *btn = new QPushButton("click", this);


    over = new overlay(this);

    over->box->raise();

    connect(btn, &QPushButton::clicked, this, &Widget::T);



}

Widget::~Widget() {

}


void Widget::T() {
    over->show();
}

void Widget::resizeEvent(QResizeEvent *event) {

    over->resize(event->size().width(), event->size().height());
}
