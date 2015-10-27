#ifndef BUTTON_AREA_H
#define BUTTON_AREA_H


#include"button.h"
#include<QWidget>
class QGridLayout;

QT_END_NAMESPACE
class Button;

class ButtonArea:public QWidget
{
    Q_OBJECT
public:
    ButtonArea(QWidget* parent=0);

    enum { NumLEDButtons = 10 };
    Button *LEDButtons[NumLEDButtons];


private slots:
    void ButtonPressed();
    Button *createButton(const QString &text, const char *member);

private:
    QGridLayout* mainLayout;
    int column_;

};


#endif // BUTTON_AREA_H
