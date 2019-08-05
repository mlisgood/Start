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
		QPoint pt1;//保存鼠标起始坐标
		QPoint pt2;//保存鼠标结束坐标
		bool mousedown;//判断是否应该截图

	public:

		Screenshot(QWidget *parent = 0);
		~Screenshot();

		//鼠标事件
		void mousePressEvent(QMouseEvent *);
		void mouseMoveEvent(QMouseEvent *);
		void mouseReleaseEvent(QMouseEvent *);

		//键盘事件
		void keyPressEvent(QKeyEvent *);

		//绘制事件
		void paintEvent(QPaintEvent *);

	signals:

		void finish(QPoint pt1, QPoint pt2);//截图成功
		void close_window();//截图失败
	};
}

#endif
