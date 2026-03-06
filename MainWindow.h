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

    int m_shadow_margin = 5; // Отступ для тени
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setResizeBorderWidth(const int &resize_border_width);
    void setTitlebarHeight(const int &titlebar_height);
    QWidget &getContentWidget();
    QWidget &getTitlebarWidget();
    QHBoxLayout &getCustomTitlebarLayout();

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


    // visible or hidden titlebarBtns
    bool stateFlagTitlesBtn = false;
};

#endif // HEADER__FILE__MAINWINDOW
