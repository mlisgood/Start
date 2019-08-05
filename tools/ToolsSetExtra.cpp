#include "define.h"

namespace rem
{

	//引用全局变量
	extern int counter_mutex;

	//构造与析构函数
	ToolsSetExtra::ToolsSetExtra(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		is_escape_pressed = false;//默认未按下esc键以退出

		//加载图片作为窗口背景
		main_picture.load(DIALOG_TOOLS_SET_EXTRA_BACKGROUND_PICTURE_PATH_STRING);
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
		ui.comboBox_3->setPalette(text_palette);
		ui.spinBox_1->setPalette(text_palette);
		ui.spinBox_2->setPalette(text_palette);
		ui.spinBox_3->setPalette(text_palette);
		ui.spinBox_4->setPalette(text_palette);
		ui.spinBox_5->setPalette(text_palette);
		

		//去掉关联性控件的右键菜单
		QList<QScrollBar *> scroll_bar = this->findChildren<QScrollBar *>();//由于无法用常规方式获得combobox的滚动条，因此使用该方法查找所有同类型控件并进行操作
		foreach(QScrollBar *scroll_bar_style_control, scroll_bar)
		{
			scroll_bar_style_control->setContextMenuPolicy(Qt::NoContextMenu);
		}

		//读取预置内容，对窗口显示进行初始化
		QSettings *begin_read = new QSettings(FILE_SETTING_MAINWINDOW_STYLE_EXTRA_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		QString combobox_index[3];//读取combobox需要的内容
		combobox_index[0] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_1_2_INNER_PATH_STRING)).toString();
		combobox_index[1] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_2_3_INNER_PATH_STRING)).toString();
		combobox_index[2] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_2_4_INNER_PATH_STRING)).toString();
		ui.comboBox_1->setCurrentText(combobox_index[0]);//设置内容
		ui.comboBox_2->setCurrentText(combobox_index[1]);
		ui.comboBox_3->setCurrentText(combobox_index[2]);
		QString spinbox_index[5];//读取spinbox需要的内容
		spinbox_index[0] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_1_1_INNER_PATH_STRING)).toString();
		spinbox_index[1] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_2_2_INNER_PATH_STRING)).toString();
		spinbox_index[2] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_2_5_INNER_PATH_STRING)).toString();
		spinbox_index[3] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_2_6_INNER_PATH_STRING)).toString();
		spinbox_index[4] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_2_7_INNER_PATH_STRING)).toString();
		bool temp_transform_status[5];//字符串转换为整数是否成功
		int spinbox_index_transform[5];//spinbox读取的实际转换后内容
		spinbox_index_transform[0] = spinbox_index[0].toInt(&temp_transform_status[0], 10);//转换为整数
		spinbox_index_transform[1] = spinbox_index[1].toInt(&temp_transform_status[1], 10);
		spinbox_index_transform[2] = spinbox_index[2].toInt(&temp_transform_status[2], 10);
		spinbox_index_transform[3] = spinbox_index[3].toInt(&temp_transform_status[3], 10);
		spinbox_index_transform[4] = spinbox_index[4].toInt(&temp_transform_status[4], 10);
		if (!temp_transform_status[0])//如果有数字转换失败，则强制改为默认值
		{
			spinbox_index_transform[0] = 10;
		}
		else
		{

		}
		if (!temp_transform_status[1])
		{
			spinbox_index_transform[1] = 1;
		}
		else
		{

		}
		if (!temp_transform_status[2])
		{
			spinbox_index_transform[2] = 0;
		}
		else
		{

		}
		if (!temp_transform_status[3])
		{
			spinbox_index_transform[3] = 0;
		}
		else
		{

		}
		if (!temp_transform_status[4])
		{
			spinbox_index_transform[4] = 10;
		}
		else
		{

		}
		ui.spinBox_1->setValue(spinbox_index_transform[0]);
		ui.spinBox_2->setValue(spinbox_index_transform[1]);
		ui.spinBox_3->setValue(spinbox_index_transform[2]);
		ui.spinBox_4->setValue(spinbox_index_transform[3]);
		ui.spinBox_5->setValue(spinbox_index_transform[4]);
		QString checkbox_index;//读取checkbox需要的内容
		checkbox_index = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_2_1_INNER_PATH_STRING)).toString();
		if (checkbox_index == tr("1"))
		{
			ui.checkBox->setChecked(true);
		}
		else if (checkbox_index == tr("0"))
		{
			ui.checkBox->setChecked(false);
		}
		else
		{
			ui.checkBox->setChecked(false);
		}
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

	ToolsSetExtra::~ToolsSetExtra()
	{

	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void ToolsSetExtra::mousePressEvent(QMouseEvent *event)
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
	void ToolsSetExtra::mouseMoveEvent(QMouseEvent *event)
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
	void ToolsSetExtra::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void ToolsSetExtra::keyPressEvent(QKeyEvent *event)
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

	void ToolsSetExtra::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(WINDOW_BACKGROUND_PAINT_START_X_NUMBER, WINDOW_BACKGROUND_PAINT_START_Y_NUMBER, main_picture);//画图作为窗口背景
	}

	//槽函数
	void ToolsSetExtra::set_apply()//设置生效
	{

		//写入ini文件
		QSettings *write_setting = new QSettings(FILE_SETTING_MAINWINDOW_STYLE_EXTRA_PATH_STRING, QSettings::IniFormat);
		QString combobox_index[3];//写入combobox的内容
		combobox_index[0] = ui.comboBox_1->currentText();
		combobox_index[1] = ui.comboBox_2->currentText();
		combobox_index[2] = ui.comboBox_3->currentText();
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_1_2_INNER_PATH_STRING, combobox_index[0]);
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_3_INNER_PATH_STRING, combobox_index[1]);
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_4_INNER_PATH_STRING, combobox_index[2]);
		QString spinbox_index[5];//写入spinbox的内容
		spinbox_index[0] = QString::number(ui.spinBox_1->value(), 10);
		spinbox_index[1] = QString::number(ui.spinBox_2->value(), 10);
		spinbox_index[2] = QString::number(ui.spinBox_3->value(), 10);
		spinbox_index[3] = QString::number(ui.spinBox_4->value(), 10);
		spinbox_index[4] = QString::number(ui.spinBox_5->value(), 10);
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_1_1_INNER_PATH_STRING, spinbox_index[0]);
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_2_INNER_PATH_STRING, spinbox_index[1]);
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_5_INNER_PATH_STRING, spinbox_index[2]);
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_6_INNER_PATH_STRING, spinbox_index[3]);
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_7_INNER_PATH_STRING, spinbox_index[4]);
		if (ui.checkBox->isChecked())//写入checkbox的内容
		{
			write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_1_INNER_PATH_STRING, tr("1"));
		}
		else
		{
			write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_1_INNER_PATH_STRING, tr("0"));
		}
		delete write_setting;
		close_window_include_animation();//设置结束
	}

	void ToolsSetExtra::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

