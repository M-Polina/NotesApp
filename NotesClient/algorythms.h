#ifndef ALGORYTHMS_H
#define ALGORYTHMS_H

#include <QDialog>
#include <QHostAddress>


class Algorythms
{
public:
    Algorythms();
    static QString makeConnectionNotifyString(QHostAddress address, quint16 port);
    static QString makeDisconnectionNotifyString(QHostAddress address, quint16 port);
};

#endif // ALGORYTHMS_H
