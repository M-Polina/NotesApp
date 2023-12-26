#include <QTest>
#include "test_mainwindow.h"

Test_MainWindow::Test_MainWindow(QObject *parent) :
    QObject(parent)
{
}

void Test_MainWindow::test_display_error_message()
{
    MainWindow main_window;
    QLabel label;

    QString error_message_1 = "Error message!";
    QString error_message_2 = "";
    QString error_message_3 = "E";


    main_window.display_error_message(&label, error_message_1);
    QCOMPARE(label.text(), error_message_1);

    main_window.display_error_message(&label, error_message_2);
    QCOMPARE(label.text(), error_message_2);

    main_window.display_error_message(&label, error_message_3);
    QCOMPARE(label.text(), error_message_3);
}

void Test_MainWindow::test_add_note_widget()
{
    MainWindow main_window;

    QVBoxLayout vbox;

    QCOMPARE_EQ(main_window.noteWidgets.size(), 0);

     QString creationTime_1 = "time 1";
     QString header_1 = "header 1";
     QString str_1 = "content 1";

     main_window.addNoteWidget(&vbox, creationTime_1, header_1, str_1);
     QCOMPARE_EQ(main_window.noteWidgets.size(), 1);

     QString creationTime_2 = "time 2";
     QString header_2 = "header 2";
     QString str_2 = "content 2";

     main_window.addNoteWidget(&vbox, creationTime_2, header_2, str_2);
     QCOMPARE_EQ(main_window.noteWidgets.size(), 2);
}

void Test_MainWindow::test_clear_notes_area() {
    MainWindow main_window;

    QVBoxLayout vbox;

    QCOMPARE_EQ(main_window.noteWidgets.size(), 0);

    QString creationTime_1 = "time 1";
    QString header_1 = "header 1";
    QString str_1 = "content 1";

    QString creationTime_2 = "time 2";
    QString header_2 = "header 2";
    QString str_2 = "content 2";

    main_window.addNoteWidget(&vbox, creationTime_1, header_1, str_1);
    main_window.addNoteWidget(&vbox, creationTime_2, header_2, str_2);
    QCOMPARE_EQ(main_window.noteWidgets.size(), 2);

    main_window.clearNotesArea();
    QCOMPARE_EQ(main_window.noteWidgets.size(), 0);
}

void Test_MainWindow::test_process_text_message() {
    MainWindow main_window;

    QString not_json_str = "just a string";
    QString error_json_srt = "{\"type\":\"error\",\"errorText\":\"Error string\"}";
    QString note_json_str_1 = "{\"notes\":[],\"type\":\"notesList\"}";
    QString note_json_str_2 = "{\"notes\":[{\"content\":\"hi\",\"creationTime\":\"Tue Dec 26 2023 10:50:31\",\"header\":\"New note\",\"type\":\"note\"}],\"type\":\"notesList\"}";

    QVERIFY_THROWS_NO_EXCEPTION(main_window.processTextMessage(not_json_str));

    main_window.processTextMessage(error_json_srt);
    QCOMPARE(main_window.errorLabel->text(), QString("Error string"));

    main_window.processTextMessage(note_json_str_1);
    QCOMPARE_EQ(main_window.noteWidgets.size(), 0);

    main_window.processTextMessage(note_json_str_2);
    QCOMPARE_EQ(main_window.noteWidgets.size(), 1);
}

void Test_MainWindow::test_on_disconnected() {
    MainWindow main_window;

    main_window.onDisconnected();

    QCOMPARE(main_window.errorLabel->text(), QString("Connection error"));
}














