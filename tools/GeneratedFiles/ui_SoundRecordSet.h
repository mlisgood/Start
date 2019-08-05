/********************************************************************************
** Form generated from reading UI file 'SoundRecordSet.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOUNDRECORDSET_H
#define UI_SOUNDRECORDSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SoundRecordSetClass
{
public:
    QPushButton *pushButton_apply;
    QPushButton *pushButton_cancel;
    QComboBox *comboBox_1;
    QComboBox *comboBox_2;
    QPushButton *pushButton_choose;
    QLineEdit *lineedit;

    void setupUi(QDialog *SoundRecordSetClass)
    {
        if (SoundRecordSetClass->objectName().isEmpty())
            SoundRecordSetClass->setObjectName(QStringLiteral("SoundRecordSetClass"));
        SoundRecordSetClass->resize(400, 400);
        QIcon icon;
        icon.addFile(QStringLiteral(":/picture_tools/icon/picture_tools/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        SoundRecordSetClass->setWindowIcon(icon);
        SoundRecordSetClass->setWindowOpacity(5);
        pushButton_apply = new QPushButton(SoundRecordSetClass);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(100, 335, 41, 23));
        pushButton_apply->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_cancel = new QPushButton(SoundRecordSetClass);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(260, 335, 41, 23));
        pushButton_cancel->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        comboBox_1 = new QComboBox(SoundRecordSetClass);
        comboBox_1->setObjectName(QStringLiteral("comboBox_1"));
        comboBox_1->setGeometry(QRect(40, 114, 250, 25));
        QFont font;
        font.setKerning(true);
        comboBox_1->setFont(font);
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
        comboBox_1->setInputMethodHints(Qt::ImhNone);
        comboBox_1->setEditable(false);
        comboBox_1->setMaxVisibleItems(7);
        comboBox_1->setMaxCount(2147483646);
        comboBox_1->setInsertPolicy(QComboBox::InsertAtBottom);
        comboBox_2 = new QComboBox(SoundRecordSetClass);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(40, 200, 200, 25));
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
        pushButton_choose = new QPushButton(SoundRecordSetClass);
        pushButton_choose->setObjectName(QStringLiteral("pushButton_choose"));
        pushButton_choose->setGeometry(QRect(330, 286, 35, 20));
        pushButton_choose->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        lineedit = new QLineEdit(SoundRecordSetClass);
        lineedit->setObjectName(QStringLiteral("lineedit"));
        lineedit->setGeometry(QRect(40, 289, 280, 15));
        lineedit->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit->setReadOnly(true);

        retranslateUi(SoundRecordSetClass);

        comboBox_1->setCurrentIndex(-1);
        comboBox_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SoundRecordSetClass);
    } // setupUi

    void retranslateUi(QDialog *SoundRecordSetClass)
    {
        SoundRecordSetClass->setWindowTitle(QApplication::translate("SoundRecordSetClass", "\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_apply->setText(QString());
        pushButton_cancel->setText(QString());
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("SoundRecordSetClass", "mono", Q_NULLPTR)
         << QApplication::translate("SoundRecordSetClass", "stereo", Q_NULLPTR)
        );
        pushButton_choose->setText(QString());
        lineedit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SoundRecordSetClass: public Ui_SoundRecordSetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOUNDRECORDSET_H
