#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkProxy>
#include <QTcpSocket>
#include <QSslSocket>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include<QTextEdit>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <notewidget.h>
#include "JsonParser.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private Q_SLOTS:
    void on_sendButton_clicked();
    void on_connectButton_clicked();
    void display_error_message(QString error_message);

    void onConnected();
    void onDisconnected();
    void processTextMessage(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;

    Ui::MainWindow *ui;
    QByteArray Data;
    QWidget* messageWidget;
    QVBoxLayout* vbox;
    QList<NoteWidget *> noteWidgets;

    void SendToServer(QString header, QString content, QString creationTime);
    void AddTextLabel(QString creationTime, QString header, QString str);
    void clearNotesArea();
};

#endif // MAINWINDOW_H
