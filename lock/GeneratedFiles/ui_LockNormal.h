/********************************************************************************
** Form generated from reading UI file 'LockNormal.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCKNORMAL_H
#define UI_LOCKNORMAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LockNormalClass
{
public:
    QPushButton *pushButton_select_1;
    QPushButton *pushButton_select_2;
    QWidget *centralWidget;
    QLabel *label;
    QComboBox *comboBox_1;
    QTextEdit *textEdit;

    void setupUi(QDialog *LockNormalClass)
    {
        if (LockNormalClass->objectName().isEmpty())
            LockNormalClass->setObjectName(QStringLiteral("LockNormalClass"));
        LockNormalClass->resize(400, 400);
        LockNormalClass->setAcceptDrops(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_lock/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        LockNormalClass->setWindowIcon(icon);
        pushButton_select_1 = new QPushButton(LockNormalClass);
        pushButton_select_1->setObjectName(QStringLiteral("pushButton_select_1"));
        pushButton_select_1->setGeometry(QRect(65, 350, 60, 30));
        pushButton_select_1->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_10.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_10.png);"));
        pushButton_select_2 = new QPushButton(LockNormalClass);
        pushButton_select_2->setObjectName(QStringLiteral("pushButton_select_2"));
        pushButton_select_2->setGeometry(QRect(250, 350, 60, 30));
        pushButton_select_2->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_11.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_11.png);"));
        centralWidget = new QWidget(LockNormalClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setGeometry(QRect(0, 0, 400, 400));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 400, 400));
        label->setPixmap(QPixmap(QString::fromUtf8("picture/lock_normal_dialog/dialog.png")));
        comboBox_1 = new QComboBox(centralWidget);
        comboBox_1->setObjectName(QStringLiteral("comboBox_1"));
        comboBox_1->setGeometry(QRect(50, 120, 300, 25));
        comboBox_1->setContextMenuPolicy(Qt::NoContextMenu);
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
"    background: #00FDEAD3;\n"
"}\n"
"QComboBox:!editable\n"
"{\n"
"    background: #00FDEAD3;\n"
"}\n"
"QComboBox:!editable:on, QComboBox::drop-down:editable:on\n"
"{\n"
"    background: #00FDEAD3;  \n"
"}\n"
"QComboBox::drop-down:editable\n"
"{\n"
"    background: #00E49C97;\n"
"}\n"
"QComboBox::drop-down:editable\n"
"{\n"
"    background: #00E49C97;\n"
"}\n"
"QComboBox::drop-down:editable\n"
"{\n"
"    background: #00E49C97;\n"
"}\n"
"QComboBox::drop-down:!editable\n"
"{\n"
"    background: #00E49C97;\n"
"}\n"
"QComboBox::drop-down:!editable\n"
"{\n"
"    background: #00E49C97;\n"
"}\n"
"QComboBox::drop-down\n"
"{\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 15px;\n"
"    border-left-width: 1px;\n"
"    border-left-color: #804C47;\n"
"    border-left-style: solid;\n"
"    border-top-right-r"
                        "adius: 0px;\n"
"    border-bottom-right-radius: 0px;\n"
"}\n"
"QComboBox::down-arrow\n"
"{\n"
"    image: url(:/picture_lock/combobox/picture_lock/combobox_style/arrow.png);\n"
"}\n"
"QComboBox::down-arrow:on\n"
"{ \n"
"     image: url(:/picture_lock/combobox/picture_lock/combobox_style/arrow.png);\n"
"}\n"
"QComboBox QAbstractItemView  \n"
"{  \n"
"    border: 1px solid #804C47;\n"
"    background: #F8F5E2;\n"
"    selection-background-color: #E49C97;\n"
"    color: #461C0A;  \n"
"    selection-color: #FFFFFF;\n"
"}\n"
"QComboBox QScrollBar::vertical\n"
"{\n"
"    margin: 9px 0px 9px 0px;\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png);\n"
"    border: 0px; \n"
"    width: 9px;\n"
"}\n"
"QComboBox QScrollBar::handle:vertical {\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_vertical.png);\n"
"    min-height:10px;\n"
"}\n"
"QComboBox QScrollBar::handle:vertical:pressed \n"
"{\n"
"    border-image: url(:/picture_lock/scrol"
                        "lbar/picture_lock/scrollbar_style/button_vertical.png); }\n"
"QComboBox QScrollBar::add-page:vertical \n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png);\n"
"}\n"
"QComboBox QScrollBar::sub-page:vertical \n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png);\n"
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
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/down.png);\n"
"}\n"
"QComboBox QScrollBar::up-arrow:vertical\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/up.png);\n"
"}\n"
"QComboBox QScrollBar::horizontal\n"
"{\n"
"    margin: 0px 9px 0px 9px;\n"
"    b"
                        "order-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_horizental.png);\n"
"    border: 0px;\n"
"    height: 9px;\n"
"}\n"
"QComboBox QScrollBar::handle:horizontal \n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"    min-width:10px;\n"
"}\n"
"QTableWidget QScrollBar::handle:horizontal:pressed\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTableWidget QScrollBar::add-page:horizontal \n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTableWidget QScrollBar::sub-page:horizontal \n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"}\n"
"QComboBox QScrollBar::add-line:horizontal \n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:9px\n"
"}\n"
"QComboBox QScrollBar::sub-line:horizontal \n"
""
                        "{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:9px\n"
"}\n"
"QComboBox QScrollBar::left-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/left.png);\n"
"}\n"
"QTableWidget QScrollBar::right-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/right.png);\n"
"}"));
        comboBox_1->setEditable(false);
        comboBox_1->setMaxVisibleItems(7);
        comboBox_1->setMaxCount(2147483646);
        comboBox_1->setInsertPolicy(QComboBox::InsertAtBottom);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setEnabled(false);
        textEdit->setGeometry(QRect(50, 170, 300, 160));
        textEdit->setContextMenuPolicy(Qt::NoContextMenu);
        textEdit->setStyleSheet(QLatin1String("QTextEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}\n"
"QTextEdit QScrollBar::vertical\n"
"{\n"
"    margin: 15px 0px 15px 0px;\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png); \n"
"    border: 0px; \n"
"    width: 15px;\n"
"}\n"
"QTextEdit QScrollBar::handle:vertical\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_vertical.png);\n"
"    min-height:50px;\n"
"}\n"
"QTextEdit QScrollBar::handle:vertical:pressed\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_vertical.png);\n"
"}\n"
"QTextEdit QScrollBar::add-page:vertical\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png);\n"
"}\n"
"QTextEdit QScrollBar::sub-page:vertical\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png);\n"
"}\n"
"QTextEdit QScrollBar::sub-line:vert"
                        "ical\n"
"{\n"
"    subcontrol-origin: margin; border: 0px solid black; \n"
"    height:15px\n"
"}\n"
"QTextEdit QScrollBar::add-line:vertical\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    height: 15px\n"
"}\n"
"QTextEdit QScrollBar::down-arrow:vertical\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/down.png);\n"
"}\n"
"QTextEdit QScrollBar::up-arrow:vertical\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/up.png);\n"
"}\n"
"QTextEdit QScrollBar::horizontal\n"
"{\n"
"    margin: 0px 15px 0px 15px;\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_horizental.png); \n"
"    border: 0px;\n"
"    height: 15px;\n"
"}\n"
"QTextEdit QScrollBar::handle:horizontal\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"    min-width:50px;\n"
"}\n"
"QTextEdit QScrollBar::handle:horizontal:pressed \n"
"{\n"
"    border-image: url(:/p"
                        "icture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTextEdit QScrollBar::add-page:horizontal\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_horizental.png);\n"
"}\n"
"QTextEdit QScrollBar::sub-page:horizontal\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_horizental.png);\n"
"}\n"
"QTextEdit QScrollBar::add-line:horizontal\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:15px\n"
"}\n"
"QTextEdit QScrollBar::sub-line:horizontal\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:15px\n"
"}\n"
"QTextEdit QScrollBar::left-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/left.png);\n"
"}\n"
"QTextEdit QScrollBar::right-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/right.png);\n"
"}"));
        textEdit->setUndoRedoEnabled(false);
        textEdit->setReadOnly(true);
        textEdit->setAcceptRichText(false);
        centralWidget->raise();
        pushButton_select_1->raise();
        pushButton_select_2->raise();

        retranslateUi(LockNormalClass);

        QMetaObject::connectSlotsByName(LockNormalClass);
    } // setupUi

    void retranslateUi(QDialog *LockNormalClass)
    {
        LockNormalClass->setWindowTitle(QApplication::translate("LockNormalClass", "\345\270\270\350\247\204\345\212\240\345\257\206", Q_NULLPTR));
        pushButton_select_1->setText(QString());
        pushButton_select_2->setText(QString());
        label->setText(QString());
        comboBox_1->clear();
        comboBox_1->insertItems(0, QStringList()
         << QApplication::translate("LockNormalClass", "DES", Q_NULLPTR)
         << QApplication::translate("LockNormalClass", "2-Key 3DES", Q_NULLPTR)
         << QApplication::translate("LockNormalClass", "3-Key 3DES", Q_NULLPTR)
         << QApplication::translate("LockNormalClass", "AES-128", Q_NULLPTR)
         << QApplication::translate("LockNormalClass", "AES-192", Q_NULLPTR)
         << QApplication::translate("LockNormalClass", "AES-256", Q_NULLPTR)
         << QApplication::translate("LockNormalClass", "RSA", Q_NULLPTR)
         << QApplication::translate("LockNormalClass", "ECC", Q_NULLPTR)
         << QApplication::translate("LockNormalClass", "MD4", Q_NULLPTR)
         << QApplication::translate("LockNormalClass", "MD5", Q_NULLPTR)
         << QApplication::translate("LockNormalClass", "SHA-1", Q_NULLPTR)
         << QApplication::translate("LockNormalClass", "SHA-2", Q_NULLPTR)
         << QApplication::translate("LockNormalClass", "SHA-3", Q_NULLPTR)
         << QApplication::translate("LockNormalClass", "Keccak", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class LockNormalClass: public Ui_LockNormalClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCKNORMAL_H
