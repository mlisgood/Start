#ifndef SET_H
#define SET_H

#include "define.h"

namespace rem
{
	class Set : public QDialog
	{
		Q_OBJECT

	private:

		Ui::SetClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QPixmap main_picture;//��Ҫ�����Ա�����Ϊ���ڵ�ͼƬ
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��

	protected:

		void paintEvent(QPaintEvent *); //���Ʊ���ͼ��

	public:

		//��������������
		Set(QWidget *parent = Q_NULLPTR);
		~Set();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

		//·����Ϣ��ȡ
		void set_save_path(QLineEdit *lineEdit);//���ļ��򿪽����ȡ·����Ϣ������Ϊ����ʾ��QLineEdit
		void run_path(QString path, QString default_path);//����Ӧ·�����ú�������Ҫ������ں����Ĳ�����Ŀ��������ѡ������壨1����ڲ��������ǳ���Ŀ�꣨2����ڲ���������ֱ�Ӵ򿪡��������ļ�·����Ĭ��·��

		//�������ܺ���
		bool delete_files(QString path);//ɾ���ļ�����ȫ���ļ����������ļ��С�����Ϊ�ļ���·��

	public slots:

		void open_path_lock();//�򿪼����ļ�·��
		void open_path_unlock();//�򿪽����ļ�·��
		void open_path_temp();//����ʱ�ļ�·��
		void open_path_history();//����ʷ�ļ�·��
		void delete_temp();//ɾ����ʱ�ļ�
		void delete_history();//�����ʷ�ļ�
		void get_path_lock();//��ü����ļ�·������
		void get_path_unlock();//��ý����ļ�·������
		void get_path_temp();//�����ʱ�ļ�·������
		void get_path_history();//�����ʷ�ļ�·������
		void set_apply();//������Ч
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif