#include "propertyanimation.h"

pa::PropertyAnimation::PropertyAnimation(ui::uiWidget *parent)
    : QPropertyAnimation(parent)
{
    this->setDurationf(270);
    this->setEsingCurvef(QEasingCurve::OutQuint);
}

pa::PropertyAnimation::PropertyAnimation(ui::uiWidget *parent, const QByteArray &prop)
    : QPropertyAnimation(parent, prop)

{
    this->setDurationf(270);
    this->setEsingCurvef(QEasingCurve::OutQuint);
}

void pa::PropertyAnimation::setStartAnimation(const QVariant &begin_val, const QVariant &end_val, int microsecond) {
    this->setStartValuef(begin_val);
    this->setEndValuef(end_val);
    // set pause before start animatiom
    std::this_thread::sleep_for(std::chrono::microseconds(microsecond));
}

void pa::PropertyAnimation::setEndAnimation(const QVariant &begin_val, const QVariant &end_val, int microsecond) {
    this->setStartValuef(begin_val);
    this->setEndValuef(end_val);
    // set pause before start end animatiom
    std::this_thread::sleep_for(std::chrono::microseconds(microsecond));
}



void pa::PropertyAnimation::setDurationf(int msecs) {
    this->setDuration(msecs);
}

void pa::PropertyAnimation::setEsingCurvef(const QEasingCurve &easing) {
    this->setEasingCurve(easing);
}

void pa::PropertyAnimation::setStartValuef(const QVariant &var) {
    this->setStartValue(var);
}
void pa::PropertyAnimation::setEndValuef(const QVariant &var) {
    this->setEndValue(var);
}


