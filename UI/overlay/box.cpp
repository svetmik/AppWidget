#include "box.h"

Box::Box(QWidget *parent)
    : ui::uiWidget(parent)
{
    infoLabelFont = this->font();
    infoLabelFont.setWeight(QFont::Weight::Normal);

    this->setStyleSheet("background-color: white");

    QHBoxLayout *lay = new QHBoxLayout(this);

    _ptrLabel = new QLabel(this);
    _ptrLabel->setAlignment(Qt::AlignCenter);
    _ptrLabel->setObjectName("widget_module_box_caption_lbl");
    _ptrLabel->setWordWrap(true);

    lay->addWidget(_ptrLabel);

}

void Box::setCaption(const QString &caption) {

    _ptrLabel->setText(caption);
}



void Box::paintEvent(QPaintEvent *event) {

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    p.fillRect(rect(), Qt::transparent);

    QRect _rect = this->rect().adjusted(1,1,-1,-1);
    p.setPen(QColor(0, 150, 237, 255));
    p.setBrush(QBrush(QColor(255,255,255)));
    p.drawRoundedRect(_rect, 6,6);

}

void Box::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {

        event->accept();
    } else {
        QWidget::mousePressEvent(event);
    }
}


