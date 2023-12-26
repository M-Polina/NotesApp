#ifndef TEST_MAINWINDOW_H
#define TEST_MAINWINDOW_H

#define private public

#include <QCoreApplication>
#include <QObject>
#include "mainwindow.h"


class Test_MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit Test_MainWindow(QObject *parent = nullptr);

private slots:
    void test_display_error_message();

    void test_add_note_widget();

    void test_clear_notes_area();

    void test_process_text_message();

    void test_on_disconnected();
};

#endif // TEST_MAINWINDOW_H
