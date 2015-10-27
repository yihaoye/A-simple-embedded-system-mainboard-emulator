#include <QtWidgets>

#include "button.h"


Button::Button(QWidget *parent)
    : QLabel(parent)
{
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    Pressed = 0;
    setPixmap(QPixmap(":/images/buttonnormal.png"));
}

void Button::mousePressEvent(QMouseEvent *event)
{
        if (event->button() == Qt::RightButton)
        {
            Pressed = 0;
            setPixmap(QPixmap(":/images/buttonnormal.png"));
            update();
        }

        if (event->button() == Qt::LeftButton)
        {
            Pressed = 1;
            setPixmap(QPixmap(":/images/buttonpressed.png"));
            update();
        }
}



