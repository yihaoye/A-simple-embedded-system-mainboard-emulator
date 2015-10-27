#include"block_area.h"
#include<algorithm>
#include<QMessageBox>
#include<QWidget>
#include<QGridLayout>
#include <QLabel>
#include "button_area.h"
//#include "lcd.h"


BlockArea::BlockArea(QWidget* parent)
    :QWidget(parent)
{

    column_=10;


    for (int j = 0; j <= NumNewBlock; j++)
    {
        NewBlock[j] = new Block;
    }


    mainLayout=new QGridLayout(this);
        for(int j=0;j<column_;j++)
        {//
            mainLayout->addWidget(NewBlock[j],0,j);//0 change to i
            //mainLayout->addWidget(new Block,0,j);//0 change to i 可行 6.30

        }//

    setFixedSize(sizeHint());
}





