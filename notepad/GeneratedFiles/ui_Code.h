/********************************************************************************
** Form generated from reading UI file 'Code.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODE_H
#define UI_CODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CodeClass
{
public:
    QPushButton *pushButton_close_window;
    QPushButton *pushButton_close_dialog;
    QPushButton *pushButton_accept_dialog;
    QComboBox *comboBox_1;
    QLabel *label;

    void setupUi(QDialog *CodeClass)
    {
        if (CodeClass->objectName().isEmpty())
            CodeClass->setObjectName(QStringLiteral("CodeClass"));
        CodeClass->resize(600, 201);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_notepad/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        CodeClass->setWindowIcon(icon);
        CodeClass->setWindowOpacity(5);
        pushButton_close_window = new QPushButton(CodeClass);
        pushButton_close_window->setObjectName(QStringLiteral("pushButton_close_window"));
        pushButton_close_window->setGeometry(QRect(525, 15, 25, 25));
        pushButton_close_window->setStyleSheet(QStringLiteral("border-image: url(:/icon/manage/picture_notepad/icon/window_close.png);"));
        pushButton_close_dialog = new QPushButton(CodeClass);
        pushButton_close_dialog->setObjectName(QStringLiteral("pushButton_close_dialog"));
        pushButton_close_dialog->setGeometry(QRect(435, 150, 90, 40));
        pushButton_close_dialog->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_pressed.png);"));
        pushButton_accept_dialog = new QPushButton(CodeClass);
        pushButton_accept_dialog->setObjectName(QStringLiteral("pushButton_accept_dialog"));
        pushButton_accept_dialog->setGeometry(QRect(245, 150, 120, 40));
        pushButton_accept_dialog->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_pressed.png);"));
        comboBox_1 = new QComboBox(CodeClass);
        comboBox_1->setObjectName(QStringLiteral("comboBox_1"));
        comboBox_1->setGeometry(QRect(375, 45, 154, 25));
        comboBox_1->setContextMenuPolicy(Qt::NoContextMenu);
        comboBox_1->setAutoFillBackground(false);
        comboBox_1->setStyleSheet(QStringLiteral(""));
        comboBox_1->setEditable(false);
        comboBox_1->setMaxVisibleItems(7);
        comboBox_1->setMaxCount(2147483646);
        comboBox_1->setInsertPolicy(QComboBox::InsertAtBottom);
        label = new QLabel(CodeClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(258, 81, 280, 65));

        retranslateUi(CodeClass);

        QMetaObject::connectSlotsByName(CodeClass);
    } // setupUi

    void retranslateUi(QDialog *CodeClass)
    {
        CodeClass->setWindowTitle(QApplication::translate("CodeClass", "\347\274\226\347\240\201\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_close_window->setText(QString());
        pushButton_close_dialog->setText(QString());
        pushButton_accept_dialog->setText(QString());
        comboBox_1->clear();
        comboBox_1->insertItems(0, QStringList()
         << QApplication::translate("CodeClass", "Big5", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Big5-HKSCS", Q_NULLPTR)
         << QApplication::translate("CodeClass", "CP949", Q_NULLPTR)
         << QApplication::translate("CodeClass", "EUC-JP", Q_NULLPTR)
         << QApplication::translate("CodeClass", "EUC-KR", Q_NULLPTR)
         << QApplication::translate("CodeClass", "GB18030", Q_NULLPTR)
         << QApplication::translate("CodeClass", "HP-ROMAN8", Q_NULLPTR)
         << QApplication::translate("CodeClass", "IBM 850", Q_NULLPTR)
         << QApplication::translate("CodeClass", "IBM 866", Q_NULLPTR)
         << QApplication::translate("CodeClass", "IBM 874", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 2022-JP", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 8859-1", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 8859-2", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 8859-3", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 8859-4", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 8859-5", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 8859-6", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 8859-7", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 8859-8", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 8859-9", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 8859-10", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 8859-13", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 8859-14", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 8859-15", Q_NULLPTR)
         << QApplication::translate("CodeClass", "ISO 8859-16", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Iscii-Bng", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Iscii-Dev", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Iscii-Gjr", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Iscii-Knd", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Iscii-Mlm", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Iscii-Ori", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Iscii-Pnj", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Iscii-Tlg", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Iscii-Tml", Q_NULLPTR)
         << QApplication::translate("CodeClass", "KOI8-R", Q_NULLPTR)
         << QApplication::translate("CodeClass", "KOI8-U", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Macintosh", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Shift-JIS", Q_NULLPTR)
         << QApplication::translate("CodeClass", "TIS-620", Q_NULLPTR)
         << QApplication::translate("CodeClass", "TSCII", Q_NULLPTR)
         << QApplication::translate("CodeClass", "UTF-8", Q_NULLPTR)
         << QApplication::translate("CodeClass", "UTF-16", Q_NULLPTR)
         << QApplication::translate("CodeClass", "UTF-16BE", Q_NULLPTR)
         << QApplication::translate("CodeClass", "UTF-16LE", Q_NULLPTR)
         << QApplication::translate("CodeClass", "UTF-32", Q_NULLPTR)
         << QApplication::translate("CodeClass", "UTF-32BE", Q_NULLPTR)
         << QApplication::translate("CodeClass", "UTF-32LE", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Windows-1250", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Windows-1251", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Windows-1252", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Windows-1253", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Windows-1254", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Windows-1255", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Windows-1256", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Windows-1257", Q_NULLPTR)
         << QApplication::translate("CodeClass", "Windows-1258", Q_NULLPTR)
        );
        comboBox_1->setCurrentText(QApplication::translate("CodeClass", "Big5", Q_NULLPTR));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CodeClass: public Ui_CodeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODE_H
