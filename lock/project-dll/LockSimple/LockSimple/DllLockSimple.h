#ifndef LOCKSIMPLE_H
#define LOCKSIMPLE_H

//ͷ�ļ�
#include <QtCore/qglobal.h>
#include <QtWidgets/QMainWindow>
#include <QString>
#include <QDateTime>
#include <string>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include "ExportClassLockSimple.h"

//�궨��
#define FILE_ONCE_MAX_SIZE_NUMBER 1048576//����һ�δ�����С�������ֵ����1024*1024
#define FILE_HEAD_NUMBER_SIZE_NUMBER 4//��������ռ���ֽ���
#define FILE_HEAD_RAW_NUMBER_SIZE_NUMBER 8//��������ת��Ϊԭʼ���ݺ�ռ���ֽ���
#define FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER 1900//��ʷ�ļ�д������1��1970����ʼ��ʱ����Ϊ1900����ʼ��ʱ�䣬Ҳ�������Ҫ����1900
#define FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER 1//��ʷ�ļ�д������1�·�ȡֵ��Χ����
#define FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER 3//˫�������ʹ�õ����ڽ�����������ļ���С�ı���
#define FILE_LOCK_TAIL_SIZE_TIME_NUMBER 2//���������ʹ�õ����ڽ�����������ļ���С�ı���
#define FILE_KEY_WRITE_BINARY_TYPE_1_NUMBER 1//��������Կ�ļ���������1����ȡ������Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_2_NUMBER 2//��������Կ�ļ���������2���򵥼Ӽ�����Ӧ����
#define FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER 1//��������Կ�ļ�ͷ���������ֵı��1�����������֣���Ӧ����
#define FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER 0//��������Կ�ļ�ͷ���������ֵı��0�����������֣���Ӧ����
#define FILE_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER 16//�Ӽ��������ѭ����Ԫ��Ŀ
#define FILE_FILE_INTERVAL_STRING "\\"//�ļ�·���ָ���
#define FILE_TEMP_FILE_TIME_FORMAT_STRING "yyyy-MM-dd hh-mm-ss-zzz"//��ʱ�ļ�ʱ���ʽ
#define FILE_TEMP_FILE_BACK_PATH_STRING "temp.locktemp"//��������ļ�ʱʹ�õ���ʱ�ļ�·���ĺ�벿��
#define FILE_TEMP_DOUBLE_FILE_BACK_PATH_STRING "tempdouble.locktemp"//�����˫������ļ�ʱʹ�õ���ʱ�ļ�·���ĺ�벿��
#define FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING "\n"//��ʷ�ļ�д�����ݻ��з�
#define FILE_HISTORY_WRITE_INFORMATION_1_STRING "time:"//��ʷ�ļ�д������1
#define FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING "-"//��ʷ�ļ�д������1ʱ��ָ���1
#define FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING " "//��ʷ�ļ�д������1ʱ��ָ���2
#define FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING ":"//��ʷ�ļ�д������1ʱ��ָ���3
#define FILE_HISTORY_WRITE_INFORMATION_2_STRING "name:"//��ʷ�ļ�д������2
#define FILE_HISTORY_WRITE_INFORMATION_3_STRING "path:"//��ʷ�ļ�д������3
#define FILE_HISTORY_WRITE_INFORMATION_4_1_STRING "operation:"//��ʷ�ļ�д������4-1
#define FILE_HISTORY_WRITE_INFORMATION_4_2_STRING "lock"//��ʷ�ļ�д������4-2
#define FILE_HISTORY_WRITE_INFORMATION_4_3_STRING "unlock"//��ʷ�ļ�д������4-3
#define FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING "\n"//��Կ�ļ�д�����ݻ��з�
#define FILE_KEY_WRITE_INFORMATION_1_STRING "һ�w�˥�ե�դ���` Text Type Key File"//��Կ�ļ�д������1
#define FILE_KEY_WRITE_INFORMATION_2_STRING "filename:"//��Կ�ļ�д������2
#define FILE_KEY_WRITE_INFORMATION_3_STRING "filepath:"//��Կ�ļ�д������3
#define FILE_KEY_WRITE_INFORMATION_4_STRING "type:"//��Կ�ļ�д������4
#define FILE_KEY_WRITE_INFORMATION_4_1_STRING "simple-opposite"//��Կ�ļ�д������4-1
#define FILE_KEY_WRITE_INFORMATION_4_2_STRING "simple-add"//��Կ�ļ�д������4-2
#define FILE_KEY_WRITE_INFORMATION_5_STRING "direction:"//��Կ�ļ�д������5
#define FILE_KEY_WRITE_INFORMATION_5_1_STRING "right"//��Կ�ļ�д������5-1
#define FILE_KEY_WRITE_INFORMATION_5_2_STRING "left"//��Կ�ļ�д������5-2
#define FILE_KEY_WRITE_INFORMATION_5_3_STRING "right and left"//��Կ�ļ�д������5-3
#define FILE_KEY_WRITE_INFORMATION_6_STRING "ignore-head:"//��Կ�ļ�д������6
#define FILE_KEY_WRITE_INFORMATION_7_STRING "ignore-tail:"//��Կ�ļ�д������7
#define FILE_KEY_WRITE_INFORMATION_8_STRING "cycle:"//��Կ�ļ�д������8
#define FILE_KEY_WRITE_INFORMATION_9_STRING "magic-number:"//��Կ�ļ�д������9
#define FILE_KEY_WRITE_INFORMATION_9_1_STRING "null"//��Կ�ļ�д������9-1
#define FILE_KEY_WRITE_INFORMATION_10_STRING "key-number:"//��Կ�ļ�д������10
#define FILE_KEY_WRITE_INFORMATION_10_1_STRING ";"//��Կ�ļ�д������10-1
#define FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING "57555341FFFF4C46"//��������Կ�ļ�ͷ��ħ�����ֶ�Ӧʮ���������ݣ���������Ϊ��WUSAxxLF������xx����ʮ�������롰FFFF����䣩
#define FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING "FFFFFFFFFFFFFFFF"//��������Կ�ļ��ָ�����Ӧʮ����������
#define FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING "FFFFFFFF"//��������Կ�ļ��̷ָ�����Ӧʮ����������

namespace rem
{
	//ʹ�ñ�׼�����ռ�
	using std::string;

	//����
	class LockOpposite :public Export_LockSimple_virtual_class//�����࣬ʹ�÷���������ͷ�ļ�����ʹ��
	{

		Q_OBJECT

	public:

		virtual void lock_opposite(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, const string &temp_file_path, int direction, long long head_offset, long long tail_offset, long long cycle, bool have_head_digit, char *head_digit);//�ļ�ȡ�����ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺����ʱ�ļ���·�������ܷ���1����˳��2������3����˫���򣩣�ͷ��������㣬β��������㣬ѭ�����ڣ��Ƿ���ͷ���������֣�ͷ����������
		virtual void unlock_opposite(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, const string &temp_file_path, int direction, long long head_offset, long long tail_offset, long long cycle, bool have_head_digit, char *head_digit);//�ļ�ȡ�����ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·������ʱ�ļ���·�������ܷ���1����˳��2������3����˫���򣩣�ͷ��������㣬β��������㣬ѭ�����ڣ��Ƿ���ͷ���������֣�ͷ����������
		virtual void lock_add(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, const string &temp_file_path, int direction, long long head_offset, long long tail_offset, int cycle, bool have_head_digit, char *head_digit, int *unit_digit);//�ļ�ȡ�����ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺����ʱ�ļ���·�������ܷ���1����˳��2������3����˫���򣩣�ͷ��������㣬β��������㣬ѭ�����ڣ�ע������ѭ������ָ���ǼӼ�ѭ����Ԫ��Ŀ��������ȡ�����ܵļ��ܼ��������Ҫ���м�1���������Ƿ���ͷ���������֣�ͷ���������֣���ѭ����λ�Ӽ�������Ϊ����16��int�͵����飩
		virtual void unlock_add(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, const string &temp_file_path, int direction, long long head_offset, long long tail_offset, int cycle, bool have_head_digit, char *head_digit, int *unit_digit);//�ļ�ȡ�����ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·������ʱ�ļ���·�������ܷ���1����˳��2������3����˫���򣩣�ͷ��������㣬β��������㣬ѭ�����ڣ�ע������ѭ������ָ���ǼӼ�ѭ����Ԫ��Ŀ��������ȡ�����ܵļ��ܼ��������Ҫ���м�1���������Ƿ���ͷ���������֣�ͷ���������֣���ѭ����λ�Ӽ�������Ϊ����16��int�͵����飩

	signals:

		void lock_simple_opposite_process(double process_count);//ȡ�����ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void lock_simple_opposite_final(bool is_success);//ȡ�����ܴ������źš�������Ϻ󷵻�
		void unlock_simple_opposite_process(double process_count);//ȡ�����ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void unlock_simple_opposite_final(bool is_success);//ȡ�����ܴ������źš�������Ϻ󷵻�
		void lock_simple_add_process(double process_count);//�Ӽ����ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void lock_simple_add_final(bool is_success);//�Ӽ����ܴ������źš�������Ϻ󷵻�
		void unlock_simple_add_process(double process_count);//�Ӽ����ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void unlock_simple_add_final(bool is_success);//�Ӽ����ܴ������źš�������Ϻ󷵻�
	};
}
#endif