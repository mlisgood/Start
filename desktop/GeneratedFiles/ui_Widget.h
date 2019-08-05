/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_WidgetClass
{
public:

    void setupUi(QDialog *WidgetClass)
    {
        if (WidgetClass->objectName().isEmpty())
            WidgetClass->setObjectName(QStringLiteral("WidgetClass"));
        WidgetClass->resize(200, 200);
        WidgetClass->setAcceptDrops(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/picture_desktop/icon/picture_desktop/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        WidgetClass->setWindowIcon(icon);
        WidgetClass->setWindowOpacity(5);

        retranslateUi(WidgetClass);

        QMetaObject::connectSlotsByName(WidgetClass);
    } // setupUi

    void retranslateUi(QDialog *WidgetClass)
    {
        WidgetClass->setWindowTitle(QApplication::translate("WidgetClass", "undefine - widget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WidgetClass: public Ui_WidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
