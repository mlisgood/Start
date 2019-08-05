#ifndef DESKTOP_H
#define DESKTOP_H 

#include "define.h"

namespace rem
{

	//导入标准命名空间
	using std::wstring;

	class Desktop : public QMainWindow
	{
		Q_OBJECT

	private:

		Ui::DesktopClass ui;
		QPoint m_point;//记录坐标用于移动窗口
		QTimer *time_counter;//主界面计时器
		QSystemTrayIcon *system_tray_icon;//系统托盘图标
		QMenu *system_tray_menu;//托盘菜单
		QAction *action_static_set;//托盘菜单静态配置文件功能
		QAction *action_dynamic_set;//托盘菜单动态配置文件功能
		QAction *action_auto_start_set;//托盘菜单开机自启动配置功能
		QAction *action_help;//托盘菜单信息功能
		QAction *action_exit;//托盘菜单退出功能
		QPixmap background_picture;//背景图片
		QString background_path;//背景路径
		wstring widget_path[7];//控件打开程序路径
		double transparent;//透明度
		int randnumber;//决定背景的随机数
		int position[2];//显示时的位置
		int screen_resolution[2];//当前分辨率
		int timer_interval_number;//计时器计时间隔
		int widget_transparent[7];//控件不透明度
		bool on_top;//确定窗口是否在顶层，true表示在窗口顶层，false表示不在顶层
		bool counter_already_run;//确定计时器是否已经在运行
		bool is_hide;//确定窗口是否被隐藏，false表示未被隐藏，true表示被隐藏，被隐藏时可以接收鼠标点击显示事件
		bool is_hide_available;//确定窗口是否可以被隐藏
		bool is_special_effect;//确定窗口是否有鼠标特效
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		bool widget_is_enable[7];//控件是否使用
		bool widget_is_on_top[7];//控件是否位于最顶层
		bool autorun;//是否开机自启动
		bool move_enable;//是否移动的数值会被记录进配置文件
		bool m_bPressed;//确定窗口是否被按下

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造和析构函数
		Desktop(QWidget *parent = Q_NULLPTR);
		~Desktop();

		//系统托盘
		void create_system_tray_menu();//添加系统托盘菜单
		void create_system_tray_menu_action();//添加系统托盘菜单功能

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件
		void keyPressEvent(QKeyEvent *event);

		//其他功能
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
		void key_press_method(int widget_id);//键盘事件处理

		//槽函数
		public slots:

			void system_tray_icon_clicked(QSystemTrayIcon::ActivationReason);//系统托盘点击事件
			void show_system_tray_action_set_static();//菜单常规设置功能
			void show_system_tray_action_set_dynamic();//菜单特殊设置功能
			void show_system_tray_action_set_other();//菜单开机自启动功能
			void show_system_tray_action_help();//菜单信息功能
			void show_system_tray_action_exit();//菜单退出功能
			void time_hide_animation_disappear();//隐藏过程计时器到期消失动画播放
			void time_hide_animation_appear();//隐藏过程计时器到期出现动画播放
			void time_hide_repaint();//隐藏过程计时器到期绘制窗口函数
			void show_animation_appear();//显示过程出现动画播放

	};
}

#endif