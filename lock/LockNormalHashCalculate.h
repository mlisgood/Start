#ifndef LOCKNORMALHASHCALCULATE_H
#define LOCKNORMALHASHCALCULATE_H

#include "define.h"

namespace rem
{

	//使用标准命名空间
	using std::string;

	//导入crypto++命名空间
	using namespace CryptoPP;

	class LockNormalHashCalculate : public QDialog
	{
		Q_OBJECT

	private:

		Ui::LockNormalHashCalculateClass ui;//窗口
		qreal timer_transparent_count;//计时器透明度计数
		QPoint m_point;//记录坐标用于移动窗口
		QGraphicsOpacityEffect *effect_1;//label_chara_1透明效果
		QGraphicsOpacityEffect *effect_2;//label_chara_2透明效果
		QTimer *timer;//计时器
		QValidator *validator;//限制文本框输入使用的模式
		QString method;//计算方法
		QString calculate_type;//计算类型
		string string_array[3];//存放字符串信息，按顺序分为：文件路径，文件名，输出历史文件路径
		char result[1024];//存放结果
		int timer_picture_count;//计时器图片顺序计数
		int timer_interval;//计时器计时间隔
		int key_size;//实际密钥长度
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		bool bool_array[1];//存放布尔值信息，按顺序分为：是否输出历史文件
		bool progress_bar_change_color;//进度条文字是否切换颜色
		bool is_continue;//在执行完另一界面后是否继续下面的操作

	public:

		//构造与析构函数
		LockNormalHashCalculate(QWidget *parent = Q_NULLPTR);
		~LockNormalHashCalculate();

		//设置成员函数
		void set_method(QString method);//设置加密方式，参数为加密方式

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

	signals:

		void show_lock_normal_window();//返回上一级信号
		void send_data(string *string_array, bool *bool_array, char *result, QString calculate_type, QString method);//发送数据
		void send_target_class_point(Export_HashCalculate_virtual_class *point);//发送dll导出类对象指针
		void send_dll_name(HINSTANCE dll_name);//发送dll名

	public slots:

		void timer_timeout();//计时器到期
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
		void combobox_change_method(const QString &combobox_string);//组合框内容更改后处理
		void combobox_change_type(const QString &combobox_string);//组合框内容更改后处理
		void file_explore();//浏览文件
		void calculate_file();//计算散列值
		void check_file();//校验文件
		void receive_hash_calculate_final(int length);//计算结束。参数为结果长度
		void receive_hash_calculate_final_check(int length);//计算结束，并进行比对。参数为结果长度
	};

	class HashCalculate_file_thread : public QThread//加密文件子线程
	{
		Q_OBJECT

	protected:

		Export_HashCalculate_virtual_class *target_class_point;//dll导出类对象指针
		HINSTANCE dll_name;//dll名
		QMutex mutex;//互斥锁
		QString method;//加密方法
		QString calculate_type;//计算类型
		string string_array[3];//存放字符串信息，按顺序分为：文件路径，文件名，输出历史文件路径
		char *result;//存放结果
		bool bool_array[1];//存放布尔值信息，按顺序分为：是否输出历史文件

	private:

		void run();//子线程主函数

	public:

		HashCalculate_file_thread();//构造函数
		~HashCalculate_file_thread();//析构函数

	public slots:

		void get_data(string *string_array, bool *bool_array, char *result, QString calculate_type, QString method);//获取全部数据
		void get_target_class_point(Export_HashCalculate_virtual_class *point);//获取dll导出类对象指针
		void get_dll_name(HINSTANCE dll_name);//获取dll名
		
	};

}

#endif