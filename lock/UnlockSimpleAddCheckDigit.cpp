#include "define.h"

namespace rem
{

	//ʹ�ñ�׼�����ռ�
	using std::string;
	using std::ifstream;
	using std::ofstream;
	using std::fstream;
	using std::ios_base;

	//��������������
	UnlockSimpleAddCheckDigit::UnlockSimpleAddCheckDigit(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����					
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�

		//����ͼƬ��Ϊ���ڱ���
		main_picture.load(DIALOG_BACKGROUND_UNLOCK_SIMPLE_ADD_SET_DIGIT_PATH_STRING);
		resize(main_picture.size());//���ڴ�С��ΪͼƬ��С

		//���ؽ���
		ui.setupUi(this);

		//�źź���
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//ȷ�ϰ�ť

		//���ð�ť��ʽ
		ui.pushButton_apply->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_10.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_10.png);}");

		//����������ɫ
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::WindowText, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::Highlight, QColor(128, 76, 71, 64));
		ui.listWidget_1->setPalette(text_palette);

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�

		//���ÿؼ�����
		extern QString font_str;//��ΪlistWidget_1�ڲ��Ŀؼ������޷�ʹ��Ĭ���������ã���˱��뵥�����á�ע����Ϊû�������ռ�Ĺ�ϵ�������main�������涨���ȫ�ֱ������ܺ�find_dialog_mutexһ����������ж��壬����ᱻ����һ���¶����ȫ�ֱ���rem::font_str
		if (font_str != "")
		{
			QFont file_font(font_str, FILE_FONT_DEFAULT_SIZE);//����Ĭ������
			ui.listWidget_1->setFont(file_font);
		}
		else//����ʧ�ܣ�ʹ������趨�õ�Ĭ������
		{

		}
	}
	UnlockSimpleAddCheckDigit::~UnlockSimpleAddCheckDigit()
	{
		
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void UnlockSimpleAddCheckDigit::mousePressEvent(QMouseEvent *event)
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
	void UnlockSimpleAddCheckDigit::mouseMoveEvent(QMouseEvent *event)
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
	void UnlockSimpleAddCheckDigit::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void UnlockSimpleAddCheckDigit::keyPressEvent(QKeyEvent *event)
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

	void UnlockSimpleAddCheckDigit::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//��ͼ��Ϊ���ڱ���
	}

	//���ó�Ա����
	void UnlockSimpleAddCheckDigit::set_information(int *extra_int_information)//������Ҫ��ʾ�ļӼ�����
	{
		for (int index = 0; index < extra_int_information[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER]; index++)//�������Ԫ�Ӽ�����
		{
			QString transform_result = QString::number((extra_int_information[index]), 10);
			if (transform_result != "")
			{
				ui.listWidget_1->addItem(transform_result);//������Ŀ��ӽ�listwidget
			}
			else
			{
				ui.listWidget_1->addItem(DIALOG_LOCK_SIMPLE_ADD_DEFAULT_UNIT_INSERT_STRING);
			}
		}
	}

	void UnlockSimpleAddCheckDigit::set_apply()//������Ч
	{
		close_window_include_animation();//�رմ���
	}

	void UnlockSimpleAddCheckDigit::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

