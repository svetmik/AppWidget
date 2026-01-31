#ifndef CONTAINER_H
#define CONTAINER_H

#include <QWidget>
#include <QMargins>

class Container : public QWidget
{
    Q_OBJECT
public:
    explicit Container(QWidget *parent = nullptr);

    void setMargins();
signals:

private:
    QMargins m_margin;

};

#endif // CONTAINER_H
