/********************************************************************************
** Form generated from reading UI file 'CreateObject.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEOBJECT_H
#define UI_CREATEOBJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_CreateObjectClass
{
public:

    void setupUi(QDialog *CreateObjectClass)
    {
        if (CreateObjectClass->objectName().isEmpty())
            CreateObjectClass->setObjectName(QStringLiteral("CreateObjectClass"));
        CreateObjectClass->resize(92, 16);

        retranslateUi(CreateObjectClass);

        QMetaObject::connectSlotsByName(CreateObjectClass);
    } // setupUi

    void retranslateUi(QDialog *CreateObjectClass)
    {
        CreateObjectClass->setWindowTitle(QApplication::translate("CreateObjectClass", "undefine", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CreateObjectClass: public Ui_CreateObjectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEOBJECT_H
