#pragma once

#include <QtCore/qglobal.h>
#include <QFile>
#include <QTextStream>
#include <QDataStream>

#define FILE_BIT_TO_KBIT 1024//B转化为KB的倍率

QString file_read_text(QTextStream *file_textstream, int once_index);//读取文本文件。输入字符串，每输入一次，就返回一次字符串。参数为文件输入流和一次处理块大小，块大小的单位为K字符（1K=1024）
void file_write_text(QTextStream *file_textstream, QString file_output);//输出文本文件。输出指定文件流中的内容。参数为文件输出流和需要输出的内容
QString file_read_binary(QDataStream *file_datastream, int once_index, bool string_addspace);//读取二进制文件。输入字符串，每输入一次，就返回一次字符串。参数为二进制输入流，一次处理块大小和是否添加空格。块大小的单位为字节
void file_write_binary(QDataStream *file_datastream, QString file_output);//存储二进制文件。输出指定文件流中的内容。参数为二进制输入流和需要输出的内容