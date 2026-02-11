#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

#include <QStyleOption>
#include <QStyle>
#include <QMargins>

#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QFontDatabase>
#include <QFont>
#include <QFontInfo>
#include <QFontMetrics>

#include <QHideEvent>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>

template<typename Widget>
class BaseWidget;

class DefaultWidgetWrap {
public:

    virtual ~DefaultWidgetWrap() = default;

};


template<typename Widget>
class BaseWidget: public Widget, public DefaultWidgetWrap {


public:

    using Widget::Widget;

    virtual ~BaseWidget() = default;

};

namespace ui {

class uiWidget : public BaseWidget<QWidget> {

public:

    uiWidget(QWidget *parent = nullptr);

    virtual ~uiWidget();

protected:

    void paintEvent(QPaintEvent *event) override;
};

}

#endif // BASEWIDGET_H
