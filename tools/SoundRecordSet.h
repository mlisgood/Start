#ifndef SOUNDRECORDSET_H
#define SOUNDRECORDSET_H

#include "define.h"

namespace rem
{
	class SoundRecordSet : public QDialog
	{
		Q_OBJECT

	private:

		Ui::SoundRecordSetClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QPixmap main_picture;//��Ҫ�����Ա�����Ϊ���ڵ�ͼƬ
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��

	protected:

		void paintEvent(QPaintEvent *); //���Ʊ���ͼ��

	public:

		//��������������
		SoundRecordSet(QWidget *parent = Q_NULLPTR);
		~SoundRecordSet();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		public slots:
		
			void set_apply();//������Ч
			void set_save_path();//���ñ���·��
			void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif