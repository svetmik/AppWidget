#ifndef WIDGET_H
#define WIDGET_H


#include <thread>  // Required for std::this_thread::sleep_for
#include <chrono>  // Required for duration types
#include <iostream>

#include "global_objects.h"
#include "left_bar.h"
#include "button.h"
#include "qboxlayout.h"
#include "textedit.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QResizeEvent>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    Button *btnSend;
    Button *btnAttachment;
    Button *btnClose;
    Button *btnOpenSideBar;

    QHBoxLayout *h_controlLayout;
    QVBoxLayout *v_controlLayoutSidebar;
    QVBoxLayout *v_controlLayoutMain;


    TextEdit *edit;
    left_bar *leftBar;


protected:

    void mousePressEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void toggle();

};
#endif // WIDGET_H
