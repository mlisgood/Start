#ifndef FONT_H
#define FONT_H

#include "define.h"

namespace rem
{
	class Font : public QDialog
	{
		Q_OBJECT

	private:

		Ui::FontClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QString filepath;//����ͼƬ·��
		QString dialog_information_path;//������ʾ��Ϣ
		QTextEdit *textedit_font;//�������ı���ָ�룬�����޸�����
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		int totalrandomnumber;//���ھ���ȫ�ֵ������
		int resource_randomnumber;//���ھ�����Դ�ļ��������
		int hex_status;//�Ƿ�Ϊʮ������ģʽ

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//��������������
		Font(QWidget *parent = Q_NULLPTR);
		~Font();

		//��ʼ����
		void read_font();//��ȡ�����ļ�

		//���ó�Ա����
		void set_textedit(QTextEdit *main_textedit);//��ȡ�ı����ַ
		void set_resource_random_number(int number, int status);//��ȡ��Դ�ļ���Ҫ����ֵ����

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		public slots:

		//��Ͽ�ѡ��
		void combobox_change(const QString &);
		void font_change();

		//�رն���
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif