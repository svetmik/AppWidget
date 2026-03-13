#include "systeminfo.h"

SystemInfo::SystemInfo() {

}



QString SystemInfo::localIpAddressPc()
{
    for(const QHostAddress &address : QNetworkInterface::allAddresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback())
        {
            return address.toString();
        }
    }
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


