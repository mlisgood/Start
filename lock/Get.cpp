#include "define.h"

namespace rem
{

	//��������������
	Get::Get(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		resize(DIALOG_LOCK_SIZE_WIDTH_NUMBER, DIALOG_LOCK_SIZE_HEIGHT_NUMBER);//������ǿ�Ƹ�Ϊ�˴�С
		setFixedSize(this->width(), this->height());//��ֹ�ı䴰�ڴ�С
		setAttribute(Qt::WA_QuitOnClose, true);//�ô��ڹر�ʱ���˳�����

		//��ʱ��
		timer_picture_count = DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER + rand() % (DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER - DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER + 1);//����ָ������������ڹ��캯����ʹ��һ�Σ��Ա�֤����������ز��򿪴��ں󱳾���Ϊ���»�ͼ�����仯������
		timer_transparent_count = 0;//ͼƬ��ʼ͸�����趨
		timer_interval = DIALOG_LOCK_CHARA_PICTURE_COUNT_INTERVAL_NUMNER;//��ʼͼƬ���ֲ����Ϊ��׼���л�ͼƬ���
		timer = new QTimer(this);//��ʼ����ʱ��
		connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));//�źŴ���
		timer->start(timer_interval);

		//���ؽ��棬�����������Ա�����汻֮��Ļ�ͼ����
		ui.setupUi(this);

		//��ť
		ui.pushButton_1->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture/icon/get_button_normal_1.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture/icon/get_button_pressed_1.png);}");
		ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture/icon/get_button_normal_2.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture/icon/get_button_pressed_2.png);}");

		//ͼƬ��ʼ��
		effect_1 = new QGraphicsOpacityEffect(this);//��Ч
		effect_2 = new QGraphicsOpacityEffect(this);
		effect_1->setOpacity(1 - timer_transparent_count);
		effect_2->setOpacity(0);
		QPixmap background_picture;//����δ�л�ʱ�ı���ͼƬ
		QString background_path = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//��ʱ�洢ԭʼ����ͼƬ·��
		background_path += QString::number(timer_picture_count, 10);//��һ��ͼƬʹ�������
		background_path += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
		background_picture.load(background_path);//���ر���ͼƬ
		ui.label_chara_1->setGraphicsEffect(effect_1);//����ʹ������ͼƬ
		ui.label_chara_1->setPixmap(background_picture);
		ui.label_chara_2->setGraphicsEffect(effect_2);//ǰ��ʹ��ȫ͸��ͼƬ
		ui.label_chara_2->setPixmap(QPixmap(DIALOG_BACKGROUND_CHARA_TRANSPARENT_PICTURE_PATH_STRING));
	}

	Get::~Get()
	{
		delete timer;
		delete effect_1;
		delete effect_2;
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void Get::mousePressEvent(QMouseEvent *event)
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
	void Get::mouseMoveEvent(QMouseEvent *event)
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
	void Get::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ������������Ϊֻ��ȷ�ϲ�������������Ҫ��д����Ϊ�˱���ͳһ�����ǽ�������д
	void Get::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Enter)
		{

		}
		else if (event->key() == Qt::Key_Escape)
		{
			close();
		}
		else
		{

		}
	}

	void Get::timer_timeout()//ʹ��2��label��������ͼƬ������ָ��һ����ʱ����������ʾͼƬ����ʱͼƬ���²�label���ϲ�labelʹ��ȫ͸��ͼƬ����������ԡ�ʱ�䵽�ں󣬸����л�ͼƬ͸������ʹ�õĶ�ʱ������ͬʱ��ʼ�޸�͸���ȼ������²�label��ʾԭʼͼƬ����͸�����𽥼�С���ϲ�label��ʾ�л���ͼƬ����͸���������ӡ����ϲ�labelͼƬ͸����Ϊ1ʱ���л�������ͼƬ��������1�����µĳ�ʱ�������¿�ʼ��һ��ʱѭ��
	{
		if (timer_interval == DIALOG_LOCK_CHARA_PICTURE_COUNT_INTERVAL_NUMNER)//�����ʱ�䵽�ڣ�˵��Ӧ���л�ͼƬ
		{
			timer_interval = DIALOG_LOCK_CHARA_PICTURE_TRANSPARENT_COUNT_INTERVAL_NUMNER;//�л�Ϊ͸���ȸ��ļ��
			timer_transparent_count = DIALOG_LOCK_CHARA_PICTURE_TRANSPARENT_COUNT_MEASURE_NUMNER;
			effect_1->setOpacity(1 - timer_transparent_count);
			effect_2->setOpacity(timer_transparent_count);
			QPixmap background_picture_back;//����ԭʼͼƬ
			QString background_path_back = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//��ʱ�洢ԭʼ����ͼƬ·��
			background_path_back += QString::number(timer_picture_count, 10);
			background_path_back += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
			background_picture_back.load(background_path_back);//����ͼƬ
			QPixmap background_picture_next;//�����л���ͼƬ
			QString background_path_next = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//��ʱ�洢�л��󱳾�ͼƬ·��
			if (timer_picture_count + 1 >= DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER + 1)//����ͼƬ˳���������Χ
			{
				background_path_next += QString::number(DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER, 10);
			}
			else
			{
				background_path_next += QString::number(timer_picture_count + 1, 10);
			}
			background_path_next += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
			background_picture_next.load(background_path_next);//���ر���ͼƬ
			ui.label_chara_1->setGraphicsEffect(effect_1);//����ʹ��ԭʼͼƬ
			ui.label_chara_1->setPixmap(background_picture_back);
			ui.label_chara_2->setGraphicsEffect(effect_2);//ǰ��ʹ���л���ͼƬ
			ui.label_chara_2->setPixmap(background_picture_next);
			timer->start(timer_interval);//����͸�����л���ʱ��������������ʱ��
		}
		else
		{
			if (timer_transparent_count >= 1)//����һ���л�
			{
				timer_transparent_count = 0;
				timer_interval = DIALOG_LOCK_CHARA_PICTURE_COUNT_INTERVAL_NUMNER;
				if (timer_picture_count + 1 >= DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER + 1)//ͼƬ����������Χ
				{
					timer_picture_count = 1;
				}
				else
				{
					timer_picture_count += 1;
				}
				effect_1->setOpacity(1 - timer_transparent_count);
				effect_2->setOpacity(0);
				QPixmap background_picture;//����δ�л�ʱ�ı���ͼƬ
				QString background_path = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//��ʱ�洢ԭʼ����ͼƬ·��
				background_path += QString::number(timer_picture_count, 10);
				background_path += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
				background_picture.load(background_path);//���ر���ͼƬ
				ui.label_chara_1->setGraphicsEffect(effect_1);//����ʹ������ͼƬ
				ui.label_chara_1->setPixmap(background_picture);
				ui.label_chara_2->setGraphicsEffect(effect_2);//ǰ��ʹ��ȫ͸��ͼƬ
				ui.label_chara_2->setPixmap(QPixmap(DIALOG_BACKGROUND_CHARA_TRANSPARENT_PICTURE_PATH_STRING));
				timer->start(timer_interval);
			}
			else//͸����û�дﵽָ����С
			{
				timer_transparent_count += DIALOG_LOCK_CHARA_PICTURE_TRANSPARENT_COUNT_MEASURE_NUMNER;
				effect_1->setOpacity(1 - timer_transparent_count);
				effect_2->setOpacity(timer_transparent_count);
				QPixmap background_picture_back;//����ԭʼͼƬ
				QString background_path_back = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//��ʱ�洢ԭʼ����ͼƬ·��
				background_path_back += QString::number(timer_picture_count, 10);
				background_path_back += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
				background_picture_back.load(background_path_back);//����ͼƬ
				QPixmap background_picture_next;//�����л���ͼƬ
				QString background_path_next = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//��ʱ�洢�л��󱳾�ͼƬ·��
				if (timer_picture_count + 1 >= DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER + 1)//����ͼƬ˳���������Χ
				{
					background_path_next += QString::number(DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER, 10);
				}
				else
				{
					background_path_next += QString::number(timer_picture_count + 1, 10);
				}
				background_path_next += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
				background_picture_next.load(background_path_next);//���ر���ͼƬ
				ui.label_chara_1->setGraphicsEffect(effect_1);//����ʹ��ԭʼͼƬ
				ui.label_chara_1->setPixmap(background_picture_back);
				ui.label_chara_2->setGraphicsEffect(effect_2);//ǰ��ʹ���л���ͼƬ
				ui.label_chara_2->setPixmap(background_picture_next);
				timer->start(timer_interval);
			}
		}
	}
}

