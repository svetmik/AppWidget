#include "overlay_box.h"


OverlayBox::OverlayBox(QWidget *parent)
    : ui::uiWidget{parent} 
    
{
    this->hide();

    setWindowFlags(Qt::FramelessWindowHint); // удаляет стандартную рамку и заголовок окна приложения

    setAttribute(Qt::WA_TranslucentBackground); // делает окно возможным полупрозрачным

    this->setStyleSheet("background-color: rgba(0, 0, 0, 40%);"); // 40% прозрачность окна

    init();
}

void OverlayBox::bodyText(const QString &text) {
    this->moduleBox->setCaption(text);
}

void OverlayBox::mousePressEvent(QMouseEvent *event) {

    if(event->button() == Qt::LeftButton) {
        this->hide();
    } else {
        QWidget::mousePressEvent(event);
    }

}



void OverlayBox::resizeEvent(QResizeEvent *event) {

    QWidget::resizeEvent(event);

    boxSize();

}

void OverlayBox::init() {

    moduleBox = new Box(this);

}


void OverlayBox::boxSize() {

    const auto sizeWidthBox = 180;

    const auto sizeHeightBox = 80;

    moduleBox->resize(sizeWidthBox, sizeHeightBox);

    if (!moduleBox)
        return;

    int kwidth = (width() - moduleBox->width()) / 2;
    int kheight = (height() - moduleBox->height()) / 2;

    moduleBox->move(kwidth, kheight);


    dumpObjectTree();
}



