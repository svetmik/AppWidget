#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;

    app.setFont(fontSettings());

    QObject::connect(window.m_widget->_exitAppButton, &Button::clicked, &app, &QApplication::quit);

    window.setMinimumSize(550,350);
    window.setMaximumSize(550,350);

    window.show();

    return app.exec();
}
