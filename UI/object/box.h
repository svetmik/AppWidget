#ifndef BOX_H
#define BOX_H


#include <QWidget>
#include <QtWidgets>
#include <QPointer>

class Box : public QWidget
{
    Q_OBJECT

public:
    explicit Box(QWidget *parent = nullptr);


protected:

    void paintEvent(QPaintEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
};


class overlay : public QWidget
{
    Q_OBJECT
public:

    explicit overlay(QWidget *parent = nullptr);

    QPointer<Box> box;

protected:

    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:

    void centerChild();

    QPointer<overlay> bodysize;

    void init();

    void boxWindow();

    void boxSize();

};

#endif // BOX_H
