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
#include <QPen>
#include <QBrush>
#include <QClipboard>
#include <QButtonGroup>
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
#include <string>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include <math.h>
#include "ui_Desktop.h"
#include "ui_Help.h"
#include "ui_File.h"
#include "ui_Widget.h"
#include "ui_Setting.h"
#include "ui_SettingDynamic.h"
#include "ui_SettingOther.h"
#include "Desktop.h"
#include "Help.h"
#include "File.h"
#include "Widget.h"
#include "Setting.h"
#include "SettingDynamic.h"
#include "SettingOther.h"

//语言环境
#pragma execution_character_set("utf-8")

//全局常量
#define REG_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"//程序开机自启动需要的注册表项
#define PROGRAM_SYSTEM_TRAY_ICON_PATH_STRING ".\\picture_desktop\\icon\\icon_system_tray.png"//系统托盘图标
#define PROGRAM_SYSTEM_TRAY_TIP_STRING "wusa-desktop"//系统托盘提示
#define FILE_FONT_DEFAULT_SIZE 9//默认字体大小
#define FILE_FONT_PATH_STRING ".\\font\\font_df_girl.ttf"//字体文件路径
#define FILE_SETTING_STATIC_PATH_STRING ".\\setting_desktop\\setting_static.ini"//静态信息配置文件
#define FILE_SETTING_DYNAMIC_PATH_STRING ".\\setting_desktop\\setting_dynamic.ini"//动态信息配置文件
#define FILE_SETTING_OPEN_PATH_UNDEFINE_DEFAULT_STRING L"null"//配置文件打开程序为空时默认字符串
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING "/mainwindow"//静态信息配置文件目录头部1文件内路径
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING "/subwindow"//静态信息配置文件目录头部2前半部分文件内路径
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_1_STRING "/is_hide"//静态信息配置文件目录尾部1文件内路径
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_2_STRING "/time_interval"//静态信息配置文件目录尾部2文件内路径
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING "/is_on_top"//静态信息配置文件目录尾部3文件内路径
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_4_STRING "/transparent"//静态信息配置文件目录尾部4文件内路径
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_5_STRING "/auto_run"//静态信息配置文件目录尾部5文件内路径
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING "/is_enable"//静态信息配置文件目录尾部6文件内路径
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_7_STRING "/path"//静态信息配置文件目录尾部7文件内路径
#define FILE_SETTING_DYNAMIC_CATALOG_1_1_INNER_PATH_STRING "/mainposition/main_x"//动态信息配置文件目录1_1文件内路径
#define FILE_SETTING_DYNAMIC_CATALOG_1_2_INNER_PATH_STRING "/mainposition/main_y"//动态信息配置文件目录1_2文件内路径
#define FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING "/subposition/sub_"//动态信息配置文件目录2前半部分文件内路径
#define FILE_SETTING_DYNAMIC_CATALOG_2_1_BACK_INNER_PATH_STRING "_x"//动态信息配置文件目录2_1后半部分文件内路径
#define FILE_SETTING_DYNAMIC_CATALOG_2_2_BACK_INNER_PATH_STRING "_y"//动态信息配置文件目录2_2后半部分文件内路径
#define WINDOW_ANIMATION_TIME_NUMBER 300//启动和关闭动画持续时间
#define WINDOW_ANIMATION_HIDE_NUMBER 1//窗口隐藏时的透明度
#define WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER 0//窗口消失透明度
#define WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER 1//窗口常规透明度
#define WINDOW_SIZE_WIDTH_NUMBER 160//窗口宽度
#define WINDOW_SIZE_HEIGHT_NUMBER 160//窗口高度
#define WINDOW_SIZE_SIDE_LENGTH_NUMBER 100//隐藏窗口边长
#define WINDOW_RANDOM_MAX_NUMBER 7//绘制窗口背景用到随机数的最大值
#define WINDOW_RANDOM_MIN_NUMBER 1//绘制窗口背景用到随机数的最小值
#define WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER 7//最大控件数目，如需要修改该属性，则相应文件也需要被修改
#define WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\mainwindow_background\\bg_"//背景图片路径的非后缀部分的不变部分
#define WINDOW_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//背景图片路径的后缀部分
#define WINDOW_BACKGROUND_UP_HIDE_PICTURE_PATH_STRING ".\\picture_desktop\\mainwindow_background\\bg_hide_up.png"//隐藏状态屏幕上方背景图片路径
#define WINDOW_BACKGROUND_DOWN_HIDE_PICTURE_PATH_STRING ".\\picture_desktop\\mainwindow_background\\bg_hide_down.png"//隐藏状态屏幕下方背景图片路径
#define WINDOW_BACKGROUND_LEFT_HIDE_PICTURE_PATH_STRING ".\\picture_desktop\\mainwindow_background\\bg_hide_left.png"//隐藏状态屏幕左边背景图片路径
#define WINDOW_BACKGROUND_RIGHT_HIDE_PICTURE_PATH_STRING ".\\picture_desktop\\mainwindow_background\\bg_hide_right.png"//隐藏状态屏幕右边背景图片路径
#define DIALOG_WEDGIT_SIZE_WIDTH_NUMBER 72//组件界面宽度
#define DIALOG_WEDGIT_SIZE_HEIGHT_NUMBER 80//组件界面宽度
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
#define DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER 0//设置界面最小透明度
#define DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER 10//设置界面最大透明度
#define DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER 1//设置界面每次透明度改变量
#define DIALOG_SETTING_PATH_DEFAULT_STRING "null"//设置界面路径默认字符串
#define DIALOG_WIDGET_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\desktop_widget_background\\bg_"//控件背景图片路径的非后缀部分的不变部分
#define DIALOG_WIDGET_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//控件背景图片路径的后缀部分
#define DIALOG_SETTING_WIDGET_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\setting_widget_background\\bg_"//设置界面控件背景图片路径的非后缀部分的不变部分
#define DIALOG_SETTING_WIDGET_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//设置界面控件背景图片路径的后缀部分
#define DIALOG_SETTING_STATIC_BACKGROUND_PICTURE_PATH_STRING ".\\picture_desktop\\setting_static_background\\dialog.png"//静态设置界面背景图片路径
#define DIALOG_SETTING_DYNAMIC_BACKGROUND_PICTURE_PATH_STRING ".\\picture_desktop\\setting_dynamic_background\\dialog.png"//动态设置界面背景图片路径
#define DIALOG_SETTING_OTHER_BACKGROUND_PICTURE_PATH_STRING ".\\picture_desktop\\setting_other_background\\dialog.png"//其他设置界面背景图片路径
#define DIALOG_INFORMATION_HELP_PATH_STRING ".\\picture_desktop\\help_information\\information_"//信息框提示内容文字路径的非后缀不变部分
#define DIALOG_MARGIN_PICTURE_PATH_STRING ".\\picture_start\\warning_margin\\margin.png"//信息框边框图片路径
#define DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_background\\background_"//信息框背景路径的非后缀部分的不变部分
#define DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//信息框背景路径的后缀部分
#define DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING ".png"//信息框提示内容文字路径的后缀部分
#define DIALOG_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_chara\\chara_0"//信息框左侧图片路径的非后缀部分的不变部分
#define DIALOG_CHARA_PICTURE_PATH_BREAK_STRING "_0"//信息框左侧图片路径的下划线部分
#define DIALOG_CHARA_PICTURE_PATH_BACK_STRING ".png"//信息框左侧图片路径的后缀部分
#define DIALOG_INFORMATION_OPEN_MORE_THAN_ONE_PATH_STRING ".\\picture_desktop\\open_more_than_one_information\\information_"//多开程序阻止提示信息
#define DIALOG_INFORMATION_FILE_PICTURE_PATH_STRING ".\\picture_desktop\\filedialog_information\\information_"//文件打开或保存选择提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_FILE_HEAD_PICTURE_PATH_STRING ".\\picture_desktop\\filedialog_information\\informationhead_"//文件打开或保存选择提示框头部文字路径的非后缀部分的不变部分
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\filedialog_background\\background_"//打开或保存文件信息框背景路径的非后缀部分的不变部分
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//打开或保存文件信息框背景路径的后缀部分
#define DIALOG_FILE_MARGIN_PICTURE_PATH_STRING ".\\picture_desktop\\filedialog_margin\\margin.png"//文件打开与保存信息框边框图片路径
#define DIALOG_INFORMATION_CANNOT_START_PROGRAM_PATH_STRING ".\\picture_desktop\\cannot_start_program_information\\information_"//无法打开程序提示信息
#define DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING ".\\picture_desktop\\wrong_file_or_path_information\\information_"//设置窗口不存在的文件或路径窗口提示信息

#endif