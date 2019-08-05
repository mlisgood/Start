#include "define.h"

namespace rem
{

	//使用标准命名空间
	using std::string;
	using std::wstring;
	using std::ifstream;
	using std::ofstream;
	using std::fstream;
	using std::ios_base;

	//构造与析构函数
	Set::Set(QWidget *parent) : QDialog(parent)
	{
		
		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		is_escape_pressed = false;//默认未按下esc键以退出

		//加载图片作为窗口背景
		main_picture.load(DIALOG_BACKGROUND_SET_PATH_STRING);
		resize(main_picture.size());//窗口大小改为图片大小

		//加载界面
		ui.setupUi(this);
		
		//设置按钮样式
		ui.pushButton_1->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_7.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_7.png);}");
		ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_7.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_7.png);}");
		ui.pushButton_3->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_7.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_7.png);}");
		ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_8.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_8.png);}");
		ui.pushButton_5->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_7.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_7.png);}");
		ui.pushButton_6->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_9.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_9.png);}");
		ui.pushButton_7->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_10.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_10.png);}");
		ui.pushButton_8->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_11.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_11.png);}");

		//设置文字颜色
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::WindowText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::Highlight, QColor(70, 28, 10, 64));
		ui.lineEdit_1->setPalette(text_palette);
		ui.lineEdit_2->setPalette(text_palette);
		ui.lineEdit_3->setPalette(text_palette);
		ui.lineEdit_4->setPalette(text_palette);
		ui.lineEdit_5->setPalette(text_palette);
		ui.lineEdit_6->setPalette(text_palette);
		ui.lineEdit_7->setPalette(text_palette);
		ui.lineEdit_8->setPalette(text_palette);
		
		//读取预置内容，对窗口显示进行初始化
		QSettings *begin_read = new QSettings(FILE_SET_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		QString information_temp[11];//读取需要显示的内容
		information_temp[0] = begin_read->value(FILE_SETTING_CATALOG_1_1_INNER_PATH_STRING).toString();//文件夹路径
		information_temp[1] = begin_read->value(FILE_SETTING_CATALOG_1_2_INNER_PATH_STRING).toString();
		information_temp[2] = begin_read->value(FILE_SETTING_CATALOG_1_3_INNER_PATH_STRING).toString();
		information_temp[3] = begin_read->value(FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING).toString();
		for (int index = 0; index <= 3; index++)//处理配置文件丢失的情况
		{
			if (information_temp[index].length() == 0)
			{
				information_temp[index] = FILE_SETTING_CATALOG_PATH_DEFAULT_STRING;
			}
			else
			{

			}
		}
		ui.lineEdit_5->setText(information_temp[0]);
		ui.lineEdit_6->setText(information_temp[1]);
		ui.lineEdit_7->setText(information_temp[2]);
		ui.lineEdit_8->setText(information_temp[3]);
		information_temp[4] = begin_read->value(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING).toString();//生成文件后缀
		information_temp[5] = begin_read->value(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING).toString();
		if (information_temp[4].length() == 0)
		{
			information_temp[4] = FILE_SETTING_SUFFIX_LOCK_DEFAULT_STRING;
		}
		else
		{

		}
		if (information_temp[5].length() == 0)
		{
			information_temp[5] = FILE_SETTING_SUFFIX_UNLOCK_DEFAULT_STRING;
		}
		else
		{

		}
		ui.lineEdit_1->setText(information_temp[4]);
		ui.lineEdit_2->setText(information_temp[5]);
		information_temp[6] = begin_read->value(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING).toString();//布尔值
		information_temp[7] = begin_read->value(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING).toString();
		information_temp[8] = begin_read->value(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING).toString();
		if (information_temp[6] == "0")
		{
			ui.checkBox1->setChecked(false);
		}
		else//顺带处理没有配置文件的情况
		{
			ui.checkBox1->setChecked(true);
		}
		if (information_temp[7] == "0")
		{
			ui.checkBox2->setChecked(false);
		}
		else//顺带处理没有配置文件的情况
		{
			ui.checkBox2->setChecked(true);
		}
		if (information_temp[8] == "0")
		{
			ui.checkBox3->setChecked(false);
		}
		else//顺带处理没有配置文件的情况
		{
			ui.checkBox3->setChecked(true);
		}
		information_temp[9] = begin_read->value(FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING).toString();//密钥文件文件后缀
		information_temp[10] = begin_read->value(FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING).toString();
		if (information_temp[9].length() == 0)
		{
			information_temp[9] = FILE_OUTPUT_FILE_KEY_BACK_PATH_STRING;
		}
		else
		{

		}
		if (information_temp[10].length() == 0)
		{
			information_temp[10] = FILE_OUTPUT_FILE_KEY_BINARY_BACK_PATH_STRING;
		}
		else
		{

		}
		ui.lineEdit_3->setText(information_temp[9]);
		ui.lineEdit_4->setText(information_temp[10]);
		delete begin_read;

		//信号函数
		connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(open_path_lock()));//打开加密文件路径
		connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(open_path_unlock()));//打开解密文件路径
		connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(open_path_temp()));//打开临时文件路径
		connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(delete_temp()));//删除临时文件
		connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(open_path_history()));//打开历史文件路径
		connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(delete_history()));//清空历史文件
		connect(ui.pushButton_9, SIGNAL(clicked()), this, SLOT(get_path_lock()));//获得加密文件路径输入
		connect(ui.pushButton_10, SIGNAL(clicked()), this, SLOT(get_path_unlock()));//获得解密文件路径输入
		connect(ui.pushButton_11, SIGNAL(clicked()), this, SLOT(get_path_temp()));//获得临时文件路径输入
		connect(ui.pushButton_12, SIGNAL(clicked()), this, SLOT(get_path_history()));//获得临时文件路径输入
		connect(ui.pushButton_7, SIGNAL(clicked()), this, SLOT(set_apply()));//设置生效
		connect(ui.pushButton_8, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//关闭窗口

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}

	Set::~Set()
	{

	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void Set::mousePressEvent(QMouseEvent *event)
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
	void Set::mouseMoveEvent(QMouseEvent *event)
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
	void Set::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void Set::keyPressEvent(QKeyEvent *event)
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

	void Set::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//画图作为窗口背景
	}

	//其他功能函数
	bool Set::delete_files(QString path)//删除文件夹下全部文件，不包括文件夹。参数为文件夹路径
	{
		if (path.isEmpty())//空字符串
		{
			return false;
		}
		else
		{

		}
		QDir remove_dir(path);//获得对应文件夹路径
		if (!remove_dir.exists())//路径不存在
		{
			return false;
		}
		else
		{

		}
		remove_dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);//设置过滤器
		QFileInfoList file_remove_list = remove_dir.entryInfoList();//获取所有的文件信息
		foreach(QFileInfo file, file_remove_list)//遍历文件信息
		{
			if (file.isFile())//如果是文件，则删除
			{
				file.dir().remove(file.fileName());
			}
			else//否则是文件夹，不做处理
			{
				
			}
		}
		return true;
	}

	//槽函数
	void Set::open_path_lock()//打开加密文件路径
	{
		run_path(ui.lineEdit_5->text(), FILE_OUTPUT_FILE_LOCK_FRONT_PATH_STRING);
	}

	void Set::open_path_unlock()//打开解密文件路径
	{
		run_path(ui.lineEdit_6->text(), FILE_OUTPUT_FILE_UNLOCK_FRONT_PATH_STRING);
	}

	void Set::open_path_temp()//打开临时文件路径
	{
		run_path(ui.lineEdit_7->text(), FILE_TEMP_FILE_FRONT_PATH_STRING);
	}

	void Set::open_path_history()//打开历史文件路径
	{
		run_path(ui.lineEdit_8->text(), FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING);
	}

	void Set::get_path_lock()//获得加密文件路径输入
	{
		set_save_path(ui.lineEdit_5);//获取文件路径并修改label显示
	}

	void Set::get_path_unlock()//获得解密文件路径输入
	{
		set_save_path(ui.lineEdit_6);//获取文件路径并修改label显示
	}

	void Set::get_path_temp()//获得临时文件路径输入
	{
		set_save_path(ui.lineEdit_7);//获取文件路径并修改label显示
	}

	void Set::get_path_history()//获得历史文件路径输入
	{
		set_save_path(ui.lineEdit_8);//获取文件路径并修改label显示
	}

	void Set::delete_temp()//删除临时文件
	{
		QString temp_path = ui.lineEdit_7->text();//临时文件夹路径
		if (temp_path == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)//默认路径
		{
			temp_path = FILE_TEMP_FILE_FRONT_PATH_STRING;
		}
		else
		{
			
		}
		if (delete_files(temp_path))//删除成功
		{
			
		}
		else
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("出错了！"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_DELETE_FAIL_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
	}

	void Set::delete_history()//清空历史文件
	{
		QString full_history_path = ui.lineEdit_8->text();//历史文件路径
		if (full_history_path != FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
		{
			full_history_path += FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING;
		}
		else
		{
			full_history_path = FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING;
			full_history_path += FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING;//不能直接相加。字符串常量相当于指针，如果相加会报错：不能添加两个指针
		}
		string full_history_path_string = string((const char *)full_history_path.toLocal8Bit());//QString转string
		ofstream keyfile(full_history_path_string, ios_base::out | ios_base::beg);//打开历史文件，然后直接关闭，这个函数会自动把文件内容清空
		keyfile << "";//给文件写一个空的字符串
		keyfile.close();
	}

	void Set::run_path(QString path, QString default_path)//打开相应路径。该函数不需要考虑入口函数的参数数目，不论是选择程序本体（1个入口参数）还是程序目标（2个入口参数）都能直接打开。参数是文件路径和默认路径
	{
		HINSTANCE return_value;//指定返回值
		wstring transform_path;//指定传入的具体路径
		if (path != FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)//不是默认值
		{
			transform_path = path.toStdWString();//将Qstring转化为wstring，这样转化不会导致乱码，因为wstring本身就支持Unicode编码
		}
		else
		{
			transform_path = default_path.toStdWString();
		}
		return_value = ShellExecute(NULL, L"open", transform_path.c_str(), NULL, NULL, SW_SHOWNORMAL);//打开程序
		if (return_value >= (HINSTANCE)0 && return_value <= (HINSTANCE)31)//无法打开指定程序
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("出错了！"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_OPEN_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else if (return_value >= (HINSTANCE)32)//已经打开，正常运行
		{

		}
		else//其他异常情况
		{

		}
	}

	//路径信息获取
	void Set::set_save_path(QLineEdit *lineEdit)//从文件打开界面获取路径信息，参数为待显示的QLineEdit
	{
		File_only_path dialog;//这个窗口是从Notepad.exe引用的，调用方式比较麻烦
		dialog.setWindowTitle(tr("选择路径"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if (file_information.isFile())//该文件存在
		{
			file_dialog_file_name = file_information.path();//只取文件路径
		}
		else
		{

		}
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		if (change_result)
		{
			QFileInfo file_information(file_dialog_file_name);//获取文件信息
			if (file_information.isFile())//该文件存在
			{
				file_dialog_file_name = file_information.absoluteDir().absolutePath();//只取文件路径
				file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));//获得文件路径
				lineEdit->setText(file_dialog_file_name);//设置显示文本
			}
			else if(!file_information.isDir())
			{
				Help dialog;//信息提示框
				dialog.setWindowTitle(tr("文件或文件路径不存在"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
				dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
			}
			else
			{
				file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));//获得文件路径
				lineEdit->setText(file_dialog_file_name);//设置显示文本
			}
		}
		else
		{

		}
	}

	void Set::set_apply()//设置生效
	{

		//写入ini文件
		QSettings *write_setting = new QSettings(FILE_SET_PATH_STRING, QSettings::IniFormat);
		write_setting->setValue(FILE_SETTING_CATALOG_1_1_INNER_PATH_STRING, ui.lineEdit_5->text());
		write_setting->setValue(FILE_SETTING_CATALOG_1_2_INNER_PATH_STRING, ui.lineEdit_6->text());
		write_setting->setValue(FILE_SETTING_CATALOG_1_3_INNER_PATH_STRING, ui.lineEdit_7->text());
		write_setting->setValue(FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING, ui.lineEdit_8->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING, ui.lineEdit_1->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING, ui.lineEdit_2->text());
		if (ui.checkBox1->isChecked())//根据QCheckBox是否被勾选来确定输出到ini文件的值
		{
			write_setting->setValue(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING, "1");
		}
		else
		{
			write_setting->setValue(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING, "0");
		}
		if (ui.checkBox2->isChecked())
		{
			write_setting->setValue(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING, "1");
		}
		else
		{
			write_setting->setValue(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING, "0");
		}
		if (ui.checkBox3->isChecked())
		{
			write_setting->setValue(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING, "1");
		}
		else
		{
			write_setting->setValue(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING, "0");
		}
		write_setting->setValue(FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING, ui.lineEdit_3->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING, ui.lineEdit_4->text());
		delete write_setting;
		close_window_include_animation();//设置结束
	}

	void Set::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

