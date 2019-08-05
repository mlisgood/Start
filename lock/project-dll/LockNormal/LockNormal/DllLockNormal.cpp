#include "DllLockNormal.h"

//使用标准命名空间
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios_base;

//导入crypto++命名空间
using namespace CryptoPP;

//函数
namespace rem
{

	//dll主体函数
	void LockSingle::lock_DES(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully)//DES加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否加密剩下不足一个加密单位的明文（DES需要补足才会进行加密，这样的话解密出来的文件与原来的可能会有偏差）
	{
		srand((int)time(NULL));//生成随机种子供之后使用
		char *source_file_data = new char[DES::BLOCKSIZE];//待加密文件数据
		char *target_file_data = new char[DES::BLOCKSIZE];//加密后文件数据
		DESEncryption encryption_DES;//构造DES加密器
		set_key_DES(key);//生成一个随机的DES密钥
		encryption_DES.SetKey((unsigned char*)key, DES::KEYLENGTH);//设置DES密钥
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_DES_final(false, key);
			goto Delete_this_class_lock_DES;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
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
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_DES_final(false, key);
			goto Delete_this_class_lock_DES;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		long long total_count = source_file_size / DES::BLOCKSIZE;//总处理周期数，不包含最后一次
		long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, DES::BLOCKSIZE);//读入DES::BLOCKSIZE个字节
			encryption_DES.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//加密
			target_file.write(target_file_data, DES::BLOCKSIZE);//写入目标文件
			emit lock_DES_process((double)(DES::BLOCKSIZE*loop_count) / (double)source_file_size);//发出信号给主界面进度条使用
		}
		int source_file_size_remain = source_file_size - total_count * DES::BLOCKSIZE;//剩余字节数
		if (source_file_size_remain > 0)//如果还有剩余的内容，要计入最后一次处理
		{
			if (is_encode_fully)
			{
				char *source_file_data_remain = new char[DES::BLOCKSIZE];
				char *target_file_data_remain = new char[DES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, DES::BLOCKSIZE);//初始化数组为填充内容
				source_file.read(source_file_data_remain, DES::BLOCKSIZE);//读入DES::BLOCKSIZE个字节
				encryption_DES.ProcessBlock((unsigned char*)source_file_data_remain, (unsigned char*)target_file_data_remain);//加密
				target_file.write(target_file_data_remain, DES::BLOCKSIZE);//写入目标文件
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//读入剩下的字节
				target_file.write(source_file_data_remain, source_file_size_remain);//写入目标文件
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//释放内存
		delete target_file_data;//释放内存
		source_file.close();
		target_file.close();
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
			QByteArray key_transform(key, DES::DEFAULT_KEYLENGTH * 2);//输出密钥
			key_transform = (key_transform.toHex()).toUpper();
			string key_string(key_transform.data(), DES::DEFAULT_KEYLENGTH * 2);
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//输出头部特征数字
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得头部数字并将其转换回原始数据显示
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
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_3_NUMBER;//加密类型
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//无头部特征数字标记
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//有头部特征数字标记
			key_file_binary << magic_number_string;//写入头部魔术数字
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//输出加密类型，按int型格式写入（4字节）
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write(key, DES::DEFAULT_KEYLENGTH);//写入密钥
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
		emit lock_DES_final(true, key);
	Delete_this_class_lock_DES://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockSingle::unlock_DES(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully)//DES解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否解密剩下不足一个解密单位的密文（DES需要补足才会进行解密，这样的话解密出来的文件与原来的可能会有偏差）
	{

		//注意因为是对称加密，所以加解密方式非常接近
		char *source_file_data = new char[DES::BLOCKSIZE];//待解密文件数据
		char *target_file_data = new char[DES::BLOCKSIZE];//解密后文件数据
		DESDecryption decryption_DES;//构造DES加密器
		decryption_DES.SetKey((unsigned char*)key, DES::KEYLENGTH);//设置DES密钥
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		long long source_file_size;//文件数据总需要处理的字节数
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_DES_final(false);
			goto Delete_this_class_unlock_DES;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		if (have_head_digit)//头部特征数字校验。因为tellg()仅在读取文件之前有效，如果先读取头部特征数字会造成该函数无效
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得解密信息确认界面提供的头部数字并将其转换回原始数据显示
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//转为QString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//存放输入文件头部特征数字的char数组
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//读取特征数字。这里需要注意，如果特征数字为全空即“00000000”的时候，使用动态数组则会出现数组长度为0的情况，因此需要用固定长度的char数组
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//存放加密文件头部魔法数字的十六进制数据
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//获得十六进制数据，转换为大写
			QString source_head_digit_transform_string = source_head_digit_transform;//转为QString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//头部特征数字相同，进行解密
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//去掉头部特征数字占用的空间
				source_file.clear();//清空文件流，否则可能无法定位
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//将文件指针偏移到头部特征数字之后
			}
			else//头部特征数字不同，取消解密
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_DES_final(false);
				goto Delete_this_class_unlock_DES;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_DES_final(false);
			goto Delete_this_class_unlock_DES;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		long long total_count = source_file_size / DES::BLOCKSIZE;//总处理周期数，不包含最后一次
		long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, DES::BLOCKSIZE);//读入DES::BLOCKSIZE个字节
			decryption_DES.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//加密
			target_file.write(target_file_data, DES::BLOCKSIZE);//写入目标文件
			emit unlock_DES_process((double)(DES::BLOCKSIZE*loop_count) / (double)source_file_size);//发出信号给主界面进度条使用
		}
		int source_file_size_remain = source_file_size - total_count * DES::BLOCKSIZE;//剩余字节数
		if (source_file_size_remain > 0)//如果还有剩余的内容，要计入最后一次处理
		{
			if (is_decode_fully)
			{
				char *source_file_data_remain = new char[DES::BLOCKSIZE];
				char *target_file_data_remain = new char[DES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, DES::BLOCKSIZE);//初始化数组为填充内容
				source_file.read(source_file_data_remain, DES::BLOCKSIZE);//读入DES::BLOCKSIZE个字节
				decryption_DES.ProcessBlock((unsigned char*)source_file_data_remain, (unsigned char*)target_file_data_remain);//加密
				target_file.write(target_file_data_remain, DES::BLOCKSIZE);//写入目标文件
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//读入剩下的字节
				target_file.write(source_file_data_remain, source_file_size_remain);//写入目标文件
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//释放内存
		delete target_file_data;//释放内存
		source_file.close();
		target_file.close();
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
		emit unlock_DES_final(true);
	Delete_this_class_unlock_DES://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockSingle::lock_DES_EDE2(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully)//2-Key TripleDES加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否加密剩下不足一个加密单位的明文（DES需要补足才会进行加密，这样的话解密出来的文件与原来的可能会有偏差）
	{
		srand((int)time(NULL));//生成随机种子供之后使用
		char *source_file_data = new char[DES_EDE2::BLOCKSIZE];//待加密文件数据
		char *target_file_data = new char[DES_EDE2::BLOCKSIZE];//加密后文件数据
		DES_EDE2_Encryption encryption_DES_EDE2;//构造DES_EDE2加密器
		set_key_DES_EDE2(key);//生成一个随机的DES_EDE2密钥
		encryption_DES_EDE2.SetKey((unsigned char*)key, DES_EDE2::KEYLENGTH);//设置DES密钥
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_DES_EDE2_final(false, key);
			goto Delete_this_class_lock_DES_EDE2;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
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
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_DES_EDE2_final(false, key);
			goto Delete_this_class_lock_DES_EDE2;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		long long total_count = source_file_size / DES_EDE2::BLOCKSIZE;//总处理周期数，不包含最后一次
		long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, DES_EDE2::BLOCKSIZE);//读入DES::BLOCKSIZE个字节
			encryption_DES_EDE2.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//加密
			target_file.write(target_file_data, DES_EDE2::BLOCKSIZE);//写入目标文件
			emit lock_DES_EDE2_process((double)(DES_EDE2::BLOCKSIZE*loop_count) / (double)source_file_size);//发出信号给主界面进度条使用
		}
		int source_file_size_remain = source_file_size - total_count * DES_EDE2::BLOCKSIZE;//剩余字节数
		if (source_file_size_remain > 0)//如果还有剩余的内容，要计入最后一次处理
		{
			if (is_encode_fully)
			{
				char *source_file_data_remain = new char[DES_EDE2::BLOCKSIZE];
				char *target_file_data_remain = new char[DES_EDE2::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, DES_EDE2::BLOCKSIZE);//初始化数组为填充内容
				source_file.read(source_file_data_remain, DES_EDE2::BLOCKSIZE);//读入DES::BLOCKSIZE个字节
				encryption_DES_EDE2.ProcessBlock((unsigned char*)source_file_data_remain, (unsigned char*)target_file_data_remain);//加密
				target_file.write(target_file_data_remain, DES_EDE2::BLOCKSIZE);//写入目标文件
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//读入剩下的字节
				target_file.write(source_file_data_remain, source_file_size_remain);//写入目标文件
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//释放内存
		delete target_file_data;//释放内存
		source_file.close();
		target_file.close();
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
			QByteArray key_transform(key, DES_EDE2::DEFAULT_KEYLENGTH * 2);//输出密钥
			key_transform = (key_transform.toHex()).toUpper();
			string key_string(key_transform.data(), DES_EDE2::DEFAULT_KEYLENGTH * 2);
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//输出头部特征数字
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得头部数字并将其转换回原始数据显示
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
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_4_NUMBER;//加密类型
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//无头部特征数字标记
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//有头部特征数字标记
			key_file_binary << magic_number_string;//写入头部魔术数字
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//输出加密类型，按int型格式写入（4字节）
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write(key, DES_EDE2::DEFAULT_KEYLENGTH);//写入密钥
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
		emit lock_DES_EDE2_final(true, key);
	Delete_this_class_lock_DES_EDE2://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockSingle::unlock_DES_EDE2(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully)//2-Key TripleDES解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否解密剩下不足一个解密单位的密文（DES需要补足才会进行解密，这样的话解密出来的文件与原来的可能会有偏差）
	{

		//注意因为是对称加密，所以加解密方式非常接近
		char *source_file_data = new char[DES_EDE2::BLOCKSIZE];//待解密文件数据
		char *target_file_data = new char[DES_EDE2::BLOCKSIZE];//解密后文件数据
		DES_EDE2_Decryption decryption_DES_EDE2;//构造DES加密器
		decryption_DES_EDE2.SetKey((unsigned char*)key, DES_EDE2::KEYLENGTH);//设置DES密钥
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		long long source_file_size;//文件数据总需要处理的字节数
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_DES_EDE2_final(false);
			goto Delete_this_class_unlock_DES_EDE2;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		if (have_head_digit)//头部特征数字校验。因为tellg()仅在读取文件之前有效，如果先读取头部特征数字会造成该函数无效
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得解密信息确认界面提供的头部数字并将其转换回原始数据显示
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//转为QString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//存放输入文件头部特征数字的char数组
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//读取特征数字。这里需要注意，如果特征数字为全空即“00000000”的时候，使用动态数组则会出现数组长度为0的情况，因此需要用固定长度的char数组
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//存放加密文件头部魔法数字的十六进制数据
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//获得十六进制数据，转换为大写
			QString source_head_digit_transform_string = source_head_digit_transform;//转为QString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//头部特征数字相同，进行解密
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//去掉头部特征数字占用的空间
				source_file.clear();//清空文件流，否则可能无法定位
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//将文件指针偏移到头部特征数字之后
			}
			else//头部特征数字不同，取消解密
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_DES_EDE2_final(false);
				goto Delete_this_class_unlock_DES_EDE2;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_DES_EDE2_final(false);
			goto Delete_this_class_unlock_DES_EDE2;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		long long total_count = source_file_size / DES_EDE2::BLOCKSIZE;//总处理周期数，不包含最后一次
		long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, DES_EDE2::BLOCKSIZE);//读入DES::BLOCKSIZE个字节
			decryption_DES_EDE2.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//加密
			target_file.write(target_file_data, DES_EDE2::BLOCKSIZE);//写入目标文件
			emit unlock_DES_EDE2_process((double)(DES_EDE2::BLOCKSIZE*loop_count) / (double)source_file_size);//发出信号给主界面进度条使用
		}
		int source_file_size_remain = source_file_size - total_count * DES_EDE2::BLOCKSIZE;//剩余字节数
		if (source_file_size_remain > 0)//如果还有剩余的内容，要计入最后一次处理
		{
			if (is_decode_fully)
			{
				char *source_file_data_remain = new char[DES_EDE2::BLOCKSIZE];
				char *target_file_data_remain = new char[DES_EDE2::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, DES_EDE2::BLOCKSIZE);//初始化数组为填充内容
				source_file.read(source_file_data_remain, DES_EDE2::BLOCKSIZE);//读入DES::BLOCKSIZE个字节
				decryption_DES_EDE2.ProcessBlock((unsigned char*)source_file_data_remain, (unsigned char*)target_file_data_remain);//加密
				target_file.write(target_file_data_remain, DES_EDE2::BLOCKSIZE);//写入目标文件
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//读入剩下的字节
				target_file.write(source_file_data_remain, source_file_size_remain);//写入目标文件
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//释放内存
		delete target_file_data;//释放内存
		source_file.close();
		target_file.close();
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
		emit unlock_DES_EDE2_final(true);
	Delete_this_class_unlock_DES_EDE2://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockSingle::lock_DES_EDE3(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully)//3-Key TripleDES加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否加密剩下不足一个加密单位的明文（DES需要补足才会进行加密，这样的话解密出来的文件与原来的可能会有偏差）
	{
		srand((int)time(NULL));//生成随机种子供之后使用
		char *source_file_data = new char[DES_EDE3::BLOCKSIZE];//待加密文件数据
		char *target_file_data = new char[DES_EDE3::BLOCKSIZE];//加密后文件数据
		DES_EDE3_Encryption encryption_DES_EDE3;//构造DES_EDE3加密器
		set_key_DES_EDE3(key);//生成一个随机的DES_EDE3密钥
		encryption_DES_EDE3.SetKey((unsigned char*)key, DES_EDE3::KEYLENGTH);//设置DES密钥
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_DES_EDE3_final(false, key);
			goto Delete_this_class_lock_DES_EDE3;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
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
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_DES_EDE3_final(false, key);
			goto Delete_this_class_lock_DES_EDE3;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		long long total_count = source_file_size / DES_EDE3::BLOCKSIZE;//总处理周期数，不包含最后一次
		long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, DES_EDE3::BLOCKSIZE);//读入DES::BLOCKSIZE个字节
			encryption_DES_EDE3.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//加密
			target_file.write(target_file_data, DES_EDE3::BLOCKSIZE);//写入目标文件
			emit lock_DES_EDE3_process((double)(DES_EDE3::BLOCKSIZE*loop_count) / (double)source_file_size);//发出信号给主界面进度条使用
		}
		int source_file_size_remain = source_file_size - total_count * DES_EDE3::BLOCKSIZE;//剩余字节数
		if (source_file_size_remain > 0)//如果还有剩余的内容，要计入最后一次处理
		{
			if (is_encode_fully)
			{
				char *source_file_data_remain = new char[DES_EDE3::BLOCKSIZE];
				char *target_file_data_remain = new char[DES_EDE3::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, DES_EDE3::BLOCKSIZE);//初始化数组为填充内容
				source_file.read(source_file_data_remain, DES_EDE3::BLOCKSIZE);//读入DES::BLOCKSIZE个字节
				encryption_DES_EDE3.ProcessBlock((unsigned char*)source_file_data_remain, (unsigned char*)target_file_data_remain);//加密
				target_file.write(target_file_data_remain, DES_EDE3::BLOCKSIZE);//写入目标文件
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//读入剩下的字节
				target_file.write(source_file_data_remain, source_file_size_remain);//写入目标文件
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//释放内存
		delete target_file_data;//释放内存
		source_file.close();
		target_file.close();
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
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_3_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出加密类型
			QByteArray key_transform(key, DES_EDE3::DEFAULT_KEYLENGTH * 2);//输出密钥
			key_transform = (key_transform.toHex()).toUpper();
			string key_string(key_transform.data(), DES_EDE3::DEFAULT_KEYLENGTH * 2);
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//输出头部特征数字
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得头部数字并将其转换回原始数据显示
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
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_5_NUMBER;//加密类型
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//无头部特征数字标记
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//有头部特征数字标记
			key_file_binary << magic_number_string;//写入头部魔术数字
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//输出加密类型，按int型格式写入（4字节）
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write(key, DES_EDE3::DEFAULT_KEYLENGTH);//写入密钥
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
		emit lock_DES_EDE3_final(true, key);
	Delete_this_class_lock_DES_EDE3://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockSingle::unlock_DES_EDE3(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully)//3-Key TripleDES解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否解密剩下不足一个解密单位的密文（DES需要补足才会进行解密，这样的话解密出来的文件与原来的可能会有偏差）
	{

		//注意因为是对称加密，所以加解密方式非常接近
		char *source_file_data = new char[DES_EDE3::BLOCKSIZE];//待解密文件数据
		char *target_file_data = new char[DES_EDE3::BLOCKSIZE];//解密后文件数据
		DES_EDE3_Decryption decryption_DES_EDE3;//构造DES加密器
		decryption_DES_EDE3.SetKey((unsigned char*)key, DES_EDE3::KEYLENGTH);//设置DES密钥
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		long long source_file_size;//文件数据总需要处理的字节数
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_DES_EDE3_final(false);
			goto Delete_this_class_unlock_DES_EDE3;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		if (have_head_digit)//头部特征数字校验。因为tellg()仅在读取文件之前有效，如果先读取头部特征数字会造成该函数无效
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得解密信息确认界面提供的头部数字并将其转换回原始数据显示
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//转为QString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//存放输入文件头部特征数字的char数组
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//读取特征数字。这里需要注意，如果特征数字为全空即“00000000”的时候，使用动态数组则会出现数组长度为0的情况，因此需要用固定长度的char数组
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//存放加密文件头部魔法数字的十六进制数据
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//获得十六进制数据，转换为大写
			QString source_head_digit_transform_string = source_head_digit_transform;//转为QString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//头部特征数字相同，进行解密
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//去掉头部特征数字占用的空间
				source_file.clear();//清空文件流，否则可能无法定位
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//将文件指针偏移到头部特征数字之后
			}
			else//头部特征数字不同，取消解密
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_DES_EDE3_final(false);
				goto Delete_this_class_unlock_DES_EDE3;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_DES_EDE3_final(false);
			goto Delete_this_class_unlock_DES_EDE3;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		long long total_count = source_file_size / DES_EDE3::BLOCKSIZE;//总处理周期数，不包含最后一次
		long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, DES_EDE3::BLOCKSIZE);//读入DES::BLOCKSIZE个字节
			decryption_DES_EDE3.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//加密
			target_file.write(target_file_data, DES_EDE3::BLOCKSIZE);//写入目标文件
			emit unlock_DES_EDE3_process((double)(DES_EDE3::BLOCKSIZE*loop_count) / (double)source_file_size);//发出信号给主界面进度条使用
		}
		int source_file_size_remain = source_file_size - total_count * DES_EDE3::BLOCKSIZE;//剩余字节数
		if (source_file_size_remain > 0)//如果还有剩余的内容，要计入最后一次处理
		{
			if (is_decode_fully)
			{
				char *source_file_data_remain = new char[DES_EDE3::BLOCKSIZE];
				char *target_file_data_remain = new char[DES_EDE3::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, DES_EDE3::BLOCKSIZE);//初始化数组为填充内容
				source_file.read(source_file_data_remain, DES_EDE3::BLOCKSIZE);//读入DES::BLOCKSIZE个字节
				decryption_DES_EDE3.ProcessBlock((unsigned char*)source_file_data_remain, (unsigned char*)target_file_data_remain);//加密
				target_file.write(target_file_data_remain, DES_EDE3::BLOCKSIZE);//写入目标文件
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//读入剩下的字节
				target_file.write(source_file_data_remain, source_file_size_remain);//写入目标文件
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//释放内存
		delete target_file_data;//释放内存
		source_file.close();
		target_file.close();
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
		emit unlock_DES_EDE3_final(true);
	Delete_this_class_unlock_DES_EDE3://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockSingle::lock_AES_MIN(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully)//AES加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否加密剩下不足一个加密单位的明文（AES需要补足才会进行加密，这样的话解密出来的文件与原来的可能会有偏差）
	{
		srand((int)time(NULL));//生成随机种子供之后使用
		char *source_file_data = new char[AES::BLOCKSIZE];//待加密文件数据
		char *target_file_data = new char[AES::BLOCKSIZE];//加密后文件数据
		unsigned char *xor_block = new unsigned char[AES::BLOCKSIZE];//必须设定为全零
		memset(xor_block, 0, AES::BLOCKSIZE);//置零
		AESEncryption encryption_AES_MIN;//构造AES加密器
		set_key_AES_MIN(key);//生成一个随机的AES密钥
		encryption_AES_MIN.SetKey((unsigned char*)key, AES::MIN_KEYLENGTH);//设置AES密钥
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_AES_MIN_final(false, key);
			goto Delete_this_class_lock_AES_MIN;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
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
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_AES_MIN_final(false, key);
			goto Delete_this_class_lock_AES_MIN;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		long long total_count = source_file_size / AES::BLOCKSIZE;//总处理周期数，不包含最后一次
		long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, AES::BLOCKSIZE);//读入AES::BLOCKSIZE个字节
			encryption_AES_MIN.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//加密
			target_file.write(target_file_data, AES::BLOCKSIZE);//写入目标文件
			emit lock_AES_MIN_process((double)(AES::BLOCKSIZE*loop_count) / (double)source_file_size);//发出信号给主界面进度条使用
		}
		int source_file_size_remain = source_file_size - total_count * AES::BLOCKSIZE;//剩余字节数
		if (source_file_size_remain > 0)//如果还有剩余的内容，要计入最后一次处理
		{
			if (is_encode_fully)
			{
				char *source_file_data_remain = new char[AES::BLOCKSIZE];
				char *target_file_data_remain = new char[AES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, AES::BLOCKSIZE);//初始化数组为填充内容
				source_file.read(source_file_data_remain, AES::BLOCKSIZE);//读入AES::BLOCKSIZE个字节
				encryption_AES_MIN.ProcessAndXorBlock((unsigned char*)source_file_data_remain, xor_block, (unsigned char*)target_file_data_remain);//加密
				target_file.write(target_file_data_remain, AES::BLOCKSIZE);//写入目标文件
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//读入剩下的字节
				target_file.write(source_file_data_remain, source_file_size_remain);//写入目标文件
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//释放内存
		delete target_file_data;//释放内存
		delete xor_block;//释放内存
		source_file.close();
		target_file.close();
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
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_4_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出加密类型
			QByteArray key_transform(key, AES::MIN_KEYLENGTH * 2);//输出密钥
			key_transform = (key_transform.toHex()).toUpper();
			string key_string(key_transform.data(), AES::MIN_KEYLENGTH * 2);
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//输出头部特征数字
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得头部数字并将其转换回原始数据显示
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
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_6_NUMBER;//加密类型
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//无头部特征数字标记
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//有头部特征数字标记
			key_file_binary << magic_number_string;//写入头部魔术数字
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//输出加密类型，按int型格式写入（4字节）
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write(key, AES::MIN_KEYLENGTH);//写入密钥
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
		emit lock_AES_MIN_final(true, key);
	Delete_this_class_lock_AES_MIN://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockSingle::unlock_AES_MIN(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully)//AES-128解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否解密剩下不足一个解密单位的密文（AES需要补足才会进行解密，这样的话解密出来的文件与原来的可能会有偏差）
	{

		//注意因为是对称加密，所以加解密方式非常接近
		char *source_file_data = new char[AES::BLOCKSIZE];//待解密文件数据
		char *target_file_data = new char[AES::BLOCKSIZE];//解密后文件数据
		unsigned char *xor_block = new unsigned char[AES::BLOCKSIZE];//必须设定为全零
		memset(xor_block, 0, AES::BLOCKSIZE);//置零
		AESDecryption decryption_AES_MIN;//构造AES加密器
		decryption_AES_MIN.SetKey((unsigned char*)key, AES::MIN_KEYLENGTH);//设置AES密钥
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		long long source_file_size;//文件数据总需要处理的字节数
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_AES_MIN_final(false);
			goto Delete_this_class_unlock_AES_MIN;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		if (have_head_digit)//头部特征数字校验。因为tellg()仅在读取文件之前有效，如果先读取头部特征数字会造成该函数无效
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得解密信息确认界面提供的头部数字并将其转换回原始数据显示
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//转为QString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//存放输入文件头部特征数字的char数组
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//读取特征数字。这里需要注意，如果特征数字为全空即“00000000”的时候，使用动态数组则会出现数组长度为0的情况，因此需要用固定长度的char数组
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//存放加密文件头部魔法数字的十六进制数据
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//获得十六进制数据，转换为大写
			QString source_head_digit_transform_string = source_head_digit_transform;//转为QString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//头部特征数字相同，进行解密
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//去掉头部特征数字占用的空间
				source_file.clear();//清空文件流，否则可能无法定位
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//将文件指针偏移到头部特征数字之后
			}
			else//头部特征数字不同，取消解密
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_AES_MIN_final(false);
				goto Delete_this_class_unlock_AES_MIN;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_AES_MIN_final(false);
			goto Delete_this_class_unlock_AES_MIN;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		long long total_count = source_file_size / AES::BLOCKSIZE;//总处理周期数，不包含最后一次
		long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, AES::BLOCKSIZE);//读入AES::BLOCKSIZE个字节
			decryption_AES_MIN.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//加密
			target_file.write(target_file_data, AES::BLOCKSIZE);//写入目标文件
			emit unlock_AES_MIN_process((double)(AES::BLOCKSIZE*loop_count) / (double)source_file_size);//发出信号给主界面进度条使用
		}
		int source_file_size_remain = source_file_size - total_count * AES::BLOCKSIZE;//剩余字节数
		if (source_file_size_remain > 0)//如果还有剩余的内容，要计入最后一次处理
		{
			if (is_decode_fully)
			{
				char *source_file_data_remain = new char[AES::BLOCKSIZE];
				char *target_file_data_remain = new char[AES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, AES::BLOCKSIZE);//初始化数组为填充内容
				source_file.read(source_file_data_remain, AES::BLOCKSIZE);//读入AES::BLOCKSIZE个字节
				decryption_AES_MIN.ProcessAndXorBlock((unsigned char*)source_file_data_remain, xor_block, (unsigned char*)target_file_data_remain);//加密
				target_file.write(target_file_data_remain, AES::BLOCKSIZE);//写入目标文件
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//读入剩下的字节
				target_file.write(source_file_data_remain, source_file_size_remain);//写入目标文件
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//释放内存
		source_file.close();
		target_file.close();
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
		emit unlock_AES_MIN_final(true);
	Delete_this_class_unlock_AES_MIN://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockSingle::lock_AES_MIDDLE(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully)//AES加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否加密剩下不足一个加密单位的明文（AES需要补足才会进行加密，这样的话解密出来的文件与原来的可能会有偏差）
	{
		srand((int)time(NULL));//生成随机种子供之后使用
		char *source_file_data = new char[AES::BLOCKSIZE];//待加密文件数据
		char *target_file_data = new char[AES::BLOCKSIZE];//加密后文件数据
		unsigned char *xor_block = new unsigned char[AES::BLOCKSIZE];//必须设定为全零
		memset(xor_block, 0, AES::BLOCKSIZE);//置零
		AESEncryption encryption_AES_MIDDLE;//构造AES加密器
		set_key_AES_MIDDLE(key);//生成一个随机的AES密钥
		encryption_AES_MIDDLE.SetKey((unsigned char*)key, FILE_KEY_AES_MIDDLE_KEY_LENGTH);//设置AES密钥
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_AES_MIDDLE_final(false, key);
			goto Delete_this_class_lock_AES_MIDDLE;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
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
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_AES_MIDDLE_final(false, key);
			goto Delete_this_class_lock_AES_MIDDLE;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		long long total_count = source_file_size / AES::BLOCKSIZE;//总处理周期数，不包含最后一次
		long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, AES::BLOCKSIZE);//读入AES::BLOCKSIZE个字节
			encryption_AES_MIDDLE.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//加密
			target_file.write(target_file_data, AES::BLOCKSIZE);//写入目标文件
			emit lock_AES_MIDDLE_process((double)(AES::BLOCKSIZE*loop_count) / (double)source_file_size);//发出信号给主界面进度条使用
		}
		int source_file_size_remain = source_file_size - total_count * AES::BLOCKSIZE;//剩余字节数
		if (source_file_size_remain > 0)//如果还有剩余的内容，要计入最后一次处理
		{
			if (is_encode_fully)
			{
				char *source_file_data_remain = new char[AES::BLOCKSIZE];
				char *target_file_data_remain = new char[AES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, AES::BLOCKSIZE);//初始化数组为填充内容
				source_file.read(source_file_data_remain, AES::BLOCKSIZE);//读入AES::BLOCKSIZE个字节
				encryption_AES_MIDDLE.ProcessAndXorBlock((unsigned char*)source_file_data_remain, xor_block, (unsigned char*)target_file_data_remain);//加密
				target_file.write(target_file_data_remain, AES::BLOCKSIZE);//写入目标文件
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//读入剩下的字节
				target_file.write(source_file_data_remain, source_file_size_remain);//写入目标文件
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//释放内存
		delete target_file_data;//释放内存
		delete xor_block;//释放内存
		source_file.close();
		target_file.close();
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
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_5_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出加密类型
			QByteArray key_transform(key, FILE_KEY_AES_MIDDLE_KEY_LENGTH * 2);//输出密钥
			key_transform = (key_transform.toHex()).toUpper();
			string key_string(key_transform.data(), FILE_KEY_AES_MIDDLE_KEY_LENGTH * 2);
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//输出头部特征数字
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得头部数字并将其转换回原始数据显示
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
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_7_NUMBER;//加密类型
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//无头部特征数字标记
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//有头部特征数字标记
			key_file_binary << magic_number_string;//写入头部魔术数字
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//输出加密类型，按int型格式写入（4字节）
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write(key, FILE_KEY_AES_MIDDLE_KEY_LENGTH);//写入密钥
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
		emit lock_AES_MIDDLE_final(true, key);
	Delete_this_class_lock_AES_MIDDLE://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockSingle::unlock_AES_MIDDLE(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully)//AES-128解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否解密剩下不足一个解密单位的密文（AES需要补足才会进行解密，这样的话解密出来的文件与原来的可能会有偏差）
	{

		//注意因为是对称加密，所以加解密方式非常接近
		char *source_file_data = new char[AES::BLOCKSIZE];//待解密文件数据
		char *target_file_data = new char[AES::BLOCKSIZE];//解密后文件数据
		unsigned char *xor_block = new unsigned char[AES::BLOCKSIZE];//必须设定为全零
		memset(xor_block, 0, AES::BLOCKSIZE);//置零
		AESDecryption decryption_AES_MIDDLE;//构造AES加密器
		decryption_AES_MIDDLE.SetKey((unsigned char*)key, FILE_KEY_AES_MIDDLE_KEY_LENGTH);//设置AES密钥
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		long long source_file_size;//文件数据总需要处理的字节数
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_AES_MIDDLE_final(false);
			goto Delete_this_class_unlock_AES_MIDDLE;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		if (have_head_digit)//头部特征数字校验。因为tellg()仅在读取文件之前有效，如果先读取头部特征数字会造成该函数无效
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得解密信息确认界面提供的头部数字并将其转换回原始数据显示
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//转为QString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//存放输入文件头部特征数字的char数组
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//读取特征数字。这里需要注意，如果特征数字为全空即“00000000”的时候，使用动态数组则会出现数组长度为0的情况，因此需要用固定长度的char数组
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//存放加密文件头部魔法数字的十六进制数据
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//获得十六进制数据，转换为大写
			QString source_head_digit_transform_string = source_head_digit_transform;//转为QString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//头部特征数字相同，进行解密
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//去掉头部特征数字占用的空间
				source_file.clear();//清空文件流，否则可能无法定位
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//将文件指针偏移到头部特征数字之后
			}
			else//头部特征数字不同，取消解密
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_AES_MIDDLE_final(false);
				goto Delete_this_class_unlock_AES_MIDDLE;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_AES_MIDDLE_final(false);
			goto Delete_this_class_unlock_AES_MIDDLE;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		long long total_count = source_file_size / AES::BLOCKSIZE;//总处理周期数，不包含最后一次
		long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, AES::BLOCKSIZE);//读入AES::BLOCKSIZE个字节
			decryption_AES_MIDDLE.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//加密
			target_file.write(target_file_data, AES::BLOCKSIZE);//写入目标文件
			emit unlock_AES_MIDDLE_process((double)(AES::BLOCKSIZE*loop_count) / (double)source_file_size);//发出信号给主界面进度条使用
		}
		int source_file_size_remain = source_file_size - total_count * AES::BLOCKSIZE;//剩余字节数
		if (source_file_size_remain > 0)//如果还有剩余的内容，要计入最后一次处理
		{
			if (is_decode_fully)
			{
				char *source_file_data_remain = new char[AES::BLOCKSIZE];
				char *target_file_data_remain = new char[AES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, AES::BLOCKSIZE);//初始化数组为填充内容
				source_file.read(source_file_data_remain, AES::BLOCKSIZE);//读入AES::BLOCKSIZE个字节
				decryption_AES_MIDDLE.ProcessAndXorBlock((unsigned char*)source_file_data_remain, xor_block, (unsigned char*)target_file_data_remain);//加密
				target_file.write(target_file_data_remain, AES::BLOCKSIZE);//写入目标文件
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//读入剩下的字节
				target_file.write(source_file_data_remain, source_file_size_remain);//写入目标文件
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//释放内存
		source_file.close();
		target_file.close();
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
		emit unlock_AES_MIDDLE_final(true);
	Delete_this_class_unlock_AES_MIDDLE://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockSingle::lock_AES_MAX(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, char *key, bool is_encode_fully)//AES加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否加密剩下不足一个加密单位的明文（AES需要补足才会进行加密，这样的话解密出来的文件与原来的可能会有偏差）
	{
		srand((int)time(NULL));//生成随机种子供之后使用
		char *source_file_data = new char[AES::BLOCKSIZE];//待加密文件数据
		char *target_file_data = new char[AES::BLOCKSIZE];//加密后文件数据
		unsigned char *xor_block = new unsigned char[AES::BLOCKSIZE];//必须设定为全零
		memset(xor_block, 0, AES::BLOCKSIZE);//置零
		AESEncryption encryption_AES_MAX;//构造AES加密器
		set_key_AES_MAX(key);//生成一个随机的AES密钥
		encryption_AES_MAX.SetKey((unsigned char*)key, AES::MAX_KEYLENGTH);//设置AES密钥
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_AES_MAX_final(false, key);
			goto Delete_this_class_lock_AES_MAX;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
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
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_AES_MAX_final(false, key);
			goto Delete_this_class_lock_AES_MAX;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		long long total_count = source_file_size / AES::BLOCKSIZE;//总处理周期数，不包含最后一次
		long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, AES::BLOCKSIZE);//读入AES::BLOCKSIZE个字节
			encryption_AES_MAX.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//加密
			target_file.write(target_file_data, AES::BLOCKSIZE);//写入目标文件
			emit lock_AES_MAX_process((double)(AES::BLOCKSIZE*loop_count) / (double)source_file_size);//发出信号给主界面进度条使用
		}
		int source_file_size_remain = source_file_size - total_count * AES::BLOCKSIZE;//剩余字节数
		if (source_file_size_remain > 0)//如果还有剩余的内容，要计入最后一次处理
		{
			if (is_encode_fully)
			{
				char *source_file_data_remain = new char[AES::BLOCKSIZE];
				char *target_file_data_remain = new char[AES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, AES::BLOCKSIZE);//初始化数组为填充内容
				source_file.read(source_file_data_remain, AES::BLOCKSIZE);//读入AES::BLOCKSIZE个字节
				encryption_AES_MAX.ProcessAndXorBlock((unsigned char*)source_file_data_remain, xor_block, (unsigned char*)target_file_data_remain);//加密
				target_file.write(target_file_data_remain, AES::BLOCKSIZE);//写入目标文件
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//读入剩下的字节
				target_file.write(source_file_data_remain, source_file_size_remain);//写入目标文件
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//释放内存
		delete target_file_data;//释放内存
		delete xor_block;//释放内存
		source_file.close();
		target_file.close();
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
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_6_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出加密类型
			QByteArray key_transform(key, AES::MAX_KEYLENGTH * 2);//输出密钥
			key_transform = (key_transform.toHex()).toUpper();
			string key_string(key_transform.data(), AES::MAX_KEYLENGTH * 2);
			key_file << FILE_KEY_WRITE_INFORMATION_6_STRING << key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//输出头部特征数字
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得头部数字并将其转换回原始数据显示
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
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_8_NUMBER;//加密类型
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//无头部特征数字标记
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//有头部特征数字标记
			key_file_binary << magic_number_string;//写入头部魔术数字
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//输出加密类型，按int型格式写入（4字节）
			key_file_binary << interval_number_string;//写入分隔符
			key_file_binary.write(key, AES::MAX_KEYLENGTH);//写入密钥
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
		emit lock_AES_MAX_final(true, key);
	Delete_this_class_lock_AES_MAX://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockSingle::unlock_AES_MAX(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *key, bool is_decode_fully)//AES-128解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否有头部特征数字，头部特征数字，存储密钥所用数组，是否解密剩下不足一个解密单位的密文（AES需要补足才会进行解密，这样的话解密出来的文件与原来的可能会有偏差）
	{

		//注意因为是对称加密，所以加解密方式非常接近
		char *source_file_data = new char[AES::BLOCKSIZE];//待解密文件数据
		char *target_file_data = new char[AES::BLOCKSIZE];//解密后文件数据
		unsigned char *xor_block = new unsigned char[AES::BLOCKSIZE];//必须设定为全零
		memset(xor_block, 0, AES::BLOCKSIZE);//置零
		AESDecryption decryption_AES_MAX;//构造AES加密器
		decryption_AES_MAX.SetKey((unsigned char*)key, AES::MAX_KEYLENGTH);//设置AES密钥
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//待加密的输入文件流对象，按二进制格式打开，打开时光标在文件结尾
		string target_file_path = file_output_front_path;//输出文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		long long source_file_size;//文件数据总需要处理的字节数
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_AES_MAX_final(false);
			goto Delete_this_class_unlock_AES_MAX;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		if (have_head_digit)//头部特征数字校验。因为tellg()仅在读取文件之前有效，如果先读取头部特征数字会造成该函数无效
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得解密信息确认界面提供的头部数字并将其转换回原始数据显示
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//转为QString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//存放输入文件头部特征数字的char数组
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//读取特征数字。这里需要注意，如果特征数字为全空即“00000000”的时候，使用动态数组则会出现数组长度为0的情况，因此需要用固定长度的char数组
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//存放加密文件头部魔法数字的十六进制数据
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//获得十六进制数据，转换为大写
			QString source_head_digit_transform_string = source_head_digit_transform;//转为QString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//头部特征数字相同，进行解密
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//去掉头部特征数字占用的空间
				source_file.clear();//清空文件流，否则可能无法定位
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//将文件指针偏移到头部特征数字之后
			}
			else//头部特征数字不同，取消解密
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_AES_MAX_final(false);
				goto Delete_this_class_unlock_AES_MAX;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_AES_MAX_final(false);
			goto Delete_this_class_unlock_AES_MAX;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		long long total_count = source_file_size / AES::BLOCKSIZE;//总处理周期数，不包含最后一次
		long long cycle_rest_count = 0;//每个周期按照处理周期处理之后剩下的单个处理间隔内的字节数。比如处理文件块大小FILE_ONCE_MAX_SIZE_NUMBER为10，处理间隔cycle为4，上一周期该数值为1，那么首先偏移1，处理该字节，然后偏移4，处理该字节，再偏移4，处理，最后有1个字节，小于处理间隔，就是当前处理周期内的该值
		for (long long loop_count = 1; loop_count <= total_count; loop_count++)
		{
			source_file.read(source_file_data, AES::BLOCKSIZE);//读入AES::BLOCKSIZE个字节
			decryption_AES_MAX.ProcessBlock((unsigned char*)source_file_data, (unsigned char*)target_file_data);//加密
			target_file.write(target_file_data, AES::BLOCKSIZE);//写入目标文件
			emit unlock_AES_MAX_process((double)(AES::BLOCKSIZE*loop_count) / (double)source_file_size);//发出信号给主界面进度条使用
		}
		int source_file_size_remain = source_file_size - total_count * AES::BLOCKSIZE;//剩余字节数
		if (source_file_size_remain > 0)//如果还有剩余的内容，要计入最后一次处理
		{
			if (is_decode_fully)
			{
				char *source_file_data_remain = new char[AES::BLOCKSIZE];
				char *target_file_data_remain = new char[AES::BLOCKSIZE];
				memset(source_file_data_remain, FILE_LOCK_TAIL_ADD_CHAR, AES::BLOCKSIZE);//初始化数组为填充内容
				source_file.read(source_file_data_remain, AES::BLOCKSIZE);//读入AES::BLOCKSIZE个字节
				decryption_AES_MAX.ProcessAndXorBlock((unsigned char*)source_file_data_remain, xor_block, (unsigned char*)target_file_data_remain);//加密
				target_file.write(target_file_data_remain, AES::BLOCKSIZE);//写入目标文件
				delete source_file_data_remain;
				delete target_file_data_remain;
			}
			else
			{
				char *source_file_data_remain = new char[source_file_size_remain];
				source_file.read(source_file_data_remain, source_file_size_remain);//读入剩下的字节
				target_file.write(source_file_data_remain, source_file_size_remain);//写入目标文件
				delete source_file_data_remain;
			}
		}
		else
		{

		}
		delete source_file_data;//释放内存
		source_file.close();
		target_file.close();
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
		emit unlock_AES_MAX_final(true);
	Delete_this_class_unlock_AES_MAX://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockDouble::lock_RSA(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *public_key, int size)//RSA加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否有头部特征数字，头部特征数字，公钥，密钥大小
	{
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//输入文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		string target_file_data_string;//加密之后得到的密文的十六进制进制码
		string target_file_path = file_output_front_path;
		string source_file_data_string;
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		AutoSeededRandomPool pool;
		QByteArray public_key_hex_string(public_key, size / 2);//将密钥转化为QBytearray
		public_key_hex_string = public_key_hex_string.toHex().toUpper();//获得十六进制数据，转换为大写
		RSAES_OAEP_SHA_Encryptor encryptor;//加密器
		RSA::PublicKey rsa_public_key;
		string rsa_public_key_string = (string((const char *)((QString)public_key_hex_string).toLocal8Bit()));
		HexDecoder decoder;
		try
		{
			decoder.Put((byte*)rsa_public_key_string.c_str(), size);
			encryptor.AccessKey().Load(decoder);
		}
		catch (BERDecodeErr eBERDecodeErr)//出现由密钥错误导致无法解码的异常
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_RSA_wrong_key();
			goto Delete_this_class_lock_RSA;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_RSA_final(false);
			goto Delete_this_class_lock_RSA;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
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
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_RSA_final(false);
			goto Delete_this_class_lock_RSA;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		char *source_file_data = new char[source_file_size];//待加密文件数据
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		source_file.read(source_file_data, source_file_size);//读入source_file_size个字节
		source_file_data_string = source_file_data;//crypto++库极其神秘，如果使用char*会出现无法识别“\0”字符的情况，并且解密出来的内容还会带有不少垃圾数据，可是使用配合了resize()的string却没有问题，和平时使用的情况有点不一样。初步猜测是这个库数据类型转换的问题
		source_file_data_string.resize(source_file_size);
		try
		{
			StringSink *temp_stringsink = new StringSink(target_file_data_string);
			HexEncoder *temp_hexencorder = new HexEncoder(temp_stringsink);
			PK_EncryptorFilter *temp_encryptorfilter = new PK_EncryptorFilter(pool, encryptor, temp_hexencorder);
			StringSource(source_file_data_string, true, temp_encryptorfilter);
			QByteArray file_hex_bytearray(target_file_data_string.c_str(), target_file_data_string.length());//加密出来的内容是十六进制码的文本形式，必须将其转回原始的十六进制码
			delete temp_stringsink;
			delete temp_hexencorder;
			delete temp_encryptorfilter;
			file_hex_bytearray = QByteArray::fromHex(file_hex_bytearray);//获得十六进制数据，转换为大写
			target_file.write(file_hex_bytearray.data(), file_hex_bytearray.length());//写入目标文件
		}
		catch (InvalidArgument eInvalidArgument)//出现由密钥长度过短或者原文长度过长引起的异常
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_RSA_out_of_range();
			goto Delete_this_class_lock_RSA;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		delete source_file_data;//释放内存
		source_file.close();
		target_file.close();
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
		emit lock_RSA_final(true);
	Delete_this_class_lock_RSA://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockDouble::unlock_RSA(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *private_key, int size)//RSA解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否有头部特征数字，头部特征数字，私钥，密钥大小
	{

		//经过漫长时间测试出来的crypto++参数：和大多数资料表明的不一样，加密、解密两个StringSource()中，原始字符串绝对不能使用char*，否则处理过程中会出现加密时无法识别“\0”，解密时会附带一些垃圾数据（原因不明，虽然char*数组规定了长度，但毫无作用）。这两个地方都应该使用string类型，为保险起见，使用resize()重新固定长度，这样解密出来的内容和原文完全一样，也不会加密过长但带有“\0”的文件（比如含有大量“\0”的exe文件）
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//输入文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		string target_file_data_string;
		string target_file_path = file_output_front_path;
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		AutoSeededRandomPool pool;
		QByteArray private_key_hex_string(private_key, size / 2);//将密钥转化为QBytearray
		private_key_hex_string = private_key_hex_string.toHex().toUpper();//获得十六进制数据，转换为大写
		RSAES_OAEP_SHA_Decryptor decryptor;//解密器
		RSA::PrivateKey rsa_private_key;
		string rsa_private_key_string = (string((const char *)((QString)private_key_hex_string).toLocal8Bit()));
		HexDecoder decoder;
		try
		{
			decoder.Put((byte*)rsa_private_key_string.c_str(), size);
			decryptor.AccessKey().Load(decoder);
		}
		catch (BERDecodeErr eBERDecodeErr)//出现由密钥错误导致无法解码的异常
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_RSA_wrong_key();
			goto Delete_this_class_unlock_RSA;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_RSA_final(false);
			goto Delete_this_class_unlock_RSA;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		long long source_file_size;//文件数据总需要处理的字节
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		if (have_head_digit)//头部特征数字校验。因为tellg()仅在读取文件之前有效，如果先读取头部特征数字会造成该函数无效
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得解密信息确认界面提供的头部数字并将其转换回原始数据显示
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//转为QString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//存放输入文件头部特征数字的char数组
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//读取特征数字。这里需要注意，如果特征数字为全空即“00000000”的时候，使用动态数组则会出现数组长度为0的情况，因此需要用固定长度的char数组
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//存放加密文件头部魔法数字的十六进制数据
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//获得十六进制数据，转换为大写
			QString source_head_digit_transform_string = source_head_digit_transform;//转为QString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//头部特征数字相同，进行解密
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//去掉头部特征数字占用的空间
				source_file.clear();//清空文件流，否则可能无法定位
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//将文件指针偏移到头部特征数字之后
			}
			else//头部特征数字不同，取消解密
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_RSA_final(false);
				goto Delete_this_class_unlock_RSA;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_RSA_final(false);
			goto Delete_this_class_unlock_RSA;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		char *source_file_data = new char[source_file_size];//待加密文件数据
		source_file.read(source_file_data, source_file_size);//读入source_file_size个字节
		try//之前说过crypto++极其神秘，这里如果不使用string，大概率会出现解密失败的情况，根据异常来看密文长度出错，又是不能识别“\0”字符的问题，但诡异的是，有时候这个库识别出来的密文长度居然比实际长度还大，目前原因不明，猜测是char*转byte*的过程中出现了一些问题
		{
			QByteArray source_file_hex_bytearray(source_file_data, source_file_size);//将原文转化为QBytearray
			source_file_hex_bytearray = source_file_hex_bytearray.toHex().toUpper();//获得十六进制数据，转换为大写
			string source_file_data_string = source_file_hex_bytearray.data();
			source_file_data_string.resize(source_file_size * 2);
			StringSource(source_file_data_string, true, new HexDecoder(new PK_DecryptorFilter(pool, decryptor, new StringSink(target_file_data_string))));
		}
		catch (InvalidArgument eInvalidArgument)//出现由密钥长度过短或者原文长度过长引起的异常
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_RSA_out_of_range();
			goto Delete_this_class_unlock_RSA;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		catch (InvalidCiphertext eInvalidCiphertext)//密文错误异常
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_RSA_out_of_range();
			goto Delete_this_class_unlock_RSA;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		catch (Exception eException)//密钥错误
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_RSA_wrong_key();
			goto Delete_this_class_unlock_RSA;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		target_file.write(target_file_data_string.c_str(), target_file_data_string.length());//写入目标文件
		delete source_file_data;//释放内存
		source_file.close();
		target_file.close();
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
		emit unlock_RSA_final(true);
	Delete_this_class_unlock_RSA://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockDouble::lock_ECC(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *public_key, int size)//RSA加密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否有头部特征数字，头部特征数字，公钥，密钥大小
	{
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//输入文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		string target_file_data_string;//加密之后得到的密文的十六进制进制码
		string target_file_path = file_output_front_path;
		string source_file_data_string;
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		AutoSeededRandomPool pool;
		QByteArray public_key_hex_string(public_key, size / 2);//将密钥转化为QBytearray
		public_key_hex_string = public_key_hex_string.toHex().toUpper();//获得十六进制数据，转换为大写
		ECIES<ECP>::Encryptor encryptor;//加密器
		ECIES<ECP>::PublicKey rsa_public_key;
		string rsa_public_key_string = (string((const char *)((QString)public_key_hex_string).toLocal8Bit()));
		HexDecoder decoder;
		try
		{
			decoder.Put((byte*)rsa_public_key_string.c_str(), size);
			encryptor.AccessKey().Load(decoder);
		}
		catch (BERDecodeErr eBERDecodeErr)//出现由密钥错误导致无法解码的异常
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_ECC_wrong_key();
			goto Delete_this_class_lock_ECC;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_ECC_final(false);
			goto Delete_this_class_lock_ECC;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
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
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_ECC_final(false);
			goto Delete_this_class_lock_ECC;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		char *source_file_data = new char[source_file_size];//待加密文件数据
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		source_file.read(source_file_data, source_file_size);//读入source_file_size个字节
		source_file_data_string = source_file_data;//crypto++库极其神秘，如果使用char*会出现无法识别“\0”字符的情况，并且解密出来的内容还会带有不少垃圾数据，可是使用配合了resize()的string却没有问题，和平时使用的情况有点不一样。初步猜测是这个库数据类型转换的问题
		source_file_data_string.resize(source_file_size);
		try
		{
			StringSource(source_file_data_string, true, new PK_EncryptorFilter(pool, encryptor, new HexEncoder(new StringSink(target_file_data_string))));
			QByteArray file_hex_bytearray(target_file_data_string.c_str(), target_file_data_string.length());//加密出来的内容是十六进制码的文本形式，必须将其转回原始的十六进制码
			file_hex_bytearray = QByteArray::fromHex(file_hex_bytearray);//获得十六进制数据，转换为大写
			target_file.write(file_hex_bytearray.data(), file_hex_bytearray.length());//写入目标文件
		}
		catch (InvalidArgument eInvalidArgument)//出现由密钥长度过短或者原文长度过长引起的异常
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit lock_ECC_out_of_range();
			goto Delete_this_class_lock_ECC;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		delete source_file_data;//释放内存
		source_file.close();
		target_file.close();
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
		emit lock_ECC_final(true);
	Delete_this_class_lock_ECC://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void LockDouble::unlock_ECC(const string &file_path, const string &file_name, const string &file_output_front_path, const string &file_output_back_path, bool is_output_history_file, const string &history_file_path, bool have_head_digit, char *head_digit, char *private_key, int size)//ECC解密。输入参数：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，是否输出历史文件，输出历史文件路径，是否有头部特征数字，头部特征数字，私钥，密钥大小
	{

		//经过漫长时间测试出来的crypto++参数：和大多数资料表明的不一样，加密、解密两个StringSource()中，原始字符串绝对不能使用char*，否则处理过程中会出现加密时无法识别“\0”，解密时会附带一些垃圾数据（原因不明，虽然char*数组规定了长度，但毫无作用）。这两个地方都应该使用string类型，为保险起见，使用resize()重新固定长度，这样解密出来的内容和原文完全一样，也不会加密过长但带有“\0”的文件（比如含有大量“\0”的exe文件）
		ifstream source_file(file_path, ios_base::in | ios_base::binary | ios_base::ate);//输入文件路径。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		string target_file_data_string;
		string target_file_path = file_output_front_path;
		target_file_path += FILE_FILE_INTERVAL_STRING;
		target_file_path += file_name;
		target_file_path += file_output_back_path;
		ofstream target_file(target_file_path, ios_base::out | ios_base::binary);//生成文件，按二进制格式打开，没有则创建。注意goto不能跳过类类型的初始化语句，因此这个初始化语句必须放到goto之前
		AutoSeededRandomPool pool;
		QByteArray private_key_hex_string(private_key, size / 2);//将密钥转化为QBytearray
		private_key_hex_string = private_key_hex_string.toHex().toUpper();//获得十六进制数据，转换为大写
		ECIES<ECP>::Decryptor decryptor;//加密器
		ECIES<ECP>::PrivateKey rsa_private_key;
		string rsa_private_key_string = (string((const char *)((QString)private_key_hex_string).toLocal8Bit()));
		HexDecoder decoder;
		try
		{
			decoder.Put((byte*)rsa_private_key_string.c_str(), size);
			decryptor.AccessKey().Load(decoder);
		}
		catch (BERDecodeErr eBERDecodeErr)//出现由密钥错误导致无法解码的异常
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_ECC_wrong_key();
			goto Delete_this_class_unlock_ECC;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		if (!source_file.is_open())//文件打开失败
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_ECC_final(false);
			goto Delete_this_class_unlock_ECC;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		long long source_file_size;//文件数据总需要处理的字节
		source_file_size = source_file.tellg();//去掉头部处理起点和尾部处理终点占用的位置
		source_file.seekg(ios_base::beg);//将文件指针偏移到处理起点处，因为之前使用tellg函数时需要光标在文件末尾。此时并不是读取文件造成的文件指针在文件末尾，不需要使用clear
		if (have_head_digit)//头部特征数字校验。因为tellg()仅在读取文件之前有效，如果先读取头部特征数字会造成该函数无效
		{
			QByteArray key_head_digit_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得解密信息确认界面提供的头部数字并将其转换回原始数据显示
			key_head_digit_transform = (key_head_digit_transform.toHex()).toUpper();
			QString key_head_digit_transform_string = key_head_digit_transform;//转为QString
			char source_head_digit_char_array[FILE_HEAD_NUMBER_SIZE_NUMBER + 1] = { 0 };//存放输入文件头部特征数字的char数组
			source_file.read(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//读取特征数字。这里需要注意，如果特征数字为全空即“00000000”的时候，使用动态数组则会出现数组长度为0的情况，因此需要用固定长度的char数组
			QByteArray source_head_digit_transform(source_head_digit_char_array, FILE_HEAD_NUMBER_SIZE_NUMBER);//存放加密文件头部魔法数字的十六进制数据
			source_head_digit_transform = source_head_digit_transform.toHex().toUpper();//获得十六进制数据，转换为大写
			QString source_head_digit_transform_string = source_head_digit_transform;//转为QString
			if (key_head_digit_transform_string == source_head_digit_transform_string)//头部特征数字相同，进行解密
			{
				source_file_size -= FILE_HEAD_NUMBER_SIZE_NUMBER;//去掉头部特征数字占用的空间
				source_file.clear();//清空文件流，否则可能无法定位
				source_file.seekg(FILE_HEAD_NUMBER_SIZE_NUMBER, ios_base::beg);//将文件指针偏移到头部特征数字之后
			}
			else//头部特征数字不同，取消解密
			{
				target_file.close();
				remove(target_file_path.c_str());//删除文件
				emit unlock_ECC_final(false);
				goto Delete_this_class_unlock_ECC;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
			}
		}
		else
		{

		}
		if (source_file_size <= 0)
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_RSA_final(false);
			goto Delete_this_class_unlock_ECC;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		else
		{

		}
		char *source_file_data = new char[source_file_size];//待加密文件数据
		source_file.read(source_file_data, source_file_size);//读入source_file_size个字节
		try//之前说过crypto++极其神秘，这里如果不使用string，大概率会出现解密失败的情况，根据异常来看密文长度出错，又是不能识别“\0”字符的问题，但诡异的是，有时候这个库识别出来的密文长度居然比实际长度还大，目前原因不明，猜测是char*转byte*的过程中出现了一些问题
		{
			QByteArray source_file_hex_bytearray(source_file_data, source_file_size);//将原文转化为QBytearray
			source_file_hex_bytearray = source_file_hex_bytearray.toHex().toUpper();//获得十六进制数据，转换为大写
			string source_file_data_string = source_file_hex_bytearray.data();
			source_file_data_string.resize(source_file_size * 2);
			StringSource(source_file_data_string, true, new HexDecoder(new PK_DecryptorFilter(pool, decryptor, new StringSink(target_file_data_string))));
		}
		catch (InvalidArgument eInvalidArgument)//出现由密钥长度过短或者原文长度过长引起的异常
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_ECC_out_of_range();
			goto Delete_this_class_unlock_ECC;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		catch (InvalidCiphertext eInvalidCiphertext)//密文错误异常
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_ECC_out_of_range();
			goto Delete_this_class_unlock_ECC;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		catch (Exception eException)//密钥错误
		{
			target_file.close();
			remove(target_file_path.c_str());//删除文件
			emit unlock_ECC_wrong_key();
			goto Delete_this_class_unlock_ECC;//由于调试时在此处删除该类指针会报错，用if语句又会非常复杂，故使用跳转语句直接跳转到最后的指针释放语句处
		}
		target_file.write(target_file_data_string.c_str(), target_file_data_string.length());//写入目标文件
		delete source_file_data;//释放内存
		source_file.close();
		target_file.close();
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
		emit unlock_ECC_final(true);
	Delete_this_class_unlock_ECC://用于打开某文件失败时跳出该方法时使用goto语句的跳转标签
		delete this;
	}

	void HashCalculate::hash_calculate_MD4(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path)//MD4计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径
	{
		string result_string;
		MD4 md4;
		FileSource(file_path.c_str(), true, new HashFilter(md4, new HexEncoder(new StringSink(result_string))));
		memmove(result, result_string.c_str(), result_string.length());
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
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_5_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出操作
			history_file.close();
		}
		else
		{

		}
		emit hash_calculate_MD4_final(result_string.length());
		delete this;
	}

	void HashCalculate::hash_calculate_MD5(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path)//MD4计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径
	{
		string result_string;
		MD5 md5;
		FileSource(file_path.c_str(), true, new HashFilter(md5, new HexEncoder(new StringSink(result_string))));
		memmove(result, result_string.c_str(), result_string.length());
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
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_5_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出操作
			history_file.close();
		}
		else
		{

		}
		emit hash_calculate_MD5_final(result_string.length());
		delete this;
	}

	void HashCalculate::hash_calculate_SHA1(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path)//SHA1计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径
	{
		string result_string;
		SHA1 sha1;
		FileSource(file_path.c_str(), true, new HashFilter(sha1, new HexEncoder(new StringSink(result_string))));
		memmove(result, result_string.c_str(), result_string.length());
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
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_5_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出操作
			history_file.close();
		}
		else
		{

		}
		emit hash_calculate_SHA1_final(result_string.length());
		delete this;
	}

	void HashCalculate::hash_calculate_SHA2(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type)//SHA2计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径，计算类型
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
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_5_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出操作
			history_file.close();
		}
		else
		{

		}
		emit hash_calculate_SHA2_final(result_string.length());
		delete this;
	}

	void HashCalculate::hash_calculate_SHA3(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type)//SHA2计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径，计算类型
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
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_5_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出操作
			history_file.close();
		}
		else
		{

		}
		emit hash_calculate_SHA3_final(result_string.length());
		delete this;
	}

	void HashCalculate::hash_calculate_Keccak(const string &file_path, const string &file_name, char *result, bool is_output_history_file, const string &history_file_path, const string &calculate_type)//SHA2计算。输入参数：文件路径，文件名，结果存储单元，是否输出历史文件，输出历史文件路径，计算类型
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
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_5_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出操作
			history_file.close();
		}
		else
		{

		}
		emit hash_calculate_Keccak_final(result_string.length());
		delete this;
	}

	//内部使用的函数
	void LockSingle::set_key_DES(char *key)//生成随机DES密钥，参数为存储密钥的数组
	{
		//因为DES的密钥长度（由枚举DES::DEFAULT_KEYLENGTH表示）实际上为8字节，针对每4位，生成1个随机的十六进制码，然后把生成的十六进制码转化为密钥即可
		QByteArray key_bytearray;//存储密钥
		int randnumber;//随机数
		for (int index = 0; index < DES::DEFAULT_KEYLENGTH * 2; index++)//注意每个字节由2个十六进制码构成
		{
			randnumber = FILE_KEY_RANDOM_HEX_MIN_NUMBER + rand() % (FILE_KEY_RANDOM_HEX_MAX_NUMBER - FILE_KEY_RANDOM_HEX_MIN_NUMBER + 1);//生成随机数
			if (randnumber >= 0 &&randnumber <= 9)
			{
				key_bytearray[index] = (char)(randnumber + (int)FILE_KEY_RANDOM_HEX_0_STRING);//请注意，直接将int转换为char得到的char数值就是原来的int数值，无法使用，需要转换为ASCII码对应的数值
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
		key_bytearray = QByteArray::fromHex(key_bytearray);//转化16进制编码为数据
		memmove(key, key_bytearray.data(), DES::DEFAULT_KEYLENGTH);//将得到的密钥转化为char*作为输出
	}

	void LockSingle::set_key_DES_EDE2(char *key)//生成随机DES_EDE2密钥，参数为存储密钥的数组
	{
		//因为DES-EDE2的密钥长度（由枚举DES_EDE2::DEFAULT_KEYLENGTH表示）实际上为16字节，针对每4位，生成1个随机的十六进制码，然后把生成的十六进制码转化为密钥即可
		QByteArray key_bytearray;//存储密钥
		int randnumber;//随机数
		for (int index = 0; index < DES_EDE2::DEFAULT_KEYLENGTH * 2; index++)//注意每个字节由2个十六进制码构成
		{
			randnumber = FILE_KEY_RANDOM_HEX_MIN_NUMBER + rand() % (FILE_KEY_RANDOM_HEX_MAX_NUMBER - FILE_KEY_RANDOM_HEX_MIN_NUMBER + 1);//生成随机数
			if (randnumber >= 0 &&randnumber <= 9)
			{
				key_bytearray[index] = (char)(randnumber + (int)FILE_KEY_RANDOM_HEX_0_STRING);//请注意，直接将int转换为char得到的char数值就是原来的int数值，无法使用，需要转换为ASCII码对应的数值
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
		key_bytearray = QByteArray::fromHex(key_bytearray);//转化16进制编码为数据
		memmove(key, key_bytearray.data(), DES_EDE2::DEFAULT_KEYLENGTH);//将得到的密钥转化为char*作为输出
	}

	void LockSingle::set_key_DES_EDE3(char *key)//生成随机DES_EDE2密钥，参数为存储密钥的数组
	{
		//因为DES-EDE3的密钥长度（由枚举DES_EDE3::DEFAULT_KEYLENGTH表示）实际上为24字节，针对每4位，生成1个随机的十六进制码，然后把生成的十六进制码转化为密钥即可
		QByteArray key_bytearray;//存储密钥
		int randnumber;//随机数
		for (int index = 0; index < DES_EDE3::DEFAULT_KEYLENGTH * 2; index++)//注意每个字节由2个十六进制码构成
		{
			randnumber = FILE_KEY_RANDOM_HEX_MIN_NUMBER + rand() % (FILE_KEY_RANDOM_HEX_MAX_NUMBER - FILE_KEY_RANDOM_HEX_MIN_NUMBER + 1);//生成随机数
			if (randnumber >= 0 &&randnumber <= 9)
			{
				key_bytearray[index] = (char)(randnumber + (int)FILE_KEY_RANDOM_HEX_0_STRING);//请注意，直接将int转换为char得到的char数值就是原来的int数值，无法使用，需要转换为ASCII码对应的数值
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
		key_bytearray = QByteArray::fromHex(key_bytearray);//转化16进制编码为数据
		memmove(key, key_bytearray.data(), DES_EDE3::DEFAULT_KEYLENGTH);//将得到的密钥转化为char*作为输出
	}

	void LockSingle::set_key_AES_MIN(char *key)//生成随机AES-128密钥，参数为存储密钥的数组
	{
		//因为AES-128的密钥长度（由枚举AES::MIN_KEYLENGTH表示）实际上为16字节，针对每4位，生成1个随机的十六进制码，然后把生成的十六进制码转化为密钥即可
		QByteArray key_bytearray;//存储密钥
		int randnumber;//随机数
		for (int index = 0; index < AES::MIN_KEYLENGTH * 2; index++)//注意每个字节由2个十六进制码构成
		{
			randnumber = FILE_KEY_RANDOM_HEX_MIN_NUMBER + rand() % (FILE_KEY_RANDOM_HEX_MAX_NUMBER - FILE_KEY_RANDOM_HEX_MIN_NUMBER + 1);//生成随机数
			if (randnumber >= 0 &&randnumber <= 9)
			{
				key_bytearray[index] = (char)(randnumber + (int)FILE_KEY_RANDOM_HEX_0_STRING);//请注意，直接将int转换为char得到的char数值就是原来的int数值，无法使用，需要转换为ASCII码对应的数值
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
		key_bytearray = QByteArray::fromHex(key_bytearray);//转化16进制编码为数据
		memmove(key, key_bytearray.data(), AES::MIN_KEYLENGTH);//将得到的密钥转化为char*作为输出
	}

	void LockSingle::set_key_AES_MIDDLE(char *key)//生成随机AES-192密钥，参数为存储密钥的数组
	{
		//因为AES-192的密钥长度（由枚举AES::MIN_KEYLENGTH表示）实际上为24字节，针对每4位，生成1个随机的十六进制码，然后把生成的十六进制码转化为密钥即可
		QByteArray key_bytearray;//存储密钥
		int randnumber;//随机数
		for (int index = 0; index < FILE_KEY_AES_MIDDLE_KEY_LENGTH * 2; index++)//注意每个字节由2个十六进制码构成
		{
			randnumber = FILE_KEY_RANDOM_HEX_MIN_NUMBER + rand() % (FILE_KEY_RANDOM_HEX_MAX_NUMBER - FILE_KEY_RANDOM_HEX_MIN_NUMBER + 1);//生成随机数
			if (randnumber >= 0 &&randnumber <= 9)
			{
				key_bytearray[index] = (char)(randnumber + (int)FILE_KEY_RANDOM_HEX_0_STRING);//请注意，直接将int转换为char得到的char数值就是原来的int数值，无法使用，需要转换为ASCII码对应的数值
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
		key_bytearray = QByteArray::fromHex(key_bytearray);//转化16进制编码为数据
		memmove(key, key_bytearray.data(), FILE_KEY_AES_MIDDLE_KEY_LENGTH);//将得到的密钥转化为char*作为输出
	}

	void LockSingle::set_key_AES_MAX(char *key)//生成随机AES-256密钥，参数为存储密钥的数组
	{
		//因为AES-256的密钥长度（由枚举AES::MIN_KEYLENGTH表示）实际上为32字节，针对每4位，生成1个随机的十六进制码，然后把生成的十六进制码转化为密钥即可
		QByteArray key_bytearray;//存储密钥
		int randnumber;//随机数
		for (int index = 0; index < AES::MAX_KEYLENGTH * 2; index++)//注意每个字节由2个十六进制码构成
		{
			randnumber = FILE_KEY_RANDOM_HEX_MIN_NUMBER + rand() % (FILE_KEY_RANDOM_HEX_MAX_NUMBER - FILE_KEY_RANDOM_HEX_MIN_NUMBER + 1);//生成随机数
			if (randnumber >= 0 &&randnumber <= 9)
			{
				key_bytearray[index] = (char)(randnumber + (int)FILE_KEY_RANDOM_HEX_0_STRING);//请注意，直接将int转换为char得到的char数值就是原来的int数值，无法使用，需要转换为ASCII码对应的数值
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
		key_bytearray = QByteArray::fromHex(key_bytearray);//转化16进制编码为数据
		memmove(key, key_bytearray.data(), AES::MAX_KEYLENGTH);//将得到的密钥转化为char*作为输出
	}

	//非对称加密密钥生成
	void LockDouble::set_key_RSA(char *public_key, char *private_key, int size, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, const string &output_path)//RSA密钥生成。输入参数：公钥存储单元，私钥存储单元，密钥长度，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径，是否有头部特征数字，头部特征数字，密钥文件生成路径
	{
		AutoSeededRandomPool randompool;
		InvertibleRSAFunction rsa_function;
		rsa_function.GenerateRandomWithKeySize(randompool, size);
		RSA::PrivateKey rsa_private_key(rsa_function);//私钥
		RSA::PublicKey rsa_public_key(rsa_function);//公钥
		string rsa_private_key_string;//将密钥保存到指定位置
		string rsa_public_key_string;
		HexEncoder public_key_encoder(new StringSink(rsa_public_key_string));//将密钥转化为字符串并输出
		rsa_public_key.DEREncode(public_key_encoder);
		public_key_encoder.MessageEnd();
		HexEncoder private_key_encoder(new StringSink(rsa_private_key_string));
		rsa_private_key.DEREncode(private_key_encoder);
		private_key_encoder.MessageEnd();
		int public_key_length = rsa_public_key_string.length();//密钥长度
		int private_key_length = rsa_private_key_string.length();
		if (is_output_history_file)//需要写入历史文件
		{
			time_t system_time;//存储系统时间
			time(&system_time);//获取系统时间
			struct tm *time_struct = localtime(&system_time);//获取指向时间结构体的指针
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//历史文件使用附加方式打开
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//输出相应内容。这里为时间
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//按格式输出时间
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_4_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出操作
			history_file.close();
		}
		else
		{

		}
		if (is_output_key_file)//需要生成密钥文件
		{
			ofstream key_file(output_path + key_file_path, ios_base::out);//处理文本类型的密钥文件，使用覆盖方式打开
			key_file << FILE_KEY_WRITE_INFORMATION_1_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出相应内容。这里为密钥文件头部内容
			key_file << FILE_KEY_WRITE_INFORMATION_3_STRING << output_path << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出文件路径
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_7_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出加密类型
			key_file << FILE_KEY_WRITE_INFORMATION_6_1_STRING << rsa_public_key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			key_file << FILE_KEY_WRITE_INFORMATION_6_2_STRING << rsa_private_key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//输出头部特征数字
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得头部数字并将其转换回原始数据显示
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
		QByteArray public_key_bytearray((char*)rsa_public_key_string.c_str(), public_key_length);//转换为QByteArray
		public_key_bytearray = QByteArray::fromHex(public_key_bytearray);//转化为16进制编码
		memmove(public_key, public_key_bytearray.data(), public_key_length / 2);//直接复制内存。注意转换编码后长度会减少一半
		QByteArray private_key_bytearray((char*)rsa_private_key_string.c_str(), private_key_length);//转换为QByteArray
		private_key_bytearray = QByteArray::fromHex(private_key_bytearray);//转化为16进制编码
		memmove(private_key, private_key_bytearray.data(), private_key_length / 2);//直接复制内存。注意转换编码后长度会减少一半
		if (is_output_key_file_binary)//需要生成二进制密钥文件
		{

			//输出公钥文件
			ofstream public_key_file_binary(output_path + key_file_binary_path + FILE_PUBLIC_KEY_FILE_EXTRA_PATH_STRING, ios_base::binary | ios_base::out);//处理二进制类型的密钥文件，使用覆盖方式打开
			QByteArray magic_number = FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING;//等待加入的头部魔术数字
			QByteArray interval_number = FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING;//二进制文件分隔符
			QByteArray interval_short_number = FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING;//二进制文件短分隔符
			magic_number = QByteArray::fromHex(magic_number);//转化为16进制编码
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			string magic_number_string(magic_number.constData(), magic_number.length());//QByteArray转string
			string interval_number_string(interval_number.constData(), interval_number.length());
			string interval_short_number_string(interval_short_number.constData(), interval_short_number.length());
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_9_NUMBER;//加密类型
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//无头部特征数字标记
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//有头部特征数字标记
			public_key_file_binary << magic_number_string;//写入头部魔术数字
			public_key_file_binary << interval_number_string;//写入分隔符
			public_key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//输出加密类型，按int型格式写入（4字节）
			public_key_file_binary << interval_number_string;//写入分隔符
			public_key_file_binary.write((char*)(&public_key_length), sizeof(public_key_length));//输出密钥长度，按int型格式写入（4字节）
			public_key_file_binary.write(public_key, public_key_length / 2);//写入密钥
			public_key_file_binary << interval_number_string;//写入分隔符
			if (have_head_digit)//写入头部特征数字信息
			{
				public_key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//输出有头部特征数字标记，按int型格式写入（4字节）
				public_key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//写入头部特征数字
			}
			else
			{
				public_key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//输出无头部特征数字标记，按int型格式写入（4字节）
				public_key_file_binary << interval_short_number_string;//写入相应位数的分隔符占位
			}
			public_key_file_binary << interval_number_string;//写入分隔符
			public_key_file_binary.close();

			//输出私钥文件
			ofstream private_key_file_binary(output_path + key_file_binary_path + FILE_PRIVATE_KEY_FILE_EXTRA_PATH_STRING, ios_base::binary | ios_base::out);//处理二进制类型的密钥文件，使用覆盖方式打开
			magic_number = QByteArray::fromHex(magic_number);//转化为16进制编码
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_10_NUMBER;//加密类型
			private_key_file_binary << magic_number_string;//写入头部魔术数字
			private_key_file_binary << interval_number_string;//写入分隔符
			private_key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//输出加密类型，按int型格式写入（4字节）
			private_key_file_binary << interval_number_string;//写入分隔符
			private_key_file_binary.write((char*)(&private_key_length), sizeof(private_key_length));//输出密钥长度，按int型格式写入（4字节）
			private_key_file_binary.write(private_key, private_key_length / 2);//写入密钥
			private_key_file_binary << interval_number_string;//写入分隔符
			if (have_head_digit)//写入头部特征数字信息
			{
				private_key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//输出有头部特征数字标记，按int型格式写入（4字节）
				private_key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//写入头部特征数字
			}
			else
			{
				private_key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//输出无头部特征数字标记，按int型格式写入（4字节）
				private_key_file_binary << interval_short_number_string;//写入相应位数的分隔符占位
			}
			private_key_file_binary << interval_number_string;//写入分隔符
			private_key_file_binary.close();
		}
		else
		{

		}
		emit set_key_RSA_final(public_key_length, private_key_length);//密钥生成完毕
		delete this;
	}

	void LockDouble::set_key_ECC(char *public_key, char *private_key, const string &curve_type, bool is_output_history_file, const string &history_file_path, bool is_output_key_file, bool is_output_key_file_binary, const string &key_file_path, const string &key_file_binary_path, bool have_head_digit, char *head_digit, const string &output_path)//ECC密钥生成。输入参数：公钥存储单元，私钥存储单元，密钥长度，是否输出历史文件，输出历史文件路径，是否输出密钥文件，是否输出二进制密钥文件，输出密钥文件路径，是否有头部特征数字，头部特征数字，密钥文件生成路径
	{
		AutoSeededRandomPool randompool;
		ECIES<ECP>::PrivateKey ecc_private_key;
		ECIES<ECP>::PublicKey ecc_public_key;
		if (curve_type == "secp112r1")//生成私钥
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
		ecc_private_key.MakePublicKey(ecc_public_key);//由私钥生成公钥
		string ecc_private_key_string;//将密钥保存到指定位置
		string ecc_public_key_string;
		HexEncoder public_key_encoder(new StringSink(ecc_public_key_string));//将密钥转化为字符串并输出
		ecc_public_key.DEREncode(public_key_encoder);
		public_key_encoder.MessageEnd();
		HexEncoder private_key_encoder(new StringSink(ecc_private_key_string));
		ecc_private_key.DEREncode(private_key_encoder);
		private_key_encoder.MessageEnd();
		int public_key_length = ecc_public_key_string.length();//密钥长度
		int private_key_length = ecc_private_key_string.length();
		if (is_output_history_file)//需要写入历史文件
		{
			time_t system_time;//存储系统时间
			time(&system_time);//获取系统时间
			struct tm *time_struct = localtime(&system_time);//获取指向时间结构体的指针
			ofstream history_file(history_file_path, ios_base::out | ios_base::app);//历史文件使用附加方式打开
			history_file << FILE_HISTORY_WRITE_INFORMATION_1_STRING;//输出相应内容。这里为时间
			history_file << time_struct->tm_year + FILE_HISTORY_WRITE_INFORMATION_1_YEAR_BEGIN_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mon + FILE_HISTORY_WRITE_INFORMATION_1_MONTH_OFFSET_NUMBER << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_1_STRING << time_struct->tm_mday << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_2_STRING << time_struct->tm_hour << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_min << FILE_HISTORY_WRITE_INFORMATION_1_INTERVAL_3_STRING << time_struct->tm_sec << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING;//按格式输出时间
			history_file << FILE_HISTORY_WRITE_INFORMATION_4_1_STRING << FILE_HISTORY_WRITE_INFORMATION_4_4_STRING << FILE_HISTORY_WRITE_INFORMATION_1_CHANGE_LINE_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出操作
			history_file.close();
		}
		else
		{

		}
		if (is_output_key_file)//需要生成密钥文件
		{
			ofstream key_file(output_path + key_file_path, ios_base::out);//处理文本类型的密钥文件，使用覆盖方式打开
			key_file << FILE_KEY_WRITE_INFORMATION_1_1_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出相应内容。这里为密钥文件头部内容
			key_file << FILE_KEY_WRITE_INFORMATION_3_STRING << output_path << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出文件路径
			key_file << FILE_KEY_WRITE_INFORMATION_4_STRING << FILE_KEY_WRITE_INFORMATION_4_8_STRING << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;//输出加密类型
			key_file << FILE_KEY_WRITE_INFORMATION_6_1_STRING << ecc_public_key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			key_file << FILE_KEY_WRITE_INFORMATION_6_2_STRING << ecc_private_key_string << FILE_KEY_WRITE_INFORMATION_CHANGE_LINE_STRING;
			if (have_head_digit)//输出头部特征数字
			{
				QByteArray magic_number_transform(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//取得头部数字并将其转换回原始数据显示
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
		QByteArray public_key_bytearray((char*)ecc_public_key_string.c_str(), public_key_length);//转换为QByteArray
		public_key_bytearray = QByteArray::fromHex(public_key_bytearray);//转化为16进制编码
		memmove(public_key, public_key_bytearray.data(), public_key_length / 2);//直接复制内存。注意转换编码后长度会减少一半
		QByteArray private_key_bytearray((char*)ecc_private_key_string.c_str(), private_key_length);//转换为QByteArray
		private_key_bytearray = QByteArray::fromHex(private_key_bytearray);//转化为16进制编码
		memmove(private_key, private_key_bytearray.data(), private_key_length / 2);//直接复制内存。注意转换编码后长度会减少一半
		if (is_output_key_file_binary)//需要生成二进制密钥文件
		{

			//输出公钥文件
			ofstream public_key_file_binary(output_path + key_file_binary_path + FILE_PUBLIC_KEY_FILE_EXTRA_PATH_STRING, ios_base::binary | ios_base::out);//处理二进制类型的密钥文件，使用覆盖方式打开
			QByteArray magic_number = FILE_KEY_WRITE_BINARY_MAGIC_NUMBER_HEX_STRING;//等待加入的头部魔术数字
			QByteArray interval_number = FILE_KEY_WRITE_BINARY_INTERVAL_NUMBER_HEX_STRING;//二进制文件分隔符
			QByteArray interval_short_number = FILE_KEY_WRITE_BINARY_INTERVAL_SHORT_NUMBER_HEX_STRING;//二进制文件短分隔符
			magic_number = QByteArray::fromHex(magic_number);//转化为16进制编码
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			string magic_number_string(magic_number.constData(), magic_number.length());//QByteArray转string
			string interval_number_string(interval_number.constData(), interval_number.length());
			string interval_short_number_string(interval_short_number.constData(), interval_short_number.length());
			int type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_11_NUMBER;//加密类型
			int have_head_digit_0_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_0_NUMBER;//无头部特征数字标记
			int have_head_digit_1_number_digit = FILE_KEY_WRITE_BINARY_HAVE_HEAD_DIGIT_1_NUMBER;//有头部特征数字标记
			public_key_file_binary << magic_number_string;//写入头部魔术数字
			public_key_file_binary << interval_number_string;//写入分隔符
			public_key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//输出加密类型，按int型格式写入（4字节）
			public_key_file_binary << interval_number_string;//写入分隔符
			public_key_file_binary.write((char*)(&public_key_length), sizeof(public_key_length));//输出密钥长度，按int型格式写入（4字节）
			public_key_file_binary.write(public_key, public_key_length / 2);//写入密钥
			public_key_file_binary << interval_number_string;//写入分隔符
			if (have_head_digit)//写入头部特征数字信息
			{
				public_key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//输出有头部特征数字标记，按int型格式写入（4字节）
				public_key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//写入头部特征数字
			}
			else
			{
				public_key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//输出无头部特征数字标记，按int型格式写入（4字节）
				public_key_file_binary << interval_short_number_string;//写入相应位数的分隔符占位
			}
			public_key_file_binary << interval_number_string;//写入分隔符
			public_key_file_binary.close();

			//输出私钥文件
			ofstream private_key_file_binary(output_path + key_file_binary_path + FILE_PRIVATE_KEY_FILE_EXTRA_PATH_STRING, ios_base::binary | ios_base::out);//处理二进制类型的密钥文件，使用覆盖方式打开
			magic_number = QByteArray::fromHex(magic_number);//转化为16进制编码
			interval_number = QByteArray::fromHex(interval_number);
			interval_short_number = QByteArray::fromHex(interval_short_number);
			type_number_digit = FILE_KEY_WRITE_BINARY_TYPE_12_NUMBER;//加密类型
			private_key_file_binary << magic_number_string;//写入头部魔术数字
			private_key_file_binary << interval_number_string;//写入分隔符
			private_key_file_binary.write((char*)(&type_number_digit), sizeof(type_number_digit));//输出加密类型，按int型格式写入（4字节）
			private_key_file_binary << interval_number_string;//写入分隔符
			private_key_file_binary.write((char*)(&private_key_length), sizeof(private_key_length));//输出密钥长度，按int型格式写入（4字节）
			private_key_file_binary.write(private_key, private_key_length / 2);//写入密钥
			private_key_file_binary << interval_number_string;//写入分隔符
			if (have_head_digit)//写入头部特征数字信息
			{
				private_key_file_binary.write((char*)(&have_head_digit_1_number_digit), sizeof(have_head_digit_1_number_digit));//输出有头部特征数字标记，按int型格式写入（4字节）
				private_key_file_binary.write(head_digit, FILE_HEAD_NUMBER_SIZE_NUMBER);//写入头部特征数字
			}
			else
			{
				private_key_file_binary.write((char*)(&have_head_digit_0_number_digit), sizeof(have_head_digit_0_number_digit));//输出无头部特征数字标记，按int型格式写入（4字节）
				private_key_file_binary << interval_short_number_string;//写入相应位数的分隔符占位
			}
			private_key_file_binary << interval_number_string;//写入分隔符
			private_key_file_binary.close();
		}
		else
		{

		}
		emit set_key_ECC_final(public_key_length, private_key_length);//密钥生成完毕
		delete this;
	}
}

