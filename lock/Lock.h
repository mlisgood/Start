#ifndef LOCK_H
#define LOCK_H 

#include "define.h"

namespace rem
{
	class Lock: public QMainWindow
	{
		Q_OBJECT

	private:

		Ui::LockClass ui;
		QPoint m_point;//记录坐标用于移动窗口
		int randnumber;//决定背景的随机数
		bool m_bPressed;//确定窗口是否被按下

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造和析构函数
		Lock(QWidget *parent = Q_NULLPTR);
		~Lock();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//关闭动画
		void hide_window_include_animation();//包含隐藏窗口动画的隐藏窗口方法
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法

	public slots:

		void close_dialog();//关闭窗口
		void normal_lock_dialog();//常规加密窗口
		void simple_lock_dialog();//简单加密窗口
		void set_dialog();//设置窗口
		void help_information();//程序信息
		void show_window_include_animation();//包含显示窗口动画的显示窗口方法
		void show_window_include_animation_end();//窗口显示结束处理函数
	};
}

#endif