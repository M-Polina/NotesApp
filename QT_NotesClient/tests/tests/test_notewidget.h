#ifndef TEST_NOTEWIDGET_H
#define TEST_NOTEWIDGET_H

#define private public

#include <QCoreApplication>
#include <QObject>
#include "notewidget.h"

class Test_NoteWidget : public QObject
{
    Q_OBJECT
public:
    explicit Test_NoteWidget(QObject *parent = nullptr);

private slots:
    void test_set_info();
};

#endif // TEST_NOTEWIDGET_H
