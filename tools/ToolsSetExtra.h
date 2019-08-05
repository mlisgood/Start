#ifndef TOOLSSETEXTRA_H
#define TOOLSSETEXTRA_H

#include "define.h"

namespace rem
{
	class ToolsSetExtra : public QDialog
	{
		Q_OBJECT

	private:

		Ui::ToolsSetExtraClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QPixmap main_picture;//需要绘制以便于作为窗口的图片
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环

	protected:

		void paintEvent(QPaintEvent *); //绘制背景图像

	public:

		//构造与析构函数
		ToolsSetExtra(QWidget *parent = Q_NULLPTR);
		~ToolsSetExtra();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		public slots:
		
			void set_apply();//设置生效
			void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
	};
}

#endif