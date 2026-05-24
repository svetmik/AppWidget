#ifndef WIDGET_H
#define WIDGET_H


#include "box.h"

#include <QWidget>


class Widget : public QWidget
{

    Q_OBJECT
public:
    explicit  Widget(QWidget *parent = nullptr);


    ~Widget();


    QPointer<overlay> over;

    void resizeEvent(QResizeEvent *event) override;
private:

    void T();

};

#endif // WIDGET_H
