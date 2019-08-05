#include "define.h"

namespace rem
{

	//ʹ�ñ�׼�����ռ�
	using std::string;

	//����crypto++�����ռ�
	using namespace CryptoPP;

	//��������������
	LockNormalHashCalculate::LockNormalHashCalculate(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		resize(DIALOG_LOCK_SIZE_WIDTH_NUMBER, DIALOG_LOCK_SIZE_HEIGHT_NUMBER);//������ǿ�Ƹ�Ϊ�˴�С
		setFixedSize(this->width(), this->height());//��ֹ�ı䴰�ڴ�С
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		is_escape_pressed = false;//������esc���˳�����

		//��ʱ��
		timer_picture_count = DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER + rand() % (DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER - DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER + 1);//����ָ������������ڹ��캯����ʹ��һ�Σ��Ա�֤����������ز��򿪴��ں󱳾���Ϊ���»�ͼ�����仯������
		timer_transparent_count = 0;//ͼƬ��ʼ͸�����趨
		timer_interval = DIALOG_LOCK_CHARA_PICTURE_COUNT_INTERVAL_NUMNER;//��ʼͼƬ���ֲ����Ϊ��׼���л�ͼƬ���
		timer = new QTimer(this);//��ʼ����ʱ��
		timer->setTimerType(Qt::PreciseTimer);//�޸ľ���
		connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));//�źŴ���
		timer->start(timer_interval);

		//���ؽ��棬�����������Ա�����汻֮��Ļ�ͼ����
		ui.setupUi(this);

		//��ť
		ui.pushButton_1->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_19.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_19.png);}");
		ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_18.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_18.png);}");
		ui.pushButton_3->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_3.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_3.png);}");
		ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_20.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_20.png);}");

		//�źź���
		connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(file_explore()));//�����ļ�
		connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(calculate_file()));//�����ļ�
		connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//�����ϼ�����
		connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(check_file()));//������Կ
		connect(ui.comboBox_1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change_method(const QString &)));
		connect(ui.comboBox_2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change_type(const QString &)));

		//�˳�ʱ���ٸô��������ڴ�й©
		setAttribute(Qt::WA_DeleteOnClose);

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

		//����������ɫ
		QPalette global_text_palette;
		global_text_palette.setColor(QPalette::Text, QColor(70, 28, 10, 255));
		global_text_palette.setColor(QPalette::HighlightedText, QColor(70, 28, 10, 255));
		global_text_palette.setColor(QPalette::WindowText, QColor(70, 28, 10, 255));
		global_text_palette.setColor(QPalette::Highlight, QColor(70, 28, 10, 64));
		ui.comboBox_1->setPalette(global_text_palette);
		ui.comboBox_2->setPalette(global_text_palette);
		ui.lineEdit_1->setPalette(global_text_palette);
		ui.lineEdit_2->setPalette(global_text_palette);

		//�ı���ֻ�����������ֺ���ĸ
		QRegExp regexp("[a-fA-F0-9]+$");//������ʽ��ֻ��������ʮ����������������ַ�
		validator = new QRegExpValidator(regexp, ui.lineEdit_2);//������Ҫʹ�õ�ģʽ
		ui.lineEdit_2->setValidator(validator);//Ӧ��ģʽ

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
	}
	LockNormalHashCalculate::~LockNormalHashCalculate()
	{
		delete timer;
		delete effect_1;
		delete effect_2;
		delete validator;
	}

	//���ó�Ա����
	void LockNormalHashCalculate::set_method(QString method)//���ü��ܷ�ʽ������Ϊ���ܷ�ʽ
	{
		this->method = method;
		ui.comboBox_1->setCurrentText(method);//�����������еļ��ܷ���
		combobox_change_type(DIALOG_HASH_CALCULATOR_TYPE_STRING);
		if (method == tr("MD4"))
		{
			ui.comboBox_2->setEnabled(false);
			ui.lineEdit_2->setMaxLength(MD4::DIGESTSIZE * 2);
		}
		else if (method == tr("MD5"))
		{
			ui.comboBox_2->setEnabled(false);
			ui.lineEdit_2->setMaxLength(MD5::DIGESTSIZE * 2);
		}
		else if (method == tr("SHA-1"))
		{
			ui.comboBox_2->setEnabled(false);
			ui.lineEdit_2->setMaxLength(SHA1::DIGESTSIZE * 2);
		}
		else if (method == tr("SHA-2"))
		{
			ui.comboBox_2->setEnabled(true);
			ui.lineEdit_2->setMaxLength(SHA224::DIGESTSIZE * 2);
		}
		else if (method == tr("SHA-3"))
		{
			ui.comboBox_2->setEnabled(true);
			ui.lineEdit_2->setMaxLength(SHA3_224::DIGESTSIZE * 2);
		}
		else if (method == tr("Keccak"))
		{
			ui.comboBox_2->setEnabled(true);
			ui.lineEdit_2->setMaxLength(Keccak_224::DIGESTSIZE * 2);
		}
		else
		{
			ui.comboBox_2->setEnabled(false);
			ui.lineEdit_2->setMaxLength(MD4::DIGESTSIZE * 2);
		}
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void LockNormalHashCalculate::mousePressEvent(QMouseEvent *event)
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
	void LockNormalHashCalculate::mouseMoveEvent(QMouseEvent *event)
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
	void LockNormalHashCalculate::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ������������Ϊֻ��ȷ�ϲ�������������Ҫ��д����Ϊ�˱���ͳһ�����ǽ�������д
	void LockNormalHashCalculate::keyPressEvent(QKeyEvent *event)
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

	void LockNormalHashCalculate::timer_timeout()//ʹ��2��label��������ͼƬ������ָ��һ����ʱ����������ʾͼƬ����ʱͼƬ���²�label���ϲ�labelʹ��ȫ͸��ͼƬ����������ԡ�ʱ�䵽�ں󣬸����л�ͼƬ͸������ʹ�õĶ�ʱ������ͬʱ��ʼ�޸�͸���ȼ������²�label��ʾԭʼͼƬ����͸�����𽥼�С���ϲ�label��ʾ�л���ͼƬ����͸���������ӡ����ϲ�labelͼƬ͸����Ϊ1ʱ���л�������ͼƬ��������1�����µĳ�ʱ�������¿�ʼ��һ��ʱѭ��
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

	void LockNormalHashCalculate::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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
		emit show_lock_normal_window();//������ʾ�ϼ������ź�
		connect(animation_close, SIGNAL(finished()), this, SLOT(close()));
	}

	void LockNormalHashCalculate::combobox_change_method(const QString &combobox_string)//���ü��ܷ�ʽ������Ϊ���ܷ�ʽ
	{
		if (combobox_string == tr("MD4"))
		{
			ui.comboBox_2->setEnabled(false);
			method = tr("MD4");
			ui.lineEdit_2->setMaxLength(MD4::DIGESTSIZE * 2);
		}
		else if (combobox_string == tr("MD5"))
		{
			ui.comboBox_2->setEnabled(false);
			method = tr("MD5");
			ui.lineEdit_2->setMaxLength(MD5::DIGESTSIZE * 2);
		}
		else if (combobox_string == tr("SHA-1"))
		{
			ui.comboBox_2->setEnabled(false);
			method = tr("SHA-1");
			ui.lineEdit_2->setMaxLength(SHA1::DIGESTSIZE * 2);
		}
		else if (combobox_string == tr("SHA-2"))
		{
			ui.comboBox_2->setEnabled(true);
			method = tr("SHA-2");
			if (ui.comboBox_2->currentText() == tr("224"))
			{
				ui.lineEdit_2->setMaxLength(SHA224::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("256"))
			{
				ui.lineEdit_2->setMaxLength(SHA256::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("384"))
			{
				ui.lineEdit_2->setMaxLength(SHA384::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("512"))
			{
				ui.lineEdit_2->setMaxLength(SHA512::DIGESTSIZE * 2);
			}
			else
			{
				ui.lineEdit_2->setMaxLength(SHA224::DIGESTSIZE * 2);
			}
		}
		else if (combobox_string == tr("SHA-3"))
		{
			ui.comboBox_2->setEnabled(true);
			method = tr("SHA-3");
			if (ui.comboBox_2->currentText() == tr("224"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_224::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("256"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_256::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("384"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_384::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("512"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_512::DIGESTSIZE * 2);
			}
			else
			{
				ui.lineEdit_2->setMaxLength(SHA3_224::DIGESTSIZE * 2);
			}
		}
		else if (combobox_string == tr("Keccak"))
		{
			ui.comboBox_2->setEnabled(true);
			method = tr("Keccak");
			if (ui.comboBox_2->currentText() == tr("224"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_224::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("256"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_256::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("384"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_384::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("512"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_512::DIGESTSIZE * 2);
			}
			else
			{
				ui.lineEdit_2->setMaxLength(Keccak_224::DIGESTSIZE * 2);
			}
		}
		else
		{
			ui.comboBox_2->setEnabled(false);
			method = tr("MD4");
			ui.lineEdit_2->setMaxLength(MD4::DIGESTSIZE * 2);
		}
	}

	void LockNormalHashCalculate::combobox_change_type(const QString &combobox_string)//��Ͽ����ݸ��ĺ���
	{
		calculate_type = combobox_string;
		if (method == tr("SHA-2"))
		{
			if (calculate_type == tr("224"))
			{
				ui.lineEdit_2->setMaxLength(SHA224::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("256"))
			{
				ui.lineEdit_2->setMaxLength(SHA256::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("384"))
			{
				ui.lineEdit_2->setMaxLength(SHA384::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("512"))
			{
				ui.lineEdit_2->setMaxLength(SHA512::DIGESTSIZE * 2);
			}
			else
			{
				ui.lineEdit_2->setMaxLength(SHA224::DIGESTSIZE * 2);
			}
		}
		else if (method == tr("SHA-3"))
		{
			if (calculate_type == tr("224"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_224::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("256"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_256::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("384"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_384::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("512"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_512::DIGESTSIZE * 2);
			}
			else
			{
				ui.lineEdit_2->setMaxLength(SHA3_224::DIGESTSIZE * 2);
			}
		}
		else if (method == tr("Keccak"))
		{
			if (calculate_type == tr("224"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_224::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("256"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_256::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("384"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_384::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("512"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_512::DIGESTSIZE * 2);
			}
			else
			{
				ui.lineEdit_2->setMaxLength(Keccak_224::DIGESTSIZE * 2);
			}
		}
		else
		{
			if (calculate_type == tr("224"))
			{
				ui.lineEdit_2->setMaxLength(SHA224::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("256"))
			{
				ui.lineEdit_2->setMaxLength(SHA256::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("384"))
			{
				ui.lineEdit_2->setMaxLength(SHA384::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("512"))
			{
				ui.lineEdit_2->setMaxLength(SHA512::DIGESTSIZE * 2);
			}
			else
			{
				ui.lineEdit_2->setMaxLength(SHA224::DIGESTSIZE * 2);
			}
		}
	}

	void LockNormalHashCalculate::calculate_file()//����ɢ��ֵ
	{

		//��ȡ�����ļ���Ϣ
		QSettings *begin_read = new QSettings(FILE_SET_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		QString information_temp[2];//��ʱ��Ŷ�ȡ���
		information_temp[0] = begin_read->value(FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING).toString();
		if (information_temp[0].length() == 0)
		{
			information_temp[0] = FILE_SETTING_CATALOG_PATH_DEFAULT_STRING;
		}
		else
		{

		}
		information_temp[1] = begin_read->value(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING).toString();//����ֵ
		if (information_temp[1] == "0")//�Ƿ������ʷ�ļ�
		{
			bool_array[0] = false;
		}
		else
		{
			bool_array[0] = true;
		}
		if (information_temp[0] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
		{
			information_temp[0] = FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING;
		}
		else
		{

		}
		delete begin_read;
		string_array[2] = string((const char *)(information_temp[0] + FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING).toLocal8Bit());//��ʷ�ļ���벿��·��
		HashCalculate_file_thread *thread = new HashCalculate_file_thread();//�����ļ����߳�
		connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
		connect(this, SIGNAL(send_data(string*, bool*, char*, QString, QString)), thread, SLOT(get_data(string*, bool*, char*, QString, QString)));
		connect(this, SIGNAL(send_target_class_point(Export_HashCalculate_virtual_class *)), thread, SLOT(get_target_class_point(Export_HashCalculate_virtual_class *)));
		connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
		emit send_data(string_array, bool_array, result, calculate_type, method);//��������
		using export_class = Export_HashCalculate_virtual_class * (*)(void);//����ָ�򵼳�������ָ������
		HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//��̬����dll�����ҵ���ָ������Ķ���ָ�룬ͨ���źŴ��ݸ����߳�ʹ��
		if (dll_name != NULL)
		{
			emit send_dll_name(dll_name);//��Ϊ�����߳�ʹ����dll֮ǰ����ж��dll����ֻ��ͨ���źŽ�dll�����ݸ����߳�
			export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_hash_calculate");//ͨ������ָ���ĵ���������������Ҫ����
			if (get_class != NULL)
			{
				Export_HashCalculate_virtual_class *target_class_object = get_class();//���Ŀ����Ķ���ָ��
				emit send_target_class_point(target_class_object);//����dll���������ָ��
				QString file_path = ui.lineEdit_1->text();//����ļ�·���Ϸ���
				QFileInfo file_information(file_path);//��ȡ�ļ���Ϣ
				if (file_information.isFile())//���ļ�����
				{
					ui.lineEdit_1->setText(file_path);
					string_array[0] = string((const char *)file_path.toLocal8Bit());//�ļ�·��
					string_array[1] = string((const char *)(file_information.fileName()).toLocal8Bit());//�ļ���
					if (method == tr("MD4"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_MD4_final(int)), this, SLOT(receive_hash_calculate_final(int)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					}
					else if (method == tr("MD5"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_MD5_final(int)), this, SLOT(receive_hash_calculate_final(int)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					}
					else if (method == tr("SHA-1"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_SHA1_final(int)), this, SLOT(receive_hash_calculate_final(int)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					}
					else if (method == tr("SHA-2"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_SHA2_final(int)), this, SLOT(receive_hash_calculate_final(int)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					}
					else if (method == tr("SHA-3"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_SHA3_final(int)), this, SLOT(receive_hash_calculate_final(int)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					}
					else if (method == tr("Keccak"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_Keccak_final(int)), this, SLOT(receive_hash_calculate_final(int)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					}
					else
					{
						connect(target_class_object, SIGNAL(hash_calculate_MD4_final(int)), this, SLOT(receive_hash_calculate_final(int)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					}
					thread->start();//��ʼ���߳�
				}
				else
				{
					Help dialog;//��ʾ������Ϣ
					dialog.set_dialog_information_path(DIALOG_INFORMATION_KEYFILE_CANNOT_OPEN_PATH_STRING);
					dialog.setWindowTitle(tr("���ļ�ʧ�ܣ�"));
					dialog.exec();
				}
			}
			else
			{

			}
		}
		else
		{

		}
	}

	void LockNormalHashCalculate::check_file()//У���ļ�
	{
		//��ȡ�����ļ���Ϣ
		QSettings *begin_read = new QSettings(FILE_SET_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		QString information_temp[2];//��ʱ��Ŷ�ȡ���
		information_temp[0] = begin_read->value(FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING).toString();
		if (information_temp[0].length() == 0)
		{
			information_temp[0] = FILE_SETTING_CATALOG_PATH_DEFAULT_STRING;
		}
		else
		{

		}
		information_temp[1] = begin_read->value(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING).toString();//����ֵ
		if (information_temp[1] == "0")//�Ƿ������ʷ�ļ�
		{
			bool_array[0] = false;
		}
		else
		{
			bool_array[0] = true;
		}
		if (information_temp[1] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
		{
			information_temp[1] = FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING;
		}
		else
		{

		}
		delete begin_read;
		string_array[2] = string((const char *)(information_temp[0] + FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING).toLocal8Bit());//��ʷ�ļ���벿��·��
		HashCalculate_file_thread *thread = new HashCalculate_file_thread();//�����ļ����߳�
		connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
		connect(this, SIGNAL(send_data(string*, bool*, char*, QString, QString)), thread, SLOT(get_data(string*, bool*, char*, QString, QString)));
		connect(this, SIGNAL(send_target_class_point(Export_HashCalculate_virtual_class *)), thread, SLOT(get_target_class_point(Export_HashCalculate_virtual_class *)));
		connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
		emit send_data(string_array, bool_array, result, calculate_type, method);//��������
		using export_class = Export_HashCalculate_virtual_class * (*)(void);//����ָ�򵼳�������ָ������
		HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//��̬����dll�����ҵ���ָ������Ķ���ָ�룬ͨ���źŴ��ݸ����߳�ʹ��
		if (dll_name != NULL)
		{
			emit send_dll_name(dll_name);//��Ϊ�����߳�ʹ����dll֮ǰ����ж��dll����ֻ��ͨ���źŽ�dll�����ݸ����߳�
			export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_hash_calculate");//ͨ������ָ���ĵ���������������Ҫ����
			if (get_class != NULL)
			{
				Export_HashCalculate_virtual_class *target_class_object = get_class();//���Ŀ����Ķ���ָ��
				emit send_target_class_point(target_class_object);//����dll���������ָ��
				QString file_path = ui.lineEdit_1->text();//����ļ�·���Ϸ���
				QFileInfo file_information(file_path);//��ȡ�ļ���Ϣ
				if (file_information.isFile())//���ļ�����
				{
					ui.lineEdit_1->setText(file_path);
					string_array[0] = string((const char *)file_path.toLocal8Bit());//�ļ�·��
					string_array[1] = string((const char *)(file_information.fileName()).toLocal8Bit());//�ļ���
					if (method == tr("MD4"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_MD4_final(int)), this, SLOT(receive_hash_calculate_final_check(int)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					}
					else if (method == tr("MD5"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_MD5_final(int)), this, SLOT(receive_hash_calculate_final_check(int)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					}
					else if (method == tr("SHA-1"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_SHA1_final(int)), this, SLOT(receive_hash_calculate_final_check(int)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					}
					else if (method == tr("SHA-2"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_SHA2_final(int)), this, SLOT(receive_hash_calculate_final_check(int)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					}
					else if (method == tr("SHA-3"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_SHA3_final(int)), this, SLOT(receive_hash_calculate_final_check(int)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					}
					else if (method == tr("Keccak"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_Keccak_final(int)), this, SLOT(receive_hash_calculate_final_check(int)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					}
					else
					{
						connect(target_class_object, SIGNAL(hash_calculate_MD4_final(int)), this, SLOT(receive_hash_calculate_final_check(int)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					}
					thread->start();//��ʼ���߳�
				}
				else
				{
					Help dialog;//��ʾ������Ϣ
					dialog.set_dialog_information_path(DIALOG_INFORMATION_KEYFILE_CANNOT_OPEN_PATH_STRING);
					dialog.setWindowTitle(tr("���ļ�ʧ�ܣ�"));
					dialog.exec();
				}
			}
			else
			{

			}
		}
		else
		{

		}
	}

	void LockNormalHashCalculate::file_explore()
	{
		File dialog;//��������Ǵ�Notepad.exeֱ�����õģ�û�н����κ��޸ģ����File��ĵ��÷�ʽ��Ƚ��鷳
		dialog.setWindowTitle(tr("ѡ���ļ�"));
		QString file_dialog_file_name = QDir::currentPath();//��ǰ·�������ڻ�ñ��򿪵��ļ�·��
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//ȷ���Ƿ���Ҫ�޸�·����ֻ�е��ȷ���Ż��޸�
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//�������ļ�·���ı���
		dialog.set_file_dialog_status_address(change_result_address);//�������Ƿ���Ҫ�޸�·���ı���
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//���빤��·��
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//��ȡ�ļ���Ϣ
		if (file_information.isFile() && *change_result_address)//���ļ�����
		{
			ui.lineEdit_1->setText(file_dialog_file_name);
			string_array[0] = string((const char *)file_dialog_file_name.toLocal8Bit());//�ļ�·��
			string_array[1] = string((const char *)(file_information.fileName()).toLocal8Bit());//�ļ���
		}
		else if (*change_result_address)
		{
			Help dialog;//��ʾ������Ϣ
			dialog.set_dialog_information_path(DIALOG_INFORMATION_KEYFILE_CANNOT_OPEN_PATH_STRING);
			dialog.setWindowTitle(tr("���ļ�ʧ�ܣ�"));
			dialog.exec();
		}
		else
		{

		}
	}

	void LockNormalHashCalculate::receive_hash_calculate_final(int length)//�������������Ϊ�������
	{
		QByteArray result_string(result, length);//�����ת��ΪQBytearray
		result_string.toUpper();
		ui.lineEdit_2->setText(ui.lineEdit_2->text().toUpper());
		ui.lineEdit_2->setText((QString)result_string);//��������ʾ����Ľ����ע��QByteArray����ֱ��ת����QString
	}

	void LockNormalHashCalculate::receive_hash_calculate_final_check(int length)//��������������бȶԡ�����Ϊ�������
	{
		QByteArray result_string(result, length);//�����ת��ΪQBytearray
		result_string.toUpper();
		ui.lineEdit_2->setText(ui.lineEdit_2->text().toUpper());
		int correct_length;//��ȷ����
		if (method == tr("MD4"))
		{
			correct_length = MD4::DIGESTSIZE * 2;
		}
		else if (method == tr("MD5"))
		{
			correct_length = MD5::DIGESTSIZE * 2;
		}
		else if (method == tr("SHA-1"))
		{
			correct_length = SHA1::DIGESTSIZE * 2;
		}
		else if (method == tr("SHA-2"))
		{
			if (ui.comboBox_2->currentText() == tr("224"))
			{
				correct_length=SHA224::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("256"))
			{
				correct_length=SHA256::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("384"))
			{
				correct_length = SHA384::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("512"))
			{
				correct_length = SHA512::DIGESTSIZE * 2;
			}
			else
			{
				correct_length = SHA224::DIGESTSIZE * 2;
			}
		}
		else if (method == tr("SHA-3"))
		{
			if (ui.comboBox_2->currentText() == tr("224"))
			{
				correct_length = SHA3_224::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("256"))
			{
				correct_length = SHA3_256::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("384"))
			{
				correct_length = SHA3_384::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("512"))
			{
				correct_length = SHA3_512::DIGESTSIZE * 2;
			}
			else
			{
				correct_length = SHA3_224::DIGESTSIZE * 2;
			}
		}
		else if (method == tr("Keccak"))
		{
			if (ui.comboBox_2->currentText() == tr("224"))
			{
				correct_length = Keccak_224::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("256"))
			{
				correct_length = Keccak_256::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("384"))
			{
				correct_length = Keccak_384::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("512"))
			{
				correct_length = Keccak_512::DIGESTSIZE * 2;
			}
			else
			{
				correct_length = Keccak_224::DIGESTSIZE * 2;
			}
		}
		else
		{
			correct_length = MD4::DIGESTSIZE * 2;
		}
		if (ui.lineEdit_2->text().length() != correct_length)
		{
			Help dialog;//��ʾ������Ϣ
			dialog.set_dialog_information_path(DIALOG_INFORMATION_HASH_CHECK_WRONG_HASH_STRING);
			dialog.setWindowTitle(tr("���˵������˵����"));
			dialog.exec();
		}
		else
		{
			if (ui.lineEdit_2->text() == (QString)result_string)//����ȶ�
			{
				Help dialog;//��ʾ������Ϣ
				dialog.set_dialog_information_path(DIALOG_INFORMATION_HASH_CHECK_CORRECT_STRING);
				dialog.setWindowTitle(tr("У��ɹ�����"));
				dialog.exec();
			}
			else
			{
				Help dialog;//��ʾ������Ϣ
				dialog.set_dialog_information_path(DIALOG_INFORMATION_HASH_CHECK_INCORRECT_STRING);
				dialog.setWindowTitle(tr("���˵������˵����"));
				dialog.exec();
			}
		}
	}

	//���߳�
	HashCalculate_file_thread::HashCalculate_file_thread()//���߳�
	{

	}

	HashCalculate_file_thread::~HashCalculate_file_thread()//���߳�
	{

	}

	void HashCalculate_file_thread::get_data(string *string_array, bool *bool_array, char *result, QString calculate_type, QString method)//��ȡȫ������
	{
		this->string_array[0] = string_array[0];//��ʷ�ļ�·��
		this->string_array[1] = string_array[1];//��Կ�ļ�·��
		this->string_array[2] = string_array[2];//��������Կ�ļ�·��
		this->bool_array[0] = bool_array[0];//�Ƿ������ʷ�ļ�
		this->method = method;//���ܷ���
		this->calculate_type = calculate_type;//���ܷ���
		this->result = result;//���
	}


	void HashCalculate_file_thread::run()//���߳�������
	{
		mutex.lock();
		if (method == tr("MD4"))//MD4
		{
			target_class_point->hash_calculate_MD4(string_array[0], string_array[1], result, bool_array[0], string_array[2]);
		}
		else if (method == tr("MD5"))//MD5
		{
			target_class_point->hash_calculate_MD5(string_array[0], string_array[1], result, bool_array[0], string_array[2]);
		}
		else if (method == tr("SHA-1"))//SHA-1
		{
			target_class_point->hash_calculate_SHA1(string_array[0], string_array[1], result, bool_array[0], string_array[2]);
		}
		else if (method == tr("SHA-2"))//SHA-2
		{
			target_class_point->hash_calculate_SHA2(string_array[0], string_array[1], result, bool_array[0], string_array[2], string((const char *)calculate_type.toLocal8Bit()));
		}
		else if (method == tr("SHA-3"))//SHA-3
		{
			target_class_point->hash_calculate_SHA3(string_array[0], string_array[1], result, bool_array[0], string_array[2], string((const char *)calculate_type.toLocal8Bit()));
		}
		else if (method == tr("Keccak"))//Keccak
		{
			target_class_point->hash_calculate_Keccak(string_array[0], string_array[1], result, bool_array[0], string_array[2], string((const char *)calculate_type.toLocal8Bit()));
		}
		else
		{
			target_class_point->hash_calculate_MD4(string_array[0], string_array[1], result, bool_array[0], string_array[2]);
		}
		FreeLibrary(dll_name);
		mutex.unlock();
		this->quit();//�˳����߳�
	}

	void HashCalculate_file_thread::get_target_class_point(Export_HashCalculate_virtual_class *point)//��ȡdll���������ָ��
	{
		this->target_class_point = point;
	}

	void HashCalculate_file_thread::get_dll_name(HINSTANCE dll_name)//��ȡdll��
	{
		this->dll_name = dll_name;
	}
}

