#include "AbstractButton.h"



AbstractButton::AbstractButton(QWidget *parent, FlagText flag)
    : ui::uiWidget(parent)
    , _colorText(255, 255, 255) // colorText Button Widget
    , _m_Color_bg(0, 150, 237, 255)
    , _m_Color_hover(31,111,204)
    , _disabled(true)
    , _enabled(false)
    , _alignFlag(flag)
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

// void AbstractButton::updateHoverState(QPainter &p, QRect &r) {

//     if(hovered) {
//         p.fillRect(r, QBrush(_m_Color_hover));
//     } else {
//         p.fillRect(r, QBrush(_m_Color_bg));
//     }

// }


void AbstractButton::setPaddingsWidth(const int &left, const int &right) {

    this->_actual_padding_left = left;
    this->_actual_padding_right = right;

}

void AbstractButton::updatePaddingWidth()
{
    // Здесь можно пересчитать отступы в зависимости от размера текста
    QFontMetrics fm(this->font());

    int widthFont = fm.horizontalAdvance(_text);

    if(_actual_padding_left + _actual_padding_right > widthFont) {
        _actual_padding_left = 0;
        _actual_padding_right = 0;
        qDebug() << "Fatal width";
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
    p.setRenderHint(QPainter::TextAntialiasing);
    p.setPen(_colorText);


    // Используем отступы
    QRect textRect = _rect.adjusted(
        _actual_padding_left,
        _actual_padding_top,
        -_actual_padding_right,
        -_actual_padding_bottom
    );

    p.drawText(textRect, static_cast<int>(_alignFlag), _text);


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

























