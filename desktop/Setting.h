#ifndef Setting_H
#define Setting_H

#include "define.h"

namespace rem
{
	class Setting : public QDialog
	{
		Q_OBJECT

	private:

		Ui::SettingClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QPixmap main_picture;//��Ҫ�����Ա�����Ϊ���ڵ�ͼƬ
		QPixmap widget_picture[7];//��Ҫ���Ƶ����ͼƬ
		int picture_digit[7];//ͼƬ͸����
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��

	protected:

		void paintEvent(QPaintEvent *); //���Ʊ���ͼ��

	public:

		//��������������
		Setting(QWidget *parent = Q_NULLPTR);
		~Setting();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		public slots:
		
			void set_apply();//������Ч
			void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���

			//ѡ��·��
			void pushButton_select_1();
			void pushButton_select_2();
			void pushButton_select_3();
			void pushButton_select_4();
			void pushButton_select_5();
			void pushButton_select_6();
			void pushButton_select_7();

			//���·��
			void pushButton_delete_1();
			void pushButton_delete_2();
			void pushButton_delete_3();
			void pushButton_delete_4();
			void pushButton_delete_5();
			void pushButton_delete_6();
			void pushButton_delete_7();

			//͸���ȼ���
			void pushButton_transparent_down_1();
			void pushButton_transparent_down_2();
			void pushButton_transparent_down_3();
			void pushButton_transparent_down_4();
			void pushButton_transparent_down_5();
			void pushButton_transparent_down_6();
			void pushButton_transparent_down_7();

			//͸��������
			void pushButton_transparent_up_1();
			void pushButton_transparent_up_2();
			void pushButton_transparent_up_3();
			void pushButton_transparent_up_4();
			void pushButton_transparent_up_5();
			void pushButton_transparent_up_6();
			void pushButton_transparent_up_7();
	};
}

#endif