#include "DllLockSimple.h"

//ʹ�ñ�׼�����ռ�
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios_base;

//����
namespace rem
{
	
	//dll���庯��
	void LockOpposite::lock_opposite(const string &file_path, const string & file_name, const string & file_output_front_path, const string & file_output_back_path, bool is_output_history_file, const string & history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string & key_file_path, const string & key_file_binary_path, const string & temp_file_path, int direction, long long head_offset, long long tail_offset, long long cycle, bool have_head_digit, char *head_digit)//�ļ�ȡ�����ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺����ʱ�ļ���·�������ܷ���1����˳��2������3����˫���򣩣�ͷ��������㣬β��������㣬ѭ�����ڣ��Ƿ���ͷ���������֣�ͷ����������
	{
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		string temp_file_double_path_str = temp_file_path;//˫�����ʱ��Ҫ����ʱ�ļ������˳����ܽ��
		temp_file_double_path_str += FILE_FILE_INTERVAL_STRING;
		QDateTime current_date_time = QDateTime::currentDateTime();//��ȡ��ǰʱ��
		QString current_date_string = current_date_time.toString(FILE_TEMP_FILE_TIME_FORMAT_STRING);
		temp_file_double_path_str += string((const char *)current_date_string.toLocal8Bit());//����ʱ�ļ�·������ʱ���Ա�����̴߳���ʱ���ظ�����
		temp_file_double_path_str += FILE_TEMP_FILE_BACK_PATH_STRING;
		string temp_file_path_str = temp_file_path;//������ܺ�˫�����ʱ��Ҫ����ʱ�ļ�����ŵ�����ܽ����֮��Ը��ļ�������ݽ�������
		temp_file_path_str += FILE_FILE_INTERVAL_STRING;
		temp_file_path_str += string((const char *)current_date_string.toLocal8Bit());//����ʱ�ļ�·������ʱ���Ա�����̴߳���ʱ���ظ�����
		temp_file_path_str += FILE_TEMP_DOUBLE_FILE_BACK_PATH_STRING;
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_simple_opposite_final(false);
			goto Delete_this_class_lock_opposite;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
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
		if (direction == 1 || direction == 3)//˳�������
		{
			ofstream temp_file_double(temp_file_double_path_str, ios_base::out | ios_base::binary);//˫������ʱ��Ҫ�������ʱ�ļ�
			source_file_size = source_file.tellg() - head_offset - tail_offset;//ȥ��ͷ����������β�������յ�ռ�õ�λ��
			if (source_file_size <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit lock_simple_opposite_final(false);
				goto Delete_this_class_lock_opposite;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
			else
			{

			}
			long long source_file_size_double_lock = source_file_size * FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER;//˫������ܣ���������ʾ�õ����ļ��ܳ���Ӧ�������μ��ܵ������ֵ���ܺ�
			source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
			if (head_offset > 0)//���ڼ������
			{
				char *source_file_data_head = new char[head_offset];//�������ļ�ͷ���Ǵ�������
				source_file.read(source_file_data_head, head_offset);//�����ļ�ͷ���Ǵ�������
				target_file.write(source_file_data_head, head_offset);//д���ļ�ͷ���Ǵ�������
				delete source_file_data_head;
			}
			else
			{

			}
			long long total_count = source_file_size / FILE_ONCE_MAX_SIZE_NUMBER;//�ܴ��������������������һ��
			long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
			char *source_file_data = new char[FILE_ONCE_MAX_SIZE_NUMBER];//�������ļ�����
			for (long long loop_count = 1; loop_count <= total_count; loop_count++)
			{
				int cycle_rest_count_temp = 0;//һ��ѭ��ʹ�õ�һ������ʣ���ֽ�����ʱ����
				source_file.read(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//����FILE_ONCE_MAX_SIZE_NUMBER���ֽ�
				for (int byte_position = 0; byte_position < FILE_ONCE_MAX_SIZE_NUMBER; byte_position++, cycle_rest_count_temp++)
				{
					if ((byte_position + cycle_rest_count) % (cycle + 1) == 0)//������ڴ����λ�ü���ǰ������ʣ�µ�cycle_rest_count�ܱ���������������˵����Ҫȡ��
					{
						source_file_data[byte_position] = ~source_file_data[byte_position];//ָ���ֽ�ȡ��
						cycle_rest_count_temp = 0;//��Ϊ�Ѿ���������ʣ��������
					}
					else
					{

					}
				}
				cycle_rest_count = cycle_rest_count_temp;//��ʱ��������
				if (direction == 1)
				{
					target_file.write(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//д��Ŀ���ļ�
				}
				else
				{
					temp_file_double.write(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//д����ʱ�ļ�
				}
				if (direction == 1)
				{
					emit lock_simple_opposite_process((double)(FILE_ONCE_MAX_SIZE_NUMBER*loop_count) / (double)source_file_size);//�����źŸ������������ʹ��
				}
				else
				{
					emit lock_simple_opposite_process((double)(FILE_ONCE_MAX_SIZE_NUMBER*loop_count) / (double)source_file_size_double_lock);//�����źŸ������������ʹ��
				}
			}
			int rest_file_size_count = source_file_size % FILE_ONCE_MAX_SIZE_NUMBER;//�������һ�δ���ʹ���ļ�ʣ��δ�����ִ�С
			delete source_file_data;//�ͷ��ڴ�
			if (rest_file_size_count > 0)//���ʣ���ֽ�������0�Ŵ���
			{
				char *source_file_data_rest = new char[rest_file_size_count];
				source_file.read(source_file_data_rest, rest_file_size_count);//����rest_file_size_count���ֽ�
				for (int byte_position = 0; byte_position < rest_file_size_count; byte_position++)
				{
					if ((byte_position + cycle_rest_count) % (cycle + 1) == 0)//������ڴ����λ�ü���ǰ������ʣ�µ�cycle_rest_count�ܱ���������������˵����Ҫȡ��
					{
						source_file_data_rest[byte_position] = ~source_file_data_rest[byte_position];//ָ���ֽ�ȡ��
					}
				}
				if (direction == 1)
				{
					target_file.write(source_file_data_rest, rest_file_size_count);//д��Ŀ���ļ�
				}
				else
				{
					temp_file_double.write(source_file_data_rest, rest_file_size_count);//д����ʱ�ļ�
				}
				delete source_file_data_rest;//�ͷ��ڴ�
			}
			if (tail_offset > 0 && direction == 1)//���ڼ����յ㣬д���ļ�β���ݡ�˫�������д��
			{
				char *source_file_data_tail = new char[tail_offset];//�������ļ�β���Ǵ�������
				source_file.read(source_file_data_tail, tail_offset);//�����ļ�β���Ǵ�������
				target_file.write(source_file_data_tail, tail_offset);//д���ļ�β���Ǵ�������
				delete source_file_data_tail;
			}
			else
			{

			}
			if (direction == 1)//�ر��ļ�
			{
				source_file.close();
				target_file.close();
				temp_file_double.close();
				int delete_succeed = remove(temp_file_double_path_str.c_str());//��˳����ܲ���Ҫ��ʱ�ļ�
			}
			else
			{
				temp_file_double.close();
			}
		}
		else
		{

		}
		if (direction == 2 || direction == 3)//���������
		{
			ifstream temp_file_double(temp_file_double_path_str, ios_base::in | ios_base::binary | ios_base::ate);//������ʱ�ļ����������Ƹ�ʽ�򿪣���ʱ������ļ���β
			if ((!temp_file_double.is_open()) && direction == 3)//��ʱ�ļ���ʧ��
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit lock_simple_opposite_final(false);
				goto Delete_this_class_lock_opposite;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
			else
			{

			}
			ofstream temp_file(temp_file_path_str, ios_base::out | ios_base::binary | ios_base::app);//��Ϊc++��֧�����ļ��м�������ݣ�ֻ����������ʱ�ļ���Ȼ��������ļ��ж���ʱ�ļ��е����ݽ�������
			if (direction == 2)
			{
				source_file_size = source_file.tellg() - head_offset - tail_offset;//ȥ��ͷ����������β�������յ�ռ�õ�λ��
			}
			else
			{
				source_file_size = temp_file_double.tellg();//��ʱ�ļ�����ͷβ�����ܲ���
			}
			if (source_file_size <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit lock_simple_opposite_final(false);
				goto Delete_this_class_lock_opposite;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
			else
			{

			}
			source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
			if (head_offset > 0 && direction == 2)//���ڼ�����㣬�����˫�������д��
			{
				char *source_file_data_head = new char[head_offset];//�������ļ�ͷ���Ǵ�������
				source_file.read(source_file_data_head, head_offset);//�����ļ�ͷ���Ǵ�������
				target_file.write(source_file_data_head, head_offset);//д���ļ�ͷ���Ǵ�������
				delete source_file_data_head;
			}
			else
			{

			}
			long long total_count = source_file_size / FILE_ONCE_MAX_SIZE_NUMBER;//�ܴ��������������������һ��
			int rest_file_size_count = source_file_size % FILE_ONCE_MAX_SIZE_NUMBER;//�������һ�δ���ʹ���ļ�ʣ��δ�����ִ�С
			long long source_file_size_include_temp = source_file_size * FILE_LOCK_TAIL_SIZE_TIME_NUMBER;//���ǵ���Ҫ���ļ��������飬��������ʾ�õ����ļ��ܳ�����Ҫ���Ϻ����������Ŀ
			long long source_file_size_double_lock = source_file_size * FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER;//˫������ܣ���������ʾ�õ����ļ��ܳ���Ӧ�������μ��ܵ������ֵ���ܺ�
			long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
			char *source_file_data = new char[FILE_ONCE_MAX_SIZE_NUMBER];//�������ļ�����
			for (long long loop_count = 1; loop_count <= total_count; loop_count++)//������Ļ��������������һ���ļ��鿪ʼ��ȡ��ÿ�ζ�ȡһ���ļ���֮ǰ���Ȱ��ļ�ָ���ƶ������ļ�����ʼλ��
			{
				if (direction == 2)
				{
					source_file.clear();//����ļ�������������޷���λ
					source_file.seekg(source_file_size + head_offset - loop_count * FILE_ONCE_MAX_SIZE_NUMBER, ios_base::beg);//���ļ�ָ���ƶ�����ǰ����ȡ�ļ����ǰ��
				}
				else
				{
					temp_file_double.clear();//����ļ�������������޷���λ
					temp_file_double.seekg(source_file_size - loop_count * FILE_ONCE_MAX_SIZE_NUMBER, ios_base::beg);//���ļ�ָ���ƶ�����ǰ����ȡ�ļ����ǰ��
				}
				int cycle_rest_count_temp = 0;//һ��ѭ��ʹ�õ�һ������ʣ���ֽ�����ʱ����
				if (direction == 2)
				{
					source_file.read(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//����FILE_ONCE_MAX_SIZE_NUMBER���ֽ�
				}
				else
				{
					temp_file_double.read(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//����FILE_ONCE_MAX_SIZE_NUMBER���ֽ�
				}
				for (int byte_position = FILE_ONCE_MAX_SIZE_NUMBER - 1, position_count = 0; byte_position > -1; byte_position--, cycle_rest_count_temp++, position_count++)//�ļ����ڲ�ͬ����Ҫ������Ϊ��֤����λ����ȷ��������һ�������˳������ʱ��λ�ñ���position_count��ָ������λ�á����⻹��Ҫע��c++��֧����forѭ���ĳ�ʼ������г�ʼ��������͵ı���
				{
					if ((position_count + cycle_rest_count) % (cycle + 1) == 0)//������ڴ����λ�ü���ǰ������ʣ�µ�cycle_rest_count�ܱ���������������˵����Ҫȡ��
					{
						source_file_data[byte_position] = ~source_file_data[byte_position];//ָ���ֽ�ȡ��
						cycle_rest_count_temp = 0;//��Ϊ�Ѿ���������ʣ��������
					}
					else
					{

					}
				}
				cycle_rest_count = cycle_rest_count_temp;//��ʱ��������
				temp_file.write(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//д����ʱ�ļ�
				if (direction == 2)
				{
					emit lock_simple_opposite_process((double)(FILE_ONCE_MAX_SIZE_NUMBER*loop_count) / (double)source_file_size_include_temp);//�����źŸ������������ʹ��
				}
				else
				{
					emit lock_simple_opposite_process((double)(source_file_size + (FILE_ONCE_MAX_SIZE_NUMBER*loop_count)) / (double)source_file_size_double_lock);//�����źŸ������������ʹ��
				}
			}
			delete source_file_data;//�ͷ��ڴ�
			if (rest_file_size_count > 0)//���ʣ���ֽ�������0�Ŵ���
			{
				if (direction == 2)
				{
					source_file.clear();//����ļ�������������޷���λ
					source_file.seekg(ios_base::beg + head_offset);//��ȡ�ļ�ָ�붨λ
				}
				else
				{
					temp_file_double.clear();//����ļ�������������޷���λ
					temp_file_double.seekg(ios_base::beg);//��ȡ�ļ�ָ�붨λ
				}
				char *source_file_data_rest = new char[rest_file_size_count];
				if (direction == 2)
				{
					source_file.read(source_file_data_rest, rest_file_size_count);//����rest_file_size_count���ֽ�
				}
				else
				{
					temp_file_double.read(source_file_data_rest, rest_file_size_count);//����rest_file_size_count���ֽ�
				}
				for (int byte_position = rest_file_size_count - 1, position_count = 0; byte_position > -1; byte_position--, position_count++)
				{
					if ((position_count + cycle_rest_count) % (cycle + 1) == 0)//������ڴ����λ�ü���ǰ������ʣ�µ�cycle_rest_count�ܱ���������������˵����Ҫȡ��
					{
						source_file_data_rest[byte_position] = ~source_file_data_rest[byte_position];//ָ���ֽ�ȡ��
					}
				}
				temp_file.write(source_file_data_rest, rest_file_size_count);//д����ʱ�ļ�
				delete source_file_data_rest;//�ͷ��ڴ�
			}
			else
			{

			}
			temp_file.close();//�ر��ļ�����ɾ��˳������̲�������ʱ�ļ�
			temp_file_double.close();
			int delete_succeed = remove(temp_file_double_path_str.c_str());
			ifstream temp_file_rebuild(temp_file_path_str.c_str(), ios_base::in | ios_base::binary | ios_base::ate);//����ʱ�ļ�������������
			if(!temp_file_rebuild.is_open())
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit lock_simple_opposite_final(false);
				goto Delete_this_class_lock_opposite;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
			else
			{

			}
			if (rest_file_size_count > 0)//�ļ�����ķ�����֮ǰ�ǰ��ļ��鵹���������ʱ�ļ����棬������Ҫ�ӵ�һ���ļ��鿪ʼ��ȡ������д��Ŀ���ļ������ȴ�����������ļ���Ĳ���
			{
				char *temp_file_data_rest = new char[rest_file_size_count];//���������ݵ��ڴ�ռ�
				temp_file_rebuild.clear();//����ļ�������������޷���λ
				temp_file_rebuild.seekg(source_file_size - rest_file_size_count, ios_base::beg);//��ȡ�ļ�ָ�붨λ�����һ���������ļ����λ��
				temp_file_rebuild.read(temp_file_data_rest, rest_file_size_count);//����rest_file_size_count���ֽ�
				target_file.write(temp_file_data_rest, rest_file_size_count);//д��Ŀ���ļ�
				delete temp_file_data_rest;//�ͷ��ڴ�
			}
			else
			{

			}
			char *temp_file_data = new char[FILE_ONCE_MAX_SIZE_NUMBER];//���������ݵ��ڴ�ռ�
			for (long long loop_count = 1; loop_count <= total_count; loop_count++)//������ܲ��ֵ�ʣ�ಿ�֣��ⲿ�������������ļ������
			{
				temp_file_rebuild.clear();//����ļ�������������޷���λ
				temp_file_rebuild.seekg(source_file_size  - rest_file_size_count - loop_count * FILE_ONCE_MAX_SIZE_NUMBER, ios_base::beg);//���ļ�ָ���ƶ�����ǰ����ȡ�ļ����ǰ��
				temp_file_rebuild.read(temp_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//����FILE_ONCE_MAX_SIZE_NUMBER���ֽ�
				target_file.write(temp_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//д��Ŀ���ļ�
				if (direction == 2)
				{
					emit lock_simple_opposite_process((double)(source_file_size + (FILE_ONCE_MAX_SIZE_NUMBER*loop_count)) / (double)source_file_size_include_temp);//��Ȼ�����źŸ������������ʹ�á���Ҫ����֮ǰ�Ѿ�����Ĳ���
				}
				else
				{
					emit lock_simple_opposite_process((double)(source_file_size + source_file_size + (FILE_ONCE_MAX_SIZE_NUMBER*loop_count)) / (double)source_file_size_include_temp);//��Ȼ�����źŸ������������ʹ�á���Ҫ����֮ǰ�Ѿ�����Ĳ���
				}
			}
			delete temp_file_data;
			if (tail_offset > 0)//���ڼ����յ㣬д���ļ�β���ݣ��������д��
			{
				source_file.clear();//c++�и����ԣ��ļ�ָ�뵽���ļ�β��ʹ���ļ�ָ��λ�ò�����������Ч����Ҫ��������ļ���
				source_file.seekg(source_file_size + head_offset, ios_base::beg);//��Ϊ�Ƕ�ȡ�ļ�β�����ݣ������Ҫ���ƶ����ļ����������ݵ��ײ�
				char *source_file_data_tail = new char[tail_offset];//�������ļ�β���Ǵ�������
				source_file.read(source_file_data_tail, tail_offset);//�����ļ�β���Ǵ�������
				target_file.write(source_file_data_tail, tail_offset);//д���ļ�β���Ǵ�������
				delete source_file_data_tail;
			}
			else
			{

			}
			source_file.close();//�ر��ļ�
			target_file.close();
			temp_file_rebuild.close();
			delete_succeed = remove(temp_file_path_str.c_str());//ɾ����ʱ�ļ�
		}
		else
		{

		}
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
			if (direction == 1)//������ܷ���
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			else if (direction == 2)
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_2_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			else
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_3_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << head_offset << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//���ͷ�������ַ���
			key_file << FILE_KEY_WRITE_INFORMATION_7_STRING << tail_offset << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//���β�������ַ���
			key_file << FILE_KEY_WRITE_INFORMATION_8_STRING << cycle << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//���ѭ������
			if (have_head_digit)//���ͷ����������
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ��ͷ�����ֲ�����ת����ԭʼ������ʾ
				magic_number_transform = (magic_number_transform.toHex()).toUpper();
				string magic_number_string(magic_number_transform.data(), FILE_HEAD_RAW_NUMBER_SIZE_NUMBER);
				key_file << FILE_KEY_WRITE_INFORMATION_9_STRING << magic_number_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			else
			{
				key_file << FILE_KEY_WRITE_INFORMATION_9_STRING << FILE_KEY_WRITE_INFORMATION_9_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
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
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_1_NUMBER;//��������
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//��ͷ���������ֱ��
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//��ͷ���������ֱ��
			key_file_binary << magic_number_string;//д��ͷ��ħ������
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//����������ͣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary.write((char*)(&direction), sizeof(direction));//������ܷ��򣬰�int�͸�ʽд�루4�ֽڣ�
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write((char*)(&head_offset), sizeof(head_offset));//���ͷ�������ַ�������long long�͸�ʽд�루8�ֽڣ�
			key_file_binary.write((char*)(&tail_offset), sizeof(tail_offset));//���β�������ַ�������long long�͸�ʽд�루8�ֽڣ�
			key_file_binary.write((char*)(&cycle), sizeof(cycle));//����������ڣ���long long�͸�ʽд�루8�ֽڣ�
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
		emit lock_simple_opposite_final(true);
	Delete_this_class_lock_opposite://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockOpposite::unlock_opposite(const string & file_path, const string & file_name, const string & file_output_front_path, const string & file_output_back_path, bool is_output_history_file, const string & history_file_path, const string & temp_file_path, int direction, long long head_offset, long long tail_offset, long long cycle, bool have_head_digit, char *head_digit)//�ļ�ȡ�����ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·������ʱ�ļ���·�������ܷ���1����˳��2������3����˫���򣩣�ͷ��������㣬β��������㣬ѭ�����ڣ��Ƿ���ͷ���������֣�ͷ����������
	{
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		string temp_file_double_path_str = temp_file_path;//˫�����ʱ��Ҫ����ʱ�ļ������˳����ܽ��
		temp_file_double_path_str += FILE_FILE_INTERVAL_STRING;
		QDateTime current_date_time = QDateTime::currentDateTime();//��ȡ��ǰʱ��
		QString current_date_string = current_date_time.toString(FILE_TEMP_FILE_TIME_FORMAT_STRING);
		temp_file_double_path_str += string((const char *)current_date_string.toLocal8Bit());//����ʱ�ļ�·������ʱ���Ա�����̴߳���ʱ���ظ�����
		temp_file_double_path_str += FILE_TEMP_FILE_BACK_PATH_STRING;
		string temp_file_path_str = temp_file_path;//������ܺ�˫�����ʱ��Ҫ����ʱ�ļ�����ŵ�����ܽ����֮��Ը��ļ�������ݽ�������
		temp_file_path_str += FILE_FILE_INTERVAL_STRING;
		temp_file_path_str += string((const char *)current_date_string.toLocal8Bit());//����ʱ�ļ�·������ʱ���Ա�����̴߳���ʱ���ظ�����
		temp_file_path_str += FILE_TEMP_DOUBLE_FILE_BACK_PATH_STRING;
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_simple_opposite_final(false);
			goto Delete_this_class_unlock_opposite;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		long long source_file_size;//�ļ���������Ҫ������ֽ���
		if (direction == 1 || direction == 3)//˳�������
		{
			ofstream temp_file_double(temp_file_double_path_str, ios_base::out | ios_base::binary);//˫������ʱ��Ҫ�������ʱ�ļ�
			source_file_size = source_file.tellg() - head_offset - tail_offset;//ȥ��ͷ����������β�������յ�ռ�õ�λ��
			if (have_head_digit)//ͷ����������У�顣��Ϊtellg()���ڶ�ȡ�ļ�֮ǰ��Ч������ȶ�ȡͷ���������ֻ���ɸú�����Ч
			{
				QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ�ý�����Ϣȷ�Ͻ����ṩ��ͷ�����ֲ�����ת����ԭʼ������ʾ
				key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
				QString key_head_digit_transform_string = key_head_digit_transform;//תΪQString
				source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
				char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//��������ļ�ͷ���������ֵ�char����
				source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ȡ�������֡�������Ҫע�⣬�����������Ϊȫ�ռ���00000000����ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char����
				QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
				source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
				QString source_head_digit_transform_string = source_head_digit_transform;//תΪQString
				if (key_head_digit_transform_string == source_head_digit_transform_string)//ͷ������������ͬ�����н���
				{
					source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//ȥ��ͷ����������ռ�õĿռ�
				}
				else//ͷ���������ֲ�ͬ��ȡ������
				{
					target_file.close();
					remove(target_file_path.c_str());//ɾ���ļ�
					emit unlock_simple_opposite_final(false);
					goto Delete_this_class_unlock_opposite;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
				}
			}
			else
			{

			}
			if (source_file_size <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_simple_opposite_final(false);
				goto Delete_this_class_unlock_opposite;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
			else
			{

			}
			long long source_file_size_double_lock = source_file_size * FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER;//˫������ܣ���������ʾ�õ����ļ��ܳ���Ӧ�������μ��ܵ������ֵ���ܺ�
			source_file.clear();//����ļ�������������޷���λ
			if (have_head_digit)//�����ͷ���������֣�ע�ⲻ�ܽ���������д������ļ�
			{
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//���ļ�ָ��ƫ�Ƶ�ͷ����������֮��
			}
			else
			{
				source_file.seekg(ios_base::beg);//�ض����ļ�ָ��
			}
			if (head_offset > 0)//���ڼ������
			{
				char *source_file_data_head = new char[head_offset];//�������ļ�ͷ���Ǵ�������
				source_file.read(source_file_data_head, head_offset);//�����ļ�ͷ���Ǵ�������
				target_file.write(source_file_data_head, head_offset);//д���ļ�ͷ���Ǵ�������
				delete source_file_data_head;
			}
			else
			{

			}
			long long total_count = source_file_size / FILE_ONCE_MAX_SIZE_NUMBER;//�ܴ��������������������һ��
			long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
			char *source_file_data = new char[FILE_ONCE_MAX_SIZE_NUMBER];//�������ļ�����
			for (long long loop_count = 1; loop_count <= total_count; loop_count++)
			{
				int cycle_rest_count_temp = 0;//һ��ѭ��ʹ�õ�һ������ʣ���ֽ�����ʱ����
				source_file.read(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//����FILE_ONCE_MAX_SIZE_NUMBER���ֽ�
				for (int byte_position = 0; byte_position < FILE_ONCE_MAX_SIZE_NUMBER; byte_position++, cycle_rest_count_temp++)
				{
					if ((byte_position + cycle_rest_count) % (cycle + 1) == 0)//������ڴ����λ�ü���ǰ������ʣ�µ�cycle_rest_count�ܱ���������������˵����Ҫȡ��
					{
						source_file_data[byte_position] = ~source_file_data[byte_position];//ָ���ֽ�ȡ��
						cycle_rest_count_temp = 0;//��Ϊ�Ѿ���������ʣ��������
					}
					else
					{

					}
				}
				cycle_rest_count = cycle_rest_count_temp;//��ʱ��������
				if (direction == 1)
				{
					target_file.write(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//д��Ŀ���ļ�
				}
				else
				{
					temp_file_double.write(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//д����ʱ�ļ�
				}
				if (direction == 1)
				{
					emit unlock_simple_opposite_process((double)(FILE_ONCE_MAX_SIZE_NUMBER*loop_count) / (double)source_file_size);//�����źŸ������������ʹ��
				}
				else
				{
					emit unlock_simple_opposite_process((double)(FILE_ONCE_MAX_SIZE_NUMBER*loop_count) / (double)source_file_size_double_lock);//�����źŸ������������ʹ��
				}
			}
			int rest_file_size_count = source_file_size % FILE_ONCE_MAX_SIZE_NUMBER;//�������һ�δ���ʹ���ļ�ʣ��δ�����ִ�С
			delete source_file_data;//�ͷ��ڴ�
			if (rest_file_size_count > 0)//���ʣ���ֽ�������0�Ŵ���
			{
				char *source_file_data_rest = new char[rest_file_size_count];
				source_file.read(source_file_data_rest, rest_file_size_count);//����rest_file_size_count���ֽ�
				for (int byte_position = 0; byte_position < rest_file_size_count; byte_position++)
				{
					if ((byte_position + cycle_rest_count) % (cycle + 1) == 0)//������ڴ����λ�ü���ǰ������ʣ�µ�cycle_rest_count�ܱ���������������˵����Ҫȡ��
					{
						source_file_data_rest[byte_position] = ~source_file_data_rest[byte_position];//ָ���ֽ�ȡ��
					}
				}
				if (direction == 1)
				{
					target_file.write(source_file_data_rest, rest_file_size_count);//д��Ŀ���ļ�
				}
				else
				{
					temp_file_double.write(source_file_data_rest, rest_file_size_count);//д����ʱ�ļ�
				}
				delete source_file_data_rest;//�ͷ��ڴ�
			}
			if (tail_offset > 0 && direction == 1)//���ڼ����յ㣬д���ļ�β���ݡ�˫�������д��
			{
				char *source_file_data_tail = new char[tail_offset];//�������ļ�β���Ǵ�������
				source_file.read(source_file_data_tail, tail_offset);//�����ļ�β���Ǵ�������
				target_file.write(source_file_data_tail, tail_offset);//д���ļ�β���Ǵ�������
				delete source_file_data_tail;
			}
			else
			{

			}
			if (direction == 1)//�ر��ļ�
			{
				source_file.close();
				target_file.close();
				temp_file_double.close();
				int delete_succeed = remove(temp_file_double_path_str.c_str());//��˳����ܲ���Ҫ��ʱ�ļ�
			}
			else
			{
				temp_file_double.close();
			}
		}
		else
		{

		}
		if (direction == 2 || direction == 3)//���������
		{
			ifstream temp_file_double(temp_file_double_path_str, ios_base::in | ios_base::binary | ios_base::ate);//������ʱ�ļ����������Ƹ�ʽ�򿪣���ʱ������ļ���β
			if ((!temp_file_double.is_open()) && direction == 3)//��ʱ�ļ���ʧ��
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_simple_opposite_final(false);
				goto Delete_this_class_unlock_opposite;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
			else
			{

			}
			ofstream temp_file(temp_file_path_str, ios_base::out | ios_base::binary | ios_base::app);//��Ϊc++��֧�����ļ��м�������ݣ�ֻ����������ʱ�ļ���Ȼ��������ļ��ж���ʱ�ļ��е����ݽ�������
			if (direction == 2)//˫������Ѿ���ǰ�洦����ˣ�ֻ��Ҫ��������ܵ�ͷ����������
			{
				source_file_size = source_file.tellg() - head_offset - tail_offset;//ȥ��ͷ����������β�������յ�ռ�õ�λ��
				if (have_head_digit)//ͷ����������У�顣��Ϊtellg()���ڶ�ȡ�ļ�֮ǰ��Ч������ȶ�ȡͷ���������ֻ���ɸú�����Ч
				{
					QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ�ý�����Ϣȷ�Ͻ����ṩ��ͷ�����ֲ�����ת����ԭʼ������ʾ
					key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
					QString key_head_digit_transform_string = key_head_digit_transform;//תΪQString
					source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
					char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//��������ļ�ͷ���������ֵ�char����
					source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ȡ�������֡�������Ҫע�⣬�����������Ϊȫ�ռ���00000000����ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char����
					QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
					source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
					QString source_head_digit_transform_string = source_head_digit_transform;//תΪQString
					if (key_head_digit_transform_string == source_head_digit_transform_string)//ͷ������������ͬ�����н���
					{
						source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//ȥ��ͷ����������ռ�õĿռ�

					}
					else//ͷ���������ֲ�ͬ��ȡ������
					{
						target_file.close();
						remove(target_file_path.c_str());//ɾ���ļ�
						emit unlock_simple_opposite_final(false);
						goto Delete_this_class_unlock_opposite;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
					}
				}
				else
				{

				}
			}
			else
			{
				source_file_size = temp_file_double.tellg();//��ʱ�ļ�����ͷβ�����ܲ���
			}
			if (source_file_size <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_simple_opposite_final(false);
				goto Delete_this_class_unlock_opposite;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
			else
			{

			}
			source_file.clear();//����ļ�������������޷���λ
			if (have_head_digit)//�����ͷ���������֣�ע�ⲻ�ܽ���������д������ļ�
			{
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//���ļ�ָ��ƫ�Ƶ�ͷ����������֮��
			}
			else
			{
				source_file.seekg(ios_base::beg);//�ض����ļ�ָ��
			}
			if (head_offset > 0 && direction == 2)//���ڼ�����㣬�����˫�������д��
			{
				char *source_file_data_head = new char[head_offset];//�������ļ�ͷ���Ǵ�������
				source_file.read(source_file_data_head, head_offset);//�����ļ�ͷ���Ǵ�������
				target_file.write(source_file_data_head, head_offset);//д���ļ�ͷ���Ǵ�������
				delete source_file_data_head;
			}
			else
			{

			}
			long long total_count = source_file_size / FILE_ONCE_MAX_SIZE_NUMBER;//�ܴ��������������������һ��
			int rest_file_size_count = source_file_size % FILE_ONCE_MAX_SIZE_NUMBER;//�������һ�δ���ʹ���ļ�ʣ��δ�����ִ�С
			long long source_file_size_include_temp = source_file_size * FILE_LOCK_TAIL_SIZE_TIME_NUMBER;//���ǵ���Ҫ���ļ��������飬��������ʾ�õ����ļ��ܳ�����Ҫ���Ϻ����������Ŀ
			long long source_file_size_double_lock = source_file_size * FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER;//˫������ܣ���������ʾ�õ����ļ��ܳ���Ӧ�������μ��ܵ������ֵ���ܺ�
			long long cycle_rest_count = 0;//ÿ�����ڰ��մ������ڴ���֮��ʣ�µĵ����������ڵ��ֽ��������紦���ļ����СFILE_ONCE_MAX_SIZE_NUMBERΪ10��������cycleΪ4����һ���ڸ���ֵΪ1����ô����ƫ��1��������ֽڣ�Ȼ��ƫ��4��������ֽڣ���ƫ��4�����������1���ֽڣ�С�ڴ����������ǵ�ǰ���������ڵĸ�ֵ
			char *source_file_data = new char[FILE_ONCE_MAX_SIZE_NUMBER];//�������ļ�����
			for (long long loop_count = 1; loop_count <= total_count; loop_count++)//������Ļ��������������һ���ļ��鿪ʼ��ȡ��ÿ�ζ�ȡһ���ļ���֮ǰ���Ȱ��ļ�ָ���ƶ������ļ�����ʼλ��
			{
				if (direction == 2)
				{
					source_file.clear();//����ļ�������������޷���λ
					if (have_head_digit)//�����ͷ���������֣�ע�ⲻ�ܽ���������д������ļ�
					{
						source_file.seekg(source_file_size + head_offset - loop_count * FILE_ONCE_MAX_SIZE_NUMBER + FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//���ļ�ָ���ƶ�����ǰ����ȡ�ļ����ǰ�棬��Ҫ����ͷ����������
					}
					else
					{
						source_file.seekg(source_file_size + head_offset - loop_count * FILE_ONCE_MAX_SIZE_NUMBER, ios_base::beg);//���ļ�ָ���ƶ�����ǰ����ȡ�ļ����ǰ��
					}
				}
				else
				{
					temp_file_double.clear();//����ļ�������������޷���λ
					temp_file_double.seekg(source_file_size - loop_count * FILE_ONCE_MAX_SIZE_NUMBER, ios_base::beg);//���ļ�ָ���ƶ�����ǰ����ȡ�ļ����ǰ��
				}
				int cycle_rest_count_temp = 0;//һ��ѭ��ʹ�õ�һ������ʣ���ֽ�����ʱ����
				if (direction == 2)
				{
					source_file.read(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//����FILE_ONCE_MAX_SIZE_NUMBER���ֽ�
				}
				else
				{
					temp_file_double.read(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//����FILE_ONCE_MAX_SIZE_NUMBER���ֽ�
				}
				for (int byte_position = FILE_ONCE_MAX_SIZE_NUMBER - 1, position_count = 0; byte_position > -1; byte_position--, cycle_rest_count_temp++, position_count++)//�ļ����ڲ�ͬ����Ҫ������Ϊ��֤����λ����ȷ��������һ�������˳������ʱ��λ�ñ���position_count��ָ������λ�á����⻹��Ҫע��c++��֧����forѭ���ĳ�ʼ������г�ʼ��������͵ı���
				{
					if ((position_count + cycle_rest_count) % (cycle + 1) == 0)//������ڴ����λ�ü���ǰ������ʣ�µ�cycle_rest_count�ܱ���������������˵����Ҫȡ��
					{
						source_file_data[byte_position] = ~source_file_data[byte_position];//ָ���ֽ�ȡ��
						cycle_rest_count_temp = 0;//��Ϊ�Ѿ���������ʣ��������
					}
					else
					{

					}
				}
				cycle_rest_count = cycle_rest_count_temp;//��ʱ��������
				temp_file.write(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//д����ʱ�ļ�
				if (direction == 2)
				{
					emit unlock_simple_opposite_process((double)(FILE_ONCE_MAX_SIZE_NUMBER*loop_count) / (double)source_file_size_include_temp);//�����źŸ������������ʹ��
				}
				else
				{
					emit unlock_simple_opposite_process((double)(source_file_size + (FILE_ONCE_MAX_SIZE_NUMBER*loop_count)) / (double)source_file_size_double_lock);//�����źŸ������������ʹ��
				}
			}
			delete source_file_data;//�ͷ��ڴ�
			if (rest_file_size_count > 0)//���ʣ���ֽ�������0�Ŵ���
			{
				if (direction == 2)
				{
					source_file.clear();//����ļ�������������޷���λ
					source_file.clear();//����ļ�������������޷���λ
					if (have_head_digit)//�����ͷ���������֣�ע�ⲻ�ܽ���������д������ļ�
					{
						source_file.seekg(ios_base::beg + head_offset + FILE_HEAD_NUMBER_SIZE_NUMBER);//��ȡ�ļ�ָ�붨λ����Ҫ����ͷ����������
					}
					else
					{
						source_file.seekg(ios_base::beg + head_offset);//��ȡ�ļ�ָ�붨λ
					}
				}
				else
				{
					temp_file_double.clear();//����ļ�������������޷���λ
					temp_file_double.seekg(ios_base::beg);//��ȡ�ļ�ָ�붨λ
				}
				char *source_file_data_rest = new char[rest_file_size_count];
				if (direction == 2)
				{
					source_file.read(source_file_data_rest, rest_file_size_count);//����rest_file_size_count���ֽ�
				}
				else
				{
					temp_file_double.read(source_file_data_rest, rest_file_size_count);//����rest_file_size_count���ֽ�
				}
				for (int byte_position = rest_file_size_count - 1, position_count = 0; byte_position > -1; byte_position--, position_count++)
				{
					if ((position_count + cycle_rest_count) % (cycle + 1) == 0)//������ڴ����λ�ü���ǰ������ʣ�µ�cycle_rest_count�ܱ���������������˵����Ҫȡ��
					{
						source_file_data_rest[byte_position] = ~source_file_data_rest[byte_position];//ָ���ֽ�ȡ��
					}
				}
				temp_file.write(source_file_data_rest, rest_file_size_count);//д����ʱ�ļ�
				delete source_file_data_rest;//�ͷ��ڴ�
			}
			else
			{

			}
			temp_file.close();//�ر��ļ�����ɾ��˳������̲�������ʱ�ļ�
			temp_file_double.close();
			int delete_succeed = remove(temp_file_double_path_str.c_str());
			ifstream temp_file_rebuild(temp_file_path_str, ios_base::in | ios_base::binary | ios_base::ate);//����ʱ�ļ�������������
			if (!temp_file_rebuild.is_open())
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_simple_opposite_final(false);
				goto Delete_this_class_unlock_opposite;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
			else
			{

			}
			if (rest_file_size_count > 0)//�ļ�����ķ�����֮ǰ�ǰ��ļ��鵹���������ʱ�ļ����棬������Ҫ�ӵ�һ���ļ��鿪ʼ��ȡ������д��Ŀ���ļ������ȴ�����������ļ���Ĳ���
			{
				char *temp_file_data_rest = new char[rest_file_size_count];//���������ݵ��ڴ�ռ�
				temp_file_rebuild.clear();//����ļ�������������޷���λ
				temp_file_rebuild.seekg(source_file_size - rest_file_size_count, ios_base::beg);//��ȡ�ļ�ָ�붨λ�����һ���������ļ����λ��
				temp_file_rebuild.read(temp_file_data_rest, rest_file_size_count);//����rest_file_size_count���ֽ�
				target_file.write(temp_file_data_rest, rest_file_size_count);//д��Ŀ���ļ�
				delete temp_file_data_rest;//�ͷ��ڴ�
			}
			else
			{

			}
			char *temp_file_data = new char[FILE_ONCE_MAX_SIZE_NUMBER];//���������ݵ��ڴ�ռ�
			for (long long loop_count = 1; loop_count <= total_count; loop_count++)//������ܲ��ֵ�ʣ�ಿ�֣��ⲿ�������������ļ������
			{
				temp_file_rebuild.clear();//����ļ�������������޷���λ
				temp_file_rebuild.seekg(source_file_size - rest_file_size_count - loop_count * FILE_ONCE_MAX_SIZE_NUMBER, ios_base::beg);//���ļ�ָ���ƶ�����ǰ����ȡ�ļ����ǰ��
				temp_file_rebuild.read(temp_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//����FILE_ONCE_MAX_SIZE_NUMBER���ֽ�
				target_file.write(temp_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//д��Ŀ���ļ�
				if (direction == 2)
				{
					emit unlock_simple_opposite_process((double)(source_file_size + (FILE_ONCE_MAX_SIZE_NUMBER*loop_count)) / (double)source_file_size_include_temp);//��Ȼ�����źŸ������������ʹ�á���Ҫ����֮ǰ�Ѿ�����Ĳ���
				}
				else
				{
					emit unlock_simple_opposite_process((double)(source_file_size + source_file_size + (FILE_ONCE_MAX_SIZE_NUMBER*loop_count)) / (double)source_file_size_include_temp);//��Ȼ�����źŸ������������ʹ�á���Ҫ����֮ǰ�Ѿ�����Ĳ���
				}
			}
			delete temp_file_data;
			if (tail_offset > 0)//���ڼ����յ㣬д���ļ�β���ݣ��������д�롣���⣬��ע�ⲻ��д��ͷ����������
			{
				source_file.clear();//c++�и����ԣ��ļ�ָ�뵽���ļ�β��ʹ���ļ�ָ��λ�ò�����������Ч����Ҫ��������ļ���
				if (have_head_digit)//�����ͷ���������֣�ע�ⲻ�ܽ���������д������ļ�
				{
					source_file.seekg(source_file_size + head_offset + FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//��Ϊ�Ƕ�ȡ�ļ�β�����ݣ������Ҫ���ƶ����ļ����������ݵ��ײ�
				}
				else
				{
					source_file.seekg(source_file_size + head_offset, ios_base::beg);//��Ϊ�Ƕ�ȡ�ļ�β�����ݣ������Ҫ���ƶ����ļ����������ݵ��ײ�
				}
				char *source_file_data_tail = new char[tail_offset];//�������ļ�β���Ǵ�������
				source_file.read(source_file_data_tail, tail_offset);//�����ļ�β���Ǵ�������
				target_file.write(source_file_data_tail, tail_offset);//д���ļ�β���Ǵ�������
				delete source_file_data_tail;
			}
			else
			{

			}
			source_file.close();//�ر��ļ�
			target_file.close();
			temp_file_rebuild.close();
			delete_succeed = remove(temp_file_path_str.c_str());//ɾ����ʱ�ļ�
		}
		else
		{

		}
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
		emit unlock_simple_opposite_final(true);
	Delete_this_class_unlock_opposite://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockOpposite::lock_add(const string & file_path, const string & file_name, const string & file_output_front_path, const string & file_output_back_path, bool is_output_history_file, const string & history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string & key_file_path, const string & key_file_binary_path, const string & temp_file_path, int direction, long long head_offset, long long tail_offset, int cycle, bool have_head_digit, char *head_digit, int *unit_digit)//�ļ�ȡ�����ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·�����Ƿ������Կ�ļ����Ƿ������������Կ�ļ��������Կ�ļ�·����׺�������������Կ�ļ�·����׺����ʱ�ļ���·�������ܷ���1����˳��2������3����˫���򣩣�ͷ��������㣬β��������㣬ѭ�����ڣ�ע������ѭ������ָ���ǼӼ�ѭ����Ԫ��Ŀ��������ȡ�����ܵļ��ܼ��������Ҫ���м�1���������Ƿ���ͷ���������֣�ͷ���������֣���ѭ����λ�Ӽ�������Ϊ����16��int�͵����飩
	{

		//���ܹ��̣�����ѭ����Ԫ��Ŀ��ÿһ��ѭ���ڣ�����Ԫ������Ӧλ�õļӼ�������Ȼ�������һѭ��
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		QDateTime current_date_time = QDateTime::currentDateTime();//��ȡ��ǰʱ��
		QString current_date_string = current_date_time.toString(FILE_TEMP_FILE_TIME_FORMAT_STRING);
		string temp_file_path_str = temp_file_path;//������ܺ�˫�����ʱ��Ҫ����ʱ�ļ�����ŵ�����ܽ����֮��Ը��ļ�������ݽ�������
		temp_file_path_str += FILE_FILE_INTERVAL_STRING;
		temp_file_path_str += string((const char *)current_date_string.toLocal8Bit());//����ʱ�ļ�·������ʱ���Ա�����̴߳���ʱ���ظ�����
		temp_file_path_str += FILE_TEMP_DOUBLE_FILE_BACK_PATH_STRING;
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit lock_simple_add_final(false);
			goto Delete_this_class_lock_add;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		if (have_head_digit)//�����������ͷ����������
		{
			target_file.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//����QByteArrayת��Ϊ16���Ʊ�����ַ����ĳ��ȼ���һ�룬��Ϊ����16������ֵ��ʾһ���ֽ�
		}
		long long source_file_unit_count;//�ļ���������Ҫ����ĵ�Ԫ��
		if (direction == 1)//˳�������
		{
			source_file_unit_count = source_file.tellg() - head_offset - tail_offset;//ȥ��ͷ����������β�������յ�ռ�õ�λ��
			int tail_offset_update = tail_offset + source_file_unit_count % sizeof(int);//��ȡ��������β������һ��int���ȵĲ��֣�����β������
			long long int_size_temp = sizeof(int);//����ֱ��ʹ��source_file_unit_count/=sizeof(int)���������source_file_unit_countΪ��������ַǳ���Ľ��ֵ����������Ϊsizeof(int)Ϊunsigned long���ڶԽ��ת����ʱ�򣬸����ڲ�ͬ���������µı�ʾ��ͬ
			source_file_unit_count /= int_size_temp;//��ô����ܵ�Ԫ��Ŀ
			if (source_file_unit_count <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit lock_simple_add_final(false);
				goto Delete_this_class_lock_add;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
			else
			{

			}
			long long source_file_unit_count_double_lock = source_file_unit_count * FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER;//˫������ܣ���������ʾ�õ����ļ��ܳ���Ӧ�������μ��ܵ������ֵ���ܺ�
			source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
			if (head_offset > 0)//���ڼ������
			{
				char *source_file_data_head = new char[head_offset];//�������ļ�ͷ���Ǵ�������
				source_file.read(source_file_data_head, head_offset);//�����ļ�ͷ���Ǵ�������
				target_file.write(source_file_data_head, head_offset);//д���ļ�ͷ���Ǵ�������
				delete source_file_data_head;
			}
			else
			{

			}
			int cycle_count = 0;//ѭ����Ԫ����
			int unit;//��������int��λ
			for (long long loop_count = 1; loop_count <= source_file_unit_count; loop_count++)
			{
				source_file.read((char*)&unit, sizeof(int));//��ȡ��ǰ��Ԫ����
				unit += unit_digit[cycle_count];//��Ԫ���ݼ���ָ����ֵ
				target_file.write((char*)&unit, sizeof(unit));//������������ݣ���int�͸�ʽд�루4�ֽڣ�
				emit lock_simple_add_process((double)loop_count / (double)source_file_unit_count);//�����źŸ������������ʹ��
				cycle_count++;
				if (cycle_count >= cycle)//ѭ�����ﵽ���ֵ������ѭ����
				{
					cycle_count = 0;
				}
				else
				{

				}
			}
			if (tail_offset_update > 0 )//���ڼ����յ㣬д���ļ�β���ݡ�˫�������д��
			{
				char *source_file_data_tail = new char[tail_offset_update];//�������ļ�β���Ǵ�������
				source_file.read(source_file_data_tail, tail_offset_update);//�����ļ�β���Ǵ�������
				target_file.write(source_file_data_tail, tail_offset_update);//д���ļ�β���Ǵ�������
				delete source_file_data_tail;
			}
			else
			{

			}
			source_file.close();
			target_file.close();
		}
		else//���������
		{
			ofstream temp_file(temp_file_path_str, ios_base::out | ios_base::binary | ios_base::app);//��Ϊc++��֧�����ļ��м�������ݣ�ֻ����������ʱ�ļ���Ȼ��������ļ��ж���ʱ�ļ��е����ݽ�������
			source_file_unit_count = source_file.tellg() - head_offset - tail_offset;//ȥ��ͷ����������β�������յ�ռ�õ�λ��
			int head_offset_update = head_offset + source_file_unit_count % sizeof(int);//��ȡ��������ͷ������һ��int���ȵĲ��֣�����ͷ������
			long long int_size_temp = sizeof(int);//����ֱ��ʹ��source_file_unit_count/=sizeof(int)���������source_file_unit_countΪ��������ַǳ���Ľ��ֵ����������Ϊsizeof(int)Ϊunsigned long���ڶԽ��ת����ʱ�򣬸����ڲ�ͬ���������µı�ʾ��ͬ
			source_file_unit_count /= int_size_temp;//��ô����ܵ�Ԫ��Ŀ
			if (source_file_unit_count <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit lock_simple_add_final(false);
				goto Delete_this_class_lock_add;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
			else
			{

			}
			source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
			if (head_offset_update > 0)//���ڼ������
			{
				char *source_file_data_head = new char[head_offset_update];//�������ļ�ͷ���Ǵ�������
				source_file.read(source_file_data_head, head_offset_update);//�����ļ�ͷ���Ǵ�������
				target_file.write(source_file_data_head, head_offset_update);//д���ļ�ͷ���Ǵ�������
				delete source_file_data_head;
			}
			else
			{

			}
			long long source_file_unit_count_include_temp = source_file_unit_count * FILE_LOCK_TAIL_SIZE_TIME_NUMBER;//���ǵ���Ҫ���ļ��������飬��������ʾ�õ����ļ��ܳ�����Ҫ���Ϻ����������Ŀ
			long long source_file_unit_count_double_lock = source_file_unit_count * FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER;//˫������ܣ���������ʾ�õ����ļ��ܳ���Ӧ�������μ��ܵ������ֵ���ܺ�
			int cycle_count = 0;//ѭ����Ԫ����
			int unit;//��������int��λ
			for (long long loop_count = 1; loop_count <= source_file_unit_count; loop_count++)//������Ļ��������������һ������Ԫ��ʼ��ȡ��ÿ�ζ�ȡһ������Ԫ֮ǰ���Ȱ��ļ�ָ���ƶ����õ�Ԫ��ʼλ��
			{
				source_file.clear();//����ļ�������������޷���λ
				source_file.seekg(source_file_unit_count * sizeof(int) + head_offset_update - loop_count * sizeof(int), ios_base::beg);//���ļ�ָ���ƶ�����ǰ����ȡ����Ԫ��ǰ��
				source_file.read((char*)&unit, sizeof(int));//��ȡ��ǰ��Ԫ����
				unit += unit_digit[cycle_count];//��Ԫ���ݼ���ָ����ֵ
				temp_file.write((char*)&unit, sizeof(unit));//������������ݣ���int�͸�ʽд�루4�ֽڣ�
				emit lock_simple_add_process((double)loop_count / (double)source_file_unit_count_include_temp);//�����źŸ������������ʹ��
				cycle_count++;
				if (cycle_count >= cycle)//ѭ�����ﵽ���ֵ������ѭ����
				{
					cycle_count = 0;
				}
				else
				{

				}
			
			}
			temp_file.close();//�ر��ļ�����ɾ��˳������̲�������ʱ�ļ�
			ifstream temp_file_rebuild(temp_file_path_str.c_str(), ios_base::in | ios_base::binary | ios_base::ate);//����ʱ�ļ�������������
			if (!temp_file_rebuild.is_open())
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit lock_simple_add_final(false);
				goto Delete_this_class_lock_add;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
			else
			{

			}
			for (long long loop_count = 1; loop_count <= source_file_unit_count; loop_count++)//�ļ�����ķ�����֮ǰ�ǰѴ���Ԫ�����������ʱ�ļ����棬������Ҫ�ӵ�һ������Ԫ��ʼ��ȡ������д��Ŀ���ļ�
			{
				temp_file_rebuild.clear();//����ļ�������������޷���λ
				temp_file_rebuild.seekg(source_file_unit_count * sizeof(int) - loop_count * sizeof(int), ios_base::beg);//���ļ�ָ���ƶ�����ǰ����ȡ����Ԫ��ǰ��
				temp_file_rebuild.read((char*)&unit, sizeof(int));//��ȡ��ǰ��Ԫ����
				target_file.write((char*)&unit, sizeof(unit));//������������ݣ���int�͸�ʽд�루4�ֽڣ�
				emit lock_simple_add_process((double)(loop_count + source_file_unit_count) / (double)source_file_unit_count_include_temp);//�����źŸ������������ʹ��
				cycle_count++;
				if (cycle_count >= cycle)//ѭ�����ﵽ���ֵ������ѭ����
				{
					cycle_count = 0;
				}
				else
				{

				}
			}
			if (tail_offset > 0)//���ڼ����յ㣬д���ļ�β���ݣ��������д��
			{
				source_file.clear();//c++�и����ԣ��ļ�ָ�뵽���ļ�β��ʹ���ļ�ָ��λ�ò�����������Ч����Ҫ��������ļ���
				source_file.seekg(source_file_unit_count * sizeof(int) + head_offset_update, ios_base::beg);//��Ϊ�Ƕ�ȡ�ļ�β�����ݣ������Ҫ���ƶ����ļ����������ݵ��ײ�
				char *source_file_data_tail = new char[tail_offset];//�������ļ�β���Ǵ�������
				source_file.read(source_file_data_tail, tail_offset);//�����ļ�β���Ǵ�������
				target_file.write(source_file_data_tail, tail_offset);//д���ļ�β���Ǵ�������
				delete source_file_data_tail;
			}
			else
			{

			}
			source_file.close();//�ر��ļ�
			target_file.close();
			temp_file_rebuild.close();
			int delete_succeed = remove(temp_file_path_str.c_str());//ɾ����ʱ�ļ�
		}
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
			if (direction == 1)//������ܷ���
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			else
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_2_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << head_offset << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//���ͷ�������ַ���
			key_file << FILE_KEY_WRITE_INFORMATION_7_STRING << tail_offset << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//���β�������ַ���
			key_file << FILE_KEY_WRITE_INFORMATION_8_STRING << cycle << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//���ѭ������
			key_file << FILE_KEY_WRITE_INFORMATION_10_STRING;//����Ӽ�����
			for (int index = 0; index < cycle; index++)
			{
				key_file << unit_digit[index];
				if (index < cycle - 1)//���������֮��ļ�����ţ����һ�β�����
				{
					key_file << FILE_KEY_WRITE_INFORMATION_10_1_STRING;
				}
				else
				{

				}
			}
			key_file << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//���ͷ����������
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ��ͷ�����ֲ�����ת����ԭʼ������ʾ
				magic_number_transform = (magic_number_transform.toHex()).toUpper();
				string magic_number_string(magic_number_transform.data(), FILE_HEAD_RAW_NUMBER_SIZE_NUMBER);
				key_file << FILE_KEY_WRITE_INFORMATION_9_STRING << magic_number_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			else
			{
				key_file << FILE_KEY_WRITE_INFORMATION_9_STRING << FILE_KEY_WRITE_INFORMATION_9_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
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
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_2_NUMBER;//��������
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//��ͷ���������ֱ��
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//��ͷ���������ֱ��
			key_file_binary << magic_number_string;//д��ͷ��ħ������
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//����������ͣ���int�͸�ʽд�루4�ֽڣ�
			key_file_binary.write((char*)(&direction), sizeof(direction));//������ܷ��򣬰�int�͸�ʽд�루4�ֽڣ�
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write((char*)(&head_offset), sizeof(head_offset));//���ͷ�������ַ�������long long�͸�ʽд�루8�ֽڣ�
			key_file_binary.write((char*)(&tail_offset), sizeof(tail_offset));//���β�������ַ�������long long�͸�ʽд�루8�ֽڣ�
			key_file_binary << interval_number_string;//д��ָ���
			key_file_binary.write((char*)(&cycle), sizeof(cycle));//����������ڣ���long long�͸�ʽд�루8�ֽڣ�
			for (int index = 0; index < cycle; index++)
			{
				key_file_binary.write((char*)&unit_digit[index], sizeof(unit_digit[index]));//�����żӼ���Ϣ������Ӽ���Ϣ�����ݣ���int�洢��4�ֽڣ�
			}
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
		emit lock_simple_add_final(true);
	Delete_this_class_lock_add://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

	void LockOpposite::unlock_add(const string & file_path, const string & file_name, const string & file_output_front_path, const string & file_output_back_path, bool is_output_history_file, const string & history_file_path, const string & temp_file_path, int direction, long long head_offset, long long tail_offset, int cycle, bool have_head_digit, char *head_digit, int *unit_digit)//�ļ�ȡ�����ܡ�����������ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺���Ƿ������ʷ�ļ��������ʷ�ļ�·������ʱ�ļ���·�������ܷ���1����˳��2������3����˫���򣩣�ͷ��������㣬β��������㣬ѭ�����ڣ�ע������ѭ������ָ���ǼӼ�ѭ����Ԫ��Ŀ��������ȡ�����ܵļ��ܼ��������Ҫ���м�1���������Ƿ���ͷ���������֣�ͷ���������֣���ѭ����λ�Ӽ�������Ϊ����16��int�͵����飩
	{

		//���ܹ��̣�����ѭ����Ԫ��Ŀ��ÿһ��ѭ���ڣ�����Ԫ��ȥ��Ӧλ�õļӼ�������Ȼ�������һѭ��
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//�����ܵ������ļ������󣬰������Ƹ�ʽ�򿪣���ʱ������ļ���β
		string target_file_path = file_output_front_path;//����ļ�·����ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//�����ļ����������Ƹ�ʽ�򿪣�û���򴴽���ע��goto�������������͵ĳ�ʼ����䣬��������ʼ��������ŵ�goto֮ǰ
		QDateTime current_date_time = QDateTime::currentDateTime();//��ȡ��ǰʱ��
		QString current_date_string = current_date_time.toString(FILE_TEMP_FILE_TIME_FORMAT_STRING);
		string temp_file_path_str = temp_file_path;//������ܺ�˫�����ʱ��Ҫ����ʱ�ļ�����ŵ�����ܽ����֮��Ը��ļ�������ݽ�������
		temp_file_path_str += FILE_FILE_INTERVAL_STRING;
		temp_file_path_str += string((const char *)current_date_string.toLocal8Bit());//����ʱ�ļ�·������ʱ���Ա�����̴߳���ʱ���ظ�����
		temp_file_path_str += FILE_TEMP_DOUBLE_FILE_BACK_PATH_STRING;
		if (!source_file.is_open())//�ļ���ʧ��
		{
			target_file.close();
			remove(target_file_path.c_str());//ɾ���ļ�
			emit unlock_simple_add_final(false);
			goto Delete_this_class_unlock_add;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
		}
		else
		{

		}
		long long source_file_unit_count;//�ļ���������Ҫ����ĵ�Ԫ��
		if (direction == 1)//˳�������
		{
			source_file_unit_count = source_file.tellg() - head_offset - tail_offset;//ȥ��ͷ����������β�������յ�ռ�õ�λ��
			if (have_head_digit)//ͷ����������У�顣��Ϊtellg()���ڶ�ȡ�ļ�֮ǰ��Ч������ȶ�ȡͷ���������ֻ���ɸú�����Ч
			{
				QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ�ý�����Ϣȷ�Ͻ����ṩ��ͷ�����ֲ�����ת����ԭʼ������ʾ
				key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
				QString key_head_digit_transform_string = key_head_digit_transform;//תΪQString
				source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
				char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//��������ļ�ͷ���������ֵ�char����
				source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ȡ�������֡�������Ҫע�⣬�����������Ϊȫ�ռ���00000000����ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char����
				QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
				source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
				QString source_head_digit_transform_string = source_head_digit_transform;//תΪQString
				if (key_head_digit_transform_string == source_head_digit_transform_string)//ͷ������������ͬ�����н���
				{
					source_file_unit_count -= FILE_HEAD_NUMBER_SIZE_NUMBER;//ȥ��ͷ����������ռ�õĿռ�

				}
				else//ͷ���������ֲ�ͬ��ȡ������
				{
					target_file.close();
					remove(target_file_path.c_str());//ɾ���ļ�
					emit unlock_simple_add_final(false);
					goto Delete_this_class_unlock_add;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
				}
			}
			else
			{

			}
			int tail_offset_update = tail_offset + source_file_unit_count % sizeof(int);//��ȡ��������β������һ��int���ȵĲ��֣�����β������
			long long int_size_temp = sizeof(int);//����ֱ��ʹ��source_file_unit_count/=sizeof(int)���������source_file_unit_countΪ��������ַǳ���Ľ��ֵ����������Ϊsizeof(int)Ϊunsigned long���ڶԽ��ת����ʱ�򣬸����ڲ�ͬ���������µı�ʾ��ͬ
			source_file_unit_count /= int_size_temp;//��ô����ܵ�Ԫ��Ŀ
			if (source_file_unit_count <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_simple_add_final(false);
				goto Delete_this_class_unlock_add;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
			else
			{

			}
			long long source_file_unit_count_double_lock = source_file_unit_count * FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER;//˫������ܣ���������ʾ�õ����ļ��ܳ���Ӧ�������μ��ܵ������ֵ���ܺ�
			source_file.clear();//����ļ�������������޷���λ
			if (have_head_digit)//�����ͷ���������֣�ע�ⲻ�ܽ���������д������ļ�
			{
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//���ļ�ָ��ƫ�Ƶ�ͷ����������֮��
			}
			else
			{
				source_file.seekg(ios_base::beg);//�ض����ļ�ָ��
			}
			if (head_offset > 0)//���ڼ������
			{
				char *source_file_data_head = new char[head_offset];//�������ļ�ͷ���Ǵ�������
				source_file.read(source_file_data_head, head_offset);//�����ļ�ͷ���Ǵ�������
				target_file.write(source_file_data_head, head_offset);//д���ļ�ͷ���Ǵ�������
				delete source_file_data_head;
			}
			else
			{

			}
			int cycle_count = 0;//ѭ����Ԫ����
			int unit;//��������int��λ
			for (long long loop_count = 1; loop_count <= source_file_unit_count; loop_count++)
			{
				source_file.read((char*)&unit, sizeof(int));//��ȡ��ǰ��Ԫ����
				unit -= unit_digit[cycle_count];//��Ԫ���ݼ���ָ����ֵ
				target_file.write((char*)&unit, sizeof(unit));//������������ݣ���int�͸�ʽд�루4�ֽڣ�
				emit unlock_simple_add_process((double)loop_count / (double)source_file_unit_count);//�����źŸ������������ʹ��
				cycle_count++;
				if (cycle_count >= cycle)//ѭ�����ﵽ���ֵ������ѭ����
				{
					cycle_count = 0;
				}
				else
				{

				}
			}
			if (tail_offset_update > 0)//���ڼ����յ㣬д���ļ�β���ݡ�˫�������д��
			{
				char *source_file_data_tail = new char[tail_offset_update];//�������ļ�β���Ǵ�������
				source_file.read(source_file_data_tail, tail_offset_update);//�����ļ�β���Ǵ�������
				target_file.write(source_file_data_tail, tail_offset_update);//д���ļ�β���Ǵ�������
				delete source_file_data_tail;
			}
			else
			{

			}
			source_file.close();
			target_file.close();
		}
		if (direction == 2)//���������
		{
			ofstream temp_file(temp_file_path_str, ios_base::out | ios_base::binary | ios_base::app);//��Ϊc++��֧�����ļ��м�������ݣ�ֻ����������ʱ�ļ���Ȼ��������ļ��ж���ʱ�ļ��е����ݽ�������
			source_file_unit_count = source_file.tellg() - head_offset - tail_offset;//ȥ��ͷ����������β�������յ�ռ�õ�λ��
			if (have_head_digit)//ͷ����������У�顣��Ϊtellg()���ڶ�ȡ�ļ�֮ǰ��Ч������ȶ�ȡͷ���������ֻ���ɸú�����Ч
			{
				QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//ȡ�ý�����Ϣȷ�Ͻ����ṩ��ͷ�����ֲ�����ת����ԭʼ������ʾ
				key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
				QString key_head_digit_transform_string = key_head_digit_transform;//תΪQString
				source_file.seekg(ios_base::beg);//���ļ�ָ��ƫ�Ƶ�������㴦����Ϊ֮ǰʹ��tellg����ʱ��Ҫ������ļ�ĩβ����ʱ�����Ƕ�ȡ�ļ���ɵ��ļ�ָ�����ļ�ĩβ������Ҫʹ��clear
				char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//��������ļ�ͷ���������ֵ�char����
				source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ȡ�������֡�������Ҫע�⣬�����������Ϊȫ�ռ���00000000����ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char����
				QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
				source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
				QString source_head_digit_transform_string = source_head_digit_transform;//תΪQString
				if (key_head_digit_transform_string == source_head_digit_transform_string)//ͷ������������ͬ�����н���
				{
					source_file_unit_count -= FILE_HEAD_NUMBER_SIZE_NUMBER;//ȥ��ͷ����������ռ�õĿռ�

				}
				else//ͷ���������ֲ�ͬ��ȡ������
				{
					target_file.close();
					remove(target_file_path.c_str());//ɾ���ļ�
					emit unlock_simple_add_final(false);
					goto Delete_this_class_unlock_add;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
				}
			}
			else
			{

			}
			int head_offset_update = head_offset + source_file_unit_count % sizeof(int);//��ȡ��������ͷ������һ��int���ȵĲ��֣�����ͷ������
			long long int_size_temp = sizeof(int);//����ֱ��ʹ��source_file_unit_count/=sizeof(int)���������source_file_unit_countΪ��������ַǳ���Ľ��ֵ����������Ϊsizeof(int)Ϊunsigned long���ڶԽ��ת����ʱ�򣬸����ڲ�ͬ���������µı�ʾ��ͬ
			source_file_unit_count /= int_size_temp;//��ô����ܵ�Ԫ��Ŀ
			if (source_file_unit_count <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_simple_add_final(false);
				goto Delete_this_class_unlock_add;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
			else
			{

			}
			source_file.clear();//����ļ�������������޷���λ
			if (have_head_digit)//�����ͷ���������֣�ע�ⲻ�ܽ���������д������ļ�
			{
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//���ļ�ָ��ƫ�Ƶ�ͷ����������֮��
			}
			else
			{
				source_file.seekg(ios_base::beg);//�ض����ļ�ָ��
			}
			if (head_offset_update > 0)//���ڼ������
			{
				char *source_file_data_head = new char[head_offset_update];//�������ļ�ͷ���Ǵ�������
				source_file.read(source_file_data_head, head_offset_update);//�����ļ�ͷ���Ǵ�������
				target_file.write(source_file_data_head, head_offset_update);//д���ļ�ͷ���Ǵ�������
				delete source_file_data_head;
			}
			else
			{

			}
			long long source_file_unit_count_include_temp = source_file_unit_count * FILE_LOCK_TAIL_SIZE_TIME_NUMBER;//���ǵ���Ҫ���ļ��������飬��������ʾ�õ����ļ��ܳ�����Ҫ���Ϻ����������Ŀ
			int cycle_count = 0;//ѭ����Ԫ����
			int unit;//��������int��λ
			for (long long loop_count = 1; loop_count <= source_file_unit_count; loop_count++)//������Ļ��������������һ������Ԫ��ʼ��ȡ��ÿ�ζ�ȡһ������Ԫ֮ǰ���Ȱ��ļ�ָ���ƶ����õ�Ԫ��ʼλ��
			{
				source_file.clear();//����ļ�������������޷���λ
				if (have_head_digit)//�����ͷ���������֣�ע�ⲻ�ܽ���������д������ļ�
				{
					source_file.seekg(source_file_unit_count * sizeof(int) + head_offset_update - loop_count * sizeof(int) + FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//���ļ�ָ���ƶ�����ǰ����ȡ����Ԫ��ǰ��
				}
				else
				{
					source_file.seekg(source_file_unit_count * sizeof(int) + head_offset_update - loop_count * sizeof(int), ios_base::beg);//���ļ�ָ���ƶ�����ǰ����ȡ����Ԫ��ǰ��
				}
				source_file.read((char*)&unit, sizeof(int));//��ȡ��ǰ��Ԫ����
				unit -= unit_digit[cycle_count];//��Ԫ���ݼ���ָ����ֵ
				temp_file.write((char*)&unit, sizeof(unit));//������������ݣ���int�͸�ʽд�루4�ֽڣ�
				emit unlock_simple_add_process((double)loop_count / (double)source_file_unit_count_include_temp);//�����źŸ������������ʹ��
				cycle_count++;
				if (cycle_count >= cycle)//ѭ�����ﵽ���ֵ������ѭ����
				{
					cycle_count = 0;
				}
				else
				{

				}

			}
			temp_file.close();//�ر��ļ�����ɾ��˳������̲�������ʱ�ļ�
			ifstream temp_file_rebuild(temp_file_path_str.c_str(), ios_base::in | ios_base::binary | ios_base::ate);//����ʱ�ļ�������������
			if (!temp_file_rebuild.is_open())
			{
				target_file.close();
				remove(target_file_path.c_str());//ɾ���ļ�
				emit unlock_simple_add_final(false);
				goto Delete_this_class_unlock_add;//���ڵ���ʱ�ڴ˴�ɾ������ָ��ᱨ����if����ֻ�ǳ����ӣ���ʹ����ת���ֱ����ת������ָ���ͷ���䴦
			}
			else
			{

			}
			for (long long loop_count = 1; loop_count <= source_file_unit_count; loop_count++)//�ļ�����ķ�����֮ǰ�ǰѴ���Ԫ�����������ʱ�ļ����棬������Ҫ�ӵ�һ������Ԫ��ʼ��ȡ������д��Ŀ���ļ�
			{
				temp_file_rebuild.clear();//����ļ�������������޷���λ
				temp_file_rebuild.seekg(source_file_unit_count * sizeof(int) - loop_count * sizeof(int), ios_base::beg);//���ļ�ָ���ƶ�����ǰ����ȡ����Ԫ��ǰ��
				temp_file_rebuild.read((char*)&unit, sizeof(int));//��ȡ��ǰ��Ԫ����
				target_file.write((char*)&unit, sizeof(unit));//������������ݣ���int�͸�ʽд�루4�ֽڣ�
				emit unlock_simple_add_process((double)(loop_count + source_file_unit_count) / (double)source_file_unit_count_include_temp);//�����źŸ������������ʹ��
				cycle_count++;
				if (cycle_count >= cycle)//ѭ�����ﵽ���ֵ������ѭ����
				{
					cycle_count = 0;
				}
				else
				{

				}
			}
			if (tail_offset > 0)//���ڼ����յ㣬д���ļ�β���ݣ��������д��
			{
				source_file.clear();//c++�и����ԣ��ļ�ָ�뵽���ļ�β��ʹ���ļ�ָ��λ�ò�����������Ч����Ҫ��������ļ���
				if (have_head_digit)
				{
					source_file.seekg(source_file_unit_count * sizeof(int) + head_offset_update + FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//��Ϊ�Ƕ�ȡ�ļ�β�����ݣ������Ҫ���ƶ����ļ����������ݵ��ײ�
				}
				else
				{
					source_file.seekg(source_file_unit_count * sizeof(int) + head_offset_update, ios_base::beg);//��Ϊ�Ƕ�ȡ�ļ�β�����ݣ������Ҫ���ƶ����ļ����������ݵ��ײ�
				}
				char *source_file_data_tail = new char[tail_offset];//�������ļ�β���Ǵ�������
				source_file.read(source_file_data_tail, tail_offset);//�����ļ�β���Ǵ�������
				target_file.write(source_file_data_tail, tail_offset);//д���ļ�β���Ǵ�������
				delete source_file_data_tail;
			}
			else
			{

			}
			source_file.close();//�ر��ļ�
			target_file.close();
			temp_file_rebuild.close();
			int delete_succeed = remove(temp_file_path_str.c_str());//ɾ����ʱ�ļ�
		}
		else
		{

		}
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
		emit unlock_simple_add_final(true);
	Delete_this_class_unlock_add://���ڴ�ĳ�ļ�ʧ��ʱ�����÷���ʱʹ��goto������ת��ǩ
		delete this;
	}

}

