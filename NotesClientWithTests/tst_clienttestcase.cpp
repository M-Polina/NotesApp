#include <QCoreApplication>
#include <QtTest>
#include "/Users/andreymarusin/Polina/C_plus_Labs/NotesApp/NotesClient/algorythms.h"
#include "/Users/andreymarusin/Polina/C_plus_Labs/NotesApp/NotesClient/algorythms.cpp"


class ClientTestCase : public QObject
{
    Q_OBJECT

public:
    ClientTestCase();
    ~ClientTestCase();

private slots:
    void test_make_disconnection_notify_string();
    void cleanupTestCase();
    void test_make_connection_notify_string();
};

ClientTestCase::ClientTestCase() {}

ClientTestCase::~ClientTestCase() {}

void ClientTestCase::test_make_disconnection_notify_string() {
    QString str = Algorythms::makeDisconnectionNotifyString(QHostAddress("127.0.0.1"), (quint16)8080);
    QCOMPARE(str, QString("Disconnected from 127.0.0.1:8080"));
}

void ClientTestCase::cleanupTestCase() {}

void ClientTestCase::test_make_connection_notify_string() {
    QString str = Algorythms::makeConnectionNotifyString(QHostAddress("127.0.0.1"), (quint16)8080);
    QCOMPARE(str, QString("Connected to 127.0.0.1:8080"));
}

QTEST_MAIN(ClientTestCase)

#include "tst_clienttestcase.moc"
