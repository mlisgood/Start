#ifndef LOCKSIMPLE_H
#define LOCKSIMPLE_H

//头文件
#include <QtCore/qglobal.h>
#include <QtWidgets/QMainWindow>
#include <QString>
#include <QDateTime>
#include <string>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include "ExportClassLockSimple.h"

//宏定义
#define FILE_ONCE_MAX_SIZE_NUMBER 1048576//程序一次处理块大小。这里的值就是1024*1024
#define FILE_HEAD_NUMBER_SIZE_NUMBER 4//特征数字占用字节数
#define FILE_HEAD_RAW_NUMBER_SIZE_NUMBER 8//特征数字转换为原始数据后占用字节数
#define FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER 1900//历史文件写入内容1从1970年起始的时间会成为1900年起始的时间，也就是年份要加上1900
#define FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER 1//历史文件写入内容1月份取值范围修正
#define FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER 3//双方向加密使用的用于进度条计算的文件大小的倍率
#define FILE_LOCK_TAIL_SIZE_TIME_NUMBER 2//反方向加密使用的用于进度条计算的文件大小的倍率
#define FILE_KEY_WRITE_BINARY_TYPE_1_NUMBER 1//二进制密钥文件加密类型1（简单取反）对应数据
#define FILE_KEY_WRITE_BINARY_TYPE_2_NUMBER 2//二进制密钥文件加密类型2（简单加减）对应数据
#define FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER 1//二进制密钥文件头部特征数字的标记1（有特征数字）对应数据
#define FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER 0//二进制密钥文件头部特征数字的标记0（无特征数字）对应数据
#define FILE_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER 16//加减加密最大循环单元数目
#define FILE_FILE_INTERVAL_STRING "\\"//文件路径分隔符
#define FILE_TEMP_FILE_TIME_FORMAT_STRING "yyyy-MM-dd hh-mm-ss-zzz"//临时文件时间格式
#define FILE_TEMP_FILE_BACK_PATH_STRING "temp.locktemp"//倒序加密文件时使用的临时文件路径的后半部分
#define FILE_TEMP_DOUBLE_FILE_BACK_PATH_STRING "tempdouble.locktemp"//倒序和双向加密文件时使用的临时文件路径的后半部分
#define FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING "\n"//历史文件写入内容换行符
#define FILE_HISTORY_WRITE_INFORMATION_1_STRING "time:"//历史文件写入内容1
#define FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING "-"//历史文件写入内容1时间分隔符1
#define FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING " "//历史文件写入内容1时间分隔符2
#define FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING ":"//历史文件写入内容1时间分隔符3
#define FILE_HISTORY_WRITE_INFORMATION_2_STRING "name:"//历史文件写入内容2
#define FILE_HISTORY_WRITE_INFORMATION_3_STRING "path:"//历史文件写入内容3
#define FILE_HISTORY_WRITE_INFORMATION_4_1_STRING "operation:"//历史文件写入内容4-1
#define FILE_HISTORY_WRITE_INFORMATION_4_2_STRING "lock"//历史文件写入内容4-2
#define FILE_HISTORY_WRITE_INFORMATION_4_3_STRING "unlock"//历史文件写入内容4-3
#define FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING "\n"//密钥文件写入内容换行符
#define FILE_KEY_WRITE_INFORMATION_1_STRING "一緒にモフモフしよー Text Type Key File"//密钥文件写入内容1
#define FILE_KEY_WRITE_INFORMATION_2_STRING "filename:"//密钥文件写入内容2
#define FILE_KEY_WRITE_INFORMATION_3_STRING "filepath:"//密钥文件写入内容3
#define FILE_KEY_WRITE_INFORMATION_4_STRING "type:"//密钥文件写入内容4
#define FILE_KEY_WRITE_INFORMATION_4_1_STRING "simple-opposite"//密钥文件写入内容4-1
#define FILE_KEY_WRITE_INFORMATION_4_2_STRING "simple-add"//密钥文件写入内容4-2
#define FILE_KEY_WRITE_INFORMATION_5_STRING "direction:"//密钥文件写入内容5
#define FILE_KEY_WRITE_INFORMATION_5_1_STRING "right"//密钥文件写入内容5-1
#define FILE_KEY_WRITE_INFORMATION_5_2_STRING "left"//密钥文件写入内容5-2
#define FILE_KEY_WRITE_INFORMATION_5_3_STRING "right and left"//密钥文件写入内容5-3
#define FILE_KEY_WRITE_INFORMATION_6_STRING "ignore-head:"//密钥文件写入内容6
#define FILE_KEY_WRITE_INFORMATION_7_STRING "ignore-tail:"//密钥文件写入内容7
#define FILE_KEY_WRITE_INFORMATION_8_STRING "cycle:"//密钥文件写入内容8
#define FILE_KEY_WRITE_INFORMATION_9_STRING "magic-number:"//密钥文件写入内容9
#define FILE_KEY_WRITE_INFORMATION_9_1_STRING "null"//密钥文件写入内容9-1
#define FILE_KEY_WRITE_INFORMATION_10_STRING "key-number:"//密钥文件写入内容10
#define FILE_KEY_WRITE_INFORMATION_10_1_STRING ";"//密钥文件写入内容10-1
#define FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING "57555341FFFF4C46"//二进制密钥文件头部魔术数字对应十六进制数据，具体内容为“WUSAxxLF”（“xx”用十六进制码“FFFF”填充）
#define FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING "FFFFFFFFFFFFFFFF"//二进制密钥文件分隔符对应十六进制数据
#define FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING "FFFFFFFF"//二进制密钥文件短分隔符对应十六进制数据

namespace rem
{
	//使用标准命名空间
	using std::string;

	//函数
	class LockOpposite :public Export_LockSimple_virtual_class//导出类，使用方法：包含头文件即可使用
	{

		Q_OBJECT

	public:

		virtual void lock_opposite(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, const string &temp_file_path, int direction, long long head_offset, long long tail_offset, long long cycle, bool have_head_digit, char *head_digit);//文件取反加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，临时文件夹路径，加密方向（1代表顺序，2代表倒序，3代表双方向），头部处理起点，尾部处理起点，循环周期，是否有头部特征数字，头部特征数字
		virtual void unlock_opposite(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, const string &temp_file_path, int direction, long long head_offset, long long tail_offset, long long cycle, bool have_head_digit, char *head_digit);//文件取反解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，临时文件夹路径，加密方向（1代表顺序，2代表倒序，3代表双方向），头部处理起点，尾部处理起点，循环周期，是否有头部特征数字，头部特征数字
		virtual void lock_add(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, const string &temp_file_path, int direction, long long head_offset, long long tail_offset, int cycle, bool have_head_digit, char *head_digit, int *unit_digit);//文件取反加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，临时文件夹路径，加密方向（1代表顺序，2代表倒序，3代表双方向），头部处理起点，尾部处理起点，循环周期（注意这里循环周期指的是加减循环单元数目，不再是取反加密的加密间隔，不需要进行加1修正），是否有头部特征数字，头部特征数字，各循环单位加减数量（为包含16个int型的数组）
		virtual void unlock_add(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, const string &temp_file_path, int direction, long long head_offset, long long tail_offset, int cycle, bool have_head_digit, char *head_digit, int *unit_digit);//文件取反加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，临时文件夹路径，加密方向（1代表顺序，2代表倒序，3代表双方向），头部处理起点，尾部处理起点，循环周期（注意这里循环周期指的是加减循环单元数目，不再是取反加密的加密间隔，不需要进行加1修正），是否有头部特征数字，头部特征数字，各循环单位加减数量（为包含16个int型的数组）

	signals:

		void lock_simple_opposite_process(double process_count);//取反加密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void lock_simple_opposite_final(bool is_success);//取反加密处理完信号。处理完毕后返回
		void unlock_simple_opposite_process(double process_count);//取反解密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void unlock_simple_opposite_final(bool is_success);//取反解密处理完信号。处理完毕后返回
		void lock_simple_add_process(double process_count);//加减加密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void lock_simple_add_final(bool is_success);//加减加密处理完信号。处理完毕后返回
		void unlock_simple_add_process(double process_count);//加减解密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void unlock_simple_add_final(bool is_success);//加减解密处理完信号。处理完毕后返回
	};
}
#endif