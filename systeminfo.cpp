#include "systeminfo.h"



SystemInfo::SystemInfo() {

}



QString SystemInfo::localIpAddressPc()
{

    const QList<QHostAddress> &local_address = QNetworkInterface::allAddresses();

    //fix
    if(local_address.isEmpty()) {
        qWarning() << "No network interfaces found";
    } else {

        for(const QHostAddress &local_address : QNetworkInterface::allAddresses())
        {
            if(local_address.protocol() == QAbstractSocket::IPv4Protocol && !local_address.isLoopback())
            {
                return local_address.toString();
            }
        }

    }

    return QString();
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


