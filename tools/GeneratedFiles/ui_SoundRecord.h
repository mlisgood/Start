/********************************************************************************
** Form generated from reading UI file 'SoundRecord.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOUNDRECORD_H
#define UI_SOUNDRECORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SoundRecordClass
{
public:
    QPushButton *pushButton_new;
    QPushButton *pushButton_save;

    void setupUi(QDialog *SoundRecordClass)
    {
        if (SoundRecordClass->objectName().isEmpty())
            SoundRecordClass->setObjectName(QStringLiteral("SoundRecordClass"));
        SoundRecordClass->resize(140, 200);
        SoundRecordClass->setWindowOpacity(5);
        pushButton_new = new QPushButton(SoundRecordClass);
        pushButton_new->setObjectName(QStringLiteral("pushButton_new"));
        pushButton_new->setGeometry(QRect(14, 55, 15, 15));
        pushButton_new->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));
        pushButton_save = new QPushButton(SoundRecordClass);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setGeometry(QRect(114, 99, 15, 15));
        pushButton_save->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"}"));

        retranslateUi(SoundRecordClass);

        QMetaObject::connectSlotsByName(SoundRecordClass);
    } // setupUi

    void retranslateUi(QDialog *SoundRecordClass)
    {
        SoundRecordClass->setWindowTitle(QApplication::translate("SoundRecordClass", "undefined", Q_NULLPTR));
        pushButton_new->setText(QString());
        pushButton_save->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SoundRecordClass: public Ui_SoundRecordClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOUNDRECORD_H
