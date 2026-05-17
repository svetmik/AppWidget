


#include <QApplication>
#include "MainWindow.h"
#include "widget.h"
#include "font.h"
#include "ui/widgets/button.h"

#define FLAG_STATE false

QString loadFont() {

    Font initFontFamily;

    initFontFamily.loadFontForWidget(styleFont::FONT_REGULAR);

    const auto fontFamily =  initFontFamily.fontFamily();

    return fontFamily;
}

QFont fontSettings() {

    QFont qAppFontGlobal;

    qAppFontGlobal.setFamily(loadFont());
    qAppFontGlobal.setPointSizeF(10);
    qAppFontGlobal.setWeight(QFont::Weight::DemiBold);
    qAppFontGlobal.setStyle(QFont::StyleNormal);

    qAppFontGlobal.setStyleStrategy(QFont::PreferAntialias);

    qAppFontGlobal.setKerning(true);

    return qAppFontGlobal;
}


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);

    MainWindow window;

    app.setFont(fontSettings());

    window.setResizeBorderWidth(6); //! You can set the resize border width.
    window.setTitlebarHeight(24);   //! You also can set the title bar height.

    QWidget *non_clickable = new QWidget(&window);
    non_clickable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    non_clickable->setProperty("clickable widget", false);
    window.getCustomTitlebarLayout().addWidget(non_clickable);

    window.setWindowIcon(QIcon(":/icon/ApplicationIcon.png"));

    auto pal = window.getTitlebarWidget().palette();
    pal.setColor(QPalette::Window, QColor(241,241,241));
    window.getTitlebarWidget().setAutoFillBackground(true);
    window.getTitlebarWidget().setPalette(pal);

    //! MainWindow class provides getContentWidget() function.
    //! It return main content widget.
    // Set main content widget palette.
    pal = window.getContentWidget().palette();
    pal.setColor(QPalette::Window, QColor(255,255,255));
    window.getContentWidget().setAutoFillBackground(true);
    window.getContentWidget().setPalette(pal);

    // Add layout to main content widget.
    QVBoxLayout *main_widget_layout = new QVBoxLayout(&window);
    main_widget_layout->setContentsMargins(0,0,0,0);
    window.getContentWidget().setLayout(main_widget_layout);

    Widget *main_container = new Widget(&window.getContentWidget());

    main_widget_layout->addWidget(main_container);

    main_container->qss.includeStyle();

    main_container->qss.setStyle(main_container);

    if(FLAG_STATE) {

        QByteArray screen_data = main_container->getScreenshotApp(0, "JPG", 30);

        main_container->writetoFile("debug", "screenshot_data.png", screen_data);
    }

    QObject::connect(main_container->_exitAppButton, &Button::clicked, &app, &QApplication::quit);
    window.setMinimumSize(550,350);
    window.setMaximumSize(550,350);
    window.show();
    return app.exec();
}
