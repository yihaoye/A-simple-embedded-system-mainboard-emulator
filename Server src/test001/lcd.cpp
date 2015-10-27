#include "lcd.h"
#include "ui_lcd.h"
#include "block.h"
#include "button.h"

#include<algorithm>
#include<QMessageBox>
#include<QWidget>
#include<QGridLayout>
#include<QLabel>
#include<QPushButton>
#include<QToolButton>

#define off 0
#define green 1
#define red 2
#define orange 3

#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3
#define LED5 4
#define LED6 5
#define LED7 6
#define LED8 7

#define Button1 0
#define Button2 1
#define Button3 2
#define Button4 3
#define Button5 4
#define Button6 5
#define Button7 6
#define Button8 7


lcd::lcd(QWidget *parent)
    : QWidget(parent)
{
    //
    resize(850, 660);
    //
    column_=8;
    memset(pixelarrayRED,0,sizeof(pixelarrayRED));
    memset(pixelarrayGREEN,0,sizeof(pixelarrayGREEN));
    memset(pixelarrayBLUE,0,sizeof(pixelarrayBLUE));


    //create LEDs
    for (int j = 0; j <= NumNewBlock; j++)
    {
        NewBlock[j] = new Block;
    }

    //?
    QSpacerItem* vSpacer1 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    //

    mainLayout=new QGridLayout(this);

    mainLayout->addItem(vSpacer1,0,0);//?

        for(int j=0;j<column_;j++)
        {//
            mainLayout->addWidget(NewBlock[j],1,j);//
        }//


    //create buttons
    for (int i = 0; i <= NumLEDButtons; i++) {
        LEDButtons[i] = new Button;//user
    }

    for(int j=0;j<column_;j++)
    {//
        mainLayout->addWidget(LEDButtons[j], 2, j);//user
    }//


    //reset button
    QPushButton *ResetButton = new QPushButton(tr("Reset"),this);
    connect(ResetButton, &QPushButton::clicked, this, &lcd::Reset);

    ResetButton->setGeometry(750,100,60,40);


    /*************************socket network*********************************/

    udpSocket1 = new QUdpSocket(this);
    udpSocket2 = new QUdpSocket(this);

    hostaddr1 = new QHostAddress("127.0.0.1");
    hostaddr2 = new QHostAddress("127.0.0.1");
    bool  conn=udpSocket1->bind(*hostaddr1,6665,QUdpSocket::ShareAddress);//listen to the port 6665
    if(!conn)
    {
    }
    else
    {
        connect(udpSocket1,SIGNAL(readyRead()),this,SLOT(receive()));
    }
}

void lcd::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //draw the OLED,640*512(160*128 pixel)
    painter.setPen(Qt::black);
    painter.setBrush(Qt::darkGreen);
    painter.drawRect(15,15,650,522);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawRect(20,20,640,512);
    painter.setPen(Qt::gray);
    for(int ii = 5;ii <= 165;ii++)
    {
        painter.drawLine(ii*4,20,ii*4,532);//y direction
    }
    for(int ii = 5;ii <= 133;ii++)
    {
        painter.drawLine(20,ii*4,660,ii*4);//x direction
    }

    //LCD functions
    //pixelarray[i][j] = black or ...;
    for(int i=0;i<160;i++)
    {
        for(int j=0;j<128;j++)
        {
            painter.setBrush(QColor(pixelarrayRED[i][j],pixelarrayGREEN[i][j],pixelarrayBLUE[i][j],255));
            painter.setPen(Qt::gray);//user

            temp_Rect = createRect(i,j);
            painter.drawRect(temp_Rect);
            //painter.setBrush(QColor(255,0,0,255));//for test:QColor(red,green,blue,deep)
        }
    }
//    update();

}

QRect lcd::createRect(int x, int y)//create a rect
{
    QRect rect(20+x*4,20+y*4,4,4);//former two decide position，following two decide size
    return rect;
}


/*****************************Libray list*****************************************/


void lcd::SetOLEDPixelColour(unsigned short x, unsigned short y, unsigned short RGBred, unsigned short RGBgreen, unsigned short RGBblue)
{
    pixelarrayRED[x][y] = RGBred;
    pixelarrayGREEN[x][y] = RGBgreen;
    pixelarrayBLUE[x][y] = RGBblue;
}


void lcd::SetLEDcolor(int i, int Color)
{
        NewBlock[i]->delight(Color);
}

void lcd::SetAllLEDs(int Color)
{
        for(int i=0;i<NumNewBlock;i++)//delight all the leds
        {
            NewBlock[i]->delight(Color);
        }
}

char lcd::GetLEDcolor(int i)
{
    return NewBlock[i]->color_;
}

int lcd::IsButtonPressed(int j)
{
        if(LEDButtons[j]->Pressed == 1)
        {
            send("true");
        }
        else
        {
            send("false");
        }

    return LEDButtons[j]->Pressed;
}


void lcd::Reset()
{
    for(int i=0;i<NumNewBlock;i++)//delight all the leds
    {
        NewBlock[i]->delight(off);
    }
    for(int i=0;i<160;i++)
    {
        for(int j=0;j<128;j++)
        {
            pixelarrayRED[i][j] = 0;
            pixelarrayGREEN[i][j] = 0;
            pixelarrayBLUE[i][j] = 0;
        }
    }

    update();
    //QMessageBox::information(this,tr("Result"),tr("Turn on"));
}


/********************************Network*******************************************/


void lcd::send(QString text)
{
    udpSocket2->writeDatagram(text.toUtf8(),text.length(),*hostaddr2,6666);//send data to port 6666 of computer which IP is 127.0.0.1
}


void lcd::receive()
{
    while(udpSocket1->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(udpSocket1->pendingDatagramSize());
        udpSocket1->readDatagram(data.data(),data.size());
        str = data.data();

        QStringList strList;
        int LEDNum;
        int colour;
        int ButtonNum;
        strList = str.split(" ");

        //if receive led functions
        if(strList[0] == "SetLEDcolor")
        {

            if(strList[2] == "off")
                colour = 0;
            else if(strList[2] == "green")
                colour = 1;
            else if(strList[2] == "red")
                colour = 2;
            else if(strList[2] == "orange")
                colour = 3;
            else
                colour = 4;

            if(strList[1] == "0")
                LEDNum = 0;
            else if(strList[1] == "1")
                LEDNum = 1;
            else if(strList[1] == "2")
                LEDNum = 2;
            else if(strList[1] == "3")
                LEDNum = 3;
            else if(strList[1] == "4")
                LEDNum = 4;
            else if(strList[1] == "5")
                LEDNum = 5;
            else if(strList[1] == "6")
                LEDNum = 6;
            else if(strList[1] == "7")
                LEDNum = 7;
            else
                LEDNum = 8;

            if(LEDNum != 8 && colour != 4)
            {
                SetLEDcolor(LEDNum, colour);
                break;
            }
            else
            {
                send("SetLEDcolor function error");
            }
        }

        //if receive button functions
        if(strList[0] == "IsButtonPressed")
        {
            if(strList[1] == "Button1")
                ButtonNum = 0;
            else if(strList[1] == "Button2")
                ButtonNum = 1;
            else if(strList[1] == "Button3")
                ButtonNum = 2;
            else if(strList[1] == "Button4")
                ButtonNum = 3;
            else if(strList[1] == "Button5")
                ButtonNum = 4;
            else if(strList[1] == "Button6")
                ButtonNum = 5;
            else if(strList[1] == "Button7")
                ButtonNum = 6;
            else if(strList[1] == "Button8")
                ButtonNum = 7;
            else
                ButtonNum = 8;

            if(ButtonNum != 8)
            {
                IsButtonPressed(ButtonNum);
                break;
            }
            else
            {
                send("IsButtonPressed function error");
            }
        }


        //if receive OLED pixel set functions
        if(strList[0] == "SetOLEDPixelColour")
        {
            int pixel_x = strList[1].toInt();
            int pixel_y = strList[2].toInt();
            int DecimalRed = strList[3].toInt();
            int DecimalGreen = strList[4].toInt();
            int DecimalBlue = strList[5].toInt();

            int RGB888red, RGB888green, RGB888blue;

            RGB888red = (DecimalRed + 1)*256/32 - 1;
            RGB888green = (DecimalGreen + 1)*256/64 - 1;
            RGB888blue = (DecimalBlue + 1)*256/32 - 1;

            SetOLEDPixelColour(pixel_x,pixel_y,RGB888red,RGB888green,RGB888blue);
            update();
            break;
        }

    }
}

