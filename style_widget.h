#ifndef STYLE_WIDGET_H
#define STYLE_WIDGET_H

#include <QWidget>
#include <QFile>
#include <QString>


class style_widget : public QWidget
{
    Q_OBJECT
public:
    explicit style_widget(QWidget *parent = nullptr);


    void setOpenStyleQss(const QString &fileName);

    void readAll();

    QString getStyle();

private:

    QString _fileName;
    QFile readStyleQss;

signals:
};

#endif // STYLE_WIDGET_H
