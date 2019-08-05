#ifndef DEFINE_H
#define DEFINE_H

//所需要的头文件

#include <QtWidgets/QMainWindow>
#include <QtCore>
#include <QSplashScreen> 
#include <QThread>
#include <QMouseEvent>
#include <QMainWindow>
#include <QPoint>
#include <QWidget>
#include <QString>
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QFontDatabase>
#include <QFileSystemModel>
#include <QDir>
#include <QScrollBar>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include "ui_Start.h"
#include "ui_Filemissing.h"
#include "Start.h"
#include "Filemissing.h"
#include "main.h" 

//指定语言环境
#pragma execution_character_set("utf-8")

//所需要的常量

#define FILE_FONT_DEFAULT_SIZE 9//默认字体大小
#define FILE_FONT_PATH_STRING ".\\font\\font_df_girl.ttf"//字体文件路径
#define FILE_COPY_SOURCE_1_PATH_STRING ".\\default_setting\\setting_desktop"//拷贝配置文件源文件夹1路径
#define FILE_COPY_SOURCE_2_PATH_STRING ".\\default_setting\\setting_lock"//拷贝配置文件源文件夹2路径
#define FILE_COPY_SOURCE_3_PATH_STRING ".\\default_setting\\setting_notepad"//拷贝配置文件源文件夹3路径
#define FILE_COPY_SOURCE_4_PATH_STRING ".\\default_setting\\setting_tools"//拷贝配置文件源文件夹4路径
#define FILE_COPY_TARGET_1_PATH_STRING ".\\setting_desktop"//拷贝配置文件目标文件夹1路径
#define FILE_COPY_TARGET_2_PATH_STRING ".\\setting_lock"//拷贝配置文件目标文件夹2路径
#define FILE_COPY_TARGET_3_PATH_STRING ".\\setting_notepad"//拷贝配置文件目标文件夹3路径
#define FILE_COPY_TARGET_4_PATH_STRING ".\\setting_tools"//拷贝配置文件目标文件夹4路径
#define WINDOW_ANIMATION_TIME_NUMBER 300//启动和关闭动画持续时间
#define WINDOW_ANIMATION_TRANSPRENT_TRANSPRENT_NUMBER 0.4//窗口透明模式透明度
#define WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER 1//窗口常规模式透明度
#define WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER 0//窗口消失透明度
#define WINDOW_START_BACKGROUND_PICTURE_PATH_STRING ".\\picture_start\\window_start_background\\dialog.png"
#define DIALOG_SIZE_WIDTH_NUMBER 600//提示框宽度
#define DIALOG_SIZE_HEIGHT_NUMBER 200//提示框高度
#define DIALOG_RANDOM_MAX_NUMBER 5//绘制提示框背景用到随机数的最大值。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define DIALOG_RANDOM_MIN_NUMBER 1//绘制提示框背景用到随机数的最小值。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER 8//绘制提示框左侧图片用到随机数的最大值。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER 1//绘制提示框左侧图片用到随机数的最小值。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define DIALOG_INFORMATION_STATUS_1_FLAG 1//提示框提示信息1
#define DIALOG_INFORMATION_STATUS_2_FLAG 2//提示框提示信息2
#define DIALOG_INFORMATION_STATUS_3_FLAG 3//提示框提示信息3
#define DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_background\\background_"//提示框背景路径的非后缀部分的不变部分
#define DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//提示框背景路径的后缀部分
#define DIALOG_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_chara\\chara_0"//提示框左侧图片路径的非后缀部分的不变部分。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define DIALOG_CHARA_PICTURE_PATH_BREAK_STRING "_0"//提示框左侧图片路径的下划线部分。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define DIALOG_CHARA_PICTURE_PATH_BACK_STRING ".png"//提示框左侧图片路径的后缀部分，这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define DIALOG_MARGIN_PICTURE_PATH_STRING ".\\picture_start\\warning_margin\\margin.png"//提示框边框图片路径
#define DIALOG_INFORMATION_1_PICTURE_PATH_STRING ".\\picture_start\\warning_information\\information_1_"//提示框提示内容1文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_2_PICTURE_PATH_STRING ".\\picture_start\\warning_information\\information_2_"//提示框提示内容2文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_3_PICTURE_PATH_STRING ".\\picture_start\\warning_information\\information_3_"//提示框提示内容3文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING ".png"//提示框提示内容文字路径的后缀部分
#define DIALOG_SET_BACKGROUND_PICTURE_PATH_STRING ".\\picture_start\\set_dialog\\dialog.png"
#define DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING ".\\picture_start\\wrong_file_or_path_information\\information_"//设置窗口不存在的文件或路径窗口提示信息
#define DIALOG_INFORMATION_FILE_PICTURE_PATH_STRING ".\\picture_start\\filedialog_information\\information_"//文件打开或保存选择提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_FILE_HEAD_PICTURE_PATH_STRING ".\\picture_start\\filedialog_information\\informationhead_"//文件打开或保存选择提示框头部文字路径的非后缀部分的不变部分

#endif
