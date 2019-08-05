#ifndef DEFINE_H
#define DEFINE_H

//指定头文件
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
#include <QSound>
#include <QTimer>
#include <QScrollBar>
#include <QFontDatabase>
#include <QFileSystemModel>
#include <QPropertyAnimation>
#include <QAudioInput>
#include <QDateTime>
#include <QFontDatabase>
#include <QAudioEncoderSettings>
#include <string>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include "ui_Tools.h"
#include "ui_Help.h"
#include "ui_Screenshot.h"
#include "ui_CounterSet.h"
#include "ui_Counter.h"
#include "ui_Note.h"
#include "ui_ToolsSet.h"
#include "ui_File.h"
#include "ui_ToolsSetExtra.h"
#include "ui_SoundRecordSet.h"
#include "ui_SoundRecord.h"
#include "Tools.h"
#include "Help.h"
#include "Screenshot.h"
#include "CounterSet.h"
#include "Counter.h"
#include "Note.h"
#include "ToolsSet.h"
#include "File.h"
#include "ToolsSetExtra.h"
#include "SoundRecordSet.h"
#include "SoundRecord.h"

//指定语言环境
#pragma execution_character_set("utf-8")

//全局常量
#define REG_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"//程序开机自启动需要的注册表项
#define PROGRAM_SYSTEM_TRAY_ICON_PATH_STRING ".\\picture_tools\\icon\\icon_system_tray.png"//系统托盘图标
#define PROGRAM_SYSTEM_TRAY_TIP_STRING "wusa-tools"//系统托盘提示
#define FILE_FONT_DEFAULT_SIZE 9//默认字体大小
#define FILE_FONT_PATH_STRING ".\\font\\font_df_girl.ttf"//字体文件路径
#define FILE_SETTING_MAINWINDOW_STYLE_PATH_STRING ".\\setting_tools\\mainwindow_style.ini"//主窗口风格及设置配置文件
#define FILE_SETTING_MAINWINDOW_STYLE_EXTRA_PATH_STRING ".\\setting_tools\\mainwindow_style_extra.ini"//主窗口风格及设置配置文件
#define FILE_SETTING_SOUND_RECORD_PATH_STRING ".\\setting_tools\\sound_record.ini"//录音设置配置文件
#define FILE_SOUND_RECORD_TIME_FORMAT_STRING "yyyy-MM-dd hh-mm-ss-zzz ddd"//录音输出文件时间格式
#define FILE_SOUND_RECORD_BACK_PATH_STRING ".wav"//录音输出文件后缀
#define FILE_SETTING_CATALOG_2_UNDEFINE_DEFAULT_STRING "null"//配置文件目录2未设置时的默认值
#define FILE_SETTING_CATALOG_1_INNER_PATH_STRING "/picture/mainpicture"//配置文件目录1文件内路径
#define FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING "/function/program1"//配置文件目录2-1文件内路径
#define FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING "/function/program2"//配置文件目录2-2文件内路径
#define FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING "/function/program3"//配置文件目录2-3文件内路径
#define FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING "/function/program4"//配置文件目录2-4文件内路径
#define FILE_SETTING_CATALOG_2_5_INNER_PATH_STRING "/function/program5"//配置文件目录2-5文件内路径
#define FILE_SETTING_CATALOG_2_6_INNER_PATH_STRING "/function/program6"//配置文件目录2-6文件内路径
#define FILE_SETTING_CATALOG_2_7_INNER_PATH_STRING "/function/program7"//配置文件目录2-7文件内路径
#define FILE_SETTING_CATALOG_2_8_INNER_PATH_STRING "/function/program8"//配置文件目录2-8文件内路径
#define FILE_SETTING_CATALOG_3_INNER_PATH_STRING "/autorun/autorun"//配置文件目录3文件内路径
#define FILE_SETTING_CATALOG_4_INNER_PATH_STRING "/font/font"//配置文件目录4文件内路径
#define FILE_SETTING_CATALOG_5_1_INNER_PATH_STRING "/position/x"//配置文件目录5-1文件内路径
#define FILE_SETTING_CATALOG_5_2_INNER_PATH_STRING "/position/y"//配置文件目录5-2文件内路径
#define FILE_EXTRA_SETTING_CATALOG_1_1_INNER_PATH_STRING "/background/transparent"//附加高级设置配置文件目录1-1文件内路径
#define FILE_EXTRA_SETTING_CATALOG_1_2_INNER_PATH_STRING "/background/size"//附加高级设置配置文件目录1-2文件内路径
#define FILE_EXTRA_SETTING_CATALOG_2_1_INNER_PATH_STRING "/backgroundhide/isactive"//附加高级设置配置文件目录2-1文件内路径
#define FILE_EXTRA_SETTING_CATALOG_2_2_INNER_PATH_STRING "/backgroundhide/waittime"//附加高级设置配置文件目录2-2文件内路径
#define FILE_EXTRA_SETTING_CATALOG_2_3_INNER_PATH_STRING "/backgroundhide/background"//附加高级设置配置文件目录2-3文件内路径
#define FILE_EXTRA_SETTING_CATALOG_2_4_INNER_PATH_STRING "/backgroundhide/size"//附加高级设置配置文件目录2-4文件内路径
#define FILE_EXTRA_SETTING_CATALOG_2_5_INNER_PATH_STRING "/backgroundhide/x"//附加高级设置配置文件目录2-5文件内路径
#define FILE_EXTRA_SETTING_CATALOG_2_6_INNER_PATH_STRING "/backgroundhide/y"//附加高级设置配置文件目录2-6文件内路径
#define FILE_EXTRA_SETTING_CATALOG_2_7_INNER_PATH_STRING "/backgroundhide/transparent"//附加高级设置配置文件目录2-7文件内路径
#define FILE_SOUND_RECORD_SETTING_CATALOG_1_INNER_PATH_STRING "/machine/value"//录音设置配置文件目录1文件内路径
#define FILE_SOUND_RECORD_SETTING_CATALOG_2_INNER_PATH_STRING "/trackmodel/value"//录音设置配置文件目录2文件内路径
#define FILE_SOUND_RECORD_SETTING_CATALOG_3_INNER_PATH_STRING "/path/value"//录音设置配置文件目录3文件内路径
#define FILE_SETTING_PATH_DEFAULT_SHOW_STRING "#default#"//录音设置文件路径的默认显示值
#define FILE_SETTING_PATH_DEFAULT_STRING ".\\soundrecord\\"//录音设置文件路径的默认值
#define WINDOW_ANIMATION_TIME_NUMBER 300//启动和关闭动画持续时间
#define WINDOW_ANIMATION_TRANSPRENT_TRANSPRENT_NUMBER 0.4//窗口透明模式透明度
#define WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER 1//窗口常规模式透明度
#define WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER 0//窗口消失透明度
#define WINDOW_BACKGROUND_PAINT_START_X_NUMBER 0//背景图片绘制起始点横坐标
#define WINDOW_BACKGROUND_PAINT_START_Y_NUMBER 0//背景图片绘制起始点纵坐标
#define WINDOW_DIALOG_TITLE_INDEX_1_PATH_STRING "魔法少女　チノ - 一緒にモフモフしよー"//窗口标题1
#define WINDOW_DIALOG_TITLE_INDEX_2_PATH_STRING "ソーサラー　チノ - 一緒にモフモフしよー"//窗口标题2
#define WINDOW_DIALOG_TITLE_INDEX_3_PATH_STRING "ガンナー　マヤ - 一緒にモフモフしよー"//窗口标题3
#define WINDOW_DIALOG_TITLE_INDEX_4_PATH_STRING "バーサーカー　メグ - 一緒にモフモフしよー"//窗口标题4
#define WINDOW_PICTURE_BACKGROUND_INDEX_1_PATH_STRING ".\\picture_tools\\background\\background_1_"//背景图片1非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_INDEX_2_PATH_STRING ".\\picture_tools\\background\\background_2_"//背景图片2非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_INDEX_3_PATH_STRING ".\\picture_tools\\background\\background_3_"//背景图片3非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_INDEX_4_PATH_STRING ".\\picture_tools\\background\\background_4_"//背景图片4非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_INDEX_1_MIDDLE_PATH_STRING "1"//背景图片尺寸1非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_INDEX_2_MIDDLE_PATH_STRING "2"//背景图片尺寸2非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_INDEX_3_MIDDLE_PATH_STRING "3"//背景图片尺寸3非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_INDEX_4_MIDDLE_PATH_STRING "4"//背景图片尺寸4非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_1_PATH_STRING ".\\picture_tools\\background_extra\\background_1_"//额外背景图片1非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_2_PATH_STRING ".\\picture_tools\\background_extra\\background_2_"//额外背景图片2非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_3_PATH_STRING ".\\picture_tools\\background_extra\\background_3_"//额外背景图片3非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_4_PATH_STRING ".\\picture_tools\\background_extra\\background_4_"//额外背景图片4非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_5_PATH_STRING ".\\picture_tools\\background_extra\\background_5_"//额外背景图片5非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_6_PATH_STRING ".\\picture_tools\\background_extra\\background_6_"//额外背景图片6非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_7_PATH_STRING ".\\picture_tools\\background_extra\\background_7_"//额外背景图片7非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_1_MIDDLE_PATH_STRING "1"//额外背景图片尺寸1非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_2_MIDDLE_PATH_STRING "2"//额外背景图片尺寸2非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_3_MIDDLE_PATH_STRING "3"//额外背景图片尺寸3非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_4_MIDDLE_PATH_STRING "4"//额外背景图片尺寸4非后缀不变部分
#define WINDOW_PICTURE_BACKGROUND_INDEX_PATH_BACK_STRING ".png"//背景图片后缀部分
#define DIALOG_SIZE_WIDTH_NUMBER 600//信息框宽度
#define DIALOG_SIZE_HEIGHT_NUMBER 200//信息框高度
#define DIALOG_COUNTER_SIZE_WIDTH_NUMBER 290//计时器宽度
#define DIALOG_COUNTER_SIZE_HEIGHT_NUMBER 60//计时器高度
#define DIALOG_RANDOM_MAX_NUMBER 5//绘制信息框背景用到随机数的最大值
#define DIALOG_RANDOM_MIN_NUMBER 1//绘制信息框背景用到随机数的最小值
#define DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER 8//绘制信息框左侧图片用到随机数的最大值
#define DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER 1//绘制信息框左侧图片用到随机数的最小值
#define DIALOG_NOTE_BACKGROUND_PICTURE_RANDOM_MAX_NUMBER 10//绘制便签背景图片用到随机数的最大值
#define DIALOG_NOTE_BACKGROUND_PICTURE_RANDOM_MIN_NUMBER 1//绘制便签背景图片用到随机数的最小值
#define DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER 50//计时器时间图片绘制起始点横坐标
#define DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER 27//计时器时间图片绘制起始点纵坐标
#define DIALOG_COUNTER_NUMBER_PICTURE_WIDTH 20//计时器时间图片宽度
#define DIALOG_COUNTER_INTERVAL_NUMBER 1000//计时器计时间隔
#define DIALOG_TIME_COUNTER_END_VOICE_MAX_NUMBER 5//计时器到期播放声音的随机数的最大值
#define DIALOG_TIME_COUNTER_END_VOICE_MIN_NUMBER 1//计时器到期播放声音的随机数的最小值
#define DIALOG_INFORMATION_FILE_WIDTH_NUMBER 600//文件打开或保存信息框总文本信息宽度
#define DIALOG_INFORMATION_FILE_HEIGHT_NUMBER 30//文件打开或保存信息框总文本信息高度
#define DIALOG_INFORMATION_FILE_X_OFFSET_NUMBER 0//文件打开或保存信息框文本信息横向起始位置
#define DIALOG_INFORMATION_FILE_Y_OFFSET_NUMBER 445//文件打开或保存信息框文本信息纵向起始位置
#define DIALOG_INFORMATION_FILE_HEAD_X_OFFSET_NUMBER 0//文件打开或保存信息框头部文本信息横向起始位置
#define DIALOG_INFORMATION_FILE_HEAD_Y_OFFSET_NUMBER 50//文件打开或保存信息框头部文本信息纵向起始位置
#define DIALOG_SOUND_RECORD_NUMBER_PICTURE_WIDTH_NUMBER 140//录音窗口图片宽度
#define DIALOG_SOUND_RECORD_NUMBER_PICTURE_HEIGHT_NUMBER 200//录音窗口图片高度
#define DIALOG_SETTING_SOUND_RECORD_RATE_DEFAULT_NUMBER 48000//录音设置窗口默认采样频率
#define DIALOG_SETTING_SOUND_RECORD_BIT_DEFAULT_NUMBER 16//录音设置窗口默认量化位数
#define DIALOG_SCREENSHOT_EDGE_ALPHA_NUMBER 100//截图窗口周围非截图区域颜色不透明度
#define DIALOG_SCREENSHOT_RECT_RED_NUMBER 0//截图窗口截图区域矩形边框颜色R分量
#define DIALOG_SCREENSHOT_RECT_GREEN_NUMBER 150//截图窗口截图区域矩形边框颜色G分量
#define DIALOG_SCREENSHOT_RECT_BLUE_NUMBER 255//截图窗口截图区域矩形边框颜色B分量
#define DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING ".png"//信息框提示内容文字路径的后缀部分
#define DIALOG_MARGIN_PICTURE_PATH_STRING ".\\picture_start\\warning_margin\\margin.png"//信息框边框图片路径
#define DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_background\\background_"//信息框背景路径的非后缀部分的不变部分
#define DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//信息框背景路径的后缀部分
#define DIALOG_TOOLS_SET_BACKGROUND_PICTURE_PATH_STRING ".\\picture_tools\\tools_set_dialog\\dialog.png"//悬浮组件设置框背景路径
#define DIALOG_TOOLS_SET_EXTRA_BACKGROUND_PICTURE_PATH_STRING ".\\picture_tools\\tools_set_extra_dialog\\dialog.png"//悬浮组件额外设置框背景路径
#define DIALOG_TOOLS_SOUND_RECORD_SET_BACKGROUND_PICTURE_PATH_STRING ".\\picture_tools\\sound_record_set_dialog\\dialog.png"//悬浮组件录音设置框背景路径
#define DIALOG_COUNTER_SET_BACKGROUND_PICTURE_PATH_STRING ".\\picture_tools\\counter_set_dialog\\dialog.png"//计时器设置框背景路径
#define DIALOG_COUNTER_BACKGROUND_PICTURE_PATH_STRING ".\\picture_tools\\counter_dialog\\dialog.png"//计时器背景路径
#define DIALOG_COUNTER_NUMBER_PICTURE_PATH_FRONT_STRING ".\\picture_tools\\counter_number\\time_"//计时器数字图片非后缀部分的不变部分
#define DIALOG_COUNTER_NUMBER_PICTURE_PATH_BACK_STRING ".png"//计时器数字图片后缀部分
#define DIALOG_COUNTER_COLON_PICTURE_PATH_STRING ".\\picture_tools\\counter_number\\time_colon.png"//计时器分隔符图片路径
#define DIALOG_SOUND_RECORD_BACKGROUND_PICTURE_PATH_STRING ".\\picture_tools\\sound_record_dialog\\dialog.png"//录音窗口背景路径
#define DIALOG_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_chara\\chara_0"//信息框左侧图片路径的非后缀部分的不变部分
#define DIALOG_CHARA_PICTURE_PATH_BREAK_STRING "_0"//信息框左侧图片路径的下划线部分
#define DIALOG_CHARA_PICTURE_PATH_BACK_STRING ".png"//信息框左侧图片路径的后缀部分
#define DIALOG_INFORMATION_OPEN_MORE_THAN_ONE_PATH_STRING ".\\picture_tools\\open_more_than_one_information\\information_"//多开程序阻止提示信息
#define DIALOG_INFORMATION_CANNOT_START_PROGRAM_PATH_STRING ".\\picture_tools\\cannot_start_program_information\\information_"//无法打开程序提示信息
#define DIALOG_INFORMATION_CANNOT_SHUTDOWN_OR_RESTART_PATH_STRING ".\\picture_tools\\cannot_shutdown_or_restart_information\\information_"//无法关机或者重启提示信息
#define DIALOG_INFORMATION_HELP_PATH_STRING ".\\picture_tools\\help_information\\information_"//程序信息窗口提示信息
#define DIALOG_INFORMATION_WRONG_DEVICE_PATH_STRING ".\\picture_tools\\wrong_device_information\\information_"//查找录音设备失败窗口提示信息
#define DIALOG_INFORMATION_WRONG_SOUND_FILE_SAVE_PATH_STRING ".\\picture_tools\\wrong_sound_save_path_information\\information_"//录音保存文件路径出错窗口提示信息
#define DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING ".\\picture_tools\\wrong_file_or_path_information\\information_"//设置窗口不存在的文件或路径窗口提示信息
#define DIALOG_NOTE_BACKGROUND_PICTURE_FRONT_STRING ".\\picture_tools\\note_background\\background_"//便签背景窗口的非后缀部分的不变部分
#define DIALOG_NOTE_BACKGROUND_PICTURE_BACK_STRING ".png"//便签背景窗口的后缀部分
#define DIALOG_INFORMATION_FILE_PICTURE_PATH_STRING ".\\picture_tools\\filedialog_information\\information_"//文件打开或保存选择提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_FILE_HEAD_PICTURE_PATH_STRING ".\\picture_tools\\filedialog_information\\informationhead_"//文件打开或保存选择提示框头部文字路径的非后缀部分的不变部分
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_tools\\filedialog_background\\background_"//打开或保存文件信息框背景路径的非后缀部分的不变部分
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//打开或保存文件信息框背景路径的后缀部分
#define DIALOG_FILE_MARGIN_PICTURE_PATH_STRING ".\\picture_tools\\filedialog_margin\\margin.png"//文件打开与保存信息框边框图片路径
#define DIALOG_TIME_COUNTER_END_VOICE_FRONT_STRING ".\\sound\\time_counter_end_voice\\voice_"//计时器到期播放声音路径的非后缀部分
#define DIALOG_TIME_COUNTER_END_VOICE_BREAK_STRING "_"//计时器到期播放声音路径的下划线部分
#define DIALOG_TIME_COUNTER_END_VOICE_BACK_STRING ".wav"//计时器到期播放声音路径的后缀部分

#endif