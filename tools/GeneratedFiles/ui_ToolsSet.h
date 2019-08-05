/********************************************************************************
** Form generated from reading UI file 'ToolsSet.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLSSET_H
#define UI_TOOLSSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ToolsSetClass
{
public:
    QSpinBox *spinBox_1;
    QSpinBox *spinBox_2;
    QPushButton *pushButton_apply;
    QPushButton *pushButton_cancel;
    QLineEdit *lineedit_program_1;
    QComboBox *comboBox_2;
    QComboBox *comboBox_1;
    QPushButton *pushButton_choose_1;
    QPushButton *pushButton_choose_2;
    QPushButton *pushButton_choose_3;
    QPushButton *pushButton_choose_4;
    QPushButton *pushButton_choose_5;
    QPushButton *pushButton_choose_6;
    QPushButton *pushButton_choose_7;
    QPushButton *pushButton_choose_8;
    QLineEdit *lineedit_program_2;
    QLineEdit *lineedit_program_3;
    QLineEdit *lineedit_program_4;
    QLineEdit *lineedit_program_5;
    QLineEdit *lineedit_program_6;
    QLineEdit *lineedit_program_7;
    QLineEdit *lineedit_program_8;
    QCheckBox *checkBox;
    QPushButton *pushButton_choose_9;
    QPushButton *pushButton_choose_10;
    QPushButton *pushButton_choose_11;
    QPushButton *pushButton_choose_12;
    QPushButton *pushButton_choose_13;
    QPushButton *pushButton_choose_14;
    QPushButton *pushButton_choose_15;
    QPushButton *pushButton_choose_16;

    void setupUi(QDialog *ToolsSetClass)
    {
        if (ToolsSetClass->objectName().isEmpty())
            ToolsSetClass->setObjectName(QStringLiteral("ToolsSetClass"));
        ToolsSetClass->resize(400, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/picture_tools/icon/picture_tools/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        ToolsSetClass->setWindowIcon(icon);
        ToolsSetClass->setWindowOpacity(5);
        spinBox_1 = new QSpinBox(ToolsSetClass);
        spinBox_1->setObjectName(QStringLiteral("spinBox_1"));
        spinBox_1->setGeometry(QRect(69, 443, 50, 22));
        spinBox_1->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_1->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/up_button.png);     \n"
"    background: #FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/up_button.png);   \n"
"    background: #FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"}"));
        spinBox_1->setMaximum(9999);
        spinBox_2 = new QSpinBox(ToolsSetClass);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(235, 443, 50, 22));
        spinBox_2->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/up_button.png);     \n"
"    background: #FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/up_button.png);   \n"
"    background: #FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"}"));
        spinBox_2->setMaximum(9999);
        pushButton_apply = new QPushButton(ToolsSetClass);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(100, 536, 41, 23));
        pushButton_apply->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_cancel = new QPushButton(ToolsSetClass);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(260, 536, 41, 23));
        pushButton_cancel->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        lineedit_program_1 = new QLineEdit(ToolsSetClass);
        lineedit_program_1->setObjectName(QStringLiteral("lineedit_program_1"));
        lineedit_program_1->setGeometry(QRect(140, 158, 163, 16));
        lineedit_program_1->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_program_1->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_program_1->setReadOnly(true);
        comboBox_2 = new QComboBox(ToolsSetClass);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(40, 383, 200, 25));
        comboBox_2->setContextMenuPolicy(Qt::PreventContextMenu);
        comboBox_2->setAutoFillBackground(false);
        comboBox_2->setStyleSheet(QLatin1String("QComboBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    border-radius: 0px;\n"
"    padding: 1px 3px 1px 3px;\n"
"    min-width: 6px;\n"
"}\n"
"QComboBox:editable\n"
"{\n"
"    background: #FDEAD3;\n"
"}\n"
"QComboBox:!editable\n"
"{\n"
"    background: #FDEAD3;\n"
"}\n"
"QComboBox:!editable:on, QComboBox::drop-down:editable:on\n"
"{\n"
"    background: #FDEAD3;  \n"
"}\n"
"QComboBox::drop-down:editable\n"
"{\n"
"    background: #E49C97;\n"
"}\n"
"QComboBox::drop-down:editable\n"
"{\n"
"    background: #E49C97;\n"
"}\n"
"QComboBox::drop-down:editable\n"
"{\n"
"    background: #E49C97;\n"
"}\n"
"QComboBox::drop-down:!editable\n"
"{\n"
"    background: #E49C97;\n"
"}\n"
"QComboBox::drop-down:!editable\n"
"{\n"
"    background: #E49C97;\n"
"}\n"
"QComboBox::drop-down\n"
"{\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 15px;\n"
"    border-left-width: 1px;\n"
"    border-left-color: #804C47;\n"
"    border-left-style: solid;\n"
"    border-top-right-radius: 0px;\n"
""
                        "    border-bottom-right-radius: 0px;\n"
"}\n"
"QComboBox::down-arrow\n"
"{\n"
"    image: url(:/picture_tools/combobox/picture_tools/combobox_style/arrow.png);\n"
"}\n"
"QComboBox::down-arrow:on\n"
"{ \n"
"     image: url(:/picture_tools/combobox/picture_tools/combobox_style/arrow.png);\n"
"}\n"
"QComboBox QAbstractItemView  \n"
"{  \n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"    selection-background-color: #E49C97;\n"
"    color: #461C0A;  \n"
"    selection-color: #FFFFFF;\n"
"}\n"
"QComboBox QScrollBar::vertical\n"
"{\n"
"    margin: 9px 0px 9px 0px;\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/line_vertical.png);\n"
"    border: 0px; \n"
"    width: 9px;\n"
"}\n"
"QComboBox QScrollBar::handle:vertical {\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_vertical.png);\n"
"    min-height:10px;\n"
"}\n"
"QComboBox QScrollBar::handle:vertical:pressed \n"
"{\n"
"    border-image: url(:/picture_tools/scrollbar/pi"
                        "cture_tools/scrollbar_style/button_vertical.png); }\n"
"QComboBox QScrollBar::add-page:vertical \n"
"{\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/line_vertical.png);\n"
"}\n"
"QComboBox QScrollBar::sub-page:vertical \n"
"{\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/line_vertical.png);\n"
"}\n"
"QComboBox QScrollBar::sub-line:vertical \n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    height:9px\n"
"}\n"
"QComboBox QScrollBar::add-line:vertical \n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    height:9px\n"
"}\n"
"QComboBox QScrollBar::down-arrow:vertical\n"
"{\n"
"    image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/down.png);\n"
"}\n"
"QComboBox QScrollBar::up-arrow:vertical\n"
"{\n"
"    image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/up.png);\n"
"}\n"
"QComboBox QScrollBar::horizontal\n"
"{\n"
"    margin: 0px 9px 0px 9px;\n"
"   "
                        " border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/line_horizental.png);\n"
"    border: 0px;\n"
"    height: 9px;\n"
"}\n"
"QComboBox QScrollBar::handle:horizontal \n"
"{\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_horizental.png);\n"
"    min-width:10px;\n"
"}\n"
"QTableWidget QScrollBar::handle:horizontal:pressed\n"
"{\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTableWidget QScrollBar::add-page:horizontal \n"
"{\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTableWidget QScrollBar::sub-page:horizontal \n"
"{\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_horizental.png);\n"
"}\n"
"QComboBox QScrollBar::add-line:horizontal \n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:9px\n"
"}\n"
"QComboBox QScrollBar::sub-line:hori"
                        "zontal \n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:9px\n"
"}\n"
"QComboBox QScrollBar::left-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/left.png);\n"
"}\n"
"QTableWidget QScrollBar::right-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/right.png);\n"
"}"));
        comboBox_2->setEditable(false);
        comboBox_2->setMaxVisibleItems(7);
        comboBox_2->setMaxCount(2147483646);
        comboBox_2->setInsertPolicy(QComboBox::InsertAtBottom);
        comboBox_1 = new QComboBox(ToolsSetClass);
        comboBox_1->setObjectName(QStringLiteral("comboBox_1"));
        comboBox_1->setGeometry(QRect(40, 100, 200, 25));
        comboBox_1->setContextMenuPolicy(Qt::PreventContextMenu);
        comboBox_1->setAutoFillBackground(false);
        comboBox_1->setStyleSheet(QLatin1String("QComboBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    border-radius: 0px;\n"
"    padding: 1px 3px 1px 3px;\n"
"    min-width: 6px;\n"
"}\n"
"QComboBox:editable\n"
"{\n"
"    background: #FDEAD3;\n"
"}\n"
"QComboBox:!editable\n"
"{\n"
"    background: #FDEAD3;\n"
"}\n"
"QComboBox:!editable:on, QComboBox::drop-down:editable:on\n"
"{\n"
"    background: #FDEAD3;  \n"
"}\n"
"QComboBox::drop-down:editable\n"
"{\n"
"    background: #E49C97;\n"
"}\n"
"QComboBox::drop-down:editable\n"
"{\n"
"    background: #E49C97;\n"
"}\n"
"QComboBox::drop-down:editable\n"
"{\n"
"    background: #E49C97;\n"
"}\n"
"QComboBox::drop-down:!editable\n"
"{\n"
"    background: #E49C97;\n"
"}\n"
"QComboBox::drop-down:!editable\n"
"{\n"
"    background: #E49C97;\n"
"}\n"
"QComboBox::drop-down\n"
"{\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 15px;\n"
"    border-left-width: 1px;\n"
"    border-left-color: #804C47;\n"
"    border-left-style: solid;\n"
"    border-top-right-radius: 0px;\n"
""
                        "    border-bottom-right-radius: 0px;\n"
"}\n"
"QComboBox::down-arrow\n"
"{\n"
"    image: url(:/picture_tools/combobox/picture_tools/combobox_style/arrow.png);\n"
"}\n"
"QComboBox::down-arrow:on\n"
"{ \n"
"     image: url(:/picture_tools/combobox/picture_tools/combobox_style/arrow.png);\n"
"}\n"
"QComboBox QAbstractItemView  \n"
"{  \n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"    selection-background-color: #E49C97;\n"
"    color: #461C0A;  \n"
"    selection-color: #FFFFFF;\n"
"}\n"
"QComboBox QScrollBar::vertical\n"
"{\n"
"    margin: 9px 0px 9px 0px;\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/line_vertical.png);\n"
"    border: 0px; \n"
"    width: 9px;\n"
"}\n"
"QComboBox QScrollBar::handle:vertical {\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_vertical.png);\n"
"    min-height:10px;\n"
"}\n"
"QComboBox QScrollBar::handle:vertical:pressed \n"
"{\n"
"    border-image: url(:/picture_tools/scrollbar/pi"
                        "cture_tools/scrollbar_style/button_vertical.png); }\n"
"QComboBox QScrollBar::add-page:vertical \n"
"{\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/line_vertical.png);\n"
"}\n"
"QComboBox QScrollBar::sub-page:vertical \n"
"{\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/line_vertical.png);\n"
"}\n"
"QComboBox QScrollBar::sub-line:vertical \n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    height:9px\n"
"}\n"
"QComboBox QScrollBar::add-line:vertical \n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    height:9px\n"
"}\n"
"QComboBox QScrollBar::down-arrow:vertical\n"
"{\n"
"    image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/down.png);\n"
"}\n"
"QComboBox QScrollBar::up-arrow:vertical\n"
"{\n"
"    image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/up.png);\n"
"}\n"
"QComboBox QScrollBar::horizontal\n"
"{\n"
"    margin: 0px 9px 0px 9px;\n"
"   "
                        " border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/line_horizental.png);\n"
"    border: 0px;\n"
"    height: 9px;\n"
"}\n"
"QComboBox QScrollBar::handle:horizontal \n"
"{\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_horizental.png);\n"
"    min-width:10px;\n"
"}\n"
"QTableWidget QScrollBar::handle:horizontal:pressed\n"
"{\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTableWidget QScrollBar::add-page:horizontal \n"
"{\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTableWidget QScrollBar::sub-page:horizontal \n"
"{\n"
"    border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_horizental.png);\n"
"}\n"
"QComboBox QScrollBar::add-line:horizontal \n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:9px\n"
"}\n"
"QComboBox QScrollBar::sub-line:hori"
                        "zontal \n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:9px\n"
"}\n"
"QComboBox QScrollBar::left-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/left.png);\n"
"}\n"
"QTableWidget QScrollBar::right-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/right.png);\n"
"}"));
        comboBox_1->setEditable(false);
        comboBox_1->setMaxVisibleItems(7);
        comboBox_1->setMaxCount(2147483646);
        comboBox_1->setInsertPolicy(QComboBox::InsertAtBottom);
        pushButton_choose_1 = new QPushButton(ToolsSetClass);
        pushButton_choose_1->setObjectName(QStringLiteral("pushButton_choose_1"));
        pushButton_choose_1->setGeometry(QRect(90, 159, 33, 13));
        pushButton_choose_1->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_choose_2 = new QPushButton(ToolsSetClass);
        pushButton_choose_2->setObjectName(QStringLiteral("pushButton_choose_2"));
        pushButton_choose_2->setGeometry(QRect(90, 184, 33, 13));
        pushButton_choose_2->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_choose_3 = new QPushButton(ToolsSetClass);
        pushButton_choose_3->setObjectName(QStringLiteral("pushButton_choose_3"));
        pushButton_choose_3->setGeometry(QRect(90, 209, 33, 13));
        pushButton_choose_3->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_choose_4 = new QPushButton(ToolsSetClass);
        pushButton_choose_4->setObjectName(QStringLiteral("pushButton_choose_4"));
        pushButton_choose_4->setGeometry(QRect(90, 234, 33, 13));
        pushButton_choose_4->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_choose_5 = new QPushButton(ToolsSetClass);
        pushButton_choose_5->setObjectName(QStringLiteral("pushButton_choose_5"));
        pushButton_choose_5->setGeometry(QRect(90, 259, 33, 13));
        pushButton_choose_5->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_choose_6 = new QPushButton(ToolsSetClass);
        pushButton_choose_6->setObjectName(QStringLiteral("pushButton_choose_6"));
        pushButton_choose_6->setGeometry(QRect(90, 284, 33, 13));
        pushButton_choose_6->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_choose_7 = new QPushButton(ToolsSetClass);
        pushButton_choose_7->setObjectName(QStringLiteral("pushButton_choose_7"));
        pushButton_choose_7->setGeometry(QRect(90, 309, 33, 13));
        pushButton_choose_7->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_choose_8 = new QPushButton(ToolsSetClass);
        pushButton_choose_8->setObjectName(QStringLiteral("pushButton_choose_8"));
        pushButton_choose_8->setGeometry(QRect(90, 334, 33, 13));
        pushButton_choose_8->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        lineedit_program_2 = new QLineEdit(ToolsSetClass);
        lineedit_program_2->setObjectName(QStringLiteral("lineedit_program_2"));
        lineedit_program_2->setGeometry(QRect(140, 183, 163, 16));
        lineedit_program_2->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_program_2->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_program_2->setReadOnly(true);
        lineedit_program_3 = new QLineEdit(ToolsSetClass);
        lineedit_program_3->setObjectName(QStringLiteral("lineedit_program_3"));
        lineedit_program_3->setGeometry(QRect(140, 208, 163, 15));
        lineedit_program_3->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_program_3->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_program_3->setReadOnly(true);
        lineedit_program_4 = new QLineEdit(ToolsSetClass);
        lineedit_program_4->setObjectName(QStringLiteral("lineedit_program_4"));
        lineedit_program_4->setGeometry(QRect(140, 233, 163, 15));
        lineedit_program_4->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_program_4->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_program_4->setReadOnly(true);
        lineedit_program_5 = new QLineEdit(ToolsSetClass);
        lineedit_program_5->setObjectName(QStringLiteral("lineedit_program_5"));
        lineedit_program_5->setGeometry(QRect(140, 258, 163, 15));
        lineedit_program_5->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_program_5->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_program_5->setReadOnly(true);
        lineedit_program_6 = new QLineEdit(ToolsSetClass);
        lineedit_program_6->setObjectName(QStringLiteral("lineedit_program_6"));
        lineedit_program_6->setEnabled(true);
        lineedit_program_6->setGeometry(QRect(140, 283, 163, 15));
        lineedit_program_6->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_program_6->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_program_6->setReadOnly(true);
        lineedit_program_7 = new QLineEdit(ToolsSetClass);
        lineedit_program_7->setObjectName(QStringLiteral("lineedit_program_7"));
        lineedit_program_7->setEnabled(true);
        lineedit_program_7->setGeometry(QRect(140, 308, 163, 15));
        lineedit_program_7->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_program_7->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_program_7->setReadOnly(true);
        lineedit_program_8 = new QLineEdit(ToolsSetClass);
        lineedit_program_8->setObjectName(QStringLiteral("lineedit_program_8"));
        lineedit_program_8->setEnabled(true);
        lineedit_program_8->setGeometry(QRect(140, 333, 163, 15));
        lineedit_program_8->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_program_8->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_program_8->setReadOnly(true);
        checkBox = new QCheckBox(ToolsSetClass);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(40, 503, 20, 22));
        checkBox->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}"));
        pushButton_choose_9 = new QPushButton(ToolsSetClass);
        pushButton_choose_9->setObjectName(QStringLiteral("pushButton_choose_9"));
        pushButton_choose_9->setGeometry(QRect(319, 159, 33, 13));
        pushButton_choose_9->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_choose_10 = new QPushButton(ToolsSetClass);
        pushButton_choose_10->setObjectName(QStringLiteral("pushButton_choose_10"));
        pushButton_choose_10->setGeometry(QRect(319, 184, 33, 13));
        pushButton_choose_10->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_choose_11 = new QPushButton(ToolsSetClass);
        pushButton_choose_11->setObjectName(QStringLiteral("pushButton_choose_11"));
        pushButton_choose_11->setGeometry(QRect(319, 209, 33, 13));
        pushButton_choose_11->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_choose_12 = new QPushButton(ToolsSetClass);
        pushButton_choose_12->setObjectName(QStringLiteral("pushButton_choose_12"));
        pushButton_choose_12->setGeometry(QRect(319, 234, 33, 13));
        pushButton_choose_12->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_choose_13 = new QPushButton(ToolsSetClass);
        pushButton_choose_13->setObjectName(QStringLiteral("pushButton_choose_13"));
        pushButton_choose_13->setGeometry(QRect(319, 259, 33, 13));
        pushButton_choose_13->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_choose_14 = new QPushButton(ToolsSetClass);
        pushButton_choose_14->setObjectName(QStringLiteral("pushButton_choose_14"));
        pushButton_choose_14->setGeometry(QRect(319, 284, 33, 13));
        pushButton_choose_14->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_choose_15 = new QPushButton(ToolsSetClass);
        pushButton_choose_15->setObjectName(QStringLiteral("pushButton_choose_15"));
        pushButton_choose_15->setGeometry(QRect(319, 309, 33, 13));
        pushButton_choose_15->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_choose_16 = new QPushButton(ToolsSetClass);
        pushButton_choose_16->setObjectName(QStringLiteral("pushButton_choose_16"));
        pushButton_choose_16->setGeometry(QRect(319, 334, 33, 13));
        pushButton_choose_16->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));

        retranslateUi(ToolsSetClass);

        QMetaObject::connectSlotsByName(ToolsSetClass);
    } // setupUi

    void retranslateUi(QDialog *ToolsSetClass)
    {
        ToolsSetClass->setWindowTitle(QApplication::translate("ToolsSetClass", "\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_apply->setText(QString());
        pushButton_cancel->setText(QString());
        lineedit_program_1->setText(QString());
        comboBox_1->clear();
        comboBox_1->insertItems(0, QStringList()
         << QApplication::translate("ToolsSetClass", "\351\255\224\346\263\225\345\260\221\345\245\263\343\200\200\343\203\201\343\203\216", Q_NULLPTR)
         << QApplication::translate("ToolsSetClass", "\343\202\275\343\203\274\343\202\265\343\203\251\343\203\274\343\200\200\343\203\201\343\203\216", Q_NULLPTR)
         << QApplication::translate("ToolsSetClass", "\343\202\254\343\203\263\343\203\212\343\203\274\343\200\200\343\203\236\343\203\244", Q_NULLPTR)
         << QApplication::translate("ToolsSetClass", "\343\203\220\343\203\274\343\202\265\343\203\274\343\202\253\343\203\274\343\200\200\343\203\241\343\202\260", Q_NULLPTR)
         << QApplication::translate("ToolsSetClass", "\343\202\263\343\202\263\343\202\242\357\274\210\345\271\274\345\260\221\346\234\237\357\274\211", Q_NULLPTR)
        );
        pushButton_choose_1->setText(QString());
        pushButton_choose_2->setText(QString());
        pushButton_choose_3->setText(QString());
        pushButton_choose_4->setText(QString());
        pushButton_choose_5->setText(QString());
        pushButton_choose_6->setText(QString());
        pushButton_choose_7->setText(QString());
        pushButton_choose_8->setText(QString());
        lineedit_program_2->setText(QString());
        lineedit_program_3->setText(QString());
        lineedit_program_4->setText(QString());
        lineedit_program_5->setText(QString());
        lineedit_program_6->setText(QString());
        lineedit_program_7->setText(QString());
        lineedit_program_8->setText(QString());
        checkBox->setText(QString());
        pushButton_choose_9->setText(QString());
        pushButton_choose_10->setText(QString());
        pushButton_choose_11->setText(QString());
        pushButton_choose_12->setText(QString());
        pushButton_choose_13->setText(QString());
        pushButton_choose_14->setText(QString());
        pushButton_choose_15->setText(QString());
        pushButton_choose_16->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ToolsSetClass: public Ui_ToolsSetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLSSET_H
