#ifndef DESKTOPOMAKE_H
#define DESKTOPOMAKE_H 

#include "define.h"

namespace rem
{

	class DesktopOmake : public QMainWindow
	{
		Q_OBJECT

	private:

		Ui::DesktopOmakeClass ui;
		QPixmap background_picture;//����ͼƬ
		QPixmap word_picture;//����ͼƬ
		QPixmap picture_pixmap;//Ŀ��ͼ��
		QImage picture_image;//Ŀ��ͼ��
		QImage temp_image;//ÿ�β���ԭͼ�Ͻ��в��������Ա���ԭͼ�����½�
		QPoint m_point;//��¼���������ƶ�����
		QColor color;//����ɫ
		double value_resize;//��¼����ֵ
		int value_rotate;//��¼��תֵ
		bool background_enable;//�Ƿ���������ɫ
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		bool m_bPressed;//ȷ�������Ƿ񱻰���

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//�������������
		DesktopOmake(QWidget *parent = Q_NULLPTR);
		~DesktopOmake();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//��ק�¼�
		void dragEnterEvent(QDragEnterEvent *event);
		void dropEvent(QDropEvent *event);

		//�����¼�
		void keyPressEvent(QKeyEvent *event);

		//��������
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���

		//�ۺ���
		public slots:

			void slider_resize_change(int value);//ͼƬ�ߴ�ı�
			void slider_rotate_change(int value);//ͼƬ�Ƕȸı�
			void slider_color_red_change(int value);//ͼƬ��ɫ�������죩�ı�
			void slider_color_green_change(int value);//ͼƬ��ɫ�������̣��ı�
			void slider_color_blue_change(int value);//ͼƬ��ɫ�����������ı�
			void spinbox_1_change(int value);//spinbox�ı�
			void spinbox_2_change(int value);//spinbox�ı�
			void spinbox_3_change(int value);//spinbox�ı�
			void spinbox_4_change(int value);//spinbox�ı�
			void spinbox_5_change(int value);//spinbox�ı�
	};
}

#endif