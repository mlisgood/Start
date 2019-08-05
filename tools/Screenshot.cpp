#include "define.h"

namespace rem
{

	//该窗口用于截图。创建该窗口后，该窗口透明，充满整个屏幕，并且为模态窗口，还不能直接关闭，因此方便了对整个屏幕上鼠标的轨迹进行获取以便于截图的进行
	//构造和析构函数
	Screenshot::Screenshot(QWidget *parent) : QDialog(parent)
	{
		ui.setupUi(this);
		setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);//去掉标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//将窗口背景改为透明
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		QWidget *desktop = QApplication::desktop()->screen();//设置窗口是整个屏幕，这样便于截图
		resize(desktop->width(), desktop->height());
		setMouseTracking(true);//即使没有鼠标按键被按下，窗口也会接收光标移动事件
		pt1.setX(0);//初始化
		pt1.setY(0);
		pt2.setX(0);
		pt2.setY(0);
	}

	Screenshot::~Screenshot()
	{

	}

	//鼠标事件
	void Screenshot::mousePressEvent(QMouseEvent * event)
	{
		if (event->button() == Qt::RightButton)//如果使用了鼠标右键就退出，使用左键就进行截图
		{
			mousedown = false;
			emit close_window();
			close();
		}
		if (event->button() == Qt::LeftButton)//如果使用了鼠标左键就开始准备截图，并记录起始坐标
		{
			pt1.setX(event->x());
			pt1.setY(event->y());
			mousedown = true;
		}
	}

	void Screenshot::mouseMoveEvent(QMouseEvent * event)//鼠标移动的时候，如果需要截图，就保存当前点的坐标作为终止坐标以便于画出矩形
	{
		if (mousedown)
		{
			pt2.setX(event->x());
			pt2.setY(event->y());
			update();//重新绘制
		}
	}

	void Screenshot::mouseReleaseEvent(QMouseEvent * event)//释放鼠标按钮，如果是鼠标左键，就仍然保存当前点坐标记为坐标
	{
		if (event->button() == Qt::LeftButton)
		{
			pt2.setX(event->x());
			pt2.setY(event->y());
			repaint();//重新绘制。因为截图最终绘制的矩形到点的转换过程的即时性要求非常高，因此不能使用等到下一次paintEvent被调用时才生效的update()，必须使用立即生效的repaint()，否则在选取图片的过程中不断快速移动鼠标然后立即停止，截下来的图可能会带有矩形边框
			mousedown = false;
			emit finish(pt1, pt2);//发出结束信号，使用两个点作为参数以便于截图
			close();
		}
	}

	//键盘事件
	void Screenshot::keyPressEvent(QKeyEvent * event)//如果按下了esc键、回车键、空格键，就取消截图
	{
		int key = event->key();
		if (key == Qt::Key_Escape || Qt::Key_Space || key == Qt::Key_Enter)
		{
			mousedown = false;
			emit close_window();
			close();
		}
		else
		{

		}
	}

	void Screenshot::paintEvent(QPaintEvent * event)//绘制透明窗口，注意矩形截图区域内不能保留不透明度，否则即使不透明度设为1，所截图像颜色RGB分量也会有轻微变化
	{
		int alpha_set = DIALOG_SCREENSHOT_EDGE_ALPHA_NUMBER;
		QPainter rect_paint(this);//将中间矩形以外的部分分为4个，分别绘制
		if (pt2.x() >= pt1.x() && pt2.y() >= pt1.y())
		{
			rect_paint.fillRect(0, 0, width(), pt1.y(), QColor(0, 0, 0, alpha_set));
			rect_paint.fillRect(0, pt2.y(), width(), height() - pt2.y(), QColor(0, 0, 0, alpha_set));
			rect_paint.fillRect(0, pt1.y(), pt1.x(), pt2.y() - pt1.y(), QColor(0, 0, 0, alpha_set));
			rect_paint.fillRect(pt2.x(), pt1.y(), width() - pt2.x(), pt2.y() - pt1.y(), QColor(0, 0, 0, alpha_set));
		}
		else if (pt2.x() < pt1.x() && pt2.y() >= pt1.y())
		{
			rect_paint.fillRect(0, 0, width(), pt1.y(), QColor(0, 0, 0, alpha_set));
			rect_paint.fillRect(0, pt2.y(), width(), height() - pt2.y(), QColor(0, 0, 0, alpha_set));
			rect_paint.fillRect(0, pt1.y(), pt2.x(), pt2.y() - pt1.y(), QColor(0, 0, 0, alpha_set));
			rect_paint.fillRect(pt1.x(), pt1.y(), width() - pt1.x(), pt2.y() - pt1.y(), QColor(0, 0, 0, alpha_set));
		}
		else if (pt2.x() >= pt1.x() && pt2.y() < pt1.y())
		{
			rect_paint.fillRect(0, 0, width(), pt2.y(), QColor(0, 0, 0, alpha_set));
			rect_paint.fillRect(0, pt1.y(), width(), height() - pt1.y(), QColor(0, 0, 0, alpha_set));
			rect_paint.fillRect(0, pt2.y(), pt1.x(), pt1.y() - pt2.y(), QColor(0, 0, 0, alpha_set));
			rect_paint.fillRect(pt2.x(), pt2.y(), width() - pt2.x(), pt1.y() - pt2.y(), QColor(0, 0, 0, alpha_set));
		}
		else
		{
			rect_paint.fillRect(0, 0, width(), pt2.y(), QColor(0, 0, 0, alpha_set));
			rect_paint.fillRect(0, pt1.y(), width(), height() - pt1.y(), QColor(0, 0, 0, alpha_set));
			rect_paint.fillRect(0, pt2.y(), pt2.x(), pt1.y() - pt2.y(), QColor(0, 0, 0, alpha_set));
			rect_paint.fillRect(pt1.x(), pt2.y(), width() - pt1.x(), pt1.y() - pt2.y(), QColor(0, 0, 0, alpha_set));
		}
		QPen rect_pen(QColor(DIALOG_SCREENSHOT_RECT_RED_NUMBER, DIALOG_SCREENSHOT_RECT_GREEN_NUMBER, DIALOG_SCREENSHOT_RECT_BLUE_NUMBER), 1);//矩形的颜色为红色，边框宽度为1
		rect_paint.setPen(rect_pen);
		rect_paint.drawRect(pt1.x(), pt1.y(), pt2.x() - pt1.x(), pt2.y() - pt1.y());//绘制矩形
	}
}
