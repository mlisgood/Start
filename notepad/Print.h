#ifndef PRINT_H
#define PRINT_H

#include "define.h"

namespace rem
{
	class Print : public QDialog
	{
		Q_OBJECT

	private:

		Ui::PrintClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QTimer *timer_print;//主界面计时器
		QLabel *label_chara_print;//主界面人物形象标签
		QLabel *label_margin_print;//主界面左侧边界标签
		QTextEdit *textedit_print;//主界面文本框
		QString chara_path_print;//主界面人物形象正常状态路径
		QString filepath;//背景图片路径
		QString chara_path;//左侧图片路径
		QString dialog_information_path;//窗口提示信息
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		int *flag_print;//主界面计时器状态
		int totalrandomnumber;//用于决定全局的随机数

	public:

		//构造与析构函数
		Print(QWidget *parent = Q_NULLPTR);
		~Print();

		//成员变量设置
		void set_textedit(QTextEdit *main_textedit);//获取主界面文本框地址
		void set_timer(QTimer *main_timer);//获取主界面计时器地址
		void set_label_chara(QLabel *main_label);//获取主界面人物形象标签地址
		void set_label_margin(QLabel *main_label);//获取主界面左侧边界标签地址
		void set_chara_path(QString main_chara_path);//获取主界面人物形象正常状态路径
		void set_flag(int *main_flag);//获取主界面计时器状态

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		public slots:

		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法	 
		void dialog_accept();//确认操作
	};
}

#endif