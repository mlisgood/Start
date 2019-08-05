#include "define.h"

//ȫ�ֱ�������
extern QString font_str = "";

int main(int argc, char *argv[])
{
	using namespace rem;//���������ռ�

	QApplication application(argc, argv);//�½�������

	srand((int)time(NULL));//�����������

	//�޸Ľ��̹���Ŀ¼Ϊexe�ļ��ľ���Ŀ¼�������ڲ�ʹ�ó��淽���򿪳������Ҽ��˵��򿪳����������������øó���ʱ���������Ŀ¼�йص���Դ��ȫ��ʧЧ
	QString path = QCoreApplication::applicationDirPath();
	QDir::setCurrent(path);

	//�򵥷�ֹ����࿪ʵ��
	HANDLE hObject = ::CreateMutex(NULL, FALSE, _T("MUTEX_START"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hObject);
		Filemissing dialog;//��Ϣ��ʾ��
		dialog.setWindowTitle(QObject::tr("�����ٴ�Ӵ����"));
		dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_3_FLAG);//ʹ��״̬3
		dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		return FALSE;
	}
	else
	{

	}

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
	Start window;
	window.show();
	return application.exec();
}