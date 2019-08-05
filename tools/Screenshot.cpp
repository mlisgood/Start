#include "define.h"

namespace rem
{

	//�ô������ڽ�ͼ�������ô��ں󣬸ô���͸��������������Ļ������Ϊģ̬���ڣ�������ֱ�ӹرգ���˷����˶�������Ļ�����Ĺ켣���л�ȡ�Ա��ڽ�ͼ�Ľ���
	//�������������
	Screenshot::Screenshot(QWidget *parent) : QDialog(parent)
	{
		ui.setupUi(this);
		setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);//ȥ��������
		setAttribute(Qt::WA_TranslucentBackground, true);//�����ڱ�����Ϊ͸��
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		QWidget *desktop = QApplication::desktop()->screen();//���ô�����������Ļ���������ڽ�ͼ
		resize(desktop->width(), desktop->height());
		setMouseTracking(true);//��ʹû����갴�������£�����Ҳ����չ���ƶ��¼�
		pt1.setX(0);//��ʼ��
		pt1.setY(0);
		pt2.setX(0);
		pt2.setY(0);
	}

	Screenshot::~Screenshot()
	{

	}

	//����¼�
	void Screenshot::mousePressEvent(QMouseEvent * event)
	{
		if (event->button() == Qt::RightButton)//���ʹ��������Ҽ����˳���ʹ������ͽ��н�ͼ
		{
			mousedown = false;
			emit close_window();
			close();
		}
		if (event->button() == Qt::LeftButton)//���ʹ�����������Ϳ�ʼ׼����ͼ������¼��ʼ����
		{
			pt1.setX(event->x());
			pt1.setY(event->y());
			mousedown = true;
		}
	}

	void Screenshot::mouseMoveEvent(QMouseEvent * event)//����ƶ���ʱ�������Ҫ��ͼ���ͱ��浱ǰ���������Ϊ��ֹ�����Ա��ڻ�������
	{
		if (mousedown)
		{
			pt2.setX(event->x());
			pt2.setY(event->y());
			update();//���»���
		}
	}

	void Screenshot::mouseReleaseEvent(QMouseEvent * event)//�ͷ���갴ť�������������������Ȼ���浱ǰ�������Ϊ����
	{
		if (event->button() == Qt::LeftButton)
		{
			pt2.setX(event->x());
			pt2.setY(event->y());
			repaint();//���»��ơ���Ϊ��ͼ���ջ��Ƶľ��ε����ת�����̵ļ�ʱ��Ҫ��ǳ��ߣ���˲���ʹ�õȵ���һ��paintEvent������ʱ����Ч��update()������ʹ��������Ч��repaint()��������ѡȡͼƬ�Ĺ����в��Ͽ����ƶ����Ȼ������ֹͣ����������ͼ���ܻ���о��α߿�
			mousedown = false;
			emit finish(pt1, pt2);//���������źţ�ʹ����������Ϊ�����Ա��ڽ�ͼ
			close();
		}
	}

	//�����¼�
	void Screenshot::keyPressEvent(QKeyEvent * event)//���������esc�����س������ո������ȡ����ͼ
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

	void Screenshot::paintEvent(QPaintEvent * event)//����͸�����ڣ�ע����ν�ͼ�����ڲ��ܱ�����͸���ȣ�����ʹ��͸������Ϊ1������ͼ����ɫRGB����Ҳ������΢�仯
	{
		int alpha_set = DIALOG_SCREENSHOT_EDGE_ALPHA_NUMBER;
		QPainter rect_paint(this);//���м��������Ĳ��ַ�Ϊ4�����ֱ����
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
		QPen rect_pen(QColor(DIALOG_SCREENSHOT_RECT_RED_NUMBER, DIALOG_SCREENSHOT_RECT_GREEN_NUMBER, DIALOG_SCREENSHOT_RECT_BLUE_NUMBER), 1);//���ε���ɫΪ��ɫ���߿���Ϊ1
		rect_paint.setPen(rect_pen);
		rect_paint.drawRect(pt1.x(), pt1.y(), pt2.x() - pt1.x(), pt2.y() - pt1.y());//���ƾ���
	}
}
