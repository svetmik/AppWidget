#include "sidebar.h"
#include "global_objects.h"

constexpr auto sidebarname = "siBarWidgetPanel";

sidebar::sidebar(QWidget *parent)
    : QWidget{parent}
{
    // Начальная позиция - скрыт за левым краем
    move(-230, 0);

    // Фиксируем высоту данного виджета
    setFixedWidth(230);
    // Имя виджета
    this->setObjectName(sidebarname);

    setAttribute(Qt::WA_StyledBackground, true);

    // Стили виджета
    setStyleSheet("background-color: #2c3e50;");


    // Layout и содержимое
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,20,0,20);
    btn1 = new QPushButton("Кнопка 1", this);

    btn2 = new QPushButton("Кнопка 2", this);

    layout->setSpacing(10);

    btn1->setStyleSheet("background-color: white; color: black;");
    btn2->setStyleSheet("background-color: white; color: black;");
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(new Button("Кнопка x", this));
    layout->addWidget(new Button("Кнопка x", this));
    layout->addWidget(new Button("Кнопка x", this));
    layout->addWidget(new Button("Кнопка x", this));
    layout->addWidget(new Button("Кнопка x", this));
    layout->addStretch();

    // Настройка анимации ||
    animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(250);
    animation->setEasingCurve(QEasingCurve::OutCubic);
}

void sidebar::toggle()
{
    bool curState = _sidebar->visibleState(); // default state = false;

    if (curState) {
        // Скрываем Боковую панель
        _sidebar->animation->setStartValue(_sidebar->pos());
        _sidebar->animation->setEndValue(QPoint(-270, 0));
        std::this_thread::sleep_for(std::chrono::microseconds(800));
        _overlay->hide();
    } else {
        // Показываем Боковую панель
        _sidebar->animation->setStartValue(_sidebar->pos());
        _sidebar->animation->setEndValue(QPoint(0, 0));
        std::this_thread::sleep_for(std::chrono::microseconds(800));
        _overlay->show();
    }

    _sidebar->animation->start();
    _sidebar->setVisibleState(!curState);
}


void sidebar::setVisibleState(bool stateVisible) {
    this->isVisible = stateVisible;
}

bool sidebar::visibleState(){
    return  this->isVisible;
}

void sidebar::resizeEvent(QResizeEvent *event) {
    qDebug() << btn2->size().width();
    qDebug() << btn2->size().height();
}

overlay::overlay(QWidget *parent): QWidget(parent) {

    setWindowFlags(Qt::FramelessWindowHint); // удаляет стандартную рамку и заголовок окна приложения
    setAttribute(Qt::WA_TranslucentBackground); // делает окно возможным полупрозрачным
    this->setStyleSheet("background-color: rgba(0, 0, 0, 40%);"); // 40% прозрачность окна
}


//
void overlay::mousePressEvent(QMouseEvent *event) {

    bool curState = _sidebar->visibleState(); // cur state = false;

    if (curState) {
        // Скрываем Боковую панель
        _sidebar->animation->setStartValue(_sidebar->pos());
        _sidebar->animation->setEndValue(QPoint(-270, 0));
        std::this_thread::sleep_for(std::chrono::microseconds(800));
        _overlay->hide();
    }

    _sidebar->animation->start();
    _sidebar->setVisibleState(!curState);

}


void overlay::paintEvent(QPaintEvent *event) {

    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
