/********************************************************************************
** Form generated from reading UI file 'Replace.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPLACE_H
#define UI_REPLACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ReplaceClass
{
public:
    QPushButton *pushButton_close_window;
    QLineEdit *lineEdit_1;
    QPushButton *pushButton_next;
    QPushButton *pushButton_exit;
    QPushButton *pushButton_last;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QPushButton *pushButton_hide_window;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_all;

    void setupUi(QDialog *ReplaceClass)
    {
        if (ReplaceClass->objectName().isEmpty())
            ReplaceClass->setObjectName(QStringLiteral("ReplaceClass"));
        ReplaceClass->resize(600, 200);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_notepad/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        ReplaceClass->setWindowIcon(icon);
        ReplaceClass->setWindowOpacity(5);
        pushButton_close_window = new QPushButton(ReplaceClass);
        pushButton_close_window->setObjectName(QStringLiteral("pushButton_close_window"));
        pushButton_close_window->setGeometry(QRect(525, 15, 25, 25));
        pushButton_close_window->setStyleSheet(QStringLiteral("border-image: url(:/icon/manage/picture_notepad/icon/window_close.png);"));
        lineEdit_1 = new QLineEdit(ReplaceClass);
        lineEdit_1->setObjectName(QStringLiteral("lineEdit_1"));
        lineEdit_1->setGeometry(QRect(336, 50, 130, 20));
        lineEdit_1->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_1->setInputMethodHints(Qt::ImhNone);
        pushButton_next = new QPushButton(ReplaceClass);
        pushButton_next->setObjectName(QStringLiteral("pushButton_next"));
        pushButton_next->setGeometry(QRect(475, 82, 100, 40));
        pushButton_next->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_next_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_next_pressed.png);"));
        pushButton_exit = new QPushButton(ReplaceClass);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(422, 150, 100, 40));
        pushButton_exit->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_exit_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_exit_pressed.png);"));
        pushButton_last = new QPushButton(ReplaceClass);
        pushButton_last->setObjectName(QStringLiteral("pushButton_last"));
        pushButton_last->setGeometry(QRect(475, 40, 100, 40));
        pushButton_last->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_last_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_last_pressed.png);"));
        checkBox_1 = new QCheckBox(ReplaceClass);
        checkBox_1->setObjectName(QStringLiteral("checkBox_1"));
        checkBox_1->setGeometry(QRect(230, 130, 20, 20));
        checkBox_1->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}"));
        checkBox_2 = new QCheckBox(ReplaceClass);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(461, 130, 20, 20));
        checkBox_2->setStyleSheet(QLatin1String("QCheckBox{spacing: 5px;color: white;}\n"
"QCheckBox::indicator {width: 20px;height: 20px;}\n"
"QCheckBox::indicator:enabled:unchecked {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:hover  {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:unchecked:pressed {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_off.png);}\n"
"QCheckBox::indicator:enabled:checked {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:hover {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}\n"
"QCheckBox::indicator:enabled:checked:pressed {image: url(:/picture_notepad/checkbox/picture_notepad/checkbox_style/checkbox_on.png);}"));
        pushButton_hide_window = new QPushButton(ReplaceClass);
        pushButton_hide_window->setObjectName(QStringLiteral("pushButton_hide_window"));
        pushButton_hide_window->setGeometry(QRect(485, 15, 25, 25));
        pushButton_hide_window->setStyleSheet(QStringLiteral("border-image: url(:/icon/manage/picture_notepad/icon/window_hide.png);"));
        lineEdit_2 = new QLineEdit(ReplaceClass);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(336, 92, 130, 20));
        lineEdit_2->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit_2->setInputMethodHints(Qt::ImhNone);
        pushButton_all = new QPushButton(ReplaceClass);
        pushButton_all->setObjectName(QStringLiteral("pushButton_all"));
        pushButton_all->setGeometry(QRect(252, 150, 100, 40));
        pushButton_all->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_all_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_all_pressed.png);"));

        retranslateUi(ReplaceClass);
        QObject::connect(pushButton_hide_window, SIGNAL(clicked()), ReplaceClass, SLOT(showMinimized()));

        QMetaObject::connectSlotsByName(ReplaceClass);
    } // setupUi

    void retranslateUi(QDialog *ReplaceClass)
    {
        ReplaceClass->setWindowTitle(QApplication::translate("ReplaceClass", "\346\233\277\346\215\242", Q_NULLPTR));
        pushButton_close_window->setText(QString());
        pushButton_next->setText(QString());
        pushButton_exit->setText(QString());
        pushButton_last->setText(QString());
        checkBox_1->setText(QString());
        checkBox_2->setText(QString());
        pushButton_hide_window->setText(QString());
        pushButton_all->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ReplaceClass: public Ui_ReplaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPLACE_H
