/********************************************************************************
** Form generated from reading UI file 'Screenshot.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENSHOT_H
#define UI_SCREENSHOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ScreenshotClass
{
public:

    void setupUi(QDialog *ScreenshotClass)
    {
        if (ScreenshotClass->objectName().isEmpty())
            ScreenshotClass->setObjectName(QStringLiteral("ScreenshotClass"));
        ScreenshotClass->resize(400, 300);

        retranslateUi(ScreenshotClass);

        QMetaObject::connectSlotsByName(ScreenshotClass);
    } // setupUi

    void retranslateUi(QDialog *ScreenshotClass)
    {
        ScreenshotClass->setWindowTitle(QApplication::translate("ScreenshotClass", "undefine", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ScreenshotClass: public Ui_ScreenshotClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENSHOT_H
