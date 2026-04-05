#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H


#include <QWidget>
#include <QPrinter>
#include <QTcpSocket>

#include <QHostInfo>
#include <QNetworkInterface>

class SystemInfo {

private:

public:

    explicit SystemInfo();

    QString localIpAddressPc();

    QString localPrinterName();

    QString localHostName();

};


#endif // SYSTEMINFO_H
