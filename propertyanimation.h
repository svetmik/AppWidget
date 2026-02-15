#ifndef PROPERTYANIMATION_H
#define PROPERTYANIMATION_H

#include "UI/widgets/basewidget.h"
#include <iostream>
#include <thread>  // Required for std::this_thread::sleep_for
#include <chrono>  // Required for duration types

namespace pa {

class PropertyAnimation : public QPropertyAnimation
{
    Q_OBJECT
public:

    explicit PropertyAnimation(ui::uiWidget *parent);
    explicit PropertyAnimation(ui::uiWidget *parent, const QByteArray &prop);

    void setDurationf(int msecs);
    void setStartAnimation(const QVariant &begin_val, const QVariant &end_val, int microsecond = 800);
    void setEndAnimation(const QVariant &begin_val, const QVariant &end_val, int microsecond = 800);

    QVariant startAnimation();
    QVariant endAnimation();
private:

    void setEsingCurvef(const QEasingCurve &easing);
    void setStartValuef(const QVariant &var);
    void setEndValuef(const QVariant &var);
signals:
};

}


#endif // PROPERTYANIMATION_H
