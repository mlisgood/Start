#include "define.h"

namespace rem
{

	//�������������
	LockNormal::LockNormal(QWidget *parent) : QDialog(parent)
	{
		randnumber = WINDOW_RANDOM_MIN_NUMBER + rand() % (WINDOW_RANDOM_MAX_NUMBER - WINDOW_RANDOM_MIN_NUMBER + 1);//����ָ������������ڹ��캯����ʹ��һ�Σ��Ա�֤����������ز��򿪴��ں󱳾���Ϊ���»�ͼ�����仯������
		setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);//ȥ�����ڱ��������Ҵ��ڿ���ͨ������������Ŵ���С
		resize(WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_HEIGHT_NUMBER);//������ǿ�Ƹ�Ϊ�˴�С
		setFixedSize(this->width(), this->height());//��ֹ�ı䴰�ڴ�С
		setAttribute(Qt::WA_QuitOnClose, true);//�ô��ڹر�ʱ���˳�����
		is_escape_pressed = false;//������esc���˳�����

		ui.setupUi(this);

		//����������ɫ
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::WindowText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::Highlight, QColor(70, 28, 10, 64));
		ui.comboBox_1->setPalette(text_palette);
		ui.textEdit->setPalette(text_palette);

		//��ť����
		ui.pushButton_select_1->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_10.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_10.png);}");
		ui.pushButton_select_2->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_11.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_11.png);}");

		//�źź���
		connect(ui.pushButton_select_1, SIGNAL(clicked()), this, SLOT(apply()));//ȡ�����ܴ���
		connect(ui.pushButton_select_2, SIGNAL(clicked()), this, SLOT(close_dialog()));//����������
		connect(ui.comboBox_1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change(const QString &)));

		//�˳�ʱ���ٸô��������ڴ�й©
		setAttribute(Qt::WA_DeleteOnClose);

		//������������Ч��
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�

		//ȥ�������Կؼ����Ҽ��˵�
		QList<QScrollBar *> scroll_bar = this->findChildren<QScrollBar *>();//�����޷��ó��淽ʽ���combobox�Ĺ����������ʹ�ø÷�����������ͬ���Ϳؼ������в���
		foreach(QScrollBar *scroll_bar_style_control, scroll_bar)
		{
			scroll_bar_style_control->setContextMenuPolicy(Qt::NoContextMenu);
		}

		//������Ͽ��ʼֵ
		ui.comboBox_1->setCurrentText(tr("DES"));
		ui.textEdit->setText(DIALOG_LOCK_NORMAL_DES_DESCRIPTION_STRING);
	}

	LockNormal::~LockNormal()
	{
		
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	void LockNormal::mousePressEvent(QMouseEvent *event)//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
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

	void LockNormal::mouseMoveEvent(QMouseEvent *event)//�������������£����ƶ�����λ��
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}
	}

	void LockNormal::mouseReleaseEvent(QMouseEvent *event)//���δ�����£�����Ӧ����Ϊfalse
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void LockNormal::keyPressEvent(QKeyEvent *event)
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

	void LockNormal::paintEvent(QPaintEvent *)//���Ʊ���ͼ��
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
	void LockNormal::close_dialog()
	{
		close_window_include_animation_and_show_mainwindow();//�رմ��ڲ���ʾ������
	}

	void LockNormal::apply()
	{
		hide_window_include_animation();//���ش��ڡ���Ϊ�������������������ģ�����ֱ�ӹرմ��ڣ����������´򿪵Ĵ��ڱ�����
		if (ui.comboBox_1->currentText() == tr("DES") || ui.comboBox_1->currentText() == tr("2-Key 3DES") || ui.comboBox_1->currentText() == tr("3-Key 3DES") || ui.comboBox_1->currentText() == tr("AES-128") || ui.comboBox_1->currentText() == tr("AES-192") || ui.comboBox_1->currentText() == tr("AES-256"))//�ԳƼ���
		{
			LockNormalSingleKey *dialog = new LockNormalSingleKey();//����ʹ�ô˷����������ڣ�����connect�����޷�ʹ��
			connect(dialog, SIGNAL(show_lock_normal_window()), this, SLOT(show_window_include_animation()));//���Ӻ�������ΪҪͬʱ����������Ӵ��ڵĵ�ַ������ڴ˴�ʹ��
			dialog->set_method(ui.comboBox_1->currentText());//������ܷ�ʽ
			dialog->show();//������Ϊ���漰��������ʾ����ʹ��ģ̬���ڣ���Ϊ����һ����ʹ�÷�ģ̬����
		}
		else if (ui.comboBox_1->currentText() == tr("RSA") || ui.comboBox_1->currentText() == tr("ECC"))//�ǶԳƼ���
		{
			LockNormalDoubleKey *dialog = new LockNormalDoubleKey();//����ʹ�ô˷����������ڣ�����connect�����޷�ʹ��
			connect(dialog, SIGNAL(show_lock_normal_window()), this, SLOT(show_window_include_animation()));//���Ӻ�������ΪҪͬʱ����������Ӵ��ڵĵ�ַ������ڴ˴�ʹ��
			dialog->set_method(ui.comboBox_1->currentText());//������ܷ�ʽ
			dialog->show();//������Ϊ���漰��������ʾ����ʹ��ģ̬���ڣ���Ϊ����һ����ʹ�÷�ģ̬����
		}
		else if (ui.comboBox_1->currentText() == tr("MD4") || ui.comboBox_1->currentText() == tr("MD5") || ui.comboBox_1->currentText() == tr("SHA-1") || ui.comboBox_1->currentText() == tr("SHA-2") || ui.comboBox_1->currentText() == tr("SHA-3") || ui.comboBox_1->currentText() == tr("Keccak"))//ɢ�к���
		{
			LockNormalHashCalculate *dialog = new LockNormalHashCalculate();//����ʹ�ô˷����������ڣ�����connect�����޷�ʹ��
			connect(dialog, SIGNAL(show_lock_normal_window()), this, SLOT(show_window_include_animation()));//���Ӻ�������ΪҪͬʱ����������Ӵ��ڵĵ�ַ������ڴ˴�ʹ��
			dialog->set_method(ui.comboBox_1->currentText());//������ܷ�ʽ
			dialog->show();//������Ϊ���漰��������ʾ����ʹ��ģ̬���ڣ���Ϊ����һ����ʹ�÷�ģ̬����
		}
		else
		{
			LockNormalSingleKey *dialog = new LockNormalSingleKey();//����ʹ�ô˷����������ڣ�����connect�����޷�ʹ��
			connect(dialog, SIGNAL(show_lock_normal_window()), this, SLOT(show_window_include_animation()));//���Ӻ�������ΪҪͬʱ����������Ӵ��ڵĵ�ַ������ڴ˴�ʹ��
			dialog->set_method(tr("DES"));//������ܷ�ʽ
			dialog->show();//������Ϊ���漰��������ʾ����ʹ��ģ̬���ڣ���Ϊ����һ����ʹ�÷�ģ̬����
		}
	}

	void LockNormal::combobox_change(const QString &combobox_string)//��Ͽ����ݸ��ĺ���
	{
		if (combobox_string == tr("DES"))
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_DES_DESCRIPTION_STRING);
		}
		else if(combobox_string == tr("2-Key 3DES"))
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_DES_EDE2_DESCRIPTION_STRING);
		}
		else if (combobox_string == tr("3-Key 3DES"))
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_DES_EDE3_DESCRIPTION_STRING);
		}
		else if (combobox_string == tr("AES-128"))
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_AES_MIN_DESCRIPTION_STRING);
		}
		else if (combobox_string == tr("AES-192"))
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_AES_MIDDLE_DESCRIPTION_STRING);
		}
		else if (combobox_string == tr("AES-256"))
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_AES_MAX_DESCRIPTION_STRING);
		}
		else if (combobox_string == tr("RSA"))
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_RSA_DESCRIPTION_STRING);
		}
		else if (combobox_string == tr("ECC"))
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_ECC_DESCRIPTION_STRING);
		}
		else if (combobox_string == tr("MD4"))
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_MD4_DESCRIPTION_STRING);
		}
		else if (combobox_string == tr("MD5"))
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_MD5_DESCRIPTION_STRING);
		}
		else if (combobox_string == tr("SHA-1"))
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_SHA1_DESCRIPTION_STRING);
		}
		else if (combobox_string == tr("SHA-2"))
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_SHA2_DESCRIPTION_STRING);
		}
		else if (combobox_string == tr("SHA-3"))
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_SHA3_DESCRIPTION_STRING);
		}
		else if (combobox_string == tr("Keccak"))
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_KECCAK_DESCRIPTION_STRING);
		}
		else
		{
			ui.textEdit->setText(DIALOG_LOCK_NORMAL_DES_DESCRIPTION_STRING);
		}
	}

	void LockNormal::hide_window_include_animation()//�������ش��ڶ��������ش��ڷ���
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

	void LockNormal::close_window_include_animation_and_show_mainwindow()//�����رմ��ڶ����Ĺرմ�����ʾ�����ڷ���
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

	void LockNormal::show_window_include_animation()//������ʾ���ڶ�������ʾ���ڷ���
	{
		show();//��������ʾ�����ٲ��Ŷ���
		QPropertyAnimation *animation_show = new QPropertyAnimation(this, "windowOpacity");
		animation_show->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//������ʾ����Ч��
		animation_show->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_show->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation_show->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		connect(animation_show, SIGNAL(finished()), this, SLOT(show_window_include_animation_end()));
	}

	void LockNormal::show_window_include_animation_end()//������ʾ����������
	{

		//�������а�ť�������ڶ���������֮��ʹ�ã�����Ҳ����ֲ��ϵ����ذ�ťʱ�����������ŵ����
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(true);
		}
	}
}

