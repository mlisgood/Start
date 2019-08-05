#ifndef LOCK_H
#define LOCK_H 

#include "define.h"

namespace rem
{
	class Lock: public QMainWindow
	{
		Q_OBJECT

	private:

		Ui::LockClass ui;
		QPoint m_point;//��¼���������ƶ�����
		int randnumber;//���������������
		bool m_bPressed;//ȷ�������Ƿ񱻰���

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//�������������
		Lock(QWidget *parent = Q_NULLPTR);
		~Lock();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�رն���
		void hide_window_include_animation();//�������ش��ڶ��������ش��ڷ���
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���

	public slots:

		void close_dialog();//�رմ���
		void normal_lock_dialog();//������ܴ���
		void simple_lock_dialog();//�򵥼��ܴ���
		void set_dialog();//���ô���
		void help_information();//������Ϣ
		void show_window_include_animation();//������ʾ���ڶ�������ʾ���ڷ���
		void show_window_include_animation_end();//������ʾ����������
	};
}

#endif