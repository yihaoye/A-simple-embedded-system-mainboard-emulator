#include "mysocket.h"
#include <QMessageBox>

MySocket::MySocket(QWidget *parent) :
    QWidget(parent)
{
    ReceiveStatement = 0;

    udpSocket1 = new QUdpSocket(this);
    udpSocket2 = new QUdpSocket(this);

    hostaddr1 = new QHostAddress("127.0.0.1");
    hostaddr2 = new QHostAddress("127.0.0.1");
    bool  conn=udpSocket1->bind(*hostaddr1,6665,QUdpSocket::ShareAddress);//监听本机上的6665端口，如果有消息到来，就会发送readyRead()信号。
    if(!conn)
    {
        QMessageBox box;
        box.setText(tr("连接错误"));
        box.exec();
    }
    else
    {
        connect(udpSocket1,SIGNAL(readyRead()),this,SLOT(receive()));
        //connect(ui->send,SIGNAL(clicked()),this,SLOT(send()));
    }

}



//void MySocket::send()
//{
//    QMessageBox box;
//    QString text=ui->textSend->toPlainText();
//    if(text.length()==0)
//    {
//        box.setText(tr("请输入发送内容"));
//        box.exec();
//    }
//    udpSocket2->writeDatagram(text.toUtf8(),text.length(),*hostaddr2,6666);//向IP为127.0.0.1的机器的6666端口发送数据
//}

void MySocket::receive()
{
    while(udpSocket1->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(udpSocket1->pendingDatagramSize());
        udpSocket1->readDatagram(data.data(),data.size());
        QString str = data.data();
        //ui->textReceive->insertPlainText(str+"\n");
    }
}
