#ifndef BLOCK_H
#define BLOCK_H

#include<QLabel>
class QWidget;
class QMouseEvent;

class Block:public QLabel
{
    Q_OBJECT

public:
    explicit Block(QWidget* parent=0);


//signals:


//protected:
    void delight(int Color);

//private:
    int color_;

};



#endif // BLOCK_H
