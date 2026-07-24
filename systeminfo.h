#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H


#include <QWidget>
#include <QPrinterInfo>
#include <QTcpSocket>

#include <QHostInfo>
#include <QNetworkInterface>

class SystemInfo {

private:
    QPrinterInfo m_infoPrinter;
public:

    explicit SystemInfo();

    QString localIpAddressPc();

    QString localPrinterName();

    QString localHostName();



};


#endif // SYSTEMINFO_H
