#ifndef COUNTERSET_H
#define COUNTERSET_H

#include "define.h"

namespace rem
{
	class CounterSet : public QDialog
	{
		Q_OBJECT

	private:

		Ui::CounterSetClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QPixmap main_picture;//需要绘制以便于作为窗口的图片
		QButtonGroup *radioButton_type;//单选项目分组1
		QButtonGroup *radioButton_voice;//单选项目分组2
		QButtonGroup *radioButton_dialog;//单选项目分组3
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环

	protected:

		void paintEvent(QPaintEvent *); //绘制背景图像

	public:

		//构造与析构函数
		CounterSet(QWidget *parent = Q_NULLPTR);
		~CounterSet();

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