#ifndef COUNTER_H
#define COUNTER_H

#include "define.h"

namespace rem
{
	class Counter : public QDialog
	{
		Q_OBJECT

	private:

		Ui::CounterClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QPixmap main_picture;//需要绘制以便于作为窗口的图片
		QPixmap counter_time[8];//绘制计时器时间图片。因为时间的数字一共有8个部分，因此需要8个变量来容纳
		QString count_number;//计时器的数字路径
		QTimer *time_counter;//计时器
		bool m_bPressed;//确定窗口是否被按下
		bool counter_pause;//确定计时器是否暂停
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		int setting_information[6];//设置信息，为方便起见直接采用数组存储。对于单选框组，存储被按下的按钮序号；对于数字选择框，存储数字的值
		int counter_hour;//计时器显示的时
		int counter_minute;//计时器显示的分
		int counter_second;//计时器显示的秒
		int voice_randnumber;//决定计时器到期使用的声音序号的随机数

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造与析构函数
		Counter(QWidget *parent = Q_NULLPTR);
		~Counter();

		//成员变量设置
		void set_setting_information(int index, int value);//设置存储设置值的数组元素值，参数分别为数组索引和元素值
		void set_beginning_value();//设置不适合在构造函数中设置的初始值

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseDoubleClickEvent(QMouseEvent * event);

		//键盘事件，用于响应快捷键
		void keyPressEvent(QKeyEvent *event);

		//槽函数
		public slots:

			void time_repaint();//计时器到期，重新绘制函数
			void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
			void close_window_sound();//倒数计时器关闭窗口播放声音
	};
}

#endif