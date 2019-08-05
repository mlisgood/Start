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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetClass
{
public:
    QCheckBox *checkBox1;
    QCheckBox *checkBox2;
    QCheckBox *checkBox3;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_1;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;

    void setupUi(QDialog *SetClass)
    {
        if (SetClass->objectName().isEmpty())
            SetClass->setObjectName(QStringLiteral("SetClass"));
        SetClass->resize(400, 400);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_lock/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        SetClass->setWindowIcon(icon);
        SetClass->setWindowOpacity(5);
        checkBox1 = new QCheckBox(SetClass);
        checkBox1->setObjectName(QStringLiteral("checkBox1"));
        checkBox1->setGeometry(QRect(45, 281, 16, 16));
        QFont font;
        font.setKerning(true);
        checkBox1->setFont(font);
        checkBox1->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 16px;height: 16px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off_small.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off_small.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off_small.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on_small.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on_small.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on_small.png);}"));
        checkBox1->setCheckable(true);
        checkBox1->setChecked(false);
        checkBox2 = new QCheckBox(SetClass);
        checkBox2->setObjectName(QStringLiteral("checkBox2"));
        checkBox2->setGeometry(QRect(45, 303, 16, 16));
        checkBox2->setFont(font);
        checkBox2->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 16px;height: 16px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off_small.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off_small.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off_small.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on_small.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on_small.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on_small.png);}"));
        checkBox2->setCheckable(true);
        checkBox2->setChecked(false);
        checkBox3 = new QCheckBox(SetClass);
        checkBox3->setObjectName(QStringLiteral("checkBox3"));
        checkBox3->setGeometry(QRect(45, 324, 16, 16));
        checkBox3->setFont(font);
        checkBox3->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 16px;height: 16px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off_small.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off_small.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off_small.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on_small.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on_small.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on_small.png);}"));
        checkBox3->setCheckable(true);
        checkBox3->setChecked(false);
        lineEdit_5 = new QLineEdit(SetClass);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(50, 89, 284, 16));
        lineEdit_5->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_5->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        lineEdit_5->setReadOnly(true);
        lineEdit_6 = new QLineEdit(SetClass);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(50, 132, 284, 16));
        lineEdit_6->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_6->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        lineEdit_6->setReadOnly(true);
        lineEdit_7 = new QLineEdit(SetClass);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(50, 175, 284, 16));
        lineEdit_7->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_7->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        lineEdit_7->setReadOnly(true);
        lineEdit_8 = new QLineEdit(SetClass);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(50, 217, 284, 16));
        lineEdit_8->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_8->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        lineEdit_8->setReadOnly(true);
        lineEdit_1 = new QLineEdit(SetClass);
        lineEdit_1->setObjectName(QStringLiteral("lineEdit_1"));
        lineEdit_1->setGeometry(QRect(160, 239, 190, 16));
        lineEdit_1->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_1->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        lineEdit_1->setInputMethodHints(Qt::ImhNone);
        lineEdit_1->setMaxLength(255);
        lineEdit_2 = new QLineEdit(SetClass);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(160, 259, 190, 16));
        lineEdit_2->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_2->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        lineEdit_2->setInputMethodHints(Qt::ImhNone);
        lineEdit_2->setMaxLength(255);
        pushButton_1 = new QPushButton(SetClass);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setGeometry(QRect(240, 60, 90, 30));
        pushButton_1->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_7.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_7.png);"));
        pushButton_2 = new QPushButton(SetClass);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(240, 103, 90, 30));
        pushButton_2->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_7.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_7.png);"));
        pushButton_3 = new QPushButton(SetClass);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(180, 145, 90, 30));
        pushButton_3->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_7.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_7.png);"));
        pushButton_4 = new QPushButton(SetClass);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(270, 145, 90, 30));
        pushButton_4->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_8.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_8.png);"));
        pushButton_5 = new QPushButton(SetClass);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(180, 190, 90, 30));
        pushButton_5->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_7.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_7.png);"));
        pushButton_6 = new QPushButton(SetClass);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(270, 190, 90, 30));
        pushButton_6->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_9.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_9.png);"));
        pushButton_7 = new QPushButton(SetClass);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(65, 350, 60, 30));
        pushButton_7->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_10.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_10.png);"));
        pushButton_8 = new QPushButton(SetClass);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(250, 350, 60, 30));
        pushButton_8->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_11.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_11.png);"));
        pushButton_9 = new QPushButton(SetClass);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(334, 89, 16, 16));
        pushButton_9->setStyleSheet(QStringLiteral("border-image: url(:/icon/mainicon/picture_lock/icon/dialog_file_path_select.png);"));
        pushButton_10 = new QPushButton(SetClass);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(334, 132, 16, 16));
        pushButton_10->setStyleSheet(QStringLiteral("border-image: url(:/icon/mainicon/picture_lock/icon/dialog_file_path_select.png);"));
        pushButton_11 = new QPushButton(SetClass);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setGeometry(QRect(334, 175, 16, 16));
        pushButton_11->setStyleSheet(QStringLiteral("border-image: url(:/icon/mainicon/picture_lock/icon/dialog_file_path_select.png);"));
        pushButton_12 = new QPushButton(SetClass);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setGeometry(QRect(334, 217, 16, 16));
        pushButton_12->setStyleSheet(QStringLiteral("border-image: url(:/icon/mainicon/picture_lock/icon/dialog_file_path_select.png);"));
        lineEdit_3 = new QLineEdit(SetClass);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(249, 302, 101, 16));
        lineEdit_3->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_3->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        lineEdit_3->setInputMethodHints(Qt::ImhNone);
        lineEdit_3->setMaxLength(255);
        lineEdit_4 = new QLineEdit(SetClass);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(264, 324, 86, 16));
        lineEdit_4->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_4->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        lineEdit_4->setInputMethodHints(Qt::ImhNone);
        lineEdit_4->setMaxLength(255);

        retranslateUi(SetClass);

        QMetaObject::connectSlotsByName(SetClass);
    } // setupUi

    void retranslateUi(QDialog *SetClass)
    {
        SetClass->setWindowTitle(QApplication::translate("SetClass", "\350\256\276\347\275\256", Q_NULLPTR));
        checkBox1->setText(QString());
        checkBox2->setText(QString());
        checkBox3->setText(QString());
        lineEdit_5->setText(QString());
        lineEdit_6->setText(QString());
        lineEdit_7->setText(QString());
        lineEdit_8->setText(QString());
        pushButton_1->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_8->setText(QString());
        pushButton_9->setText(QString());
        pushButton_10->setText(QString());
        pushButton_11->setText(QString());
        pushButton_12->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SetClass: public Ui_SetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_H
