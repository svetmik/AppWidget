#include "basewidget.h"


ui::uiWidget::uiWidget(QWidget *parent)
    :BaseWidget<QWidget>(parent)
{

}


ui::uiWidget::~uiWidget() {

}


void ui::uiWidget::paintEvent(QPaintEvent *event) {

    QStyleOption opt;

    opt.initFrom(this);

    QPainter p(this);

    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}
