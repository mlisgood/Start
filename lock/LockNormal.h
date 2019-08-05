#ifndef LOCKNORMAL_H
#define LOCKNORMAL_H 

#include "define.h"

namespace rem
{
	class LockNormal: public QDialog
	{
		Q_OBJECT

	private:

		Ui::LockNormalClass ui;
		QPoint m_point;//��¼���������ƶ�����
		int randnumber;//���������������
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//�������������
		LockNormal(QWidget *parent = Q_NULLPTR);
		~LockNormal();

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
		void apply();//�������
		void combobox_change(const QString &combobox_string);//��Ͽ����ݸ��ĺ���
		void show_window_include_animation();//������ʾ���ڶ�������ʾ���ڷ���
		void show_window_include_animation_end();//������ʾ����������
	};
}

#endif