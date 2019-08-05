/********************************************************************************
** Form generated from reading UI file 'Note.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTE_H
#define UI_NOTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_NoteClass
{
public:
    QTextEdit *textEdit_main;

    void setupUi(QDialog *NoteClass)
    {
        if (NoteClass->objectName().isEmpty())
            NoteClass->setObjectName(QStringLiteral("NoteClass"));
        NoteClass->resize(200, 200);
        QIcon icon;
        icon.addFile(QStringLiteral(":/picture_tools/icon/picture_tools/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        NoteClass->setWindowIcon(icon);
        NoteClass->setWindowOpacity(5);
        textEdit_main = new QTextEdit(NoteClass);
        textEdit_main->setObjectName(QStringLiteral("textEdit_main"));
        textEdit_main->setGeometry(QRect(20, 20, 160, 160));
        textEdit_main->setContextMenuPolicy(Qt::NoContextMenu);
        textEdit_main->setStyleSheet(QLatin1String("QTextEdit QScrollBar::vertical {margin: 9px 0px 9px 0px;border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/line_vertical.png); border: 0px; width: 9px;}\n"
"QTextEdit QScrollBar::handle:vertical {border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_vertical.png);min-height:15px;}\n"
"QTextEdit QScrollBar::handle:vertical:pressed {border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_vertical.png); }\n"
"QTextEdit QScrollBar::add-page:vertical {border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/line_vertical.png);}\n"
"QTextEdit QScrollBar::sub-page:vertical {border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/line_vertical.png);}\n"
"QTextEdit QScrollBar::sub-line:vertical {subcontrol-origin: margin; border: 0px solid black; height:9px}\n"
"QTextEdit QScrollBar::add-line:vertical {subcontrol-origin: margin; border: 0px solid black; height:9px}\n"
"QTextEdit QScrollBar::down-arrow:vertical "
                        "{ image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/down.png); }\n"
"QTextEdit QScrollBar::up-arrow:vertical { image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/up.png); }\n"
"QTextEdit QScrollBar::horizontal {margin: 0px 9px 0px 9px;border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/line_horizental.png); border: 0px; height: 9px;}\n"
"QTextEdit QScrollBar::handle:horizontal {border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_horizental.png);min-width:15px;}\n"
"QTableWidget QScrollBar::handle:horizontal:pressed {border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_horizental.png); }\n"
"QTableWidget QScrollBar::add-page:horizontal {border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_horizental.png);}\n"
"QTableWidget QScrollBar::sub-page:horizontal {border-image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/button_horizental.png); }\n"
"QTextEdit QScrol"
                        "lBar::add-line:horizontal {subcontrol-origin: margin; border: 0px solid black; width:9px}\n"
"QTextEdit QScrollBar::sub-line:horizontal {subcontrol-origin: margin; border: 0px solid black; width:9px}\n"
"QTextEdit QScrollBar::left-arrow:horizontal { image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/left.png); }\n"
"QTableWidget QScrollBar::right-arrow:horizontal {image: url(:/picture_tools/scrollbar/picture_tools/scrollbar_style/right.png); }"));

        retranslateUi(NoteClass);

        QMetaObject::connectSlotsByName(NoteClass);
    } // setupUi

    void retranslateUi(QDialog *NoteClass)
    {
        NoteClass->setWindowTitle(QApplication::translate("NoteClass", "undefine", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NoteClass: public Ui_NoteClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTE_H
