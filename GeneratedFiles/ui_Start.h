/********************************************************************************
** Form generated from reading UI file 'Start.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_H
#define UI_START_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;

    void setupUi(QMainWindow *StartClass)
    {
        if (StartClass->objectName().isEmpty())
            StartClass->setObjectName(QStringLiteral("StartClass"));
        StartClass->setEnabled(true);
        StartClass->resize(300, 300);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/main/picture_start/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        StartClass->setWindowIcon(icon);
        centralWidget = new QWidget(StartClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_1 = new QPushButton(centralWidget);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setGeometry(QRect(55, 80, 18, 41));
        pushButton_1->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,255,255,0);\n"
"    border:0px solid rgb(0,128,76,71);\n"
"}"));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(171, 90, 18, 41));
        pushButton_2->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,255,255,0);\n"
"    border:0px solid rgb(0,128,76,71);\n"
"}"));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(87, 197, 25, 16));
        pushButton_3->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,255,255,0);\n"
"    border:0px solid rgb(0,128,76,71);\n"
"}"));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(200, 214, 33, 20));
        pushButton_4->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,255,255,0);\n"
"    border:0px solid rgb(0,128,76,71);\n"
"}"));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(197, 249, 37, 20));
        pushButton_5->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,255,255,0);\n"
"    border:0px solid rgb(0,128,76,71);\n"
"}"));
        StartClass->setCentralWidget(centralWidget);

        retranslateUi(StartClass);

        QMetaObject::connectSlotsByName(StartClass);
    } // setupUi

    void retranslateUi(QMainWindow *StartClass)
    {
        StartClass->setWindowTitle(QApplication::translate("StartClass", "\344\270\200\347\267\222\343\201\253\343\203\242\343\203\225\343\203\242\343\203\225\343\201\227\343\202\210\343\203\274", Q_NULLPTR));
        pushButton_1->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StartClass: public Ui_StartClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_H
