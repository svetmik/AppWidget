#include "api_window.h"

ApiWindow::ApiWindow()
    : m_WindowHepler(std::make_unique<ApiWindowHelper>())
    , m_WindowShadow(std::make_unique<ApiWindowShadow>())
{
    initWindowShadowMargin();
}

void ApiWindow::setWinId(HWND hwnd) {

    this->initWindow(hwnd);

    initIntoClientArea();
}


void ApiWindow::initWindow(HWND hwnd) {

    m_WindowHepler->setHandle(hwnd);

}

void ApiWindow::initIntoClientArea() {

    const auto w_shadow = getWindowShadowMargin();

    const auto w_handle = getWindowId();

    if(!w_handle) {
        return;
    }

    ::DwmExtendFrameIntoClientArea(static_cast<HWND>(w_handle), &w_shadow);

}



HWND ApiWindow::getWindowId() const {

    return m_WindowHepler->getHandle();
}


void ApiWindow::initWindowShadowMargin() {

    m_WindowShadow->setMargins(1,1,1,1);

}

MARGINS ApiWindow::getWindowShadowMargin() const  {

    return m_WindowShadow->margins();
}


