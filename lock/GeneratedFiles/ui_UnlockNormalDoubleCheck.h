/********************************************************************************
** Form generated from reading UI file 'UnlockNormalDoubleCheck.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNLOCKNORMALDOUBLECHECK_H
#define UI_UNLOCKNORMALDOUBLECHECK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UnlockNormalDoubleCheckClass
{
public:
    QPushButton *pushButton_import;
    QPushButton *pushButton_apply;
    QPushButton *pushButton_cancel;
    QLineEdit *lineEdit_show_1;
    QLineEdit *lineEdit_show_2;
    QLineEdit *lineEdit_show_3;

    void setupUi(QDialog *UnlockNormalDoubleCheckClass)
    {
        if (UnlockNormalDoubleCheckClass->objectName().isEmpty())
            UnlockNormalDoubleCheckClass->setObjectName(QStringLiteral("UnlockNormalDoubleCheckClass"));
        UnlockNormalDoubleCheckClass->resize(400, 200);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_lock/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        UnlockNormalDoubleCheckClass->setWindowIcon(icon);
        UnlockNormalDoubleCheckClass->setWindowOpacity(5);
        pushButton_import = new QPushButton(UnlockNormalDoubleCheckClass);
        pushButton_import->setObjectName(QStringLiteral("pushButton_import"));
        pushButton_import->setGeometry(QRect(43, 150, 100, 30));
        pushButton_import->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_14.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_14.png);"));
        pushButton_apply = new QPushButton(UnlockNormalDoubleCheckClass);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(143, 150, 100, 30));
        pushButton_apply->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_5.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_5.png);"));
        pushButton_cancel = new QPushButton(UnlockNormalDoubleCheckClass);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(243, 150, 100, 30));
        pushButton_cancel->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_6.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_6.png);"));
        lineEdit_show_1 = new QLineEdit(UnlockNormalDoubleCheckClass);
        lineEdit_show_1->setObjectName(QStringLiteral("lineEdit_show_1"));
        lineEdit_show_1->setEnabled(false);
        lineEdit_show_1->setGeometry(QRect(160, 66, 190, 20));
        lineEdit_show_1->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_show_1->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71,0);\n"
"}"));
        lineEdit_show_2 = new QLineEdit(UnlockNormalDoubleCheckClass);
        lineEdit_show_2->setObjectName(QStringLiteral("lineEdit_show_2"));
        lineEdit_show_2->setEnabled(false);
        lineEdit_show_2->setGeometry(QRect(160, 95, 190, 20));
        lineEdit_show_2->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_show_2->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71,0);\n"
"}"));
        lineEdit_show_3 = new QLineEdit(UnlockNormalDoubleCheckClass);
        lineEdit_show_3->setObjectName(QStringLiteral("lineEdit_show_3"));
        lineEdit_show_3->setEnabled(false);
        lineEdit_show_3->setGeometry(QRect(160, 124, 190, 20));
        lineEdit_show_3->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_show_3->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71,0);\n"
"}"));

        retranslateUi(UnlockNormalDoubleCheckClass);

        QMetaObject::connectSlotsByName(UnlockNormalDoubleCheckClass);
    } // setupUi

    void retranslateUi(QDialog *UnlockNormalDoubleCheckClass)
    {
        UnlockNormalDoubleCheckClass->setWindowTitle(QApplication::translate("UnlockNormalDoubleCheckClass", "\350\247\243\345\257\206\344\277\241\346\201\257", Q_NULLPTR));
        pushButton_import->setText(QString());
        pushButton_apply->setText(QString());
        pushButton_cancel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UnlockNormalDoubleCheckClass: public Ui_UnlockNormalDoubleCheckClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNLOCKNORMALDOUBLECHECK_H
