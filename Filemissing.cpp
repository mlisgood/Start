#include "define.h"

namespace rem
{

	//��������������
	Filemissing::Filemissing(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		totalrandomnumber = DIALOG_RANDOM_MIN_NUMBER + rand() % (DIALOG_RANDOM_MAX_NUMBER - DIALOG_RANDOM_MIN_NUMBER + 1);//����ָ��������Ա��������ͼƬ������ͼƬ��ʽ
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		resize(DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER);//������ǿ�Ƹ�Ϊ�˴�С
		setFixedSize(this->width(), this->height());//��ֹ�ı䴰�ڴ�С
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����

		//ͼƬ·��
		//����ͼƬ·��
		filepath = DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING + QString::number(totalrandomnumber, 10);
		filepath += DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING;

		//���ͼƬ·��
		chara_path = DIALOG_CHARA_PICTURE_PATH_FRONT_STRING;
		QString chara_path_number = QString::number(totalrandomnumber, 10);//�������ת��Ϊ·���е�һ����
		chara_path += chara_path_number;
		chara_path += DIALOG_CHARA_PICTURE_PATH_BREAK_STRING;
		chara_path += QString::number(DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER + rand() % (DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER - DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER + 1), 10);//�ӵ�ǰϵ�е�3��ͼƬ����ѡȡһ�Ų����ӵ�·����
		chara_path += DIALOG_CHARA_PICTURE_PATH_BACK_STRING;

		//���ؽ��棬�����������Ա�����汻֮��Ļ�ͼ����
		ui.setupUi(this);

		//���ذ�ť��ʽ
		ui.pushButton_close_dialog->setStyleSheet("QPushButton{border-image: url(:/icon/item/picture_start/icon/dialog_main_exit_normal.png);}""QPushButton:hover{border-image: url(:/icon/item/picture_start/icon/dialog_main_exit_pressed.png);}""QPushButton:pressed{border-image: url(:/icon/item/picture/icon/dialog_main_exit_pressed.png;}");
	
		//�رհ�ť
		connect(ui.pushButton_close_window, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));
		connect(ui.pushButton_close_dialog, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));

		//������������Ч��
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}

	Filemissing::~Filemissing()
	{

	}

	//���ó�Ա����
	void Filemissing::set_dialog_information_status(int dialog_information_status)
	{
		information_status = dialog_information_status;
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void Filemissing::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bPressed = true;
			m_point = event->pos();
		}
	}
	//�������������£����ƶ�����λ��
	void Filemissing::mouseMoveEvent(QMouseEvent *event)
	{
		if (m_bPressed)
			move(event->pos() - m_point + pos());
	}

	//���δ�����£�����Ӧ����Ϊfalse
	void Filemissing::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	void Filemissing::paintEvent(QPaintEvent *)
	{

		//���ƴ����õ���ͼƬ�����巽��������ָ��5�ֱ������֮���5���������ѡȡһ����ӳ�䵽����һ�ַ�����档�����Ƕ�Ӧ��ӳ���ϵ��[1,5]->��������[6,10]->���Σ�[11,15]->�ꥼ��[16,20]->�����,[21,25]->ǧҹ�����⣬֮�������ͼƬҲ�͹�������ʹ�õ�������йء�ÿ��������Ӧ3��ͼƬ��ÿ�����ѡȡ1�š�
		//���¹����õ��˳�������Ҫ�޸������д
		//����ͼƬ
		QPainter background_painter(this);//����
		QPainter margin_painter(this);//�߿�
		QPainter chara_painter(this);//����
		QPainter information_painter(this);//����
		QPixmap background_picture;
		QPixmap margin_picture;
		QPixmap chara_picture;
		QPixmap information_picture;
		if (information_status == DIALOG_INFORMATION_STATUS_1_FLAG)//�ڴ治��
		{
			information_path = DIALOG_INFORMATION_1_PICTURE_PATH_STRING;
		}
		else if(information_status == DIALOG_INFORMATION_STATUS_2_FLAG)//�޷����ļ�
		{
			information_path = DIALOG_INFORMATION_2_PICTURE_PATH_STRING;
		}
		else if (information_status == DIALOG_INFORMATION_STATUS_3_FLAG)//����������ͬ����
		{
			information_path = DIALOG_INFORMATION_3_PICTURE_PATH_STRING;
		}
		else
		{

		}
		information_path += QString::number(totalrandomnumber, 10);//�������ת��Ϊ·���е�һ����
		information_path += DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING;
		background_picture.load(filepath);
		margin_picture.load((QString)DIALOG_MARGIN_PICTURE_PATH_STRING);
		chara_picture.load(chara_path);
		information_picture.load(information_path);
		background_painter.drawPixmap(0, 0, DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, background_picture);
		chara_painter.drawPixmap(0, 0, DIALOG_SIZE_HEIGHT_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, chara_picture);//���ͼƬʹ�������Σ����Ϳ��봰�ڿ��һ��
		information_painter.drawPixmap(DIALOG_SIZE_HEIGHT_NUMBER, 0, DIALOG_SIZE_WIDTH_NUMBER - DIALOG_SIZE_HEIGHT_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, information_picture);//���ֲ���Ӧ�ô���ߵ�ͼƬ���ֵ��ұ�Ե��ʼ
		margin_painter.drawPixmap(0, 0, DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, margin_picture);//�����ʾ���ⱻͼƬ����
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ������������Ϊֻ��ȷ�ϲ�������������Ҫ��д����Ϊ�˱���ͳһ�����ǽ�������д
	void Filemissing::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Enter)
		{

		}
		else if (event->key() == Qt::Key_Escape)
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
		else
		{

		}
	}

	void Filemissing::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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
}

