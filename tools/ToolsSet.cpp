#include "define.h"

namespace rem
{

	//引用全局变量
	extern int counter_mutex;

	//构造与析构函数
	ToolsSet::ToolsSet(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		is_escape_pressed = false;//默认未按下esc键以退出

		//加载图片作为窗口背景
		main_picture.load(DIALOG_TOOLS_SET_BACKGROUND_PICTURE_PATH_STRING);
		resize(main_picture.size());//窗口大小改为图片大小

		//加载界面
		ui.setupUi(this);
		
		//设置文字颜色
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::WindowText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::Highlight, QColor(70, 28, 10, 64));
		ui.comboBox_1->setPalette(text_palette);
		ui.comboBox_2->setPalette(text_palette);
		ui.lineedit_program_1->setPalette(text_palette);
		ui.lineedit_program_2->setPalette(text_palette);
		ui.lineedit_program_3->setPalette(text_palette);
		ui.lineedit_program_4->setPalette(text_palette);
		ui.lineedit_program_5->setPalette(text_palette);
		ui.lineedit_program_6->setPalette(text_palette);
		ui.lineedit_program_7->setPalette(text_palette);
		ui.lineedit_program_8->setPalette(text_palette);
		ui.spinBox_1->setPalette(text_palette);
		ui.spinBox_2->setPalette(text_palette);
		
		//加载字体表
		read_font();

		//去掉关联性控件的右键菜单
		QList<QScrollBar *> scroll_bar = this->findChildren<QScrollBar *>();//由于无法用常规方式获得combobox的滚动条，因此使用该方法查找所有同类型控件并进行操作
		foreach(QScrollBar *scroll_bar_style_control, scroll_bar)
		{
			scroll_bar_style_control->setContextMenuPolicy(Qt::NoContextMenu);
		}

		//读取预置内容，对窗口显示进行初始化
		QSettings *begin_read = new QSettings(FILE_SETTING_MAINWINDOW_STYLE_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		QString combobox_1_index;//决定第一个combobox的内容
		combobox_1_index = (begin_read->value(FILE_SETTING_CATALOG_1_INNER_PATH_STRING)).toString();
		if (combobox_1_index == "1")//背景初始化
		{
			ui.comboBox_1->setCurrentText(tr("魔法少女　チノ"));
		}
		else if (combobox_1_index == "2")
		{
			ui.comboBox_1->setCurrentText(tr("ソーサラー　チノ"));
		}
		else if (combobox_1_index == "3")
		{
			ui.comboBox_1->setCurrentText(tr("ガンナー　マヤ"));
		}
		else if (combobox_1_index == "4")
		{
			ui.comboBox_1->setCurrentText(tr("バーサーカー　メグ"));
		}
		else
		{
			ui.comboBox_1->setCurrentText(tr("魔法少女　チノ"));
		}
		QString program_path[8];//程序路径
		program_path[0] = (begin_read->value(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING)).toString();
		program_path[1] = (begin_read->value(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING)).toString();
		program_path[2] = (begin_read->value(FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING)).toString();
		program_path[3] = (begin_read->value(FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING)).toString();
		program_path[4] = (begin_read->value(FILE_SETTING_CATALOG_2_5_INNER_PATH_STRING)).toString();
		program_path[5] = (begin_read->value(FILE_SETTING_CATALOG_2_6_INNER_PATH_STRING)).toString();
		program_path[6] = (begin_read->value(FILE_SETTING_CATALOG_2_7_INNER_PATH_STRING)).toString();
		program_path[7] = (begin_read->value(FILE_SETTING_CATALOG_2_8_INNER_PATH_STRING)).toString();
		ui.lineedit_program_1->setText(program_path[0]);//快捷键启动程序初始化
		ui.lineedit_program_2->setText(program_path[1]);
		ui.lineedit_program_3->setText(program_path[2]);
		ui.lineedit_program_4->setText(program_path[3]);
		ui.lineedit_program_5->setText(program_path[4]);
		ui.lineedit_program_6->setText(program_path[5]);
		ui.lineedit_program_7->setText(program_path[6]);
		ui.lineedit_program_8->setText(program_path[7]);
		if (program_path[0].length()==0)//初始值设置，处理配置文件丢失
		{
			ui.lineedit_program_1->setText(tr("null"));
		}
		else
		{

		}
		if (program_path[1].length() == 0)
		{
			ui.lineedit_program_2->setText(tr("null"));
		}
		else
		{

		}
		if (program_path[2].length() == 0)
		{
			ui.lineedit_program_3->setText(tr("null"));
		}
		else
		{

		}
		if (program_path[3].length() == 0)
		{
			ui.lineedit_program_4->setText(tr("null"));
		}
		else
		{

		}
		if (program_path[4].length() == 0)
		{
			ui.lineedit_program_5->setText(tr("null"));
		}
		else
		{

		}
		if (program_path[5].length() == 0)
		{
			ui.lineedit_program_6->setText(tr("null"));
		}
		else
		{

		}
		if (program_path[6].length() == 0)
		{
			ui.lineedit_program_7->setText(tr("null"));
		}
		else
		{

		}
		if (program_path[7].length() == 0)
		{
			ui.lineedit_program_8->setText(tr("null"));
		}
		else
		{

		}
		bool temp_transform_status_x;//字符串转换为整数是否成功
		bool temp_transform_status_y;
		QString temp_transform_string_x = (begin_read->value(FILE_SETTING_CATALOG_5_1_INNER_PATH_STRING)).toString();
		QString temp_transform_string_y = (begin_read->value(FILE_SETTING_CATALOG_5_2_INNER_PATH_STRING)).toString();
		int position_x = temp_transform_string_x.toInt(&temp_transform_status_x, 10);//转换为整数
		int position_y = temp_transform_string_y.toInt(&temp_transform_status_y, 10);
		if (temp_transform_status_x&&temp_transform_status_y)//转换失败则强制将坐标转为0
		{

		}
		else
		{
			position_x = 0;
			position_y = 0;
		}
		ui.spinBox_1->setValue(position_x);//起始坐标初始化
		ui.spinBox_2->setValue(position_y);
		QString note_font;//便签字体
		note_font = (begin_read->value(FILE_SETTING_CATALOG_4_INNER_PATH_STRING)).toString();
		ui.comboBox_2->setCurrentText(note_font);//便签字体初始化
		QString autorun_status;//是否开机自启动
		autorun_status = (begin_read->value(FILE_SETTING_CATALOG_3_INNER_PATH_STRING)).toString();
		if (autorun_status == "1")
		{
			ui.checkBox->setChecked(true);
		}
		else if (autorun_status == "0")
		{
			ui.checkBox->setChecked(false);
		}
		else
		{
			ui.checkBox->setChecked(false);
		}

		delete begin_read;

		//信号函数
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//设置生效
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//取消设置
		connect(ui.pushButton_choose_1, SIGNAL(clicked()), this, SLOT(pushButton_choose_1_apply()));//选择路径按钮
		connect(ui.pushButton_choose_2, SIGNAL(clicked()), this, SLOT(pushButton_choose_2_apply()));
		connect(ui.pushButton_choose_3, SIGNAL(clicked()), this, SLOT(pushButton_choose_3_apply()));
		connect(ui.pushButton_choose_4, SIGNAL(clicked()), this, SLOT(pushButton_choose_4_apply()));
		connect(ui.pushButton_choose_5, SIGNAL(clicked()), this, SLOT(pushButton_choose_5_apply()));
		connect(ui.pushButton_choose_6, SIGNAL(clicked()), this, SLOT(pushButton_choose_6_apply()));
		connect(ui.pushButton_choose_7, SIGNAL(clicked()), this, SLOT(pushButton_choose_7_apply()));
		connect(ui.pushButton_choose_8, SIGNAL(clicked()), this, SLOT(pushButton_choose_8_apply()));
		connect(ui.pushButton_choose_9, SIGNAL(clicked()), this, SLOT(pushButton_choose_9_apply()));
		connect(ui.pushButton_choose_10, SIGNAL(clicked()), this, SLOT(pushButton_choose_10_apply()));
		connect(ui.pushButton_choose_11, SIGNAL(clicked()), this, SLOT(pushButton_choose_11_apply()));
		connect(ui.pushButton_choose_12, SIGNAL(clicked()), this, SLOT(pushButton_choose_12_apply()));
		connect(ui.pushButton_choose_13, SIGNAL(clicked()), this, SLOT(pushButton_choose_13_apply()));
		connect(ui.pushButton_choose_14, SIGNAL(clicked()), this, SLOT(pushButton_choose_14_apply()));
		connect(ui.pushButton_choose_15, SIGNAL(clicked()), this, SLOT(pushButton_choose_15_apply()));
		connect(ui.pushButton_choose_16, SIGNAL(clicked()), this, SLOT(pushButton_choose_16_apply()));

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}

	ToolsSet::~ToolsSet()
	{

	}

	//初始设置
	void ToolsSet::read_font()//读取系统已有字体并置入组合框
	{
		QFontDatabase combobox_fontdatabase;
		foreach(const QString &font_name, combobox_fontdatabase.families())
		{
			ui.comboBox_2->addItem(font_name);
		}
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void ToolsSet::mousePressEvent(QMouseEvent *event)
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
	void ToolsSet::mouseMoveEvent(QMouseEvent *event)
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
	void ToolsSet::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void ToolsSet::keyPressEvent(QKeyEvent *event)
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

	void ToolsSet::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(WINDOW_BACKGROUND_PAINT_START_X_NUMBER, WINDOW_BACKGROUND_PAINT_START_Y_NUMBER, main_picture);//画图作为窗口背景
	}

	//槽函数
	void ToolsSet::set_apply()//设置生效
	{

		//写入ini文件
		QSettings *write_setting = new QSettings(FILE_SETTING_MAINWINDOW_STYLE_PATH_STRING, QSettings::IniFormat);
		QString background_picture = ui.comboBox_1->currentText();//背景图片
		if (background_picture == tr("魔法少女　チノ"))
		{
			write_setting->setValue(FILE_SETTING_CATALOG_1_INNER_PATH_STRING, "1");
		}
		else if (background_picture == tr("ソーサラー　チノ"))
		{
			write_setting->setValue(FILE_SETTING_CATALOG_1_INNER_PATH_STRING, "2");
		}
		else if (background_picture == tr("ガンナー　マヤ"))
		{
			write_setting->setValue(FILE_SETTING_CATALOG_1_INNER_PATH_STRING, "3");
		}
		else if (background_picture == tr("バーサーカー　メグ"))
		{
			write_setting->setValue(FILE_SETTING_CATALOG_1_INNER_PATH_STRING, "4");
		}
		else
		{
			write_setting->setValue(FILE_SETTING_CATALOG_1_INNER_PATH_STRING, "1");
		}
		write_setting->setValue(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING, ui.lineedit_program_1->text());//程序功能
		write_setting->setValue(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING, ui.lineedit_program_2->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING, ui.lineedit_program_3->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING, ui.lineedit_program_4->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_5_INNER_PATH_STRING, ui.lineedit_program_5->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_6_INNER_PATH_STRING, ui.lineedit_program_6->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_7_INNER_PATH_STRING, ui.lineedit_program_7->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_8_INNER_PATH_STRING, ui.lineedit_program_8->text());
		QString application_name = QApplication::applicationName();//是否自动启动
		QSettings *regedit_settings = new QSettings(REG_RUN, QSettings::NativeFormat);//修改注册表
		if (ui.checkBox->isChecked())//是否自动启动
		{
			QString application_path = QApplication::applicationFilePath();//获得绝对路径
			regedit_settings->setValue(application_name, application_path.replace("/", "\\"));//写入注册表项，注意注册表使用的路径分隔符和QT输出的相反
			write_setting->setValue(FILE_SETTING_CATALOG_3_INNER_PATH_STRING, "1");
		}
		else
		{
			regedit_settings->remove(application_name);//删除注册表项
			write_setting->setValue(FILE_SETTING_CATALOG_3_INNER_PATH_STRING, "0");
		}
		write_setting->setValue(FILE_SETTING_CATALOG_4_INNER_PATH_STRING, ui.comboBox_2->currentText());//字体
		write_setting->setValue(FILE_SETTING_CATALOG_5_1_INNER_PATH_STRING, QString::number(ui.spinBox_1->value(), 10));//起始位置坐标
		write_setting->setValue(FILE_SETTING_CATALOG_5_2_INNER_PATH_STRING, QString::number(ui.spinBox_2->value(), 10));
		delete regedit_settings;
		delete write_setting;
		close_window_include_animation();//设置结束
	}

	void ToolsSet::pushButton_choose_1_apply()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_1->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void ToolsSet::pushButton_choose_2_apply()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_2->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void ToolsSet::pushButton_choose_3_apply()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_3->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void ToolsSet::pushButton_choose_4_apply()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_4->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void ToolsSet::pushButton_choose_5_apply()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_5->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void ToolsSet::pushButton_choose_6_apply()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_6->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void ToolsSet::pushButton_choose_7_apply()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_7->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void ToolsSet::pushButton_choose_8_apply()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_8->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void ToolsSet::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

	void ToolsSet::pushButton_choose_9_apply()//清除路径
	{
		ui.lineedit_program_1->setText("null");
	}

	void ToolsSet::pushButton_choose_10_apply()//清除路径
	{
		ui.lineedit_program_2->setText("null");
	}

	void ToolsSet::pushButton_choose_11_apply()//清除路径
	{
		ui.lineedit_program_3->setText("null");
	}

	void ToolsSet::pushButton_choose_12_apply()//清除路径
	{
		ui.lineedit_program_4->setText("null");
	}

	void ToolsSet::pushButton_choose_13_apply()//清除路径
	{
		ui.lineedit_program_5->setText("null");
	}

	void ToolsSet::pushButton_choose_14_apply()//清除路径
	{
		ui.lineedit_program_6->setText("null");
	}

	void ToolsSet::pushButton_choose_15_apply()//清除路径
	{
		ui.lineedit_program_7->setText("null");
	}

	void ToolsSet::pushButton_choose_16_apply()//清除路径
	{
		ui.lineedit_program_8->setText("null");
	}
}

