#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSizePolicy>
#include <QDate>
#include <QPalette>
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile styleFile(":/style.qss");
    if(styleFile.open(QFile::ReadOnly)) {
        qDebug() << "style";
        QString StyleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(StyleSheet);
    }

    ui->messagesScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->messagesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->messagesScrollArea->setWidgetResizable(true);

    this->messageWidget = new QWidget();
    this->vbox = new QVBoxLayout();

    this->vbox->setSizeConstraint(QLayout::SetFixedSize);


    this->messageWidget->setLayout(vbox);

    ui->messagesScrollArea->setWidget(messageWidget);

    connect(&m_webSocket, &QWebSocket::connected, this, &MainWindow::onConnected);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &MainWindow::processTextMessage);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &MainWindow::onDisconnected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnected()
{
    foreach(NoteWidget * child, noteWidgets)
    {
        qDebug() << "del";
        this->vbox->removeWidget(child);
        delete child;
    }
    noteWidgets.clear();
    qDebug() << noteWidgets.length();

    QString username = ui->loginLineEdit->text();
    std::string username_json = JsonParser::createLoginJsonString(username.toStdString());
    QString username_json_string = QString::fromStdString(username_json);

    m_webSocket.sendTextMessage(username_json_string);
    qDebug() << "WebSocket connected";

    ui->loginLineEdit->setReadOnly(true);
    ui->loginLineEdit->setStyleSheet("background-color: lightgray; border: 0px; padding: 4px 4px 4px 4px; border-radius: 4px; font-size: 16px;");
    ui->connectButton->setVisible(false);
}

void MainWindow::onDisconnected()
{
    foreach(NoteWidget * child, noteWidgets)
    {
        qDebug() << "del";
        this->vbox->removeWidget(child);
        delete child;
    }
    noteWidgets.clear();
    qDebug() << noteWidgets.length();

    qDebug() << "WebSocket disconnected";

    ui->loginLineEdit->setReadOnly(false);
    ui->loginLineEdit->setStyleSheet(styleSheet());
    ui->connectButton->setVisible(true);

    m_webSocket.close();
}

void MainWindow::processTextMessage(QString message) {
    qDebug() << "text recived: " << message;

    json reply_json;
    try {
        reply_json = JsonParser::stringToJson(message.toStdString());
    } catch (std::exception ex) {
        qDebug() << "not json message recived!";
        return;
    }

    std::string request_type = reply_json.at("type");

    if (request_type == NOTES_TYPE) {
        std::vector<Note> got_notes = JsonParser::parseNotesJson(reply_json);
        for (auto note : got_notes) {
            AddTextLabel(QString::fromStdString(note.getCreationTime()),
                         QString::fromStdString(note.getHeader()),
                         QString::fromStdString(note.getContent()));
        }

    } else {
        qDebug() << "wrong request type";
        return;
    }
}

void MainWindow::on_connectButton_clicked()
{
    qDebug() << "trying to connect";
    using namespace Qt::Literals::StringLiterals;
    m_url.setScheme(u"ws"_s);
    m_url.setHost("127.0.0.1");
    m_url.setPort(8080);

    m_webSocket.open(QUrl(m_url));
}

void MainWindow::SendToServer(QString header, QString content, QString creationTime)
{
    std::vector<Note> notes;
    Note new_note(header.toStdString(), content.toStdString(), creationTime.toStdString());

    notes.push_back(new_note);

    std::string message = JsonParser::createNotesJsonString(notes);

    m_webSocket.sendTextMessage(QString::fromStdString(message));
    ui->plainTextEdit->clear();
}


void MainWindow::AddTextLabel(QString creationTime, QString header, QString str) {
    NoteWidget *note = new NoteWidget();
    note->SetInfo(creationTime, header, str);
    this->vbox->addWidget(note);
    noteWidgets.append(note);
}


void MainWindow::on_sendButton_clicked()
{
    qDebug() << "sending header... " << (ui->headerLineEdit->text());
    qDebug() << "sending... " << (ui->plainTextEdit->toPlainText());
    QString creationTime = QDate::currentDate().toString() + " " + QTime::currentTime().toString();

    AddTextLabel(creationTime, ui->headerLineEdit->text(), ui->plainTextEdit->toPlainText());
    SendToServer(ui->headerLineEdit->text(), ui->plainTextEdit->toPlainText(), creationTime);
}


