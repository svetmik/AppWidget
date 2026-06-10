#ifndef API_WINDOW_H
#define API_WINDOW_H

#include <Windowsx.h>

#include "api_window_helper.h"
#include "api_window_shadow.h"

#include <memory>


class ApiWindow {

public:

    ApiWindow();

    ApiWindow(const ApiWindow&) = delete;

    ApiWindow& operator=(const ApiWindow&) = delete;

    virtual ~ApiWindow() = default;

    void setWinId(HWND hwnd);

private:

    void initWindow(HWND hwnd);

    // HWND
    HWND getWindowId() const;

    void  initWindowShadowMargin();

    MARGINS getWindowShadowMargin() const ;

    void initIntoClientArea();

    std::unique_ptr<ApiWindowHelper> m_WindowHepler;

    std::unique_ptr<ApiWindowShadow> m_WindowShadow;

};

#endif // API_WINDOW_H
