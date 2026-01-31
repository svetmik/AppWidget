#include "sidebar.h"
#include "global_objects.h"



constexpr auto sidebarname = "siBarWidgetPanel";

sidebar::sidebar(QWidget *parent)
    : QWidget{parent}
{
    setAutoFillBackground(true);
    // Начальная позиция - скрыт за левым краем
    move(-230, 0);
    setFixedWidth(230);
    setMinimumHeight(300);
    setContentsMargins(0,0,0,0);

    //
    container = new Container;
    container->setContentsMargins(0,0,0,0);
    container->setMinimumHeight(450);
    container->setMinimumWidth(this->width());

    QVBoxLayout *contentLayout = new QVBoxLayout(container);
    contentLayout->setContentsMargins(margin.left, margin.top, margin.rigth, margin.bottom);
    contentLayout->setSpacing(0);

    btn1 = new Button("z");
    btn2 = new Button("d");
    btn3 = new Button("b");

    contentLayout->addWidget(btn1);
    contentLayout->addWidget(btn2);
    contentLayout->addStretch();
    contentLayout->addWidget(btn3, 0, Qt::AlignBottom);

    // ***
    container->setLayout(contentLayout);

    scrollbar = new scrollArea;
    scrollbar->setAlwaysShowWhenNeeded(true);
    scrollbar->setStyleSheet("border: none;");
    scrollbar->setGeometry(0,0,width(), height());
    scrollbar->setUseSmoothScroll(true);
    // ***
    scrollbar->setWidget(container);


    QVBoxLayout *mainlayout = new QVBoxLayout(this);

    mainlayout->setContentsMargins(0,0,0,0);

    // ***
    mainlayout->addWidget(scrollbar);




    this->setLayout(mainlayout);

    // Настройка анимации
    animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(250);
    animation->setEasingCurve(QEasingCurve::OutCubic);

}

void sidebar::resizeEvent(QResizeEvent *event) {

    if(container) {
        qDebug() << "QWidget: content "<< container->minimumHeight();
    }

}


void sidebar::toggle()
{
    this->raise();

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



void sidebar::showEvent(QShowEvent *event) {

}

void sidebar::paintEvent(QPaintEvent *event) {

    // Q_UNUSED(event);

    // QStyleOption opt;

    // opt.initFrom(this);

    // QPainter p(this); // Создаем QPainter, привязанный к этому виджету
    // p.setRenderHint(QPainter::Antialiasing); // Для сглаживания

    // // Рисуем с учетом текущих размеров
    // p.drawRect(rect()); // Рисует прямоугольник на весь виджет
    // p.setPen(Qt::red);
    // p.drawText(rect(), Qt::AlignCenter, "Размер изменился!");

    // style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}
void sidebar::setVisibleState(bool stateVisible) {
    this->isVisible = stateVisible;
}

bool sidebar::visibleState(){
    return this->isVisible;
}

void sidebar::updateState() {

    if (_sidebar->visibleState()) {
        _sidebar->toggle();
    } else {
        _sidebar->toggle();

    }
}



QSize sidebar::sizeHint() const {

}


QSize sidebar::minimumSizeHint() const {
    return sizeHint();
}


void sidebar::hideEvent(QHideEvent *event) {

}









overlay::overlay(QWidget *parent)
    : QWidget(parent)
{

    setWindowFlags(Qt::FramelessWindowHint); // удаляет стандартную рамку и заголовок окна приложения
    setAttribute(Qt::WA_TranslucentBackground); // делает окно возможным полупрозрачным
    this->setStyleSheet("background-color: rgba(0, 0, 0, 40%);"); // 40% прозрачность окна
}


//
void overlay::mousePressEvent(QMouseEvent *event) {

    _sidebar->updateState();

}

void overlay::paintEvent(QPaintEvent *event) {


    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
