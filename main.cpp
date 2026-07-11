#include "mainwindow.h"
#include "style_widget.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setFont(fontSettings());

    MainWindow window;

    style_widget initStyle;
    initStyle.includeStyle();
    initStyle.setStyle(&window);

    QObject::connect(window.m_widget->_exitAppButton, &Button::clicked, &app, &QApplication::quit);

    window.setMinimumSize(550,350);
    window.setMaximumSize(550,350);

    Updater update;

    window.show();

    return app.exec();
}
