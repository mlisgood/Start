/********************************************************************************
** Form generated from reading UI file 'ToolsSetExtra.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLSSETEXTRA_H
#define UI_TOOLSSETEXTRA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ToolsSetExtraClass
{
public:
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QPushButton *pushButton_apply;
    QPushButton *pushButton_cancel;
    QComboBox *comboBox_3;
    QComboBox *comboBox_1;
    QSpinBox *spinBox_1;
    QCheckBox *checkBox;
    QSpinBox *spinBox_2;
    QComboBox *comboBox_2;
    QSpinBox *spinBox_5;

    void setupUi(QDialog *ToolsSetExtraClass)
    {
        if (ToolsSetExtraClass->objectName().isEmpty())
            ToolsSetExtraClass->setObjectName(QStringLiteral("ToolsSetExtraClass"));
        ToolsSetExtraClass->resize(400, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/picture_tools/icon/picture_tools/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        ToolsSetExtraClass->setWindowIcon(icon);
        ToolsSetExtraClass->setWindowOpacity(5);
        spinBox_3 = new QSpinBox(ToolsSetExtraClass);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setGeometry(QRect(69, 440, 50, 22));
        spinBox_3->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_3->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_3->setMaximum(9999);
        spinBox_4 = new QSpinBox(ToolsSetExtraClass);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setGeometry(QRect(235, 440, 50, 22));
        spinBox_4->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_4->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_4->setMaximum(9999);
        pushButton_apply = new QPushButton(ToolsSetExtraClass);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(100, 536, 41, 23));
        pushButton_apply->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_cancel = new QPushButton(ToolsSetExtraClass);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(260, 536, 41, 23));
        pushButton_cancel->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        comboBox_3 = new QComboBox(ToolsSetExtraClass);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(40, 378, 250, 25));
        comboBox_3->setContextMenuPolicy(Qt::PreventContextMenu);
        comboBox_3->setAutoFillBackground(false);
        comboBox_3->setStyleSheet(QLatin1String("QComboBox\n"
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
        comboBox_3->setEditable(false);
        comboBox_3->setMaxVisibleItems(7);
        comboBox_3->setMaxCount(2147483646);
        comboBox_3->setInsertPolicy(QComboBox::InsertAtBottom);
        comboBox_1 = new QComboBox(ToolsSetExtraClass);
        comboBox_1->setObjectName(QStringLiteral("comboBox_1"));
        comboBox_1->setGeometry(QRect(40, 158, 200, 25));
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
        spinBox_1 = new QSpinBox(ToolsSetExtraClass);
        spinBox_1->setObjectName(QStringLiteral("spinBox_1"));
        spinBox_1->setGeometry(QRect(40, 102, 50, 22));
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
        spinBox_1->setMaximum(10);
        spinBox_1->setValue(10);
        checkBox = new QCheckBox(ToolsSetExtraClass);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(40, 223, 20, 20));
        checkBox->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}"));
        spinBox_2 = new QSpinBox(ToolsSetExtraClass);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(40, 254, 50, 22));
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
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(3600);
        spinBox_2->setValue(1);
        comboBox_2 = new QComboBox(ToolsSetExtraClass);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(40, 314, 200, 25));
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
        spinBox_5 = new QSpinBox(ToolsSetExtraClass);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setGeometry(QRect(40, 498, 50, 22));
        spinBox_5->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_5->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_5->setMaximum(10);
        spinBox_5->setValue(10);

        retranslateUi(ToolsSetExtraClass);

        comboBox_3->setCurrentIndex(0);
        comboBox_1->setCurrentIndex(1);
        comboBox_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ToolsSetExtraClass);
    } // setupUi

    void retranslateUi(QDialog *ToolsSetExtraClass)
    {
        ToolsSetExtraClass->setWindowTitle(QApplication::translate("ToolsSetExtraClass", "\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_apply->setText(QString());
        pushButton_cancel->setText(QString());
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("ToolsSetExtraClass", "\343\200\214\346\231\256\351\200\232\343\200\215\344\270\272150*250\357\274\214\343\200\214\347\211\271\345\210\245\343\200\215\344\270\272100*100", Q_NULLPTR)
         << QApplication::translate("ToolsSetExtraClass", "\343\200\214\346\231\256\351\200\232\343\200\215\344\270\272100*167\357\274\214\343\200\214\347\211\271\345\210\245\343\200\215\344\270\27275*75", Q_NULLPTR)
         << QApplication::translate("ToolsSetExtraClass", "\343\200\214\346\231\256\351\200\232\343\200\215\344\270\27275*125\357\274\214\343\200\214\347\211\271\345\210\245\343\200\215\344\270\27250*50", Q_NULLPTR)
         << QApplication::translate("ToolsSetExtraClass", "\343\200\214\346\231\256\351\200\232\343\200\215\344\270\27250*83\357\274\214\343\200\214\347\211\271\345\210\245\343\200\215\344\270\27225*25", Q_NULLPTR)
        );
        comboBox_1->clear();
        comboBox_1->insertItems(0, QStringList()
         << QApplication::translate("ToolsSetExtraClass", "150*250", Q_NULLPTR)
         << QApplication::translate("ToolsSetExtraClass", "100*167", Q_NULLPTR)
         << QApplication::translate("ToolsSetExtraClass", "75*125", Q_NULLPTR)
         << QApplication::translate("ToolsSetExtraClass", "50*83", Q_NULLPTR)
        );
        checkBox->setText(QString());
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("ToolsSetExtraClass", "\357\274\210\346\231\256\351\200\232\357\274\211\351\255\224\346\263\225\345\260\221\345\245\263\343\200\200\343\203\201\343\203\216", Q_NULLPTR)
         << QApplication::translate("ToolsSetExtraClass", "\357\274\210\346\231\256\351\200\232\357\274\211\343\202\275\343\203\274\343\202\265\343\203\251\343\203\274\343\200\200\343\203\201\343\203\216", Q_NULLPTR)
         << QApplication::translate("ToolsSetExtraClass", "\357\274\210\346\231\256\351\200\232\357\274\211\343\202\254\343\203\263\343\203\212\343\203\274\343\200\200\343\203\236\343\203\244", Q_NULLPTR)
         << QApplication::translate("ToolsSetExtraClass", "\357\274\210\346\231\256\351\200\232\357\274\211\343\203\220\343\203\274\343\202\265\343\203\274\343\202\253\343\203\274\343\200\200\343\203\241\343\202\260", Q_NULLPTR)
         << QApplication::translate("ToolsSetExtraClass", "\357\274\210\346\231\256\351\200\232\357\274\211\343\202\263\343\202\263\343\202\242\357\274\210\345\271\274\345\260\221\346\234\237\357\274\211", Q_NULLPTR)
         << QApplication::translate("ToolsSetExtraClass", "\357\274\210\347\211\271\345\210\245\357\274\211\343\202\263\343\202\263\343\202\242\343\201\250\343\203\201\343\203\216", Q_NULLPTR)
         << QApplication::translate("ToolsSetExtraClass", "\357\274\210\347\211\271\345\210\245\357\274\211\343\203\206\343\202\243\343\203\203\343\203\224\343\203\274", Q_NULLPTR)
         << QApplication::translate("ToolsSetExtraClass", "\357\274\210\347\211\271\345\210\245\357\274\211\343\201\252\343\201\227", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class ToolsSetExtraClass: public Ui_ToolsSetExtraClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLSSETEXTRA_H
