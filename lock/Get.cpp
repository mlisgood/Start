#include "define.h"

namespace rem
{

	//构造与析构函数
	Get::Get(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		resize(DIALOG_LOCK_SIZE_WIDTH_NUMBER, DIALOG_LOCK_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_QuitOnClose, true);//该窗口关闭时会退出程序

		//计时器
		timer_picture_count = DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER + rand() % (DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER - DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER + 1);//产生指定随机数。仅在构造函数中使用一次，以保证不会出现隐藏并打开窗口后背景因为重新绘图发生变化的问题
		timer_transparent_count = 0;//图片初始透明度设定
		timer_interval = DIALOG_LOCK_CHARA_PICTURE_COUNT_INTERVAL_NUMNER;//初始图片的轮播间隔为标准的切换图片间隔
		timer = new QTimer(this);//初始化计时器
		connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));//信号处理
		timer->start(timer_interval);

		//加载界面，必须放在最后以避免界面被之后的绘图覆盖
		ui.setupUi(this);

		//按钮
		ui.pushButton_1->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture/icon/get_button_normal_1.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture/icon/get_button_pressed_1.png);}");
		ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture/icon/get_button_normal_2.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture/icon/get_button_pressed_2.png);}");

		//图片初始化
		effect_1 = new QGraphicsOpacityEffect(this);//特效
		effect_2 = new QGraphicsOpacityEffect(this);
		effect_1->setOpacity(1 - timer_transparent_count);
		effect_2->setOpacity(0);
		QPixmap background_picture;//绘制未切换时的背景图片
		QString background_path = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//临时存储原始背景图片路径
		background_path += QString::number(timer_picture_count, 10);//第一张图片使用随机数
		background_path += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
		background_picture.load(background_path);//加载背景图片
		ui.label_chara_1->setGraphicsEffect(effect_1);//后面使用人物图片
		ui.label_chara_1->setPixmap(background_picture);
		ui.label_chara_2->setGraphicsEffect(effect_2);//前面使用全透明图片
		ui.label_chara_2->setPixmap(QPixmap(DIALOG_BACKGROUND_CHARA_TRANSPARENT_PICTURE_PATH_STRING));
	}

	Get::~Get()
	{
		delete timer;
		delete effect_1;
		delete effect_2;
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void Get::mousePressEvent(QMouseEvent *event)
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
	void Get::mouseMoveEvent(QMouseEvent *event)
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
	void Get::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉。这个窗口因为只有确认操作，本来不需要重写，但为了保持统一，还是进行了重写
	void Get::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Enter)
		{

		}
		else if (event->key() == Qt::Key_Escape)
		{
			close();
		}
		else
		{

		}
	}

	void Get::timer_timeout()//使用2个label用来容纳图片。首先指定一个长时间间隔用来显示图片，此时图片在下层label，上层label使用全透明图片，即将其忽略。时间到期后，改用切换图片透明度所使用的短时间间隔，同时开始修改透明度计数，下层label显示原始图片，不透明度逐渐减小；上层label显示切换后图片，不透明度逐渐增加。当上层label图片透明度为1时，切换结束，图片计数增加1，以新的长时间间隔重新开始下一计时循环
	{
		if (timer_interval == DIALOG_LOCK_CHARA_PICTURE_COUNT_INTERVAL_NUMNER)//最大间隔时间到期，说明应该切换图片
		{
			timer_interval = DIALOG_LOCK_CHARA_PICTURE_TRANSPARENT_COUNT_INTERVAL_NUMNER;//切换为透明度更改间隔
			timer_transparent_count = DIALOG_LOCK_CHARA_PICTURE_TRANSPARENT_COUNT_MEASURE_NUMNER;
			effect_1->setOpacity(1 - timer_transparent_count);
			effect_2->setOpacity(timer_transparent_count);
			QPixmap background_picture_back;//绘制原始图片
			QString background_path_back = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//临时存储原始背景图片路径
			background_path_back += QString::number(timer_picture_count, 10);
			background_path_back += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
			background_picture_back.load(background_path_back);//加载图片
			QPixmap background_picture_next;//绘制切换后图片
			QString background_path_next = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//临时存储切换后背景图片路径
			if (timer_picture_count + 1 >= DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER + 1)//超出图片顺序最大数范围
			{
				background_path_next += QString::number(DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER, 10);
			}
			else
			{
				background_path_next += QString::number(timer_picture_count + 1, 10);
			}
			background_path_next += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
			background_picture_next.load(background_path_next);//加载背景图片
			ui.label_chara_1->setGraphicsEffect(effect_1);//后面使用原始图片
			ui.label_chara_1->setPixmap(background_picture_back);
			ui.label_chara_2->setGraphicsEffect(effect_2);//前面使用切换后图片
			ui.label_chara_2->setPixmap(background_picture_next);
			timer->start(timer_interval);//按照透明度切换的时间间隔继续启动计时器
		}
		else
		{
			if (timer_transparent_count >= 1)//结束一次切换
			{
				timer_transparent_count = 0;
				timer_interval = DIALOG_LOCK_CHARA_PICTURE_COUNT_INTERVAL_NUMNER;
				if (timer_picture_count + 1 >= DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER + 1)//图片计数超出范围
				{
					timer_picture_count = 1;
				}
				else
				{
					timer_picture_count += 1;
				}
				effect_1->setOpacity(1 - timer_transparent_count);
				effect_2->setOpacity(0);
				QPixmap background_picture;//绘制未切换时的背景图片
				QString background_path = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//临时存储原始背景图片路径
				background_path += QString::number(timer_picture_count, 10);
				background_path += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
				background_picture.load(background_path);//加载背景图片
				ui.label_chara_1->setGraphicsEffect(effect_1);//后面使用人物图片
				ui.label_chara_1->setPixmap(background_picture);
				ui.label_chara_2->setGraphicsEffect(effect_2);//前面使用全透明图片
				ui.label_chara_2->setPixmap(QPixmap(DIALOG_BACKGROUND_CHARA_TRANSPARENT_PICTURE_PATH_STRING));
				timer->start(timer_interval);
			}
			else//透明度没有达到指定大小
			{
				timer_transparent_count += DIALOG_LOCK_CHARA_PICTURE_TRANSPARENT_COUNT_MEASURE_NUMNER;
				effect_1->setOpacity(1 - timer_transparent_count);
				effect_2->setOpacity(timer_transparent_count);
				QPixmap background_picture_back;//绘制原始图片
				QString background_path_back = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//临时存储原始背景图片路径
				background_path_back += QString::number(timer_picture_count, 10);
				background_path_back += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
				background_picture_back.load(background_path_back);//加载图片
				QPixmap background_picture_next;//绘制切换后图片
				QString background_path_next = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//临时存储切换后背景图片路径
				if (timer_picture_count + 1 >= DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER + 1)//超出图片顺序最大数范围
				{
					background_path_next += QString::number(DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER, 10);
				}
				else
				{
					background_path_next += QString::number(timer_picture_count + 1, 10);
				}
				background_path_next += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
				background_picture_next.load(background_path_next);//加载背景图片
				ui.label_chara_1->setGraphicsEffect(effect_1);//后面使用原始图片
				ui.label_chara_1->setPixmap(background_picture_back);
				ui.label_chara_2->setGraphicsEffect(effect_2);//前面使用切换后图片
				ui.label_chara_2->setPixmap(background_picture_next);
				timer->start(timer_interval);
			}
		}
	}
}

