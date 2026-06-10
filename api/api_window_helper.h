#ifndef API_WINDOW_HELPER_H
#define API_WINDOW_HELPER_H

#include <QtGlobal>

#ifdef Q_OS_WIN
    #include <Windows.h>
#endif // Q_OS_WIN



class ApiWindowHelper {

public:

    ApiWindowHelper();

    ApiWindowHelper(const ApiWindowHelper&) = delete;
    ApiWindowHelper& operator=(const ApiWindowHelper&) = delete;

    virtual ~ApiWindowHelper() = default;


    void setHandle(const HWND &handle);

    HWND getHandle() const;

#ifdef Q_OS_WIN
    HWND m_hwnd_win = nullptr;
#endif
};

#endif // API_WINDOW_HELPER_H
