#include "define.h"

//全局变量定义
extern QString font_str="";

int main(int argc, char *argv[])//这两个参数表示传入的参数数量和参数，程序自身的文件路径为argv[0]，数组后面的内容需要注册表信息的配合，可以得到目标文件路径argv[1]，从而实现右键菜单打开与关联程序打开等功能
{

	//导入命名空间
	using namespace rem;
	using std::string;
	using std::wstring;

	QApplication application(argc, argv);//新建主对象

	srand((int)time(NULL));//生成随机种子

	//修改进程工作目录为exe文件的绝对目录，否则在不使用常规方法打开程序，如右键菜单打开程序或者其他程序调用该程序时所有与相对目录有关的资源会全部失效
	QString path = QCoreApplication::applicationDirPath();
	QDir::setCurrent(path);

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
	Notepad mainwindow;//主界面对象

	if (argc > 1)//参数数目大于1表示不是使用常规方法打开程序的，而是使用右键菜单等方式。此时的第二个参数是被打开的文件，需要向注册表写入相应信息
	{
		mainwindow.set_args_string(argv[1]);//传入入口参数
		string path_transform = argv[1];//字符串转换
		QString path_transform_final = QString(QString::fromLocal8Bit(path_transform.c_str()));
		mainwindow.set_current_path(path_transform_final);//传入文件打开与保存窗口在此种打开方式下使用的初始路径
	}
	else
	{
		mainwindow.set_current_path(QObject::tr(""));//如果是常规方式，那么默认的文件打开与保存窗口的路径为空
	}
	mainwindow.show();
	splash->finish(&mainwindow);//销毁登陆界面对象，释放内存并调出主界面
	delete splash;
	application.setQuitOnLastWindowClosed(true);//实现关闭主窗口时关闭所有程序
	
	return application.exec();
}