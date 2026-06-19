#include "mainwindow.h"

#define FLAG_STATE false

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_uiHelper = new uiWindow(this);
    m_uiHelper->initCentralWidget(this);

    QWidget *non_clickable = new QWidget(this);
    non_clickable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    non_clickable->setProperty("clickable widget", false);
    m_uiHelper->getCustomTitlebarLayout().addWidget(non_clickable);

    m_widget = new Widget(&m_uiHelper->getContentWidget());

    QVBoxLayout *main_widget_layout = new QVBoxLayout(this);
    main_widget_layout->setContentsMargins(0,0,0,0);
    main_widget_layout->addWidget(m_widget);

    m_uiHelper->getContentWidget().setLayout(main_widget_layout);

    if(FLAG_STATE) {

        QByteArray screen_data = m_widget->getScreenshotApp(0, "JPG", 30);

        m_widget->writetoFile("debug", "screenshot_data.png", screen_data);
    }

}

MainWindow::~MainWindow() {

}


bool MainWindow::nativeEvent(

    const QByteArray &eventType,
    void *message,
    qintptr *result)
{
    MSG *msg = static_cast<MSG*>(message);

    if(m_uiHelper->nativeEvent(eventType, msg, result)) {
        return true;
    }

    return QMainWindow::nativeEvent(
        eventType,
        message,
        result);
}


bool MainWindow::event(QEvent *evt)
{
    switch (evt->type())
    {
    case QEvent::WindowActivate: {
#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)

        //Q_ASSERT(m_maximize_btn);
        m_uiHelper->m_close_btn->setStyleSheet(m_uiHelper->m_close_btn->styleSheet());
        m_uiHelper->m_minimize_btn->setStyleSheet(m_uiHelper->m_minimize_btn->styleSheet());
        m_uiHelper->m_maximize_btn->setStyleSheet(m_uiHelper->m_maximize_btn->styleSheet());
#endif
        m_uiHelper->propagateActiveStateInCustomTitlebar(&m_uiHelper->getCustomTitlebarLayout(), true);
        break;
    }

    case QEvent::WindowDeactivate: {
#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)
        m_uiHelper->m_close_btn->setStyleSheet(m_uiHelper->m_close_btn->styleSheet());
        m_uiHelper->m_minimize_btn->setStyleSheet(m_uiHelper->m_minimize_btn->styleSheet());
        m_uiHelper->m_maximize_btn->setStyleSheet(m_uiHelper->m_maximize_btn->styleSheet());
#endif
        m_uiHelper->propagateActiveStateInCustomTitlebar(&m_uiHelper->getCustomTitlebarLayout(), false);
        break;
    }

    default:
        break;
    }

    return QMainWindow::event(evt);
}
