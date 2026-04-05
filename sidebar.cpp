#include "sidebar.h"
#include "global_objects.h"





sidebar::sidebar(QWidget *parent)
    : ui::uiWidget{parent}
{
    setAutoFillBackground(true);
    // Начальная позиция - скрыт за левым краем
    move(-230, 0);
    setFixedWidth(230);
    setMinimumHeight(300);
    setContentsMargins(0,0,0,0);
    setStyleSheet("background-color: white");

    panel_widget = new Sidebar_panel(this);

    anim = new pa::PropertyAnimation(this, "pos");
}


void sidebar::toggle()
{
    if(!visibleState()) {
        this->raise(); // на передний план
    }

     bool curState = _sidebar->visibleState(); // default state = false;

     if (!curState) {
         // Показываем Боковую панель
         _sidebar->anim->setStartAnimation(_sidebar->pos(), QPoint(0,0));
         _overlay->show();
     } else {
         // // скрываем Боковую панель
         _sidebar->anim->setEndAnimation(_sidebar->pos(), QPoint(-270, 0));
         _overlay->hide();
     }

    _sidebar->anim->start();
    _sidebar->setVisibleState(!curState);

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

void sidebar::resizeEvent(QResizeEvent *event) {
    if(panel_widget) {
        panel_widget->setGeometry(QRect(panel_widget->pos(), QSize(size())));
    }
}


QSize sidebar::sizeHint() const {
  // .....
}


QSize sidebar::minimumSizeHint() const {
    return sizeHint();
}


overlay::overlay(QWidget *parent)
    : ui::uiWidget(parent)
{

    setWindowFlags(Qt::FramelessWindowHint); // удаляет стандартную рамку и заголовок окна приложения

    setAttribute(Qt::WA_TranslucentBackground); // делает окно возможным полупрозрачным

    this->setStyleSheet("background-color: rgba(0, 0, 0, 40%);"); // 40% прозрачность окна

    //
    this->hide();
}


//
void overlay::mousePressEvent(QMouseEvent *event) {

    _sidebar->updateState();

}

