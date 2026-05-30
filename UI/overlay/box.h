#pragma once


#include "../widgets/basewidget.h"

class Box : public ui::uiWidget
{
    Q_OBJECT

public:

    explicit Box(QWidget *parent = nullptr);

    void setCaption(const QString &caption);
protected:

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    QFont infoLabelFont;

    QPointer<QLabel> _ptrLabel;


};
