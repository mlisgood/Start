#ifndef DEFINE_H
#define DEFINE_H

//指定头文件
#include <QtWidgets/QMainWindow>
#include <QtCore>
#include <QSplashScreen>
#include <QMouseEvent>
#include <QMainWindow>
#include <QPoint>
#include <QWidget>
#include <QString>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QFontDatabase>
#include <QScreen>
#include <QFileSystemModel>
#include <QScrollBar>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QUrl>
#include <QDrag>
#include <QPrinter>
#include <QPrinterInfo>
#include <QMutex>
#include <QThread>
#include <QTextCursor>
#include <qmovie.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include "ui_Notepad.h"
#include "ui_Help.h"
#include "ui_Save.h"
#include "ui_Find.h"
#include "ui_Replace.h"
#include "ui_Font.h"
#include "ui_Color.h"
#include "ui_File.h"
#include "ui_Code.h"
#include "ui_Print.h"
#include "ui_Setting.h"
#include "Notepad.h"
#include "Help.h"
#include "Save.h"
#include "Find.h"
#include "Replace.h"
#include "Font.h"
#include "Color.h"
#include "File.h"
#include "Code.h"
#include "Print.h"
#include "Setting.h"
#include "main.h"

//指定语言环境
#pragma execution_character_set("utf-8")

//全局常量
#define FILE_FONT_DEFAULT_SIZE 9//默认字体大小
#define FILE_FONT_PATH_STRING ".\\font\\font_df_girl.ttf"//字体文件路径
#define REG_MENU_1 "HKEY_CLASSES_ROOT\\*\\shell\\Cup Of Notepad\\command"//程序右键菜单注册表项路径1
#define REG_MENU_2 "HKEY_CLASSES_ROOT\\*\\shell\\Cup Of Notepad"//程序右键菜单注册表项路径2
#define REG_MENU_NAME_PATH_STRING "Cup Of Notepad"//供注册表使用的右键菜单项的名称
#define REG_MENU_ICON_PATH_STRING "\\picture_notepad\\icon\\icon_menu.ico"//供注册表使用的右键菜单项的图标文件位置
#define FILE_BIT_TO_KBIT 1024//B转化为KB的倍率
#define FILE_DLL_FILE_READ_PATH_STRING L"FileReadAndWrite.dll"//文件读取dll文件位置
#define FILE_SETTING_TEXT_AND_BINARY_END_WRITE_STRING "#end#"//其他设置窗口写入文件后缀时结束所使用的字符串标识
#define FILE_FONT_OUTPUT_FILE_PATH_FRONT_STRING ".\\setting_notepad\\font_setting_"//字体输出配置文件非后缀不变部分
#define FILE_FONT_OUTPUT_FILE_PATH_BINARY_EXTRA_STRING "_b"//字体输出配置文件二进制模式非后缀附加部分
#define FILE_FONT_OUTPUT_FILE_PATH_BACK_STRING ".txt"//字体输出配置文件后缀
#define FILE_COLOR_OUTPUT_FILE_PATH_FRONT_STRING ".\\setting_notepad\\color_save_"//颜色输出配置文件前缀不变部分
#define FILE_COLOR_OUTPUT_FILE_PATH_BACK_STRING ".txt"//颜色输出配置文件后缀
#define FILE_CODE_OUTPUT_FILE_PATH_STRING ".\\setting_notepad\\text_code.txt"//编码输出配置文件路径
#define FILE_SETTING_TEXT_OUTPUT_FILE_PATH_STRING ".\\setting_notepad\\setting_text.txt"//其他设置输出配置文件1路径
#define FILE_SETTING_BINARY_OUTPUT_FILE_PATH_STRING ".\\setting_notepad\\setting_binary.txt"//其他设置输出配置文件2路径
#define FILE_SETTING_OTHER_PATH_STRING ".\\setting_notepad\\setting_other.ini"//其他设置配置文件
#define FILE_SETTING_CATALOG_1_INNER_PATH_STRING "/defaultopenmethod/type"//其他设置配置文件目录1文件内路径
#define FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING "/size/text"//其他设置配置文件目录2-1文件内路径
#define FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING "/size/binary"//其他设置配置文件目录2-2文件内路径
#define FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING "/boolvalue/changeline"//其他设置配置文件目录3_1文件内路径
#define FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING "/boolvalue/menu"//其他设置配置文件目录3_2文件内路径
#define FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING "/boolvalue/addblank"//其他设置配置文件目录3_3文件内路径
#define WINDOW_THREAD_WAIT_TIME_NUMBER 1//子线程每运行一次后休眠的时间
#define WINDOW_SIZE_WIDTH_NUMBER 1000//窗口宽度
#define WINDOW_SIZE_HEIGHT_NUMBER 600//窗口高度
#define WINDOW_ANIMATION_TIME_NUMBER 300//启动和关闭动画持续时间
#define WINDOW_ANIMATION_TRANSPRENT_TRANSPRENT_NUMBER 0.4//窗口透明模式透明度
#define WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER 1//窗口常规模式透明度
#define WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER 0//窗口消失透明度
#define WINDOW_SIZE_PICTURE_CHARA_WIDTH_NUMBER 421//人物形象宽度
#define WINDOW_SIZE_PICTURE_CHARA_HEIGHT_NUMBER 600//人物形象高度
#define WINDOW_TEXTEDIT_X_OFFSET_NUMBER 470//文本框横向偏移。这里文本框的设置比文本框实际的大小要大，这是为了保证背景图片的显示效果。
#define WINDOW_TEXTEDIT_Y_OFFSET_NUMBER 90//文本框纵向偏移
#define WINDOW_TEXTEDIT_SIZE_WIDTH_NUMBER 480//文本框宽度
#define WINDOW_TEXTEDIT_SIZE_HEIGHT_NUMBER 450//文本框高度
#define WINDOW_RANDOM_MAX_NUMBER 25//绘制窗口背景用到随机数的最大值。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define WINDOW_RANDOM_MIN_NUMBER 1//绘制窗口背景用到随机数的最小值。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define WINDOW_RANDOM_TIMER_CHARA_NORMAL_MAX_NUMBER 9000//背景人物常规状态下计时器间隔
#define WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER 5000//背景人物常规状态下计时器间隔
#define WINDOW_RANDOM_TIMER_CHARA_SPECIAL_NUMBER 60//背景人物特殊状态下计时器间隔
#define WINDOW_SIZE_MARGIN_PICTURE_LEFT_WIDTH_NUMBER 425//窗口边界左边部分宽度
#define WINDOW_SIZE_MARGIN_PICTURE_LEFT_HEIGHT_NUMBER 600//窗口边界左边部分高度
#define WINDOW_SIZE_MARGIN_PICTURE_RIGHT_WIDTH_NUMBER 575//窗口边界右边部分宽度
#define WINDOW_SIZE_MARGIN_PICTURE_RIGHT_HEIGHT_NUMBER 600//窗口边界右边部分高度
#define WINDOW_BUTTON_CLOSE_WINDOW_WIDTH_NUMBER 25//窗口关闭按钮宽度
#define WINDOW_BUTTON_CLOSE_WINDOW_HEIGHT_NUMBER 25//窗口关闭按钮高度
#define WINDOW_PROGRESSBAR_MAX_VALUE_NUMBER 100//主窗口进度条最大值
#define WINDOW_DIALOG_TITLE_PATH_STRING " - 一緒にモフモフしよー"//窗口标题后缀
#define WINDOW_SPLASH_PICTURE_PATH_FRONT_STRING ".\\picture_notepad\\splash\\splash.png"//启动界面图片路径
#define WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_start\\background\\background_"//背景图片路径的非后缀部分的不变部分
#define WINDOW_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//背景图片路径的后缀部分
#define WINDOW_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_start\\background_chara\\chara_"//人物图片的非后缀部分的不变部分。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define WINDOW_CHARA_PICTURE_PATH_BACK_STRING ".png"//人物图片路径的后缀部分，这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define WINDOW_CHARA_PICTURE_PATH_BREAK_STRING "_"//人物图片路径的下划线部分。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define WINDOW_MARGIN_PICTURE_LEFT_PATH_STRING ".\\picture_start\\background_margin\\margin_left.png"//边框图片左边部分路径
#define WINDOW_MARGIN_PICTURE_RIGHT_PATH_STRING ".\\picture_notepad\\background_margin\\margin_right.png"//边框图片右边部分路径
#define WINDOW_BUTTON_CLOSE_WINDOW_PATH_STRING ".\\picture_start\\icon\\window_close.png"//窗口关闭按钮路径
#define WINDOW_BUTTON_HIDE_WINDOW_PATH_STRING ".\\picture_start\\icon\\window_hide.png"//窗口最小化按钮路径
#define WINDOW_TEXTEDIT_BACKGROUND_PICTURE_PATH_STRING ".\\picture_notepad\\background_text\\background_text_0"//文本框背景文字路径的非后缀部分的不变部分
#define WINDOW_TEXTEDIT_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//文本框背景路径的后缀部分
#define WINDOW_CHARA_NORMAL_FLAG 1//背景人物常规状态下标志。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define WINDOW_CHARA_SPECIAL_FLAG 0//背景人物特殊状态下标志。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define WINDOW_TOOL_TOHEX_STATUS_YES_FLAG 0//表示当前文字是十六进制
#define WINDOW_TOOL_TOHEX_STATUS_NO_FLAG 1//表示当前文字是文本字符
#define DIALOG_SIZE_WIDTH_NUMBER 600//信息框宽度
#define DIALOG_SIZE_HEIGHT_NUMBER 200//信息框高度
#define DIALOG_FONT_SIZE_WIDTH_NUMBER 600//字体信息框宽度
#define DIALOG_FONT_SIZE_HEIGHT_NUMBER 400//字体信息框高度
#define DIALOG_COLOR_SIZE_WIDTH_NUMBER 600//色彩信息框宽度
#define DIALOG_COLOR_SIZE_HEIGHT_NUMBER 400//色彩信息框高度
#define DIALOG_SETTING_MAX_TEXT_SIZE_NUMBER 1024//其他设置窗口最大允许一次以文本方式处理文件的数据块大小
#define DIALOG_SETTING_MIN_TEXT_SIZE_NUMBER 64//其他设置窗口最小允许一次以文本方式处理文件的数据块大小
#define DIALOG_SETTING_MAX_BINARY_SIZE_NUMBER 32//其他设置窗口最大允许一次以二进制方式处理文件的数据块大小
#define DIALOG_SETTING_MIN_BINARY_SIZE_NUMBER 4//其他设置窗口最小允许一次以二进制方式处理文件的数据块大小
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_MARGIN_1_NUMBER 540//色彩信息框右侧渐变指定直线参数1
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_MARGIN_2_NUMBER 81//色彩信息框右侧渐变指定直线参数2
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_MARGIN_3_NUMBER 540//色彩信息框右侧渐变指定直线参数3
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_MARGIN_4_NUMBER 229//色彩信息框右侧渐变指定直线参数4
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_RECT_1_NUMBER 521//色彩信息框右侧渐变指定形状参数1
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_RECT_2_NUMBER 81//色彩信息框右侧渐变指定形状参数2
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_RECT_3_NUMBER 38//色彩信息框右侧渐变指定形状参数3
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_RECT_4_NUMBER 148//色彩信息框右侧渐变指定形状参数4
#define DIALOG_COLOR_SLIDER_X_BEGIN_NUMBER 540//色彩信息框右侧渐变条取色横向位置
#define DIALOG_COLOR_SLIDER_Y_BEGIN_NUMBER 82//色彩信息框右侧渐变条取色纵向起始位置
#define DIALOG_RANDOM_MAX_NUMBER 5//绘制信息框背景用到随机数的最大值。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define DIALOG_RANDOM_MIN_NUMBER 1//绘制信息框背景用到随机数的最小值。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER 8//绘制信息框左侧图片用到随机数的最大值。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER 1//绘制信息框左侧图片用到随机数的最小值。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define DIALOG_INFORMATION_CANNOT_SAVE_NORMAL_RETURN_NUMBER 0//无法存储提示框默认值
#define DIALOG_INFORMATION_CANNOT_SAVE_SAVE_RETURN_NUMBER 1//无法存储提示框Save选项返回值
#define DIALOG_INFORMATION_CANNOT_SAVE_DISCARD_RETURN_NUMBER 2//无法存储提示框Discard选项返回值
#define DIALOG_INFORMATION_FIND_WIDTH_NUMBER 400//查找框文本信息宽度
#define DIALOG_INFORMATION_FIND_HEIGHT_NUMBER 100//查找框文本信息高度
#define DIALOG_INFORMATION_FIND_X_OFFSET_NUMBER 200//查找框文本信息横向起始位置
#define DIALOG_INFORMATION_FIND_Y_OFFSET_NUMBER 50//查找框文本信息纵向起始位置
#define DIALOG_INFORMATION_FILE_WIDTH_NUMBER 600//文件打开或保存信息框总文本信息宽度
#define DIALOG_INFORMATION_FILE_HEIGHT_NUMBER 30//文件打开或保存信息框总文本信息高度
#define DIALOG_INFORMATION_FILE_X_OFFSET_NUMBER 0//文件打开或保存信息框文本信息横向起始位置
#define DIALOG_INFORMATION_FILE_Y_OFFSET_NUMBER 445//文件打开或保存信息框文本信息纵向起始位置
#define DIALOG_INFORMATION_FILE_HEAD_X_OFFSET_NUMBER 0//文件打开或保存信息框头部文本信息横向起始位置
#define DIALOG_INFORMATION_FILE_HEAD_Y_OFFSET_NUMBER 50//文件打开或保存信息框头部文本信息纵向起始位置
#define DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_background\\background_"//信息框背景路径的非后缀部分的不变部分
#define DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//信息框背景路径的后缀部分
#define DIALOG_FONT_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_notepad\\font_background\\background_"//字体信息框背景路径的非后缀部分的不变部分
#define DIALOG_FONT_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//字体信息框背景路径的后缀部分
#define DIALOG_COLOR_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_notepad\\font_background\\background_"//色彩信息框背景路径的非后缀部分的不变部分
#define DIALOG_COLOR_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//色彩信息框背景路径的后缀部分
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_notepad\\filedialog_background\\background_"//打开或保存文件信息框背景路径的非后缀部分的不变部分
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//打开或保存文件信息框背景路径的后缀部分
#define DIALOG_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_chara\\chara_0"//信息框左侧图片路径的非后缀部分的不变部分。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define DIALOG_CHARA_PICTURE_PATH_BREAK_STRING "_0"//信息框左侧图片路径的下划线部分。这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define DIALOG_CHARA_PICTURE_PATH_BACK_STRING ".png"//信息框左侧图片路径的后缀部分，这个地方关联到的功能使用了常量，如要修改最好重写相关功能
#define DIALOG_MARGIN_PICTURE_PATH_STRING ".\\picture_start\\warning_margin\\margin.png"//信息框边框图片路径
#define DIALOG_FONT_MARGIN_PICTURE_PATH_STRING ".\\picture_notepad\\font_margin\\margin.png"//字体信息框边框图片路径
#define DIALOG_COLOR_MARGIN_PICTURE_PATH_STRING ".\\picture_notepad\\font_margin\\margin.png"//色彩信息框边框图片路径
#define DIALOG_FILE_MARGIN_PICTURE_PATH_STRING ".\\picture_notepad\\filedialog_margin\\margin.png"//文件打开与保存信息框边框图片路径
#define DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_STRING ".\\style\\font_dialog\\font_"//字体样式文件的非后缀部分的不变部分
#define DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_BACK_STRING ".qss"//字体样式文件的后缀部分
#define DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING ".png"//信息框提示内容文字路径的后缀部分
#define DIALOG_INFORMATION_HELP_PICTURE_PATH_STRING ".\\picture_notepad\\help_information\\information_"//帮助框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_CANNOT_READ_PICTURE_PATH_STRING ".\\picture_notepad\\cannot_read_information\\information_"//无法读取提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_CANNOT_WRITE_PICTURE_PATH_STRING ".\\picture_notepad\\cannot_write_information\\information_"//无法写入提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_CANNOT_SAVE_PICTURE_PATH_STRING ".\\picture_notepad\\cannot_save_information\\information_"//无法存储提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_CANNOT_FIND_PICTURE_PATH_STRING ".\\picture_notepad\\cannot_find_information\\information_"//查找失败提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_FIND_PICTURE_PATH_STRING ".\\picture_notepad\\find_information\\information_"//查找框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_REPLACE_PICTURE_PATH_STRING ".\\picture_notepad\\replace_information\\information_"//替换框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_REPLACE_ALL_PICTURE_PATH_STRING ".\\picture_notepad\\replace_all_information\\information_"//替换框全部替换文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_TEXT_FILE_TOO_LARGE_SAVE_PICTURE_PATH_STRING ".\\picture_notepad\\file_too_large_save_information\\information_"//文本文件过大不能保存提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_TEXT_FILE_TOO_LARGE_LOAD_PICTURE_PATH_STRING ".\\picture_notepad\\file_too_large_load_information\\information_"//文本文件过大不能读取提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_BINARY_FILE_TOO_LARGE_LOAD_PICTURE_PATH_STRING ".\\picture_notepad\\file_binary_too_large_load_information\\information_"//二进制文件过大不能读取提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_BINARY_FILE_TOO_LARGE_SAVE_PICTURE_PATH_STRING ".\\picture_notepad\\file_binary_too_large_save_information\\information_"//二进制文件过大不能保存提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_FONT_PICTURE_PATH_STRING ".\\picture_notepad\\font_information\\information_"//字体选择提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_COLOR_PICTURE_PATH_STRING ".\\picture_notepad\\color_information\\information_"//色彩选择提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_COLOR_CANNOT_ADD_PICTURE_PATH_STRING ".\\picture_notepad\\color_add_fail_information\\information_"//无法添加自定义颜色提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_FILE_PICTURE_PATH_STRING ".\\picture_notepad\\filedialog_information\\information_"//文件打开或保存选择提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_FILE_HEAD_PICTURE_PATH_STRING ".\\picture_notepad\\filedialog_information\\informationhead_"//文件打开或保存选择提示框头部文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_CODE_PICTURE_PATH_STRING ".\\picture_notepad\\code_information\\information_"//编码修改框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_PRINT_PICTURE_PATH_STRING ".\\picture_notepad\\print_information\\information_"//打印框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_SETTING_PICTURE_PATH_STRING ".\\picture_notepad\\setting_information\\information_"//其他设置框文字路径的非后缀部分的不变部分

#endif
