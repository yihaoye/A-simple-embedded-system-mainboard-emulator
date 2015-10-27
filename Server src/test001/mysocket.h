#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QWidget>
#include <QMainWindow>
#include <QtNetwork>

class MySocket : public QWidget
{
    Q_OBJECT
public:
    explicit MySocket(QWidget *parent = 0);

    QHostAddress *hostaddr1;
    QHostAddress *hostaddr2;

    int ReceiveStatement;

private:

    QUdpSocket *udpSocket1;
    QUdpSocket *udpSocket2;

private slots:
    //void send();
    void receive();

};

#endif // MYSOCKET_H
