#include "define.h"

namespace rem
{

	//引用全局变量
	extern int counter_mutex;

	//构造与析构函数
	Counter::Counter(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		voice_randnumber = DIALOG_TIME_COUNTER_END_VOICE_MIN_NUMBER + rand() % (DIALOG_TIME_COUNTER_END_VOICE_MAX_NUMBER - DIALOG_TIME_COUNTER_END_VOICE_MIN_NUMBER + 1);//产生指定随机数用于选择结束时的人物声音
		setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | windowFlags());//去掉窗口标题栏，并且任务栏中不会出现窗口
		setAttribute(Qt::WA_TranslucentBackground, true);//将窗口背景透明化
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		setAttribute(Qt::WA_DeleteOnClose);//退出时销毁该窗口以免内存泄漏
		counter_mutex--;//允许的计时器窗口的数目减少1
		counter_pause = false;//计时器未进入暂停状态
		is_escape_pressed = false;//默认未按下esc键以退出
		
		//加载界面
		ui.setupUi(this);

		//加载图片作为窗口背景
		main_picture.load(DIALOG_COUNTER_BACKGROUND_PICTURE_PATH_STRING);
		resize(DIALOG_COUNTER_SIZE_WIDTH_NUMBER, DIALOG_COUNTER_SIZE_HEIGHT_NUMBER);//窗口大小改为图片大小，此次不再以图片为界，因为需要保留部分透明区域
	
		//定时器
		time_counter = new QTimer(this);//创建一个定时器
		time_counter->setTimerType(Qt::PreciseTimer);//修改精度
		time_counter->start(DIALOG_COUNTER_INTERVAL_NUMBER);//初始化计时器，然后开始，只计时1个间隔
		connect(time_counter, SIGNAL(timeout()), this, SLOT(time_repaint()));//计时器到期处理，重新绘制时间图片

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}
	Counter::~Counter()
	{
		counter_mutex++;//允许的计时器窗口的数目增加1
		delete time_counter;
	}

	//成员变量设置
	void Counter::set_setting_information(int index, int value)
	{
		setting_information[index] = value;
	}

	void Counter::set_beginning_value()//设置初始值，这一部分绝对不能放进构造函数，因为构造函数在创建窗口对象的时候就会使用，比对数组的赋值要早
	{
		//根据上一个窗口的配置来进行初始化
		if (setting_information[5] == 1)//窗口是否在最顶部
		{
			setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
		}
		else if (setting_information[5] == 2)
		{
			
		}
		else
		{
			
		}
		if (setting_information[0] == 1)//计时器类型
		{
			counter_hour = 0;//时
			counter_minute = 0;//分
			counter_second = 0;//秒
		}
		else if (setting_information[0] == 2)
		{
			counter_hour = setting_information[1];//时
			counter_minute = setting_information[2];//分
			counter_second = setting_information[3];//秒
		}
		else
		{
			counter_hour = 0;//时
			counter_minute = 0;//分
			counter_second = 0;//秒
		}
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void Counter::mousePressEvent(QMouseEvent *event)
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
	void Counter::mouseMoveEvent(QMouseEvent *event)
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
	void Counter::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//鼠标双击在暂停与恢复状态之间切换
	void Counter::mouseDoubleClickEvent(QMouseEvent *event)
	{
		if (counter_pause == false)
		{
			counter_pause = true;
			time_counter->stop();
		}
		else
		{
			counter_pause = false;
			time_counter->start();
		}
	}

	//键盘事件，用于结束程序
	void Counter::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Escape)
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
	}

	void Counter::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(WINDOW_BACKGROUND_PAINT_START_X_NUMBER, WINDOW_BACKGROUND_PAINT_START_Y_NUMBER, main_picture);//画图作为窗口背景
		count_number = DIALOG_COUNTER_NUMBER_PICTURE_PATH_FRONT_STRING;//时的十位
		count_number += QString::number((int)counter_hour / 10, 10);
		count_number += DIALOG_COUNTER_NUMBER_PICTURE_PATH_BACK_STRING;
		counter_time[0].load(count_number);
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[0]);//每次绘制的时候，起始点的横坐标向右移动一个时间数字图片间隔
		count_number = DIALOG_COUNTER_NUMBER_PICTURE_PATH_FRONT_STRING;//时的个位
		count_number += QString::number((int)counter_hour % 10, 10);
		count_number += DIALOG_COUNTER_NUMBER_PICTURE_PATH_BACK_STRING;
		counter_time[1].load(count_number);
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER + DIALOG_COUNTER_NUMBER_PICTURE_WIDTH, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[1]);
		counter_time[2].load(DIALOG_COUNTER_COLON_PICTURE_PATH_STRING);//分隔符1
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER + DIALOG_COUNTER_NUMBER_PICTURE_WIDTH * 2, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[2]);
		count_number = DIALOG_COUNTER_NUMBER_PICTURE_PATH_FRONT_STRING;//分的十位
		count_number += QString::number((int)counter_minute / 10, 10);
		count_number += DIALOG_COUNTER_NUMBER_PICTURE_PATH_BACK_STRING;
		counter_time[3].load(count_number);
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER + DIALOG_COUNTER_NUMBER_PICTURE_WIDTH * 3, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[3]);
		count_number = DIALOG_COUNTER_NUMBER_PICTURE_PATH_FRONT_STRING;//分的个位
		count_number += QString::number((int)counter_minute % 10, 10);
		count_number += DIALOG_COUNTER_NUMBER_PICTURE_PATH_BACK_STRING;
		counter_time[4].load(count_number);
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER + DIALOG_COUNTER_NUMBER_PICTURE_WIDTH * 4, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[4]);
		counter_time[5].load(DIALOG_COUNTER_COLON_PICTURE_PATH_STRING);//分隔符2
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER + DIALOG_COUNTER_NUMBER_PICTURE_WIDTH * 5, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[5]);
		count_number = DIALOG_COUNTER_NUMBER_PICTURE_PATH_FRONT_STRING;//秒的十位
		count_number += QString::number((int)counter_second / 10, 10);
		count_number += DIALOG_COUNTER_NUMBER_PICTURE_PATH_BACK_STRING;
		counter_time[6].load(count_number);
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER + DIALOG_COUNTER_NUMBER_PICTURE_WIDTH * 6, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[6]);
		count_number = DIALOG_COUNTER_NUMBER_PICTURE_PATH_FRONT_STRING;//秒的个位
		count_number += QString::number((int)counter_second % 10, 10);
		count_number += DIALOG_COUNTER_NUMBER_PICTURE_PATH_BACK_STRING;
		counter_time[7].load(count_number);
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER + DIALOG_COUNTER_NUMBER_PICTURE_WIDTH * 7, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[7]);
	}

	void Counter::time_repaint()//计时器到期
	{
		if (setting_information[0] == 2)//是倒数计时器
		{
			if (counter_second > 0)//如果秒数大于0，就令其减1；否则分数减1，秒数重新置为最大值；分数按照同样方式处理，当时、分、秒均为0时，退出。注意从上至下，各个条件之间应该没有包含关系
			{
				counter_second--;
			}
			else if (counter_second <= 0 && counter_minute > 0)
			{
				counter_minute--;
				counter_second = 59;
			}
			else if (counter_second <= 0 && counter_minute <= 0 && counter_hour > 0)
			{
				counter_hour--;
				counter_minute = 59;
				counter_second = 59;
			}
			else if (counter_second <= 0 && counter_minute <= 0 && counter_hour <= 0)
			{
				QPropertyAnimation *animation_close = new QPropertyAnimation(this, "windowOpacity");
				animation_close->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//窗口关闭动画效果
				animation_close->setStartValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
				animation_close->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
				animation_close->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
				connect(animation_close, SIGNAL(finished()), this, SLOT(close_window_sound()));
			}
			else
			{

			}
		}
		else//是常规计时器
		{
			if (counter_hour >= 99 && counter_second >= 59 && counter_minute >= 59)//时间达到上限直接中止
			{
				close_window_include_animation();
			}
			else if (counter_minute >= 59 && counter_second >= 59)//如果秒数小于59，就令其加1；否则分数加1，秒数重新置为最小值；分数按照同样方式处理。注意从上至下，各个条件之间应该没有包含关系
			{
				counter_hour++;
				counter_minute = 0;
				counter_second = 0;
			}
			else if (counter_second >= 59)
			{
				counter_minute++;
				counter_second = 0;
			}
			else if (counter_second < 59)
			{
				counter_second++;
			}
			else
			{
				close_window_include_animation();
			}
		}
		update();//重新绘制	
	}

	void Counter::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

	void Counter::close_window_sound()//倒数计时器关闭窗口播放声音
	{
		QString voice_path_string = DIALOG_TIME_COUNTER_END_VOICE_FRONT_STRING;//播放声音的路径
		voice_path_string += QString::number(setting_information[4], 10);//第一个参数由上一个窗口的选项决定
		voice_path_string += DIALOG_TIME_COUNTER_END_VOICE_BREAK_STRING;//分隔符
		voice_path_string += QString::number(voice_randnumber, 10);//第二个参数随机选择
		voice_path_string += DIALOG_TIME_COUNTER_END_VOICE_BACK_STRING;//后缀
		QSound::play(voice_path_string);//播放音效，其独立使用一个线程。注意QSound实际上非常坑，wav文件的比特率不能太大，否则无法播放
		close();
	}
}

