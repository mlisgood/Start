#include "define.h"

//ȫ�ֱ�������
extern QString font_str = "";

int main(int argc, char *argv[])
{

	//���������ռ�
	using namespace rem;

	//���س���
	QApplication application(argc, argv);

	//�޸Ľ��̹���Ŀ¼Ϊexe�ļ��ľ���Ŀ¼������������λ�õ��øó���ʱ�����Ҽ��˵��򿪳������ע�������������ʱ���������Ŀ¼�йص���Դ��ȫ��ʧЧ
	QString path = QCoreApplication::applicationDirPath();
	QDir::setCurrent(path);

	srand((int)time(NULL));//�����������

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

	//�򵥷�ֹ����࿪ʵ��
	HANDLE hObject = ::CreateMutex(NULL, FALSE, _T("MUTEX_TOOLS"));//����������
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hObject);//����رջ�����
		Help dialog;//��Ϣ��ʾ��
		dialog.setWindowTitle(QObject::tr("�����ٴ�Ӵ����"));
		dialog.set_dialog_information_path(DIALOG_INFORMATION_OPEN_MORE_THAN_ONE_PATH_STRING);//��ʾ��Ϣ
		dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		return FALSE;
	}
	else
	{

	}

	//����������
	Tools window;
	window.show();
	return application.exec();
}
