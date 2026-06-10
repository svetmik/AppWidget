cmake_minimum_required(VERSION 3.5)

project(app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network PrintSupport)

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(app
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        fonts/OpenSans-Italic.ttf
        fonts/OpenSans-Regular.ttf
        fonts/OpenSans-SemiBold.ttf
        fonts/OpenSans-SemiBoldItalic.ttf
        sidebar.cpp sidebar.h
        font.cpp
        font.h
        font_styles.h
        style_widget.cpp
        style_widget.h
        textedit.cpp
        textedit.h
        components.qrc
        global_objects.h
        UI/widgets/AbstractButton.cpp
        UI/widgets/AbstractButton.h
        UI/widgets/basewidget.h
        UI/widgets/basewidget.cpp
        UI/widgets/button.h
        UI/widgets/button.cpp
        scrollarea.h
        container.h container.cpp
        Resources/ApplicationIcon.ico
        Resources/ApplicationIcon.png
        resources.qrc
        MainWindow.cpp MainWindow.h
        UI/style.qss
        propertyanimation.h propertyanimation.cpp
        zipreader_p.h
        zipwriter_p.h
        systeminfo.cpp
        systeminfo.h
        header/CMakeLists.txt
        header/emailaddress.cpp
        header/emailaddress.h
        header/mimeattachment.cpp
        header/mimeattachment.h
        header/mimebase64encoder.cpp
        header/mimebase64encoder.h
        header/mimebase64formatter.cpp
        header/mimebase64formatter.h
        header/mimebytearrayattachment.cpp
        header/mimebytearrayattachment.h
        header/mimecontentencoder.cpp
        header/mimecontentencoder.h
        header/mimecontentformatter.cpp
        header/mimecontentformatter.h
        header/mimefile.cpp
        header/mimefile.h
        header/mimehtml.cpp
        header/mimehtml.h
        header/mimeinlinefile.cpp
        header/mimeinlinefile.h
        header/mimemessage.cpp
        header/mimemessage.h
        header/mimemultipart.cpp
        header/mimemultipart.h
        header/mimepart.cpp
        header/mimepart.h
        header/mimeqpencoder.cpp
        header/mimeqpencoder.h
        header/mimeqpformatter.cpp
        header/mimeqpformatter.h
        header/mimetext.cpp
        header/mimetext.h
        header/quotedprintable.cpp
        header/quotedprintable.h
        header/smtpclient.cpp
        header/smtpclient.h
        header/SMTPEmail.pro
        header/SmtpMime
        header/smtpmime_global.h
        header/SmtpMimeConfig.cmake
        sidebar_panel.h sidebar_panel.cpp
        UI/Controller/filecontroller.h
        UI/Controller/filecontroller.cpp
        UI/overlay/overlay_box.cpp
        UI/overlay/overlay_box.h
        UI/overlay/box.h
        UI/overlay/box.cpp
        api/ui/res.h
        api/ui/window_main.cpp
        api/ui/window_main.h
        api/api_window.cpp
        api/api_window.h
        api/api_window_helper.cpp
        api/api_window_helper.h
        api/api_window_shadow.cpp
        api/api_window_shadow.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET app APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(app SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(app
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(app PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::PrintSupport)

# ДОБАВЬ ЭТО ДЛЯ WINDOWS
if(WIN32)
    # Для MinGW
    target_link_libraries(app PRIVATE dwmapi)
    # Или для всех Windows компиляторов
    # find_library(DWMAPI dwmapi)
    # target_link_libraries(st PRIVATE ${DWMAPI})
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.app)
endif()
set_target_properties(app PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(app)
endif()
