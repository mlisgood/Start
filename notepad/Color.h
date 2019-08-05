#ifndef COLOR_H
#define COLOR_H

#include "define.h"

namespace rem
{
	class Color : public QDialog
	{
		Q_OBJECT

	private:

		Ui::ColorClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QString filepath;//背景图片路径
		QString dialog_information_path;//窗口提示信息
		QTextEdit *textedit_font;//主界面文本框指针，用于修改字体
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		int totalrandomnumber;//用于决定全局的随机数
		int resource_randomnumber;//用于决定资源文件的随机数
		int select_color;//决定是否可以选取颜色
		int forbid_change;//为1则阻止spinbox引起右侧渐变滑块颜色改变
		int color_status[24];//自定义颜色状态位
		int color_red[24];//自定义颜色红
		int color_green[24];//自定义颜色绿
		int color_blue[24];//自定义颜色蓝

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造与析构函数
		Color(QWidget *parent = Q_NULLPTR);
		~Color();

		//设置成员变量
		void set_textedit(QTextEdit *main_textedit);//获取文本框地址
		void set_resource_random_number(int number);//获取资源文件需要的变量

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		public slots:

		//颜色框选项
		void color_change_1();
		void color_change_2();
		void color_change_3();
		void color_change_4();
		void color_change_5();
		void color_change_6();
		void color_change_7();
		void color_change_8();
		void color_change_9();
		void color_change_10();
		void color_change_11();
		void color_change_12();
		void color_change_13();
		void color_change_14();
		void color_change_15();
		void color_change_16();
		void color_change_17();
		void color_change_18();
		void color_change_19();
		void color_change_20();
		void color_change_21();
		void color_change_22();
		void color_change_23();
		void color_change_24();
		void color_change_25();
		void color_change_26();
		void color_change_27();
		void color_change_28();
		void color_change_29();
		void color_change_30();
		void color_change_31();
		void color_change_32();
		void color_change_33();
		void color_change_34();
		void color_change_35();
		void color_change_36();
		void color_change_37();
		void color_change_38();
		void color_change_39();
		void color_change_40();
		void color_change_41();
		void color_change_42();
		void color_change_43();
		void color_change_44();
		void color_change_45();
		void color_change_46();
		void color_change_47();
		void color_change_48();
		void color_change_self_1();
		void color_change_self_2();
		void color_change_self_3();
		void color_change_self_4();
		void color_change_self_5();
		void color_change_self_6();
		void color_change_self_7();
		void color_change_self_8();
		void color_change_self_9();
		void color_change_self_10();
		void color_change_self_11();
		void color_change_self_12();
		void color_change_self_13();
		void color_change_self_14();
		void color_change_self_15();
		void color_change_self_16();
		void color_change_self_17();
		void color_change_self_18();
		void color_change_self_19();
		void color_change_self_20();
		void color_change_self_21();
		void color_change_self_22();
		void color_change_self_23();
		void color_change_self_24();

		//改变颜色
		void color_change_spinbox(int number);//参数仅用于占位，无实际效果

		//滑块处理
		void color_slider_change(int value);//滑块颜色选取

		//其他按钮处理
		void color_select();//鼠标颜色选取
		void color_remove();//自定义颜色清除
		void color_add();//自定义颜色添加
		void color_accept();//确定文字颜色

		//关闭动画
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
	};
}

#endif