#include "define.h"

//ȫ�ֱ�������
extern QString font_str="";

int main(int argc, char *argv[])//������������ʾ����Ĳ��������Ͳ���������������ļ�·��Ϊargv[0]����������������Ҫע�����Ϣ����ϣ����Եõ�Ŀ���ļ�·��argv[1]���Ӷ�ʵ���Ҽ��˵������������򿪵ȹ���
{

	//���������ռ�
	using namespace rem;
	using std::string;
	using std::wstring;

	QApplication application(argc, argv);//�½�������

	srand((int)time(NULL));//�����������

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

	//��������������棬֮����ɾ��
	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap(WINDOW_SPLASH_PICTURE_PATH_FRONT_STRING));//����ͼƬ
	splash->show();//��ʾͼƬ
	application.processEvents();
	Notepad mainwindow;//���������

	if (argc > 1)//������Ŀ����1��ʾ����ʹ�ó��淽���򿪳���ģ�����ʹ���Ҽ��˵��ȷ�ʽ����ʱ�ĵڶ��������Ǳ��򿪵��ļ�����Ҫ��ע���д����Ӧ��Ϣ
	{
		mainwindow.set_args_string(argv[1]);//������ڲ���
		string path_transform = argv[1];//�ַ���ת��
		QString path_transform_final = QString(QString::fromLocal8Bit(path_transform.c_str()));
		mainwindow.set_current_path(path_transform_final);//�����ļ����뱣�洰���ڴ��ִ򿪷�ʽ��ʹ�õĳ�ʼ·��
	}
	else
	{
		mainwindow.set_current_path(QObject::tr(""));//����ǳ��淽ʽ����ôĬ�ϵ��ļ����뱣�洰�ڵ�·��Ϊ��
	}
	mainwindow.show();
	splash->finish(&mainwindow);//���ٵ�½��������ͷ��ڴ沢����������
	delete splash;
	application.setQuitOnLastWindowClosed(true);//ʵ�ֹر�������ʱ�ر����г���
	
	return application.exec();
}