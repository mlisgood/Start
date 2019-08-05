#ifndef DEFINE_H
#define DEFINE_H

//头文件
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QFileInfo>
#include <QByteArray>
#include <QFile>
#include <QPropertyAnimation>
#include <QThread>
#include <QMutex>
#include <QDir>
#include <QFileSystemModel>
#include <QScrollBar>
#include <QFontDatabase>
#include <QSettings>
#include <string>
#include <tchar.h>
#include <fstream>
#include <windows.h>
#include <shellapi.h>
#include <des.h>
#include <aes.h>
#include <md4.h>
#include <md5.h>
#include <sha.h>
#include <sha3.h>
#include <keccak.h>
#include "ExportClassLockSimple.h"
#include "ExportClassLockNormal.h"
#include "ui_Lock.h"
#include "ui_Help.h"
#include "ui_LockSimpleOpposite.h"
#include "ui_LockSimple.h"
#include "ui_LockNormal.h"
#include "ui_LockNormalSingleKey.h"
#include "ui_LockNormalDoubleKey.h"
#include "ui_File.h"
#include "ui_UnlockSimpleOppositeCheck.h"
#include "ui_UnlockSimpleAddCheck.h"
#include "ui_UnlockNormalSingleCheck.h"
#include "ui_UnlockNormalDoubleCheck.h"
#include "ui_LockNormalHashCalculate.h"
#include "ui_Set.h"
#include "ui_LockSimpleAdd.h"
#include "ui_LockSimpleAddGetDigit.h"
#include "ui_UnlockSimpleAddCheckDigit.h"
#include "Lock.h"
#include "Help.h"
#include "LockSimpleOpposite.h"
#include "LockSimple.h"
#include "LockNormal.h"
#include "LockNormalSingleKey.h"
#include "LockNormalDoubleKey.h"
#include "LockNormalHashCalculate.h"
#include "File.h"
#include "UnlockSimpleOppositeCheck.h"
#include "UnlockSimpleAddCheck.h"
#include "UnlockNormalSingleCheck.h"
#include "UnlockNormalDoubleCheck.h"
#include "Set.h"
#include "LockSimpleAdd.h"
#include "LockSimpleAddGetDigit.h"
#include "UnlockSimpleAddCheckDigit.h"

//运行库
#pragma comment(lib,"cryptlib.lib")//导入crypto++运行库

//语言环境
#pragma execution_character_set("utf-8")

//全局常量
#define FILE_FONT_DEFAULT_SIZE 9//默认字体大小
#define FILE_FONT_PATH_STRING ".\\font\\font_df_girl.ttf"//字体文件路径
#define FILE_KEY_WRITE_BINARY_TYPE_1_NUMBER 1//二进制密钥文件加密类型1（简单取反）对应数据
#define FILE_KEY_WRITE_BINARY_TYPE_2_NUMBER 2//二进制密钥文件加密类型2（简单加减）对应数据
#define FILE_KEY_WRITE_BINARY_TYPE_3_NUMBER 3//二进制密钥文件加密类型3（DES）对应数据
#define FILE_KEY_WRITE_BINARY_TYPE_4_NUMBER 4//二进制密钥文件加密类型4（2-key 3DES）对应数据
#define FILE_KEY_WRITE_BINARY_TYPE_5_NUMBER 5//二进制密钥文件加密类型5（3-key 3DES）对应数据
#define FILE_KEY_WRITE_BINARY_TYPE_6_NUMBER 6//二进制密钥文件加密类型6（AES-128）对应数据
#define FILE_KEY_WRITE_BINARY_TYPE_7_NUMBER 7//二进制密钥文件加密类型7（AES-192）对应数据
#define FILE_KEY_WRITE_BINARY_TYPE_8_NUMBER 8//二进制密钥文件加密类型8（AES-256）对应数据
#define FILE_KEY_WRITE_BINARY_TYPE_9_NUMBER 9//二进制密钥文件加密类型9（RSA公钥）对应数据
#define FILE_KEY_WRITE_BINARY_TYPE_10_NUMBER 10//二进制密钥文件加密类型10（RSA私钥）对应数据
#define FILE_KEY_WRITE_BINARY_TYPE_11_NUMBER 11//二进制密钥文件加密类型11（ECC公钥）对应数据
#define FILE_KEY_WRITE_BINARY_TYPE_12_NUMBER 12//二进制密钥文件加密类型12（ECC私钥）对应数据
#define FILE_KEY_AES_MIDDLE_KEY_LENGTH 24//AES-192对应密钥长度
#define FILE_KEYFILE_MAGIC_NUMBER_STRING_SIZE_NUMBER 8//密钥文件头部魔术数字对应十六进制数据所占大小
#define FILE_KEYFILR_INTERVAL_NUMBER_HEX_STRING_SIZE_NUMBER 8//密钥文件分隔符对应十六进制数据所占大小
#define FILE_KEYFILR_INTERVAL_SHORT_NUMBER_HEX_STRING_SIZE_NUMBER 4//密钥文件短分隔符对应十六进制数据所占大小
#define FILE_KEYFILE_HEAD_NUMBER_STRING_SIZE_NUMBER 4//密钥文件包含的头部特征数字对应十六进制数据所占大小
#define FILE_OUTPUT_FILE_LOCK_FRONT_PATH_STRING ".\\target_lock"//默认输出加密文件前半部分不变路径
#define FILE_OUTPUT_FILE_UNLOCK_FRONT_PATH_STRING ".\\target_unlock"//默认输出解密文件前半部分不变路径
#define FILE_OUTPUT_FILE_KEY_BACK_PATH_STRING "key.txt"//输出密钥文件路径后缀
#define FILE_OUTPUT_FILE_KEY_BINARY_BACK_PATH_STRING "keyfile"//默认输出二进制密钥文件路径后缀
#define FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING ".\\history"//默认输出历史信息文件前半部分不变路径
#define FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING "\\history.txt"//输出历史信息文件路径后缀
#define FILE_TEMP_FILE_FRONT_PATH_STRING ".\\tempfile"//默认临时文件路径的前半部分
#define FILE_DLL_FILE_READ_PATH_STRING L"LockSimple.dll"//简单加密读取dll文件位置
#define FILE_DLL_FILE_NORMAL_READ_PATH_STRING L"LockNormal.dll"//常规加密读取dll文件位置
#define FILE_LOCK_DOUBLE_KEY_DEFAULT_NAME_STRING "未命名"//非对称加密密钥文件默认文件名
#define FILE_SET_PATH_STRING ".\\setting_lock\\setting.ini"//设置配置文件路径
#define FILE_SETTING_CATALOG_1_1_INNER_PATH_STRING "/path/lock"//配置文件目录1-1文件内路径
#define FILE_SETTING_CATALOG_1_2_INNER_PATH_STRING "/path/unlock"//配置文件目录1-2文件内路径
#define FILE_SETTING_CATALOG_1_3_INNER_PATH_STRING "/path/temp"//配置文件目录1-3文件内路径
#define FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING "/path/history"//配置文件目录1-4文件内路径
#define FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING "/suffix/lock"//配置文件目录2-1文件内路径
#define FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING "/suffix/unlock"//配置文件目录2-2文件内路径
#define FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING "/suffix/text"//配置文件目录2-3文件内路径
#define FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING "/suffix/binary"//配置文件目录2-4文件内路径
#define FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING "/boolvalue/history"//配置文件目录3-1文件内路径
#define FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING "/boolvalue/textkey"//配置文件目录3-2文件内路径
#define FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING "/boolvalue/binarykey"//配置文件目录3-3文件内路径
#define FILE_SETTING_CATALOG_PATH_DEFAULT_STRING "#default#"//配置文件路径默认值
#define FILE_SETTING_SUFFIX_LOCK_DEFAULT_STRING "lock"//配置文件加密文件后缀默认值
#define FILE_SETTING_SUFFIX_UNLOCK_DEFAULT_STRING "unlock"//配置文件解密文件后缀默认值
#define FILE_SETTING_SUFFIX_INTERVAL_STRING "."//配置文件加密文件后缀分隔符
#define FILE_KEY_FILE_MAGIC_NUMBER_HEX_STRING "57555341FFFF4C46"//二进制密钥文件头部魔术数字对应十六进制数据，具体内容为“WUSAxxLF”（“xx”用十六进制码“FFFF”填充）
#define FILE_PUBLIC_KEY_TYPE_STRING "public"//非对称加密公钥密钥类型名称
#define FILE_PRIVATE_KEY_TYPE_STRING "private"//非对称加密私钥密钥类型名称
#define WINDOW_SIZE_WIDTH_NUMBER 400//窗口宽度
#define WINDOW_SIZE_HEIGHT_NUMBER 400//窗口高度
#define WINDOW_RANDOM_MAX_NUMBER 8//绘制窗口背景用到随机数的最大值
#define WINDOW_RANDOM_MIN_NUMBER 1//绘制窗口背景用到随机数的最小值
#define WINDOW_ANIMATION_TIME_NUMBER 300//启动和关闭动画持续时间
#define WINDOW_ANIMATION_TRANSPRENT_TRANSPRENT_NUMBER 0.4//窗口透明模式透明度
#define WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER 1//窗口常规模式透明度
#define WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER 0//窗口消失透明度
#define WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_lock\\background\\background_"//背景图片路径的非后缀部分的不变部分
#define WINDOW_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//背景图片路径的后缀部分
#define WINDOW_BACKGROUND_MARGIN_PICTURE_PATH_STRING ".\\picture_lock\\background_margin\\margin.png"//边框图片路径
#define DIALOG_SIZE_WIDTH_NUMBER 600//信息框宽度
#define DIALOG_SIZE_HEIGHT_NUMBER 200//信息框高度
#define DIALOG_LOCK_SIZE_WIDTH_NUMBER 400//加密解密窗口宽度
#define DIALOG_LOCK_SIZE_HEIGHT_NUMBER 600//加密解密窗口高度
#define DIALOG_LOCK_BACKGROUND_OFFSET_X_NUMBER 0//加密解密窗口非人物背景图像横坐标偏移
#define DIALOG_LOCK_BACKGROUND_OFFSET_Y_NUMBER 400//加密解密窗口非人物背景图像纵坐标偏移
#define DIALOG_RANDOM_MAX_NUMBER 5//绘制信息框背景用到随机数的最大值
#define DIALOG_RANDOM_MIN_NUMBER 1//绘制信息框背景用到随机数的最小值
#define DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER 8//绘制信息框左侧图片用到随机数的最大值
#define DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER 1//绘制信息框左侧图片用到随机数的最小值
#define DIALOG_LOCK_CHARA_PICTURE_COUNT_INTERVAL_NUMNER 5000//加密解密窗口人物图片轮播间隔
#define DIALOG_LOCK_CHARA_PICTURE_TRANSPARENT_COUNT_INTERVAL_NUMNER 50//加密解密窗口人物图片透明度切换时间间隔
#define DIALOG_LOCK_CHARA_PICTURE_TRANSPARENT_COUNT_MEASURE_NUMNER 0.05//加密解密窗口人物图片透明度切换精度
#define DIALOG_INFORMATION_FILE_WIDTH_NUMBER 600//文件打开或保存信息框总文本信息宽度
#define DIALOG_INFORMATION_FILE_HEIGHT_NUMBER 30//文件打开或保存信息框总文本信息高度
#define DIALOG_INFORMATION_FILE_X_OFFSET_NUMBER 0//文件打开或保存信息框文本信息横向起始位置
#define DIALOG_INFORMATION_FILE_Y_OFFSET_NUMBER 445//文件打开或保存信息框文本信息纵向起始位置
#define DIALOG_INFORMATION_FILE_HEAD_X_OFFSET_NUMBER 0//文件打开或保存信息框头部文本信息横向起始位置
#define DIALOG_INFORMATION_FILE_HEAD_Y_OFFSET_NUMBER 50//文件打开或保存信息框头部文本信息纵向起始位置
#define DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER 1//加密解密窗口人物图片轮播最小序号
#define DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER 8//加密解密窗口人物图片轮播最大序号
#define DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER 8//简单加密文本框允许输入的元素最大数目
#define DIALOG_SIMPLE_LOCK_LINEEDIT_TRANSFORM_LENGTH_NUMBER 4//简单加密文本框转化为16进制数据后占用空间
#define DIALOG_PROGRESSBAR_TIMES_NUMBER 100//加密窗口进度条倍率
#define DIALOG_PROGRESSBAR_MAX_NUMBER 100//加密窗口进度条最大值
#define DIALOG_PROGRESSBAR_CHANGE_FONT_COLOR_NUMBER 50//加密窗口进度条切换字体颜色时的数值
#define DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER 16//加减加密最大循环单元数目
#define DIALOG_LOCK_NORMAL_DOUBLE_DEFAULE_SIZE_NUMBER 1024//RSA加密默认密钥长度
#define DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_CHAR '0'//简单加密文本框元素过少时默认插入的字符
#define DIALOG_LOCK_SIMPLE_DIRECTION_RIGHT_STRING "right"//加密顺序描述字符串：顺序
#define DIALOG_LOCK_SIMPLE_DIRECTION_LEFT_STRING "left"//加密顺序描述字符串：倒序
#define DIALOG_LOCK_SIMPLE_DIRECTION_RIGHT_AND_LEFT_STRING "right and left"//加密顺序描述字符串：双向
#define DIALOG_LOCK_SIMPLE_DIRECTION_NO_HEAD_DIGIT_STRING "null"//无头部特征数字提示
#define DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING ".png"//信息框提示内容文字路径的后缀部分
#define DIALOG_INFORMATION_HELP_PATH_STRING ".\\picture_lock\\help_information\\information_"//信息框提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_LOCK_FAIL_PATH_STRING ".\\picture_lock\\lock_fail_information\\information_"//取反加密失败提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_UNLOCK_FAIL_PATH_STRING ".\\picture_lock\\unlock_fail_information\\information_"//取反解密失败提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_KEYFILE_CANNOT_OPEN_PATH_STRING ".\\picture_lock\\keyfile_cannot_open_information\\information_"//无法打开密钥文件提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_OPEN_WRONG_KEYFILE_PATH_STRING ".\\picture_lock\\open_wrong_keyfile_information\\information_"//打开错误的密钥文件提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_CANNOT_OPEN_PATH_STRING ".\\picture_lock\\cannot_open_path_information\\information_"//设置界面打开错误提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_DELETE_FAIL_PATH_STRING ".\\picture_lock\\delete_fail_information\\information_"//设置界面删除失败提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_WRONG_KEY_PATH_STRING ".\\picture_lock\\wrong_key_information\\information_"//常规加密密钥过短提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_WRONG_LENGTH_KEY_PATH_STRING ".\\picture_lock\\wrong_length_key_information\\information_"//常规加密密钥长度不正确提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_CANNOT_SAVE_STRING ".\\picture_lock\\cannot_save_information\\information_"//常规加密无法保存提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_WRONG_KEY_STRING ".\\picture_lock\\lock_normal_wrong_key_information\\information_"//常规加密密钥错误提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_OUT_OF_RANGE_STRING ".\\picture_lock\\lock_normal_out_of_range_information\\information_"//常规加密密钥过短或原文超出范围提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_UNLOCK_OUT_OF_RANGE_STRING ".\\picture_lock\\unlock_normal_out_of_range_information\\information_"//常规加密解密密文长度不正确提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_HASH_CHECK_CORRECT_STRING ".\\picture_lock\\hash_check_correct\\information_"//常规加密校验成功提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_HASH_CHECK_INCORRECT_STRING ".\\picture_lock\\hash_check_incorrect\\information_"//常规加密校验失败提示内容文字路径的非后缀不变部分
#define DIALOG_INFORMATION_HASH_CHECK_WRONG_HASH_STRING ".\\picture_lock\\hash_check_wrong_hash\\information_"//常规加密校验信息不正确提示内容文字路径的非后缀不变部分
#define DIALOG_MARGIN_PICTURE_PATH_STRING ".\\picture_start\\warning_margin\\margin.png"//信息框边框图片路径
#define DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_background\\background_"//信息框背景路径的非后缀部分的不变部分
#define DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//信息框背景路径的后缀部分
#define DIALOG_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_chara\\chara_0"//信息框左侧图片路径的非后缀部分的不变部分
#define DIALOG_CHARA_PICTURE_PATH_BREAK_STRING "_0"//信息框左侧图片路径的下划线部分
#define DIALOG_CHARA_PICTURE_PATH_BACK_STRING ".png"//信息框左侧图片路径的后缀部分
#define DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_lock\\background\\background_real_"//加密窗口可切换人物背景图片路径的非后缀部分的不变部分
#define DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING ".png"//加密窗口可切换人物背景图片路径的后缀部分
#define DIALOG_BACKGROUND_CHARA_TRANSPARENT_PICTURE_PATH_STRING ".\\picture_lock\\background\\transparent.png"//加密窗口可切换人物背景图片全透明图片路径
#define DIALOG_LOCK_MARGIN_PICTURE_PATH_STRING ".\\picture_lock\\lock_margin\\margin.png"//加密窗口边框图片路径
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_lock\\filedialog_background\\background_"//打开或保存文件信息框背景路径的非后缀部分的不变部分
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//打开或保存文件信息框背景路径的后缀部分
#define DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING ".\\picture_lock\\wrong_file_or_path_information\\information_"//设置窗口不存在的文件或路径窗口提示信息
#define DIALOG_INFORMATION_FILE_PICTURE_PATH_STRING ".\\picture_lock\\filedialog_information\\information_"//文件打开或保存选择提示框文字路径的非后缀部分的不变部分
#define DIALOG_INFORMATION_FILE_HEAD_PICTURE_PATH_STRING ".\\picture_lock\\filedialog_information\\informationhead_"//文件打开或保存选择提示框头部文字路径的非后缀部分的不变部分
#define DIALOG_FILE_MARGIN_PICTURE_PATH_STRING ".\\picture_lock\\filedialog_margin\\margin.png"//文件打开与保存信息框边框图片路径
#define DIALOG_INFORATION_FILE_KEYFILE_FILTER_STRING "*.keyfile"//打开或保存密钥文件信息框过滤器内容
#define DIALOG_BACKGROUND_UNLOCK_SIMPLE_OPPOSITE_CHECK_PATH_STRING ".\\picture_lock\\unlock_is_use_binary_key_file_dialog\\dialog.png"//简单解密确认框背景路径
#define DIALOG_BACKGROUND_UNLOCK_NORMAL_SINGLE_CHECK_PATH_STRING ".\\picture_lock\\unlock_normal_single_is_use_binary_key_file_dialog\\dialog.png"//常规对称加密解密确认框背景路径
#define DIALOG_BACKGROUND_UNLOCK_NORMAL_DOUBLE_CHECK_PATH_STRING ".\\picture_lock\\unlock_normal_double_is_use_binary_key_file_dialog\\dialog.png"//常规非对称加密解密确认框背景路径
#define DIALOG_BACKGROUND_LOCK_SIMPLE_ADD_GET_DIGIT_PATH_STRING ".\\picture_lock\\lock_get_digit_set_dialog\\dialog.png"//加密获取加减数量界面背景路径
#define DIALOG_BACKGROUND_UNLOCK_SIMPLE_ADD_SET_DIGIT_PATH_STRING ".\\picture_lock\\unlock_simple_add_digit_dialog\\dialog.png"//解密加减数量确认框背景路径
#define DIALOG_BACKGROUND_SET_PATH_STRING ".\\picture_lock\\set_dialog\\dialog.png"//设置界面背景路径
#define DIALOG_LOCK_SIMPLE_ADD_DEFAULT_UNIT_INSERT_STRING "0"//加减加密循环单元默认加减数量
#define DIALOG_LOCK_NORMAL_DOUBLE_DEFAULE_CURVE_TYPE_STRING "secp112r1"//ECC加密默认曲线类型
#define DIALOG_HASH_CALCULATOR_TYPE_STRING "224"//散列值计算默认类型
#define DIALOG_LOCK_NORMAL_DES_DESCRIPTION_STRING "DES即数据加密标准，在1976年被美国联邦政府的国家标准局确定为联邦资料处理标准，是一种使用56位密钥的对称算法，剩余8位用于奇偶校验。由于其使用的密钥过短，现在已经不是一种安全的加密方法。在2001年，DES作为一个标准已经被高级加密标准(AES)所取代。另外，DES已经不再作为国家标准科技协会即前国家标准局的一个标准。"//常规加密关于DES加密的描述
#define DIALOG_LOCK_NORMAL_DES_EDE2_DESCRIPTION_STRING "3DES是一种对称算法，相当于是对每个数据块应用三次数据加密标准(DES)算法。为应对原版DES密码的密钥长度过短变得容易被暴力破解的问题，3DES提供了一种相对简单的方法，即通过增加DES的密钥长度来避免类似的攻击。此算法使用112位密钥，安全性较简单的应用DES两次的强度高，可以防御中途相遇攻击。"//常规加密关于DES-EDE2加密的描述
#define DIALOG_LOCK_NORMAL_DES_EDE3_DESCRIPTION_STRING "3DES是一种对称算法，相当于是对每个数据块应用三次数据加密标准(DES)算法。为应对原版DES密码的密钥长度过短变得容易被暴力破解的问题，3DES提供了一种相对简单的方法，即通过增加DES的密钥长度来避免类似的攻击。此算法使用168位密钥，与2-Key 3DES相比，安全性更高。"//常规加密关于DES-EDE3加密的描述
#define DIALOG_LOCK_NORMAL_AES_MIN_DESCRIPTION_STRING "AES即高级加密标准，又称Rijndael加密法，是美国联邦政府采用的一种区块加密标准。这个标准用来替代原先的DES，已经被多方分析且广为全世界所使用。2006年，高级加密标准已成为对称密钥加密中最流行的算法之一。此算法使用128位密钥。"//常规加密关于AES_MIN加密的描述
#define DIALOG_LOCK_NORMAL_AES_MIDDLE_DESCRIPTION_STRING "AES即高级加密标准，又称Rijndael加密法，是美国联邦政府采用的一种区块加密标准。这个标准用来替代原先的DES，已经被多方分析且广为全世界所使用。2006年，高级加密标准已成为对称密钥加密中最流行的算法之一。此算法使用192位密钥。"//常规加密关于AES_MIDDLE加密的描述
#define DIALOG_LOCK_NORMAL_AES_MAX_DESCRIPTION_STRING "AES即高级加密标准，又称Rijndael加密法，是美国联邦政府采用的一种区块加密标准。这个标准用来替代原先的DES，已经被多方分析且广为全世界所使用。2006年，高级加密标准已成为对称密钥加密中最流行的算法之一。此算法使用256位密钥。"//常规加密关于AES_MAX加密的描述
#define DIALOG_LOCK_NORMAL_RSA_DESCRIPTION_STRING "RSA是1977年由Ron Rivest、Adi Shamir和Leonard Adleman一起提出的一种非对称加密算法。该算法的可靠性建立于对极大整数做因数分解的困难性上。到当前为止，世界上还没有任何可靠的攻击RSA算法的方式。"//常规加密关于RSA加密的描述
#define DIALOG_LOCK_NORMAL_ECC_DESCRIPTION_STRING "ECC即椭圆曲线密码学，是一种基于椭圆曲线数学的公开密钥加密算法。椭圆曲线在密码学中的使用是在1985年由Neal Koblitz和Victor Miller分别独立提出的。其安全性依赖于椭圆曲线离散对数问题的困难性上。在某些情况下，它比其他如RSA一类的方法使用更小的密钥，并提供相当的或更高等级的安全性。"//常规加密关于ECC加密的描述
#define DIALOG_LOCK_NORMAL_MD4_DESCRIPTION_STRING "MD4是麻省理工学院教授Ronald Rivest于1990年设计的一种信息摘要算法。它是一种用来测试信息完整性的密码散列函数的实现，其摘要长度为128位。这个算法影响了后来的算法如MD5、SHA家族等。目前MD4已被淘汰。"//常规加密关于MD4的描述
#define DIALOG_LOCK_NORMAL_MD5_DESCRIPTION_STRING "MD5由美国密码学家Ronald Linn Rivest设计，于1992年公开，用以取代MD4算法。该算法可以产生出一个128位的散列值，用于确保信息传输完整一致。2004年，MD5被证实无法防止碰撞，因此不适用于安全性认证，如SSL公开密钥认证或是数字签名等用途。当前，MD5算法因其普遍、稳定、快速的特点，仍广泛应用于普通数据的错误检查领域。"//常规加密关于MD5的描述
#define DIALOG_LOCK_NORMAL_SHA1_DESCRIPTION_STRING "SHA-1即安全散列算法1，是一种密码散列函数，美国国家安全局设计，并由美国国家标准技术研究所(NIST)发布为联邦数据处理标准(FIPS)。SHA-1可以生成一个被称为消息摘要的160位散列值。2005年，密码分析人员发现了对SHA-1的有效攻击方法，这表明该算法可能不够安全，不能继续使用。目前，SHA-1已经不再视为可抵御有充足资金、充足计算资源的攻击者。"//常规加密关于SHA1的描述
#define DIALOG_LOCK_NORMAL_SHA2_DESCRIPTION_STRING "SHA-2即安全散列算法2，是一种由美国国家安全局研发的密码散列函数算法标准。其由美国国家标准技术研究所(NIST)在2001年发布。属于SHA算法之一，是SHA-1的后继者。"//常规加密关于SHA2的描述
#define DIALOG_LOCK_NORMAL_SHA3_DESCRIPTION_STRING "SHA-3即安全散列算法3，之前名为Keccak算法。该算法在2015年8月5日由美国国家标准技术研究所(NIST)通过FIPS 202正式发表。SHA-3并非用于取代SHA-2，因为SHA-2当前并没有出现明显的弱点。由于对MD5、SHA-0和SHA-1出现成功的破解，NIST认为需要一个与之前算法不同的，可替换的加密散列算法，也就是现在的SHA-3。在2015年8月SHA3最终完成标准化时，NIST调整了填充算法，标准的SHA3和原先的Keccak就有所区别了。因为现在还有一些地方将这两种算法混用，因此使用时需要特别注意。"//常规加密关于SHA3的描述
#define DIALOG_LOCK_NORMAL_KECCAK_DESCRIPTION_STRING "Keccak是SHA-3的前身。在2015年8月SHA3最终完成标准化时，NIST调整了填充算法，标准的SHA3和原先的Keccak就有所区别了。因为现在还有一些地方将这两种算法混用，因此使用时需要特别注意。"//常规加密关于Keccak的描述


#endif