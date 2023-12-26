#include <QTest>
#include "test_notewidget.h"


Test_NoteWidget::Test_NoteWidget(QObject *parent) :
    QObject(parent)
{
}

void Test_NoteWidget::test_set_info() {
    NoteWidget note_widget;

    QString creationTime_1 = "time 1";
    QString header_1 = "header 1";
    QString str_1 = "content 1";
    QString creationTime_2 = "time 2";
    QString header_2 = "header 2";
    QString str_2 = "content 2";

    note_widget.setInfo(creationTime_1, header_1, str_1);

    QCOMPARE(note_widget.timeLabel->text(), creationTime_1);
    QCOMPARE(note_widget.noteHeader->text(), header_1);
    QCOMPARE(note_widget.noteText->text(), str_1);

    note_widget.setInfo(creationTime_2, header_2, str_2);

    QCOMPARE(note_widget.timeLabel->text(), creationTime_2);
    QCOMPARE(note_widget.noteHeader->text(), header_2);
    QCOMPARE(note_widget.noteText->text(), str_2);
}
