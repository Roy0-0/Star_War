/********************************************************************************
** Form generated from reading UI file 'mainscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCREEN_H
#define UI_MAINSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainScreen
{
public:

    void setupUi(QWidget *MainScreen)
    {
        if (MainScreen->objectName().isEmpty())
            MainScreen->setObjectName("MainScreen");
        MainScreen->resize(800, 600);

        retranslateUi(MainScreen);

        QMetaObject::connectSlotsByName(MainScreen);
    } // setupUi

    void retranslateUi(QWidget *MainScreen)
    {
        MainScreen->setWindowTitle(QCoreApplication::translate("MainScreen", "MainScreen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainScreen: public Ui_MainScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCREEN_H
