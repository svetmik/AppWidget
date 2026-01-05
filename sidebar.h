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

#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

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

protected:
   void resizeEvent(QResizeEvent *event) override;

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
