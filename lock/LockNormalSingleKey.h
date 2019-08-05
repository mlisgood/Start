#ifndef LOCKNORMALSINGLEKEY_H
#define LOCKNORMALSINGLEKEY_H

#include "define.h"

namespace rem
{

	//使用标准命名空间
	using std::string;

	//导入crypto++命名空间
	using namespace CryptoPP;

	class LockNormalSingleKey : public QDialog
	{
		Q_OBJECT

	private:

		Ui::LockNormalSingleKeyClass ui;//窗口
		qreal timer_transparent_count;//计时器透明度计数
		QPoint m_point;//记录坐标用于移动窗口
		QGraphicsOpacityEffect *effect_1;//label_chara_1透明效果
		QGraphicsOpacityEffect *effect_2;//label_chara_2透明效果
		QTimer *timer;//计时器
		QValidator *validator;//限制文本框输入使用的模式
		QString method;//加密方法
		string string_array[8];//存放字符串信息，按顺序分为：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，输出历史文件路径，输出密钥文件路径后缀，输出二进制密钥文件路径后缀，临时文件夹路径
		char key[1024];//存放加解密密钥，最大数目取1024
		char char_array[5];//存放char*字符串信息，包含头部特征数字。预留一个字节给'\0'字符
		int timer_picture_count;//计时器图片顺序计数
		int timer_interval;//计时器计时间隔
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		bool bool_array[5];//存放布尔值信息，按顺序分为：是否输出历史文件，是否输出密钥文件，是否输出二进制密钥文件，是否有头部特征数字，是否加密最后一个区块
		bool progress_bar_change_color;//进度条文字是否切换颜色
		bool is_continue;//在执行完另一界面后是否继续下面的操作

	public:

		//构造与析构函数
		LockNormalSingleKey(QWidget *parent = Q_NULLPTR);
		~LockNormalSingleKey();

		//设置成员函数
		void set_method(QString method);//设置加密方式，参数为加密方式
		void update_unlock_information(QString head_digit, bool have_head_digit, QString key);//更新需要显示在界面上的信息，参数为：加密文件头部特征数字，是否有头部特征数字，密钥

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

	signals:

		void show_lock_normal_window();//返回上一级信号
		void send_data(string *string_array, bool *bool_array, char *char_array, char *key, QString method);//发送数据
		void send_target_class_point(Export_LockSingle_virtual_class *point);//发送dll导出类对象指针
		void send_dll_name(HINSTANCE dll_name);//发送dll名

	public slots:

		void timer_timeout();//计时器到期
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
		void combobox_change(const QString &combobox_string);//组合框内容更改后处理
		void lock_file();//加密方法
		void unlock_file();//解密方法
		void receive_lock_DES_process(double index);//DES加密文件进度条显示。参数为已处理部分比例
		void receive_lock_DES_final(bool is_success, char *key);//DES加密文件结束。参数为加密是否成功及密钥
		void receive_unlock_DES_process(double index);//DES解密文件进度条显示。参数为已处理部分比例
		void receive_unlock_DES_final(bool is_success);//DES解密文件结束。参数为加密是否成功及密钥
		void receive_lock_DES_EDE2_process(double index);//DES_EDE2加密文件进度条显示。参数为已处理部分比例
		void receive_lock_DES_EDE2_final(bool is_success, char *key);//DES_EDE2加密文件结束。参数为加密是否成功及密钥
		void receive_unlock_DES_EDE2_process(double index);//DES_EDE2解密文件进度条显示。参数为已处理部分比例
		void receive_unlock_DES_EDE2_final(bool is_success);//DES_EDE2解密文件结束。参数为加密是否成功及密钥
		void receive_lock_DES_EDE3_process(double index);//DES_EDE3加密文件进度条显示。参数为已处理部分比例
		void receive_lock_DES_EDE3_final(bool is_success, char *key);//DES_EDE3加密文件结束。参数为加密是否成功及密钥
		void receive_unlock_DES_EDE3_process(double index);//DES_EDE3解密文件进度条显示。参数为已处理部分比例
		void receive_unlock_DES_EDE3_final(bool is_success);//DES_EDE3解密文件结束。参数为加密是否成功及密钥
		void receive_lock_AES_MIN_process(double index);//AES_MIN加密文件进度条显示。参数为已处理部分比例
		void receive_lock_AES_MIN_final(bool is_success, char *key);//AES_MIN加密文件结束。参数为加密是否成功及密钥
		void receive_unlock_AES_MIN_process(double index);//AES_MIN解密文件进度条显示。参数为已处理部分比例
		void receive_unlock_AES_MIN_final(bool is_success);//AES_MIN解密文件结束。参数为加密是否成功及密钥
		void receive_lock_AES_MIDDLE_process(double index);//AES_MIDDLE加密文件进度条显示。参数为已处理部分比例
		void receive_lock_AES_MIDDLE_final(bool is_success, char *key);//AES_MIDDLE加密文件结束。参数为加密是否成功及密钥
		void receive_unlock_AES_MIDDLE_process(double index);//AES_MIDDLE解密文件进度条显示。参数为已处理部分比例
		void receive_unlock_AES_MIDDLE_final(bool is_success);//AES_MIDDLE解密文件结束。参数为加密是否成功及密钥
		void receive_lock_AES_MAX_process(double index);//AES_MAX加密文件进度条显示。参数为已处理部分比例
		void receive_lock_AES_MAX_final(bool is_success, char *key);//AES_MAX加密文件结束。参数为加密是否成功及密钥
		void receive_unlock_AES_MAX_process(double index);//AES_MAX解密文件进度条显示。参数为已处理部分比例
		void receive_unlock_AES_MAX_final(bool is_success);//AES_MAX解密文件结束。参数为加密是否成功及密钥
	};

	class Lock_single_file_thread : public QThread//加密文件子线程
	{
		Q_OBJECT

	protected:

		Export_LockSingle_virtual_class *target_class_point;//dll导出类对象指针
		HINSTANCE dll_name;//dll名
		QMutex mutex;//互斥锁
		QString method;//加密方法
		string string_array[8];//存放字符串信息，按顺序分为：文件路径，文件名，输出文件前半部分不变路径，输出文件路径后缀，输出历史文件路径，输出密钥文件路径，输出二进制密钥文件路径，临时文件夹路径
		char *key;//存放加解密密钥
		bool bool_array[5];//存放布尔值信息，按顺序分为：是否输出历史文件，是否输出密钥文件，是否输出二进制密钥文件，是否有头部特征数字，是否加密最后一个区块
		char *char_array;//存放char字符串信息，包含头部特征数字

	private:

		void run();//子线程主函数

	public:

		Lock_single_file_thread();//构造函数
		~Lock_single_file_thread();//析构函数

	public slots:

		void get_data(string *string_array, bool *bool_array, char *char_array, char *key, QString method);//获取全部数据
		void get_target_class_point(Export_LockSingle_virtual_class *point);//获取dll导出类对象指针
		void get_dll_name(HINSTANCE dll_name);//获取dll名
	};

	class Unlock_single_file_thread : public Lock_single_file_thread//解密文件子线程
	{
		Q_OBJECT

	private:

		void run();//子线程主函数

	public:

		Unlock_single_file_thread();//构造函数
		~Unlock_single_file_thread();//析构函数

	};
}

#endif