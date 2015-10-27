#include <QCoreApplication>
#include <QtNetwork>

#define off "off"
#define green "green"
#define red "red"
#define orange "orange"

#define LED1 0//"LED1"
#define LED2 1//"LED2"
#define LED3 2//"LED3"
#define LED4 3//"LED4"
#define LED5 4//"LED5"
#define LED6 5//"LED6"
#define LED7 6//"LED7"
#define LED8 7//"LED8"

#define Button1 "Button1"
#define Button2 "Button2"
#define Button3 "Button3"
#define Button4 "Button4"
#define Button5 "Button5"
#define Button6 "Button6"
#define Button7 "Button7"
#define Button8 "Button8"

QHostAddress *hostaddr1;
QHostAddress *hostaddr2;

QUdpSocket *udpSocket1;
QUdpSocket *udpSocket2;
QUdpSocket *udpSocket3;

QString text;
QString str;

typedef int LEDnumber;
typedef QString LEDcolour;

void receive();
void SetLEDcolor(int LEDpos_, QString color);
void SetAllLEDs(QString ColourVector[8]);
void DrawOLEDHorizontalLine(int x, int y, int *pixels, int count);
void DrawOLEDVerticalLine(int x, int y, int *pixels, int count);
int OLEDPixelFromRGB(int RED, int GREEN, int BLUE);
void SetOLEDPixelColour(int x,int y,int pixel);
void GetButtonState(bool List[8]);
int IsButtonPressed(QString ButtonNum);
int IsButtonReleased(QString ButtonNum);
void delay_ms(int ms);

int pause;
int contect;
bool conn;

int main(int argc, char *argv[])
{
    hostaddr1 = new QHostAddress("127.0.0.1");
    hostaddr2 = new QHostAddress("127.0.0.1");
    udpSocket1 = new QUdpSocket(0);
    udpSocket2 = new QUdpSocket(0);
    udpSocket3 = new QUdpSocket(0);
    conn=udpSocket1->bind(*hostaddr1,6666,QUdpSocket::ShareAddress);//listen to the local 6666 port


    QCoreApplication a(argc, argv);

    while(1)//?
    {
        str = "";
        text = "";

    /****************************User Code******************************/

    int a[160];
    for(int i=0;i<160;i++)
    {
        a[i] = 0xFFE0;
    }
    //memset(a,0xFFFF,sizeof(a));/?

    DrawOLEDVerticalLine(29,54,a,13);
    DrawOLEDVerticalLine(39,54,a,13);
    DrawOLEDVerticalLine(44,54,a,13);
    DrawOLEDVerticalLine(59,54,a,13);
    DrawOLEDVerticalLine(74,54,a,13);
    DrawOLEDVerticalLine(89,54,a,13);
    DrawOLEDVerticalLine(99,54,a,13);

    DrawOLEDHorizontalLine(30, 60, a, 9);
    DrawOLEDHorizontalLine(45, 66, a, 10);
    DrawOLEDHorizontalLine(45, 60, a, 10);
    DrawOLEDHorizontalLine(45, 54, a, 10);
    DrawOLEDHorizontalLine(60, 66, a, 10);
    DrawOLEDHorizontalLine(75, 66, a, 10);
    DrawOLEDHorizontalLine(90, 54, a, 9);
    DrawOLEDHorizontalLine(90, 66, a, 9);


    while(IsButtonPressed(Button7))
    {
        SetLEDcolor(LED6, green);
        delay_ms(1000);
        SetLEDcolor(LED6, off);
        delay_ms(1000);
    }
    //SetOLEDPixelColour(10,25,0xF800);
    //qDebug("one loop");




    /****************************User Code******************************/

    }
    return a.exec();
}




/***************************Functions**********************************/

//delay function
void delay_ms(int ms)
{
    QTime t;
    t.start();
    while(t.elapsed()<ms);
//    while(t.elapsed()<ms)
//        QCoreApplication::processEvents();
}

//OLED functions
void SetOLEDPixelColour(int x,int y,int pixel)
{
    int HexRed = (pixel & 0xF800) >>11;
    int HexGreen = (pixel & 0x07E0) >>5;
    int HexBlue = (pixel & 0x001F);

    QString x_, y_, DecimalRED, DecimalGREEN, DecimalBLUE;
    x_ = QString::number(x);
    y_ = QString::number(y);
    DecimalRED = QString::number(HexRed);
    DecimalGREEN = QString::number(HexGreen);
    DecimalBLUE = QString::number(HexBlue);

    text = "SetOLEDPixelColour";
    text = text + " " + x_ +" " + y_ + " " + DecimalRED + " " + DecimalGREEN + " " + DecimalBLUE;
    qDebug("send:"+text.toLatin1());
    udpSocket3->writeDatagram(text.toUtf8(),text.length(),*hostaddr2,6665);//send data to 6665 port of 127.0.0.1(IP) computer
}

void DrawOLEDHorizontalLine(int x, int y, int *pixels, int count)
{
    for(int i=0;i<count;i++)
    {
        SetOLEDPixelColour(x+i,y,*(pixels+i));
    }
}

void DrawOLEDVerticalLine(int x, int y, int *pixels, int count)
{
    for(int i=0;i<count;i++)
    {
        SetOLEDPixelColour(x,y+i,*(pixels+i));
    }
}

int OLEDPixelFromRGB(int RED, int GREEN, int BLUE)//?
{
    RED = RED <<11;
    GREEN = GREEN <<5;
    int PixelValue = RED | GREEN | BLUE;
    return PixelValue;
}

//LED functions
void SetLEDcolor(int LEDpos_, QString color)
{
    QString LEDpos__;
    LEDpos__ = QString::number(LEDpos_);

    text = "SetLEDcolor";
    text = text + " " + LEDpos__ +" " + color;
    qDebug("send:"+text.toLatin1());
    udpSocket3->writeDatagram(text.toUtf8(),text.length(),*hostaddr2,6665);//
}

void SetAllLEDs(QString ColourVector[8])
{
    for(int i=0;i<8;i++)
    {
        SetLEDcolor(i, ColourVector[i]);
    }
}

//Button functions
void GetButtonState(bool List[8])//?
{
    for(int i=0;i<8;i++)
    {
        text = "IsButtonPressed";
        text = text + " " + QString::number(i);
        qDebug("send:"+text.toLatin1());
        udpSocket2->writeDatagram(text.toUtf8(),text.length(),*hostaddr2,6665);//

        if(!conn)
        {
            qDebug("warn:error in bind");
        }
        else
        {
            while (udpSocket1->waitForReadyRead(1))
            {
                qDebug("successfully bind");
                receive();
                contect = 1;
            }
            if(contect != 1)
                qDebug("no connection with server");
            contect = 0;


            if(str == "true")//here is the problem!!!
            {
                List[i] = true;
                qDebug("true");//here is problem?
            }
            else if(str == "false")//here is the problem!!!
            {
                List[i] = false;
                qDebug("false");//here is problem?
            }
            else
            {
                qDebug("bug");//here is problem?
            }
        }
    }
}

int IsButtonPressed(QString ButtonNum)
{
    text = "IsButtonPressed";
    text = text + " " + ButtonNum;
    qDebug("send:"+text.toLatin1());
    udpSocket2->writeDatagram(text.toUtf8(),text.length(),*hostaddr2,6665);//


    if(!conn)
    {
        qDebug("warn:error in bind");
    }
    else
    {
        while (udpSocket1->waitForReadyRead(1))
        {
            qDebug("successfully bind");
            receive();
            contect = 1;
        }
        if(contect != 1)
            qDebug("no connection with server");
        contect = 0;


        if(str == "true")//here is the problem!!!
        {
            return 1;
            qDebug("true");//here is problem?
        }
        else if(str == "false")//here is the problem!!!
        {
            return 0;
            qDebug("false");//here is problem?
        }
        else
        {
            return 0;
            qDebug("bug");//here is problem?
        }
    }

}


int IsButtonReleased(QString ButtonNum)
{
    text = "IsButtonPressed";
    text = text + " " + ButtonNum;
    qDebug("send:"+text.toLatin1());
    udpSocket2->writeDatagram(text.toUtf8(),text.length(),*hostaddr2,6665);//


    if(!conn)
    {
        qDebug("warn:error in bind");
    }
    else
    {
        while (udpSocket1->waitForReadyRead(1))
        {
            qDebug("successfully bind");
            receive();
            contect = 1;
        }
        if(contect != 1)
            qDebug("no connection with server");
        contect = 0;


        if(str == "true")//here is the problem!!!
        {
            return 0;
            qDebug("true");//here is problem?
        }
        else if(str == "false")//here is the problem!!!
        {
            return 1;
            qDebug("false");//here is problem?
        }
        else
        {
            return 0;
            qDebug("bug");//here is problem?
        }
    }

}

/******************************Network***********************************/
void receive()
{
    while(udpSocket1->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(udpSocket1->pendingDatagramSize());
        udpSocket1->readDatagram(data.data(),data.size());
        str = data.data();
        qDebug("receive:"+str.toLatin1());
    }
}
