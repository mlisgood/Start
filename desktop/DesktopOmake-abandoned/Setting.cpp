#include "define.h"

namespace rem
{

	//构造与析构函数
	Setting::Setting(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		is_escape_pressed = false;//默认未按下esc键以退出

		//加载图片作为窗口背景
		main_picture.load(DIALOG_SETTING_STATIC_BACKGROUND_PICTURE_PATH_STRING);
		resize(main_picture.size());//窗口大小改为图片大小

		//窗口组件图片
		QString temp_picture_string;
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER; index++)
		{
			temp_picture_string = DIALOG_SETTING_WIDGET_BACKGROUND_PICTURE_PATH_FRONT_STRING;
			temp_picture_string += QString::number(index, 10);
			temp_picture_string += DIALOG_SETTING_WIDGET_BACKGROUND_PICTURE_PATH_BACK_STRING;
			widget_picture[index].load(temp_picture_string);
		}

		//加载界面
		ui.setupUi(this);

		//设置文字颜色
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(232, 114, 162, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(232, 114, 162, 255));
		text_palette.setColor(QPalette::WindowText, QColor(232, 114, 162, 255));
		text_palette.setColor(QPalette::Highlight, QColor(232, 114, 162, 64));
		ui.lineedit_cocoa->setPalette(text_palette);
		ui.lineedit_chino->setPalette(text_palette);
		ui.lineedit_rize->setPalette(text_palette);
		ui.lineedit_syaro->setPalette(text_palette);
		ui.lineedit_chiya->setPalette(text_palette);
		ui.lineedit_maya->setPalette(text_palette);
		ui.lineedit_megu->setPalette(text_palette);

		//读取预置内容，对窗口显示进行初始化
		QSettings *begin_read = new QSettings(FILE_SETTING_STATIC_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		bool check_box_bool[WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER][2];//checkbox内容
		QString lineedit_string[WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER];//lineedit内容
		QString temp;//读取路径
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER; index++)
		{
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
			int temp_bool = begin_read->value(temp).toInt();
			if (temp_bool == 1)
			{
				check_box_bool[index][0] = true;
			}
			else
			{
				check_box_bool[index][0] = false;
			}
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
			temp_bool = begin_read->value(temp).toInt();
			if (temp_bool == 1)
			{
				check_box_bool[index][1] = true;
			}
			else
			{
				check_box_bool[index][1] = false;
			}
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_7_STRING;
			lineedit_string[index] = begin_read->value(temp).toString();
			if (lineedit_string[index].length() == 0)
			{
				lineedit_string[index] = DIALOG_SETTING_PATH_DEFAULT_STRING;
			}
			else
			{

			}
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_4_STRING;
			picture_digit[index] = begin_read->value(temp).toInt();
			if (picture_digit[index] < 0)
			{
				picture_digit[index] = 0;
			}
			else
			{

			}
		}
		delete begin_read;

		//设置界面
		if (check_box_bool[0][0])
		{
			ui.checkBox_cocoa_1->setChecked(true);
		}
		else
		{
			ui.checkBox_cocoa_1->setChecked(false);
		}
		if (check_box_bool[0][1])
		{
			ui.checkBox_cocoa_2->setChecked(true);
		}
		else
		{
			ui.checkBox_cocoa_2->setChecked(false);
		}
		if (check_box_bool[1][0])
		{
			ui.checkBox_chino_1->setChecked(true);
		}
		else
		{
			ui.checkBox_chino_1->setChecked(false);
		}
		if (check_box_bool[1][1])
		{
			ui.checkBox_chino_2->setChecked(true);
		}
		else
		{
			ui.checkBox_chino_2->setChecked(false);
		}
		if (check_box_bool[2][0])
		{
			ui.checkBox_rize_1->setChecked(true);
		}
		else
		{
			ui.checkBox_rize_1->setChecked(false);
		}
		if (check_box_bool[2][1])
		{
			ui.checkBox_rize_2->setChecked(true);
		}
		else
		{
			ui.checkBox_rize_2->setChecked(false);
		}
		if (check_box_bool[3][0])
		{
			ui.checkBox_syaro_1->setChecked(true);
		}
		else
		{
			ui.checkBox_syaro_1->setChecked(false);
		}
		if (check_box_bool[3][1])
		{
			ui.checkBox_syaro_2->setChecked(true);
		}
		else
		{
			ui.checkBox_syaro_2->setChecked(false);
		}
		if (check_box_bool[4][0])
		{
			ui.checkBox_chiya_1->setChecked(true);
		}
		else
		{
			ui.checkBox_chiya_1->setChecked(false);
		}
		if (check_box_bool[4][1])
		{
			ui.checkBox_chiya_2->setChecked(true);
		}
		else
		{
			ui.checkBox_chiya_2->setChecked(false);
		}
		if (check_box_bool[5][0])
		{
			ui.checkBox_maya_1->setChecked(true);
		}
		else
		{
			ui.checkBox_maya_1->setChecked(false);
		}
		if (check_box_bool[5][1])
		{
			ui.checkBox_maya_2->setChecked(true);
		}
		else
		{
			ui.checkBox_maya_2->setChecked(false);
		}
		if (check_box_bool[6][0])
		{
			ui.checkBox_megu_1->setChecked(true);
		}
		else
		{
			ui.checkBox_megu_1->setChecked(false);
		}
		if (check_box_bool[6][1])
		{
			ui.checkBox_megu_2->setChecked(true);
		}
		else
		{
			ui.checkBox_megu_2->setChecked(false);
		}
		ui.lineedit_cocoa->setText(lineedit_string[0]);
		ui.lineedit_chino->setText(lineedit_string[1]);
		ui.lineedit_rize->setText(lineedit_string[2]);
		ui.lineedit_syaro->setText(lineedit_string[3]);
		ui.lineedit_chiya->setText(lineedit_string[4]);
		ui.lineedit_maya->setText(lineedit_string[5]);
		ui.lineedit_megu->setText(lineedit_string[6]);


		//信号函数
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//设置生效
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//取消设置
		connect(ui.pushButton_cocoa_1, SIGNAL(clicked()), this, SLOT(pushButton_select_1()));//选择路径按钮
		connect(ui.pushButton_chino_1, SIGNAL(clicked()), this, SLOT(pushButton_select_2()));
		connect(ui.pushButton_rize_1, SIGNAL(clicked()), this, SLOT(pushButton_select_3()));
		connect(ui.pushButton_syaro_1, SIGNAL(clicked()), this, SLOT(pushButton_select_4()));
		connect(ui.pushButton_chiya_1, SIGNAL(clicked()), this, SLOT(pushButton_select_5()));
		connect(ui.pushButton_maya_1, SIGNAL(clicked()), this, SLOT(pushButton_select_6()));
		connect(ui.pushButton_megu_1, SIGNAL(clicked()), this, SLOT(pushButton_select_7()));
		connect(ui.pushButton_cocoa_2, SIGNAL(clicked()), this, SLOT(pushButton_delete_1()));//删除路径按钮
		connect(ui.pushButton_chino_2, SIGNAL(clicked()), this, SLOT(pushButton_delete_2()));
		connect(ui.pushButton_rize_2, SIGNAL(clicked()), this, SLOT(pushButton_delete_3()));
		connect(ui.pushButton_syaro_2, SIGNAL(clicked()), this, SLOT(pushButton_delete_4()));
		connect(ui.pushButton_chiya_2, SIGNAL(clicked()), this, SLOT(pushButton_delete_5()));
		connect(ui.pushButton_maya_2, SIGNAL(clicked()), this, SLOT(pushButton_delete_6()));
		connect(ui.pushButton_megu_2, SIGNAL(clicked()), this, SLOT(pushButton_delete_7()));
		connect(ui.pushButton_t_cocoa_1, SIGNAL(clicked()), this, SLOT(pushButton_transparent_down_1()));//透明度减少按钮
		connect(ui.pushButton_t_chino_1, SIGNAL(clicked()), this, SLOT(pushButton_transparent_down_2()));
		connect(ui.pushButton_t_rize_1, SIGNAL(clicked()), this, SLOT(pushButton_transparent_down_3()));
		connect(ui.pushButton_t_syaro_1, SIGNAL(clicked()), this, SLOT(pushButton_transparent_down_4()));
		connect(ui.pushButton_t_chiya_1, SIGNAL(clicked()), this, SLOT(pushButton_transparent_down_5()));
		connect(ui.pushButton_t_maya_1, SIGNAL(clicked()), this, SLOT(pushButton_transparent_down_6()));
		connect(ui.pushButton_t_megu_1, SIGNAL(clicked()), this, SLOT(pushButton_transparent_down_7()));
		connect(ui.pushButton_t_cocoa_2, SIGNAL(clicked()), this, SLOT(pushButton_transparent_up_1()));//透明度增加按钮
		connect(ui.pushButton_t_chino_2, SIGNAL(clicked()), this, SLOT(pushButton_transparent_up_2()));
		connect(ui.pushButton_t_rize_2, SIGNAL(clicked()), this, SLOT(pushButton_transparent_up_3()));
		connect(ui.pushButton_t_syaro_2, SIGNAL(clicked()), this, SLOT(pushButton_transparent_up_4()));
		connect(ui.pushButton_t_chiya_2, SIGNAL(clicked()), this, SLOT(pushButton_transparent_up_5()));
		connect(ui.pushButton_t_maya_2, SIGNAL(clicked()), this, SLOT(pushButton_transparent_up_6()));
		connect(ui.pushButton_t_megu_2, SIGNAL(clicked()), this, SLOT(pushButton_transparent_up_7()));

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}

	Setting::~Setting()
	{

	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void Setting::mousePressEvent(QMouseEvent *event)
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
	void Setting::mouseMoveEvent(QMouseEvent *event)
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
	void Setting::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void Setting::keyPressEvent(QKeyEvent *event)
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

	void Setting::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//画图作为窗口背景
		painter.setOpacity((double)picture_digit[0] / 10);
		painter.drawPixmap(ui.label_0->x(), ui.label_0->y(), widget_picture[0]);//画图作为窗口背景
		painter.setOpacity((double)picture_digit[1] / 10);
		painter.drawPixmap(ui.label_1->x(), ui.label_1->y(), widget_picture[1]);
		painter.setOpacity((double)picture_digit[2] / 10);
		painter.drawPixmap(ui.label_2->x(), ui.label_2->y(), widget_picture[2]);
		painter.setOpacity((double)picture_digit[3] / 10);
		painter.drawPixmap(ui.label_3->x(), ui.label_3->y(), widget_picture[3]);
		painter.setOpacity((double)picture_digit[4] / 10);
		painter.drawPixmap(ui.label_4->x(), ui.label_4->y(), widget_picture[4]);
		painter.setOpacity((double)picture_digit[5] / 10);
		painter.drawPixmap(ui.label_5->x(), ui.label_5->y(), widget_picture[5]);
		painter.setOpacity((double)picture_digit[6] / 10);
		painter.drawPixmap(ui.label_6->x(), ui.label_6->y(), widget_picture[6]);
	}

	//槽函数
	void Setting::set_apply()//设置生效
	{

		//写入ini文件
		QSettings *write_setting = new QSettings(FILE_SETTING_STATIC_PATH_STRING, QSettings::IniFormat);
		QString temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(0, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		if (ui.checkBox_cocoa_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(1, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		if (ui.checkBox_chino_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(2, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		if (ui.checkBox_rize_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(3, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		if (ui.checkBox_syaro_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(4, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		if (ui.checkBox_chiya_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(5, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		if (ui.checkBox_maya_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(6, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		if (ui.checkBox_megu_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(0, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		if (ui.checkBox_cocoa_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(1, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		if (ui.checkBox_chino_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(2, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		if (ui.checkBox_rize_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(3, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		if (ui.checkBox_syaro_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(4, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		if (ui.checkBox_chiya_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(5, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		if (ui.checkBox_maya_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(6, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		if (ui.checkBox_megu_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		QString transform_string[7];
		transform_string[0] = ui.lineedit_cocoa->text();
		transform_string[1] = ui.lineedit_chino->text();
		transform_string[2] = ui.lineedit_rize->text();
		transform_string[3] = ui.lineedit_syaro->text();
		transform_string[4] = ui.lineedit_chiya->text();
		transform_string[5] = ui.lineedit_maya->text();
		transform_string[6] = ui.lineedit_megu->text();
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER; index++)
		{
			if (transform_string[index].length() == 0)
			{
				transform_string[index] = DIALOG_SETTING_PATH_DEFAULT_STRING;
			}
			else
			{

			}
		}
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER; index++)
		{
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_7_STRING;
			write_setting->setValue(temp, transform_string[index]);
		}
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER; index++)
		{
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_4_STRING;
			write_setting->setValue(temp, QString::number(picture_digit[index], 10));
		}
		delete write_setting;
		close_window_include_animation();//设置结束
	}

	void Setting::pushButton_select_1()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_cocoa->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void Setting::pushButton_select_2()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_chino->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void Setting::pushButton_select_3()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_rize->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void Setting::pushButton_select_4()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_syaro->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void Setting::pushButton_select_5()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_chiya->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void Setting::pushButton_select_6()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_maya->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void Setting::pushButton_select_7()//选择路径按钮
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择程序"));
		QString file_dialog_file_name = QDir::currentPath();//当前路径，用于获得被打开的文件路径
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//获取文件信息
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//该文件存在
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_megu->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("文件或文件路径不存在"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void Setting::pushButton_delete_1()//清除路径
	{
		ui.lineedit_cocoa->setText(DIALOG_SETTING_PATH_DEFAULT_STRING);
	}

	void Setting::pushButton_delete_2()//清除路径
	{
		ui.lineedit_chino->setText(DIALOG_SETTING_PATH_DEFAULT_STRING);
	}

	void Setting::pushButton_delete_3()//清除路径
	{
		ui.lineedit_rize->setText(DIALOG_SETTING_PATH_DEFAULT_STRING);
	}

	void Setting::pushButton_delete_4()//清除路径
	{
		ui.lineedit_syaro->setText(DIALOG_SETTING_PATH_DEFAULT_STRING);
	}

	void Setting::pushButton_delete_5()//清除路径
	{
		ui.lineedit_chiya->setText(DIALOG_SETTING_PATH_DEFAULT_STRING);
	}

	void Setting::pushButton_delete_6()//清除路径
	{
		ui.lineedit_maya->setText(DIALOG_SETTING_PATH_DEFAULT_STRING);
	}

	void Setting::pushButton_delete_7()//清除路径
	{
		ui.lineedit_megu->setText(DIALOG_SETTING_PATH_DEFAULT_STRING);
	}

	void Setting::pushButton_transparent_down_1()//透明度减少
	{
		if (picture_digit[0] > DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER)
		{
			picture_digit[0] -= DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[0] = DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_down_2()//透明度减少
	{
		if (picture_digit[1] > DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER)
		{
			picture_digit[1] -= DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[1] = DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_down_3()//透明度减少
	{
		if (picture_digit[2] > DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER)
		{
			picture_digit[2] -= DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[2] = DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_down_4()//透明度减少
	{
		if (picture_digit[3] > DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER)
		{
			picture_digit[3] -= DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[3] = DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_down_5()//透明度减少
	{
		if (picture_digit[4] > DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER)
		{
			picture_digit[4] -= DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[4] = DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER;
		}
		repaint();
	}


	void Setting::pushButton_transparent_down_6()//透明度减少
	{
		if (picture_digit[5] > DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER)
		{
			picture_digit[5] -= DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[5] = DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_down_7()//透明度减少
	{
		if (picture_digit[6] > DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER)
		{
			picture_digit[6] -= DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[6] = DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_up_1()//透明度增加
	{
		if (picture_digit[0] < DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER)
		{
			picture_digit[0] += DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[0] = DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_up_2()//透明度增加
	{
		if (picture_digit[1] < DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER)
		{
			picture_digit[1] += DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[1] = DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_up_3()//透明度增加
	{
		if (picture_digit[2] < DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER)
		{
			picture_digit[2] += DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[2] = DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_up_4()//透明度增加
	{
		if (picture_digit[3] < DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER)
		{
			picture_digit[3] += DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[3] = DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_up_5()//透明度增加
	{
		if (picture_digit[4] < DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER)
		{
			picture_digit[4] += DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[4] = DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER;
		}
		repaint();
	}


	void Setting::pushButton_transparent_up_6()//透明度增加
	{
		if (picture_digit[5] < DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER)
		{
			picture_digit[5] += DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[5] = DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_up_7()//透明度增加
	{
		if (picture_digit[6] < DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER)
		{
			picture_digit[6] += DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[6] = DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER;
		}
		repaint();
	}

	void Setting::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

