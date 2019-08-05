/********************************************************************************
** Form generated from reading UI file 'CounterSet.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COUNTERSET_H
#define UI_COUNTERSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CounterSetClass
{
public:
    QRadioButton *radioButton_type_1;
    QRadioButton *radioButton_type_2;
    QRadioButton *radioButton_voice_1;
    QRadioButton *radioButton_voice_3;
    QRadioButton *radioButton_voice_5;
    QRadioButton *radioButton_voice_2;
    QRadioButton *radioButton_voice_4;
    QSpinBox *spinBox_hour;
    QSpinBox *spinBox_minute;
    QSpinBox *spinBox_second;
    QRadioButton *radioButton_dialog_1;
    QRadioButton *radioButton_dialog_2;
    QPushButton *pushButton_apply;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *CounterSetClass)
    {
        if (CounterSetClass->objectName().isEmpty())
            CounterSetClass->setObjectName(QStringLiteral("CounterSetClass"));
        CounterSetClass->resize(400, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/picture_tools/icon/picture_tools/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        CounterSetClass->setWindowIcon(icon);
        CounterSetClass->setWindowOpacity(5);
        radioButton_type_1 = new QRadioButton(CounterSetClass);
        radioButton_type_1->setObjectName(QStringLiteral("radioButton_type_1"));
        radioButton_type_1->setGeometry(QRect(70, 115, 20, 20));
        radioButton_type_1->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}"));
        radioButton_type_2 = new QRadioButton(CounterSetClass);
        radioButton_type_2->setObjectName(QStringLiteral("radioButton_type_2"));
        radioButton_type_2->setGeometry(QRect(70, 147, 20, 20));
        radioButton_type_2->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}"));
        radioButton_voice_1 = new QRadioButton(CounterSetClass);
        radioButton_voice_1->setObjectName(QStringLiteral("radioButton_voice_1"));
        radioButton_voice_1->setGeometry(QRect(70, 303, 20, 20));
        radioButton_voice_1->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}"));
        radioButton_voice_3 = new QRadioButton(CounterSetClass);
        radioButton_voice_3->setObjectName(QStringLiteral("radioButton_voice_3"));
        radioButton_voice_3->setGeometry(QRect(70, 335, 20, 20));
        radioButton_voice_3->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}"));
        radioButton_voice_5 = new QRadioButton(CounterSetClass);
        radioButton_voice_5->setObjectName(QStringLiteral("radioButton_voice_5"));
        radioButton_voice_5->setGeometry(QRect(70, 367, 20, 20));
        radioButton_voice_5->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}"));
        radioButton_voice_2 = new QRadioButton(CounterSetClass);
        radioButton_voice_2->setObjectName(QStringLiteral("radioButton_voice_2"));
        radioButton_voice_2->setGeometry(QRect(227, 303, 20, 20));
        radioButton_voice_2->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}"));
        radioButton_voice_4 = new QRadioButton(CounterSetClass);
        radioButton_voice_4->setObjectName(QStringLiteral("radioButton_voice_4"));
        radioButton_voice_4->setGeometry(QRect(227, 335, 20, 20));
        radioButton_voice_4->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}"));
        spinBox_hour = new QSpinBox(CounterSetClass);
        spinBox_hour->setObjectName(QStringLiteral("spinBox_hour"));
        spinBox_hour->setGeometry(QRect(70, 225, 40, 22));
        spinBox_hour->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_hour->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/up_button.png);     \n"
"    background: #FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/up_button.png);   \n"
"    background: #FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"}"));
        spinBox_minute = new QSpinBox(CounterSetClass);
        spinBox_minute->setObjectName(QStringLiteral("spinBox_minute"));
        spinBox_minute->setGeometry(QRect(125, 225, 40, 22));
        spinBox_minute->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_minute->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/up_button.png);     \n"
"    background: #FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/up_button.png);   \n"
"    background: #FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"}"));
        spinBox_minute->setMaximum(59);
        spinBox_second = new QSpinBox(CounterSetClass);
        spinBox_second->setObjectName(QStringLiteral("spinBox_second"));
        spinBox_second->setGeometry(QRect(180, 225, 40, 22));
        spinBox_second->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_second->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/up_button.png);     \n"
"    background: #FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/up_button.png);   \n"
"    background: #FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_tools/spinbox/picture_tools/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"}"));
        spinBox_second->setMinimum(0);
        spinBox_second->setMaximum(59);
        spinBox_second->setValue(0);
        radioButton_dialog_1 = new QRadioButton(CounterSetClass);
        radioButton_dialog_1->setObjectName(QStringLiteral("radioButton_dialog_1"));
        radioButton_dialog_1->setGeometry(QRect(70, 450, 20, 20));
        radioButton_dialog_1->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}"));
        radioButton_dialog_2 = new QRadioButton(CounterSetClass);
        radioButton_dialog_2->setObjectName(QStringLiteral("radioButton_dialog_2"));
        radioButton_dialog_2->setGeometry(QRect(70, 482, 20, 20));
        radioButton_dialog_2->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_tools/radiobutton/picture_tools/radiobutton_style/radiobutton_on.png);}"));
        pushButton_apply = new QPushButton(CounterSetClass);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(100, 536, 41, 23));
        pushButton_apply->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_cancel = new QPushButton(CounterSetClass);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(260, 536, 41, 23));
        pushButton_cancel->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));

        retranslateUi(CounterSetClass);

        QMetaObject::connectSlotsByName(CounterSetClass);
    } // setupUi

    void retranslateUi(QDialog *CounterSetClass)
    {
        CounterSetClass->setWindowTitle(QApplication::translate("CounterSetClass", "\350\256\241\346\227\266\345\231\250\350\256\276\347\275\256", Q_NULLPTR));
        radioButton_type_1->setText(QString());
        radioButton_type_2->setText(QString());
        radioButton_voice_1->setText(QString());
        radioButton_voice_3->setText(QString());
        radioButton_voice_5->setText(QString());
        radioButton_voice_2->setText(QString());
        radioButton_voice_4->setText(QString());
        radioButton_dialog_1->setText(QString());
        radioButton_dialog_2->setText(QString());
        pushButton_apply->setText(QString());
        pushButton_cancel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CounterSetClass: public Ui_CounterSetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COUNTERSET_H
