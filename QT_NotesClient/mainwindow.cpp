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

    setUpUi();

    connect(&m_webSocket, &QWebSocket::connected, this, &MainWindow::onConnected);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &MainWindow::processTextMessage);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &MainWindow::onDisconnected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpUi() {
    setWindowTitle("Notes App");

    QFile styleFile(":/style.qss");
    if(styleFile.open(QFile::ReadOnly)) {
        QString StyleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(StyleSheet);
    }

    errorLabel = ui->errorLabel;
    ui->errorLabel->setVisible(false);

    ui->messagesScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->messagesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->messagesScrollArea->setWidgetResizable(true);

    this->messageWidget = new QWidget();
    this->vbox = new QVBoxLayout();

    this->vbox->setSizeConstraint(QLayout::SetFixedSize);
    this->vbox->setObjectName("notesVLayout");


    this->messageWidget->setLayout(this->vbox);

    ui->messagesScrollArea->setWidget(this->messageWidget);
}

void MainWindow::onConnected()
{
    clearNotesArea();

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
    clearNotesArea();

    qDebug() << "WebSocket disconnected";

    ui->loginLineEdit->setReadOnly(false);
    ui->loginLineEdit->setStyleSheet(styleSheet());
    ui->connectButton->setVisible(true);

    display_error_message(this->errorLabel, this->errorLabel->text() + '\n' + QString::fromStdString("Connection error"));

    m_webSocket.close();
}

void MainWindow::processTextMessage(QString message) {
    qDebug() << "Text recived: " << message;

    json reply_json;
    try {
        reply_json = JsonParser::stringToJson(message.toStdString());
    } catch (json::parse_error& ex) {
        qDebug() << "PJson parse error. Not a json message recived!";
        return;
    }

    std::string request_type = reply_json.at("type");

    if (request_type == NOTES_TYPE) {
        std::vector<Note> got_notes = JsonParser::parseNotesJson(reply_json);
        for (auto note : got_notes) {
            addNoteWidget(this->vbox, QString::fromStdString(note.getCreationTime()),
                         QString::fromStdString(note.getHeader()),
                         QString::fromStdString(note.getContent()));
        }
    } else if (request_type == ERROR_TYPE){
        std::string error_message = JsonParser::parseErrorJson(reply_json);
        display_error_message(ui->errorLabel, QString::fromStdString(error_message));
    } else {
        qDebug() << "Wrong request type";
        return;
    }
}

void MainWindow::on_connectButton_clicked()
{
    ui->errorLabel->clear();
    ui->errorLabel->setVisible(false);

    qDebug() << "Trying to connect...";

    using namespace Qt::Literals::StringLiterals;
    m_url.setScheme(u"ws"_s);
    m_url.setHost("127.0.0.1");
    m_url.setPort(8080);

    m_webSocket.open(QUrl(m_url));
}

void MainWindow::sendToServer(QString header, QString content, QString creationTime)
{
    std::vector<Note> notes;
    Note new_note(header.toStdString(), content.toStdString(), creationTime.toStdString());

    notes.push_back(new_note);

    std::string message = JsonParser::createNotesJsonString(notes);

    m_webSocket.sendTextMessage(QString::fromStdString(message));
    ui->plainTextEdit->clear();
}


void MainWindow::addNoteWidget(QVBoxLayout *vbox, QString creationTime, QString header, QString str) {
    NoteWidget *note = new NoteWidget();
    note->setInfo(creationTime, header, str);

    this->vbox->insertWidget(0, note);
    noteWidgets.append(note);
}


void MainWindow::on_sendButton_clicked()
{
    ui->errorLabel->clear();
    ui->errorLabel->setVisible(false);

    QString creationTime = QDate::currentDate().toString() + " " + QTime::currentTime().toString();

    addNoteWidget(this->vbox, creationTime, ui->headerLineEdit->text(), ui->plainTextEdit->toPlainText());
    sendToServer(ui->headerLineEdit->text(), ui->plainTextEdit->toPlainText(), creationTime);
}

void MainWindow::display_error_message(QLabel *label, QString error_message) {
    label->clear();
    label->setVisible(true);
    label->setText(error_message);
}

void MainWindow::clearNotesArea() {
    foreach(NoteWidget * child, noteWidgets)
    {
        this->vbox->removeWidget(child);
        delete child;
    }

    noteWidgets.clear();
}
