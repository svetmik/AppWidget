#ifndef API_WINDOW_SHADOW_H
#define API_WINDOW_SHADOW_H


#include <QtGlobal>

#ifdef Q_OS_WIN
    #include <windows.h>
    #include <dwmapi.h>
#endif // Q_OS_WIN



class ApiWindowShadow {

public:

    ApiWindowShadow();

    ApiWindowShadow(const ApiWindowShadow&) = delete;
    ApiWindowShadow& operator=(const ApiWindowShadow&) = delete;

    virtual ~ApiWindowShadow() = default;

    void setMargins(const int &cxLeftWidth,
                    const int &cxRightWidth,
                    const int &cyTopHeight,
                    const int &cyBottomHeight);

    MARGINS  margins() const;

private:

    MARGINS m_margin{};
};

#endif // API_WINDOW_SHADOW_H
