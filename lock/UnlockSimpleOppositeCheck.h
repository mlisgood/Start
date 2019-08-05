#ifndef UNLOCKSIMPLEOPPOSITECHECK_H
#define UNLOCKSIMPLEOPPOSITECHECK_H

#include "define.h"

namespace rem
{
	class UnlockSimpleOppositeCheck : public QDialog
	{
		Q_OBJECT

	private:

		Ui::UnlockSimpleOppositeCheckClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QPixmap main_picture;//��Ҫ�����Ա�����Ϊ���ڵ�ͼƬ
		QString *char_point_information;//��ȡ������������õ���charָ������Ϣ�������������ļ�ͷ����������
		QString char_point_information_data;//��ȡ������������õ���charָ������Ϣ�������������ļ�ͷ����������
		int *int_information;//��ȡ������������õ�����������Ϣ�����������ܷ���
		int int_information_data;//��ȡ������������õ�����������Ϣ�����������ܷ���
		int bool_information_data_int;//��ȡ������������õ��Ĳ�������Ϣ���������Ƿ���ͷ���������֡�Ϊ�˱��ڶ�ȡ�ļ���ʹ��int����
		long long *long_long_information[3];//��ȡ������������õ��ĳ���������Ϣ��������ͷ�������ֽڣ�β�������ֽڣ�ѭ������
		long long long_long_information_data[3];//��ȡ������������õ��ĳ���������Ϣ��������ͷ�������ֽڣ�β�������ֽڣ�ѭ������
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		bool *bool_information;//��ȡ������������õ��Ĳ�������Ϣ���������Ƿ���ͷ����������
		bool bool_information_data;//��ȡ������������õ��Ĳ�������Ϣ���������Ƿ���ͷ����������
		bool *is_continue;//��������ִ������һ������Ƿ��������Ĳ���

	protected:

		void paintEvent(QPaintEvent *); //���Ʊ���ͼ��

	public:

		//��������������
		UnlockSimpleOppositeCheck(QWidget *parent = Q_NULLPTR);
		~UnlockSimpleOppositeCheck();

		//���ó�Ա����
		void set_information(int *direction, long long *head_offset, long long *tail_offset, long long *cycle, QString *head_digit, bool *have_head_digit, bool *is_continue);////������Ҫ��ʾ�ڽ����ϵ���Ϣ������Ϊ�����ܷ���1��˳����ܣ�2��������ܣ�3��˫����ܣ���ͷ�������ֽڣ�β�������ֽڣ�ѭ�����ڣ������ļ�ͷ���������֣��Ƿ���ͷ���������֣��Ƿ�ȷ�Ͻ���
		void set_information_data(int direction, long long head_offset, long long tail_offset, long long cycle, QString head_digit, bool have_head_digit);//������Ҫ��ʾ�ڽ����ϵ���Ϣ�������ٴ���ָ�룬��֮��ʹ�á������֮��ʹ��ָ�봫�ݣ�������ָ��ָ��ĵ�ַ�ı䣬��ô��ȷ�Ϻ��޷��޸���������������Ե�ֵ

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