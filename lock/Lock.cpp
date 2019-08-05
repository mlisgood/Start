#include "define.h"

namespace rem
{

	//�������������
	Lock::Lock(QWidget *parent) : QMainWindow(parent)
	{
		randnumber = WINDOW_RANDOM_MIN_NUMBER + rand() % (WINDOW_RANDOM_MAX_NUMBER - WINDOW_RANDOM_MIN_NUMBER + 1);//����ָ������������ڹ��캯����ʹ��һ�Σ��Ա�֤����������ز��򿪴��ں󱳾���Ϊ���»�ͼ�����仯������
		setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);//ȥ�����ڱ��������Ҵ��ڿ���ͨ������������Ŵ���С
		resize(WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_HEIGHT_NUMBER);//������ǿ�Ƹ�Ϊ�˴�С
		setFixedSize(this->width(), this->height());//��ֹ�ı䴰�ڴ�С
		setAttribute(Qt::WA_QuitOnClose, true);//�ô���Ϊ�����ڣ��ر�ʱֱ���˳�����

		ui.setupUi(this);

		//��ť����
		ui.pushButton_select_1->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_normal_1.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_pressed_1.png);}");
		ui.pushButton_select_2->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_normal_2.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_pressed_2.png);}");
		ui.pushButton_select_3->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_normal_3.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/botton_main_pressed_3.png);}");

		//�źź���
		connect(ui.pushButton_select_1, SIGNAL(clicked()), this, SLOT(normal_lock_dialog()));//�����ļ�����
		connect(ui.pushButton_select_2, SIGNAL(clicked()), this, SLOT(simple_lock_dialog()));//�����ļ�����
		connect(ui.pushButton_select_3, SIGNAL(clicked()), this, SLOT(help_information()));//������Ϣ
		connect(ui.pushButton_set, SIGNAL(clicked()), this, SLOT(set_dialog()));//���ô���
		connect(ui.pushButton_close_window, SIGNAL(clicked()), this, SLOT(close_dialog()));//�رմ��ڰ�ť

		//������������Ч��
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}

	Lock::~Lock()
	{

	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	void Lock::mousePressEvent(QMouseEvent *event)//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
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

	void Lock::mouseMoveEvent(QMouseEvent *event)//�������������£����ƶ�����λ��
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}
	}

	void Lock::mouseReleaseEvent(QMouseEvent *event)//���δ�����£�����Ӧ����Ϊfalse
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	void Lock::paintEvent(QPaintEvent *)//���Ʊ���ͼ��
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
	void Lock::close_dialog()
	{
		close_window_include_animation();
	}

	void Lock::normal_lock_dialog()//�������
	{
		hide_window_include_animation();//���ش���
		LockNormal *dialog = new LockNormal();//����ʹ�ô˷����������ڣ�����connect�����޷�ʹ��
		connect(dialog, SIGNAL(show_mainwindow()), this, SLOT(show_window_include_animation()));
		dialog->show();
	}

	void Lock::simple_lock_dialog()//�򵥼���
	{
		hide_window_include_animation();//���ش���
		LockSimple *dialog = new LockSimple();//����ʹ�ô˷����������ڣ�����connect�����޷�ʹ��
		connect(dialog, SIGNAL(show_mainwindow()), this, SLOT(show_window_include_animation()));//���Ӻ�������ΪҪͬʱ����������Ӵ��ڵĵ�ַ������ڴ˴�ʹ��
		dialog->show();//������Ҫ�漰��������ʾ�Ĵ�����ò�ʹ��ģ̬���ڣ���������һϵ������
	}

	void Lock::set_dialog()//���ô���
	{
		Set dialog;
		dialog.exec();
	}

	void Lock::help_information()//������Ϣ
	{
		Help dialog;//��ʾ������Ϣ
		dialog.set_dialog_information_path(DIALOG_INFORMATION_HELP_PATH_STRING);
		dialog.exec();
	}

	void Lock::hide_window_include_animation()//�������ش��ڶ��������ش��ڷ���
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

	void Lock::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

	void Lock::show_window_include_animation()//������ʾ���ڶ�������ʾ���ڷ���
	{
		show();//��������ʾ�����ٲ��Ŷ���
		QPropertyAnimation *animation_show = new QPropertyAnimation(this, "windowOpacity");
		animation_show->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//������ʾ����Ч��
		animation_show->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_show->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation_show->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		connect(animation_show, SIGNAL(finished()), this, SLOT(show_window_include_animation_end()));
	}

	void Lock::show_window_include_animation_end()//������ʾ����������
	{

		//�������а�ť�������ڶ���������֮��ʹ�ã�����Ҳ����ֲ��ϵ����ذ�ťʱ�����������ŵ����
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(true);
		}
	}
}

