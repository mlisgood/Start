#include "define.h"

namespace rem
{
	//��������������
	SoundRecordSet::SoundRecordSet(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�

		//����ͼƬ��Ϊ���ڱ���
		main_picture.load(DIALOG_TOOLS_SOUND_RECORD_SET_BACKGROUND_PICTURE_PATH_STRING);
		resize(main_picture.size());//���ڴ�С��ΪͼƬ��С

		//���ؽ���
		ui.setupUi(this);
		
		//����������ɫ
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::WindowText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::Highlight, QColor(70, 28, 10, 64));
		ui.comboBox_1->setPalette(text_palette);
		ui.comboBox_2->setPalette(text_palette);
		ui.lineedit->setPalette(text_palette);
		

		//ȥ�������Կؼ����Ҽ��˵�
		QList<QScrollBar *> scroll_bar = this->findChildren<QScrollBar *>();//�����޷��ó��淽ʽ���combobox�Ĺ����������ʹ�ø÷�����������ͬ���Ϳؼ������в���
		foreach(QScrollBar *scroll_bar_style_control, scroll_bar)
		{
			scroll_bar_style_control->setContextMenuPolicy(Qt::NoContextMenu);
		}

		//��ȡ¼���豸��������Ͽ�
		QVector<QString> audio_device_list_vector;
		foreach(QAudioDeviceInfo device_info, QAudioDeviceInfo::availableDevices(QAudio::AudioInput))
		{
			QString device_name = device_info.deviceName();
			if (device_info.isNull())
			{
				continue;
			}
			else
			{

			}
			bool have_find = false;
			foreach(QString have_find_device, audio_device_list_vector)
			{
				if (device_name == have_find_device)
				{
					have_find = true;
				}
				else
				{

				}
			}
			if (have_find == true)
			{
				continue;
			}
			else
			{

			}
			audio_device_list_vector.push_back(device_name);
			ui.comboBox_1->addItem(device_name);
		}

		//��ȡԤ�����ݣ��Դ�����ʾ���г�ʼ��
		QSettings *begin_read = new QSettings(FILE_SETTING_SOUND_RECORD_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		QString combobox_index[2];//��ȡcombobox��Ҫ������
		combobox_index[0] = (begin_read->value(FILE_SOUND_RECORD_SETTING_CATALOG_1_INNER_PATH_STRING)).toString();
		combobox_index[1] = (begin_read->value(FILE_SOUND_RECORD_SETTING_CATALOG_2_INNER_PATH_STRING)).toString();
		ui.comboBox_1->setCurrentText(combobox_index[0]);//��������
		ui.comboBox_2->setCurrentText(combobox_index[1]);
		QString label_index;
		label_index = (begin_read->value(FILE_SOUND_RECORD_SETTING_CATALOG_3_INNER_PATH_STRING)).toString();
		ui.lineedit->setText(label_index);
		if (label_index.length() == 0)//���������ļ���ʧ�����
		{
			ui.lineedit->setText(tr("#default#"));
		}
		else
		{

		}
		delete begin_read;

		//�źź���
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//������Ч
		connect(ui.pushButton_choose, SIGNAL(clicked()), this, SLOT(set_save_path()));//ѡ��·��
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//ȡ������

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}

	SoundRecordSet::~SoundRecordSet()
	{

	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void SoundRecordSet::mousePressEvent(QMouseEvent *event)
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
	void SoundRecordSet::mouseMoveEvent(QMouseEvent *event)
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
	void SoundRecordSet::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void SoundRecordSet::keyPressEvent(QKeyEvent *event)
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

	void SoundRecordSet::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(WINDOW_BACKGROUND_PAINT_START_X_NUMBER, WINDOW_BACKGROUND_PAINT_START_Y_NUMBER, main_picture);//��ͼ��Ϊ���ڱ���
	}

	//�ۺ���
	void SoundRecordSet::set_apply()//������Ч
	{

		//д��ini�ļ�
		QSettings *write_setting = new QSettings(FILE_SETTING_SOUND_RECORD_PATH_STRING, QSettings::IniFormat);
		QString combobox_index[2];//д��combobox������
		combobox_index[0] = ui.comboBox_1->currentText();
		combobox_index[1] = ui.comboBox_2->currentText();
		write_setting->setValue(FILE_SOUND_RECORD_SETTING_CATALOG_1_INNER_PATH_STRING, combobox_index[0]);
		write_setting->setValue(FILE_SOUND_RECORD_SETTING_CATALOG_2_INNER_PATH_STRING, combobox_index[1]);
		QString label_index=ui.lineedit->text();//д��ineeit������
		write_setting->setValue(FILE_SOUND_RECORD_SETTING_CATALOG_3_INNER_PATH_STRING, label_index);
		ui.lineedit->setText(label_index);
		delete write_setting;
		close_window_include_animation();//���ý���
	}

	void SoundRecordSet::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

	void SoundRecordSet::set_save_path()
	{
		File_only_path dialog;//��������Ǵ�Notepad.exe���õģ����÷�ʽ�Ƚ��鷳
		dialog.setWindowTitle(tr("ѡ��·��"));
		QString file_dialog_file_name = QDir::currentPath();//��ǰ·�������ڻ�ñ��򿪵��ļ�·��
		QFileInfo file_information(file_dialog_file_name);//��ȡ�ļ���Ϣ
		if (file_information.isFile())//���ļ�����
		{
			file_dialog_file_name = file_information.path();//ֻȡ�ļ�·��
		}
		else
		{

		}
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//ȷ���Ƿ���Ҫ�޸�·����ֻ�е��ȷ���Ż��޸�
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//�������ļ�·���ı���
		dialog.set_file_dialog_status_address(change_result_address);//�������Ƿ���Ҫ�޸�·���ı���
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//���빤��·��
		dialog.exec();
		if (change_result)
		{
			QFileInfo file_information(file_dialog_file_name);//��ȡ�ļ���Ϣ
			if (file_information.isFile())//���ļ�����
			{
				file_dialog_file_name = file_information.absoluteDir().absolutePath();//ֻȡ�ļ�·��
				file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));//����ļ�·��
				ui.lineedit->setText(file_dialog_file_name);//������ʾ�ı�
			}
			else if(!file_information.isDir())
			{
				Help dialog;//��Ϣ��ʾ��
				dialog.setWindowTitle(tr("�ļ����ļ�·��������"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//��ʾ��Ϣ
				dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
			}
			else
			{
				file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));//����ļ�·��
				ui.lineedit->setText(file_dialog_file_name);//������ʾ�ı�
			}
		}
		else
		{

		}
	}
}