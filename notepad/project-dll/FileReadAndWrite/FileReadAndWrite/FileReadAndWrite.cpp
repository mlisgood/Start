#include "FileReadAndWrite.h"

QString file_read_text(QTextStream *file_textstream, int once_index)//读取文本文件。输入字符串，每输入一次，就返回一次字符串。参数为文件输入流、一次处理块大小和需要输出的内容。块大小的单位为K字符（1K=1024）
{	
	QString return_string;//待返回字符串
	return_string = file_textstream->read(once_index*FILE_BIT_TO_KBIT);//读取指定数目字符
	return return_string;
}

void file_write_text(QTextStream *file_textstream, QString file_output)//输出文本文件。输出指定文件流中的内容。参数为文件输出流和需要输出的内容
{
	(*file_textstream) << file_output;//输出内容
	(*file_textstream).flush();
}

QString file_read_binary(QDataStream *file_datastream, int once_index, bool string_addspace)//读取二进制文件。输入字符串，每输入一次，就返回一次字符串。参数为二进制输入流，一次处理块大小和是否添加空格。块大小的单位为字节
{
	char *file_hex_data = new char[once_index];//存储读入的数据
	(*file_datastream).readRawData(file_hex_data, once_index);//读取原始数据
	QByteArray file_hex_data_transform(file_hex_data, once_index);//char*转QByteArray。注意必须指明长度，否则会在后面多出一些垃圾数据
	delete file_hex_data;//释放内存
	QString file_hex_data_transform_final = file_hex_data_transform.toHex();//QByteArray转化为二进制数据，然后转QString
	if (string_addspace)
	{
		for (int count = once_index * 2; count > 0; count -= 2)//每隔两个字符插入一个空格。因为2个二进制字符代表1个字节，故总数要乘以2。注意必须倒序插入，否则因为字符的位置随插入空格变化发生变化会造成处理困难。还有字符串下标从0开始，插入字符的位置是待插入字符的位置所在的序号
		{
			file_hex_data_transform_final.insert(count, " ");
		}
	}
	else
	{

	}
	file_hex_data_transform_final = file_hex_data_transform_final.toUpper();//转化为大写
	return file_hex_data_transform_final;
}

void file_write_binary(QDataStream *file_datastream, QString file_output)//存储二进制文件。输出指定文件流中的内容。参数为二进制输入流，需要输出的内容和是否添加空格
{
	for (long long count = file_output.length() - 1; count >= 0; count--)//因为删除字符后字符顺序会发生变化，故采用倒序处理
	{
		if (file_output.at(count) >= 'A'&&file_output.at(count) <= 'F'||file_output.at(count) >= 'a'&&file_output.at(count) <= 'f'||file_output.at(count) >= '0'&&file_output.at(count) <= '9')
		{

		}
		else//去除非法字符
		{
			file_output.remove(count, 1);
		}
	}
	if (file_output.length() % 2 == 1)//如果长度为奇数，就将最后一个字符截掉，因为QT的fromHex方法在这种情况下会截掉第1个字符，这会造成严重的信息偏差
	{
		file_output.remove(file_output.length() - 1, 1);
	}
	else
	{

	}
	QByteArray file_output_bytearray(file_output.toLatin1(), file_output.length());//按照Latin1格式转换，实际大多数编码都支持Ascii。注意QByteArray初始化最好指明长度，否则末尾可能会有垃圾数据
	file_output_bytearray = QByteArray::fromHex(file_output_bytearray);//将数据转化为二进制原始值
	char *file_output_data;
	file_output_data = file_output_bytearray.data();//QByteArray转char*。这里是把QByteArray的内容复制到以char*指针指向的地址开始的位置，因此这里不能给char*指针申请动态数组，否则会发生delete时栈损坏的问题
	(*file_datastream).writeRawData(file_output_data, file_output_bytearray.length());//将数据写入文件
}