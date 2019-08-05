#include "define.h"

namespace rem
{

	//构造和析构函数
	Lock::Lock(QWidget *parent) : QMainWindow(parent)
	{
		randnumber = WINDOW_RANDOM_MIN_NUMBER + rand() % (WINDOW_RANDOM_MAX_NUMBER - WINDOW_RANDOM_MIN_NUMBER + 1);//产生指定随机数。仅在构造函数中使用一次，以保证不会出现隐藏并打开窗口后背景因为重新绘图发生变化的问题
		setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);//去掉窗口标题栏并且窗口可以通过点击任务栏放大缩小
		resize(WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_QuitOnClose, true);//该窗口为主窗口，关闭时直接退出程序

		ui.setupUi(this);

		//按钮设置
		ui.pushButton_select_1->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_normal_1.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_pressed_1.png);}");
		ui.pushButton_select_2->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_normal_2.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_pressed_2.png);}");
		ui.pushButton_select_3->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_normal_3.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_pressed_3.png);}");

		//信号函数
		connect(ui.pushButton_select_1, SIGNAL(clicked()), this, SLOT(normal_lock_dialog()));//发送文件窗口
		connect(ui.pushButton_select_2, SIGNAL(clicked()), this, SLOT(simple_lock_dialog()));//接收文件窗口
		connect(ui.pushButton_select_3, SIGNAL(clicked()), this, SLOT(help_information()));//程序信息
		connect(ui.pushButton_set, SIGNAL(clicked()), this, SLOT(set_dialog()));//设置窗口
		connect(ui.pushButton_close_window, SIGNAL(clicked()), this, SLOT(close_dialog()));//关闭窗口按钮

		//窗口启动动画效果
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}

	Lock::~Lock()
	{

	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	void Lock::mousePressEvent(QMouseEvent *event)//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
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

	void Lock::mouseMoveEvent(QMouseEvent *event)//若鼠标左键被按下，则移动窗体位置
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}
	}

	void Lock::mouseReleaseEvent(QMouseEvent *event)//鼠标未被按下，则相应变量为false
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	void Lock::paintEvent(QPaintEvent *)//绘制背景图像
	{
		QPainter background_painter(this);//背景
		QPainter background_margin_painter(this);//边框
		QPixmap background_picture;//背景图片
		QPixmap background_margin_picture;//边框图片
		QString background_path = WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING;//临时存储背景图片路径
		background_path += QString::number(randnumber, 10);
		background_path += WINDOW_BACKGROUND_PICTURE_PATH_BACK_STRING;
		background_picture.load(background_path);//加载背景图片
		background_margin_picture.load(WINDOW_BACKGROUND_MARGIN_PICTURE_PATH_STRING);//加载边框图片
		background_painter.drawPixmap(0, 0, WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_WIDTH_NUMBER, background_picture);//绘制背景图片
		background_painter.drawPixmap(0, 0, WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_WIDTH_NUMBER, background_margin_picture);//绘制边框图片
	}

	//槽函数
	void Lock::close_dialog()
	{
		close_window_include_animation();
	}

	void Lock::normal_lock_dialog()//常规加密
	{
		hide_window_include_animation();//隐藏窗口
		LockNormal *dialog = new LockNormal();//必须使用此方法创建窗口，否则connect函数无法使用
		connect(dialog, SIGNAL(show_mainwindow()), this, SLOT(show_window_include_animation()));
		dialog->show();
	}

	void Lock::simple_lock_dialog()//简单加密
	{
		hide_window_include_animation();//隐藏窗口
		LockSimple *dialog = new LockSimple();//必须使用此方法创建窗口，否则connect函数无法使用
		connect(dialog, SIGNAL(show_mainwindow()), this, SLOT(show_window_include_animation()));//连接函数，因为要同时有主界面和子窗口的地址，因此在此处使用
		dialog->show();//对于需要涉及到隐藏显示的窗口最好不使用模态窗口，否则会出现一系列问题
	}

	void Lock::set_dialog()//设置窗口
	{
		Set dialog;
		dialog.exec();
	}

	void Lock::help_information()//程序信息
	{
		Help dialog;//显示程序信息
		dialog.set_dialog_information_path(DIALOG_INFORMATION_HELP_PATH_STRING);
		dialog.exec();
	}

	void Lock::hide_window_include_animation()//包含隐藏窗口动画的隐藏窗口方法
	{

		//禁用所有按钮，否则动画播放完毕前再次点击按钮会重新触发动画
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(false);
		}
		QPropertyAnimation *animation_hide = new QPropertyAnimation(this, "windowOpacity");
		animation_hide->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//窗口隐藏动画效果
		animation_hide->setStartValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation_hide->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_hide->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		connect(animation_hide, SIGNAL(finished()), this, SLOT(hide()));
	}

	void Lock::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

	void Lock::show_window_include_animation()//包含显示窗口动画的显示窗口方法
	{
		show();//必须先显示窗口再播放动画
		QPropertyAnimation *animation_show = new QPropertyAnimation(this, "windowOpacity");
		animation_show->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//窗口显示动画效果
		animation_show->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_show->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation_show->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		connect(animation_show, SIGNAL(finished()), this, SLOT(show_window_include_animation_end()));
	}

	void Lock::show_window_include_animation_end()//窗口显示结束处理函数
	{

		//启用所有按钮，必须在动画播放完之后使用，否则也会出现不断点击相关按钮时动画反复播放的情况
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(true);
		}
	}
}

