#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <thread>  // Required for std::this_thread::sleep_for
#include <chrono>  // Required for duration types

#include "ui/widgets/button.h"

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

protected:
   void resizeEvent(QResizeEvent *event) override;
<<<<<<< HEAD
    void showEvent(QShowEvent *event) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void updateSidebarHeight();
=======
   void hideEvent(QHideEvent *event) override;
>>>>>>> d4105f1728a0f9218dea5245871eafb5437f1ba1
private:

    bool isVisible = false;

    QPushButton *btn1;
    QPushButton *btn2;


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
