#ifndef LOCKNORMALHASHCALCULATE_H
#define LOCKNORMALHASHCALCULATE_H

#include "define.h"

namespace rem
{

	//ʹ�ñ�׼�����ռ�
	using std::string;

	//����crypto++�����ռ�
	using namespace CryptoPP;

	class LockNormalHashCalculate : public QDialog
	{
		Q_OBJECT

	private:

		Ui::LockNormalHashCalculateClass ui;//����
		qreal timer_transparent_count;//��ʱ��͸���ȼ���
		QPoint m_point;//��¼���������ƶ�����
		QGraphicsOpacityEffect *effect_1;//label_chara_1͸��Ч��
		QGraphicsOpacityEffect *effect_2;//label_chara_2͸��Ч��
		QTimer *timer;//��ʱ��
		QValidator *validator;//�����ı�������ʹ�õ�ģʽ
		QString method;//���㷽��
		QString calculate_type;//��������
		string string_array[3];//����ַ�����Ϣ����˳���Ϊ���ļ�·�����ļ����������ʷ�ļ�·��
		char result[1024];//��Ž��
		int timer_picture_count;//��ʱ��ͼƬ˳�����
		int timer_interval;//��ʱ����ʱ���
		int key_size;//ʵ����Կ����
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		bool bool_array[1];//��Ų���ֵ��Ϣ����˳���Ϊ���Ƿ������ʷ�ļ�
		bool progress_bar_change_color;//�����������Ƿ��л���ɫ
		bool is_continue;//��ִ������һ������Ƿ��������Ĳ���

	public:

		//��������������
		LockNormalHashCalculate(QWidget *parent = Q_NULLPTR);
		~LockNormalHashCalculate();

		//���ó�Ա����
		void set_method(QString method);//���ü��ܷ�ʽ������Ϊ���ܷ�ʽ

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

	signals:

		void show_lock_normal_window();//������һ���ź�
		void send_data(string *string_array, bool *bool_array, char *result, QString calculate_type, QString method);//��������
		void send_target_class_point(Export_HashCalculate_virtual_class *point);//����dll���������ָ��
		void send_dll_name(HINSTANCE dll_name);//����dll��

	public slots:

		void timer_timeout();//��ʱ������
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
		void combobox_change_method(const QString &combobox_string);//��Ͽ����ݸ��ĺ���
		void combobox_change_type(const QString &combobox_string);//��Ͽ����ݸ��ĺ���
		void file_explore();//����ļ�
		void calculate_file();//����ɢ��ֵ
		void check_file();//У���ļ�
		void receive_hash_calculate_final(int length);//�������������Ϊ�������
		void receive_hash_calculate_final_check(int length);//��������������бȶԡ�����Ϊ�������
	};

	class HashCalculate_file_thread : public QThread//�����ļ����߳�
	{
		Q_OBJECT

	protected:

		Export_HashCalculate_virtual_class *target_class_point;//dll���������ָ��
		HINSTANCE dll_name;//dll��
		QMutex mutex;//������
		QString method;//���ܷ���
		QString calculate_type;//��������
		string string_array[3];//����ַ�����Ϣ����˳���Ϊ���ļ�·�����ļ����������ʷ�ļ�·��
		char *result;//��Ž��
		bool bool_array[1];//��Ų���ֵ��Ϣ����˳���Ϊ���Ƿ������ʷ�ļ�

	private:

		void run();//���߳�������

	public:

		HashCalculate_file_thread();//���캯��
		~HashCalculate_file_thread();//��������

	public slots:

		void get_data(string *string_array, bool *bool_array, char *result, QString calculate_type, QString method);//��ȡȫ������
		void get_target_class_point(Export_HashCalculate_virtual_class *point);//��ȡdll���������ָ��
		void get_dll_name(HINSTANCE dll_name);//��ȡdll��
		
	};

}

#endif