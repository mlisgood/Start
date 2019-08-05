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
	UnlockSimpleAddCheckDigit::UnlockSimpleAddCheckDigit(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序					
		is_escape_pressed = false;//默认未按下esc键以退出

		//加载图片作为窗口背景
		main_picture.load(DIALOG_BACKGROUND_UNLOCK_SIMPLE_ADD_SET_DIGIT_PATH_STRING);
		resize(main_picture.size());//窗口大小改为图片大小

		//加载界面
		ui.setupUi(this);

		//信号函数
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//确认按钮

		//设置按钮样式
		ui.pushButton_apply->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_10.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_10.png);}");

		//设置文字颜色
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::WindowText, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::Highlight, QColor(128, 76, 71, 64));
		ui.listWidget_1->setPalette(text_palette);

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
		}
		else//加载失败，使用软件设定好的默认字体
		{

		}
	}
	UnlockSimpleAddCheckDigit::~UnlockSimpleAddCheckDigit()
	{
		
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void UnlockSimpleAddCheckDigit::mousePressEvent(QMouseEvent *event)
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
	void UnlockSimpleAddCheckDigit::mouseMoveEvent(QMouseEvent *event)
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
	void UnlockSimpleAddCheckDigit::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void UnlockSimpleAddCheckDigit::keyPressEvent(QKeyEvent *event)
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

	void UnlockSimpleAddCheckDigit::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//画图作为窗口背景
	}

	//设置成员函数
	void UnlockSimpleAddCheckDigit::set_information(int *extra_int_information)//设置需要显示的加减数量
	{
		for (int index = 0; index < extra_int_information[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER]; index++)//传入各单元加减数量
		{
			QString transform_result = QString::number((extra_int_information[index]), 10);
			if (transform_result != "")
			{
				ui.listWidget_1->addItem(transform_result);//将各项目添加进listwidget
			}
			else
			{
				ui.listWidget_1->addItem(DIALOG_LOCK_SIMPLE_ADD_DEFAULT_UNIT_INSERT_STRING);
			}
		}
	}

	void UnlockSimpleAddCheckDigit::set_apply()//设置生效
	{
		close_window_include_animation();//关闭窗口
	}

	void UnlockSimpleAddCheckDigit::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

