#include "DllLockSimple.h"

//使用标准命名空间
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios_base;

//函数
namespace rem
{
	
	//dll主体函数
	void LockOpposite::lock_opposite(const string &file_path, const string & file_name, const string & file_output_front_path, const string & file_output_back_path, bool is_output_history_file, const string & history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string & key_file_path, const string & key_file_binary_path, const string & temp_file_path, int direction, long long head_offset, long long tail_offset, long long cycle, bool have_head_digit, char *head_digit)//文件取反加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，临时文件夹路径，加密方向（1代表顺序，2代表倒序，3代表双方向），头部处理起点，尾部处理起点，循环周期，是否有头部特征数字，头部特征数字
	{
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		string temp_file_double_path_str = temp_file_path;//双向加密时需要的临时文件，存放顺序加密结果
		temp_file_double_path_str += FILE_FILE_INTERVAL_STRING;
		QDateTime current_date_time = QDateTime::currentDateTime();//获取当前时间
		QString current_date_string = current_date_time.toString(FILE_TEMP_FILE_TIME_FORMAT_STRING);
		temp_file_double_path_str += string((const char *)current_date_string.toLocal8Bit());//将临时文件路径加上时间以避免多线程处理时的重复问题
		temp_file_double_path_str += FILE_TEMP_FILE_BACK_PATH_STRING;
		string temp_file_path_str = temp_file_path;//倒序加密和双向加密时需要的临时文件，存放倒序加密结果，之后对该文件里的内容进行重组
		temp_file_path_str += FILE_FILE_INTERVAL_STRING;
		temp_file_path_str += string((const char *)current_date_string.toLocal8Bit());//将临时文件路径加上时间以避免多线程处理时的重复问题
		temp_file_path_str += FILE_TEMP_DOUBLE_FILE_BACK_PATH_STRING;
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_simple_opposite_final(false);
			goto Delete_this_class_lock_opposite;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		if (have_head_digit)//根据情况加入头部特征数字
		{
			target_file.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//经过QByteArray转换为16进制编码后，字符串的长度减少一半，因为两个16进制数值表示一个字节
		}
		else
		{

		}
		long long source_file_size;//文件数据总需要处理的字节数
		if (direction == 1 || direction == 3)//顺序处理过程
		{
			ofstream temp_file_double(temp_file_double_path_str, ios_base::out | ios_base::binary);//双方向处理时需要额外打开临时文件
			source_file_size = source_file.tellg() - head_offset - tail_offset;//去掉头部处理起点和尾部处理终点占用的位置
			if (source_file_size <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit lock_simple_opposite_final(false);
				goto Delete_this_class_lock_opposite;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
			else
			{

			}
			long long source_file_size_double_lock = source_file_size * FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER;//双方向加密，进度条显示用到的文件总长度应该是两次加密的相关数值的总和
			source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
			if (head_offset > 0)//存在加密起点
			{
				char *source_file_data_head = new char[head_offset];//待加密文件头部非处理内容
				source_file.read(source_file_data_head, head_offset);//读入文件头部非处理内容
				target_file.write(source_file_data_head, head_offset);//写入文件头部非处理内容
				delete source_file_data_head;
			}
			else
			{

			}
			long long total_count = source_file_size / FILE_ONCE_MAX_SIZE_NUMBER;//总处理周期数，不包含最后一次
			long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
			char *source_file_data = new char[FILE_ONCE_MAX_SIZE_NUMBER];//待加密文件数据
			for (long long loop_count = 1; loop_count <= total_count; loop_count++)
			{
				int cycle_rest_count_temp = 0;//一个循环使用的一个周期剩余字节数临时变量
				source_file.read(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//读入FILE_ONCE_MAX_SIZE_NUMBER个字节
				for (int byte_position = 0; byte_position < FILE_ONCE_MAX_SIZE_NUMBER; byte_position++, cycle_rest_count_temp++)
				{
					if ((byte_position + cycle_rest_count) % (cycle + 1) == 0)//如果正在处理的位置加上前面周期剩下的cycle_rest_count能被处理周期整除，说明需要取反
					{
						source_file_data[byte_position] = ~source_file_data[byte_position];//指定字节取反
						cycle_rest_count_temp = 0;//因为已经处理，所以剩余量清零
					}
					else
					{

					}
				}
				cycle_rest_count = cycle_rest_count_temp;//临时变量保存
				if (direction == 1)
				{
					target_file.write(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//写入目标文件
				}
				else
				{
					temp_file_double.write(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//写入临时文件
				}
				if (direction == 1)
				{
					emit lock_simple_opposite_process((double)(FILE_ONCE_MAX_SIZE_NUMBER*loop_count) / (double)source_file_size);//发出信号给主界面进度条使用
				}
				else
				{
					emit lock_simple_opposite_process((double)(FILE_ONCE_MAX_SIZE_NUMBER*loop_count) / (double)source_file_size_double_lock);//发出信号给主界面进度条使用
				}
			}
			int rest_file_size_count = source_file_size % FILE_ONCE_MAX_SIZE_NUMBER;//进行最后一次处理，使用文件剩余未处理部分大小
			delete source_file_data;//释放内存
			if (rest_file_size_count > 0)//如果剩余字节数大于0才处理
			{
				char *source_file_data_rest = new char[rest_file_size_count];
				source_file.read(source_file_data_rest, rest_file_size_count);//读入rest_file_size_count个字节
				for (int byte_position = 0; byte_position < rest_file_size_count; byte_position++)
				{
					if ((byte_position + cycle_rest_count) % (cycle + 1) == 0)//如果正在处理的位置加上前面周期剩下的cycle_rest_count能被处理周期整除，说明需要取反
					{
						source_file_data_rest[byte_position] = ~source_file_data_rest[byte_position];//指定字节取反
					}
				}
				if (direction == 1)
				{
					target_file.write(source_file_data_rest, rest_file_size_count);//写入目标文件
				}
				else
				{
					temp_file_double.write(source_file_data_rest, rest_file_size_count);//写入临时文件
				}
				delete source_file_data_rest;//释放内存
			}
			if (tail_offset > 0 && direction == 1)//存在加密终点，写入文件尾内容。双向加密则不写入
			{
				char *source_file_data_tail = new char[tail_offset];//待加密文件尾部非处理内容
				source_file.read(source_file_data_tail, tail_offset);//读入文件尾部非处理内容
				target_file.write(source_file_data_tail, tail_offset);//写入文件尾部非处理内容
				delete source_file_data_tail;
			}
			else
			{

			}
			if (direction == 1)//关闭文件
			{
				source_file.close();
				target_file.close();
				temp_file_double.close();
				int delete_succeed = remove(temp_file_double_path_str.c_str());//仅顺序加密不需要临时文件
			}
			else
			{
				temp_file_double.close();
			}
		}
		else
		{

		}
		if (direction == 2 || direction == 3)//倒序处理过程
		{
			ifstream temp_file_double(temp_file_double_path_str, ios_base::in | ios_base::binary | ios_base::ate);//处理临时文件，按二进制格式打开，打开时光标在文件结尾
			if ((!temp_file_double.is_open()) && direction == 3)//临时文件打开失败
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit lock_simple_opposite_final(false);
				goto Delete_this_class_lock_opposite;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
			else
			{

			}
			ofstream temp_file(temp_file_path_str, ios_base::out | ios_base::binary | ios_base::app);//因为c++不支持在文件中间插入内容，只能先生成临时文件，然后在输出文件中对临时文件中的内容进行重组
			if (direction == 2)
			{
				source_file_size = source_file.tellg() - head_offset - tail_offset;//去掉头部处理起点和尾部处理终点占用的位置
			}
			else
			{
				source_file_size = temp_file_double.tellg();//临时文件不含头尾不加密部分
			}
			if (source_file_size <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit lock_simple_opposite_final(false);
				goto Delete_this_class_lock_opposite;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
			else
			{

			}
			source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
			if (head_offset > 0 && direction == 2)//存在加密起点，如果是双向加密则不写入
			{
				char *source_file_data_head = new char[head_offset];//待加密文件头部非处理内容
				source_file.read(source_file_data_head, head_offset);//读入文件头部非处理内容
				target_file.write(source_file_data_head, head_offset);//写入文件头部非处理内容
				delete source_file_data_head;
			}
			else
			{

			}
			long long total_count = source_file_size / FILE_ONCE_MAX_SIZE_NUMBER;//总处理周期数，不包含最后一次
			int rest_file_size_count = source_file_size % FILE_ONCE_MAX_SIZE_NUMBER;//进行最后一次处理，使用文件剩余未处理部分大小
			long long source_file_size_include_temp = source_file_size * FILE_LOCK_TAIL_SIZE_TIME_NUMBER;//考虑到需要对文件进行重组，进度条显示用到的文件总长度需要加上后续重组的数目
			long long source_file_size_double_lock = source_file_size * FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER;//双方向加密，进度条显示用到的文件总长度应该是两次加密的相关数值的总和
			long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
			char *source_file_data = new char[FILE_ONCE_MAX_SIZE_NUMBER];//待加密文件数据
			for (long long loop_count = 1; loop_count <= total_count; loop_count++)//倒序处理的基本方法：从最后一个文件块开始读取。每次读取一个文件块之前，先把文件指针移动到该文件块起始位置
			{
				if (direction == 2)
				{
					source_file.clear();//清空文件流，否则可能无法定位
					source_file.seekg(source_file_size + head_offset - loop_count * FILE_ONCE_MAX_SIZE_NUMBER, ios_base::beg);//将文件指针移动到当前待读取文件块的前面
				}
				else
				{
					temp_file_double.clear();//清空文件流，否则可能无法定位
					temp_file_double.seekg(source_file_size - loop_count * FILE_ONCE_MAX_SIZE_NUMBER, ios_base::beg);//将文件指针移动到当前待读取文件块的前面
				}
				int cycle_rest_count_temp = 0;//一个循环使用的一个周期剩余字节数临时变量
				if (direction == 2)
				{
					source_file.read(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//读入FILE_ONCE_MAX_SIZE_NUMBER个字节
				}
				else
				{
					temp_file_double.read(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//读入FILE_ONCE_MAX_SIZE_NUMBER个字节
				}
				for (int byte_position = FILE_ONCE_MAX_SIZE_NUMBER - 1, position_count = 0; byte_position > -1; byte_position--, cycle_rest_count_temp++, position_count++)//文件块内部同样需要倒序处理。为保证加密位置正确，须引入一个相对于顺序索引时的位置变量position_count来指定加密位置。此外还需要注意c++不支持在for循环的初始化语句中初始化多个类型的变量
				{
					if ((position_count + cycle_rest_count) % (cycle + 1) == 0)//如果正在处理的位置加上前面周期剩下的cycle_rest_count能被处理周期整除，说明需要取反
					{
						source_file_data[byte_position] = ~source_file_data[byte_position];//指定字节取反
						cycle_rest_count_temp = 0;//因为已经处理，所以剩余量清零
					}
					else
					{

					}
				}
				cycle_rest_count = cycle_rest_count_temp;//临时变量保存
				temp_file.write(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//写入临时文件
				if (direction == 2)
				{
					emit lock_simple_opposite_process((double)(FILE_ONCE_MAX_SIZE_NUMBER*loop_count) / (double)source_file_size_include_temp);//发出信号给主界面进度条使用
				}
				else
				{
					emit lock_simple_opposite_process((double)(source_file_size + (FILE_ONCE_MAX_SIZE_NUMBER*loop_count)) / (double)source_file_size_double_lock);//发出信号给主界面进度条使用
				}
			}
			delete source_file_data;//释放内存
			if (rest_file_size_count > 0)//如果剩余字节数大于0才处理
			{
				if (direction == 2)
				{
					source_file.clear();//清空文件流，否则可能无法定位
					source_file.seekg(ios_base::beg + head_offset);//读取文件指针定位
				}
				else
				{
					temp_file_double.clear();//清空文件流，否则可能无法定位
					temp_file_double.seekg(ios_base::beg);//读取文件指针定位
				}
				char *source_file_data_rest = new char[rest_file_size_count];
				if (direction == 2)
				{
					source_file.read(source_file_data_rest, rest_file_size_count);//读入rest_file_size_count个字节
				}
				else
				{
					temp_file_double.read(source_file_data_rest, rest_file_size_count);//读入rest_file_size_count个字节
				}
				for (int byte_position = rest_file_size_count - 1, position_count = 0; byte_position > -1; byte_position--, position_count++)
				{
					if ((position_count + cycle_rest_count) % (cycle + 1) == 0)//如果正在处理的位置加上前面周期剩下的cycle_rest_count能被处理周期整除，说明需要取反
					{
						source_file_data_rest[byte_position] = ~source_file_data_rest[byte_position];//指定字节取反
					}
				}
				temp_file.write(source_file_data_rest, rest_file_size_count);//写入临时文件
				delete source_file_data_rest;//释放内存
			}
			else
			{

			}
			temp_file.close();//关闭文件，并删除顺序处理过程产生的临时文件
			temp_file_double.close();
			int delete_succeed = remove(temp_file_double_path_str.c_str());
			ifstream temp_file_rebuild(temp_file_path_str.c_str(), ios_base::in | ios_base::binary | ios_base::ate);//打开临时文件进行内容重组
			if(!temp_file_rebuild.is_open())
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit lock_simple_opposite_final(false);
				goto Delete_this_class_lock_opposite;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
			else
			{

			}
			if (rest_file_size_count > 0)//文件重组的方法：之前是把文件块倒序放在了临时文件里面，现在需要从第一个文件块开始读取并将其写入目标文件。首先处理最后不完整文件块的部分
			{
				char *temp_file_data_rest = new char[rest_file_size_count];//申请存放数据的内存空间
				temp_file_rebuild.clear();//清空文件流，否则可能无法定位
				temp_file_rebuild.seekg(source_file_size - rest_file_size_count, ios_base::beg);//读取文件指针定位到最后一个不完整文件块的位置
				temp_file_rebuild.read(temp_file_data_rest, rest_file_size_count);//读入rest_file_size_count个字节
				target_file.write(temp_file_data_rest, rest_file_size_count);//写入目标文件
				delete temp_file_data_rest;//释放内存
			}
			else
			{

			}
			char *temp_file_data = new char[FILE_ONCE_MAX_SIZE_NUMBER];//申请存放数据的内存空间
			for (long long loop_count = 1; loop_count <= total_count; loop_count++)//处理加密部分的剩余部分，这部分由若干完整文件块组成
			{
				temp_file_rebuild.clear();//清空文件流，否则可能无法定位
				temp_file_rebuild.seekg(source_file_size  - rest_file_size_count - loop_count * FILE_ONCE_MAX_SIZE_NUMBER, ios_base::beg);//将文件指针移动到当前待读取文件块的前面
				temp_file_rebuild.read(temp_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//读入FILE_ONCE_MAX_SIZE_NUMBER个字节
				target_file.write(temp_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//写入目标文件
				if (direction == 2)
				{
					emit lock_simple_opposite_process((double)(source_file_size + (FILE_ONCE_MAX_SIZE_NUMBER*loop_count)) / (double)source_file_size_include_temp);//仍然发出信号给主界面进度条使用。需要加上之前已经处理的部分
				}
				else
				{
					emit lock_simple_opposite_process((double)(source_file_size + source_file_size + (FILE_ONCE_MAX_SIZE_NUMBER*loop_count)) / (double)source_file_size_include_temp);//仍然发出信号给主界面进度条使用。需要加上之前已经处理的部分
				}
			}
			delete temp_file_data;
			if (tail_offset > 0)//存在加密终点，写入文件尾内容，必须最后写入
			{
				source_file.clear();//c++有个特性，文件指针到达文件尾后，使用文件指针位置操作函数将无效，需要事先清空文件流
				source_file.seekg(source_file_size + head_offset, ios_base::beg);//因为是读取文件尾部内容，因此需要先移动到文件不处理内容的首部
				char *source_file_data_tail = new char[tail_offset];//待加密文件尾部非处理内容
				source_file.read(source_file_data_tail, tail_offset);//读入文件尾部非处理内容
				target_file.write(source_file_data_tail, tail_offset);//写入文件尾部非处理内容
				delete source_file_data_tail;
			}
			else
			{

			}
			source_file.close();//关闭文件
			target_file.close();
			temp_file_rebuild.close();
			delete_succeed = remove(temp_file_path_str.c_str());//删除临时文件
		}
		else
		{

		}
		if (is_output_history_file)//需要写入历史文件
		{
			time_t system_time;//存储系统时间
			time(&system_time);//获取系统时间
			struct tm *time_struct = localtime(&system_time);//获取指向时间结构体的指针
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//历史文件使用附加方式打开
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//输出相应内容。这里为时间
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//按格式输出时间
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//输出文件名
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//输出文件路径
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_2_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出操作
			history_file.close();
		}
		else
		{

		}
		if (is_output_key_file)//需要生成密钥文件
		{
			string key_file_total_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_path += file_name;//密钥文件输出路径
			key_file_total_path += key_file_path;
			ofstream key_file(key_file_total_path, ios_base::out);//处理文本类型的密钥文件，使用覆盖方式打开
			key_file << FILE_KEY_WRITE_INFORMATION_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出相应内容。这里为密钥文件头部内容
			key_file << FILE_KEY_WRITE_INFORMATION_2_STRING << file_name << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出文件名
			key_file << FILE_KEY_WRITE_INFORMATION_3_STRING << file_path << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出文件路径
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出加密类型
			if (direction == 1)//输出加密方向
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
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << head_offset << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出头部忽略字符数
			key_file << FILE_KEY_WRITE_INFORMATION_7_STRING << tail_offset << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出尾部忽略字符数
			key_file << FILE_KEY_WRITE_INFORMATION_8_STRING << cycle << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出循环周期
			if (have_head_digit)//输出头部特征数字
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得头部数字并将其转换回原始数据显示
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
		if (is_output_key_file_binary)//需要生成二进制密钥文件
		{
			string key_file_total_binary_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_binary_path += file_name;//密钥文件输出路径
			key_file_total_binary_path += key_file_binary_path;
			ofstream key_file_binary(key_file_total_binary_path, ios_base::binary | ios_base::out);//处理二进制类型的密钥文件，使用覆盖方式打开
			QByteArray magic_number = FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING;//等待加入的头部魔术数字
			QByteArray interval_number = FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING;//二进制文件分隔符
			QByteArray interval_short_number = FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING;//二进制文件短分隔符
			magic_number = QByteArray::fromHex(magic_number);//转化为16进制编码
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			string magic_number_string(magic_number.constData(), magic_number.length());//QByteArray转string
			string interval_number_string(interval_number.constData(), interval_number.length());
			string interval_short_number_string(interval_short_number.constData(), interval_short_number.length());
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_1_NUMBER;//加密类型
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//无头部特征数字标记
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//有头部特征数字标记
			key_file_binary << magic_number_string;//写入头部魔术数字
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//输出加密类型，按int型格式写入（4字节）
			key_file_binary.write((char*)(&direction), sizeof(direction));//输出加密方向，按int型格式写入（4字节）
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write((char*)(&head_offset), sizeof(head_offset));//输出头部忽略字符数，按long long型格式写入（8字节）
			key_file_binary.write((char*)(&tail_offset), sizeof(tail_offset));//输出尾部忽略字符数，按long long型格式写入（8字节）
			key_file_binary.write((char*)(&cycle), sizeof(cycle));//输出加密周期，按long long型格式写入（8字节）
			key_file_binary << interval_number_string;//写入分隔符
			if (have_head_digit)//写入头部特征数字信息
			{
				key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//输出有头部特征数字标记，按int型格式写入（4字节）
				key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//写入头部特征数字
			}
			else
			{
				key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//输出无头部特征数字标记，按int型格式写入（4字节）
				key_file_binary << interval_short_number_string;//写入相应位数的分隔符占位
			}
			key_file_binary << interval_number_string;//写入分隔符
			int file_name_length = file_name.length();//文件名长度
			int file_path_length = file_path.length();//文件路径长度
			key_file_binary.write((char*)(&file_name_length), sizeof(file_name_length));//输出文件名长度，按int型格式写入（4字节）
			key_file_binary << file_name;//写入文件名
			key_file_binary.write((char*)(&file_path_length), sizeof(file_path_length));//输出文件路径长度，按int型格式写入（4字节）
			key_file_binary << file_path;//写入文件路径
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.close();
		}
		else
		{

		}
		emit lock_simple_opposite_final(true);
	Delete_this_class_lock_opposite://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockOpposite::unlock_opposite(const string & file_path, const string & file_name, const string & file_output_front_path, const string & file_output_back_path, bool is_output_history_file, const string & history_file_path, const string & temp_file_path, int direction, long long head_offset, long long tail_offset, long long cycle, bool have_head_digit, char *head_digit)//文件取反解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，临时文件夹路径，加密方向（1代表顺序，2代表倒序，3代表双方向），头部处理起点，尾部处理起点，循环周期，是否有头部特征数字，头部特征数字
	{
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待解密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		string temp_file_double_path_str = temp_file_path;//双向加密时需要的临时文件，存放顺序加密结果
		temp_file_double_path_str += FILE_FILE_INTERVAL_STRING;
		QDateTime current_date_time = QDateTime::currentDateTime();//获取当前时间
		QString current_date_string = current_date_time.toString(FILE_TEMP_FILE_TIME_FORMAT_STRING);
		temp_file_double_path_str += string((const char *)current_date_string.toLocal8Bit());//将临时文件路径加上时间以避免多线程处理时的重复问题
		temp_file_double_path_str += FILE_TEMP_FILE_BACK_PATH_STRING;
		string temp_file_path_str = temp_file_path;//倒序加密和双向加密时需要的临时文件，存放倒序加密结果，之后对该文件里的内容进行重组
		temp_file_path_str += FILE_FILE_INTERVAL_STRING;
		temp_file_path_str += string((const char *)current_date_string.toLocal8Bit());//将临时文件路径加上时间以避免多线程处理时的重复问题
		temp_file_path_str += FILE_TEMP_DOUBLE_FILE_BACK_PATH_STRING;
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_simple_opposite_final(false);
			goto Delete_this_class_unlock_opposite;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		long long source_file_size;//文件数据总需要处理的字节数
		if (direction == 1 || direction == 3)//顺序处理过程
		{
			ofstream temp_file_double(temp_file_double_path_str, ios_base::out | ios_base::binary);//双方向处理时需要额外打开临时文件
			source_file_size = source_file.tellg() - head_offset - tail_offset;//去掉头部处理起点和尾部处理终点占用的位置
			if (have_head_digit)//头部特征数字校验。因为tellg()仅在读取文件之前有效，如果先读取头部特征数字会造成该函数无效
			{
				QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得解密信息确认界面提供的头部数字并将其转换回原始数据显示
				key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
				QString key_head_digit_transform_string = key_head_digit_transform;//转为QString
				source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
				char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//存放输入文件头部特征数字的char数组
				source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//读取特征数字。这里需要注意，如果特征数字为全空即“00000000”的时候，使用动态数组则会出现数组长度为0的情况，因此需要用固定长度的char数组
				QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//存放加密文件头部魔法数字的十六进制数据
				source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//获得十六进制数据，转换为大写
				QString source_head_digit_transform_string = source_head_digit_transform;//转为QString
				if (key_head_digit_transform_string == source_head_digit_transform_string)//头部特征数字相同，进行解密
				{
					source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//去掉头部特征数字占用的空间
				}
				else//头部特征数字不同，取消解密
				{
					target_file.close();
					remove(target_file_path.c_str());//删除文件
					emit unlock_simple_opposite_final(false);
					goto Delete_this_class_unlock_opposite;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
				}
			}
			else
			{

			}
			if (source_file_size <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_simple_opposite_final(false);
				goto Delete_this_class_unlock_opposite;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
			else
			{

			}
			long long source_file_size_double_lock = source_file_size * FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER;//双方向加密，进度条显示用到的文件总长度应该是两次加密的相关数值的总和
			source_file.clear();//清空文件流，否则可能无法定位
			if (have_head_digit)//如果开头有特征数字，注意不能将特征数字写入解密文件
			{
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//将文件指针偏移到头部特征数字之后
			}
			else
			{
				source_file.seekg(ios_base::beg);//重定向文件指针
			}
			if (head_offset > 0)//存在加密起点
			{
				char *source_file_data_head = new char[head_offset];//待加密文件头部非处理内容
				source_file.read(source_file_data_head, head_offset);//读入文件头部非处理内容
				target_file.write(source_file_data_head, head_offset);//写入文件头部非处理内容
				delete source_file_data_head;
			}
			else
			{

			}
			long long total_count = source_file_size / FILE_ONCE_MAX_SIZE_NUMBER;//总处理周期数，不包含最后一次
			long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
			char *source_file_data = new char[FILE_ONCE_MAX_SIZE_NUMBER];//待加密文件数据
			for (long long loop_count = 1; loop_count <= total_count; loop_count++)
			{
				int cycle_rest_count_temp = 0;//一个循环使用的一个周期剩余字节数临时变量
				source_file.read(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//读入FILE_ONCE_MAX_SIZE_NUMBER个字节
				for (int byte_position = 0; byte_position < FILE_ONCE_MAX_SIZE_NUMBER; byte_position++, cycle_rest_count_temp++)
				{
					if ((byte_position + cycle_rest_count) % (cycle + 1) == 0)//如果正在处理的位置加上前面周期剩下的cycle_rest_count能被处理周期整除，说明需要取反
					{
						source_file_data[byte_position] = ~source_file_data[byte_position];//指定字节取反
						cycle_rest_count_temp = 0;//因为已经处理，所以剩余量清零
					}
					else
					{

					}
				}
				cycle_rest_count = cycle_rest_count_temp;//临时变量保存
				if (direction == 1)
				{
					target_file.write(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//写入目标文件
				}
				else
				{
					temp_file_double.write(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//写入临时文件
				}
				if (direction == 1)
				{
					emit unlock_simple_opposite_process((double)(FILE_ONCE_MAX_SIZE_NUMBER*loop_count) / (double)source_file_size);//发出信号给主界面进度条使用
				}
				else
				{
					emit unlock_simple_opposite_process((double)(FILE_ONCE_MAX_SIZE_NUMBER*loop_count) / (double)source_file_size_double_lock);//发出信号给主界面进度条使用
				}
			}
			int rest_file_size_count = source_file_size % FILE_ONCE_MAX_SIZE_NUMBER;//进行最后一次处理，使用文件剩余未处理部分大小
			delete source_file_data;//释放内存
			if (rest_file_size_count > 0)//如果剩余字节数大于0才处理
			{
				char *source_file_data_rest = new char[rest_file_size_count];
				source_file.read(source_file_data_rest, rest_file_size_count);//读入rest_file_size_count个字节
				for (int byte_position = 0; byte_position < rest_file_size_count; byte_position++)
				{
					if ((byte_position + cycle_rest_count) % (cycle + 1) == 0)//如果正在处理的位置加上前面周期剩下的cycle_rest_count能被处理周期整除，说明需要取反
					{
						source_file_data_rest[byte_position] = ~source_file_data_rest[byte_position];//指定字节取反
					}
				}
				if (direction == 1)
				{
					target_file.write(source_file_data_rest, rest_file_size_count);//写入目标文件
				}
				else
				{
					temp_file_double.write(source_file_data_rest, rest_file_size_count);//写入临时文件
				}
				delete source_file_data_rest;//释放内存
			}
			if (tail_offset > 0 && direction == 1)//存在加密终点，写入文件尾内容。双向加密则不写入
			{
				char *source_file_data_tail = new char[tail_offset];//待加密文件尾部非处理内容
				source_file.read(source_file_data_tail, tail_offset);//读入文件尾部非处理内容
				target_file.write(source_file_data_tail, tail_offset);//写入文件尾部非处理内容
				delete source_file_data_tail;
			}
			else
			{

			}
			if (direction == 1)//关闭文件
			{
				source_file.close();
				target_file.close();
				temp_file_double.close();
				int delete_succeed = remove(temp_file_double_path_str.c_str());//仅顺序加密不需要临时文件
			}
			else
			{
				temp_file_double.close();
			}
		}
		else
		{

		}
		if (direction == 2 || direction == 3)//倒序处理过程
		{
			ifstream temp_file_double(temp_file_double_path_str, ios_base::in | ios_base::binary | ios_base::ate);//处理临时文件，按二进制格式打开，打开时光标在文件结尾
			if ((!temp_file_double.is_open()) && direction == 3)//临时文件打开失败
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_simple_opposite_final(false);
				goto Delete_this_class_unlock_opposite;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
			else
			{

			}
			ofstream temp_file(temp_file_path_str, ios_base::out | ios_base::binary | ios_base::app);//因为c++不支持在文件中间插入内容，只能先生成临时文件，然后在输出文件中对临时文件中的内容进行重组
			if (direction == 2)//双方向的已经在前面处理过了，只需要处理倒序解密的头部特征数字
			{
				source_file_size = source_file.tellg() - head_offset - tail_offset;//去掉头部处理起点和尾部处理终点占用的位置
				if (have_head_digit)//头部特征数字校验。因为tellg()仅在读取文件之前有效，如果先读取头部特征数字会造成该函数无效
				{
					QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得解密信息确认界面提供的头部数字并将其转换回原始数据显示
					key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
					QString key_head_digit_transform_string = key_head_digit_transform;//转为QString
					source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
					char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//存放输入文件头部特征数字的char数组
					source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//读取特征数字。这里需要注意，如果特征数字为全空即“00000000”的时候，使用动态数组则会出现数组长度为0的情况，因此需要用固定长度的char数组
					QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//存放加密文件头部魔法数字的十六进制数据
					source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//获得十六进制数据，转换为大写
					QString source_head_digit_transform_string = source_head_digit_transform;//转为QString
					if (key_head_digit_transform_string == source_head_digit_transform_string)//头部特征数字相同，进行解密
					{
						source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//去掉头部特征数字占用的空间

					}
					else//头部特征数字不同，取消解密
					{
						target_file.close();
						remove(target_file_path.c_str());//删除文件
						emit unlock_simple_opposite_final(false);
						goto Delete_this_class_unlock_opposite;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
					}
				}
				else
				{

				}
			}
			else
			{
				source_file_size = temp_file_double.tellg();//临时文件不含头尾不加密部分
			}
			if (source_file_size <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_simple_opposite_final(false);
				goto Delete_this_class_unlock_opposite;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
			else
			{

			}
			source_file.clear();//清空文件流，否则可能无法定位
			if (have_head_digit)//如果开头有特征数字，注意不能将特征数字写入解密文件
			{
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//将文件指针偏移到头部特征数字之后
			}
			else
			{
				source_file.seekg(ios_base::beg);//重定向文件指针
			}
			if (head_offset > 0 && direction == 2)//存在加密起点，如果是双向加密则不写入
			{
				char *source_file_data_head = new char[head_offset];//待加密文件头部非处理内容
				source_file.read(source_file_data_head, head_offset);//读入文件头部非处理内容
				target_file.write(source_file_data_head, head_offset);//写入文件头部非处理内容
				delete source_file_data_head;
			}
			else
			{

			}
			long long total_count = source_file_size / FILE_ONCE_MAX_SIZE_NUMBER;//总处理周期数，不包含最后一次
			int rest_file_size_count = source_file_size % FILE_ONCE_MAX_SIZE_NUMBER;//进行最后一次处理，使用文件剩余未处理部分大小
			long long source_file_size_include_temp = source_file_size * FILE_LOCK_TAIL_SIZE_TIME_NUMBER;//考虑到需要对文件进行重组，进度条显示用到的文件总长度需要加上后续重组的数目
			long long source_file_size_double_lock = source_file_size * FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER;//双方向加密，进度条显示用到的文件总长度应该是两次加密的相关数值的总和
			long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
			char *source_file_data = new char[FILE_ONCE_MAX_SIZE_NUMBER];//待加密文件数据
			for (long long loop_count = 1; loop_count <= total_count; loop_count++)//倒序处理的基本方法：从最后一个文件块开始读取。每次读取一个文件块之前，先把文件指针移动到该文件块起始位置
			{
				if (direction == 2)
				{
					source_file.clear();//清空文件流，否则可能无法定位
					if (have_head_digit)//如果开头有特征数字，注意不能将特征数字写入解密文件
					{
						source_file.seekg(source_file_size + head_offset - loop_count * FILE_ONCE_MAX_SIZE_NUMBER + FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//将文件指针移动到当前待读取文件块的前面，需要考虑头部特征数字
					}
					else
					{
						source_file.seekg(source_file_size + head_offset - loop_count * FILE_ONCE_MAX_SIZE_NUMBER, ios_base::beg);//将文件指针移动到当前待读取文件块的前面
					}
				}
				else
				{
					temp_file_double.clear();//清空文件流，否则可能无法定位
					temp_file_double.seekg(source_file_size - loop_count * FILE_ONCE_MAX_SIZE_NUMBER, ios_base::beg);//将文件指针移动到当前待读取文件块的前面
				}
				int cycle_rest_count_temp = 0;//一个循环使用的一个周期剩余字节数临时变量
				if (direction == 2)
				{
					source_file.read(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//读入FILE_ONCE_MAX_SIZE_NUMBER个字节
				}
				else
				{
					temp_file_double.read(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//读入FILE_ONCE_MAX_SIZE_NUMBER个字节
				}
				for (int byte_position = FILE_ONCE_MAX_SIZE_NUMBER - 1, position_count = 0; byte_position > -1; byte_position--, cycle_rest_count_temp++, position_count++)//文件块内部同样需要倒序处理。为保证加密位置正确，须引入一个相对于顺序索引时的位置变量position_count来指定加密位置。此外还需要注意c++不支持在for循环的初始化语句中初始化多个类型的变量
				{
					if ((position_count + cycle_rest_count) % (cycle + 1) == 0)//如果正在处理的位置加上前面周期剩下的cycle_rest_count能被处理周期整除，说明需要取反
					{
						source_file_data[byte_position] = ~source_file_data[byte_position];//指定字节取反
						cycle_rest_count_temp = 0;//因为已经处理，所以剩余量清零
					}
					else
					{

					}
				}
				cycle_rest_count = cycle_rest_count_temp;//临时变量保存
				temp_file.write(source_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//写入临时文件
				if (direction == 2)
				{
					emit unlock_simple_opposite_process((double)(FILE_ONCE_MAX_SIZE_NUMBER*loop_count) / (double)source_file_size_include_temp);//发出信号给主界面进度条使用
				}
				else
				{
					emit unlock_simple_opposite_process((double)(source_file_size + (FILE_ONCE_MAX_SIZE_NUMBER*loop_count)) / (double)source_file_size_double_lock);//发出信号给主界面进度条使用
				}
			}
			delete source_file_data;//释放内存
			if (rest_file_size_count > 0)//如果剩余字节数大于0才处理
			{
				if (direction == 2)
				{
					source_file.clear();//清空文件流，否则可能无法定位
					source_file.clear();//清空文件流，否则可能无法定位
					if (have_head_digit)//如果开头有特征数字，注意不能将特征数字写入解密文件
					{
						source_file.seekg(ios_base::beg + head_offset + FILE_HEAD_NUMBER_SIZE_NUMBER);//读取文件指针定位，需要考虑头部特征数字
					}
					else
					{
						source_file.seekg(ios_base::beg + head_offset);//读取文件指针定位
					}
				}
				else
				{
					temp_file_double.clear();//清空文件流，否则可能无法定位
					temp_file_double.seekg(ios_base::beg);//读取文件指针定位
				}
				char *source_file_data_rest = new char[rest_file_size_count];
				if (direction == 2)
				{
					source_file.read(source_file_data_rest, rest_file_size_count);//读入rest_file_size_count个字节
				}
				else
				{
					temp_file_double.read(source_file_data_rest, rest_file_size_count);//读入rest_file_size_count个字节
				}
				for (int byte_position = rest_file_size_count - 1, position_count = 0; byte_position > -1; byte_position--, position_count++)
				{
					if ((position_count + cycle_rest_count) % (cycle + 1) == 0)//如果正在处理的位置加上前面周期剩下的cycle_rest_count能被处理周期整除，说明需要取反
					{
						source_file_data_rest[byte_position] = ~source_file_data_rest[byte_position];//指定字节取反
					}
				}
				temp_file.write(source_file_data_rest, rest_file_size_count);//写入临时文件
				delete source_file_data_rest;//释放内存
			}
			else
			{

			}
			temp_file.close();//关闭文件，并删除顺序处理过程产生的临时文件
			temp_file_double.close();
			int delete_succeed = remove(temp_file_double_path_str.c_str());
			ifstream temp_file_rebuild(temp_file_path_str, ios_base::in | ios_base::binary | ios_base::ate);//打开临时文件进行内容重组
			if (!temp_file_rebuild.is_open())
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_simple_opposite_final(false);
				goto Delete_this_class_unlock_opposite;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
			else
			{

			}
			if (rest_file_size_count > 0)//文件重组的方法：之前是把文件块倒序放在了临时文件里面，现在需要从第一个文件块开始读取并将其写入目标文件。首先处理最后不完整文件块的部分
			{
				char *temp_file_data_rest = new char[rest_file_size_count];//申请存放数据的内存空间
				temp_file_rebuild.clear();//清空文件流，否则可能无法定位
				temp_file_rebuild.seekg(source_file_size - rest_file_size_count, ios_base::beg);//读取文件指针定位到最后一个不完整文件块的位置
				temp_file_rebuild.read(temp_file_data_rest, rest_file_size_count);//读入rest_file_size_count个字节
				target_file.write(temp_file_data_rest, rest_file_size_count);//写入目标文件
				delete temp_file_data_rest;//释放内存
			}
			else
			{

			}
			char *temp_file_data = new char[FILE_ONCE_MAX_SIZE_NUMBER];//申请存放数据的内存空间
			for (long long loop_count = 1; loop_count <= total_count; loop_count++)//处理加密部分的剩余部分，这部分由若干完整文件块组成
			{
				temp_file_rebuild.clear();//清空文件流，否则可能无法定位
				temp_file_rebuild.seekg(source_file_size - rest_file_size_count - loop_count * FILE_ONCE_MAX_SIZE_NUMBER, ios_base::beg);//将文件指针移动到当前待读取文件块的前面
				temp_file_rebuild.read(temp_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//读入FILE_ONCE_MAX_SIZE_NUMBER个字节
				target_file.write(temp_file_data, FILE_ONCE_MAX_SIZE_NUMBER);//写入目标文件
				if (direction == 2)
				{
					emit unlock_simple_opposite_process((double)(source_file_size + (FILE_ONCE_MAX_SIZE_NUMBER*loop_count)) / (double)source_file_size_include_temp);//仍然发出信号给主界面进度条使用。需要加上之前已经处理的部分
				}
				else
				{
					emit unlock_simple_opposite_process((double)(source_file_size + source_file_size + (FILE_ONCE_MAX_SIZE_NUMBER*loop_count)) / (double)source_file_size_include_temp);//仍然发出信号给主界面进度条使用。需要加上之前已经处理的部分
				}
			}
			delete temp_file_data;
			if (tail_offset > 0)//存在加密终点，写入文件尾内容，必须最后写入。此外，需注意不能写入头部特征数字
			{
				source_file.clear();//c++有个特性，文件指针到达文件尾后，使用文件指针位置操作函数将无效，需要事先清空文件流
				if (have_head_digit)//如果开头有特征数字，注意不能将特征数字写入解密文件
				{
					source_file.seekg(source_file_size + head_offset + FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//因为是读取文件尾部内容，因此需要先移动到文件不处理内容的首部
				}
				else
				{
					source_file.seekg(source_file_size + head_offset, ios_base::beg);//因为是读取文件尾部内容，因此需要先移动到文件不处理内容的首部
				}
				char *source_file_data_tail = new char[tail_offset];//待加密文件尾部非处理内容
				source_file.read(source_file_data_tail, tail_offset);//读入文件尾部非处理内容
				target_file.write(source_file_data_tail, tail_offset);//写入文件尾部非处理内容
				delete source_file_data_tail;
			}
			else
			{

			}
			source_file.close();//关闭文件
			target_file.close();
			temp_file_rebuild.close();
			delete_succeed = remove(temp_file_path_str.c_str());//删除临时文件
		}
		else
		{

		}
		if (is_output_history_file)//需要写入历史文件
		{
			time_t system_time;//存储系统时间
			time(&system_time);//获取系统时间
			struct tm *time_struct = localtime(&system_time);//获取指向时间结构体的指针
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//历史文件使用附加方式打开
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//输出相应内容。这里为时间
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//按格式输出时间
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//输出文件名
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//输出文件路径
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_3_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出操作
			history_file.close();
		}
		else
		{

		}
		emit unlock_simple_opposite_final(true);
	Delete_this_class_unlock_opposite://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockOpposite::lock_add(const string & file_path, const string & file_name, const string & file_output_front_path, const string & file_output_back_path, bool is_output_history_file, const string & history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string & key_file_path, const string & key_file_binary_path, const string & temp_file_path, int direction, long long head_offset, long long tail_offset, int cycle, bool have_head_digit, char *head_digit, int *unit_digit)//文件取反加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，临时文件夹路径，加密方向（1代表顺序，2代表倒序，3代表双方向），头部处理起点，尾部处理起点，循环周期（注意这里循环周期指的是加减循环单元数目，不再是取反加密的加密间隔，不需要进行加1修正），是否有头部特征数字，头部特征数字，各循环单位加减数量（为包含16个int型的数组）
	{

		//加密过程：根据循环单元数目，每一个循环内，各单元加上相应位置的加减数量，然后进入下一循环
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		QDateTime current_date_time = QDateTime::currentDateTime();//获取当前时间
		QString current_date_string = current_date_time.toString(FILE_TEMP_FILE_TIME_FORMAT_STRING);
		string temp_file_path_str = temp_file_path;//倒序加密和双向加密时需要的临时文件，存放倒序加密结果，之后对该文件里的内容进行重组
		temp_file_path_str += FILE_FILE_INTERVAL_STRING;
		temp_file_path_str += string((const char *)current_date_string.toLocal8Bit());//将临时文件路径加上时间以避免多线程处理时的重复问题
		temp_file_path_str += FILE_TEMP_DOUBLE_FILE_BACK_PATH_STRING;
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_simple_add_final(false);
			goto Delete_this_class_lock_add;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		if (have_head_digit)//根据情况加入头部特征数字
		{
			target_file.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//经过QByteArray转换为16进制编码后，字符串的长度减少一半，因为两个16进制数值表示一个字节
		}
		long long source_file_unit_count;//文件数据总需要处理的单元数
		if (direction == 1)//顺序处理过程
		{
			source_file_unit_count = source_file.tellg() - head_offset - tail_offset;//去掉头部处理起点和尾部处理终点占用的位置
			int tail_offset_update = tail_offset + source_file_unit_count % sizeof(int);//获取待处理部分尾部不足一个int长度的部分，计入尾部长度
			long long int_size_temp = sizeof(int);//不能直接使用source_file_unit_count/=sizeof(int)，否则如果source_file_unit_count为负数会出现非常大的结果值，估计是因为sizeof(int)为unsigned long，在对结果转换的时候，负数在不同数据类型下的表示不同
			source_file_unit_count /= int_size_temp;//获得处理总单元数目
			if (source_file_unit_count <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit lock_simple_add_final(false);
				goto Delete_this_class_lock_add;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
			else
			{

			}
			long long source_file_unit_count_double_lock = source_file_unit_count * FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER;//双方向加密，进度条显示用到的文件总长度应该是两次加密的相关数值的总和
			source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
			if (head_offset > 0)//存在加密起点
			{
				char *source_file_data_head = new char[head_offset];//待加密文件头部非处理内容
				source_file.read(source_file_data_head, head_offset);//读入文件头部非处理内容
				target_file.write(source_file_data_head, head_offset);//写入文件头部非处理内容
				delete source_file_data_head;
			}
			else
			{

			}
			int cycle_count = 0;//循环单元计数
			int unit;//被操作的int单位
			for (long long loop_count = 1; loop_count <= source_file_unit_count; loop_count++)
			{
				source_file.read((char*)&unit, sizeof(int));//读取当前单元数据
				unit += unit_digit[cycle_count];//单元数据加上指定数值
				target_file.write((char*)&unit, sizeof(unit));//输出处理后的数据，按int型格式写入（4字节）
				emit lock_simple_add_process((double)loop_count / (double)source_file_unit_count);//发出信号给主界面进度条使用
				cycle_count++;
				if (cycle_count >= cycle)//循环数达到最大值，重置循环数
				{
					cycle_count = 0;
				}
				else
				{

				}
			}
			if (tail_offset_update > 0 )//存在加密终点，写入文件尾内容。双向加密则不写入
			{
				char *source_file_data_tail = new char[tail_offset_update];//待加密文件尾部非处理内容
				source_file.read(source_file_data_tail, tail_offset_update);//读入文件尾部非处理内容
				target_file.write(source_file_data_tail, tail_offset_update);//写入文件尾部非处理内容
				delete source_file_data_tail;
			}
			else
			{

			}
			source_file.close();
			target_file.close();
		}
		else//倒序处理过程
		{
			ofstream temp_file(temp_file_path_str, ios_base::out | ios_base::binary | ios_base::app);//因为c++不支持在文件中间插入内容，只能先生成临时文件，然后在输出文件中对临时文件中的内容进行重组
			source_file_unit_count = source_file.tellg() - head_offset - tail_offset;//去掉头部处理起点和尾部处理终点占用的位置
			int head_offset_update = head_offset + source_file_unit_count % sizeof(int);//获取待处理部分头部不足一个int长度的部分，计入头部长度
			long long int_size_temp = sizeof(int);//不能直接使用source_file_unit_count/=sizeof(int)，否则如果source_file_unit_count为负数会出现非常大的结果值，估计是因为sizeof(int)为unsigned long，在对结果转换的时候，负数在不同数据类型下的表示不同
			source_file_unit_count /= int_size_temp;//获得处理总单元数目
			if (source_file_unit_count <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit lock_simple_add_final(false);
				goto Delete_this_class_lock_add;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
			else
			{

			}
			source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
			if (head_offset_update > 0)//存在加密起点
			{
				char *source_file_data_head = new char[head_offset_update];//待加密文件头部非处理内容
				source_file.read(source_file_data_head, head_offset_update);//读入文件头部非处理内容
				target_file.write(source_file_data_head, head_offset_update);//写入文件头部非处理内容
				delete source_file_data_head;
			}
			else
			{

			}
			long long source_file_unit_count_include_temp = source_file_unit_count * FILE_LOCK_TAIL_SIZE_TIME_NUMBER;//考虑到需要对文件进行重组，进度条显示用到的文件总长度需要加上后续重组的数目
			long long source_file_unit_count_double_lock = source_file_unit_count * FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER;//双方向加密，进度条显示用到的文件总长度应该是两次加密的相关数值的总和
			int cycle_count = 0;//循环单元计数
			int unit;//被操作的int单位
			for (long long loop_count = 1; loop_count <= source_file_unit_count; loop_count++)//倒序处理的基本方法：从最后一个处理单元开始读取。每次读取一个处理单元之前，先把文件指针移动到该单元起始位置
			{
				source_file.clear();//清空文件流，否则可能无法定位
				source_file.seekg(source_file_unit_count * sizeof(int) + head_offset_update - loop_count * sizeof(int), ios_base::beg);//将文件指针移动到当前待读取处理单元的前面
				source_file.read((char*)&unit, sizeof(int));//读取当前单元数据
				unit += unit_digit[cycle_count];//单元数据加上指定数值
				temp_file.write((char*)&unit, sizeof(unit));//输出处理后的数据，按int型格式写入（4字节）
				emit lock_simple_add_process((double)loop_count / (double)source_file_unit_count_include_temp);//发出信号给主界面进度条使用
				cycle_count++;
				if (cycle_count >= cycle)//循环数达到最大值，重置循环数
				{
					cycle_count = 0;
				}
				else
				{

				}
			
			}
			temp_file.close();//关闭文件，并删除顺序处理过程产生的临时文件
			ifstream temp_file_rebuild(temp_file_path_str.c_str(), ios_base::in | ios_base::binary | ios_base::ate);//打开临时文件进行内容重组
			if (!temp_file_rebuild.is_open())
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit lock_simple_add_final(false);
				goto Delete_this_class_lock_add;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
			else
			{

			}
			for (long long loop_count = 1; loop_count <= source_file_unit_count; loop_count++)//文件重组的方法：之前是把处理单元倒序放在了临时文件里面，现在需要从第一个处理单元开始读取并将其写入目标文件
			{
				temp_file_rebuild.clear();//清空文件流，否则可能无法定位
				temp_file_rebuild.seekg(source_file_unit_count * sizeof(int) - loop_count * sizeof(int), ios_base::beg);//将文件指针移动到当前待读取处理单元的前面
				temp_file_rebuild.read((char*)&unit, sizeof(int));//读取当前单元数据
				target_file.write((char*)&unit, sizeof(unit));//输出处理后的数据，按int型格式写入（4字节）
				emit lock_simple_add_process((double)(loop_count + source_file_unit_count) / (double)source_file_unit_count_include_temp);//发出信号给主界面进度条使用
				cycle_count++;
				if (cycle_count >= cycle)//循环数达到最大值，重置循环数
				{
					cycle_count = 0;
				}
				else
				{

				}
			}
			if (tail_offset > 0)//存在加密终点，写入文件尾内容，必须最后写入
			{
				source_file.clear();//c++有个特性，文件指针到达文件尾后，使用文件指针位置操作函数将无效，需要事先清空文件流
				source_file.seekg(source_file_unit_count * sizeof(int) + head_offset_update, ios_base::beg);//因为是读取文件尾部内容，因此需要先移动到文件不处理内容的首部
				char *source_file_data_tail = new char[tail_offset];//待加密文件尾部非处理内容
				source_file.read(source_file_data_tail, tail_offset);//读入文件尾部非处理内容
				target_file.write(source_file_data_tail, tail_offset);//写入文件尾部非处理内容
				delete source_file_data_tail;
			}
			else
			{

			}
			source_file.close();//关闭文件
			target_file.close();
			temp_file_rebuild.close();
			int delete_succeed = remove(temp_file_path_str.c_str());//删除临时文件
		}
		if (is_output_history_file)//需要写入历史文件
		{
			time_t system_time;//存储系统时间
			time(&system_time);//获取系统时间
			struct tm *time_struct = localtime(&system_time);//获取指向时间结构体的指针
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//历史文件使用附加方式打开
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//输出相应内容。这里为时间
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//按格式输出时间
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//输出文件名
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//输出文件路径
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_2_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出操作
			history_file.close();
		}
		else
		{

		}
		if (is_output_key_file)//需要生成密钥文件
		{
			string key_file_total_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_path += file_name;//密钥文件输出路径
			key_file_total_path += key_file_path;
			ofstream key_file(key_file_total_path, ios_base::out);//处理文本类型的密钥文件，使用覆盖方式打开
			key_file << FILE_KEY_WRITE_INFORMATION_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出相应内容。这里为密钥文件头部内容
			key_file << FILE_KEY_WRITE_INFORMATION_2_STRING << file_name << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出文件名
			key_file << FILE_KEY_WRITE_INFORMATION_3_STRING << file_path << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出文件路径
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_2_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出加密类型
			if (direction == 1)//输出加密方向
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			else
			{
				key_file << FILE_KEY_WRITE_INFORMATION_5_STRING << FILE_KEY_WRITE_INFORMATION_5_2_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			}
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << head_offset << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出头部忽略字符数
			key_file << FILE_KEY_WRITE_INFORMATION_7_STRING << tail_offset << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出尾部忽略字符数
			key_file << FILE_KEY_WRITE_INFORMATION_8_STRING << cycle << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出循环周期
			key_file << FILE_KEY_WRITE_INFORMATION_10_STRING;//输出加减数量
			for (int index = 0; index < cycle; index++)
			{
				key_file << unit_digit[index];
				if (index < cycle - 1)//输出各数字之间的间隔符号，最后一次不输入
				{
					key_file << FILE_KEY_WRITE_INFORMATION_10_1_STRING;
				}
				else
				{

				}
			}
			key_file << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//输出头部特征数字
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得头部数字并将其转换回原始数据显示
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
		if (is_output_key_file_binary)//需要生成二进制密钥文件
		{
			string key_file_total_binary_path = file_output_front_path + FILE_FILE_INTERVAL_STRING;
			key_file_total_binary_path += file_name;//密钥文件输出路径
			key_file_total_binary_path += key_file_binary_path;
			ofstream key_file_binary(key_file_total_binary_path, ios_base::binary | ios_base::out);//处理二进制类型的密钥文件，使用覆盖方式打开
			QByteArray magic_number = FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING;//等待加入的头部魔术数字
			QByteArray interval_number = FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING;//二进制文件分隔符
			QByteArray interval_short_number = FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING;//二进制文件短分隔符
			magic_number = QByteArray::fromHex(magic_number);//转化为16进制编码
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			string magic_number_string(magic_number.constData(), magic_number.length());//QByteArray转string
			string interval_number_string(interval_number.constData(), interval_number.length());
			string interval_short_number_string(interval_short_number.constData(), interval_short_number.length());
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_2_NUMBER;//加密类型
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//无头部特征数字标记
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//有头部特征数字标记
			key_file_binary << magic_number_string;//写入头部魔术数字
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//输出加密类型，按int型格式写入（4字节）
			key_file_binary.write((char*)(&direction), sizeof(direction));//输出加密方向，按int型格式写入（4字节）
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write((char*)(&head_offset), sizeof(head_offset));//输出头部忽略字符数，按long long型格式写入（8字节）
			key_file_binary.write((char*)(&tail_offset), sizeof(tail_offset));//输出尾部忽略字符数，按long long型格式写入（8字节）
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write((char*)(&cycle), sizeof(cycle));//输出加密周期，按long long型格式写入（8字节）
			for (int index = 0; index < cycle; index++)
			{
				key_file_binary.write((char*)&unit_digit[index], sizeof(unit_digit[index]));//输出存放加减信息的数组加减信息的内容，按int存储（4字节）
			}
			key_file_binary << interval_number_string;//写入分隔符
			if (have_head_digit)//写入头部特征数字信息
			{
				key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//输出有头部特征数字标记，按int型格式写入（4字节）
				key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//写入头部特征数字
			}
			else
			{
				key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//输出无头部特征数字标记，按int型格式写入（4字节）
				key_file_binary << interval_short_number_string;//写入相应位数的分隔符占位
			}
			key_file_binary << interval_number_string;//写入分隔符
			int file_name_length = file_name.length();//文件名长度
			int file_path_length = file_path.length();//文件路径长度
			key_file_binary.write((char*)(&file_name_length), sizeof(file_name_length));//输出文件名长度，按int型格式写入（4字节）
			key_file_binary << file_name;//写入文件名
			key_file_binary.write((char*)(&file_path_length), sizeof(file_path_length));//输出文件路径长度，按int型格式写入（4字节）
			key_file_binary << file_path;//写入文件路径
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.close();
		}
		else
		{

		}
		emit lock_simple_add_final(true);
	Delete_this_class_lock_add://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockOpposite::unlock_add(const string & file_path, const string & file_name, const string & file_output_front_path, const string & file_output_back_path, bool is_output_history_file, const string & history_file_path, const string & temp_file_path, int direction, long long head_offset, long long tail_offset, int cycle, bool have_head_digit, char *head_digit, int *unit_digit)//文件取反加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，临时文件夹路径，加密方向（1代表顺序，2代表倒序，3代表双方向），头部处理起点，尾部处理起点，循环周期（注意这里循环周期指的是加减循环单元数目，不再是取反加密的加密间隔，不需要进行加1修正），是否有头部特征数字，头部特征数字，各循环单位加减数量（为包含16个int型的数组）
	{

		//解密过程：根据循环单元数目，每一个循环内，各单元减去相应位置的加减数量，然后进入下一循环
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		QDateTime current_date_time = QDateTime::currentDateTime();//获取当前时间
		QString current_date_string = current_date_time.toString(FILE_TEMP_FILE_TIME_FORMAT_STRING);
		string temp_file_path_str = temp_file_path;//倒序加密和双向加密时需要的临时文件，存放倒序加密结果，之后对该文件里的内容进行重组
		temp_file_path_str += FILE_FILE_INTERVAL_STRING;
		temp_file_path_str += string((const char *)current_date_string.toLocal8Bit());//将临时文件路径加上时间以避免多线程处理时的重复问题
		temp_file_path_str += FILE_TEMP_DOUBLE_FILE_BACK_PATH_STRING;
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_simple_add_final(false);
			goto Delete_this_class_unlock_add;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		long long source_file_unit_count;//文件数据总需要处理的单元数
		if (direction == 1)//顺序处理过程
		{
			source_file_unit_count = source_file.tellg() - head_offset - tail_offset;//去掉头部处理起点和尾部处理终点占用的位置
			if (have_head_digit)//头部特征数字校验。因为tellg()仅在读取文件之前有效，如果先读取头部特征数字会造成该函数无效
			{
				QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得解密信息确认界面提供的头部数字并将其转换回原始数据显示
				key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
				QString key_head_digit_transform_string = key_head_digit_transform;//转为QString
				source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
				char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//存放输入文件头部特征数字的char数组
				source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//读取特征数字。这里需要注意，如果特征数字为全空即“00000000”的时候，使用动态数组则会出现数组长度为0的情况，因此需要用固定长度的char数组
				QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//存放加密文件头部魔法数字的十六进制数据
				source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//获得十六进制数据，转换为大写
				QString source_head_digit_transform_string = source_head_digit_transform;//转为QString
				if (key_head_digit_transform_string == source_head_digit_transform_string)//头部特征数字相同，进行解密
				{
					source_file_unit_count -= FILE_HEAD_NUMBER_SIZE_NUMBER;//去掉头部特征数字占用的空间

				}
				else//头部特征数字不同，取消解密
				{
					target_file.close();
					remove(target_file_path.c_str());//删除文件
					emit unlock_simple_add_final(false);
					goto Delete_this_class_unlock_add;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
				}
			}
			else
			{

			}
			int tail_offset_update = tail_offset + source_file_unit_count % sizeof(int);//获取待处理部分尾部不足一个int长度的部分，计入尾部长度
			long long int_size_temp = sizeof(int);//不能直接使用source_file_unit_count/=sizeof(int)，否则如果source_file_unit_count为负数会出现非常大的结果值，估计是因为sizeof(int)为unsigned long，在对结果转换的时候，负数在不同数据类型下的表示不同
			source_file_unit_count /= int_size_temp;//获得处理总单元数目
			if (source_file_unit_count <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_simple_add_final(false);
				goto Delete_this_class_unlock_add;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
			else
			{

			}
			long long source_file_unit_count_double_lock = source_file_unit_count * FILE_LOCK_HEAD_AND_TAIL_SIZE_TIME_NUMBER;//双方向加密，进度条显示用到的文件总长度应该是两次加密的相关数值的总和
			source_file.clear();//清空文件流，否则可能无法定位
			if (have_head_digit)//如果开头有特征数字，注意不能将特征数字写入解密文件
			{
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//将文件指针偏移到头部特征数字之后
			}
			else
			{
				source_file.seekg(ios_base::beg);//重定向文件指针
			}
			if (head_offset > 0)//存在加密起点
			{
				char *source_file_data_head = new char[head_offset];//待加密文件头部非处理内容
				source_file.read(source_file_data_head, head_offset);//读入文件头部非处理内容
				target_file.write(source_file_data_head, head_offset);//写入文件头部非处理内容
				delete source_file_data_head;
			}
			else
			{

			}
			int cycle_count = 0;//循环单元计数
			int unit;//被操作的int单位
			for (long long loop_count = 1; loop_count <= source_file_unit_count; loop_count++)
			{
				source_file.read((char*)&unit, sizeof(int));//读取当前单元数据
				unit -= unit_digit[cycle_count];//单元数据加上指定数值
				target_file.write((char*)&unit, sizeof(unit));//输出处理后的数据，按int型格式写入（4字节）
				emit unlock_simple_add_process((double)loop_count / (double)source_file_unit_count);//发出信号给主界面进度条使用
				cycle_count++;
				if (cycle_count >= cycle)//循环数达到最大值，重置循环数
				{
					cycle_count = 0;
				}
				else
				{

				}
			}
			if (tail_offset_update > 0)//存在加密终点，写入文件尾内容。双向加密则不写入
			{
				char *source_file_data_tail = new char[tail_offset_update];//待加密文件尾部非处理内容
				source_file.read(source_file_data_tail, tail_offset_update);//读入文件尾部非处理内容
				target_file.write(source_file_data_tail, tail_offset_update);//写入文件尾部非处理内容
				delete source_file_data_tail;
			}
			else
			{

			}
			source_file.close();
			target_file.close();
		}
		if (direction == 2)//倒序处理过程
		{
			ofstream temp_file(temp_file_path_str, ios_base::out | ios_base::binary | ios_base::app);//因为c++不支持在文件中间插入内容，只能先生成临时文件，然后在输出文件中对临时文件中的内容进行重组
			source_file_unit_count = source_file.tellg() - head_offset - tail_offset;//去掉头部处理起点和尾部处理终点占用的位置
			if (have_head_digit)//头部特征数字校验。因为tellg()仅在读取文件之前有效，如果先读取头部特征数字会造成该函数无效
			{
				QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得解密信息确认界面提供的头部数字并将其转换回原始数据显示
				key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
				QString key_head_digit_transform_string = key_head_digit_transform;//转为QString
				source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
				char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//存放输入文件头部特征数字的char数组
				source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//读取特征数字。这里需要注意，如果特征数字为全空即“00000000”的时候，使用动态数组则会出现数组长度为0的情况，因此需要用固定长度的char数组
				QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//存放加密文件头部魔法数字的十六进制数据
				source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//获得十六进制数据，转换为大写
				QString source_head_digit_transform_string = source_head_digit_transform;//转为QString
				if (key_head_digit_transform_string == source_head_digit_transform_string)//头部特征数字相同，进行解密
				{
					source_file_unit_count -= FILE_HEAD_NUMBER_SIZE_NUMBER;//去掉头部特征数字占用的空间

				}
				else//头部特征数字不同，取消解密
				{
					target_file.close();
					remove(target_file_path.c_str());//删除文件
					emit unlock_simple_add_final(false);
					goto Delete_this_class_unlock_add;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
				}
			}
			else
			{

			}
			int head_offset_update = head_offset + source_file_unit_count % sizeof(int);//获取待处理部分头部不足一个int长度的部分，计入头部长度
			long long int_size_temp = sizeof(int);//不能直接使用source_file_unit_count/=sizeof(int)，否则如果source_file_unit_count为负数会出现非常大的结果值，估计是因为sizeof(int)为unsigned long，在对结果转换的时候，负数在不同数据类型下的表示不同
			source_file_unit_count /= int_size_temp;//获得处理总单元数目
			if (source_file_unit_count <= 0)
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_simple_add_final(false);
				goto Delete_this_class_unlock_add;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
			else
			{

			}
			source_file.clear();//清空文件流，否则可能无法定位
			if (have_head_digit)//如果开头有特征数字，注意不能将特征数字写入解密文件
			{
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//将文件指针偏移到头部特征数字之后
			}
			else
			{
				source_file.seekg(ios_base::beg);//重定向文件指针
			}
			if (head_offset_update > 0)//存在加密起点
			{
				char *source_file_data_head = new char[head_offset_update];//待加密文件头部非处理内容
				source_file.read(source_file_data_head, head_offset_update);//读入文件头部非处理内容
				target_file.write(source_file_data_head, head_offset_update);//写入文件头部非处理内容
				delete source_file_data_head;
			}
			else
			{

			}
			long long source_file_unit_count_include_temp = source_file_unit_count * FILE_LOCK_TAIL_SIZE_TIME_NUMBER;//考虑到需要对文件进行重组，进度条显示用到的文件总长度需要加上后续重组的数目
			int cycle_count = 0;//循环单元计数
			int unit;//被操作的int单位
			for (long long loop_count = 1; loop_count <= source_file_unit_count; loop_count++)//倒序处理的基本方法：从最后一个处理单元开始读取。每次读取一个处理单元之前，先把文件指针移动到该单元起始位置
			{
				source_file.clear();//清空文件流，否则可能无法定位
				if (have_head_digit)//如果开头有特征数字，注意不能将特征数字写入解密文件
				{
					source_file.seekg(source_file_unit_count * sizeof(int) + head_offset_update - loop_count * sizeof(int) + FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//将文件指针移动到当前待读取处理单元的前面
				}
				else
				{
					source_file.seekg(source_file_unit_count * sizeof(int) + head_offset_update - loop_count * sizeof(int), ios_base::beg);//将文件指针移动到当前待读取处理单元的前面
				}
				source_file.read((char*)&unit, sizeof(int));//读取当前单元数据
				unit -= unit_digit[cycle_count];//单元数据加上指定数值
				temp_file.write((char*)&unit, sizeof(unit));//输出处理后的数据，按int型格式写入（4字节）
				emit unlock_simple_add_process((double)loop_count / (double)source_file_unit_count_include_temp);//发出信号给主界面进度条使用
				cycle_count++;
				if (cycle_count >= cycle)//循环数达到最大值，重置循环数
				{
					cycle_count = 0;
				}
				else
				{

				}

			}
			temp_file.close();//关闭文件，并删除顺序处理过程产生的临时文件
			ifstream temp_file_rebuild(temp_file_path_str.c_str(), ios_base::in | ios_base::binary | ios_base::ate);//打开临时文件进行内容重组
			if (!temp_file_rebuild.is_open())
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_simple_add_final(false);
				goto Delete_this_class_unlock_add;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
			else
			{

			}
			for (long long loop_count = 1; loop_count <= source_file_unit_count; loop_count++)//文件重组的方法：之前是把处理单元倒序放在了临时文件里面，现在需要从第一个处理单元开始读取并将其写入目标文件
			{
				temp_file_rebuild.clear();//清空文件流，否则可能无法定位
				temp_file_rebuild.seekg(source_file_unit_count * sizeof(int) - loop_count * sizeof(int), ios_base::beg);//将文件指针移动到当前待读取处理单元的前面
				temp_file_rebuild.read((char*)&unit, sizeof(int));//读取当前单元数据
				target_file.write((char*)&unit, sizeof(unit));//输出处理后的数据，按int型格式写入（4字节）
				emit unlock_simple_add_process((double)(loop_count + source_file_unit_count) / (double)source_file_unit_count_include_temp);//发出信号给主界面进度条使用
				cycle_count++;
				if (cycle_count >= cycle)//循环数达到最大值，重置循环数
				{
					cycle_count = 0;
				}
				else
				{

				}
			}
			if (tail_offset > 0)//存在加密终点，写入文件尾内容，必须最后写入
			{
				source_file.clear();//c++有个特性，文件指针到达文件尾后，使用文件指针位置操作函数将无效，需要事先清空文件流
				if (have_head_digit)
				{
					source_file.seekg(source_file_unit_count * sizeof(int) + head_offset_update + FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//因为是读取文件尾部内容，因此需要先移动到文件不处理内容的首部
				}
				else
				{
					source_file.seekg(source_file_unit_count * sizeof(int) + head_offset_update, ios_base::beg);//因为是读取文件尾部内容，因此需要先移动到文件不处理内容的首部
				}
				char *source_file_data_tail = new char[tail_offset];//待加密文件尾部非处理内容
				source_file.read(source_file_data_tail, tail_offset);//读入文件尾部非处理内容
				target_file.write(source_file_data_tail, tail_offset);//写入文件尾部非处理内容
				delete source_file_data_tail;
			}
			else
			{

			}
			source_file.close();//关闭文件
			target_file.close();
			temp_file_rebuild.close();
			int delete_succeed = remove(temp_file_path_str.c_str());//删除临时文件
		}
		else
		{

		}
		if (is_output_history_file)//需要写入历史文件
		{
			time_t system_time;//存储系统时间
			time(&system_time);//获取系统时间
			struct tm *time_struct = localtime(&system_time);//获取指向时间结构体的指针
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//历史文件使用附加方式打开
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//输出相应内容。这里为时间
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//按格式输出时间
			history_file << FILE_HISTORY_WRITE_INFORMATION_2_STRING << file_name << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//输出文件名
			history_file << FILE_HISTORY_WRITE_INFORMATION_3_STRING << file_path << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//输出文件路径
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_3_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出操作
			history_file.close();
		}
		else
		{

		}
		emit unlock_simple_add_final(true);
	Delete_this_class_unlock_add://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

}

