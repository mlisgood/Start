#ifndef NOTEPAD_H
#define NOTEPAD_H

#include "define.h"

namespace rem
{

	//使用标准命名空间
	using std::string;

	class Notepad : public QMainWindow
	{
		Q_OBJECT

	private:

		Ui::NotepadClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QTimer *chara_picture_timer;//显示人物图像计时器
		QPixmap chara_picture;//人物形象图片
		QPixmap chara_picture_extra;//人物形象特殊状态图片
		QPixmap margin_picture;//左侧边界图片
		QLabel *chara_picture_label;//人物图像显示用到的标签
		QLabel *margin_picture_label;//边框图像显示用到的标签
		QStringList setting_text;//其他设置文本类型后缀
		QStringList *setting_text_address;//其他设置文本类型后缀地址
		QStringList setting_binary;//其他设置二进制类型后缀
		QStringList *setting_binary_address;//其他设置二进制类型后缀地址
		QString dialog_information;//提示框信息内容
		QString current_file_name;//当前文件名
		QString file_dialog_file_name;//用于打开与保存文件窗口传输的文件名
		QString *file_dialog_file_name_address;//用于打开与保存文件窗口传输的文件名地址
		QString *text_code;//文件编码
		QString code_undefine;//文件编码默认值
		QString chara_path_normal;//人物形象普通
		QString chara_path_close_eye;//人物形象切换
		QString setting_default_open_method;//其他设置打开文件默认方式
		QString *setting_default_open_method_address;//其他设置打开文件默认方式地址
		string args_string;//传入的入口参数
		bool m_bPressed;//确定窗口是否被按下
		bool file_dialog_status;//确定打开与保存文件窗口中是否选择打开或保存文件，false为退出，true为打开或保存
		bool *file_dialog_status_address;//确定打开与保存文件窗口中是否选择打开或保存文件判断量地址
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		bool setting_bool_value[3];//其他设置布尔值，分别表示其他设置窗口的三个选项
		bool *setting_bool_value_address[3];//其他设置布尔值地址
		int chara_randnumber;//显示人物图像随机数
		int randnumber;//用于画图的随机数
		int font_randnumber;//字体和色彩文件输入所使用的随机数
		int timer_interval_number;//计时器间隔时间
		int timer_chara_status;//人物形象状态，决定计时器间隔时间长短
		int *timer_chara_status_address;//人物形象状态地址
		int hex_status;//表明是否是十六进制状态
		int setting_size[2];//其他设置处理文件块大小，分别表示text和binary
		int *setting_size_address[2];//其他设置处理文件块大小地址
		int progress_bar_change_color;//进度条字体是否已经切换颜色

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造与析构函数
		Notepad(QWidget *parent = Q_NULLPTR);
		~Notepad();

		//配置文件设置
		void setting_file_read();//设置文件读取
		void setting_file_font_read();//字体设置文件读取，因为字体文件在之后也会用到，因此单独做成一个函数

		//成员变量设置
		void set_args_string(string object_string);//获取通过右键菜单等方式打开程序时传入的目标文件路径
		void set_current_path(QString object_string);//设置文件打开或保存窗口使用的路径

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于响应快捷键
		void keyPressEvent(QKeyEvent *event);

		//拖拽事件，用于拖拽打开文件
		void dragEnterEvent(QDragEnterEvent *e);
		void dropEvent(QDropEvent *e);

		//功能函数
		bool file_save(QString name);//实际的保存功能。这里用到了大量常量，如要修改最好重写
		bool save_status();//是否需要保存
		void file_load(QString name);//加载文件。这里用到了大量常量，如要修改最好重写
		void set_file_name(QString name);//设置文件名并初始化文本框修改状态

	signals:

		void send_file_name(QString file_name);//传递文件名
		void send_file_size(int file_size);//传递一次处理文件块大小
		void send_file_code(QString file_code);//传递文件编码
		void send_file_output(QString file_output);//传递文件需要输出的内容
		void send_file_addspace(bool file_addspace);//传递是否添加空格的布尔值

	public slots:

		void timer_chara_picture_timeout();//处理计时器到期事件。参数：计时器对象
		void text_line_and_col();//文本框获得所在行数和列数
		void close_dialog();//关闭窗口按钮
		void set_not_save_status();//设置未保存标记

		//各项功能
		void textedit_copy();//复制
		void textedit_paste();//粘贴
		void textedit_cut();//剪切
		void textedit_undo();//撤销
		void textedit_redo();//重做
		void textedit_font();//字体
		void textedit_color();//颜色
		void textedit_help();//程序信息
		void textedit_new();//新建
		void textedit_open();//打开
		bool textedit_save();//保存
		bool textedit_saveas();//另存为
		void textedit_find();//查找
		void textedit_replace();//替换
		void textedit_tohex();//十六进制转换
		void textedit_code();//编码转换
		void textedit_setting();//其他设置
		void textedit_print();//打印

		//关闭动画
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法

		//File_read_text_thread类的子线程数据接收
		void get_data_t_r(QString data, bool status);//显示内容，status决定是否为最后一次
		void get_index_t_r(long long index, long long total_size);//进度条显示
		void get_advance_final_t_r();//隐藏进度提示并显示进度条
		void get_final_t_r();//隐藏进度条

		//File_write_text_thread类的子线程数据接收
		void get_final_t_w();//隐藏进度提示

		//File_read_binary_thread类的子线程数据接收
		void get_data_b_r(QString data, bool status);//显示内容，status决定是否为最后一次
		void get_index_b_r(long long index, long long total_size);//进度条显示
		void get_final_b_r();//隐藏进度条

		//File_write_text_thread类的子线程数据接收
		void get_final_b_w();//隐藏进度提示
	};

	class File_read_text_thread : public QThread//读取文本文件子线程
	{
		Q_OBJECT

	protected:

		QMutex mutex;//互斥锁
		QString data;//数据流
		QString file_name;//文件名
		QString file_code;//文件编码
		char *data_transform;//读取后未转换数据流
		int index;//已处理大小
		int file_size;//一次处理文件块大小

	private:

		void run();//子线程主函数

	public:

		File_read_text_thread();//构造函数
		~File_read_text_thread();//析构函数

	signals:

		void send_data(QString data, bool status);//传递主线程的数据流，status决定是否为最后一次
		void send_index(long long index, long long total_size);//传递主线程已处理大小，同时传递总大小便于计算比例
		void send_advance_final();//文件预处理完毕
		void send_final();//文件处理完毕

	public slots:

		void get_file_name(QString file_name);//获取文件名
		void get_file_size(int file_size);//获取一次处理文件块大小
		void get_file_code(QString file_code);//获取文件编码
	};

	class File_write_text_thread : public File_read_text_thread//保存文本文件子线程，不需要再继承QThread，因为父类已经继承
	{
		Q_OBJECT

	private:

		QString file_output;//需要写入文件的数据
		void run();//子线程主函数

	public:

		File_write_text_thread();//构造函数
		~File_write_text_thread();//析构函数

	signals:

		void send_final();//文件处理完毕

	public slots:

		void get_file_output(QString file_output);//获得文件需要输出的内容
	};

	class File_read_binary_thread : public File_read_text_thread//读取二进制文件子线程
	{
		Q_OBJECT

	private:

		bool file_addspace;//决定是否插入空格的布尔值
		void run();//子线程主函数

	public:

		File_read_binary_thread();//构造函数
		~File_read_binary_thread();//析构函数

	signals:

		void send_data(QString data, bool status);//传递主线程的数据流，status决定是否为最后一次
		void send_index(long long index, long long total_size);//传递主线程已处理大小，同时传递总大小便于计算比例
		void send_advance_final();//文件预处理完毕
		void send_final();//文件处理完毕

	public slots:

		void get_file_addspace(bool file_addspace);//获取是否添加空格的布尔值
	};

	class File_write_binary_thread : public File_read_text_thread//保存文本文件子线程，不需要再继承QThread，因为父类已经继承
	{
		Q_OBJECT

	private:

		QString file_output;//需要写入文件的数据
		void run();//子线程主函数

	public:

		File_write_binary_thread();//构造函数
		~File_write_binary_thread();//析构函数

	signals:

		void send_final();//文件处理完毕

	public slots:

		void get_file_output(QString file_output);//获得文件需要输出的内容
	};
}
#endif