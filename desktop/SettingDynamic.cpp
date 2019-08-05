#include "define.h"

namespace rem
{

	//构造与析构函数
	SettingDynamic::SettingDynamic(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		is_escape_pressed = false;//默认未按下esc键以退出

		//加载图片作为窗口背景
		main_picture.load(DIALOG_SETTING_DYNAMIC_BACKGROUND_PICTURE_PATH_STRING);
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
		ui.spinBox_cocoa_1->setPalette(text_palette);
		ui.spinBox_cocoa_2->setPalette(text_palette);
		ui.spinBox_chino_1->setPalette(text_palette);
		ui.spinBox_chino_2->setPalette(text_palette);
		ui.spinBox_rize_1->setPalette(text_palette);
		ui.spinBox_rize_2->setPalette(text_palette);
		ui.spinBox_syaro_1->setPalette(text_palette);
		ui.spinBox_syaro_2->setPalette(text_palette);
		ui.spinBox_chiya_1->setPalette(text_palette);
		ui.spinBox_chiya_2->setPalette(text_palette);
		ui.spinBox_maya_1->setPalette(text_palette);
		ui.spinBox_maya_2->setPalette(text_palette);
		ui.spinBox_megu_1->setPalette(text_palette);
		ui.spinBox_megu_2->setPalette(text_palette);


		//读取预置内容，对窗口显示进行初始化
		QSettings *begin_read = new QSettings(FILE_SETTING_DYNAMIC_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		int position[WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER + 1][2];//位置
		position[0][0] = begin_read->value(FILE_SETTING_DYNAMIC_CATALOG_1_1_INNER_PATH_STRING).toInt();
		position[0][1] = begin_read->value(FILE_SETTING_DYNAMIC_CATALOG_1_2_INNER_PATH_STRING).toInt();
		QString temp;//临时存储路径
		for (int index = 1; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER + 1; index++)
		{
			temp = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;
			temp += QString::number(index - 1, 10);
			temp += FILE_SETTING_DYNAMIC_CATALOG_2_1_BACK_INNER_PATH_STRING;
			position[index][0] = begin_read->value(temp).toInt();
			temp = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;
			temp += QString::number(index - 1, 10);
			temp += FILE_SETTING_DYNAMIC_CATALOG_2_2_BACK_INNER_PATH_STRING;
			position[index][1] = begin_read->value(temp).toInt();
		}
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER + 1; index++)
		{
			if (position[index][0] < 0)
			{
				position[index][0] = 0;
			}
			else
			{

			}
			if (position[index][1] < 0)
			{
				position[index][1] = 0;
			}
			else
			{

			}
		}
		delete begin_read;

		//设置界面
		ui.spinBox_main_1->setValue(position[0][0]);
		ui.spinBox_main_2->setValue(position[0][1]);
		ui.spinBox_cocoa_1->setValue(position[1][0]);
		ui.spinBox_cocoa_2->setValue(position[1][1]);
		ui.spinBox_chino_1->setValue(position[2][0]);
		ui.spinBox_chino_2->setValue(position[2][1]);
		ui.spinBox_rize_1->setValue(position[3][0]);
		ui.spinBox_rize_2->setValue(position[3][1]);
		ui.spinBox_syaro_1->setValue(position[4][0]);
		ui.spinBox_syaro_2->setValue(position[4][1]);
		ui.spinBox_chiya_1->setValue(position[5][0]);
		ui.spinBox_chiya_2->setValue(position[5][1]);
		ui.spinBox_maya_1->setValue(position[6][0]);
		ui.spinBox_maya_2->setValue(position[6][1]);
		ui.spinBox_megu_1->setValue(position[7][0]);
		ui.spinBox_megu_2->setValue(position[7][1]);

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

	SettingDynamic::~SettingDynamic()
	{

	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void SettingDynamic::mousePressEvent(QMouseEvent *event)
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
	void SettingDynamic::mouseMoveEvent(QMouseEvent *event)
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
	void SettingDynamic::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void SettingDynamic::keyPressEvent(QKeyEvent *event)
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

	void SettingDynamic::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//画图作为窗口背景
	}

	//槽函数
	void SettingDynamic::set_apply()//设置生效
	{

		//写入ini文件
		QSettings *write_setting = new QSettings(FILE_SETTING_DYNAMIC_PATH_STRING, QSettings::IniFormat);
		int position_temp[WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER + 1][2];
		position_temp[0][0] = ui.spinBox_main_1->value();
		position_temp[0][1] = ui.spinBox_main_2->value();
		position_temp[1][0] = ui.spinBox_cocoa_1->value();
		position_temp[1][1] = ui.spinBox_cocoa_2->value();
		position_temp[2][0] = ui.spinBox_chino_1->value();
		position_temp[2][1] = ui.spinBox_chino_2->value();
		position_temp[3][0] = ui.spinBox_rize_1->value();
		position_temp[3][1] = ui.spinBox_rize_2->value();
		position_temp[4][0] = ui.spinBox_syaro_1->value();
		position_temp[4][1] = ui.spinBox_syaro_2->value();
		position_temp[5][0] = ui.spinBox_chiya_1->value();
		position_temp[5][1] = ui.spinBox_chiya_2->value();
		position_temp[6][0] = ui.spinBox_maya_1->value();
		position_temp[6][1] = ui.spinBox_maya_2->value();
		position_temp[7][0] = ui.spinBox_megu_1->value();
		position_temp[7][1] = ui.spinBox_megu_2->value();
		write_setting->setValue(FILE_SETTING_DYNAMIC_CATALOG_1_1_INNER_PATH_STRING, QString::number(position_temp[0][0], 10));
		write_setting->setValue(FILE_SETTING_DYNAMIC_CATALOG_1_2_INNER_PATH_STRING, QString::number(position_temp[0][1], 10));
		QString temp;//临时存储路径
		for (int index = 1; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER + 1; index++)
		{
			temp = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_DYNAMIC_CATALOG_2_1_BACK_INNER_PATH_STRING;
			write_setting->setValue(temp, QString::number(position_temp[index][0], 10));
			temp = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_DYNAMIC_CATALOG_2_2_BACK_INNER_PATH_STRING;
			write_setting->setValue(temp, QString::number(position_temp[index][1], 10));
		}
		delete write_setting;
		close_window_include_animation();//设置结束
	}

	void SettingDynamic::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

