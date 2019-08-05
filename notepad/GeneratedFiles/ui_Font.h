/********************************************************************************
** Form generated from reading UI file 'Font.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FONT_H
#define UI_FONT_H

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

class Ui_FontClass
{
public:
    QPushButton *pushButton_close_window;
    QPushButton *pushButton_close_dialog;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;
    QLabel *label_sample;
    QComboBox *comboBox_1;
    QPushButton *pushButton_accept_dialog;

    void setupUi(QDialog *FontClass)
    {
        if (FontClass->objectName().isEmpty())
            FontClass->setObjectName(QStringLiteral("FontClass"));
        FontClass->resize(596, 400);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_notepad/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        FontClass->setWindowIcon(icon);
        FontClass->setWindowOpacity(5);
        FontClass->setSizeGripEnabled(false);
        pushButton_close_window = new QPushButton(FontClass);
        pushButton_close_window->setObjectName(QStringLiteral("pushButton_close_window"));
        pushButton_close_window->setGeometry(QRect(525, 15, 25, 25));
        pushButton_close_window->setStyleSheet(QStringLiteral("border-image: url(:/icon/manage/picture_notepad/icon/window_close.png);"));
        pushButton_close_dialog = new QPushButton(FontClass);
        pushButton_close_dialog->setObjectName(QStringLiteral("pushButton_close_dialog"));
        pushButton_close_dialog->setGeometry(QRect(341, 325, 150, 60));
        pushButton_close_dialog->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_font_exit_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_font_exit_pressed.png);"));
        comboBox_2 = new QComboBox(FontClass);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(300, 90, 100, 25));
        comboBox_2->setContextMenuPolicy(Qt::DefaultContextMenu);
        comboBox_2->setAutoFillBackground(false);
        comboBox_2->setStyleSheet(QStringLiteral(""));
        comboBox_2->setEditable(false);
        comboBox_2->setMaxVisibleItems(4);
        comboBox_2->setMaxCount(2147483646);
        comboBox_2->setInsertPolicy(QComboBox::InsertAtBottom);
        comboBox_3 = new QComboBox(FontClass);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(450, 90, 100, 25));
        comboBox_3->setContextMenuPolicy(Qt::NoContextMenu);
        comboBox_3->setStyleSheet(QStringLiteral(""));
        comboBox_3->setInputMethodHints(Qt::ImhNone);
        comboBox_3->setEditable(true);
        comboBox_3->setMaxVisibleItems(7);
        comboBox_3->setMaxCount(2147483646);
        comboBox_4 = new QComboBox(FontClass);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));
        comboBox_4->setGeometry(QRect(50, 250, 150, 25));
        comboBox_4->setStyleSheet(QStringLiteral(""));
        comboBox_4->setEditable(false);
        comboBox_4->setMaxVisibleItems(3);
        label_sample = new QLabel(FontClass);
        label_sample->setObjectName(QStringLiteral("label_sample"));
        label_sample->setGeometry(QRect(280, 230, 270, 65));
        label_sample->setStyleSheet(QStringLiteral(""));
        label_sample->setAlignment(Qt::AlignCenter);
        comboBox_1 = new QComboBox(FontClass);
        comboBox_1->setObjectName(QStringLiteral("comboBox_1"));
        comboBox_1->setGeometry(QRect(50, 90, 200, 25));
        comboBox_1->setContextMenuPolicy(Qt::DefaultContextMenu);
        comboBox_1->setAutoFillBackground(false);
        comboBox_1->setStyleSheet(QStringLiteral(""));
        comboBox_1->setEditable(false);
        comboBox_1->setMaxVisibleItems(7);
        comboBox_1->setMaxCount(2147483646);
        comboBox_1->setInsertPolicy(QComboBox::InsertAtBottom);
        pushButton_accept_dialog = new QPushButton(FontClass);
        pushButton_accept_dialog->setObjectName(QStringLiteral("pushButton_accept_dialog"));
        pushButton_accept_dialog->setGeometry(QRect(81, 325, 200, 60));
        pushButton_accept_dialog->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_font_accept_normal.png);\n"
"border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_font_accept_pressed.png);"));

        retranslateUi(FontClass);

        QMetaObject::connectSlotsByName(FontClass);
    } // setupUi

    void retranslateUi(QDialog *FontClass)
    {
        FontClass->setWindowTitle(QApplication::translate("FontClass", "\345\255\227\344\275\223\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_close_window->setText(QString());
        pushButton_close_dialog->setText(QString());
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("FontClass", "\345\270\270\350\247\204", Q_NULLPTR)
         << QApplication::translate("FontClass", "\347\262\227\344\275\223", Q_NULLPTR)
         << QApplication::translate("FontClass", "\345\200\276\346\226\234", Q_NULLPTR)
         << QApplication::translate("FontClass", "\347\262\227\344\275\223\345\200\276\346\226\234", Q_NULLPTR)
        );
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("FontClass", "4", Q_NULLPTR)
         << QApplication::translate("FontClass", "5", Q_NULLPTR)
         << QApplication::translate("FontClass", "6", Q_NULLPTR)
         << QApplication::translate("FontClass", "7", Q_NULLPTR)
         << QApplication::translate("FontClass", "8", Q_NULLPTR)
         << QApplication::translate("FontClass", "9", Q_NULLPTR)
         << QApplication::translate("FontClass", "10", Q_NULLPTR)
         << QApplication::translate("FontClass", "12", Q_NULLPTR)
         << QApplication::translate("FontClass", "14", Q_NULLPTR)
         << QApplication::translate("FontClass", "16", Q_NULLPTR)
         << QApplication::translate("FontClass", "18", Q_NULLPTR)
         << QApplication::translate("FontClass", "20", Q_NULLPTR)
         << QApplication::translate("FontClass", "22", Q_NULLPTR)
         << QApplication::translate("FontClass", "24", Q_NULLPTR)
         << QApplication::translate("FontClass", "26", Q_NULLPTR)
         << QApplication::translate("FontClass", "28", Q_NULLPTR)
         << QApplication::translate("FontClass", "32", Q_NULLPTR)
         << QApplication::translate("FontClass", "36", Q_NULLPTR)
         << QApplication::translate("FontClass", "48", Q_NULLPTR)
         << QApplication::translate("FontClass", "72", Q_NULLPTR)
        );
        comboBox_3->setCurrentText(QApplication::translate("FontClass", "4", Q_NULLPTR));
        comboBox_4->clear();
        comboBox_4->insertItems(0, QStringList()
         << QApplication::translate("FontClass", "\347\256\200\344\275\223\344\270\255\346\226\207", Q_NULLPTR)
         << QApplication::translate("FontClass", "English", Q_NULLPTR)
         << QApplication::translate("FontClass", "\346\227\245\346\234\254\350\252\236", Q_NULLPTR)
        );
        label_sample->setText(QString());
        pushButton_accept_dialog->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FontClass: public Ui_FontClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FONT_H
