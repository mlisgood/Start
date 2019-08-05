#include "define.h"

namespace rem
{

	//构造与析构函数
	Note::Note(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		totalrandomnumber = DIALOG_NOTE_BACKGROUND_PICTURE_RANDOM_MIN_NUMBER + rand() % (DIALOG_NOTE_BACKGROUND_PICTURE_RANDOM_MAX_NUMBER - DIALOG_NOTE_BACKGROUND_PICTURE_RANDOM_MIN_NUMBER + 1);//产生指定随机数以便决定背景图片样式
		setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint | windowFlags());//去掉窗口标题栏，并且任务栏中不会出现窗口
		resize(DIALOG_SIZE_HEIGHT_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		setAttribute(Qt::WA_DeleteOnClose);//退出时销毁该窗口以免内存泄漏
		is_escape_pressed = false;//默认未按下esc键以退出
		on_top = true;//初始时刻在最顶层

		//背景图片路径
		filepath = DIALOG_NOTE_BACKGROUND_PICTURE_FRONT_STRING + QString::number(totalrandomnumber, 10);
		filepath += DIALOG_NOTE_BACKGROUND_PICTURE_BACK_STRING;

		//加载界面，必须放在最后以避免界面被之后的绘图覆盖
		ui.setupUi(this);

		//禁用富文本
		ui.textEdit_main->setAcceptRichText(false);

		//去除文本框背景。鉴于直接设置会导致文字超过一页出现滚动条后，背景跟随滚动条滚动成为平铺样式，故去掉文本框背景和边界，改为绘制背景
		ui.textEdit_main->setStyleSheet("background-color: rgb(255, 255, 255, 0);border:0px solid #e1e0e0;");

		//文字颜色
		QPalette text_palette;
		switch (totalrandomnumber)//决定文字和Highlight颜色
		{
		case 1:

			text_palette.setColor(QPalette::Text, QColor(255, 111, 111, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(255, 111, 111, 255));
			text_palette.setColor(QPalette::Highlight, QColor(255, 111, 111, 64));
			break;

		case 2:

			text_palette.setColor(QPalette::Text, QColor(91, 166, 222, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(91, 166, 222, 255));
			text_palette.setColor(QPalette::Highlight, QColor(91, 166, 222, 64));
			break;

		case 3:

			text_palette.setColor(QPalette::Text, QColor(151, 47, 151, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(151, 47, 151, 255));
			text_palette.setColor(QPalette::Highlight, QColor(151, 47, 151, 64));
			break;

		case 4:

			text_palette.setColor(QPalette::Text, QColor(250, 125, 0, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(250, 125, 0, 255));
			text_palette.setColor(QPalette::Highlight, QColor(250, 125, 0, 64));
			break;

		case 5:

			text_palette.setColor(QPalette::Text, QColor(100, 200, 20, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(100, 200, 20, 255));
			text_palette.setColor(QPalette::Highlight, QColor(100, 200, 20, 64));
			break;

		case 6:

			text_palette.setColor(QPalette::Text, QColor(255, 111, 111, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(255, 111, 111, 255));
			text_palette.setColor(QPalette::Highlight, QColor(255, 111, 111, 64));
			break;

		case 7:

			text_palette.setColor(QPalette::Text, QColor(250, 125, 0, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(250, 125, 0, 255));
			text_palette.setColor(QPalette::Highlight, QColor(250, 125, 0, 64));
			break;

		case 8:

			text_palette.setColor(QPalette::Text, QColor(91, 166, 222, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(91, 166, 222, 255));
			text_palette.setColor(QPalette::Highlight, QColor(91, 166, 222, 64));
			break;

		case 9:

			text_palette.setColor(QPalette::Text, QColor(100, 200, 20, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(100, 200, 20, 255));
			text_palette.setColor(QPalette::Highlight, QColor(100, 200, 20, 64));
			break;

		case 10:

			text_palette.setColor(QPalette::Text, QColor(151, 47, 151, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(151, 47, 151, 255));
			text_palette.setColor(QPalette::Highlight, QColor(151, 47, 151, 64));
			break;
		}
		ui.textEdit_main->setPalette(text_palette);

		//去掉关联性控件的右键菜单
		ui.textEdit_main->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
		ui.textEdit_main->horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}
	Note::~Note()
	{

	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void Note::mousePressEvent(QMouseEvent *event)
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
	void Note::mouseMoveEvent(QMouseEvent *event)
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
	void Note::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉。这个窗口因为只有确认操作，本来不需要重写，但为了保持统一，还是进行了重写
	void Note::keyPressEvent(QKeyEvent *event)
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
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_S))
		{
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
		}
		else
		{

		}
	}

	void Note::paintEvent(QPaintEvent *)
	{

		//绘制窗口用到的图片。具体方法：首先指派5种背景风格。之后从5组随机数中选取一个，映射到其中一种风格上面。以下是对应的映射关系：[1,5]->ココア，[6,10]->チノ，[11,15]->リゼ，[16,20]->シャロ,[21,25]->千夜。此外，之后的其他图片也和构建背景使用的随机数有关。每个背景对应3张图片，每次随机选取1张。
		//以下功能用到了常量，如要修改最好重写
		//绘制图片
		QPainter background_painter(this);//背景
		QPixmap background_picture;
		background_picture.load(filepath);
		background_painter.drawPixmap(0, 0, DIALOG_SIZE_HEIGHT_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, background_picture);
	}

	//其他功能
	void Note::set_font(QString font)//修改字体
	{
		ui.textEdit_main->setFont(QFont(font, 15, QFont::Normal, false));
	}

	//槽函数
	void Note::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

