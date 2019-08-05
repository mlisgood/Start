/********************************************************************************
** Form generated from reading UI file 'Setting.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingClass
{
public:
    QPushButton *pushButton_apply;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_cocoa_2;
    QLineEdit *lineedit_cocoa;
    QCheckBox *checkBox_cocoa_1;
    QCheckBox *checkBox_cocoa_2;
    QCheckBox *checkBox_chino_1;
    QCheckBox *checkBox_rize_1;
    QCheckBox *checkBox_chino_2;
    QLineEdit *lineedit_chino;
    QPushButton *pushButton_chino_2;
    QCheckBox *checkBox_rize_2;
    QLineEdit *lineedit_rize;
    QPushButton *pushButton_rize_2;
    QCheckBox *checkBox_syaro_1;
    QCheckBox *checkBox_syaro_2;
    QLineEdit *lineedit_syaro;
    QPushButton *pushButton_syaro_2;
    QCheckBox *checkBox_chiya_1;
    QCheckBox *checkBox_chiya_2;
    QLineEdit *lineedit_chiya;
    QPushButton *pushButton_chiya_2;
    QCheckBox *checkBox_maya_1;
    QCheckBox *checkBox_maya_2;
    QLineEdit *lineedit_maya;
    QPushButton *pushButton_maya_2;
    QCheckBox *checkBox_megu_1;
    QCheckBox *checkBox_megu_2;
    QLineEdit *lineedit_megu;
    QPushButton *pushButton_megu_2;
    QPushButton *pushButton_cocoa_1;
    QPushButton *pushButton_chino_1;
    QPushButton *pushButton_rize_1;
    QPushButton *pushButton_syaro_1;
    QPushButton *pushButton_chiya_1;
    QPushButton *pushButton_maya_1;
    QPushButton *pushButton_megu_1;
    QLabel *label_0;
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton_t_cocoa_1;
    QPushButton *pushButton_t_cocoa_2;
    QPushButton *pushButton_t_chino_1;
    QPushButton *pushButton_t_chino_2;
    QPushButton *pushButton_t_rize_1;
    QPushButton *pushButton_t_rize_2;
    QPushButton *pushButton_t_syaro_1;
    QPushButton *pushButton_t_syaro_2;
    QPushButton *pushButton_t_chiya_1;
    QPushButton *pushButton_t_chiya_2;
    QPushButton *pushButton_t_maya_1;
    QPushButton *pushButton_t_maya_2;
    QPushButton *pushButton_t_megu_1;
    QPushButton *pushButton_t_megu_2;

    void setupUi(QDialog *SettingClass)
    {
        if (SettingClass->objectName().isEmpty())
            SettingClass->setObjectName(QStringLiteral("SettingClass"));
        SettingClass->resize(600, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/picture_desktop/icon/picture_desktop/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        SettingClass->setWindowIcon(icon);
        SettingClass->setWindowOpacity(5);
        pushButton_apply = new QPushButton(SettingClass);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(174, 520, 50, 20));
        pushButton_apply->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_cancel = new QPushButton(SettingClass);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(382, 520, 35, 20));
        pushButton_cancel->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_cocoa_2 = new QPushButton(SettingClass);
        pushButton_cocoa_2->setObjectName(QStringLiteral("pushButton_cocoa_2"));
        pushButton_cocoa_2->setGeometry(QRect(520, 90, 16, 16));
        pushButton_cocoa_2->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);"));
        lineedit_cocoa = new QLineEdit(SettingClass);
        lineedit_cocoa->setObjectName(QStringLiteral("lineedit_cocoa"));
        lineedit_cocoa->setGeometry(QRect(278, 90, 220, 16));
        lineedit_cocoa->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_cocoa->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_cocoa->setReadOnly(true);
        checkBox_cocoa_1 = new QCheckBox(SettingClass);
        checkBox_cocoa_1->setObjectName(QStringLiteral("checkBox_cocoa_1"));
        checkBox_cocoa_1->setGeometry(QRect(116, 90, 16, 16));
        checkBox_cocoa_1->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_cocoa_1->setChecked(false);
        checkBox_cocoa_2 = new QCheckBox(SettingClass);
        checkBox_cocoa_2->setObjectName(QStringLiteral("checkBox_cocoa_2"));
        checkBox_cocoa_2->setGeometry(QRect(190, 90, 16, 16));
        checkBox_cocoa_2->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_cocoa_2->setChecked(false);
        checkBox_chino_1 = new QCheckBox(SettingClass);
        checkBox_chino_1->setObjectName(QStringLiteral("checkBox_chino_1"));
        checkBox_chino_1->setGeometry(QRect(116, 146, 16, 16));
        checkBox_chino_1->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_chino_1->setChecked(false);
        checkBox_rize_1 = new QCheckBox(SettingClass);
        checkBox_rize_1->setObjectName(QStringLiteral("checkBox_rize_1"));
        checkBox_rize_1->setGeometry(QRect(116, 202, 16, 16));
        checkBox_rize_1->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_rize_1->setChecked(false);
        checkBox_chino_2 = new QCheckBox(SettingClass);
        checkBox_chino_2->setObjectName(QStringLiteral("checkBox_chino_2"));
        checkBox_chino_2->setGeometry(QRect(190, 146, 16, 16));
        checkBox_chino_2->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_chino_2->setChecked(false);
        lineedit_chino = new QLineEdit(SettingClass);
        lineedit_chino->setObjectName(QStringLiteral("lineedit_chino"));
        lineedit_chino->setGeometry(QRect(278, 146, 220, 16));
        lineedit_chino->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_chino->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_chino->setReadOnly(true);
        pushButton_chino_2 = new QPushButton(SettingClass);
        pushButton_chino_2->setObjectName(QStringLiteral("pushButton_chino_2"));
        pushButton_chino_2->setGeometry(QRect(520, 146, 16, 16));
        pushButton_chino_2->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);"));
        checkBox_rize_2 = new QCheckBox(SettingClass);
        checkBox_rize_2->setObjectName(QStringLiteral("checkBox_rize_2"));
        checkBox_rize_2->setGeometry(QRect(190, 202, 16, 16));
        checkBox_rize_2->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_rize_2->setChecked(false);
        lineedit_rize = new QLineEdit(SettingClass);
        lineedit_rize->setObjectName(QStringLiteral("lineedit_rize"));
        lineedit_rize->setGeometry(QRect(278, 202, 220, 16));
        lineedit_rize->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_rize->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_rize->setReadOnly(true);
        pushButton_rize_2 = new QPushButton(SettingClass);
        pushButton_rize_2->setObjectName(QStringLiteral("pushButton_rize_2"));
        pushButton_rize_2->setGeometry(QRect(520, 202, 16, 16));
        pushButton_rize_2->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);"));
        checkBox_syaro_1 = new QCheckBox(SettingClass);
        checkBox_syaro_1->setObjectName(QStringLiteral("checkBox_syaro_1"));
        checkBox_syaro_1->setGeometry(QRect(116, 258, 16, 16));
        checkBox_syaro_1->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_syaro_1->setChecked(false);
        checkBox_syaro_2 = new QCheckBox(SettingClass);
        checkBox_syaro_2->setObjectName(QStringLiteral("checkBox_syaro_2"));
        checkBox_syaro_2->setGeometry(QRect(190, 258, 16, 16));
        checkBox_syaro_2->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_syaro_2->setChecked(false);
        lineedit_syaro = new QLineEdit(SettingClass);
        lineedit_syaro->setObjectName(QStringLiteral("lineedit_syaro"));
        lineedit_syaro->setGeometry(QRect(278, 258, 220, 16));
        lineedit_syaro->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_syaro->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_syaro->setReadOnly(true);
        pushButton_syaro_2 = new QPushButton(SettingClass);
        pushButton_syaro_2->setObjectName(QStringLiteral("pushButton_syaro_2"));
        pushButton_syaro_2->setGeometry(QRect(520, 258, 16, 16));
        pushButton_syaro_2->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);"));
        checkBox_chiya_1 = new QCheckBox(SettingClass);
        checkBox_chiya_1->setObjectName(QStringLiteral("checkBox_chiya_1"));
        checkBox_chiya_1->setGeometry(QRect(116, 314, 16, 16));
        checkBox_chiya_1->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_chiya_1->setChecked(false);
        checkBox_chiya_2 = new QCheckBox(SettingClass);
        checkBox_chiya_2->setObjectName(QStringLiteral("checkBox_chiya_2"));
        checkBox_chiya_2->setGeometry(QRect(190, 314, 16, 16));
        checkBox_chiya_2->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_chiya_2->setChecked(false);
        lineedit_chiya = new QLineEdit(SettingClass);
        lineedit_chiya->setObjectName(QStringLiteral("lineedit_chiya"));
        lineedit_chiya->setGeometry(QRect(278, 314, 220, 16));
        lineedit_chiya->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_chiya->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_chiya->setReadOnly(true);
        pushButton_chiya_2 = new QPushButton(SettingClass);
        pushButton_chiya_2->setObjectName(QStringLiteral("pushButton_chiya_2"));
        pushButton_chiya_2->setGeometry(QRect(520, 314, 16, 16));
        pushButton_chiya_2->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);"));
        checkBox_maya_1 = new QCheckBox(SettingClass);
        checkBox_maya_1->setObjectName(QStringLiteral("checkBox_maya_1"));
        checkBox_maya_1->setGeometry(QRect(116, 370, 16, 16));
        checkBox_maya_1->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_maya_1->setChecked(false);
        checkBox_maya_2 = new QCheckBox(SettingClass);
        checkBox_maya_2->setObjectName(QStringLiteral("checkBox_maya_2"));
        checkBox_maya_2->setGeometry(QRect(190, 370, 16, 16));
        checkBox_maya_2->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_maya_2->setChecked(false);
        lineedit_maya = new QLineEdit(SettingClass);
        lineedit_maya->setObjectName(QStringLiteral("lineedit_maya"));
        lineedit_maya->setGeometry(QRect(278, 370, 220, 16));
        lineedit_maya->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_maya->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_maya->setReadOnly(true);
        pushButton_maya_2 = new QPushButton(SettingClass);
        pushButton_maya_2->setObjectName(QStringLiteral("pushButton_maya_2"));
        pushButton_maya_2->setGeometry(QRect(520, 370, 16, 16));
        pushButton_maya_2->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);"));
        checkBox_megu_1 = new QCheckBox(SettingClass);
        checkBox_megu_1->setObjectName(QStringLiteral("checkBox_megu_1"));
        checkBox_megu_1->setGeometry(QRect(116, 426, 16, 16));
        checkBox_megu_1->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_megu_1->setChecked(false);
        checkBox_megu_2 = new QCheckBox(SettingClass);
        checkBox_megu_2->setObjectName(QStringLiteral("checkBox_megu_2"));
        checkBox_megu_2->setGeometry(QRect(190, 426, 16, 16));
        checkBox_megu_2->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_on.png);}"));
        checkBox_megu_2->setChecked(false);
        lineedit_megu = new QLineEdit(SettingClass);
        lineedit_megu->setObjectName(QStringLiteral("lineedit_megu"));
        lineedit_megu->setGeometry(QRect(278, 426, 220, 16));
        lineedit_megu->setContextMenuPolicy(Qt::NoContextMenu);
        lineedit_megu->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));
        lineedit_megu->setReadOnly(true);
        pushButton_megu_2 = new QPushButton(SettingClass);
        pushButton_megu_2->setObjectName(QStringLiteral("pushButton_megu_2"));
        pushButton_megu_2->setGeometry(QRect(520, 426, 16, 16));
        pushButton_megu_2->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/checkbox/picture_desktop/checkbox_style/checkbox_off.png);"));
        pushButton_cocoa_1 = new QPushButton(SettingClass);
        pushButton_cocoa_1->setObjectName(QStringLiteral("pushButton_cocoa_1"));
        pushButton_cocoa_1->setGeometry(QRect(500, 90, 16, 16));
        pushButton_cocoa_1->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/icon/picture_desktop/icon/dialog_arrow.png);"));
        pushButton_chino_1 = new QPushButton(SettingClass);
        pushButton_chino_1->setObjectName(QStringLiteral("pushButton_chino_1"));
        pushButton_chino_1->setGeometry(QRect(500, 146, 16, 16));
        pushButton_chino_1->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/icon/picture_desktop/icon/dialog_arrow.png);"));
        pushButton_rize_1 = new QPushButton(SettingClass);
        pushButton_rize_1->setObjectName(QStringLiteral("pushButton_rize_1"));
        pushButton_rize_1->setGeometry(QRect(500, 202, 16, 16));
        pushButton_rize_1->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/icon/picture_desktop/icon/dialog_arrow.png);"));
        pushButton_syaro_1 = new QPushButton(SettingClass);
        pushButton_syaro_1->setObjectName(QStringLiteral("pushButton_syaro_1"));
        pushButton_syaro_1->setGeometry(QRect(500, 258, 16, 16));
        pushButton_syaro_1->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/icon/picture_desktop/icon/dialog_arrow.png);"));
        pushButton_chiya_1 = new QPushButton(SettingClass);
        pushButton_chiya_1->setObjectName(QStringLiteral("pushButton_chiya_1"));
        pushButton_chiya_1->setGeometry(QRect(500, 314, 16, 16));
        pushButton_chiya_1->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/icon/picture_desktop/icon/dialog_arrow.png);"));
        pushButton_maya_1 = new QPushButton(SettingClass);
        pushButton_maya_1->setObjectName(QStringLiteral("pushButton_maya_1"));
        pushButton_maya_1->setGeometry(QRect(500, 370, 16, 16));
        pushButton_maya_1->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/icon/picture_desktop/icon/dialog_arrow.png);"));
        pushButton_megu_1 = new QPushButton(SettingClass);
        pushButton_megu_1->setObjectName(QStringLiteral("pushButton_megu_1"));
        pushButton_megu_1->setGeometry(QRect(500, 426, 16, 16));
        pushButton_megu_1->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/icon/picture_desktop/icon/dialog_arrow.png);"));
        label_0 = new QLabel(SettingClass);
        label_0->setObjectName(QStringLiteral("label_0"));
        label_0->setGeometry(QRect(60, 450, 60, 60));
        label_1 = new QLabel(SettingClass);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setGeometry(QRect(130, 450, 60, 60));
        label_2 = new QLabel(SettingClass);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(200, 450, 60, 60));
        label_3 = new QLabel(SettingClass);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(270, 450, 60, 60));
        label_4 = new QLabel(SettingClass);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(340, 450, 60, 60));
        label_5 = new QLabel(SettingClass);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(410, 450, 60, 60));
        label_6 = new QLabel(SettingClass);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(480, 450, 60, 60));
        pushButton_t_cocoa_1 = new QPushButton(SettingClass);
        pushButton_t_cocoa_1->setObjectName(QStringLiteral("pushButton_t_cocoa_1"));
        pushButton_t_cocoa_1->setGeometry(QRect(60, 450, 30, 60));
        pushButton_t_cocoa_1->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_t_cocoa_2 = new QPushButton(SettingClass);
        pushButton_t_cocoa_2->setObjectName(QStringLiteral("pushButton_t_cocoa_2"));
        pushButton_t_cocoa_2->setGeometry(QRect(90, 450, 30, 60));
        pushButton_t_cocoa_2->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_t_chino_1 = new QPushButton(SettingClass);
        pushButton_t_chino_1->setObjectName(QStringLiteral("pushButton_t_chino_1"));
        pushButton_t_chino_1->setGeometry(QRect(130, 450, 30, 60));
        pushButton_t_chino_1->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_t_chino_2 = new QPushButton(SettingClass);
        pushButton_t_chino_2->setObjectName(QStringLiteral("pushButton_t_chino_2"));
        pushButton_t_chino_2->setGeometry(QRect(160, 450, 30, 60));
        pushButton_t_chino_2->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_t_rize_1 = new QPushButton(SettingClass);
        pushButton_t_rize_1->setObjectName(QStringLiteral("pushButton_t_rize_1"));
        pushButton_t_rize_1->setGeometry(QRect(200, 450, 30, 60));
        pushButton_t_rize_1->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_t_rize_2 = new QPushButton(SettingClass);
        pushButton_t_rize_2->setObjectName(QStringLiteral("pushButton_t_rize_2"));
        pushButton_t_rize_2->setGeometry(QRect(230, 450, 30, 60));
        pushButton_t_rize_2->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_t_syaro_1 = new QPushButton(SettingClass);
        pushButton_t_syaro_1->setObjectName(QStringLiteral("pushButton_t_syaro_1"));
        pushButton_t_syaro_1->setGeometry(QRect(270, 450, 30, 60));
        pushButton_t_syaro_1->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_t_syaro_2 = new QPushButton(SettingClass);
        pushButton_t_syaro_2->setObjectName(QStringLiteral("pushButton_t_syaro_2"));
        pushButton_t_syaro_2->setGeometry(QRect(300, 450, 30, 60));
        pushButton_t_syaro_2->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_t_chiya_1 = new QPushButton(SettingClass);
        pushButton_t_chiya_1->setObjectName(QStringLiteral("pushButton_t_chiya_1"));
        pushButton_t_chiya_1->setGeometry(QRect(340, 450, 30, 60));
        pushButton_t_chiya_1->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_t_chiya_2 = new QPushButton(SettingClass);
        pushButton_t_chiya_2->setObjectName(QStringLiteral("pushButton_t_chiya_2"));
        pushButton_t_chiya_2->setGeometry(QRect(370, 450, 30, 60));
        pushButton_t_chiya_2->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_t_maya_1 = new QPushButton(SettingClass);
        pushButton_t_maya_1->setObjectName(QStringLiteral("pushButton_t_maya_1"));
        pushButton_t_maya_1->setGeometry(QRect(410, 450, 30, 60));
        pushButton_t_maya_1->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_t_maya_2 = new QPushButton(SettingClass);
        pushButton_t_maya_2->setObjectName(QStringLiteral("pushButton_t_maya_2"));
        pushButton_t_maya_2->setGeometry(QRect(440, 450, 30, 60));
        pushButton_t_maya_2->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_t_megu_1 = new QPushButton(SettingClass);
        pushButton_t_megu_1->setObjectName(QStringLiteral("pushButton_t_megu_1"));
        pushButton_t_megu_1->setGeometry(QRect(480, 450, 30, 60));
        pushButton_t_megu_1->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_t_megu_2 = new QPushButton(SettingClass);
        pushButton_t_megu_2->setObjectName(QStringLiteral("pushButton_t_megu_2"));
        pushButton_t_megu_2->setGeometry(QRect(510, 450, 30, 60));
        pushButton_t_megu_2->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));

        retranslateUi(SettingClass);

        QMetaObject::connectSlotsByName(SettingClass);
    } // setupUi

    void retranslateUi(QDialog *SettingClass)
    {
        SettingClass->setWindowTitle(QApplication::translate("SettingClass", "\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_apply->setText(QString());
        pushButton_cancel->setText(QString());
        pushButton_cocoa_2->setText(QString());
        lineedit_cocoa->setText(QString());
        checkBox_cocoa_1->setText(QString());
        checkBox_cocoa_2->setText(QString());
        checkBox_chino_1->setText(QString());
        checkBox_rize_1->setText(QString());
        checkBox_chino_2->setText(QString());
        lineedit_chino->setText(QString());
        pushButton_chino_2->setText(QString());
        checkBox_rize_2->setText(QString());
        lineedit_rize->setText(QString());
        pushButton_rize_2->setText(QString());
        checkBox_syaro_1->setText(QString());
        checkBox_syaro_2->setText(QString());
        lineedit_syaro->setText(QString());
        pushButton_syaro_2->setText(QString());
        checkBox_chiya_1->setText(QString());
        checkBox_chiya_2->setText(QString());
        lineedit_chiya->setText(QString());
        pushButton_chiya_2->setText(QString());
        checkBox_maya_1->setText(QString());
        checkBox_maya_2->setText(QString());
        lineedit_maya->setText(QString());
        pushButton_maya_2->setText(QString());
        checkBox_megu_1->setText(QString());
        checkBox_megu_2->setText(QString());
        lineedit_megu->setText(QString());
        pushButton_megu_2->setText(QString());
        pushButton_cocoa_1->setText(QString());
        pushButton_chino_1->setText(QString());
        pushButton_rize_1->setText(QString());
        pushButton_syaro_1->setText(QString());
        pushButton_chiya_1->setText(QString());
        pushButton_maya_1->setText(QString());
        pushButton_megu_1->setText(QString());
        label_0->setText(QString());
        label_1->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
        label_5->setText(QString());
        label_6->setText(QString());
        pushButton_t_cocoa_1->setText(QString());
        pushButton_t_cocoa_2->setText(QString());
        pushButton_t_chino_1->setText(QString());
        pushButton_t_chino_2->setText(QString());
        pushButton_t_rize_1->setText(QString());
        pushButton_t_rize_2->setText(QString());
        pushButton_t_syaro_1->setText(QString());
        pushButton_t_syaro_2->setText(QString());
        pushButton_t_chiya_1->setText(QString());
        pushButton_t_chiya_2->setText(QString());
        pushButton_t_maya_1->setText(QString());
        pushButton_t_maya_2->setText(QString());
        pushButton_t_megu_1->setText(QString());
        pushButton_t_megu_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SettingClass: public Ui_SettingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
