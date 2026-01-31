#ifndef BUTTON_H
#define BUTTON_H

#include "AbstractButton.h"
#include "../../../../../../../Users/user/repos/AppWidget/font.h"
#include "QFont"

class Button : public AbstractButton {

    Q_OBJECT
public:

    explicit Button(QWidget *parent = nullptr);
    explicit Button(const QString &title, QWidget *parent = nullptr);
protected:

    Font m_font;
    QFont _font;

private:

};

#endif // BUTTON_H
