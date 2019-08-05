/********************************************************************************
** Form generated from reading UI file 'LockNormalHashCalculate.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCKNORMALHASHCALCULATE_H
#define UI_LOCKNORMALHASHCALCULATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LockNormalHashCalculateClass
{
public:
    QLabel *label_chara_1;
    QLabel *label_chara_2;
    QLabel *label_margin;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label_background;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_1;
    QComboBox *comboBox_1;
    QComboBox *comboBox_2;
    QPushButton *pushButton_4;

    void setupUi(QDialog *LockNormalHashCalculateClass)
    {
        if (LockNormalHashCalculateClass->objectName().isEmpty())
            LockNormalHashCalculateClass->setObjectName(QStringLiteral("LockNormalHashCalculateClass"));
        LockNormalHashCalculateClass->resize(400, 600);
        LockNormalHashCalculateClass->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_lock/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        LockNormalHashCalculateClass->setWindowIcon(icon);
        LockNormalHashCalculateClass->setWindowOpacity(5);
        label_chara_1 = new QLabel(LockNormalHashCalculateClass);
        label_chara_1->setObjectName(QStringLiteral("label_chara_1"));
        label_chara_1->setGeometry(QRect(0, 0, 400, 400));
        label_chara_2 = new QLabel(LockNormalHashCalculateClass);
        label_chara_2->setObjectName(QStringLiteral("label_chara_2"));
        label_chara_2->setGeometry(QRect(0, 0, 400, 400));
        label_margin = new QLabel(LockNormalHashCalculateClass);
        label_margin->setObjectName(QStringLiteral("label_margin"));
        label_margin->setGeometry(QRect(0, 0, 400, 600));
        label_margin->setPixmap(QPixmap(QString::fromUtf8("picture_lock/lock_margin/margin.png")));
        pushButton_1 = new QPushButton(LockNormalHashCalculateClass);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setGeometry(QRect(43, 530, 100, 30));
        pushButton_1->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_19.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_19.png);"));
        pushButton_2 = new QPushButton(LockNormalHashCalculateClass);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(243, 530, 100, 30));
        pushButton_2->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_18.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_18.png);"));
        pushButton_3 = new QPushButton(LockNormalHashCalculateClass);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(243, 560, 100, 30));
        pushButton_3->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_3.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_3.png);"));
        label_background = new QLabel(LockNormalHashCalculateClass);
        label_background->setObjectName(QStringLiteral("label_background"));
        label_background->setGeometry(QRect(0, 0, 400, 600));
        label_background->setFrameShape(QFrame::NoFrame);
        label_background->setPixmap(QPixmap(QString::fromUtf8("picture_lock/hash_calculate_background/background_1.png")));
        lineEdit_2 = new QLineEdit(LockNormalHashCalculateClass);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(138, 474, 221, 20));
        lineEdit_2->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_2->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        lineEdit_2->setInputMethodHints(Qt::ImhNone);
        lineEdit_2->setMaxLength(32767);
        lineEdit_1 = new QLineEdit(LockNormalHashCalculateClass);
        lineEdit_1->setObjectName(QStringLiteral("lineEdit_1"));
        lineEdit_1->setGeometry(QRect(138, 445, 221, 20));
        lineEdit_1->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_1->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        lineEdit_1->setInputMethodHints(Qt::ImhNone);
        lineEdit_1->setMaxLength(32767);
        lineEdit_1->setReadOnly(false);
        comboBox_1 = new QComboBox(LockNormalHashCalculateClass);
        comboBox_1->setObjectName(QStringLiteral("comboBox_1"));
        comboBox_1->setGeometry(QRect(138, 416, 221, 20));
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
        comboBox_2 = new QComboBox(LockNormalHashCalculateClass);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(138, 503, 221, 20));
        comboBox_2->setContextMenuPolicy(Qt::NoContextMenu);
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
        comboBox_2->setEditable(false);
        comboBox_2->setMaxVisibleItems(7);
        comboBox_2->setMaxCount(2147483646);
        comboBox_2->setInsertPolicy(QComboBox::InsertAtBottom);
        pushButton_4 = new QPushButton(LockNormalHashCalculateClass);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(43, 560, 100, 30));
        pushButton_4->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_20.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_20.png);"));
        label_background->raise();
        label_chara_2->raise();
        label_chara_1->raise();
        label_margin->raise();
        lineEdit_2->raise();
        pushButton_1->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        lineEdit_1->raise();
        comboBox_1->raise();
        comboBox_2->raise();
        pushButton_4->raise();

        retranslateUi(LockNormalHashCalculateClass);

        comboBox_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LockNormalHashCalculateClass);
    } // setupUi

    void retranslateUi(QDialog *LockNormalHashCalculateClass)
    {
        LockNormalHashCalculateClass->setWindowTitle(QApplication::translate("LockNormalHashCalculateClass", "\351\235\236\345\257\271\347\247\260\345\212\240\345\257\206", Q_NULLPTR));
        label_chara_1->setText(QString());
        label_chara_2->setText(QString());
        label_margin->setText(QString());
        pushButton_1->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        label_background->setText(QString());
        comboBox_1->clear();
        comboBox_1->insertItems(0, QStringList()
         << QApplication::translate("LockNormalHashCalculateClass", "MD4", Q_NULLPTR)
         << QApplication::translate("LockNormalHashCalculateClass", "MD5", Q_NULLPTR)
         << QApplication::translate("LockNormalHashCalculateClass", "SHA-1", Q_NULLPTR)
         << QApplication::translate("LockNormalHashCalculateClass", "SHA-2", Q_NULLPTR)
         << QApplication::translate("LockNormalHashCalculateClass", "SHA-3", Q_NULLPTR)
         << QApplication::translate("LockNormalHashCalculateClass", "Keccak", Q_NULLPTR)
        );
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("LockNormalHashCalculateClass", "224", Q_NULLPTR)
         << QApplication::translate("LockNormalHashCalculateClass", "256", Q_NULLPTR)
         << QApplication::translate("LockNormalHashCalculateClass", "384", Q_NULLPTR)
         << QApplication::translate("LockNormalHashCalculateClass", "512", Q_NULLPTR)
        );
        pushButton_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LockNormalHashCalculateClass: public Ui_LockNormalHashCalculateClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCKNORMALHASHCALCULATE_H
