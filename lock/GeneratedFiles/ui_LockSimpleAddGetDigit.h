/********************************************************************************
** Form generated from reading UI file 'LockSimpleAddGetDigit.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCKSIMPLEADDGETDIGIT_H
#define UI_LOCKSIMPLEADDGETDIGIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_LockSimpleAddGetDigitClass
{
public:
    QPushButton *pushButton_apply;
    QPushButton *pushButton_cancel;
    QListWidget *listWidget_1;
    QSpinBox *spinBox_1;
    QPushButton *pushButton_list_2;
    QPushButton *pushButton_list_1;
    QPushButton *pushButton_list_3;
    QPushButton *pushButton_list_4;
    QSpinBox *spinBox_2;

    void setupUi(QDialog *LockSimpleAddGetDigitClass)
    {
        if (LockSimpleAddGetDigitClass->objectName().isEmpty())
            LockSimpleAddGetDigitClass->setObjectName(QStringLiteral("LockSimpleAddGetDigitClass"));
        LockSimpleAddGetDigitClass->resize(400, 400);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_lock/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        LockSimpleAddGetDigitClass->setWindowIcon(icon);
        LockSimpleAddGetDigitClass->setWindowOpacity(5);
        pushButton_apply = new QPushButton(LockSimpleAddGetDigitClass);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(65, 345, 60, 30));
        pushButton_apply->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_10.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_10.png);"));
        pushButton_cancel = new QPushButton(LockSimpleAddGetDigitClass);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(250, 345, 60, 30));
        pushButton_cancel->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_11.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_11.png);"));
        listWidget_1 = new QListWidget(LockSimpleAddGetDigitClass);
        listWidget_1->setObjectName(QStringLiteral("listWidget_1"));
        listWidget_1->setGeometry(QRect(40, 110, 141, 221));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        listWidget_1->setFont(font);
        listWidget_1->setContextMenuPolicy(Qt::NoContextMenu);
        listWidget_1->setStyleSheet(QString::fromUtf8("QListWidget\n"
"{\n"
"    background:rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}\n"
"QListWidget::Item:hover\n"
"{\n"
"    background:#C0FDEAD3;\n"
"}\n"
"QListWidget::item:selected\n"
"{\n"
"    background:#C0FDEAD3;\n"
"}\n"
"QListWidget::item:selected:!active\n"
"{\n"
"    background:#C0FDEAD3;\n"
"}\n"
"/*\346\273\232\345\212\250\346\235\241*/\n"
"QListWidget QScrollBar::vertical\n"
"{\n"
"    margin: 15px 0px 15px 0px;\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png); \n"
"    border: 0px;\n"
"    width: 15px;\n"
"}\n"
"QListWidget QScrollBar::handle:vertical\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_vertical.png);\n"
"    min-height:50px;\n"
"}\n"
"QListWidget QScrollBar::handle:vertical:pressed \n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_vertical.png);\n"
"}\n"
"QListWidget QScrollBar::add-page:vertical\n"
"{\n"
"    border-image: u"
                        "rl(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png);\n"
"}\n"
"QListWidget QScrollBar::sub-page:vertical\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png);\n"
"}\n"
"QListWidget QScrollBar::sub-line:vertical\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    height:15px\n"
"}\n"
"QListWidget QScrollBar::add-line:vertical\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    height:15px\n"
"}\n"
"QListWidget QScrollBar::down-arrow:vertical\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/down.png);\n"
"}\n"
"QListWidget QScrollBar::up-arrow:vertical\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/up.png);\n"
"}\n"
"QListWidget QScrollBar::horizontal\n"
"{\n"
"    margin: 0px 15px 0px 15px;\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_horizental.png); \n"
"    border: 0px; \n"
""
                        "    height: 15px;\n"
"}\n"
"QListWidget QScrollBar::handle:horizontal\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"    min-width:50px;\n"
"}\n"
"QTableWidget QScrollBar::handle:horizontal:pressed\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTreeView QScrollBar::add-page:horizontal\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTreeView QScrollBar::sub-page:horizontal\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTreeView QScrollBar::add-line:horizontal\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:15px\n"
"}\n"
"QTreeView QScrollBar::sub-line:horizontal\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:15px\n"
"}\n"
"QTreeView QScrollBar::left"
                        "-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/left.png);\n"
"}\n"
"QTreeView QScrollBar::right-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/right.png);\n"
"}"));
        listWidget_1->setBatchSize(16);
        spinBox_1 = new QSpinBox(LockSimpleAddGetDigitClass);
        spinBox_1->setObjectName(QStringLiteral("spinBox_1"));
        spinBox_1->setGeometry(QRect(220, 222, 151, 22));
        spinBox_1->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_1->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/up_button_no_background.png);     \n"
"    background: #00FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/down_button_no_background.png); \n"
"    background: #00FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/up_button_no_background.png);   \n"
"    background: #00FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/down_button_no_background.png); \n"
"    background: #00FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #00FFFFFF;\n"
"}"));
        spinBox_1->setMinimum(-2147483647);
        spinBox_1->setMaximum(2147483647);
        spinBox_1->setValue(0);
        spinBox_1->setDisplayIntegerBase(10);
        pushButton_list_2 = new QPushButton(LockSimpleAddGetDigitClass);
        pushButton_list_2->setObjectName(QStringLiteral("pushButton_list_2"));
        pushButton_list_2->setGeometry(QRect(310, 255, 15, 15));
        pushButton_list_2->setStyleSheet(QStringLiteral("border-image: url(:/icon/mainicon/picture_lock/icon/dialog_setting_remove_item.png);"));
        pushButton_list_1 = new QPushButton(LockSimpleAddGetDigitClass);
        pushButton_list_1->setObjectName(QStringLiteral("pushButton_list_1"));
        pushButton_list_1->setGeometry(QRect(230, 255, 15, 15));
        pushButton_list_1->setStyleSheet(QStringLiteral("border-image: url(:/icon/mainicon/picture_lock/icon/dialog_setting_add_item.png);"));
        pushButton_list_3 = new QPushButton(LockSimpleAddGetDigitClass);
        pushButton_list_3->setObjectName(QStringLiteral("pushButton_list_3"));
        pushButton_list_3->setGeometry(QRect(350, 255, 15, 15));
        pushButton_list_3->setStyleSheet(QStringLiteral("border-image: url(:/icon/mainicon/picture_lock/icon/dialog_setting_remove_all_item.png);"));
        pushButton_list_4 = new QPushButton(LockSimpleAddGetDigitClass);
        pushButton_list_4->setObjectName(QStringLiteral("pushButton_list_4"));
        pushButton_list_4->setGeometry(QRect(270, 255, 15, 15));
        pushButton_list_4->setStyleSheet(QStringLiteral("border-image: url(:/icon/mainicon/picture_lock/icon/dialog_setting_edit_item.png);"));
        spinBox_2 = new QSpinBox(LockSimpleAddGetDigitClass);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(306, 102, 65, 22));
        spinBox_2->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/up_button_no_background.png);     \n"
"    background: #00FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/down_button_no_background.png); \n"
"    background: #00FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/up_button_no_background.png);   \n"
"    background: #00FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/down_button_no_background.png); \n"
"    background: #00FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #00FFFFFF;\n"
"}"));
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(16);
        spinBox_2->setValue(16);
        spinBox_2->setDisplayIntegerBase(10);

        retranslateUi(LockSimpleAddGetDigitClass);

        QMetaObject::connectSlotsByName(LockSimpleAddGetDigitClass);
    } // setupUi

    void retranslateUi(QDialog *LockSimpleAddGetDigitClass)
    {
        LockSimpleAddGetDigitClass->setWindowTitle(QApplication::translate("LockSimpleAddGetDigitClass", "\345\212\240\345\207\217\346\225\260\351\207\217\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_apply->setText(QString());
        pushButton_cancel->setText(QString());
        pushButton_list_2->setText(QString());
        pushButton_list_1->setText(QString());
        pushButton_list_3->setText(QString());
        pushButton_list_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LockSimpleAddGetDigitClass: public Ui_LockSimpleAddGetDigitClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCKSIMPLEADDGETDIGIT_H
