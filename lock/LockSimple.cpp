#include "define.h"

namespace rem
{

	//构造和析构函数
	LockSimple::LockSimple(QWidget *parent) : QDialog(parent)
	{
		randnumber = WINDOW_RANDOM_MIN_NUMBER + rand() % (WINDOW_RANDOM_MAX_NUMBER - WINDOW_RANDOM_MIN_NUMBER + 1);//产生指定随机数。仅在构造函数中使用一次，以保证不会出现隐藏并打开窗口后背景因为重新绘图发生变化的问题
		setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);//去掉窗口标题栏并且窗口可以通过点击任务栏放大缩小
		resize(WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_QuitOnClose, true);//该窗口关闭时会退出程序
		is_escape_pressed = false;//允许按下esc键退出程序

		ui.setupUi(this);

		//按钮设置
		ui.pushButton_select_1->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_normal_1.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_pressed_1.png);}");
		ui.pushButton_select_2->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_normal_2.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_pressed_2.png);}");
		ui.pushButton_select_3->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_normal_3.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_pressed_3.png);}");

		//信号函数
		connect(ui.pushButton_select_1, SIGNAL(clicked()), this, SLOT(method_1_dialog()));//取反加密窗口
		connect(ui.pushButton_select_2, SIGNAL(clicked()), this, SLOT(method_2_dialog()));//加减加密窗口
		connect(ui.pushButton_select_3, SIGNAL(clicked()), this, SLOT(close_dialog()));//返回主界面

		//退出时销毁该窗口以免内存泄漏
		setAttribute(Qt::WA_DeleteOnClose);

		//窗口启动动画效果
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}

	LockSimple::~LockSimple()
	{
		
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	void LockSimple::mousePressEvent(QMouseEvent *event)//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
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

	void LockSimple::mouseMoveEvent(QMouseEvent *event)//若鼠标左键被按下，则移动窗体位置
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}
	}

	void LockSimple::mouseReleaseEvent(QMouseEvent *event)//鼠标未被按下，则相应变量为false
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void LockSimple::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Enter)
		{

		}
		else if (event->key() == Qt::Key_Escape)
		{
			if (!is_escape_pressed)//仅执行一次按下esc退出
			{
				is_escape_pressed = true;
				close_window_include_animation_and_show_mainwindow();
			}
			else
			{

			}
		}
		else
		{

		}
	}

	void LockSimple::paintEvent(QPaintEvent *)//绘制背景图像
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
	void LockSimple::close_dialog()
	{
		close_window_include_animation_and_show_mainwindow();//关闭窗口并显示主窗口
	}

	void LockSimple::method_1_dialog()
	{
		hide_window_include_animation();//隐藏窗口。因为这个对象是在这里申请的，不能直接关闭窗口，否则会造成新打开的窗口被析构
		LockSimpleOpposite *dialog = new LockSimpleOpposite();//必须使用此方法创建窗口，否则connect函数无法使用
		connect(dialog, SIGNAL(show_lock_simple_window()), this, SLOT(show_window_include_animation()));//连接函数，因为要同时有主界面和子窗口的地址，因此在此处使用
		dialog->show();//这里因为不涉及到隐藏显示可以使用模态窗口，但为保持一致仍使用非模态窗口
	}

	void LockSimple::method_2_dialog()
	{
		hide_window_include_animation();//隐藏窗口。因为这个对象是在这里申请的，不能直接关闭窗口，否则会造成新打开的窗口被析构
		LockSimpleAdd *dialog = new LockSimpleAdd();//必须使用此方法创建窗口，否则connect函数无法使用
		connect(dialog, SIGNAL(show_lock_simple_window()), this, SLOT(show_window_include_animation()));//连接函数，因为要同时有主界面和子窗口的地址，因此在此处使用
		dialog->show();//这里因为不涉及到隐藏显示可以使用模态窗口，但为保持一致仍使用非模态窗口
	}

	void LockSimple::hide_window_include_animation()//包含隐藏窗口动画的隐藏窗口方法
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

	void LockSimple::close_window_include_animation_and_show_mainwindow()//包含关闭窗口动画的关闭窗并显示主窗口方法
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
		emit show_mainwindow();//发出显示主窗口信号
		connect(animation_close, SIGNAL(finished()), this, SLOT(close()));
	}

	void LockSimple::show_window_include_animation()//包含显示窗口动画的显示窗口方法
	{
		show();//必须先显示窗口再播放动画
		QPropertyAnimation *animation_show = new QPropertyAnimation(this, "windowOpacity");
		animation_show->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//窗口显示动画效果
		animation_show->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_show->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation_show->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		connect(animation_show, SIGNAL(finished()), this, SLOT(show_window_include_animation_end()));
	}

	void LockSimple::show_window_include_animation_end()//窗口显示结束处理函数
	{

		//启用所有按钮，必须在动画播放完之后使用，否则也会出现不断点击相关按钮时动画反复播放的情况
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(true);
		}
	}
}

