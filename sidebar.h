#ifndef SIDEBAR_H
#define SIDEBAR_H



#include "UI/widgets/basewidget.h"
#include "ui/widgets/button.h"
#include "scrollarea.h"
#include "container.h"
#include "propertyanimation.h"
#include "systeminfo.h"
#include "sidebar_panel.h"

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

   SystemInfo *pcInfo;
protected:

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void resizeEvent(QResizeEvent *event) override;

private:

    Sidebar_panel *panel_widget;

    pa::PropertyAnimation *anim;

    bool isVisible = false;
};


class overlay : public ui::uiWidget
{
    Q_OBJECT
public:

    explicit overlay(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;


};




#endif // SIDEBAR_H
