#ifndef WIDGET_H
#define WIDGET_H

#include "define.h"

namespace rem
{

	//导入标准命名空间
	using std::wstring;

	class Widget : public QDialog
	{
		Q_OBJECT

	private:

		Ui::WidgetClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QPixmap picture;//背景图片
		wstring program_path;//打开程序路径
		double transparent;//透明度
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		int widget_id;//控件序号，决定背景图片
		int on_top;//是否显示在最顶层
		int position[2];//控件位置

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造与析构函数
		Widget(QWidget *parent = Q_NULLPTR);
		~Widget();

		//设置成员变量
		void set_attribute(bool on_top, int widget_id, int transparent, wstring program_path);//设置使用的图片id和打开程序路径

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//鼠标事件，用于启动程序
		void mouseDoubleClickEvent(QMouseEvent *event);

		//拖拽事件
		void dragEnterEvent(QDragEnterEvent *event);
		void dropEvent(QDropEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

	public slots:

		void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
	};
}

#endif