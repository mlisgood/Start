#include "define.h"

namespace rem
{

	//全局变量定义
	extern bool widget_mutex[7] = { true,true,true,true,true,true,true };//只允许创建1个子窗口。注意使用全局变量时，不管是声明还是定义都不能在头文件中，并且需要用extern。全局变量只能定义1次，也就是赋初值1次，但需要用到其的文件中均需声明。

	//导入标准命名空间
	using std::wstring;

	//构造和析构函数
	Desktop::Desktop(QWidget *parent) : QMainWindow(parent)
	{
		setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint | windowFlags());//去掉窗口标题栏，并且任务栏中不会出现窗口，窗口始终在最顶层
		resize(WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, true);//该窗口关闭时会退出程序
		setAttribute(Qt::WA_WState_WindowOpacitySet, true);//该窗口允许直接设置透明度
		is_escape_pressed = false;//默认未按下esc键以退出
		is_hide = false;//主界面没有被隐藏
		move_enable = true;//移动时坐标会记录进配置文件

		ui.setupUi(this);

		//修改坐标
		QSettings *setting_dynamic = new QSettings(FILE_SETTING_DYNAMIC_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		position[0] = setting_dynamic->value(FILE_SETTING_DYNAMIC_CATALOG_1_1_INNER_PATH_STRING).toInt();//修正坐标
		position[1] = setting_dynamic->value(FILE_SETTING_DYNAMIC_CATALOG_1_2_INNER_PATH_STRING).toInt();
		delete setting_dynamic;
		if (position[0] < 0 || position[1] < 0)
		{
			position[0] = 0;
			position[1] = 0;
		}
		else
		{

		}
		move(position[0], position[1]);//修改窗口起始坐标

		//静态信息读取
		QSettings *setting_static = new QSettings(FILE_SETTING_STATIC_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		QString temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_1_STRING;
		int is_hide_available_temp = setting_static->value(temp).toInt();
		if (is_hide_available_temp == 1)
		{
			is_hide_available = true;
		}
		else
		{
			is_hide_available = false;
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_2_STRING;
		timer_interval_number = setting_static->value(temp).toInt();
		if (timer_interval_number < 0)
		{
			timer_interval_number = 0;
		}
		else
		{

		}
		timer_interval_number *= 1000;//秒转化为毫秒
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		int is_on_top_temp = setting_static->value(temp).toInt();
		if (is_on_top_temp == 1)
		{
			on_top = true;
		}
		else
		{
			on_top = false;
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_4_STRING;
		transparent = setting_static->value(temp).toDouble();
		if (transparent < 0)
		{
			transparent = 0;
		}
		else
		{

		}
		transparent /= 10;//除以10，按照QT标准使用该透明度
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_5_STRING;
		int auto_run_temp = setting_static->value(temp).toInt();
		autorun = false;//是否自启动
		if (auto_run_temp == 1)
		{
			autorun = true;
		}
		else
		{
			autorun = false;
		}

		//控件属性读取
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER; index++)
		{
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
			int temp_bool = setting_static->value(temp).toInt();
			if (temp_bool == 1)
			{
				widget_is_enable[index] = true;
			}
			else
			{
				widget_is_enable[index] = false;
			}
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
			temp_bool = setting_static->value(temp).toInt();
			if (temp_bool == 1)
			{
				widget_is_on_top[index] = true;
			}
			else
			{
				widget_is_on_top[index] = false;
			}
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_4_STRING;
			widget_transparent[index] = setting_static->value(temp).toInt();
			if (widget_transparent[index] < 0)
			{
				widget_transparent[index] = 0;
			}
			else
			{

			}
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_7_STRING;
			QString temp_path = setting_static->value(temp).toString();
			widget_path[index] = temp_path.toStdWString();//将Qstring转化为wstring，因为wstring就是Unicode字符串，因此这样转化不会导致乱码
		}
		delete setting_static;

		//设置是否在最顶层
		if (on_top)
		{
			setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);//窗口总是显示在最前面
		}
		else
		{
			setWindowFlags(windowFlags()&~Qt::WindowStaysOnTopHint);//窗口不会总是显示在最前面
		}

		//启动组件
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER; index++)
		{
			if (widget_is_enable[index])
			{
				Widget *dialog = new Widget;//非模态窗口
				dialog->set_attribute(widget_is_on_top[index], index, widget_transparent[index], widget_path[index]);//设置初始值
				dialog->setModal(false);//指定为非模态对话框
				dialog->show();
			}
			else
			{

			}
		}

		//开机自启动检查
		QString application_name = QApplication::applicationName();//启动悬浮组件时检查是否开机自动启动
		QSettings *regedit_settings_begin = new QSettings(REG_RUN, QSettings::NativeFormat);//修改注册表
		if (autorun)//是否自动启动
		{
			QString application_path = QApplication::applicationFilePath();//获得绝对路径
			regedit_settings_begin->setValue(application_name, application_path.replace("/", "\\"));//写入注册表项，注意注册表使用的路径分隔符和QT输出的相反
		}
		else
		{
			regedit_settings_begin->remove(application_name);//删除注册表项
		}
		delete regedit_settings_begin;

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(transparent);
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
		if (is_hide_available == true)//启用不点击隐藏功能后才能使用
		{
			time_counter->setInterval(timer_interval_number);//设置计时间隔
			time_counter->start();//初始时候需要启动计时器
			connect(time_counter, SIGNAL(timeout()), this, SLOT(time_hide_animation_disappear()));//计时器到期处理，改变图片
		}
		else
		{

		}

		//加载背景图片
		randnumber = WINDOW_RANDOM_MIN_NUMBER + rand() % (WINDOW_RANDOM_MAX_NUMBER - WINDOW_RANDOM_MIN_NUMBER + 1);//生成一个随机的数字，该数字用来决定主界面的背景。每次显示主界面，这个数字都会发生变化
		background_path = WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING;//临时存储背景图片路径
		background_path += QString::number(randnumber, 10);
		background_path += WINDOW_BACKGROUND_PICTURE_PATH_BACK_STRING;
		background_picture.load(background_path);//加载背景图片
}

	Desktop::~Desktop()
	{
		delete system_tray_icon;
		delete system_tray_menu;
		delete action_static_set;
		delete action_dynamic_set;
		delete action_auto_start_set;
		delete action_help;
		delete action_exit;
		delete time_counter;
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标。此外，隐藏部件的处理也在此处进行
	void Desktop::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bPressed = true;
			m_point = event->pos();
		}
		else
		{

		}
		if (is_hide_available)//启用不点击隐藏功能后才能使用
		{
			time_counter->stop();//停止计时器，只有鼠标释放之后才重新开始计时，防止移动过程中隐藏的情况出现
			if (is_hide)//窗口被隐藏，并且不处于截图完毕的时候，需要显示
			{
				move_enable = false;//禁止记录，否则主界面可能会偏离位置
				is_hide = false;//屏蔽鼠标点击显示事件
				QPropertyAnimation *animation_show_disappear = new QPropertyAnimation(this, "windowOpacity");//隐藏窗口消失动画
				animation_show_disappear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
				animation_show_disappear->setStartValue(transparent);
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

	void Desktop::mouseMoveEvent(QMouseEvent *event)//若鼠标左键被按下，则移动窗体位置
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}

		//获取主界面坐标。在结束之后，将坐标写入动态信息配置文件
		if (move_enable)
		{
			position[0] = this->pos().x();
			position[1] = this->pos().y();
		}
		else
		{

		}
	}

	void Desktop::mouseReleaseEvent(QMouseEvent *event)//鼠标未被按下，则相应变量为false
	{
		Q_UNUSED(event);
		m_bPressed = false;
		if (is_hide_available)//启用不点击隐藏功能后才能使用
		{
			time_counter->start();//重新开始计时
		}
		else
		{

		}

		//释放鼠标后，记录主界面坐标并写入配置文件
		QSettings *write_setting = new QSettings(FILE_SETTING_DYNAMIC_PATH_STRING, QSettings::IniFormat);
		write_setting->setValue(FILE_SETTING_DYNAMIC_CATALOG_1_1_INNER_PATH_STRING, QString::number(position[0], 10));
		write_setting->setValue(FILE_SETTING_DYNAMIC_CATALOG_1_2_INNER_PATH_STRING, QString::number(position[1], 10));
		delete write_setting;
	}


	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void Desktop::keyPressEvent(QKeyEvent *event)
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

		//控件
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_Q))
		{
			key_press_method(0);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_W))
		{
			key_press_method(1);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_E))
		{
			key_press_method(2);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_A))
		{
			key_press_method(3);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_S))
		{
			key_press_method(4);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_D))
		{
			key_press_method(5);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_F))
		{
			key_press_method(6);
		}
		else
		{

		}
	}

	void Desktop::paintEvent(QPaintEvent *)//绘制背景图像
	{
		QPainter background_painter(this);//背景
		background_painter.drawPixmap(0, 0, background_picture.size().width(), background_picture.size().height(), background_picture);//绘制背景图片
	}

	//系统托盘
	void Desktop::create_system_tray_menu()//系统托盘菜单
	{
		system_tray_menu = new QMenu(this);
		system_tray_menu->addAction(action_static_set);//添加设置静态属性功能
		system_tray_menu->addAction(action_dynamic_set);//添加设置动态属性功能
		system_tray_menu->addAction(action_auto_start_set);//添加设置开机自启动功能
		system_tray_menu->addSeparator();//增加分隔符
		system_tray_menu->addAction(action_help);//添加信息功能
		system_tray_menu->addSeparator();//增加分隔符
		system_tray_menu->addAction(action_exit);//添加退出功能
		system_tray_icon->setContextMenu(system_tray_menu);//把菜单赋给托盘图标
	}

	void Desktop::create_system_tray_menu_action()//系统托盘菜单功能
	{
		action_static_set = new QAction(QObject::tr("常规设置   "), this);//设置功能
		connect(action_static_set, SIGNAL(triggered()), this, SLOT(show_system_tray_action_set_static()));
		action_dynamic_set = new QAction(QObject::tr("特殊设置   "), this);//设置功能
		connect(action_dynamic_set, SIGNAL(triggered()), this, SLOT(show_system_tray_action_set_dynamic()));
		action_auto_start_set = new QAction(QObject::tr("其他设置   "), this);//设置功能
		connect(action_auto_start_set, SIGNAL(triggered()), this, SLOT(show_system_tray_action_set_other()));
		action_help = new QAction(QObject::tr("程序信息   "), this);//信息功能
		connect(action_help, SIGNAL(triggered()), this, SLOT(show_system_tray_action_help()));
		action_exit = new QAction(QObject::tr("退出程序   "), this);//退出功能
		connect(action_exit, SIGNAL(triggered()), this, SLOT(show_system_tray_action_exit()));
	}

	//槽函数
	void Desktop::system_tray_icon_clicked(QSystemTrayIcon::ActivationReason reason)
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

	void Desktop::show_system_tray_action_set_static()//菜单常规设置功能
	{
		Setting dialog;//修改配置文件
		dialog.exec();
	}

	void Desktop::show_system_tray_action_set_dynamic()//菜单特殊设置功能
	{
		SettingDynamic dialog;//修改配置文件
		dialog.exec();
	}

	void Desktop::show_system_tray_action_set_other()//菜单开机自启动功能
	{
		SettingOther dialog;//修改配置文件
		dialog.exec();
	}

	void Desktop::show_system_tray_action_help()//系统托盘菜单信息功能
	{
		Help dialog;//显示程序信息
		dialog.set_dialog_information_path(DIALOG_INFORMATION_HELP_PATH_STRING);
		dialog.exec();
	}

	void Desktop::show_system_tray_action_exit()//系统托盘菜单退出功能
	{
		close_window_include_animation();//关闭窗口并退出程序
	}

	void Desktop::time_hide_animation_disappear()//隐藏过程计时器到期消失动画播放
	{
		QPropertyAnimation *animation_hide_disappear = new QPropertyAnimation(this, "windowOpacity");//主窗口消失动画
		animation_hide_disappear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_hide_disappear->setStartValue(transparent);
		animation_hide_disappear->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_hide_disappear->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		connect(animation_hide_disappear, SIGNAL(finished()), this, SLOT(time_hide_animation_appear()));
	}

	void Desktop::time_hide_animation_appear()//隐藏过程计时器到期出现动画播放
	{
	
		//计算隐藏窗口移动的方向。该逻辑是：根据隐藏窗口其离屏幕最近的x和y方向上的距离，取与屏幕总宽度比值最接近的作为x或y方向，隐藏后移动到同样x或y方向上的屏幕边缘处。就是手机悬浮球的逻辑，
		QScreen *screen = QGuiApplication::primaryScreen();//获取分辨率
		QRect rect = screen->availableGeometry();
		screen_resolution[0] = rect.width();
		screen_resolution[1] = rect.height();
		int hidewindow_x;
		int hidewindow_y;
		int mainwindow_x = position[0] + WINDOW_SIZE_WIDTH_NUMBER / 2;//获取主窗口中心点
		int mainwindow_y = position[1] + WINDOW_SIZE_WIDTH_NUMBER / 2;
		double ratio_x = ((double)mainwindow_x - (double)screen_resolution[0] / 2) / ((double)screen_resolution[0] / 2);//取屏幕中心点作为参考，在x方向上，主窗口中心x坐标减去屏幕中心点坐标得到该点离屏幕中心点的x距离，除以屏幕中心点x坐标得到其于屏幕中心点的相对x距离，该值越大，相对x距离越大，该点在x方向上离屏幕边缘越近，同样方法算出y方向上的比值，取较近的作为移动方向
		double ratio_y = ((double)mainwindow_y - (double)screen_resolution[1] / 2) / ((double)screen_resolution[1] / 2);
		double abs_ratio_x = abs(ratio_x);
		double abs_ratio_y = abs(ratio_y);

		//计算隐藏窗口坐标。注意移动到边缘时，坐标要进行修正，因为这个坐标并不是隐藏窗口的中心坐标。得到图片位置后，加载指定图片
		if (ratio_y >= 0 && ratio_x >= 0)//主界面中心点在屏幕右下方
		{
			if (abs_ratio_y >= abs_ratio_x)//y方向上更近，移动到屏幕下边缘
			{
				hidewindow_x = mainwindow_x - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = screen_resolution[1] - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_DOWN_HIDE_PICTURE_PATH_STRING);
			}
			else//x方向上更近，移动到屏幕右边缘
			{
				hidewindow_x = screen_resolution[0] - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = mainwindow_y - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_RIGHT_HIDE_PICTURE_PATH_STRING);
			}
		}
		else if (ratio_y >= 0 && ratio_x < 0)//主界面中心点在屏幕左下方
		{
			if (abs_ratio_y >= abs_ratio_x)//y方向上更近，移动到屏幕下边缘
			{
				hidewindow_x = mainwindow_x - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = screen_resolution[1] - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_DOWN_HIDE_PICTURE_PATH_STRING);
			}
			else//x方向上更近，移动到屏幕左边缘
			{
				hidewindow_x = 0 - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = mainwindow_y - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_LEFT_HIDE_PICTURE_PATH_STRING);
			}
		}
		else if (ratio_y < 0 && ratio_x >= 0)//主界面中心点在屏幕右上方
		{
			if (abs_ratio_y >= abs_ratio_x)//y方向上更近，移动到屏幕上边缘
			{
				hidewindow_x = mainwindow_x - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = 0 - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_UP_HIDE_PICTURE_PATH_STRING);
			}
			else//x方向上更近，移动到屏幕右边缘
			{
				hidewindow_x = screen_resolution[0] - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = mainwindow_y - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_RIGHT_HIDE_PICTURE_PATH_STRING);
			}
		}
		else//主界面中心点在屏幕左上方
		{
			if (abs_ratio_y >= abs_ratio_x)//y方向上更近，移动到屏幕上边缘
			{
				hidewindow_x = mainwindow_x - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = 0 - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_UP_HIDE_PICTURE_PATH_STRING);
			}
			else//x方向上更近，移动到屏幕左边缘
			{
				hidewindow_x = 0 - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = mainwindow_y - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_LEFT_HIDE_PICTURE_PATH_STRING);
			}
		}
		background_picture = background_picture.scaled(QSize(WINDOW_SIZE_SIDE_LENGTH_NUMBER, WINDOW_SIZE_SIDE_LENGTH_NUMBER), Qt::KeepAspectRatio);//重定义图片大小
		resize(background_picture.size());//重定义窗口大小
		move(hidewindow_x, hidewindow_y);//根据计算出来的坐标值移动隐藏窗口
		update();
		setWindowOpacity(transparent);//设置隐藏窗口透明度
		QPropertyAnimation *animation_hide_appear = new QPropertyAnimation(this, "windowOpacity");//主窗口消失动画
		animation_hide_appear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_hide_appear->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_hide_appear->setEndValue(transparent);
		animation_hide_appear->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		connect(animation_hide_appear, SIGNAL(finished()), this, SLOT(time_hide_repaint()));
		time_hide_repaint();
	}

	void Desktop::time_hide_repaint()//隐藏过程计时器到期绘制窗口函数
	{
		time_counter->stop();//必须关闭计时器，否则会继续循环计时
		is_hide = true;//设置为主窗口被隐藏，可以继续接收点击显示事件
	}

	void Desktop::show_animation_appear()//显示过程出现动画播放
	{
		move_enable = true;//允许记录
		randnumber = WINDOW_RANDOM_MIN_NUMBER + rand() % (WINDOW_RANDOM_MAX_NUMBER - WINDOW_RANDOM_MIN_NUMBER + 1);//生成一个随机的数字，该数字用来决定主界面的背景。每次显示主界面，这个数字都会发生变化
		background_path = WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING;//临时存储背景图片路径
		background_path += QString::number(randnumber, 10);
		background_path += WINDOW_BACKGROUND_PICTURE_PATH_BACK_STRING;
		background_picture.load(background_path);//加载背景图片
		resize(WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		move(position[0], position[1]);//修改窗口起始坐标
		update();
		setWindowOpacity(transparent);
		QPropertyAnimation *animation_show_appear = new QPropertyAnimation(this, "windowOpacity");//主窗口消失动画
		animation_show_appear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_show_appear->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_show_appear->setEndValue(transparent);
		animation_show_appear->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		QPoint mouse_position(position[0] + WINDOW_SIZE_WIDTH_NUMBER / 2, position[1] + WINDOW_SIZE_HEIGHT_NUMBER / 2);//修改鼠标位置，否则主界面出现时会瞬移到鼠标位置，非常不和谐
		QCursor::setPos(mouse_position);
	}

	//其他功能
	void Desktop::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
	{

		//禁用所有按钮，否则动画播放完毕前再次点击按钮会重新触发动画
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(false);
		}
		QPropertyAnimation *animation_close = new QPropertyAnimation(this, "windowOpacity");
		animation_close->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//窗口关闭动画效果
		animation_close->setStartValue(transparent);
		animation_close->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_close->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		connect(animation_close, SIGNAL(finished()), this, SLOT(close()));
	}

	void Desktop::key_press_method(int widget_id)//键盘事件处理
	{
		if (widget_mutex[widget_id])
		{

			//将配置文件相应内容修改为允许，并启动窗口
			QSettings *write_setting = new QSettings(FILE_SETTING_STATIC_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
			QString temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(widget_id, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
			write_setting->setValue(temp, 1);
			delete write_setting;
			Widget *dialog = new Widget;//非模态窗口
			dialog->set_attribute(widget_is_on_top[widget_id], widget_id, widget_transparent[widget_id], widget_path[widget_id]);//设置初始值
			dialog->setModal(false);//指定为非模态对话框
			dialog->show();
		}
		else
		{

		}
	}
}

