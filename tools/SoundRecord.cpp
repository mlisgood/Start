#include "define.h"

namespace rem
{

	//引用全局变量
	extern int sound_record_mutex;

	//构造与析构函数
	SoundRecord::SoundRecord(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | windowFlags());//去掉窗口标题栏，并且任务栏中不会出现窗口
		setAttribute(Qt::WA_TranslucentBackground, true);//将窗口背景透明化
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		setAttribute(Qt::WA_DeleteOnClose);//退出时销毁该窗口以免内存泄漏
		setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);//窗口始终在最顶层
		sound_record_mutex--;//允许的计时器窗口的数目减少1
		is_escape_pressed = false;//默认未按下esc键以退出
		is_save = true;//初始没有未保存的录音
		is_wrong = false;//初始没有错误
		on_top = true;//初始时刻在最顶层
		
		//加载界面
		ui.setupUi(this);

		//加载图片作为窗口背景
		main_picture.load(DIALOG_SOUND_RECORD_BACKGROUND_PICTURE_PATH_STRING);
		resize(DIALOG_SOUND_RECORD_NUMBER_PICTURE_WIDTH_NUMBER, DIALOG_SOUND_RECORD_NUMBER_PICTURE_HEIGHT_NUMBER);//窗口大小改为图片大小，此次不再以图片为界，因为需要保留部分透明区域

		//读取配置文件
		QSettings *begin_read = new QSettings(FILE_SETTING_SOUND_RECORD_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		setting_string[0] = (begin_read->value(FILE_SOUND_RECORD_SETTING_CATALOG_1_INNER_PATH_STRING)).toString();
		setting_string[1] = (begin_read->value(FILE_SOUND_RECORD_SETTING_CATALOG_2_INNER_PATH_STRING)).toString();
		setting_string[2] = (begin_read->value(FILE_SOUND_RECORD_SETTING_CATALOG_3_INNER_PATH_STRING)).toString();
		delete begin_read;
		QFileInfo file_information(setting_string[2]);//检查文件路径合法性
		if (!file_information.isDir())//不是文件路径
		{
			if (setting_string[2] == FILE_SETTING_PATH_DEFAULT_SHOW_STRING)//默认路径
			{
				setting_string[2] = FILE_SETTING_PATH_DEFAULT_STRING;
			}
			else
			{
				Help dialog;//信息提示框
				dialog.setWindowTitle(tr("文件路径有误"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_SOUND_FILE_SAVE_PATH_STRING);//提示信息
				dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
				is_wrong = true;
			}
		}
		else
		{

		}

		//信号函数
		connect(ui.pushButton_new, SIGNAL(clicked()), this, SLOT(new_file()));//新建
		connect(ui.pushButton_save, SIGNAL(clicked()), this, SLOT(save_file()));//保存

		//录音格式
		audio_format.setByteOrder(QAudioFormat::LittleEndian);
		if (setting_string[1] == tr("mono"))//设置声道数
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
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("查找设备失败"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_DEVICE_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
			is_wrong = true;
		}
		else
		{

		}
		if (!device_info_set_final.isFormatSupported(audio_format))//当前使用设备不支持该格式，则转换为最接近的支持格式
		{
			audio_format = device_info_set_final.nearestFormat(audio_format); //转换为最接近格式
		}
		else
		{

		}
		audio_input = new QAudioInput(device_info_set_final, audio_format, this);//创建录音流

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存

		if (is_wrong)//前面的处理过程出现错误，直接退出
		{
			close_window_include_animation();
		}
		else
		{

		}
	}
	SoundRecord::~SoundRecord()
	{
		sound_record_mutex++;//允许的录音窗口的数目增加1
		delete audio_input;//释放内存
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
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
	//若鼠标左键被按下，则移动窗体位置
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

	//鼠标未被按下，则相应变量为false
	void SoundRecord::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//鼠标双击事件
	void SoundRecord::mouseDoubleClickEvent(QMouseEvent *event)
	{
		if (on_top == false)
		{
			setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);//窗口总是显示在最前面
			on_top = true;
		}
		else
		{
			setWindowFlags(windowFlags()&~Qt::WindowStaysOnTopHint);//窗口不会总是显示在最前面
			on_top = false;
		}
		show();//如果不加上这一句会出问题，比如窗口永远无法显示
	}

	//键盘事件，用于结束程序
	void SoundRecord::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Escape)
		{
			if (!is_escape_pressed)//仅执行一次按下esc退出
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
		painter.drawPixmap(WINDOW_BACKGROUND_PAINT_START_X_NUMBER, WINDOW_BACKGROUND_PAINT_START_Y_NUMBER, main_picture);//画图作为窗口背景
	}

	void SoundRecord::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
	{

		//禁用所有按钮，否则动画播放完毕前再次点击按钮会重新触发动画
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(false);
		}
		if (!is_save)//如果有尚未保存的文件，则先保存
		{
			save_file();
		}
		else
		{

		}
		QPropertyAnimation *animation_close = new QPropertyAnimation(this, "windowOpacity");
		animation_close->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//窗口关闭动画效果
		animation_close->setStartValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation_close->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_close->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		connect(animation_close, SIGNAL(finished()), this, SLOT(close()));
	}

	void SoundRecord::new_file()//新建
	{
		if (!is_save)//已经保存，则开始下一录音，否则需要事先处理
		{
			save_file();
		}
		else
		{

		}
		is_save = false;//未保存
		QDateTime current_date_time = QDateTime::currentDateTime();//获取当前时间
		QString current_date_string = setting_string[2];
		current_date_string += current_date_time.toString(FILE_SOUND_RECORD_TIME_FORMAT_STRING);
		output_file.setFileName(current_date_string + FILE_SOUND_RECORD_BACK_PATH_STRING); //语音原始文件
		output_file.open(QIODevice::WriteOnly);//录音并写入文件
		audio_input->start(&output_file);
	}
	void SoundRecord::save_file()//保存
	{
		audio_input->stop();//停止录音

		//定义IO设备类，这里直接引用
		QIODevice *device
		{
			nullptr
		};
		device = &output_file;

		//添加wav文件头，这里直接引用
		static WAVHEADER wavHeader;
		qstrcpy(wavHeader.RiffName, "RIFF");
		qstrcpy(wavHeader.WavName, "WAVE");
		qstrcpy(wavHeader.FmtName, "fmt ");
		qstrcpy(wavHeader.DATANAME, "data");
		wavHeader.nFmtLength = 16;
		int nAudioFormat = 1;
		wavHeader.nAudioFormat = nAudioFormat;
		wavHeader.nBitsPerSample = DIALOG_SETTING_SOUND_RECORD_BIT_DEFAULT_NUMBER;
		if (setting_string[1] == tr("mono"))//设置声道数
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
		wavHeader.nRiffLength = device->size() - 8;//整个文件大小（头部44字节加上音频数据大小）-8，注意这里的device->size()已经包含了头部数据大小。如果数据大小书写错误，用部分音频处理软件打开会报错
		wavHeader.nDataLength = device->size() - sizeof(WAVHEADER);//整个文件中音频数据大小

		//写到IO设备头，这里直接引用
		device->seek(0);
		device->write(reinterpret_cast<char*>(&wavHeader), sizeof (WAVHEADER));

		//关闭文件并设置已保存标记
		output_file.close();
		device->close();
		is_save = true;//已保存
	}
}

