#ifndef BUTTON_H
#define BUTTON_H

#include "AbstractButton.h"


class Button : public AbstractButton {

    Q_OBJECT
public:

    explicit Button(QWidget *parent = nullptr);
    explicit Button(const QString &title, QWidget *parent = nullptr);
protected:


private:

};

#endif // BUTTON_H
