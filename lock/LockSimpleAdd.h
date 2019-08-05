#ifndef LOCKSIMPLEADD_H
#define LOCKSIMPLEADD_H

#include "define.h"

namespace rem
{

	//ʹ�ñ�׼�����ռ�
	using std::string;

	class LockSimpleAdd : public QDialog
	{
		Q_OBJECT

	private:

		Ui::LockSimpleAddClass ui;//����
		qreal timer_transparent_count;//��ʱ��͸���ȼ���
		QPoint m_point;//��¼���������ƶ�����
		QGraphicsOpacityEffect *effect_1;//label_chara_1͸��Ч��
		QGraphicsOpacityEffect *effect_2;//label_chara_2͸��Ч��
		QTimer *timer;//��ʱ��
		QValidator *validator;//�����ı�������ʹ�õ�ģʽ
		string string_array[8];//����ַ�����Ϣ����˳���Ϊ���ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺�������ʷ�ļ�·���������Կ�ļ�·����׺�������������Կ�ļ�·����׺����ʱ�ļ���·��
		long long digit_array[2];//���long long����ֵ��Ϣ����˳���Ϊ��ͷ��������㣬β��������㣬ѭ������
		char char_array[5];//���char*�ַ�����Ϣ������ͷ���������֡�Ԥ��һ���ֽڸ�'\0'�ַ�
		int flag_array[1];//���int�ͱ����Ϣ����˳���Ϊ�����ܷ���1����˳��2������3����˫����
		int extra_digit_array[17];//���int�ͼ��ܼӼ����������16�������һ������ָ��һ��ѭ���ڵĵ�λ��Ŀ
		int LockSimpleAdd_already_send_size;//�Ѿ����ʹ�С
		int LockSimpleAdd_file_size;//�ļ���С
		int timer_picture_count;//��ʱ��ͼƬ˳�����
		int timer_interval;//��ʱ����ʱ���
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		bool bool_array[4];//��Ų���ֵ��Ϣ����˳���Ϊ���Ƿ������ʷ�ļ����Ƿ������Կ�ļ����Ƿ������������Կ�ļ����Ƿ���ͷ����������
		bool progress_bar_change_color;//�����������Ƿ��л���ɫ
		bool is_continue;//��ִ������һ������Ƿ��������Ĳ���

	public:

		//��������������
		LockSimpleAdd(QWidget *parent = Q_NULLPTR);
		~LockSimpleAdd();

		//���ó�Ա����
		void update_unlock_information(int direction, long long head_offset, long long tail_offset, int cycle, QString head_digit, bool have_head_digit, int *operate_count);//������Ҫ��ʾ�ڽ����ϵ���Ϣ������Ϊ�����ܷ���1��˳����ܣ�2��������ܣ�3��˫����ܣ���ͷ�������ֽڣ�β�������ֽڣ�ѭ�����ڣ������ļ�ͷ���������֣��Ƿ���ͷ���������֣��Ӽ�����

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

	signals:

		void show_lock_simple_window();//������һ���ź�
		void send_data(string *string_array, bool *bool_array, long long *digit_array, int *flag_array, int *extra_digit_array, char* char_array);//��������
		void send_target_class_point(Export_LockSimple_virtual_class *point);//����dll���������ָ��
		void send_dll_name(HINSTANCE dll_name);//����dll��

	public slots:

		void timer_timeout();//��ʱ������
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
		void lock_file();//���ܷ���
		void unlock_file();//���ܷ���
		void digit_set();//���üӼ�����
		void receive_lock_simple_add_process(double index);//�Ӽ������ļ���������ʾ������Ϊ�Ѵ����ֱ���
		void receive_lock_simple_add_final(bool is_success);//�Ӽ������ļ�����������Ϊ�����Ƿ�ɹ�
		void receive_unlock_simple_add_process(double index);//�Ӽ������ļ���������ʾ������Ϊ�Ѵ����ֱ���
		void receive_unlock_simple_add_final(bool is_success);//�Ӽ������ļ�����������Ϊ�����Ƿ�ɹ�
	};

	class Lock_add_file_thread : public QThread//�����ļ����߳�
	{
		Q_OBJECT

	protected:

		Export_LockSimple_virtual_class *target_class_point;//dll���������ָ��
		HINSTANCE dll_name;//dll��
		QMutex mutex;//������
		string string_array[8];//����ַ�����Ϣ����˳���Ϊ���ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺�������ʷ�ļ�·���������Կ�ļ�·���������������Կ�ļ�·������ʱ�ļ���·��
		bool bool_array[4];//��Ų���ֵ��Ϣ����˳���Ϊ���Ƿ������ʷ�ļ����Ƿ������Կ�ļ����Ƿ������������Կ�ļ����Ƿ���ͷ����������
		long long digit_array[2];//���long long����ֵ��Ϣ����˳���Ϊ��ͷ��������㣬β���������
		int flag_array[2];//���int�ͱ����Ϣ����˳���Ϊ�����ܷ���ѭ������
		int extra_digit_array[16];//���int�ͼ��ܼӼ����������16��
		char *char_array;//���char�ַ�����Ϣ������ͷ����������

	private:

		void run();//���߳�������

	public:

		Lock_add_file_thread();//���캯��
		~Lock_add_file_thread();//��������

	public slots:

		void get_data(string *string_array, bool *bool_array, long long *digit_array, int *flag_array, int *extra_digit_array, char *char_array);//��ȡȫ������
		void get_target_class_point(Export_LockSimple_virtual_class *point);//��ȡdll���������ָ��
		void get_dll_name(HINSTANCE dll_name);//��ȡdll��
	};

	class Unlock_add_file_thread : public Lock_add_file_thread//�����ļ����߳�
	{
		Q_OBJECT

	private:

		void run();//���߳�������

	public:

		Unlock_add_file_thread();//���캯��
		~Unlock_add_file_thread();//��������

	};
}

#endif