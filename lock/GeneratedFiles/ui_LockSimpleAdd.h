/********************************************************************************
** Form generated from reading UI file 'LockSimpleAdd.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCKSIMPLEADD_H
#define UI_LOCKSIMPLEADD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_LockSimpleAddClass
{
public:
    QLabel *label_chara_1;
    QLabel *label_chara_2;
    QLabel *label_margin;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label_background;
    QSpinBox *spinBox_1;
    QSpinBox *spinBox_2;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QCheckBox *checkBox;
    QLineEdit *lineEdit;
    QProgressBar *progressBar;
    QPushButton *pushButton_4;

    void setupUi(QDialog *LockSimpleAddClass)
    {
        if (LockSimpleAddClass->objectName().isEmpty())
            LockSimpleAddClass->setObjectName(QStringLiteral("LockSimpleAddClass"));
        LockSimpleAddClass->resize(400, 600);
        LockSimpleAddClass->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_lock/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        LockSimpleAddClass->setWindowIcon(icon);
        LockSimpleAddClass->setWindowOpacity(5);
        label_chara_1 = new QLabel(LockSimpleAddClass);
        label_chara_1->setObjectName(QStringLiteral("label_chara_1"));
        label_chara_1->setGeometry(QRect(0, 0, 400, 400));
        label_chara_2 = new QLabel(LockSimpleAddClass);
        label_chara_2->setObjectName(QStringLiteral("label_chara_2"));
        label_chara_2->setGeometry(QRect(0, 0, 400, 400));
        label_margin = new QLabel(LockSimpleAddClass);
        label_margin->setObjectName(QStringLiteral("label_margin"));
        label_margin->setGeometry(QRect(0, 0, 400, 600));
        label_margin->setPixmap(QPixmap(QString::fromUtf8("picture_lock/lock_margin/margin.png")));
        pushButton_1 = new QPushButton(LockSimpleAddClass);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setGeometry(QRect(43, 560, 100, 30));
        pushButton_1->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_1.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_1.png);"));
        pushButton_2 = new QPushButton(LockSimpleAddClass);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(143, 560, 100, 30));
        pushButton_2->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_2.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_2.png);"));
        pushButton_3 = new QPushButton(LockSimpleAddClass);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(243, 560, 100, 30));
        pushButton_3->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_3.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_3.png);"));
        label_background = new QLabel(LockSimpleAddClass);
        label_background->setObjectName(QStringLiteral("label_background"));
        label_background->setGeometry(QRect(0, 0, 400, 600));
        label_background->setFrameShape(QFrame::NoFrame);
        label_background->setPixmap(QPixmap(QString::fromUtf8("picture_lock/lock_simple_add_background/background_1.png")));
        spinBox_1 = new QSpinBox(LockSimpleAddClass);
        spinBox_1->setObjectName(QStringLiteral("spinBox_1"));
        spinBox_1->setGeometry(QRect(175, 443, 55, 22));
        spinBox_1->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_1->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/up_button.png);     \n"
"    background: #FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/up_button.png);   \n"
"    background: #FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"}"));
        spinBox_1->setMaximum(1048576);
        spinBox_1->setValue(0);
        spinBox_2 = new QSpinBox(LockSimpleAddClass);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(294, 443, 55, 22));
        spinBox_2->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/up_button.png);     \n"
"    background: #FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/up_button.png);   \n"
"    background: #FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_lock/spinbox/picture_lock/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"}"));
        spinBox_2->setMaximum(1048576);
        spinBox_2->setValue(0);
        radioButton_1 = new QRadioButton(LockSimpleAddClass);
        radioButton_1->setObjectName(QStringLiteral("radioButton_1"));
        radioButton_1->setGeometry(QRect(138, 415, 20, 20));
        radioButton_1->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}"));
        radioButton_1->setChecked(true);
        radioButton_2 = new QRadioButton(LockSimpleAddClass);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(267, 415, 20, 20));
        radioButton_2->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}"));
        checkBox = new QCheckBox(LockSimpleAddClass);
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
        lineEdit = new QLineEdit(LockSimpleAddClass);
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
        progressBar = new QProgressBar(LockSimpleAddClass);
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
        pushButton_4 = new QPushButton(LockSimpleAddClass);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(269, 468, 90, 30));
        pushButton_4->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_12.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_12.png);"));
        label_background->raise();
        label_chara_2->raise();
        label_chara_1->raise();
        label_margin->raise();
        radioButton_1->raise();
        radioButton_2->raise();
        checkBox->raise();
        lineEdit->raise();
        progressBar->raise();
        pushButton_1->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        spinBox_1->raise();
        spinBox_2->raise();
        pushButton_4->raise();

        retranslateUi(LockSimpleAddClass);

        QMetaObject::connectSlotsByName(LockSimpleAddClass);
    } // setupUi

    void retranslateUi(QDialog *LockSimpleAddClass)
    {
        LockSimpleAddClass->setWindowTitle(QApplication::translate("LockSimpleAddClass", "\345\212\240\345\207\217\345\212\240\345\257\206", Q_NULLPTR));
        label_chara_1->setText(QString());
        label_chara_2->setText(QString());
        label_margin->setText(QString());
        pushButton_1->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        label_background->setText(QString());
        radioButton_1->setText(QString());
        radioButton_2->setText(QString());
        checkBox->setText(QString());
        pushButton_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LockSimpleAddClass: public Ui_LockSimpleAddClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCKSIMPLEADD_H
