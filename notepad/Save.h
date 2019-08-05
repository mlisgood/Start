#ifndef SAVE_H
#define SAVE_H

#include "define.h"

namespace rem
{
	class Save : public QDialog
	{
		Q_OBJECT

	private:

		Ui::SaveClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QString filepath;//����ͼƬ·��
		QString chara_path;//���ͼƬ·��
		QString dialog_information_path;//������ʾ��Ϣ
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		int totalrandomnumber;//���ھ���ȫ�ֵ������
		int return_number;//���°�ť�ķ���ֵ

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//��������������
		Save(QWidget *parent = Q_NULLPTR);
		~Save();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		//���ó�Ա����
		void set_dialog_information_path(QString inforation_path);//��������ͼƬ·��
		void set_return_number(int set_number);//���ð��°�ť���ص�ֵ
		int get_return_number();//ȡ�ð��°�ť���ص�ֵ

		public slots:

		//�ı�return_number��ֵ�������źŴ���
		void change_return_number_save();
		void change_return_number_discard();

		//�رն���
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif