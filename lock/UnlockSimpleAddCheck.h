#ifndef UNLOCKSIMPLEADDCHECK_H
#define UNLOCKSIMPLEADDCHECK_H

#include "define.h"

namespace rem
{
	class UnlockSimpleAddCheck : public QDialog
	{
		Q_OBJECT

	private:

		Ui::UnlockSimpleAddCheckClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QPixmap main_picture;//需要绘制以便于作为窗口的图片
		QString *char_point_information;//从加减加密主界面得到的char指针型信息，包括：加密文件头部特征数字
		QString char_point_information_data;//从加减加密主界面得到的char指针型信息，包括：加密文件头部特征数字
		int *int_information;//从加减加密主界面得到的整数型信息，包括：加密方向
		int int_information_data;//从加减加密主界面得到的整数型信息，包括：加密方向
		int *extra_int_information[17];//从加减加密主界面得到的整数型信息，包括：加减数量，最后一个元素存放循环周期
		int extra_int_information_data[17];//从加减加密主界面得到的整数型信息，包括：加减数量，最后一个元素存放循环周期
		int bool_information_data_int;//从加减加密主界面得到的布尔型信息，包括：是否有头部特征数字。为了便于读取文件，使用int类型
		long long *long_long_information[2];//从加减加密主界面得到的长整数型信息，包括：头部忽略字节，尾部忽略字节
		long long long_long_information_data[2];//从加减加密主界面得到的长整数型信息，包括：头部忽略字节，尾部忽略字节
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		bool *bool_information;//从加减加密主界面得到的布尔型信息，包括：是否有头部特征数字
		bool bool_information_data;//从加减加密主界面得到的布尔型信息，包括：是否有头部特征数字
		bool *is_continue;//主界面在执行完另一界面后是否继续下面的操作

	protected:

		void paintEvent(QPaintEvent *); //绘制背景图像

	public:

		//构造与析构函数
		UnlockSimpleAddCheck(QWidget *parent = Q_NULLPTR);
		~UnlockSimpleAddCheck();

		//设置成员函数
		void set_information(int *direction, long long *head_offset, long long *tail_offset, int *cycle, QString *head_digit, bool *have_head_digit, bool *is_continue, int *operate_count);//设置需要显示在界面上的信息，参数为：加密方向（1：顺序加密，2：倒序加密，3：双向加密），头部忽略字节，尾部忽略字节，循环周期，加密文件头部特征数字，是否有头部特征数字，是否确认解密，加减数量
		void set_information_data(int direction, long long head_offset, long long tail_offset, int cycle, QString head_digit, bool have_head_digit, int *operate_count);//设置需要显示在界面上的信息，但不再传入指针，供之后使用。如果在之后使用指针传递，则会造成指针指向的地址改变，那么在确认后无法修改主窗口中相关属性的值

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		public slots:
		
			void set_apply();//设置生效
			void cancel_apply();//设置取消
			void import_set();//导入设置
			void look_set();//查看设置
			void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
	};
}

#endif