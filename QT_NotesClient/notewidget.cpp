#include "notewidget.h"


NoteWidget::
    NoteWidget(QWidget *parent) :
    QWidget(parent)
{
    timeLabel = new QLabel(this);
    noteFrame = new QFrame(this);

    timeLabel->setObjectName("timeLabel");
    timeLabel->setWordWrap(false);
    noteFrame->setObjectName("noteFrame");

    noteHeader = new QLabel(noteFrame);
    noteText = new QLabel(noteFrame);

    noteHeader->setObjectName("noteHeader");
    noteText->setObjectName("noteText");
    noteHeader->setWordWrap(true);
    noteText->setWordWrap(true);
    noteHeader->setTextInteractionFlags(Qt::TextSelectableByMouse);
    noteText->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setAlignment(Qt::AlignLeft);
    vbox->setObjectName("noteVLayout");

    QVBoxLayout *frame_ayout = new QVBoxLayout(noteFrame);
    frame_ayout->setAlignment(Qt::AlignLeft);
    frame_ayout->setSizeConstraint(QLayout::SetFixedSize);

    frame_ayout->addWidget(noteHeader);
    frame_ayout->addWidget(noteText);
    frame_ayout->setObjectName("noteVLayout");

    vbox->addWidget(timeLabel);
    vbox->addWidget(noteFrame);

}

void NoteWidget::setInfo(QString creationTime, QString header, QString str) {
    timeLabel->setText(creationTime);
    noteHeader->setText(header);
    noteText->setText(str);
}

