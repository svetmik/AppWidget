#ifndef SIDEBAR_PANEL_H
#define SIDEBAR_PANEL_H

#include "UI/widgets/basewidget.h"
#include "UI/widgets/button.h"

#include "container.h"
#include "scrollarea.h"
#include "systeminfo.h"
#include "style_widget.h"

namespace Ui {
    constexpr int headerHeight = 100;
    constexpr int margin = 15;
    constexpr int margin_5 = 5;
};

class Sidebar_panel : public ui::uiWidget
{
    Q_OBJECT
public:
    explicit Sidebar_panel(QWidget *parent = nullptr);

signals:

private:

    void setStyle(QWidget *widget);

    style_widget qss;

    void setupHeader(QLayout *parentLayout);

    ui::uiWidget *createHeader();

    QVBoxLayout *vLayout();
    QHBoxLayout *hLayout();

    QLabel *infoRowText(const QString &text, bool wrap = true);
    QLabel *infoRowText(const QString &text, const QString &value, bool wrap = true);

    QLabel *infoRowTitle(const QString &text,bool wrap = true);

    SystemInfo *pcInfo;


    Container *_contaier_header;
    // main container_box widget
    // Основной виджет в котором распологаются все элементы
    Container *_container;

    // Вертикальный слой для управления размещением элементов внутри _container
    QVBoxLayout *_layout_container;

    // Область прокрутки, вложенная в основной контейнер
    ScrollArea *_scrollArea;

    QVBoxLayout *_layout_main;


    LinkButton *_link_btn;

    QLabel infoVerionApp;
    QLabel infoNameDesktopApp;


    QVBoxLayout *v_box;
    QVBoxLayout *v_box_child;

    QVBoxLayout *v_box_1;
    QHBoxLayout *h_box_child;

    QFont infoLabelFont;

};

#endif // SIDEBAR_PANEL_H
