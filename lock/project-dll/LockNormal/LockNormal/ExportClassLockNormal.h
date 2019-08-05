#ifndef EXPORTCLASSLOCKNORMAL_H
#define EXPORTCLASSLOCKNORMAL_H

#include <QtWidgets/QApplication>
#include <string>

namespace rem
{

	//ʹ�ñ�׼�����ռ�
	using std::string;

	class Export_LockSingle_virtual_class :public QObject//ͨ�����ർ��ʵ�ʵ���
	{
		Q_OBJECT

	public:

		virtual	~Export_LockSingle_virtual_class() {};

		//��Ҫ�����ĺ�������Ϊ���麯��
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

	class Export_LockDouble_virtual_class :public QObject//ͨ�����ർ��ʵ�ʵ���
	{
		Q_OBJECT

	public:

		virtual	~Export_LockDouble_virtual_class() {};

		//��Ҫ�����ĺ�������Ϊ���麯��
		virtual void set_key_RSA(char *public_key, char *private_key, int size, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, const string &output_path) = 0;
		virtual void set_key_ECC(char *public_key, char *private_key, const string &curve_type, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, const string &output_path) = 0;
		virtual void lock_RSA(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *public_key, int size) = 0;
		virtual void unlock_RSA(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *private_key, int size) = 0;
		virtual void lock_ECC(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *public_key, int size) = 0;
		virtual void unlock_ECC(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *public_key, int size) = 0;
	};

	class Export_HashCalculate_virtual_class :public QObject//ͨ�����ർ��ʵ�ʵ���
	{
		Q_OBJECT

	public:

		virtual	~Export_HashCalculate_virtual_class() {};

		//��Ҫ�����ĺ�������Ϊ���麯��
		virtual void hash_calculate_MD4(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path) = 0;//MD4���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·��
		virtual void hash_calculate_MD5(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path) = 0;//MD5���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·��
		virtual void hash_calculate_SHA1(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path) = 0;//SHA1���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·��
		virtual void hash_calculate_SHA2(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type) = 0;//SHA2���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·������������
		virtual void hash_calculate_SHA3(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type) = 0;//SHA3���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·������������
		virtual void hash_calculate_Keccak(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type) = 0;//Keccak���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·������������

	};

	extern "C" __declspec(dllexport) Export_LockSingle_virtual_class *export_class_lock_single(void);//����ʵ�ʵ���
	extern "C" __declspec(dllexport) Export_LockDouble_virtual_class *export_class_lock_double(void);
	extern "C" __declspec(dllexport) Export_HashCalculate_virtual_class *export_class_hash_calculate(void);
}

#endif
