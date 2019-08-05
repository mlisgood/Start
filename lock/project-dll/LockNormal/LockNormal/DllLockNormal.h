#ifndef LOCKNORMAL_H
#define LOCKNORMAL_H

//头文件
#include <QtCore/qglobal.h>
#include <QtWidgets/QMainWindow>
#include <QString>
#include <QDateTime>
#include <string>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <oids.h>
#include <osrng.h>
#include <hex.h>
#include <randpool.h>
#include <eccrypto.h>
#include <osrng.h>
#include <filters.h>
#include <files.h>
#include <des.h>
#include <aes.h>
#include <rsa.h>
#include <eccrypto.h>
#include <md4.h>
#include <md5.h>
#include <sha.h>
#include <sha3.h>
#include <keccak.h>
#include "ExportClassLockNormal.h"

//宏定义
#define FILE_KEY_SEED_SIZE_NUMBER 1024//生成随机密钥用到的种子数组大小
#define FILE_HEAD_NUMBER_SIZE_NUMBER 4//特征数字占用字节数
#define FILE_HEAD_RAW_NUMBER_SIZE_NUMBER 8//特征数字转换为原始数据后占用字节数
#define FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER 1900//历史文件写入内容1从1970年起始的时间会成为1900年起始的时间，也就是年份要加上1900
#define FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER 1//历史文件写入内容1月份取值范围修正
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
#define FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER 1//二进制密钥文件头部特征数字的标记1（有特征数字）对应数据
#define FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER 0//二进制密钥文件头部特征数字的标记0（无特征数字）对应数据
#define FILE_KEY_RANDOM_HEX_MIN_NUMBER 0//生成密钥最小十六进制代码对应数量
#define FILE_KEY_RANDOM_HEX_MAX_NUMBER 15//生成密钥最大十六进制代码对应数量
#define FILE_LOCK_TAIL_ADD_CHAR '\0'//常规加密尾部补足加密块大小的字符
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
#define FILE_HISTORY_WRITE_INFORMATION_4_4_STRING "set key"//历史文件写入内容4-4
#define FILE_HISTORY_WRITE_INFORMATION_4_5_STRING "hash calculate"//历史文件写入内容4-5
#define FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING "\n"//密钥文件写入内容换行符
#define FILE_KEY_WRITE_INFORMATION_1_STRING "一緒にモフモフしよー Text Type Key File"//密钥文件写入内容1
#define FILE_KEY_WRITE_INFORMATION_1_1_STRING "一緒にモフモフしよー Text Type Key File\nPlease use the public key to encrypt, and use the private key to decrypt. You shouldn't lose the private key."//密钥文件写入内容1-1
#define FILE_KEY_WRITE_INFORMATION_2_STRING "filename:"//密钥文件写入内容2
#define FILE_KEY_WRITE_INFORMATION_3_STRING "filepath:"//密钥文件写入内容3
#define FILE_KEY_WRITE_INFORMATION_4_STRING "type:"//密钥文件写入内容4
#define FILE_KEY_WRITE_INFORMATION_4_1_STRING "normal-DES"//密钥文件写入内容4-1
#define FILE_KEY_WRITE_INFORMATION_4_2_STRING "normal-DES-EDE2"//密钥文件写入内容4-2
#define FILE_KEY_WRITE_INFORMATION_4_3_STRING "normal-DES-EDE3"//密钥文件写入内容4-3
#define FILE_KEY_WRITE_INFORMATION_4_4_STRING "normal-AES-128"//密钥文件写入内容4-4
#define FILE_KEY_WRITE_INFORMATION_4_5_STRING "normal-AES-192"//密钥文件写入内容4-5
#define FILE_KEY_WRITE_INFORMATION_4_6_STRING "normal-AES-256"//密钥文件写入内容4-6
#define FILE_KEY_WRITE_INFORMATION_4_7_STRING "normal-RSA"//密钥文件写入内容4-7
#define FILE_KEY_WRITE_INFORMATION_4_8_STRING "normal-ECC"//密钥文件写入内容4-8
#define FILE_KEY_WRITE_INFORMATION_5_STRING "magic-number:"//密钥文件写入内容5
#define FILE_KEY_WRITE_INFORMATION_5_1_STRING "null"//密钥文件写入内容5-1
#define FILE_KEY_WRITE_INFORMATION_6_STRING "key:"//密钥文件写入内容6
#define FILE_KEY_WRITE_INFORMATION_6_1_STRING "public key:"//密钥文件写入内容6_1
#define FILE_KEY_WRITE_INFORMATION_6_2_STRING "private key:"//密钥文件写入内容6_2
#define FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING "57555341FFFF4C46"//二进制密钥文件头部魔术数字对应十六进制数据，具体内容为“WUSAxxLF”（“xx”用十六进制码“FFFF”填充）
#define FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING "FFFFFFFFFFFFFFFF"//二进制密钥文件分隔符对应十六进制数据
#define FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING "FFFFFFFF"//二进制密钥文件短分隔符对应十六进制数据
#define FILE_KEY_RANDOM_HEX_10_STRING 'A'//生成密钥10对应十六进制进制代码
#define FILE_KEY_RANDOM_HEX_11_STRING 'B'//生成密钥10对应十六进制进制代码
#define FILE_KEY_RANDOM_HEX_12_STRING 'C'//生成密钥10对应十六进制进制代码
#define FILE_KEY_RANDOM_HEX_13_STRING 'D'//生成密钥10对应十六进制进制代码
#define FILE_KEY_RANDOM_HEX_14_STRING 'E'//生成密钥10对应十六进制进制代码
#define FILE_KEY_RANDOM_HEX_15_STRING 'F'//生成密钥10对应十六进制进制代码
#define FILE_KEY_RANDOM_HEX_0_STRING '0'//生成密钥0对应十六进制进制代码
#define FILE_PUBLIC_KEY_FILE_EXTRA_PATH_STRING "-public"//非对称加密公钥文件文件名附加字符串
#define FILE_PRIVATE_KEY_FILE_EXTRA_PATH_STRING "-private"//非对称加密私钥文件文件名附加字符串


//运行库
#pragma comment(lib,"cryptlib.lib")//导入crypto++运行库

namespace rem
{
	//使用标准命名空间
	using std::string;

	//导入crypto++命名空间
	using namespace CryptoPP;

	//函数
	class LockSingle :public Export_LockSingle_virtual_class//导出类，使用方法：包含头文件即可使用
	{
		Q_OBJECT

	public:

		virtual void lock_DES(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully);//DES加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否加密剩下不足一个加密单位的明文（DES需要补足才会进行加密，这样的话解密出来的文件与原来的可能会有偏差）
		virtual void unlock_DES(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully);//DES解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否解密剩下不足一个解密单位的密文（DES需要补足才会进行解密，这样的话解密出来的文件与原来的可能会有偏差）
		virtual void lock_DES_EDE2(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully);//2-Key TripleDES加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否加密剩下不足一个加密单位的明文（DES需要补足才会进行加密，这样的话解密出来的文件与原来的可能会有偏差）
		virtual void unlock_DES_EDE2(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully);//2-Key TripleDES解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否解密剩下不足一个解密单位的密文（DES需要补足才会进行解密，这样的话解密出来的文件与原来的可能会有偏差）
		virtual void lock_DES_EDE3(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully);//3-Key TripleDES加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否加密剩下不足一个加密单位的明文（DES需要补足才会进行加密，这样的话解密出来的文件与原来的可能会有偏差）
		virtual void unlock_DES_EDE3(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully);//3-Key TripleDES解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否解密剩下不足一个解密单位的密文（DES需要补足才会进行解密，这样的话解密出来的文件与原来的可能会有偏差）
		virtual void lock_AES_MIN(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully);//AES-128加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否加密剩下不足一个加密单位的明文（AES需要补足才会进行加密，这样的话解密出来的文件与原来的可能会有偏差）
		virtual void unlock_AES_MIN(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully);//AES-128解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否解密剩下不足一个解密单位的密文（AES需要补足才会进行解密，这样的话解密出来的文件与原来的可能会有偏差）
		virtual void lock_AES_MIDDLE(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully);//AES-192加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否加密剩下不足一个加密单位的明文（AES需要补足才会进行加密，这样的话解密出来的文件与原来的可能会有偏差）
		virtual void unlock_AES_MIDDLE(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully);//AES-192解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否解密剩下不足一个解密单位的密文（AES需要补足才会进行解密，这样的话解密出来的文件与原来的可能会有偏差）
		virtual void lock_AES_MAX(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully);//AES-256加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否加密剩下不足一个加密单位的明文（AES需要补足才会进行加密，这样的话解密出来的文件与原来的可能会有偏差）
		virtual void unlock_AES_MAX(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully);//AES-256解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否解密剩下不足一个解密单位的密文（AES需要补足才会进行解密，这样的话解密出来的文件与原来的可能会有偏差）

		//内部使用的函数
		void set_key_DES(char *key);//生成随机DES密钥，参数为存储密钥的数组
		void set_key_DES_EDE2(char *key);//生成随机DES_EDE2密钥，参数为存储密钥的数组
		void set_key_DES_EDE3(char *key);//生成随机DES_EDE3密钥，参数为存储密钥的数组
		void set_key_AES_MIN(char *key);//生成随机AES_MIN密钥，参数为存储密钥的数组
		void set_key_AES_MIDDLE(char *key);//生成随机AES_MIDDLE密钥，参数为存储密钥的数组
		void set_key_AES_MAX(char *key);//生成随机AES_MAX密钥，参数为存储密钥的数组

	signals:

		void lock_DES_process(double process_count);//DES加密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void lock_DES_final(bool is_success, char *key);//DES加密处理完信号。处理完毕后返回密钥
		void unlock_DES_process(double process_count);//DES解密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void unlock_DES_final(bool is_success);//DES解密处理完信号。处理完毕后返回
		void lock_DES_EDE2_process(double process_count);//DES_EDE2加密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void lock_DES_EDE2_final(bool is_success, char *key);//DES_EDE2加密处理完信号。处理完毕后返回密钥
		void unlock_DES_EDE2_process(double process_count);//DES_EDE2解密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void unlock_DES_EDE2_final(bool is_success);//DES_EDE2解密处理完信号。处理完毕后返回
		void lock_DES_EDE3_process(double process_count);//DES_EDE3加密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void lock_DES_EDE3_final(bool is_success, char *key);//DES_EDE3加密处理完信号。处理完毕后返回密钥
		void unlock_DES_EDE3_process(double process_count);//DES_EDE3解密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void unlock_DES_EDE3_final(bool is_success);//DES_EDE3解密处理完信号。处理完毕后返回
		void lock_AES_MIN_process(double process_count);//AES_MIN加密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void lock_AES_MIN_final(bool is_success, char *key);//AES_MIN加密处理完信号。处理完毕后返回密钥
		void unlock_AES_MIN_process(double process_count);//AES_MIN解密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void unlock_AES_MIN_final(bool is_success);//AES_MIN解密处理完信号。处理完毕后返回
		void lock_AES_MIDDLE_process(double process_count);//AES_MIDDLE加密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void lock_AES_MIDDLE_final(bool is_success, char *key);//AES_MIDDLE加密处理完信号。处理完毕后返回密钥
		void unlock_AES_MIDDLE_process(double process_count);//AES_MIDDLE解密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void unlock_AES_MIDDLE_final(bool is_success);//AES_MIDDLE解密处理完信号。处理完毕后返回
		void lock_AES_MAX_process(double process_count);//AES_MAX加密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void lock_AES_MAX_final(bool is_success, char *key);//AES_MAX加密处理完信号。处理完毕后返回密钥
		void unlock_AES_MAX_process(double process_count);//AES_MAX解密处理中信号。在最后一次处理之前，每处理一次便返回一次，供进度条使用
		void unlock_AES_MAX_final(bool is_success);//AES_MAX解密处理完信号。处理完毕后返回
	};

	class LockDouble :public Export_LockDouble_virtual_class//导出类，使用方法：包含头文件即可使用
	{
		Q_OBJECT

	public:

		virtual void set_key_RSA(char *public_key, char *private_key, int size, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, const string &output_path);//RSA密钥生成。输入参数：公钥存储单元，私钥存储单元，密钥长度，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径，是否有头部特征数字，头部特征数字，密钥文件生成路径
		virtual void set_key_ECC(char *public_key, char *private_key, const string &curve_type, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, const string &output_path);//ECC密钥生成。输入参数：公钥存储单元，私钥存储单元，曲线类型，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径，是否有头部特征数字，头部特征数字，密钥文件生成路径
		virtual void lock_RSA(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *public_key, int size);//RSA加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否有头部特征数字，头部特征数字，公钥，密钥大小
		virtual void unlock_RSA(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *private_key, int size);//RSA解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否有头部特征数字，头部特征数字，私钥，密钥大小
		virtual void lock_ECC(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *public_key, int size);//ECC加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否有头部特征数字，头部特征数字，公钥，密钥大小
		virtual void unlock_ECC(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *private_key, int size);//ECC解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否有头部特征数字，头部特征数字，私钥，密钥大小

	signals:

		void set_key_RSA_final(int public_key_length, int private_key_length);//RSA密钥设置完信号，参数为公钥和私钥长度
		void set_key_ECC_final(int public_key_length, int private_key_length);//ECC密钥设置完信号，参数为公钥和私钥长度
		void lock_RSA_out_of_range();//RSA加密文件大小超出范围
		void lock_RSA_wrong_key();//RSA加密密钥错误
		void lock_RSA_final(bool is_success);//RSA加密处理完信号。处理完毕后返回
		void unlock_RSA_out_of_range();//RSA解密密文长度不正确
		void unlock_RSA_wrong_key();//RSA解密密钥错误
		void unlock_RSA_final(bool is_success);//RSA解密处理完信号。处理完毕后返回
		void lock_ECC_out_of_range();//ECC加密文件大小超出范围
		void lock_ECC_wrong_key();//ECC加密密钥错误
		void lock_ECC_final(bool is_success);//ECC加密处理完信号。处理完毕后返回
		void unlock_ECC_out_of_range();//ECC解密密文长度不正确
		void unlock_ECC_wrong_key();//ECC解密密钥错误
		void unlock_ECC_final(bool is_success);//ECC解密处理完信号。处理完毕后返回
	};

	class HashCalculate :public Export_HashCalculate_virtual_class//导出类，使用方法：包含头文件即可使用
	{
		Q_OBJECT

	public:

		virtual void hash_calculate_MD4(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path);//MD4计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径
		virtual void hash_calculate_MD5(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path);//MD5计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径
		virtual void hash_calculate_SHA1(const string &file_path,const string &file_name, char *result, bool is_output_history_file, const string &history_file_path);//SHA1计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径
		virtual void hash_calculate_SHA2(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type);//SHA2计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径，计算类型
		virtual void hash_calculate_SHA3(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type);//SHA3计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径，计算类型
		virtual void hash_calculate_Keccak(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type);//Keccak计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径，计算类型
		
	signals:

		void hash_calculate_MD4_final(int length);//MD4运算处理完信号，参数为结果长度
		void hash_calculate_MD5_final(int length);//MD5运算处理完信号，参数为结果长度
		void hash_calculate_SHA1_final(int length);//SHA1运算处理完信号，参数为结果长度
		void hash_calculate_SHA2_final(int length);//SHA2运算处理完信号，参数为结果长度
		void hash_calculate_SHA3_final(int length);//SHA3运算处理完信号，参数为结果长度
		void hash_calculate_Keccak_final(int length);//SHA3运算处理完信号，参数为结果长度
	};
}
#endif