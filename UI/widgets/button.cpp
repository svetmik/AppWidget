#include "button.h"
#include "QFont"


Button::Button(QWidget *parent)
    : AbstractButton(parent)
{


}

Button::Button(const QString &title, QWidget *parent)
    : AbstractButton(parent)
{
    this->setText(title);


    m_font.loadFontForWidget(styleFont::FONT_REGULAR);

    const auto family = m_font.fontFamily();

    if(!family.isEmpty()) {
        qDebug() << "Шрифт загрузился";
    }

    _font.setFamily(family);
    _font.setPointSize(10);
    this->setFont(_font);

    _font = this->font();

    qDebug() << "Семейство:" << _font.family();
    qDebug() << "Размер:" << _font.pointSize();
    qDebug() << "Жирный:" << _font.bold();
    qDebug() << "Курсив:" << _font.italic();
    qDebug() << "Подчеркнутый:" << _font.underline();
    qDebug() << "Вес:" << _font.weight(); // QFont::Weight
}
