#ifndef CONTAINER_H
#define CONTAINER_H


#include "UI/widgets/basewidget.h"

class Container : public ui::uiWidget
{
    Q_OBJECT
public:
    explicit Container(QWidget *parent = nullptr);

    void setMargins();
signals:

private:
    QMargins m_margin;

};

#endif // CONTAINER_H
