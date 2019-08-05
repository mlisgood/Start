/********************************************************************************
** Form generated from reading UI file 'UnlockSimpleOppositeCheck.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNLOCKSIMPLEOPPOSITECHECK_H
#define UI_UNLOCKSIMPLEOPPOSITECHECK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UnlockSimpleOppositeCheckClass
{
public:
    QLabel *label_show_1;
    QLabel *label_show_2;
    QLabel *label_show_3;
    QLabel *label_show_4;
    QLabel *label_show_5;
    QPushButton *pushButton_import;
    QPushButton *pushButton_apply;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *UnlockSimpleOppositeCheckClass)
    {
        if (UnlockSimpleOppositeCheckClass->objectName().isEmpty())
            UnlockSimpleOppositeCheckClass->setObjectName(QStringLiteral("UnlockSimpleOppositeCheckClass"));
        UnlockSimpleOppositeCheckClass->resize(400, 400);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_lock/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        UnlockSimpleOppositeCheckClass->setWindowIcon(icon);
        UnlockSimpleOppositeCheckClass->setWindowOpacity(5);
        label_show_1 = new QLabel(UnlockSimpleOppositeCheckClass);
        label_show_1->setObjectName(QStringLiteral("label_show_1"));
        label_show_1->setGeometry(QRect(155, 84, 190, 12));
        label_show_2 = new QLabel(UnlockSimpleOppositeCheckClass);
        label_show_2->setObjectName(QStringLiteral("label_show_2"));
        label_show_2->setGeometry(QRect(155, 126, 190, 12));
        label_show_3 = new QLabel(UnlockSimpleOppositeCheckClass);
        label_show_3->setObjectName(QStringLiteral("label_show_3"));
        label_show_3->setGeometry(QRect(155, 167, 190, 12));
        label_show_4 = new QLabel(UnlockSimpleOppositeCheckClass);
        label_show_4->setObjectName(QStringLiteral("label_show_4"));
        label_show_4->setGeometry(QRect(155, 208, 190, 12));
        label_show_5 = new QLabel(UnlockSimpleOppositeCheckClass);
        label_show_5->setObjectName(QStringLiteral("label_show_5"));
        label_show_5->setGeometry(QRect(155, 249, 190, 12));
        pushButton_import = new QPushButton(UnlockSimpleOppositeCheckClass);
        pushButton_import->setObjectName(QStringLiteral("pushButton_import"));
        pushButton_import->setGeometry(QRect(128, 300, 125, 30));
        pushButton_import->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_4.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_4.png);"));
        pushButton_apply = new QPushButton(UnlockSimpleOppositeCheckClass);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(42, 345, 100, 30));
        pushButton_apply->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_5.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_5.png);"));
        pushButton_cancel = new QPushButton(UnlockSimpleOppositeCheckClass);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(242, 345, 100, 30));
        pushButton_cancel->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_6.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_6.png);"));

        retranslateUi(UnlockSimpleOppositeCheckClass);

        QMetaObject::connectSlotsByName(UnlockSimpleOppositeCheckClass);
    } // setupUi

    void retranslateUi(QDialog *UnlockSimpleOppositeCheckClass)
    {
        UnlockSimpleOppositeCheckClass->setWindowTitle(QApplication::translate("UnlockSimpleOppositeCheckClass", "\350\247\243\345\257\206\344\277\241\346\201\257", Q_NULLPTR));
        label_show_1->setText(QString());
        label_show_2->setText(QString());
        label_show_3->setText(QString());
        label_show_4->setText(QString());
        label_show_5->setText(QString());
        pushButton_import->setText(QString());
        pushButton_apply->setText(QString());
        pushButton_cancel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UnlockSimpleOppositeCheckClass: public Ui_UnlockSimpleOppositeCheckClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNLOCKSIMPLEOPPOSITECHECK_H
