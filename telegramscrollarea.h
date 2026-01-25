// telegramscrollarea.h
#ifndef TELEGRAMSCROLLAREA_H
#define TELEGRAMSCROLLAREA_H

#include <QScrollArea>
#include <QPropertyAnimation>
#include <QTimer>
#include <QWheelEvent>
#include <QScrollBar>
#include <QEasingCurve>

class TelegramScrollArea : public QScrollArea
{
    Q_OBJECT
    Q_PROPERTY(int scrollOpacity READ scrollOpacity WRITE setScrollOpacity)

public:
    explicit TelegramScrollArea(QWidget *parent = nullptr)
        : QScrollArea(parent)
        , m_scrollOpacity(0)
        , m_smoothScrollEnabled(true)
        , m_targetScrollValue(0)
        , m_alwaysShowWhenNeeded(true)  // НОВОЕ: всегда показывать если нужно
    {
        // Настройка области
        setWidgetResizable(true);
        setFrameShape(QFrame::NoFrame);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        // Настройка стиля полосы прокрутки
        setupScrollBarStyle();

        // Анимация скролла
        m_scrollAnimation = new QPropertyAnimation(verticalScrollBar(), "value", this);
        m_scrollAnimation->setEasingCurve(QEasingCurve::OutCubic);
        m_scrollAnimation->setDuration(300);

        connect(m_scrollAnimation, &QPropertyAnimation::finished,
                this, &TelegramScrollArea::onScrollAnimationFinished);

        // Таймер для скрытия полосы прокрутки
        m_scrollHideTimer = new QTimer(this);
        m_scrollHideTimer->setSingleShot(true);
        m_scrollHideTimer->setInterval(1500);
        connect(m_scrollHideTimer, &QTimer::timeout,
                this, &TelegramScrollArea::hideScrollBar);

        // Начальное состояние
        updateScrollBarStyle();

        // Проверяем сразу нужен ли скролл
        QTimer::singleShot(100, this, &TelegramScrollArea::checkScrollNeeded);
    }

    void setUseSmoothScroll(bool enable) { m_smoothScrollEnabled = enable; }
    bool useSmoothScroll() const { return m_smoothScrollEnabled; }

    // НОВЫЙ МЕТОД: всегда показывать скролл когда он нужен
    void setAlwaysShowWhenNeeded(bool show) {
        m_alwaysShowWhenNeeded = show;
        checkScrollNeeded();
    }

    bool alwaysShowWhenNeeded() const { return m_alwaysShowWhenNeeded; }

    void scrollToBottom() {
        if (widget()) {
            verticalScrollBar()->setValue(verticalScrollBar()->maximum());
            showScrollBarTemporarily();
        }
    }

    void scrollToTop() {
        verticalScrollBar()->setValue(verticalScrollBar()->minimum());
        showScrollBarTemporarily();
    }

    void ensureWidgetVisible(QWidget *widget, int xmargin = 50, int ymargin = 50) {
        QScrollArea::ensureWidgetVisible(widget, xmargin, ymargin);
        showScrollBarTemporarily();
    }

    // Метод для принудительного показа полосы на время
    void showScrollBarTemporarily(int timeoutMs = 1500) {
        fadeInScrollBar();
        m_scrollHideTimer->start(timeoutMs);
    }

    // НОВЫЙ МЕТОД: принудительно показать скролл
    void showScrollBar() {
        fadeInScrollBar();
        m_scrollHideTimer->stop(); // Не скрываем автоматически
    }

    // НОВЫЙ МЕТОД: проверить нужен ли скролл и показать/скрыть
    void checkScrollNeeded() {
        if (!widget()) return;

        bool scrollNeeded = widget()->height() > height();

        if (scrollNeeded && m_alwaysShowWhenNeeded) {
            // Если скролл нужен и включена опция "всегда показывать"
            showScrollBar();
        } else if (!scrollNeeded) {
            // Если скролл не нужен - скрываем
            fadeOutScrollBar();
        }
        // Иначе оставляем как есть (показан если пользователь скроллил)
    }

    // Настройка стиля
    void setScrollBarStyle(const QString& style) {
        m_scrollBarStyle = style;
        updateScrollBarStyle();
    }

    QString scrollBarStyle() const { return m_scrollBarStyle; }

protected:
    void wheelEvent(QWheelEvent *event) override {
        if (!m_smoothScrollEnabled || event->angleDelta().isNull()) {
            QScrollArea::wheelEvent(event);
            return;
        }

        handleSmoothScroll(event);
        event->accept();
    }

    void showEvent(QShowEvent *event) override {
        QScrollArea::showEvent(event);
        // Проверяем нужен ли скролл при показе
        QTimer::singleShot(50, this, &TelegramScrollArea::checkScrollNeeded);
    }

    void resizeEvent(QResizeEvent *event) override {
        QScrollArea::resizeEvent(event);
        // Проверяем нужен ли скролл при изменении размера
        QTimer::singleShot(50, this, &TelegramScrollArea::checkScrollNeeded);
    }

    // Обработка когда виджет меняется
    void set(QWidget *widget)  {
        QScrollArea::setWidget(widget);
        if (widget) {
            connect(widget, &QWidget::destroyed, this, [this]() {
                QTimer::singleShot(0, this, &TelegramScrollArea::checkScrollNeeded);
            });
        }
        QTimer::singleShot(100, this, &TelegramScrollArea::checkScrollNeeded);
    }

private slots:
    void onScrollAnimationFinished() {
        // После завершения анимации запускаем таймер скрытия
        // но только если не включено "всегда показывать"
        if (!m_alwaysShowWhenNeeded && !m_scrollHideTimer->isActive()) {
            m_scrollHideTimer->start();
        }
    }

    void hideScrollBar() {
        // Не скрываем если включено "всегда показывать"
        if (!m_alwaysShowWhenNeeded) {
            fadeOutScrollBar();
        }
    }

private:
    void setupScrollBarStyle() {
        m_scrollBarStyle = R"(
            QScrollBar:vertical {
                border: none;
                background: transparent;
                width: 6px;
                margin: 0px;
            }

            QScrollBar::handle:vertical {
                background: rgba(150, 150, 150, %1);
                border-radius: 3px;
                min-height: 20px;
            }

            QScrollBar::handle:vertical:hover {
                background: rgba(120, 120, 120, %1);
            }

            QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
                height: 0px;
            }

            QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
                background: none;
            }
        )";
    }

    void updateScrollBarStyle() {
        verticalScrollBar()->setStyleSheet(
            m_scrollBarStyle.arg(m_scrollOpacity)
            );
    }

    void handleSmoothScroll(QWheelEvent *event) {
        int delta = event->angleDelta().y();
        int currentValue = verticalScrollBar()->value();
        int maxValue = verticalScrollBar()->maximum();
        int minValue = verticalScrollBar()->minimum();

        // Вычисляем целевое значение
        m_targetScrollValue = currentValue - delta / 2;
        m_targetScrollValue = qMax(minValue, qMin(m_targetScrollValue, maxValue));

        if (m_targetScrollValue == currentValue) {
            return;
        }

        // Останавливаем предыдущую анимацию
        if (m_scrollAnimation->state() == QAbstractAnimation::Running) {
            m_scrollAnimation->stop();
        }

        // Запускаем новую анимацию
        m_scrollAnimation->setStartValue(currentValue);
        m_scrollAnimation->setEndValue(m_targetScrollValue);
        m_scrollAnimation->start();

        // Показываем полосу прокрутки
        showScrollBarTemporarily();
    }

    int scrollOpacity() const { return m_scrollOpacity; }

    void setScrollOpacity(int opacity) {
        m_scrollOpacity = qBound(0, opacity, 100);
        updateScrollBarStyle();
    }

    void fadeInScrollBar() {
        if (m_scrollOpacity == 100) return;

        QPropertyAnimation *fadeIn = new QPropertyAnimation(this, "scrollOpacity");
        fadeIn->setDuration(150);
        fadeIn->setStartValue(m_scrollOpacity);
        fadeIn->setEndValue(100);
        fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
    }

    void fadeOutScrollBar() {
        if (m_scrollOpacity == 0) return;

        QPropertyAnimation *fadeOut = new QPropertyAnimation(this, "scrollOpacity");
        fadeOut->setDuration(300);
        fadeOut->setStartValue(m_scrollOpacity);
        fadeOut->setEndValue(0);
        fadeOut->start(QAbstractAnimation::DeleteWhenStopped);
    }

private:
    QPropertyAnimation *m_scrollAnimation;
    QTimer *m_scrollHideTimer;
    QString m_scrollBarStyle;
    int m_scrollOpacity;
    bool m_smoothScrollEnabled;
    bool m_alwaysShowWhenNeeded;  // НОВОЕ: всегда показывать если нужно
    int m_targetScrollValue;
};

#endif // TELEGRAMSCROLLAREA_H
