#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <iostream>
#include <thread>  // Required for std::this_thread::sleep_for
#include <chrono>  // Required for duration types


#include "ui/widgets/button.h"
#include "UI/widgets/basewidget.h"
#include "scrollarea.h"
#include "container.h"

class overlay;

class sidebar : public ui::uiWidget
{
    Q_OBJECT
public:
   explicit sidebar(QWidget *parent = nullptr);

   void toggle();
   void setVisibleState(bool stateVisible = false);
   bool visibleState();
   void updateState();

   QScrollArea *barArea;
   Container *container;
   QPropertyAnimation *animation;
protected:

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:

    struct m_layout
    {
        int left = 0;
        int top = 0;
        int rigth = 0;
        int bottom = 0;
    }margin;

    bool isVisible = false;

    Button *btn1;
    Button *btn2;
    Button *btn3;
    Button *btn4;

    scrollArea *scrollbar;
};


class overlay : public ui::uiWidget
{
    Q_OBJECT
public:
    void extracted(QWidget *&child);
    explicit overlay(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

    QWidget *findBarWidget;

};




#endif // SIDEBAR_H
