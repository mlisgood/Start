#include "define.h"

namespace rem
{

	//ʹ�ñ�׼�����ռ�
	using std::string;

	//����crypto++�����ռ�
	using namespace CryptoPP;

	//��������������
	LockNormalSingleKey::LockNormalSingleKey(QWidget *parent) : QDialog(parent)
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
		ui.pushButton_1->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_1.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_1.png);}");
		ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_2.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_2.png);}");
		ui.pushButton_3->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_3.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_3.png);}");

		//�źź���
		connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(lock_file()));//�����ļ�
		connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(unlock_file()));//�����ļ�
		connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//�����ϼ�����
		connect(ui.comboBox_1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change(const QString &)));

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
		ui.lineEdit_1->setPalette(global_text_palette);
		ui.lineEdit_2->setPalette(global_text_palette);
		ui.lineEdit->setPalette(global_text_palette);
		ui.progressBar->setPalette(global_text_palette);

		//��������ɫ
		progress_bar_change_color = false;//�ļ���ʱ������������ɫδ�л�
		ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");

		//�ı���ֻ�����������ֺ���ĸ
		QRegExp regexp("[a-fA-F0-9]+$");//������ʽ��ֻ��������ʮ����������������ַ�
		validator = new QRegExpValidator(regexp, ui.lineEdit);//������Ҫʹ�õ�ģʽ
		ui.lineEdit->setValidator(validator);//Ӧ��ģʽ
		ui.lineEdit_1->setValidator(validator);
		ui.lineEdit_2->setValidator(validator);

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
	LockNormalSingleKey::~LockNormalSingleKey()
	{
		delete timer;
		delete effect_1;
		delete effect_2;
		delete validator;
	}

	//���ó�Ա����
	void LockNormalSingleKey::update_unlock_information(QString head_digit, bool have_head_digit, QString key)//������Ҫ��ʾ�ڽ����ϵ���Ϣ������Ϊ�������ļ�ͷ���������֣��Ƿ���ͷ���������֣���Կ
	{
		bool_array[2] = have_head_digit;//�Ƿ���ͷ����������
		if (have_head_digit)//��ͷ����������
		{
			ui.checkBox->setChecked(true);
			QString head_digit_text = head_digit;//ת����Ϊʮ�����Ʊ��벢���¸����ַ�����
			head_digit_text = head_digit_text.toUpper();//ת��Ϊ��д
			QByteArray head_digit_bytearray = head_digit_text.toLatin1();//ת��ΪQByteArray��ת��Ϊ֧��ASCII���ַ�������
			for (int index = 0; index < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER; index++)//���QByteArray�Ƿ���8��Ԫ�أ���������Ͳ���Ԥ���ַ�
			{
				if (head_digit_bytearray.length() < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER)
				{
					head_digit_bytearray.insert(0, DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_CHAR);
				}
				else//��������ѭ��
				{
					break;
				}
			}
			head_digit_text = head_digit_bytearray;//�޸�lineEdit������
			ui.lineEdit->setText(head_digit_text);//������ʾ����
			head_digit_bytearray = QByteArray::fromHex(head_digit_bytearray);//ת��Ϊ16���Ʊ���
			memmove(char_array, head_digit_bytearray.data(), DIALOG_SIMPLE_LOCK_LINEEDIT_TRANSFORM_LENGTH_NUMBER);//ֱ�Ӹ����ڴ档������char[]����鷳�����ǲ�����char*����Ϊ��ᵼ�´���ʱ���̲߳ۺ�������ʱ���ڸú�������������̵߳���س�Աָ���ֵ��Ҳ������string��������Ϊ����'\0'��Ϊ��β��־�����δת��ʱ���ַ����к��С�00�������������ַ��ᱻȫ������
		}
		else
		{
			ui.checkBox->setChecked(false);
			ui.lineEdit->setText("");//������ʾ����
		}
		ui.lineEdit_2->setText(key);
	}

	void LockNormalSingleKey::set_method(QString method)//���ü��ܷ�ʽ������Ϊ���ܷ�ʽ
	{
		this->method = method;
		ui.comboBox_1->setCurrentText(method);//�����������еļ��ܷ���
		if (method == tr("DES"))
		{
			ui.lineEdit_1->setMaxLength(DES::DEFAULT_KEYLENGTH * 2);
			ui.lineEdit_2->setMaxLength(DES::DEFAULT_KEYLENGTH * 2);
		}
		else if (method == tr("2-Key 3DES"))
		{
			ui.lineEdit_1->setMaxLength(DES_EDE2::DEFAULT_KEYLENGTH * 2);
			ui.lineEdit_2->setMaxLength(DES_EDE2::DEFAULT_KEYLENGTH * 2);
		}
		else if (method == tr("3-Key 3DES"))
		{
			ui.lineEdit_1->setMaxLength(DES_EDE3::DEFAULT_KEYLENGTH * 2);
			ui.lineEdit_2->setMaxLength(DES_EDE3::DEFAULT_KEYLENGTH * 2);
		}
		else if (method == tr("AES-128"))
		{
			ui.lineEdit_1->setMaxLength(AES::MIN_KEYLENGTH * 2);
			ui.lineEdit_2->setMaxLength(AES::MIN_KEYLENGTH * 2);
		}
		else if (method == tr("AES-192"))
		{
			ui.lineEdit_1->setMaxLength(FILE_KEY_AES_MIDDLE_KEY_LENGTH * 2);
			ui.lineEdit_2->setMaxLength(FILE_KEY_AES_MIDDLE_KEY_LENGTH * 2);
		}
		else if (method == tr("AES-256"))
		{
			ui.lineEdit_1->setMaxLength(AES::MAX_KEYLENGTH * 2);
			ui.lineEdit_2->setMaxLength(AES::MAX_KEYLENGTH * 2);
		}
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void LockNormalSingleKey::mousePressEvent(QMouseEvent *event)
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
	void LockNormalSingleKey::mouseMoveEvent(QMouseEvent *event)
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
	void LockNormalSingleKey::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ������������Ϊֻ��ȷ�ϲ�������������Ҫ��д����Ϊ�˱���ͳһ�����ǽ�������д
	void LockNormalSingleKey::keyPressEvent(QKeyEvent *event)
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

	void LockNormalSingleKey::timer_timeout()//ʹ��2��label��������ͼƬ������ָ��һ����ʱ����������ʾͼƬ����ʱͼƬ���²�label���ϲ�labelʹ��ȫ͸��ͼƬ����������ԡ�ʱ�䵽�ں󣬸����л�ͼƬ͸������ʹ�õĶ�ʱ������ͬʱ��ʼ�޸�͸���ȼ������²�label��ʾԭʼͼƬ����͸�����𽥼�С���ϲ�label��ʾ�л���ͼƬ����͸���������ӡ����ϲ�labelͼƬ͸����Ϊ1ʱ���л�������ͼƬ��������1�����µĳ�ʱ�������¿�ʼ��һ��ʱѭ��
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

	void LockNormalSingleKey::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

	void LockNormalSingleKey::combobox_change(const QString &combobox_string)//��Ͽ����ݸ��ĺ���
	{

		//���������������Կ����
		if (combobox_string == tr("DES"))//DES��Կ�ܳ���Ϊ64λ
		{
			ui.lineEdit_1->setMaxLength(DES::DEFAULT_KEYLENGTH * 2);
			ui.lineEdit_2->setMaxLength(DES::DEFAULT_KEYLENGTH * 2);
			method = tr("DES");
		}
		else if(combobox_string == tr("2-Key 3DES"))//DES_EDE2��Կ�ܳ���Ϊ128λ
		{
			ui.lineEdit_1->setMaxLength(DES_EDE2::DEFAULT_KEYLENGTH * 2);
			ui.lineEdit_2->setMaxLength(DES_EDE2::DEFAULT_KEYLENGTH * 2);
			method = tr("2-Key 3DES");
		}
		else if (combobox_string == tr("3-Key 3DES"))//DES_EDE3��Կ�ܳ���Ϊ192λ
		{
			ui.lineEdit_1->setMaxLength(DES_EDE3::DEFAULT_KEYLENGTH * 2);
			ui.lineEdit_2->setMaxLength(DES_EDE3::DEFAULT_KEYLENGTH * 2);
			method = tr("3-Key 3DES");
		}
		else if (combobox_string == tr("AES-128"))//AES-128��Կ�ܳ���Ϊ128λ
		{
			ui.lineEdit_1->setMaxLength(AES::MIN_KEYLENGTH * 2);
			ui.lineEdit_2->setMaxLength(AES::MIN_KEYLENGTH * 2);
			method = tr("AES-128");
		}
		else if (combobox_string == tr("AES-192"))//AES-192��Կ�ܳ���Ϊ192λ
		{
			ui.lineEdit_1->setMaxLength(FILE_KEY_AES_MIDDLE_KEY_LENGTH * 2);
			ui.lineEdit_2->setMaxLength(FILE_KEY_AES_MIDDLE_KEY_LENGTH * 2);
			method = tr("AES-192");
		}
		else if (combobox_string == tr("AES-256"))//AES-256��Կ�ܳ���Ϊ256λ
		{
			ui.lineEdit_1->setMaxLength(AES::MAX_KEYLENGTH * 2);
			ui.lineEdit_2->setMaxLength(AES::MAX_KEYLENGTH * 2);
			method = tr("AES-256");
		}
		else
		{
			ui.lineEdit_1->setMaxLength(DES::DEFAULT_KEYLENGTH * 2);
			ui.lineEdit_2->setMaxLength(DES::DEFAULT_KEYLENGTH * 2);
			method = tr("DES");
		}
	}

	void LockNormalSingleKey::lock_file()//�����ļ�
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
			
			//��ȡ�����ļ���Ϣ
			QSettings *begin_read = new QSettings(FILE_SET_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
			QString information_temp[11];//��ȡ��Ҫ��ʾ������
			information_temp[0] = begin_read->value(FILE_SETTING_CATALOG_1_1_INNER_PATH_STRING).toString();//�ļ���·��
			information_temp[1] = begin_read->value(FILE_SETTING_CATALOG_1_2_INNER_PATH_STRING).toString();
			information_temp[2] = begin_read->value(FILE_SETTING_CATALOG_1_3_INNER_PATH_STRING).toString();
			information_temp[3] = begin_read->value(FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING).toString();
			for (int index = 0; index <= 3; index++)//���������ļ���ʧ�����
			{
				if (information_temp[index].length() == 0)
				{
					information_temp[index] = FILE_SETTING_CATALOG_PATH_DEFAULT_STRING;
				}
				else
				{

				}
			}
			information_temp[4] = begin_read->value(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING).toString();//�����ļ���׺
			information_temp[5] = begin_read->value(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING).toString();
			if (information_temp[4].length() == 0)
			{
				information_temp[4] = FILE_SETTING_SUFFIX_LOCK_DEFAULT_STRING;
			}
			else
			{

			}
			if (information_temp[5].length() == 0)
			{
				information_temp[5] = FILE_SETTING_SUFFIX_UNLOCK_DEFAULT_STRING;
			}
			else
			{

			}
			information_temp[6] = begin_read->value(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING).toString();//����ֵ
			information_temp[7] = begin_read->value(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING).toString();//����ֵ
			information_temp[8] = begin_read->value(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING).toString();//����ֵ
			if (information_temp[6] == "0")//�Ƿ������ʷ�ļ�
			{
				bool_array[0] = false;
			}
			else
			{
				bool_array[0] = true;
			}
			if (information_temp[7] == "0")//�Ƿ������Կ�ļ�
			{
				bool_array[1] = false;
			}
			else
			{
				bool_array[1] = true;
			}
			if (information_temp[8] == "0")//�Ƿ������������Կ�ļ�
			{
				bool_array[2] = false;
			}
			else
			{
				bool_array[2] = true;
			}
			if (ui.checkBox->isChecked())//�Ƿ���ͷ����������
			{
				bool_array[3] = true;
			}
			else
			{
				bool_array[3] = false;
			}
			if (information_temp[0] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)//����Ĭ�����
			{
				information_temp[0] = FILE_OUTPUT_FILE_LOCK_FRONT_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[1] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
			{
				information_temp[1] = FILE_OUTPUT_FILE_UNLOCK_FRONT_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[2] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
			{
				information_temp[2] = FILE_TEMP_FILE_FRONT_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[3] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
			{
				information_temp[3] = FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING;
			}
			else
			{

			}
			information_temp[9] = begin_read->value(FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING).toString();//��Կ�ļ���׺
			information_temp[10] = begin_read->value(FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING).toString();
			if (information_temp[9].length() == 0)
			{
				information_temp[9] = FILE_OUTPUT_FILE_KEY_BACK_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[10].length() == 0)
			{
				information_temp[10] = FILE_OUTPUT_FILE_KEY_BINARY_BACK_PATH_STRING;
			}
			else
			{

			}
			delete begin_read;
			string_array[0] = string((const char *)file_dialog_file_name.toLocal8Bit());//�洢�ַ�����Ϣ���������ļ�·��
			string_array[1] = string((const char *)(file_information.fileName()).toLocal8Bit());//�ļ���
			string_array[2] = string((const char *)information_temp[0].toLocal8Bit());//��������ļ�ǰ�벿�ֲ���·��
			string_array[3] = string((const char *)(FILE_SETTING_SUFFIX_INTERVAL_STRING + information_temp[4]).toLocal8Bit());//��������ļ�·����׺
			string_array[4] = string((const char *)(information_temp[3] + FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING).toLocal8Bit());//�����ʷ�ļ�·��
			string_array[5] = string((const char *)(FILE_SETTING_SUFFIX_INTERVAL_STRING + information_temp[9]).toLocal8Bit());//�����Կ�ļ�·����׺
			string_array[6] = string((const char *)(FILE_SETTING_SUFFIX_INTERVAL_STRING + information_temp[10]).toLocal8Bit());//�����������Կ�ļ�·����׺
			string_array[7] = string((const char *)information_temp[2].toLocal8Bit());//��ʱ�ļ���λ��
			QString lineEdit_text = ui.lineEdit->text().toLatin1();//��ȡ��������ݣ�ת��Ϊ֧��ASCII���ַ�������
			lineEdit_text = lineEdit_text.toUpper();//ת��Ϊ��д
			QByteArray head_digit_bytearray = lineEdit_text.toLatin1();//ת��ΪQByteArray��ת��Ϊ֧��ASCII���ַ�������
			if (bool_array[3])//��Ҫ������������
			{
				for (int index = 0; index < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER; index++)//���QByteArray�Ƿ���8��Ԫ�أ���������Ͳ���Ԥ���ַ�
				{
					if (head_digit_bytearray.length() < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER)
					{
						head_digit_bytearray.insert(0, DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_CHAR);
					}
					else//��������ѭ��
					{
						break;
					}
				}
				lineEdit_text = head_digit_bytearray;//�޸�lineEdit������
				ui.lineEdit->setText(lineEdit_text);
				head_digit_bytearray = QByteArray::fromHex(head_digit_bytearray);//ת��Ϊ16���Ʊ���
				memmove(char_array, head_digit_bytearray.data(), DIALOG_SIMPLE_LOCK_LINEEDIT_TRANSFORM_LENGTH_NUMBER);//ֱ�Ӹ����ڴ档������char[]����鷳�����ǲ�����char*����Ϊ��ᵼ�´���ʱ���̲߳ۺ�������ʱ���ڸú�������������̵߳���س�Աָ���ֵ��Ҳ������string��������Ϊ����'\0'��Ϊ��β��־�����δת��ʱ���ַ����к��С�00�������������ַ��ᱻȫ������
			}
			else
			{
				
			}
			if (ui.checkBox_2->isChecked())//�Ƿ�������һ������
			{
				bool_array[4] = true;
			}
			else
			{
				bool_array[4] = false;
			}
			Lock_single_file_thread *thread = new Lock_single_file_thread();//�����ļ����߳�
			connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
			connect(this, SIGNAL(send_data(string*, bool*, char*, char*, QString)), thread, SLOT(get_data(string*, bool*, char*, char*, QString)));
			connect(this, SIGNAL(send_target_class_point(Export_LockSingle_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockSingle_virtual_class *)));
			connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
			emit send_data(string_array, bool_array, char_array, key, method);//��������
			using export_class = Export_LockSingle_virtual_class * (*)(void);//����ָ�򵼳�������ָ������
			HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//��̬����dll�����ҵ���ָ������Ķ���ָ�룬ͨ���źŴ��ݸ����߳�ʹ��
			ui.progressBar->setVisible(true);//��ʾ������
			ui.progressBar->setValue(0);//��������ʼֵΪ0
			progress_bar_change_color = false;//��ʼ����ʱ������������ɫδ�л�
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");//���ý�������ɫ
			if (dll_name != NULL)
			{
				emit send_dll_name(dll_name);//��Ϊ�����߳�ʹ����dll֮ǰ����ж��dll����ֻ��ͨ���źŽ�dll�����ݸ����߳�
				export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_single");//ͨ������ָ���ĵ���������������Ҫ����
				if (get_class != NULL)
				{
					Export_LockSingle_virtual_class *target_class_object = get_class();//���Ŀ����Ķ���ָ��
					emit send_target_class_point(target_class_object);//����dll���������ָ��
					if (method == tr("DES"))
					{
						connect(target_class_object, SIGNAL(lock_DES_process(double)), this, SLOT(receive_lock_DES_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
						connect(target_class_object, SIGNAL(lock_DES_final(bool, char*)), this, SLOT(receive_lock_DES_final(bool, char*)));
					}
					else if (method == tr("2-Key 3DES"))
					{
						connect(target_class_object, SIGNAL(lock_DES_EDE2_process(double)), this, SLOT(receive_lock_DES_EDE2_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
						connect(target_class_object, SIGNAL(lock_DES_EDE2_final(bool, char*)), this, SLOT(receive_lock_DES_EDE2_final(bool, char*)));
					}
					else if (method == tr("3-Key 3DES"))
					{
						connect(target_class_object, SIGNAL(lock_DES_EDE3_process(double)), this, SLOT(receive_lock_DES_EDE3_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
						connect(target_class_object, SIGNAL(lock_DES_EDE3_final(bool, char*)), this, SLOT(receive_lock_DES_EDE3_final(bool, char*)));
					}
					else if (method == tr("AES-128"))
					{
						connect(target_class_object, SIGNAL(lock_AES_MIN_process(double)), this, SLOT(receive_lock_AES_MIN_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
						connect(target_class_object, SIGNAL(lock_AES_MIN_final(bool, char*)), this, SLOT(receive_lock_AES_MIN_final(bool, char*)));
					}
					else if (method == tr("AES-192"))
					{
						connect(target_class_object, SIGNAL(lock_AES_MIDDLE_process(double)), this, SLOT(receive_lock_AES_MIDDLE_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
						connect(target_class_object, SIGNAL(lock_AES_MIDDLE_final(bool, char*)), this, SLOT(receive_lock_AES_MIDDLE_final(bool, char*)));
					}
					else if (method == tr("AES-256"))
					{
						connect(target_class_object, SIGNAL(lock_AES_MAX_process(double)), this, SLOT(receive_lock_AES_MAX_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
						connect(target_class_object, SIGNAL(lock_AES_MAX_final(bool, char*)), this, SLOT(receive_lock_AES_MAX_final(bool, char*)));
					}
					else
					{
						connect(target_class_object, SIGNAL(lock_DES_process(double)), this, SLOT(receive_lock_DES_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
						connect(target_class_object, SIGNAL(lock_DES_final(bool, char*)), this, SLOT(receive_lock_DES_final(bool, char*)));
					}
				}
				else
				{

				}
			}
			else
			{

			}
			thread->start();//��ʼ���߳�
		}
		else if(*change_result_address)
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

	void LockNormalSingleKey::unlock_file()//�����ļ�
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
			//��ȡ�����ļ���Ϣ
			QSettings *begin_read = new QSettings(FILE_SET_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
			QString information_temp[9];//��ȡ��Ҫ��ʾ������
			information_temp[0] = begin_read->value(FILE_SETTING_CATALOG_1_1_INNER_PATH_STRING).toString();//�ļ���·��
			information_temp[1] = begin_read->value(FILE_SETTING_CATALOG_1_2_INNER_PATH_STRING).toString();
			information_temp[2] = begin_read->value(FILE_SETTING_CATALOG_1_3_INNER_PATH_STRING).toString();
			information_temp[3] = begin_read->value(FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING).toString();
			for (int index = 0; index <= 3; index++)//���������ļ���ʧ�����
			{
				if (information_temp[index].length() == 0)
				{
					information_temp[index] = FILE_SETTING_CATALOG_PATH_DEFAULT_STRING;
				}
				else
				{

				}
			}
			information_temp[4] = begin_read->value(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING).toString();//�ļ���׺
			information_temp[5] = begin_read->value(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING).toString();
			if (information_temp[4].length() == 0)
			{
				information_temp[4] = FILE_SETTING_SUFFIX_LOCK_DEFAULT_STRING;
			}
			else
			{

			}
			if (information_temp[5].length() == 0)
			{
				information_temp[5] = FILE_SETTING_SUFFIX_UNLOCK_DEFAULT_STRING;
			}
			else
			{

			}
			information_temp[6] = begin_read->value(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING).toString();//����ֵ
			information_temp[7] = begin_read->value(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING).toString();//����ֵ
			information_temp[8] = begin_read->value(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING).toString();//����ֵ
			delete begin_read;
			if (information_temp[6] == "0")//�Ƿ������ʷ�ļ�
			{
				bool_array[0] = false;
			}
			else
			{
				bool_array[0] = true;
			}
			if (information_temp[7] == "0")//�Ƿ������Կ�ļ�
			{
				bool_array[1] = false;
			}
			else
			{
				bool_array[1] = true;
			}
			if (information_temp[8] == "0")//�Ƿ������������Կ�ļ�
			{
				bool_array[2] = false;
			}
			else
			{
				bool_array[2] = true;
			}
			if (ui.checkBox->isChecked())//�Ƿ���ͷ����������
			{
				bool_array[3] = true;
			}
			else
			{
				bool_array[3] = false;
			}
			if (information_temp[0] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)//����Ĭ�����
			{
				information_temp[0] = FILE_OUTPUT_FILE_LOCK_FRONT_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[1] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
			{
				information_temp[1] = FILE_OUTPUT_FILE_UNLOCK_FRONT_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[2] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
			{
				information_temp[2] = FILE_TEMP_FILE_FRONT_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[3] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
			{
				information_temp[3] = FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING;
			}
			else
			{

			}
			string_array[0] = string((const char *)file_dialog_file_name.toLocal8Bit());//�洢�ַ�����Ϣ���������ļ�·��
			string_array[1] = string((const char *)(file_information.fileName()).toLocal8Bit());//�ļ���
			string_array[2] = string((const char *)information_temp[1].toLocal8Bit());//��������ļ�ǰ�벿�ֲ���·��
			string_array[3] = string((const char *)(FILE_SETTING_SUFFIX_INTERVAL_STRING + information_temp[5]).toLocal8Bit());//��������ļ�·����׺
			string_array[4] = string((const char *)(information_temp[3] + FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING).toLocal8Bit());//�����ʷ�ļ�·��
			string_array[5] = "";//�����Կ�ļ�·����׺����������ʹ��
			string_array[6] = "";//�����������Կ�ļ�·����׺����������ʹ��
			string_array[7] = string((const char *)information_temp[2].toLocal8Bit());//��ʱ�ļ���λ��
			QString lineEdit_text = ui.lineEdit->text().toLatin1();//��ȡ��������ݣ�ת��Ϊ֧��ASCII���ַ�������
			lineEdit_text = lineEdit_text.toUpper();//ת��Ϊ��д
			QByteArray head_digit_bytearray = lineEdit_text.toLatin1();//ת��ΪQByteArray��ת��Ϊ֧��ASCII���ַ�������
			if (bool_array[3])//��Ҫ������������
			{
				for (int index = 0; index < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER; index++)//���QByteArray�Ƿ���8��Ԫ�أ���������Ͳ���Ԥ���ַ�
				{
					if (head_digit_bytearray.length() < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER)
					{
						head_digit_bytearray.insert(0, DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_CHAR);
					}
					else//��������ѭ��
					{
						break;
					}
				}
				lineEdit_text = head_digit_bytearray;//�޸�lineEdit������
				ui.lineEdit->setText(lineEdit_text);
				head_digit_bytearray = QByteArray::fromHex(head_digit_bytearray);//ת��Ϊ16���Ʊ���
				memmove(char_array, head_digit_bytearray.data(), DIALOG_SIMPLE_LOCK_LINEEDIT_TRANSFORM_LENGTH_NUMBER);//ֱ�Ӹ����ڴ档������char[]����鷳�����ǲ�����char*����Ϊ��ᵼ�´���ʱ���̲߳ۺ�������ʱ���ڸú�������������̵߳���س�Աָ���ֵ��Ҳ������string��������Ϊ����'\0'��Ϊ��β��־�����δת��ʱ���ַ����к��С�00�������������ַ��ᱻȫ������
			}
			else
			{

			}
			if (ui.checkBox_2->isChecked())//�Ƿ�������һ������
			{
				bool_array[4] = true;
			}
			else
			{
				bool_array[4] = false;
			}
			QString key_text = ui.lineEdit_2->text().toLatin1();//��ȡ��Կ���ݣ�ת��Ϊ֧��ASCII���ַ�������
			key_text = key_text.toUpper();//ת��Ϊ��д
			QByteArray key_text_bytearray = key_text.toLatin1();//ת��ΪQByteArray��ת��Ϊ֧��ASCII���ַ�������
			key_text = key_text_bytearray;//�޸�lineEdit������
			ui.lineEdit_2->setText(key_text);
			if (method == tr("DES"))
			{
				key_text_bytearray = QByteArray::fromHex(key_text_bytearray);//ת��Ϊ16���Ʊ���
				memmove(key, key_text_bytearray.data(), DES::DEFAULT_KEYLENGTH);//ֱ�Ӹ����ڴ�
				UnlockNormalSingleCheck dialog;//����ȷ�Ͻ�����Ϣ��
				is_continue = false;//�����Ƿ���Ҫ����һ����ִ������������
				dialog.set_information(method, &key_text, &lineEdit_text, &bool_array[3], &is_continue);//�趨��ʼֵ
				dialog.exec();
				if (is_continue)//�ڽ���ȷ�ϴ��ڵ��ȷ�ϣ����������н��ܲ���
				{
					if (key_text.length() < DES::DEFAULT_KEYLENGTH * 2)
					{
						Help dialog;//��ʾ������Ϣ
						dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_KEY_PATH_STRING);
						dialog.setWindowTitle(tr("����ʧ���ˡ���"));
						dialog.exec();
					}
					else
					{
						update_unlock_information(lineEdit_text, bool_array[3], key_text);//���´�������
						key_text_bytearray = key_text.toLatin1();//����Կ�ı�ת��Ϊ���������ݲ���ֵ
						key_text_bytearray = QByteArray::fromHex(key_text_bytearray);//ת��Ϊ16���Ʊ���
						memmove(key, key_text_bytearray.data(), DES::DEFAULT_KEYLENGTH);//ֱ�Ӹ����ڴ�
						Unlock_single_file_thread *thread = new Unlock_single_file_thread;//�����ļ����߳�
						connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
						connect(this, SIGNAL(send_data(string*, bool*, char*, char*, QString)), thread, SLOT(get_data(string*, bool*, char*, char*, QString)));
						connect(this, SIGNAL(send_target_class_point(Export_LockSingle_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockSingle_virtual_class *)));
						connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
						emit send_data(string_array, bool_array, char_array, key, method);//��������
						using export_class = Export_LockSingle_virtual_class * (*)(void);//����ָ�򵼳�������ָ������
						HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//��̬����dll�����ҵ���ָ������Ķ���ָ�룬ͨ���źŴ��ݸ����߳�ʹ��
						ui.progressBar->setVisible(true);//��ʾ������
						ui.progressBar->setValue(0);//��������ʼֵΪ0
						progress_bar_change_color = false;//��ʼ����ʱ������������ɫδ�л�
						ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");//���ý�������ɫ
						if (dll_name != NULL)
						{
							emit send_dll_name(dll_name);//��Ϊ�����߳�ʹ����dll֮ǰ����ж��dll����ֻ��ͨ���źŽ�dll�����ݸ����߳�
							export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_single");//ͨ������ָ���ĵ���������������Ҫ����
							if (get_class != NULL)
							{
								Export_LockSingle_virtual_class *target_class_object = get_class();//���Ŀ����Ķ���ָ��
								emit send_target_class_point(target_class_object);//����dll���������ָ��
								connect(target_class_object, SIGNAL(unlock_DES_process(double)), this, SLOT(receive_unlock_DES_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
								connect(target_class_object, SIGNAL(unlock_DES_final(bool)), this, SLOT(receive_unlock_DES_final(bool)));
							}
							else
							{

							}
						}
						else
						{

						}
						thread->start();//��ʼ���߳�
					}
				}
				else//�ڽ���ȷ�ϴ��ڵ��ȡ�����������κβ���
				{

				}
			}
			else if (method == tr("2-Key 3DES"))
			{
				key_text_bytearray = QByteArray::fromHex(key_text_bytearray);//ת��Ϊ16���Ʊ���
				memmove(key, key_text_bytearray.data(), DES_EDE2::DEFAULT_KEYLENGTH);//ֱ�Ӹ����ڴ�
				UnlockNormalSingleCheck dialog;//����ȷ�Ͻ�����Ϣ��
				is_continue = false;//�����Ƿ���Ҫ����һ����ִ������������
				dialog.set_information(method, &key_text, &lineEdit_text, &bool_array[3], &is_continue);//�趨��ʼֵ
				dialog.exec();
				if (is_continue)//�ڽ���ȷ�ϴ��ڵ��ȷ�ϣ����������н��ܲ���
				{
					if (key_text.length() < DES_EDE2::DEFAULT_KEYLENGTH * 2)
					{
						Help dialog;//��ʾ������Ϣ
						dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_KEY_PATH_STRING);
						dialog.setWindowTitle(tr("����ʧ���ˡ���"));
						dialog.exec();
					}
					else
					{
						update_unlock_information(lineEdit_text, bool_array[3], key_text);//���´�������
						key_text_bytearray = key_text.toLatin1();//����Կ�ı�ת��Ϊ���������ݲ���ֵ
						key_text_bytearray = QByteArray::fromHex(key_text_bytearray);//ת��Ϊ16���Ʊ���
						memmove(key, key_text_bytearray.data(), DES_EDE2::DEFAULT_KEYLENGTH);//ֱ�Ӹ����ڴ�
						Unlock_single_file_thread *thread = new Unlock_single_file_thread;//�����ļ����߳�
						connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
						connect(this, SIGNAL(send_data(string*, bool*, char*, char*, QString)), thread, SLOT(get_data(string*, bool*, char*, char*, QString)));
						connect(this, SIGNAL(send_target_class_point(Export_LockSingle_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockSingle_virtual_class *)));
						connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
						emit send_data(string_array, bool_array, char_array, key, method);//��������
						using export_class = Export_LockSingle_virtual_class * (*)(void);//����ָ�򵼳�������ָ������
						HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//��̬����dll�����ҵ���ָ������Ķ���ָ�룬ͨ���źŴ��ݸ����߳�ʹ��
						ui.progressBar->setVisible(true);//��ʾ������
						ui.progressBar->setValue(0);//��������ʼֵΪ0
						progress_bar_change_color = false;//��ʼ����ʱ������������ɫδ�л�
						ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");//���ý�������ɫ
						if (dll_name != NULL)
						{
							emit send_dll_name(dll_name);//��Ϊ�����߳�ʹ����dll֮ǰ����ж��dll����ֻ��ͨ���źŽ�dll�����ݸ����߳�
							export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_single");//ͨ������ָ���ĵ���������������Ҫ����
							if (get_class != NULL)
							{
								Export_LockSingle_virtual_class *target_class_object = get_class();//���Ŀ����Ķ���ָ��
								emit send_target_class_point(target_class_object);//����dll���������ָ��
								connect(target_class_object, SIGNAL(unlock_DES_EDE2_process(double)), this, SLOT(receive_unlock_DES_EDE2_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
								connect(target_class_object, SIGNAL(unlock_DES_EDE2_final(bool)), this, SLOT(receive_unlock_DES_EDE2_final(bool)));
							}
							else
							{

							}
						}
						else
						{

						}
						thread->start();//��ʼ���߳�
					}
				}
				else//�ڽ���ȷ�ϴ��ڵ��ȡ�����������κβ���
				{

				}
			}
			else if (method == tr("3-Key 3DES"))
			{
				key_text_bytearray = QByteArray::fromHex(key_text_bytearray);//ת��Ϊ16���Ʊ���
				memmove(key, key_text_bytearray.data(), DES_EDE3::DEFAULT_KEYLENGTH);//ֱ�Ӹ����ڴ�
				UnlockNormalSingleCheck dialog;//����ȷ�Ͻ�����Ϣ��
				is_continue = false;//�����Ƿ���Ҫ����һ����ִ������������
				dialog.set_information(method, &key_text, &lineEdit_text, &bool_array[3], &is_continue);//�趨��ʼֵ
				dialog.exec();
				if (is_continue)//�ڽ���ȷ�ϴ��ڵ��ȷ�ϣ����������н��ܲ���
				{
					if (key_text.length() < DES_EDE3::DEFAULT_KEYLENGTH * 2)
					{
						Help dialog;//��ʾ������Ϣ
						dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_KEY_PATH_STRING);
						dialog.setWindowTitle(tr("����ʧ���ˡ���"));
						dialog.exec();
					}
					else
					{
						update_unlock_information(lineEdit_text, bool_array[3], key_text);//���´�������
						key_text_bytearray = key_text.toLatin1();//����Կ�ı�ת��Ϊ���������ݲ���ֵ
						key_text_bytearray = QByteArray::fromHex(key_text_bytearray);//ת��Ϊ16���Ʊ���
						memmove(key, key_text_bytearray.data(), DES_EDE3::DEFAULT_KEYLENGTH);//ֱ�Ӹ����ڴ�
						Unlock_single_file_thread *thread = new Unlock_single_file_thread;//�����ļ����߳�
						connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
						connect(this, SIGNAL(send_data(string*, bool*, char*, char*, QString)), thread, SLOT(get_data(string*, bool*, char*, char*, QString)));
						connect(this, SIGNAL(send_target_class_point(Export_LockSingle_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockSingle_virtual_class *)));
						connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
						emit send_data(string_array, bool_array, char_array, key, method);//��������
						using export_class = Export_LockSingle_virtual_class * (*)(void);//����ָ�򵼳�������ָ������
						HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//��̬����dll�����ҵ���ָ������Ķ���ָ�룬ͨ���źŴ��ݸ����߳�ʹ��
						ui.progressBar->setVisible(true);//��ʾ������
						ui.progressBar->setValue(0);//��������ʼֵΪ0
						progress_bar_change_color = false;//��ʼ����ʱ������������ɫδ�л�
						ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");//���ý�������ɫ
						if (dll_name != NULL)
						{
							emit send_dll_name(dll_name);//��Ϊ�����߳�ʹ����dll֮ǰ����ж��dll����ֻ��ͨ���źŽ�dll�����ݸ����߳�
							export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_single");//ͨ������ָ���ĵ���������������Ҫ����
							if (get_class != NULL)
							{
								Export_LockSingle_virtual_class *target_class_object = get_class();//���Ŀ����Ķ���ָ��
								emit send_target_class_point(target_class_object);//����dll���������ָ��
								connect(target_class_object, SIGNAL(unlock_DES_EDE3_process(double)), this, SLOT(receive_unlock_DES_EDE3_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
								connect(target_class_object, SIGNAL(unlock_DES_EDE3_final(bool)), this, SLOT(receive_unlock_DES_EDE3_final(bool)));
							}
							else
							{

							}
						}
						else
						{

						}
						thread->start();//��ʼ���߳�
					}
				}
				else//�ڽ���ȷ�ϴ��ڵ��ȡ�����������κβ���
				{

				}
			}
			else if (method == tr("AES-128"))
			{
				key_text_bytearray = QByteArray::fromHex(key_text_bytearray);//ת��Ϊ16���Ʊ���
				memmove(key, key_text_bytearray.data(), AES::MIN_KEYLENGTH);//ֱ�Ӹ����ڴ�
				UnlockNormalSingleCheck dialog;//����ȷ�Ͻ�����Ϣ��
				is_continue = false;//�����Ƿ���Ҫ����һ����ִ������������
				dialog.set_information(method, &key_text, &lineEdit_text, &bool_array[3], &is_continue);//�趨��ʼֵ
				dialog.exec();
				if (is_continue)//�ڽ���ȷ�ϴ��ڵ��ȷ�ϣ����������н��ܲ���
				{
					if (key_text.length() < AES::MIN_KEYLENGTH * 2)
					{
						Help dialog;//��ʾ������Ϣ
						dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_KEY_PATH_STRING);
						dialog.setWindowTitle(tr("����ʧ���ˡ���"));
						dialog.exec();
					}
					else
					{
						update_unlock_information(lineEdit_text, bool_array[3], key_text);//���´�������
						key_text_bytearray = key_text.toLatin1();//����Կ�ı�ת��Ϊ���������ݲ���ֵ
						key_text_bytearray = QByteArray::fromHex(key_text_bytearray);//ת��Ϊ16���Ʊ���
						memmove(key, key_text_bytearray.data(), AES::MIN_KEYLENGTH);//ֱ�Ӹ����ڴ�
						Unlock_single_file_thread *thread = new Unlock_single_file_thread;//�����ļ����߳�
						connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
						connect(this, SIGNAL(send_data(string*, bool*, char*, char*, QString)), thread, SLOT(get_data(string*, bool*, char*, char*, QString)));
						connect(this, SIGNAL(send_target_class_point(Export_LockSingle_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockSingle_virtual_class *)));
						connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
						emit send_data(string_array, bool_array, char_array, key, method);//��������
						using export_class = Export_LockSingle_virtual_class * (*)(void);//����ָ�򵼳�������ָ������
						HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//��̬����dll�����ҵ���ָ������Ķ���ָ�룬ͨ���źŴ��ݸ����߳�ʹ��
						ui.progressBar->setVisible(true);//��ʾ������
						ui.progressBar->setValue(0);//��������ʼֵΪ0
						progress_bar_change_color = false;//��ʼ����ʱ������������ɫδ�л�
						ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");//���ý�������ɫ
						if (dll_name != NULL)
						{
							emit send_dll_name(dll_name);//��Ϊ�����߳�ʹ����dll֮ǰ����ж��dll����ֻ��ͨ���źŽ�dll�����ݸ����߳�
							export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_single");//ͨ������ָ���ĵ���������������Ҫ����
							if (get_class != NULL)
							{
								Export_LockSingle_virtual_class *target_class_object = get_class();//���Ŀ����Ķ���ָ��
								emit send_target_class_point(target_class_object);//����dll���������ָ��
								connect(target_class_object, SIGNAL(unlock_AES_MIN_process(double)), this, SLOT(receive_unlock_AES_MIN_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
								connect(target_class_object, SIGNAL(unlock_AES_MIN_final(bool)), this, SLOT(receive_unlock_AES_MIN_final(bool)));
							}
							else
							{

							}
						}
						else
						{

						}
						thread->start();//��ʼ���߳�
					}
				}
				else//�ڽ���ȷ�ϴ��ڵ��ȡ�����������κβ���
				{

				}
			}
			else if (method == tr("AES-192"))
			{
				key_text_bytearray = QByteArray::fromHex(key_text_bytearray);//ת��Ϊ16���Ʊ���
				memmove(key, key_text_bytearray.data(), FILE_KEY_AES_MIDDLE_KEY_LENGTH);//ֱ�Ӹ����ڴ�
				UnlockNormalSingleCheck dialog;//����ȷ�Ͻ�����Ϣ��
				is_continue = false;//�����Ƿ���Ҫ����һ����ִ������������
				dialog.set_information(method, &key_text, &lineEdit_text, &bool_array[3], &is_continue);//�趨��ʼֵ
				dialog.exec();
				if (is_continue)//�ڽ���ȷ�ϴ��ڵ��ȷ�ϣ����������н��ܲ���
				{
					if (key_text.length() < FILE_KEY_AES_MIDDLE_KEY_LENGTH * 2)
					{
						Help dialog;//��ʾ������Ϣ
						dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_KEY_PATH_STRING);
						dialog.setWindowTitle(tr("����ʧ���ˡ���"));
						dialog.exec();
					}
					else
					{
						update_unlock_information(lineEdit_text, bool_array[3], key_text);//���´�������
						key_text_bytearray = key_text.toLatin1();//����Կ�ı�ת��Ϊ���������ݲ���ֵ
						key_text_bytearray = QByteArray::fromHex(key_text_bytearray);//ת��Ϊ16���Ʊ���
						memmove(key, key_text_bytearray.data(), FILE_KEY_AES_MIDDLE_KEY_LENGTH);//ֱ�Ӹ����ڴ�
						Unlock_single_file_thread *thread = new Unlock_single_file_thread;//�����ļ����߳�
						connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
						connect(this, SIGNAL(send_data(string*, bool*, char*, char*, QString)), thread, SLOT(get_data(string*, bool*, char*, char*, QString)));
						connect(this, SIGNAL(send_target_class_point(Export_LockSingle_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockSingle_virtual_class *)));
						connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
						emit send_data(string_array, bool_array, char_array, key, method);//��������
						using export_class = Export_LockSingle_virtual_class * (*)(void);//����ָ�򵼳�������ָ������
						HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//��̬����dll�����ҵ���ָ������Ķ���ָ�룬ͨ���źŴ��ݸ����߳�ʹ��
						ui.progressBar->setVisible(true);//��ʾ������
						ui.progressBar->setValue(0);//��������ʼֵΪ0
						progress_bar_change_color = false;//��ʼ����ʱ������������ɫδ�л�
						ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");//���ý�������ɫ
						if (dll_name != NULL)
						{
							emit send_dll_name(dll_name);//��Ϊ�����߳�ʹ����dll֮ǰ����ж��dll����ֻ��ͨ���źŽ�dll�����ݸ����߳�
							export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_single");//ͨ������ָ���ĵ���������������Ҫ����
							if (get_class != NULL)
							{
								Export_LockSingle_virtual_class *target_class_object = get_class();//���Ŀ����Ķ���ָ��
								emit send_target_class_point(target_class_object);//����dll���������ָ��
								connect(target_class_object, SIGNAL(unlock_AES_MIDDLE_process(double)), this, SLOT(receive_unlock_AES_MIDDLE_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
								connect(target_class_object, SIGNAL(unlock_AES_MIDDLE_final(bool)), this, SLOT(receive_unlock_AES_MIDDLE_final(bool)));
							}
							else
							{

							}
						}
						else
						{

						}
						thread->start();//��ʼ���߳�
					}
				}
				else//�ڽ���ȷ�ϴ��ڵ��ȡ�����������κβ���
				{

				}
			}
			else if (method == tr("AES-256"))
			{
				key_text_bytearray = QByteArray::fromHex(key_text_bytearray);//ת��Ϊ16���Ʊ���
				memmove(key, key_text_bytearray.data(), AES::MAX_KEYLENGTH);//ֱ�Ӹ����ڴ�
				UnlockNormalSingleCheck dialog;//����ȷ�Ͻ�����Ϣ��
				is_continue = false;//�����Ƿ���Ҫ����һ����ִ������������
				dialog.set_information(method, &key_text, &lineEdit_text, &bool_array[3], &is_continue);//�趨��ʼֵ
				dialog.exec();
				if (is_continue)//�ڽ���ȷ�ϴ��ڵ��ȷ�ϣ����������н��ܲ���
				{
					if (key_text.length() < AES::MAX_KEYLENGTH * 2)
					{
						Help dialog;//��ʾ������Ϣ
						dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_KEY_PATH_STRING);
						dialog.setWindowTitle(tr("����ʧ���ˡ���"));
						dialog.exec();
					}
					else
					{
						update_unlock_information(lineEdit_text, bool_array[3], key_text);//���´�������
						key_text_bytearray = key_text.toLatin1();//����Կ�ı�ת��Ϊ���������ݲ���ֵ
						key_text_bytearray = QByteArray::fromHex(key_text_bytearray);//ת��Ϊ16���Ʊ���
						memmove(key, key_text_bytearray.data(), AES::MAX_KEYLENGTH);//ֱ�Ӹ����ڴ�
						Unlock_single_file_thread *thread = new Unlock_single_file_thread;//�����ļ����߳�
						connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
						connect(this, SIGNAL(send_data(string*, bool*, char*, char*, QString)), thread, SLOT(get_data(string*, bool*, char*, char*, QString)));
						connect(this, SIGNAL(send_target_class_point(Export_LockSingle_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockSingle_virtual_class *)));
						connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
						emit send_data(string_array, bool_array, char_array, key, method);//��������
						using export_class = Export_LockSingle_virtual_class * (*)(void);//����ָ�򵼳�������ָ������
						HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//��̬����dll�����ҵ���ָ������Ķ���ָ�룬ͨ���źŴ��ݸ����߳�ʹ��
						ui.progressBar->setVisible(true);//��ʾ������
						ui.progressBar->setValue(0);//��������ʼֵΪ0
						progress_bar_change_color = false;//��ʼ����ʱ������������ɫδ�л�
						ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");//���ý�������ɫ
						if (dll_name != NULL)
						{
							emit send_dll_name(dll_name);//��Ϊ�����߳�ʹ����dll֮ǰ����ж��dll����ֻ��ͨ���źŽ�dll�����ݸ����߳�
							export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_single");//ͨ������ָ���ĵ���������������Ҫ����
							if (get_class != NULL)
							{
								Export_LockSingle_virtual_class *target_class_object = get_class();//���Ŀ����Ķ���ָ��
								emit send_target_class_point(target_class_object);//����dll���������ָ��
								connect(target_class_object, SIGNAL(unlock_AES_MAX_process(double)), this, SLOT(receive_unlock_AES_MAX_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
								connect(target_class_object, SIGNAL(unlock_AES_MAX_final(bool)), this, SLOT(receive_unlock_AES_MAX_final(bool)));
							}
							else
							{

							}
						}
						else
						{

						}
						thread->start();//��ʼ���߳�
					}
				}
				else//�ڽ���ȷ�ϴ��ڵ��ȡ�����������κβ���
				{

				}
			}
			else
			{
				key_text_bytearray = QByteArray::fromHex(key_text_bytearray);//ת��Ϊ16���Ʊ���
				memmove(key, key_text_bytearray.data(), DES::DEFAULT_KEYLENGTH);//ֱ�Ӹ����ڴ�
				UnlockNormalSingleCheck dialog;//����ȷ�Ͻ�����Ϣ��
				is_continue = false;//�����Ƿ���Ҫ����һ����ִ������������
				dialog.set_information(method, &key_text, &lineEdit_text, &bool_array[3], &is_continue);//�趨��ʼֵ
				dialog.exec();
				if (is_continue)//�ڽ���ȷ�ϴ��ڵ��ȷ�ϣ����������н��ܲ���
				{
					if (key_text.length() < DES::DEFAULT_KEYLENGTH * 2)
					{
						Help dialog;//��ʾ������Ϣ
						dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_KEY_PATH_STRING);
						dialog.setWindowTitle(tr("����ʧ���ˡ���"));
						dialog.exec();
					}
					else
					{
						update_unlock_information(lineEdit_text, bool_array[3], key_text);//���´�������
						key_text_bytearray = key_text.toLatin1();//����Կ�ı�ת��Ϊ���������ݲ���ֵ
						key_text_bytearray = QByteArray::fromHex(key_text_bytearray);//ת��Ϊ16���Ʊ���
						memmove(key, key_text_bytearray.data(), DES::DEFAULT_KEYLENGTH);//ֱ�Ӹ����ڴ�
						Unlock_single_file_thread *thread = new Unlock_single_file_thread;//�����ļ����߳�
						connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
						connect(this, SIGNAL(send_data(string*, bool*, char*, char*, QString)), thread, SLOT(get_data(string*, bool*, char*, char*, QString)));
						connect(this, SIGNAL(send_target_class_point(Export_LockSingle_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockSingle_virtual_class *)));
						connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
						emit send_data(string_array, bool_array, char_array, key, method);//��������
						using export_class = Export_LockSingle_virtual_class * (*)(void);//����ָ�򵼳�������ָ������
						HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//��̬����dll�����ҵ���ָ������Ķ���ָ�룬ͨ���źŴ��ݸ����߳�ʹ��
						ui.progressBar->setVisible(true);//��ʾ������
						ui.progressBar->setValue(0);//��������ʼֵΪ0
						progress_bar_change_color = false;//��ʼ����ʱ������������ɫδ�л�
						ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");//���ý�������ɫ
						if (dll_name != NULL)
						{
							emit send_dll_name(dll_name);//��Ϊ�����߳�ʹ����dll֮ǰ����ж��dll����ֻ��ͨ���źŽ�dll�����ݸ����߳�
							export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_single");//ͨ������ָ���ĵ���������������Ҫ����
							if (get_class != NULL)
							{
								Export_LockSingle_virtual_class *target_class_object = get_class();//���Ŀ����Ķ���ָ��
								emit send_target_class_point(target_class_object);//����dll���������ָ��
								connect(target_class_object, SIGNAL(unlock_DES_process(double)), this, SLOT(receive_unlock_DES_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
								connect(target_class_object, SIGNAL(unlock_DES_final(bool)), this, SLOT(receive_unlock_DES_final(bool)));
							}
							else
							{

							}
						}
						else
						{

						}
						thread->start();//��ʼ���߳�
					}
				}
				else//�ڽ���ȷ�ϴ��ڵ��ȡ�����������κβ���
				{

				}
			}
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

	void LockNormalSingleKey::receive_lock_DES_process(double index)//DES���ܽ�������ʾ������Ϊ�Ѵ����ֱ���
	{
		double progress_bar_value = (index * DIALOG_PROGRESSBAR_TIMES_NUMBER);//�������
		if (progress_bar_value > DIALOG_PROGRESSBAR_MAX_NUMBER)
		{
			progress_bar_value = DIALOG_PROGRESSBAR_MAX_NUMBER;
		}
		else
		{

		}
		if (progress_bar_value > DIALOG_PROGRESSBAR_CHANGE_FONT_COLOR_NUMBER && !progress_bar_change_color)//���⿴��������
		{
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#F8F5E2;}QProgressBar::chunk{background-color:#461C0A;}");
			progress_bar_change_color = true;//��ֻ֤�л�һ��������ɫ
		}
		else
		{

		}
		ui.progressBar->setValue((int)progress_bar_value);//��������ʾ
	}

	void LockNormalSingleKey::receive_lock_DES_final(bool is_success, char *key)//DES���ܽ���������Ϊdll������ָ��
	{
		ui.progressBar->setValue(0);//��������ʾ��Сֵ
		progress_bar_change_color = false;//��ֻ֤�л�һ��������ɫ
		ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");
		if (is_success == true)
		{
			QByteArray key_hex_string(key, DES::DEFAULT_KEYLENGTH);//����Կת��ΪQBytearray
			key_hex_string = key_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			ui.lineEdit_1->setText((QString)key_hex_string);//��������ʾ���ɵ���Կ
		}
		else
		{
			Help dialog;//��ʾ������Ϣ
			dialog.set_dialog_information_path(DIALOG_INFORMATION_LOCK_FAIL_PATH_STRING);
			dialog.setWindowTitle(tr("����ʧ���ˡ���"));
			dialog.exec();
		}
	}

	void LockNormalSingleKey::receive_unlock_DES_process(double index)//DES�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
	{
		double progress_bar_value = (index * DIALOG_PROGRESSBAR_TIMES_NUMBER);//�������
		if (progress_bar_value > DIALOG_PROGRESSBAR_MAX_NUMBER)
		{
			progress_bar_value = DIALOG_PROGRESSBAR_MAX_NUMBER;
		}
		else
		{

		}
		if (progress_bar_value > DIALOG_PROGRESSBAR_CHANGE_FONT_COLOR_NUMBER && !progress_bar_change_color)//���⿴��������
		{
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#F8F5E2;}QProgressBar::chunk{background-color:#461C0A;}");
			progress_bar_change_color = true;//��ֻ֤�л�һ��������ɫ
		}
		else
		{

		}
		ui.progressBar->setValue((int)progress_bar_value);//��������ʾ
	}

	void LockNormalSingleKey::receive_unlock_DES_final(bool is_success)//DES���ܽ���������Ϊdll������ָ��
	{
		ui.progressBar->setValue(0);//��������ʾ��Сֵ
		progress_bar_change_color = false;//��ֻ֤�л�һ��������ɫ
		ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");
		if (is_success == true)
		{

		}
		else
		{
			Help dialog;//��ʾ������Ϣ
			dialog.set_dialog_information_path(DIALOG_INFORMATION_UNLOCK_FAIL_PATH_STRING);
			dialog.setWindowTitle(tr("����ʧ���ˡ���"));
			dialog.exec();
		}
	}

	void LockNormalSingleKey::receive_lock_DES_EDE2_process(double index)//DES-EDE2���ܽ�������ʾ������Ϊ�Ѵ����ֱ���
	{
		receive_lock_DES_process(index);
	}

	void LockNormalSingleKey::receive_lock_DES_EDE2_final(bool is_success, char *key)//DES-EDE2���ܽ���������Ϊdll������ָ��
	{
		ui.progressBar->setValue(0);//��������ʾ��Сֵ
		progress_bar_change_color = false;//��ֻ֤�л�һ��������ɫ
		ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");
		if (is_success == true)
		{
			QByteArray key_hex_string(key, DES_EDE2::DEFAULT_KEYLENGTH);//����Կת��ΪQBytearray
			key_hex_string = key_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			ui.lineEdit_1->setText((QString)key_hex_string);//��������ʾ���ɵ���Կ
		}
		else
		{
			Help dialog;//��ʾ������Ϣ
			dialog.set_dialog_information_path(DIALOG_INFORMATION_LOCK_FAIL_PATH_STRING);
			dialog.setWindowTitle(tr("����ʧ���ˡ���"));
			dialog.exec();
		}
	}

	void LockNormalSingleKey::receive_unlock_DES_EDE2_process(double index)//DES-EDE2�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
	{
		receive_unlock_DES_process(index);
	}

	void LockNormalSingleKey::receive_unlock_DES_EDE2_final(bool is_success)//DES-EDE2���ܽ���������Ϊdll������ָ��
	{
		receive_unlock_DES_final(is_success);
	}

	void LockNormalSingleKey::receive_lock_DES_EDE3_process(double index)//DES-EDE3���ܽ�������ʾ������Ϊ�Ѵ����ֱ���
	{
		receive_lock_DES_process(index);
	}

	void LockNormalSingleKey::receive_lock_DES_EDE3_final(bool is_success, char *key)//DES-EDE3���ܽ���������Ϊdll������ָ��
	{
		ui.progressBar->setValue(0);//��������ʾ��Сֵ
		progress_bar_change_color = false;//��ֻ֤�л�һ��������ɫ
		ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");
		if (is_success == true)
		{
			QByteArray key_hex_string(key, DES_EDE3::DEFAULT_KEYLENGTH);//����Կת��ΪQBytearray
			key_hex_string = key_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			ui.lineEdit_1->setText((QString)key_hex_string);//��������ʾ���ɵ���Կ
		}
		else
		{
			Help dialog;//��ʾ������Ϣ
			dialog.set_dialog_information_path(DIALOG_INFORMATION_LOCK_FAIL_PATH_STRING);
			dialog.setWindowTitle(tr("����ʧ���ˡ���"));
			dialog.exec();
		}
	}

	void LockNormalSingleKey::receive_unlock_DES_EDE3_process(double index)//DES-EDE3�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
	{
		receive_unlock_DES_process(index);
	}

	void LockNormalSingleKey::receive_unlock_DES_EDE3_final(bool is_success)//DES-EDE3���ܽ���������Ϊdll������ָ��
	{
		receive_unlock_DES_final(is_success);
	}

	void LockNormalSingleKey::receive_lock_AES_MIN_process(double index)//AES-128���ܽ�������ʾ������Ϊ�Ѵ����ֱ���
	{
		receive_lock_DES_process(index);
	}

	void LockNormalSingleKey::receive_lock_AES_MIN_final(bool is_success, char *key)//AES-128���ܽ���������Ϊdll������ָ��
	{
		ui.progressBar->setValue(0);//��������ʾ��Сֵ
		progress_bar_change_color = false;//��ֻ֤�л�һ��������ɫ
		ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");
		if (is_success == true)
		{
			QByteArray key_hex_string(key, AES::MIN_KEYLENGTH);//����Կת��ΪQBytearray
			key_hex_string = key_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			ui.lineEdit_1->setText((QString)key_hex_string);//��������ʾ���ɵ���Կ
		}
		else
		{
			Help dialog;//��ʾ������Ϣ
			dialog.set_dialog_information_path(DIALOG_INFORMATION_LOCK_FAIL_PATH_STRING);
			dialog.setWindowTitle(tr("����ʧ���ˡ���"));
			dialog.exec();
		}
	}

	void LockNormalSingleKey::receive_unlock_AES_MIN_process(double index)//AES-128�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
	{
		receive_unlock_DES_process(index);
	}

	void LockNormalSingleKey::receive_unlock_AES_MIN_final(bool is_success)//AES-128���ܽ���������Ϊdll������ָ��
	{
		receive_unlock_DES_final(is_success);
	}

	void LockNormalSingleKey::receive_lock_AES_MIDDLE_process(double index)//AES-256���ܽ�������ʾ������Ϊ�Ѵ����ֱ���
	{
		receive_lock_DES_process(index);
	}

	void LockNormalSingleKey::receive_lock_AES_MIDDLE_final(bool is_success, char *key)//AES-256���ܽ���������Ϊdll������ָ��
	{
		ui.progressBar->setValue(0);//��������ʾ��Сֵ
		progress_bar_change_color = false;//��ֻ֤�л�һ��������ɫ
		ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");
		if (is_success == true)
		{
			QByteArray key_hex_string(key, FILE_KEY_AES_MIDDLE_KEY_LENGTH);//����Կת��ΪQBytearray
			key_hex_string = key_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			ui.lineEdit_1->setText((QString)key_hex_string);//��������ʾ���ɵ���Կ
		}
		else
		{
			Help dialog;//��ʾ������Ϣ
			dialog.set_dialog_information_path(DIALOG_INFORMATION_LOCK_FAIL_PATH_STRING);
			dialog.setWindowTitle(tr("����ʧ���ˡ���"));
			dialog.exec();
		}
	}

	void LockNormalSingleKey::receive_unlock_AES_MIDDLE_process(double index)//AES-256�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
	{
		receive_unlock_DES_process(index);
	}

	void LockNormalSingleKey::receive_unlock_AES_MIDDLE_final(bool is_success)//AES-256���ܽ���������Ϊdll������ָ��
	{
		receive_unlock_DES_final(is_success);
	}

	void LockNormalSingleKey::receive_lock_AES_MAX_process(double index)//AES-256���ܽ�������ʾ������Ϊ�Ѵ����ֱ���
	{
		receive_lock_DES_process(index);
	}

	void LockNormalSingleKey::receive_lock_AES_MAX_final(bool is_success, char *key)//AES-256���ܽ���������Ϊdll������ָ��
	{
		ui.progressBar->setValue(0);//��������ʾ��Сֵ
		progress_bar_change_color = false;//��ֻ֤�л�һ��������ɫ
		ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");
		if (is_success == true)
		{
			QByteArray key_hex_string(key, AES::MAX_KEYLENGTH);//����Կת��ΪQBytearray
			key_hex_string = key_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
			ui.lineEdit_1->setText((QString)key_hex_string);//��������ʾ���ɵ���Կ
		}
		else
		{
			Help dialog;//��ʾ������Ϣ
			dialog.set_dialog_information_path(DIALOG_INFORMATION_LOCK_FAIL_PATH_STRING);
			dialog.setWindowTitle(tr("����ʧ���ˡ���"));
			dialog.exec();
		}
	}

	void LockNormalSingleKey::receive_unlock_AES_MAX_process(double index)//AES-256�����ļ���������ʾ������Ϊ�Ѵ����ֱ���
	{
		receive_unlock_DES_process(index);
	}

	void LockNormalSingleKey::receive_unlock_AES_MAX_final(bool is_success)//AES-256���ܽ���������Ϊdll������ָ��
	{
		receive_unlock_DES_final(is_success);
	}

	//�������߳��ຯ��
	Lock_single_file_thread::Lock_single_file_thread()
	{

	}

	Lock_single_file_thread::~Lock_single_file_thread()
	{

	}

	void Lock_single_file_thread::get_data(string *string_array, bool *bool_array, char *char_array, char *key, QString method)//��ȡȫ������
	{
		this->string_array[0] = string_array[0];
		this->string_array[1] = string_array[1];
		this->string_array[2] = string_array[2];
		this->string_array[3] = string_array[3];
		this->string_array[4] = string_array[4];
		this->string_array[5] = string_array[5];
		this->string_array[6] = string_array[6];
		this->string_array[7] = string_array[7];
		this->bool_array[0] = bool_array[0];
		this->bool_array[1] = bool_array[1];
		this->bool_array[2] = bool_array[2];
		this->bool_array[3] = bool_array[3];
		this->bool_array[4] = bool_array[4];
		this->char_array = char_array;
		this->key = key;
		this->method = method;
	}

	void Lock_single_file_thread::get_target_class_point(Export_LockSingle_virtual_class *point)//��ȡdll���������ָ��
	{
		this->target_class_point = point;
	}

	void Lock_single_file_thread::get_dll_name(HINSTANCE dll_name)//��ȡdll��
	{
		this->dll_name = dll_name;
	}

	void Lock_single_file_thread::run()//���߳�������
	{
		mutex.lock();
		if (method == tr("DES"))//DES����
		{
			target_class_point->lock_DES(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[1], bool_array[2], string_array[5], string_array[6], bool_array[3], char_array, key, bool_array[4]);//�����ļ����ҷ����Ƿ�ɹ�������ʹ��string��������Ϊ��Ὣ'\0'��Ϊ������־�����ǡ���С�00���ֶ������������ݻᱻֱ�Ӻ��ԡ�����DES������Ҫ���㲻��һ�����ܵ�λ�Ĳ��֣���ѡ�񲻼��������һ�����ܵ�λ�����ݿ飬�����������ĺ����ĳ��Ȳ���ͬ
		}
		else if (method == tr("2-Key 3DES"))//DES_EDE2����
		{
			target_class_point->lock_DES_EDE2(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[1], bool_array[2], string_array[5], string_array[6], bool_array[3], char_array, key, bool_array[4]);
		}
		else if (method == tr("3-Key 3DES"))//DES_EDE3����
		{
			target_class_point->lock_DES_EDE3(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[1], bool_array[2], string_array[5], string_array[6], bool_array[3], char_array, key, bool_array[4]);
		}
		else if (method == tr("AES-128"))//AES-128����
		{
			target_class_point->lock_AES_MIN(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[1], bool_array[2], string_array[5], string_array[6], bool_array[3], char_array, key, bool_array[4]);
		}
		else if (method == tr("AES-192"))//AES-192����
		{
			target_class_point->lock_AES_MIDDLE(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[1], bool_array[2], string_array[5], string_array[6], bool_array[3], char_array, key, bool_array[4]);
		}
		else if (method == tr("AES-256"))//AES-256����
		{
			target_class_point->lock_AES_MAX(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[1], bool_array[2], string_array[5], string_array[6], bool_array[3], char_array, key, bool_array[4]);
		}
		else
		{
			target_class_point->lock_DES(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[1], bool_array[2], string_array[5], string_array[6], bool_array[3], char_array, key, bool_array[4]);//�����ļ����ҷ����Ƿ�ɹ�������ʹ��string��������Ϊ��Ὣ'\0'��Ϊ������־�����ǡ���С�00���ֶ������������ݻᱻֱ�Ӻ��ԡ�����DES������Ҫ���㲻��һ�����ܵ�λ�Ĳ��֣���ѡ�񲻼��������һ�����ܵ�λ�����ݿ飬�����������ĺ����ĳ��Ȳ���ͬ
		}
		FreeLibrary(dll_name);
		mutex.unlock();
		this->quit();//�˳����߳�
	}

	Unlock_single_file_thread::Unlock_single_file_thread()
	{

	}

	Unlock_single_file_thread::~Unlock_single_file_thread()
	{

	}

	void Unlock_single_file_thread::run()//���߳�������
	{
		mutex.lock();
		if (method == tr("DES"))//DES����
		{
			target_class_point->unlock_DES(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[3], char_array, key, bool_array[4]);//�����ļ����ҷ����Ƿ�ɹ�������ʹ��string��������Ϊ��Ὣ'\0'��Ϊ������־�����ǡ���С�00���ֶ������������ݻᱻֱ�Ӻ���
		}
		else if (method == tr("2-Key 3DES"))//DES_EDE2����
		{
			target_class_point->unlock_DES_EDE2(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[3], char_array, key, bool_array[4]);//�����ļ����ҷ����Ƿ�ɹ�������ʹ��string��������Ϊ��Ὣ'\0'��Ϊ������־�����ǡ���С�00���ֶ������������ݻᱻֱ�Ӻ���
		}
		else if (method == tr("3-Key 3DES"))//DES_EDE3����
		{
			target_class_point->unlock_DES_EDE3(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[3], char_array, key, bool_array[4]);//�����ļ����ҷ����Ƿ�ɹ�������ʹ��string��������Ϊ��Ὣ'\0'��Ϊ������־�����ǡ���С�00���ֶ������������ݻᱻֱ�Ӻ���
		}
		else if (method == tr("AES-128"))//AES_MIN����
		{
			target_class_point->unlock_AES_MIN(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[3], char_array, key, bool_array[4]);//�����ļ����ҷ����Ƿ�ɹ�������ʹ��string��������Ϊ��Ὣ'\0'��Ϊ������־�����ǡ���С�00���ֶ������������ݻᱻֱ�Ӻ���
		}
		else if (method == tr("AES-192"))//AES_MIN����
		{
			target_class_point->unlock_AES_MIDDLE(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[3], char_array, key, bool_array[4]);//�����ļ����ҷ����Ƿ�ɹ�������ʹ��string��������Ϊ��Ὣ'\0'��Ϊ������־�����ǡ���С�00���ֶ������������ݻᱻֱ�Ӻ���
		}
		else if (method == tr("AES-256"))//AES_MIN����
		{
			target_class_point->unlock_AES_MAX(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[3], char_array, key, bool_array[4]);//�����ļ����ҷ����Ƿ�ɹ�������ʹ��string��������Ϊ��Ὣ'\0'��Ϊ������־�����ǡ���С�00���ֶ������������ݻᱻֱ�Ӻ���
		}
		else
		{
			target_class_point->unlock_DES(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[3], char_array, key, bool_array[4]);//�����ļ����ҷ����Ƿ�ɹ�������ʹ��string��������Ϊ��Ὣ'\0'��Ϊ������־�����ǡ���С�00���ֶ������������ݻᱻֱ�Ӻ���
		}
		FreeLibrary(dll_name);
		mutex.unlock();
		this->quit();//�˳����߳�
	}
}

