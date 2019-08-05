#ifndef NOTE_H
#define NOTE_H

#include "define.h"

namespace rem
{
	class Note : public QDialog
	{
		Q_OBJECT

	private:

		Ui::NoteClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QString filepath;//背景图片路径
		bool m_bPressed;//确定窗口是否被按下
		bool on_top;//确定窗口是否始终在顶部
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		int totalrandomnumber;//用于决定全局的随机数

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造与析构函数
		Note(QWidget *parent = Q_NULLPTR);
		~Note();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		//其他
		void set_font(QString font);//修改字体

		//槽函数
		public slots:

			void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
	};
}

#endif