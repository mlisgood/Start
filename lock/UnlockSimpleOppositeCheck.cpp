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
	UnlockSimpleOppositeCheck::UnlockSimpleOppositeCheck(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����					
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�

		//����ͼƬ��Ϊ���ڱ���
		main_picture.load(DIALOG_BACKGROUND_UNLOCK_SIMPLE_OPPOSITE_CHECK_PATH_STRING);
		resize(main_picture.size());//���ڴ�С��ΪͼƬ��С

		//���ؽ���
		ui.setupUi(this);

		//�źź���
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//������Ч
		connect(ui.pushButton_import, SIGNAL(clicked()), this, SLOT(import_set()));//��������
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(cancel_apply()));//ȡ������

		//���ð�ť��ʽ
		ui.pushButton_import->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_4.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_4.png);}");
		ui.pushButton_apply->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_5.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_5.png);}");
		ui.pushButton_cancel->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_6.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_6.png);}");

		//����������ɫ
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::WindowText, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::Highlight, QColor(128, 76, 71, 64));
		ui.label_show_1->setPalette(text_palette);
		ui.label_show_2->setPalette(text_palette);
		ui.label_show_3->setPalette(text_palette);
		ui.label_show_4->setPalette(text_palette);
		ui.label_show_5->setPalette(text_palette);

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}
	UnlockSimpleOppositeCheck::~UnlockSimpleOppositeCheck()
	{
		
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void UnlockSimpleOppositeCheck::mousePressEvent(QMouseEvent *event)
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
	void UnlockSimpleOppositeCheck::mouseMoveEvent(QMouseEvent *event)
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
	void UnlockSimpleOppositeCheck::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void UnlockSimpleOppositeCheck::keyPressEvent(QKeyEvent *event)
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

	void UnlockSimpleOppositeCheck::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//��ͼ��Ϊ���ڱ���
	}

	//���ó�Ա����
	void UnlockSimpleOppositeCheck::set_information(int *direction, long long *head_offset, long long *tail_offset, long long *cycle, QString *head_digit, bool *have_head_digit, bool *is_continue)//������Ҫ��ʾ�ڽ����ϵ���Ϣ������Ϊ�����ܷ���1��˳����ܣ�2��������ܣ�3��˫����ܣ���ͷ�������ֽڣ�β�������ֽڣ������ļ�ͷ���������֣��Ƿ���ͷ����������
	{
		long_long_information[0] = head_offset;//ͷ�������ֽ�
		long_long_information[1] = tail_offset;//β�������ֽ�
		long_long_information[2] = cycle;//��������
		char_point_information = head_digit;//ͷ����������
		int_information = direction;//���ܷ���
		bool_information = have_head_digit;//�Ƿ���ͷ����������
		this->is_continue = is_continue;//������ȷ�ϣ���������������н��ܲ���������ִ���κβ���
		if (*int_information == 1)//��ʾ���ܷ�������Ϊ˳�����
		{
			ui.label_show_1->setText(DIALOG_LOCK_SIMPLE_DIRECTION_RIGHT_STRING);
		}
		else if (*int_information == 2)//�������
		{
			ui.label_show_1->setText(DIALOG_LOCK_SIMPLE_DIRECTION_LEFT_STRING);
		}
		else//˫�������
		{
			ui.label_show_1->setText(DIALOG_LOCK_SIMPLE_DIRECTION_RIGHT_AND_LEFT_STRING);
		}
		ui.label_show_2->setText(QString::number(*head_offset, 10));//��ʾͷ�������ֽ�
		ui.label_show_3->setText(QString::number(*tail_offset, 10));//��ʾβ�������ֽ�
		ui.label_show_4->setText(QString::number(*cycle, 10));//��ʾѭ������
		if (*bool_information)//��ͷ����������
		{
			ui.label_show_5->setText(*head_digit);//��ʾ��������
		}
		else
		{
			ui.label_show_5->setText(DIALOG_LOCK_SIMPLE_DIRECTION_NO_HEAD_DIGIT_STRING);//��ʾ������������Ϣ
		}
		set_information_data(*direction, *head_offset, *tail_offset, *cycle, *head_digit, *have_head_digit);//�Ƚ����ݴ�������Դ��ĳ�Ա�����У����������Կ�ļ��ٸ���
	}

	void UnlockSimpleOppositeCheck::set_information_data(int direction, long long head_offset, long long tail_offset, long long cycle, QString head_digit, bool have_head_digit)//������Ҫ��ʾ�ڽ����ϵ���Ϣ�������ٴ���ָ�룬��֮��ʹ�á������֮��ʹ��ָ�봫�ݣ�������ָ��ָ��ĵ�ַ�ı䣬��ô��ȷ�Ϻ��޷��޸���������������Ե�ֵ
	{
		long_long_information_data[0] = head_offset;//ͷ�������ֽ�
		long_long_information_data[1] = tail_offset;//β�������ֽ�
		long_long_information_data[2] = cycle;//��������
		char_point_information_data = head_digit;//ͷ����������
		int_information_data = direction;//���ܷ���
		bool_information_data = have_head_digit;//�Ƿ���ͷ����������
		if (int_information_data == 1)//��ʾ���ܷ�������Ϊ˳�����
		{
			ui.label_show_1->setText(DIALOG_LOCK_SIMPLE_DIRECTION_RIGHT_STRING);
		}
		else if (int_information_data == 2)//�������
		{
			ui.label_show_1->setText(DIALOG_LOCK_SIMPLE_DIRECTION_LEFT_STRING);
		}
		else//˫�������
		{
			ui.label_show_1->setText(DIALOG_LOCK_SIMPLE_DIRECTION_RIGHT_AND_LEFT_STRING);
		}
		ui.label_show_2->setText(QString::number(head_offset, 10));//��ʾͷ�������ֽ�
		ui.label_show_3->setText(QString::number(tail_offset, 10));//��ʾβ�������ֽ�
		ui.label_show_4->setText(QString::number(cycle, 10));//��ʾѭ������
		if (bool_information_data)//��ͷ����������
		{
			ui.label_show_5->setText(head_digit);//��ʾ��������
		}
		else
		{
			ui.label_show_5->setText(DIALOG_LOCK_SIMPLE_DIRECTION_NO_HEAD_DIGIT_STRING);//��ʾ������������Ϣ
		}
	}

	void UnlockSimpleOppositeCheck::set_apply()//������Ч
	{
		*char_point_information = char_point_information_data;//���õ���ֵ����ָ�룬�Ա����޸���������ر�����ֵ
		*long_long_information[0] = long_long_information_data[0];
		*long_long_information[1] = long_long_information_data[1];
		*long_long_information[2] = long_long_information_data[2];
		*bool_information = bool_information_data;
		*int_information = int_information_data;
		*is_continue = true;//���ȷ�ϣ���������������н��ܲ���
		close_window_include_animation();//�رմ���
	}

	void UnlockSimpleOppositeCheck::cancel_apply()//����ȡ��
	{
		*is_continue = false;//���ȡ������ִ���κβ���
		close_window_include_animation();//�رմ���
	}

	void UnlockSimpleOppositeCheck::import_set()//��������
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
					if (type_number_digit != FILE_KEY_WRITE_BINARY_TYPE_1_NUMBER)//���Ǽ�ȡ��
					{
						Help dialog;//��ʾ������Ϣ
						dialog.set_dialog_information_path(DIALOG_INFORMATION_OPEN_WRONG_KEYFILE_PATH_STRING);
						dialog.setWindowTitle(tr("���˴�����ļ�����"));
						dialog.exec();
					}
					else
					{
						keyfile.read((char*)&int_information_data, sizeof(int));//��ȡ���ܷ���
						seek_offset += sizeof(int);
						seek_offset += FILE_KEYFILR_INTERVAL_NUMBER_HEX_STRING_SIZE_NUMBER;//�ָ���
						keyfile.clear();//����ļ�������������޷���λ
						keyfile.seekg(seek_offset, ios_base::beg);//�ƶ��ļ�ָ��
						keyfile.read((char*)&long_long_information_data[0], sizeof(long long));//��ȡͷ�������ֽ�
						seek_offset += sizeof(long long);
						keyfile.read((char*)&long_long_information_data[1], sizeof(long long));//��ȡβ�������ֽ�
						seek_offset += sizeof(long long);
						keyfile.read((char*)&long_long_information_data[2], sizeof(long long));//��ȡѭ������
						seek_offset += sizeof(long long);
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
						set_information_data(int_information_data, long_long_information_data[0], long_long_information_data[1], long_long_information_data[2], char_point_information_data, bool_information_data);//�����޸ĺ���Ϣ����ʱ��������ָ�봫ֵ������������Ӧ����ָ���ַ�ĸı�
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

	void UnlockSimpleOppositeCheck::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

