/********************************************************************************
** Form generated from reading UI file 'Notepad.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEPAD_H
#define UI_NOTEPAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NotepadClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_hide_windows;
    QPushButton *pushButton_close_windows;
    QTextEdit *textEdit_main;
    QPushButton *pushButton_tool_01;
    QPushButton *pushButton_tool_02;
    QPushButton *pushButton_tool_03;
    QPushButton *pushButton_tool_04;
    QPushButton *pushButton_tool_05;
    QLabel *label_filename;
    QLabel *label_filestatus;
    QPushButton *pushButton_tool_06;
    QPushButton *pushButton_tool_07;
    QPushButton *pushButton_tool_09;
    QPushButton *pushButton_tool_10;
    QPushButton *pushButton_tool_08;
    QPushButton *pushButton_tool_11;
    QPushButton *pushButton_tool_12;
    QPushButton *pushButton_tool_13;
    QPushButton *pushButton_tool_14;
    QPushButton *pushButton_tool_15;
    QPushButton *pushButton_tool_17;
    QLabel *label_code;
    QLabel *label_savestatus;
    QPushButton *pushButton_tool_16;
    QPushButton *pushButton_tool_18;
    QProgressBar *progressBar;
    QLabel *label_file_read_advance;

    void setupUi(QMainWindow *NotepadClass)
    {
        if (NotepadClass->objectName().isEmpty())
            NotepadClass->setObjectName(QStringLiteral("NotepadClass"));
        NotepadClass->resize(1000, 600);
        NotepadClass->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_notepad/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        NotepadClass->setWindowIcon(icon);
        centralWidget = new QWidget(NotepadClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_hide_windows = new QPushButton(centralWidget);
        pushButton_hide_windows->setObjectName(QStringLiteral("pushButton_hide_windows"));
        pushButton_hide_windows->setGeometry(QRect(885, 15, 25, 25));
        pushButton_hide_windows->setStyleSheet(QStringLiteral("border-image: url(:/icon/manage/picture_notepad/icon/window_hide.png);"));
        pushButton_close_windows = new QPushButton(centralWidget);
        pushButton_close_windows->setObjectName(QStringLiteral("pushButton_close_windows"));
        pushButton_close_windows->setGeometry(QRect(925, 15, 25, 25));
        pushButton_close_windows->setStyleSheet(QStringLiteral("border-image: url(:/icon/manage/picture_notepad/icon/window_close.png);"));
        textEdit_main = new QTextEdit(centralWidget);
        textEdit_main->setObjectName(QStringLiteral("textEdit_main"));
        textEdit_main->setGeometry(QRect(485, 105, 450, 420));
        textEdit_main->setContextMenuPolicy(Qt::NoContextMenu);
        textEdit_main->setAcceptDrops(true);
        textEdit_main->setToolTipDuration(-1);
        textEdit_main->setStyleSheet(QLatin1String("QTextEdit QScrollBar::vertical\n"
"{\n"
"    margin: 15px 0px 15px 0px;\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/line_vertical.png); \n"
"    border: 0px; \n"
"    width: 15px;\n"
"}\n"
"QTextEdit QScrollBar::handle:vertical\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_vertical.png);\n"
"    min-height:50px;\n"
"}\n"
"QTextEdit QScrollBar::handle:vertical:pressed\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_vertical.png);\n"
"}\n"
"QTextEdit QScrollBar::add-page:vertical\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/line_vertical.png);\n"
"}\n"
"QTextEdit QScrollBar::sub-page:vertical\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/line_vertical.png);\n"
"}\n"
"QTextEdit QScrollBar::sub-line:vertical\n"
"{\n"
"    subcontrol-origin: margin; border: 0px solid black; \n"
" "
                        "   height:15px\n"
"}\n"
"QTextEdit QScrollBar::add-line:vertical\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    height: 15px\n"
"}\n"
"QTextEdit QScrollBar::down-arrow:vertical\n"
"{\n"
"    image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/down.png);\n"
"}\n"
"QTextEdit QScrollBar::up-arrow:vertical\n"
"{\n"
"    image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/up.png);\n"
"}\n"
"QTextEdit QScrollBar::horizontal\n"
"{\n"
"    margin: 0px 15px 0px 15px;\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/line_horizental.png); \n"
"    border: 0px;\n"
"    height: 15px;\n"
"}\n"
"QTextEdit QScrollBar::handle:horizontal\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/button_horizental.png);\n"
"    min-width:50px;\n"
"}\n"
"QTextEdit QScrollBar::handle:horizontal:pressed \n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_st"
                        "yle/button_horizental.png);\n"
"}\n"
"QTextEdit QScrollBar::add-page:horizontal\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/line_horizental.png);\n"
"}\n"
"QTextEdit QScrollBar::sub-page:horizontal\n"
"{\n"
"    border-image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/line_horizental.png);\n"
"}\n"
"QTextEdit QScrollBar::add-line:horizontal\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:15px\n"
"}\n"
"QTextEdit QScrollBar::sub-line:horizontal\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:15px\n"
"}\n"
"QTextEdit QScrollBar::left-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/left.png);\n"
"}\n"
"QTextEdit QScrollBar::right-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_notepad/scrollbar/picture_notepad/scrollbar_style/right.png);\n"
"}"));
        textEdit_main->setFrameShadow(QFrame::Raised);
        pushButton_tool_01 = new QPushButton(centralWidget);
        pushButton_tool_01->setObjectName(QStringLiteral("pushButton_tool_01"));
        pushButton_tool_01->setGeometry(QRect(476, 50, 25, 25));
        pushButton_tool_01->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_01.png);"));
        pushButton_tool_01->setInputMethodHints(Qt::ImhNone);
        pushButton_tool_02 = new QPushButton(centralWidget);
        pushButton_tool_02->setObjectName(QStringLiteral("pushButton_tool_02"));
        pushButton_tool_02->setGeometry(QRect(502, 50, 25, 25));
        pushButton_tool_02->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_02.png);"));
        pushButton_tool_03 = new QPushButton(centralWidget);
        pushButton_tool_03->setObjectName(QStringLiteral("pushButton_tool_03"));
        pushButton_tool_03->setGeometry(QRect(528, 50, 25, 25));
        pushButton_tool_03->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_03.png);"));
        pushButton_tool_04 = new QPushButton(centralWidget);
        pushButton_tool_04->setObjectName(QStringLiteral("pushButton_tool_04"));
        pushButton_tool_04->setGeometry(QRect(554, 50, 25, 25));
        pushButton_tool_04->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_04.png);"));
        pushButton_tool_05 = new QPushButton(centralWidget);
        pushButton_tool_05->setObjectName(QStringLiteral("pushButton_tool_05"));
        pushButton_tool_05->setGeometry(QRect(606, 50, 25, 25));
        pushButton_tool_05->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_1.png);"));
        label_filename = new QLabel(centralWidget);
        label_filename->setObjectName(QStringLiteral("label_filename"));
        label_filename->setGeometry(QRect(475, 20, 400, 15));
        label_filestatus = new QLabel(centralWidget);
        label_filestatus->setObjectName(QStringLiteral("label_filestatus"));
        label_filestatus->setGeometry(QRect(475, 560, 200, 15));
        pushButton_tool_06 = new QPushButton(centralWidget);
        pushButton_tool_06->setObjectName(QStringLiteral("pushButton_tool_06"));
        pushButton_tool_06->setGeometry(QRect(632, 50, 25, 25));
        pushButton_tool_06->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_06.png);"));
        pushButton_tool_07 = new QPushButton(centralWidget);
        pushButton_tool_07->setObjectName(QStringLiteral("pushButton_tool_07"));
        pushButton_tool_07->setGeometry(QRect(658, 50, 25, 25));
        pushButton_tool_07->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_07.png);"));
        pushButton_tool_09 = new QPushButton(centralWidget);
        pushButton_tool_09->setObjectName(QStringLiteral("pushButton_tool_09"));
        pushButton_tool_09->setGeometry(QRect(710, 50, 25, 25));
        pushButton_tool_09->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_08.png);"));
        pushButton_tool_10 = new QPushButton(centralWidget);
        pushButton_tool_10->setObjectName(QStringLiteral("pushButton_tool_10"));
        pushButton_tool_10->setGeometry(QRect(736, 50, 25, 25));
        pushButton_tool_10->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_09.png);"));
        pushButton_tool_08 = new QPushButton(centralWidget);
        pushButton_tool_08->setObjectName(QStringLiteral("pushButton_tool_08"));
        pushButton_tool_08->setGeometry(QRect(684, 50, 25, 25));
        pushButton_tool_08->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_10.png);"));
        pushButton_tool_11 = new QPushButton(centralWidget);
        pushButton_tool_11->setObjectName(QStringLiteral("pushButton_tool_11"));
        pushButton_tool_11->setGeometry(QRect(762, 50, 25, 25));
        pushButton_tool_11->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_11.png);"));
        pushButton_tool_12 = new QPushButton(centralWidget);
        pushButton_tool_12->setObjectName(QStringLiteral("pushButton_tool_12"));
        pushButton_tool_12->setGeometry(QRect(788, 50, 25, 25));
        pushButton_tool_12->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_12.png);"));
        pushButton_tool_13 = new QPushButton(centralWidget);
        pushButton_tool_13->setObjectName(QStringLiteral("pushButton_tool_13"));
        pushButton_tool_13->setGeometry(QRect(814, 50, 25, 25));
        pushButton_tool_13->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_13.png);"));
        pushButton_tool_14 = new QPushButton(centralWidget);
        pushButton_tool_14->setObjectName(QStringLiteral("pushButton_tool_14"));
        pushButton_tool_14->setGeometry(QRect(840, 50, 25, 25));
        pushButton_tool_14->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_14.png);"));
        pushButton_tool_15 = new QPushButton(centralWidget);
        pushButton_tool_15->setObjectName(QStringLiteral("pushButton_tool_15"));
        pushButton_tool_15->setGeometry(QRect(866, 50, 25, 25));
        pushButton_tool_15->setStyleSheet(QStringLiteral("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_15.png);"));
        pushButton_tool_17 = new QPushButton(centralWidget);
        pushButton_tool_17->setObjectName(QStringLiteral("pushButton_tool_17"));
        pushButton_tool_17->setGeometry(QRect(892, 50, 25, 25));
        pushButton_tool_17->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_17.png);\n"
""));
        label_code = new QLabel(centralWidget);
        label_code->setObjectName(QStringLiteral("label_code"));
        label_code->setGeometry(QRect(885, 560, 80, 15));
        label_savestatus = new QLabel(centralWidget);
        label_savestatus->setObjectName(QStringLiteral("label_savestatus"));
        label_savestatus->setGeometry(QRect(690, 560, 50, 15));
        pushButton_tool_16 = new QPushButton(centralWidget);
        pushButton_tool_16->setObjectName(QStringLiteral("pushButton_tool_16"));
        pushButton_tool_16->setGeometry(QRect(580, 50, 25, 25));
        pushButton_tool_16->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_16.png);\n"
""));
        pushButton_tool_18 = new QPushButton(centralWidget);
        pushButton_tool_18->setObjectName(QStringLiteral("pushButton_tool_18"));
        pushButton_tool_18->setGeometry(QRect(918, 50, 25, 25));
        pushButton_tool_18->setStyleSheet(QLatin1String("border-image: url(:/picture_notepad/toolicon/picture_notepad/icon/tool_18.png);\n"
""));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(475, 542, 470, 15));
        progressBar->setContextMenuPolicy(Qt::NoContextMenu);
        progressBar->setStyleSheet(QLatin1String("QProgressBar\n"
"{\n"
"   border: 1px solid #804C47;\n"
"   background-color: #00FFFFFF;\n"
"   text-align: center;\n"
"}\n"
" \n"
"QProgressBar::chunk\n"
"{\n"
"   background-color: #804C47;\n"
"}"));
        progressBar->setValue(0);
        label_file_read_advance = new QLabel(centralWidget);
        label_file_read_advance->setObjectName(QStringLiteral("label_file_read_advance"));
        label_file_read_advance->setGeometry(QRect(475, 542, 200, 15));
        NotepadClass->setCentralWidget(centralWidget);

        retranslateUi(NotepadClass);
        QObject::connect(pushButton_hide_windows, SIGNAL(clicked()), NotepadClass, SLOT(showMinimized()));

        QMetaObject::connectSlotsByName(NotepadClass);
    } // setupUi

    void retranslateUi(QMainWindow *NotepadClass)
    {
        NotepadClass->setWindowTitle(QApplication::translate("NotepadClass", "\346\234\252\345\221\275\345\220\215 - \344\270\200\347\267\222\343\201\253\343\203\242\343\203\225\343\203\242\343\203\225\343\201\227\343\202\210\343\203\274", Q_NULLPTR));
        pushButton_hide_windows->setText(QString());
        pushButton_close_windows->setText(QString());
#ifndef QT_NO_TOOLTIP
        textEdit_main->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButton_tool_01->setText(QString());
        pushButton_tool_02->setText(QString());
        pushButton_tool_03->setText(QString());
        pushButton_tool_04->setText(QString());
        pushButton_tool_05->setText(QString());
        label_filename->setText(QString());
        label_filestatus->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_tool_06->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButton_tool_06->setText(QString());
        pushButton_tool_07->setText(QString());
        pushButton_tool_09->setText(QString());
        pushButton_tool_10->setText(QString());
        pushButton_tool_08->setText(QString());
        pushButton_tool_11->setText(QString());
        pushButton_tool_12->setText(QString());
        pushButton_tool_13->setText(QString());
        pushButton_tool_14->setText(QString());
        pushButton_tool_15->setText(QString());
        pushButton_tool_17->setText(QString());
        label_code->setText(QString());
        label_savestatus->setText(QString());
        pushButton_tool_16->setText(QString());
        pushButton_tool_18->setText(QString());
        label_file_read_advance->setText(QApplication::translate("NotepadClass", "\346\255\243\345\234\250\350\216\267\345\217\226\346\226\207\344\273\266\346\200\273\345\255\227\350\212\202\346\225\260\344\277\241\346\201\257\342\200\246\342\200\246", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NotepadClass: public Ui_NotepadClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEPAD_H
