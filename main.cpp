#include "widget.h"
#include "sidebar.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // Главное окно
    Widget *window = new Widget();


    window->setMinimumSize(0,0);
    window->resize(800, 500);
    window->show();

    return a.exec();
}
