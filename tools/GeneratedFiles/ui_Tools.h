/********************************************************************************
** Form generated from reading UI file 'Tools.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLS_H
#define UI_TOOLS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToolsClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *ToolsClass)
    {
        if (ToolsClass->objectName().isEmpty())
            ToolsClass->setObjectName(QStringLiteral("ToolsClass"));
        ToolsClass->resize(600, 400);
        QIcon icon;
        icon.addFile(QStringLiteral(":/picture_tools/icon/picture_tools/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        ToolsClass->setWindowIcon(icon);
        centralWidget = new QWidget(ToolsClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ToolsClass->setCentralWidget(centralWidget);

        retranslateUi(ToolsClass);

        QMetaObject::connectSlotsByName(ToolsClass);
    } // setupUi

    void retranslateUi(QMainWindow *ToolsClass)
    {
        ToolsClass->setWindowTitle(QApplication::translate("ToolsClass", "undefine - tools", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ToolsClass: public Ui_ToolsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLS_H
