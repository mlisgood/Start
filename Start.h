#ifndef START_H
#define START_H

#include "define.h"

namespace rem
{
	class Start : public QMainWindow
	{
		Q_OBJECT

	private:

		Ui::StartClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QPixmap main_pixmap;//����ͼƬ·��
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��

	protected:

		void paintEvent(QPaintEvent *); //���Ʊ���ͼ��

	public:

		//��������������
		Start(QWidget *parent = Q_NULLPTR);
		~Start();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼���������Ӧ��ݼ�
		void keyPressEvent(QKeyEvent *event);

		//��������
		bool copy_files(const QString &source_dir, const QString &target_dir);//�����ļ���

		public slots:

			void item1_clicked();//item1
			void item2_clicked();//item2
			void item3_clicked();//item3
			void item4_clicked();//item4
			void item5_clicked();//item5
			void close_window_include_animation();//�رմ���
	};
}

#endif