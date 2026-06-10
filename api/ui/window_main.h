#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include "../api_window.h"
#include "res.h"

#include <QWidget>
#include <QMainWindow>
#include <QWindow>
#include <QEvent>
#include <QPushButton>
#include <QLayout>
#include <QPointer>

class uiWindowPalette : public QWidget {

    Q_OBJECT
    enum class schemeWidgetColor {
        darkWindow,
        darkHeader,
        lightWindow,
        lightHeader,
    };

public:

    uiWindowPalette(QWidget *parent = nullptr)
        : QWidget{parent}{}

    void setTitleBarBackground(QWidget *widget, schemeWidgetColor schemeColor = schemeWidgetColor::lightHeader) {

        m_palette_titleBar_widget = widget->palette();
        m_palette_titleBar_widget.setColor(QPalette::Window, getColor(schemeColor));
        widget->setAutoFillBackground(true);
        widget->setPalette(m_palette_titleBar_widget);
    }

    void setCentralWidgetBackground(QWidget *widget, schemeWidgetColor schemeColor = schemeWidgetColor::lightWindow) {

        m_palette_central_widget = widget->palette();
        m_palette_central_widget.setColor(QPalette::Window, getColor(schemeColor));
        widget->setAutoFillBackground(true);
        widget->setPalette(m_palette_central_widget);
    }

    QPalette getBackgroundTitleBar() const {
        return this->m_palette_titleBar_widget;
    }

    QPalette getBackgroundCentralWidget() const {
        return this->m_palette_central_widget;
    }

private:

    QColor getColor(schemeWidgetColor colortype) {

        switch (colortype) {

        case schemeWidgetColor::darkWindow:
            return QColor(30, 34, 39);

            break;
        case schemeWidgetColor::darkHeader:
            return QColor(35, 39, 46);

            break;
        case schemeWidgetColor::lightWindow:
            return QColor(250,250,250);
            break;
        case schemeWidgetColor::lightHeader:

            return QColor(241,241,241);

            break;
        }

        return QColor(255,255,255);
    }


    QPalette m_palette_titleBar_widget;
    QPalette m_palette_central_widget;

};

class uiWindow :  public QWidget
{
    Q_OBJECT

private:
    HWND m_hwnd;
    int m_resize_border_width{};

    void setinit(const WId &id);
    HWND getID();

    QHBoxLayout *m_custom_titlebar_layout{};
    QWidget *m_title_bar_widget{};
    QWidget *m_content_widget{};

    std::unique_ptr<ApiWindow> apiWindow;

    QPointer<uiWindowPalette> m_window_paltte;

    bool stateFlagTitlesBtn = false;
    void setVisibleTitleBtns(bool flag);
public:

    uiWindow(QWidget *parent = nullptr);


    void initCentralWidget(QMainWindow *parent);

    QPushButton *windowTitleBtn(QWidget *parent, const QString &style, const bool &stateFlag, const int &fixWidth = 36);
    QVBoxLayout *vLayout(QWidget *parent = nullptr);
    QHBoxLayout *hLayout(QWidget *parent = nullptr);

    QWidget *box();

    QPushButton *m_minimize_btn;
    QPushButton *m_maximize_btn;
    QPushButton *m_close_btn;



    QWidget &getContentWidget();
    QWidget &getTitlebarWidget();
    QHBoxLayout &getCustomTitlebarLayout();

    //API_WINDOW
    void onScreenChanged(QScreen *screen);
    void propagateActiveStateInCustomTitlebar(QLayout *layout, bool active_state);
    void onMinimizeButtonClicked();
    void onMaximizeButtonClicked();
    void onCloseButtonClicked();
    void setResizeBorderWidth(const int &resize_border_width);
    void setTitlebarHeight(const int &titlebar_height);

#ifdef Q_OS_WIN
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    bool nativeEvent(const QByteArray &event_type, void *message, long *result);
#else
    bool nativeEvent(const QByteArray &event_type, void *message, qintptr *result);
#endif
#else
    //LINUX
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
#endif // Q_IS_WIN

protected:
    bool determineNonClickableWidgetUnderMouse(QLayout *layout, int x, int y);
};

#endif // WINDOW_MAIN_H
