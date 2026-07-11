#ifndef STYLE_WIDGET_H
#define STYLE_WIDGET_H

#include <QWidget>
#include <QFile>
#include <QString>
#include <QMainWindow>

namespace {
    constexpr char filePathUiStyle[] = ":/UI/style.qss";
}


class style_widget : public QWidget
{
    Q_OBJECT
public:

    explicit style_widget(QWidget *parent = nullptr);

    void includeStyle();

    void setStyle(QMainWindow *parent = nullptr);
    void setStyle(QWidget *parent = nullptr);

private:


    QString _fileName;
    QFile readStyleQss;

    void setOpenStyleQss(const QString &fileName);

    void readAll();

    //подключить стили к виджету
    QString getStyle();

signals:
};

#endif // STYLE_WIDGET_H
