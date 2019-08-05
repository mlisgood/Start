/********************************************************************************
** Form generated from reading UI file 'SettingOther.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGOTHER_H
#define UI_SETTINGOTHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingOtherClass
{
public:
    QPushButton *pushButton_apply;
    QPushButton *pushButton_cancel;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QSpinBox *spinBox_main_1;
    QSpinBox *spinBox_main_2;

    void setupUi(QDialog *SettingOtherClass)
    {
        if (SettingOtherClass->objectName().isEmpty())
            SettingOtherClass->setObjectName(QStringLiteral("SettingOtherClass"));
        SettingOtherClass->resize(600, 330);
        QIcon icon;
        icon.addFile(QStringLiteral(":/picture_desktop/icon/picture_desktop/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        SettingOtherClass->setWindowIcon(icon);
        SettingOtherClass->setWindowOpacity(5);
        pushButton_apply = new QPushButton(SettingOtherClass);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(174, 245, 50, 20));
        pushButton_apply->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_cancel = new QPushButton(SettingOtherClass);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(382, 245, 35, 20));
        pushButton_cancel->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        checkBox_1 = new QCheckBox(SettingOtherClass);
        checkBox_1->setObjectName(QStringLiteral("checkBox_1"));
        checkBox_1->setGeometry(QRect(116, 96, 16, 16));
        checkBox_1->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_1->setChecked(false);
        checkBox_2 = new QCheckBox(SettingOtherClass);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(116, 152, 16, 16));
        checkBox_2->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_2->setChecked(false);
        spinBox_main_1 = new QSpinBox(SettingOtherClass);
        spinBox_main_1->setObjectName(QStringLiteral("spinBox_main_1"));
        spinBox_main_1->setGeometry(QRect(104, 177, 50, 22));
        spinBox_main_1->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_main_1->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/up_button.png);   \n"
"    background: #00FFFFFF;  \n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/down_button.png); \n"
"    background: #00FFFFFF;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/up_button.png);   \n"
"    background: #00FFFFFF;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/down_button.png); \n"
"    background: #00FFFFFF;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #E872A2;\n"
"    background: #00FFFFFF;\n"
"}"));
        spinBox_main_1->setMinimum(1);
        spinBox_main_1->setMaximum(3600);
        spinBox_main_1->setValue(1);
        spinBox_main_2 = new QSpinBox(SettingOtherClass);
        spinBox_main_2->setObjectName(QStringLiteral("spinBox_main_2"));
        spinBox_main_2->setGeometry(QRect(172, 205, 50, 22));
        spinBox_main_2->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_main_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/up_button.png);   \n"
"    background: #00FFFFFF;  \n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/down_button.png); \n"
"    background: #00FFFFFF;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/up_button.png);   \n"
"    background: #00FFFFFF;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/down_button.png); \n"
"    background: #00FFFFFF;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #E872A2;\n"
"    background: #00FFFFFF;\n"
"}"));
        spinBox_main_2->setMaximum(10);
        spinBox_main_2->setValue(0);

        retranslateUi(SettingOtherClass);

        QMetaObject::connectSlotsByName(SettingOtherClass);
    } // setupUi

    void retranslateUi(QDialog *SettingOtherClass)
    {
        SettingOtherClass->setWindowTitle(QApplication::translate("SettingOtherClass", "\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_apply->setText(QString());
        pushButton_cancel->setText(QString());
        checkBox_1->setText(QString());
        checkBox_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SettingOtherClass: public Ui_SettingOtherClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGOTHER_H
