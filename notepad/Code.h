#ifndef CODE_H
#define CODE_H

#include "define.h"

namespace rem
{
	class Code : public QDialog
	{
		Q_OBJECT

	private:

		Ui::CodeClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QLabel *code_label;//�����������Ϣ��ʾ��
		QString filepath;//����ͼƬ·��
		QString chara_path;//���ͼƬ·��
		QString dialog_information_path;//������ʾ��Ϣ
		QString *code_receive;//�������������ڵı�����Ϣ
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		int totalrandomnumber;//���ھ���ȫ�ֵ������
		int hex_status;//�Ƿ��ڶ����Ʊ༭״̬

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//��������������
		Code(QWidget *parent = Q_NULLPTR);
		~Code();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		//���ó�Ա����
		void set_code_information(QString* code_information, QLabel *code_label_main_dialog, int status);//��ȡ������Ϣ���Ƿ��ڶ����Ʊ༭״̬

		public slots:

		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���	 
		void combobox_change(const QString &code_string);//��Ͽ�ѡ��
		void dialog_accept();//ȷ�ϲ���
	};
}

#endif