#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile styleFile(":/style.qss");
    if(styleFile.open(QFile::ReadOnly)) {
        QString StyleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(StyleSheet);
    }

    ui->messagesScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->messagesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ui->messagesScrollArea->sizeHint();
    // ui->messagesScrollArea->
    // ui->messagesScrollArea->setHorizontalScrollBarPolicy(); //Horizontal.setVerticalStretch(0);
    // ui->messagesScrollArea->

    this->messageWidget = new QWidget();
    this->vbox = new QVBoxLayout();

    QLabel* textLabel = new QLabel();
    textLabel->setText("Initial note");
    textLabel->setWordWrap(true);
    // textLabel->maximumHeight(textLabel->text());
    this->vbox->addWidget(textLabel);
    this->vbox->setSizeConstraint(QLayout::SetFixedSize);


    this->messageWidget->setLayout(vbox);

    ui->messagesScrollArea->setWidget(messageWidget);

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    qDebug() << "trying to connect";
    // socket->setProxy(QNetworkProxy::NoProxy);
    socket->connectToHost("127.0.0.1", 8080);
    if (socket->waitForConnected(5000)) {
        qDebug() << "Connected";
    } else {
        qDebug() << "Not connected";
        qDebug() << socket->errorString();
    }
}

void MainWindow::SendToServer(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);
    out << str;
    socket->write(Data);
    ui->lineEdit->clear();
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Version::Qt_6_6);
    if(in.status() == QDataStream::Ok)
    {
        QString str;
        in >> str;
        AddTextLabel("Got: " + str);
        qDebug() << "read: " << str;
    }
    else
    {
        qDebug() << "read error";
    }
}

void MainWindow::AddTextLabel(QString str){
    QLabel* textLabel = new QLabel();
    textLabel->setText(str);
    textLabel->setWordWrap(true);
    this->vbox->addWidget(textLabel);
}


void MainWindow::on_sendButton_clicked()
{
    qDebug() << "sending... " << (ui->lineEdit->text());
    AddTextLabel(ui->lineEdit->text());
    SendToServer(ui->lineEdit->text()+"\r");
}


void MainWindow::on_lineEdit_returnPressed()
{
    qDebug() << "sending... " << (ui->lineEdit->text());
    AddTextLabel(ui->lineEdit->text());
    SendToServer(ui->lineEdit->text()+"\r");
}


