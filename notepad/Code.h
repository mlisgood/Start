#ifndef CODE_H
#define CODE_H

#include "define.h"

namespace rem
{
	class Code : public QDialog
	{
		Q_OBJECT

	private:

		Ui::CodeClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QLabel *code_label;//主界面代码信息显示框
		QString filepath;//背景图片路径
		QString chara_path;//左侧图片路径
		QString dialog_information_path;//窗口提示信息
		QString *code_receive;//接收来自主窗口的编码信息
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		int totalrandomnumber;//用于决定全局的随机数
		int hex_status;//是否处于二进制编辑状态

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造与析构函数
		Code(QWidget *parent = Q_NULLPTR);
		~Code();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		//设置成员变量
		void set_code_information(QString* code_information, QLabel *code_label_main_dialog, int status);//获取编码信息和是否处于二进制编辑状态

		public slots:

		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法	 
		void combobox_change(const QString &code_string);//组合框选项
		void dialog_accept();//确认操作
	};
}

#endif