#ifndef BLOCK_AREA_H
#define BLOCK_AREA_H


#include"block.h"
#include<QWidget>
//#include"lcd.h"
class QGridLayout;

QT_END_NAMESPACE
//class Button;

class BlockArea:public QWidget
{
    Q_OBJECT
public:
    BlockArea(QWidget* parent=0);


    enum { NumNewBlock = 10 };
    Block *NewBlock[NumNewBlock];

//private slots:
//    void ButtonPressed();
//    Block *createBlock();


private:
    QGridLayout* mainLayout;
//    int row_;
    int column_;


};


#endif // BLOCK_AREA_H
