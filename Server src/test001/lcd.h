#ifndef LCD_H
#define LCD_H

#include <QMainWindow>
#include <QDialog>
#include <QPainter>
#include <QKeyEvent>
#include <QString>
#include <QFont>
#include <QRect>
#include <QTimer>

#include"block.h"
#include"button.h"
#include <QWidget>
#include <QtNetwork>

class QGridLayout;
class Button;


class lcd : public QWidget
{
    Q_OBJECT

public:
    lcd(QWidget *parent = 0);
    QRect createRect(int x,int y);//create a rect

    //block_area & button_area
    enum { NumNewBlock = 8 };
    enum { NumLEDButtons = 8 };
    Block *NewBlock[NumNewBlock];
    Button *LEDButtons[NumLEDButtons];

    int IsButtonPressed(int j);
    void SetLEDcolor(int i, int Color);
    void SetAllLEDs(int Color);
    char GetLEDcolor(int i);
    void Reset();

    void SetOLEDPixelColour(unsigned short x, unsigned short y, unsigned short RGBred, unsigned short RGBgreen, unsigned short RGBblue);
    void DrawOLEDVerticalLine(unsigned short x, unsigned short y, unsigned short *pixels, short count);
    void DrawOLEDHorizontalLine(unsigned short x, unsigned short y, unsigned short *pixels, short count);

    //socket
    QHostAddress *hostaddr1;
    QHostAddress *hostaddr2;


protected:
    void paintEvent(QPaintEvent *);

private:
    QRect temp_Rect;//rect
    unsigned short Rect_Color;
    unsigned short pixelarrayRED[160][128];
    unsigned short pixelarrayGREEN[160][128];
    unsigned short pixelarrayBLUE[160][128];

    QString str;
    QTimer *timer;  //timer
    QString display;//

    //block_area & button_area
    QGridLayout* mainLayout;
    int column_;

    //socket
    QUdpSocket *udpSocket1;
    QUdpSocket *udpSocket2;

private slots:
    //socket
    void send(QString i);
    void receive();
};

#endif // LCD_H
