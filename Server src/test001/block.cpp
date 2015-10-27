#include"block.h"
#include<QLabel>
#include<QPixmap>
#include<QWidget>
#include<QMouseEvent>

Block::Block(QWidget* parent)
    :QLabel(parent)
{
    color_= 0;
    setPixmap(QPixmap(":/images/LEDoff1.png"));
}

void Block::delight(int Color)
{
    color_ = Color;

        if(color_==0)
        {
                setPixmap(QPixmap(":/images/LEDoff1.png"));
                update();
        }
        if(color_==1)
        {
                setPixmap(QPixmap(":/images/LEDgreen1.png"));
                update();
        }
        if(color_==2)
        {
                setPixmap(QPixmap(":/images/LEDred1.png"));
                update();
        }
        if(color_==3)
        {
                setPixmap(QPixmap(":/images/LEDorange1.png"));
                update();
        }
}



