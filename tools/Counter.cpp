#include "define.h"

namespace rem
{

	//����ȫ�ֱ���
	extern int counter_mutex;

	//��������������
	Counter::Counter(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		voice_randnumber = DIALOG_TIME_COUNTER_END_VOICE_MIN_NUMBER + rand() % (DIALOG_TIME_COUNTER_END_VOICE_MAX_NUMBER - DIALOG_TIME_COUNTER_END_VOICE_MIN_NUMBER + 1);//����ָ�����������ѡ�����ʱ����������
		setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | windowFlags());//ȥ�����ڱ������������������в�����ִ���
		setAttribute(Qt::WA_TranslucentBackground, true);//�����ڱ���͸����
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		setAttribute(Qt::WA_DeleteOnClose);//�˳�ʱ���ٸô��������ڴ�й©
		counter_mutex--;//����ļ�ʱ�����ڵ���Ŀ����1
		counter_pause = false;//��ʱ��δ������ͣ״̬
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�
		
		//���ؽ���
		ui.setupUi(this);

		//����ͼƬ��Ϊ���ڱ���
		main_picture.load(DIALOG_COUNTER_BACKGROUND_PICTURE_PATH_STRING);
		resize(DIALOG_COUNTER_SIZE_WIDTH_NUMBER, DIALOG_COUNTER_SIZE_HEIGHT_NUMBER);//���ڴ�С��ΪͼƬ��С���˴β�����ͼƬΪ�磬��Ϊ��Ҫ��������͸������
	
		//��ʱ��
		time_counter = new QTimer(this);//����һ����ʱ��
		time_counter->setTimerType(Qt::PreciseTimer);//�޸ľ���
		time_counter->start(DIALOG_COUNTER_INTERVAL_NUMBER);//��ʼ����ʱ����Ȼ��ʼ��ֻ��ʱ1�����
		connect(time_counter, SIGNAL(timeout()), this, SLOT(time_repaint()));//��ʱ�����ڴ������»���ʱ��ͼƬ

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}
	Counter::~Counter()
	{
		counter_mutex++;//����ļ�ʱ�����ڵ���Ŀ����1
		delete time_counter;
	}

	//��Ա��������
	void Counter::set_setting_information(int index, int value)
	{
		setting_information[index] = value;
	}

	void Counter::set_beginning_value()//���ó�ʼֵ����һ���־��Բ��ܷŽ����캯������Ϊ���캯���ڴ������ڶ����ʱ��ͻ�ʹ�ã��ȶ�����ĸ�ֵҪ��
	{
		//������һ�����ڵ����������г�ʼ��
		if (setting_information[5] == 1)//�����Ƿ������
		{
			setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
		}
		else if (setting_information[5] == 2)
		{
			
		}
		else
		{
			
		}
		if (setting_information[0] == 1)//��ʱ������
		{
			counter_hour = 0;//ʱ
			counter_minute = 0;//��
			counter_second = 0;//��
		}
		else if (setting_information[0] == 2)
		{
			counter_hour = setting_information[1];//ʱ
			counter_minute = setting_information[2];//��
			counter_second = setting_information[3];//��
		}
		else
		{
			counter_hour = 0;//ʱ
			counter_minute = 0;//��
			counter_second = 0;//��
		}
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void Counter::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bPressed = true;
			m_point = event->pos();
		}
		else
		{

		}
	}
	//�������������£����ƶ�����λ��
	void Counter::mouseMoveEvent(QMouseEvent *event)
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}
	}

	//���δ�����£�����Ӧ����Ϊfalse
	void Counter::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//���˫������ͣ��ָ�״̬֮���л�
	void Counter::mouseDoubleClickEvent(QMouseEvent *event)
	{
		if (counter_pause == false)
		{
			counter_pause = true;
			time_counter->stop();
		}
		else
		{
			counter_pause = false;
			time_counter->start();
		}
	}

	//�����¼������ڽ�������
	void Counter::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Escape)
		{
			if (!is_escape_pressed)//��ִ��һ�ΰ���esc�˳�
			{
				is_escape_pressed = true;
				close_window_include_animation();
			}
			else
			{

			}
		}
	}

	void Counter::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(WINDOW_BACKGROUND_PAINT_START_X_NUMBER, WINDOW_BACKGROUND_PAINT_START_Y_NUMBER, main_picture);//��ͼ��Ϊ���ڱ���
		count_number = DIALOG_COUNTER_NUMBER_PICTURE_PATH_FRONT_STRING;//ʱ��ʮλ
		count_number += QString::number((int)counter_hour / 10, 10);
		count_number += DIALOG_COUNTER_NUMBER_PICTURE_PATH_BACK_STRING;
		counter_time[0].load(count_number);
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[0]);//ÿ�λ��Ƶ�ʱ����ʼ��ĺ����������ƶ�һ��ʱ������ͼƬ���
		count_number = DIALOG_COUNTER_NUMBER_PICTURE_PATH_FRONT_STRING;//ʱ�ĸ�λ
		count_number += QString::number((int)counter_hour % 10, 10);
		count_number += DIALOG_COUNTER_NUMBER_PICTURE_PATH_BACK_STRING;
		counter_time[1].load(count_number);
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER + DIALOG_COUNTER_NUMBER_PICTURE_WIDTH, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[1]);
		counter_time[2].load(DIALOG_COUNTER_COLON_PICTURE_PATH_STRING);//�ָ���1
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER + DIALOG_COUNTER_NUMBER_PICTURE_WIDTH * 2, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[2]);
		count_number = DIALOG_COUNTER_NUMBER_PICTURE_PATH_FRONT_STRING;//�ֵ�ʮλ
		count_number += QString::number((int)counter_minute / 10, 10);
		count_number += DIALOG_COUNTER_NUMBER_PICTURE_PATH_BACK_STRING;
		counter_time[3].load(count_number);
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER + DIALOG_COUNTER_NUMBER_PICTURE_WIDTH * 3, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[3]);
		count_number = DIALOG_COUNTER_NUMBER_PICTURE_PATH_FRONT_STRING;//�ֵĸ�λ
		count_number += QString::number((int)counter_minute % 10, 10);
		count_number += DIALOG_COUNTER_NUMBER_PICTURE_PATH_BACK_STRING;
		counter_time[4].load(count_number);
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER + DIALOG_COUNTER_NUMBER_PICTURE_WIDTH * 4, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[4]);
		counter_time[5].load(DIALOG_COUNTER_COLON_PICTURE_PATH_STRING);//�ָ���2
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER + DIALOG_COUNTER_NUMBER_PICTURE_WIDTH * 5, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[5]);
		count_number = DIALOG_COUNTER_NUMBER_PICTURE_PATH_FRONT_STRING;//���ʮλ
		count_number += QString::number((int)counter_second / 10, 10);
		count_number += DIALOG_COUNTER_NUMBER_PICTURE_PATH_BACK_STRING;
		counter_time[6].load(count_number);
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER + DIALOG_COUNTER_NUMBER_PICTURE_WIDTH * 6, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[6]);
		count_number = DIALOG_COUNTER_NUMBER_PICTURE_PATH_FRONT_STRING;//��ĸ�λ
		count_number += QString::number((int)counter_second % 10, 10);
		count_number += DIALOG_COUNTER_NUMBER_PICTURE_PATH_BACK_STRING;
		counter_time[7].load(count_number);
		painter.drawPixmap(DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER + DIALOG_COUNTER_NUMBER_PICTURE_WIDTH * 7, DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER, counter_time[7]);
	}

	void Counter::time_repaint()//��ʱ������
	{
		if (setting_information[0] == 2)//�ǵ�����ʱ��
		{
			if (counter_second > 0)//�����������0���������1�����������1������������Ϊ���ֵ����������ͬ����ʽ������ʱ���֡����Ϊ0ʱ���˳���ע��������£���������֮��Ӧ��û�а�����ϵ
			{
				counter_second--;
			}
			else if (counter_second <= 0 && counter_minute > 0)
			{
				counter_minute--;
				counter_second = 59;
			}
			else if (counter_second <= 0 && counter_minute <= 0 && counter_hour > 0)
			{
				counter_hour--;
				counter_minute = 59;
				counter_second = 59;
			}
			else if (counter_second <= 0 && counter_minute <= 0 && counter_hour <= 0)
			{
				QPropertyAnimation *animation_close = new QPropertyAnimation(this, "windowOpacity");
				animation_close->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//���ڹرն���Ч��
				animation_close->setStartValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
				animation_close->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
				animation_close->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
				connect(animation_close, SIGNAL(finished()), this, SLOT(close_window_sound()));
			}
			else
			{

			}
		}
		else//�ǳ����ʱ��
		{
			if (counter_hour >= 99 && counter_second >= 59 && counter_minute >= 59)//ʱ��ﵽ����ֱ����ֹ
			{
				close_window_include_animation();
			}
			else if (counter_minute >= 59 && counter_second >= 59)//�������С��59���������1�����������1������������Ϊ��Сֵ����������ͬ����ʽ����ע��������£���������֮��Ӧ��û�а�����ϵ
			{
				counter_hour++;
				counter_minute = 0;
				counter_second = 0;
			}
			else if (counter_second >= 59)
			{
				counter_minute++;
				counter_second = 0;
			}
			else if (counter_second < 59)
			{
				counter_second++;
			}
			else
			{
				close_window_include_animation();
			}
		}
		update();//���»���	
	}

	void Counter::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
	{

		//�������а�ť�����򶯻��������ǰ�ٴε����ť�����´�������
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(false);
		}
		QPropertyAnimation *animation_close = new QPropertyAnimation(this, "windowOpacity");
		animation_close->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//���ڹرն���Ч��
		animation_close->setStartValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation_close->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_close->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		connect(animation_close, SIGNAL(finished()), this, SLOT(close()));
	}

	void Counter::close_window_sound()//������ʱ���رմ��ڲ�������
	{
		QString voice_path_string = DIALOG_TIME_COUNTER_END_VOICE_FRONT_STRING;//����������·��
		voice_path_string += QString::number(setting_information[4], 10);//��һ����������һ�����ڵ�ѡ�����
		voice_path_string += DIALOG_TIME_COUNTER_END_VOICE_BREAK_STRING;//�ָ���
		voice_path_string += QString::number(voice_randnumber, 10);//�ڶ����������ѡ��
		voice_path_string += DIALOG_TIME_COUNTER_END_VOICE_BACK_STRING;//��׺
		QSound::play(voice_path_string);//������Ч�������ʹ��һ���̡߳�ע��QSoundʵ���Ϸǳ��ӣ�wav�ļ��ı����ʲ���̫�󣬷����޷�����
		close();
	}
}

