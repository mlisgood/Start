/********************************************************************************
** Form generated from reading UI file 'Desktop.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESKTOP_H
#define UI_DESKTOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DesktopClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *DesktopClass)
    {
        if (DesktopClass->objectName().isEmpty())
            DesktopClass->setObjectName(QStringLiteral("DesktopClass"));
        DesktopClass->resize(400, 380);
        DesktopClass->setAcceptDrops(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/picture_desktop/icon/picture_desktop/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        DesktopClass->setWindowIcon(icon);
        centralWidget = new QWidget(DesktopClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        DesktopClass->setCentralWidget(centralWidget);

        retranslateUi(DesktopClass);

        QMetaObject::connectSlotsByName(DesktopClass);
    } // setupUi

    void retranslateUi(QMainWindow *DesktopClass)
    {
        DesktopClass->setWindowTitle(QApplication::translate("DesktopClass", "\344\270\200\347\267\222\343\201\253\343\203\242\343\203\225\343\203\242\343\203\225\343\201\227\343\202\210\343\203\274", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DesktopClass: public Ui_DesktopClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESKTOP_H
