/********************************************************************************
** Form generated from reading UI file 'DesktopOmake.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESKTOPOMAKE_H
#define UI_DESKTOPOMAKE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DesktopOmakeClass
{
public:
    QWidget *centralWidget;
    QLabel *label_picture;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QSlider *slider_rotate;
    QSlider *slider_resize;
    QSlider *slider_bg_r;
    QSlider *slider_bg_g;
    QSlider *slider_bg_b;
    QLabel *label_background;
    QLabel *label;
    QPushButton *pushButton_cocoa_1;
    QLabel *label_file_path;
    QSpinBox *spinBox_1;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_5;

    void setupUi(QMainWindow *DesktopOmakeClass)
    {
        if (DesktopOmakeClass->objectName().isEmpty())
            DesktopOmakeClass->setObjectName(QStringLiteral("DesktopOmakeClass"));
        DesktopOmakeClass->resize(1000, 625);
        DesktopOmakeClass->setAcceptDrops(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/picture_desktop/icon/picture_desktop/icon/icon_main_mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        DesktopOmakeClass->setWindowIcon(icon);
        centralWidget = new QWidget(DesktopOmakeClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_picture = new QLabel(centralWidget);
        label_picture->setObjectName(QStringLiteral("label_picture"));
        label_picture->setGeometry(QRect(447, 73, 480, 480));
        label_picture->setStyleSheet(QString::fromUtf8("/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QLabel\n"
"{\n"
"    border: 1px solid #00E872A2;\n"
"    background: #00FFFFFF;\n"
"}"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(447, 73, 480, 480));
        scrollArea->setLayoutDirection(Qt::LeftToRight);
        scrollArea->setStyleSheet(QString::fromUtf8("/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QScrollArea\n"
"{\n"
"    border: 1px solid #E872A2;\n"
"    background-color:transparent;\n"
"}\n"
"/*\346\273\232\345\212\250\346\235\241*/\n"
"QScrollArea QScrollBar::vertical\n"
"{\n"
"    margin: 9px 0px 9px 0px;\n"
"    border-image: url(:/picture_desktop/scrollbar/picture_desktop/scrollbar_style/line_vertical.png); \n"
"    border: 0px; \n"
"    width: 9px;\n"
"}\n"
"QScrollArea QScrollBar::handle:vertical\n"
"{\n"
"    border-image: url(:/picture_desktop/scrollbar/picture_desktop/scrollbar_style/button_vertical.png);\n"
"    min-height:50px;\n"
"}\n"
"QScrollArea QScrollBar::handle:vertical:pressed\n"
"{\n"
"    border-image: url(:/picture_desktop/scrollbar/picture_desktop/scrollbar_style/button_vertical.png);\n"
"}\n"
"QScrollArea QScrollBar::add-page:vertical\n"
"{\n"
"    border-image: url(:/picture_desktop/scrollbar/picture_desktop/scrollbar_style/line_vertical.png);\n"
"}\n"
"QScrollArea QScrollBar::sub-page:vertical\n"
"{\n"
"    border-ima"
                        "ge: url(:/picture_desktop/scrollbar/picture_desktop/scrollbar_style/line_vertical.png);\n"
"}\n"
"QScrollArea QScrollBar::sub-line:vertical\n"
"{\n"
"    subcontrol-origin: margin; border: 0px solid black; \n"
"    height:9px\n"
"}\n"
"QScrollArea QScrollBar::add-line:vertical\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    height: 9px\n"
"}\n"
"QScrollArea QScrollBar::down-arrow:vertical\n"
"{\n"
"    image: url(:/picture_desktop/scrollbar/picture_desktop/scrollbar_style/down.png);\n"
"}\n"
"QScrollArea QScrollBar::up-arrow:vertical\n"
"{\n"
"    image: url(:/picture_desktop/scrollbar/picture_desktop/scrollbar_style/up.png);\n"
"}\n"
"QScrollArea QScrollBar::horizontal\n"
"{\n"
"    margin: 0px 9px 0px 9px;\n"
"    border-image: url(:/picture_desktop/scrollbar/picture_desktop/scrollbar_style/line_horizental.png); \n"
"    border: 0px;\n"
"    height: 9px;\n"
"}\n"
"QScrollArea QScrollBar::handle:horizontal\n"
"{\n"
"    border-image: url(:/picture_desktop/scrollbar/picture_de"
                        "sktop/scrollbar_style/button_horizental.png);\n"
"    min-width:50px;\n"
"}\n"
"QScrollArea QScrollBar::handle:horizontal:pressed \n"
"{\n"
"    border-image: url(:/picture_desktop/scrollbar/picture_desktop/scrollbar_style/button_horizental.png);\n"
"}\n"
"QScrollArea QScrollBar::add-page:horizontal\n"
"{\n"
"    border-image: url(:/picture_desktop/scrollbar/picture_desktop/scrollbar_style/line_horizental.png);\n"
"}\n"
"QScrollArea QScrollBar::sub-page:horizontal\n"
"{\n"
"    border-image: url(:/picture_desktop/scrollbar/picture_desktop/scrollbar_style/line_horizental.png);\n"
"}\n"
"QScrollArea QScrollBar::add-line:horizontal\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:9px\n"
"}\n"
"QScrollArea QScrollBar::sub-line:horizontal\n"
"{\n"
"    subcontrol-origin: margin;\n"
"    border: 0px solid black;\n"
"    width:9px\n"
"}\n"
"QScrollArea QScrollBar::left-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_desktop/scrollbar/picture_desktop/scrollbar_style/left.png)"
                        ";\n"
"}\n"
"QScrollArea QScrollBar::right-arrow:horizontal\n"
"{\n"
"    image: url(:/picture_desktop/scrollbar/picture_desktop/scrollbar_style/right.png);\n"
"}"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 478, 478));
        scrollArea->setWidget(scrollAreaWidgetContents);
        slider_rotate = new QSlider(centralWidget);
        slider_rotate->setObjectName(QStringLiteral("slider_rotate"));
        slider_rotate->setGeometry(QRect(940, 103, 20, 420));
        slider_rotate->setStyleSheet(QString::fromUtf8("/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSlider\n"
"{\n"
"    border-color: #E872A2;\n"
"}\n"
"QSlider::groove:vertical \n"
"{  \n"
"    background: #E872A2;  \n"
"    width: 4px;  \n"
"    border-radius: 1px;  \n"
"    padding-left:-1px;  \n"
"    padding-right:-1px;  \n"
"    padding-top:-1px;  \n"
"    padding-bottom:-1px;  \n"
"} \n"
"QSlider::sub-page:vertical\n"
"{  \n"
"    background: #E872A2;  \n"
"    border-radius: 2px;  \n"
"}\n"
"QSlider::add-page:vertical\n"
"{  \n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #439cf4, stop:1 #439cf4);  \n"
"    background: qlineargradient(x1: 0.2, y1: 0, x2: 1, y2: 1, stop: 0 #E872A2, stop: 1 #E872A2);  \n"
"    width: 10px;  \n"
"    border-radius: 2px;  \n"
"}\n"
"QSlider::handle:vertical\n"
"{     \n"
"    border-image: url(:/picture_desktop/slider/picture_desktop/slider_style/handle.png);\n"
"    margin: 1px -7px 1px -7px; \n"
"    height: 20px;\n"
"} "));
        slider_rotate->setMinimum(-180);
        slider_rotate->setMaximum(180);
        slider_rotate->setValue(0);
        slider_rotate->setOrientation(Qt::Vertical);
        slider_rotate->setInvertedAppearance(true);
        slider_resize = new QSlider(centralWidget);
        slider_resize->setObjectName(QStringLiteral("slider_resize"));
        slider_resize->setGeometry(QRect(413, 103, 20, 420));
        slider_resize->setStyleSheet(QString::fromUtf8("/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSlider\n"
"{\n"
"    border-color: #E872A2;\n"
"}\n"
"QSlider::groove:vertical \n"
"{  \n"
"    background: #E872A2;  \n"
"    width: 4px;  \n"
"    border-radius: 1px;  \n"
"    padding-left:-1px;  \n"
"    padding-right:-1px;  \n"
"    padding-top:-1px;  \n"
"    padding-bottom:-1px;  \n"
"} \n"
"QSlider::sub-page:vertical\n"
"{  \n"
"    background: #E872A2;  \n"
"    border-radius: 2px;  \n"
"}\n"
"QSlider::add-page:vertical\n"
"{  \n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #439cf4, stop:1 #439cf4);  \n"
"    background: qlineargradient(x1: 0.2, y1: 0, x2: 1, y2: 1, stop: 0 #E872A2, stop: 1 #E872A2);  \n"
"    width: 10px;  \n"
"    border-radius: 2px;  \n"
"}\n"
"QSlider::handle:vertical\n"
"{     \n"
"    border-image: url(:/picture_desktop/slider/picture_desktop/slider_style/handle.png);\n"
"    margin: 1px -7px 1px -7px; \n"
"    height: 20px;\n"
"} "));
        slider_resize->setMinimum(1);
        slider_resize->setMaximum(1600);
        slider_resize->setValue(100);
        slider_resize->setOrientation(Qt::Vertical);
        slider_resize->setInvertedAppearance(true);
        slider_bg_r = new QSlider(centralWidget);
        slider_bg_r->setObjectName(QStringLiteral("slider_bg_r"));
        slider_bg_r->setGeometry(QRect(480, 566, 130, 20));
        slider_bg_r->setStyleSheet(QString::fromUtf8("/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSlider\n"
"{\n"
"    border-color: #E872A2;\n"
"}\n"
"QSlider::groove:horizontal \n"
"{  \n"
"    background: #E872A2;  \n"
"    height: 4px;  \n"
"    border-radius: 1px;  \n"
"    padding-left:-1px;  \n"
"    padding-right:-1px;  \n"
"    padding-top:-1px;  \n"
"    padding-bottom:-1px;  \n"
"} \n"
"QSlider::sub-page:horizontal\n"
"{  \n"
"    background: #E872A2;  \n"
"    border-radius: 2px;  \n"
"}\n"
"QSlider::add-page:horizontal\n"
"{  \n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #439cf4, stop:1 #439cf4);  \n"
"    background: qlineargradient(x1: 0.2, y1: 0, x2: 1, y2: 1, stop: 0 #E872A2, stop: 1 #E872A2);  \n"
"    height: 10px;  \n"
"    border-radius: 2px;  \n"
"}\n"
"QSlider::handle:horizontal\n"
"{     \n"
"    border-image: url(:/picture_desktop/slider/picture_desktop/slider_style/handle.png);\n"
"    margin: -7px 1px -7px 1px; \n"
"    width: 20px;\n"
"} "));
        slider_bg_r->setMinimum(0);
        slider_bg_r->setMaximum(255);
        slider_bg_r->setSingleStep(0);
        slider_bg_r->setValue(255);
        slider_bg_r->setOrientation(Qt::Horizontal);
        slider_bg_g = new QSlider(centralWidget);
        slider_bg_g->setObjectName(QStringLiteral("slider_bg_g"));
        slider_bg_g->setGeometry(QRect(625, 566, 130, 20));
        slider_bg_g->setStyleSheet(QString::fromUtf8("/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSlider\n"
"{\n"
"    border-color: #E872A2;\n"
"}\n"
"QSlider::groove:horizontal \n"
"{  \n"
"    background: #E872A2;  \n"
"    height: 4px;  \n"
"    border-radius: 1px;  \n"
"    padding-left:-1px;  \n"
"    padding-right:-1px;  \n"
"    padding-top:-1px;  \n"
"    padding-bottom:-1px;  \n"
"} \n"
"QSlider::sub-page:horizontal\n"
"{  \n"
"    background: #E872A2;  \n"
"    border-radius: 2px;  \n"
"}\n"
"QSlider::add-page:horizontal\n"
"{  \n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #439cf4, stop:1 #439cf4);  \n"
"    background: qlineargradient(x1: 0.2, y1: 0, x2: 1, y2: 1, stop: 0 #E872A2, stop: 1 #E872A2);  \n"
"    height: 10px;  \n"
"    border-radius: 2px;  \n"
"}\n"
"QSlider::handle:horizontal\n"
"{     \n"
"    border-image: url(:/picture_desktop/slider/picture_desktop/slider_style/handle.png);\n"
"    margin: -7px 1px -7px 1px; \n"
"    width: 20px;\n"
"} "));
        slider_bg_g->setMinimum(0);
        slider_bg_g->setMaximum(255);
        slider_bg_g->setValue(255);
        slider_bg_g->setOrientation(Qt::Horizontal);
        slider_bg_b = new QSlider(centralWidget);
        slider_bg_b->setObjectName(QStringLiteral("slider_bg_b"));
        slider_bg_b->setGeometry(QRect(770, 566, 130, 20));
        slider_bg_b->setStyleSheet(QString::fromUtf8("/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSlider\n"
"{\n"
"    border-color: #E872A2;\n"
"}\n"
"QSlider::groove:horizontal \n"
"{  \n"
"    background: #E872A2;  \n"
"    height: 4px;  \n"
"    border-radius: 1px;  \n"
"    padding-left:-1px;  \n"
"    padding-right:-1px;  \n"
"    padding-top:-1px;  \n"
"    padding-bottom:-1px;  \n"
"} \n"
"QSlider::sub-page:horizontal\n"
"{  \n"
"    background: #E872A2;  \n"
"    border-radius: 2px;  \n"
"}\n"
"QSlider::add-page:horizontal\n"
"{  \n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #439cf4, stop:1 #439cf4);  \n"
"    background: qlineargradient(x1: 0.2, y1: 0, x2: 1, y2: 1, stop: 0 #E872A2, stop: 1 #E872A2);  \n"
"    height: 10px;  \n"
"    border-radius: 2px;  \n"
"}\n"
"QSlider::handle:horizontal\n"
"{     \n"
"    border-image: url(:/picture_desktop/slider/picture_desktop/slider_style/handle.png);\n"
"    margin: -7px 1px -7px 1px; \n"
"    width: 20px;\n"
"} "));
        slider_bg_b->setMinimum(0);
        slider_bg_b->setMaximum(255);
        slider_bg_b->setValue(255);
        slider_bg_b->setOrientation(Qt::Horizontal);
        label_background = new QLabel(centralWidget);
        label_background->setObjectName(QStringLiteral("label_background"));
        label_background->setGeometry(QRect(447, 73, 480, 480));
        label_background->setStyleSheet(QString::fromUtf8("/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QLabel\n"
"{\n"
"    border: 1px solid #00E872A2;\n"
"    background: #00FFFFFF;\n"
"}"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(447, 0, 480, 73));
        label->setPixmap(QPixmap(QString::fromUtf8("C:/Users/Administrator/Desktop/word.png")));
        pushButton_cocoa_1 = new QPushButton(centralWidget);
        pushButton_cocoa_1->setObjectName(QStringLiteral("pushButton_cocoa_1"));
        pushButton_cocoa_1->setGeometry(QRect(911, 31, 16, 16));
        pushButton_cocoa_1->setStyleSheet(QStringLiteral("border-image: url(:/picture_desktop/icon/picture_desktop/icon/dialog_arrow.png);"));
        label_file_path = new QLabel(centralWidget);
        label_file_path->setObjectName(QStringLiteral("label_file_path"));
        label_file_path->setGeometry(QRect(490, 31, 410, 16));
        spinBox_1 = new QSpinBox(centralWidget);
        spinBox_1->setObjectName(QStringLiteral("spinBox_1"));
        spinBox_1->setGeometry(QRect(501, 54, 38, 18));
        spinBox_1->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_1->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/up_button.png);   \n"
"    background: #00FFFFFF;  \n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/down_button.png); \n"
"    background: #00FFFFFF;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/up_button.png);   \n"
"    background: #00FFFFFF;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/down_button.png); \n"
"    background: #00FFFFFF;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #E872A2;\n"
"    background: #00FFFFFF;\n"
"}"));
        spinBox_1->setMinimum(1);
        spinBox_1->setMaximum(1600);
        spinBox_1->setValue(100);
        spinBox_2 = new QSpinBox(centralWidget);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(607, 54, 38, 18));
        spinBox_2->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/up_button.png);   \n"
"    background: #00FFFFFF;  \n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/down_button.png); \n"
"    background: #00FFFFFF;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/up_button.png);   \n"
"    background: #00FFFFFF;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/down_button.png); \n"
"    background: #00FFFFFF;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #E872A2;\n"
"    background: #00FFFFFF;\n"
"}"));
        spinBox_2->setMinimum(-180);
        spinBox_2->setMaximum(180);
        spinBox_2->setValue(0);
        spinBox_3 = new QSpinBox(centralWidget);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setGeometry(QRect(791, 54, 38, 18));
        spinBox_3->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_3->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/up_button.png);   \n"
"    background: #00FFFFFF;  \n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/down_button.png); \n"
"    background: #00FFFFFF;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/up_button.png);   \n"
"    background: #00FFFFFF;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/down_button.png); \n"
"    background: #00FFFFFF;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #E872A2;\n"
"    background: #00FFFFFF;\n"
"}"));
        spinBox_3->setMinimum(0);
        spinBox_3->setMaximum(255);
        spinBox_3->setValue(255);
        spinBox_4 = new QSpinBox(centralWidget);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setGeometry(QRect(840, 54, 38, 18));
        spinBox_4->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_4->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/up_button.png);   \n"
"    background: #00FFFFFF;  \n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/down_button.png); \n"
"    background: #00FFFFFF;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/up_button.png);   \n"
"    background: #00FFFFFF;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/down_button.png); \n"
"    background: #00FFFFFF;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #E872A2;\n"
"    background: #00FFFFFF;\n"
"}"));
        spinBox_4->setMinimum(0);
        spinBox_4->setMaximum(255);
        spinBox_4->setValue(255);
        spinBox_5 = new QSpinBox(centralWidget);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setGeometry(QRect(889, 54, 38, 18));
        spinBox_5->setContextMenuPolicy(Qt::NoContextMenu);
        spinBox_5->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\234\252\346\214\211\344\270\213*/\n"
"QSpinBox::up-button\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/up_button.png);   \n"
"    background: #00FFFFFF;  \n"
"}\n"
"QSpinBox::down-button\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/down_button.png); \n"
"    background: #00FFFFFF;\n"
"}\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213*/\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/up_button.png);   \n"
"    background: #00FFFFFF;     \n"
"}\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"    image: url(:/picture_desktop/spinbox/picture_desktop/spinbox_style/down_button.png); \n"
"    background: #00FFFFFF;\n"
"}\n"
"/*\346\200\273\344\275\223\350\256\276\347\275\256*/\n"
"QSpinBox\n"
"{\n"
"    border: 1px solid #E872A2;\n"
"    background: #00FFFFFF;\n"
"}"));
        spinBox_5->setMinimum(0);
        spinBox_5->setMaximum(255);
        spinBox_5->setValue(255);
        DesktopOmakeClass->setCentralWidget(centralWidget);
        label_background->raise();
        label_picture->raise();
        scrollArea->raise();
        slider_rotate->raise();
        slider_resize->raise();
        slider_bg_r->raise();
        slider_bg_g->raise();
        slider_bg_b->raise();
        label->raise();
        pushButton_cocoa_1->raise();
        label_file_path->raise();
        spinBox_1->raise();
        spinBox_2->raise();
        spinBox_3->raise();
        spinBox_4->raise();
        spinBox_5->raise();

        retranslateUi(DesktopOmakeClass);

        QMetaObject::connectSlotsByName(DesktopOmakeClass);
    } // setupUi

    void retranslateUi(QMainWindow *DesktopOmakeClass)
    {
        DesktopOmakeClass->setWindowTitle(QApplication::translate("DesktopOmakeClass", "PictureWatch", Q_NULLPTR));
        label_picture->setText(QString());
        label_background->setText(QString());
        label->setText(QString());
        pushButton_cocoa_1->setText(QString());
        label_file_path->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DesktopOmakeClass: public Ui_DesktopOmakeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESKTOPOMAKE_H
