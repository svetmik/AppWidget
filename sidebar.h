#ifndef SIDEBAR_H
#define SIDEBAR_H




#include "ui/widgets/button.h"
#include "UI/widgets/basewidget.h"
#include "scrollarea.h"
#include "container.h"
#include "propertyanimation.h"
#include "systeminfo.h"


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

protected:

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:

    Button *btn1;
    Button *btn2;
    Button *btn3;
    Button *btn4;

    Container *container;
    Container *infoContaier;

    QLabel infoMessageAboutPc;

    QLabel infoAboutPrinter;
    QLabel infoAboutIpPc;
    QLabel infoAboutDomainName;

    QLabel infoVerionApp;
    QLabel infoNameDesktopApp;

    QVBoxLayout *v_box;
    QVBoxLayout *v_box_child;

    QVBoxLayout *v_box_1;
    QHBoxLayout *h_box_child;


    SystemInfo *pcInfo;
    scrollArea *scrollbar;
    pa::PropertyAnimation *anim;

    QFont infoLabelFont;

    bool isVisible = false;
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
