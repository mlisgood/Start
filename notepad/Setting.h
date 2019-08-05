#ifndef SETTING_H
#define SETTING_H

#include "define.h"

namespace rem
{
	class Setting : public QDialog
	{
		Q_OBJECT

	private:

		Ui::SettingClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QStringList *setting_text_address;//主窗口文本类型后缀地址
		QStringList *setting_binary_address;//主窗口二进制类型后缀地址
		QString filepath;//背景图片路径
		QString dialog_information_path;//窗口提示信息
		QString *setting_default_open_method_address;//主窗口打开文件默认方式地址
		QTextEdit *textedit_main;//主界面文本框指针，用于修改自动换行状态
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		bool *setting_bool_value_address[3];//主窗口布尔值地址
		int totalrandomnumber;//用于决定全局的随机数
		int *setting_size_address[2];//主窗口文件块大小地址

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造与析构函数
		Setting(QWidget *parent = Q_NULLPTR);
		~Setting();

		//设置成员变量
		void set_textedit(QTextEdit *main_textedit);//获取文本框地址
		void set_setting_text_address(QStringList *main_list);//获取主界面字符串组1地址
		void set_setting_binary_address(QStringList *main_list);//获取主界面字符串组2地址
		void set_setting_default_open_method_address(QString *main_string);//获取主界面字符串地址
		void set_setting_bool_value_address(bool *main_array_index, int index);//获取主界面bool类型数组元素地址
		void set_setting_size_address(int *main_array_index, int index);//获取主界面int类型数组元素地址

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		public slots:

			//列表操作按钮
			void list_1_button();//添加
			void list_2_button();//删除一项
			void list_3_button();//删除全部
			void list_4_button();//添加
			void list_5_button();//删除一项
			void list_6_button();//删除全部

			//确定按钮操作
			void accept_button();//确认操作

			//关闭动画
			void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
	};
}

#endif