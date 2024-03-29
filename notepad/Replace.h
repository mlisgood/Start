#ifndef REPLACE_H
#define REPLACE_H

#include "define.h"

namespace rem
{
	class Replace : public QDialog
	{
		Q_OBJECT

	private:

		Ui::ReplaceClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QString filepath;//背景图片路径
		QString chara_path;//左侧图片路径
		QString dialog_information_path;//窗口提示信息
		QTextEdit *textedit_find;//主界面文本框指针，用于查找和替换
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		int totalrandomnumber;//用于决定全局的随机数

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造与析构函数
		Replace(QWidget *parent = Q_NULLPTR);
		~Replace();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		//设置成员变量
		void set_dialog_information_path(QString inforation_path);//设置文字图片路径
		void set_textedit(QTextEdit *main_textedit);//获取文本框地址

		public slots:

		void find_text_last();//向后替换文本
		void find_text_next();//向前替换文本
		void find_text_all();//全部替换文本
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
	};
}

#endif