#ifndef PRINT_H
#define PRINT_H

#include "define.h"

namespace rem
{
	class Print : public QDialog
	{
		Q_OBJECT

	private:

		Ui::PrintClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QTimer *timer_print;//�������ʱ��
		QLabel *label_chara_print;//���������������ǩ
		QLabel *label_margin_print;//���������߽��ǩ
		QTextEdit *textedit_print;//�������ı���
		QString chara_path_print;//������������������״̬·��
		QString filepath;//����ͼƬ·��
		QString chara_path;//���ͼƬ·��
		QString dialog_information_path;//������ʾ��Ϣ
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		int *flag_print;//�������ʱ��״̬
		int totalrandomnumber;//���ھ���ȫ�ֵ������

	public:

		//��������������
		Print(QWidget *parent = Q_NULLPTR);
		~Print();

		//��Ա��������
		void set_textedit(QTextEdit *main_textedit);//��ȡ�������ı����ַ
		void set_timer(QTimer *main_timer);//��ȡ�������ʱ����ַ
		void set_label_chara(QLabel *main_label);//��ȡ���������������ǩ��ַ
		void set_label_margin(QLabel *main_label);//��ȡ���������߽��ǩ��ַ
		void set_chara_path(QString main_chara_path);//��ȡ������������������״̬·��
		void set_flag(int *main_flag);//��ȡ�������ʱ��״̬

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		public slots:

		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���	 
		void dialog_accept();//ȷ�ϲ���
	};
}

#endif