#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

#include <QFile>
#include "font.h"
#include "style_widget.h"


constexpr auto BTN_STYLE_QSS(":/UI/button.qss");
constexpr auto OBJECT_NAME("sendButton");

class Button : public QPushButton
{
    Q_OBJECT

public:

    Button() = default;

    Button(QWidget *parent= nullptr);

    Button(const QString &title, QWidget *parent = nullptr);

    Button(const QIcon &icon, const QString &title, QWidget *parent= nullptr);
    ~Button();


    Font _fontWidget;
    style_widget *qss;

protected:

    void debugFontInfo();

    QFont _font;

private:
    const QString _title{};
    const QIcon _icon{};
public slots:

};

#endif // BUTTON_H
