#include "api_window_helper.h"



ApiWindowHelper::ApiWindowHelper() {

}


void ApiWindowHelper::setHandle(const HWND &handle) {

    m_hwnd_win = handle;
}

HWND ApiWindowHelper::getHandle() const {

    return m_hwnd_win;
}

