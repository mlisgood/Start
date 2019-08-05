#ifndef DEFINE_H
#define DEFINE_H

//头文件
#include <QtWidgets/QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QString>
#include <QDesktopWidget>
#include <QDialog>
#include <QPoint>
#include <QDesktopWidget>
#include <QTimer>
#include <QScrollBar>
#include <QFontDatabase>
#include <QFileSystemModel>
#include <QPropertyAnimation>
#include <QDateTime>
#include <QFontDatabase>
#include <QScreen>
#include <QDrag>
#include <QUrl>
#include <QMimeData>
#include <QSplashScreen>
#include <string>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include "ui_DesktopOmake.h"
#include "ui_Help.h"
#include "ui_File.h"
#include "DesktopOmake.h"
#include "Help.h"
#include "File.h"

//语言环境
#pragma execution_character_set("utf-8")

//全局常量
#define FILE_FONT_DEFAULT_SIZE 9//默认字体大小
#define FILE_FONT_PATH_STRING ".\\font\\font_df_girl.ttf"//字体文件路径
#define FILE_SETTING_STATIC_PATH_STRING ".\\setting_desktop\\setting_static.ini"//静态信息配置文件
#define WINDOW_SIZE_WIDTH_NUMBER 1000//主界面宽度
#define WINDOW_SIZE_HEIGHT_NUMBER 600//主界面高度
#define WINDOW_WORD_PICTURE_X_OFFSET_NUMBER 447//文字图片横向偏移
#define WINDOW_WORD_PICTURE_Y_OFFSET_NUMBER 0//文字图片纵向偏移
#define WINDOW_WORD_PICTURE_SIZE_WIDTH_NUMBER 480//主界面宽度
#define WINDOW_WORD_PICTURE_SIZE_HEIGHT_NUMBER 73//主界面高度
#define WINDOW_ANIMATION_TIME_NUMBER 300//启动和关闭动画持续时间
#define WINDOW_ANIMATION_HIDE_NUMBER 1//窗口隐藏时的透明度
#define WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER 0//窗口消失透明度
#define WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER 1//窗口常规透明度
#define WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\program_desktopomake\\main_background\\dialog.png"//背景图片路径
#define WINDOW_WORD_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\program_desktopomake\\word_background\\word.png"//文字图片路径
#define WINDOW_SPLASH_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\program_desktopomake\\splash_picture\\splash.png"//启动界面图片路径
#define DIALOG_SIZE_WIDTH_NUMBER 600//信息框宽度
#define DIALOG_SIZE_HEIGHT_NUMBER 200//信息框高度
#define DIALOG_RANDOM_MAX_NUMBER 5//绘制信息框背景用到随机数的最大值
#define DIALOG_RANDOM_MIN_NUMBER 1//绘制信息框背景用到随机数的最小值
#define DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER 8//绘制信息框左侧图片用到随机数的最大值
#define DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER 1//绘制信息框左侧图片用到随机数的最小值
#define DIALOG_INFORMATION_FILE_WIDTH_NUMBER 600//文件打开或保存信息框总文本信息宽度
#define DIALOG_INFORMATION_FILE_HEIGHT_NUMBER 30//文件打开或保存信息框总文本信息高度
#define DIALOG_INFORMATION_FILE_X_OFFSET_NUMBER 0//文件打开或保存信息框文本信息横向起始位置
#define DIALOG_INFORMATION_FILE_Y_OFFSET_NUMBER 445//文件打开或保存信息框文本信息纵向起始位置
#define DIALOG_INFORMATION_FILE_HEAD_X_OFFSET_NUMBER 0//文件打开或保存信息框头部文本信息横向起始位置
#define DIALOG_INFORMATION_FILE_HEAD_Y_OFFSET_NUMBER 50//文件打开或保存信息框头部文本信息纵向起始位置
#define DIALOG_INFORMATION_HELP_PATH_STRING ".\\picture_desktop\\help_information\\information_"//信息框提示内容文字路径的非后缀不变部分
#define DIALOG_MARGIN_PICTURE_PATH_STRING ".\\picture_start\\warning_margin\\margin.png"//信息框边框图片路径
#define DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_background\\background_"//信息框背景路径的非后缀部分的不变部分
#define DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//信息框背景路径的后缀部分
#define DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING ".png"//信息框提示内容文字路径的后缀部分
#define DIALOG_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_chara\\chara_0"//信息框左侧图片路径的非后缀部分的不变部分
#define DIALOG_CHARA_PICTURE_PATH_BREAK_STRING "_0"//信息框左侧图片路径的下划线部分
#define DIALOG_CHARA_PICTURE_PATH_BACK_STRING ".png"//信息框左侧图片路径的后缀部分
#define DIALOG_INFORMATION_FILE_PICTURE_PATH_STRING ".\\picture_desktop\\filedialog_information\\information_"//文件打开或保存选择提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_FILE_HEAD_PICTURE_PATH_STRING ".\\picture_desktop\\filedialog_information\\informationhead_"//文件打开或保存选择提示框头部文字路径的非后缀部分的不变部分
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\filedialog_background\\background_"//打开或保存文件信息框背景路径的非后缀部分的不变部分
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//打开或保存文件信息框背景路径的后缀部分
#define DIALOG_FILE_MARGIN_PICTURE_PATH_STRING ".\\picture_desktop\\filedialog_margin\\margin.png"//文件打开与保存信息框边框图片路径
#define DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING ".\\picture_desktop\\program_desktopomake\\wrong_picture_file\\information_"//打开图片错误提示信息

#endif