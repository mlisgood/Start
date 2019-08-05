#ifndef TOOLSSET_H
#define TOOLSSET_H

#include "define.h"

namespace rem
{
	class ToolsSet : public QDialog
	{
		Q_OBJECT

	private:

		Ui::ToolsSetClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QPixmap main_picture;//需要绘制以便于作为窗口的图片
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环

	protected:

		void paintEvent(QPaintEvent *); //绘制背景图像

	public:

		//构造与析构函数
		ToolsSet(QWidget *parent = Q_NULLPTR);
		~ToolsSet();

		//初始设置
		void read_font();//读取系统字体并置入combobox

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		public slots:
		
			void set_apply();//设置生效
			void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
			void pushButton_choose_1_apply();//设置按钮生效
			void pushButton_choose_2_apply();
			void pushButton_choose_3_apply();
			void pushButton_choose_4_apply();
			void pushButton_choose_5_apply();
			void pushButton_choose_6_apply();
			void pushButton_choose_7_apply();
			void pushButton_choose_8_apply();
			void pushButton_choose_9_apply();
			void pushButton_choose_10_apply();
			void pushButton_choose_11_apply();
			void pushButton_choose_12_apply();
			void pushButton_choose_13_apply();
			void pushButton_choose_14_apply();
			void pushButton_choose_15_apply();
			void pushButton_choose_16_apply();
	};
}

#endif