#ifndef FILEMISSING_H
#define FILEMISSING_H

#include "define.h"

namespace rem
{
	class Filemissing : public QDialog
	{
		Q_OBJECT

	private:

		Ui::FilemissingClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QString filepath;//背景图片路径
		QString chara_path;//左侧图片路径
		QString information_path;//窗口提示信息
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		int totalrandomnumber;//用于决定全局的随机数
		int information_status;//决定信息显示内容的标志

	protected:

		void paintEvent(QPaintEvent *); //绘制背景图像

	public:

		//构造与析构函数
		Filemissing(QWidget *parent = Q_NULLPTR);
		~Filemissing();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		//设置成员变量
		void set_dialog_information_status(int dialog_information_status);//设置成员变量information_status的值。参数：想要设置的标志。1为内存不足，2为无法打开文件。
		
	public slots:
	
		//槽函数
		void close_window_include_animation();//关闭窗口
	};
}

#endif