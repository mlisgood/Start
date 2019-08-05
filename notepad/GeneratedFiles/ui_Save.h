/********************************************************************************
** Form generated from reading UI file 'Save.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVE_H
#define UI_SAVE_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SaveClass
{
public:
    QPushButton *pushButton_close_window;
    QPushButton *pushButton_choice_1;
    QPushButton *pushButton_choice_2;
    QPushButton *pushButton_choice_3;

    void setupUi(QDialog *SaveClass)
    {
        if (SaveClass->objectName().isEmpty())
            SaveClass->setObjectName(QStringLiteral("SaveClass"));
        SaveClass->resize(600, 200);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_notepad/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        SaveClass->setWindowIcon(icon);
        SaveClass->setWindowOpacity(5);
        SaveClass->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        pushButton_close_window = new QPushButton(SaveClass);
        pushButton_close_window->setObjectName(QStringLiteral("pushButton_close_window"));
        pushButton_close_window->setGeometry(QRect(525, 15, 25, 25));
        pushButton_close_window->setStyleSheet(QStringLiteral("border-image: url(:/icon/manage/picture_notepad/icon/window_close.png);"));
        pushButton_choice_1 = new QPushButton(SaveClass);
        pushButton_choice_1->setObjectName(QStringLiteral("pushButton_choice_1"));
        pushButton_choice_1->setGeometry(QRect(225, 140, 100, 30));
        pushButton_choice_1->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_save_choice_1_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_save_choice_1_pressed.png);"));
        pushButton_choice_2 = new QPushButton(SaveClass);
        pushButton_choice_2->setObjectName(QStringLiteral("pushButton_choice_2"));
        pushButton_choice_2->setGeometry(QRect(328, 140, 100, 30));
        pushButton_choice_2->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_save_choice_2_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_save_choice_2_pressed.png);"));
        pushButton_choice_3 = new QPushButton(SaveClass);
        pushButton_choice_3->setObjectName(QStringLiteral("pushButton_choice_3"));
        pushButton_choice_3->setGeometry(QRect(445, 140, 100, 30));
        pushButton_choice_3->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_save_choice_3_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_save_choice_3_pressed.png);"));
        QWidget::setTabOrder(pushButton_close_window, pushButton_choice_1);
        QWidget::setTabOrder(pushButton_choice_1, pushButton_choice_2);
        QWidget::setTabOrder(pushButton_choice_2, pushButton_choice_3);

        retranslateUi(SaveClass);

        QMetaObject::connectSlotsByName(SaveClass);
    } // setupUi

    void retranslateUi(QDialog *SaveClass)
    {
        SaveClass->setWindowTitle(QApplication::translate("SaveClass", "\346\226\207\344\273\266\350\277\230\346\262\241\344\277\235\345\255\230\345\221\242\342\200\246\342\200\246", Q_NULLPTR));
        pushButton_close_window->setText(QString());
        pushButton_choice_1->setText(QString());
        pushButton_choice_2->setText(QString());
        pushButton_choice_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SaveClass: public Ui_SaveClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVE_H
