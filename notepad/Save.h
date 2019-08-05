#ifndef SAVE_H
#define SAVE_H

#include "define.h"

namespace rem
{
	class Save : public QDialog
	{
		Q_OBJECT

	private:

		Ui::SaveClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QString filepath;//背景图片路径
		QString chara_path;//左侧图片路径
		QString dialog_information_path;//窗口提示信息
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		int totalrandomnumber;//用于决定全局的随机数
		int return_number;//按下按钮的返回值

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造与析构函数
		Save(QWidget *parent = Q_NULLPTR);
		~Save();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		//设置成员变量
		void set_dialog_information_path(QString inforation_path);//设置文字图片路径
		void set_return_number(int set_number);//设置按下按钮返回的值
		int get_return_number();//取得按下按钮返回的值

		public slots:

		//改变return_number的值，用于信号传递
		void change_return_number_save();
		void change_return_number_discard();

		//关闭动画
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
	};
}

#endif