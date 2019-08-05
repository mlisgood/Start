#include "define.h"

//ȫ�ֱ�������
extern QString font_str = "";

int main(int argc, char *argv[])
{

	using namespace rem;

	srand((int)time(NULL));//�����������

	//�½�������
	QApplication application(argc, argv);

	//�޸Ľ��̹���Ŀ¼Ϊexe�ļ��ľ���Ŀ¼�������ڲ�ʹ�ó��淽���򿪳������Ҽ��˵��򿪳����������������øó���ʱ���������Ŀ¼�йص���Դ��ȫ��ʧЧ
	QString path = QCoreApplication::applicationDirPath();
	QDir::setCurrent(path);

	//����ȫ�����塣ͬ����Ҫ���޸Ľ��̹���Ŀ¼��ʹ�ã�������޷��������壬���³����޷�����
	int font_id = QFontDatabase::addApplicationFont(FILE_FONT_PATH_STRING);//���ز��޸ĳ����Ĭ������
	if (font_id != -1)
	{
		font_str = QFontDatabase::applicationFontFamilies(font_id).at(0);//�õ��ĵ�һ��Ԫ�ؾ�����Ҫ�������family
		QFont app_font(font_str, FILE_FONT_DEFAULT_SIZE);//����Ĭ������
		QApplication::setFont(app_font);
	}
	else//����ʧ�ܣ�ʹ������趨�õ�Ĭ������
	{

	}

	//����������
	Lock window;
	window.show();
	return application.exec();
}
