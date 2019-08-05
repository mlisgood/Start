#ifndef FIND_H
#define FIND_H

#include "define.h"

namespace rem
{
	class Find : public QDialog
	{
		Q_OBJECT

	private:

		Ui::FindClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QString filepath;//����ͼƬ·��
		QString chara_path;//���ͼƬ·��
		QString dialog_information_path;//������ʾ��Ϣ
		QTextEdit *textedit_find;//�������ı���ָ�룬���ڲ��Һ��滻
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		int totalrandomnumber;//���ھ���ȫ�ֵ������

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//��������������
		Find(QWidget *parent = Q_NULLPTR);
		~Find();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		//���ó�Ա����
		void set_dialog_information_path(QString inforation_path);//��������ͼƬ·��
		void set_textedit(QTextEdit *main_textedit);//��ȡ�ı����ַ

		public slots:

		void find_text_last();//�������ı�
		void find_text_next();//��ǰ�����ı�
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif