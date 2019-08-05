#ifndef EXPORTCLASSLOCKSIMPLE_H
#define EXPORTCLASSLOCKSIMPLE_H

#include <QtWidgets/QApplication>
#include <string>

namespace rem
{

	//使用标准命名空间
	using std::string;

	class Export_LockSimple_virtual_class :public QObject//通过该类导出实际的类
	{

		Q_OBJECT

	public:

		virtual	~Export_LockSimple_virtual_class() {};

		//需要导出的函数声明为纯虚函数
		virtual void lock_opposite(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, const string &temp_file_path, int direction, long long head_offset, long long tail_offset, long long cycle, bool have_head_digit, char *head_digit) = 0;
		virtual void unlock_opposite(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, const string &temp_file_path, int direction, long long head_offset, long long tail_offset, long long cycle, bool have_head_digit, char *head_digit) = 0;
		virtual void lock_add(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, const string &temp_file_path, int direction, long long head_offset, long long tail_offset, int cycle, bool have_head_digit, char *head_digit, int *unit_digit) = 0;
		virtual void unlock_add(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, const string &temp_file_path, int direction, long long head_offset, long long tail_offset, int cycle, bool have_head_digit, char *head_digit, int *unit_digit) = 0;
	};

	extern "C" __declspec(dllexport) Export_LockSimple_virtual_class *export_class_lock_simple(void);//导出实际的类
}

#endif
