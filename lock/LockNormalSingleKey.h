#ifndef LOCKNORMALSINGLEKEY_H
#define LOCKNORMALSINGLEKEY_H

#include "define.h"

namespace rem
{

	//ʹ�ñ�׼�����ռ�
	using std::string;

	//����crypto++�����ռ�
	using namespace CryptoPP;

	class LockNormalSingleKey : public QDialog
	{
		Q_OBJECT

	private:

		Ui::LockNormalSingleKeyClass ui;//����
		qreal timer_transparent_count;//��ʱ��͸���ȼ���
		QPoint m_point;//��¼���������ƶ�����
		QGraphicsOpacityEffect *effect_1;//label_chara_1͸��Ч��
		QGraphicsOpacityEffect *effect_2;//label_chara_2͸��Ч��
		QTimer *timer;//��ʱ��
		QValidator *validator;//�����ı�������ʹ�õ�ģʽ
		QString method;//���ܷ���
		string string_array[8];//����ַ�����Ϣ����˳���Ϊ���ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺�������ʷ�ļ�·���������Կ�ļ�·����׺�������������Կ�ļ�·����׺����ʱ�ļ���·��
		char key[1024];//��żӽ�����Կ�������Ŀȡ1024
		char char_array[5];//���char*�ַ�����Ϣ������ͷ���������֡�Ԥ��һ���ֽڸ�'\0'�ַ�
		int timer_picture_count;//��ʱ��ͼƬ˳�����
		int timer_interval;//��ʱ����ʱ���
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		bool bool_array[5];//��Ų���ֵ��Ϣ����˳���Ϊ���Ƿ������ʷ�ļ����Ƿ������Կ�ļ����Ƿ������������Կ�ļ����Ƿ���ͷ���������֣��Ƿ�������һ������
		bool progress_bar_change_color;//�����������Ƿ��л���ɫ
		bool is_continue;//��ִ������һ������Ƿ��������Ĳ���

	public:

		//��������������
		LockNormalSingleKey(QWidget *parent = Q_NULLPTR);
		~LockNormalSingleKey();

		//���ó�Ա����
		void set_method(QString method);//���ü��ܷ�ʽ������Ϊ���ܷ�ʽ
		void update_unlock_information(QString head_digit, bool have_head_digit, QString key);//������Ҫ��ʾ�ڽ����ϵ���Ϣ������Ϊ�������ļ�ͷ���������֣��Ƿ���ͷ���������֣���Կ

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

	signals:

		void show_lock_normal_window();//������һ���ź�
		void send_data(string *string_array, bool *bool_array, char *char_array, char *key, QString method);//��������
		void send_target_class_point(Export_LockSingle_virtual_class *point);//����dll���������ָ��
		void send_dll_name(HINSTANCE dll_name);//����dll��

	public slots:

		void timer_timeout();//��ʱ������
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
		void combobox_change(const QString &combobox_string);//��Ͽ����ݸ��ĺ���
		void lock_file();//���ܷ���
		void unlock_file();//���ܷ���
		void receive_lock_DES_process(double index);//DES�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
		void receive_lock_DES_final(bool is_success, char *key);//DES�����ļ�����������Ϊ�����Ƿ�ɹ�����Կ
		void receive_unlock_DES_process(double index);//DES�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
		void receive_unlock_DES_final(bool is_success);//DES�����ļ�����������Ϊ�����Ƿ�ɹ�����Կ
		void receive_lock_DES_EDE2_process(double index);//DES_EDE2�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
		void receive_lock_DES_EDE2_final(bool is_success, char *key);//DES_EDE2�����ļ�����������Ϊ�����Ƿ�ɹ�����Կ
		void receive_unlock_DES_EDE2_process(double index);//DES_EDE2�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
		void receive_unlock_DES_EDE2_final(bool is_success);//DES_EDE2�����ļ�����������Ϊ�����Ƿ�ɹ�����Կ
		void receive_lock_DES_EDE3_process(double index);//DES_EDE3�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
		void receive_lock_DES_EDE3_final(bool is_success, char *key);//DES_EDE3�����ļ�����������Ϊ�����Ƿ�ɹ�����Կ
		void receive_unlock_DES_EDE3_process(double index);//DES_EDE3�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
		void receive_unlock_DES_EDE3_final(bool is_success);//DES_EDE3�����ļ�����������Ϊ�����Ƿ�ɹ�����Կ
		void receive_lock_AES_MIN_process(double index);//AES_MIN�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
		void receive_lock_AES_MIN_final(bool is_success, char *key);//AES_MIN�����ļ�����������Ϊ�����Ƿ�ɹ�����Կ
		void receive_unlock_AES_MIN_process(double index);//AES_MIN�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
		void receive_unlock_AES_MIN_final(bool is_success);//AES_MIN�����ļ�����������Ϊ�����Ƿ�ɹ�����Կ
		void receive_lock_AES_MIDDLE_process(double index);//AES_MIDDLE�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
		void receive_lock_AES_MIDDLE_final(bool is_success, char *key);//AES_MIDDLE�����ļ�����������Ϊ�����Ƿ�ɹ�����Կ
		void receive_unlock_AES_MIDDLE_process(double index);//AES_MIDDLE�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
		void receive_unlock_AES_MIDDLE_final(bool is_success);//AES_MIDDLE�����ļ�����������Ϊ�����Ƿ�ɹ�����Կ
		void receive_lock_AES_MAX_process(double index);//AES_MAX�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
		void receive_lock_AES_MAX_final(bool is_success, char *key);//AES_MAX�����ļ�����������Ϊ�����Ƿ�ɹ�����Կ
		void receive_unlock_AES_MAX_process(double index);//AES_MAX�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
		void receive_unlock_AES_MAX_final(bool is_success);//AES_MAX�����ļ�����������Ϊ�����Ƿ�ɹ�����Կ
	};

	class Lock_single_file_thread : public QThread//�����ļ����߳�
	{
		Q_OBJECT

	protected:

		Export_LockSingle_virtual_class *target_class_point;//dll���������ָ��
		HINSTANCE dll_name;//dll��
		QMutex mutex;//������
		QString method;//���ܷ���
		string string_array[8];//����ַ�����Ϣ����˳���Ϊ���ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺�������ʷ�ļ�·���������Կ�ļ�·���������������Կ�ļ�·������ʱ�ļ���·��
		char *key;//��żӽ�����Կ
		bool bool_array[5];//��Ų���ֵ��Ϣ����˳���Ϊ���Ƿ������ʷ�ļ����Ƿ������Կ�ļ����Ƿ������������Կ�ļ����Ƿ���ͷ���������֣��Ƿ�������һ������
		char *char_array;//���char�ַ�����Ϣ������ͷ����������

	private:

		void run();//���߳�������

	public:

		Lock_single_file_thread();//���캯��
		~Lock_single_file_thread();//��������

	public slots:

		void get_data(string *string_array, bool *bool_array, char *char_array, char *key, QString method);//��ȡȫ������
		void get_target_class_point(Export_LockSingle_virtual_class *point);//��ȡdll���������ָ��
		void get_dll_name(HINSTANCE dll_name);//��ȡdll��
	};

	class Unlock_single_file_thread : public Lock_single_file_thread//�����ļ����߳�
	{
		Q_OBJECT

	private:

		void run();//���߳�������

	public:

		Unlock_single_file_thread();//���캯��
		~Unlock_single_file_thread();//��������

	};
}

#endif