#include "systeminfo.h"



SystemInfo::SystemInfo() {

}


QString SystemInfo::localIpAddressPc()
{

    for(const QHostAddress &local_address : QNetworkInterface::allAddresses()) {

        if(local_address.protocol() == QAbstractSocket::IPv4Protocol && local_address != QHostAddress(QHostAddress::LocalHost)) {
                return local_address.toString();

        }

    }

    return QString("None");
}

QString SystemInfo::localPrinterName()
{
    QPrinter printName;

    return printName.printerName();

}

QString SystemInfo::localHostName()
{
    return QHostInfo::localHostName();
}


