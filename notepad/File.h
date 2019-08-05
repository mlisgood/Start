#ifndef FILE_H
#define FILE_H

#include "define.h"

namespace rem
{
	class File : public QDialog
	{
		Q_OBJECT

	private:

		Ui::FileClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QString filepath_background;//����ͼƬ·��
		QString dialog_information_path_temp;//�洢��ϢͼƬ·��
		QString dialog_information_head_path_temp;//�洢ͷ����ϢͼƬ·��
		QString file_path_show;//������ʾ���ļ�·��
		QString current_path;//��ǰ����·��
		QString *file_path;//�ļ�·��ָ��
		QFileSystemModel *file_tree;//�ļ�Ŀ¼
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool *file_dialog_status;//�ļ����򿪻��߱����Լ��˳��ô��ڵ��ж���
		bool open_or_save;//ȷ���Ǵ򿪻��Ǳ��棬0Ϊ�򿪣�1Ϊ����
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		int totalrandomnumber;//���ھ���ȫ�ֵ������

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//��������������
		File(QWidget *parent = Q_NULLPTR);
		~File();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		//���ó�Ա����
		void set_button_save_or_open(int status);//���ô��������Ǵ��ļ����Ǳ����ļ�����־����Ϊ0������Ϊ1
		void set_file_path_address(QString *path);//�����ļ�·����ַ
		void set_file_dialog_status_address(bool *status);//���ô��ڲ�����ַ
		void set_current_path(QString object_string);//���뵱ǰ����·��

		public slots:

		void get_tree_view_selected_file_name(const QModelIndex &index);//�õ��ļ�·��
		void get_text_edit_file_name();//�ļ�·���ı�����Ϣ�ı�ʱ����ļ�·��
		void open_or_save_button();//�򿪻��߱��水ť
		void open_or_save_branch();//��֧˫��
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif