#ifndef NOTE_H
#define NOTE_H

#include "define.h"

namespace rem
{
	class Note : public QDialog
	{
		Q_OBJECT

	private:

		Ui::NoteClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QString filepath;//����ͼƬ·��
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool on_top;//ȷ�������Ƿ�ʼ���ڶ���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		int totalrandomnumber;//���ھ���ȫ�ֵ������

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//��������������
		Note(QWidget *parent = Q_NULLPTR);
		~Note();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		//����
		void set_font(QString font);//�޸�����

		//�ۺ���
		public slots:

			void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif