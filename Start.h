#ifndef START_H
#define START_H

#include "define.h"

namespace rem
{
	class Start : public QMainWindow
	{
		Q_OBJECT

	private:

		Ui::StartClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QPixmap main_pixmap;//背景图片路径
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环

	protected:

		void paintEvent(QPaintEvent *); //绘制背景图像

	public:

		//构造与析构函数
		Start(QWidget *parent = Q_NULLPTR);
		~Start();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于响应快捷键
		void keyPressEvent(QKeyEvent *event);

		//其他功能
		bool copy_files(const QString &source_dir, const QString &target_dir);//拷贝文件夹

		public slots:

			void item1_clicked();//item1
			void item2_clicked();//item2
			void item3_clicked();//item3
			void item4_clicked();//item4
			void item5_clicked();//item5
			void close_window_include_animation();//关闭窗口
	};
}

#endif