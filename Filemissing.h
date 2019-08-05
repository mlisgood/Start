#ifndef FILEMISSING_H
#define FILEMISSING_H

#include "define.h"

namespace rem
{
	class Filemissing : public QDialog
	{
		Q_OBJECT

	private:

		Ui::FilemissingClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QString filepath;//����ͼƬ·��
		QString chara_path;//���ͼƬ·��
		QString information_path;//������ʾ��Ϣ
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		int totalrandomnumber;//���ھ���ȫ�ֵ������
		int information_status;//������Ϣ��ʾ���ݵı�־

	protected:

		void paintEvent(QPaintEvent *); //���Ʊ���ͼ��

	public:

		//��������������
		Filemissing(QWidget *parent = Q_NULLPTR);
		~Filemissing();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		//���ó�Ա����
		void set_dialog_information_status(int dialog_information_status);//���ó�Ա����information_status��ֵ����������Ҫ���õı�־��1Ϊ�ڴ治�㣬2Ϊ�޷����ļ���
		
	public slots:
	
		//�ۺ���
		void close_window_include_animation();//�رմ���
	};
}

#endif