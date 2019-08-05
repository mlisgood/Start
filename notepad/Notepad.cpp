#include "define.h"

namespace rem
{

	//全局变量定义
	extern int find_dialog_mutex = 1;//只允许创建1个查找窗口。注意使用全局变量时，不管是声明还是定义都不需要在头文件中，并且需要用extern。全局变量只能定义1次，也就是赋初值1次，但需要用到其的文件中均需声明。

	//使用标准命名空间
	using std::string;
	using std::ifstream;
	using std::ofstream;
	using std::fstream;
	using std::ios_base;

	//构造与析构函数
	Notepad::Notepad(QWidget *parent) : QMainWindow(parent)
	{

		//常规初始化
		//以下功能用到了常量，如要修改最好重写
		randnumber = WINDOW_RANDOM_MIN_NUMBER + rand() % (WINDOW_RANDOM_MAX_NUMBER - WINDOW_RANDOM_MIN_NUMBER + 1);//产生指定随机数。仅在构造函数中使用一次，以保证不会出现隐藏并打开窗口后背景因为重新绘图发生变化的问题
		setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);//去掉窗口标题栏并且窗口可以通过点击任务栏放大缩小
		resize(WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_QuitOnClose, true);//该窗口为主窗口，关闭时直接退出程序
		hex_status = WINDOW_TOOL_TOHEX_STATUS_NO_FLAG;//默认不是十六进制模式
		if (randnumber >= 1 && randnumber <= 5)//决定人物图像以及相关文字颜色
		{
			chara_randnumber = 1 + rand() % (5 - 1 + 1);
			font_randnumber = 1;
		}
		else if (randnumber >= 6 && randnumber <= 10)
		{
			chara_randnumber = 6 + rand() % (10 - 6 + 1);
			font_randnumber = 2;
		}
		else if (randnumber >= 11 && randnumber <= 15)
		{
			chara_randnumber = 11 + rand() % (15 - 11 + 1);
			font_randnumber = 3;
		}
		else if (randnumber >= 16 && randnumber <= 20)
		{
			chara_randnumber = 16 + rand() % (20 - 16 + 1);
			font_randnumber = 4;
		}
		else if (randnumber >= 21 && randnumber <= 25)
		{
			chara_randnumber = 21 + rand() % (25 - 21 + 1);
			font_randnumber = 5;
		}
		else
		{

		}

		//初始化计时器
		chara_picture_timer = new QTimer(this);//创建一个定时器
		chara_picture_timer->setTimerType(Qt::PreciseTimer);//修改精度
		connect(chara_picture_timer, SIGNAL(timeout()), this, SLOT(timer_chara_picture_timeout()));//计时器到期处理
		timer_interval_number = WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER + rand() % (WINDOW_RANDOM_TIMER_CHARA_NORMAL_MAX_NUMBER - WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER + 1);//初始化计时间隔，取值在之前选取的区间当中
		timer_chara_status = WINDOW_CHARA_NORMAL_FLAG;//初始化状态为常规状态
		timer_chara_status_address = &timer_chara_status;//设置计时器状态地址
		chara_picture_timer->start(timer_interval_number);//初始化计时器

		//初始化人物图像
		//以下功能用到了常量，如要修改最好重写
		chara_path_normal = WINDOW_CHARA_PICTURE_PATH_FRONT_STRING;//人物形象常规状态
		chara_path_normal += QString::number(chara_randnumber, 10);//将随机数转化为路径中的一部分
		chara_path_normal += WINDOW_CHARA_PICTURE_PATH_BREAK_STRING;
		chara_path_close_eye = chara_path_normal;//需要切换的图片（人物眼睛闭上的状态）前半部分路径和常规状态的一样
		chara_path_normal += tr("01");
		chara_path_close_eye += tr("02");
		chara_path_normal += WINDOW_CHARA_PICTURE_PATH_BACK_STRING;
		chara_path_close_eye += WINDOW_CHARA_PICTURE_PATH_BACK_STRING;
		chara_picture_label = new QLabel(this);//人物形象必须比左侧边界先绘制，否则其会覆盖左侧边界
		margin_picture_label = new QLabel(this);
		chara_picture_label->setGeometry(0, 0, WINDOW_SIZE_PICTURE_CHARA_WIDTH_NUMBER, WINDOW_SIZE_PICTURE_CHARA_HEIGHT_NUMBER);//设置label的边界
		margin_picture_label->setGeometry(0, 0, WINDOW_SIZE_MARGIN_PICTURE_LEFT_WIDTH_NUMBER, WINDOW_SIZE_MARGIN_PICTURE_LEFT_HEIGHT_NUMBER);
		chara_picture.load(chara_path_normal);//加载人物图片，采用先加载，之后每次使用而不重新加载的方法以提高效率
		chara_picture_extra.load(chara_path_close_eye);//加载人物特殊状态图片
		if (timer_chara_status == WINDOW_CHARA_NORMAL_FLAG)//通过人物状态的判断来映射到指定图片上面
		{
			chara_picture_label->setPixmap(chara_picture);
		}
		else if (timer_chara_status == WINDOW_CHARA_SPECIAL_FLAG)
		{
			chara_picture_label->setPixmap(chara_picture_extra);
		}
		else
		{
			chara_picture_label->setPixmap(chara_picture);
		}
		margin_picture.load((QString)WINDOW_MARGIN_PICTURE_LEFT_PATH_STRING);
		margin_picture_label->setPixmap(margin_picture);//左侧边界

		//加载界面，必须放在最后以避免界面被之后的绘图覆盖
		ui.setupUi(this);

		//去除文本框背景。鉴于直接设置会导致文字超过一页出现滚动条后，背景跟随滚动条滚动成为平铺样式，故去掉文本框背景和边界，改为绘制背景
		ui.textEdit_main->setStyleSheet("background-color: rgb(255, 255, 255, 0);border:0px solid #e1e0e0;");

		//功能实现
		connect(ui.textEdit_main, SIGNAL(cursorPositionChanged()), this, SLOT(text_line_and_col()));//文本框鼠标行数和列数的获取
		connect(ui.textEdit_main, SIGNAL(textChanged()), this, SLOT(set_not_save_status()));//设置未保存标记
		connect(ui.pushButton_close_windows, SIGNAL(clicked()), this, SLOT(close_dialog()));//关闭窗口按钮
		connect(ui.pushButton_tool_06, SIGNAL(clicked()), this, SLOT(textedit_copy()));//复制
		connect(ui.pushButton_tool_07, SIGNAL(clicked()), this, SLOT(textedit_paste()));//粘贴
		connect(ui.pushButton_tool_08, SIGNAL(clicked()), this, SLOT(textedit_cut()));//剪切
		connect(ui.pushButton_tool_09, SIGNAL(clicked()), this, SLOT(textedit_undo()));//撤销
		connect(ui.pushButton_tool_10, SIGNAL(clicked()), this, SLOT(textedit_redo()));//重做
		connect(ui.pushButton_tool_13, SIGNAL(clicked()), this, SLOT(textedit_font()));//字体
		connect(ui.pushButton_tool_14, SIGNAL(clicked()), this, SLOT(textedit_color()));//颜色
		connect(ui.pushButton_tool_18, SIGNAL(clicked()), this, SLOT(textedit_help()));//程序信息
		connect(ui.pushButton_tool_01, SIGNAL(clicked()), this, SLOT(textedit_new()));//新建
		connect(ui.pushButton_tool_02, SIGNAL(clicked()), this, SLOT(textedit_open()));//打开
		connect(ui.pushButton_tool_03, SIGNAL(clicked()), this, SLOT(textedit_save()));//保存
		connect(ui.pushButton_tool_04, SIGNAL(clicked()), this, SLOT(textedit_saveas()));//另存为
		connect(ui.pushButton_tool_11, SIGNAL(clicked()), this, SLOT(textedit_find()));//查找
		connect(ui.pushButton_tool_12, SIGNAL(clicked()), this, SLOT(textedit_replace()));//替换
		connect(ui.pushButton_tool_05, SIGNAL(clicked()), this, SLOT(textedit_tohex()));//十六进制转换
		connect(ui.pushButton_tool_15, SIGNAL(clicked()), this, SLOT(textedit_code()));//编码转换
		connect(ui.pushButton_tool_16, SIGNAL(clicked()), this, SLOT(textedit_print()));//打印
		connect(ui.pushButton_tool_17, SIGNAL(clicked()), this, SLOT(textedit_setting()));//设置

		//初始化显示
		ui.label_filestatus->setText(tr("行:1  列:0"));//行列数显示
		ui.label_filename->setText(tr("未命名"));//文件名显示
		ui.label_savestatus->setText(tr("已保存"));//保存状态显示
		QPalette label_palette;
		QPalette text_palette;
		if (randnumber >= 1 && randnumber <= 5)//决定人物图像以及相关文字颜色，label使用WindowText，其余的使用Text，文本编辑还需要使用Highlight
		{
			label_palette.setColor(QPalette::WindowText, QColor(255, 83, 185, 255));
			label_palette.setColor(QPalette::HighlightedText, QColor(255, 83, 185, 255));
			label_palette.setColor(QPalette::Highlight, QColor(255, 83, 185, 64));
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #FF53B9;background-color: #00FFFFFF;text-align:center;color:#FF53B9;}QProgressBar::chunk{background-color:#FF53B9;}");
		}
		else if (randnumber >= 6 && randnumber <= 10)
		{
			label_palette.setColor(QPalette::WindowText, QColor(133, 153, 212, 255));
			label_palette.setColor(QPalette::HighlightedText, QColor(133, 153, 212, 255));
			label_palette.setColor(QPalette::Highlight, QColor(133, 153, 212, 64));
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #8599D4;background-color: #00FFFFFF;text-align:center;color:#8599D4;}QProgressBar::chunk{background-color:#8599D4;}");
		}
		else if (randnumber >= 11 && randnumber <= 15)
		{
			label_palette.setColor(QPalette::WindowText, QColor(222, 63, 235, 255));
			label_palette.setColor(QPalette::HighlightedText, QColor(222, 63, 235, 255));
			label_palette.setColor(QPalette::Highlight, QColor(222, 63, 235, 64));
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #DE3FEB;background-color: #00FFFFFF;text-align:center;color:#DE3FEB;}QProgressBar::chunk{background-color:#DE3FEB;}");
		}
		else if (randnumber >= 16 && randnumber <= 20)
		{
			label_palette.setColor(QPalette::WindowText, QColor(242, 153, 93, 255));
			label_palette.setColor(QPalette::HighlightedText, QColor(242, 153, 93, 255));
			label_palette.setColor(QPalette::Highlight, QColor(242, 153, 93, 64));
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #F2995D;background-color: #00FFFFFF;text-align:center;color:#F2995D;}QProgressBar::chunk{background-color:#F2995D;}");
		}
		else if (randnumber >= 21 && randnumber <= 25)
		{
			label_palette.setColor(QPalette::WindowText, QColor(71, 185, 78, 255));
			label_palette.setColor(QPalette::HighlightedText, QColor(71, 185, 78, 255));
			label_palette.setColor(QPalette::Highlight, QColor(71, 185, 78, 64));
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #47B94E;background-color: #00FFFFFF;text-align:center;color:#47B94E;}QProgressBar::chunk{background-color:#47B94E;}");
		}
		else
		{

		}
		ui.label_filename->setPalette(label_palette);
		ui.label_filestatus->setPalette(label_palette);
		ui.label_code->setPalette(label_palette);
		ui.label_savestatus->setPalette(label_palette);
		ui.label_file_read_advance->setPalette(label_palette);

		//进度条初始化
		ui.progressBar->setVisible(false);//进度条初始不可见
		ui.label_file_read_advance->setText(tr("正在获取文件信息……"));//进度条初始文本
		ui.label_file_read_advance->setVisible(false);//进度提示初始不可见
		progress_bar_change_color = false;//进度条字体未切换颜色

		//初始化配置文件信息
		setting_file_read();

		//禁用富文本
		ui.textEdit_main->setAcceptRichText(false);

		//去掉关联性控件的右键菜单
		ui.textEdit_main->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
		ui.textEdit_main->horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);

		//拖拽事件初始化
		ui.textEdit_main->setAcceptDrops(false);//禁用textEdit控件默认的放下操作
		setAcceptDrops(true);//启用全局的放下操作

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}
	Notepad::~Notepad()
	{
		delete chara_picture_timer;
		delete chara_picture_label;
		delete margin_picture_label;
	}

	//初始设置
	void Notepad::setting_file_read()//设置文件读取
	{
		setting_file_font_read();//字体
		ifstream setting_file_color;//颜色
		QString file_color_input = FILE_COLOR_OUTPUT_FILE_PATH_FRONT_STRING;
		file_color_input += QString::number(font_randnumber, 10);
		file_color_input += FILE_COLOR_OUTPUT_FILE_PATH_BACK_STRING;
		string file_color_input_final = string((const char *)file_color_input.toLocal8Bit());
		setting_file_color.open(file_color_input_final, ios_base::in);//打开文件
		if (!setting_file_color.is_open())//打开文件失败
		{
			QPalette text_palette;//字体着色
			text_palette.setColor(QPalette::Text, QColor(0, 0, 0, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(0, 0, 0, 255));
			text_palette.setColor(QPalette::Highlight, QColor(0, 0, 0, 64));
			ui.textEdit_main->setPalette(text_palette);
		}
		else
		{
			int setting_color[3];//初始化设置
			string temp;//临时存储读入的字符串
			setting_file_color >> temp;//红
			setting_color[0] = atoi(temp.c_str());
			setting_file_color >> temp;//绿
			setting_color[1] = atoi(temp.c_str());
			setting_file_color >> temp;//蓝
			setting_color[2] = atoi(temp.c_str());
			QPalette text_palette;//字体着色
			text_palette.setColor(QPalette::Text, QColor(setting_color[0], setting_color[1], setting_color[2], 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(setting_color[0], setting_color[1], setting_color[2], 255));
			text_palette.setColor(QPalette::Highlight, QColor(setting_color[0], setting_color[1], setting_color[2], 64));
			ui.textEdit_main->setPalette(text_palette);
			setting_file_color.close();
		}
		ifstream setting_file_code;//编码
		setting_file_code.open(FILE_CODE_OUTPUT_FILE_PATH_STRING, ios_base::in);//打开文件
		if (!setting_file_code.is_open())//打开文件失败
		{
			code_undefine = tr("UTF-8");//这里不能使用临时变量，否则等到该函数运行完毕，临时变量会被释放，指针会指向空地址，从而出错
		}
		else
		{
			string information_code_temp;
			setting_file_code >> information_code_temp;//读取文件内容
			code_undefine = QString(QString::fromLocal8Bit(information_code_temp.c_str()));
			setting_file_code.close();
		}
		text_code = &code_undefine;
		ui.label_code->setText(*text_code);
		ifstream setting_text_file;//其他设置，因为此函数在构造函数里面，比右键菜单打开处理的函数set_args_string运行时间要早，故在此处读取文件
		ifstream setting_binary_file;
		setting_text_file.open(FILE_SETTING_TEXT_OUTPUT_FILE_PATH_STRING, ios_base::in);//打开文件
		setting_binary_file.open(FILE_SETTING_BINARY_OUTPUT_FILE_PATH_STRING, ios_base::in);
		if (!setting_text_file.is_open())//打开文件失败
		{
			setting_text << tr("txt") << tr("ini") << tr("inf") << tr("bat") << tr("reg");//默认值
			setting_binary << tr("exe") << tr("dll");
		}
		else
		{
			string temp_string;//临时字符串
			for (int maxsize = 0; maxsize < 100; maxsize++)
			{
				setting_text_file >> temp_string;
				if (temp_string != ""&&temp_string != FILE_SETTING_TEXT_AND_BINARY_END_WRITE_STRING)//读取的字符串不为空或结尾标志
				{
					setting_text << QString(QString::fromLocal8Bit(temp_string.c_str()));
				}
				else
				{
					break;
				}
			}
			for (int maxsize = 0; maxsize < 100; maxsize++)
			{
				setting_binary_file >> temp_string;
				if (temp_string != ""&&temp_string != FILE_SETTING_TEXT_AND_BINARY_END_WRITE_STRING)//读取的字符串不为空或结尾标志
				{
					setting_binary << QString(QString::fromLocal8Bit(temp_string.c_str()));
				}
				else
				{
					break;
				}
			}
			setting_text_file.close();//关闭文件
			setting_binary_file.close();
		}
		setting_text_address = &setting_text;//获得地址
		setting_binary_address = &setting_binary;
		QSettings *setting_other_file = new QSettings(FILE_SETTING_OTHER_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		setting_default_open_method = (setting_other_file->value(FILE_SETTING_CATALOG_1_INNER_PATH_STRING)).toString();
		if (setting_default_open_method != tr("文本方式") && setting_default_open_method != tr("二进制方式"))
		{
			setting_default_open_method = tr("文本方式");
		}
		else
		{

		}
		setting_default_open_method_address = &setting_default_open_method;
		setting_size[0] = (setting_other_file->value(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING)).toInt();
		setting_size[1] = (setting_other_file->value(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING)).toInt();
		if (setting_size[0]<DIALOG_SETTING_MIN_TEXT_SIZE_NUMBER || setting_size[0]>DIALOG_SETTING_MAX_TEXT_SIZE_NUMBER)//spinbox超出范围设定，即读取失败
		{
			setting_size[0] = DIALOG_SETTING_MIN_TEXT_SIZE_NUMBER;
		}
		else
		{

		}
		if (setting_size[1]<DIALOG_SETTING_MIN_BINARY_SIZE_NUMBER || setting_size[1]>DIALOG_SETTING_MAX_BINARY_SIZE_NUMBER)
		{
			setting_size[0] = DIALOG_SETTING_MIN_BINARY_SIZE_NUMBER;
		}
		else
		{

		}
		setting_size_address[0] = &setting_size[0];
		setting_size_address[1] = &setting_size[1];
		setting_bool_value[0] = (setting_other_file->value(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING)).toBool();//读取失败时，会根据初始值进行强制转换，不是0就是1，因此不需要另行处理
		setting_bool_value[1] = (setting_other_file->value(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING)).toBool();
		setting_bool_value[2] = (setting_other_file->value(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING)).toBool();
		setting_bool_value_address[0] = &setting_bool_value[0];
		setting_bool_value_address[1] = &setting_bool_value[1];
		setting_bool_value_address[2] = &setting_bool_value[2];
		if (*setting_bool_value_address[0] == true)
		{
			ui.textEdit_main->setLineWrapMode(QTextEdit::WidgetWidth);//允许在窗口部件的当前宽度自动换行
		}
		else
		{
			ui.textEdit_main->setLineWrapMode(QTextEdit::NoWrap);//禁止自动换行
		}
		delete setting_other_file;
		QSettings *regedit_settings_1 = new QSettings(REG_MENU_1, QSettings::NativeFormat);//写入注册表
		QSettings *regedit_settings_2 = new QSettings(REG_MENU_2, QSettings::NativeFormat);
		if (*setting_bool_value_address[1] == true)//是否关联右键菜单。这里用到了大量常量，如需修改，请修改此处
		{
			QString reg_path = "\"" + QApplication::applicationFilePath();//获得绝对路径，注意applicationDirPath只获取路径，applicationFilePath还会包括程序文件名
			reg_path += "\" \"%1\"";
			regedit_settings_1->setValue(".", reg_path.replace("/", "\\"));//写入注册表项，注意注册表使用的路径分隔符和QT输出的相反。默认值用一个点表示
			regedit_settings_2->setValue(".", REG_MENU_NAME_PATH_STRING);
			reg_path = QApplication::applicationDirPath() + REG_MENU_ICON_PATH_STRING;
			regedit_settings_2->setValue(tr("icon"), reg_path.replace("/", "\\"));
			delete regedit_settings_1;
			delete regedit_settings_2;
		}
		else
		{
			regedit_settings_1->clear();//清除注册表项
			regedit_settings_2->clear();
			delete regedit_settings_1;
			delete regedit_settings_2;
		}
	}

	void Notepad::setting_file_font_read()//字体设置文件读取，因为字体文件在之后也会用到，因此单独做成一个函数
	{
		ifstream setting_file;
		QString file_font_input = FILE_FONT_OUTPUT_FILE_PATH_FRONT_STRING;
		file_font_input += QString::number(font_randnumber, 10);
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_YES_FLAG)//二进制模式下需要读取另外的字体文件
		{
			file_font_input += FILE_FONT_OUTPUT_FILE_PATH_BINARY_EXTRA_STRING;
		}
		else
		{

		}
		file_font_input += FILE_FONT_OUTPUT_FILE_PATH_BACK_STRING;
		string file_font_input_final = string((const char *)file_font_input.toLocal8Bit());
		setting_file.open(file_font_input_final, ios_base::in);//打开文件
		if (!setting_file.is_open())//打开文件失败
		{
			ui.textEdit_main->setFont(QFont(tr("宋体"), 9, QFont::Normal, false));
		}
		else//输入配置信息
		{
			string information_font;//字体
			string information_type;//类型
			string information_size;//尺寸
			string information_throw;//弃去不用的字符串
			setting_file >> information_throw;//读取文件内容，用文件在输出时自带的空格符和回车符筛选各个字符串，然后弃掉不需要的
			setting_file >> information_throw;
			setting_file.get();//这种方法能在空格字符处停下，但无法删除空格字符，如果没有这一步，下面的字符串开头会包含一个空格
			getline(setting_file, information_font, '\n');
			setting_file >> information_throw;
			setting_file >> information_throw;
			setting_file.get();
			getline(setting_file, information_type, '\n');
			setting_file >> information_throw;
			setting_file >> information_throw;
			setting_file.get();
			getline(setting_file, information_size, '\n');
			setting_file.close();
			bool information_size_receive;//转换是否成功的返回值
			int size_digit = QString(QString::fromLocal8Bit(information_size.c_str())).toInt(&information_size_receive);//转换尺寸为数值
			QString type_transform = QString(QString::fromLocal8Bit(information_type.c_str()));//转化字符串格式
			if (information_size_receive == false)//限定数字选择范围
			{
				size_digit = 1;
			}
			else
			{
				if (size_digit < 1)
				{
					size_digit = 1;
				}
				else if (size_digit > 200)
				{
					size_digit = 200;
				}
				else
				{

				}
			}
			if (type_transform == tr("常规"))//设置字体
			{
				ui.textEdit_main->setFont(QFont(QString(QString::fromLocal8Bit(information_font.c_str())), size_digit, QFont::Normal, false));
			}
			else if (type_transform == tr("粗体"))
			{
				ui.textEdit_main->setFont(QFont(QString(QString::fromLocal8Bit(information_font.c_str())), size_digit, QFont::Bold, false));
			}
			else if (type_transform == tr("倾斜"))
			{
				ui.textEdit_main->setFont(QFont(QString(QString::fromLocal8Bit(information_font.c_str())), size_digit, QFont::Normal, true));
			}
			else if (type_transform == tr("粗体倾斜"))
			{
				ui.textEdit_main->setFont(QFont(QString(QString::fromLocal8Bit(information_font.c_str())), size_digit, QFont::Bold, true));
			}
			else
			{
				ui.textEdit_main->setFont(QFont(QString(QString::fromLocal8Bit(information_font.c_str())), size_digit, QFont::Normal, false));
			}
			setting_file.close();
		}
	}

	//成员变量设置
	void Notepad::set_args_string(string object_string)//获取通过右键菜单等方式打开程序时传入的目标文件路径
	{
		args_string = object_string;

		//解析命令行
		QString args_string_result;//最终参数
		args_string_result = QString(QString::fromLocal8Bit(args_string.c_str()));//string转qstring
		if (!args_string_result.isEmpty())//读取文件
		{
			QFileInfo args_file_info(args_string_result);//提取文件后缀以便于指定打开方式
			QString file_suffix = args_file_info.suffix();
			if ((*setting_text_address).contains(file_suffix))//文本方式
			{
				hex_status = WINDOW_TOOL_TOHEX_STATUS_NO_FLAG;
				ui.pushButton_tool_05->setStyleSheet("border-image:url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_1.png);");//改变按钮样式		
			}
			else if ((*setting_binary_address).contains(file_suffix))
			{
				hex_status = WINDOW_TOOL_TOHEX_STATUS_YES_FLAG;
				ui.pushButton_tool_05->setStyleSheet("border-image:url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_2.png);");//改变按钮样式
			}
			else
			{
				if (*setting_default_open_method_address == tr("文本方式"))
				{
					hex_status = WINDOW_TOOL_TOHEX_STATUS_NO_FLAG;
					ui.pushButton_tool_05->setStyleSheet("border-image:url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_1.png);");//改变按钮样式
				}
				else if (*setting_default_open_method_address == tr("二进制方式"))
				{
					hex_status = WINDOW_TOOL_TOHEX_STATUS_YES_FLAG;
					ui.pushButton_tool_05->setStyleSheet("border-image:url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_2.png);");//改变按钮样式
				}
				else
				{
					hex_status = WINDOW_TOOL_TOHEX_STATUS_NO_FLAG;
					ui.pushButton_tool_05->setStyleSheet("border-image:url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_1.png);");//改变按钮样式
				}
			}
			file_load(args_string_result);
		}
		else
		{

		}
	}

	void Notepad::set_current_path(QString object_string)//设置文件打开或保存窗口使用的路径
	{
		file_dialog_file_name = object_string;
	}

	//键盘事件，用于响应快捷键
	void Notepad::keyPressEvent(QKeyEvent *event)
	{
		//ctrl和字母键的组合，先按下字母键再按下ctrl则无效
		if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_N))//新建
		{
			textedit_new();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_O))//打开
		{
			textedit_open();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_S))//保存
		{
			textedit_save();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_D))//另存为
		{
			textedit_saveas();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_P))//打印
		{
			textedit_print();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_B))//文本模式/二进制模式切换
		{
			textedit_tohex();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_F))//查找
		{
			textedit_find();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_H))//替换
		{
			textedit_replace();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_T))//字体设置
		{
			textedit_font();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_R))//颜色设置
		{
			textedit_color();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_E))//编码设置
		{
			textedit_code();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_G))//其他设置
		{
			textedit_setting();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_I))//程序信息
		{
			textedit_help();
		}
		else
		{

		}
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	void Notepad::mousePressEvent(QMouseEvent *event)//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bPressed = true;
			m_point = event->pos();
		}
		else
		{

		}
	}

	void Notepad::mouseMoveEvent(QMouseEvent *event)//若鼠标左键被按下，则移动窗体位置
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}
	}

	void Notepad::mouseReleaseEvent(QMouseEvent *event)//鼠标未被按下，则相应变量为false
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//拖拽事件
	void Notepad::dragEnterEvent(QDragEnterEvent *e)
	{
		if (e->mimeData()->hasUrls())//防止出现拖拽文本框中的文字造成Url识别出错，然后程序崩溃
		{
			e->acceptProposedAction(); //可以在这个窗口部件上拖放对象
		}
		else
		{

		}
	}
	
	void Notepad::dropEvent(QDropEvent *e)//释放时执行的操作
	{
		QList<QUrl> urls = e->mimeData()->urls();
		QString file_name = urls.first().toLocalFile();//获得文件名
		file_dialog_file_name = file_name;//传入工作路径便于后续打开或保存文件窗口展开路径初始化
		file_dialog_file_name_address = &file_dialog_file_name;//传入工作路径便于后续打开或保存文件窗口显示路径初始化。不能使用file_name，因为其为临时变量
		file_name = (file_name).replace(tr("/"), tr("\\"));//替换路径中的指定字符
		file_load(file_name);//加载文件
	}

	void Notepad::paintEvent(QPaintEvent *)//绘制事件
	{

		//绘制窗口背景。具体方法：首先指派5种背景风格。之后从5组随机数中选取一个，映射到其中一种风格上面。以下是对应的映射关系：[1,5]->ココア，[6,10]->チノ，[11,15]->リゼ，[16,20]->シャロ,[21,25]->千夜。此外，之后的其他图片也和构建背景使用的随机数有关。
		QString backrandnumber;//决定背景图片的参数
		//以下功能用到了常量，如要修改最好重写
		if (randnumber >= 1 && randnumber <= 5)
		{
			backrandnumber = "1";
		}
		else if (randnumber >= 6 && randnumber <= 10)
		{
			backrandnumber = "2";
		}
		else if (randnumber >= 11 && randnumber <= 15)
		{
			backrandnumber = "3";
		}
		else if (randnumber >= 16 && randnumber <= 20)
		{
			backrandnumber = "4";
		}
		else if (randnumber >= 21 && randnumber <= 25)
		{
			backrandnumber = "5";
		}
		else
		{

		}

		//绘制背景，文本框背景及右边边界
		QString filepath;//背景图片路径
		QString texteditbackground;//文本框背景图片路径
		filepath = WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING + backrandnumber;
		filepath += WINDOW_BACKGROUND_PICTURE_PATH_BACK_STRING;
		texteditbackground = WINDOW_TEXTEDIT_BACKGROUND_PICTURE_PATH_STRING + backrandnumber;
		texteditbackground += WINDOW_TEXTEDIT_BACKGROUND_PICTURE_PATH_BACK_STRING;
		QPainter background_painter(this);
		QPainter margin_right_painter(this);
		QPainter textedit_painter(this);
		QPixmap background_picture;
		QPixmap margin_right_picture;
		QPixmap textedit_picture;
		background_picture.load(filepath);
		margin_right_picture.load((QString)WINDOW_MARGIN_PICTURE_RIGHT_PATH_STRING);
		textedit_picture.load(texteditbackground);
		background_painter.drawPixmap(0, 0, WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_HEIGHT_NUMBER, background_picture);
		margin_right_painter.drawPixmap(WINDOW_SIZE_MARGIN_PICTURE_LEFT_WIDTH_NUMBER, 0, WINDOW_SIZE_MARGIN_PICTURE_RIGHT_WIDTH_NUMBER, WINDOW_SIZE_MARGIN_PICTURE_LEFT_HEIGHT_NUMBER, margin_right_picture);//从左边图片边界末尾的位置画右边边界，因为需要使用UI控件，因此右边部分只能画一次，否则会造成控件失效
		textedit_painter.drawPixmap(WINDOW_TEXTEDIT_X_OFFSET_NUMBER, WINDOW_TEXTEDIT_Y_OFFSET_NUMBER, WINDOW_TEXTEDIT_SIZE_WIDTH_NUMBER, WINDOW_TEXTEDIT_SIZE_HEIGHT_NUMBER, textedit_picture);
	}

	//定时器到期处理函数
	void Notepad::timer_chara_picture_timeout()
	{
		chara_picture_timer->stop();
		if (timer_chara_status == WINDOW_CHARA_NORMAL_FLAG)
		{
			timer_chara_status = WINDOW_CHARA_SPECIAL_FLAG;
		}
		else if (timer_chara_status == WINDOW_CHARA_SPECIAL_FLAG)
		{
			timer_chara_status = WINDOW_CHARA_NORMAL_FLAG;
		}

		//绘制人物图像和左侧边界
		if (timer_chara_status == WINDOW_CHARA_NORMAL_FLAG)//通过人物状态的判断来映射到指定图片上面
		{
			chara_picture_label->setPixmap(chara_picture);
			timer_interval_number = WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER + rand() % (WINDOW_RANDOM_TIMER_CHARA_NORMAL_MAX_NUMBER - WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER + 1);//长时间间隔，即人物眼睛睁开的时间
		}
		else if (timer_chara_status == WINDOW_CHARA_SPECIAL_FLAG)
		{
			chara_picture_label->setPixmap(chara_picture_extra);
			timer_interval_number = WINDOW_RANDOM_TIMER_CHARA_SPECIAL_NUMBER;//短时间间隔，即人物形象眼睛闭上的时间
		}
		else
		{
			chara_picture_label->setPixmap(chara_picture);
			timer_interval_number = WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER + rand() % (WINDOW_RANDOM_TIMER_CHARA_NORMAL_MAX_NUMBER - WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER + 1);
		}
		margin_picture.load((QString)WINDOW_MARGIN_PICTURE_LEFT_PATH_STRING);
		margin_picture_label->setPixmap(margin_picture);//左侧边界
		chara_picture_timer->setInterval(timer_interval_number);
		chara_picture_timer->start();
	}

	//显示光标所在的行数与列数
	void Notepad::text_line_and_col()
	{
		QTextCursor textCursor = ui.textEdit_main->textCursor();//鼠标光标对象
		int linenumber = textCursor.blockNumber();//获取光标行数。这是以回车符判别，不是显示出来的行数
		int colnumber = textCursor.columnNumber();//获得光标列数
		ui.label_filestatus->setText(tr("行:%1  列:%2").arg(linenumber + 1).arg(colnumber));//行数从0开始，因此需要增加1
	}

	//基本功能实现
	void Notepad::textedit_copy()//复制
	{
		ui.textEdit_main->copy();
	}

	void Notepad::textedit_paste()//粘贴
	{
		ui.textEdit_main->paste();
	}

	void Notepad::textedit_cut()//剪切
	{
		ui.textEdit_main->cut();
	}

	void Notepad::textedit_undo()//撤销
	{
		ui.textEdit_main->undo();
	}

	void Notepad::textedit_redo()//重做
	{
		ui.textEdit_main->redo();
	}

	void Notepad::textedit_font()//字体
	{
		Font dialog;//信息提示框
		dialog.set_textedit(ui.textEdit_main);//传入文本框地址
		dialog.set_resource_random_number(font_randnumber, hex_status);//设置资源文件使用的随机数和处理模式
		dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
	}

	void Notepad::textedit_color()//颜色
	{
		Color dialog;//信息提示框
		dialog.set_textedit(ui.textEdit_main);//传入文本框地址
		dialog.set_resource_random_number(font_randnumber);//设置资源文件使用的随机数
		dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
	}

	void Notepad::textedit_help()//程序信息
	{
		Help dialog;//信息提示框
		dialog.setWindowTitle(tr("关于我"));
		dialog.set_dialog_information_path(DIALOG_INFORMATION_HELP_PICTURE_PATH_STRING);
		dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
	}

	void Notepad::textedit_new()//新建
	{
		if (save_status())
		{
			ui.textEdit_main->clear();
			set_file_name("");
			ui.label_filename->setText(tr("未命名"));//文件名显示
			QString dialog_title_name = (tr("未命名"));//窗口标题
			dialog_title_name += WINDOW_DIALOG_TITLE_PATH_STRING;
			setWindowTitle(dialog_title_name);
			if (hex_status == WINDOW_TOOL_TOHEX_STATUS_YES_FLAG)//根据处理方式更新编码提示框内容
			{
				ui.label_code->setText(tr("二进制数据"));//修改主界面编码信息显示
			}
			else
			{
				ui.label_code->setText(*text_code);//修改主界面编码信息显示
			}
			setting_file_font_read();//加载对应字体文件
		}
		else
		{

		}
	}

	void Notepad::textedit_open()//打开
	{
		if (save_status())
		{
			File dialog;//信息提示框
			dialog.setWindowTitle(tr("打开文件"));
			file_dialog_file_name = current_file_name;
			file_dialog_file_name_address = &file_dialog_file_name;//设置地址
			file_dialog_status_address = &file_dialog_status;
			dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
			dialog.set_file_dialog_status_address(file_dialog_status_address);//传入存放文件打开或保存窗口的状态的变量
			dialog.set_button_save_or_open(0);
			dialog.set_current_path(file_dialog_file_name);//传入工作路径
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
			if (file_dialog_status == true)
			{
				if (!file_dialog_file_name.isEmpty())
				{
					file_load(file_dialog_file_name);
				}
				else
				{
					Help dialog;//信息提示框
					dialog.setWindowTitle(tr("有错误哦……"));
					dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_READ_PICTURE_PATH_STRING);
					dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
				}
			}
			else
			{

			}
		}
		else
		{

		}
	}

	bool Notepad::textedit_save()//保存
	{
		if (current_file_name.isEmpty())//如果当前文件没有文件名
		{
			return textedit_saveas();
		}
		else
		{
			return file_save(current_file_name);
		}
	}

	bool Notepad::textedit_saveas()//另存为
	{
		File dialog;//信息提示框
		dialog.setWindowTitle(tr("保存文件"));
		file_dialog_file_name = current_file_name;
		file_dialog_file_name_address = &file_dialog_file_name;//设置地址
		file_dialog_status_address = &file_dialog_status;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(file_dialog_status_address);//传入存放文件打开或保存窗口的状态的变量
		dialog.set_button_save_or_open(1);
		dialog.set_current_path(file_dialog_file_name);//传入工作路径
		dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		if (file_dialog_status == true)
		{
			if (file_dialog_file_name.isEmpty())
			{
				Help dialog;//信息提示框
				dialog.setWindowTitle(tr("有错误哦……"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_WRITE_PICTURE_PATH_STRING);
				dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
				return false;
			}
			else
			{
				return file_save(file_dialog_file_name);
			}
		}
		else
		{
			return false;
		}
	}

	void Notepad::textedit_find()//查找
	{
		if (find_dialog_mutex == 1)//只有在没有查找对话框时才能创建
		{
			Find *dialog = new Find;//信息提示框
			dialog->set_dialog_information_path(DIALOG_INFORMATION_FIND_PICTURE_PATH_STRING);
			dialog->set_textedit(ui.textEdit_main);
			dialog->setModal(false);
			dialog->show();//改用非模态对话框，注意非模态窗口不能直接用对象创建，需要用new方法，否则会立即退出
		}
		else
		{

		}
		
	}

	void Notepad::textedit_replace()//替换
	{
		if (find_dialog_mutex == 1)//只有在没有查找对话框时才能创建
		{
			Replace *dialog = new Replace;//信息提示框
			dialog->set_dialog_information_path(DIALOG_INFORMATION_REPLACE_PICTURE_PATH_STRING);
			dialog->set_textedit(ui.textEdit_main);
			dialog->setModal(false);
			dialog->show();//改用非模态对话框，注意非模态窗口不能直接用对象创建，需要用new方法，否则会立即退出
		}
		else
		{

		}

	}

	void Notepad::textedit_tohex()//十六进制转化
	{
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_NO_FLAG)
		{
			hex_status = WINDOW_TOOL_TOHEX_STATUS_YES_FLAG;
			ui.pushButton_tool_05->setStyleSheet("border-image:url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_2.png);");//改变按钮样式
		}
		else
		{
			hex_status = WINDOW_TOOL_TOHEX_STATUS_NO_FLAG;
			ui.pushButton_tool_05->setStyleSheet("border-image:url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_1.png);");//改变按钮样式
		}
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_YES_FLAG)//根据处理方式更新编码提示框内容
		{
			ui.label_code->setText(tr("二进制数据"));//修改主界面编码信息显示
		}
		else
		{
			ui.label_code->setText(*text_code);//修改主界面编码信息显示
		}
		setting_file_font_read();//字体切换
	}

	void Notepad::textedit_code()//编码转换
	{
		Code dialog;
		dialog.set_code_information(text_code, ui.label_code, hex_status);
		dialog.exec();
	}

	void Notepad::textedit_setting()//其他设置
	{
		Setting dialog;
		dialog.set_textedit(ui.textEdit_main);//利用指针传递参数
		dialog.set_setting_text_address(setting_text_address);
		dialog.set_setting_binary_address(setting_binary_address);
		dialog.set_setting_default_open_method_address(setting_default_open_method_address);
		dialog.set_setting_bool_value_address(setting_bool_value_address[0], 0);
		dialog.set_setting_bool_value_address(setting_bool_value_address[1], 1);
		dialog.set_setting_bool_value_address(setting_bool_value_address[2], 2);
		dialog.set_setting_size_address(setting_size_address[0], 0);
		dialog.set_setting_size_address(setting_size_address[1], 1);
		dialog.exec();
	}

	void Notepad::textedit_print()//打印
	{
		Print dialog;
		dialog.set_textedit(ui.textEdit_main);//传入主界面参数
		dialog.set_timer(chara_picture_timer);
		dialog.set_label_chara(chara_picture_label);
		dialog.set_label_margin(margin_picture_label);
		dialog.set_chara_path(chara_path_normal);
		dialog.set_flag(timer_chara_status_address);
		dialog.exec();
	}

	void Notepad::file_load(QString name)//加载文件。这里用到了大量常量，如要修改最好重写
	{
		QFile file(name);
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_NO_FLAG)//不是十六进制模式
		{
			if (!file.open(QFile::ReadOnly | QFile::Text))
			{
				Help dialog;//信息提示框
				dialog.setWindowTitle(tr("有错误哦……"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_READ_PICTURE_PATH_STRING);
				dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
			}
			else
			{

				set_file_name(name);
				ui.label_filename->setText(name);//文件名显示
				QString dialog_title_name = name;//窗口标题
				dialog_title_name += WINDOW_DIALOG_TITLE_PATH_STRING;
				setWindowTitle(dialog_title_name);
				file.close();
				File_read_text_thread *thread = new File_read_text_thread();//启用子线程
				connect(thread, &QThread::finished, thread, &QObject::deleteLater);//直接delete子线程极其容易出现各种问题，要想安全删除线程可以使用此方式
				connect(this, SIGNAL(send_file_name(QString)), thread, SLOT(get_file_name(QString)));//信号连接函数不仅应该放在能同时获得两个对象的地方，还要保证这里的子线程能在启动前得到所有参数。此外，信号函数和槽函数里面的参数只写类型，不写变量名，并且必须使用指针对象
				connect(this, SIGNAL(send_file_size(int)), thread, SLOT(get_file_size(int)));
				connect(this, SIGNAL(send_file_code(QString)), thread, SLOT(get_file_code(QString)));
				emit send_file_name(name);//发出信号，给子线程传递文件名
				emit send_file_size(*setting_size_address[0]);//发出信号，给子线程传递一次处理文件块大小
				emit send_file_code(*text_code);//发出信号，给子线程传递文件编码
				ui.label_file_read_advance->setText(tr("正在获取文件信息……"));//显示预处理进度信息
				ui.label_file_read_advance->setVisible(true);//显示进度提示
				progress_bar_change_color = false;//文件打开时进度条字体颜色未切换
				ui.textEdit_main->clear();//清除文本内容
				connect(thread, SIGNAL(send_data(QString, bool)), this, SLOT(get_data_t_r(QString, bool)));//接受子线程返回的参数
				connect(thread, SIGNAL(send_index(long long, long long)), this, SLOT(get_index_t_r(long long, long long)));
				connect(thread, SIGNAL(send_advance_final()), this, SLOT(get_advance_final_t_r()));
				connect(thread, SIGNAL(send_final()), this, SLOT(get_final_t_r()));
				thread->start();//开始子线程。一定放在前面3个connect函数后面，否则有概率比它们先执行完子线程，connect函数还没被读取子线程那里的信号就已经发出来了，然后接收不到，造成槽函数无法运行
			}
		}
		else//是十六进制模式
		{
			if (!file.open(QFile::ReadOnly))
			{
				Help dialog;//信息提示框
				dialog.setWindowTitle(tr("有错误哦……"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_READ_PICTURE_PATH_STRING);
				dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
			}
			else
			{
				ui.label_code->setText("二进制数据");
				set_file_name(name);
				ui.label_filename->setText(name);//文件名显示
				QString dialog_title_name = name;//窗口标题
				dialog_title_name += WINDOW_DIALOG_TITLE_PATH_STRING;
				setWindowTitle(dialog_title_name);
				file.close();
				File_read_binary_thread *thread = new File_read_binary_thread();//启用子线程
				connect(thread, &QThread::finished, thread, &QObject::deleteLater);//直接delete子线程极其容易出现各种问题，要想安全删除线程可以使用此方式
				connect(this, SIGNAL(send_file_name(QString)), thread, SLOT(get_file_name(QString)));//信号连接函数不仅应该放在能同时获得两个对象的地方，还要保证这里的子线程能在启动前得到所有参数。此外，信号函数和槽函数里面的参数只写类型，不写变量名，并且必须使用指针对象
				connect(this, SIGNAL(send_file_size(int)), thread, SLOT(get_file_size(int)));
				connect(this, SIGNAL(send_file_addspace(bool)), thread, SLOT(get_file_addspace(bool)));
				emit send_file_name(name);//发出信号，给子线程传递文件名
				emit send_file_size(*setting_size_address[1]);//发出信号，给子线程传递一次处理文件块大小
				emit send_file_addspace(*setting_bool_value_address[2]);//发出信号，给子线程传递决定是否添加空格字符的布尔值
				ui.progressBar->setVisible(true);//显示进度条
				ui.progressBar->setValue(0);//进度条初始值为0
				progress_bar_change_color = false;//文件打开时进度条字体颜色未切换
				if (randnumber >= 1 && randnumber <= 5)//进度条文字颜色初始化
				{
					ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #FF53B9;background-color: #00FFFFFF;text-align:center;color:#FF53B9;}QProgressBar::chunk{background-color:#FF53B9;}");
				}
				else if (randnumber >= 6 && randnumber <= 10)
				{
					ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #8599D4;background-color: #00FFFFFF;text-align:center;color:#8599D4;}QProgressBar::chunk{background-color:#8599D4;}");
				}
				else if (randnumber >= 11 && randnumber <= 15)
				{
					ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #DE3FEB;background-color: #00FFFFFF;text-align:center;color:#DE3FEB;}QProgressBar::chunk{background-color:#DE3FEB;}");
				}
				else if (randnumber >= 16 && randnumber <= 20)
				{
					ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #F2995D;background-color: #00FFFFFF;text-align:center;color:#F2995D;}QProgressBar::chunk{background-color:#F2995D;}");
				}
				else if (randnumber >= 21 && randnumber <= 25)
				{
					ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #47B94E;background-color: #00FFFFFF;text-align:center;color:#47B94E;}QProgressBar::chunk{background-color:#47B94E;}");
				}
				else
				{

				}
				ui.textEdit_main->clear();//清除文本内容
				connect(thread, SIGNAL(send_data(QString, bool)), this, SLOT(get_data_b_r(QString, bool)));//接受子线程返回的参数
				connect(thread, SIGNAL(send_index(long long, long long)), this, SLOT(get_index_b_r(long long, long long)));
				connect(thread, SIGNAL(send_final()), this, SLOT(get_final_b_r()));
				thread->start();//开始子线程。一定放在前面3个connect函数后面，否则有概率比它们先执行完子线程，connect函数还没被读取子线程那里的信号就已经发出来了，然后接收不到，造成槽函数无法运行
			}
		}
		setting_file_font_read();//加载对应字体文件
	}

	bool Notepad::save_status()//判断是否需要保存
	{
		if (ui.textEdit_main->document()->isModified())//判断文件是否被修改
		{
			Save dialog;//相关提示框
			dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_SAVE_PICTURE_PATH_STRING);
			dialog.set_return_number(DIALOG_INFORMATION_CANNOT_SAVE_NORMAL_RETURN_NUMBER);//预先还原返回值
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
			if (dialog.get_return_number() == DIALOG_INFORMATION_CANNOT_SAVE_NORMAL_RETURN_NUMBER)//取消
			{
				return false;
			}
			else if (dialog.get_return_number() == DIALOG_INFORMATION_CANNOT_SAVE_SAVE_RETURN_NUMBER)//保存
			{
				
				return textedit_save();
			}
			else if (dialog.get_return_number() == DIALOG_INFORMATION_CANNOT_SAVE_DISCARD_RETURN_NUMBER)//忽略，即不保存
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}

	bool Notepad::file_save(QString name)//实际保存功能。这里用到了大量常量，如要修改最好重写
	{
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_NO_FLAG)//不是十六进制模式
		{
			QFile file(name);
			if (!file.open(QFile::WriteOnly | QFile::Text))
			{
				Help dialog;//信息提示框
				dialog.setWindowTitle(tr("有错误哦……"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_WRITE_PICTURE_PATH_STRING);
				dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
				return false;
			}
			else
			{
				set_file_name(name);
				ui.label_filename->setText(name);//文件名显示
				QString dialog_title_name = name;//窗口标题
				dialog_title_name += WINDOW_DIALOG_TITLE_PATH_STRING;
				setWindowTitle(dialog_title_name);
				file.close();
				File_write_text_thread *thread = new File_write_text_thread();//启用子线程
				connect(thread, &QThread::finished, thread, &QObject::deleteLater);//直接delete子线程极其容易出现各种问题，要想安全删除线程可以使用此方式
				connect(this, SIGNAL(send_file_name(QString)), thread, SLOT(get_file_name(QString)));//信号连接函数不仅应该放在能同时获得两个对象的地方，还要保证这里的子线程能在启动前得到所有参数。此外，信号函数和槽函数里面的参数只写类型，不写变量名，并且必须使用指针对象
				connect(this, SIGNAL(send_file_output(QString)), thread, SLOT(get_file_output(QString)));
				connect(this, SIGNAL(send_file_code(QString)), thread, SLOT(get_file_code(QString)));
				emit send_file_name(name);//发出信号，给子线程传递文件名
				emit send_file_output(ui.textEdit_main->toPlainText());//发出信号，给子线程传递需要输出的文本
				ui.label_file_read_advance->setText(tr("正在保存文件……"));//显示进度信息
				ui.label_file_read_advance->setVisible(true);//显示进度提示
				emit send_file_code(*text_code);//发出信号，给子线程传递文件编码
				progress_bar_change_color = false;//文件打开时进度条字体颜色未切换
				connect(thread, SIGNAL(send_final()), this, SLOT(get_final_t_w()));
				thread->start();//开始子线程。一定放在前面3个connect函数后面，否则有概率比它们先执行完子线程，connect函数还没被读取子线程那里的信号就已经发出来了，然后接收不到，造成槽函数无法运行
				return true;
			}
		}
		else
		{
			QFile file(name);
			if (!file.open(QFile::WriteOnly))
			{
				Help dialog;//信息提示框
				dialog.setWindowTitle(tr("有错误哦……"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_WRITE_PICTURE_PATH_STRING);
				dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
				return false;
			}
			else
			{
				set_file_name(name);
				ui.label_filename->setText(name);//文件名显示
				QString dialog_title_name = name;//窗口标题
				dialog_title_name += WINDOW_DIALOG_TITLE_PATH_STRING;
				setWindowTitle(dialog_title_name);
				file.close();
				File_write_binary_thread *thread = new File_write_binary_thread();//启用子线程
				connect(thread, &QThread::finished, thread, &QObject::deleteLater);//直接delete子线程极其容易出现各种问题，要想安全删除线程可以使用此方式
				connect(this, SIGNAL(send_file_name(QString)), thread, SLOT(get_file_name(QString)));//信号连接函数不仅应该放在能同时获得两个对象的地方，还要保证这里的子线程能在启动前得到所有参数。此外，信号函数和槽函数里面的参数只写类型，不写变量名，并且必须使用指针对象
				connect(this, SIGNAL(send_file_output(QString)), thread, SLOT(get_file_output(QString)));
				emit send_file_name(name);//发出信号，给子线程传递文件名
				emit send_file_output(ui.textEdit_main->toPlainText());//发出信号，给子线程传递需要输出的文本
				ui.label_file_read_advance->setText(tr("正在保存文件……"));//显示进度信息
				ui.label_file_read_advance->setVisible(true);//显示进度提示
				progress_bar_change_color = false;//文件打开时进度条字体颜色未切换
				connect(thread, SIGNAL(send_final()), this, SLOT(get_final_b_w()));
				thread->start();//开始子线程。一定放在前面3个connect函数后面，否则有概率比它们先执行完子线程，connect函数还没被读取子线程那里的信号就已经发出来了，然后接收不到，造成槽函数无法运行
				return true;
			}
		}
	}

	void Notepad::set_file_name(QString name)//设置文件名并初始化文本框修改状态
	{
		current_file_name = name;
		ui.textEdit_main->document()->setModified(false);//重置文本框修改状态为未修改
		ui.label_savestatus->setText(tr("已保存"));
		this->setWindowModified(false);
		name.isEmpty() ? this->setWindowFilePath("new.txt") : this->setWindowFilePath(name);
	}

	void Notepad::close_dialog()//关闭窗口按钮
	{
		if (save_status())
		{
			close_window_include_animation();//关闭窗口并且退出程序
		}
		else
		{

		}
	}

	void Notepad::set_not_save_status()//设置未保存标记
	{
		if (ui.textEdit_main->document()->isModified())//加入该判断，防止出现利用撤销功能回到初始状态却显示未保存的状况
		{
			ui.label_savestatus->setText(tr("未保存"));
		}
		else
		{
			ui.label_savestatus->setText(tr("已保存"));
		}
	}

	void Notepad::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
	{

		//禁用所有按钮，否则动画播放完毕前再次点击按钮会重新触发动画
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(false);
		}
		QPropertyAnimation *animation_close = new QPropertyAnimation(this, "windowOpacity");
		animation_close->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//窗口关闭动画效果
		animation_close->setStartValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation_close->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_close->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		connect(animation_close, SIGNAL(finished()), this, SLOT(close()));
	}
	
	//File_read_text_thread类的子线程数据接收
	void Notepad::get_data_t_r(QString data, bool status)//显示内容，status决定是否为最后一次
	{
		char *transform_final;//QString转char*，获得编码名称
		QByteArray transform = (*text_code).toLocal8Bit();
		transform_final = transform.data();
		ui.label_code->setText(*text_code);
		ui.textEdit_main->insertPlainText(data);
		if (status)//最后一次需要单独处理
		{
			ui.textEdit_main->document()->setModified(false);//重置文本框修改状态为未修改
			ui.label_savestatus->setText(tr("已保存"));
		}
		else
		{

		}
	}

	void Notepad::get_index_t_r(long long index, long long total_size)//进度条显示
	{
		double progress_bar_value = (((double)index / (double)total_size)*100);//计算比例
		if (progress_bar_value > 100)
		{
			progress_bar_value = 100;
		}
		else
		{

		}
		if (progress_bar_value > 50 && !progress_bar_change_color)//避免看不见数字
		{
			if (randnumber >= 1 && randnumber <= 5)
			{
				ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #FF53B9;background-color: #00FFFFFF;text-align:center;color:#F8EBF4;}QProgressBar::chunk{background-color:#FF53B9;}");
			}
			else if (randnumber >= 6 && randnumber <= 10)
			{
				ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #8599D4;background-color: #00FFFFFF;text-align:center;color:#EDECF7;}QProgressBar::chunk{background-color:#8599D4;}");
			}
			else if (randnumber >= 11 && randnumber <= 15)
			{
				ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #DE3FEB;background-color: #00FFFFFF;text-align:center;color:#F0E5F7;}QProgressBar::chunk{background-color:#DE3FEB;}");
			}
			else if (randnumber >= 16 && randnumber <= 20)
			{
				ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #F2995D;background-color: #00FFFFFF;text-align:center;color:#FBEDE4;}QProgressBar::chunk{background-color:#F2995D;}");
			}
			else if (randnumber >= 21 && randnumber <= 25)
			{
				ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #47B94E;background-color: #00FFFFFF;text-align:center;color:#EEF2EB;}QProgressBar::chunk{background-color:#47B94E;}");
			}
			else
			{

			}
			progress_bar_change_color = true;//保证只切换一次字体颜色
		}
		else
		{

		}
		ui.progressBar->setValue((int)progress_bar_value);//进度条显示
	}

	void Notepad::get_advance_final_t_r()//隐藏进度提示并显示进度条
	{
		ui.label_file_read_advance->setVisible(false);//隐藏进度提示
		ui.progressBar->setValue(0);//进度条数值初始化
		if (randnumber >= 1 && randnumber <= 5)//进度条文字颜色初始化
		{
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #FF53B9;background-color: #00FFFFFF;text-align:center;color:#FF53B9;}QProgressBar::chunk{background-color:#FF53B9;}");
		}
		else if (randnumber >= 6 && randnumber <= 10)
		{
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #8599D4;background-color: #00FFFFFF;text-align:center;color:#8599D4;}QProgressBar::chunk{background-color:#8599D4;}");
		}
		else if (randnumber >= 11 && randnumber <= 15)
		{
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #DE3FEB;background-color: #00FFFFFF;text-align:center;color:#DE3FEB;}QProgressBar::chunk{background-color:#DE3FEB;}");
		}
		else if (randnumber >= 16 && randnumber <= 20)
		{
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #F2995D;background-color: #00FFFFFF;text-align:center;color:#F2995D;}QProgressBar::chunk{background-color:#F2995D;}");
		}
		else if (randnumber >= 21 && randnumber <= 25)
		{
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #47B94E;background-color: #00FFFFFF;text-align:center;color:#47B94E;}QProgressBar::chunk{background-color:#47B94E;}");
		}
		else
		{

		}
		ui.progressBar->setVisible(true);//显示进度条
	}

	void Notepad::get_final_t_r()//结束
	{
		ui.progressBar->setValue((int)WINDOW_PROGRESSBAR_MAX_VALUE_NUMBER);//进度条显示最大值
		ui.progressBar->setVisible(false);//隐藏进度条
	}

	//File_write_text_thread类的子线程数据接收
	void Notepad::get_final_t_w()//结束
	{
		ui.label_file_read_advance->setVisible(false);//隐藏进度显示
	}

	//File_read_binary_thread类的子线程数据接收
	void Notepad::get_data_b_r(QString data, bool status)//显示内容，status决定是否为最后一次
	{
		ui.textEdit_main->insertPlainText(data);
		if (status)//最后一次需要单独处理
		{
			ui.textEdit_main->document()->setModified(false);//重置文本框修改状态为未修改
			ui.label_savestatus->setText(tr("已保存"));
		}
		else
		{

		}
	}

	void Notepad::get_index_b_r(long long index, long long total_size)//进度条显示
	{
		get_index_t_r(index, total_size);//和读取文本文件一样
	}

	void Notepad::get_final_b_r()//结束
	{
		get_final_t_r();
	}

	void Notepad::get_final_b_w()//隐藏进度提示
	{
		get_final_t_w();
	}

	//子线程类函数
	File_read_text_thread::File_read_text_thread()//构造函数
	{
		
	}

	File_read_text_thread::~File_read_text_thread()//析构函数
	{

	}

	void File_read_text_thread::get_file_name(QString file_name)//获取文件名
	{
		this->file_name = file_name;//因为类的成员变量名和参数名相同，因此必须用this指代
	}

	void File_read_text_thread::get_file_size(int file_size)//获取一次处理文件块大小
	{
		this->file_size = file_size;
	}

	void File_read_text_thread::get_file_code(QString file_code)//获取一次处理文件块大小
	{
		this->file_code = file_code;
	}

	void File_read_text_thread::run()//子线程主函数
	{
		mutex.lock();//必须加锁
		QFile sourcefile(file_name);
		if (!sourcefile.open(QFile::ReadOnly | QFile::Text))//第二次打开文件，如果无法打开就不给予提示，因为之前一次已经进行了提示
		{

		}
		else
		{
			QTextStream sourcefile_textstream(&sourcefile);
			QTextStream *sourcefile_textstream_address = &sourcefile_textstream;//QTextStream不能直接按值传递，也不能使用引用传递，但是可以用指针传递
			char* transform_final;//QString转char*
			QByteArray transform = (file_code).toLocal8Bit();
			transform_final = transform.data();
			sourcefile_textstream.setCodec(transform_final);//设置编码
			long long total_time = 0;//之后读取文件总共需要循环的次数，这样计算比实际处理次数少一次
			long long total_size = 0;//文件总大小
			int once_size = 0;//在某一次读取时获得的块大小
			for (total_time = 0;; total_time++)//先读取一次文件获得总字符数信息信息
			{
				QString temp_string = sourcefile_textstream.read(file_size*FILE_BIT_TO_KBIT);//读取指send_advance_final定块大小的文件字节，然后计算实际字节数（因为最后一次大部分情况下读取的字符串不会达到相应的块大小），并同时对总的处理次数进行记录
				once_size = temp_string.size();
				total_size += once_size;
				if (once_size < file_size*FILE_BIT_TO_KBIT)
				{
					break;
				}
				else
				{

				}
			}
			emit send_advance_final();//文件获取总字符数目处理完毕，发出信号
			sourcefile_textstream.seek(0);//指针重新定义到文件开头便于接下来的实际读取
			typedef QString(*FUNCPROC)(QTextStream*, int);//宏定义函数指针类型，自定义名称为FUNCPROC
			HINSTANCE dll_name;//显式加载dll文件
			dll_name = LoadLibrary(FILE_DLL_FILE_READ_PATH_STRING);//加载dll文件，常量为宽字符类型
			if (dll_name != NULL)
			{
				FUNCPROC file_read_text_func = (FUNCPROC)GetProcAddress(dll_name, "file_read_text");//获得dll中函数名地址并用file_read_text_func替代其名字
				if (file_read_text_func != NULL)
				{
					for (long long temp_time = 1; temp_time <= total_time; temp_time++)//使用循环读取文件内容，不包含最后一次
					{
						QString return_string = file_read_text_func(sourcefile_textstream_address, file_size);//经过测试，直接将return_string右边部分全部写在emit里面会导致错误
						Sleep(WINDOW_THREAD_WAIT_TIME_NUMBER);//子线程休眠一段时间，否则运行过快导致主线程卡死
						emit send_data(return_string, false);
						emit send_index(file_size*temp_time*FILE_BIT_TO_KBIT, total_size);
					}
					QString return_string;//最后一次因为信号的原因单独处理
					return_string = file_read_text_func(sourcefile_textstream_address, file_size);
					Sleep(WINDOW_THREAD_WAIT_TIME_NUMBER);//子线程休眠一段时间，否则运行过快导致主线程卡死
					emit send_data(return_string, true);
					emit send_index(file_size*((total_time + 1)*FILE_BIT_TO_KBIT), total_size);
					emit send_final();//处理完毕
				}
				else
				{

				}
				FreeLibrary(dll_name);//卸载dll文件，注意参数和加载dll文件不同
			}
			else
			{

			}
			sourcefile.close();
		}
		mutex.unlock();//解锁
		this->quit();//退出子线程
	}

	File_write_text_thread::File_write_text_thread()//构造函数
	{

	}

	File_write_text_thread::~File_write_text_thread()//析构函数
	{

	}

	void File_write_text_thread::get_file_output(QString file_output)//获得文件需要输出的内容
	{
		this->file_output = file_output;
	}

	void File_write_text_thread::run()
	{
		mutex.lock();//必须加锁
		QFile outputfile(file_name);
		QTextStream outputfile_textstream(&outputfile);
		QTextStream *outputfile_textstream_address = &outputfile_textstream;//QTextStream不能直接按值传递，也不能使用引用传递，但是可以用指针传递
		char* transform_final;//QString转char*
		QByteArray transform = file_code.toLocal8Bit();
		transform_final = transform.data();
		outputfile_textstream.setCodec(transform_final);//设置编码
		if (!outputfile.open(QFile::WriteOnly | QFile::Text))//第二次打开文件，如果无法打开就不给予提示，因为之前一次已经进行了提示
		{

		}
		else
		{
			typedef void(*FUNCPROC)(QTextStream*, QString);//宏定义函数指针类型，自定义名称为FUNCPROC
			HINSTANCE dll_name;//显式加载dll文件
			dll_name = LoadLibrary(FILE_DLL_FILE_READ_PATH_STRING);//加载dll文件，常量为宽字符类型
			if (dll_name != NULL)
			{
				FUNCPROC file_write_text_func = (FUNCPROC)GetProcAddress(dll_name, "file_write_text");//获得dll中函数名地址并用file_read_text_func替代其名字
				if (file_write_text_func != NULL)
				{
					file_write_text_func(outputfile_textstream_address, file_output);
					Sleep(WINDOW_THREAD_WAIT_TIME_NUMBER);//子线程休眠一段时间，否则运行过快导致主线程卡死
					emit send_final();//处理完毕
				}
				else
				{
					
				}
				FreeLibrary(dll_name);//卸载dll文件，注意参数和加载dll文件不同
			}
			else
			{

			}
			outputfile.close();
		}
		mutex.unlock();//解锁
		this->quit();//退出子线程
	}

	File_read_binary_thread::File_read_binary_thread()//构造函数
	{

	}

	File_read_binary_thread::~File_read_binary_thread()//析构函数
	{

	}

	void File_read_binary_thread::get_file_addspace(bool file_addspace)//获取是否添加空格的布尔值
	{
		this->file_addspace = file_addspace;
	}

	void File_read_binary_thread::run()//子线程主函数
	{
		mutex.lock();//必须加锁
		QFile sourcefile(file_name);
		if (!sourcefile.open(QFile::ReadOnly))//第二次打开文件，如果无法打开就不给予提示，因为之前一次已经进行了提示
		{

		}
		else
		{
			QDataStream sourcefile_datastream(&sourcefile);
			QDataStream *sourcefile_datastream_address = &sourcefile_datastream;//QTextStream不能直接按值传递，也不能使用引用传递，但是可以用指针传递
			long long total_size = sourcefile.size();//文件总大小
			long long total_time = (long long)(sourcefile.size() / file_size/ FILE_BIT_TO_KBIT);//之后读取文件总共需要循环的次数，这样计算比实际处理次数少一次
			typedef QString(*FUNCPROC)(QDataStream*, int, bool);//宏定义函数指针类型，自定义名称为FUNCPROC
			HINSTANCE dll_name;//显式加载dll文件
			dll_name = LoadLibrary(FILE_DLL_FILE_READ_PATH_STRING);//加载dll文件，常量为宽字符类型
			if (dll_name != NULL)
			{
				FUNCPROC file_read_binary_func = (FUNCPROC)GetProcAddress(dll_name, "file_read_binary");//获得dll中函数名地址并用file_read_text_func替代其名字
				if (file_read_binary_func != NULL)
				{
					for (long long temp_time = 1; temp_time <= total_time; temp_time++)//使用循环读取文件内容，不包含最后一次
					{
						QString return_string = file_read_binary_func(sourcefile_datastream_address, file_size*FILE_BIT_TO_KBIT, file_addspace);//经过测试，直接将return_string右边部分全部写在emit里面会导致错误。注意块大小的单位，dll文件函数没有乘以倍率，需要在这里处理
						Sleep(WINDOW_THREAD_WAIT_TIME_NUMBER);//子线程休眠一段时间，否则运行过快导致主线程卡死
						emit send_data(return_string, false);
						emit send_index(file_size*temp_time*FILE_BIT_TO_KBIT, total_size);
					}
					QString return_string;//最后一次因为信号的原因单独处理
					return_string = file_read_binary_func(sourcefile_datastream_address, total_size - file_size * total_time*FILE_BIT_TO_KBIT, file_addspace);//由于读取原始数据是存入char*的，但动态申请的char*数据会有初始垃圾数据，胡最后一次要控制好大小以免在文件末尾出现其他数据
					Sleep(WINDOW_THREAD_WAIT_TIME_NUMBER);//子线程休眠一段时间，否则运行过快导致主线程卡死
					emit send_data(return_string, true);
					emit send_index(file_size*((total_time + 1)*FILE_BIT_TO_KBIT), total_size);
					emit send_final();//处理完毕
				}
				else
				{

				}
				FreeLibrary(dll_name);//卸载dll文件，注意参数和加载dll文件不同
			}
			else
			{

			}
			sourcefile.close();
		}
		mutex.unlock();//解锁
		this->quit();//退出子线程
	}

	File_write_binary_thread::File_write_binary_thread()//构造函数
	{

	}

	File_write_binary_thread::~File_write_binary_thread()//析构函数
	{

	}

	void File_write_binary_thread::get_file_output(QString file_output)//获得文件需要输出的内容
	{
		this->file_output = file_output;
	}

	void File_write_binary_thread::run()
	{
		mutex.lock();//必须加锁
		QFile outputfile(file_name);
		QDataStream outputfile_datastream(&outputfile);
		QDataStream *outputfile_datastream_address = &outputfile_datastream;//QTextStream不能直接按值传递，也不能使用引用传递，但是可以用指针传递
		if (!outputfile.open(QFile::WriteOnly))//第二次打开文件，如果无法打开就不给予提示，因为之前一次已经进行了提示
		{

		}
		else
		{
			typedef void(*FUNCPROC)(QDataStream*, QString);//宏定义函数指针类型，自定义名称为FUNCPROC
			HINSTANCE dll_name;//显式加载dll文件
			dll_name = LoadLibrary(FILE_DLL_FILE_READ_PATH_STRING);//加载dll文件，常量为宽字符类型
			if (dll_name != NULL)
			{
				FUNCPROC file_write_binary_func = (FUNCPROC)GetProcAddress(dll_name, "file_write_binary");//获得dll中函数名地址并用file_read_text_func替代其名字
				if (file_write_binary_func != NULL)
				{
					file_write_binary_func(outputfile_datastream_address, file_output);
					Sleep(WINDOW_THREAD_WAIT_TIME_NUMBER);//子线程休眠一段时间，否则运行过快导致主线程卡死
					emit send_final();//处理完毕
				}
				else
				{

				}
				FreeLibrary(dll_name);//卸载dll文件，注意参数和加载dll文件不同
			}
			else
			{

			}
			outputfile.close();
		}
		mutex.unlock();//解锁
		this->quit();//退出子线程
	}
}

