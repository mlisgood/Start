/********************************************************************************
** Form generated from reading UI file 'SettingDynamic.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDYNAMIC_H
#define UI_SETTINGDYNAMIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingDynamicClass
{
public:
    QPushButton *pushButton_apply;
    QPushButton *pushButton_cancel;
    QSpinBox *spinBox_main_1;
    QSpinBox *spinBox_main_2;
    QSpinBox *spinBox_cocoa_1;
    QSpinBox *spinBox_cocoa_2;
    QSpinBox *spinBox_chino_1;
    QSpinBox *spinBox_chino_2;
    QSpinBox *spinBox_rize_1;
    QSpinBox *spinBox_rize_2;
    QSpinBox *spinBox_syaro_1;
    QSpinBox *spinBox_syaro_2;
    QSpinBox *spinBox_chiya_1;
    QSpinBox *spinBox_chiya_2;
    QSpinBox *spinBox_maya_1;
    QSpinBox *spinBox_maya_2;
    QSpinBox *spinBox_megu_1;
    QSpinBox *spinBox_megu_2;

    void setupUi(QDialog *SettingDynamicClass)
    {
        if (SettingDynamicClass->objectName().isEmpty())
            SettingDynamicClass->setObjectName(QStringLiteral("SettingDynamicClass"));
        SettingDynamicClass->resize(600, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/picture_desktop/icon/picture_desktop/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        SettingDynamicClass->setWindowIcon(icon);
        SettingDynamicClass->setWindowOpacity(5);
        pushButton_apply = new QPushButton(SettingDynamicClass);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(174, 520, 50, 20));
        pushButton_apply->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_cancel = new QPushButton(SettingDynamicClass);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(382, 520, 35, 20));
        pushButton_cancel->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        spinBox_main_1 = new QSpinBox(SettingDynamicClass);
        spinBox_main_1->setObjectName(QStringLiteral("spinBox_main_1"));
        spinBox_main_1->setGeometry(QRect(90, 87, 50, 22));
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
        spinBox_main_1->setMaximum(9999);
        spinBox_main_1->setValue(0);
        spinBox_main_2 = new QSpinBox(SettingDynamicClass);
        spinBox_main_2->setObjectName(QStringLiteral("spinBox_main_2"));
        spinBox_main_2->setGeometry(QRect(322, 87, 50, 22));
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
        spinBox_main_2->setMaximum(9999);
        spinBox_main_2->setValue(0);
        spinBox_cocoa_1 = new QSpinBox(SettingDynamicClass);
        spinBox_cocoa_1->setObjectName(QStringLiteral("spinBox_cocoa_1"));
        spinBox_cocoa_1->setGeometry(QRect(90, 143, 50, 22));
        spinBox_cocoa_1->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_cocoa_1->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_cocoa_1->setMaximum(9999);
        spinBox_cocoa_1->setValue(0);
        spinBox_cocoa_2 = new QSpinBox(SettingDynamicClass);
        spinBox_cocoa_2->setObjectName(QStringLiteral("spinBox_cocoa_2"));
        spinBox_cocoa_2->setGeometry(QRect(322, 143, 50, 22));
        spinBox_cocoa_2->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_cocoa_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_cocoa_2->setMaximum(9999);
        spinBox_cocoa_2->setValue(0);
        spinBox_chino_1 = new QSpinBox(SettingDynamicClass);
        spinBox_chino_1->setObjectName(QStringLiteral("spinBox_chino_1"));
        spinBox_chino_1->setGeometry(QRect(90, 199, 50, 22));
        spinBox_chino_1->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_chino_1->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_chino_1->setMaximum(9999);
        spinBox_chino_1->setValue(0);
        spinBox_chino_2 = new QSpinBox(SettingDynamicClass);
        spinBox_chino_2->setObjectName(QStringLiteral("spinBox_chino_2"));
        spinBox_chino_2->setGeometry(QRect(322, 199, 50, 22));
        spinBox_chino_2->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_chino_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_chino_2->setMaximum(9999);
        spinBox_chino_2->setValue(0);
        spinBox_rize_1 = new QSpinBox(SettingDynamicClass);
        spinBox_rize_1->setObjectName(QStringLiteral("spinBox_rize_1"));
        spinBox_rize_1->setGeometry(QRect(90, 255, 50, 22));
        spinBox_rize_1->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_rize_1->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_rize_1->setMaximum(9999);
        spinBox_rize_1->setValue(0);
        spinBox_rize_2 = new QSpinBox(SettingDynamicClass);
        spinBox_rize_2->setObjectName(QStringLiteral("spinBox_rize_2"));
        spinBox_rize_2->setGeometry(QRect(322, 255, 50, 22));
        spinBox_rize_2->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_rize_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_rize_2->setMaximum(9999);
        spinBox_rize_2->setValue(0);
        spinBox_syaro_1 = new QSpinBox(SettingDynamicClass);
        spinBox_syaro_1->setObjectName(QStringLiteral("spinBox_syaro_1"));
        spinBox_syaro_1->setGeometry(QRect(90, 311, 50, 22));
        spinBox_syaro_1->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_syaro_1->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_syaro_1->setMaximum(9999);
        spinBox_syaro_1->setValue(0);
        spinBox_syaro_2 = new QSpinBox(SettingDynamicClass);
        spinBox_syaro_2->setObjectName(QStringLiteral("spinBox_syaro_2"));
        spinBox_syaro_2->setGeometry(QRect(322, 311, 50, 22));
        spinBox_syaro_2->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_syaro_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_syaro_2->setMaximum(9999);
        spinBox_syaro_2->setValue(0);
        spinBox_chiya_1 = new QSpinBox(SettingDynamicClass);
        spinBox_chiya_1->setObjectName(QStringLiteral("spinBox_chiya_1"));
        spinBox_chiya_1->setGeometry(QRect(90, 367, 50, 22));
        spinBox_chiya_1->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_chiya_1->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_chiya_1->setMaximum(9999);
        spinBox_chiya_1->setValue(0);
        spinBox_chiya_2 = new QSpinBox(SettingDynamicClass);
        spinBox_chiya_2->setObjectName(QStringLiteral("spinBox_chiya_2"));
        spinBox_chiya_2->setGeometry(QRect(322, 367, 50, 22));
        spinBox_chiya_2->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_chiya_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_chiya_2->setMaximum(9999);
        spinBox_chiya_2->setValue(0);
        spinBox_maya_1 = new QSpinBox(SettingDynamicClass);
        spinBox_maya_1->setObjectName(QStringLiteral("spinBox_maya_1"));
        spinBox_maya_1->setGeometry(QRect(90, 423, 50, 22));
        spinBox_maya_1->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_maya_1->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_maya_1->setMaximum(9999);
        spinBox_maya_1->setValue(0);
        spinBox_maya_2 = new QSpinBox(SettingDynamicClass);
        spinBox_maya_2->setObjectName(QStringLiteral("spinBox_maya_2"));
        spinBox_maya_2->setGeometry(QRect(322, 423, 50, 22));
        spinBox_maya_2->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_maya_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_maya_2->setMaximum(9999);
        spinBox_maya_2->setValue(0);
        spinBox_megu_1 = new QSpinBox(SettingDynamicClass);
        spinBox_megu_1->setObjectName(QStringLiteral("spinBox_megu_1"));
        spinBox_megu_1->setGeometry(QRect(90, 479, 50, 22));
        spinBox_megu_1->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_megu_1->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_megu_1->setMaximum(9999);
        spinBox_megu_1->setValue(0);
        spinBox_megu_2 = new QSpinBox(SettingDynamicClass);
        spinBox_megu_2->setObjectName(QStringLiteral("spinBox_megu_2"));
        spinBox_megu_2->setGeometry(QRect(322, 479, 50, 22));
        spinBox_megu_2->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_megu_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_megu_2->setMaximum(9999);
        spinBox_megu_2->setValue(0);

        retranslateUi(SettingDynamicClass);

        QMetaObject::connectSlotsByName(SettingDynamicClass);
    } // setupUi

    void retranslateUi(QDialog *SettingDynamicClass)
    {
        SettingDynamicClass->setWindowTitle(QApplication::translate("SettingDynamicClass", "\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_apply->setText(QString());
        pushButton_cancel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SettingDynamicClass: public Ui_SettingDynamicClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDYNAMIC_H
