#ifndef DESKTOP_H
#define DESKTOP_H 

#include "define.h"

namespace rem
{

	//�����׼�����ռ�
	using std::wstring;

	class Desktop : public QMainWindow
	{
		Q_OBJECT

	private:

		Ui::DesktopClass ui;
		QPoint m_point;//��¼���������ƶ�����
		QTimer *time_counter;//�������ʱ��
		QSystemTrayIcon *system_tray_icon;//ϵͳ����ͼ��
		QMenu *system_tray_menu;//���̲˵�
		QAction *action_static_set;//���̲˵���̬�����ļ�����
		QAction *action_dynamic_set;//���̲˵���̬�����ļ�����
		QAction *action_auto_start_set;//���̲˵��������������ù���
		QAction *action_help;//���̲˵���Ϣ����
		QAction *action_exit;//���̲˵��˳�����
		QPixmap background_picture;//����ͼƬ
		QString background_path;//����·��
		wstring widget_path[7];//�ؼ��򿪳���·��
		double transparent;//͸����
		int randnumber;//���������������
		int position[2];//��ʾʱ��λ��
		int screen_resolution[2];//��ǰ�ֱ���
		int timer_interval_number;//��ʱ����ʱ���
		int widget_transparent[7];//�ؼ���͸����
		bool on_top;//ȷ�������Ƿ��ڶ��㣬true��ʾ�ڴ��ڶ��㣬false��ʾ���ڶ���
		bool counter_already_run;//ȷ����ʱ���Ƿ��Ѿ�������
		bool is_hide;//ȷ�������Ƿ����أ�false��ʾδ�����أ�true��ʾ�����أ�������ʱ���Խ����������ʾ�¼�
		bool is_hide_available;//ȷ�������Ƿ���Ա�����
		bool is_special_effect;//ȷ�������Ƿ��������Ч
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		bool widget_is_enable[7];//�ؼ��Ƿ�ʹ��
		bool widget_is_on_top[7];//�ؼ��Ƿ�λ�����
		bool autorun;//�Ƿ񿪻�������
		bool move_enable;//�Ƿ��ƶ�����ֵ�ᱻ��¼�������ļ�
		bool m_bPressed;//ȷ�������Ƿ񱻰���

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//�������������
		Desktop(QWidget *parent = Q_NULLPTR);
		~Desktop();

		//ϵͳ����
		void create_system_tray_menu();//���ϵͳ���̲˵�
		void create_system_tray_menu_action();//���ϵͳ���̲˵�����

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼�
		void keyPressEvent(QKeyEvent *event);

		//��������
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
		void key_press_method(int widget_id);//�����¼�����

		//�ۺ���
		public slots:

			void system_tray_icon_clicked(QSystemTrayIcon::ActivationReason);//ϵͳ���̵���¼�
			void show_system_tray_action_set_static();//�˵��������ù���
			void show_system_tray_action_set_dynamic();//�˵��������ù���
			void show_system_tray_action_set_other();//�˵���������������
			void show_system_tray_action_help();//�˵���Ϣ����
			void show_system_tray_action_exit();//�˵��˳�����
			void time_hide_animation_disappear();//���ع��̼�ʱ��������ʧ��������
			void time_hide_animation_appear();//���ع��̼�ʱ�����ڳ��ֶ�������
			void time_hide_repaint();//���ع��̼�ʱ�����ڻ��ƴ��ں���
			void show_animation_appear();//��ʾ���̳��ֶ�������

	};
}

#endif