#ifndef LOCKSIMPLE_H
#define LOCKSIMPLE_H 

#include "define.h"

namespace rem
{
	class LockSimple: public QDialog
	{
		Q_OBJECT

	private:

		Ui::LockSimpleClass ui;
		QPoint m_point;//��¼���������ƶ�����
		int randnumber;//���������������
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//�������������
		LockSimple(QWidget *parent = Q_NULLPTR);
		~LockSimple();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		//�رն���
		void hide_window_include_animation();//�������ش��ڶ��������ش��ڷ���
		void close_window_include_animation_and_show_mainwindow();//�����رմ��ڶ����Ĺرմ�����ʾ�����ڷ���

	signals:

		void show_mainwindow();//��ʾ�������ź�

	public slots:

		void close_dialog();//����������
		void method_1_dialog();//ȡ�����ܴ���
		void method_2_dialog();//�Ӽ����ܴ���
		void show_window_include_animation();//������ʾ���ڶ�������ʾ���ڷ���
		void show_window_include_animation_end();//������ʾ����������
	};
}

#endif