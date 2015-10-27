/********************************************************************************
** Form generated from reading UI file 'lcd.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LCD_H
#define UI_LCD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lcd
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *lcd)
    {
        if (lcd->objectName().isEmpty())
            lcd->setObjectName(QStringLiteral("lcd"));
        lcd->resize(400, 300);
        menuBar = new QMenuBar(lcd);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        lcd->setMenuBar(menuBar);
        mainToolBar = new QToolBar(lcd);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        lcd->addToolBar(mainToolBar);
        centralWidget = new QWidget(lcd);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lcd->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(lcd);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        lcd->setStatusBar(statusBar);

        retranslateUi(lcd);

        QMetaObject::connectSlotsByName(lcd);
    } // setupUi

    void retranslateUi(QMainWindow *lcd)
    {
        lcd->setWindowTitle(QApplication::translate("lcd", "lcd", 0));
    } // retranslateUi

};

namespace Ui {
    class lcd: public Ui_lcd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LCD_H
