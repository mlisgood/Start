#ifndef DESKTOPOMAKE_H
#define DESKTOPOMAKE_H 

#include "define.h"

namespace rem
{

	class DesktopOmake : public QMainWindow
	{
		Q_OBJECT

	private:

		Ui::DesktopOmakeClass ui;
		QPixmap background_picture;//背景图片
		QPixmap word_picture;//文字图片
		QPixmap picture_pixmap;//目标图像
		QImage picture_image;//目标图像
		QImage temp_image;//每次不在原图上进行操作，可以避免原图质量下降
		QPoint m_point;//记录坐标用于移动窗口
		QColor color;//背景色
		double value_resize;//记录放缩值
		int value_rotate;//记录旋转值
		bool background_enable;//是否允许背景颜色
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		bool m_bPressed;//确定窗口是否被按下

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造和析构函数
		DesktopOmake(QWidget *parent = Q_NULLPTR);
		~DesktopOmake();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//拖拽事件
		void dragEnterEvent(QDragEnterEvent *event);
		void dropEvent(QDropEvent *event);

		//键盘事件
		void keyPressEvent(QKeyEvent *event);

		//其他功能
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法

		//槽函数
		public slots:

			void slider_resize_change(int value);//图片尺寸改变
			void slider_rotate_change(int value);//图片角度改变
			void slider_color_red_change(int value);//图片颜色分量（红）改变
			void slider_color_green_change(int value);//图片颜色分量（绿）改变
			void slider_color_blue_change(int value);//图片颜色分量（蓝）改变
			void spinbox_1_change(int value);//spinbox改变
			void spinbox_2_change(int value);//spinbox改变
			void spinbox_3_change(int value);//spinbox改变
			void spinbox_4_change(int value);//spinbox改变
			void spinbox_5_change(int value);//spinbox改变
	};
}

#endif