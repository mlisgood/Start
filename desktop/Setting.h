#ifndef Setting_H
#define Setting_H

#include "define.h"

namespace rem
{
	class Setting : public QDialog
	{
		Q_OBJECT

	private:

		Ui::SettingClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QPixmap main_picture;//需要绘制以便于作为窗口的图片
		QPixmap widget_picture[7];//需要绘制的组件图片
		int picture_digit[7];//图片透明度
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环

	protected:

		void paintEvent(QPaintEvent *); //绘制背景图像

	public:

		//构造与析构函数
		Setting(QWidget *parent = Q_NULLPTR);
		~Setting();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		public slots:
		
			void set_apply();//设置生效
			void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法

			//选择路径
			void pushButton_select_1();
			void pushButton_select_2();
			void pushButton_select_3();
			void pushButton_select_4();
			void pushButton_select_5();
			void pushButton_select_6();
			void pushButton_select_7();

			//清除路径
			void pushButton_delete_1();
			void pushButton_delete_2();
			void pushButton_delete_3();
			void pushButton_delete_4();
			void pushButton_delete_5();
			void pushButton_delete_6();
			void pushButton_delete_7();

			//透明度减少
			void pushButton_transparent_down_1();
			void pushButton_transparent_down_2();
			void pushButton_transparent_down_3();
			void pushButton_transparent_down_4();
			void pushButton_transparent_down_5();
			void pushButton_transparent_down_6();
			void pushButton_transparent_down_7();

			//透明度增加
			void pushButton_transparent_up_1();
			void pushButton_transparent_up_2();
			void pushButton_transparent_up_3();
			void pushButton_transparent_up_4();
			void pushButton_transparent_up_5();
			void pushButton_transparent_up_6();
			void pushButton_transparent_up_7();
	};
}

#endif