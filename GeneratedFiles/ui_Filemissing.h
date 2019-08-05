/********************************************************************************
** Form generated from reading UI file 'Filemissing.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEMISSING_H
#define UI_FILEMISSING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FilemissingClass
{
public:
    QPushButton *pushButton_close_window;
    QPushButton *pushButton_close_dialog;
    QLabel *label_information;

    void setupUi(QDialog *FilemissingClass)
    {
        if (FilemissingClass->objectName().isEmpty())
            FilemissingClass->setObjectName(QStringLiteral("FilemissingClass"));
        FilemissingClass->resize(600, 200);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/main/picture_start/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        FilemissingClass->setWindowIcon(icon);
        FilemissingClass->setWindowOpacity(5);
        pushButton_close_window = new QPushButton(FilemissingClass);
        pushButton_close_window->setObjectName(QStringLiteral("pushButton_close_window"));
        pushButton_close_window->setGeometry(QRect(525, 15, 25, 25));
        pushButton_close_window->setStyleSheet(QStringLiteral("border-image: url(:/icon/managebutton/picture_start/icon/window_close.png);"));
        pushButton_close_dialog = new QPushButton(FilemissingClass);
        pushButton_close_dialog->setObjectName(QStringLiteral("pushButton_close_dialog"));
        pushButton_close_dialog->setGeometry(QRect(305, 140, 150, 60));
        pushButton_close_dialog->setStyleSheet(QLatin1String("border-image: url(:/icon/item/picture_start/icon/dialog_main_exit_normal.png);\n"
"border-image: url(:/icon/item/picture_start/icon/dialog_main_exit_pressed.png);"));
        label_information = new QLabel(FilemissingClass);
        label_information->setObjectName(QStringLiteral("label_information"));
        label_information->setGeometry(QRect(255, 60, 300, 70));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(12);
        label_information->setFont(font);
        label_information->setCursor(QCursor(Qt::ArrowCursor));
        label_information->setLineWidth(1);
        label_information->setWordWrap(true);

        retranslateUi(FilemissingClass);

        QMetaObject::connectSlotsByName(FilemissingClass);
    } // setupUi

    void retranslateUi(QDialog *FilemissingClass)
    {
        FilemissingClass->setWindowTitle(QApplication::translate("FilemissingClass", "\347\250\213\345\272\217\345\244\261\350\270\252\344\272\206\357\274\201", Q_NULLPTR));
        pushButton_close_window->setText(QString());
        pushButton_close_dialog->setText(QString());
        label_information->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FilemissingClass: public Ui_FilemissingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEMISSING_H
