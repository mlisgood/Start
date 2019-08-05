#include "FileReadAndWrite.h"

QString file_read_text(QTextStream *file_textstream, int once_index)//��ȡ�ı��ļ��������ַ�����ÿ����һ�Σ��ͷ���һ���ַ���������Ϊ�ļ���������һ�δ�����С����Ҫ��������ݡ����С�ĵ�λΪK�ַ���1K=1024��
{	
	QString return_string;//�������ַ���
	return_string = file_textstream->read(once_index*FILE_BIT_TO_KBIT);//��ȡָ����Ŀ�ַ�
	return return_string;
}

void file_write_text(QTextStream *file_textstream, QString file_output)//����ı��ļ������ָ���ļ����е����ݡ�����Ϊ�ļ����������Ҫ���������
{
	(*file_textstream) << file_output;//�������
	(*file_textstream).flush();
}

QString file_read_binary(QDataStream *file_datastream, int once_index, bool string_addspace)//��ȡ�������ļ��������ַ�����ÿ����һ�Σ��ͷ���һ���ַ���������Ϊ��������������һ�δ�����С���Ƿ���ӿո񡣿��С�ĵ�λΪ�ֽ�
{
	char *file_hex_data = new char[once_index];//�洢���������
	(*file_datastream).readRawData(file_hex_data, once_index);//��ȡԭʼ����
	QByteArray file_hex_data_transform(file_hex_data, once_index);//char*תQByteArray��ע�����ָ�����ȣ�������ں�����һЩ��������
	delete file_hex_data;//�ͷ��ڴ�
	QString file_hex_data_transform_final = file_hex_data_transform.toHex();//QByteArrayת��Ϊ���������ݣ�Ȼ��תQString
	if (string_addspace)
	{
		for (int count = once_index * 2; count > 0; count -= 2)//ÿ�������ַ�����һ���ո���Ϊ2���������ַ�����1���ֽڣ�������Ҫ����2��ע����뵹����룬������Ϊ�ַ���λ�������ո�仯�����仯����ɴ������ѡ������ַ����±��0��ʼ�������ַ���λ���Ǵ������ַ���λ�����ڵ����
		{
			file_hex_data_transform_final.insert(count, " ");
		}
	}
	else
	{

	}
	file_hex_data_transform_final = file_hex_data_transform_final.toUpper();//ת��Ϊ��д
	return file_hex_data_transform_final;
}

void file_write_binary(QDataStream *file_datastream, QString file_output)//�洢�������ļ������ָ���ļ����е����ݡ�����Ϊ����������������Ҫ��������ݺ��Ƿ���ӿո�
{
	for (long long count = file_output.length() - 1; count >= 0; count--)//��Ϊɾ���ַ����ַ�˳��ᷢ���仯���ʲ��õ�����
	{
		if (file_output.at(count) >= 'A'&&file_output.at(count) <= 'F'||file_output.at(count) >= 'a'&&file_output.at(count) <= 'f'||file_output.at(count) >= '0'&&file_output.at(count) <= '9')
		{

		}
		else//ȥ���Ƿ��ַ�
		{
			file_output.remove(count, 1);
		}
	}
	if (file_output.length() % 2 == 1)//�������Ϊ�������ͽ����һ���ַ��ص�����ΪQT��fromHex��������������»�ص���1���ַ������������ص���Ϣƫ��
	{
		file_output.remove(file_output.length() - 1, 1);
	}
	else
	{

	}
	QByteArray file_output_bytearray(file_output.toLatin1(), file_output.length());//����Latin1��ʽת����ʵ�ʴ�������붼֧��Ascii��ע��QByteArray��ʼ�����ָ�����ȣ�����ĩβ���ܻ�����������
	file_output_bytearray = QByteArray::fromHex(file_output_bytearray);//������ת��Ϊ������ԭʼֵ
	char *file_output_data;
	file_output_data = file_output_bytearray.data();//QByteArrayתchar*�������ǰ�QByteArray�����ݸ��Ƶ���char*ָ��ָ��ĵ�ַ��ʼ��λ�ã�������ﲻ�ܸ�char*ָ�����붯̬���飬����ᷢ��deleteʱջ�𻵵�����
	(*file_datastream).writeRawData(file_output_data, file_output_bytearray.length());//������д���ļ�
}