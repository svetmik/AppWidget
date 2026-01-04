#include "button.h"
#include <QFontDatabase>

Button::Button(QWidget *parent)
    : QPushButton(parent)
{

    this->setCursor(Qt::PointingHandCursor);
    this->setObjectName(OBJECT_NAME); // btn Name sendButton

    qss = new style_widget(this);
    qss->setOpenStyleQss(BTN_STYLE_QSS);
    qss->readAll();
    this->setStyleSheet(qss->getStyle());

    _fontWidget.loadFontForWidget(styleFont::FONT_REGULAR);

    const auto family = _fontWidget.fontFamily();

    _font.setFamily(family);
    _font.setPixelSize(12);

    this->setFont(_font);

}

Button::Button(const QString &title, QWidget *parent)
    : QPushButton(parent),
    _title{title}

{
    this->setDefault(false);
    this->setAutoFillBackground(true);
    this->setText(_title);
    this->setCursor(Qt::PointingHandCursor);
    this->setObjectName(OBJECT_NAME); // btn Name sendButton

    qss = new style_widget(this);
    qss->setOpenStyleQss(BTN_STYLE_QSS);
    qss->readAll();
    this->setStyleSheet(qss->getStyle());

    _fontWidget.loadFontForWidget(styleFont::FONT_REGULAR);

    const auto family = _fontWidget.fontFamily();
    if(!family.isEmpty()) {
        qDebug() << "Шрифт загрузился";
    }

    _font.setFamily(family);
    _font.setPointSize(10);
    _font.setWeight(QFont::Normal);
    _font.setStyleHint(QFont::SansSerif, QFont::PreferQuality);
    _font.setLetterSpacing(QFont::AbsoluteSpacing, 0.1);
    _font.setStretch(QFont::Unstretched);
    this->setFont(_font);

    _font = this->font(); // debug fontinfo

    this->debugFontInfo();

}

Button::Button(const QIcon &icon, const QString &title, QWidget *parent)
    : QPushButton(parent),
    _title{title},
    _icon{icon}
{
    this->setIcon(_icon);
    this->setText(_title);
    this->setCursor(Qt::PointingHandCursor);
    this->setObjectName(OBJECT_NAME); // btn Name sendButton

    qss = new style_widget(this);
    qss->setOpenStyleQss(BTN_STYLE_QSS);
    qss->readAll();
    this->setStyleSheet(qss->getStyle());

    _fontWidget.loadFontForWidget(styleFont::FONT_REGULAR);

    const auto family = _fontWidget.fontFamily();

    _font.setFamily(family);
    _font.setPixelSize(12);

    this->setFont(_font);

}


Button::~Button() {

}




void Button::debugFontInfo() {

    QFontInfo finfo(_font);
    qDebug() << "Widget:" << this->metaObject()->className()
             << "objectName:" << this->objectName();
    qDebug() << " requested family:" << _font.family()
             << "pointSize:" << _font.pointSize()
             << "weight:" << _font.weight()
             << "italic:" << _font.italic();
    qDebug() << " resolved family:" << finfo.family()
             << "styleName:" << finfo.styleName()
             << "pixelSize:" << finfo.pixelSize();
}
