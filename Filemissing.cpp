#include "define.h"

namespace rem
{

	//构造与析构函数
	Filemissing::Filemissing(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		totalrandomnumber = DIALOG_RANDOM_MIN_NUMBER + rand() % (DIALOG_RANDOM_MAX_NUMBER - DIALOG_RANDOM_MIN_NUMBER + 1);//产生指定随机数以便决定背景图片和人物图片样式
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		resize(DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序

		//图片路径
		//背景图片路径
		filepath = DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING + QString::number(totalrandomnumber, 10);
		filepath += DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING;

		//左侧图片路径
		chara_path = DIALOG_CHARA_PICTURE_PATH_FRONT_STRING;
		QString chara_path_number = QString::number(totalrandomnumber, 10);//将随机数转化为路径中的一部分
		chara_path += chara_path_number;
		chara_path += DIALOG_CHARA_PICTURE_PATH_BREAK_STRING;
		chara_path += QString::number(DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER + rand() % (DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER - DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER + 1), 10);//从当前系列的3张图片当中选取一张并增加到路径中
		chara_path += DIALOG_CHARA_PICTURE_PATH_BACK_STRING;

		//加载界面，必须放在最后以避免界面被之后的绘图覆盖
		ui.setupUi(this);

		//加载按钮样式
		ui.pushButton_close_dialog->setStyleSheet("QPushButton{border-image: url(:/icon/item/picture_start/icon/dialog_main_exit_normal.png);}""QPushButton:hover{border-image: url(:/icon/item/picture_start/icon/dialog_main_exit_pressed.png);}""QPushButton:pressed{border-image: url(:/icon/item/picture/icon/dialog_main_exit_pressed.png;}");
	
		//关闭按钮
		connect(ui.pushButton_close_window, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));
		connect(ui.pushButton_close_dialog, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));

		//窗口启动动画效果
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}

	Filemissing::~Filemissing()
	{

	}

	//设置成员变量
	void Filemissing::set_dialog_information_status(int dialog_information_status)
	{
		information_status = dialog_information_status;
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void Filemissing::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bPressed = true;
			m_point = event->pos();
		}
	}
	//若鼠标左键被按下，则移动窗体位置
	void Filemissing::mouseMoveEvent(QMouseEvent *event)
	{
		if (m_bPressed)
			move(event->pos() - m_point + pos());
	}

	//鼠标未被按下，则相应变量为false
	void Filemissing::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	void Filemissing::paintEvent(QPaintEvent *)
	{

		//绘制窗口用到的图片。具体方法：首先指派5种背景风格。之后从5组随机数中选取一个，映射到其中一种风格上面。以下是对应的映射关系：[1,5]->ココア，[6,10]->チノ，[11,15]->リゼ，[16,20]->シャロ,[21,25]->千夜。此外，之后的其他图片也和构建背景使用的随机数有关。每个背景对应3张图片，每次随机选取1张。
		//以下功能用到了常量，如要修改最好重写
		//绘制图片
		QPainter background_painter(this);//背景
		QPainter margin_painter(this);//边框
		QPainter chara_painter(this);//人物
		QPainter information_painter(this);//文字
		QPixmap background_picture;
		QPixmap margin_picture;
		QPixmap chara_picture;
		QPixmap information_picture;
		if (information_status == DIALOG_INFORMATION_STATUS_1_FLAG)//内存不足
		{
			information_path = DIALOG_INFORMATION_1_PICTURE_PATH_STRING;
		}
		else if(information_status == DIALOG_INFORMATION_STATUS_2_FLAG)//无法打开文件
		{
			information_path = DIALOG_INFORMATION_2_PICTURE_PATH_STRING;
		}
		else if (information_status == DIALOG_INFORMATION_STATUS_3_FLAG)//不能启动相同程序
		{
			information_path = DIALOG_INFORMATION_3_PICTURE_PATH_STRING;
		}
		else
		{

		}
		information_path += QString::number(totalrandomnumber, 10);//将随机数转化为路径中的一部分
		information_path += DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING;
		background_picture.load(filepath);
		margin_picture.load((QString)DIALOG_MARGIN_PICTURE_PATH_STRING);
		chara_picture.load(chara_path);
		information_picture.load(information_path);
		background_painter.drawPixmap(0, 0, DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, background_picture);
		chara_painter.drawPixmap(0, 0, DIALOG_SIZE_HEIGHT_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, chara_picture);//左侧图片使用正方形，长和宽与窗口宽度一致
		information_painter.drawPixmap(DIALOG_SIZE_HEIGHT_NUMBER, 0, DIALOG_SIZE_WIDTH_NUMBER - DIALOG_SIZE_HEIGHT_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, information_picture);//文字部分应该从左边的图片部分的右边缘开始
		margin_painter.drawPixmap(0, 0, DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, margin_picture);//最后显示以免被图片覆盖
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉。这个窗口因为只有确认操作，本来不需要重写，但为了保持统一，还是进行了重写
	void Filemissing::keyPressEvent(QKeyEvent *event)
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

	void Filemissing::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

