#include "define.h"

//全局变量定义
extern QString font_str = "";

int main(int argc, char *argv[])
{

	//导入命名空间
	using namespace rem;

	//加载程序
	QApplication application(argc, argv);

	//修改进程工作目录为exe文件的绝对目录，否则在其他位置调用该程序时，如右键菜单打开程序或者注册表自启动程序时所有与相对目录有关的资源会全部失效
	QString path = QCoreApplication::applicationDirPath();
	QDir::setCurrent(path);

	srand((int)time(NULL));//生成随机种子

	//设置全局字体。同样需要在修改进程工作目录后使用，否则会无法加载字体，导致程序无法运行
	int font_id = QFontDatabase::addApplicationFont(FILE_FONT_PATH_STRING);//加载并修改程序的默认字体
	if (font_id != -1)
	{
		font_str = QFontDatabase::applicationFontFamilies(font_id).at(0);//得到的第一个元素就是需要的字体的family
		QFont app_font(font_str, FILE_FONT_DEFAULT_SIZE);//设置默认字体
		QApplication::setFont(app_font);
	}
	else//加载失败，使用软件设定好的默认字体
	{

	}

	//定义程序启动画面，之后将其删除
	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap(WINDOW_SPLASH_PICTURE_PATH_FRONT_STRING));//设置图片
	splash->show();//显示图片
	application.processEvents();
	DesktopOmake window;
	application.setQuitOnLastWindowClosed(true);//实现关闭主窗口时关闭所有程序

	//运行主窗口
	window.show();
	splash->finish(&window);//销毁登陆界面对象，释放内存并调出主界面
	delete splash;
	return application.exec();
}
