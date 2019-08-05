#ifndef LOCKNORMALDOUBLEKEY_H
#define LOCKNORMALDOUBLEKEY_H

#include "define.h"

namespace rem
{

	//ʹ�ñ�׼�����ռ�
	using std::string;

	//����crypto++�����ռ�
	using namespace CryptoPP;

	class LockNormalDoubleKey : public QDialog
	{

		Q_OBJECT

	private:

		Ui::LockNormalDoubleKeyClass ui;//����
		qreal timer_transparent_count;//��ʱ��͸���ȼ���
		QPoint m_point;//��¼���������ƶ�����
		QGraphicsOpacityEffect *effect_1;//label_chara_1͸��Ч��
		QGraphicsOpacityEffect *effect_2;//label_chara_2͸��Ч��
		QTimer *timer;//��ʱ��
		QValidator *validator_1;//�����ı�������ʹ�õ�ģʽ
		QValidator *validator_2;//�����ı�������ʹ�õ�ģʽ
		QValidator *validator_3;//�����ı�������ʹ�õ�ģʽ
		QString method;//���ܷ���
		QString curve_type;//ECC������������
		string string_array[8];//����ַ�����Ϣ����˳���Ϊ���ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺�������ʷ�ļ�·���������Կ�ļ�·����׺�������������Կ�ļ�·����׺����ʱ�ļ���·��
		char public_key[4096];//��Ź�Կ
		char private_key[4096];//���˽Կ
		char char_array[5];//���char*�ַ�����Ϣ������ͷ���������֡�Ԥ��һ���ֽڸ�'\0'�ַ�
		int timer_picture_count;//��ʱ��ͼƬ˳�����
		int timer_interval;//��ʱ����ʱ���
		int key_size;//ʵ����Կ����
		int size;//RSA������Ͽ���ѡ�����Կ����
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		bool bool_array[4];//��Ų���ֵ��Ϣ����˳���Ϊ���Ƿ������ʷ�ļ����Ƿ������Կ�ļ����Ƿ������������Կ�ļ����Ƿ���ͷ����������
		bool progress_bar_change_color;//�����������Ƿ��л���ɫ
		bool is_continue;//��ִ������һ������Ƿ��������Ĳ���

	public:

		//��������������
		LockNormalDoubleKey(QWidget *parent = Q_NULLPTR);
		~LockNormalDoubleKey();

		//���ó�Ա����
		void update_lock_information(QString head_digit, bool have_head_digit, QString key);//���¼���ǰ��Ҫ��ʾ�ڽ����ϵ���Ϣ������Ϊ�������ļ�ͷ���������֣��Ƿ���ͷ���������֣���Կ
		void update_unlock_information(QString head_digit, bool have_head_digit, QString key);//���½���ǰ��Ҫ��ʾ�ڽ����ϵ���Ϣ������Ϊ�������ļ�ͷ���������֣��Ƿ���ͷ���������֣���Կ
		void set_method(QString method);//���ü��ܷ�ʽ������Ϊ���ܷ�ʽ

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

	signals:

		void show_lock_normal_window();//������һ���ź�
		void send_data(string *string_array, bool *bool_array, char *char_array, char *key, int size, QString method);//��������
		void send_target_class_point(Export_LockDouble_virtual_class *point);//����dll���������ָ��
		void send_dll_name(HINSTANCE dll_name);//����dll��
		void send_key_data(string *string_array, bool *bool_array, char *char_array, char *public_key, char *private_key, QString method, int size, QString curve_type, string output_path);//������Կ����

	public slots:

		void timer_timeout();//��ʱ������
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
		void combobox_change_method(const QString &combobox_string);//��Ͽ����ݸ��ĺ���
		void combobox_change_size(const QString &combobox_string);//��Ͽ����ݸ��ĺ���
		void lock_file();//���ܷ���
		void unlock_file();//���ܷ���
		void set_key();//������Կ
		void set_key_final(int public_key_length, int private_key_length);//������Կ��ϣ�����Ϊ��Կ��˽Կ����
		void receive_lock_out_of_range();//�����ļ����ݳ�����Χ
		void receive_lock_wrong_key();//������Կ���̻��ļ����ݳ�����Χ
		void receive_lock_final(bool is_success);//�����ļ�����������Ϊ�����Ƿ�ɹ�
		void receive_unlock_out_of_range();//�����ļ����ݳ�����Χ
		void receive_unlock_wrong_key();//������Կ���̻��ļ����ݳ�����Χ
		void receive_unlock_final(bool is_success);//�����ļ�����������Ϊ�����Ƿ�ɹ�
	};

	class Lock_double_file_thread : public QThread//�����ļ����߳�
	{

		Q_OBJECT

	protected:

		Export_LockDouble_virtual_class *target_class_point;//dll���������ָ��
		HINSTANCE dll_name;//dll��
		QMutex mutex;//������
		QString method;//���ܷ���
		string string_array[8];//����ַ�����Ϣ����˳���Ϊ���ļ�·�����ļ���������ļ�ǰ�벿�ֲ���·��������ļ�·����׺�������ʷ�ļ�·���������Կ�ļ�·���������������Կ�ļ�·������ʱ�ļ���·��
		char *key;//��żӽ�����Կ
		bool bool_array[4];//��Ų���ֵ��Ϣ����˳���Ϊ���Ƿ������ʷ�ļ����Ƿ������Կ�ļ����Ƿ������������Կ�ļ����Ƿ���ͷ����������
		char *char_array;//���char�ַ�����Ϣ������ͷ����������
		int size;//��Կ����

	private:

		void run();//���߳�������

	public:

		Lock_double_file_thread();//���캯��
		~Lock_double_file_thread();//��������

	public slots:

		void get_data(string *string_array, bool *bool_array, char *char_array, char *key, int size, QString method);//��ȡȫ������
		void get_target_class_point(Export_LockDouble_virtual_class *point);//��ȡdll���������ָ��
		void get_dll_name(HINSTANCE dll_name);//��ȡdll��
		
	};

	class Unlock_double_file_thread : public Lock_double_file_thread//�����ļ����߳�
	{

		Q_OBJECT

	private:

		void run();//���߳�������

	public:

		Unlock_double_file_thread();//���캯��
		~Unlock_double_file_thread();//��������

	};

	class Lock_double_get_key_thread : public QThread//�����ļ����߳�
	{
		Q_OBJECT

	protected:

		Export_LockDouble_virtual_class *target_class_point;//dll���������ָ��
		HINSTANCE dll_name;//dll��
		QMutex mutex;//������
		QString method;//���ܷ���
		QString curve_type;//ECC������������
		string string_array[3];//����ַ�����Ϣ����˳���Ϊ�����ʷ�ļ�·���������Կ�ļ�·���������������Կ�ļ�·��
		string output_path;//�����Կ�ļ�·��
		int size;//RSA������Կ����
		char *public_key;//��Ź�Կ
		char *private_key;//���˽Կ
		bool bool_array[4];//��Ų���ֵ��Ϣ����˳���Ϊ���Ƿ������ʷ�ļ����Ƿ������Կ�ļ����Ƿ������������Կ�ļ����Ƿ���ͷ����������
		char *char_array;//���char�ַ�����Ϣ������ͷ����������

	private:

		void run();//���߳�������

	public:

		Lock_double_get_key_thread();//���캯��
		~Lock_double_get_key_thread();//��������

	public slots:

		void get_key_data(string *string_array, bool *bool_array, char *char_array, char *public_key, char *private_key, QString method, int size, QString curve_type, string output_path);//��ȡȫ������
		void get_target_class_point(Export_LockDouble_virtual_class *point);//��ȡdll���������ָ��
		void get_dll_name(HINSTANCE dll_name);//��ȡdll��
	};
}

#endif