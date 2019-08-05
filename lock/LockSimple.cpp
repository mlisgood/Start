#include "define.h"

namespace rem
{

	//�������������
	LockSimple::LockSimple(QWidget *parent) : QDialog(parent)
	{
		randnumber = WINDOW_RANDOM_MIN_NUMBER + rand() % (WINDOW_RANDOM_MAX_NUMBER - WINDOW_RANDOM_MIN_NUMBER + 1);//����ָ������������ڹ��캯����ʹ��һ�Σ��Ա�֤����������ز��򿪴��ں󱳾���Ϊ���»�ͼ�����仯������
		setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);//ȥ�����ڱ��������Ҵ��ڿ���ͨ������������Ŵ���С
		resize(WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_HEIGHT_NUMBER);//������ǿ�Ƹ�Ϊ�˴�С
		setFixedSize(this->width(), this->height());//��ֹ�ı䴰�ڴ�С
		setAttribute(Qt::WA_QuitOnClose, true);//�ô��ڹر�ʱ���˳�����
		is_escape_pressed = false;//������esc���˳�����

		ui.setupUi(this);

		//��ť����
		ui.pushButton_select_1->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_normal_1.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_pressed_1.png);}");
		ui.pushButton_select_2->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_normal_2.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_pressed_2.png);}");
		ui.pushButton_select_3->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_normal_3.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/botton_simple_lock_pressed_3.png);}");

		//�źź���
		connect(ui.pushButton_select_1, SIGNAL(clicked()), this, SLOT(method_1_dialog()));//ȡ�����ܴ���
		connect(ui.pushButton_select_2, SIGNAL(clicked()), this, SLOT(method_2_dialog()));//�Ӽ����ܴ���
		connect(ui.pushButton_select_3, SIGNAL(clicked()), this, SLOT(close_dialog()));//����������

		//�˳�ʱ���ٸô��������ڴ�й©
		setAttribute(Qt::WA_DeleteOnClose);

		//������������Ч��
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}

	LockSimple::~LockSimple()
	{
		
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	void LockSimple::mousePressEvent(QMouseEvent *event)//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
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

	void LockSimple::mouseMoveEvent(QMouseEvent *event)//�������������£����ƶ�����λ��
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}
	}

	void LockSimple::mouseReleaseEvent(QMouseEvent *event)//���δ�����£�����Ӧ����Ϊfalse
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void LockSimple::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Enter)
		{

		}
		else if (event->key() == Qt::Key_Escape)
		{
			if (!is_escape_pressed)//��ִ��һ�ΰ���esc�˳�
			{
				is_escape_pressed = true;
				close_window_include_animation_and_show_mainwindow();
			}
			else
			{

			}
		}
		else
		{

		}
	}

	void LockSimple::paintEvent(QPaintEvent *)//���Ʊ���ͼ��
	{
		QPainter background_painter(this);//����
		QPainter background_margin_painter(this);//�߿�
		QPixmap background_picture;//����ͼƬ
		QPixmap background_margin_picture;//�߿�ͼƬ
		QString background_path = WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING;//��ʱ�洢����ͼƬ·��
		background_path += QString::number(randnumber, 10);
		background_path += WINDOW_BACKGROUND_PICTURE_PATH_BACK_STRING;
		background_picture.load(background_path);//���ر���ͼƬ
		background_margin_picture.load(WINDOW_BACKGROUND_MARGIN_PICTURE_PATH_STRING);//���ر߿�ͼƬ
		background_painter.drawPixmap(0, 0, WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_WIDTH_NUMBER, background_picture);//���Ʊ���ͼƬ
		background_painter.drawPixmap(0, 0, WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_WIDTH_NUMBER, background_margin_picture);//���Ʊ߿�ͼƬ
	}

	//�ۺ���
	void LockSimple::close_dialog()
	{
		close_window_include_animation_and_show_mainwindow();//�رմ��ڲ���ʾ������
	}

	void LockSimple::method_1_dialog()
	{
		hide_window_include_animation();//���ش��ڡ���Ϊ�������������������ģ�����ֱ�ӹرմ��ڣ����������´򿪵Ĵ��ڱ�����
		LockSimpleOpposite *dialog = new LockSimpleOpposite();//����ʹ�ô˷����������ڣ�����connect�����޷�ʹ��
		connect(dialog, SIGNAL(show_lock_simple_window()), this, SLOT(show_window_include_animation()));//���Ӻ�������ΪҪͬʱ����������Ӵ��ڵĵ�ַ������ڴ˴�ʹ��
		dialog->show();//������Ϊ���漰��������ʾ����ʹ��ģ̬���ڣ���Ϊ����һ����ʹ�÷�ģ̬����
	}

	void LockSimple::method_2_dialog()
	{
		hide_window_include_animation();//���ش��ڡ���Ϊ�������������������ģ�����ֱ�ӹرմ��ڣ����������´򿪵Ĵ��ڱ�����
		LockSimpleAdd *dialog = new LockSimpleAdd();//����ʹ�ô˷����������ڣ�����connect�����޷�ʹ��
		connect(dialog, SIGNAL(show_lock_simple_window()), this, SLOT(show_window_include_animation()));//���Ӻ�������ΪҪͬʱ����������Ӵ��ڵĵ�ַ������ڴ˴�ʹ��
		dialog->show();//������Ϊ���漰��������ʾ����ʹ��ģ̬���ڣ���Ϊ����һ����ʹ�÷�ģ̬����
	}

	void LockSimple::hide_window_include_animation()//�������ش��ڶ��������ش��ڷ���
	{

		//�������а�ť�����򶯻��������ǰ�ٴε����ť�����´�������
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(false);
		}
		QPropertyAnimation *animation_hide = new QPropertyAnimation(this, "windowOpacity");
		animation_hide->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//�������ض���Ч��
		animation_hide->setStartValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation_hide->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_hide->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		connect(animation_hide, SIGNAL(finished()), this, SLOT(hide()));
	}

	void LockSimple::close_window_include_animation_and_show_mainwindow()//�����رմ��ڶ����Ĺرմ�����ʾ�����ڷ���
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
		emit show_mainwindow();//������ʾ�������ź�
		connect(animation_close, SIGNAL(finished()), this, SLOT(close()));
	}

	void LockSimple::show_window_include_animation()//������ʾ���ڶ�������ʾ���ڷ���
	{
		show();//��������ʾ�����ٲ��Ŷ���
		QPropertyAnimation *animation_show = new QPropertyAnimation(this, "windowOpacity");
		animation_show->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//������ʾ����Ч��
		animation_show->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_show->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation_show->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		connect(animation_show, SIGNAL(finished()), this, SLOT(show_window_include_animation_end()));
	}

	void LockSimple::show_window_include_animation_end()//������ʾ����������
	{

		//�������а�ť�������ڶ���������֮��ʹ�ã�����Ҳ����ֲ��ϵ����ذ�ťʱ�����������ŵ����
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(true);
		}
	}
}

