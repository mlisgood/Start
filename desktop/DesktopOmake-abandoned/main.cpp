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

	//��������������棬֮����ɾ��
	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap(WINDOW_SPLASH_PICTURE_PATH_FRONT_STRING));//����ͼƬ
	splash->show();//��ʾͼƬ
	application.processEvents();
	DesktopOmake window;
	application.setQuitOnLastWindowClosed(true);//ʵ�ֹر�������ʱ�ر����г���

	//����������
	window.show();
	splash->finish(&window);//���ٵ�½��������ͷ��ڴ沢����������
	delete splash;
	return application.exec();
}
