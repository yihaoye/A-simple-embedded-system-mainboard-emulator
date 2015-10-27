#include "lcd.h"

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QTime>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    lcd window;

    window.setWindowTitle("Main Board Emulator");

    window.show();

    return a.exec();
}


