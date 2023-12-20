#include <QCoreApplication>
#include <QtTest>
#include <QString>

#include "/Users/andreymarusin/Polina/C_plus_Labs/NotesApp/NotesServer/serveralgotythms.h"
#include "/Users/andreymarusin/Polina/C_plus_Labs/NotesApp/NotesServer/serveralgotythms.cpp"

class ServerTestCase : public QObject
{
    Q_OBJECT

public:
    ServerTestCase();
    ~ServerTestCase();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_is_name_valid_len_grater_then_2();
    void test_is_name_valid_len_less_then_21();
    void test_is_name_valid_req_expr_check();
};

ServerTestCase::ServerTestCase() {}

ServerTestCase::~ServerTestCase() {}

void ServerTestCase::initTestCase() {}

void ServerTestCase::cleanupTestCase() {}

void ServerTestCase::test_is_name_valid_len_grater_then_2() {
    QString str1 = "Anna";
    QString str2 = "Ann";
    QString str3 = "An";

    bool is_valid1 = ServerAlgotythms::isNameValid(str1);
    bool is_valid2 = ServerAlgotythms::isNameValid(str2);
    bool is_valid3 = ServerAlgotythms::isNameValid(str3);

    QCOMPARE_EQ(true, is_valid1);
    QCOMPARE_EQ(true, is_valid2);
    QCOMPARE_EQ(false, is_valid3);
}

void ServerTestCase::test_is_name_valid_len_less_then_21() {
    QString str1 = "AnnaAnnaAnnaAnnaAnn";
    QString str2 = "AnnaAnnaAnnaAnnaAnna";
    QString str3 = "AnnaAnnaAnnaAnnaAnnaA";

    bool is_valid1 = ServerAlgotythms::isNameValid(str1);
    bool is_valid2 = ServerAlgotythms::isNameValid(str2);
    bool is_valid3 = ServerAlgotythms::isNameValid(str3);

    QCOMPARE_EQ(true, is_valid1);
    QCOMPARE_EQ(true, is_valid2);
    QCOMPARE_EQ(false, is_valid3);
}

void ServerTestCase::test_is_name_valid_req_expr_check() {
    QString str1 = "Aa90xJ_";
    QString str2 = "_90_";
    QString str3 = "_90*_";
    QString str4 = "Anna)*_";

    bool is_valid1 = ServerAlgotythms::isNameValid(str1);
    bool is_valid2 = ServerAlgotythms::isNameValid(str2);
    bool is_valid3 = ServerAlgotythms::isNameValid(str3);
    bool is_valid4 = ServerAlgotythms::isNameValid(str4);

    QCOMPARE_EQ(true, is_valid1);
    QCOMPARE_EQ(true, is_valid2);
    QCOMPARE_EQ(false, is_valid3);
    QCOMPARE_EQ(false, is_valid4);
}

QTEST_MAIN(ServerTestCase)

#include "tst_servertestcase.moc"
