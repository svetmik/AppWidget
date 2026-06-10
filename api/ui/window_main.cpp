#include "window_main.h"


uiWindow::uiWindow(QWidget *parent)
    : QWidget(parent),
    m_resize_border_width{6}
{
    apiWindow = std::make_unique<ApiWindow>();
    m_window_paltte = new uiWindowPalette(this);

    setVisibleTitleBtns(false);

    this->m_maximize_btn = windowTitleBtn(parent, qss_m_maximize_btn(), stateFlagTitlesBtn);
    this->m_minimize_btn = windowTitleBtn(parent, qss_title_btn_minimize(), stateFlagTitlesBtn);
    this->m_close_btn = windowTitleBtn(parent, qss_title_btn_close(), stateFlagTitlesBtn);

    this->m_maximize_btn->setCheckable(true);

    QObject::connect(m_minimize_btn, &QPushButton::clicked,  this, [this]() {
        onMinimizeButtonClicked();
    });
    QObject::connect(m_maximize_btn, &QPushButton::clicked, this, [this]() {
        onMaximizeButtonClicked();
    });
    QObject::connect(m_close_btn, &QPushButton::clicked,  this, [this]() {
        onCloseButtonClicked();
    });

    QObject::connect(windowHandle(), &QWindow::screenChanged, this, [this](QScreen *screen) {
        onScreenChanged(screen);
    });
}


void uiWindow::setinit(const WId &id) {

    m_hwnd = reinterpret_cast<HWND>(id);

    apiWindow->setWinId(m_hwnd);
}


HWND uiWindow::getID() {
    return m_hwnd;
}

void uiWindow::setVisibleTitleBtns(bool flag) {

    if(stateFlagTitlesBtn != flag) {
        this->stateFlagTitlesBtn = flag;
    }
}


QPushButton *uiWindow::windowTitleBtn(QWidget *parent, const QString &style, const bool &stateFlag, const int &fixWidth) {

    auto *btn = new QPushButton(parent);

    btn->setFixedWidth(fixWidth);

    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    btn->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    btn->setStyleSheet(style);

    btn->setVisible(stateFlag);

    return btn;
}

QWidget *uiWindow::box() {

    auto *box = new QWidget();

    box->setContentsMargins(0, 0, 0, 0);

    return box;
}



QVBoxLayout *uiWindow::vLayout(QWidget *parent) {

    auto layout = new QVBoxLayout(parent);

    layout->setContentsMargins(0,0,0,0);

    return layout;
}


QHBoxLayout *uiWindow::hLayout(QWidget *parent) {

    auto layout = new QHBoxLayout(parent);

    layout->setContentsMargins(0,0,0,0);

    return layout;
}

void uiWindow::initCentralWidget(QMainWindow *parent) {

    setinit(parent->winId());

    const auto centralWindowWidget = box();
    parent->setCentralWidget(centralWindowWidget);

    const auto v_centralLayout = vLayout(parent);
    v_centralLayout->setSpacing(0);
    centralWindowWidget->setLayout(v_centralLayout);

    m_title_bar_widget = box();
    v_centralLayout->addWidget(m_title_bar_widget);
    this->setTitlebarHeight(24);

    m_title_bar_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);


    const auto titlebar_layout = hLayout(parent);
    titlebar_layout->setSpacing(0);
    m_title_bar_widget->setLayout(titlebar_layout);


    const auto custom_titlebar_widget = box();

    titlebar_layout->addWidget(custom_titlebar_widget);
    custom_titlebar_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    titlebar_layout->addWidget(m_minimize_btn);
    titlebar_layout->addWidget(m_maximize_btn);
    titlebar_layout->addWidget(m_close_btn);

    m_custom_titlebar_layout = hLayout(custom_titlebar_widget);
    custom_titlebar_widget->setLayout(m_custom_titlebar_layout);
    m_custom_titlebar_layout->setSpacing(0);
    m_custom_titlebar_layout->setAlignment(Qt::AlignLeft);

    this->m_content_widget = box();
    v_centralLayout->addWidget(m_content_widget);
    m_content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->m_window_paltte->setTitleBarBackground(m_title_bar_widget);
    this->m_window_paltte->setCentralWidgetBackground(m_content_widget);


}

QWidget &uiWindow::getContentWidget() { return *m_content_widget; }

QWidget &uiWindow::getTitlebarWidget() { return *m_title_bar_widget; }

QHBoxLayout &uiWindow::getCustomTitlebarLayout() { return *m_custom_titlebar_layout; }

void uiWindow::setResizeBorderWidth(const int &w) { m_resize_border_width = w; }

void uiWindow::setTitlebarHeight(const int &h) { m_title_bar_widget->setFixedHeight(h); }


void uiWindow::onScreenChanged(QScreen *screen)
{
#ifdef Q_OS_WIN
    SetWindowPos(this->getID(), NULL, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                     SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE);
#endif // Q_OS_WIN
}

void uiWindow::onMinimizeButtonClicked()
{
#ifdef Q_OS_WIN
    SendMessage(this->getID(), WM_SYSCOMMAND, SC_MINIMIZE, 0);
#endif // Q_OS_WIN
}

void uiWindow::onMaximizeButtonClicked()
{
#ifdef Q_OS_WIN
    SendMessage(this->getID(), WM_SYSCOMMAND, m_maximize_btn->isChecked() ? SC_MAXIMIZE : SC_RESTORE, 0);
    // Remove the hover state from the maximize button.
    m_maximize_btn->setAttribute(Qt::WA_UnderMouse, false);
#endif

}

void uiWindow::onCloseButtonClicked()
{
#ifdef Q_OS_WIN
    SendMessage(this->getID(), WM_CLOSE, 0, 0);
#endif
}


#ifdef Q_OS_WIN
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
bool uiWindow::nativeEvent(const QByteArray &event_type, void *message, long *result)
#else
bool uiWindow::nativeEvent(const QByteArray &event_type, void *message, qintptr *result)
#endif
{

    MSG *msg = (MSG*)message;

    qDebug() << "msg =" << Qt::hex << msg->message;

    switch (msg->message)
    {
    // Remove the default window frame by hooking the WM_NCCALCSIZE message.
    case WM_NCCALCSIZE: {

        qDebug() << "WM_NCCALCSIZE";

        if (msg->lParam)
        {
            WINDOWPLACEMENT wp;
            GetWindowPlacement(this->getID(), &wp);

            if (wp.showCmd == SW_MAXIMIZE)
            {
                NCCALCSIZE_PARAMS *sz = (NCCALCSIZE_PARAMS *)msg->lParam;
                sz->rgrc[0].left += 8;
                sz->rgrc[0].top += 8;
                sz->rgrc[0].right -= 8;
                sz->rgrc[0].bottom -= 8;
            }
        }
        return true;
    }

        // Process the mouse when it is on the window border.
    case WM_NCHITTEST: {

        qDebug() << "WM_NCHITTEST";

        RECT winrect;
        GetWindowRect(msg->hwnd, &winrect);
        long x = GET_X_LPARAM(msg->lParam);
        long y = GET_Y_LPARAM(msg->lParam);
        long local_x = x - winrect.left;
        long local_y = y - winrect.top;

        if (x >= winrect.left && x < winrect.left + m_resize_border_width &&
            y < winrect.bottom && y >= winrect.bottom - m_resize_border_width)
        {
            *result = HTBOTTOMLEFT;
            return true;
        }

        if (x < winrect.right && x >= winrect.right - m_resize_border_width &&
            y < winrect.bottom && y >= winrect.bottom - m_resize_border_width)
        {
            *result = HTBOTTOMRIGHT;
            return true;
        }

        if (x >= winrect.left && x < winrect.left + m_resize_border_width &&
            y >= winrect.top && y < winrect.top + m_resize_border_width)
        {
            *result = HTTOPLEFT;
            return true;
        }

        if (x < winrect.right && x >= winrect.right - m_resize_border_width &&
            y >= winrect.top && y < winrect.top + m_resize_border_width)
        {
            *result = HTTOPRIGHT;
            return true;
        }

        if (x >= winrect.left && x < winrect.left + m_resize_border_width)
        {
            *result = HTLEFT;
            return true;
        }

        if (x < winrect.right && x >= winrect.right - m_resize_border_width)
        {
            *result = HTRIGHT;
            return true;
        }

        if (y < winrect.bottom && y >= winrect.bottom - m_resize_border_width)
        {
            *result = HTBOTTOM;
            return true;
        }

        if (y >= winrect.top && y < winrect.top + m_resize_border_width)
        {
            *result = HTTOP;
            return true;
        }

        // Check the area where the user can click to move the window.
        if (determineNonClickableWidgetUnderMouse(m_custom_titlebar_layout, local_x, local_y))
        {
            *result = HTCAPTION;
            return true;
        }

        *result = HTTRANSPARENT;
        break;
    }
    case WM_SIZE: {
        if (m_maximize_btn)
        {
            WINDOWPLACEMENT wp;
            GetWindowPlacement(this->getID(), &wp);

            m_maximize_btn->setChecked(wp.showCmd == SW_MAXIMIZE ? true : false);
        }
        break;
    }
    default:
        break;
    }

    return false;
}
#endif // Q_OS_WIN


bool uiWindow::determineNonClickableWidgetUnderMouse(QLayout *layout, int x, int y)
{
    if (!layout->count() && layout->geometry().contains(x, y))
        return true;

    for (size_t i = 0; i < layout->count(); i++)
    {
        auto item = layout->itemAt(i)->widget();
        if (item)
        {
            if (item->geometry().contains(x, y))
                return !item->property("clickable widget").toBool();
        }
        else
        {
            auto child_layout = layout->itemAt(i)->layout();
            if (child_layout && child_layout->geometry().contains(x, y))
                return determineNonClickableWidgetUnderMouse(child_layout, x, y);
        }
    }
    return false;
}

// Set `active' state using recursive method.
void uiWindow::propagateActiveStateInCustomTitlebar(QLayout *layout, bool active_state)
{
    for (size_t i = 0; i < layout->count(); i++)
    {
        auto item = layout->itemAt(i)->widget();
        if (item)
        {
            item->setProperty("active", active_state);
            item->setStyleSheet(item->styleSheet());
        }
        else
        {
            auto child_layout = layout->itemAt(i)->layout();
            if (child_layout)
                propagateActiveStateInCustomTitlebar(child_layout, active_state);
        }
    }
}


