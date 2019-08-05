#ifndef FILE_H
#define FILE_H

#include "define.h"

namespace rem
{
	class File : public QDialog
	{
		Q_OBJECT

	private:

		Ui::FileClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QString filepath_background;//背景图片路径
		QString dialog_information_path_temp;//存储信息图片路径
		QString dialog_information_head_path_temp;//存储头部信息图片路径
		QString file_path_show;//用于显示的文件路径
		QString current_path;//当前工作路径
		QString *file_path;//文件路径指针
		QFileSystemModel *file_tree;//文件目录
		bool m_bPressed;//确定窗口是否被按下
		bool *file_dialog_status;//文件被打开或者保存以及退出该窗口的判断量
		bool open_or_save;//确认是打开还是保存，0为打开，1为保存
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		int totalrandomnumber;//用于决定全局的随机数

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造与析构函数
		File(QWidget *parent = Q_NULLPTR);
		~File();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		//设置成员变量
		void set_button_save_or_open(int status);//设置窗口类型是打开文件还是保存文件。标志：打开为0，保存为1
		void set_file_path_address(QString *path);//设置文件路径地址
		void set_file_dialog_status_address(bool *status);//设置窗口参数地址
		void set_current_path(QString object_string);//传入当前工作路径

		public slots:

		void get_tree_view_selected_file_name(const QModelIndex &index);//得到文件路径
		void get_text_edit_file_name();//文件路径文本框信息改变时获得文件路径
		void open_or_save_button();//打开或者保存按钮
		void open_or_save_branch();//分支双击
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
	};
}

#endif