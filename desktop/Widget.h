#ifndef WIDGET_H
#define WIDGET_H

#include "define.h"

namespace rem
{

	//�����׼�����ռ�
	using std::wstring;

	class Widget : public QDialog
	{
		Q_OBJECT

	private:

		Ui::WidgetClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QPixmap picture;//����ͼƬ
		wstring program_path;//�򿪳���·��
		double transparent;//͸����
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		int widget_id;//�ؼ���ţ���������ͼƬ
		int on_top;//�Ƿ���ʾ�����
		int position[2];//�ؼ�λ��

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//��������������
		Widget(QWidget *parent = Q_NULLPTR);
		~Widget();

		//���ó�Ա����
		void set_attribute(bool on_top, int widget_id, int transparent, wstring program_path);//����ʹ�õ�ͼƬid�ʹ򿪳���·��

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//����¼���������������
		void mouseDoubleClickEvent(QMouseEvent *event);

		//��ק�¼�
		void dragEnterEvent(QDragEnterEvent *event);
		void dropEvent(QDropEvent *event);

		//�����¼��������޸Ļس�����Ĭ���˳�����
		void keyPressEvent(QKeyEvent *event);

	public slots:

		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
	};
}

#endif