#ifndef WIDGET_H
#define WIDGET_H

#include "UI/widgets/basewidget.h"

#include "global_objects.h"
#include "left_bar.h"
#include "textedit.h"
#include "systeminfo.h"

class Widget : public ui::uiWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    Button *btnSend;
    Button *btnAttachment;
    Button *btnClose;
    Button *btnOpenSideBar;

    QHBoxLayout *h_controlLayout;
    QVBoxLayout *v_controlLayoutSidebar;
    QVBoxLayout *v_controlLayoutMain;


    TextEdit *edit;
    left_bar *leftBar;

    void closeWindowApp(QMainWindow &handleEvent);
protected:

    SystemInfo pc;
    void mousePressEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;
    void hideEvent(QHideEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void toggle();


};
#endif // WIDGET_H
