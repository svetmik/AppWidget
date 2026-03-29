#ifndef ABSTRACTBUTTON_H
#define ABSTRACTBUTTON_H


#include "basewidget.h"



class AbstractButton : public ui::uiWidget {

    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor colorText READ colorText WRITE setColorText)
    Q_PROPERTY(bool isDisable READ isDisable WRITE setDisable)
    Q_PROPERTY(bool isEnable READ isEnable WRITE setEnable)
    Q_PROPERTY(QString text READ text WRITE setText)

signals:
    void backgroundColorChanged(QColor color);
    void colorTextChanged(QColor color);
    void disableChanged(bool flag);
    void enableChanged(bool flag);
    void textChanged(QString title);
    void clicked();
    //void clicked(bool flag = false);
public:

    enum class FlagText {
        leftText = Qt::AlignLeft | Qt::AlignVCenter,
        rigthText = Qt::AlignRight | Qt::AlignVCenter,
        center = Qt::AlignCenter,
    };

    AbstractButton(QWidget *parent = nullptr, FlagText flag = FlagText::center);


    void setBackgroundColor(const QColor &bgColor) {
        if(_m_Color_bg != bgColor) {
            _m_Color_bg = bgColor;
            update();
        }

    }
    QColor backgroundColor() const { return _m_Color_bg; }


    void setHoverBackgroundColor(const QColor &hoverColor) {
        if(_m_Color_hover != hoverColor) {
            _m_Color_hover = hoverColor;
            update();
        }
    }

    QColor hoverBackgroundColor() const { return _m_Color_hover; }

    void setColorText(const QColor &color) {
        if(_colorText != color) {
            _colorText = color;
            update();
        }

    }
    QColor colorText() const { return _colorText; }


    void setDisable(bool disable = true) {
        if(_disabled != disable ) {
            _disabled = disable;
            update();
        }

    }
    bool isDisable() const { return _disabled; }



    void setEnable(bool enable = false) {
        if(_enabled != enable) {
            _enabled = enable;
            update();
        }

    }
    bool isEnable() const { return _enabled; }


    void setText(const QString &text) {
        if(_text != text) {
            _text = text;
            update();
            updatePaddingWidth();
        }
    }
    QString text() const { return _text; }


    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void setBorderRadius(const int &xRadiusRound, const int &yRadiusRound) {
        m_xRadiusRound = xRadiusRound;
        m_yRadiusRound = yRadiusRound;
    }
    int xRadius() const {
        return m_xRadiusRound;
    }

    int yRadius() const {
        return m_yRadiusRound;
    }

    // default Align text Qt::AlignCenter
    void setAlignText(const FlagText &flag) {
        this->_alignFlag = flag;
    }

    void setPaddingsWidth(const int &left, const int &right);
    void updatePaddingWidth();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:

    void updateHoverState(QPainter &p, QRect &r);

    QPen _pen;

    QColor _colorText;
    QColor _m_Color_bg;
    QColor _m_Color_hover;

    QString _text;

    bool _disabled;
    bool _enabled;

    bool hovered = false;

    QRect _rect;

    int m_xRadiusRound{0};
    int m_yRadiusRound{0};

    //enum class
    FlagText _alignFlag;

    int _actual_padding_left = 0;
    int _actual_padding_top = 0;
    int _actual_padding_right = 0;
    int _actual_padding_bottom = 0;

};






#endif // ABSTRACTBUTTON_H
