#include "widget.h"



Widget::Widget(QWidget *parent)
    : ui::uiWidget{parent}

{

    h_controlLayout = new QHBoxLayout(this); // main layout;
    h_controlLayout->setContentsMargins(0,0,0,0);

    leftBar = new left_bar(this);

    btnOpenSideBar = new Button("☰ Меню", leftBar);
    btnOpenSideBar->resize(leftBar->width(), btnOpenSideBar->height() + 15);
    btnOpenSideBar->setBackgroundColor(QColor(59,67,83));
    btnOpenSideBar->setHoverBackgroundColor(QColor(83,94,116));

    v_controlLayoutSidebar = new QVBoxLayout(); // layout для TextEdit, btnsend, btnAttchment, btnClose
    v_controlLayoutSidebar->addWidget(leftBar);

    v_controlLayoutMain= new QVBoxLayout(this);
    v_controlLayoutMain->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    v_controlLayoutMain->setContentsMargins(0,5,5,5);

    edit = new TextEdit(this);
    edit->setPlaceholderText("Описание вашей проблемы");

    btnSend = new Button("Отправить заявку");
    btnSend->setBorderRadius(3,3);

    btnAttachment = new Button("Прикрепить файл к заявке");
    btnAttachment->setBorderRadius(3,3);

    btnClose = new Button("Выйти");
    btnClose->setBorderRadius(3,3);

    v_controlLayoutMain->addWidget(edit);
    v_controlLayoutMain->addWidget(btnSend);
    v_controlLayoutMain->addWidget(btnAttachment);
    v_controlLayoutMain->addWidget(btnClose);


    h_controlLayout->addLayout(v_controlLayoutSidebar);
    h_controlLayout->addLayout(v_controlLayoutMain);


    _sidebar = new sidebar(this);
    _sidebar->setGeometry(_sidebar->x(), _sidebar->y(), _sidebar->width(), this->height());

    _overlay = new overlay(this);
    _overlay->hide();

    QObject::connect(btnOpenSideBar, &Button::clicked, this, &Widget::toggle);

}

Widget::~Widget()
{

}


void Widget::toggle()
{
    _sidebar->raise(); // перемещаем виджет на передний план;

    _sidebar->updateState();

}

void Widget::closeWindowApp(QMainWindow &handleEvent) {

    handleEvent.close();
}


void Widget::mousePressEvent(QMouseEvent *event) {

}

void Widget::hideEvent(QHideEvent *event) {


}

void Widget::paintEvent(QPaintEvent *event) {

    QPainter p(this);
}

void Widget::resizeEvent(QResizeEvent *event) {


    if (_sidebar) {
        _sidebar->setGeometry(_sidebar->x(), _sidebar->y(), _sidebar->width(), height()); // Занимаем весь родительский
        _sidebar->update(); // Принудительно перерисовать
    }


    if(_overlay) {
        _overlay->resize(event->size().width(), event->size().height());
    }
}
