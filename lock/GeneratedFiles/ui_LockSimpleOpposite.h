/********************************************************************************
** Form generated from reading UI file 'LockSimpleOpposite.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCKSIMPLEOPPOSITE_H
#define UI_LOCKSIMPLEOPPOSITE_H

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

class Ui_LockSimpleOppositeClass
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
    QSpinBox *spinBox_3;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QCheckBox *checkBox;
    QLineEdit *lineEdit;
    QProgressBar *progressBar;

    void setupUi(QDialog *LockSimpleOppositeClass)
    {
        if (LockSimpleOppositeClass->objectName().isEmpty())
            LockSimpleOppositeClass->setObjectName(QStringLiteral("LockSimpleOppositeClass"));
        LockSimpleOppositeClass->resize(400, 600);
        LockSimpleOppositeClass->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_lock/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        LockSimpleOppositeClass->setWindowIcon(icon);
        LockSimpleOppositeClass->setWindowOpacity(5);
        label_chara_1 = new QLabel(LockSimpleOppositeClass);
        label_chara_1->setObjectName(QStringLiteral("label_chara_1"));
        label_chara_1->setGeometry(QRect(0, 0, 400, 400));
        label_chara_2 = new QLabel(LockSimpleOppositeClass);
        label_chara_2->setObjectName(QStringLiteral("label_chara_2"));
        label_chara_2->setGeometry(QRect(0, 0, 400, 400));
        label_margin = new QLabel(LockSimpleOppositeClass);
        label_margin->setObjectName(QStringLiteral("label_margin"));
        label_margin->setGeometry(QRect(0, 0, 400, 600));
        label_margin->setPixmap(QPixmap(QString::fromUtf8("picture_lock/lock_margin/margin.png")));
        pushButton_1 = new QPushButton(LockSimpleOppositeClass);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setGeometry(QRect(43, 560, 100, 30));
        pushButton_1->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_1.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_1.png);"));
        pushButton_2 = new QPushButton(LockSimpleOppositeClass);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(143, 560, 100, 30));
        pushButton_2->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_2.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_2.png);"));
        pushButton_3 = new QPushButton(LockSimpleOppositeClass);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(243, 560, 100, 30));
        pushButton_3->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_3.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_3.png);"));
        label_background = new QLabel(LockSimpleOppositeClass);
        label_background->setObjectName(QStringLiteral("label_background"));
        label_background->setGeometry(QRect(0, 0, 400, 600));
        label_background->setFrameShape(QFrame::NoFrame);
        label_background->setPixmap(QPixmap(QString::fromUtf8("picture_lock/lock_simple_background/background_1.png")));
        spinBox_1 = new QSpinBox(LockSimpleOppositeClass);
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
        spinBox_2 = new QSpinBox(LockSimpleOppositeClass);
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
        spinBox_3 = new QSpinBox(LockSimpleOppositeClass);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setGeometry(QRect(175, 473, 55, 22));
        spinBox_3->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_3->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_3->setMinimum(0);
        spinBox_3->setMaximum(1048576);
        spinBox_3->setValue(0);
        radioButton_1 = new QRadioButton(LockSimpleOppositeClass);
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
        radioButton_2 = new QRadioButton(LockSimpleOppositeClass);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(212, 415, 20, 20));
        radioButton_2->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}"));
        radioButton_3 = new QRadioButton(LockSimpleOppositeClass);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(288, 415, 20, 20));
        radioButton_3->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_lock/checkbox/picture_lock/checkbox_style/checkbox_on.png);}"));
        checkBox = new QCheckBox(LockSimpleOppositeClass);
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
        lineEdit = new QLineEdit(LockSimpleOppositeClass);
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
        progressBar = new QProgressBar(LockSimpleOppositeClass);
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
        label_background->raise();
        label_chara_2->raise();
        label_chara_1->raise();
        label_margin->raise();
        radioButton_1->raise();
        radioButton_3->raise();
        radioButton_2->raise();
        checkBox->raise();
        lineEdit->raise();
        progressBar->raise();
        pushButton_1->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        spinBox_1->raise();
        spinBox_2->raise();
        spinBox_3->raise();

        retranslateUi(LockSimpleOppositeClass);

        QMetaObject::connectSlotsByName(LockSimpleOppositeClass);
    } // setupUi

    void retranslateUi(QDialog *LockSimpleOppositeClass)
    {
        LockSimpleOppositeClass->setWindowTitle(QApplication::translate("LockSimpleOppositeClass", "\345\217\226\345\217\215\345\212\240\345\257\206", Q_NULLPTR));
        label_chara_1->setText(QString());
        label_chara_2->setText(QString());
        label_margin->setText(QString());
        pushButton_1->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        label_background->setText(QString());
        radioButton_1->setText(QString());
        radioButton_2->setText(QString());
        radioButton_3->setText(QString());
        checkBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LockSimpleOppositeClass: public Ui_LockSimpleOppositeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCKSIMPLEOPPOSITE_H
