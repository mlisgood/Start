#ifndef UNLOCKSIMPLEADDCHECKDIGIT_H
#define UNLOCKSIMPLEADDCHECKDIGIT_H

#include "define.h"

namespace rem
{
	class UnlockSimpleAddCheckDigit : public QDialog
	{
		Q_OBJECT

	private:

		Ui::UnlockSimpleAddCheckDigitClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QPixmap main_picture;//��Ҫ�����Ա�����Ϊ���ڵ�ͼƬ
		int extra_int_information[17];//�ӼӼ�����������õ�����������Ϣ���������Ӽ�������ѭ����λ��Ŀ
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��

	protected:

		void paintEvent(QPaintEvent *); //���Ʊ���ͼ��

	public:

		//��������������
		UnlockSimpleAddCheckDigit(QWidget *parent = Q_NULLPTR);
		~UnlockSimpleAddCheckDigit();

		//���ó�Ա����
		void set_information(int *extra_int_information);//������Ҫ��ʾ�ļӼ�����

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		public slots:
		
			void set_apply();//������Ч
			void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif