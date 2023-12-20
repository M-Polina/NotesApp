#include "algorythms.h"

Algorythms::Algorythms() {}

QString Algorythms::makeConnectionNotifyString(QHostAddress address, quint16 port) {
    return "Connected to " + address.toString() + ":" + QString::number(port);
}

QString Algorythms::makeDisconnectionNotifyString(QHostAddress address, quint16 port) {
    return "Disconnected from " + address.toString() + ":" + QString::number(port);
}
