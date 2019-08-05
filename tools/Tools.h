#ifndef TOOLS_H
#define TOOLS_H

#include "define.h"

namespace rem
{
	class Tools : public QMainWindow
	{
		Q_OBJECT

	private:

		Ui::ToolsClass ui;
		QSystemTrayIcon *system_tray_icon;//系统托盘图标
		QPixmap main_picture;//需要绘制以便于作为窗口的图片
		QPixmap screenshot_picture;//截图功能用到的图片
		QPoint m_point;//记录坐标用于移动窗口
		QMenu *system_tray_menu;//托盘菜单
		QTimer *time_counter;//隐藏窗口用计时器
		QAction *action_set;//托盘菜单配置文件功能
		QAction *action_set_extra;//托盘菜单高级设置功能
		QAction *action_set_sound_record;//托盘菜单录音设置功能
		QAction *action_help;//托盘菜单信息功能
		QAction *action_exit;//托盘菜单退出功能
		QString setting_picture_mainpicture;//配置文件信息，背景图片
		QString setting_function_program[8];//配置文件信息，各个程序
		QString setting_font_font;//配置文件信息，便签窗口字体
		QString setting_extra_index[9];//配置文件额外信息
		QString main_picture_normal_hole_path;//常规状况下完整图片路径
		QString main_picture_hide_hole_path;//隐藏状况下完整图片路径
		bool m_bPressed;//确定窗口是否被按下
		bool on_top;//确定窗口是否在顶层，true表示在窗口顶层，false表示不在顶层
		bool counter_already_run;//确定计时器是否已经在运行
		bool is_hide;//确定窗口是否被隐藏，false表示未被隐藏，true表示被隐藏，被隐藏时可以接收鼠标点击显示事件
		bool screenshot_end_mouse_event_disable;//截图后屏蔽鼠标点击悬浮组件事件，以免悬浮组件出现和消失的动画被再次播放
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		int timer_interval_number;//计时器计时间隔
		int x_position;//主界面位置横坐标
		int y_position;//主界面位置纵坐标
		int extra_x_position;//主界面隐藏位置横坐标
		int extra_y_position;//主界面隐藏位置纵坐标
		double animation_transparent_number;//窗口透明度
		double animation_transparent_hide_number;//隐藏窗口透明度

	protected:

		void paintEvent(QPaintEvent *);//绘制事件

	public:

		Tools(QWidget *parent = Q_NULLPTR);
		~Tools();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于响应快捷键
		void keyPressEvent(QKeyEvent *event);

		//系统托盘
		void create_system_tray_menu();//添加系统托盘菜单
		void create_system_tray_menu_action();//添加系统托盘菜单功能

		//其他功能
		bool shutdown_or_reboot(int status);//关机或重启。参数为1表示关机，为2表示重启
		void run_program(int index);//运行外部程序，参数是设置文件的目录2项目的对应顺序，取值1-8
		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法

		//槽函数
		public slots:

			void system_tray_icon_clicked(QSystemTrayIcon::ActivationReason);//系统托盘点击事件
			void show_system_tray_action_set();//菜单设置功能
			void show_system_tray_action_set_extra();//菜单高级设置功能
			void show_system_tray_action_set_sound_record();//菜单录音设置功能
			void show_system_tray_action_help();//菜单信息功能
			void show_system_tray_action_exit();//菜单退出功能
			void screenshot_fail();//截图失败
			void screenshot_success(QPoint pt1, QPoint pt2);//截图成功，参数从信号传递进来
			void close_and_exit();//和带动画关闭窗口方法一起使用
			void time_hide_animation_disappear();//隐藏过程计时器到期消失动画播放
			void time_hide_animation_appear();//隐藏过程计时器到期出现动画播放
			void time_hide_repaint();//隐藏过程计时器到期绘制窗口函数
			void show_animation_appear();//显示过程出现动画播放
	};
}

#endif