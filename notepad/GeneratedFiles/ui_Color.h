/********************************************************************************
** Form generated from reading UI file 'Color.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLOR_H
#define UI_COLOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ColorClass
{
public:
    QPushButton *pushButton_close_window;
    QLabel *label_1;
    QSpinBox *spinBox_1;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_accept;
    QPushButton *pushButton_exit;
    QPushButton *pushButton_remove;
    QPushButton *pushButton_add;
    QPushButton *pushButton_color_1;
    QPushButton *pushButton_color_2;
    QPushButton *pushButton_color_3;
    QPushButton *pushButton_color_4;
    QPushButton *pushButton_color_5;
    QPushButton *pushButton_color_6;
    QPushButton *pushButton_color_7;
    QPushButton *pushButton_color_8;
    QPushButton *pushButton_color_9;
    QPushButton *pushButton_color_10;
    QPushButton *pushButton_color_11;
    QPushButton *pushButton_color_12;
    QPushButton *pushButton_color_13;
    QPushButton *pushButton_color_14;
    QPushButton *pushButton_color_15;
    QPushButton *pushButton_color_16;
    QPushButton *pushButton_color_17;
    QPushButton *pushButton_color_18;
    QPushButton *pushButton_color_19;
    QPushButton *pushButton_color_20;
    QPushButton *pushButton_color_21;
    QPushButton *pushButton_color_22;
    QPushButton *pushButton_color_23;
    QPushButton *pushButton_color_24;
    QPushButton *pushButton_color_25;
    QPushButton *pushButton_color_26;
    QPushButton *pushButton_color_27;
    QPushButton *pushButton_color_28;
    QPushButton *pushButton_color_29;
    QPushButton *pushButton_color_30;
    QPushButton *pushButton_color_31;
    QPushButton *pushButton_color_32;
    QPushButton *pushButton_color_33;
    QPushButton *pushButton_color_34;
    QPushButton *pushButton_color_35;
    QPushButton *pushButton_color_36;
    QPushButton *pushButton_color_37;
    QPushButton *pushButton_color_38;
    QPushButton *pushButton_color_39;
    QPushButton *pushButton_color_40;
    QPushButton *pushButton_color_41;
    QPushButton *pushButton_color_42;
    QPushButton *pushButton_color_43;
    QPushButton *pushButton_color_44;
    QPushButton *pushButton_color_45;
    QPushButton *pushButton_color_46;
    QPushButton *pushButton_color_47;
    QPushButton *pushButton_color_48;
    QPushButton *pushButton_self_1;
    QPushButton *pushButton_self_2;
    QPushButton *pushButton_self_3;
    QPushButton *pushButton_self_4;
    QPushButton *pushButton_self_5;
    QPushButton *pushButton_self_6;
    QPushButton *pushButton_self_7;
    QPushButton *pushButton_self_8;
    QPushButton *pushButton_self_9;
    QPushButton *pushButton_self_10;
    QPushButton *pushButton_self_11;
    QPushButton *pushButton_self_12;
    QPushButton *pushButton_self_13;
    QPushButton *pushButton_self_14;
    QPushButton *pushButton_self_15;
    QPushButton *pushButton_self_16;
    QPushButton *pushButton_self_17;
    QPushButton *pushButton_self_18;
    QPushButton *pushButton_self_19;
    QPushButton *pushButton_self_20;
    QPushButton *pushButton_self_21;
    QPushButton *pushButton_self_22;
    QPushButton *pushButton_self_23;
    QPushButton *pushButton_self_24;
    QPushButton *pushButton_select;
    QSlider *verticalSlider;
    QLabel *label_3_extra;
    QPushButton *pushButton_label_3_extra;

    void setupUi(QDialog *ColorClass)
    {
        if (ColorClass->objectName().isEmpty())
            ColorClass->setObjectName(QStringLiteral("ColorClass"));
        ColorClass->resize(600, 400);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_notepad/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        ColorClass->setWindowIcon(icon);
        ColorClass->setWindowOpacity(5);
        ColorClass->setSizeGripEnabled(false);
        pushButton_close_window = new QPushButton(ColorClass);
        pushButton_close_window->setObjectName(QStringLiteral("pushButton_close_window"));
        pushButton_close_window->setGeometry(QRect(525, 15, 25, 25));
        pushButton_close_window->setStyleSheet(QStringLiteral("border-image: url(:/icon/manage/picture_notepad/icon/window_close.png);"));
        label_1 = new QLabel(ColorClass);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setGeometry(QRect(340, 300, 50, 30));
        label_1->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        spinBox_1 = new QSpinBox(ColorClass);
        spinBox_1->setObjectName(QStringLiteral("spinBox_1"));
        spinBox_1->setGeometry(QRect(420, 250, 42, 22));
        spinBox_1->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_1->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/up_button.png);     \n"
"    background: #FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/up_button.png);   \n"
"    background: #FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"}"));
        spinBox_1->setMaximum(255);
        spinBox_1->setValue(255);
        spinBox_2 = new QSpinBox(ColorClass);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(420, 280, 42, 22));
        spinBox_2->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/up_button.png);     \n"
"    background: #FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/up_button.png);   \n"
"    background: #FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"}"));
        spinBox_2->setMaximum(255);
        spinBox_2->setValue(255);
        spinBox_3 = new QSpinBox(ColorClass);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setGeometry(QRect(420, 310, 42, 22));
        spinBox_3->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_3->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/up_button.png);     \n"
"    background: #FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/up_button.png);   \n"
"    background: #FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"}"));
        spinBox_3->setMaximum(255);
        spinBox_3->setValue(255);
        label_2 = new QLabel(ColorClass);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(340, 80, 150, 150));
        label_2->setStyleSheet(QStringLiteral(""));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/picture_notepad/color/picture_notepad/color_style/right_style.png")));
        label_2->setMargin(0);
        label_3 = new QLabel(ColorClass);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(520, 80, 40, 150));
        label_3->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:2px solid rgb(128,76,71);\n"
"}"));
        pushButton_accept = new QPushButton(ColorClass);
        pushButton_accept->setObjectName(QStringLiteral("pushButton_accept"));
        pushButton_accept->setGeometry(QRect(125, 350, 105, 30));
        pushButton_accept->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_accept_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_accept_pressed.png);"));
        pushButton_exit = new QPushButton(ColorClass);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(385, 350, 75, 30));
        pushButton_exit->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_exit_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_exit_pressed.png);"));
        pushButton_remove = new QPushButton(ColorClass);
        pushButton_remove->setObjectName(QStringLiteral("pushButton_remove"));
        pushButton_remove->setGeometry(QRect(470, 275, 100, 30));
        pushButton_remove->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_remove_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_remove_pressed.png);"));
        pushButton_add = new QPushButton(ColorClass);
        pushButton_add->setObjectName(QStringLiteral("pushButton_add"));
        pushButton_add->setGeometry(QRect(470, 245, 75, 30));
        pushButton_add->setMaximumSize(QSize(16777215, 16777215));
        pushButton_add->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_add_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_add_pressed.png);"));
        pushButton_color_1 = new QPushButton(ColorClass);
        pushButton_color_1->setObjectName(QStringLiteral("pushButton_color_1"));
        pushButton_color_1->setGeometry(QRect(30, 80, 25, 15));
        pushButton_color_1->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,128,128);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_2 = new QPushButton(ColorClass);
        pushButton_color_2->setObjectName(QStringLiteral("pushButton_color_2"));
        pushButton_color_2->setGeometry(QRect(65, 80, 25, 15));
        pushButton_color_2->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,128);\n"
"    border:1px solid rgb(128,76,71);\n"
"}pushButton_color_1"));
        pushButton_color_3 = new QPushButton(ColorClass);
        pushButton_color_3->setObjectName(QStringLiteral("pushButton_color_3"));
        pushButton_color_3->setEnabled(true);
        pushButton_color_3->setGeometry(QRect(100, 80, 25, 15));
        pushButton_color_3->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(128,255,128);\n"
"    border:1px solid rgb(128,76,71);\n"
"}pushButton_color_1"));
        pushButton_color_4 = new QPushButton(ColorClass);
        pushButton_color_4->setObjectName(QStringLiteral("pushButton_color_4"));
        pushButton_color_4->setEnabled(true);
        pushButton_color_4->setGeometry(QRect(135, 80, 25, 15));
        pushButton_color_4->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,255,128);\n"
"    border:1px solid rgb(128,76,71);\n"
"}pushButton_color_1"));
        pushButton_color_5 = new QPushButton(ColorClass);
        pushButton_color_5->setObjectName(QStringLiteral("pushButton_color_5"));
        pushButton_color_5->setEnabled(true);
        pushButton_color_5->setGeometry(QRect(170, 80, 25, 15));
        pushButton_color_5->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(128,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}pushButton_color_1"));
        pushButton_color_6 = new QPushButton(ColorClass);
        pushButton_color_6->setObjectName(QStringLiteral("pushButton_color_6"));
        pushButton_color_6->setEnabled(true);
        pushButton_color_6->setGeometry(QRect(205, 80, 25, 15));
        pushButton_color_6->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,128,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}pushButton_color_1"));
        pushButton_color_7 = new QPushButton(ColorClass);
        pushButton_color_7->setObjectName(QStringLiteral("pushButton_color_7"));
        pushButton_color_7->setEnabled(true);
        pushButton_color_7->setGeometry(QRect(240, 80, 25, 15));
        pushButton_color_7->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,128,192);\n"
"    border:1px solid rgb(128,76,71);\n"
"}pushButton_color_1"));
        pushButton_color_8 = new QPushButton(ColorClass);
        pushButton_color_8->setObjectName(QStringLiteral("pushButton_color_8"));
        pushButton_color_8->setEnabled(true);
        pushButton_color_8->setGeometry(QRect(275, 80, 25, 15));
        pushButton_color_8->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,128,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}pushButton_color_1"));
        pushButton_color_9 = new QPushButton(ColorClass);
        pushButton_color_9->setObjectName(QStringLiteral("pushButton_color_9"));
        pushButton_color_9->setGeometry(QRect(30, 105, 25, 15));
        pushButton_color_9->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,0,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_10 = new QPushButton(ColorClass);
        pushButton_color_10->setObjectName(QStringLiteral("pushButton_color_10"));
        pushButton_color_10->setGeometry(QRect(65, 105, 25, 15));
        pushButton_color_10->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_11 = new QPushButton(ColorClass);
        pushButton_color_11->setObjectName(QStringLiteral("pushButton_color_11"));
        pushButton_color_11->setGeometry(QRect(100, 105, 25, 15));
        pushButton_color_11->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(128,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_12 = new QPushButton(ColorClass);
        pushButton_color_12->setObjectName(QStringLiteral("pushButton_color_12"));
        pushButton_color_12->setGeometry(QRect(135, 105, 25, 15));
        pushButton_color_12->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,255,64);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_13 = new QPushButton(ColorClass);
        pushButton_color_13->setObjectName(QStringLiteral("pushButton_color_13"));
        pushButton_color_13->setGeometry(QRect(170, 105, 25, 15));
        pushButton_color_13->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_14 = new QPushButton(ColorClass);
        pushButton_color_14->setObjectName(QStringLiteral("pushButton_color_14"));
        pushButton_color_14->setGeometry(QRect(205, 105, 25, 15));
        pushButton_color_14->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,128,192);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_15 = new QPushButton(ColorClass);
        pushButton_color_15->setObjectName(QStringLiteral("pushButton_color_15"));
        pushButton_color_15->setGeometry(QRect(240, 105, 25, 15));
        pushButton_color_15->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(128,128,192);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_16 = new QPushButton(ColorClass);
        pushButton_color_16->setObjectName(QStringLiteral("pushButton_color_16"));
        pushButton_color_16->setGeometry(QRect(275, 105, 25, 15));
        pushButton_color_16->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,0,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_17 = new QPushButton(ColorClass);
        pushButton_color_17->setObjectName(QStringLiteral("pushButton_color_17"));
        pushButton_color_17->setGeometry(QRect(30, 130, 25, 15));
        pushButton_color_17->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(128,64,64);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_18 = new QPushButton(ColorClass);
        pushButton_color_18->setObjectName(QStringLiteral("pushButton_color_18"));
        pushButton_color_18->setGeometry(QRect(65, 130, 25, 15));
        pushButton_color_18->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,128,64);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_19 = new QPushButton(ColorClass);
        pushButton_color_19->setObjectName(QStringLiteral("pushButton_color_19"));
        pushButton_color_19->setGeometry(QRect(100, 130, 25, 15));
        pushButton_color_19->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_20 = new QPushButton(ColorClass);
        pushButton_color_20->setObjectName(QStringLiteral("pushButton_color_20"));
        pushButton_color_20->setGeometry(QRect(135, 130, 25, 15));
        pushButton_color_20->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,128,128);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_21 = new QPushButton(ColorClass);
        pushButton_color_21->setObjectName(QStringLiteral("pushButton_color_21"));
        pushButton_color_21->setGeometry(QRect(170, 130, 25, 15));
        pushButton_color_21->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,64,128);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_22 = new QPushButton(ColorClass);
        pushButton_color_22->setObjectName(QStringLiteral("pushButton_color_22"));
        pushButton_color_22->setGeometry(QRect(205, 130, 25, 15));
        pushButton_color_22->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(128,128,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_23 = new QPushButton(ColorClass);
        pushButton_color_23->setObjectName(QStringLiteral("pushButton_color_23"));
        pushButton_color_23->setGeometry(QRect(240, 130, 25, 15));
        pushButton_color_23->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(128,0,64);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_24 = new QPushButton(ColorClass);
        pushButton_color_24->setObjectName(QStringLiteral("pushButton_color_24"));
        pushButton_color_24->setGeometry(QRect(275, 130, 25, 15));
        pushButton_color_24->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,0,128);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_25 = new QPushButton(ColorClass);
        pushButton_color_25->setObjectName(QStringLiteral("pushButton_color_25"));
        pushButton_color_25->setGeometry(QRect(30, 155, 25, 15));
        pushButton_color_25->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(128,0,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_26 = new QPushButton(ColorClass);
        pushButton_color_26->setObjectName(QStringLiteral("pushButton_color_26"));
        pushButton_color_26->setGeometry(QRect(65, 155, 25, 15));
        pushButton_color_26->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,128,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_27 = new QPushButton(ColorClass);
        pushButton_color_27->setObjectName(QStringLiteral("pushButton_color_27"));
        pushButton_color_27->setGeometry(QRect(100, 155, 25, 15));
        pushButton_color_27->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,128,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_28 = new QPushButton(ColorClass);
        pushButton_color_28->setObjectName(QStringLiteral("pushButton_color_28"));
        pushButton_color_28->setGeometry(QRect(135, 155, 25, 15));
        pushButton_color_28->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,128,64);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_29 = new QPushButton(ColorClass);
        pushButton_color_29->setObjectName(QStringLiteral("pushButton_color_29"));
        pushButton_color_29->setGeometry(QRect(170, 155, 25, 15));
        pushButton_color_29->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,0,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_30 = new QPushButton(ColorClass);
        pushButton_color_30->setObjectName(QStringLiteral("pushButton_color_30"));
        pushButton_color_30->setGeometry(QRect(205, 155, 25, 15));
        pushButton_color_30->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,0,160);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_31 = new QPushButton(ColorClass);
        pushButton_color_31->setObjectName(QStringLiteral("pushButton_color_31"));
        pushButton_color_31->setGeometry(QRect(240, 155, 25, 15));
        pushButton_color_31->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(128,0,128);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_32 = new QPushButton(ColorClass);
        pushButton_color_32->setObjectName(QStringLiteral("pushButton_color_32"));
        pushButton_color_32->setGeometry(QRect(275, 155, 25, 15));
        pushButton_color_32->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(128,0,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_33 = new QPushButton(ColorClass);
        pushButton_color_33->setObjectName(QStringLiteral("pushButton_color_33"));
        pushButton_color_33->setGeometry(QRect(30, 180, 25, 15));
        pushButton_color_33->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(64,0,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_34 = new QPushButton(ColorClass);
        pushButton_color_34->setObjectName(QStringLiteral("pushButton_color_34"));
        pushButton_color_34->setGeometry(QRect(65, 180, 25, 15));
        pushButton_color_34->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(128,64,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_35 = new QPushButton(ColorClass);
        pushButton_color_35->setObjectName(QStringLiteral("pushButton_color_35"));
        pushButton_color_35->setGeometry(QRect(100, 180, 25, 15));
        pushButton_color_35->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,64,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_36 = new QPushButton(ColorClass);
        pushButton_color_36->setObjectName(QStringLiteral("pushButton_color_36"));
        pushButton_color_36->setGeometry(QRect(135, 180, 25, 15));
        pushButton_color_36->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,64,64);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_37 = new QPushButton(ColorClass);
        pushButton_color_37->setObjectName(QStringLiteral("pushButton_color_37"));
        pushButton_color_37->setGeometry(QRect(170, 180, 25, 15));
        pushButton_color_37->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,0,128);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_38 = new QPushButton(ColorClass);
        pushButton_color_38->setObjectName(QStringLiteral("pushButton_color_38"));
        pushButton_color_38->setGeometry(QRect(205, 180, 25, 15));
        pushButton_color_38->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,0,64);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_39 = new QPushButton(ColorClass);
        pushButton_color_39->setObjectName(QStringLiteral("pushButton_color_39"));
        pushButton_color_39->setGeometry(QRect(240, 180, 25, 15));
        pushButton_color_39->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(64,0,64);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_40 = new QPushButton(ColorClass);
        pushButton_color_40->setObjectName(QStringLiteral("pushButton_color_40"));
        pushButton_color_40->setGeometry(QRect(275, 180, 25, 15));
        pushButton_color_40->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(64,0,128);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_41 = new QPushButton(ColorClass);
        pushButton_color_41->setObjectName(QStringLiteral("pushButton_color_41"));
        pushButton_color_41->setGeometry(QRect(30, 205, 25, 15));
        pushButton_color_41->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(0,0,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_42 = new QPushButton(ColorClass);
        pushButton_color_42->setObjectName(QStringLiteral("pushButton_color_42"));
        pushButton_color_42->setGeometry(QRect(65, 205, 25, 15));
        pushButton_color_42->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(128,128,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_43 = new QPushButton(ColorClass);
        pushButton_color_43->setObjectName(QStringLiteral("pushButton_color_43"));
        pushButton_color_43->setGeometry(QRect(100, 205, 25, 15));
        pushButton_color_43->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(128,128,64);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_44 = new QPushButton(ColorClass);
        pushButton_color_44->setObjectName(QStringLiteral("pushButton_color_44"));
        pushButton_color_44->setGeometry(QRect(135, 205, 25, 15));
        pushButton_color_44->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(128,128,128);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_45 = new QPushButton(ColorClass);
        pushButton_color_45->setObjectName(QStringLiteral("pushButton_color_45"));
        pushButton_color_45->setGeometry(QRect(170, 205, 25, 15));
        pushButton_color_45->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(64,128,128);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_46 = new QPushButton(ColorClass);
        pushButton_color_46->setObjectName(QStringLiteral("pushButton_color_46"));
        pushButton_color_46->setGeometry(QRect(205, 205, 25, 15));
        pushButton_color_46->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(192,192,192);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_47 = new QPushButton(ColorClass);
        pushButton_color_47->setObjectName(QStringLiteral("pushButton_color_47"));
        pushButton_color_47->setGeometry(QRect(240, 205, 25, 15));
        pushButton_color_47->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(64,64,64);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_color_48 = new QPushButton(ColorClass);
        pushButton_color_48->setObjectName(QStringLiteral("pushButton_color_48"));
        pushButton_color_48->setGeometry(QRect(275, 205, 25, 15));
        pushButton_color_48->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_1 = new QPushButton(ColorClass);
        pushButton_self_1->setObjectName(QStringLiteral("pushButton_self_1"));
        pushButton_self_1->setGeometry(QRect(30, 265, 25, 15));
        pushButton_self_1->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_2 = new QPushButton(ColorClass);
        pushButton_self_2->setObjectName(QStringLiteral("pushButton_self_2"));
        pushButton_self_2->setGeometry(QRect(65, 265, 25, 15));
        pushButton_self_2->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_3 = new QPushButton(ColorClass);
        pushButton_self_3->setObjectName(QStringLiteral("pushButton_self_3"));
        pushButton_self_3->setEnabled(true);
        pushButton_self_3->setGeometry(QRect(100, 265, 25, 15));
        pushButton_self_3->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_4 = new QPushButton(ColorClass);
        pushButton_self_4->setObjectName(QStringLiteral("pushButton_self_4"));
        pushButton_self_4->setEnabled(true);
        pushButton_self_4->setGeometry(QRect(135, 265, 25, 15));
        pushButton_self_4->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_5 = new QPushButton(ColorClass);
        pushButton_self_5->setObjectName(QStringLiteral("pushButton_self_5"));
        pushButton_self_5->setEnabled(true);
        pushButton_self_5->setGeometry(QRect(170, 265, 25, 15));
        pushButton_self_5->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_6 = new QPushButton(ColorClass);
        pushButton_self_6->setObjectName(QStringLiteral("pushButton_self_6"));
        pushButton_self_6->setEnabled(true);
        pushButton_self_6->setGeometry(QRect(205, 265, 25, 15));
        pushButton_self_6->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_7 = new QPushButton(ColorClass);
        pushButton_self_7->setObjectName(QStringLiteral("pushButton_self_7"));
        pushButton_self_7->setEnabled(true);
        pushButton_self_7->setGeometry(QRect(240, 265, 25, 15));
        pushButton_self_7->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_8 = new QPushButton(ColorClass);
        pushButton_self_8->setObjectName(QStringLiteral("pushButton_self_8"));
        pushButton_self_8->setEnabled(true);
        pushButton_self_8->setGeometry(QRect(275, 265, 25, 15));
        pushButton_self_8->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_9 = new QPushButton(ColorClass);
        pushButton_self_9->setObjectName(QStringLiteral("pushButton_self_9"));
        pushButton_self_9->setGeometry(QRect(30, 290, 25, 15));
        pushButton_self_9->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_10 = new QPushButton(ColorClass);
        pushButton_self_10->setObjectName(QStringLiteral("pushButton_self_10"));
        pushButton_self_10->setGeometry(QRect(65, 290, 25, 15));
        pushButton_self_10->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_11 = new QPushButton(ColorClass);
        pushButton_self_11->setObjectName(QStringLiteral("pushButton_self_11"));
        pushButton_self_11->setGeometry(QRect(100, 290, 25, 15));
        pushButton_self_11->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_12 = new QPushButton(ColorClass);
        pushButton_self_12->setObjectName(QStringLiteral("pushButton_self_12"));
        pushButton_self_12->setGeometry(QRect(135, 290, 25, 15));
        pushButton_self_12->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_13 = new QPushButton(ColorClass);
        pushButton_self_13->setObjectName(QStringLiteral("pushButton_self_13"));
        pushButton_self_13->setGeometry(QRect(170, 290, 25, 15));
        pushButton_self_13->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_14 = new QPushButton(ColorClass);
        pushButton_self_14->setObjectName(QStringLiteral("pushButton_self_14"));
        pushButton_self_14->setGeometry(QRect(205, 290, 25, 15));
        pushButton_self_14->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_15 = new QPushButton(ColorClass);
        pushButton_self_15->setObjectName(QStringLiteral("pushButton_self_15"));
        pushButton_self_15->setGeometry(QRect(240, 290, 25, 15));
        pushButton_self_15->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_16 = new QPushButton(ColorClass);
        pushButton_self_16->setObjectName(QStringLiteral("pushButton_self_16"));
        pushButton_self_16->setGeometry(QRect(275, 290, 25, 15));
        pushButton_self_16->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_17 = new QPushButton(ColorClass);
        pushButton_self_17->setObjectName(QStringLiteral("pushButton_self_17"));
        pushButton_self_17->setGeometry(QRect(30, 315, 25, 15));
        pushButton_self_17->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_18 = new QPushButton(ColorClass);
        pushButton_self_18->setObjectName(QStringLiteral("pushButton_self_18"));
        pushButton_self_18->setGeometry(QRect(65, 315, 25, 15));
        pushButton_self_18->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_19 = new QPushButton(ColorClass);
        pushButton_self_19->setObjectName(QStringLiteral("pushButton_self_19"));
        pushButton_self_19->setGeometry(QRect(100, 315, 25, 15));
        pushButton_self_19->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_20 = new QPushButton(ColorClass);
        pushButton_self_20->setObjectName(QStringLiteral("pushButton_self_20"));
        pushButton_self_20->setGeometry(QRect(135, 315, 25, 15));
        pushButton_self_20->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_21 = new QPushButton(ColorClass);
        pushButton_self_21->setObjectName(QStringLiteral("pushButton_self_21"));
        pushButton_self_21->setGeometry(QRect(170, 315, 25, 15));
        pushButton_self_21->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_22 = new QPushButton(ColorClass);
        pushButton_self_22->setObjectName(QStringLiteral("pushButton_self_22"));
        pushButton_self_22->setGeometry(QRect(205, 315, 25, 15));
        pushButton_self_22->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_23 = new QPushButton(ColorClass);
        pushButton_self_23->setObjectName(QStringLiteral("pushButton_self_23"));
        pushButton_self_23->setGeometry(QRect(240, 315, 25, 15));
        pushButton_self_23->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_self_24 = new QPushButton(ColorClass);
        pushButton_self_24->setObjectName(QStringLiteral("pushButton_self_24"));
        pushButton_self_24->setGeometry(QRect(275, 315, 25, 15));
        pushButton_self_24->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        pushButton_select = new QPushButton(ColorClass);
        pushButton_select->setObjectName(QStringLiteral("pushButton_select"));
        pushButton_select->setGeometry(QRect(470, 305, 90, 30));
        pushButton_select->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_select_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_select_pressed.png);"));
        verticalSlider = new QSlider(ColorClass);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setGeometry(QRect(560, 80, 19, 150));
        verticalSlider->setContextMenuPolicy(Qt::NoContextMenu);
        verticalSlider->setLayoutDirection(Qt::LeftToRight);
        verticalSlider->setAutoFillBackground(false);
        verticalSlider->setStyleSheet(QString::fromUtf8("/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSlider\n"
"{\n"
"    border-color: #FDEAD3;\n"
"}\n"
"QSlider::groove:vertical\n"
"{  \n"
"    background: #FDEAD3;  \n"
"    width: 6px;  \n"
"    border-radius: 1px;  \n"
"    padding-left:-1px;  \n"
"    padding-right:-1px;  \n"
"    padding-top:-1px;  \n"
"    padding-bottom:-1px;  \n"
"} \n"
"QSlider::sub-page:vertical\n"
"{  \n"
"    background: #FDEAD3;  \n"
"    border-radius: 2px;  \n"
"} \n"
"QSlider::add-page:vertical\n"
"{  \n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #439cf4, stop:1 #439cf4);  \n"
"    background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1, stop: 0 #FDEAD3, stop: 1 #FDEAD3);  \n"
"    width: 10px;  \n"
"    border-radius: 2px;  \n"
"}\n"
"QSlider::handle:vertical   \n"
"{     \n"
"    border-image: url(:/picture_notepad/slider/picture_notepad/slider_style/handle.png);\n"
"    margin: 1px -7px 1px -7px; \n"
"    height: 20px;\n"
"} "));
        verticalSlider->setMinimum(0);
        verticalSlider->setMaximum(145);
        verticalSlider->setSingleStep(1);
        verticalSlider->setValue(73);
        verticalSlider->setSliderPosition(73);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider->setInvertedAppearance(true);
        verticalSlider->setInvertedControls(false);
        label_3_extra = new QLabel(ColorClass);
        label_3_extra->setObjectName(QStringLiteral("label_3_extra"));
        label_3_extra->setGeometry(QRect(520, 80, 40, 150));
        label_3_extra->setStyleSheet(QStringLiteral(""));
        label_3_extra->setPixmap(QPixmap(QString::fromUtf8(":/picture_notepad/color/picture_notepad/color_style/right_style_extra.png")));
        pushButton_label_3_extra = new QPushButton(ColorClass);
        pushButton_label_3_extra->setObjectName(QStringLiteral("pushButton_label_3_extra"));
        pushButton_label_3_extra->setEnabled(false);
        pushButton_label_3_extra->setGeometry(QRect(520, 80, 40, 150));
        pushButton_label_3_extra->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));

        retranslateUi(ColorClass);

        QMetaObject::connectSlotsByName(ColorClass);
    } // setupUi

    void retranslateUi(QDialog *ColorClass)
    {
        ColorClass->setWindowTitle(QApplication::translate("ColorClass", "\351\242\234\350\211\262\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_close_window->setText(QString());
        label_1->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        pushButton_accept->setText(QString());
        pushButton_exit->setText(QString());
        pushButton_remove->setText(QString());
        pushButton_add->setText(QString());
        pushButton_color_1->setText(QString());
        pushButton_color_2->setText(QString());
        pushButton_color_3->setText(QString());
        pushButton_color_4->setText(QString());
        pushButton_color_5->setText(QString());
        pushButton_color_6->setText(QString());
        pushButton_color_7->setText(QString());
        pushButton_color_8->setText(QString());
        pushButton_color_9->setText(QString());
        pushButton_color_10->setText(QString());
        pushButton_color_11->setText(QString());
        pushButton_color_12->setText(QString());
        pushButton_color_13->setText(QString());
        pushButton_color_14->setText(QString());
        pushButton_color_15->setText(QString());
        pushButton_color_16->setText(QString());
        pushButton_color_17->setText(QString());
        pushButton_color_18->setText(QString());
        pushButton_color_19->setText(QString());
        pushButton_color_20->setText(QString());
        pushButton_color_21->setText(QString());
        pushButton_color_22->setText(QString());
        pushButton_color_23->setText(QString());
        pushButton_color_24->setText(QString());
        pushButton_color_25->setText(QString());
        pushButton_color_26->setText(QString());
        pushButton_color_27->setText(QString());
        pushButton_color_28->setText(QString());
        pushButton_color_29->setText(QString());
        pushButton_color_30->setText(QString());
        pushButton_color_31->setText(QString());
        pushButton_color_32->setText(QString());
        pushButton_color_33->setText(QString());
        pushButton_color_34->setText(QString());
        pushButton_color_35->setText(QString());
        pushButton_color_36->setText(QString());
        pushButton_color_37->setText(QString());
        pushButton_color_38->setText(QString());
        pushButton_color_39->setText(QString());
        pushButton_color_40->setText(QString());
        pushButton_color_41->setText(QString());
        pushButton_color_42->setText(QString());
        pushButton_color_43->setText(QString());
        pushButton_color_44->setText(QString());
        pushButton_color_45->setText(QString());
        pushButton_color_46->setText(QString());
        pushButton_color_47->setText(QString());
        pushButton_color_48->setText(QString());
        pushButton_self_1->setText(QString());
        pushButton_self_2->setText(QString());
        pushButton_self_3->setText(QString());
        pushButton_self_4->setText(QString());
        pushButton_self_5->setText(QString());
        pushButton_self_6->setText(QString());
        pushButton_self_7->setText(QString());
        pushButton_self_8->setText(QString());
        pushButton_self_9->setText(QString());
        pushButton_self_10->setText(QString());
        pushButton_self_11->setText(QString());
        pushButton_self_12->setText(QString());
        pushButton_self_13->setText(QString());
        pushButton_self_14->setText(QString());
        pushButton_self_15->setText(QString());
        pushButton_self_16->setText(QString());
        pushButton_self_17->setText(QString());
        pushButton_self_18->setText(QString());
        pushButton_self_19->setText(QString());
        pushButton_self_20->setText(QString());
        pushButton_self_21->setText(QString());
        pushButton_self_22->setText(QString());
        pushButton_self_23->setText(QString());
        pushButton_self_24->setText(QString());
        pushButton_select->setText(QString());
        label_3_extra->setText(QString());
        pushButton_label_3_extra->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ColorClass: public Ui_ColorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLOR_H
