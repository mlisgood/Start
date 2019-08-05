/********************************************************************************
** Form generated from reading UI file 'LockNormalSingleKey.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCKNORMALSINGLEKEY_H
#define UI_LOCKNORMALSINGLEKEY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LockNormalSingleKeyClass
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
    QProgressBar *progressBar;
    QLineEdit *lineEdit_1;
    QLineEdit *lineEdit;
    QCheckBox *checkBox;
    QComboBox *comboBox_1;
    QCheckBox *checkBox_2;

    void setupUi(QDialog *LockNormalSingleKeyClass)
    {
        if (LockNormalSingleKeyClass->objectName().isEmpty())
            LockNormalSingleKeyClass->setObjectName(QStringLiteral("LockNormalSingleKeyClass"));
        LockNormalSingleKeyClass->resize(400, 600);
        LockNormalSingleKeyClass->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_lock/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        LockNormalSingleKeyClass->setWindowIcon(icon);
        LockNormalSingleKeyClass->setWindowOpacity(5);
        label_chara_1 = new QLabel(LockNormalSingleKeyClass);
        label_chara_1->setObjectName(QStringLiteral("label_chara_1"));
        label_chara_1->setGeometry(QRect(0, 0, 400, 400));
        label_chara_2 = new QLabel(LockNormalSingleKeyClass);
        label_chara_2->setObjectName(QStringLiteral("label_chara_2"));
        label_chara_2->setGeometry(QRect(0, 0, 400, 400));
        label_margin = new QLabel(LockNormalSingleKeyClass);
        label_margin->setObjectName(QStringLiteral("label_margin"));
        label_margin->setGeometry(QRect(0, 0, 400, 600));
        label_margin->setPixmap(QPixmap(QString::fromUtf8("picture_lock/lock_margin/margin.png")));
        pushButton_1 = new QPushButton(LockNormalSingleKeyClass);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setGeometry(QRect(43, 560, 100, 30));
        pushButton_1->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_1.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_1.png);"));
        pushButton_2 = new QPushButton(LockNormalSingleKeyClass);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(143, 560, 100, 30));
        pushButton_2->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_2.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_2.png);"));
        pushButton_3 = new QPushButton(LockNormalSingleKeyClass);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(243, 560, 100, 30));
        pushButton_3->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_3.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_3.png);"));
        label_background = new QLabel(LockNormalSingleKeyClass);
        label_background->setObjectName(QStringLiteral("label_background"));
        label_background->setGeometry(QRect(0, 0, 400, 600));
        label_background->setFrameShape(QFrame::NoFrame);
        label_background->setPixmap(QPixmap(QString::fromUtf8("picture_lock/lock_normal_single_background/background_1.png")));
        lineEdit_2 = new QLineEdit(LockNormalSingleKeyClass);
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
        progressBar = new QProgressBar(LockNormalSingleKeyClass);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(138, 532, 221, 20));
        progressBar->setContextMenuPolicy(Qt::NoContextMenu);
        progressBar->setStyleSheet(QLatin1String("QProgressBar\n"
"{\n"
"   border: 1px solid #804C47;\n"
"   background-color: #00FFFFFF;\n"
"   text-align: center;\n"
"}\n"
" \n"
"QProgressBar::chunk\n"
"{\n"
"   background-color: #804C47;\n"
"}"));
        progressBar->setMinimum(0);
        progressBar->setMaximum(100);
        progressBar->setValue(0);
        lineEdit_1 = new QLineEdit(LockNormalSingleKeyClass);
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
        lineEdit_1->setReadOnly(true);
        lineEdit = new QLineEdit(LockNormalSingleKeyClass);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(303, 503, 56, 20));
        lineEdit->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        lineEdit->setInputMethodHints(Qt::ImhNone);
        lineEdit->setMaxLength(8);
        checkBox = new QCheckBox(LockNormalSingleKeyClass);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(138, 503, 20, 20));
        checkBox->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}"));
        comboBox_1 = new QComboBox(LockNormalSingleKeyClass);
        comboBox_1->setObjectName(QStringLiteral("comboBox_1"));
        comboBox_1->setGeometry(QRect(138, 416, 127, 20));
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
        checkBox_2 = new QCheckBox(LockNormalSingleKeyClass);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(268, 416, 20, 20));
        checkBox_2->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}"));
        label_background->raise();
        label_chara_2->raise();
        label_chara_1->raise();
        label_margin->raise();
        lineEdit_2->raise();
        progressBar->raise();
        pushButton_1->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        lineEdit_1->raise();
        lineEdit->raise();
        checkBox->raise();
        comboBox_1->raise();
        checkBox_2->raise();

        retranslateUi(LockNormalSingleKeyClass);

        QMetaObject::connectSlotsByName(LockNormalSingleKeyClass);
    } // setupUi

    void retranslateUi(QDialog *LockNormalSingleKeyClass)
    {
        LockNormalSingleKeyClass->setWindowTitle(QApplication::translate("LockNormalSingleKeyClass", "\345\257\271\347\247\260\345\212\240\345\257\206", Q_NULLPTR));
        label_chara_1->setText(QString());
        label_chara_2->setText(QString());
        label_margin->setText(QString());
        pushButton_1->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        label_background->setText(QString());
        checkBox->setText(QString());
        comboBox_1->clear();
        comboBox_1->insertItems(0, QStringList()
         << QApplication::translate("LockNormalSingleKeyClass", "DES", Q_NULLPTR)
         << QApplication::translate("LockNormalSingleKeyClass", "2-Key 3DES", Q_NULLPTR)
         << QApplication::translate("LockNormalSingleKeyClass", "3-Key 3DES", Q_NULLPTR)
         << QApplication::translate("LockNormalSingleKeyClass", "AES-128", Q_NULLPTR)
         << QApplication::translate("LockNormalSingleKeyClass", "AES-192", Q_NULLPTR)
         << QApplication::translate("LockNormalSingleKeyClass", "AES-256", Q_NULLPTR)
        );
        checkBox_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LockNormalSingleKeyClass: public Ui_LockNormalSingleKeyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCKNORMALSINGLEKEY_H
