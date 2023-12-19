#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkProxy>
#include <QTcpSocket>
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include<QTextEdit>

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

private slots:

    void on_lineEdit_returnPressed();

    void on_sendButton_clicked();

    void on_connectButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray Data;
    QWidget* messageWidget;
    QVBoxLayout* vbox;
    void SendToServer(QString str);
    void AddTextLabel(QString str);

public slots:
    void slotReadyRead();
};
#endif // MAINWINDOW_H
