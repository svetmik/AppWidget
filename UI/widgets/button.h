#ifndef BUTTON_H
#define BUTTON_H

#include "AbstractButton.h"


class Button : public AbstractButton {

    Q_OBJECT
public:

    explicit Button(QWidget *parent = nullptr);
    explicit Button(const QString &title, QWidget *parent = nullptr);
    explicit Button(const QString &title, const FlagText &flag, QWidget *parent = nullptr);

protected:


private:

};


class LinkButton : public AbstractButton {

public:

    explicit LinkButton(QWidget *parent = nullptr);
    explicit LinkButton(const QString &title, QWidget *parent = nullptr, const FlagText flag = FlagText::leftText);

protected:

private:

    void defaultStyles();

};

#endif // BUTTON_H
