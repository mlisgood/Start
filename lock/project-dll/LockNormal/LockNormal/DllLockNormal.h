#ifndef LOCKNORMAL_H
#define LOCKNORMAL_H

//ͷ�ļ�
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

//�궨��
#define FILE_KEY_SEED_SIZE_NUMBER 1024//���������Կ�õ������������С
#define FILE_HEAD_NUMBER_SIZE_NUMBER 4//��������ռ���ֽ���
#define FILE_HEAD_RAW_NUMBER_SIZE_NUMBER 8//��������ת��Ϊԭʼ���ݺ�ռ���ֽ���
#define FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER 1900//��ʷ�ļ�д������1��1970����ʼ��ʱ����Ϊ1900����ʼ��ʱ�䣬Ҳ�������Ҫ����1900
#define FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER 1//��ʷ�ļ�д������1�·�ȡֵ��Χ����
#define FILE_KEY_WRITE_BINARY_TYPE_3_NUMBER 3//��������Կ�ļ���������3��DES����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_4_NUMBER 4//��������Կ�ļ���������4��2-key 3DES����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_5_NUMBER 5//��������Կ�ļ���������5��3-key 3DES����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_6_NUMBER 6//��������Կ�ļ���������6��AES-128����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_7_NUMBER 7//��������Կ�ļ���������7��AES-192����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_8_NUMBER 8//��������Կ�ļ���������8��AES-256����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_9_NUMBER 9//��������Կ�ļ���������9��RSA��Կ����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_10_NUMBER 10//��������Կ�ļ���������10��RSA˽Կ����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_11_NUMBER 11//��������Կ�ļ���������11��ECC��Կ����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_12_NUMBER 12//��������Կ�ļ���������12��ECC˽Կ����Ӧ����
#define FILE_KEY_AES_MIDDLE_KEY_LENGTH 24//AES-192��Ӧ��Կ����
#define FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER 1//��������Կ�ļ�ͷ���������ֵı��1�����������֣���Ӧ����
#define FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER 0//��������Կ�ļ�ͷ���������ֵı��0�����������֣���Ӧ����
#define FILE_KEY_RANDOM_HEX_MIN_NUMBER 0//������Կ��Сʮ�����ƴ����Ӧ����
#define FILE_KEY_RANDOM_HEX_MAX_NUMBER 15//������Կ���ʮ�����ƴ����Ӧ����
#define FILE_LOCK_TAIL_ADD_CHAR '\0'//�������β��������ܿ��С���ַ�
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
#define FILE_HISTORY_WRITE_INFORMATION_4_4_STRING "set key"//��ʷ�ļ�д������4-4
#define FILE_HISTORY_WRITE_INFORMATION_4_5_STRING "hash calculate"//��ʷ�ļ�д������4-5
#define FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING "\n"//��Կ�ļ�д�����ݻ��з�
#define FILE_KEY_WRITE_INFORMATION_1_STRING "һ�w�˥�ե�դ���` Text Type Key File"//��Կ�ļ�д������1
#define FILE_KEY_WRITE_INFORMATION_1_1_STRING "һ�w�˥�ե�դ���` Text Type Key File\nPlease use the public key to encrypt, and use the private key to decrypt. You shouldn't lose the private key."//��Կ�ļ�д������1-1
#define FILE_KEY_WRITE_INFORMATION_2_STRING "filename:"//��Կ�ļ�д������2
#define FILE_KEY_WRITE_INFORMATION_3_STRING "filepath:"//��Կ�ļ�д������3
#define FILE_KEY_WRITE_INFORMATION_4_STRING "type:"//��Կ�ļ�д������4
#define FILE_KEY_WRITE_INFORMATION_4_1_STRING "normal-DES"//��Կ�ļ�д������4-1
#define FILE_KEY_WRITE_INFORMATION_4_2_STRING "normal-DES-EDE2"//��Կ�ļ�д������4-2
#define FILE_KEY_WRITE_INFORMATION_4_3_STRING "normal-DES-EDE3"//��Կ�ļ�д������4-3
#define FILE_KEY_WRITE_INFORMATION_4_4_STRING "normal-AES-128"//��Կ�ļ�д������4-4
#define FILE_KEY_WRITE_INFORMATION_4_5_STRING "normal-AES-192"//��Կ�ļ�д������4-5
#define FILE_KEY_WRITE_INFORMATION_4_6_STRING "normal-AES-256"//��Կ�ļ�д������4-6
#define FILE_KEY_WRITE_INFORMATION_4_7_STRING "normal-RSA"//��Կ�ļ�д������4-7
#define FILE_KEY_WRITE_INFORMATION_4_8_STRING "normal-ECC"//��Կ�ļ�д������4-8
#define FILE_KEY_WRITE_INFORMATION_5_STRING "magic-number:"//��Կ�ļ�д������5
#define FILE_KEY_WRITE_INFORMATION_5_1_STRING "null"//��Կ�ļ�д������5-1
#define FILE_KEY_WRITE_INFORMATION_6_STRING "key:"//��Կ�ļ�д������6
#define FILE_KEY_WRITE_INFORMATION_6_1_STRING "public key:"//��Կ�ļ�д������6_1
#define FILE_KEY_WRITE_INFORMATION_6_2_STRING "private key:"//��Կ�ļ�д������6_2
#define FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING "57555341FFFF4C46"//��������Կ�ļ�ͷ��ħ�����ֶ�Ӧʮ���������ݣ���������Ϊ��WUSAxxLF������xx����ʮ�������롰FFFF����䣩
#define FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING "FFFFFFFFFFFFFFFF"//��������Կ�ļ��ָ�����Ӧʮ����������
#define FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING "FFFFFFFF"//��������Կ�ļ��̷ָ�����Ӧʮ����������
#define FILE_KEY_RANDOM_HEX_10_STRING 'A'//������Կ10��Ӧʮ�����ƽ��ƴ���
#define FILE_KEY_RANDOM_HEX_11_STRING 'B'//������Կ10��Ӧʮ�����ƽ��ƴ���
#define FILE_KEY_RANDOM_HEX_12_STRING 'C'//������Կ10��Ӧʮ�����ƽ��ƴ���
#define FILE_KEY_RANDOM_HEX_13_STRING 'D'//������Կ10��Ӧʮ�����ƽ��ƴ���
#define FILE_KEY_RANDOM_HEX_14_STRING 'E'//������Կ10��Ӧʮ�����ƽ��ƴ���
#define FILE_KEY_RANDOM_HEX_15_STRING 'F'//������Կ10��Ӧʮ�����ƽ��ƴ���
#define FILE_KEY_RANDOM_HEX_0_STRING '0'//������Կ0��Ӧʮ�����ƽ��ƴ���
#define FILE_PUBLIC_KEY_FILE_EXTRA_PATH_STRING "-public"//�ǶԳƼ��ܹ�Կ�ļ��ļ��������ַ���
#define FILE_PRIVATE_KEY_FILE_EXTRA_PATH_STRING "-private"//�ǶԳƼ���˽Կ�ļ��ļ��������ַ���


//���п�
#pragma comment(lib,"cryptlib.lib")//����crypto++���п�

namespace rem
{
	//ʹ�ñ�׼�����ռ�
	using std::string;

	//����crypto++�����ռ�
	using namespace CryptoPP;

	//����
	class LockSingle :public Export_LockSingle_virtual_class//�����࣬ʹ�÷���������ͷ�ļ�����ʹ��
	{
		Q_OBJECT

	public:

		virtual void lock_DES(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully);//DES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�DES��Ҫ����Ż���м��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
		virtual void unlock_DES(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully);//DES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�DES��Ҫ����Ż���н��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
		virtual void lock_DES_EDE2(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully);//2-Key TripleDES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�DES��Ҫ����Ż���м��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
		virtual void unlock_DES_EDE2(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully);//2-Key TripleDES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�DES��Ҫ����Ż���н��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
		virtual void lock_DES_EDE3(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully);//3-Key TripleDES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�DES��Ҫ����Ż���м��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
		virtual void unlock_DES_EDE3(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully);//3-Key TripleDES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�DES��Ҫ����Ż���н��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
		virtual void lock_AES_MIN(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully);//AES-128���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�AES��Ҫ����Ż���м��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
		virtual void unlock_AES_MIN(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully);//AES-128���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�AES��Ҫ����Ż���н��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
		virtual void lock_AES_MIDDLE(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully);//AES-192���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�AES��Ҫ����Ż���м��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
		virtual void unlock_AES_MIDDLE(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully);//AES-192���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�AES��Ҫ����Ż���н��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
		virtual void lock_AES_MAX(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully);//AES-256���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�AES��Ҫ����Ż���м��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
		virtual void unlock_AES_MAX(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully);//AES-256���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�AES��Ҫ����Ż���н��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�

		//�ڲ�ʹ�õĺ���
		void set_key_DES(char *key);//�������DES��Կ������Ϊ�洢��Կ������
		void set_key_DES_EDE2(char *key);//�������DES_EDE2��Կ������Ϊ�洢��Կ������
		void set_key_DES_EDE3(char *key);//�������DES_EDE3��Կ������Ϊ�洢��Կ������
		void set_key_AES_MIN(char *key);//�������AES_MIN��Կ������Ϊ�洢��Կ������
		void set_key_AES_MIDDLE(char *key);//�������AES_MIDDLE��Կ������Ϊ�洢��Կ������
		void set_key_AES_MAX(char *key);//�������AES_MAX��Կ������Ϊ�洢��Կ������

	signals:

		void lock_DES_process(double process_count);//DES���ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void lock_DES_final(bool is_success, char *key);//DES���ܴ������źš�������Ϻ󷵻���Կ
		void unlock_DES_process(double process_count);//DES���ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void unlock_DES_final(bool is_success);//DES���ܴ������źš�������Ϻ󷵻�
		void lock_DES_EDE2_process(double process_count);//DES_EDE2���ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void lock_DES_EDE2_final(bool is_success, char *key);//DES_EDE2���ܴ������źš�������Ϻ󷵻���Կ
		void unlock_DES_EDE2_process(double process_count);//DES_EDE2���ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void unlock_DES_EDE2_final(bool is_success);//DES_EDE2���ܴ������źš�������Ϻ󷵻�
		void lock_DES_EDE3_process(double process_count);//DES_EDE3���ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void lock_DES_EDE3_final(bool is_success, char *key);//DES_EDE3���ܴ������źš�������Ϻ󷵻���Կ
		void unlock_DES_EDE3_process(double process_count);//DES_EDE3���ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void unlock_DES_EDE3_final(bool is_success);//DES_EDE3���ܴ������źš�������Ϻ󷵻�
		void lock_AES_MIN_process(double process_count);//AES_MIN���ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void lock_AES_MIN_final(bool is_success, char *key);//AES_MIN���ܴ������źš�������Ϻ󷵻���Կ
		void unlock_AES_MIN_process(double process_count);//AES_MIN���ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void unlock_AES_MIN_final(bool is_success);//AES_MIN���ܴ������źš�������Ϻ󷵻�
		void lock_AES_MIDDLE_process(double process_count);//AES_MIDDLE���ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void lock_AES_MIDDLE_final(bool is_success, char *key);//AES_MIDDLE���ܴ������źš�������Ϻ󷵻���Կ
		void unlock_AES_MIDDLE_process(double process_count);//AES_MIDDLE���ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void unlock_AES_MIDDLE_final(bool is_success);//AES_MIDDLE���ܴ������źš�������Ϻ󷵻�
		void lock_AES_MAX_process(double process_count);//AES_MAX���ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void lock_AES_MAX_final(bool is_success, char *key);//AES_MAX���ܴ������źš�������Ϻ󷵻���Կ
		void unlock_AES_MAX_process(double process_count);//AES_MAX���ܴ������źš������һ�δ���֮ǰ��ÿ����һ�α㷵��һ�Σ���������ʹ��
		void unlock_AES_MAX_final(bool is_success);//AES_MAX���ܴ������źš�������Ϻ󷵻�
	};

	class LockDouble :public Export_LockDouble_virtual_class//�����࣬ʹ�÷���������ͷ�ļ�����ʹ��
	{
		Q_OBJECT

	public:

		virtual void set_key_RSA(char *public_key, char *private_key, int size, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, const string &output_path);//RSA��Կ���ɡ������������Կ�洢��Ԫ��˽Կ�洢��Ԫ����Կ���ȣ��Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·�����Ƿ���ͷ���������֣�ͷ���������֣���Կ�ļ�����·��
		virtual void set_key_ECC(char *public_key, char *private_key, const string &curve_type, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, const string &output_path);//ECC��Կ���ɡ������������Կ�洢��Ԫ��˽Կ�洢��Ԫ���������ͣ��Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·�����Ƿ���ͷ���������֣�ͷ���������֣���Կ�ļ�����·��
		virtual void lock_RSA(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *public_key, int size);//RSA���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ���ͷ���������֣�ͷ���������֣���Կ����Կ��С
		virtual void unlock_RSA(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *private_key, int size);//RSA���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ���ͷ���������֣�ͷ���������֣�˽Կ����Կ��С
		virtual void lock_ECC(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *public_key, int size);//ECC���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ���ͷ���������֣�ͷ���������֣���Կ����Կ��С
		virtual void unlock_ECC(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *private_key, int size);//ECC���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ���ͷ���������֣�ͷ���������֣�˽Կ����Կ��С

	signals:

		void set_key_RSA_final(int public_key_length, int private_key_length);//RSA��Կ�������źţ�����Ϊ��Կ��˽Կ����
		void set_key_ECC_final(int public_key_length, int private_key_length);//ECC��Կ�������źţ�����Ϊ��Կ��˽Կ����
		void lock_RSA_out_of_range();//RSA�����ļ���С������Χ
		void lock_RSA_wrong_key();//RSA������Կ����
		void lock_RSA_final(bool is_success);//RSA���ܴ������źš�������Ϻ󷵻�
		void unlock_RSA_out_of_range();//RSA�������ĳ��Ȳ���ȷ
		void unlock_RSA_wrong_key();//RSA������Կ����
		void unlock_RSA_final(bool is_success);//RSA���ܴ������źš�������Ϻ󷵻�
		void lock_ECC_out_of_range();//ECC�����ļ���С������Χ
		void lock_ECC_wrong_key();//ECC������Կ����
		void lock_ECC_final(bool is_success);//ECC���ܴ������źš�������Ϻ󷵻�
		void unlock_ECC_out_of_range();//ECC�������ĳ��Ȳ���ȷ
		void unlock_ECC_wrong_key();//ECC������Կ����
		void unlock_ECC_final(bool is_success);//ECC���ܴ������źš�������Ϻ󷵻�
	};

	class HashCalculate :public Export_HashCalculate_virtual_class//�����࣬ʹ�÷���������ͷ�ļ�����ʹ��
	{
		Q_OBJECT

	public:

		virtual void hash_calculate_MD4(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path);//MD4���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·��
		virtual void hash_calculate_MD5(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path);//MD5���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·��
		virtual void hash_calculate_SHA1(const string &file_path,const string &file_name, char *result, bool is_output_history_file, const string &history_file_path);//SHA1���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·��
		virtual void hash_calculate_SHA2(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type);//SHA2���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·������������
		virtual void hash_calculate_SHA3(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type);//SHA3���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·������������
		virtual void hash_calculate_Keccak(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type);//Keccak���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·������������
		
	signals:

		void hash_calculate_MD4_final(int length);//MD4���㴦�����źţ�����Ϊ�������
		void hash_calculate_MD5_final(int length);//MD5���㴦�����źţ�����Ϊ�������
		void hash_calculate_SHA1_final(int length);//SHA1���㴦�����źţ�����Ϊ�������
		void hash_calculate_SHA2_final(int length);//SHA2���㴦�����źţ�����Ϊ�������
		void hash_calculate_SHA3_final(int length);//SHA3���㴦�����źţ�����Ϊ�������
		void hash_calculate_Keccak_final(int length);//SHA3���㴦�����źţ�����Ϊ�������
	};
}
#endif