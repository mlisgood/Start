/********************************************************************************
** Form generated from reading UI file 'Help.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELP_H
#define UI_HELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_HelpClass
{
public:
    QPushButton *pushButton_close_window;
    QPushButton *pushButton_close_dialog;

    void setupUi(QDialog *HelpClass)
    {
        if (HelpClass->objectName().isEmpty())
            HelpClass->setObjectName(QStringLiteral("HelpClass"));
        HelpClass->resize(600, 200);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_notepad/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        HelpClass->setWindowIcon(icon);
        HelpClass->setWindowOpacity(5);
        pushButton_close_window = new QPushButton(HelpClass);
        pushButton_close_window->setObjectName(QStringLiteral("pushButton_close_window"));
        pushButton_close_window->setGeometry(QRect(525, 15, 25, 25));
        pushButton_close_window->setStyleSheet(QStringLiteral("border-image: url(:/icon/manage/picture_notepad/icon/window_close.png);"));
        pushButton_close_dialog = new QPushButton(HelpClass);
        pushButton_close_dialog->setObjectName(QStringLiteral("pushButton_close_dialog"));
        pushButton_close_dialog->setGeometry(QRect(310, 140, 150, 60));
        pushButton_close_dialog->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_main_exit_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_main_exit_pressed.png);"));

        retranslateUi(HelpClass);

        QMetaObject::connectSlotsByName(HelpClass);
    } // setupUi

    void retranslateUi(QDialog *HelpClass)
    {
        HelpClass->setWindowTitle(QApplication::translate("HelpClass", "\345\205\263\344\272\216\346\210\221", Q_NULLPTR));
        pushButton_close_window->setText(QString());
        pushButton_close_dialog->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HelpClass: public Ui_HelpClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELP_H
