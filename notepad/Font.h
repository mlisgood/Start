#ifndef FONT_H
#define FONT_H

#include "define.h"

namespace rem
{
	class Font : public QDialog
	{
		Q_OBJECT

	private:

		Ui::FontClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QString filepath;//背景图片路径
		QString dialog_information_path;//窗口提示信息
		QTextEdit *textedit_font;//主界面文本框指针，用于修改字体
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		int totalrandomnumber;//用于决定全局的随机数
		int resource_randomnumber;//用于决定资源文件的随机数
		int hex_status;//是否为十六进制模式

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造与析构函数
		Font(QWidget *parent = Q_NULLPTR);
		~Font();

		//初始设置
		void read_font();//读取设置文件

		//设置成员变量
		void set_textedit(QTextEdit *main_textedit);//获取文本框地址
		void set_resource_random_number(int number, int status);//获取资源文件需要的数值变量

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		public slots:

		//组合框选项
		void combobox_change(const QString &);
		void font_change();

		//关闭动画
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
	};
}

#endif