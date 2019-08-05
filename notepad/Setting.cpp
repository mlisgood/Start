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
	Setting::Setting(QWidget *parent) : QDialog(parent)
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
		ui.pushButton_close_dialog->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_pressed.png);}");
		ui.pushButton_accept_dialog->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_pressed.png);}");

		//列表操作按钮
		connect(ui.pushButton_list_1, SIGNAL(clicked()), this, SLOT(list_1_button()));
		connect(ui.pushButton_list_2, SIGNAL(clicked()), this, SLOT(list_2_button()));
		connect(ui.pushButton_list_3, SIGNAL(clicked()), this, SLOT(list_3_button()));
		connect(ui.pushButton_list_4, SIGNAL(clicked()), this, SLOT(list_4_button()));
		connect(ui.pushButton_list_5, SIGNAL(clicked()), this, SLOT(list_5_button()));
		connect(ui.pushButton_list_6, SIGNAL(clicked()), this, SLOT(list_6_button()));

		//确定按钮
		connect(ui.pushButton_accept_dialog, SIGNAL(clicked()), this, SLOT(accept_button()));

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
		ui.spinBox_1->setPalette(lineedit_palette);
		ui.spinBox_2->setPalette(lineedit_palette);
		ui.listWidget_1->setPalette(lineedit_palette);
		ui.listWidget_2->setPalette(lineedit_palette);
		ui.lineEdit_1->setPalette(lineedit_palette);
		ui.lineEdit_2->setPalette(lineedit_palette);

		//加载样式文件
		QString stylesheet_file_name = DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_STRING;
		stylesheet_file_name += QString::number(totalrandomnumber, 10);
		stylesheet_file_name += DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_BACK_STRING;
		QFile stylesheet_file(stylesheet_file_name);
		stylesheet_file.open(QFile::ReadOnly);
		ui.comboBox_1->setStyleSheet(stylesheet_file.readAll());
		stylesheet_file.close();

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

		//设置控件字体
		extern QString font_str;//因为listWidget_1内部的控件字体无法使用默认字体设置，因此必须单独设置。注意因为没有命名空间的关系，这个在main函数外面定义的全局变量不能和find_dialog_mutex一样在外面进行定义，否则会被当成一个新定义的全局变量rem::font_str
		if (font_str != "")
		{
			QFont file_font(font_str, FILE_FONT_DEFAULT_SIZE);//设置默认字体
			ui.listWidget_1->setFont(file_font);
			ui.listWidget_2->setFont(file_font);
		}
		else//加载失败，使用软件设定好的默认字体
		{

		}
	}

	Setting::~Setting()
	{

	}

	//设置成员变量
	void Setting::set_textedit(QTextEdit *main_textedit)
	{
		textedit_main = main_textedit;
	}

	void Setting::set_setting_text_address(QStringList *main_list)//获取主界面字符串组1地址
	{
		setting_text_address = main_list;
		ui.listWidget_1->addItems(*setting_text_address);//界面初始化不能放在构造函数里面，否则因为构造函数先执行，等到初始化完毕，才能接收到主界面传来的值，而此前初始化已经完毕，指针可能因为指向了空地址而发生错误
	}

	void Setting::set_setting_binary_address(QStringList *main_list)//获取主界面字符串组2地址
	{
		setting_binary_address = main_list;
		ui.listWidget_2->addItems(*setting_binary_address);
	}

	void Setting::set_setting_default_open_method_address(QString *main_string)//获取主界面字符串地址
	{
		setting_default_open_method_address = main_string;
		if (*setting_default_open_method_address == tr("文本方式"))
		{
			ui.comboBox_1->setCurrentText(tr("文本方式"));
		}
		else if (*setting_default_open_method_address == tr("二进制方式"))
		{
			ui.comboBox_1->setCurrentText(tr("二进制方式"));
		}
		else
		{
			ui.comboBox_1->setCurrentText(tr("文本方式"));
		}
	}

	void Setting::set_setting_bool_value_address(bool *main_array_index, int index)//获取主界面bool类型数组元素地址
	{
		setting_bool_value_address[index] = main_array_index;
		if (index == 0)//必须分开判断，否则有可能读到空地址
		{
			if (*setting_bool_value_address[0] == true)
			{
				ui.checkBox_1->setCheckState(Qt::Checked);
			}
			else
			{
				ui.checkBox_1->setCheckState(Qt::Unchecked);
			}
		}
		else if (index == 1)
		{
			if (*setting_bool_value_address[1] == true)
			{
				ui.checkBox_2->setCheckState(Qt::Checked);
			}
			else
			{
				ui.checkBox_2->setCheckState(Qt::Unchecked);
			}
		}
		else if (index == 2)
		{
			if (*setting_bool_value_address[2] == true)
			{
				ui.checkBox_3->setCheckState(Qt::Checked);
			}
			else
			{
				ui.checkBox_3->setCheckState(Qt::Unchecked);
			}
		}
		else
		{

		}
	}

	void Setting::set_setting_size_address(int *main_array_index, int index)//获取主界面int类型数组元素地址
	{
		setting_size_address[index] = main_array_index;
		if (index == 0)
		{
			ui.spinBox_1->setValue(*setting_size_address[index]);
		}
		else if (index == 1)
		{
			ui.spinBox_2->setValue(*setting_size_address[index]);
		}
		else
		{

		}
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void Setting::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bPressed = true;
			m_point = event->pos();
		}
	}
	//若鼠标左键被按下，则移动窗体位置
	void Setting::mouseMoveEvent(QMouseEvent *event)
	{
		if (m_bPressed)
			move(event->pos() - m_point + pos());
	}

	//鼠标未被按下，则相应变量为false
	void Setting::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉，因此这里除了修改回车键的功能，还要加上原来的esc键的功能
	void Setting::keyPressEvent(QKeyEvent *event)
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

	void Setting::paintEvent(QPaintEvent *)
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
		dialog_information_path = DIALOG_INFORMATION_SETTING_PICTURE_PATH_STRING;//文字信息
		dialog_information_path += QString::number(totalrandomnumber, 10);//将随机数转化为路径中的一部分
		dialog_information_path += DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING;
		background_picture.load(filepath);
		margin_picture.load((QString)DIALOG_FONT_MARGIN_PICTURE_PATH_STRING);
		information_picture.load(dialog_information_path);
		background_painter.drawPixmap(0, 0, DIALOG_FONT_SIZE_WIDTH_NUMBER, DIALOG_FONT_SIZE_HEIGHT_NUMBER, background_picture);
		information_painter.drawPixmap(0, 0, DIALOG_FONT_SIZE_WIDTH_NUMBER, DIALOG_FONT_SIZE_HEIGHT_NUMBER, information_picture);//文字部分应该从左边的图片部分的右边缘开始
		margin_painter.drawPixmap(0, 0, DIALOG_FONT_SIZE_WIDTH_NUMBER, DIALOG_FONT_SIZE_HEIGHT_NUMBER, margin_picture);//最后显示以免被图片覆盖
	}

	//槽函数
	//列表按钮操作
	void Setting::list_1_button()//添加
	{
		if (ui.lineEdit_1->text() != "")
		{
			ui.listWidget_1->addItem(ui.lineEdit_1->text());
		}
		else
		{

		}
	}

	void Setting::list_2_button()//删除一项
	{
		if (ui.listWidget_1->currentItem() != Q_NULLPTR)
		{
			QListWidgetItem *item = ui.listWidget_1->takeItem(ui.listWidget_1->currentRow());
			delete item;
		}
	}

	void Setting::list_3_button()//删除全部
	{
		int temp_count = ui.listWidget_1->count();//必须初始时候将这个值赋给另一个变量，不能直接放进循环作为判断条件，因为在循环过程中每次循环会使其减少1
		for (int temp = 0; temp < temp_count; temp++)
		{
			QListWidgetItem *item = ui.listWidget_1->takeItem(0);//注意是每次删除最上面一项，因为每删除一项，其余项会自动移到上面
			delete item;
		}
	}

	void Setting::list_4_button()//添加
	{
		if (ui.lineEdit_2->text() != "")
		{
			ui.listWidget_2->addItem(ui.lineEdit_2->text());
		}
		else
		{

		}
	}

	void Setting::list_5_button()//删除一项
	{
		if (ui.listWidget_2->currentItem() != Q_NULLPTR)
		{
			QListWidgetItem *item = ui.listWidget_2->takeItem(ui.listWidget_2->currentRow());
			delete item;
		}
	}

	void Setting::list_6_button()//删除全部
	{
		int temp_count = ui.listWidget_2->count();
		for (int temp = 0; temp < temp_count; temp++)
		{
			QListWidgetItem *item = ui.listWidget_2->takeItem(0);
			delete item;
		}
	}

	void Setting::accept_button()//确认操作
	{
		*setting_default_open_method_address = ui.comboBox_1->currentText();//将值赋给变量
		*setting_size_address[0] = ui.spinBox_1->value();
		*setting_size_address[1] = ui.spinBox_2->value();
		if (ui.checkBox_1->isChecked())
		{
			*setting_bool_value_address[0] = true;
			textedit_main->setLineWrapMode(QTextEdit::WidgetWidth);//允许在窗口部件的当前宽度自动换行
		}
		else
		{
			*setting_bool_value_address[0] = false;
			textedit_main->setLineWrapMode(QTextEdit::NoWrap);//禁止自动换行
		}
		if (ui.checkBox_2->isChecked())
		{
			*setting_bool_value_address[1] = true;
		}
		else
		{
			*setting_bool_value_address[1] = false;
		}
		if (ui.checkBox_3->isChecked())
		{
			*setting_bool_value_address[2] = true;
		}
		else
		{
			*setting_bool_value_address[2] = false;
		}
		(*setting_text_address).clear();//清空字符串列表
		(*setting_binary_address).clear();
		for (int temp = 0; temp < ui.listWidget_1->count(); temp++)
		{
			*setting_text_address << ui.listWidget_1->item(temp)->text();
		}
		for (int temp = 0; temp < ui.listWidget_2->count(); temp++)
		{
			*setting_binary_address << ui.listWidget_2->item(temp)->text();
		}
		ofstream setting_text_file;//输出文件
		ofstream setting_binary_file;
		setting_text_file.open(FILE_SETTING_TEXT_OUTPUT_FILE_PATH_STRING, ios_base::out);//打开文件，若不存在则创建
		setting_binary_file.open(FILE_SETTING_BINARY_OUTPUT_FILE_PATH_STRING, ios_base::out);
		if (!setting_text_file.is_open())//打开文件失败
		{

		}
		else//输出配置信息
		{
			for (int temp = 0; temp < (*setting_text_address).count(); temp++)
			{
				setting_text_file << string((const char *)((*setting_text_address).at(temp)).toLocal8Bit());
				setting_text_file << " ";//需要输出空格作为分隔符
			}
			setting_text_file << FILE_SETTING_TEXT_AND_BINARY_END_WRITE_STRING;
			setting_text_file.close();
		}
		if (!setting_binary_file.is_open())//打开文件失败
		{

		}
		else//输出配置信息
		{
			for (int temp = 0; temp < (*setting_binary_address).count(); temp++)
			{
				setting_binary_file << string((const char *)((*setting_binary_address).at(temp)).toLocal8Bit());
				setting_binary_file << " ";//需要输出空格作为分隔符
			}
			setting_binary_file << FILE_SETTING_TEXT_AND_BINARY_END_WRITE_STRING;
			setting_binary_file.close();
		}
		//写入ini文件
		QSettings *setting_other = new QSettings(FILE_SETTING_OTHER_PATH_STRING, QSettings::IniFormat);
		setting_other->setValue(FILE_SETTING_CATALOG_1_INNER_PATH_STRING, *setting_default_open_method_address);
		setting_other->setValue(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING, QString::number(*setting_size_address[0], 10));
		setting_other->setValue(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING, QString::number(*setting_size_address[1], 10));
		setting_other->setValue(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING, QString::number(*setting_bool_value_address[0], 10));
		setting_other->setValue(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING, QString::number(*setting_bool_value_address[1], 10));
		setting_other->setValue(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING, QString::number(*setting_bool_value_address[2], 10));
		delete setting_other;

		//写入注册表
		QSettings *regedit_settings_1 = new QSettings(REG_MENU_1, QSettings::NativeFormat);
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

		close_window_include_animation();
	}

	void Setting::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

