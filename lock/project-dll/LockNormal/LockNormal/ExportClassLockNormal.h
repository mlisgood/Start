#ifndef EXPORTCLASSLOCKNORMAL_H
#define EXPORTCLASSLOCKNORMAL_H

#include <QtWidgets/QApplication>
#include <string>

namespace rem
{

	//使用标准命名空间
	using std::string;

	class Export_LockSingle_virtual_class :public QObject//通过该类导出实际的类
	{
		Q_OBJECT

	public:

		virtual	~Export_LockSingle_virtual_class() {};

		//需要导出的函数声明为纯虚函数
		virtual void lock_DES(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully) = 0;
		virtual void unlock_DES(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully) = 0;
		virtual void lock_DES_EDE2(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully) = 0;
		virtual void unlock_DES_EDE2(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully) = 0;
		virtual void lock_DES_EDE3(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully) = 0;
		virtual void unlock_DES_EDE3(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully) = 0;
		virtual void lock_AES_MIN(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully) = 0;
		virtual void unlock_AES_MIN(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully) = 0;
		virtual void lock_AES_MIDDLE(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully) = 0;
		virtual void unlock_AES_MIDDLE(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully) = 0;
		virtual void lock_AES_MAX(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully) = 0;
		virtual void unlock_AES_MAX(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully) = 0;
	};

	class Export_LockDouble_virtual_class :public QObject//通过该类导出实际的类
	{
		Q_OBJECT

	public:

		virtual	~Export_LockDouble_virtual_class() {};

		//需要导出的函数声明为纯虚函数
		virtual void set_key_RSA(char *public_key, char *private_key, int size, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, const string &output_path) = 0;
		virtual void set_key_ECC(char *public_key, char *private_key, const string &curve_type, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, const string &output_path) = 0;
		virtual void lock_RSA(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *public_key, int size) = 0;
		virtual void unlock_RSA(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *private_key, int size) = 0;
		virtual void lock_ECC(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *public_key, int size) = 0;
		virtual void unlock_ECC(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *public_key, int size) = 0;
	};

	class Export_HashCalculate_virtual_class :public QObject//通过该类导出实际的类
	{
		Q_OBJECT

	public:

		virtual	~Export_HashCalculate_virtual_class() {};

		//需要导出的函数声明为纯虚函数
		virtual void hash_calculate_MD4(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path) = 0;//MD4计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径
		virtual void hash_calculate_MD5(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path) = 0;//MD5计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径
		virtual void hash_calculate_SHA1(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path) = 0;//SHA1计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径
		virtual void hash_calculate_SHA2(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type) = 0;//SHA2计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径，计算类型
		virtual void hash_calculate_SHA3(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type) = 0;//SHA3计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径，计算类型
		virtual void hash_calculate_Keccak(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type) = 0;//Keccak计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径，计算类型

	};

	extern "C" __declspec(dllexport) Export_LockSingle_virtual_class *export_class_lock_single(void);//导出实际的类
	extern "C" __declspec(dllexport) Export_LockDouble_virtual_class *export_class_lock_double(void);
	extern "C" __declspec(dllexport) Export_HashCalculate_virtual_class *export_class_hash_calculate(void);
}

#endif
