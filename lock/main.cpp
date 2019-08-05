#include "define.h"

//全局变量定义
extern QString font_str = "";

int main(int argc, char *argv[])
{

	using namespace rem;

	srand((int)time(NULL));//生成随机种子

	//新建主对象
	QApplication application(argc, argv);

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

	//运行主程序
	Lock window;
	window.show();
	return application.exec();
}
