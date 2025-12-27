#include "textedit.h"

TextEdit::TextEdit(QWidget *parent)
    : QTextEdit{parent}
{

    this->setObjectName(OBJECT_NAME_TEXTEDIT);

    qss = new style_widget(this);

    qss->setOpenStyleQss(TEXTEDIT_QSS);

    qss->readAll();

    this->setStyleSheet(qss->getStyle());


}


