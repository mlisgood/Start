#ifndef LOCKSIMPLEADDGETDIGIT_H
#define LOCKSIMPLEADDGETDIGIT_H

#include "define.h"

namespace rem
{
	class LockSimpleAddGetDigit : public QDialog
	{
		Q_OBJECT

	private:

		Ui::LockSimpleAddGetDigitClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QPixmap main_picture;//��Ҫ�����Ա�����Ϊ���ڵ�ͼƬ
		int *int_information[17];//��ȡ������������õ�����������Ϣ���������Ӽ�������ѭ����λ��Ŀ
		int int_information_data[17];//��ȡ������������õ�����������Ϣ���������Ӽ�������ѭ����λ��Ŀ


		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		bool *bool_information;//��ȡ������������õ��Ĳ�������Ϣ���������Ƿ���ͷ����������
		bool bool_information_data;//��ȡ������������õ��Ĳ�������Ϣ���������Ƿ���ͷ����������

	protected:

		void paintEvent(QPaintEvent *); //���Ʊ���ͼ��

	public:

		//��������������
		LockSimpleAddGetDigit(QWidget *parent = Q_NULLPTR);
		~LockSimpleAddGetDigit();

		//���ó�Ա����
		void set_information(int *extra_digit_array);//������Ҫ��ʾ�ڽ����ϵ���Ϣ������Ϊ�����Ӽ�������ѭ����λ��Ŀ������

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		public slots:
		
			void set_apply();//������Ч
			void cancel_apply();//����ȡ��
			void add_item();//�����Ŀ
			void edit_item();//�޸���Ŀ
			void delete_item();//ɾ����Ŀ
			void delete_all_item();//ɾ��ȫ����Ŀ
			void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif