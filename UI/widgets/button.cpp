#include "widget.h"

ui::uiWidget::uiWidget(QWidget *parent)
    :BaseWidget<QWidget>(parent)
{

}


ui::uiWidget::~uiWidget() {

}


void ui::uiWidget::paintEvent(QPaintEvent *event) {

    QStyleOption opt;

    opt.initFrom(this);

    QPainter p(this);

    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}


AbstractButton::AbstractButton(QWidget *parent)
    : ui::uiWidget(parent)
    , _colorText(255, 255, 255) // colorText Button Widget
    , _m_Color_bg(43,137,247)
    , _m_Color_hover(31,111,204)
    , _disabled(true)
    , _enabled(false)
{
    this->setMouseTracking(true);
    this->setCursor(Qt::PointingHandCursor);

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

QSize AbstractButton::sizeHint() const {
    // Рассчитываем размер на основе текста
    QFontMetrics fm(this->font());
    int textWidth = fm.horizontalAdvance(_text) + 40;  // + отступы по 20px с каждой стороны
    int textHeight = fm.height() + 20;                 // + отступы по 10px сверху/снизу

    // Возвращаем размер, но не меньше минимального
    return QSize(qMax(100, textWidth), qMax(40, textHeight));
}

QSize AbstractButton::minimumSizeHint() const {
    return sizeHint();  // Минимальный размер кнопки
}

void AbstractButton::updateHoverState(QPainter &p) {

    if(hovered) {
        p.fillRect(_rect, QBrush(_m_Color_hover));
    } else {
        p.fillRect(_rect, QBrush(_m_Color_bg));
    }

}
void AbstractButton::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    _pen.setColor(_colorText);

    _rect = event->rect();


    this->updateHoverState(p);
    p.setPen(_pen);
    p.drawText(_rect, Qt::AlignHCenter | Qt::AlignVCenter, _text);


}

void AbstractButton::enterEvent(QEnterEvent *event) {
    this->hovered = true;

    this->update();
}
void AbstractButton::leaveEvent(QEvent *event) {
    this->hovered = false;

    this->update();
}

void AbstractButton::resizeEvent(QResizeEvent *event) {

}

void AbstractButton::mousePressEvent(QMouseEvent *event) {

    if(event->buttons() == Qt::LeftButton)  {
        qDebug() << "click left btn mouse";
    } else if (event->buttons() == Qt::RightButton) {
        qDebug() << "click right btn mouse";
    }
}

void AbstractButton::mouseReleaseEvent(QMouseEvent *event) {

}

Button::Button(QWidget *parent)
    : AbstractButton(parent)
{

}

Button::Button(const QString &title, QWidget *parent)
    : AbstractButton(parent)
{
    this->setText(title);
}























