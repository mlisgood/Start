#ifndef UNLOCKNORMALDOUBLECHECK_H
#define UNLOCKNORMALDOUBLECHECK_H

#include "define.h"

namespace rem
{
	class UnlockNormalDoubleCheck : public QDialog
	{
		Q_OBJECT

	private:

		Ui::UnlockNormalDoubleCheckClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QPixmap main_picture;//��Ҫ�����Ա�����Ϊ���ڵ�ͼƬ
		QString *char_point_information;//�Ӽ���������õ���charָ������Ϣ�������������ļ�ͷ����������
		QString char_point_information_data;//�Ӽ���������õ���charָ������Ϣ�������������ļ�ͷ����������
		QString *key;//�Ӽ���������õ�����Կ��Ϣ
		QString key_data;//�Ӽ���������õ�����Կ��Ϣ
		QString key_type;//�Ӽ���������õ�����Կ������Ϣ
		QString method;//�Ӽ���������õ��ļ��ܷ�����Ϣ
		int bool_information_data_int;//�Ӽ���������õ��Ĳ�������Ϣ���������Ƿ���ͷ���������֡�Ϊ�˱��ڶ�ȡ�ļ���ʹ��int����
		int *key_size;//�Ӽ���������õ���int����Ϣ����������Կ��С
		int key_size_data;//�Ӽ���������õ���int����Ϣ����������Կ��С
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		bool *bool_information;//�Ӽ���������õ��Ĳ�������Ϣ���������Ƿ���ͷ����������
		bool bool_information_data;//�Ӽ���������õ��Ĳ�������Ϣ���������Ƿ���ͷ����������
		bool *is_continue;//��������ִ������һ������Ƿ��������Ĳ���

	protected:

		void paintEvent(QPaintEvent *); //���Ʊ���ͼ��

	public:

		//��������������
		UnlockNormalDoubleCheck(QWidget *parent = Q_NULLPTR);
		~UnlockNormalDoubleCheck();

		//���ó�Ա����
		void set_information(QString key_type, QString method, QString *key, QString *head_digit, bool *have_head_digit, bool *is_continue, int *key_size);//������Ҫ��ʾ�ڽ����ϵ���Ϣ������Ϊ����Կ���ͣ����ܷ������ɶ���������ת��Ϊ�ı�����Կ�������ļ�ͷ���������֣��Ƿ���ͷ���������֣��Ƿ�ȷ�Ͻ��ܣ���Կ��С
		void set_information_data(QString key, QString head_digit, bool have_head_digit, int key_size);//������Ҫ��ʾ�ڽ����ϵ���Ϣ�������ٴ���ָ�룬��֮��ʹ�á������֮��ʹ��ָ�봫�ݣ�������ָ��ָ��ĵ�ַ�ı䣬��ô��ȷ�Ϻ��޷��޸���������������Ե�ֵ

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		public slots:
		
			void set_apply();//������Ч
			void cancel_apply();//����ȡ��
			void import_set();//��������
			void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif