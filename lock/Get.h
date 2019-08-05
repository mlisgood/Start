#ifndef Get_H
#define Get_H

#include "define.h"

namespace rem
{
	class Get : public QDialog
	{
		Q_OBJECT

	private:

		Ui::GetClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QTimer *timer;//��ʱ��
		QGraphicsOpacityEffect *effect_1;//label_chara_1͸��Ч��
		QGraphicsOpacityEffect *effect_2;//label_chara_2͸��Ч��
		int timer_picture_count;//��ʱ��ͼƬ˳�����
		int timer_interval;//��ʱ����ʱ���
		qreal timer_transparent_count;//��ʱ��͸���ȼ���
		bool m_bPressed;//ȷ�������Ƿ񱻰���

	public:

		//��������������
		Get(QWidget *parent = Q_NULLPTR);
		~Get();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		public slots:

			void timer_timeout();
	};
}

#endif