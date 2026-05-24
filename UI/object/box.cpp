#include "box.h"

Box::Box(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color: white;");



    QLabel *lbl = new QLabel(this);

    lbl->setText("hello world");
    lbl->setAlignment(Qt::AlignCenter);

    QHBoxLayout *lay = new QHBoxLayout(this);

    lay->addWidget(lbl);

}


void Box::paintEvent(QPaintEvent *event) {

    QStyleOption opt;

    opt.initFrom(this);

    QPainter p(this);

    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    p.drawRoundedRect(rect(), 6,6);

    QWidget::paintEvent(event);

}

void Box::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {

        event->accept();
    } else {
        QWidget::mousePressEvent(event);
    }
}

overlay::overlay(QWidget *parent)
    : QWidget(parent)
{
    this->hide();

    setWindowFlags(Qt::FramelessWindowHint); // удаляет стандартную рамку и заголовок окна приложения

    setAttribute(Qt::WA_TranslucentBackground); // делает окно возможным полупрозрачным

    this->setStyleSheet("background-color: rgba(0, 0, 0, 10%);"); // 40% прозрачность окна


    init();
}


//
void overlay::mousePressEvent(QMouseEvent *event) {

    if(event->button() == Qt::LeftButton) {
        this->hide();
    } else {
        QWidget::mousePressEvent(event);
    }

}


void overlay::paintEvent(QPaintEvent *event) {

    QStyleOption opt;

    opt.initFrom(this);

    QPainter p(this);

    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);

}


void overlay::resizeEvent(QResizeEvent *event) {

    QWidget::resizeEvent(event);

    boxSize();

}

void overlay::init() {

    box = new Box(this);

}


void overlay::boxWindow() {

}

void overlay::boxSize() {

    const auto sizeWidthBox = 180;

    const auto sizeHeightBox = 80;

    box->resize(sizeWidthBox, sizeHeightBox);

    if (!box)
        return;

    int kwidth = (width() - box->width()) / 2;
    int kheight = (height() - box->height()) / 2;

    box->move(kwidth, kheight);


    dumpObjectTree();
}

void overlay::centerChild() {


    // int marginWidth = 100;
    // int marginHeight = 20;

    // int newWidth = width() - (marginWidth * 2);
    // int newHeight = height() - (marginHeight * 2);


    // if (newWidth < 0) newWidth = 0;
    // if (newHeight < 0) newHeight = 0;

    // box->setGeometry(kwidth, kheight, newWidth, newHeight);


    //if (!box) return; // Защита, если box еще не создан

    // 1. Задаем идеальные (желаемые) размеры окна в стиле Telegram
    // int maxBoxWidth = 250;
    // int maxBoxHeight = 500;
    // int margin = 24; // Фиксированный отступ от краев экрана

    // 2. Вычисляем доступное пространство внутри главного окна
    // int availableWidth = width() - (margin * 2);
    // int availableHeight = height() - (margin * 2);

    // 3. Если главное окно меньше идеального размера Box,
    //    то Box уменьшается (адаптируется под размер экрана), иначе остается максимальным
    // int finalWidth = qMin(maxBoxWidth, availableWidth);
    // int finalHeight = qMin(availableHeight, availableHeight);


    // finalWidth = qMax(0, finalWidth);
    // finalHeight = qMax(0, finalHeight);

    // 4. Центрируем Box с учетом вычисленных адаптивных размеров
    // int x = (width() - finalWidth) / 2;
    // int y = (height() - finalHeight) / 2;

    // // 5. Применяем геометрию
    // box->setGeometry(x, y, finalWidth, finalHeight);


    dumpObjectTree();
}
