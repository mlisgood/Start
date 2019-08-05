#ifndef COUNTER_H
#define COUNTER_H

#include "define.h"

namespace rem
{
	class Counter : public QDialog
	{
		Q_OBJECT

	private:

		Ui::CounterClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QPixmap main_picture;//��Ҫ�����Ա�����Ϊ���ڵ�ͼƬ
		QPixmap counter_time[8];//���Ƽ�ʱ��ʱ��ͼƬ����Ϊʱ�������һ����8�����֣������Ҫ8������������
		QString count_number;//��ʱ��������·��
		QTimer *time_counter;//��ʱ��
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool counter_pause;//ȷ����ʱ���Ƿ���ͣ
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		int setting_information[6];//������Ϣ��Ϊ�������ֱ�Ӳ�������洢�����ڵ�ѡ���飬�洢�����µİ�ť��ţ���������ѡ��򣬴洢���ֵ�ֵ
		int counter_hour;//��ʱ����ʾ��ʱ
		int counter_minute;//��ʱ����ʾ�ķ�
		int counter_second;//��ʱ����ʾ����
		int voice_randnumber;//������ʱ������ʹ�õ�������ŵ������

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//��������������
		Counter(QWidget *parent = Q_NULLPTR);
		~Counter();

		//��Ա��������
		void set_setting_information(int index, int value);//���ô洢����ֵ������Ԫ��ֵ�������ֱ�Ϊ����������Ԫ��ֵ
		void set_beginning_value();//���ò��ʺ��ڹ��캯�������õĳ�ʼֵ

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseDoubleClickEvent(QMouseEvent * event);

		//�����¼���������Ӧ��ݼ�
		void keyPressEvent(QKeyEvent *event);

		//�ۺ���
		public slots:

			void time_repaint();//��ʱ�����ڣ����»��ƺ���
			void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
			void close_window_sound();//������ʱ���رմ��ڲ�������
	};
}

#endif