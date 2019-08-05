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
	Font::Font(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		totalrandomnumber = DIALOG_RANDOM_MIN_NUMBER + rand() % (DIALOG_RANDOM_MAX_NUMBER - DIALOG_RANDOM_MIN_NUMBER + 1);//产生指定随机数以便决定背景图片和人物图片样式
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		resize(DIALOG_FONT_SIZE_WIDTH_NUMBER, DIALOG_FONT_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		is_escape_pressed = false;//允许按下esc键退出程序

		//图片路径
		//背景图片路径
		filepath = DIALOG_FONT_BACKGROUND_PICTURE_PATH_FRONT_STRING + QString::number(totalrandomnumber, 10);
		filepath += DIALOG_FONT_BACKGROUND_PICTURE_PATH_BACK_STRING;

		//加载界面，必须放在最后以避免界面被之后的绘图覆盖
		ui.setupUi(this);

		//加载按钮和显示框样式
		ui.pushButton_close_dialog->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_font_exit_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_font_exit_pressed.png);}");
		ui.pushButton_accept_dialog->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_font_accept_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_font_accept_pressed.png);}");
		ui.label_sample->setStyleSheet("QLabel{border:2px solid rgb(128, 76, 71);}");

		//加载字体表
		read_font();

		//连接处理函数
		connect(ui.comboBox_1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change(const QString &)));
		connect(ui.comboBox_2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change(const QString &)));
		connect(ui.comboBox_3, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change(const QString &)));
		connect(ui.comboBox_4, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change(const QString &)));

		//确定按钮
		connect(ui.pushButton_accept_dialog, SIGNAL(clicked()), this, SLOT(font_change()));

		//关闭按钮
		connect(ui.pushButton_close_window, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));
		connect(ui.pushButton_close_dialog, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));

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
		ui.comboBox_2->setPalette(lineedit_palette);
		ui.comboBox_3->setPalette(lineedit_palette);
		ui.comboBox_4->setPalette(lineedit_palette);
		ui.label_sample->setPalette(lineedit_palette);

		//加载样式文件
		QString stylesheet_file_name = DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_STRING;
		stylesheet_file_name += QString::number(totalrandomnumber, 10);
		stylesheet_file_name += DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_BACK_STRING;
		QFile stylesheet_file_1(stylesheet_file_name);
		QFile stylesheet_file_2(stylesheet_file_name);
		QFile stylesheet_file_3(stylesheet_file_name);
		QFile stylesheet_file_4(stylesheet_file_name);
		stylesheet_file_1.open(QFile::ReadOnly);
		stylesheet_file_2.open(QFile::ReadOnly);
		stylesheet_file_3.open(QFile::ReadOnly);
		stylesheet_file_4.open(QFile::ReadOnly);
		ui.comboBox_1->setStyleSheet(stylesheet_file_1.readAll());
		ui.comboBox_2->setStyleSheet(stylesheet_file_2.readAll());
		ui.comboBox_3->setStyleSheet(stylesheet_file_3.readAll());
		ui.comboBox_4->setStyleSheet(stylesheet_file_4.readAll());
		stylesheet_file_1.close();
		stylesheet_file_2.close();
		stylesheet_file_3.close();
		stylesheet_file_4.close();

		//去掉关联性控件的右键菜单
		QList<QScrollBar *> scroll_bar = this->findChildren<QScrollBar *>();//由于无法用常规方式获得combobox的滚动条，因此使用该方法查找所有同类型控件并进行操作
		foreach(QScrollBar *scroll_bar_style_control, scroll_bar)
		{
			scroll_bar_style_control->setContextMenuPolicy(Qt::NoContextMenu);
		}

		//组合框输入限制
		ui.comboBox_3->setValidator(new QIntValidator(1, 200, this));//只允许输入指定范围的数字

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}

	Font::~Font()
	{

	}

	//初始设置
	void Font::read_font()//读取系统已有字体并置入组合框
	{
		QFontDatabase combobox_fontdatabase;
		foreach(const QString &font_name, combobox_fontdatabase.families())
		{
			ui.comboBox_1->addItem(font_name);
		}
	}

	//设置成员变量
	void Font::set_textedit(QTextEdit *main_textedit)
	{
		textedit_font = main_textedit;
	}

	void Font::set_resource_random_number(int number, int status)//获取资源文件需要的数值变量
	{
		resource_randomnumber = number;
		hex_status = status;
		ifstream setting_file;//字体
		QString file_font_input = FILE_FONT_OUTPUT_FILE_PATH_FRONT_STRING;
		file_font_input += QString::number(resource_randomnumber, 10);
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_YES_FLAG)//二进制模式需要加载另外的字体文件
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
			ui.comboBox_1->setCurrentText(tr("宋体"));
			ui.comboBox_2->setCurrentText(tr("常规"));
			ui.comboBox_3->setCurrentText(tr("9"));
			ui.label_sample->setFont(QFont(tr("宋体"), 9, QFont::Normal, false));
			ui.label_sample->setText(tr("请问您今天要来点兔子吗？"));
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
			bool information_size_recieve;//转换是否成功的返回值
			int size_digit = QString(QString::fromLocal8Bit(information_size.c_str())).toInt(&information_size_recieve);//转换尺寸为数值
			QString type_transform = QString(QString::fromLocal8Bit(information_type.c_str()));//转化字符串格式
			if (information_size_recieve == false)//限定数字选择范围
			{
				size_digit = 9;
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
			setting_file.close();
			QString information_font_final = QString(QString::fromLocal8Bit(information_font.c_str()));
			QString information_type_final = QString(QString::fromLocal8Bit(information_type.c_str()));
			QString information_size_final = QString(QString::fromLocal8Bit(information_size.c_str()));
			ui.comboBox_1->setCurrentText(information_font_final);
			ui.comboBox_2->setCurrentText(information_type_final);
			ui.comboBox_3->setCurrentText(information_size_final);
			QString combobox_2_text = ui.comboBox_2->currentText();
			QString sample_string;//要显示的信息
			bool combobox_3_recieve;//转换是否成功的返回值
			int combobox_3_digit = ui.comboBox_3->currentText().toInt(&combobox_3_recieve);
			if (combobox_3_recieve == false)//限定数字选择范围
			{
				combobox_3_digit = 9;
			}
			else
			{
				if (combobox_3_digit < 1)
				{
					combobox_3_digit = 1;
				}
				else if (combobox_3_digit > 200)
				{
					combobox_3_digit = 200;
				}
				else
				{

				}
			}
			if (combobox_2_text == tr("常规"))//设置字体
			{
				ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal, false));
			}
			else if (combobox_2_text == tr("粗体"))
			{
				ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Bold, false));
			}
			else if (combobox_2_text == tr("倾斜"))
			{
				ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal, true));
			}
			else if (combobox_2_text == tr("粗体倾斜"))
			{
				ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Bold, true));
			}
			else
			{
				ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal));
			}
			ui.label_sample->setText(tr("请问您今天要来点兔子吗？"));
		}
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void Font::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bPressed = true;
			m_point = event->pos();
		}
	}
	//若鼠标左键被按下，则移动窗体位置
	void Font::mouseMoveEvent(QMouseEvent *event)
	{
		if (m_bPressed)
			move(event->pos() - m_point + pos());
	}

	//鼠标未被按下，则相应变量为false
	void Font::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉，因此这里除了修改回车键的功能，还要加上原来的esc键的功能
	void Font::keyPressEvent(QKeyEvent *event)
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

	void Font::paintEvent(QPaintEvent *)
	{

		//绘制窗口用到的图片。具体方法：首先指派5种背景风格。之后从5组随机数中选取一个，映射到其中一种风格上面。以下是对应的映射关系：[1,5]->ココア，[6,10]->チノ，[11,15]->リゼ，[16,20]->シャロ,[21,25]->千夜。此外，之后的其他图片也和构建背景使用的随机数有关。每个背景对应3张图片，每次随机选取1张。
		//以下功能用到了常量，如要修改最好重写
		//绘制图片
		QPainter background_painter(this);//背景
		QPainter margin_painter(this);//边框
		QPainter information_painter(this);//文字
		QPixmap background_picture;
		QPixmap margin_picture;
		QPixmap information_picture;
		dialog_information_path = DIALOG_INFORMATION_FONT_PICTURE_PATH_STRING;//文字信息
		dialog_information_path += QString::number(totalrandomnumber, 10);//将随机数转化为路径中的一部分
		dialog_information_path += DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING;
		background_picture.load(filepath);
		margin_picture.load((QString)DIALOG_FONT_MARGIN_PICTURE_PATH_STRING);
		information_picture.load(dialog_information_path);
		background_painter.drawPixmap(0, 0, DIALOG_FONT_SIZE_WIDTH_NUMBER, DIALOG_FONT_SIZE_HEIGHT_NUMBER, background_picture);
		information_painter.drawPixmap(0, 0, DIALOG_FONT_SIZE_WIDTH_NUMBER, DIALOG_FONT_SIZE_HEIGHT_NUMBER, information_picture);//文字部分应该从左边的图片部分的右边缘开始
		margin_painter.drawPixmap(0, 0, DIALOG_FONT_SIZE_WIDTH_NUMBER, DIALOG_FONT_SIZE_HEIGHT_NUMBER, margin_picture);//最后显示以免被图片覆盖
	}

	//组合框选项
	//以下功能用到了常量，如要修改最好重写
	void Font::combobox_change(const QString &)
	{
		QString combobox_2_text = ui.comboBox_2->currentText();
		QString sample_string;//要显示的信息
		bool combobox_3_recieve;//转换是否成功的返回值
		int combobox_3_digit = ui.comboBox_3->currentText().toInt(&combobox_3_recieve);
		if (combobox_3_recieve == false)//限定数字选择范围
		{
			combobox_3_digit = 9;
		}
		else
		{
			if (combobox_3_digit < 1)
			{
				combobox_3_digit = 1;
				ui.comboBox_3->setCurrentText("1");
			}
			else if (combobox_3_digit > 200)
			{
				combobox_3_digit = 200;
			}
			else
			{

			}
		}
		if (ui.comboBox_4->currentText() == tr("简体中文"))//设置文字内容
		{
			sample_string = tr("请问您今天要来点兔子吗？");
		}
		else if (ui.comboBox_4->currentText() == tr("English"))
		{
			sample_string = tr("Is the order a rabbit?");
		}
		else if (ui.comboBox_4->currentText() == tr("日本語"))
		{
			sample_string = tr("ご注文はうさぎですが？");
		}
		else
		{
			sample_string = tr("请问您今天要来点兔子吗？");
		}
		if (combobox_2_text == tr("常规"))//设置字体
		{
			ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal, false));
		}
		else if (combobox_2_text == tr("粗体"))
		{
			ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Bold, false));
		}
		else if (combobox_2_text == tr("倾斜"))
		{
			ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal, true));
		}
		else if (combobox_2_text == tr("粗体倾斜"))
		{
			ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Bold, true));
		}
		else
		{
			ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal));
		}
		ui.label_sample->setText(sample_string);
	}
	void Font::font_change()
	{
		QString combobox_2_text = ui.comboBox_2->currentText();
		QString temp_string;//临时存储要显示的信息
		QString sample_string;//要显示的信息
		bool combobox_3_recieve;//转换是否成功的返回值
		int combobox_3_digit = ui.comboBox_3->currentText().toInt(&combobox_3_recieve);
		if (combobox_3_recieve == false)//限定数字选择范围
		{
			combobox_3_digit = 9;
		}
		else
		{
			if (combobox_3_digit < 1)
			{
				combobox_3_digit = 9;
			}
			else if (combobox_3_digit > 200)
			{
				combobox_3_digit = 9;
			}
			else
			{

			}
		}
		if (combobox_2_text == tr("常规"))//设置字体
		{
			textedit_font->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal, false));
		}
		else if (combobox_2_text == tr("粗体"))
		{
			textedit_font->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Bold, false));
		}
		else if (combobox_2_text == tr("倾斜"))
		{
			textedit_font->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal, true));
		}
		else if (combobox_2_text == tr("粗体倾斜"))
		{
			textedit_font->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Bold, true));
		}
		else
		{
			textedit_font->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal));
		}
		ofstream setting_file;//输出设置文件
		QString file_font_output = FILE_FONT_OUTPUT_FILE_PATH_FRONT_STRING;
		file_font_output += QString::number(resource_randomnumber, 10);
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_YES_FLAG)//二进制模式需要加载另外的字体文件
		{
			file_font_output += FILE_FONT_OUTPUT_FILE_PATH_BINARY_EXTRA_STRING;
		}
		else
		{

		}
		file_font_output += FILE_FONT_OUTPUT_FILE_PATH_BACK_STRING;
		string file_font_out_put_final = string((const char *)file_font_output.toLocal8Bit());
		setting_file.open(file_font_out_put_final, ios_base::out);//打开文件，若不存在则创建
		if (!setting_file.is_open())//打开文件失败
		{

		}
		else//输出配置信息
		{
			setting_file << "font = " << string((const char *)(ui.comboBox_1->currentText()).toLocal8Bit()) << "\n";
			setting_file << "type = " << string((const char *)combobox_2_text.toLocal8Bit()) << "\n";
			setting_file << "size = " << combobox_3_digit << "\n";
			setting_file.close();
		}
		close_window_include_animation();
	}

	void Font::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

