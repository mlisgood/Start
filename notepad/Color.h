#ifndef COLOR_H
#define COLOR_H

#include "define.h"

namespace rem
{
	class Color : public QDialog
	{
		Q_OBJECT

	private:

		Ui::ColorClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QString filepath;//����ͼƬ·��
		QString dialog_information_path;//������ʾ��Ϣ
		QTextEdit *textedit_font;//�������ı���ָ�룬�����޸�����
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		int totalrandomnumber;//���ھ���ȫ�ֵ������
		int resource_randomnumber;//���ھ�����Դ�ļ��������
		int select_color;//�����Ƿ����ѡȡ��ɫ
		int forbid_change;//Ϊ1����ֹspinbox�����Ҳཥ�们����ɫ�ı�
		int color_status[24];//�Զ�����ɫ״̬λ
		int color_red[24];//�Զ�����ɫ��
		int color_green[24];//�Զ�����ɫ��
		int color_blue[24];//�Զ�����ɫ��

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//��������������
		Color(QWidget *parent = Q_NULLPTR);
		~Color();

		//���ó�Ա����
		void set_textedit(QTextEdit *main_textedit);//��ȡ�ı����ַ
		void set_resource_random_number(int number);//��ȡ��Դ�ļ���Ҫ�ı���

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		public slots:

		//��ɫ��ѡ��
		void color_change_1();
		void color_change_2();
		void color_change_3();
		void color_change_4();
		void color_change_5();
		void color_change_6();
		void color_change_7();
		void color_change_8();
		void color_change_9();
		void color_change_10();
		void color_change_11();
		void color_change_12();
		void color_change_13();
		void color_change_14();
		void color_change_15();
		void color_change_16();
		void color_change_17();
		void color_change_18();
		void color_change_19();
		void color_change_20();
		void color_change_21();
		void color_change_22();
		void color_change_23();
		void color_change_24();
		void color_change_25();
		void color_change_26();
		void color_change_27();
		void color_change_28();
		void color_change_29();
		void color_change_30();
		void color_change_31();
		void color_change_32();
		void color_change_33();
		void color_change_34();
		void color_change_35();
		void color_change_36();
		void color_change_37();
		void color_change_38();
		void color_change_39();
		void color_change_40();
		void color_change_41();
		void color_change_42();
		void color_change_43();
		void color_change_44();
		void color_change_45();
		void color_change_46();
		void color_change_47();
		void color_change_48();
		void color_change_self_1();
		void color_change_self_2();
		void color_change_self_3();
		void color_change_self_4();
		void color_change_self_5();
		void color_change_self_6();
		void color_change_self_7();
		void color_change_self_8();
		void color_change_self_9();
		void color_change_self_10();
		void color_change_self_11();
		void color_change_self_12();
		void color_change_self_13();
		void color_change_self_14();
		void color_change_self_15();
		void color_change_self_16();
		void color_change_self_17();
		void color_change_self_18();
		void color_change_self_19();
		void color_change_self_20();
		void color_change_self_21();
		void color_change_self_22();
		void color_change_self_23();
		void color_change_self_24();

		//�ı���ɫ
		void color_change_spinbox(int number);//����������ռλ����ʵ��Ч��

		//���鴦��
		void color_slider_change(int value);//������ɫѡȡ

		//������ť����
		void color_select();//�����ɫѡȡ
		void color_remove();//�Զ�����ɫ���
		void color_add();//�Զ�����ɫ���
		void color_accept();//ȷ��������ɫ

		//�رն���
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif