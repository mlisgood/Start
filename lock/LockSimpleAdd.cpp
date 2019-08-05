#include "define.h"

namespace rem
{

	//ʹ�ñ�׼�����ռ�
	using std::string;

	//��������������
	LockSimpleAdd::LockSimpleAdd(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		resize(DIALOG_LOCK_SIZE_WIDTH_NUMBER, DIALOG_LOCK_SIZE_HEIGHT_NUMBER);//������ǿ�Ƹ�Ϊ�˴�С
		setFixedSize(this->width(), this->height());//��ֹ�ı䴰�ڴ�С
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ���˳�����
		is_escape_pressed = false;//������esc���˳�����
		for (int index = 0; index < DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER; index++)//��ʼ��int�ͼ��ܼӼ�������Ĭ�Ͼ�Ϊ0������Ĭ�����ֵ16
		{
			extra_digit_array[index] = 0;
		}
		extra_digit_array[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER] = DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER;

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
		ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_12.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_12.png);}");

		//�źź���
		connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(lock_file()));//�����ļ�
		connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(unlock_file()));//�����ļ�
		connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(digit_set()));//���üӼ�����
		connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//�����ϼ�����

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
		ui.lineEdit->setPalette(global_text_palette);
		ui.spinBox_1->setPalette(global_text_palette);
		ui.spinBox_2->setPalette(global_text_palette);
		ui.progressBar->setPalette(global_text_palette);

		//��������ɫ
		progress_bar_change_color = false;//�ļ���ʱ������������ɫδ�л�
		ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");

		//�ı���ֻ�����������ֺ���ĸ
		QRegExp regexp("[a-fA-F0-9]+$");//������ʽ��ֻ��������ʮ����������������ַ�
		validator = new QRegExpValidator(regexp, ui.lineEdit);//������Ҫʹ�õ�ģʽ
		ui.lineEdit->setValidator(validator);//Ӧ��ģʽ

		//������������Ч��
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�

	}
	LockSimpleAdd::~LockSimpleAdd()
	{
		delete timer;
		delete effect_1;
		delete effect_2;
		delete validator;
	}

	//���ó�Ա����
	void LockSimpleAdd::update_unlock_information(int direction, long long head_offset, long long tail_offset, int cycle, QString head_digit, bool have_head_digit, int *operate_count)//������Ҫ��ʾ�ڽ����ϵ���Ϣ������Ϊ�����ܷ���1��˳����ܣ�2��������ܣ�3��˫����ܣ���ͷ�������ֽڣ�β�������ֽڣ�ѭ�����ڣ������ļ�ͷ���������֣��Ƿ���ͷ���������֣��Ӽ�����
	{
		flag_array[0] = direction;//���ü��ܷ���
		if (flag_array[0]==1)//���ܷ�����
		{
			ui.radioButton_1->setChecked(true);
			ui.radioButton_2->setChecked(false);
		}
		else//���ܷ�����
		{
			ui.radioButton_1->setChecked(false);
			ui.radioButton_2->setChecked(true);
		}
		digit_array[0] = head_offset;//�������
		ui.spinBox_1->setValue(head_offset);
		digit_array[1] = tail_offset;//�����յ�
		ui.spinBox_2->setValue(tail_offset);
		extra_digit_array[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER] = cycle;//ѭ������
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
		for (int index = 0; index < cycle; index++)
		{
			extra_digit_array[index] = operate_count[index];
		}
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void LockSimpleAdd::mousePressEvent(QMouseEvent *event)
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
	void LockSimpleAdd::mouseMoveEvent(QMouseEvent *event)
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
	void LockSimpleAdd::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ������������Ϊֻ��ȷ�ϲ�������������Ҫ��д����Ϊ�˱���ͳһ�����ǽ�������д
	void LockSimpleAdd::keyPressEvent(QKeyEvent *event)
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

	void LockSimpleAdd::timer_timeout()//ʹ��2��label��������ͼƬ������ָ��һ����ʱ����������ʾͼƬ����ʱͼƬ���²�label���ϲ�labelʹ��ȫ͸��ͼƬ����������ԡ�ʱ�䵽�ں󣬸����л�ͼƬ͸������ʹ�õĶ�ʱ������ͬʱ��ʼ�޸�͸���ȼ������²�label��ʾԭʼͼƬ����͸�����𽥼�С���ϲ�label��ʾ�л���ͼƬ����͸���������ӡ����ϲ�labelͼƬ͸����Ϊ1ʱ���л�������ͼƬ��������1�����µĳ�ʱ�������¿�ʼ��һ��ʱѭ��
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

	void LockSimpleAdd::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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
		emit show_lock_simple_window();//������ʾ�ϼ������ź�
		connect(animation_close, SIGNAL(finished()), this, SLOT(close()));
	}

	void LockSimpleAdd::lock_file()//�����ļ�
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
			if (ui.radioButton_1->isChecked())//�洢int�ͱ����Ϣ
			{
				flag_array[0] = 1;
			}
			else
			{
				flag_array[0] = 2;
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
			digit_array[0] = ui.spinBox_1->value();//�洢long long����ֵ��Ϣ��������ͷ���������
			digit_array[1] = ui.spinBox_2->value();//β���������
			Lock_add_file_thread *thread = new Lock_add_file_thread();//�����ļ����߳�
			connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
			connect(this, SIGNAL(send_data(string*, bool*, long long*, int*, int*, char*)), thread, SLOT(get_data(string*, bool*, long long*, int*, int*, char*)));
			connect(this, SIGNAL(send_target_class_point(Export_LockSimple_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockSimple_virtual_class *)));
			connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
			emit send_data(string_array, bool_array, digit_array, flag_array, extra_digit_array, char_array);//��������
			using export_class = Export_LockSimple_virtual_class * (*)(void);//����ָ�򵼳�������ָ������
			HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_READ_PATH_STRING);//��̬����dll�����ҵ���ָ������Ķ���ָ�룬ͨ���źŴ��ݸ����߳�ʹ��
			ui.progressBar->setVisible(true);//��ʾ������
			ui.progressBar->setValue(0);//��������ʼֵΪ0
			progress_bar_change_color = false;//��ʼ����ʱ������������ɫδ�л�
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");//���ý�������ɫ
			if (dll_name != NULL)
			{
				emit send_dll_name(dll_name);//��Ϊ�����߳�ʹ����dll֮ǰ����ж��dll����ֻ��ͨ���źŽ�dll�����ݸ����߳�
				export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_simple");//ͨ������ָ���ĵ���������������Ҫ����
				if (get_class != NULL)
				{
					Export_LockSimple_virtual_class *target_class_object = get_class();//���Ŀ����Ķ���ָ��
					emit send_target_class_point(target_class_object);//����dll���������ָ��
					connect(target_class_object, SIGNAL(lock_simple_add_process(double)), this, SLOT(receive_lock_simple_add_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
					connect(target_class_object, SIGNAL(lock_simple_add_final(bool)), this, SLOT(receive_lock_simple_add_final(bool)));
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

	void LockSimpleAdd::unlock_file()//�����ļ�
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
			if (ui.radioButton_1->isChecked())//�洢int�ͱ����Ϣ
			{
				flag_array[0] = 1;
			}
			else
			{
				flag_array[0] = 2;
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
			digit_array[0] = ui.spinBox_1->value();//�洢long long����ֵ��Ϣ��������ͷ���������
			digit_array[1] = ui.spinBox_2->value();//β���������
			UnlockSimpleAddCheck dialog;//����ȷ�Ͻ�����Ϣ��
			is_continue = false;//�����Ƿ���Ҫ����һ����ִ������������
			dialog.set_information(&flag_array[0], &digit_array[0], &digit_array[1], &extra_digit_array[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER], &lineEdit_text, &bool_array[3], &is_continue, extra_digit_array);//�趨��ʼֵ
			dialog.exec();
			if (is_continue)//�ڽ���ȷ�ϴ��ڵ��ȷ�ϣ����������н��ܲ���
			{
				update_unlock_information(flag_array[0], digit_array[0], digit_array[1], extra_digit_array[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER], lineEdit_text, bool_array[3], extra_digit_array);//���´�������
				Unlock_add_file_thread *thread = new Unlock_add_file_thread;//�����ļ����߳�
				connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
				connect(this, SIGNAL(send_data(string*, bool*, long long*, int*, int*, char*)), thread, SLOT(get_data(string*, bool*, long long*, int*, int*, char*)));
				connect(this, SIGNAL(send_target_class_point(Export_LockSimple_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockSimple_virtual_class *)));
				connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
				emit send_data(string_array, bool_array, digit_array, flag_array, extra_digit_array, char_array);//��������
				using export_class = Export_LockSimple_virtual_class * (*)(void);//����ָ�򵼳�������ָ������
				HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_READ_PATH_STRING);//��̬����dll�����ҵ���ָ������Ķ���ָ�룬ͨ���źŴ��ݸ����߳�ʹ��
				ui.progressBar->setVisible(true);//��ʾ������
				ui.progressBar->setValue(0);//��������ʼֵΪ0
				progress_bar_change_color = false;//��ʼ����ʱ������������ɫδ�л�
				ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");//���ý�������ɫ
				if (dll_name != NULL)
				{
					emit send_dll_name(dll_name);//��Ϊ�����߳�ʹ����dll֮ǰ����ж��dll����ֻ��ͨ���źŽ�dll�����ݸ����߳�
					export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_simple");//ͨ������ָ���ĵ���������������Ҫ����
					if (get_class != NULL)
					{
						Export_LockSimple_virtual_class *target_class_object = get_class();//���Ŀ����Ķ���ָ��
						emit send_target_class_point(target_class_object);//����dll���������ָ��
						connect(target_class_object, SIGNAL(unlock_simple_add_process(double)), this, SLOT(receive_unlock_simple_add_process(double)));//�ú���Ҫ�����������������Ҫ�̳�QObject�ಢ�����к���Q_OBJECT��
						connect(target_class_object, SIGNAL(unlock_simple_add_final(bool)), this, SLOT(receive_unlock_simple_add_final(bool)));
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
			else//�ڽ���ȷ�ϴ��ڵ��ȡ�����������κβ���
			{

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

	void LockSimpleAdd::digit_set()//�Ӽ���������
	{
		LockSimpleAddGetDigit dialog;
		dialog.set_information(extra_digit_array);
		dialog.exec();
	}

	void LockSimpleAdd::receive_lock_simple_add_process(double index)//ȡ�������ļ���������ʾ������Ϊ�Ѵ����ֱ���
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

	void LockSimpleAdd::receive_lock_simple_add_final(bool is_success)//ȡ�������ļ�����������Ϊdll������ָ��
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
			dialog.set_dialog_information_path(DIALOG_INFORMATION_LOCK_FAIL_PATH_STRING);
			dialog.setWindowTitle(tr("����ʧ���ˡ���"));
			dialog.exec();
		}
	}

	void LockSimpleAdd::receive_unlock_simple_add_process(double index)//ȡ�������ļ���������ʾ������Ϊ�Ѵ����ֱ���
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

	void LockSimpleAdd::receive_unlock_simple_add_final(bool is_success)//ȡ�������ļ�����������Ϊdll������ָ��
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

	//�������߳��ຯ��
	Lock_add_file_thread::Lock_add_file_thread()
	{

	}

	Lock_add_file_thread::~Lock_add_file_thread()
	{

	}

	void Lock_add_file_thread::get_data(string *string_array, bool *bool_array, long long *digit_array, int *flag_array, int *extra_digit_array, char *char_array)//��ȡȫ�����ݣ�ע��ѭ�����ڴ洢��extra_digit_array�����һ����Ԫ
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
		this->digit_array[0] = digit_array[0];
		this->digit_array[1] = digit_array[1];
		this->extra_digit_array[0] = extra_digit_array[0];
		this->extra_digit_array[1] = extra_digit_array[1];
		this->extra_digit_array[2] = extra_digit_array[2];
		this->extra_digit_array[3] = extra_digit_array[3];
		this->extra_digit_array[4] = extra_digit_array[4];
		this->extra_digit_array[5] = extra_digit_array[5];
		this->extra_digit_array[6] = extra_digit_array[6];
		this->extra_digit_array[7] = extra_digit_array[7];
		this->extra_digit_array[8] = extra_digit_array[8];
		this->extra_digit_array[9] = extra_digit_array[9];
		this->extra_digit_array[10] = extra_digit_array[10];
		this->extra_digit_array[11] = extra_digit_array[11];
		this->extra_digit_array[12] = extra_digit_array[12];
		this->extra_digit_array[13] = extra_digit_array[13];
		this->extra_digit_array[14] = extra_digit_array[14];
		this->extra_digit_array[15] = extra_digit_array[15];
		this->flag_array[0] = flag_array[0];
		this->flag_array[1] = extra_digit_array[16];
		this->char_array = char_array;
	}

	void Lock_add_file_thread::get_target_class_point(Export_LockSimple_virtual_class *point)//��ȡdll���������ָ��
	{
		this->target_class_point = point;
	}

	void Lock_add_file_thread::get_dll_name(HINSTANCE dll_name)//��ȡdll��
	{
		this->dll_name = dll_name;
	}

	void Lock_add_file_thread::run()//���߳�������
	{
		mutex.lock();
		target_class_point->lock_add(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[1], bool_array[2], string_array[5], string_array[6], string_array[7], flag_array[0], digit_array[0], digit_array[1], flag_array[1], bool_array[3], char_array, extra_digit_array);//�����ļ����ҷ����Ƿ�ɹ�������ʹ��string��������Ϊ��Ὣ'\0'��Ϊ������־�����ǡ���С�00���ֶ������������ݻᱻֱ�Ӻ���
		FreeLibrary(dll_name);
		mutex.unlock();
		this->quit();//�˳����߳�
	}

	Unlock_add_file_thread::Unlock_add_file_thread()
	{

	}

	Unlock_add_file_thread::~Unlock_add_file_thread()
	{

	}

	void Unlock_add_file_thread::run()//���߳�������
	{
		mutex.lock();
		target_class_point->unlock_add(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], string_array[7], flag_array[0], digit_array[0], digit_array[1], flag_array[1], bool_array[3], char_array, extra_digit_array);//�����ļ����ҷ����Ƿ�ɹ�������ʹ��string��������Ϊ��Ὣ'\0'��Ϊ������־�����ǡ���С�00���ֶ������������ݻᱻֱ�Ӻ���
		FreeLibrary(dll_name);
		mutex.unlock();
		this->quit();//�˳����߳�
	}
}

