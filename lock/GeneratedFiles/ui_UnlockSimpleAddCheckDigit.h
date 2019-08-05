/********************************************************************************
** Form generated from reading UI file 'UnlockSimpleAddCheckDigit.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNLOCKSIMPLEADDCHECKDIGIT_H
#define UI_UNLOCKSIMPLEADDCHECKDIGIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UnlockSimpleAddCheckDigitClass
{
public:
    QPushButton *pushButton_apply;
    QListWidget *listWidget_1;

    void setupUi(QDialog *UnlockSimpleAddCheckDigitClass)
    {
        if (UnlockSimpleAddCheckDigitClass->objectName().isEmpty())
            UnlockSimpleAddCheckDigitClass->setObjectName(QStringLiteral("UnlockSimpleAddCheckDigitClass"));
        UnlockSimpleAddCheckDigitClass->resize(400, 400);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_lock/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        UnlockSimpleAddCheckDigitClass->setWindowIcon(icon);
        UnlockSimpleAddCheckDigitClass->setWindowOpacity(5);
        pushButton_apply = new QPushButton(UnlockSimpleAddCheckDigitClass);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setGeometry(QRect(158, 340, 60, 30));
        pushButton_apply->setContextMenuPolicy(Qt::NoContextMenu);
        pushButton_apply->setStyleSheet(QLatin1String("border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_10.png);\n"
"border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_10.png);"));
        listWidget_1 = new QListWidget(UnlockSimpleAddCheckDigitClass);
        listWidget_1->setObjectName(QStringLiteral("listWidget_1"));
        listWidget_1->setGeometry(QRect(130, 90, 141, 221));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        listWidget_1->setFont(font);
        listWidget_1->setContextMenuPolicy(Qt::NoContextMenu);
        listWidget_1->setStyleSheet(QString::fromUtf8("QListWidget\n"
"{\n"
"    background:rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}\n"
"QListWidget::Item:hover\n"
"{\n"
"    background:#C0FDEAD3;\n"
"}\n"
"QListWidget::item:selected\n"
"{\n"
"    background:#C0FDEAD3;\n"
"}\n"
"QListWidget::item:selected:!active\n"
"{\n"
"    background:#C0FDEAD3;\n"
"}\n"
"/*\346\273\232\345\212\250\346\235\241*/\n"
"QListWidget QScrollBar::vertical\n"
"{\n"
"    margin: 15px 0px 15px 0px;\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png); \n"
"    border: 0px;\n"
"    width: 15px;\n"
"}\n"
"QListWidget QScrollBar::handle:vertical\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_vertical.png);\n"
"    min-height:50px;\n"
"}\n"
"QListWidget QScrollBar::handle:vertical:pressed \n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_vertical.png);\n"
"}\n"
"QListWidget QScrollBar::add-page:vertical\n"
"{\n"
"    border-image: u"
                        "rl(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png);\n"
"}\n"
"QListWidget QScrollBar::sub-page:vertical\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png);\n"
"}\n"
"QListWidget QScrollBar::sub-line:vertical\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    height:15px\n"
"}\n"
"QListWidget QScrollBar::add-line:vertical\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    height:15px\n"
"}\n"
"QListWidget QScrollBar::down-arrow:vertical\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/down.png);\n"
"}\n"
"QListWidget QScrollBar::up-arrow:vertical\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/up.png);\n"
"}\n"
"QListWidget QScrollBar::horizontal\n"
"{\n"
"    margin: 0px 15px 0px 15px;\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_horizental.png); \n"
"    border: 0px; \n"
""
                        "    height: 15px;\n"
"}\n"
"QListWidget QScrollBar::handle:horizontal\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"    min-width:50px;\n"
"}\n"
"QTableWidget QScrollBar::handle:horizontal:pressed\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTreeView QScrollBar::add-page:horizontal\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTreeView QScrollBar::sub-page:horizontal\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"}\n"
"QTreeView QScrollBar::add-line:horizontal\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:15px\n"
"}\n"
"QTreeView QScrollBar::sub-line:horizontal\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:15px\n"
"}\n"
"QTreeView QScrollBar::left"
                        "-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/left.png);\n"
"}\n"
"QTreeView QScrollBar::right-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/right.png);\n"
"}"));
        listWidget_1->setBatchSize(16);

        retranslateUi(UnlockSimpleAddCheckDigitClass);

        QMetaObject::connectSlotsByName(UnlockSimpleAddCheckDigitClass);
    } // setupUi

    void retranslateUi(QDialog *UnlockSimpleAddCheckDigitClass)
    {
        UnlockSimpleAddCheckDigitClass->setWindowTitle(QApplication::translate("UnlockSimpleAddCheckDigitClass", "\345\212\240\345\207\217\346\225\260\351\207\217", Q_NULLPTR));
        pushButton_apply->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UnlockSimpleAddCheckDigitClass: public Ui_UnlockSimpleAddCheckDigitClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNLOCKSIMPLEADDCHECKDIGIT_H
