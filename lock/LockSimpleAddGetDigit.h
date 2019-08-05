#ifndef LOCKSIMPLEADDGETDIGIT_H
#define LOCKSIMPLEADDGETDIGIT_H

#include "define.h"

namespace rem
{
	class LockSimpleAddGetDigit : public QDialog
	{
		Q_OBJECT

	private:

		Ui::LockSimpleAddGetDigitClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QPixmap main_picture;//需要绘制以便于作为窗口的图片
		int *int_information[17];//从取反加密主界面得到的整数型信息，包括：加减数量和循环单位数目
		int int_information_data[17];//从取反加密主界面得到的整数型信息，包括：加减数量和循环单位数目


		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		bool *bool_information;//从取反加密主界面得到的布尔型信息，包括：是否有头部特征数字
		bool bool_information_data;//从取反加密主界面得到的布尔型信息，包括：是否有头部特征数字

	protected:

		void paintEvent(QPaintEvent *); //绘制背景图像

	public:

		//构造与析构函数
		LockSimpleAddGetDigit(QWidget *parent = Q_NULLPTR);
		~LockSimpleAddGetDigit();

		//设置成员函数
		void set_information(int *extra_digit_array);//设置需要显示在界面上的信息，参数为包含加减数量和循环单位数目的数组

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		public slots:
		
			void set_apply();//设置生效
			void cancel_apply();//设置取消
			void add_item();//添加项目
			void edit_item();//修改项目
			void delete_item();//删除项目
			void delete_all_item();//删除全部项目
			void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
	};
}

#endif