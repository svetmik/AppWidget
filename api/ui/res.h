#ifndef RES_H
#define RES_H

#include <QString>
#include <QPushButton>

namespace {

QPushButton *windowTitleBtn(QWidget *parent, const QString &style, const bool &stateFlag, const int &fixWidth) {

    auto *btn = new QPushButton(parent);

    btn->setFixedWidth(fixWidth);

    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    btn->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    btn->setStyleSheet(style);

    btn->setVisible(stateFlag);

    return btn;
}


}
inline QString qss_title_btn_close() {
    return R"(
            QPushButton {
                border-image: url(:/icon/btn_close.png);
                background-color: rgba(255, 255, 255, 0%);
                background-repeat: no-repeat;
            }
            QPushButton:hover {
                border-image: url(:/icon/btn_close_hover.png);
                background-color: #e81123;
            }
            QPushButton:pressed {
                border-image: url(:/icon/btn_close_hover.png);
                background-color: #e81123;
            }
            QPushButton:!active {
                border-image: url(:/icon/btn_close.png);

            }
            QPushButton:hover:!active {
                border-image: url(:/icon/btn_close_hover.png);
                background-color: #e81123;
            }
        )";
}

inline QString qss_title_btn_minimize() {
    return R"(
            QPushButton {
                border-image: url(:/icon/button_minimize.png);
                background-color: rgba(255, 255, 255, 0%);
                background-repeat: no-repeat;
            }

            QPushButton:hover {
                background-color: rgba(228, 228, 228, 80%);
            }

            QPushButton:pressed {
                background-color: rgba(255, 255, 255, 40%);
            }

            QPushButton:!active {
                border-image: url(:/icon/button_minimize.png);
            }
        )";
}

inline QString qss_m_maximize_btn() {
    return R"(
            QPushButton {
                border-image: url(:/icon/button_maximize.png);
                background-color: rgba(255, 255, 255, 0%);
                background-repeat: no-repeat;
            }
            QPushButton:hover {
                background-color: rgba(228, 228, 228, 80%);
            }
            QPushButton:pressed {
                background-color: rgba(255, 255, 255, 40%);
            }
            QPushButton:checked {
                border-image: url(:/icon/button_restore.png);
                background-color: rgba(255, 255, 255, 0%);
                background-repeat: no-repeat;
            }
            QPushButton:checked:hover {
                background-color: rgba(228, 228, 228, 80%);
            }
            QPushButton:checked:pressed {
                background-color: rgba(255, 255, 255, 40%);
            }
            QPushButton:!active {
                border-image: url(:/icon/button_maximize.png);
            }
            QPushButton:checked:!active {
                border-image: url(:/icon/button_restore.png);
            }
        )";
}

#endif // RES_H

