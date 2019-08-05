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
		QSystemTrayIcon *system_tray_icon;//ϵͳ����ͼ��
		QPixmap main_picture;//��Ҫ�����Ա�����Ϊ���ڵ�ͼƬ
		QPixmap screenshot_picture;//��ͼ�����õ���ͼƬ
		QPoint m_point;//��¼���������ƶ�����
		QMenu *system_tray_menu;//���̲˵�
		QTimer *time_counter;//���ش����ü�ʱ��
		QAction *action_set;//���̲˵������ļ�����
		QAction *action_set_extra;//���̲˵��߼����ù���
		QAction *action_set_sound_record;//���̲˵�¼�����ù���
		QAction *action_help;//���̲˵���Ϣ����
		QAction *action_exit;//���̲˵��˳�����
		QString setting_picture_mainpicture;//�����ļ���Ϣ������ͼƬ
		QString setting_function_program[8];//�����ļ���Ϣ����������
		QString setting_font_font;//�����ļ���Ϣ����ǩ��������
		QString setting_extra_index[9];//�����ļ�������Ϣ
		QString main_picture_normal_hole_path;//����״��������ͼƬ·��
		QString main_picture_hide_hole_path;//����״��������ͼƬ·��
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool on_top;//ȷ�������Ƿ��ڶ��㣬true��ʾ�ڴ��ڶ��㣬false��ʾ���ڶ���
		bool counter_already_run;//ȷ����ʱ���Ƿ��Ѿ�������
		bool is_hide;//ȷ�������Ƿ����أ�false��ʾδ�����أ�true��ʾ�����أ�������ʱ���Խ����������ʾ�¼�
		bool screenshot_end_mouse_event_disable;//��ͼ�������������������¼�����������������ֺ���ʧ�Ķ������ٴβ���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		int timer_interval_number;//��ʱ����ʱ���
		int x_position;//������λ�ú�����
		int y_position;//������λ��������
		int extra_x_position;//����������λ�ú�����
		int extra_y_position;//����������λ��������
		double animation_transparent_number;//����͸����
		double animation_transparent_hide_number;//���ش���͸����

	protected:

		void paintEvent(QPaintEvent *);//�����¼�

	public:

		Tools(QWidget *parent = Q_NULLPTR);
		~Tools();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼���������Ӧ��ݼ�
		void keyPressEvent(QKeyEvent *event);

		//ϵͳ����
		void create_system_tray_menu();//���ϵͳ���̲˵�
		void create_system_tray_menu_action();//���ϵͳ���̲˵�����

		//��������
		bool shutdown_or_reboot(int status);//�ػ�������������Ϊ1��ʾ�ػ���Ϊ2��ʾ����
		void run_program(int index);//�����ⲿ���򣬲����������ļ���Ŀ¼2��Ŀ�Ķ�Ӧ˳��ȡֵ1-8
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���

		//�ۺ���
		public slots:

			void system_tray_icon_clicked(QSystemTrayIcon::ActivationReason);//ϵͳ���̵���¼�
			void show_system_tray_action_set();//�˵����ù���
			void show_system_tray_action_set_extra();//�˵��߼����ù���
			void show_system_tray_action_set_sound_record();//�˵�¼�����ù���
			void show_system_tray_action_help();//�˵���Ϣ����
			void show_system_tray_action_exit();//�˵��˳�����
			void screenshot_fail();//��ͼʧ��
			void screenshot_success(QPoint pt1, QPoint pt2);//��ͼ�ɹ����������źŴ��ݽ���
			void close_and_exit();//�ʹ������رմ��ڷ���һ��ʹ��
			void time_hide_animation_disappear();//���ع��̼�ʱ��������ʧ��������
			void time_hide_animation_appear();//���ع��̼�ʱ�����ڳ��ֶ�������
			void time_hide_repaint();//���ع��̼�ʱ�����ڻ��ƴ��ں���
			void show_animation_appear();//��ʾ���̳��ֶ�������
	};
}

#endif