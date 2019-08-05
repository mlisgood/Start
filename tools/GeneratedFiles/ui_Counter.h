/********************************************************************************
** Form generated from reading UI file 'Counter.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COUNTER_H
#define UI_COUNTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_CounterClass
{
public:

    void setupUi(QDialog *CounterClass)
    {
        if (CounterClass->objectName().isEmpty())
            CounterClass->setObjectName(QStringLiteral("CounterClass"));
        CounterClass->resize(200, 100);
        CounterClass->setWindowOpacity(5);

        retranslateUi(CounterClass);

        QMetaObject::connectSlotsByName(CounterClass);
    } // setupUi

    void retranslateUi(QDialog *CounterClass)
    {
        CounterClass->setWindowTitle(QApplication::translate("CounterClass", "undefined", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CounterClass: public Ui_CounterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COUNTER_H
