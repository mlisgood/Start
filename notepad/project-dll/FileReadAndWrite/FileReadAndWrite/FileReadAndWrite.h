#pragma once

#include <QtCore/qglobal.h>
#include <QFile>
#include <QTextStream>
#include <QDataStream>

#define FILE_BIT_TO_KBIT 1024//Bת��ΪKB�ı���

QString file_read_text(QTextStream *file_textstream, int once_index);//��ȡ�ı��ļ��������ַ�����ÿ����һ�Σ��ͷ���һ���ַ���������Ϊ�ļ���������һ�δ�����С�����С�ĵ�λΪK�ַ���1K=1024��
void file_write_text(QTextStream *file_textstream, QString file_output);//����ı��ļ������ָ���ļ����е����ݡ�����Ϊ�ļ����������Ҫ���������
QString file_read_binary(QDataStream *file_datastream, int once_index, bool string_addspace);//��ȡ�������ļ��������ַ�����ÿ����һ�Σ��ͷ���һ���ַ���������Ϊ��������������һ�δ�����С���Ƿ���ӿո񡣿��С�ĵ�λΪ�ֽ�
void file_write_binary(QDataStream *file_datastream, QString file_output);//�洢�������ļ������ָ���ļ����е����ݡ�����Ϊ����������������Ҫ���������