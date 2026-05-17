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
    constexpr int kMinHeight = 200;
};

class Sidebar_panel : public ui::uiWidget
{
    Q_OBJECT
public:
    explicit Sidebar_panel(QWidget *parent = nullptr);

signals:

private:


    void setupHeader(QLayout *parentLayout = nullptr);
    ui::uiWidget *createHeader();


    void setupMain(ScrollArea *parent = nullptr);
    ui::uiWidget *createMain();

    QVBoxLayout *vLayout(QWidget *parent = nullptr);
    QHBoxLayout *hLayout(QWidget *parent = nullptr);

    QLabel *infoRowText(const QString &text, bool wrap = true);
    QLabel *infoRowText(const QString &text, const QString &value, bool wrap = true);

    QLabel *infoRowTitle(const QString &text,bool wrap = true);

    SystemInfo *pcInfo;

    // Область прокрутки, вложенная в основной контейнер
    ScrollArea *_scrollArea;

    QVBoxLayout *_layout_main;

    LinkButton *_link_btn;

    QFont infoLabelFont;

};

#endif // SIDEBAR_PANEL_H
