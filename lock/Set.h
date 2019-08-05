#ifndef SET_H
#define SET_H

#include "define.h"

namespace rem
{
	class Set : public QDialog
	{
		Q_OBJECT

	private:

		Ui::SetClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QPixmap main_picture;//需要绘制以便于作为窗口的图片
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环

	protected:

		void paintEvent(QPaintEvent *); //绘制背景图像

	public:

		//构造与析构函数
		Set(QWidget *parent = Q_NULLPTR);
		~Set();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		//路径信息获取
		void set_save_path(QLineEdit *lineEdit);//从文件打开界面获取路径信息，参数为待显示的QLineEdit
		void run_path(QString path, QString default_path);//打开相应路径。该函数不需要考虑入口函数的参数数目，不论是选择程序本体（1个入口参数）还是程序目标（2个入口参数）都能直接打开。参数是文件路径和默认路径

		//其他功能函数
		bool delete_files(QString path);//删除文件夹下全部文件，不包括文件夹。参数为文件夹路径

	public slots:

		void open_path_lock();//打开加密文件路径
		void open_path_unlock();//打开解密文件路径
		void open_path_temp();//打开临时文件路径
		void open_path_history();//打开历史文件路径
		void delete_temp();//删除临时文件
		void delete_history();//清空历史文件
		void get_path_lock();//获得加密文件路径输入
		void get_path_unlock();//获得解密文件路径输入
		void get_path_temp();//获得临时文件路径输入
		void get_path_history();//获得历史文件路径输入
		void set_apply();//设置生效
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
	};
}

#endif