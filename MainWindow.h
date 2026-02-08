#ifndef HEADER__FILE__MAINWINDOW
#define HEADER__FILE__MAINWINDOW


#include <QApplication>
#include <QLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QScreen>
#include <QSpacerItem>
#include <QWindow>

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
#endif // Q_IS_WIN
    bool event(QEvent *evt);
    bool determineNonClickableWidgetUnderMouse(QLayout *layout, int x, int y);
    void propagateActiveStateInCustomTitlebar(QLayout *layout, bool active_state);
    void onScreenChanged(QScreen *screen);
    void onMinimizeButtonClicked();
    void onMaximizeButtonClicked();
    void onCloseButtonClicked();
};

#endif // HEADER__FILE__MAINWINDOW
