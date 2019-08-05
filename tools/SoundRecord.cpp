#include "define.h"

namespace rem
{

	//����ȫ�ֱ���
	extern int sound_record_mutex;

	//��������������
	SoundRecord::SoundRecord(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | windowFlags());//ȥ�����ڱ������������������в�����ִ���
		setAttribute(Qt::WA_TranslucentBackground, true);//�����ڱ���͸����
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		setAttribute(Qt::WA_DeleteOnClose);//�˳�ʱ���ٸô��������ڴ�й©
		setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);//����ʼ�������
		sound_record_mutex--;//����ļ�ʱ�����ڵ���Ŀ����1
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�
		is_save = true;//��ʼû��δ�����¼��
		is_wrong = false;//��ʼû�д���
		on_top = true;//��ʼʱ�������
		
		//���ؽ���
		ui.setupUi(this);

		//����ͼƬ��Ϊ���ڱ���
		main_picture.load(DIALOG_SOUND_RECORD_BACKGROUND_PICTURE_PATH_STRING);
		resize(DIALOG_SOUND_RECORD_NUMBER_PICTURE_WIDTH_NUMBER, DIALOG_SOUND_RECORD_NUMBER_PICTURE_HEIGHT_NUMBER);//���ڴ�С��ΪͼƬ��С���˴β�����ͼƬΪ�磬��Ϊ��Ҫ��������͸������

		//��ȡ�����ļ�
		QSettings *begin_read = new QSettings(FILE_SETTING_SOUND_RECORD_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		setting_string[0] = (begin_read->value(FILE_SOUND_RECORD_SETTING_CATALOG_1_INNER_PATH_STRING)).toString();
		setting_string[1] = (begin_read->value(FILE_SOUND_RECORD_SETTING_CATALOG_2_INNER_PATH_STRING)).toString();
		setting_string[2] = (begin_read->value(FILE_SOUND_RECORD_SETTING_CATALOG_3_INNER_PATH_STRING)).toString();
		delete begin_read;
		QFileInfo file_information(setting_string[2]);//����ļ�·���Ϸ���
		if (!file_information.isDir())//�����ļ�·��
		{
			if (setting_string[2] == FILE_SETTING_PATH_DEFAULT_SHOW_STRING)//Ĭ��·��
			{
				setting_string[2] = FILE_SETTING_PATH_DEFAULT_STRING;
			}
			else
			{
				Help dialog;//��Ϣ��ʾ��
				dialog.setWindowTitle(tr("�ļ�·������"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_SOUND_FILE_SAVE_PATH_STRING);//��ʾ��Ϣ
				dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
				is_wrong = true;
			}
		}
		else
		{

		}

		//�źź���
		connect(ui.pushButton_new, SIGNAL(clicked()), this, SLOT(new_file()));//�½�
		connect(ui.pushButton_save, SIGNAL(clicked()), this, SLOT(save_file()));//����

		//¼����ʽ
		audio_format.setByteOrder(QAudioFormat::LittleEndian);
		if (setting_string[1] == tr("mono"))//����������
		{
			audio_format.setChannelCount(1);
		}
		else
		{
			audio_format.setChannelCount(2);
			setting_string[1] == tr("stereo");
		}
		QAudioEncoderSettings audioSettings;
		audioSettings.setQuality(QMultimedia::VeryHighQuality);
		audio_format.setSampleRate(DIALOG_SETTING_SOUND_RECORD_RATE_DEFAULT_NUMBER);
		audio_format.setCodec("audio/pcm");
		audio_format.setSampleSize(16);
		audio_format.setSampleType(QAudioFormat::SignedInt);
		foreach(const QAudioDeviceInfo &device_info_set, QAudioDeviceInfo::availableDevices(QAudio::AudioInput))
		{
			if (device_info_set.deviceName() == setting_string[0])
			{
				device_info_set_final = device_info_set;
				break;
			}
			else
			{

			}
		}
		if (device_info_set_final.isNull())
		{
			Help dialog;//��Ϣ��ʾ��
			dialog.setWindowTitle(tr("�����豸ʧ��"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_DEVICE_PATH_STRING);//��ʾ��Ϣ
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
			is_wrong = true;
		}
		else
		{

		}
		if (!device_info_set_final.isFormatSupported(audio_format))//��ǰʹ���豸��֧�ָø�ʽ����ת��Ϊ��ӽ���֧�ָ�ʽ
		{
			audio_format = device_info_set_final.nearestFormat(audio_format); //ת��Ϊ��ӽ���ʽ
		}
		else
		{

		}
		audio_input = new QAudioInput(device_info_set_final, audio_format, this);//����¼����

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�

		if (is_wrong)//ǰ��Ĵ�����̳��ִ���ֱ���˳�
		{
			close_window_include_animation();
		}
		else
		{

		}
	}
	SoundRecord::~SoundRecord()
	{
		sound_record_mutex++;//�����¼�����ڵ���Ŀ����1
		delete audio_input;//�ͷ��ڴ�
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void SoundRecord::mousePressEvent(QMouseEvent *event)
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
	void SoundRecord::mouseMoveEvent(QMouseEvent *event)
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
	void SoundRecord::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//���˫���¼�
	void SoundRecord::mouseDoubleClickEvent(QMouseEvent *event)
	{
		if (on_top == false)
		{
			setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);//����������ʾ����ǰ��
			on_top = true;
		}
		else
		{
			setWindowFlags(windowFlags()&~Qt::WindowStaysOnTopHint);//���ڲ���������ʾ����ǰ��
			on_top = false;
		}
		show();//�����������һ�������⣬���細����Զ�޷���ʾ
	}

	//�����¼������ڽ�������
	void SoundRecord::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Escape)
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
	}

	void SoundRecord::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(WINDOW_BACKGROUND_PAINT_START_X_NUMBER, WINDOW_BACKGROUND_PAINT_START_Y_NUMBER, main_picture);//��ͼ��Ϊ���ڱ���
	}

	void SoundRecord::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
	{

		//�������а�ť�����򶯻��������ǰ�ٴε����ť�����´�������
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(false);
		}
		if (!is_save)//�������δ������ļ������ȱ���
		{
			save_file();
		}
		else
		{

		}
		QPropertyAnimation *animation_close = new QPropertyAnimation(this, "windowOpacity");
		animation_close->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//���ڹرն���Ч��
		animation_close->setStartValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation_close->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_close->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		connect(animation_close, SIGNAL(finished()), this, SLOT(close()));
	}

	void SoundRecord::new_file()//�½�
	{
		if (!is_save)//�Ѿ����棬��ʼ��һ¼����������Ҫ���ȴ���
		{
			save_file();
		}
		else
		{

		}
		is_save = false;//δ����
		QDateTime current_date_time = QDateTime::currentDateTime();//��ȡ��ǰʱ��
		QString current_date_string = setting_string[2];
		current_date_string += current_date_time.toString(FILE_SOUND_RECORD_TIME_FORMAT_STRING);
		output_file.setFileName(current_date_string + FILE_SOUND_RECORD_BACK_PATH_STRING); //����ԭʼ�ļ�
		output_file.open(QIODevice::WriteOnly);//¼����д���ļ�
		audio_input->start(&output_file);
	}
	void SoundRecord::save_file()//����
	{
		audio_input->stop();//ֹͣ¼��

		//����IO�豸�࣬����ֱ������
		QIODevice *device
		{
			nullptr
		};
		device = &output_file;

		//���wav�ļ�ͷ������ֱ������
		static WAVHEADER wavHeader;
		qstrcpy(wavHeader.RiffName, "RIFF");
		qstrcpy(wavHeader.WavName, "WAVE");
		qstrcpy(wavHeader.FmtName, "fmt ");
		qstrcpy(wavHeader.DATANAME, "data");
		wavHeader.nFmtLength = 16;
		int nAudioFormat = 1;
		wavHeader.nAudioFormat = nAudioFormat;
		wavHeader.nBitsPerSample = DIALOG_SETTING_SOUND_RECORD_BIT_DEFAULT_NUMBER;
		if (setting_string[1] == tr("mono"))//����������
		{
			wavHeader.nChannleNumber = 1;
		}
		else
		{
			wavHeader.nChannleNumber = 2;
		}
		wavHeader.nSampleRate = DIALOG_SETTING_SOUND_RECORD_RATE_DEFAULT_NUMBER;
		wavHeader.nBytesPerSample = wavHeader.nChannleNumber * wavHeader.nBitsPerSample / 8;
		wavHeader.nBytesPerSecond = wavHeader.nSampleRate * wavHeader.nChannleNumber *  wavHeader.nBitsPerSample / 8;
		wavHeader.nRiffLength = device->size() - 8;//�����ļ���С��ͷ��44�ֽڼ�����Ƶ���ݴ�С��-8��ע�������device->size()�Ѿ�������ͷ�����ݴ�С��������ݴ�С��д�����ò�����Ƶ��������򿪻ᱨ��
		wavHeader.nDataLength = device->size() - sizeof(WAVHEADER);//�����ļ�����Ƶ���ݴ�С

		//д��IO�豸ͷ������ֱ������
		device->seek(0);
		device->write(reinterpret_cast<char*>(&wavHeader), sizeof (WAVHEADER));

		//�ر��ļ��������ѱ�����
		output_file.close();
		device->close();
		is_save = true;//�ѱ���
	}
}

