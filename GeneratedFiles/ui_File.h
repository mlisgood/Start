/********************************************************************************
** Form generated from reading UI file 'File.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILE_H
#define UI_FILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_FileClass
{
public:
    QPushButton *pushButton_close_window;
    QTreeView *treeView_file;
    QPushButton *pushButton_open;
    QPushButton *pushButton_exit;
    QLineEdit *textEdit_name;

    void setupUi(QDialog *FileClass)
    {
        if (FileClass->objectName().isEmpty())
            FileClass->setObjectName(QStringLiteral("FileClass"));
        FileClass->resize(600, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/mainicon/picture_lock/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        FileClass->setWindowIcon(icon);
        FileClass->setWindowOpacity(5);
        FileClass->setSizeGripEnabled(false);
        pushButton_close_window = new QPushButton(FileClass);
        pushButton_close_window->setObjectName(QStringLiteral("pushButton_close_window"));
        pushButton_close_window->setGeometry(QRect(525, 15, 25, 25));
        pushButton_close_window->setStyleSheet(QStringLiteral("border-image: url(:/icon/managebutton/picture_start/icon/window_close.png);"));
        treeView_file = new QTreeView(FileClass);
        treeView_file->setObjectName(QStringLiteral("treeView_file"));
        treeView_file->setGeometry(QRect(50, 90, 500, 320));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        treeView_file->setFont(font);
        treeView_file->setContextMenuPolicy(Qt::NoContextMenu);
        treeView_file->setStyleSheet(QString::fromUtf8("/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QTreeView\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:1px solid rgb(128,76,71);\n"
"}\n"
"QTreeView::Item:hover\n"
"{\n"
"    background:#C0FDEAD3;\n"
"}\n"
"QTreeView::item:selected\n"
"{\n"
"    background:#C0FDEAD3;\n"
"}\n"
"QTreeView::item:selected:!active\n"
"{\n"
"    background:#C0FDEAD3;\n"
"}\n"
"/*\346\273\232\345\212\250\346\235\241*/\n"
"QTreeView QScrollBar::vertical\n"
"{\n"
"    margin: 9px 0px 9px 0px;\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png); \n"
"    border: 0px;\n"
"    width: 9px;\n"
"}\n"
"QTreeView QScrollBar::handle:vertical\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_vertical.png);\n"
"    min-height:50px;\n"
"}\n"
"QTreeView QScrollBar::handle:vertical:pressed \n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_vertical.png);\n"
"}\n"
"QTreeView QScrollBar::add-page"
                        ":vertical\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png);\n"
"}\n"
"QTreeView QScrollBar::sub-page:vertical\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_vertical.png);\n"
"}\n"
"QTreeView QScrollBar::sub-line:vertical\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    height:9px\n"
"}\n"
"QTreeView QScrollBar::add-line:vertical\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    height:9px\n"
"}\n"
"QTreeView QScrollBar::down-arrow:vertical\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/down.png);\n"
"}\n"
"QTreeView QScrollBar::up-arrow:vertical\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/up.png);\n"
"}\n"
"QTreeView QScrollBar::horizontal\n"
"{\n"
"    margin: 0px 9px 0px 9px;\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/line_horizental.png); \n"
""
                        "    border: 0px; \n"
"    height: 9px;\n"
"}\n"
"QTreeView QScrollBar::handle:horizontal\n"
"{\n"
"    border-image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/button_horizental.png);\n"
"    min-width:50px;\n"
"}\n"
"QTreeView QScrollBar::handle:horizontal:pressed\n"
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
"    width:9px\n"
"}\n"
"QTreeView QScrollBar::sub-line:horizontal\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:9px\n"
"}\n"
"QTreeView QS"
                        "crollBar::left-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/left.png);\n"
"}\n"
"QTreeView QScrollBar::right-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_lock/scrollbar/picture_lock/scrollbar_style/right.png);\n"
"}\n"
"/*\345\210\206\346\224\257\346\214\211\351\222\256*/\n"
"QTreeView::branch:has-children:!has-siblings:closed,\n"
"QTreeView::branch:closed:has-children:has-siblings\n"
"{\n"
"    border-image: none;\n"
"    image: url(:/picture_lock/treeview/picture_lock/treeview_style/down_branch.png);\n"
"}\n"
"QTreeView::branch:has-children:!has-siblings:closed:hover,\n"
"QTreeView::branch:closed:has-children:has-siblings:hover\n"
"{\n"
"    border-image: none;\n"
"    image: url(:/picture_lock/treeview/picture_lock/treeview_style/down_branch.png);\n"
"}\n"
"QTreeView::branch:has-children:!has-siblings:closed:pressed,\n"
"QTreeView::branch:closed:has-children:has-siblings:pressed\n"
"{\n"
"    border-image: none;\n"
"    image: url(:/picture_lock/tree"
                        "view/picture_lock/treeview_style/down_branch.png);\n"
"}\n"
"\n"
"QTreeView::branch:open:has-children:!has-siblings,\n"
"QTreeView::branch:open:has-children:has-siblings \n"
"{\n"
"    border-image: none;\n"
"    image: url(:/picture_lock/treeview/picture_lock/treeview_style/up_branch.png);\n"
"    width:12px;\n"
"    height:8px;\n"
"}\n"
"QTreeView::branch:open:has-children:!has-siblings:hover,\n"
"QTreeView::branch:open:has-children:has-siblings:hover\n"
"{\n"
"    border-image: none;\n"
"    image: url(:/picture_lock/treeview/picture_lock/treeview_style/up_branch.png);\n"
"}\n"
"QTreeView::branch:open:has-children:!has-siblings:pressed,\n"
"QTreeView::branch:open:has-children:has-siblings:pressed\n"
"{\n"
"    border-image: none;\n"
"    image: url(:/picture_lock/treeview/picture_lock/treeview_style/up_branch.png);\n"
"}"));
        pushButton_open = new QPushButton(FileClass);
        pushButton_open->setObjectName(QStringLiteral("pushButton_open"));
        pushButton_open->setGeometry(QRect(72, 510, 150, 60));
        pushButton_open->setStyleSheet(QLatin1String("border-image: url(:/picture_start/dialogicon/picture_start/icon/dialog_filedialog_open_normal.png);\n"
"border-image: url(:/picture_start/dialogicon/picture_start/icon/dialog_filedialog_open_pressed.png);\n"
""));
        pushButton_exit = new QPushButton(FileClass);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(352, 510, 150, 60));
        pushButton_exit->setStyleSheet(QLatin1String("border-image: url(:/picture_start/dialogicon/picture_start/icon/dialog_filedialog_exit_normal.png);\n"
"border-image: url(:/picture_start/dialogicon/picture_start/icon/dialog_filedialog_exit_pressed.png);"));
        textEdit_name = new QLineEdit(FileClass);
        textEdit_name->setObjectName(QStringLiteral("textEdit_name"));
        textEdit_name->setGeometry(QRect(160, 452, 290, 15));
        textEdit_name->setContextMenuPolicy(Qt::NoContextMenu);
        textEdit_name->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background: rgb(255,255,255,0);\n"
"    border:0px solid rgb(255,255,255,0);\n"
"}"));

        retranslateUi(FileClass);

        QMetaObject::connectSlotsByName(FileClass);
    } // setupUi

    void retranslateUi(QDialog *FileClass)
    {
        FileClass->setWindowTitle(QApplication::translate("FileClass", "\351\242\234\350\211\262\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_close_window->setText(QString());
        pushButton_open->setText(QString());
        pushButton_exit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FileClass: public Ui_FileClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILE_H
