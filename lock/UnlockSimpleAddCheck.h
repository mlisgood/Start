#ifndef UNLOCKSIMPLEADDCHECK_H
#define UNLOCKSIMPLEADDCHECK_H

#include "define.h"

namespace rem
{
	class UnlockSimpleAddCheck : public QDialog
	{
		Q_OBJECT

	private:

		Ui::UnlockSimpleAddCheckClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QPixmap main_picture;//��Ҫ�����Ա�����Ϊ���ڵ�ͼƬ
		QString *char_point_information;//�ӼӼ�����������õ���charָ������Ϣ�������������ļ�ͷ����������
		QString char_point_information_data;//�ӼӼ�����������õ���charָ������Ϣ�������������ļ�ͷ����������
		int *int_information;//�ӼӼ�����������õ�����������Ϣ�����������ܷ���
		int int_information_data;//�ӼӼ�����������õ�����������Ϣ�����������ܷ���
		int *extra_int_information[17];//�ӼӼ�����������õ�����������Ϣ���������Ӽ����������һ��Ԫ�ش��ѭ������
		int extra_int_information_data[17];//�ӼӼ�����������õ�����������Ϣ���������Ӽ����������һ��Ԫ�ش��ѭ������
		int bool_information_data_int;//�ӼӼ�����������õ��Ĳ�������Ϣ���������Ƿ���ͷ���������֡�Ϊ�˱��ڶ�ȡ�ļ���ʹ��int����
		long long *long_long_information[2];//�ӼӼ�����������õ��ĳ���������Ϣ��������ͷ�������ֽڣ�β�������ֽ�
		long long long_long_information_data[2];//�ӼӼ�����������õ��ĳ���������Ϣ��������ͷ�������ֽڣ�β�������ֽ�
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		bool *bool_information;//�ӼӼ�����������õ��Ĳ�������Ϣ���������Ƿ���ͷ����������
		bool bool_information_data;//�ӼӼ�����������õ��Ĳ�������Ϣ���������Ƿ���ͷ����������
		bool *is_continue;//��������ִ������һ������Ƿ��������Ĳ���

	protected:

		void paintEvent(QPaintEvent *); //���Ʊ���ͼ��

	public:

		//��������������
		UnlockSimpleAddCheck(QWidget *parent = Q_NULLPTR);
		~UnlockSimpleAddCheck();

		//���ó�Ա����
		void set_information(int *direction, long long *head_offset, long long *tail_offset, int *cycle, QString *head_digit, bool *have_head_digit, bool *is_continue, int *operate_count);//������Ҫ��ʾ�ڽ����ϵ���Ϣ������Ϊ�����ܷ���1��˳����ܣ�2��������ܣ�3��˫����ܣ���ͷ�������ֽڣ�β�������ֽڣ�ѭ�����ڣ������ļ�ͷ���������֣��Ƿ���ͷ���������֣��Ƿ�ȷ�Ͻ��ܣ��Ӽ�����
		void set_information_data(int direction, long long head_offset, long long tail_offset, int cycle, QString head_digit, bool have_head_digit, int *operate_count);//������Ҫ��ʾ�ڽ����ϵ���Ϣ�������ٴ���ָ�룬��֮��ʹ�á������֮��ʹ��ָ�봫�ݣ�������ָ��ָ��ĵ�ַ�ı䣬��ô��ȷ�Ϻ��޷��޸���������������Ե�ֵ

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
			void look_set();//�鿴����
			void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif