#ifndef LOCKSIMPLEOPPOSITE_H
#define LOCKSIMPLEOPPOSITE_H

#include "define.h"

namespace rem
{

	//使用标准命名空间
	using std::string;

	class LockSimpleOpposite : public QDialog
	{
		Q_OBJECT

	private:

		Ui::LockSimpleOppositeClass ui;//窗口
		qreal timer_transparent_count;//计时器透明度计数
		QPoint m_point;//记录坐标用于移动窗口
		QGraphicsOpacityEffect *effect_1;//label_chara_1透明效果
		QGraphicsOpacityEffect *effect_2;//label_chara_2透明效果
		QTimer *timer;//计时器
		QValidator *validator;//限制文本框输入使用的模式
		string string_array[8];//存放字符串信息，按顺序分为：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，输出历史文件路径，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，临时文件夹路径
		long long digit_array[3];//存放long long型数值信息，按顺序分为：头部处理起点，尾部处理起点，循环周期
		char char_array[5];//存放char*字符串信息，包含头部特征数字。预留一个字节给'\0'字符
		int flag_array[1];//存放int型标记信息，按顺序分为：加密方向（1代表顺序，2代表倒序，3代表双方向）
		int LockSimpleOpposite_already_send_size;//已经发送大小
		int LockSimpleOpposite_file_size;//文件大小
		int timer_picture_count;//计时器图片顺序计数
		int timer_interval;//计时器计时间隔
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		bool bool_array[4];//存放布尔值信息，按顺序分为：是否输出历史文件，是否输出密钥文件，是否输出二进制密钥文件，是否有头部特征数字
		bool progress_bar_change_color;//进度条文字是否切换颜色
		bool is_continue;//在执行完另一界面后是否继续下面的操作

	public:

		//构造与析构函数
		LockSimpleOpposite(QWidget *parent = Q_NULLPTR);
		~LockSimpleOpposite();

		//设置成员函数
		void update_unlock_information(int direction, long long head_offset, long long tail_offset, long long cycle, QString head_digit, bool have_head_digit);//更新需要显示在界面上的加密信息，参数为：加密方向（1：顺序加密，2：倒序加密，3：双向加密），头部忽略字节，尾部忽略字节，加密文件头部特征数字，是否有头部特征数字

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

	signals:

		void show_lock_simple_window();//返回上一级信号
		void send_data(string *string_array, bool *bool_array, long long *digit_array, int *flag_array, char* char_array);//发送数据
		void send_target_class_point(Export_LockSimple_virtual_class *point);//发送dll导出类对象指针
		void send_dll_name(HINSTANCE dll_name);//发送dll名

	public slots:

		void timer_timeout();//计时器到期
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
		void lock_file();//加密方法
		void unlock_file();//解密方法
		void receive_lock_simple_opposite_process(double index);//取反加密文件进度条显示。参数为已处理部分比例
		void receive_lock_simple_opposite_final(bool is_success);//取反加密文件结束。参数为加密是否成功
		void receive_unlock_simple_opposite_process(double index);//取反解密文件进度条显示。参数为已处理部分比例
		void receive_unlock_simple_opposite_final(bool is_success);//取反解密文件结束。参数为加密是否成功
	};

	class Lock_file_thread : public QThread//加密文件子线程
	{
		Q_OBJECT

	protected:

		Export_LockSimple_virtual_class *target_class_point;//dll导出类对象指针
		HINSTANCE dll_name;//dll名
		QMutex mutex;//互斥锁
		string string_array[8];//存放字符串信息，按顺序分为：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，输出历史文件路径，输出密钥文件路径，输出二进制密钥文件路径，临时文件夹路径
		bool bool_array[4];//存放布尔值信息，按顺序分为：是否输出历史文件，是否输出密钥文件，是否输出二进制密钥文件，是否有头部特征数字
		long long digit_array[3];//存放long long型数值信息，按顺序分为：头部处理起点，尾部处理起点，循环周期
		int flag_array[1];//存放int型标记信息，按顺序分为：加密方向
		char *char_array;//存放char字符串信息，包含头部特征数字

	private:

		void run();//子线程主函数

	public:

		Lock_file_thread();//构造函数
		~Lock_file_thread();//析构函数

	public slots:

		void get_data(string *string_array, bool *bool_array, long long *digit_array, int *flag_array, char* char_array);//获取全部数据
		void get_target_class_point(Export_LockSimple_virtual_class *point);//获取dll导出类对象指针
		void get_dll_name(HINSTANCE dll_name);//获取dll名
	};

	class Unlock_file_thread : public Lock_file_thread//解密文件子线程
	{
		Q_OBJECT

	private:

		void run();//子线程主函数

	public:

		Unlock_file_thread();//构造函数
		~Unlock_file_thread();//析构函数

	};
}

#endif