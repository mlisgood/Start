#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include "define.h"

namespace rem
{
	class Screenshot : public QDialog
	{
		Q_OBJECT

	private:

		Ui::ScreenshotClass ui;
		QPoint pt1;//���������ʼ����
		QPoint pt2;//��������������
		bool mousedown;//�ж��Ƿ�Ӧ�ý�ͼ

	public:

		Screenshot(QWidget *parent = 0);
		~Screenshot();

		//����¼�
		void mousePressEvent(QMouseEvent *);
		void mouseMoveEvent(QMouseEvent *);
		void mouseReleaseEvent(QMouseEvent *);

		//�����¼�
		void keyPressEvent(QKeyEvent *);

		//�����¼�
		void paintEvent(QPaintEvent *);

	signals:

		void finish(QPoint pt1, QPoint pt2);//��ͼ�ɹ�
		void close_window();//��ͼʧ��
	};
}

#endif
