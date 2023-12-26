#include "mainwindow.h"

#include <QTest>
#include <QApplication>
#include "tests/tests/test_mainwindow.h"
#include "tests/tests/test_notewidget.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTest::qExec(new Test_MainWindow, argc, argv);
    QTest::qExec(new Test_NoteWidget, argc, argv);

    return a.exec();
}
