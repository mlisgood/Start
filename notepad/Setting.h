#ifndef SETTING_H
#define SETTING_H

#include "define.h"

namespace rem
{
	class Setting : public QDialog
	{
		Q_OBJECT

	private:

		Ui::SettingClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QStringList *setting_text_address;//�������ı����ͺ�׺��ַ
		QStringList *setting_binary_address;//�����ڶ��������ͺ�׺��ַ
		QString filepath;//����ͼƬ·��
		QString dialog_information_path;//������ʾ��Ϣ
		QString *setting_default_open_method_address;//�����ڴ��ļ�Ĭ�Ϸ�ʽ��ַ
		QTextEdit *textedit_main;//�������ı���ָ�룬�����޸��Զ�����״̬
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		bool *setting_bool_value_address[3];//�����ڲ���ֵ��ַ
		int totalrandomnumber;//���ھ���ȫ�ֵ������
		int *setting_size_address[2];//�������ļ����С��ַ

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//��������������
		Setting(QWidget *parent = Q_NULLPTR);
		~Setting();

		//���ó�Ա����
		void set_textedit(QTextEdit *main_textedit);//��ȡ�ı����ַ
		void set_setting_text_address(QStringList *main_list);//��ȡ�������ַ�����1��ַ
		void set_setting_binary_address(QStringList *main_list);//��ȡ�������ַ�����2��ַ
		void set_setting_default_open_method_address(QString *main_string);//��ȡ�������ַ�����ַ
		void set_setting_bool_value_address(bool *main_array_index, int index);//��ȡ������bool��������Ԫ�ص�ַ
		void set_setting_size_address(int *main_array_index, int index);//��ȡ������int��������Ԫ�ص�ַ

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		public slots:

			//�б������ť
			void list_1_button();//���
			void list_2_button();//ɾ��һ��
			void list_3_button();//ɾ��ȫ��
			void list_4_button();//���
			void list_5_button();//ɾ��һ��
			void list_6_button();//ɾ��ȫ��

			//ȷ����ť����
			void accept_button();//ȷ�ϲ���

			//�رն���
			void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif