#ifndef COUNTERSET_H
#define COUNTERSET_H

#include "define.h"

namespace rem
{
	class CounterSet : public QDialog
	{
		Q_OBJECT

	private:

		Ui::CounterSetClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QPixmap main_picture;//��Ҫ�����Ա�����Ϊ���ڵ�ͼƬ
		QButtonGroup *radioButton_type;//��ѡ��Ŀ����1
		QButtonGroup *radioButton_voice;//��ѡ��Ŀ����2
		QButtonGroup *radioButton_dialog;//��ѡ��Ŀ����3
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��

	protected:

		void paintEvent(QPaintEvent *); //���Ʊ���ͼ��

	public:

		//��������������
		CounterSet(QWidget *parent = Q_NULLPTR);
		~CounterSet();

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