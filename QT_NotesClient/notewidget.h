#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QDate>


class NoteWidget : public QWidget
{
    // Q_OBJECT


public:
    NoteWidget(QWidget *parent = nullptr);
    void SetInfo(QString creationTime, QString header, QString str);

private:
    QLabel *timeLabel;
    QFrame *noteFrame;
    QLabel *noteHeader;
    QLabel *noteText;
};


#endif // NOTEWIDGET_H
