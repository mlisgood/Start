/********************************************************************************
** Form generated from reading UI file 'Print.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINT_H
#define UI_PRINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_PrintClass
{
public:
    QPushButton *pushButton_close_window;
    QPushButton *pushButton_close_dialog;
    QPushButton *pushButton_accept_dialog;
    QComboBox *comboBox_printer;
    QComboBox *comboBox_size;
    QSpinBox *spinBox_up;
    QSpinBox *spinBox_down;
    QSpinBox *spinBox_left;
    QSpinBox *spinBox_right;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QLabel *label_pixmap_background;
    QLabel *label_pixmap_chara;
    QLabel *label_pixmap_information;
    QLabel *label_pixmap_margin;

    void setupUi(QDialog *PrintClass)
    {
        if (PrintClass->objectName().isEmpty())
            PrintClass->setObjectName(QStringLiteral("PrintClass"));
        PrintClass->resize(600, 201);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_notepad/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        PrintClass->setWindowIcon(icon);
        PrintClass->setWindowOpacity(5);
        pushButton_close_window = new QPushButton(PrintClass);
        pushButton_close_window->setObjectName(QStringLiteral("pushButton_close_window"));
        pushButton_close_window->setGeometry(QRect(525, 15, 25, 25));
        pushButton_close_window->setStyleSheet(QStringLiteral("border-image: url(:/icon/manage/picture_notepad/icon/window_close.png);"));
        pushButton_close_dialog = new QPushButton(PrintClass);
        pushButton_close_dialog->setObjectName(QStringLiteral("pushButton_close_dialog"));
        pushButton_close_dialog->setGeometry(QRect(435, 150, 90, 40));
        pushButton_close_dialog->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_pressed.png);"));
        pushButton_accept_dialog = new QPushButton(PrintClass);
        pushButton_accept_dialog->setObjectName(QStringLiteral("pushButton_accept_dialog"));
        pushButton_accept_dialog->setGeometry(QRect(245, 150, 120, 40));
        pushButton_accept_dialog->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_pressed.png);"));
        comboBox_printer = new QComboBox(PrintClass);
        comboBox_printer->setObjectName(QStringLiteral("comboBox_printer"));
        comboBox_printer->setGeometry(QRect(346, 40, 211, 25));
        comboBox_printer->setContextMenuPolicy(Qt::NoContextMenu);
        comboBox_printer->setAutoFillBackground(false);
        comboBox_printer->setStyleSheet(QStringLiteral(""));
        comboBox_printer->setEditable(false);
        comboBox_printer->setMaxVisibleItems(7);
        comboBox_printer->setMaxCount(2147483646);
        comboBox_printer->setInsertPolicy(QComboBox::InsertAtBottom);
        comboBox_size = new QComboBox(PrintClass);
        comboBox_size->setObjectName(QStringLiteral("comboBox_size"));
        comboBox_size->setGeometry(QRect(346, 72, 211, 25));
        comboBox_size->setContextMenuPolicy(Qt::NoContextMenu);
        comboBox_size->setAutoFillBackground(false);
        comboBox_size->setStyleSheet(QStringLiteral(""));
        comboBox_size->setEditable(false);
        comboBox_size->setMaxVisibleItems(7);
        comboBox_size->setMaxCount(2147483646);
        comboBox_size->setInsertPolicy(QComboBox::InsertAtBottom);
        spinBox_up = new QSpinBox(PrintClass);
        spinBox_up->setObjectName(QStringLiteral("spinBox_up"));
        spinBox_up->setGeometry(QRect(363, 103, 35, 22));
        spinBox_up->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_up->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/up_button.png);     \n"
"    background: #FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/up_button.png);   \n"
"    background: #FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"}"));
        spinBox_up->setMaximum(1000);
        spinBox_up->setValue(20);
        spinBox_down = new QSpinBox(PrintClass);
        spinBox_down->setObjectName(QStringLiteral("spinBox_down"));
        spinBox_down->setGeometry(QRect(416, 103, 35, 22));
        spinBox_down->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_down->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/up_button.png);     \n"
"    background: #FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/up_button.png);   \n"
"    background: #FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"}"));
        spinBox_down->setMaximum(1000);
        spinBox_down->setValue(20);
        spinBox_left = new QSpinBox(PrintClass);
        spinBox_left->setObjectName(QStringLiteral("spinBox_left"));
        spinBox_left->setGeometry(QRect(469, 103, 35, 22));
        spinBox_left->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_left->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/up_button.png);     \n"
"    background: #FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/up_button.png);   \n"
"    background: #FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"}"));
        spinBox_left->setMaximum(1000);
        spinBox_left->setValue(20);
        spinBox_right = new QSpinBox(PrintClass);
        spinBox_right->setObjectName(QStringLiteral("spinBox_right"));
        spinBox_right->setGeometry(QRect(522, 103, 35, 22));
        spinBox_right->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_right->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/up_button.png);     \n"
"    background: #FDEAD3;\n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/up_button.png);   \n"
"    background: #FDEAD3;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_notepad/spinbox/picture_notepad/spinbox_style/down_button.png); \n"
"    background: #FDEAD3;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #804C47;\n"
"    background: #FDEAD3;\n"
"}"));
        spinBox_right->setMaximum(1000);
        spinBox_right->setValue(20);
        radioButton_1 = new QRadioButton(PrintClass);
        radioButton_1->setObjectName(QStringLiteral("radioButton_1"));
        radioButton_1->setGeometry(QRect(346, 134, 25, 22));
        radioButton_1->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}"));
        radioButton_2 = new QRadioButton(PrintClass);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(489, 134, 25, 22));
        radioButton_2->setStyleSheet(QLatin1String("QRadioButton{spacing: 5px;color: white;}\n"
"QRadioButton::indicator {width: 20px;height: 20px;}\n"
"QRadioButton::indicator:enabled:unchecked {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:hover  {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:unchecked:pressed {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QRadioButton::indicator:enabled:checked {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}\n"
"QRadioButton::indicator:enabled:checked:hover {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}\n"
"QRadioButton::indicator:enabled:checked:pressed {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}"));
        radioButton_2->setChecked(true);
        label_pixmap_background = new QLabel(PrintClass);
        label_pixmap_background->setObjectName(QStringLiteral("label_pixmap_background"));
        label_pixmap_background->setGeometry(QRect(0, 0, 600, 200));
        label_pixmap_chara = new QLabel(PrintClass);
        label_pixmap_chara->setObjectName(QStringLiteral("label_pixmap_chara"));
        label_pixmap_chara->setGeometry(QRect(0, 0, 200, 200));
        label_pixmap_information = new QLabel(PrintClass);
        label_pixmap_information->setObjectName(QStringLiteral("label_pixmap_information"));
        label_pixmap_information->setGeometry(QRect(200, 0, 400, 200));
        label_pixmap_margin = new QLabel(PrintClass);
        label_pixmap_margin->setObjectName(QStringLiteral("label_pixmap_margin"));
        label_pixmap_margin->setGeometry(QRect(0, 0, 600, 200));
        label_pixmap_background->raise();
        label_pixmap_chara->raise();
        label_pixmap_information->raise();
        label_pixmap_margin->raise();
        pushButton_close_window->raise();
        pushButton_close_dialog->raise();
        pushButton_accept_dialog->raise();
        comboBox_printer->raise();
        comboBox_size->raise();
        spinBox_up->raise();
        spinBox_down->raise();
        spinBox_left->raise();
        spinBox_right->raise();
        radioButton_1->raise();
        radioButton_2->raise();

        retranslateUi(PrintClass);

        QMetaObject::connectSlotsByName(PrintClass);
    } // setupUi

    void retranslateUi(QDialog *PrintClass)
    {
        PrintClass->setWindowTitle(QApplication::translate("PrintClass", "\346\211\223\345\215\260", Q_NULLPTR));
        pushButton_close_window->setText(QString());
        pushButton_close_dialog->setText(QString());
        pushButton_accept_dialog->setText(QString());
        comboBox_printer->setCurrentText(QString());
        comboBox_size->setCurrentText(QString());
        radioButton_1->setText(QString());
        radioButton_2->setText(QString());
        label_pixmap_background->setText(QString());
        label_pixmap_chara->setText(QString());
        label_pixmap_information->setText(QString());
        label_pixmap_margin->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PrintClass: public Ui_PrintClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINT_H
