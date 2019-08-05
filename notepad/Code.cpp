#include "define.h"

namespace rem
{

	//使用标准命名空间
	using std::string;
	using std::ifstream;
	using std::ofstream;
	using std::fstream;
	using std::ios_base;

	//构造与析构函数
	Code::Code(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		totalrandomnumber = DIALOG_RANDOM_MIN_NUMBER + rand() % (DIALOG_RANDOM_MAX_NUMBER - DIALOG_RANDOM_MIN_NUMBER + 1);//产生指定随机数以便决定背景图片和人物图片样式
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		resize(DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		is_escape_pressed = false;//允许按下esc键退出程序

		//图片路径
		//背景图片路径
		filepath = DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING + QString::number(totalrandomnumber, 10);
		filepath += DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING;

		//左侧图片路径
		chara_path = DIALOG_CHARA_PICTURE_PATH_FRONT_STRING;
		QString chara_path_number = QString::number(totalrandomnumber, 10);//将随机数转化为路径中的一部分
		chara_path += chara_path_number;
		chara_path += DIALOG_CHARA_PICTURE_PATH_BREAK_STRING;
		chara_path += QString::number(DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER + rand() % (DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER - DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER + 1), 10);//从当前系列的3张图片当中选取一张并增加到路径中
		chara_path += DIALOG_CHARA_PICTURE_PATH_BACK_STRING;

		//加载界面，必须放在最后以避免界面被之后的绘图覆盖
		ui.setupUi(this);

		//加载按钮样式
		ui.pushButton_close_dialog->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_pressed.png);}");
		ui.pushButton_accept_dialog->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_pressed.png);}");

		//设置文字颜色
		QPalette lineedit_palette;
		if (totalrandomnumber == 1)//决定相关文字颜色
		{
			lineedit_palette.setColor(QPalette::Text, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(255, 83, 185, 64));
		}
		else if (totalrandomnumber == 2)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(133, 153, 212, 64));
		}
		else if (totalrandomnumber == 3)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(222, 63, 235, 64));
		}
		else if (totalrandomnumber == 4)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(242, 153, 93, 64));
		}
		else if (totalrandomnumber == 5)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(71, 185, 78, 64));
		}
		else
		{

		}
		ui.comboBox_1->setPalette(lineedit_palette);
		ui.label->setPalette(lineedit_palette);

		//加载样式文件，这里直接使用字体设置窗口中的样式文件即可
		QString stylesheet_file_name = DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_STRING;
		stylesheet_file_name += QString::number(totalrandomnumber, 10);
		stylesheet_file_name += DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_BACK_STRING;
		QFile stylesheet_file(stylesheet_file_name);
		stylesheet_file.open(QFile::ReadOnly);
		ui.comboBox_1->setStyleSheet(stylesheet_file.readAll());
		stylesheet_file.close();

		//设置label样式
		ui.label->setWordWrap(true);//允许换行

		//去掉关联性控件的右键菜单
		QList<QScrollBar *> scroll_bar = this->findChildren<QScrollBar *>();//由于无法用常规方式获得combobox的滚动条，因此使用该方法查找所有同类型控件并进行操作
		foreach(QScrollBar *scroll_bar_style_control, scroll_bar)
		{
			scroll_bar_style_control->setContextMenuPolicy(Qt::NoContextMenu);
		}

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存

		//组合框内容改变
		connect(ui.comboBox_1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change(const QString &)));

		//关闭按钮
		connect(ui.pushButton_close_window, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));
		connect(ui.pushButton_close_dialog, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));

		//确定按钮
		connect(ui.pushButton_accept_dialog, SIGNAL(clicked()), this, SLOT(dialog_accept()));
	}
	Code::~Code()
	{

	}

	//设置成员变量
	void Code::set_code_information(QString* code_information, QLabel *code_label_main_dialog, int status)//获取编码信息和是否处于二进制编辑状态
	{
		code_receive = code_information;//获得主窗口编码
		code_label = code_label_main_dialog;//获得主界面编码信息显示框
		hex_status = status;//获得主界面是否处于二进制编辑状态
		QString code_receive_transform = *code_receive;
		ui.comboBox_1->setCurrentText(code_receive_transform);
		combobox_change(code_receive_transform);//修改编码简介显示内容
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void Code::mousePressEvent(QMouseEvent *event)
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
	//若鼠标左键被按下，则移动窗体位置
	void Code::mouseMoveEvent(QMouseEvent *event)
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}
			
	}

	//鼠标未被按下，则相应变量为false
	void Code::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉。这个窗口因为只有确认操作，本来不需要重写，但为了保持统一，还是进行了重写
	void Code::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Enter)
		{

		}
		else if (event->key() == Qt::Key_Escape)
		{
			if (!is_escape_pressed)//仅执行一次按下esc退出
			{
				is_escape_pressed = true;
				close_window_include_animation();
			}
			else
			{

			}
		}
		else
		{

		}
	}

	void Code::paintEvent(QPaintEvent *)
	{

		//绘制窗口用到的图片。具体方法：首先指派5种背景风格。之后从5组随机数中选取一个，映射到其中一种风格上面。以下是对应的映射关系：[1,5]->ココア，[6,10]->チノ，[11,15]->リゼ，[16,20]->シャロ,[21,25]->千夜。此外，之后的其他图片也和构建背景使用的随机数有关。每个背景对应3张图片，每次随机选取1张。
		//以下功能用到了常量，如要修改最好重写
		//绘制图片
		QString dialog_information_path_temp;//临时存储信息图片路径
		QPainter background_painter(this);//背景
		QPainter margin_painter(this);//边框
		QPainter chara_painter(this);//人物
		QPainter information_painter(this);//文字
		QPixmap background_picture;
		QPixmap margin_picture;
		QPixmap chara_picture;
		QPixmap information_picture;
		dialog_information_path_temp = DIALOG_INFORMATION_CODE_PICTURE_PATH_STRING;
		dialog_information_path_temp += QString::number(totalrandomnumber, 10);//将随机数转化为路径中的一部分
		dialog_information_path_temp += DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING;
		background_picture.load(filepath);
		margin_picture.load((QString)DIALOG_MARGIN_PICTURE_PATH_STRING);
		chara_picture.load(chara_path);
		information_picture.load(dialog_information_path_temp);
		background_painter.drawPixmap(0, 0, DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, background_picture);
		chara_painter.drawPixmap(0, 0, DIALOG_SIZE_HEIGHT_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, chara_picture);//左侧图片使用正方形，长和宽与窗口宽度一致
		information_painter.drawPixmap(DIALOG_SIZE_HEIGHT_NUMBER, 0, DIALOG_SIZE_WIDTH_NUMBER - DIALOG_SIZE_HEIGHT_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, information_picture);//文字部分应该从左边的图片部分的右边缘开始
		margin_painter.drawPixmap(0, 0, DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, margin_picture);//最后显示以免被图片覆盖
	}

	void Code::combobox_change(const QString &code_string)//组合框选项
	{
		if (code_string == tr("Big5"))
		{
			ui.label->setText(tr("Big5即大五码或五大码，是使用繁体中文社区中最常用的电脑汉字字符集标准。"));
		}
		else if (code_string == tr("Big5-HKSCS"))
		{
			ui.label->setText(tr("Big5-HKSCS是在香港地区使用的编码。"));
		}
		else if (code_string == tr("CP949"))
		{
			ui.label->setText(tr("CP949是codepage系列的一种，支持韩文字母。"));
		}
		else if (code_string == tr("EUC-JP"))
		{
			ui.label->setText(tr("EUC-JP用来储存日本JISX0208（旧称JISC6226）及JISX0212字集的字符。"));
		}
		else if (code_string == tr("EUC-KR"))
		{
			ui.label->setText(tr("EUC-KR用来储存韩国KSX1001字集（旧称KSC5601）的字符。此规格由KSX2901（旧称KSC5861）定义。"));
		}
		else if (code_string == tr("GB18030"))
		{
			ui.label->setText(tr("GB18030是中国继GB2312-1980和GB13000.1-1993之后最重要的汉字编码标准，是中国计算机系统必须遵循的基础性标准之一。"));
		}
		else if (code_string == tr("HP-ROMAN8"))
		{
			ui.label->setText(tr("HP-ROMAN8是一种8位单字节字符编码，主要用于HP-UX和许多Hewlett-Packard以及PCL兼容的打印机上。"));
		}
		else if (code_string == tr("IBM 850"))
		{
			ui.label->setText(tr("IBM 850就是CP850，是许多国家和地区的主要代码页和默认OEM代码页。支持Latin-1编码。"));
		}
		else if (code_string == tr("IBM 866"))
		{
			ui.label->setText(tr("IBM 866就是CP866，是在DOS和OS/2下用于编写西里尔文脚本的代码页。支持Cyril字母。"));
		}
		else if (code_string == tr("IBM 874"))
		{
			ui.label->setText(tr("IBM 866就是CP874，支持泰文字母。"));
		}
		else if (code_string == tr("ISO 2022-JP"))
		{
			ui.label->setText(tr("ISO 2022-JP是ISO/IEC 2022系列的一种，用于日文编码。"));
		}
		else if (code_string == tr("ISO 8859-1"))
		{
			ui.label->setText(tr("ISO 8859-1即Latin-1，在西欧地区常用，包括德法两国的字母。"));
		}
		else if (code_string == tr("ISO 8859-2"))
		{
			ui.label->setText(tr("ISO 8859-2即Latin-2，收录东欧字符。"));
		}
		else if (code_string == tr("ISO 8859-3"))
		{
			ui.label->setText(tr("ISO 8859-3即Latin-3，收录南欧字符。"));
		}
		else if (code_string == tr("ISO 8859-4"))
		{
			ui.label->setText(tr("ISO 8859-4即Latin-4，收录北欧字符。"));
		}
		else if (code_string == tr("ISO 8859-5"))
		{
			ui.label->setText(tr("ISO 8859-5即Cyrillic，收录斯拉夫语系字符。"));
		}
		else if (code_string == tr("ISO 8859-6"))
		{
			ui.label->setText(tr("ISO 8859-6即Arabic，收录阿拉伯语系字符。"));
		}
		else if (code_string == tr("ISO 8859-7"))
		{
			ui.label->setText(tr("ISO 8859-7即Greek，收录希腊字符。"));
		}
		else if (code_string == tr("ISO 8859-8"))
		{
			ui.label->setText(tr("ISO 8859-8即Hebrew，收录西伯莱字符。"));
		}
		else if (code_string == tr("ISO 8859-9"))
		{
			ui.label->setText(tr("ISO 8859-9即Latin-5或Turkish，收录土耳其字符。"));
		}
		else if (code_string == tr("ISO 8859-10"))
		{
			ui.label->setText(tr("ISO 8859-10即Latin-6或Nordic，收录北欧（主要指斯堪地那维亚半岛）的字符。"));
		}
		else if (code_string == tr("ISO 8859-13"))
		{
			ui.label->setText(tr("ISO 8859-13即Latin-7，主要涵盖波罗的海诸国的文字符号，也补充一些在Latin-6中遗漏的拉脱维亚字符。"));
		}
		else if (code_string == tr("ISO 8859-14"))
		{
			ui.label->setText(tr("ISO 8859-14即Latin-8，此编码将Latin-1中的某些符号换成塞尔特语的字符。"));
		}
		else if (code_string == tr("ISO 8859-15"))
		{
			ui.label->setText(tr("ISO 8859-15即Latin-9，此编码将Latin-1中较少用到的符号换成当初遗漏的法文和芬兰字母，并且把英镑和日元之间的金钱符号换成了欧盟货币符号。"));
		}
		else if (code_string == tr("ISO 8859-16"))
		{
			ui.label->setText(tr("ISO 8859-16即Latin-10，涵盖阿尔巴尼亚语、克罗地亚语、匈牙利语、意大利语、波兰语、罗马尼亚语及斯洛文尼亚语等东南欧国家语言。"));
		}
		else if (code_string == tr("Iscii-Bng"))
		{
			ui.label->setText(tr("Iscii-Bng是Iscii即国际标准信息交换代码的一种。"));
		}
		else if (code_string == tr("Iscii-Dev"))
		{
			ui.label->setText(tr("Iscii-Dev是Iscii即国际标准信息交换代码的一种。"));
		}
		else if (code_string == tr("Iscii-Gjr"))
		{
			ui.label->setText(tr("Iscii-Gjr是Iscii即国际标准信息交换代码的一种。"));
		}
		else if (code_string == tr("Iscii-Knd"))
		{
			ui.label->setText(tr("Iscii-Knd是Iscii即国际标准信息交换代码的一种。"));
		}
		else if (code_string == tr("Iscii-Mlm"))
		{
			ui.label->setText(tr("Iscii-Mlm是Iscii即国际标准信息交换代码的一种。"));
		}
		else if (code_string == tr("Iscii-Ori"))
		{
			ui.label->setText(tr("Iscii-Ori是Iscii即国际标准信息交换代码的一种。"));
		}
		else if (code_string == tr("Iscii-Pnj"))
		{
			ui.label->setText(tr("Iscii-Pnj是Iscii即国际标准信息交换代码的一种。"));
		}
		else if (code_string == tr("Iscii-Tlg"))
		{
			ui.label->setText(tr("Iscii-Tlg是Iscii即国际标准信息交换代码的一种。"));
		}
		else if (code_string == tr("Iscii-Tml"))
		{
			ui.label->setText(tr("Iscii-Tml是Iscii即国际标准信息交换代码的一种。"));
		}
		else if (code_string == tr("KOI8-R"))
		{
			ui.label->setText(tr("KOI8-R是KOI-8系列的斯拉夫文字8位元编码，供俄语及保加利亚语使用。"));
		}
		else if (code_string == tr("KOI8-U"))
		{
			ui.label->setText(tr("KOI8-U是KOI-8系列的斯拉夫文字8位元编码，供乌克兰语使用。"));
		}
		else if (code_string == tr("Macintosh"))
		{
			ui.label->setText(tr("此编码无介绍。"));
		}
		else if (code_string == tr("Shift-JIS"))
		{
			ui.label->setText(tr("Shift-JIS是日本电脑系统常用的编码表。此编码能容纳全角及半角拉丁字母、平假名、片假名、符号及日语汉字。"));
		}
		else if (code_string == tr("TIS-620"))
		{
			ui.label->setText(tr("此编码无介绍。"));
		}
		else if (code_string == tr("TSCII"))
		{
			ui.label->setText(tr("TSCII即泰米尔文字信息交换码，是一个在8位的环境下提供泰米尔语数字化的编码。"));
		}
		else if (code_string == tr("UTF-8"))
		{
			ui.label->setText(tr("UTF-8即万国码，是一种针对Unicode的可变长度字符编码，可以显示中文、英文、日文等多种语言。本程序内部使用的默认编码也是UTF-8。"));
		}
		else if (code_string == tr("UTF-16"))
		{
			ui.label->setText(tr("UTF-16是Unicode的一种格式，此编码将大部分字符都以2字节的长度存储，但无法兼容ASCII编码。"));
		}
		else if (code_string == tr("UTF-16BE"))
		{
			ui.label->setText(tr("UTF-16BE（BE指的是Big Endian）是Unicode的一种格式，此编码将字符按照大尾序的方式存储。使用此编码时，编码的前面会放置FEFF标记，但本程序不会放置该标记。"));
		}
		else if (code_string == tr("UTF-16LE"))
		{
			ui.label->setText(tr("UTF-16LE（LE指的是Little Endian）是Unicode的一种格式，此编码将字符按照小尾序的方式存储。使用此编码时，编码的前面会放置FFFE标记，但本程序不会放置该标记。"));
		}
		else if (code_string == tr("UTF-32"))
		{
			ui.label->setText(tr("UTF-32是Unicode的一种格式，此编码将所有字符都以4字节的长度存储，占用空间非常大。"));
		}
		else if (code_string == tr("UTF-32BE"))
		{
			ui.label->setText(tr("UTF-32BE（BE指的是Big Endian）是Unicode的一种格式，此编码将字符按照大尾序的方式存储。使用此编码时，编码的前面会放置0000FEFF标记，但本程序不会放置该标记。"));
		}
		else if (code_string == tr("UTF-32LE"))
		{
			ui.label->setText(tr("UTF-32LE（LE指的是Little Endian）是Unicode的一种格式，此编码将字符按照小尾序的方式存储。使用此编码时，编码的前面会放置0000FFFE标记，但本程序不会放置该标记。"));
		}
		else if (code_string == tr("Windows-1250"))
		{
			ui.label->setText(tr("Windows-1250是ANSI编码的一种，包含东欧拉丁字母。此编码也属于codepage的范畴。"));
		}
		else if (code_string == tr("Windows-1251"))
		{
			ui.label->setText(tr("Windows-1251是ANSI编码的一种，包含古斯拉夫语字母。此编码也属于codepage的范畴。"));
		}
		else if (code_string == tr("Windows-1252"))
		{
			ui.label->setText(tr("Windows-1252是ANSI编码的一种，包含西欧拉丁字母。此编码也属于codepage的范畴。"));
		}
		else if (code_string == tr("Windows-1253"))
		{
			ui.label->setText(tr("Windows-1253是ANSI编码的一种，包含希腊语字母。此编码也属于codepage的范畴。"));
		}
		else if (code_string == tr("Windows-1254"))
		{
			ui.label->setText(tr("Windows-1254是ANSI编码的一种，包含土耳其语字母。此编码也属于codepage的范畴。"));
		}
		else if (code_string == tr("Windows-1255"))
		{
			ui.label->setText(tr("Windows-1255是ANSI编码的一种，包含希伯来语字母。此编码也属于codepage的范畴。"));
		}
		else if (code_string == tr("Windows-1256"))
		{
			ui.label->setText(tr("Windows-1256是ANSI编码的一种，包含阿拉伯语字母。此编码也属于codepage的范畴。"));
		}
		else if (code_string == tr("Windows-1257"))
		{
			ui.label->setText(tr("Windows-1257是ANSI编码的一种，包含爱沙尼亚语、拉脱维亚语及立陶宛语字母。此编码也属于codepage的范畴。"));
		}
		else if (code_string == tr("Windows-1258"))
		{
			ui.label->setText(tr("Windows-1257是ANSI编码的一种，包含越语字母。此编码也属于codepage的范畴。"));
		}
		else
		{
			ui.label->setText(tr("UTF-8即万国码，是一种针对Unicode的可变长度字符编码，可以显示中文、英文、日文等多种语言。本程序内部使用的默认编码也是UTF-8。"));
		}
	}

	void Code::dialog_accept()//确认操作
	{
		QString information_code = ui.comboBox_1->currentText();//存放编码信息
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_YES_FLAG)//在二进制编辑状况下，只修改配置文件并传递给主界面数据，但不修改主界面显示
		{

		}
		else
		{
			code_label->setText(information_code);//修改主界面编码信息显示
		}
		*code_receive = information_code;//将编码信息传给主界面
		ofstream setting_file_code;//向配置文件写入信息
		QString file_code_input = FILE_CODE_OUTPUT_FILE_PATH_STRING;
		string file_code_input_final = string((const char *)file_code_input.toLocal8Bit());
		setting_file_code.open(file_code_input_final, ios_base::out);//打开文件，若不存在则创建
		if (!setting_file_code.is_open())//打开文件失败
		{
			
		}
		else
		{
			string information_code_temp = string((const char *)information_code.toLocal8Bit());//转化为string
			setting_file_code << information_code_temp;//写入配置文件
			setting_file_code.close();
		}
		close_window_include_animation();//关闭窗口
	}

	void Code::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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
}

