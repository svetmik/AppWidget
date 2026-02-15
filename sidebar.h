#ifndef SIDEBAR_H
#define SIDEBAR_H




#include "ui/widgets/button.h"
#include "UI/widgets/basewidget.h"
#include "scrollarea.h"
#include "container.h"
#include "propertyanimation.h"

class overlay;

class sidebar : public ui::uiWidget
{
    Q_OBJECT
public:
   explicit sidebar(QWidget *parent = nullptr);

   void toggle();
   void setVisibleState(bool stateVisible = false);
   bool visibleState();
   void updateState();

   Container *container;

protected:

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

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
    pa::PropertyAnimation *anim;
};


class overlay : public ui::uiWidget
{
    Q_OBJECT
public:
    void extracted(QWidget *&child);
    explicit overlay(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

    QWidget *findBarWidget;

};




#endif // SIDEBAR_H
