#ifndef ABSTRACTBUTTON_H
#define ABSTRACTBUTTON_H


#include "basewidget.h"


class AbstractButton : public ui::uiWidget {

    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged FINAL)
    Q_PROPERTY(QColor colorText READ colorText WRITE setColorText NOTIFY colorTextChanged FINAL)
    Q_PROPERTY(bool isDisable READ isDisable WRITE setDisable NOTIFY disableChanged FINAL)
    Q_PROPERTY(bool isEnable READ isEnable WRITE setEnable NOTIFY  enableChanged FINAL)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged FINAL)


signals:
    void backgroundColorChanged(QColor color);
    void colorTextChanged(QColor color);
    void disableChanged(bool flag);
    void enableChanged(bool flag);
    void textChanged(QString title);
    void clicked(bool flag = false);
public:

    AbstractButton(QWidget *parent = nullptr);

    void setBackgroundColor(const QColor &bgColor) {
        if(_m_Color_bg != bgColor) {
            _m_Color_bg = bgColor;
            emit backgroundColorChanged(bgColor);
        }

    }
    QColor backgroundColor() const { return _m_Color_bg; }


    void setColorText(const QColor &color) {
        if(_colorText != color) {
            _colorText = color;
            emit backgroundColorChanged(color);
        }

    }
    QColor colorText() const { return _colorText; }


    void setDisable(bool disable = true) {
        if(_disabled != disable ) {
            _disabled = disable;
            emit disableChanged(disable);
        }

    }
    bool isDisable() const { return _disabled; }



    void setEnable(bool enable = false) {
        if(_enabled != enable) {
            _enabled = enable;
            emit enableChanged(enable);
        }

    }
    bool isEnable() const { return _enabled; }


    void setText(const QString &text) {
        if(_text != text) {
            _text = text;
            emit textChanged(text);
        }
    }
    QString text() const { return _text; }


    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:

    void updateHoverState(QPainter &p);

    QPen _pen;

    QColor _colorText;
    QColor _m_Color_bg;
    QColor _m_Color_hover;

    QString _text;

    bool _disabled;
    bool _enabled;

    bool hovered = false;

    QRect _rect;


};




#endif // ABSTRACTBUTTON_H
