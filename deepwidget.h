#ifndef DEEPWIDGET_H
#define DEEPWIDGET_H

#include <QWidget>
#include "widget.h"

class DeepWidget : public QWidget

{
    Q_OBJECT
public:
    explicit DeepWidget(Widget *mainWidget = nullptr, QWidget *parent = nullptr);


    Widget *mainWidget;
private:

signals:
};

#endif // DEEPWIDGET_H
