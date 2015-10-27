
#include<algorithm>
#include<QMessageBox>
#include<QWidget>
#include<QGridLayout>
#include <QLabel>
#include "button_area.h"


ButtonArea::ButtonArea(QWidget* parent)
    :QWidget(parent)
{

    column_=10;

    for (int i = 0; i <= NumLEDButtons; i++) {
        LEDButtons[i] = createButton(tr("O"), SLOT(ButtonPressed()));//user
    }
    //QLabel *label = new QLabel;//user

    //std::random_shuffle(mine_flag,mine_flag+total_block_number_);

    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);//???

    mainLayout=new QGridLayout(this);
    for(int j=0;j<column_;j++)
    {//
        mainLayout->addWidget(LEDButtons[j], 0, j);//user    0 cange to i
    }//

    setFixedSize(sizeHint());
}



void ButtonArea::ButtonPressed()
{
    //QMessageBox::information(this,tr("Result"),tr("Turn on"));
    //event->button()==Qt::LeftButton;
}


Button *ButtonArea::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}



