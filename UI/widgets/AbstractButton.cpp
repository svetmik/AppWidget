#include "AbstractButton.h"


AbstractButton::AbstractButton(QWidget *parent)
    : ui::uiWidget(parent)
    , _colorText(255, 255, 255) // colorText Button Widget
    , _m_Color_bg(43,137,247, 235)
    , _m_Color_hover(31,111,204)
    , _disabled(true)
    , _enabled(false)
{

    this->setMouseTracking(true);
    this->setCursor(Qt::PointingHandCursor);

    this->setStyleSheet("border: none;");

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);


    _rect = rect();
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

void AbstractButton::updateHoverState(QPainter &p, QRect &r) {

    if(hovered) {
        p.fillRect(r, QBrush(_m_Color_hover));
    } else {
        p.fillRect(r, QBrush(_m_Color_bg));
    }

}
void AbstractButton::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    p.setPen(Qt::NoPen);
    p.setBrush(hovered ? _m_Color_hover : _m_Color_bg);
    p.drawRoundedRect(_rect, this->m_xRadiusRound, this->m_yRadiusRound);

    p.setRenderHint(QPainter::Antialiasing, false);
    p.setRenderHint(QPainter::TextAntialiasing); // Специально для текста
    p.setPen(_colorText);
    p.drawText(_rect, Qt::AlignCenter, _text);

    // p.fillRect(_rect, hovered
    //                       ?
    //                       _m_Color_hover
    //                       :
    //                       _m_Color_bg);

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
    _rect = rect();

    ui::uiWidget::resizeEvent(event);
}

void AbstractButton::mousePressEvent(QMouseEvent *event) {

    if(event->buttons() == Qt::LeftButton)  {
        qDebug() << "click left btn mouse";
    } else if (event->buttons() == Qt::RightButton) {
        qDebug() << "click right btn mouse";
    }
}

void AbstractButton::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (rect().contains(event->pos())) {
            emit clicked();
        }
    }
    ui::uiWidget::mouseReleaseEvent(event);
}

























