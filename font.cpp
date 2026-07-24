#include "font.h"



Font::Font(QWidget *parent)
    : ui::uiWidget{parent}
{

}

void Font::loadFontForWidget(const QString &filename) {

   this->_idFont = _base.addApplicationFont(filename);

    applicationFontFamilies(_idFont);
}


void Font::applicationFontFamilies(const int &id_font)  {

    this->_data = _base.applicationFontFamilies(id_font).at(0);

}


QString Font::fontFamily() const {
    return _data;
}
