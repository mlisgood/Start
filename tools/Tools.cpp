#include "define.h"

namespace rem
{

	//全局变量定义
	extern int counter_mutex = 1;//只允许创建1个计时器窗口。注意使用全局变量时，不管是声明还是定义都不能在头文件中，并且需要用extern。全局变量只能定义1次，也就是赋初值1次，但需要用到其的文件中均需声明。
	extern int sound_record_mutex = 1;//只允许创建1个录音窗口
	
	//导入标准命名空间
	using std::string;
	using std::wstring;

	Tools::Tools(QWidget *parent) : QMainWindow(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint | windowFlags());//去掉窗口标题栏，并且任务栏中不会出现窗口，窗口始终在最顶层
		on_top = true;//窗口始终在顶层
		is_hide = false;//窗口处于常规状态未被隐藏
		screenshot_end_mouse_event_disable = false;//没有屏蔽鼠标点击事件
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, true);//该窗口关闭时会退出程序
		setAttribute(Qt::WA_WState_WindowOpacitySet, true);//该窗口允许直接设置透明度
		is_escape_pressed = false;//默认未按下esc键以退出
		QSettings *begin_read = new QSettings(FILE_SETTING_MAINWINDOW_STYLE_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		setting_picture_mainpicture= begin_read->value(FILE_SETTING_CATALOG_1_INNER_PATH_STRING).toString();//背景
		setting_function_program[0] = begin_read->value(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING).toString();//运行的程序
		setting_function_program[1] = begin_read->value(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING).toString();
		setting_function_program[2] = begin_read->value(FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING).toString();
		setting_function_program[3] = begin_read->value(FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING).toString();
		setting_function_program[4] = begin_read->value(FILE_SETTING_CATALOG_2_5_INNER_PATH_STRING).toString();
		setting_function_program[5] = begin_read->value(FILE_SETTING_CATALOG_2_6_INNER_PATH_STRING).toString();
		setting_function_program[6] = begin_read->value(FILE_SETTING_CATALOG_2_7_INNER_PATH_STRING).toString();
		setting_function_program[7] = begin_read->value(FILE_SETTING_CATALOG_2_8_INNER_PATH_STRING).toString();
		setting_font_font = begin_read->value(FILE_SETTING_CATALOG_4_INNER_PATH_STRING).toString();//便签窗口字体
		bool status_temp[2];//临时布尔值，判断是否转化成功
		x_position = begin_read->value(FILE_SETTING_CATALOG_5_1_INNER_PATH_STRING).toString().toInt(&status_temp[0], 10);//修改位置
		y_position = begin_read->value(FILE_SETTING_CATALOG_5_2_INNER_PATH_STRING).toString().toInt(&status_temp[1], 10);
		if (status_temp[0] == true && status_temp[1] == true)//若出现转化失败则强制改为0
		{

		}
		else
		{
			x_position = 0;
			y_position = 0;
		}
		move(x_position, y_position);//修改窗口起始坐标
		bool autorun = begin_read->value(FILE_SETTING_CATALOG_3_INNER_PATH_STRING).toBool();//是否开机自启动
		delete begin_read;
		QSettings *begin_read_extra = new QSettings(FILE_SETTING_MAINWINDOW_STYLE_EXTRA_PATH_STRING, QSettings::IniFormat);//读取额外ini文件中的信息
		setting_extra_index[0] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_1_1_INNER_PATH_STRING).toString();//直接将信息全部读入，之后再进行处理
		setting_extra_index[1] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_1_2_INNER_PATH_STRING).toString();
		setting_extra_index[2] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_2_1_INNER_PATH_STRING).toString();
		setting_extra_index[3] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_2_2_INNER_PATH_STRING).toString();
		setting_extra_index[4] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_2_3_INNER_PATH_STRING).toString();
		setting_extra_index[5] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_2_4_INNER_PATH_STRING).toString();
		setting_extra_index[6] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_2_5_INNER_PATH_STRING).toString();
		setting_extra_index[7] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_2_6_INNER_PATH_STRING).toString();
		setting_extra_index[8] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_2_7_INNER_PATH_STRING).toString();
		delete begin_read_extra;
		QString application_name = QApplication::applicationName();//启动悬浮组件时检查是否开机自动启动
		QSettings *regedit_settings_begin = new QSettings(REG_RUN, QSettings::NativeFormat);//修改注册表
		if (autorun == true)//是否自动启动
		{
			QString application_path = QApplication::applicationFilePath();//获得绝对路径
			regedit_settings_begin->setValue(application_name, application_path.replace("/", "\\"));//写入注册表项，注意注册表使用的路径分隔符和QT输出的相反
		}
		else
		{
			regedit_settings_begin->remove(application_name);//删除注册表项
		}
		delete regedit_settings_begin;

		//加载界面
		ui.setupUi(this);

		//图片设置
		if (setting_picture_mainpicture == tr("1"))//根据配置文件读取图片，并且将窗口标题设置为关联项目
		{
			main_picture_normal_hole_path = WINDOW_PICTURE_BACKGROUND_INDEX_1_PATH_STRING;
			setWindowTitle(WINDOW_DIALOG_TITLE_INDEX_1_PATH_STRING);
		}
		else if (setting_picture_mainpicture == tr("2"))
		{
			main_picture_normal_hole_path = WINDOW_PICTURE_BACKGROUND_INDEX_2_PATH_STRING;
			setWindowTitle(WINDOW_DIALOG_TITLE_INDEX_2_PATH_STRING);
		}
		else if (setting_picture_mainpicture == tr("3"))
		{
			main_picture_normal_hole_path = WINDOW_PICTURE_BACKGROUND_INDEX_3_PATH_STRING;
			setWindowTitle(WINDOW_DIALOG_TITLE_INDEX_3_PATH_STRING);
		}
		else if (setting_picture_mainpicture == tr("4"))
		{
			main_picture_normal_hole_path = WINDOW_PICTURE_BACKGROUND_INDEX_4_PATH_STRING;
			setWindowTitle(WINDOW_DIALOG_TITLE_INDEX_4_PATH_STRING);
		}
		else
		{
			main_picture_normal_hole_path = WINDOW_PICTURE_BACKGROUND_INDEX_1_PATH_STRING;
			setWindowTitle(WINDOW_DIALOG_TITLE_INDEX_1_PATH_STRING);
		}
		if (setting_extra_index[1] == tr("150*250"))
		{
			main_picture_normal_hole_path += WINDOW_PICTURE_BACKGROUND_INDEX_1_MIDDLE_PATH_STRING;
		}
		else if (setting_extra_index[1] == tr("100*167"))
		{
			main_picture_normal_hole_path += WINDOW_PICTURE_BACKGROUND_INDEX_2_MIDDLE_PATH_STRING;
		}
		else if (setting_extra_index[1] == tr("75*125"))
		{
			main_picture_normal_hole_path += WINDOW_PICTURE_BACKGROUND_INDEX_3_MIDDLE_PATH_STRING;
		}
		else if (setting_extra_index[1] == tr("50*83"))
		{
			main_picture_normal_hole_path += WINDOW_PICTURE_BACKGROUND_INDEX_4_MIDDLE_PATH_STRING;
		}
		else
		{
			main_picture_normal_hole_path += WINDOW_PICTURE_BACKGROUND_INDEX_2_MIDDLE_PATH_STRING;
		}
		main_picture_normal_hole_path += WINDOW_PICTURE_BACKGROUND_INDEX_PATH_BACK_STRING;
		main_picture.load(main_picture_normal_hole_path);
		resize(main_picture.size());//窗口大小改为图片大小
		if (setting_extra_index[4] == tr("（特別）ココアとチノ"))//设置隐藏图片
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_1_PATH_STRING;
		}
		else if (setting_extra_index[4] == tr("（特別）ティッピー"))
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_2_PATH_STRING;
		}
		else if (setting_extra_index[4] == tr("（特別）なし"))
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_3_PATH_STRING;
		}
		else if (setting_extra_index[4] == tr("（普通）魔法少女　チノ"))
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_4_PATH_STRING;
		}
		else if (setting_extra_index[4] == tr("（普通）ソーサラー　チノ"))
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_5_PATH_STRING;
		}
		else if (setting_extra_index[4] == tr("（普通）ガンナー　マヤ"))
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_6_PATH_STRING;
		}
		else if (setting_extra_index[4] == tr("（普通）バーサーカー　メグ"))
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_7_PATH_STRING;
		}
		else
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_1_PATH_STRING;
		}
		if (setting_extra_index[5] == tr("「普通」为150*250，「特別」为100*100"))
		{
			main_picture_hide_hole_path += WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_1_MIDDLE_PATH_STRING;
		}
		else if (setting_extra_index[5] == tr("「普通」为100*167，「特別」为75*75"))
		{
			main_picture_hide_hole_path += WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_2_MIDDLE_PATH_STRING;
		}
		else if (setting_extra_index[5] == tr("「普通」为75*125，「特別」为50*50"))
		{
			main_picture_hide_hole_path += WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_3_MIDDLE_PATH_STRING;
		}
		else if (setting_extra_index[5] == tr("「普通」为50*83，「特別」为25*25"))
		{
			main_picture_hide_hole_path += WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_4_MIDDLE_PATH_STRING;
		}
		else
		{
			main_picture_hide_hole_path += WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_3_MIDDLE_PATH_STRING;
		}
		main_picture_hide_hole_path += WINDOW_PICTURE_BACKGROUND_INDEX_PATH_BACK_STRING;

		//设置透明度
		bool transform_transparent_temp;//转化是否成功的临时判断量
		animation_transparent_number = setting_extra_index[0].toInt(&transform_transparent_temp, 10);//窗口初始透明度从配置文件读取
		animation_transparent_number /= 10;
		if (!transform_transparent_temp)
		{
			animation_transparent_number = 1;
		}
		else
		{

		}
		setWindowOpacity(animation_transparent_number);
		animation_transparent_hide_number = setting_extra_index[8].toInt(&transform_transparent_temp, 10);//隐藏窗口时窗口透明度
		animation_transparent_hide_number /= 10;
		if (!transform_transparent_temp)
		{
			animation_transparent_hide_number = 1;
		}
		else
		{

		}

		//设置计时器间隔
		bool transform_timer_temp;//转化是否成功的临时判断量
		timer_interval_number = setting_extra_index[3].toInt(&transform_timer_temp, 10)*1000;//计时器间隔，注意单位是毫秒
		if (!transform_timer_temp)
		{
			timer_interval_number = 1;
		}
		else
		{

		}
		
		//设置隐藏窗口位置
		bool position_temp[2];//临时布尔值，判断是否转化成功
		extra_x_position = setting_extra_index[6].toInt(&position_temp[0], 10);
		extra_y_position = setting_extra_index[7].toInt(&position_temp[1], 10);
		if (position_temp[0] == true && position_temp[1] == true)
		{

		}
		else
		{
			extra_x_position = 0;
			extra_y_position = 0;
		}

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(animation_transparent_number);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存

		//将窗口加载入系统托盘
		system_tray_icon = new QSystemTrayIcon(this);
		QIcon icon_picture = QIcon(PROGRAM_SYSTEM_TRAY_ICON_PATH_STRING);
		system_tray_icon->setIcon(icon_picture);//图标
		system_tray_icon->setToolTip(PROGRAM_SYSTEM_TRAY_TIP_STRING);//提示
		create_system_tray_menu_action();//添加菜单功能，因为添加菜单中需要添加动作因此必须先添加动作再添加菜单，否则会因为添加菜单时还没有为动作分配内存空间而出错
		create_system_tray_menu();//添加菜单
		system_tray_icon->show();//显示托盘
		connect(system_tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(system_tray_icon_clicked(QSystemTrayIcon::ActivationReason)));//托盘信号函数
	
		//计时器处理
		time_counter = new QTimer(this);//创建一个定时器，因为之后有释放函数，因此即使不使用也需要申请一个
		time_counter->setTimerType(Qt::PreciseTimer);//修改精度
		if (setting_extra_index[2] == tr("1"))//启用不点击隐藏功能后才能使用
		{
			time_counter->setInterval(timer_interval_number);//设置计时间隔
			time_counter->start();//初始时候需要启动计时器
			connect(time_counter, SIGNAL(timeout()), this, SLOT(time_hide_animation_disappear()));//计时器到期处理，改变图片
		}
		else
		{

		}
	}

	Tools::~Tools()
	{
		delete system_tray_icon;
		delete system_tray_menu;
		delete action_set;
		delete action_set_extra;
		delete action_set_sound_record;
		delete action_help;
		delete action_exit;
		delete time_counter;
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标。此外，隐藏部件的处理也在此处进行
	void Tools::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bPressed = true;
			m_point = event->pos();
		}
		else
		{

		}
		if (setting_extra_index[2] == tr("1"))//启用不点击隐藏功能后才能使用
		{
			time_counter->stop();//停止计时器，只有鼠标释放之后才重新开始计时，防止移动过程中隐藏的情况出现
			if (is_hide && !screenshot_end_mouse_event_disable)//窗口被隐藏，并且不处于截图完毕的时候，需要显示
			{
				is_hide = false;//屏蔽鼠标点击显示事件
				QPropertyAnimation *animation_show_disappear = new QPropertyAnimation(this, "windowOpacity");//隐藏窗口消失动画
				animation_show_disappear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
				animation_show_disappear->setStartValue(animation_transparent_hide_number);
				animation_show_disappear->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
				animation_show_disappear->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
				connect(animation_show_disappear, SIGNAL(finished()), this, SLOT(show_animation_appear()));
			}
			else//未被隐藏，不接收点击显示事件
			{

			}
		}
		else
		{

		}
		
	}

	//若鼠标左键被按下，则移动窗体位置
	void Tools::mouseMoveEvent(QMouseEvent *event)
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
	void Tools::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
		if (setting_extra_index[2] == tr("1"))//启用不点击隐藏功能后才能使用
		{
			time_counter->start();//重新开始计时
		}
		else
		{

		}
	}

	//绘制事件
	void Tools::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(WINDOW_BACKGROUND_PAINT_START_X_NUMBER, WINDOW_BACKGROUND_PAINT_START_Y_NUMBER, main_picture);//画图作为窗口背景
	}

	//键盘事件，用于响应快捷键
	void Tools::keyPressEvent(QKeyEvent *event)
	{

		//ctrl和字母键的组合，先按下字母键再按下ctrl则无效。设置8个关联程序功能
		if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_1))
		{
			run_program(1);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_2))
		{
			run_program(2);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_3))
		{
			run_program(3);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_4))
		{
			run_program(4);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_5))
		{
			run_program(5);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_6))
		{
			run_program(6);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_7))
		{
			run_program(7);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_8))
		{
			run_program(8);
		}

		//截图功能
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_S))
		{
			Screenshot dialog;//创建用于截图的窗口
			connect(&dialog, &Screenshot::finish, this, &Tools::screenshot_success);//截图成功，发出信号并返回。这种格式的信号传值主要用于不同文件之间的传递
			connect(&dialog, &Screenshot::close_window, this, &Tools::screenshot_fail);//截图失败，发出信号并返回。这种格式的信号传值主要用于不同文件之间的传递
			QPropertyAnimation *animation_hide = new QPropertyAnimation(this, "windowOpacity");
			animation_hide->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
			if (is_hide == true)
			{
				animation_hide->setStartValue(animation_transparent_hide_number);
			}
			else
			{
				animation_hide->setStartValue(animation_transparent_number);
			}
			animation_hide->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
			animation_hide->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
			connect(animation_hide, SIGNAL(finished()), this, SLOT(hide()));//隐藏窗口
			dialog.exec();
		}

		//计时器功能
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_C))
		{
			if (counter_mutex == 1)
			{
				CounterSet dialog;//创建计时器设置
				dialog.exec();
			}
			else
			{

			}
		}

		//便签功能
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_E))
		{
			Note *dialog = new Note;//创建便签
			dialog->set_font(setting_font_font);//传入字体
			dialog->setModal(false);//指定为非模态对话框
			dialog->show();
		}

		//录音功能
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_D))
		{
			if (sound_record_mutex == 1)
			{
				SoundRecord *dialog = new SoundRecord;//录音窗口采用非模态窗口
				dialog->setModal(false);//指定为非模态对话框
				dialog->show();
			}
			else
			{

			}
		}

		//关机功能
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_U))
		{
			bool shut_down_success = shutdown_or_reboot(1);//执行关机操作
			if (!shut_down_success)
			{
				Help dialog;//信息提示框
				dialog.setWindowTitle(tr("失败了！"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_SHUTDOWN_OR_RESTART_PATH_STRING);//提示信息
				dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
			}
			else
			{

			}
		}

		//重启功能
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_R))
		{
			bool shut_down_success = shutdown_or_reboot(2);//执行重启操作
			if (!shut_down_success)
			{
				Help dialog;//信息提示框
				dialog.setWindowTitle(tr("失败了！"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_SHUTDOWN_OR_RESTART_PATH_STRING);//提示信息
				dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
			}
			else
			{

			}
		}

		//退出功能
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

	//系统托盘
	void Tools::create_system_tray_menu()//系统托盘菜单
	{
		system_tray_menu = new QMenu(this);
		system_tray_menu->addAction(action_set);//添加设置功能
		system_tray_menu->addAction(action_set_extra);//添加高级设置功能
		system_tray_menu->addAction(action_set_sound_record);//添加录音设置功能
		system_tray_menu->addSeparator();//增加分隔符
		system_tray_menu->addAction(action_help);//添加信息功能
		system_tray_menu->addSeparator();//增加分隔符
		system_tray_menu->addAction(action_exit);//添加退出功能
		system_tray_icon->setContextMenu(system_tray_menu);//把菜单赋给托盘图标
	}

	void Tools::create_system_tray_menu_action()//系统托盘菜单功能
	{
		action_set = new QAction(QObject::tr("基本设置   "), this);//设置功能
		connect(action_set, SIGNAL(triggered()), this, SLOT(show_system_tray_action_set()));
		action_set_extra = new QAction(QObject::tr("高级设置   "), this);//设置功能
		connect(action_set_extra, SIGNAL(triggered()), this, SLOT(show_system_tray_action_set_extra()));
		action_set_sound_record = new QAction(QObject::tr("录音设置   "), this);//设置功能
		connect(action_set_sound_record, SIGNAL(triggered()), this, SLOT(show_system_tray_action_set_sound_record()));
		action_help = new QAction(QObject::tr("程序信息   "), this);//信息功能
		connect(action_help, SIGNAL(triggered()), this, SLOT(show_system_tray_action_help()));
		action_exit = new QAction(QObject::tr("退出程序   "), this);//退出功能
		connect(action_exit, SIGNAL(triggered()), this, SLOT(show_system_tray_action_exit()));
	}

	//槽函数
	void Tools::system_tray_icon_clicked(QSystemTrayIcon::ActivationReason reason)
	{
		switch (reason)
		{
		case QSystemTrayIcon::Trigger://单击托盘显示菜单
				
			break;
				
		case QSystemTrayIcon::DoubleClick://窗口是否在始终顶部的切换

			if (on_top == false)
			{
				setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);//窗口总是显示在最前面
				on_top = true;
			}
			else
			{
				setWindowFlags(windowFlags()&~Qt::WindowStaysOnTopHint);//窗口不会总是显示在最前面
				on_top = false;
			}
			show();//如果不加上这一句会出问题，比如窗口永远无法显示
			break;

		default:

			break;
		}
	}

	void Tools::show_system_tray_action_set()//系统托盘菜单设置功能
	{
		ToolsSet dialog;//修改配置文件
		dialog.exec();
	}

	void Tools::show_system_tray_action_set_extra()//系统托盘菜单高级设置功能
	{
		ToolsSetExtra dialog;//修改配置文件
		dialog.exec();
	}

	void Tools::show_system_tray_action_set_sound_record()//系统录音菜单高级设置功能
	{
		SoundRecordSet dialog;//修改配置文件
		dialog.exec();
	}

	void Tools::show_system_tray_action_help()//系统托盘菜单信息功能
	{
		Help dialog;//显示程序信息
		dialog.set_dialog_information_path(DIALOG_INFORMATION_HELP_PATH_STRING);
		dialog.exec();
	}

	void Tools::show_system_tray_action_exit()//系统托盘菜单退出功能
	{
		close_window_include_animation();//关闭窗口并退出程序
	}

	void Tools::screenshot_fail()//截图失败
	{
		show();//先显示再播放动画
		screenshot_end_mouse_event_disable = true;//屏蔽鼠标点击悬浮组件后悬浮组件切换到显示状态的事件，否则在悬浮组件隐藏之前会出现点击悬浮组件，悬浮组件先消失然后出现的现象
		setWindowOpacity(animation_transparent_number);//透明度强制改为主界面透明度
		main_picture.load(main_picture_normal_hole_path);//强制将主界面背景改为未隐藏状态
		resize(main_picture.size());
		move(extra_x_position, extra_y_position);//修改窗口起始坐标
		update();
		QPropertyAnimation *animation_show = new QPropertyAnimation(this, "windowOpacity");
		animation_show->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_show->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_show->setEndValue(animation_transparent_number);
		animation_show->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		time_counter->stop();//不论之前动画播放情况如何，都强制重新运行动画计时器，如果不这样做在设置了悬浮组件自动隐藏后会出现在悬浮组件隐藏时截图，截完图后悬浮组件不能隐藏的问题
		time_counter->start();
	}

	void Tools::screenshot_success(QPoint pt1, QPoint pt2)//截图成功，参数来自于发出的信号
	{

		//保存截图。由于存在负数坐标的情况，需要分别处理。起始点坐标不可能是负数，但结束点有可能是负数。注意QPixmap始终用左上角的点作为矩形的起始点
		if ((pt2.x() - pt1.x()) > 1 && (pt2.y() - pt1.y()) > 1)//以起始点为原点。因为屏幕的坐标是按照左上角为原点开始计算的，y轴是向下为正的，这里也按照这种方式处理。需要同时考虑因为边框被去掉的1个像素（不是2个，因为矩形绘制终点没有包含终点在内的那一圈像素）。先去掉两者有坐标相差的绝对值小于等于2的情况，之后处理。因为函数本身的关系，需要增加1像素的修正。第一象限：不需特殊处理
		{
			screenshot_picture = QPixmap::grabWindow(QApplication::desktop()->winId(), pt1.x() + 1, pt1.y() + 1, pt2.x() - pt1.x() - 2 + 1, pt2.y() - pt1.y() - 2 + 1);//加载截图图片，这里因为要去掉截图边框所以截图宽度减少了2像素
			QClipboard *clipborder = QApplication::clipboard();//将截图写入剪贴板
			clipborder->setPixmap(screenshot_picture);
		}
		else if ((pt2.x() - pt1.x()) < -1 && (pt2.y() - pt1.y()) < -1)//第三象限：原起始点和终止点的两个坐标的位置与第一象限的情况相反，因此将两个点的坐标互换
		{
			screenshot_picture = QPixmap::grabWindow(QApplication::desktop()->winId(), pt2.x() + 1, pt2.y() + 1, pt1.x() - pt2.x() - 2 + 1, pt1.y() - pt2.y() - 2 + 1);
			QClipboard *clipborder = QApplication::clipboard();
			clipborder->setPixmap(screenshot_picture);
		}
		else if ((pt2.x() - pt1.x()) > 1 && (pt2.y() - pt1.y()) < -1)//第二象限：需要重新选择起始点。左上角的点的坐标是：(pt1.x(),pt2.y())
		{
			screenshot_picture = QPixmap::grabWindow(QApplication::desktop()->winId(), pt1.x() + 1, pt2.y() + 1, pt2.x() - pt1.x() - 2 + 1, pt1.y() - pt2.y() - 2 + 1);
			QClipboard *clipborder = QApplication::clipboard();
			clipborder->setPixmap(screenshot_picture);
		}
		else if ((pt2.x() - pt1.x()) < -1 && (pt2.y() - pt1.y()) > 1)//第四象限：需要重新选择起始点。左上角的点的坐标是：(pt2.x(),pt1.y())
		{
			screenshot_picture = QPixmap::grabWindow(QApplication::desktop()->winId(), pt2.x() + 1, pt1.y() + 1, pt1.x() - pt2.x() - 2 + 1, pt2.y() - pt1.y() - 2 + 1);
			QClipboard *clipborder = QApplication::clipboard();
			clipborder->setPixmap(screenshot_picture);
		}
		else//余下的情况一定不能截到图，直接按失败处理
		{

		}
		show();//先显示再播放动画
		screenshot_end_mouse_event_disable = true;//屏蔽鼠标点击悬浮组件后悬浮组件切换到显示状态的事件，否则在悬浮组件隐藏之前会出现点击悬浮组件，悬浮组件先消失然后出现的现象
		setWindowOpacity(animation_transparent_number);//透明度强制改为主界面透明度
		main_picture.load(main_picture_normal_hole_path);//强制将主界面背景改为未隐藏状态
		resize(main_picture.size());
		move(extra_x_position, extra_y_position);//修改窗口起始坐标
		update();
		QPropertyAnimation *animation_show = new QPropertyAnimation(this, "windowOpacity");
		animation_show->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_show->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_show->setEndValue(animation_transparent_number);
		animation_show->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		time_counter->stop();//不论之前动画播放情况如何，都强制重新运行动画计时器，如果不这样做在设置了悬浮组件自动隐藏后会出现在悬浮组件隐藏时截图，截完图后悬浮组件不能隐藏的问题
		time_counter->start();
	}

	void Tools::close_and_exit()//和带动画关闭窗口方法一起使用
	{
		close();
		delete system_tray_icon;//使用exit()之后，系统不会调用析构函数，因此必须自行销毁
		delete system_tray_menu;
		delete action_set;
		delete action_set_extra;
		delete action_help;
		delete action_exit;
		delete time_counter;
		exit(0);
	}

	//其他功能
	void Tools::run_program(int index)//运行外部程序。该函数不需要考虑入口函数的参数数目，不论是选择程序本体（1个入口参数）还是程序目标（2个入口参数）都能直接打开
	{
		HINSTANCE return_value;//指定返回值
		wstring transform_path= setting_function_program[index - 1].toStdWString();//将Qstring转化为wstring，这样转化不会导致乱码
		return_value = ShellExecute(NULL, L"open", transform_path.c_str(), NULL, NULL, SW_SHOWNORMAL);//打开程序
		if (setting_function_program[index - 1] != FILE_SETTING_CATALOG_2_UNDEFINE_DEFAULT_STRING)
		{
			if (return_value >= (HINSTANCE)0 && return_value <= (HINSTANCE)31)//无法打开指定程序
			{
				Help dialog;//信息提示框
				dialog.setWindowTitle(tr("程序失踪了！"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_START_PROGRAM_PATH_STRING);//提示信息
				dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
			}
			else if (return_value >= (HINSTANCE)32)//已经打开，正常运行
			{

			}
			else//其他异常情况
			{

			}
		}
	}

	bool Tools::shutdown_or_reboot(int status)//关机或重启
	{
		HANDLE flag_get;
		TOKEN_PRIVILEGES privilege_get;
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &flag_get))//获取进程标志，获取失败则退出函数
		{
			return false;
		}
		else
		{

		}
		if (status == 1)
		{

		}
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privilege_get.Privileges[0].Luid);//获取关机特权的LUID
		privilege_get.PrivilegeCount = 1;
		privilege_get.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(flag_get, false, &privilege_get, 0, (PTOKEN_PRIVILEGES)NULL, 0);//获取这个进程的关机特权
		if (GetLastError() != ERROR_SUCCESS)
		{
			return false;
		}
		else
		{

		}
		if (status == 1)
		{
			if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0))//关闭计算机
			{
				return false;
			}
			else
			{
				close_window_include_animation();
				return true;
			}
		}
		else if (status == 2)
		{
			if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0))//重启计算机
			{
				return false;	
			}
			else
			{
				close_window_include_animation();
				return true;
			}
		}
		else
		{
			if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0))//关闭计算机
			{
				return false;
			}
			else
			{
				close_window_include_animation();
				return true;
			}
		}
	}

	void Tools::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
	{

		//禁用所有按钮，否则动画播放完毕前再次点击按钮会重新触发动画
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(false);
		}
		QPropertyAnimation *animation_close = new QPropertyAnimation(this, "windowOpacity");
		animation_close->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//窗口关闭动画效果
		if (is_hide == true)
		{
			animation_close->setStartValue(animation_transparent_hide_number);
		}
		else
		{
			animation_close->setStartValue(animation_transparent_number);
		}
		animation_close->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_close->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		connect(animation_close, SIGNAL(finished()), this, SLOT(close_and_exit()));
	}

	void Tools::time_hide_animation_disappear()//隐藏过程计时器到期消失动画播放
	{
		QPropertyAnimation *animation_hide_disappear = new QPropertyAnimation(this, "windowOpacity");//主窗口消失动画
		animation_hide_disappear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_hide_disappear->setStartValue(animation_transparent_number);
		animation_hide_disappear->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_hide_disappear->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		connect(animation_hide_disappear, SIGNAL(finished()), this, SLOT(time_hide_animation_appear()));
	}

	void Tools::time_hide_animation_appear()//隐藏过程计时器到期出现动画播放
	{
		main_picture.load(main_picture_hide_hole_path);//先画好背景，然后播放动画
		resize(main_picture.size());
		move(extra_x_position, extra_y_position);//修改窗口起始坐标
		update();
		setWindowOpacity(animation_transparent_hide_number);
		QPropertyAnimation *animation_hide_appear = new QPropertyAnimation(this, "windowOpacity");//主窗口消失动画
		animation_hide_appear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_hide_appear->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_hide_appear->setEndValue(animation_transparent_hide_number);
		animation_hide_appear->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		connect(animation_hide_appear, SIGNAL(finished()), this, SLOT(time_hide_repaint()));
	}

	void Tools::time_hide_repaint()//隐藏过程计时器到期绘制窗口函数
	{
		time_counter->stop();//必须关闭计时器，否则会继续循环计时
		is_hide = true;//设置为主窗口被隐藏，可以继续接收点击显示事件
		screenshot_end_mouse_event_disable = false;//允许接收鼠标点击事件
	}

	void Tools::show_animation_appear()//显示过程出现动画播放
	{
		main_picture.load(main_picture_normal_hole_path);//同样需要先画出背景，之后再显示动画
		resize(main_picture.size());
		move(x_position, y_position);//修改窗口起始坐标
		update();
		setWindowOpacity(animation_transparent_number);
		QPropertyAnimation *animation_show_appear = new QPropertyAnimation(this, "windowOpacity");//主窗口消失动画
		animation_show_appear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_show_appear->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_show_appear->setEndValue(animation_transparent_number);
		animation_show_appear->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}
}

