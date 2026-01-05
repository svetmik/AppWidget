#include "widget.h"

constexpr auto style_btn_side(" QPushButton#sidebtn { width: 70px; height: 40px;"
                              "background-color: transparent; "
                              "border: none; font-size: 12px; color: white; font-weight: 500; } "
                              "QPushButton#sidebtn:hover { background-color: rgb(123, 134, 140); }");

constexpr auto obt_name("sidebtn");

Widget::Widget(QWidget *parent)
    : QWidget{parent}

{

    h_controlLayout = new QHBoxLayout(this); // main layout;
    v_controlLayoutSidebar = new QVBoxLayout(); // layout для TextEdit, btnsend, btnAttchment, btnClose

    h_controlLayout->setContentsMargins(0,0,0,0);

    leftBar = new left_bar(this);
    btnOpenSideBar = new Button("☰ Меню", leftBar);
    // btnOpenSideBar->setStyleSheet(style_btn_side);
    // btnOpenSideBar->setObjectName(obt_name);

    v_controlLayoutSidebar->addWidget(leftBar);
    v_controlLayoutMain= new QVBoxLayout(this);
    v_controlLayoutMain->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    v_controlLayoutMain->setContentsMargins(0,5,5,5);

    edit = new TextEdit(this);
    edit->setPlaceholderText("Описание вашей проблемы");

    btnSend = new Button("Отправить заявку", this);
    btnAttachment = new Button("Прикрепить файл к заявке", this);
    btnClose = new Button("Выйти(отмена)", this);

    v_controlLayoutMain->addWidget(edit);
    v_controlLayoutMain->addWidget(btnSend);
    v_controlLayoutMain->addWidget(btnAttachment);
    v_controlLayoutMain->addWidget(btnClose);
    v_controlLayoutMain->addSpacing(3);

    h_controlLayout->addLayout(v_controlLayoutSidebar);
    h_controlLayout->addLayout(v_controlLayoutMain);


    _sidebar = new sidebar(this);

    _overlay = new overlay(this);
    _overlay->hide();

    QObject::connect(btnOpenSideBar, &Button::clicked, this, &Widget::toggle); //

    qDebug() << this->children();

}

Widget::~Widget()
{

}


void Widget::toggle()
{
    _sidebar->raise(); // перемещаем виджет на передний план;

    _sidebar->updateState();

}

void Widget::mousePressEvent(QMouseEvent *event) {

}


void Widget::resizeEvent(QResizeEvent *event) {

    _sidebar->setFixedHeight(event->size().height());
    _overlay->resize(event->size().width(), event->size().height());
}
