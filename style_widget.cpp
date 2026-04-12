#include "style_widget.h"

style_widget::style_widget(QWidget *parent)
    : QWidget{parent}
{

}

void style_widget::setOpenStyleQss(const QString &fileName)  {

    this->_fileName = fileName;

    readStyleQss.setFileName(_fileName);

    if(readStyleQss.exists()) {

        readStyleQss.open(QFile::ReadOnly);

    }

}

void style_widget::readAll(){
    _fileName = this->readStyleQss.readAll();
}

QString style_widget::getStyle() {

    return this->_fileName;
}



