#include "define.h"

namespace rem
{

	//构造与析构函数
	SettingOther::SettingOther(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		is_escape_pressed = false;//默认未按下esc键以退出

		//加载图片作为窗口背景
		main_picture.load(DIALOG_SETTING_OTHER_BACKGROUND_PICTURE_PATH_STRING);
		resize(main_picture.size());//窗口大小改为图片大小

		//加载界面
		ui.setupUi(this);

		//设置文字颜色
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(232, 114, 162, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(232, 114, 162, 255));
		text_palette.setColor(QPalette::WindowText, QColor(232, 114, 162, 255));
		text_palette.setColor(QPalette::Highlight, QColor(232, 114, 162, 64));
		ui.spinBox_main_1->setPalette(text_palette);
		ui.spinBox_main_2->setPalette(text_palette);

		//读取预置内容，对窗口显示进行初始化
		QSettings *begin_read = new QSettings(FILE_SETTING_STATIC_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		QString temp;//读取路径
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_5_STRING;
		int auto_run_temp = begin_read->value(temp).toInt();
		if (auto_run_temp == 1)
		{
			ui.checkBox_1->setChecked(true);
		}
		else
		{
			ui.checkBox_1->setChecked(false);
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_1_STRING;
		int is_hide_temp= begin_read->value(temp).toInt();
		if (is_hide_temp == 1)
		{
			ui.checkBox_2->setChecked(true);
		}
		else
		{
			ui.checkBox_2->setChecked(false);
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_2_STRING;
		int time_interval_temp = begin_read->value(temp).toInt();
		ui.spinBox_main_1->setValue(time_interval_temp);
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_4_STRING;
		int transparent_temp = begin_read->value(temp).toInt();
		ui.spinBox_main_2->setValue(transparent_temp);
		delete begin_read;

		//信号函数
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//设置生效
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//取消设置

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}

	SettingOther::~SettingOther()
	{

	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void SettingOther::mousePressEvent(QMouseEvent *event)
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
	void SettingOther::mouseMoveEvent(QMouseEvent *event)
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
	void SettingOther::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void SettingOther::keyPressEvent(QKeyEvent *event)
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

	void SettingOther::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//画图作为窗口背景
	}

	//槽函数
	void SettingOther::set_apply()//设置生效
	{

		//写入ini文件
		QSettings *write_setting = new QSettings(FILE_SETTING_STATIC_PATH_STRING, QSettings::IniFormat);
		QString temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_5_STRING;
		if (ui.checkBox_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_1_STRING;
		if (ui.checkBox_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_2_STRING;
		write_setting->setValue(temp, ui.spinBox_main_1->value());
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_4_STRING;
		write_setting->setValue(temp, ui.spinBox_main_2->value());
		delete write_setting;
		QString application_name = QApplication::applicationName();//启动悬浮组件时检查是否开机自动启动
		QSettings *regedit_settings_begin = new QSettings(REG_RUN, QSettings::NativeFormat);//修改注册表
		if (ui.checkBox_1->isChecked())//是否自动启动
		{
			QString application_path = QApplication::applicationFilePath();//获得绝对路径
			regedit_settings_begin->setValue(application_name, application_path.replace("/", "\\"));//写入注册表项，注意注册表使用的路径分隔符和QT输出的相反
		}
		else
		{
			regedit_settings_begin->remove(application_name);//删除注册表项
		}
		close_window_include_animation();//设置结束
	}

	void SettingOther::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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
}

