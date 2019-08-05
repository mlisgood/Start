#ifndef LOCKSIMPLE_H
#define LOCKSIMPLE_H 

#include "define.h"

namespace rem
{
	class LockSimple: public QDialog
	{
		Q_OBJECT

	private:

		Ui::LockSimpleClass ui;
		QPoint m_point;//记录坐标用于移动窗口
		int randnumber;//决定背景的随机数
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造和析构函数
		LockSimple(QWidget *parent = Q_NULLPTR);
		~LockSimple();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		//关闭动画
		void hide_window_include_animation();//包含隐藏窗口动画的隐藏窗口方法
		void close_window_include_animation_and_show_mainwindow();//包含关闭窗口动画的关闭窗并显示主窗口方法

	signals:

		void show_mainwindow();//显示主窗口信号

	public slots:

		void close_dialog();//返回主界面
		void method_1_dialog();//取反加密窗口
		void method_2_dialog();//加减加密窗口
		void show_window_include_animation();//包含显示窗口动画的显示窗口方法
		void show_window_include_animation_end();//窗口显示结束处理函数
	};
}

#endif