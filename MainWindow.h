#ifndef HEADER__FILE__MAINWINDOW
#define HEADER__FILE__MAINWINDOW


#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScreen>
#include <QWindow>
#include <QMouseEvent>
#include <QStyle>
#include <QGraphicsDropShadowEffect>

#include <cstdlib>
#include <ctime>

#include "zipreader_p.h"
#include "zipwriter_p.h"


#ifdef Q_OS_WIN

#include <Windows.h>
#include <Windowsx.h>
#include <dwmapi.h>

#endif // Q_OS_WIN


class MainWindow : public QMainWindow
{
    Q_OBJECT

#ifdef Q_OS_WIN
    HWND m_hwnd;
#endif

    int m_resize_border_width;
    QPushButton *m_minimize_btn;
    QPushButton *m_maximize_btn;
    QPushButton *m_close_btn;
    QWidget *m_content_widget;
    QWidget *m_titlebar_widget;
    QHBoxLayout *m_custom_titlebar_layout;

    // for linux OS
    int m_shadow_margin = 5; // Отступ для тени
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setResizeBorderWidth(const int &resize_border_width);
    void setTitlebarHeight(const int &titlebar_height);
    QWidget &getContentWidget();
    QWidget &getTitlebarWidget();
    QHBoxLayout &getCustomTitlebarLayout();

    void setVisibleTitleBtns(bool flag);
private:
#ifdef Q_OS_WIN
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    bool nativeEvent(const QByteArray &event_type, void *message, long *result);
#else
    bool nativeEvent(const QByteArray &event_type, void *message, qintptr *result);
#endif
#else
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
#endif // Q_IS_WIN

    //void mousePressEvent(QMouseEvent *event) override;
    //void mouseMoveEvent(QMouseEvent *event) override;

    bool event(QEvent *evt);

    bool determineNonClickableWidgetUnderMouse(QLayout *layout, int x, int y);
    void propagateActiveStateInCustomTitlebar(QLayout *layout, bool active_state);
    void onScreenChanged(QScreen *screen);
    void onMinimizeButtonClicked();
    void onMaximizeButtonClicked();
    void onCloseButtonClicked();


    // visible or hidden titlebarButtons
    bool stateFlagTitlesBtn;


    QString qss_title_btn_close = R"(
            QPushButton {
                border-image: url(:/icon/btn_close.png);
                background-color: rgba(255, 255, 255, 0%);
                background-repeat: no-repeat;
            }
            QPushButton:hover {
                border-image: url(:/icon/btn_close_hover.png);
                background-color: #e81123;
            }
            QPushButton:pressed {
                border-image: url(:/icon/btn_close_hover.png);
                background-color: #e81123;
            }
            QPushButton:!active {
                border-image: url(:/icon/btn_close.png);

            }
            QPushButton:hover:!active {
                border-image: url(:/icon/btn_close_hover.png);
                background-color: #e81123;
            }
        )";

    QString qss_title_btn_minimize = R"(
            QPushButton {
                border-image: url(:/icon/button_minimize.png);
                background-color: rgba(255, 255, 255, 0%);
                background-repeat: no-repeat;
            }

            QPushButton:hover {
                background-color: rgba(228, 228, 228, 80%);
            }

            QPushButton:pressed {
                background-color: rgba(255, 255, 255, 40%);
            }

            QPushButton:!active {
                border-image: url(:/icon/button_minimize.png);
            }
        )";

    QString qss_m_maximize_btn = R"(
            QPushButton {
                border-image: url(:/icon/button_maximize.png);
                background-color: rgba(255, 255, 255, 0%);
                background-repeat: no-repeat;
            }
            QPushButton:hover {
                background-color: rgba(228, 228, 228, 80%);
            }
            QPushButton:pressed {
                background-color: rgba(255, 255, 255, 40%);
            }
            QPushButton:checked {
                border-image: url(:/icon/button_restore.png);
                background-color: rgba(255, 255, 255, 0%);
                background-repeat: no-repeat;
            }
            QPushButton:checked:hover {
                background-color: rgba(228, 228, 228, 80%);
            }
            QPushButton:checked:pressed {
                background-color: rgba(255, 255, 255, 40%);
            }
            QPushButton:!active {
                border-image: url(:/icon/button_maximize.png);
            }
            QPushButton:checked:!active {
                border-image: url(:/icon/button_restore.png);
            }
        )";
};

#endif // HEADER__FILE__MAINWINDOW
