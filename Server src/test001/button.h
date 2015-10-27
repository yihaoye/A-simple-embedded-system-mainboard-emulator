#ifndef BUTTON_H
#define BUTTON_H

#include<QLabel>
class QWidget;
class QMouseEvent;

//! [0]
class Button : public QLabel
{
    Q_OBJECT

public:
    explicit Button(QWidget *parent = 0);

    //QSize sizeHint() const;

    int Pressed;

//protected:
    void mousePressEvent(QMouseEvent *event);



//private:


};
//! [0]


#endif // BUTTON_H
