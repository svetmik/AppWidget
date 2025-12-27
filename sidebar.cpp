#include "sidebar.h"
#include "global_objects.h"

constexpr auto sidebarname = "siBarWidgetPanel";

sidebar::sidebar(QWidget *parent)
    : QWidget{parent}
{
    // Настройка sidebar
    setFixedWidth(230);

    this->setObjectName(sidebarname);

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background-color: #2c3e50;");

    // Начальная позиция - скрыт за левым краем
    move(-230, 0);



    // Layout и содержимое
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    btn1 = new QPushButton("Кнопка 1", this);
    btn2 = new QPushButton("Кнопка 2", this);

    layout->setSpacing(10);

    btn1->setStyleSheet("background-color: white; color: black;");
    btn2->setStyleSheet("background-color: white; color: black;");

    layout->addWidget(btn1);
    layout->addWidget(btn2);

    layout->addStretch();

    // Настройка анимации ||
    animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(280);
    animation->setEasingCurve(QEasingCurve::OutCubic);

}

// void sidebar::toggle()
// {
//     // raise(); // Поднимаем наверх
//     qDebug() << "click";
//     if (isVisible) {
//         // Скрываем
//         animation->setStartValue(pos());
//         animation->setEndValue(QPoint(-230, 0));
//     } else {
//         // Показываем
//         show();
//         animation->setStartValue(pos());
//         animation->setEndValue(QPoint(0, 0));
//     }

//     animation->start();
//     isVisible = !isVisible;

// }

void sidebar::resizeEvent(QResizeEvent *event) {
}

overlay::overlay(QWidget *parent): QWidget(parent) {

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background-color: rgba(0, 0, 0, 40%);");


    QWidget *child = parent->window();

    if(findBarWidget = child->findChild<QWidget*>("siBarWidgetPanel")) {

    }


}



void overlay::mousePressEvent(QMouseEvent *event) {

    if (_sidebar->isVisible) {
        // Скрываем
        _sidebar->animation->setStartValue(_sidebar->pos());
        _sidebar->animation->setEndValue(QPoint(-270, 0));
        std::this_thread::sleep_for(std::chrono::microseconds(800));
        _overlay->hide();

    } else {
        _sidebar->animation->setStartValue(_sidebar->pos());
        _sidebar->animation->setEndValue(QPoint(0, 0));
        std::this_thread::sleep_for(std::chrono::microseconds(800));
        _overlay->show();

    }
    _sidebar->animation->start();
    _sidebar->isVisible = !_sidebar->isVisible;
}


void overlay::paintEvent(QPaintEvent *event) {

    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
