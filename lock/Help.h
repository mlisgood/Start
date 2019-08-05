#ifndef HELP_H
#define HELP_H

#include "define.h"

namespace rem
{
	class Help : public QDialog
	{
		Q_OBJECT

	private:

		Ui::HelpClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QString filepath;//����ͼƬ·��
		QString chara_path;//���ͼƬ·��
		QString dialog_information_path;//������ʾ��Ϣ
		int totalrandomnumber;//���ھ���ȫ�ֵ������
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//��������������
		Help(QWidget *parent = Q_NULLPTR);
		~Help();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		//���ó�Ա����
		void set_dialog_information_path(QString inforation_path);//��������ͼƬ·��

	public slots:

		//�رն���
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif