#ifndef LOCKNORMALDOUBLEKEY_H
#define LOCKNORMALDOUBLEKEY_H

#include "define.h"

namespace rem
{

	//使用标准命名空间
	using std::string;

	//导入crypto++命名空间
	using namespace CryptoPP;

	class LockNormalDoubleKey : public QDialog
	{

		Q_OBJECT

	private:

		Ui::LockNormalDoubleKeyClass ui;//窗口
		qreal timer_transparent_count;//计时器透明度计数
		QPoint m_point;//记录坐标用于移动窗口
		QGraphicsOpacityEffect *effect_1;//label_chara_1透明效果
		QGraphicsOpacityEffect *effect_2;//label_chara_2透明效果
		QTimer *timer;//计时器
		QValidator *validator_1;//限制文本框输入使用的模式
		QValidator *validator_2;//限制文本框输入使用的模式
		QValidator *validator_3;//限制文本框输入使用的模式
		QString method;//加密方法
		QString curve_type;//ECC加密曲线类型
		string string_array[8];//存放字符串信息，按顺序分为：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，输出历史文件路径，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，临时文件夹路径
		char public_key[4096];//存放公钥
		char private_key[4096];//存放私钥
		char char_array[5];//存放char*字符串信息，包含头部特征数字。预留一个字节给'\0'字符
		int timer_picture_count;//计时器图片顺序计数
		int timer_interval;//计时器计时间隔
		int key_size;//实际密钥长度
		int size;//RSA加密组合框中选择的密钥长度
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		bool bool_array[4];//存放布尔值信息，按顺序分为：是否输出历史文件，是否输出密钥文件，是否输出二进制密钥文件，是否有头部特征数字
		bool progress_bar_change_color;//进度条文字是否切换颜色
		bool is_continue;//在执行完另一界面后是否继续下面的操作

	public:

		//构造与析构函数
		LockNormalDoubleKey(QWidget *parent = Q_NULLPTR);
		~LockNormalDoubleKey();

		//设置成员函数
		void update_lock_information(QString head_digit, bool have_head_digit, QString key);//更新加密前需要显示在界面上的信息，参数为：加密文件头部特征数字，是否有头部特征数字，密钥
		void update_unlock_information(QString head_digit, bool have_head_digit, QString key);//更新解密前需要显示在界面上的信息，参数为：加密文件头部特征数字，是否有头部特征数字，密钥
		void set_method(QString method);//设置加密方式，参数为加密方式

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

	signals:

		void show_lock_normal_window();//返回上一级信号
		void send_data(string *string_array, bool *bool_array, char *char_array, char *key, int size, QString method);//发送数据
		void send_target_class_point(Export_LockDouble_virtual_class *point);//发送dll导出类对象指针
		void send_dll_name(HINSTANCE dll_name);//发送dll名
		void send_key_data(string *string_array, bool *bool_array, char *char_array, char *public_key, char *private_key, QString method, int size, QString curve_type, string output_path);//发送密钥数据

	public slots:

		void timer_timeout();//计时器到期
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
		void combobox_change_method(const QString &combobox_string);//组合框内容更改后处理
		void combobox_change_size(const QString &combobox_string);//组合框内容更改后处理
		void lock_file();//加密方法
		void unlock_file();//解密方法
		void set_key();//设置密钥
		void set_key_final(int public_key_length, int private_key_length);//设置密钥完毕，参数为公钥和私钥长度
		void receive_lock_out_of_range();//加密文件内容超出范围
		void receive_lock_wrong_key();//加密密钥过短或文件内容超出范围
		void receive_lock_final(bool is_success);//加密文件结束。参数为加密是否成功
		void receive_unlock_out_of_range();//解密文件内容超出范围
		void receive_unlock_wrong_key();//解密密钥过短或文件内容超出范围
		void receive_unlock_final(bool is_success);//解密文件结束。参数为加密是否成功
	};

	class Lock_double_file_thread : public QThread//加密文件子线程
	{

		Q_OBJECT

	protected:

		Export_LockDouble_virtual_class *target_class_point;//dll导出类对象指针
		HINSTANCE dll_name;//dll名
		QMutex mutex;//互斥锁
		QString method;//加密方法
		string string_array[8];//存放字符串信息，按顺序分为：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，输出历史文件路径，输出密钥文件路径，输出二进制密钥文件路径，临时文件夹路径
		char *key;//存放加解密密钥
		bool bool_array[4];//存放布尔值信息，按顺序分为：是否输出历史文件，是否输出密钥文件，是否输出二进制密钥文件，是否有头部特征数字
		char *char_array;//存放char字符串信息，包含头部特征数字
		int size;//密钥长度

	private:

		void run();//子线程主函数

	public:

		Lock_double_file_thread();//构造函数
		~Lock_double_file_thread();//析构函数

	public slots:

		void get_data(string *string_array, bool *bool_array, char *char_array, char *key, int size, QString method);//获取全部数据
		void get_target_class_point(Export_LockDouble_virtual_class *point);//获取dll导出类对象指针
		void get_dll_name(HINSTANCE dll_name);//获取dll名
		
	};

	class Unlock_double_file_thread : public Lock_double_file_thread//解密文件子线程
	{

		Q_OBJECT

	private:

		void run();//子线程主函数

	public:

		Unlock_double_file_thread();//构造函数
		~Unlock_double_file_thread();//析构函数

	};

	class Lock_double_get_key_thread : public QThread//加密文件子线程
	{
		Q_OBJECT

	protected:

		Export_LockDouble_virtual_class *target_class_point;//dll导出类对象指针
		HINSTANCE dll_name;//dll名
		QMutex mutex;//互斥锁
		QString method;//加密方法
		QString curve_type;//ECC加密曲线类型
		string string_array[3];//存放字符串信息，按顺序分为输出历史文件路径，输出密钥文件路径，输出二进制密钥文件路径
		string output_path;//输出密钥文件路径
		int size;//RSA加密密钥长度
		char *public_key;//存放公钥
		char *private_key;//存放私钥
		bool bool_array[4];//存放布尔值信息，按顺序分为：是否输出历史文件，是否输出密钥文件，是否输出二进制密钥文件，是否有头部特征数字
		char *char_array;//存放char字符串信息，包含头部特征数字

	private:

		void run();//子线程主函数

	public:

		Lock_double_get_key_thread();//构造函数
		~Lock_double_get_key_thread();//析构函数

	public slots:

		void get_key_data(string *string_array, bool *bool_array, char *char_array, char *public_key, char *private_key, QString method, int size, QString curve_type, string output_path);//获取全部数据
		void get_target_class_point(Export_LockDouble_virtual_class *point);//获取dll导出类对象指针
		void get_dll_name(HINSTANCE dll_name);//获取dll名
	};
}

#endif