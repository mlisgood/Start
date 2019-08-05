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
	UnlockNormalSingleCheck::UnlockNormalSingleCheck(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����					
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�

		//����ͼƬ��Ϊ���ڱ���
		main_picture.load(DIALOG_BACKGROUND_UNLOCK_NORMAL_SINGLE_CHECK_PATH_STRING);
		resize(main_picture.size());//���ڴ�С��ΪͼƬ��С

		//���ؽ���
		ui.setupUi(this);

		//�źź���
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//������Ч
		connect(ui.pushButton_import, SIGNAL(clicked()), this, SLOT(import_set()));//��������
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(cancel_apply()));//ȡ������

		//���ð�ť��ʽ
		ui.pushButton_import->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_14.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_14.png);}");
		ui.pushButton_apply->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_5.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_5.png);}");
		ui.pushButton_cancel->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_6.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_6.png);}");

		//����������ɫ
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::WindowText, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::Highlight, QColor(128, 76, 71, 64));
		ui.lineEdit_show_1->setPalette(text_palette);
		ui.lineEdit_show_2->setPalette(text_palette);

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}
	UnlockNormalSingleCheck::~UnlockNormalSingleCheck()
	{
		
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void UnlockNormalSingleCheck::mousePressEvent(QMouseEvent *event)
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
	void UnlockNormalSingleCheck::mouseMoveEvent(QMouseEvent *event)
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
	void UnlockNormalSingleCheck::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void UnlockNormalSingleCheck::keyPressEvent(QKeyEvent *event)
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

	void UnlockNormalSingleCheck::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//��ͼ��Ϊ���ڱ���
	}

	//���ó�Ա����
	void UnlockNormalSingleCheck::set_information(QString method, QString *key, QString *head_digit, bool *have_head_digit, bool *is_continue)//������Ҫ��ʾ�ڽ����ϵ���Ϣ������Ϊ�����ܷ������ɶ���������ת��Ϊ�ı�����Կ�������ļ�ͷ���������֣��Ƿ���ͷ���������֣��Ƿ�ȷ�Ͻ���
	{
		if (method == tr("DES"))//DES����
		{
			ui.lineEdit_show_1->setMaxLength(DES::DEFAULT_KEYLENGTH * 2);
			ui.lineEdit_show_2->setMaxLength(DES::DEFAULT_KEYLENGTH * 2);
		}
		else if (method == tr("2-Key 3DES"))//DES-EDE2����
		{
			ui.lineEdit_show_1->setMaxLength(DES_EDE2::DEFAULT_KEYLENGTH * 2);
			ui.lineEdit_show_2->setMaxLength(DES_EDE2::DEFAULT_KEYLENGTH * 2);
		}
		else if (method == tr("3-Key 3DES"))//DES-EDE3����
		{
			ui.lineEdit_show_1->setMaxLength(DES_EDE3::DEFAULT_KEYLENGTH * 2);
			ui.lineEdit_show_2->setMaxLength(DES_EDE3::DEFAULT_KEYLENGTH * 2);
		}
		else if (method == tr("AES-128"))//AES-128����
		{
			ui.lineEdit_show_1->setMaxLength(AES::MIN_KEYLENGTH * 2);
			ui.lineEdit_show_2->setMaxLength(AES::MIN_KEYLENGTH * 2);
		}
		else if (method == tr("AES-192"))//AES-128����
		{
			ui.lineEdit_show_1->setMaxLength(FILE_KEY_AES_MIDDLE_KEY_LENGTH * 2);
			ui.lineEdit_show_2->setMaxLength(FILE_KEY_AES_MIDDLE_KEY_LENGTH * 2);
		}
		else if (method == tr("AES-256"))//AES-128����
		{
			ui.lineEdit_show_1->setMaxLength(AES::MAX_KEYLENGTH * 2);
			ui.lineEdit_show_2->setMaxLength(AES::MAX_KEYLENGTH * 2);
		}
		else
		{
			ui.lineEdit_show_1->setMaxLength(DES::DEFAULT_KEYLENGTH * 2);
			ui.lineEdit_show_2->setMaxLength(DES::DEFAULT_KEYLENGTH * 2);
		}
		char_point_information = head_digit;//ͷ����������
		bool_information = have_head_digit;//�Ƿ���ͷ����������
		this->is_continue = is_continue;//������ȷ�ϣ���������������н��ܲ���������ִ���κβ���
		if (*bool_information)//��ͷ����������
		{
			ui.lineEdit_show_2->setText(*head_digit);//��ʾ��������
		}
		else
		{
			ui.lineEdit_show_2->setText(DIALOG_LOCK_SIMPLE_DIRECTION_NO_HEAD_DIGIT_STRING);//��ʾ������������Ϣ
		}
		this->key = key;
		ui.lineEdit_show_1->setText(*key);
		this->method = method;//���ܷ���
		set_information_data(*key, *head_digit, *have_head_digit);//�Ƚ����ݴ�������Դ��ĳ�Ա�����У����������Կ�ļ��ٸ���
	}

	void UnlockNormalSingleCheck::set_information_data(QString key, QString head_digit, bool have_head_digit)//������Ҫ��ʾ�ڽ����ϵ���Ϣ�������ٴ���ָ�룬��֮��ʹ�á������֮��ʹ��ָ�봫�ݣ�������ָ��ָ��ĵ�ַ�ı䣬��ô��ȷ�Ϻ��޷��޸���������������Ե�ֵ
	{
		char_point_information_data = head_digit;//ͷ����������
		bool_information_data = have_head_digit;//�Ƿ���ͷ����������
		if (bool_information_data)//��ͷ����������
		{
			ui.lineEdit_show_2->setText(head_digit);//��ʾ��������
		}
		else
		{
			ui.lineEdit_show_2->setText(DIALOG_LOCK_SIMPLE_DIRECTION_NO_HEAD_DIGIT_STRING);//��ʾ������������Ϣ
		}
		key_data = key;
		ui.lineEdit_show_1->setText(key);
	}

	void UnlockNormalSingleCheck::set_apply()//������Ч
	{
		*char_point_information = char_point_information_data;//���õ���ֵ����ָ�룬�Ա����޸���������ر�����ֵ
		*bool_information = bool_information_data;
		*key = key_data;
		*is_continue = true;//���ȷ�ϣ���������������н��ܲ���
		close_window_include_animation();//�رմ���
	}

	void UnlockNormalSingleCheck::cancel_apply()//����ȡ��
	{
		*is_continue = false;//���ȡ������ִ���κβ���
		close_window_include_animation();//�رմ���
	}

	void UnlockNormalSingleCheck::import_set()//��������
	{
		File dialog;//ʹ�ô���ָ����׺���˵Ĵ��ļ�����
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
			string file_path = string((const char *)file_dialog_file_name.toLocal8Bit());//QStringתstring
			ifstream keyfile(file_path, ios_base::in | ios_base::binary | ios_base::beg);//�򿪶�������Կ�ļ�
			if (!keyfile.is_open())//�ļ���ʧ��
			{
				Help dialog;//��ʾ������Ϣ
				dialog.set_dialog_information_path(DIALOG_INFORMATION_KEYFILE_CANNOT_OPEN_PATH_STRING);
				dialog.setWindowTitle(tr("���ļ�ʧ�ܣ�"));
				dialog.exec();
			}
			else
			{
				char* magic_number = new char[FILE_KEYFILE_MAGIC_NUMBER_STRING_SIZE_NUMBER];//��ȡħ������
				keyfile.read(magic_number, FILE_KEYFILE_MAGIC_NUMBER_STRING_SIZE_NUMBER);
				QByteArray magic_number_hex_string(magic_number, FILE_KEYFILE_MAGIC_NUMBER_STRING_SIZE_NUMBER);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
				magic_number_hex_string = magic_number_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
				if (magic_number_hex_string != FILE_KEY_FILE_MAGIC_NUMBER_HEX_STRING)//������Կ�ļ���Ӧ��ħ��������ƥ��
				{
					Help dialog;//��ʾ������Ϣ
					dialog.set_dialog_information_path(DIALOG_INFORMATION_OPEN_WRONG_KEYFILE_PATH_STRING);
					dialog.setWindowTitle(tr("���˴�����ļ�����"));
					dialog.exec();
				}
				else
				{
					int seek_offset = FILE_KEYFILE_MAGIC_NUMBER_STRING_SIZE_NUMBER;//�ļ�ָ��ƫ����
					seek_offset += FILE_KEYFILR_INTERVAL_NUMBER_HEX_STRING_SIZE_NUMBER;//�ָ���
					keyfile.clear();//����ļ�������������޷���λ
					keyfile.seekg(seek_offset, ios_base::beg);//�ƶ��ļ�ָ��
					int type_number_digit;//��������
					keyfile.read((char*)&type_number_digit, sizeof(int));//��ȡ��������
					seek_offset += sizeof(int);
					if (type_number_digit != FILE_KEY_WRITE_BINARY_TYPE_3_NUMBER && method == tr("DES") || type_number_digit != FILE_KEY_WRITE_BINARY_TYPE_4_NUMBER && method == tr("2-Key 3DES") || type_number_digit != FILE_KEY_WRITE_BINARY_TYPE_5_NUMBER && method == tr("3-Key 3DES") || type_number_digit != FILE_KEY_WRITE_BINARY_TYPE_6_NUMBER && method == tr("AES-128") || type_number_digit != FILE_KEY_WRITE_BINARY_TYPE_7_NUMBER && method == tr("AES-192") || type_number_digit != FILE_KEY_WRITE_BINARY_TYPE_8_NUMBER && method == tr("AES-256"))//������ȷ�ļ�������
					{
						Help dialog;//��ʾ������Ϣ
						dialog.set_dialog_information_path(DIALOG_INFORMATION_OPEN_WRONG_KEYFILE_PATH_STRING);
						dialog.setWindowTitle(tr("���˴�����ļ�����"));
						dialog.exec();
					}
					else
					{
						seek_offset += FILE_KEYFILR_INTERVAL_NUMBER_HEX_STRING_SIZE_NUMBER;//�ָ���
						keyfile.clear();//����ļ�������������޷���λ
						keyfile.seekg(seek_offset, ios_base::beg);//�ƶ��ļ�ָ��
						if (method == tr("DES"))
						{
							char key_number[DES::DEFAULT_KEYLENGTH] = { 0 };//��ȡ��Կ���ݡ�������Ҫע�⣬�����������Ϊȫ�յ�ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char���顣���ң����ּ��ܷ�ʽ����Կ����������ͬ
							keyfile.read(key_number, DES::DEFAULT_KEYLENGTH);
							QByteArray key_number_hex_string(key_number, DES::DEFAULT_KEYLENGTH);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
							key_number_hex_string = key_number_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
							key_data = key_number_hex_string;
							seek_offset += DES::DEFAULT_KEYLENGTH;//�ָ���
						}
						else if(method == tr("2-Key 3DES"))
						{
							char key_number[DES_EDE2::DEFAULT_KEYLENGTH] = { 0 };//��ȡ��Կ���ݡ�������Ҫע�⣬�����������Ϊȫ�յ�ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char���顣���ң����ּ��ܷ�ʽ����Կ����������ͬ
							keyfile.read(key_number, DES_EDE2::DEFAULT_KEYLENGTH);
							QByteArray key_number_hex_string(key_number, DES_EDE2::DEFAULT_KEYLENGTH);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
							key_number_hex_string = key_number_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
							key_data = key_number_hex_string;
							seek_offset += DES_EDE2::DEFAULT_KEYLENGTH;//�ָ���
						}
						else if (method == tr("3-Key 3DES"))
						{
							char key_number[DES_EDE3::DEFAULT_KEYLENGTH] = { 0 };//��ȡ��Կ���ݡ�������Ҫע�⣬�����������Ϊȫ�յ�ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char���顣���ң����ּ��ܷ�ʽ����Կ����������ͬ
							keyfile.read(key_number, DES_EDE3::DEFAULT_KEYLENGTH);
							QByteArray key_number_hex_string(key_number, DES_EDE3::DEFAULT_KEYLENGTH);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
							key_number_hex_string = key_number_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
							key_data = key_number_hex_string;
							seek_offset += DES_EDE3::DEFAULT_KEYLENGTH;//�ָ���
						}
						else if (method == tr("AES-128"))
						{
							char key_number[AES::MIN_KEYLENGTH] = { 0 };//��ȡ��Կ���ݡ�������Ҫע�⣬�����������Ϊȫ�յ�ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char���顣���ң����ּ��ܷ�ʽ����Կ����������ͬ
							keyfile.read(key_number, AES::MIN_KEYLENGTH);
							QByteArray key_number_hex_string(key_number, AES::MIN_KEYLENGTH);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
							key_number_hex_string = key_number_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
							key_data = key_number_hex_string;
							seek_offset += AES::MIN_KEYLENGTH;//�ָ���
						}
						else if (method == tr("AES-192"))
						{
							char key_number[FILE_KEY_AES_MIDDLE_KEY_LENGTH] = { 0 };//��ȡ��Կ���ݡ�������Ҫע�⣬�����������Ϊȫ�յ�ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char���顣���ң����ּ��ܷ�ʽ����Կ����������ͬ
							keyfile.read(key_number, FILE_KEY_AES_MIDDLE_KEY_LENGTH);
							QByteArray key_number_hex_string(key_number, FILE_KEY_AES_MIDDLE_KEY_LENGTH);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
							key_number_hex_string = key_number_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
							key_data = key_number_hex_string;
							seek_offset += FILE_KEY_AES_MIDDLE_KEY_LENGTH;//�ָ���
						}
						else if (method == tr("AES-256"))
						{
							char key_number[AES::MAX_KEYLENGTH] = { 0 };//��ȡ��Կ���ݡ�������Ҫע�⣬�����������Ϊȫ�յ�ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char���顣���ң����ּ��ܷ�ʽ����Կ����������ͬ
							keyfile.read(key_number, AES::MAX_KEYLENGTH);
							QByteArray key_number_hex_string(key_number, AES::MAX_KEYLENGTH);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
							key_number_hex_string = key_number_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
							key_data = key_number_hex_string;
							seek_offset += AES::MAX_KEYLENGTH;//�ָ���
						}
						else
						{
							char key_number[DES::DEFAULT_KEYLENGTH] = { 0 };//��ȡ��Կ���ݡ�������Ҫע�⣬�����������Ϊȫ�յ�ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char���顣���ң����ּ��ܷ�ʽ����Կ����������ͬ
							keyfile.read(key_number, DES::DEFAULT_KEYLENGTH);
							QByteArray key_number_hex_string(key_number, DES::DEFAULT_KEYLENGTH);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
							key_number_hex_string = key_number_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
							key_data = key_number_hex_string;
							seek_offset += DES::DEFAULT_KEYLENGTH;//�ָ���
						}
						seek_offset += FILE_KEYFILR_INTERVAL_NUMBER_HEX_STRING_SIZE_NUMBER;//�ָ���
						keyfile.clear();//����ļ�������������޷���λ
						keyfile.seekg(seek_offset, ios_base::beg);//�ƶ��ļ�ָ��
						keyfile.read((char*)&bool_information_data_int, sizeof(int));//��ȡ�Ƿ���ͷ���������ֵ��ж���
						if (bool_information_data_int != 0)
						{
							seek_offset += sizeof(int);
							keyfile.clear();
							bool_information_data = true;
							char head_number[FILE_KEYFILE_HEAD_NUMBER_STRING_SIZE_NUMBER + 1] = {0};//��ȡ�������֡�������Ҫע�⣬�����������Ϊȫ�ռ���00000000����ʱ��ʹ�ö�̬�������������鳤��Ϊ0������������Ҫ�ù̶����ȵ�char����
							keyfile.read(head_number, FILE_KEYFILE_HEAD_NUMBER_STRING_SIZE_NUMBER);
							QByteArray head_number_hex_string(head_number, FILE_KEYFILE_HEAD_NUMBER_STRING_SIZE_NUMBER);//��ż����ļ�ͷ��ħ�����ֵ�ʮ����������
							head_number_hex_string = head_number_hex_string.toHex().toUpper();//���ʮ���������ݣ�ת��Ϊ��д
							char_point_information_data = head_number_hex_string;
						}
						else
						{
							bool_information_data = false;
							char_point_information_data = DIALOG_LOCK_SIMPLE_DIRECTION_NO_HEAD_DIGIT_STRING;
						}
						keyfile.close();
						set_information_data(key_data, char_point_information_data, bool_information_data);//�����޸ĺ���Ϣ����ʱ��������ָ�봫ֵ������������Ӧ����ָ���ַ�ĸı�
					}
				}
				delete magic_number;
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

	void UnlockNormalSingleCheck::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

