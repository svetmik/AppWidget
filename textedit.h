#ifndef TEXTEDIT_H
#define TEXTEDIT_H


#include <QTextEdit>
#include <QFile>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:

    explicit TextEdit(QWidget *parent = nullptr);



signals:
};

#endif // TEXTEDIT_H
