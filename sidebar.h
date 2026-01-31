#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <thread>  // Required for std::this_thread::sleep_for
#include <chrono>  // Required for duration types

#include "ui/widgets/button.h"
#include "scrollarea.h"
#include "container.h"

#include <QApplication>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QHideEvent>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

#include <QScrollBar>
#include <QScrollArea>

class overlay;


class sidebar : public QWidget
{
    Q_OBJECT
public:
    explicit sidebar(QWidget *parent = nullptr);

   void toggle();

   QPropertyAnimation *animation;

   void setVisibleState(bool stateVisible = false);
   bool visibleState();

   void updateState();

   QScrollBar *bar;
   QScrollArea *barArea;

   Container *container;

protected:
   void resizeEvent(QResizeEvent *event) override;

    void showEvent(QShowEvent *event) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void hideEvent(QHideEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
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


class overlay : public QWidget
{
    Q_OBJECT
public:
    void extracted(QWidget *&child);
    explicit overlay(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;


    QWidget *findBarWidget;


};




#endif // SIDEBAR_H
