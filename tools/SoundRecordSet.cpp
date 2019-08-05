#include "define.h"

namespace rem
{
	//构造与析构函数
	SoundRecordSet::SoundRecordSet(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		is_escape_pressed = false;//默认未按下esc键以退出

		//加载图片作为窗口背景
		main_picture.load(DIALOG_TOOLS_SOUND_RECORD_SET_BACKGROUND_PICTURE_PATH_STRING);
		resize(main_picture.size());//窗口大小改为图片大小

		//加载界面
		ui.setupUi(this);
		
		//设置文字颜色
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::WindowText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::Highlight, QColor(70, 28, 10, 64));
		ui.comboBox_1->setPalette(text_palette);
		ui.comboBox_2->setPalette(text_palette);
		ui.lineedit->setPalette(text_palette);
		

		//去掉关联性控件的右键菜单
		QList<QScrollBar *> scroll_bar = this->findChildren<QScrollBar *>();//由于无法用常规方式获得combobox的滚动条，因此使用该方法查找所有同类型控件并进行操作
		foreach(QScrollBar *scroll_bar_style_control, scroll_bar)
		{
			scroll_bar_style_control->setContextMenuPolicy(Qt::NoContextMenu);
		}

		//读取录音设备并输入组合框
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

		//读取预置内容，对窗口显示进行初始化
		QSettings *begin_read = new QSettings(FILE_SETTING_SOUND_RECORD_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		QString combobox_index[2];//读取combobox需要的内容
		combobox_index[0] = (begin_read->value(FILE_SOUND_RECORD_SETTING_CATALOG_1_INNER_PATH_STRING)).toString();
		combobox_index[1] = (begin_read->value(FILE_SOUND_RECORD_SETTING_CATALOG_2_INNER_PATH_STRING)).toString();
		ui.comboBox_1->setCurrentText(combobox_index[0]);//设置内容
		ui.comboBox_2->setCurrentText(combobox_index[1]);
		QString label_index;
		label_index = (begin_read->value(FILE_SOUND_RECORD_SETTING_CATALOG_3_INNER_PATH_STRING)).toString();
		ui.lineedit->setText(label_index);
		if (label_index.length() == 0)//处理配置文件丢失的情况
		{
			ui.lineedit->setText(tr("#default#"));
		}
		else
		{

		}
		delete begin_read;

		//信号函数
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//设置生效
		connect(ui.pushButton_choose, SIGNAL(clicked()), this, SLOT(set_save_path()));//选择路径
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//取消设置

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}

	SoundRecordSet::~SoundRecordSet()
	{

	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
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
	//若鼠标左键被按下，则移动窗体位置
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

	//鼠标未被按下，则相应变量为false
	void SoundRecordSet::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void SoundRecordSet::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Enter)
		{

		}
		else if (event->key() == Qt::Key_Escape)
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
		else
		{

		}
	}

	void SoundRecordSet::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(WINDOW_BACKGROUND_PAINT_START_X_NUMBER, WINDOW_BACKGROUND_PAINT_START_Y_NUMBER, main_picture);//画图作为窗口背景
	}

	//槽函数
	void SoundRecordSet::set_apply()//设置生效
	{

		//写入ini文件
		QSettings *write_setting = new QSettings(FILE_SETTING_SOUND_RECORD_PATH_STRING, QSettings::IniFormat);
		QString combobox_index[2];//写入combobox的内容
		combobox_index[0] = ui.comboBox_1->currentText();
		combobox_index[1] = ui.comboBox_2->currentText();
		write_setting->setValue(FILE_SOUND_RECORD_SETTING_CATALOG_1_INNER_PATH_STRING, combobox_index[0]);
		write_setting->setValue(FILE_SOUND_RECORD_SETTING_CATALOG_2_INNER_PATH_STRING, combobox_index[1]);
		QString label_index=ui.lineedit->text();//写入ineeit的内容
		write_setting->setValue(FILE_SOUND_RECORD_SETTING_CATALOG_3_INNER_PATH_STRING, label_index);
		ui.lineedit->setText(label_index);
		delete write_setting;
		close_window_include_animation();//设置结束
	}

	void SoundRecordSet::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
	{

		//禁用所有按钮，否则动画播放完毕前再次点击按钮会重新触发动画
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(false);
		}
		QPropertyAnimation *animation_close = new QPropertyAnimation(this, "windowOpacity");
		animation_close->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//窗口关闭动画效果
		animation_close->setStartValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation_close->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_close->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
		connect(animation_close, SIGNAL(finished()), this, SLOT(close()));
	}

	void SoundRecordSet::set_save_path()
	{
		File_only_path dialog;//这个窗口是从Notepad.exe引用的，调用方式比较麻烦
		dialog.setWindowTitle(tr("选择路径"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if (file_information.isFile())//该文件存在
		{
			file_dialog_file_name = file_information.path();//只取文件路径
		}
		else
		{

		}
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		if (change_result)
		{
			QFileInfo file_information(file_dialog_file_name);//获取文件信息
			if (file_information.isFile())//该文件存在
			{
				file_dialog_file_name = file_information.absoluteDir().absolutePath();//只取文件路径
				file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));//获得文件路径
				ui.lineedit->setText(file_dialog_file_name);//设置显示文本
			}
			else if(!file_information.isDir())
			{
				Help dialog;//信息提示框
				dialog.setWindowTitle(tr("文件或文件路径不存在"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
				dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
			}
			else
			{
				file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));//获得文件路径
				ui.lineedit->setText(file_dialog_file_name);//设置显示文本
			}
		}
		else
		{

		}
	}
}