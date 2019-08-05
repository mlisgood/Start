#include "DllLockNormal.h"

//ʹ�ñ�׼�����ռ�
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios_base;

//����crypto++�����ռ�
using namespace CryptoPP;

//����
namespace rem
{

	//dll���庯��
	void LockSingle::lock_DES(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully)//DES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�DES��Ҫ����Ż���м��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
	{
		srand((int)time(NULL));//����������ӹ�֮��ʹ��
		char *source_file_data = new char[DES::BLOCKSIZE];//�������ļ�����
		char *target_file_data = new char[DES::BLOCKSIZE];//���ܺ��ļ�����
		DESEncryption encryption_DES;//����DES������
		set_key_DES(key);//����һ�������DES��Կ
		encryption_DES.SetKey((unsigned char*)key, DES::KEYLENGTH);//����DES��Կ
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_DES_final(false, key);
			goto Delete_this_class_lock_DES;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//�����������ͷ����������
		{
			target_file.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//����QByteArrayת��Ϊ16���Ʊ�����ַ����ĳ��ȼ���һ�룬��Ϊ����16������ֵ��ʾһ���ֽ�
		}
		else
		{

		}
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_DES_final(false, key);
			goto Delete_this_class_lock_DES;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		long long total_count = source_file_size / DES::BLOCKSIZE;//�ܴ��������������������һ��
		long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, DES::BLOCKSIZE);//����DES::BLOCKSIZE���ֽ�
			encryption_DES.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//����
			target_file.write(target_file_data, DES::BLOCKSIZE);//д��Ŀ���ļ�
			emit lock_DES_process((double)(DES::BLOCKSIZE*loop_count) / (double)source_file_size);//�����źŸ������������ʹ��
		}
		int source_file_size_remain = source_file_size - total_count * DES::BLOCKSIZE;//ʣ���ֽ���
		if (source_file_size_remain > 0)//�������ʣ������ݣ�Ҫ�������һ�δ���
		{
			if (is_encode_fully)
			{
				char *source_file_data_remain = new char[DES::BLOCKSIZE];
				char *target_file_data_remain = new char[DES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, DES::BLOCKSIZE);//��ʼ������Ϊ�������
				source_file.read(source_file_data_remain, DES::BLOCKSIZE);//����DES::BLOCKSIZE���ֽ�
				encryption_DES.ProcessBlock((unsigned char*)source_file_data_remain, (unsigned char*)target_file_data_remain);//����
				target_file.write(target_file_data_remain, DES::BLOCKSIZE);//д��Ŀ���ļ�
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//����ʣ�µ��ֽ�
				target_file.write(source_file_data_remain, source_file_size_remain);//д��Ŀ���ļ�
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//�ͷ��ڴ�
		delete target_file_data;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_2_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		if (is_output_key_file)//��Ҫ������Կ�ļ�
		{
			string key_file_total_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_path += file_name;//��Կ�ļ����·��
			key_file_total_path += key_file_path;
			ofstream key_file(key_file_total_path, ios_base::out);//�����ı����͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			key_file << FILE_KEY_WRITE_INFORMATION_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����Ӧ���ݡ�����Ϊ��Կ�ļ�ͷ������
			key_file << FILE_KEY_WRITE_INFORMATION_2_STRING << file_name << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//����ļ���
			key_file << FILE_KEY_WRITE_INFORMATION_3_STRING << file_path << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//����ļ�·��
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����������
			QByteArray key_transform(key, DES::DEFAULT_KEYLENGTH * 2);//�����Կ
			key_transform = (key_transform.toHex()).toUpper();
			string key_string(key_transform.data(), DES::DEFAULT_KEYLENGTH * 2);
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//���ͷ����������
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ��ͷ�����ֲ�����ת����ԭʼ������ʾ
				magic_number_transform = (magic_number_transform.toHex()).toUpper();
				string magic_number_string(magic_number_transform.data(), FILE_HEAD_RAW_NUMBER_SIZE_NUMBER);
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << magic_number_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			else
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			key_file.close();
		}
		else
		{

		}
		if (is_output_key_file_binary)//��Ҫ���ɶ�������Կ�ļ�
		{
			string key_file_total_binary_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_binary_path += file_name;//��Կ�ļ����·��
			key_file_total_binary_path += key_file_binary_path;
			ofstream key_file_binary(key_file_total_binary_path, ios_base::binary | ios_base::out);//������������͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			QByteArray magic_number = FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING;//�ȴ������ͷ��ħ������
			QByteArray interval_number = FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING;//�������ļ��ָ���
			QByteArray interval_short_number = FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING;//�������ļ��̷ָ���
			magic_number = QByteArray::fromHex(magic_number);//ת��Ϊ16���Ʊ���
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			string magic_number_string(magic_number.constData(), magic_number.length());//QByteArrayתstring
			string interval_number_string(interval_number.constData(), interval_number.length());
			string interval_short_number_string(interval_short_number.constData(), interval_short_number.length());
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_3_NUMBER;//��������
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//��ͷ���������ֱ��
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//��ͷ���������ֱ��
			key_file_binary << magic_number_string;//д��ͷ��ħ������
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//����������ͣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write(key, DES::DEFAULT_KEYLENGTH);//д����Կ
			key_file_binary << interval_number_string;//д��ָ���
			if (have_head_digit)//д��ͷ������������Ϣ
			{
				key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//д��ͷ����������
			}
			else
			{
				key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				key_file_binary << interval_short_number_string;//д����Ӧλ���ķָ���ռλ
			}
			key_file_binary << interval_number_string;//д��ָ���
			int file_name_length = file_name.length();//�ļ�������
			int file_path_length = file_path.length();//�ļ�·������
			key_file_binary.write((char*)(&file_name_length), sizeof(file_name_length));//����ļ������ȣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << file_name;//д���ļ���
			key_file_binary.write((char*)(&file_path_length), sizeof(file_path_length));//����ļ�·�����ȣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << file_path;//д���ļ�·��
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.close();
		}
		else
		{

		}
		emit lock_DES_final(true, key);
	Delete_this_class_lock_DES://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockSingle::unlock_DES(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully)//DES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�DES��Ҫ����Ż���н��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
	{

		//ע����Ϊ�ǶԳƼ��ܣ����Լӽ��ܷ�ʽ�ǳ��ӽ�
		char *source_file_data = new char[DES::BLOCKSIZE];//�������ļ�����
		char *target_file_data = new char[DES::BLOCKSIZE];//���ܺ��ļ�����
		DESDecryption decryption_DES;//����DES������
		decryption_DES.SetKey((unsigned char*)key, DES::KEYLENGTH);//����DES��Կ
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_DES_final(false);
			goto Delete_this_class_unlock_DES;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//ͷ����������У�顣��Ϊtellg()���ڶ�ȡ�ļ�֮ǰ��Ч������ȶ�ȡͷ���������ֻ���ɸú�����Ч
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ�ý�����Ϣȷ�Ͻ����ṩ��ͷ�����ֲ�����ת����ԭʼ������ʾ
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//תΪQString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//��������ļ�ͷ���������ֵ�char����
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ȡ�������֡�������Ҫע�⣬�����������Ϊȫ�ռ���00000000����ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char����
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			QString source_head_digit_transform_string = source_head_digit_transform;//תΪQString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//ͷ������������ͬ�����н���
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//ȥ��ͷ����������ռ�õĿռ�
				source_file.clear();//����ļ�������������޷���λ
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//���ļ�ָ��ƫ�Ƶ�ͷ����������֮��
			}
			else//ͷ���������ֲ�ͬ��ȡ������
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_DES_final(false);
				goto Delete_this_class_unlock_DES;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_DES_final(false);
			goto Delete_this_class_unlock_DES;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		long long total_count = source_file_size / DES::BLOCKSIZE;//�ܴ��������������������һ��
		long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, DES::BLOCKSIZE);//����DES::BLOCKSIZE���ֽ�
			decryption_DES.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//����
			target_file.write(target_file_data, DES::BLOCKSIZE);//д��Ŀ���ļ�
			emit unlock_DES_process((double)(DES::BLOCKSIZE*loop_count) / (double)source_file_size);//�����źŸ������������ʹ��
		}
		int source_file_size_remain = source_file_size - total_count * DES::BLOCKSIZE;//ʣ���ֽ���
		if (source_file_size_remain > 0)//�������ʣ������ݣ�Ҫ�������һ�δ���
		{
			if (is_decode_fully)
			{
				char *source_file_data_remain = new char[DES::BLOCKSIZE];
				char *target_file_data_remain = new char[DES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, DES::BLOCKSIZE);//��ʼ������Ϊ�������
				source_file.read(source_file_data_remain, DES::BLOCKSIZE);//����DES::BLOCKSIZE���ֽ�
				decryption_DES.ProcessBlock((unsigned char*)source_file_data_remain, (unsigned char*)target_file_data_remain);//����
				target_file.write(target_file_data_remain, DES::BLOCKSIZE);//д��Ŀ���ļ�
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//����ʣ�µ��ֽ�
				target_file.write(source_file_data_remain, source_file_size_remain);//д��Ŀ���ļ�
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//�ͷ��ڴ�
		delete target_file_data;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_3_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit unlock_DES_final(true);
	Delete_this_class_unlock_DES://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockSingle::lock_DES_EDE2(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully)//2-Key TripleDES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�DES��Ҫ����Ż���м��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
	{
		srand((int)time(NULL));//����������ӹ�֮��ʹ��
		char *source_file_data = new char[DES_EDE2::BLOCKSIZE];//�������ļ�����
		char *target_file_data = new char[DES_EDE2::BLOCKSIZE];//���ܺ��ļ�����
		DES_EDE2_Encryption encryption_DES_EDE2;//����DES_EDE2������
		set_key_DES_EDE2(key);//����һ�������DES_EDE2��Կ
		encryption_DES_EDE2.SetKey((unsigned char*)key, DES_EDE2::KEYLENGTH);//����DES��Կ
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_DES_EDE2_final(false, key);
			goto Delete_this_class_lock_DES_EDE2;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//�����������ͷ����������
		{
			target_file.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//����QByteArrayת��Ϊ16���Ʊ�����ַ����ĳ��ȼ���һ�룬��Ϊ����16������ֵ��ʾһ���ֽ�
		}
		else
		{

		}
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_DES_EDE2_final(false, key);
			goto Delete_this_class_lock_DES_EDE2;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		long long total_count = source_file_size / DES_EDE2::BLOCKSIZE;//�ܴ��������������������һ��
		long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, DES_EDE2::BLOCKSIZE);//����DES::BLOCKSIZE���ֽ�
			encryption_DES_EDE2.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//����
			target_file.write(target_file_data, DES_EDE2::BLOCKSIZE);//д��Ŀ���ļ�
			emit lock_DES_EDE2_process((double)(DES_EDE2::BLOCKSIZE*loop_count) / (double)source_file_size);//�����źŸ������������ʹ��
		}
		int source_file_size_remain = source_file_size - total_count * DES_EDE2::BLOCKSIZE;//ʣ���ֽ���
		if (source_file_size_remain > 0)//�������ʣ������ݣ�Ҫ�������һ�δ���
		{
			if (is_encode_fully)
			{
				char *source_file_data_remain = new char[DES_EDE2::BLOCKSIZE];
				char *target_file_data_remain = new char[DES_EDE2::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, DES_EDE2::BLOCKSIZE);//��ʼ������Ϊ�������
				source_file.read(source_file_data_remain, DES_EDE2::BLOCKSIZE);//����DES::BLOCKSIZE���ֽ�
				encryption_DES_EDE2.ProcessBlock((unsigned char*)source_file_data_remain, (unsigned char*)target_file_data_remain);//����
				target_file.write(target_file_data_remain, DES_EDE2::BLOCKSIZE);//д��Ŀ���ļ�
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//����ʣ�µ��ֽ�
				target_file.write(source_file_data_remain, source_file_size_remain);//д��Ŀ���ļ�
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//�ͷ��ڴ�
		delete target_file_data;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_2_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		if (is_output_key_file)//��Ҫ������Կ�ļ�
		{
			string key_file_total_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_path += file_name;//��Կ�ļ����·��
			key_file_total_path += key_file_path;
			ofstream key_file(key_file_total_path, ios_base::out);//�����ı����͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			key_file << FILE_KEY_WRITE_INFORMATION_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����Ӧ���ݡ�����Ϊ��Կ�ļ�ͷ������
			key_file << FILE_KEY_WRITE_INFORMATION_2_STRING << file_name << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//����ļ���
			key_file << FILE_KEY_WRITE_INFORMATION_3_STRING << file_path << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//����ļ�·��
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_2_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����������
			QByteArray key_transform(key, DES_EDE2::DEFAULT_KEYLENGTH * 2);//�����Կ
			key_transform = (key_transform.toHex()).toUpper();
			string key_string(key_transform.data(), DES_EDE2::DEFAULT_KEYLENGTH * 2);
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//���ͷ����������
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ��ͷ�����ֲ�����ת����ԭʼ������ʾ
				magic_number_transform = (magic_number_transform.toHex()).toUpper();
				string magic_number_string(magic_number_transform.data(), FILE_HEAD_RAW_NUMBER_SIZE_NUMBER);
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << magic_number_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			else
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			key_file.close();
		}
		else
		{

		}
		if (is_output_key_file_binary)//��Ҫ���ɶ�������Կ�ļ�
		{
			string key_file_total_binary_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_binary_path += file_name;//��Կ�ļ����·��
			key_file_total_binary_path += key_file_binary_path;
			ofstream key_file_binary(key_file_total_binary_path, ios_base::binary | ios_base::out);//������������͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			QByteArray magic_number = FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING;//�ȴ������ͷ��ħ������
			QByteArray interval_number = FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING;//�������ļ��ָ���
			QByteArray interval_short_number = FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING;//�������ļ��̷ָ���
			magic_number = QByteArray::fromHex(magic_number);//ת��Ϊ16���Ʊ���
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			string magic_number_string(magic_number.constData(), magic_number.length());//QByteArrayתstring
			string interval_number_string(interval_number.constData(), interval_number.length());
			string interval_short_number_string(interval_short_number.constData(), interval_short_number.length());
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_4_NUMBER;//��������
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//��ͷ���������ֱ��
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//��ͷ���������ֱ��
			key_file_binary << magic_number_string;//д��ͷ��ħ������
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//����������ͣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write(key, DES_EDE2::DEFAULT_KEYLENGTH);//д����Կ
			key_file_binary << interval_number_string;//д��ָ���
			if (have_head_digit)//д��ͷ������������Ϣ
			{
				key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//д��ͷ����������
			}
			else
			{
				key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				key_file_binary << interval_short_number_string;//д����Ӧλ���ķָ���ռλ
			}
			key_file_binary << interval_number_string;//д��ָ���
			int file_name_length = file_name.length();//�ļ�������
			int file_path_length = file_path.length();//�ļ�·������
			key_file_binary.write((char*)(&file_name_length), sizeof(file_name_length));//����ļ������ȣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << file_name;//д���ļ���
			key_file_binary.write((char*)(&file_path_length), sizeof(file_path_length));//����ļ�·�����ȣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << file_path;//д���ļ�·��
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.close();
		}
		else
		{

		}
		emit lock_DES_EDE2_final(true, key);
	Delete_this_class_lock_DES_EDE2://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockSingle::unlock_DES_EDE2(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully)//2-Key TripleDES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�DES��Ҫ����Ż���н��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
	{

		//ע����Ϊ�ǶԳƼ��ܣ����Լӽ��ܷ�ʽ�ǳ��ӽ�
		char *source_file_data = new char[DES_EDE2::BLOCKSIZE];//�������ļ�����
		char *target_file_data = new char[DES_EDE2::BLOCKSIZE];//���ܺ��ļ�����
		DES_EDE2_Decryption decryption_DES_EDE2;//����DES������
		decryption_DES_EDE2.SetKey((unsigned char*)key, DES_EDE2::KEYLENGTH);//����DES��Կ
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_DES_EDE2_final(false);
			goto Delete_this_class_unlock_DES_EDE2;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//ͷ����������У�顣��Ϊtellg()���ڶ�ȡ�ļ�֮ǰ��Ч������ȶ�ȡͷ���������ֻ���ɸú�����Ч
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ�ý�����Ϣȷ�Ͻ����ṩ��ͷ�����ֲ�����ת����ԭʼ������ʾ
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//תΪQString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//��������ļ�ͷ���������ֵ�char����
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ȡ�������֡�������Ҫע�⣬�����������Ϊȫ�ռ���00000000����ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char����
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			QString source_head_digit_transform_string = source_head_digit_transform;//תΪQString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//ͷ������������ͬ�����н���
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//ȥ��ͷ����������ռ�õĿռ�
				source_file.clear();//����ļ�������������޷���λ
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//���ļ�ָ��ƫ�Ƶ�ͷ����������֮��
			}
			else//ͷ���������ֲ�ͬ��ȡ������
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_DES_EDE2_final(false);
				goto Delete_this_class_unlock_DES_EDE2;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_DES_EDE2_final(false);
			goto Delete_this_class_unlock_DES_EDE2;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		long long total_count = source_file_size / DES_EDE2::BLOCKSIZE;//�ܴ��������������������һ��
		long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, DES_EDE2::BLOCKSIZE);//����DES::BLOCKSIZE���ֽ�
			decryption_DES_EDE2.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//����
			target_file.write(target_file_data, DES_EDE2::BLOCKSIZE);//д��Ŀ���ļ�
			emit unlock_DES_EDE2_process((double)(DES_EDE2::BLOCKSIZE*loop_count) / (double)source_file_size);//�����źŸ������������ʹ��
		}
		int source_file_size_remain = source_file_size - total_count * DES_EDE2::BLOCKSIZE;//ʣ���ֽ���
		if (source_file_size_remain > 0)//�������ʣ������ݣ�Ҫ�������һ�δ���
		{
			if (is_decode_fully)
			{
				char *source_file_data_remain = new char[DES_EDE2::BLOCKSIZE];
				char *target_file_data_remain = new char[DES_EDE2::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, DES_EDE2::BLOCKSIZE);//��ʼ������Ϊ�������
				source_file.read(source_file_data_remain, DES_EDE2::BLOCKSIZE);//����DES::BLOCKSIZE���ֽ�
				decryption_DES_EDE2.ProcessBlock((unsigned char*)source_file_data_remain, (unsigned char*)target_file_data_remain);//����
				target_file.write(target_file_data_remain, DES_EDE2::BLOCKSIZE);//д��Ŀ���ļ�
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//����ʣ�µ��ֽ�
				target_file.write(source_file_data_remain, source_file_size_remain);//д��Ŀ���ļ�
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//�ͷ��ڴ�
		delete target_file_data;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_3_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit unlock_DES_EDE2_final(true);
	Delete_this_class_unlock_DES_EDE2://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockSingle::lock_DES_EDE3(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully)//3-Key TripleDES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�DES��Ҫ����Ż���м��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
	{
		srand((int)time(NULL));//����������ӹ�֮��ʹ��
		char *source_file_data = new char[DES_EDE3::BLOCKSIZE];//�������ļ�����
		char *target_file_data = new char[DES_EDE3::BLOCKSIZE];//���ܺ��ļ�����
		DES_EDE3_Encryption encryption_DES_EDE3;//����DES_EDE3������
		set_key_DES_EDE3(key);//����һ�������DES_EDE3��Կ
		encryption_DES_EDE3.SetKey((unsigned char*)key, DES_EDE3::KEYLENGTH);//����DES��Կ
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_DES_EDE3_final(false, key);
			goto Delete_this_class_lock_DES_EDE3;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//�����������ͷ����������
		{
			target_file.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//����QByteArrayת��Ϊ16���Ʊ�����ַ����ĳ��ȼ���һ�룬��Ϊ����16������ֵ��ʾһ���ֽ�
		}
		else
		{

		}
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_DES_EDE3_final(false, key);
			goto Delete_this_class_lock_DES_EDE3;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		long long total_count = source_file_size / DES_EDE3::BLOCKSIZE;//�ܴ��������������������һ��
		long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, DES_EDE3::BLOCKSIZE);//����DES::BLOCKSIZE���ֽ�
			encryption_DES_EDE3.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//����
			target_file.write(target_file_data, DES_EDE3::BLOCKSIZE);//д��Ŀ���ļ�
			emit lock_DES_EDE3_process((double)(DES_EDE3::BLOCKSIZE*loop_count) / (double)source_file_size);//�����źŸ������������ʹ��
		}
		int source_file_size_remain = source_file_size - total_count * DES_EDE3::BLOCKSIZE;//ʣ���ֽ���
		if (source_file_size_remain > 0)//�������ʣ������ݣ�Ҫ�������һ�δ���
		{
			if (is_encode_fully)
			{
				char *source_file_data_remain = new char[DES_EDE3::BLOCKSIZE];
				char *target_file_data_remain = new char[DES_EDE3::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, DES_EDE3::BLOCKSIZE);//��ʼ������Ϊ�������
				source_file.read(source_file_data_remain, DES_EDE3::BLOCKSIZE);//����DES::BLOCKSIZE���ֽ�
				encryption_DES_EDE3.ProcessBlock((unsigned char*)source_file_data_remain, (unsigned char*)target_file_data_remain);//����
				target_file.write(target_file_data_remain, DES_EDE3::BLOCKSIZE);//д��Ŀ���ļ�
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//����ʣ�µ��ֽ�
				target_file.write(source_file_data_remain, source_file_size_remain);//д��Ŀ���ļ�
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//�ͷ��ڴ�
		delete target_file_data;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_2_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		if (is_output_key_file)//��Ҫ������Կ�ļ�
		{
			string key_file_total_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_path += file_name;//��Կ�ļ����·��
			key_file_total_path += key_file_path;
			ofstream key_file(key_file_total_path, ios_base::out);//�����ı����͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			key_file << FILE_KEY_WRITE_INFORMATION_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����Ӧ���ݡ�����Ϊ��Կ�ļ�ͷ������
			key_file << FILE_KEY_WRITE_INFORMATION_2_STRING << file_name << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//����ļ���
			key_file << FILE_KEY_WRITE_INFORMATION_3_STRING << file_path << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//����ļ�·��
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_3_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����������
			QByteArray key_transform(key, DES_EDE3::DEFAULT_KEYLENGTH * 2);//�����Կ
			key_transform = (key_transform.toHex()).toUpper();
			string key_string(key_transform.data(), DES_EDE3::DEFAULT_KEYLENGTH * 2);
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//���ͷ����������
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ��ͷ�����ֲ�����ת����ԭʼ������ʾ
				magic_number_transform = (magic_number_transform.toHex()).toUpper();
				string magic_number_string(magic_number_transform.data(), FILE_HEAD_RAW_NUMBER_SIZE_NUMBER);
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << magic_number_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			else
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			key_file.close();
		}
		else
		{

		}
		if (is_output_key_file_binary)//��Ҫ���ɶ�������Կ�ļ�
		{
			string key_file_total_binary_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_binary_path += file_name;//��Կ�ļ����·��
			key_file_total_binary_path += key_file_binary_path;
			ofstream key_file_binary(key_file_total_binary_path, ios_base::binary | ios_base::out);//������������͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			QByteArray magic_number = FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING;//�ȴ������ͷ��ħ������
			QByteArray interval_number = FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING;//�������ļ��ָ���
			QByteArray interval_short_number = FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING;//�������ļ��̷ָ���
			magic_number = QByteArray::fromHex(magic_number);//ת��Ϊ16���Ʊ���
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			string magic_number_string(magic_number.constData(), magic_number.length());//QByteArrayתstring
			string interval_number_string(interval_number.constData(), interval_number.length());
			string interval_short_number_string(interval_short_number.constData(), interval_short_number.length());
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_5_NUMBER;//��������
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//��ͷ���������ֱ��
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//��ͷ���������ֱ��
			key_file_binary << magic_number_string;//д��ͷ��ħ������
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//����������ͣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write(key, DES_EDE3::DEFAULT_KEYLENGTH);//д����Կ
			key_file_binary << interval_number_string;//д��ָ���
			if (have_head_digit)//д��ͷ������������Ϣ
			{
				key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//д��ͷ����������
			}
			else
			{
				key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				key_file_binary << interval_short_number_string;//д����Ӧλ���ķָ���ռλ
			}
			key_file_binary << interval_number_string;//д��ָ���
			int file_name_length = file_name.length();//�ļ�������
			int file_path_length = file_path.length();//�ļ�·������
			key_file_binary.write((char*)(&file_name_length), sizeof(file_name_length));//����ļ������ȣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << file_name;//д���ļ���
			key_file_binary.write((char*)(&file_path_length), sizeof(file_path_length));//����ļ�·�����ȣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << file_path;//д���ļ�·��
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.close();
		}
		else
		{

		}
		emit lock_DES_EDE3_final(true, key);
	Delete_this_class_lock_DES_EDE3://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockSingle::unlock_DES_EDE3(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully)//3-Key TripleDES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�DES��Ҫ����Ż���н��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
	{

		//ע����Ϊ�ǶԳƼ��ܣ����Լӽ��ܷ�ʽ�ǳ��ӽ�
		char *source_file_data = new char[DES_EDE3::BLOCKSIZE];//�������ļ�����
		char *target_file_data = new char[DES_EDE3::BLOCKSIZE];//���ܺ��ļ�����
		DES_EDE3_Decryption decryption_DES_EDE3;//����DES������
		decryption_DES_EDE3.SetKey((unsigned char*)key, DES_EDE3::KEYLENGTH);//����DES��Կ
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_DES_EDE3_final(false);
			goto Delete_this_class_unlock_DES_EDE3;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//ͷ����������У�顣��Ϊtellg()���ڶ�ȡ�ļ�֮ǰ��Ч������ȶ�ȡͷ���������ֻ���ɸú�����Ч
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ�ý�����Ϣȷ�Ͻ����ṩ��ͷ�����ֲ�����ת����ԭʼ������ʾ
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//תΪQString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//��������ļ�ͷ���������ֵ�char����
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ȡ�������֡�������Ҫע�⣬�����������Ϊȫ�ռ���00000000����ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char����
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			QString source_head_digit_transform_string = source_head_digit_transform;//תΪQString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//ͷ������������ͬ�����н���
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//ȥ��ͷ����������ռ�õĿռ�
				source_file.clear();//����ļ�������������޷���λ
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//���ļ�ָ��ƫ�Ƶ�ͷ����������֮��
			}
			else//ͷ���������ֲ�ͬ��ȡ������
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_DES_EDE3_final(false);
				goto Delete_this_class_unlock_DES_EDE3;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_DES_EDE3_final(false);
			goto Delete_this_class_unlock_DES_EDE3;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		long long total_count = source_file_size / DES_EDE3::BLOCKSIZE;//�ܴ��������������������һ��
		long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, DES_EDE3::BLOCKSIZE);//����DES::BLOCKSIZE���ֽ�
			decryption_DES_EDE3.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//����
			target_file.write(target_file_data, DES_EDE3::BLOCKSIZE);//д��Ŀ���ļ�
			emit unlock_DES_EDE3_process((double)(DES_EDE3::BLOCKSIZE*loop_count) / (double)source_file_size);//�����źŸ������������ʹ��
		}
		int source_file_size_remain = source_file_size - total_count * DES_EDE3::BLOCKSIZE;//ʣ���ֽ���
		if (source_file_size_remain > 0)//�������ʣ������ݣ�Ҫ�������һ�δ���
		{
			if (is_decode_fully)
			{
				char *source_file_data_remain = new char[DES_EDE3::BLOCKSIZE];
				char *target_file_data_remain = new char[DES_EDE3::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, DES_EDE3::BLOCKSIZE);//��ʼ������Ϊ�������
				source_file.read(source_file_data_remain, DES_EDE3::BLOCKSIZE);//����DES::BLOCKSIZE���ֽ�
				decryption_DES_EDE3.ProcessBlock((unsigned char*)source_file_data_remain, (unsigned char*)target_file_data_remain);//����
				target_file.write(target_file_data_remain, DES_EDE3::BLOCKSIZE);//д��Ŀ���ļ�
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//����ʣ�µ��ֽ�
				target_file.write(source_file_data_remain, source_file_size_remain);//д��Ŀ���ļ�
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//�ͷ��ڴ�
		delete target_file_data;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_3_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit unlock_DES_EDE3_final(true);
	Delete_this_class_unlock_DES_EDE3://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockSingle::lock_AES_MIN(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully)//AES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�AES��Ҫ����Ż���м��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
	{
		srand((int)time(NULL));//����������ӹ�֮��ʹ��
		char *source_file_data = new char[AES::BLOCKSIZE];//�������ļ�����
		char *target_file_data = new char[AES::BLOCKSIZE];//���ܺ��ļ�����
		unsigned char *xor_block = new unsigned char[AES::BLOCKSIZE];//�����趨Ϊȫ��
		memset(xor_block, 0, AES::BLOCKSIZE);//����
		AESEncryption encryption_AES_MIN;//����AES������
		set_key_AES_MIN(key);//����һ�������AES��Կ
		encryption_AES_MIN.SetKey((unsigned char*)key, AES::MIN_KEYLENGTH);//����AES��Կ
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_AES_MIN_final(false, key);
			goto Delete_this_class_lock_AES_MIN;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//�����������ͷ����������
		{
			target_file.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//����QByteArrayת��Ϊ16���Ʊ�����ַ����ĳ��ȼ���һ�룬��Ϊ����16������ֵ��ʾһ���ֽ�
		}
		else
		{

		}
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_AES_MIN_final(false, key);
			goto Delete_this_class_lock_AES_MIN;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		long long total_count = source_file_size / AES::BLOCKSIZE;//�ܴ��������������������һ��
		long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, AES::BLOCKSIZE);//����AES::BLOCKSIZE���ֽ�
			encryption_AES_MIN.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//����
			target_file.write(target_file_data, AES::BLOCKSIZE);//д��Ŀ���ļ�
			emit lock_AES_MIN_process((double)(AES::BLOCKSIZE*loop_count) / (double)source_file_size);//�����źŸ������������ʹ��
		}
		int source_file_size_remain = source_file_size - total_count * AES::BLOCKSIZE;//ʣ���ֽ���
		if (source_file_size_remain > 0)//�������ʣ������ݣ�Ҫ�������һ�δ���
		{
			if (is_encode_fully)
			{
				char *source_file_data_remain = new char[AES::BLOCKSIZE];
				char *target_file_data_remain = new char[AES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, AES::BLOCKSIZE);//��ʼ������Ϊ�������
				source_file.read(source_file_data_remain, AES::BLOCKSIZE);//����AES::BLOCKSIZE���ֽ�
				encryption_AES_MIN.ProcessAndXorBlock((unsigned char*)source_file_data_remain, xor_block, (unsigned char*)target_file_data_remain);//����
				target_file.write(target_file_data_remain, AES::BLOCKSIZE);//д��Ŀ���ļ�
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//����ʣ�µ��ֽ�
				target_file.write(source_file_data_remain, source_file_size_remain);//д��Ŀ���ļ�
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//�ͷ��ڴ�
		delete target_file_data;//�ͷ��ڴ�
		delete xor_block;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_2_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		if (is_output_key_file)//��Ҫ������Կ�ļ�
		{
			string key_file_total_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_path += file_name;//��Կ�ļ����·��
			key_file_total_path += key_file_path;
			ofstream key_file(key_file_total_path, ios_base::out);//�����ı����͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			key_file << FILE_KEY_WRITE_INFORMATION_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����Ӧ���ݡ�����Ϊ��Կ�ļ�ͷ������
			key_file << FILE_KEY_WRITE_INFORMATION_2_STRING << file_name << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//����ļ���
			key_file << FILE_KEY_WRITE_INFORMATION_3_STRING << file_path << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//����ļ�·��
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_4_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����������
			QByteArray key_transform(key, AES::MIN_KEYLENGTH * 2);//�����Կ
			key_transform = (key_transform.toHex()).toUpper();
			string key_string(key_transform.data(), AES::MIN_KEYLENGTH * 2);
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//���ͷ����������
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ��ͷ�����ֲ�����ת����ԭʼ������ʾ
				magic_number_transform = (magic_number_transform.toHex()).toUpper();
				string magic_number_string(magic_number_transform.data(), FILE_HEAD_RAW_NUMBER_SIZE_NUMBER);
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << magic_number_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			else
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			key_file.close();
		}
		else
		{

		}
		if (is_output_key_file_binary)//��Ҫ���ɶ�������Կ�ļ�
		{
			string key_file_total_binary_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_binary_path += file_name;//��Կ�ļ����·��
			key_file_total_binary_path += key_file_binary_path;
			ofstream key_file_binary(key_file_total_binary_path, ios_base::binary | ios_base::out);//������������͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			QByteArray magic_number = FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING;//�ȴ������ͷ��ħ������
			QByteArray interval_number = FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING;//�������ļ��ָ���
			QByteArray interval_short_number = FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING;//�������ļ��̷ָ���
			magic_number = QByteArray::fromHex(magic_number);//ת��Ϊ16���Ʊ���
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			string magic_number_string(magic_number.constData(), magic_number.length());//QByteArrayתstring
			string interval_number_string(interval_number.constData(), interval_number.length());
			string interval_short_number_string(interval_short_number.constData(), interval_short_number.length());
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_6_NUMBER;//��������
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//��ͷ���������ֱ��
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//��ͷ���������ֱ��
			key_file_binary << magic_number_string;//д��ͷ��ħ������
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//����������ͣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write(key, AES::MIN_KEYLENGTH);//д����Կ
			key_file_binary << interval_number_string;//д��ָ���
			if (have_head_digit)//д��ͷ������������Ϣ
			{
				key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//д��ͷ����������
			}
			else
			{
				key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				key_file_binary << interval_short_number_string;//д����Ӧλ���ķָ���ռλ
			}
			key_file_binary << interval_number_string;//д��ָ���
			int file_name_length = file_name.length();//�ļ�������
			int file_path_length = file_path.length();//�ļ�·������
			key_file_binary.write((char*)(&file_name_length), sizeof(file_name_length));//����ļ������ȣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << file_name;//д���ļ���
			key_file_binary.write((char*)(&file_path_length), sizeof(file_path_length));//����ļ�·�����ȣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << file_path;//д���ļ�·��
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.close();
		}
		else
		{

		}
		emit lock_AES_MIN_final(true, key);
	Delete_this_class_lock_AES_MIN://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockSingle::unlock_AES_MIN(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully)//AES-128���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�AES��Ҫ����Ż���н��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
	{

		//ע����Ϊ�ǶԳƼ��ܣ����Լӽ��ܷ�ʽ�ǳ��ӽ�
		char *source_file_data = new char[AES::BLOCKSIZE];//�������ļ�����
		char *target_file_data = new char[AES::BLOCKSIZE];//���ܺ��ļ�����
		unsigned char *xor_block = new unsigned char[AES::BLOCKSIZE];//�����趨Ϊȫ��
		memset(xor_block, 0, AES::BLOCKSIZE);//����
		AESDecryption decryption_AES_MIN;//����AES������
		decryption_AES_MIN.SetKey((unsigned char*)key, AES::MIN_KEYLENGTH);//����AES��Կ
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_AES_MIN_final(false);
			goto Delete_this_class_unlock_AES_MIN;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//ͷ����������У�顣��Ϊtellg()���ڶ�ȡ�ļ�֮ǰ��Ч������ȶ�ȡͷ���������ֻ���ɸú�����Ч
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ�ý�����Ϣȷ�Ͻ����ṩ��ͷ�����ֲ�����ת����ԭʼ������ʾ
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//תΪQString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//��������ļ�ͷ���������ֵ�char����
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ȡ�������֡�������Ҫע�⣬�����������Ϊȫ�ռ���00000000����ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char����
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			QString source_head_digit_transform_string = source_head_digit_transform;//תΪQString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//ͷ������������ͬ�����н���
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//ȥ��ͷ����������ռ�õĿռ�
				source_file.clear();//����ļ�������������޷���λ
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//���ļ�ָ��ƫ�Ƶ�ͷ����������֮��
			}
			else//ͷ���������ֲ�ͬ��ȡ������
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_AES_MIN_final(false);
				goto Delete_this_class_unlock_AES_MIN;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_AES_MIN_final(false);
			goto Delete_this_class_unlock_AES_MIN;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		long long total_count = source_file_size / AES::BLOCKSIZE;//�ܴ��������������������һ��
		long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, AES::BLOCKSIZE);//����AES::BLOCKSIZE���ֽ�
			decryption_AES_MIN.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//����
			target_file.write(target_file_data, AES::BLOCKSIZE);//д��Ŀ���ļ�
			emit unlock_AES_MIN_process((double)(AES::BLOCKSIZE*loop_count) / (double)source_file_size);//�����źŸ������������ʹ��
		}
		int source_file_size_remain = source_file_size - total_count * AES::BLOCKSIZE;//ʣ���ֽ���
		if (source_file_size_remain > 0)//�������ʣ������ݣ�Ҫ�������һ�δ���
		{
			if (is_decode_fully)
			{
				char *source_file_data_remain = new char[AES::BLOCKSIZE];
				char *target_file_data_remain = new char[AES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, AES::BLOCKSIZE);//��ʼ������Ϊ�������
				source_file.read(source_file_data_remain, AES::BLOCKSIZE);//����AES::BLOCKSIZE���ֽ�
				decryption_AES_MIN.ProcessAndXorBlock((unsigned char*)source_file_data_remain, xor_block, (unsigned char*)target_file_data_remain);//����
				target_file.write(target_file_data_remain, AES::BLOCKSIZE);//д��Ŀ���ļ�
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//����ʣ�µ��ֽ�
				target_file.write(source_file_data_remain, source_file_size_remain);//д��Ŀ���ļ�
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_3_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit unlock_AES_MIN_final(true);
	Delete_this_class_unlock_AES_MIN://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockSingle::lock_AES_MIDDLE(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully)//AES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�AES��Ҫ����Ż���м��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
	{
		srand((int)time(NULL));//����������ӹ�֮��ʹ��
		char *source_file_data = new char[AES::BLOCKSIZE];//�������ļ�����
		char *target_file_data = new char[AES::BLOCKSIZE];//���ܺ��ļ�����
		unsigned char *xor_block = new unsigned char[AES::BLOCKSIZE];//�����趨Ϊȫ��
		memset(xor_block, 0, AES::BLOCKSIZE);//����
		AESEncryption encryption_AES_MIDDLE;//����AES������
		set_key_AES_MIDDLE(key);//����һ�������AES��Կ
		encryption_AES_MIDDLE.SetKey((unsigned char*)key, FILE_KEY_AES_MIDDLE_KEY_LENGTH);//����AES��Կ
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_AES_MIDDLE_final(false, key);
			goto Delete_this_class_lock_AES_MIDDLE;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//�����������ͷ����������
		{
			target_file.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//����QByteArrayת��Ϊ16���Ʊ�����ַ����ĳ��ȼ���һ�룬��Ϊ����16������ֵ��ʾһ���ֽ�
		}
		else
		{

		}
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_AES_MIDDLE_final(false, key);
			goto Delete_this_class_lock_AES_MIDDLE;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		long long total_count = source_file_size / AES::BLOCKSIZE;//�ܴ��������������������һ��
		long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, AES::BLOCKSIZE);//����AES::BLOCKSIZE���ֽ�
			encryption_AES_MIDDLE.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//����
			target_file.write(target_file_data, AES::BLOCKSIZE);//д��Ŀ���ļ�
			emit lock_AES_MIDDLE_process((double)(AES::BLOCKSIZE*loop_count) / (double)source_file_size);//�����źŸ������������ʹ��
		}
		int source_file_size_remain = source_file_size - total_count * AES::BLOCKSIZE;//ʣ���ֽ���
		if (source_file_size_remain > 0)//�������ʣ������ݣ�Ҫ�������һ�δ���
		{
			if (is_encode_fully)
			{
				char *source_file_data_remain = new char[AES::BLOCKSIZE];
				char *target_file_data_remain = new char[AES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, AES::BLOCKSIZE);//��ʼ������Ϊ�������
				source_file.read(source_file_data_remain, AES::BLOCKSIZE);//����AES::BLOCKSIZE���ֽ�
				encryption_AES_MIDDLE.ProcessAndXorBlock((unsigned char*)source_file_data_remain, xor_block, (unsigned char*)target_file_data_remain);//����
				target_file.write(target_file_data_remain, AES::BLOCKSIZE);//д��Ŀ���ļ�
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//����ʣ�µ��ֽ�
				target_file.write(source_file_data_remain, source_file_size_remain);//д��Ŀ���ļ�
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//�ͷ��ڴ�
		delete target_file_data;//�ͷ��ڴ�
		delete xor_block;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_2_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		if (is_output_key_file)//��Ҫ������Կ�ļ�
		{
			string key_file_total_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_path += file_name;//��Կ�ļ����·��
			key_file_total_path += key_file_path;
			ofstream key_file(key_file_total_path, ios_base::out);//�����ı����͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			key_file << FILE_KEY_WRITE_INFORMATION_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����Ӧ���ݡ�����Ϊ��Կ�ļ�ͷ������
			key_file << FILE_KEY_WRITE_INFORMATION_2_STRING << file_name << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//����ļ���
			key_file << FILE_KEY_WRITE_INFORMATION_3_STRING << file_path << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//����ļ�·��
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_5_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����������
			QByteArray key_transform(key, FILE_KEY_AES_MIDDLE_KEY_LENGTH * 2);//�����Կ
			key_transform = (key_transform.toHex()).toUpper();
			string key_string(key_transform.data(), FILE_KEY_AES_MIDDLE_KEY_LENGTH * 2);
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//���ͷ����������
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ��ͷ�����ֲ�����ת����ԭʼ������ʾ
				magic_number_transform = (magic_number_transform.toHex()).toUpper();
				string magic_number_string(magic_number_transform.data(), FILE_HEAD_RAW_NUMBER_SIZE_NUMBER);
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << magic_number_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			else
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			key_file.close();
		}
		else
		{

		}
		if (is_output_key_file_binary)//��Ҫ���ɶ�������Կ�ļ�
		{
			string key_file_total_binary_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_binary_path += file_name;//��Կ�ļ����·��
			key_file_total_binary_path += key_file_binary_path;
			ofstream key_file_binary(key_file_total_binary_path, ios_base::binary | ios_base::out);//������������͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			QByteArray magic_number = FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING;//�ȴ������ͷ��ħ������
			QByteArray interval_number = FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING;//�������ļ��ָ���
			QByteArray interval_short_number = FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING;//�������ļ��̷ָ���
			magic_number = QByteArray::fromHex(magic_number);//ת��Ϊ16���Ʊ���
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			string magic_number_string(magic_number.constData(), magic_number.length());//QByteArrayתstring
			string interval_number_string(interval_number.constData(), interval_number.length());
			string interval_short_number_string(interval_short_number.constData(), interval_short_number.length());
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_7_NUMBER;//��������
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//��ͷ���������ֱ��
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//��ͷ���������ֱ��
			key_file_binary << magic_number_string;//д��ͷ��ħ������
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//����������ͣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write(key, FILE_KEY_AES_MIDDLE_KEY_LENGTH);//д����Կ
			key_file_binary << interval_number_string;//д��ָ���
			if (have_head_digit)//д��ͷ������������Ϣ
			{
				key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//д��ͷ����������
			}
			else
			{
				key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				key_file_binary << interval_short_number_string;//д����Ӧλ���ķָ���ռλ
			}
			key_file_binary << interval_number_string;//д��ָ���
			int file_name_length = file_name.length();//�ļ�������
			int file_path_length = file_path.length();//�ļ�·������
			key_file_binary.write((char*)(&file_name_length), sizeof(file_name_length));//����ļ������ȣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << file_name;//д���ļ���
			key_file_binary.write((char*)(&file_path_length), sizeof(file_path_length));//����ļ�·�����ȣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << file_path;//д���ļ�·��
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.close();
		}
		else
		{

		}
		emit lock_AES_MIDDLE_final(true, key);
	Delete_this_class_lock_AES_MIDDLE://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockSingle::unlock_AES_MIDDLE(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully)//AES-128���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�AES��Ҫ����Ż���н��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
	{

		//ע����Ϊ�ǶԳƼ��ܣ����Լӽ��ܷ�ʽ�ǳ��ӽ�
		char *source_file_data = new char[AES::BLOCKSIZE];//�������ļ�����
		char *target_file_data = new char[AES::BLOCKSIZE];//���ܺ��ļ�����
		unsigned char *xor_block = new unsigned char[AES::BLOCKSIZE];//�����趨Ϊȫ��
		memset(xor_block, 0, AES::BLOCKSIZE);//����
		AESDecryption decryption_AES_MIDDLE;//����AES������
		decryption_AES_MIDDLE.SetKey((unsigned char*)key, FILE_KEY_AES_MIDDLE_KEY_LENGTH);//����AES��Կ
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_AES_MIDDLE_final(false);
			goto Delete_this_class_unlock_AES_MIDDLE;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//ͷ����������У�顣��Ϊtellg()���ڶ�ȡ�ļ�֮ǰ��Ч������ȶ�ȡͷ���������ֻ���ɸú�����Ч
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ�ý�����Ϣȷ�Ͻ����ṩ��ͷ�����ֲ�����ת����ԭʼ������ʾ
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//תΪQString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//��������ļ�ͷ���������ֵ�char����
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ȡ�������֡�������Ҫע�⣬�����������Ϊȫ�ռ���00000000����ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char����
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			QString source_head_digit_transform_string = source_head_digit_transform;//תΪQString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//ͷ������������ͬ�����н���
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//ȥ��ͷ����������ռ�õĿռ�
				source_file.clear();//����ļ�������������޷���λ
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//���ļ�ָ��ƫ�Ƶ�ͷ����������֮��
			}
			else//ͷ���������ֲ�ͬ��ȡ������
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_AES_MIDDLE_final(false);
				goto Delete_this_class_unlock_AES_MIDDLE;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_AES_MIDDLE_final(false);
			goto Delete_this_class_unlock_AES_MIDDLE;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		long long total_count = source_file_size / AES::BLOCKSIZE;//�ܴ��������������������һ��
		long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, AES::BLOCKSIZE);//����AES::BLOCKSIZE���ֽ�
			decryption_AES_MIDDLE.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//����
			target_file.write(target_file_data, AES::BLOCKSIZE);//д��Ŀ���ļ�
			emit unlock_AES_MIDDLE_process((double)(AES::BLOCKSIZE*loop_count) / (double)source_file_size);//�����źŸ������������ʹ��
		}
		int source_file_size_remain = source_file_size - total_count * AES::BLOCKSIZE;//ʣ���ֽ���
		if (source_file_size_remain > 0)//�������ʣ������ݣ�Ҫ�������һ�δ���
		{
			if (is_decode_fully)
			{
				char *source_file_data_remain = new char[AES::BLOCKSIZE];
				char *target_file_data_remain = new char[AES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, AES::BLOCKSIZE);//��ʼ������Ϊ�������
				source_file.read(source_file_data_remain, AES::BLOCKSIZE);//����AES::BLOCKSIZE���ֽ�
				decryption_AES_MIDDLE.ProcessAndXorBlock((unsigned char*)source_file_data_remain, xor_block, (unsigned char*)target_file_data_remain);//����
				target_file.write(target_file_data_remain, AES::BLOCKSIZE);//д��Ŀ���ļ�
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//����ʣ�µ��ֽ�
				target_file.write(source_file_data_remain, source_file_size_remain);//д��Ŀ���ļ�
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_3_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit unlock_AES_MIDDLE_final(true);
	Delete_this_class_unlock_AES_MIDDLE://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockSingle::lock_AES_MAX(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully)//AES���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�AES��Ҫ����Ż���м��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
	{
		srand((int)time(NULL));//����������ӹ�֮��ʹ��
		char *source_file_data = new char[AES::BLOCKSIZE];//�������ļ�����
		char *target_file_data = new char[AES::BLOCKSIZE];//���ܺ��ļ�����
		unsigned char *xor_block = new unsigned char[AES::BLOCKSIZE];//�����趨Ϊȫ��
		memset(xor_block, 0, AES::BLOCKSIZE);//����
		AESEncryption encryption_AES_MAX;//����AES������
		set_key_AES_MAX(key);//����һ�������AES��Կ
		encryption_AES_MAX.SetKey((unsigned char*)key, AES::MAX_KEYLENGTH);//����AES��Կ
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_AES_MAX_final(false, key);
			goto Delete_this_class_lock_AES_MAX;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//�����������ͷ����������
		{
			target_file.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//����QByteArrayת��Ϊ16���Ʊ�����ַ����ĳ��ȼ���һ�룬��Ϊ����16������ֵ��ʾһ���ֽ�
		}
		else
		{

		}
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_AES_MAX_final(false, key);
			goto Delete_this_class_lock_AES_MAX;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		long long total_count = source_file_size / AES::BLOCKSIZE;//�ܴ��������������������һ��
		long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, AES::BLOCKSIZE);//����AES::BLOCKSIZE���ֽ�
			encryption_AES_MAX.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//����
			target_file.write(target_file_data, AES::BLOCKSIZE);//д��Ŀ���ļ�
			emit lock_AES_MAX_process((double)(AES::BLOCKSIZE*loop_count) / (double)source_file_size);//�����źŸ������������ʹ��
		}
		int source_file_size_remain = source_file_size - total_count * AES::BLOCKSIZE;//ʣ���ֽ���
		if (source_file_size_remain > 0)//�������ʣ������ݣ�Ҫ�������һ�δ���
		{
			if (is_encode_fully)
			{
				char *source_file_data_remain = new char[AES::BLOCKSIZE];
				char *target_file_data_remain = new char[AES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, AES::BLOCKSIZE);//��ʼ������Ϊ�������
				source_file.read(source_file_data_remain, AES::BLOCKSIZE);//����AES::BLOCKSIZE���ֽ�
				encryption_AES_MAX.ProcessAndXorBlock((unsigned char*)source_file_data_remain, xor_block, (unsigned char*)target_file_data_remain);//����
				target_file.write(target_file_data_remain, AES::BLOCKSIZE);//д��Ŀ���ļ�
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//����ʣ�µ��ֽ�
				target_file.write(source_file_data_remain, source_file_size_remain);//д��Ŀ���ļ�
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//�ͷ��ڴ�
		delete target_file_data;//�ͷ��ڴ�
		delete xor_block;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_2_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		if (is_output_key_file)//��Ҫ������Կ�ļ�
		{
			string key_file_total_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_path += file_name;//��Կ�ļ����·��
			key_file_total_path += key_file_path;
			ofstream key_file(key_file_total_path, ios_base::out);//�����ı����͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			key_file << FILE_KEY_WRITE_INFORMATION_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����Ӧ���ݡ�����Ϊ��Կ�ļ�ͷ������
			key_file << FILE_KEY_WRITE_INFORMATION_2_STRING << file_name << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//����ļ���
			key_file << FILE_KEY_WRITE_INFORMATION_3_STRING << file_path << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//����ļ�·��
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_6_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����������
			QByteArray key_transform(key, AES::MAX_KEYLENGTH * 2);//�����Կ
			key_transform = (key_transform.toHex()).toUpper();
			string key_string(key_transform.data(), AES::MAX_KEYLENGTH * 2);
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//���ͷ����������
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ��ͷ�����ֲ�����ת����ԭʼ������ʾ
				magic_number_transform = (magic_number_transform.toHex()).toUpper();
				string magic_number_string(magic_number_transform.data(), FILE_HEAD_RAW_NUMBER_SIZE_NUMBER);
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << magic_number_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			else
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			key_file.close();
		}
		else
		{

		}
		if (is_output_key_file_binary)//��Ҫ���ɶ�������Կ�ļ�
		{
			string key_file_total_binary_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_binary_path += file_name;//��Կ�ļ����·��
			key_file_total_binary_path += key_file_binary_path;
			ofstream key_file_binary(key_file_total_binary_path, ios_base::binary | ios_base::out);//������������͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			QByteArray magic_number = FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING;//�ȴ������ͷ��ħ������
			QByteArray interval_number = FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING;//�������ļ��ָ���
			QByteArray interval_short_number = FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING;//�������ļ��̷ָ���
			magic_number = QByteArray::fromHex(magic_number);//ת��Ϊ16���Ʊ���
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			string magic_number_string(magic_number.constData(), magic_number.length());//QByteArrayתstring
			string interval_number_string(interval_number.constData(), interval_number.length());
			string interval_short_number_string(interval_short_number.constData(), interval_short_number.length());
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_8_NUMBER;//��������
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//��ͷ���������ֱ��
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//��ͷ���������ֱ��
			key_file_binary << magic_number_string;//д��ͷ��ħ������
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//����������ͣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write(key, AES::MAX_KEYLENGTH);//д����Կ
			key_file_binary << interval_number_string;//д��ָ���
			if (have_head_digit)//д��ͷ������������Ϣ
			{
				key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//д��ͷ����������
			}
			else
			{
				key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				key_file_binary << interval_short_number_string;//д����Ӧλ���ķָ���ռλ
			}
			key_file_binary << interval_number_string;//д��ָ���
			int file_name_length = file_name.length();//�ļ�������
			int file_path_length = file_path.length();//�ļ�·������
			key_file_binary.write((char*)(&file_name_length), sizeof(file_name_length));//����ļ������ȣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << file_name;//д���ļ���
			key_file_binary.write((char*)(&file_path_length), sizeof(file_path_length));//����ļ�·�����ȣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary << file_path;//д���ļ�·��
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.close();
		}
		else
		{

		}
		emit lock_AES_MAX_final(true, key);
	Delete_this_class_lock_AES_MAX://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockSingle::unlock_AES_MAX(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully)//AES-128���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ���ͷ���������֣�ͷ���������֣��洢��Կ�������飬�Ƿ����ʣ�²���һ�����ܵ�λ�����ģ�AES��Ҫ����Ż���н��ܣ������Ļ����ܳ������ļ���ԭ���Ŀ��ܻ���ƫ�
	{

		//ע����Ϊ�ǶԳƼ��ܣ����Լӽ��ܷ�ʽ�ǳ��ӽ�
		char *source_file_data = new char[AES::BLOCKSIZE];//�������ļ�����
		char *target_file_data = new char[AES::BLOCKSIZE];//���ܺ��ļ�����
		unsigned char *xor_block = new unsigned char[AES::BLOCKSIZE];//�����趨Ϊȫ��
		memset(xor_block, 0, AES::BLOCKSIZE);//����
		AESDecryption decryption_AES_MAX;//����AES������
		decryption_AES_MAX.SetKey((unsigned char*)key, AES::MAX_KEYLENGTH);//����AES��Կ
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_AES_MAX_final(false);
			goto Delete_this_class_unlock_AES_MAX;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//ͷ����������У�顣��Ϊtellg()���ڶ�ȡ�ļ�֮ǰ��Ч������ȶ�ȡͷ���������ֻ���ɸú�����Ч
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ�ý�����Ϣȷ�Ͻ����ṩ��ͷ�����ֲ�����ת����ԭʼ������ʾ
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//תΪQString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//��������ļ�ͷ���������ֵ�char����
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ȡ�������֡�������Ҫע�⣬�����������Ϊȫ�ռ���00000000����ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char����
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			QString source_head_digit_transform_string = source_head_digit_transform;//תΪQString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//ͷ������������ͬ�����н���
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//ȥ��ͷ����������ռ�õĿռ�
				source_file.clear();//����ļ�������������޷���λ
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//���ļ�ָ��ƫ�Ƶ�ͷ����������֮��
			}
			else//ͷ���������ֲ�ͬ��ȡ������
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_AES_MAX_final(false);
				goto Delete_this_class_unlock_AES_MAX;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_AES_MAX_final(false);
			goto Delete_this_class_unlock_AES_MAX;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		long long total_count = source_file_size / AES::BLOCKSIZE;//�ܴ��������������������һ��
		long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, AES::BLOCKSIZE);//����AES::BLOCKSIZE���ֽ�
			decryption_AES_MAX.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//����
			target_file.write(target_file_data, AES::BLOCKSIZE);//д��Ŀ���ļ�
			emit unlock_AES_MAX_process((double)(AES::BLOCKSIZE*loop_count) / (double)source_file_size);//�����źŸ������������ʹ��
		}
		int source_file_size_remain = source_file_size - total_count * AES::BLOCKSIZE;//ʣ���ֽ���
		if (source_file_size_remain > 0)//�������ʣ������ݣ�Ҫ�������һ�δ���
		{
			if (is_decode_fully)
			{
				char *source_file_data_remain = new char[AES::BLOCKSIZE];
				char *target_file_data_remain = new char[AES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, AES::BLOCKSIZE);//��ʼ������Ϊ�������
				source_file.read(source_file_data_remain, AES::BLOCKSIZE);//����AES::BLOCKSIZE���ֽ�
				decryption_AES_MAX.ProcessAndXorBlock((unsigned char*)source_file_data_remain, xor_block, (unsigned char*)target_file_data_remain);//����
				target_file.write(target_file_data_remain, AES::BLOCKSIZE);//д��Ŀ���ļ�
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//����ʣ�µ��ֽ�
				target_file.write(source_file_data_remain, source_file_size_remain);//д��Ŀ���ļ�
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_3_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit unlock_AES_MAX_final(true);
	Delete_this_class_unlock_AES_MAX://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockDouble::lock_RSA(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *public_key, int size)//RSA���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ���ͷ���������֣�ͷ���������֣���Կ����Կ��С
	{
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		string target_file_data_string;//����֮��õ������ĵ�ʮ�����ƽ�����
		string target_file_path = file_output_front_path;
		string source_file_data_string;
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		AutoSeededRandomPool pool;
		QByteArray public_key_hex_string(public_key, size / 2);//����Կת��ΪQBytearray
		public_key_hex_string = public_key_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
		RSAES_OAEP_SHA_Encryptor encryptor;//������
		RSA::PublicKey rsa_public_key;
		string rsa_public_key_string = (string((const char *)((QString)public_key_hex_string).toLocal8Bit()));
		HexDecoder decoder;
		try
		{
			decoder.Put((byte*)rsa_public_key_string.c_str(), size);
			encryptor.AccessKey().Load(decoder);
		}
		catch (BERDecodeErr eBERDecodeErr)//��������Կ�������޷�������쳣
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_RSA_wrong_key();
			goto Delete_this_class_lock_RSA;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_RSA_final(false);
			goto Delete_this_class_lock_RSA;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//�����������ͷ����������
		{
			target_file.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//����QByteArrayת��Ϊ16���Ʊ�����ַ����ĳ��ȼ���һ�룬��Ϊ����16������ֵ��ʾһ���ֽ�
		}
		else
		{

		}
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_RSA_final(false);
			goto Delete_this_class_lock_RSA;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		char *source_file_data = new char[source_file_size];//�������ļ�����
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		source_file.read(source_file_data, source_file_size);//����source_file_size���ֽ�
		source_file_data_string = source_file_data;//crypto++�⼫�����أ����ʹ��char*������޷�ʶ��\0���ַ�����������ҽ��ܳ��������ݻ�����в����������ݣ�����ʹ�������resize()��stringȴû�����⣬��ƽʱʹ�õ�����е㲻һ���������²����������������ת��������
		source_file_data_string.resize(source_file_size);
		try
		{
			StringSink *temp_stringsink = new StringSink(target_file_data_string);
			HexEncoder *temp_hexencorder = new HexEncoder(temp_stringsink);
			PK_EncryptorFilter *temp_encryptorfilter = new PK_EncryptorFilter(pool, encryptor, temp_hexencorder);
			StringSource(source_file_data_string, true, temp_encryptorfilter);
			QByteArray file_hex_bytearray(target_file_data_string.c_str(), target_file_data_string.length());//���ܳ�����������ʮ����������ı���ʽ�����뽫��ת��ԭʼ��ʮ��������
			delete temp_stringsink;
			delete temp_hexencorder;
			delete temp_encryptorfilter;
			file_hex_bytearray = QByteArray::fromHex(file_hex_bytearray);//���ʮ���������ݣ�ת��Ϊ��д
			target_file.write(file_hex_bytearray.data(), file_hex_bytearray.length());//д��Ŀ���ļ�
		}
		catch (InvalidArgument eInvalidArgument)//��������Կ���ȹ��̻���ԭ�ĳ��ȹ���������쳣
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_RSA_out_of_range();
			goto Delete_this_class_lock_RSA;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		delete source_file_data;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_2_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit lock_RSA_final(true);
	Delete_this_class_lock_RSA://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockDouble::unlock_RSA(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *private_key, int size)//RSA���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ���ͷ���������֣�ͷ���������֣�˽Կ����Կ��С
	{

		//��������ʱ����Գ�����crypto++�������ʹ�������ϱ����Ĳ�һ�������ܡ���������StringSource()�У�ԭʼ�ַ������Բ���ʹ��char*������������л���ּ���ʱ�޷�ʶ��\0��������ʱ�ḽ��һЩ�������ݣ�ԭ��������Ȼchar*����涨�˳��ȣ����������ã����������ط���Ӧ��ʹ��string���ͣ�Ϊ���������ʹ��resize()���¹̶����ȣ��������ܳ��������ݺ�ԭ����ȫһ����Ҳ������ܹ��������С�\0�����ļ������纬�д�����\0����exe�ļ���
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		string target_file_data_string;
		string target_file_path = file_output_front_path;
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		AutoSeededRandomPool pool;
		QByteArray private_key_hex_string(private_key, size / 2);//����Կת��ΪQBytearray
		private_key_hex_string = private_key_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
		RSAES_OAEP_SHA_Decryptor decryptor;//������
		RSA::PrivateKey rsa_private_key;
		string rsa_private_key_string = (string((const char *)((QString)private_key_hex_string).toLocal8Bit()));
		HexDecoder decoder;
		try
		{
			decoder.Put((byte*)rsa_private_key_string.c_str(), size);
			decryptor.AccessKey().Load(decoder);
		}
		catch (BERDecodeErr eBERDecodeErr)//��������Կ�������޷�������쳣
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_RSA_wrong_key();
			goto Delete_this_class_unlock_RSA;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_RSA_final(false);
			goto Delete_this_class_unlock_RSA;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		long long source_file_size;//�ļ���������Ҫ������ֽ�
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		if (have_head_digit)//ͷ����������У�顣��Ϊtellg()���ڶ�ȡ�ļ�֮ǰ��Ч������ȶ�ȡͷ���������ֻ���ɸú�����Ч
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ�ý�����Ϣȷ�Ͻ����ṩ��ͷ�����ֲ�����ת����ԭʼ������ʾ
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//תΪQString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//��������ļ�ͷ���������ֵ�char����
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ȡ�������֡�������Ҫע�⣬�����������Ϊȫ�ռ���00000000����ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char����
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			QString source_head_digit_transform_string = source_head_digit_transform;//תΪQString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//ͷ������������ͬ�����н���
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//ȥ��ͷ����������ռ�õĿռ�
				source_file.clear();//����ļ�������������޷���λ
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//���ļ�ָ��ƫ�Ƶ�ͷ����������֮��
			}
			else//ͷ���������ֲ�ͬ��ȡ������
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_RSA_final(false);
				goto Delete_this_class_unlock_RSA;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_RSA_final(false);
			goto Delete_this_class_unlock_RSA;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		char *source_file_data = new char[source_file_size];//�������ļ�����
		source_file.read(source_file_data, source_file_size);//����source_file_size���ֽ�
		try//֮ǰ˵��crypto++�������أ����������ʹ��string������ʻ���ֽ���ʧ�ܵ�����������쳣�������ĳ��ȳ������ǲ���ʶ��\0���ַ������⣬��������ǣ���ʱ�������ʶ����������ĳ��Ⱦ�Ȼ��ʵ�ʳ��Ȼ���Ŀǰԭ�������²���char*תbyte*�Ĺ����г�����һЩ����
		{
			QByteArray source_file_hex_bytearray(source_file_data, source_file_size);//��ԭ��ת��ΪQBytearray
			source_file_hex_bytearray = source_file_hex_bytearray.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			string source_file_data_string = source_file_hex_bytearray.data();
			source_file_data_string.resize(source_file_size * 2);
			StringSource(source_file_data_string, true, new HexDecoder(new PK_DecryptorFilter(pool, decryptor, new StringSink(target_file_data_string))));
		}
		catch (InvalidArgument eInvalidArgument)//��������Կ���ȹ��̻���ԭ�ĳ��ȹ���������쳣
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_RSA_out_of_range();
			goto Delete_this_class_unlock_RSA;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		catch (InvalidCiphertext eInvalidCiphertext)//���Ĵ����쳣
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_RSA_out_of_range();
			goto Delete_this_class_unlock_RSA;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		catch (Exception eException)//��Կ����
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_RSA_wrong_key();
			goto Delete_this_class_unlock_RSA;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		target_file.write(target_file_data_string.c_str(), target_file_data_string.length());//д��Ŀ���ļ�
		delete source_file_data;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_3_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit unlock_RSA_final(true);
	Delete_this_class_unlock_RSA://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockDouble::lock_ECC(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *public_key, int size)//RSA���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ���ͷ���������֣�ͷ���������֣���Կ����Կ��С
	{
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		string target_file_data_string;//����֮��õ������ĵ�ʮ�����ƽ�����
		string target_file_path = file_output_front_path;
		string source_file_data_string;
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		AutoSeededRandomPool pool;
		QByteArray public_key_hex_string(public_key, size / 2);//����Կת��ΪQBytearray
		public_key_hex_string = public_key_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
		ECIES<ECP>::Encryptor encryptor;//������
		ECIES<ECP>::PublicKey rsa_public_key;
		string rsa_public_key_string = (string((const char *)((QString)public_key_hex_string).toLocal8Bit()));
		HexDecoder decoder;
		try
		{
			decoder.Put((byte*)rsa_public_key_string.c_str(), size);
			encryptor.AccessKey().Load(decoder);
		}
		catch (BERDecodeErr eBERDecodeErr)//��������Կ�������޷�������쳣
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_ECC_wrong_key();
			goto Delete_this_class_lock_ECC;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_ECC_final(false);
			goto Delete_this_class_lock_ECC;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//�����������ͷ����������
		{
			target_file.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//����QByteArrayת��Ϊ16���Ʊ�����ַ����ĳ��ȼ���һ�룬��Ϊ����16������ֵ��ʾһ���ֽ�
		}
		else
		{

		}
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_ECC_final(false);
			goto Delete_this_class_lock_ECC;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		char *source_file_data = new char[source_file_size];//�������ļ�����
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		source_file.read(source_file_data, source_file_size);//����source_file_size���ֽ�
		source_file_data_string = source_file_data;//crypto++�⼫�����أ����ʹ��char*������޷�ʶ��\0���ַ�����������ҽ��ܳ��������ݻ�����в����������ݣ�����ʹ�������resize()��stringȴû�����⣬��ƽʱʹ�õ�����е㲻һ���������²����������������ת��������
		source_file_data_string.resize(source_file_size);
		try
		{
			StringSource(source_file_data_string, true, new PK_EncryptorFilter(pool, encryptor, new HexEncoder(new StringSink(target_file_data_string))));
			QByteArray file_hex_bytearray(target_file_data_string.c_str(), target_file_data_string.length());//���ܳ�����������ʮ����������ı���ʽ�����뽫��ת��ԭʼ��ʮ��������
			file_hex_bytearray = QByteArray::fromHex(file_hex_bytearray);//���ʮ���������ݣ�ת��Ϊ��д
			target_file.write(file_hex_bytearray.data(), file_hex_bytearray.length());//д��Ŀ���ļ�
		}
		catch (InvalidArgument eInvalidArgument)//��������Կ���ȹ��̻���ԭ�ĳ��ȹ���������쳣
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_ECC_out_of_range();
			goto Delete_this_class_lock_ECC;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		delete source_file_data;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_2_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit lock_ECC_final(true);
	Delete_this_class_lock_ECC://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockDouble::unlock_ECC(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *private_key, int size)//ECC���ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ���ͷ���������֣�ͷ���������֣�˽Կ����Կ��С
	{

		//��������ʱ����Գ�����crypto++�������ʹ�������ϱ����Ĳ�һ�������ܡ���������StringSource()�У�ԭʼ�ַ������Բ���ʹ��char*������������л���ּ���ʱ�޷�ʶ��\0��������ʱ�ḽ��һЩ�������ݣ�ԭ��������Ȼchar*����涨�˳��ȣ����������ã����������ط���Ӧ��ʹ��string���ͣ�Ϊ���������ʹ��resize()���¹̶����ȣ��������ܳ��������ݺ�ԭ����ȫһ����Ҳ������ܹ��������С�\0�����ļ������纬�д�����\0����exe�ļ���
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		string target_file_data_string;
		string target_file_path = file_output_front_path;
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		AutoSeededRandomPool pool;
		QByteArray private_key_hex_string(private_key, size / 2);//����Կת��ΪQBytearray
		private_key_hex_string = private_key_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
		ECIES<ECP>::Decryptor decryptor;//������
		ECIES<ECP>::PrivateKey rsa_private_key;
		string rsa_private_key_string = (string((const char *)((QString)private_key_hex_string).toLocal8Bit()));
		HexDecoder decoder;
		try
		{
			decoder.Put((byte*)rsa_private_key_string.c_str(), size);
			decryptor.AccessKey().Load(decoder);
		}
		catch (BERDecodeErr eBERDecodeErr)//��������Կ�������޷�������쳣
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_ECC_wrong_key();
			goto Delete_this_class_unlock_ECC;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_ECC_final(false);
			goto Delete_this_class_unlock_ECC;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		long long source_file_size;//�ļ���������Ҫ������ֽ�
		source_file_size = source_file.tellg();//ȥ��ͷ����������β�������յ�ռ�õ�λ��
		source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
		if (have_head_digit)//ͷ����������У�顣��Ϊtellg()���ڶ�ȡ�ļ�֮ǰ��Ч������ȶ�ȡͷ���������ֻ���ɸú�����Ч
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ�ý�����Ϣȷ�Ͻ����ṩ��ͷ�����ֲ�����ת����ԭʼ������ʾ
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//תΪQString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//��������ļ�ͷ���������ֵ�char����
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ȡ�������֡�������Ҫע�⣬�����������Ϊȫ�ռ���00000000����ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char����
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			QString source_head_digit_transform_string = source_head_digit_transform;//תΪQString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//ͷ������������ͬ�����н���
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//ȥ��ͷ����������ռ�õĿռ�
				source_file.clear();//����ļ�������������޷���λ
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//���ļ�ָ��ƫ�Ƶ�ͷ����������֮��
			}
			else//ͷ���������ֲ�ͬ��ȡ������
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_ECC_final(false);
				goto Delete_this_class_unlock_ECC;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_RSA_final(false);
			goto Delete_this_class_unlock_ECC;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		char *source_file_data = new char[source_file_size];//�������ļ�����
		source_file.read(source_file_data, source_file_size);//����source_file_size���ֽ�
		try//֮ǰ˵��crypto++�������أ����������ʹ��string������ʻ���ֽ���ʧ�ܵ�����������쳣�������ĳ��ȳ������ǲ���ʶ��\0���ַ������⣬��������ǣ���ʱ�������ʶ����������ĳ��Ⱦ�Ȼ��ʵ�ʳ��Ȼ���Ŀǰԭ�������²���char*תbyte*�Ĺ����г�����һЩ����
		{
			QByteArray source_file_hex_bytearray(source_file_data, source_file_size);//��ԭ��ת��ΪQBytearray
			source_file_hex_bytearray = source_file_hex_bytearray.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			string source_file_data_string = source_file_hex_bytearray.data();
			source_file_data_string.resize(source_file_size * 2);
			StringSource(source_file_data_string, true, new HexDecoder(new PK_DecryptorFilter(pool, decryptor, new StringSink(target_file_data_string))));
		}
		catch (InvalidArgument eInvalidArgument)//��������Կ���ȹ��̻���ԭ�ĳ��ȹ���������쳣
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_ECC_out_of_range();
			goto Delete_this_class_unlock_ECC;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		catch (InvalidCiphertext eInvalidCiphertext)//���Ĵ����쳣
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_ECC_out_of_range();
			goto Delete_this_class_unlock_ECC;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		catch (Exception eException)//��Կ����
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_ECC_wrong_key();
			goto Delete_this_class_unlock_ECC;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		target_file.write(target_file_data_string.c_str(), target_file_data_string.length());//д��Ŀ���ļ�
		delete source_file_data;//�ͷ��ڴ�
		source_file.close();
		target_file.close();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_3_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit unlock_ECC_final(true);
	Delete_this_class_unlock_ECC://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void HashCalculate::hash_calculate_MD4(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path)//MD4���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·��
	{
		string result_string;
		MD4 md4;
		FileSource(file_path.c_str(), true, new HashFilter(md4, new HexEncoder(new StringSink(result_string))));
		memmove(result, result_string.c_str(), result_string.length());
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_5_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit hash_calculate_MD4_final(result_string.length());
		delete this;
	}

	void HashCalculate::hash_calculate_MD5(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path)//MD4���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·��
	{
		string result_string;
		MD5 md5;
		FileSource(file_path.c_str(), true, new HashFilter(md5, new HexEncoder(new StringSink(result_string))));
		memmove(result, result_string.c_str(), result_string.length());
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_5_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit hash_calculate_MD5_final(result_string.length());
		delete this;
	}

	void HashCalculate::hash_calculate_SHA1(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path)//SHA1���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·��
	{
		string result_string;
		SHA1 sha1;
		FileSource(file_path.c_str(), true, new HashFilter(sha1, new HexEncoder(new StringSink(result_string))));
		memmove(result, result_string.c_str(), result_string.length());
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_5_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit hash_calculate_SHA1_final(result_string.length());
		delete this;
	}

	void HashCalculate::hash_calculate_SHA2(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type)//SHA2���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·������������
	{
		string result_string;
		if (calculate_type == "224")
		{
			SHA224 sha2;
			FileSource(file_path.c_str(), true, new HashFilter(sha2, new HexEncoder(new StringSink(result_string))));
		}
		else if (calculate_type == "256")
		{
			SHA256 sha2;
			FileSource(file_path.c_str(), true, new HashFilter(sha2, new HexEncoder(new StringSink(result_string))));
		}
		else if (calculate_type == "384")
		{
			SHA384 sha2;
			FileSource(file_path.c_str(), true, new HashFilter(sha2, new HexEncoder(new StringSink(result_string))));
		}
		else if (calculate_type == "512")
		{
			SHA512 sha2;
			FileSource(file_path.c_str(), true, new HashFilter(sha2, new HexEncoder(new StringSink(result_string))));
		}
		else
		{

		}
		memmove(result, result_string.c_str(), result_string.length());
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_5_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit hash_calculate_SHA2_final(result_string.length());
		delete this;
	}

	void HashCalculate::hash_calculate_SHA3(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type)//SHA2���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·������������
	{
		string result_string;
		if (calculate_type == "224")
		{
			SHA3_224 sha3;
			FileSource(file_path.c_str(), true, new HashFilter(sha3, new HexEncoder(new StringSink(result_string))));
		}
		else if (calculate_type == "256")
		{
			SHA3_256 sha3;
			FileSource(file_path.c_str(), true, new HashFilter(sha3, new HexEncoder(new StringSink(result_string))));
		}
		else if (calculate_type == "384")
		{
			SHA3_384 sha3;
			FileSource(file_path.c_str(), true, new HashFilter(sha3, new HexEncoder(new StringSink(result_string))));
		}
		else if (calculate_type == "512")
		{
			SHA3_512 sha3;
			FileSource(file_path.c_str(), true, new HashFilter(sha3, new HexEncoder(new StringSink(result_string))));
		}
		else
		{

		}
		memmove(result, result_string.c_str(), result_string.length());
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_5_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit hash_calculate_SHA3_final(result_string.length());
		delete this;
	}

	void HashCalculate::hash_calculate_Keccak(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type)//SHA2���㡣����������ļ�·�����ļ���������洢��Ԫ���Ƿ������ʷ�ļ��������ʷ�ļ�·������������
	{
		string result_string;
		if (calculate_type == "224")
		{
			Keccak_224 keccak;
			FileSource(file_path.c_str(), true, new HashFilter(keccak, new HexEncoder(new StringSink(result_string))));
		}
		else if (calculate_type == "256")
		{
			Keccak_256 keccak;
			FileSource(file_path.c_str(), true, new HashFilter(keccak, new HexEncoder(new StringSink(result_string))));
		}
		else if (calculate_type == "384")
		{
			Keccak_384 keccak;
			FileSource(file_path.c_str(), true, new HashFilter(keccak, new HexEncoder(new StringSink(result_string))));
		}
		else if (calculate_type == "512")
		{
			Keccak_512 keccak;
			FileSource(file_path.c_str(), true, new HashFilter(keccak, new HexEncoder(new StringSink(result_string))));
		}
		else
		{

		}
		memmove(result, result_string.c_str(), result_string.length());
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ���
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ļ�·��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_5_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		emit hash_calculate_Keccak_final(result_string.length());
		delete this;
	}

	//�ڲ�ʹ�õĺ���
	void LockSingle::set_key_DES(char *key)//�������DES��Կ������Ϊ�洢��Կ������
	{
		//��ΪDES����Կ���ȣ���ö��DES::DEFAULT_KEYLENGTH��ʾ��ʵ����Ϊ8�ֽڣ����ÿ4λ������1�������ʮ�������룬Ȼ������ɵ�ʮ��������ת��Ϊ��Կ����
		QByteArray key_bytearray;//�洢��Կ
		int randnumber;//�����
		for (int index = 0; index < DES::DEFAULT_KEYLENGTH * 2; index++)//ע��ÿ���ֽ���2��ʮ�������빹��
		{
			randnumber = FILE_KEY_RANDOM_HEX_MIN_NUMBER + rand() % (FILE_KEY_RANDOM_HEX_MAX_NUMBER - FILE_KEY_RANDOM_HEX_MIN_NUMBER + 1);//���������
			if (randnumber >= 0 &&randnumber <= 9)
			{
				key_bytearray[index] = (char)(randnumber + (int)FILE_KEY_RANDOM_HEX_0_STRING);//��ע�⣬ֱ�ӽ�intת��Ϊchar�õ���char��ֵ����ԭ����int��ֵ���޷�ʹ�ã���Ҫת��ΪASCII���Ӧ����ֵ
			}
			else
			{
				switch (randnumber)
				{
				case 10:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_10_STRING;
					break;
				}
				case 11:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_11_STRING;
					break;
				}
				case 12:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_12_STRING;
					break;
				}
				case 13:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_13_STRING;
					break;
				}
				case 14:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_14_STRING;
					break;
				}
				default:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_15_STRING;
					break;
				}
				}
			}
		}
		key_bytearray = QByteArray::fromHex(key_bytearray);//ת��16���Ʊ���Ϊ����
		memmove(key, key_bytearray.data(), DES::DEFAULT_KEYLENGTH);//���õ�����Կת��Ϊchar*��Ϊ���
	}

	void LockSingle::set_key_DES_EDE2(char *key)//�������DES_EDE2��Կ������Ϊ�洢��Կ������
	{
		//��ΪDES-EDE2����Կ���ȣ���ö��DES_EDE2::DEFAULT_KEYLENGTH��ʾ��ʵ����Ϊ16�ֽڣ����ÿ4λ������1�������ʮ�������룬Ȼ������ɵ�ʮ��������ת��Ϊ��Կ����
		QByteArray key_bytearray;//�洢��Կ
		int randnumber;//�����
		for (int index = 0; index < DES_EDE2::DEFAULT_KEYLENGTH * 2; index++)//ע��ÿ���ֽ���2��ʮ�������빹��
		{
			randnumber = FILE_KEY_RANDOM_HEX_MIN_NUMBER + rand() % (FILE_KEY_RANDOM_HEX_MAX_NUMBER - FILE_KEY_RANDOM_HEX_MIN_NUMBER + 1);//���������
			if (randnumber >= 0 &&randnumber <= 9)
			{
				key_bytearray[index] = (char)(randnumber + (int)FILE_KEY_RANDOM_HEX_0_STRING);//��ע�⣬ֱ�ӽ�intת��Ϊchar�õ���char��ֵ����ԭ����int��ֵ���޷�ʹ�ã���Ҫת��ΪASCII���Ӧ����ֵ
			}
			else
			{
				switch (randnumber)
				{
				case 10:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_10_STRING;
					break;
				}
				case 11:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_11_STRING;
					break;
				}
				case 12:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_12_STRING;
					break;
				}
				case 13:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_13_STRING;
					break;
				}
				case 14:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_14_STRING;
					break;
				}
				default:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_15_STRING;
					break;
				}
				}
			}
		}
		key_bytearray = QByteArray::fromHex(key_bytearray);//ת��16���Ʊ���Ϊ����
		memmove(key, key_bytearray.data(), DES_EDE2::DEFAULT_KEYLENGTH);//���õ�����Կת��Ϊchar*��Ϊ���
	}

	void LockSingle::set_key_DES_EDE3(char *key)//�������DES_EDE2��Կ������Ϊ�洢��Կ������
	{
		//��ΪDES-EDE3����Կ���ȣ���ö��DES_EDE3::DEFAULT_KEYLENGTH��ʾ��ʵ����Ϊ24�ֽڣ����ÿ4λ������1�������ʮ�������룬Ȼ������ɵ�ʮ��������ת��Ϊ��Կ����
		QByteArray key_bytearray;//�洢��Կ
		int randnumber;//�����
		for (int index = 0; index < DES_EDE3::DEFAULT_KEYLENGTH * 2; index++)//ע��ÿ���ֽ���2��ʮ�������빹��
		{
			randnumber = FILE_KEY_RANDOM_HEX_MIN_NUMBER + rand() % (FILE_KEY_RANDOM_HEX_MAX_NUMBER - FILE_KEY_RANDOM_HEX_MIN_NUMBER + 1);//���������
			if (randnumber >= 0 &&randnumber <= 9)
			{
				key_bytearray[index] = (char)(randnumber + (int)FILE_KEY_RANDOM_HEX_0_STRING);//��ע�⣬ֱ�ӽ�intת��Ϊchar�õ���char��ֵ����ԭ����int��ֵ���޷�ʹ�ã���Ҫת��ΪASCII���Ӧ����ֵ
			}
			else
			{
				switch (randnumber)
				{
				case 10:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_10_STRING;
					break;
				}
				case 11:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_11_STRING;
					break;
				}
				case 12:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_12_STRING;
					break;
				}
				case 13:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_13_STRING;
					break;
				}
				case 14:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_14_STRING;
					break;
				}
				default:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_15_STRING;
					break;
				}
				}
			}
		}
		key_bytearray = QByteArray::fromHex(key_bytearray);//ת��16���Ʊ���Ϊ����
		memmove(key, key_bytearray.data(), DES_EDE3::DEFAULT_KEYLENGTH);//���õ�����Կת��Ϊchar*��Ϊ���
	}

	void LockSingle::set_key_AES_MIN(char *key)//�������AES-128��Կ������Ϊ�洢��Կ������
	{
		//��ΪAES-128����Կ���ȣ���ö��AES::MIN_KEYLENGTH��ʾ��ʵ����Ϊ16�ֽڣ����ÿ4λ������1�������ʮ�������룬Ȼ������ɵ�ʮ��������ת��Ϊ��Կ����
		QByteArray key_bytearray;//�洢��Կ
		int randnumber;//�����
		for (int index = 0; index < AES::MIN_KEYLENGTH * 2; index++)//ע��ÿ���ֽ���2��ʮ�������빹��
		{
			randnumber = FILE_KEY_RANDOM_HEX_MIN_NUMBER + rand() % (FILE_KEY_RANDOM_HEX_MAX_NUMBER - FILE_KEY_RANDOM_HEX_MIN_NUMBER + 1);//���������
			if (randnumber >= 0 &&randnumber <= 9)
			{
				key_bytearray[index] = (char)(randnumber + (int)FILE_KEY_RANDOM_HEX_0_STRING);//��ע�⣬ֱ�ӽ�intת��Ϊchar�õ���char��ֵ����ԭ����int��ֵ���޷�ʹ�ã���Ҫת��ΪASCII���Ӧ����ֵ
			}
			else
			{
				switch (randnumber)
				{
				case 10:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_10_STRING;
					break;
				}
				case 11:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_11_STRING;
					break;
				}
				case 12:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_12_STRING;
					break;
				}
				case 13:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_13_STRING;
					break;
				}
				case 14:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_14_STRING;
					break;
				}
				default:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_15_STRING;
					break;
				}
				}
			}
		}
		key_bytearray = QByteArray::fromHex(key_bytearray);//ת��16���Ʊ���Ϊ����
		memmove(key, key_bytearray.data(), AES::MIN_KEYLENGTH);//���õ�����Կת��Ϊchar*��Ϊ���
	}

	void LockSingle::set_key_AES_MIDDLE(char *key)//�������AES-192��Կ������Ϊ�洢��Կ������
	{
		//��ΪAES-192����Կ���ȣ���ö��AES::MIN_KEYLENGTH��ʾ��ʵ����Ϊ24�ֽڣ����ÿ4λ������1�������ʮ�������룬Ȼ������ɵ�ʮ��������ת��Ϊ��Կ����
		QByteArray key_bytearray;//�洢��Կ
		int randnumber;//�����
		for (int index = 0; index < FILE_KEY_AES_MIDDLE_KEY_LENGTH * 2; index++)//ע��ÿ���ֽ���2��ʮ�������빹��
		{
			randnumber = FILE_KEY_RANDOM_HEX_MIN_NUMBER + rand() % (FILE_KEY_RANDOM_HEX_MAX_NUMBER - FILE_KEY_RANDOM_HEX_MIN_NUMBER + 1);//���������
			if (randnumber >= 0 &&randnumber <= 9)
			{
				key_bytearray[index] = (char)(randnumber + (int)FILE_KEY_RANDOM_HEX_0_STRING);//��ע�⣬ֱ�ӽ�intת��Ϊchar�õ���char��ֵ����ԭ����int��ֵ���޷�ʹ�ã���Ҫת��ΪASCII���Ӧ����ֵ
			}
			else
			{
				switch (randnumber)
				{
				case 10:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_10_STRING;
					break;
				}
				case 11:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_11_STRING;
					break;
				}
				case 12:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_12_STRING;
					break;
				}
				case 13:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_13_STRING;
					break;
				}
				case 14:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_14_STRING;
					break;
				}
				default:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_15_STRING;
					break;
				}
				}
			}
		}
		key_bytearray = QByteArray::fromHex(key_bytearray);//ת��16���Ʊ���Ϊ����
		memmove(key, key_bytearray.data(), FILE_KEY_AES_MIDDLE_KEY_LENGTH);//���õ�����Կת��Ϊchar*��Ϊ���
	}

	void LockSingle::set_key_AES_MAX(char *key)//�������AES-256��Կ������Ϊ�洢��Կ������
	{
		//��ΪAES-256����Կ���ȣ���ö��AES::MIN_KEYLENGTH��ʾ��ʵ����Ϊ32�ֽڣ����ÿ4λ������1�������ʮ�������룬Ȼ������ɵ�ʮ��������ת��Ϊ��Կ����
		QByteArray key_bytearray;//�洢��Կ
		int randnumber;//�����
		for (int index = 0; index < AES::MAX_KEYLENGTH * 2; index++)//ע��ÿ���ֽ���2��ʮ�������빹��
		{
			randnumber = FILE_KEY_RANDOM_HEX_MIN_NUMBER + rand() % (FILE_KEY_RANDOM_HEX_MAX_NUMBER - FILE_KEY_RANDOM_HEX_MIN_NUMBER + 1);//���������
			if (randnumber >= 0 &&randnumber <= 9)
			{
				key_bytearray[index] = (char)(randnumber + (int)FILE_KEY_RANDOM_HEX_0_STRING);//��ע�⣬ֱ�ӽ�intת��Ϊchar�õ���char��ֵ����ԭ����int��ֵ���޷�ʹ�ã���Ҫת��ΪASCII���Ӧ����ֵ
			}
			else
			{
				switch (randnumber)
				{
				case 10:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_10_STRING;
					break;
				}
				case 11:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_11_STRING;
					break;
				}
				case 12:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_12_STRING;
					break;
				}
				case 13:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_13_STRING;
					break;
				}
				case 14:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_14_STRING;
					break;
				}
				default:
				{
					key_bytearray[index] = FILE_KEY_RANDOM_HEX_15_STRING;
					break;
				}
				}
			}
		}
		key_bytearray = QByteArray::fromHex(key_bytearray);//ת��16���Ʊ���Ϊ����
		memmove(key, key_bytearray.data(), AES::MAX_KEYLENGTH);//���õ�����Կת��Ϊchar*��Ϊ���
	}

	//�ǶԳƼ�����Կ����
	void LockDouble::set_key_RSA(char *public_key, char *private_key, int size, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, const string &output_path)//RSA��Կ���ɡ������������Կ�洢��Ԫ��˽Կ�洢��Ԫ����Կ���ȣ��Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·�����Ƿ���ͷ���������֣�ͷ���������֣���Կ�ļ�����·��
	{
		AutoSeededRandomPool randompool;
		InvertibleRSAFunction rsa_function;
		rsa_function.GenerateRandomWithKeySize(randompool, size);
		RSA::PrivateKey rsa_private_key(rsa_function);//˽Կ
		RSA::PublicKey rsa_public_key(rsa_function);//��Կ
		string rsa_private_key_string;//����Կ���浽ָ��λ��
		string rsa_public_key_string;
		HexEncoder public_key_encoder(new StringSink(rsa_public_key_string));//����Կת��Ϊ�ַ��������
		rsa_public_key.DEREncode(public_key_encoder);
		public_key_encoder.MessageEnd();
		HexEncoder private_key_encoder(new StringSink(rsa_private_key_string));
		rsa_private_key.DEREncode(private_key_encoder);
		private_key_encoder.MessageEnd();
		int public_key_length = rsa_public_key_string.length();//��Կ����
		int private_key_length = rsa_private_key_string.length();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_4_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		if (is_output_key_file)//��Ҫ������Կ�ļ�
		{
			ofstream key_file(output_path + key_file_path, ios_base::out);//�����ı����͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			key_file << FILE_KEY_WRITE_INFORMATION_1_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����Ӧ���ݡ�����Ϊ��Կ�ļ�ͷ������
			key_file << FILE_KEY_WRITE_INFORMATION_3_STRING << output_path << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//����ļ�·��
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_7_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����������
			key_file << FILE_KEY_WRITE_INFORMATION_6_1_STRING << rsa_public_key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			key_file << FILE_KEY_WRITE_INFORMATION_6_2_STRING << rsa_private_key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//���ͷ����������
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ��ͷ�����ֲ�����ת����ԭʼ������ʾ
				magic_number_transform = (magic_number_transform.toHex()).toUpper();
				string magic_number_string(magic_number_transform.data(), FILE_HEAD_RAW_NUMBER_SIZE_NUMBER);
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << magic_number_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			else
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			key_file.close();
		}
		else
		{

		}
		QByteArray public_key_bytearray((char*)rsa_public_key_string.c_str(), public_key_length);//ת��ΪQByteArray
		public_key_bytearray = QByteArray::fromHex(public_key_bytearray);//ת��Ϊ16���Ʊ���
		memmove(public_key, public_key_bytearray.data(), public_key_length / 2);//ֱ�Ӹ����ڴ档ע��ת������󳤶Ȼ����һ��
		QByteArray private_key_bytearray((char*)rsa_private_key_string.c_str(), private_key_length);//ת��ΪQByteArray
		private_key_bytearray = QByteArray::fromHex(private_key_bytearray);//ת��Ϊ16���Ʊ���
		memmove(private_key, private_key_bytearray.data(), private_key_length / 2);//ֱ�Ӹ����ڴ档ע��ת������󳤶Ȼ����һ��
		if (is_output_key_file_binary)//��Ҫ���ɶ�������Կ�ļ�
		{

			//�����Կ�ļ�
			ofstream public_key_file_binary(output_path + key_file_binary_path + FILE_PUBLIC_KEY_FILE_EXTRA_PATH_STRING, ios_base::binary | ios_base::out);//������������͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			QByteArray magic_number = FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING;//�ȴ������ͷ��ħ������
			QByteArray interval_number = FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING;//�������ļ��ָ���
			QByteArray interval_short_number = FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING;//�������ļ��̷ָ���
			magic_number = QByteArray::fromHex(magic_number);//ת��Ϊ16���Ʊ���
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			string magic_number_string(magic_number.constData(), magic_number.length());//QByteArrayתstring
			string interval_number_string(interval_number.constData(), interval_number.length());
			string interval_short_number_string(interval_short_number.constData(), interval_short_number.length());
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_9_NUMBER;//��������
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//��ͷ���������ֱ��
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//��ͷ���������ֱ��
			public_key_file_binary << magic_number_string;//д��ͷ��ħ������
			public_key_file_binary << interval_number_string;//д��ָ���
			public_key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//����������ͣ���int�͸�ʽд�루4�ֽڣ�
			public_key_file_binary << interval_number_string;//д��ָ���
			public_key_file_binary.write((char*)(&public_key_length), sizeof(public_key_length));//�����Կ���ȣ���int�͸�ʽд�루4�ֽڣ�
			public_key_file_binary.write(public_key, public_key_length / 2);//д����Կ
			public_key_file_binary << interval_number_string;//д��ָ���
			if (have_head_digit)//д��ͷ������������Ϣ
			{
				public_key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				public_key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//д��ͷ����������
			}
			else
			{
				public_key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				public_key_file_binary << interval_short_number_string;//д����Ӧλ���ķָ���ռλ
			}
			public_key_file_binary << interval_number_string;//д��ָ���
			public_key_file_binary.close();

			//���˽Կ�ļ�
			ofstream private_key_file_binary(output_path + key_file_binary_path + FILE_PRIVATE_KEY_FILE_EXTRA_PATH_STRING, ios_base::binary | ios_base::out);//������������͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			magic_number = QByteArray::fromHex(magic_number);//ת��Ϊ16���Ʊ���
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_10_NUMBER;//��������
			private_key_file_binary << magic_number_string;//д��ͷ��ħ������
			private_key_file_binary << interval_number_string;//д��ָ���
			private_key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//����������ͣ���int�͸�ʽд�루4�ֽڣ�
			private_key_file_binary << interval_number_string;//д��ָ���
			private_key_file_binary.write((char*)(&private_key_length), sizeof(private_key_length));//�����Կ���ȣ���int�͸�ʽд�루4�ֽڣ�
			private_key_file_binary.write(private_key, private_key_length / 2);//д����Կ
			private_key_file_binary << interval_number_string;//д��ָ���
			if (have_head_digit)//д��ͷ������������Ϣ
			{
				private_key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				private_key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//д��ͷ����������
			}
			else
			{
				private_key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				private_key_file_binary << interval_short_number_string;//д����Ӧλ���ķָ���ռλ
			}
			private_key_file_binary << interval_number_string;//д��ָ���
			private_key_file_binary.close();
		}
		else
		{

		}
		emit set_key_RSA_final(public_key_length, private_key_length);//��Կ�������
		delete this;
	}

	void LockDouble::set_key_ECC(char *public_key, char *private_key, const string &curve_type, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, const string &output_path)//ECC��Կ���ɡ������������Կ�洢��Ԫ��˽Կ�洢��Ԫ����Կ���ȣ��Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·�����Ƿ���ͷ���������֣�ͷ���������֣���Կ�ļ�����·��
	{
		AutoSeededRandomPool randompool;
		ECIES<ECP>::PrivateKey ecc_private_key;
		ECIES<ECP>::PublicKey ecc_public_key;
		if (curve_type == "secp112r1")//����˽Կ
		{
			ecc_private_key.Initialize(randompool, ASN1::secp112r1());
		}
		else if (curve_type == "secp112r2")
		{
			ecc_private_key.Initialize(randompool, ASN1::secp112r2());
		}
		else if (curve_type == "secp128r1")
		{
			ecc_private_key.Initialize(randompool, ASN1::secp128r1());
		}
		else if (curve_type == "secp128r2")
		{
			ecc_private_key.Initialize(randompool, ASN1::secp128r2());
		}
		else if (curve_type == "secp160r1")
		{
			ecc_private_key.Initialize(randompool, ASN1::secp160r1());
		}
		else if (curve_type == "secp160k1")
		{
			ecc_private_key.Initialize(randompool, ASN1::secp160k1());
		}
		else if (curve_type == "secp160r2")
		{
			ecc_private_key.Initialize(randompool, ASN1::secp160r2());
		}
		else if (curve_type == "secp192k1")
		{
			ecc_private_key.Initialize(randompool, ASN1::secp192k1());
		}
		else if (curve_type == "secp224r1")
		{
			ecc_private_key.Initialize(randompool, ASN1::secp224r1());
		}
		else if (curve_type == "secp224k1")
		{
			ecc_private_key.Initialize(randompool, ASN1::secp224k1());
		}
		else if (curve_type == "secp256k1")
		{
			ecc_private_key.Initialize(randompool, ASN1::secp256k1());
		}
		else if (curve_type == "secp384r1")
		{
			ecc_private_key.Initialize(randompool, ASN1::secp384r1());
		}
		else if (curve_type == "secp521r1")
		{
			ecc_private_key.Initialize(randompool, ASN1::secp521r1());
		}
		else
		{

		}
		ecc_private_key.MakePublicKey(ecc_public_key);//��˽Կ���ɹ�Կ
		string ecc_private_key_string;//����Կ���浽ָ��λ��
		string ecc_public_key_string;
		HexEncoder public_key_encoder(new StringSink(ecc_public_key_string));//����Կת��Ϊ�ַ��������
		ecc_public_key.DEREncode(public_key_encoder);
		public_key_encoder.MessageEnd();
		HexEncoder private_key_encoder(new StringSink(ecc_private_key_string));
		ecc_private_key.DEREncode(private_key_encoder);
		private_key_encoder.MessageEnd();
		int public_key_length = ecc_public_key_string.length();//��Կ����
		int private_key_length = ecc_private_key_string.length();
		if (is_output_history_file)//��Ҫд����ʷ�ļ�
		{
			time_t system_time;//�洢ϵͳʱ��
			time(&system_time);//��ȡϵͳʱ��
			struct tm *time_struct = localtime(&system_time);//��ȡָ��ʱ��ṹ���ָ��
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//��ʷ�ļ�ʹ�ø��ӷ�ʽ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//�����Ӧ���ݡ�����Ϊʱ��
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//����ʽ���ʱ��
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_4_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�������
			history_file.close();
		}
		else
		{

		}
		if (is_output_key_file)//��Ҫ������Կ�ļ�
		{
			ofstream key_file(output_path + key_file_path, ios_base::out);//�����ı����͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			key_file << FILE_KEY_WRITE_INFORMATION_1_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����Ӧ���ݡ�����Ϊ��Կ�ļ�ͷ������
			key_file << FILE_KEY_WRITE_INFORMATION_3_STRING << output_path << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//����ļ�·��
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_8_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//�����������
			key_file << FILE_KEY_WRITE_INFORMATION_6_1_STRING << ecc_public_key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			key_file << FILE_KEY_WRITE_INFORMATION_6_2_STRING << ecc_private_key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//���ͷ����������
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ��ͷ�����ֲ�����ת����ԭʼ������ʾ
				magic_number_transform = (magic_number_transform.toHex()).toUpper();
				string magic_number_string(magic_number_transform.data(), FILE_HEAD_RAW_NUMBER_SIZE_NUMBER);
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << magic_number_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			else
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			key_file.close();
		}
		else
		{

		}
		QByteArray public_key_bytearray((char*)ecc_public_key_string.c_str(), public_key_length);//ת��ΪQByteArray
		public_key_bytearray = QByteArray::fromHex(public_key_bytearray);//ת��Ϊ16���Ʊ���
		memmove(public_key, public_key_bytearray.data(), public_key_length / 2);//ֱ�Ӹ����ڴ档ע��ת������󳤶Ȼ����һ��
		QByteArray private_key_bytearray((char*)ecc_private_key_string.c_str(), private_key_length);//ת��ΪQByteArray
		private_key_bytearray = QByteArray::fromHex(private_key_bytearray);//ת��Ϊ16���Ʊ���
		memmove(private_key, private_key_bytearray.data(), private_key_length / 2);//ֱ�Ӹ����ڴ档ע��ת������󳤶Ȼ����һ��
		if (is_output_key_file_binary)//��Ҫ���ɶ�������Կ�ļ�
		{

			//�����Կ�ļ�
			ofstream public_key_file_binary(output_path + key_file_binary_path + FILE_PUBLIC_KEY_FILE_EXTRA_PATH_STRING, ios_base::binary | ios_base::out);//������������͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			QByteArray magic_number = FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING;//�ȴ������ͷ��ħ������
			QByteArray interval_number = FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING;//�������ļ��ָ���
			QByteArray interval_short_number = FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING;//�������ļ��̷ָ���
			magic_number = QByteArray::fromHex(magic_number);//ת��Ϊ16���Ʊ���
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			string magic_number_string(magic_number.constData(), magic_number.length());//QByteArrayתstring
			string interval_number_string(interval_number.constData(), interval_number.length());
			string interval_short_number_string(interval_short_number.constData(), interval_short_number.length());
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_11_NUMBER;//��������
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//��ͷ���������ֱ��
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//��ͷ���������ֱ��
			public_key_file_binary << magic_number_string;//д��ͷ��ħ������
			public_key_file_binary << interval_number_string;//д��ָ���
			public_key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//����������ͣ���int�͸�ʽд�루4�ֽڣ�
			public_key_file_binary << interval_number_string;//д��ָ���
			public_key_file_binary.write((char*)(&public_key_length), sizeof(public_key_length));//�����Կ���ȣ���int�͸�ʽд�루4�ֽڣ�
			public_key_file_binary.write(public_key, public_key_length / 2);//д����Կ
			public_key_file_binary << interval_number_string;//д��ָ���
			if (have_head_digit)//д��ͷ������������Ϣ
			{
				public_key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				public_key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//д��ͷ����������
			}
			else
			{
				public_key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				public_key_file_binary << interval_short_number_string;//д����Ӧλ���ķָ���ռλ
			}
			public_key_file_binary << interval_number_string;//д��ָ���
			public_key_file_binary.close();

			//���˽Կ�ļ�
			ofstream private_key_file_binary(output_path + key_file_binary_path + FILE_PRIVATE_KEY_FILE_EXTRA_PATH_STRING, ios_base::binary | ios_base::out);//������������͵���Կ�ļ���ʹ�ø��Ƿ�ʽ��
			magic_number = QByteArray::fromHex(magic_number);//ת��Ϊ16���Ʊ���
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_12_NUMBER;//��������
			private_key_file_binary << magic_number_string;//д��ͷ��ħ������
			private_key_file_binary << interval_number_string;//д��ָ���
			private_key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//����������ͣ���int�͸�ʽд�루4�ֽڣ�
			private_key_file_binary << interval_number_string;//д��ָ���
			private_key_file_binary.write((char*)(&private_key_length), sizeof(private_key_length));//�����Կ���ȣ���int�͸�ʽд�루4�ֽڣ�
			private_key_file_binary.write(private_key, private_key_length / 2);//д����Կ
			private_key_file_binary << interval_number_string;//д��ָ���
			if (have_head_digit)//д��ͷ������������Ϣ
			{
				private_key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				private_key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//д��ͷ����������
			}
			else
			{
				private_key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//�����ͷ���������ֱ�ǣ���int�͸�ʽд�루4�ֽڣ�
				private_key_file_binary << interval_short_number_string;//д����Ӧλ���ķָ���ռλ
			}
			private_key_file_binary << interval_number_string;//д��ָ���
			private_key_file_binary.close();
		}
		else
		{

		}
		emit set_key_ECC_final(public_key_length, private_key_length);//��Կ�������
		delete this;
	}
}

