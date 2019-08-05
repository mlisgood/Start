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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingClass
{
public:
    QPushButton *pushButton_close_window;
    QPushButton *pushButton_close_dialog;
    QComboBox *comboBox_1;
    QPushButton *pushButton_accept_dialog;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QSpinBox *spinBox_1;
    QSpinBox *spinBox_2;
    QListWidget *listWidget_1;
    QListWidget *listWidget_2;
    QLineEdit *lineEdit_1;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_list_1;
    QPushButton *pushButton_list_2;
    QPushButton *pushButton_list_3;
    QPushButton *pushButton_list_4;
    QPushButton *pushButton_list_5;
    QPushButton *pushButton_list_6;

    void setupUi(QDialog *SettingClass)
    {
        if (SettingClass->objectName().isEmpty())
            SettingClass->setObjectName(QStringLiteral("SettingClass"));
        SettingClass->resize(600, 400);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_notepad/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        SettingClass->setWindowIcon(icon);
        SettingClass->setWindowOpacity(5);
        SettingClass->setSizeGripEnabled(false);
        pushButton_close_window = new QPushButton(SettingClass);
        pushButton_close_window->setObjectName(QStringLiteral("pushButton_close_window"));
        pushButton_close_window->setGeometry(QRect(525, 15, 25, 25));
        pushButton_close_window->setStyleSheet(QStringLiteral("border-image: url(:/icon/manage/picture_notepad/icon/window_close.png);"));
        pushButton_close_dialog = new QPushButton(SettingClass);
        pushButton_close_dialog->setObjectName(QStringLiteral("pushButton_close_dialog"));
        pushButton_close_dialog->setGeometry(QRect(372, 350, 90, 40));
        pushButton_close_dialog->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_pressed.png);"));
        comboBox_1 = new QComboBox(SettingClass);
        comboBox_1->setObjectName(QStringLiteral("comboBox_1"));
        comboBox_1->setGeometry(QRect(136, 314, 107, 25));
        comboBox_1->setContextMenuPolicy(Qt::NoContextMenu);
        comboBox_1->setAutoFillBackground(false);
        comboBox_1->setStyleSheet(QStringLiteral(""));
        comboBox_1->setEditable(false);
        comboBox_1->setMaxVisibleItems(7);
        comboBox_1->setMaxCount(2147483646);
        comboBox_1->setInsertPolicy(QComboBox::InsertAtBottom);
        pushButton_accept_dialog = new QPushButton(SettingClass);
        pushButton_accept_dialog->setObjectName(QStringLiteral("pushButton_accept_dialog"));
        pushButton_accept_dialog->setGeometry(QRect(111, 350, 120, 40));
        pushButton_accept_dialog->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_pressed.png);"));
        checkBox_1 = new QCheckBox(SettingClass);
        checkBox_1->setObjectName(QStringLiteral("checkBox_1"));
        checkBox_1->setGeometry(QRect(332, 64, 20, 20));
        checkBox_1->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}"));
        checkBox_2 = new QCheckBox(SettingClass);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(332, 221, 20, 20));
        checkBox_2->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}"));
        checkBox_3 = new QCheckBox(SettingClass);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setGeometry(QRect(332, 253, 20, 20));
        checkBox_3->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}"));
        spinBox_1 = new QSpinBox(SettingClass);
        spinBox_1->setObjectName(QStringLiteral("spinBox_1"));
        spinBox_1->setGeometry(QRect(425, 158, 60, 22));
        spinBox_1->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_1->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_1->setMinimum(1);
        spinBox_1->setMaximum(256);
        spinBox_1->setValue(32);
        spinBox_2 = new QSpinBox(SettingClass);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(444, 190, 60, 22));
        spinBox_2->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
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
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(64);
        spinBox_2->setValue(32);
        listWidget_1 = new QListWidget(SettingClass);
        listWidget_1->setObjectName(QStringLiteral("listWidget_1"));
        listWidget_1->setGeometry(QRect(40, 90, 100, 160));
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
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/line_vertical.png); \n"
"    border: 0px;\n"
"    width: 15px;\n"
"}\n"
"QListWidget QScrollBar::handle:vertical\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_vertical.png);\n"
"    min-height:50px;\n"
"}\n"
"QListWidget QScrollBar::handle:vertical:pressed \n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_vertical.png);\n"
"}\n"
"QListWidget QScrollBar::add-page:vertical\n"
"{\n"
" "
                        "   border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/line_vertical.png);\n"
"}\n"
"QListWidget QScrollBar::sub-page:vertical\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/line_vertical.png);\n"
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
"    image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/down.png);\n"
"}\n"
"QListWidget QScrollBar::up-arrow:vertical\n"
"{\n"
"    image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/up.png);\n"
"}\n"
"QListWidget QScrollBar::horizontal\n"
"{\n"
"    margin: 0px 15px 0px 15px;\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/"
                        "line_horizental.png); \n"
"    border: 0px; \n"
"    height: 15px;\n"
"}\n"
"QListWidget QScrollBar::handle:horizontal\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_horizental.png);\n"
"    min-width:50px;\n"
"}\n"
"QTableWidget QScrollBar::handle:horizontal:pressed\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTreeView QScrollBar::add-page:horizontal\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTreeView QScrollBar::sub-page:horizontal\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_horizental.png);\n"
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
"    border:"
                        " 0px solid black;\n"
"    width:15px\n"
"}\n"
"QTreeView QScrollBar::left-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/left.png);\n"
"}\n"
"QTreeView QScrollBar::right-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/right.png);\n"
"}"));
        listWidget_2 = new QListWidget(SettingClass);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setGeometry(QRect(178, 90, 100, 160));
        listWidget_2->setFont(font);
        listWidget_2->setContextMenuPolicy(Qt::NoContextMenu);
        listWidget_2->setStyleSheet(QString::fromUtf8("QListWidget\n"
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
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/line_vertical.png); \n"
"    border: 0px;\n"
"    width: 15px;\n"
"}\n"
"QListWidget QScrollBar::handle:vertical\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_vertical.png);\n"
"    min-height:50px;\n"
"}\n"
"QListWidget QScrollBar::handle:vertical:pressed \n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_vertical.png);\n"
"}\n"
"QListWidget QScrollBar::add-page:vertical\n"
"{\n"
" "
                        "   border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/line_vertical.png);\n"
"}\n"
"QListWidget QScrollBar::sub-page:vertical\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/line_vertical.png);\n"
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
"    image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/down.png);\n"
"}\n"
"QListWidget QScrollBar::up-arrow:vertical\n"
"{\n"
"    image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/up.png);\n"
"}\n"
"QListWidget QScrollBar::horizontal\n"
"{\n"
"    margin: 0px 15px 0px 15px;\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/"
                        "line_horizental.png); \n"
"    border: 0px; \n"
"    height: 15px;\n"
"}\n"
"QListWidget QScrollBar::handle:horizontal\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_horizental.png);\n"
"    min-width:50px;\n"
"}\n"
"QTableWidget QScrollBar::handle:horizontal:pressed\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTreeView QScrollBar::add-page:horizontal\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTreeView QScrollBar::sub-page:horizontal\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_horizental.png);\n"
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
"    border:"
                        " 0px solid black;\n"
"    width:15px\n"
"}\n"
"QTreeView QScrollBar::left-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/left.png);\n"
"}\n"
"QTreeView QScrollBar::right-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/right.png);\n"
"}"));
        lineEdit_1 = new QLineEdit(SettingClass);
        lineEdit_1->setObjectName(QStringLiteral("lineEdit_1"));
        lineEdit_1->setGeometry(QRect(40, 260, 100, 20));
        lineEdit_1->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_1->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background:rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        lineEdit_1->setMaxLength(255);
        lineEdit_2 = new QLineEdit(SettingClass);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(178, 260, 100, 20));
        lineEdit_2->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_2->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background:rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}"));
        lineEdit_2->setMaxLength(255);
        pushButton_list_1 = new QPushButton(SettingClass);
        pushButton_list_1->setObjectName(QStringLiteral("pushButton_list_1"));
        pushButton_list_1->setGeometry(QRect(40, 290, 15, 15));
        pushButton_list_1->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_setting_add_item.png);"));
        pushButton_list_2 = new QPushButton(SettingClass);
        pushButton_list_2->setObjectName(QStringLiteral("pushButton_list_2"));
        pushButton_list_2->setGeometry(QRect(83, 290, 15, 15));
        pushButton_list_2->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_setting_remove_item.png);"));
        pushButton_list_3 = new QPushButton(SettingClass);
        pushButton_list_3->setObjectName(QStringLiteral("pushButton_list_3"));
        pushButton_list_3->setGeometry(QRect(126, 290, 15, 15));
        pushButton_list_3->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_setting_remove_all_item.png);"));
        pushButton_list_4 = new QPushButton(SettingClass);
        pushButton_list_4->setObjectName(QStringLiteral("pushButton_list_4"));
        pushButton_list_4->setGeometry(QRect(178, 290, 15, 15));
        pushButton_list_4->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_setting_add_item.png);"));
        pushButton_list_5 = new QPushButton(SettingClass);
        pushButton_list_5->setObjectName(QStringLiteral("pushButton_list_5"));
        pushButton_list_5->setGeometry(QRect(221, 290, 15, 15));
        pushButton_list_5->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_setting_remove_item.png);"));
        pushButton_list_6 = new QPushButton(SettingClass);
        pushButton_list_6->setObjectName(QStringLiteral("pushButton_list_6"));
        pushButton_list_6->setGeometry(QRect(264, 290, 15, 15));
        pushButton_list_6->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_setting_remove_all_item.png);"));

        retranslateUi(SettingClass);

        comboBox_1->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingClass);
    } // setupUi

    void retranslateUi(QDialog *SettingClass)
    {
        SettingClass->setWindowTitle(QApplication::translate("SettingClass", "\345\205\266\344\273\226\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_close_window->setText(QString());
        pushButton_close_dialog->setText(QString());
        comboBox_1->clear();
        comboBox_1->insertItems(0, QStringList()
         << QApplication::translate("SettingClass", "\346\226\207\346\234\254\346\226\271\345\274\217", Q_NULLPTR)
         << QApplication::translate("SettingClass", "\344\272\214\350\277\233\345\210\266\346\226\271\345\274\217", Q_NULLPTR)
        );
        pushButton_accept_dialog->setText(QString());
        checkBox_1->setText(QString());
        checkBox_2->setText(QString());
        checkBox_3->setText(QString());
        pushButton_list_1->setText(QString());
        pushButton_list_2->setText(QString());
        pushButton_list_3->setText(QString());
        pushButton_list_4->setText(QString());
        pushButton_list_5->setText(QString());
        pushButton_list_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SettingClass: public Ui_SettingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
