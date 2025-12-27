#ifndef TEXTEDIT_H
#define TEXTEDIT_H


#include <QTextEdit>
#include <QFile>
#include "style_widget.h"

constexpr auto OBJECT_NAME_TEXTEDIT("TextInput");
constexpr auto TEXTEDIT_QSS(":/UI/TextEdit.qss");

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:

    explicit TextEdit(QWidget *parent = nullptr);

    style_widget *qss;

signals:
};

#endif // TEXTEDIT_H
