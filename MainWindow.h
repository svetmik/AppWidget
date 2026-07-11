#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPointer>
#include <QFont>
#include "font.h"
#include "api/ui/window_main.h"
#include "widget.h"

namespace {

QString loadFont()   {

    Font initFontFamily;

    initFontFamily.loadFontForWidget(styleFont::FONT_REGULAR);

    const auto fontFamily =  initFontFamily.fontFamily();

    return fontFamily;
}

QFont fontSettings()  {

    QFont qAppFontGlobal;

    qAppFontGlobal.setFamily(loadFont());
    qAppFontGlobal.setPointSizeF(10);
    qAppFontGlobal.setWeight(QFont::Weight::DemiBold);
    qAppFontGlobal.setStyle(QFont::StyleNormal);

    qAppFontGlobal.setStyleStrategy(QFont::PreferAntialias);

    qAppFontGlobal.setKerning(true);

    return qAppFontGlobal;
}

}
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    QPointer<uiWindow> m_uiHelper;

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    QPointer<Widget> m_widget;
protected:
    bool nativeEvent(
        const QByteArray &eventType,
        void *message,
        qintptr *result) override;

    bool event(QEvent *evt) override;

};
#endif // MAINWINDOW_H
