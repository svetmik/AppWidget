#ifndef LEFT_BAR_H
#define LEFT_BAR_H

#include <QWidget>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

class left_bar : public QWidget
{
    Q_OBJECT
public:
    explicit left_bar(QWidget *parent = nullptr);

protected:

    void paintEvent(QPaintEvent *event) override ;

signals:

};

#endif // LEFT_BAR_H
