/********************************************************************************
** Form generated from reading UI file 'Lock.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCK_H
#define UI_LOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LockClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_select_1;
    QPushButton *pushButton_select_2;
    QPushButton *pushButton_select_3;
    QPushButton *pushButton_close_window;
    QPushButton *pushButton_set;

    void setupUi(QMainWindow *LockClass)
    {
        if (LockClass->objectName().isEmpty())
            LockClass->setObjectName(QStringLiteral("LockClass"));
        LockClass->resize(400, 400);
        LockClass->setAcceptDrops(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_lock/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        LockClass->setWindowIcon(icon);
        centralWidget = new QWidget(LockClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_select_1 = new QPushButton(centralWidget);
        pushButton_select_1->setObjectName(QStringLiteral("pushButton_select_1"));
        pushButton_select_1->setGeometry(QRect(90, 90, 200, 60));
        pushButton_select_1->setMaximumSize(QSize(16777215, 16777215));
        pushButton_select_1->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_normal_1.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_pressed_1.png);"));
        pushButton_select_2 = new QPushButton(centralWidget);
        pushButton_select_2->setObjectName(QStringLiteral("pushButton_select_2"));
        pushButton_select_2->setGeometry(QRect(90, 170, 200, 60));
        pushButton_select_2->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_normal_2.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_pressed_2.png);"));
        pushButton_select_3 = new QPushButton(centralWidget);
        pushButton_select_3->setObjectName(QStringLiteral("pushButton_select_3"));
        pushButton_select_3->setGeometry(QRect(90, 250, 200, 60));
        pushButton_select_3->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_normal_3.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_pressed_3.png);"));
        pushButton_close_window = new QPushButton(centralWidget);
        pushButton_close_window->setObjectName(QStringLiteral("pushButton_close_window"));
        pushButton_close_window->setGeometry(QRect(325, 15, 25, 25));
        pushButton_close_window->setStyleSheet(QStringLiteral("border-image: url(:/icon/mainicon/picture_lock/icon/window_close.png);"));
        pushButton_set = new QPushButton(centralWidget);
        pushButton_set->setObjectName(QStringLiteral("pushButton_set"));
        pushButton_set->setGeometry(QRect(280, 15, 25, 25));
        pushButton_set->setStyleSheet(QStringLiteral("border-image: url(:/icon/mainicon/picture_lock/icon/window_setting.png);"));
        LockClass->setCentralWidget(centralWidget);

        retranslateUi(LockClass);

        QMetaObject::connectSlotsByName(LockClass);
    } // setupUi

    void retranslateUi(QMainWindow *LockClass)
    {
        LockClass->setWindowTitle(QApplication::translate("LockClass", "\346\226\207\344\273\266\345\212\240\345\257\206", Q_NULLPTR));
        pushButton_select_1->setText(QString());
        pushButton_select_2->setText(QString());
        pushButton_select_3->setText(QString());
        pushButton_close_window->setText(QString());
        pushButton_set->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LockClass: public Ui_LockClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCK_H
