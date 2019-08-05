/********************************************************************************
** Form generated from reading UI file 'LockSimple.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCKSIMPLE_H
#define UI_LOCKSIMPLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LockSimpleClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_select_1;
    QPushButton *pushButton_select_2;
    QPushButton *pushButton_select_3;

    void setupUi(QDialog *LockSimpleClass)
    {
        if (LockSimpleClass->objectName().isEmpty())
            LockSimpleClass->setObjectName(QStringLiteral("LockSimpleClass"));
        LockSimpleClass->resize(400, 400);
        LockSimpleClass->setAcceptDrops(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_lock/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        LockSimpleClass->setWindowIcon(icon);
        centralWidget = new QWidget(LockSimpleClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setGeometry(QRect(0, 0, 440, 325));
        pushButton_select_1 = new QPushButton(centralWidget);
        pushButton_select_1->setObjectName(QStringLiteral("pushButton_select_1"));
        pushButton_select_1->setGeometry(QRect(90, 90, 200, 60));
        pushButton_select_1->setMaximumSize(QSize(16777215, 16777215));
        pushButton_select_1->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_normal_1.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_pressed_1.png);"));
        pushButton_select_2 = new QPushButton(centralWidget);
        pushButton_select_2->setObjectName(QStringLiteral("pushButton_select_2"));
        pushButton_select_2->setGeometry(QRect(90, 170, 200, 60));
        pushButton_select_2->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_normal_2.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_pressed_2.png);"));
        pushButton_select_3 = new QPushButton(centralWidget);
        pushButton_select_3->setObjectName(QStringLiteral("pushButton_select_3"));
        pushButton_select_3->setGeometry(QRect(90, 250, 200, 60));
        pushButton_select_3->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_normal_3.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_pressed_3.png);"));

        retranslateUi(LockSimpleClass);

        QMetaObject::connectSlotsByName(LockSimpleClass);
    } // setupUi

    void retranslateUi(QDialog *LockSimpleClass)
    {
        LockSimpleClass->setWindowTitle(QApplication::translate("LockSimpleClass", "\347\256\200\345\215\225\345\212\240\345\257\206", Q_NULLPTR));
        pushButton_select_1->setText(QString());
        pushButton_select_2->setText(QString());
        pushButton_select_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LockSimpleClass: public Ui_LockSimpleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCKSIMPLE_H
