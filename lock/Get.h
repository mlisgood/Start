#ifndef Get_H
#define Get_H

#include "define.h"

namespace rem
{
	class Get : public QDialog
	{
		Q_OBJECT

	private:

		Ui::GetClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QTimer *timer;//计时器
		QGraphicsOpacityEffect *effect_1;//label_chara_1透明效果
		QGraphicsOpacityEffect *effect_2;//label_chara_2透明效果
		int timer_picture_count;//计时器图片顺序计数
		int timer_interval;//计时器计时间隔
		qreal timer_transparent_count;//计时器透明度计数
		bool m_bPressed;//确定窗口是否被按下

	public:

		//构造与析构函数
		Get(QWidget *parent = Q_NULLPTR);
		~Get();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		public slots:

			void timer_timeout();
	};
}

#endif