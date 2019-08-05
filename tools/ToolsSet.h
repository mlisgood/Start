#ifndef TOOLSSET_H
#define TOOLSSET_H

#include "define.h"

namespace rem
{
	class ToolsSet : public QDialog
	{
		Q_OBJECT

	private:

		Ui::ToolsSetClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QPixmap main_picture;//��Ҫ�����Ա�����Ϊ���ڵ�ͼƬ
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��

	protected:

		void paintEvent(QPaintEvent *); //���Ʊ���ͼ��

	public:

		//��������������
		ToolsSet(QWidget *parent = Q_NULLPTR);
		~ToolsSet();

		//��ʼ����
		void read_font();//��ȡϵͳ���岢����combobox

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		public slots:
		
			void set_apply();//������Ч
			void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
			void pushButton_choose_1_apply();//���ð�ť��Ч
			void pushButton_choose_2_apply();
			void pushButton_choose_3_apply();
			void pushButton_choose_4_apply();
			void pushButton_choose_5_apply();
			void pushButton_choose_6_apply();
			void pushButton_choose_7_apply();
			void pushButton_choose_8_apply();
			void pushButton_choose_9_apply();
			void pushButton_choose_10_apply();
			void pushButton_choose_11_apply();
			void pushButton_choose_12_apply();
			void pushButton_choose_13_apply();
			void pushButton_choose_14_apply();
			void pushButton_choose_15_apply();
			void pushButton_choose_16_apply();
	};
}

#endif