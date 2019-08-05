/********************************************************************************
** Form generated from reading UI file 'Set.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_H
#define UI_SET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetClass
{
public:
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *SetClass)
    {
        if (SetClass->objectName().isEmpty())
            SetClass->setObjectName(QStringLiteral("SetClass"));
        SetClass->resize(400, 200);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/main/picture_start/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        SetClass->setWindowIcon(icon);
        SetClass->setWindowOpacity(5);
        pushButton_1 = new QPushButton(SetClass);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setGeometry(QRect(125, 47, 152, 20));
        pushButton_1->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,255,255,0);\n"
"    border:0px solid rgb(0,128,76,71);\n"
"}"));
        pushButton_2 = new QPushButton(SetClass);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(125, 91, 152, 20));
        pushButton_2->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,255,255,0);\n"
"    border:0px solid rgb(0,128,76,71);\n"
"}"));
        pushButton_3 = new QPushButton(SetClass);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(177, 134, 48, 20));
        pushButton_3->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,255,255,0);\n"
"    border:0px solid rgb(0,128,76,71);\n"
"}"));

        retranslateUi(SetClass);

        QMetaObject::connectSlotsByName(SetClass);
    } // setupUi

    void retranslateUi(QDialog *SetClass)
    {
        SetClass->setWindowTitle(QApplication::translate("SetClass", "\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_1->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SetClass: public Ui_SetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_H
