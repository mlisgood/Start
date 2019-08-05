#include "define.h"

namespace rem
{

    //使用标准命名空间
	using std::string;
	using std::ifstream;
	using std::ofstream;
	using std::fstream;
	using std::ios_base;

	//构造与析构函数
	Color::Color(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		totalrandomnumber = DIALOG_RANDOM_MIN_NUMBER + rand() % (DIALOG_RANDOM_MAX_NUMBER - DIALOG_RANDOM_MIN_NUMBER + 1);//产生指定随机数以便决定背景图片和人物图片样式
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		resize(DIALOG_COLOR_SIZE_WIDTH_NUMBER, DIALOG_COLOR_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		select_color = 0;//不允许选取颜色
		forbid_change = 0;//允许spinbox改变右侧渐变条的颜色
		is_escape_pressed = false;//允许按下esc键退出程序

		//图片路径
		//背景图片路径
		filepath = DIALOG_COLOR_BACKGROUND_PICTURE_PATH_FRONT_STRING + QString::number(totalrandomnumber, 10);
		filepath += DIALOG_COLOR_BACKGROUND_PICTURE_PATH_BACK_STRING;

		//加载界面，必须放在最后以避免界面被之后的绘图覆盖
		ui.setupUi(this);

		//加载按钮和显示框样式
		ui.pushButton_add->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_add_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_add_pressed.png);}");
		ui.pushButton_remove->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_remove_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_remove_pressed.png);}");
		ui.pushButton_accept->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_accept_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_accept_pressed.png);}");
		ui.pushButton_exit->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_exit_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_exit_pressed.png);}");
		ui.pushButton_select->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_select_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_select_pressed.png);}");

		//连接处理函数
		//基本颜色按钮
		connect(ui.pushButton_color_1, SIGNAL(clicked()), this, SLOT(color_change_1()));
		connect(ui.pushButton_color_2, SIGNAL(clicked()), this, SLOT(color_change_2()));
		connect(ui.pushButton_color_3, SIGNAL(clicked()), this, SLOT(color_change_3()));
		connect(ui.pushButton_color_4, SIGNAL(clicked()), this, SLOT(color_change_4()));
		connect(ui.pushButton_color_5, SIGNAL(clicked()), this, SLOT(color_change_5()));
		connect(ui.pushButton_color_6, SIGNAL(clicked()), this, SLOT(color_change_6()));
		connect(ui.pushButton_color_7, SIGNAL(clicked()), this, SLOT(color_change_7()));
		connect(ui.pushButton_color_8, SIGNAL(clicked()), this, SLOT(color_change_8()));
		connect(ui.pushButton_color_9, SIGNAL(clicked()), this, SLOT(color_change_9()));
		connect(ui.pushButton_color_10, SIGNAL(clicked()), this, SLOT(color_change_10()));
		connect(ui.pushButton_color_11, SIGNAL(clicked()), this, SLOT(color_change_11()));
		connect(ui.pushButton_color_12, SIGNAL(clicked()), this, SLOT(color_change_12()));
		connect(ui.pushButton_color_13, SIGNAL(clicked()), this, SLOT(color_change_13()));
		connect(ui.pushButton_color_14, SIGNAL(clicked()), this, SLOT(color_change_14()));
		connect(ui.pushButton_color_15, SIGNAL(clicked()), this, SLOT(color_change_15()));
		connect(ui.pushButton_color_16, SIGNAL(clicked()), this, SLOT(color_change_16()));
		connect(ui.pushButton_color_17, SIGNAL(clicked()), this, SLOT(color_change_17()));
		connect(ui.pushButton_color_18, SIGNAL(clicked()), this, SLOT(color_change_18()));
		connect(ui.pushButton_color_19, SIGNAL(clicked()), this, SLOT(color_change_19()));
		connect(ui.pushButton_color_20, SIGNAL(clicked()), this, SLOT(color_change_20()));
		connect(ui.pushButton_color_21, SIGNAL(clicked()), this, SLOT(color_change_21()));
		connect(ui.pushButton_color_22, SIGNAL(clicked()), this, SLOT(color_change_22()));
		connect(ui.pushButton_color_23, SIGNAL(clicked()), this, SLOT(color_change_23()));
		connect(ui.pushButton_color_24, SIGNAL(clicked()), this, SLOT(color_change_24()));
		connect(ui.pushButton_color_25, SIGNAL(clicked()), this, SLOT(color_change_25()));
		connect(ui.pushButton_color_26, SIGNAL(clicked()), this, SLOT(color_change_26()));
		connect(ui.pushButton_color_27, SIGNAL(clicked()), this, SLOT(color_change_27()));
		connect(ui.pushButton_color_28, SIGNAL(clicked()), this, SLOT(color_change_28()));
		connect(ui.pushButton_color_29, SIGNAL(clicked()), this, SLOT(color_change_29()));
		connect(ui.pushButton_color_30, SIGNAL(clicked()), this, SLOT(color_change_30()));
		connect(ui.pushButton_color_31, SIGNAL(clicked()), this, SLOT(color_change_31()));
		connect(ui.pushButton_color_32, SIGNAL(clicked()), this, SLOT(color_change_32()));
		connect(ui.pushButton_color_33, SIGNAL(clicked()), this, SLOT(color_change_33()));
		connect(ui.pushButton_color_34, SIGNAL(clicked()), this, SLOT(color_change_34()));
		connect(ui.pushButton_color_35, SIGNAL(clicked()), this, SLOT(color_change_35()));
		connect(ui.pushButton_color_36, SIGNAL(clicked()), this, SLOT(color_change_36()));
		connect(ui.pushButton_color_37, SIGNAL(clicked()), this, SLOT(color_change_37()));
		connect(ui.pushButton_color_38, SIGNAL(clicked()), this, SLOT(color_change_38()));
		connect(ui.pushButton_color_39, SIGNAL(clicked()), this, SLOT(color_change_39()));
		connect(ui.pushButton_color_40, SIGNAL(clicked()), this, SLOT(color_change_40()));
		connect(ui.pushButton_color_41, SIGNAL(clicked()), this, SLOT(color_change_41()));
		connect(ui.pushButton_color_42, SIGNAL(clicked()), this, SLOT(color_change_42()));
		connect(ui.pushButton_color_43, SIGNAL(clicked()), this, SLOT(color_change_43()));
		connect(ui.pushButton_color_44, SIGNAL(clicked()), this, SLOT(color_change_44()));
		connect(ui.pushButton_color_45, SIGNAL(clicked()), this, SLOT(color_change_45()));
		connect(ui.pushButton_color_46, SIGNAL(clicked()), this, SLOT(color_change_46()));
		connect(ui.pushButton_color_47, SIGNAL(clicked()), this, SLOT(color_change_47()));
		connect(ui.pushButton_color_48, SIGNAL(clicked()), this, SLOT(color_change_48()));
		connect(ui.pushButton_self_1, SIGNAL(clicked()), this, SLOT(color_change_self_1()));
		connect(ui.pushButton_self_2, SIGNAL(clicked()), this, SLOT(color_change_self_2()));
		connect(ui.pushButton_self_3, SIGNAL(clicked()), this, SLOT(color_change_self_3()));
		connect(ui.pushButton_self_4, SIGNAL(clicked()), this, SLOT(color_change_self_4()));
		connect(ui.pushButton_self_5, SIGNAL(clicked()), this, SLOT(color_change_self_5()));
		connect(ui.pushButton_self_6, SIGNAL(clicked()), this, SLOT(color_change_self_6()));
		connect(ui.pushButton_self_7, SIGNAL(clicked()), this, SLOT(color_change_self_7()));
		connect(ui.pushButton_self_8, SIGNAL(clicked()), this, SLOT(color_change_self_8()));
		connect(ui.pushButton_self_9, SIGNAL(clicked()), this, SLOT(color_change_self_9()));
		connect(ui.pushButton_self_10, SIGNAL(clicked()), this, SLOT(color_change_self_10()));
		connect(ui.pushButton_self_11, SIGNAL(clicked()), this, SLOT(color_change_self_11()));
		connect(ui.pushButton_self_12, SIGNAL(clicked()), this, SLOT(color_change_self_12()));
		connect(ui.pushButton_self_13, SIGNAL(clicked()), this, SLOT(color_change_self_13()));
		connect(ui.pushButton_self_14, SIGNAL(clicked()), this, SLOT(color_change_self_14()));
		connect(ui.pushButton_self_15, SIGNAL(clicked()), this, SLOT(color_change_self_15()));
		connect(ui.pushButton_self_16, SIGNAL(clicked()), this, SLOT(color_change_self_16()));
		connect(ui.pushButton_self_17, SIGNAL(clicked()), this, SLOT(color_change_self_17()));
		connect(ui.pushButton_self_18, SIGNAL(clicked()), this, SLOT(color_change_self_18()));
		connect(ui.pushButton_self_19, SIGNAL(clicked()), this, SLOT(color_change_self_19()));
		connect(ui.pushButton_self_20, SIGNAL(clicked()), this, SLOT(color_change_self_20()));
		connect(ui.pushButton_self_21, SIGNAL(clicked()), this, SLOT(color_change_self_21()));
		connect(ui.pushButton_self_22, SIGNAL(clicked()), this, SLOT(color_change_self_22()));
		connect(ui.pushButton_self_23, SIGNAL(clicked()), this, SLOT(color_change_self_23()));
		connect(ui.pushButton_self_24, SIGNAL(clicked()), this, SLOT(color_change_self_24()));

		//其他按钮
		connect(ui.pushButton_select, SIGNAL(clicked()), this, SLOT(color_select()));
		connect(ui.pushButton_remove, SIGNAL(clicked()), this, SLOT(color_remove()));
		connect(ui.pushButton_add, SIGNAL(clicked()), this, SLOT(color_add()));
		connect(ui.pushButton_accept, SIGNAL(clicked()), this, SLOT(color_accept()));

		//颜色值变化
		connect(ui.spinBox_1, SIGNAL(valueChanged(int)), this, SLOT(color_change_spinbox(int)));
		connect(ui.spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(color_change_spinbox(int)));
		connect(ui.spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(color_change_spinbox(int)));

		//滑块选取颜色
		connect(ui.verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(color_slider_change(int)));

		//关闭按钮
		connect(ui.pushButton_close_window, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));
		connect(ui.pushButton_exit, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));

		//设置文字颜色
		QPalette lineedit_palette;
		if (totalrandomnumber == 1)//决定相关文字颜色
		{
			lineedit_palette.setColor(QPalette::Text, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(255, 83, 185, 64));
		}
		else if (totalrandomnumber == 2)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(133, 153, 212, 64));
		}
		else if (totalrandomnumber == 3)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(222, 63, 235, 64));
		}
		else if (totalrandomnumber == 4)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(242, 153, 93, 64));
		}
		else if (totalrandomnumber == 5)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(71, 185, 78, 64));
		}
		else
		{

		}
		ui.spinBox_1->setPalette(lineedit_palette);
		ui.spinBox_2->setPalette(lineedit_palette);
		ui.spinBox_3->setPalette(lineedit_palette);

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}

	Color::~Color()
	{

	}

	//设置成员变量
	void Color::set_textedit(QTextEdit *main_textedit)
	{
		textedit_font = main_textedit;
	}

	void Color::set_resource_random_number(int number)
	{
		resource_randomnumber = number;

		//读入预置颜色
		ifstream setting_file;
		QString file_color_input = FILE_COLOR_OUTPUT_FILE_PATH_FRONT_STRING;
		file_color_input += QString::number(resource_randomnumber, 10);
		file_color_input += FILE_COLOR_OUTPUT_FILE_PATH_BACK_STRING;
		string file_color_input_final = string((const char *)file_color_input.toLocal8Bit());
		setting_file.open(file_color_input_final, ios_base::in);//打开文件
		int setting_color[3];//初始化设置
		string temp;//临时存储读入的字符串
		setting_file >> temp;//红
		if (!setting_file.is_open())//打开文件失败
		{
			setting_color[0] = 255;
		}
		else
		{
			setting_color[0] = atoi(temp.c_str());
		}
		setting_file >> temp;//绿
		if (!setting_file.is_open())
		{
			setting_color[1] = 255;
		}
		else
		{
			setting_color[1] = atoi(temp.c_str());
		}
		setting_file >> temp;//蓝
		if (!setting_file.is_open())
		{
			setting_color[2] = 255;
		}
		else
		{
			setting_color[2] = atoi(temp.c_str());
		}
		ui.spinBox_1->setValue(setting_color[0]);
		ui.spinBox_2->setValue(setting_color[1]);
		ui.spinBox_3->setValue(setting_color[2]);
		for (int flag = 0; flag < 24; flag++)//读入自定义颜色
		{
			string temp;//临时存储读入的字符串
			setting_file >> temp;//状态位
			if (!setting_file.is_open())//打开文件失败
			{
				color_status[flag] = 0;
			}
			else
			{
				color_status[flag] = atoi(temp.c_str());
			}
			setting_file >> temp;//红
			if (!setting_file.is_open())
			{
				color_red[flag] = 255;
			}
			else
			{
				color_red[flag] = atoi(temp.c_str());
			}
			setting_file >> temp;//绿
			if (!setting_file.is_open())
			{
				color_green[flag] = 255;
			}
			else
			{
				color_green[flag] = atoi(temp.c_str());
			}
			setting_file >> temp;//蓝
			if (!setting_file.is_open())
			{
				color_blue[flag] = 255;
			}
			else
			{
				color_blue[flag] = atoi(temp.c_str());
			}
		}
		setting_file.close();
		ui.pushButton_self_1->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[0], 10)).arg(QString::number(color_green[0], 10)).arg(QString::number(color_blue[0], 10)));
		ui.pushButton_self_2->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[1], 10)).arg(QString::number(color_green[1], 10)).arg(QString::number(color_blue[1], 10)));
		ui.pushButton_self_3->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[2], 10)).arg(QString::number(color_green[2], 10)).arg(QString::number(color_blue[2], 10)));
		ui.pushButton_self_4->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[3], 10)).arg(QString::number(color_green[3], 10)).arg(QString::number(color_blue[3], 10)));
		ui.pushButton_self_5->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[4], 10)).arg(QString::number(color_green[4], 10)).arg(QString::number(color_blue[4], 10)));
		ui.pushButton_self_6->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[5], 10)).arg(QString::number(color_green[5], 10)).arg(QString::number(color_blue[5], 10)));
		ui.pushButton_self_7->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[6], 10)).arg(QString::number(color_green[6], 10)).arg(QString::number(color_blue[6], 10)));
		ui.pushButton_self_8->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[7], 10)).arg(QString::number(color_green[7], 10)).arg(QString::number(color_blue[7], 10)));
		ui.pushButton_self_9->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[8], 10)).arg(QString::number(color_green[8], 10)).arg(QString::number(color_blue[8], 10)));
		ui.pushButton_self_10->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[9], 10)).arg(QString::number(color_green[9], 10)).arg(QString::number(color_blue[9], 10)));
		ui.pushButton_self_11->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[10], 10)).arg(QString::number(color_green[10], 10)).arg(QString::number(color_blue[10], 10)));
		ui.pushButton_self_12->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[11], 10)).arg(QString::number(color_green[11], 10)).arg(QString::number(color_blue[11], 10)));
		ui.pushButton_self_13->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[12], 10)).arg(QString::number(color_green[12], 10)).arg(QString::number(color_blue[12], 10)));
		ui.pushButton_self_14->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[13], 10)).arg(QString::number(color_green[13], 10)).arg(QString::number(color_blue[13], 10)));
		ui.pushButton_self_15->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[14], 10)).arg(QString::number(color_green[14], 10)).arg(QString::number(color_blue[14], 10)));
		ui.pushButton_self_16->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[15], 10)).arg(QString::number(color_green[15], 10)).arg(QString::number(color_blue[15], 10)));
		ui.pushButton_self_17->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[16], 10)).arg(QString::number(color_green[16], 10)).arg(QString::number(color_blue[16], 10)));
		ui.pushButton_self_18->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[17], 10)).arg(QString::number(color_green[17], 10)).arg(QString::number(color_blue[17], 10)));
		ui.pushButton_self_19->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[18], 10)).arg(QString::number(color_green[18], 10)).arg(QString::number(color_blue[18], 10)));
		ui.pushButton_self_20->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[19], 10)).arg(QString::number(color_green[19], 10)).arg(QString::number(color_blue[19], 10)));
		ui.pushButton_self_21->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[20], 10)).arg(QString::number(color_green[20], 10)).arg(QString::number(color_blue[20], 10)));
		ui.pushButton_self_22->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[21], 10)).arg(QString::number(color_green[21], 10)).arg(QString::number(color_blue[21], 10)));
		ui.pushButton_self_23->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[22], 10)).arg(QString::number(color_green[22], 10)).arg(QString::number(color_blue[22], 10)));
		ui.pushButton_self_24->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[23], 10)).arg(QString::number(color_green[23], 10)).arg(QString::number(color_blue[23], 10)));
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void Color::mousePressEvent(QMouseEvent *event)
	{
		if (select_color == 0)//未选取颜色状态
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
		else
		{
			int x = event->x();//横坐标
			int y = event->y();//纵坐标
			QPixmap color_pixmap = QPixmap::grabWindow(this->winId(), x, y, 1, 1);//截图，只需要一个像素
			QColor color_pix = QColor(color_pixmap.toImage().pixel(QPoint(0, 0)));//获得该像素点
			ui.label_1->setStyleSheet(QString("QLabel{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_pix.red(), 10)).arg(QString::number(color_pix.green(), 10)).arg(QString::number(color_pix.blue(), 10)));
			ui.spinBox_1->setValue(color_pix.red());
			ui.spinBox_2->setValue(color_pix.green());
			ui.spinBox_3->setValue(color_pix.blue());
			update();//重绘渐变色
		}
	}
	//若鼠标左键被按下，则移动窗体位置，并且进行取色
	void Color::mouseMoveEvent(QMouseEvent *event)
	{
		if (select_color == 0)//未选取颜色状态
		{
			if (m_bPressed)
			{
				move(event->pos() - m_point + pos());
			}
			else
			{

			}
		}
		else//选取颜色状态
		{

		}
	}

	//鼠标未被按下，则相应变量为false
	void Color::mouseReleaseEvent(QMouseEvent *event)
	{
		if (select_color == 0)//未选取颜色状态
		{
			Q_UNUSED(event);
			m_bPressed = false;
		}
		else
		{

		}
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉，因此这里除了修改回车键的功能，还要加上原来的esc键的功能
	void Color::keyPressEvent(QKeyEvent *event)
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

	void Color::paintEvent(QPaintEvent *)
	{

		//绘制窗口用到的图片。具体方法：首先指派5种背景风格。之后从5组随机数中选取一个，映射到其中一种风格上面。以下是对应的映射关系：[1,5]->ココア，[6,10]->チノ，[11,15]->リゼ，[16,20]->シャロ,[21,25]->千夜。此外，之后的其他图片也和构建背景使用的随机数有关。每个背景对应3张图片，每次随机选取1张。
		//以下功能用到了常量，如要修改最好重写
		//绘制图片
		QPainter background_painter(this);//背景
		QPainter margin_painter(this);//边框
		QPainter information_painter(this);//文字
		QPixmap background_picture;
		QPixmap margin_picture;
		QPixmap information_picture;
		dialog_information_path = DIALOG_INFORMATION_COLOR_PICTURE_PATH_STRING;//文字信息
		dialog_information_path += QString::number(totalrandomnumber, 10);//将随机数转化为路径中的一部分
		dialog_information_path += DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING;
		background_picture.load(filepath);
		margin_picture.load((QString)DIALOG_COLOR_MARGIN_PICTURE_PATH_STRING);
		information_picture.load(dialog_information_path);
		background_painter.drawPixmap(0, 0, DIALOG_COLOR_SIZE_WIDTH_NUMBER, DIALOG_COLOR_SIZE_HEIGHT_NUMBER, background_picture);
		information_painter.drawPixmap(0, 0, DIALOG_COLOR_SIZE_WIDTH_NUMBER, DIALOG_COLOR_SIZE_HEIGHT_NUMBER, information_picture);//文字部分应该从左边的图片部分的右边缘开始
		margin_painter.drawPixmap(0, 0, DIALOG_COLOR_SIZE_WIDTH_NUMBER, DIALOG_COLOR_SIZE_HEIGHT_NUMBER, margin_picture);//最后显示以免被图片覆盖
	
		//渐变填充右侧竖条部分，左侧部分直接用label显示
		if (forbid_change == 0)
		{
			QPainter right_painter(this);
			right_painter.setRenderHint(QPainter::Antialiasing, true);//反走样，消除锯齿
			QLinearGradient right_linearGradient(DIALOG_COLOR_SIZE_RIGHT_PAINT_MARGIN_1_NUMBER, DIALOG_COLOR_SIZE_RIGHT_PAINT_MARGIN_2_NUMBER, DIALOG_COLOR_SIZE_RIGHT_PAINT_MARGIN_3_NUMBER, DIALOG_COLOR_SIZE_RIGHT_PAINT_MARGIN_4_NUMBER);
			right_linearGradient.setColorAt(0, QColor(255, 255, 255, 255));//基准直线开始点为0，终点为1，分段设置颜色，从白色到指定色再到黑色 
			right_linearGradient.setColorAt(0.5, QColor(ui.spinBox_1->value(), ui.spinBox_2->value(), ui.spinBox_3->value(), 255));
			right_linearGradient.setColorAt(1, QColor(0, 0, 0, 255));
			right_painter.setBrush(right_linearGradient);
			right_painter.drawRect(DIALOG_COLOR_SIZE_RIGHT_PAINT_RECT_1_NUMBER, DIALOG_COLOR_SIZE_RIGHT_PAINT_RECT_2_NUMBER, DIALOG_COLOR_SIZE_RIGHT_PAINT_RECT_3_NUMBER, DIALOG_COLOR_SIZE_RIGHT_PAINT_RECT_4_NUMBER);//绘制矩形，需要确保线性渐变线正好在矩形的水平中心线上。参数为起始点x和y坐标以及矩形的宽和高
		}
		else
		{

		}
	}

	//修改颜色
	//以下功能用到了常量，如要修改最好重写
	void Color::color_change_1()
	{
		ui.spinBox_1->setValue(255);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(128);
	}
	void Color::color_change_2()
	{
		ui.spinBox_1->setValue(255);
		ui.spinBox_2->setValue(255);
		ui.spinBox_3->setValue(128);
	}
	void Color::color_change_3()
	{
		ui.spinBox_1->setValue(128);
		ui.spinBox_2->setValue(255);
		ui.spinBox_3->setValue(128);
	}
	void Color::color_change_4()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(255);
		ui.spinBox_3->setValue(128);
	}
	void Color::color_change_5()
	{
		ui.spinBox_1->setValue(128);
		ui.spinBox_2->setValue(255);
		ui.spinBox_3->setValue(255);
	}
	void Color::color_change_6()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(255);
	}
	void Color::color_change_7()
	{
		ui.spinBox_1->setValue(255);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(192);
	}
	void Color::color_change_8()
	{
		ui.spinBox_1->setValue(255);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(255);
	}
	void Color::color_change_9()
	{
		ui.spinBox_1->setValue(255);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(0);
	}
	void Color::color_change_10()
	{
		ui.spinBox_1->setValue(255);
		ui.spinBox_2->setValue(255);
		ui.spinBox_3->setValue(0);
	}
	void Color::color_change_11()
	{
		ui.spinBox_1->setValue(128);
		ui.spinBox_2->setValue(255);
		ui.spinBox_3->setValue(0);
	}
	void Color::color_change_12()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(255);
		ui.spinBox_3->setValue(64);
	}
	void Color::color_change_13()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(255);
		ui.spinBox_3->setValue(255);
	}
	void Color::color_change_14()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(192);
	}
	void Color::color_change_15()
	{
		ui.spinBox_1->setValue(128);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(192);
	}
	void Color::color_change_16()
	{
		ui.spinBox_1->setValue(255);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(255);
	}
	void Color::color_change_17()
	{
		ui.spinBox_1->setValue(128);
		ui.spinBox_2->setValue(64);
		ui.spinBox_3->setValue(64);
	}
	void Color::color_change_18()
	{
		ui.spinBox_1->setValue(255);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(64);
	}
	void Color::color_change_19()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(255);
		ui.spinBox_3->setValue(0);
	}
	void Color::color_change_20()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(128);
	}
	void Color::color_change_21()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(64);
		ui.spinBox_3->setValue(128);
	}
	void Color::color_change_22()
	{
		ui.spinBox_1->setValue(128);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(255);
	}
	void Color::color_change_23()
	{
		ui.spinBox_1->setValue(128);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(64);
	}
	void Color::color_change_24()
	{
		ui.spinBox_1->setValue(255);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(128);
	}
	void Color::color_change_25()
	{
		ui.spinBox_1->setValue(128);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(0);
	}
	void Color::color_change_26()
	{
		ui.spinBox_1->setValue(255);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(0);
	}
	void Color::color_change_27()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(0);
	}
	void Color::color_change_28()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(64);
	}
	void Color::color_change_29()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(255);
	}
	void Color::color_change_30()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(160);
	}
	void Color::color_change_31()
	{
		ui.spinBox_1->setValue(128);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(128);
	}
	void Color::color_change_32()
	{
		ui.spinBox_1->setValue(128);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(255);
	}
	void Color::color_change_33()
	{
		ui.spinBox_1->setValue(64);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(0);
	}
	void Color::color_change_34()
	{
		ui.spinBox_1->setValue(128);
		ui.spinBox_2->setValue(64);
		ui.spinBox_3->setValue(0);
	}
	void Color::color_change_35()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(64);
		ui.spinBox_3->setValue(0);
	}
	void Color::color_change_36()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(64);
		ui.spinBox_3->setValue(64);
	}
	void Color::color_change_37()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(128);
	}
	void Color::color_change_38()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(64);
	}
	void Color::color_change_39()
	{
		ui.spinBox_1->setValue(64);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(64);
	}
	void Color::color_change_40()
	{
		ui.spinBox_1->setValue(64);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(128);
	}
	void Color::color_change_41()
	{
		ui.spinBox_1->setValue(0);
		ui.spinBox_2->setValue(0);
		ui.spinBox_3->setValue(0);
	}
	void Color::color_change_42()
	{
		ui.spinBox_1->setValue(128);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(0);
	}
	void Color::color_change_43()
	{
		ui.spinBox_1->setValue(128);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(64);
	}
	void Color::color_change_44()
	{
		ui.spinBox_1->setValue(128);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(128);
	}
	void Color::color_change_45()
	{
		ui.spinBox_1->setValue(64);
		ui.spinBox_2->setValue(128);
		ui.spinBox_3->setValue(128);
	}
	void Color::color_change_46()
	{
		ui.spinBox_1->setValue(192);
		ui.spinBox_2->setValue(192);
		ui.spinBox_3->setValue(192);
	}
	void Color::color_change_47()
	{
		ui.spinBox_1->setValue(64);
		ui.spinBox_2->setValue(64);
		ui.spinBox_3->setValue(64);
	}
	void Color::color_change_48()
	{
		ui.spinBox_1->setValue(255);
		ui.spinBox_2->setValue(255);
		ui.spinBox_3->setValue(255);
	}
	void Color::color_change_self_1()
	{
		ui.spinBox_1->setValue(color_red[0]);
		ui.spinBox_2->setValue(color_green[0]);
		ui.spinBox_3->setValue(color_blue[0]);
	}
	void Color::color_change_self_2()
	{
		ui.spinBox_1->setValue(color_red[1]);
		ui.spinBox_2->setValue(color_green[1]);
		ui.spinBox_3->setValue(color_blue[1]);
	}
	void Color::color_change_self_3()
	{
		ui.spinBox_1->setValue(color_red[2]);
		ui.spinBox_2->setValue(color_green[2]);
		ui.spinBox_3->setValue(color_blue[2]);
	}
	void Color::color_change_self_4()
	{
		ui.spinBox_1->setValue(color_red[3]);
		ui.spinBox_2->setValue(color_green[3]);
		ui.spinBox_3->setValue(color_blue[3]);
	}
	void Color::color_change_self_5()
	{
		ui.spinBox_1->setValue(color_red[4]);
		ui.spinBox_2->setValue(color_green[4]);
		ui.spinBox_3->setValue(color_blue[4]);
	}
	void Color::color_change_self_6()
	{
		ui.spinBox_1->setValue(color_red[5]);
		ui.spinBox_2->setValue(color_green[5]);
		ui.spinBox_3->setValue(color_blue[5]);
	}
	void Color::color_change_self_7()
	{
		ui.spinBox_1->setValue(color_red[6]);
		ui.spinBox_2->setValue(color_green[6]);
		ui.spinBox_3->setValue(color_blue[6]);
	}
	void Color::color_change_self_8()
	{
		ui.spinBox_1->setValue(color_red[7]);
		ui.spinBox_2->setValue(color_green[7]);
		ui.spinBox_3->setValue(color_blue[7]);
	}
	void Color::color_change_self_9()
	{
		ui.spinBox_1->setValue(color_red[8]);
		ui.spinBox_2->setValue(color_green[8]);
		ui.spinBox_3->setValue(color_blue[8]);
	}
	void Color::color_change_self_10()
	{
		ui.spinBox_1->setValue(color_red[9]);
		ui.spinBox_2->setValue(color_green[9]);
		ui.spinBox_3->setValue(color_blue[9]);
	}
	void Color::color_change_self_11()
	{
		ui.spinBox_1->setValue(color_red[10]);
		ui.spinBox_2->setValue(color_green[10]);
		ui.spinBox_3->setValue(color_blue[10]);
	}
	void Color::color_change_self_12()
	{
		ui.spinBox_1->setValue(color_red[11]);
		ui.spinBox_2->setValue(color_green[11]);
		ui.spinBox_3->setValue(color_blue[11]);
	}
	void Color::color_change_self_13()
	{
		ui.spinBox_1->setValue(color_red[12]);
		ui.spinBox_2->setValue(color_green[12]);
		ui.spinBox_3->setValue(color_blue[12]);
	}
	void Color::color_change_self_14()
	{
		ui.spinBox_1->setValue(color_red[13]);
		ui.spinBox_2->setValue(color_green[13]);
		ui.spinBox_3->setValue(color_blue[13]);
	}
	void Color::color_change_self_15()
	{
		ui.spinBox_1->setValue(color_red[14]);
		ui.spinBox_2->setValue(color_green[14]);
		ui.spinBox_3->setValue(color_blue[14]);
	}
	void Color::color_change_self_16()
	{
		ui.spinBox_1->setValue(color_red[15]);
		ui.spinBox_2->setValue(color_green[15]);
		ui.spinBox_3->setValue(color_blue[15]);
	}
	void Color::color_change_self_17()
	{
		ui.spinBox_1->setValue(color_red[16]);
		ui.spinBox_2->setValue(color_green[16]);
		ui.spinBox_3->setValue(color_blue[16]);
	}
	void Color::color_change_self_18()
	{
		ui.spinBox_1->setValue(color_red[17]);
		ui.spinBox_2->setValue(color_green[17]);
		ui.spinBox_3->setValue(color_blue[17]);
	}
	void Color::color_change_self_19()
	{
		ui.spinBox_1->setValue(color_red[18]);
		ui.spinBox_2->setValue(color_green[18]);
		ui.spinBox_3->setValue(color_blue[18]);
	}
	void Color::color_change_self_20()
	{
		ui.spinBox_1->setValue(color_red[19]);
		ui.spinBox_2->setValue(color_green[19]);
		ui.spinBox_3->setValue(color_blue[19]);
	}
	void Color::color_change_self_21()
	{
		ui.spinBox_1->setValue(color_red[20]);
		ui.spinBox_2->setValue(color_green[20]);
		ui.spinBox_3->setValue(color_blue[20]);
	}
	void Color::color_change_self_22()
	{
		ui.spinBox_1->setValue(color_red[21]);
		ui.spinBox_2->setValue(color_green[21]);
		ui.spinBox_3->setValue(color_blue[21]);
	}
	void Color::color_change_self_23()
	{
		ui.spinBox_1->setValue(color_red[22]);
		ui.spinBox_2->setValue(color_green[22]);
		ui.spinBox_3->setValue(color_blue[22]);
	}
	void Color::color_change_self_24()
	{
		ui.spinBox_1->setValue(color_red[23]);
		ui.spinBox_2->setValue(color_green[23]);
		ui.spinBox_3->setValue(color_blue[23]);
	}

	//spinbox值改变后的操作
	void Color::color_change_spinbox(int number)
	{
		ui.label_1->setStyleSheet(QString("QLabel{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(ui.spinBox_1->value(), 10)).arg(QString::number(ui.spinBox_2->value(), 10)).arg(QString::number(ui.spinBox_3->value(), 10)));
		if (forbid_change == 0)//正常情况
		{
			disconnect(ui.verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(color_slider_change(int)));
			ui.verticalSlider->setValue(73);
			connect(ui.verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(color_slider_change(int)));
			update();//重绘渐变色
		}
		else//禁止改变右侧渐变颜色
		{

		}
	}

	//颜色选取
	void Color::color_select()//鼠标
	{
		if (select_color == 0)
		{
			select_color = 1;
			ui.pushButton_select->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_cancel_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_cancel_pressed.png);}");
		}
		else
		{
			select_color = 0;
			ui.pushButton_select->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_select_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_color_select_pressed.png);}");
		}
	}

	void Color::color_slider_change(int value)//滑块
	{
		forbid_change = 1;
		QPixmap slider_pixmap = QPixmap::grabWindow(this->winId(), DIALOG_COLOR_SLIDER_X_BEGIN_NUMBER, DIALOG_COLOR_SLIDER_Y_BEGIN_NUMBER + value, 1, 1);//截图，只需要一个像素
		QColor slider_pix = QColor(slider_pixmap.toImage().pixel(QPoint(0, 0)));//获得该像素点
		ui.label_1->setStyleSheet(QString("QLabel{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(slider_pix.red(), 10)).arg(QString::number(slider_pix.green(), 10)).arg(QString::number(slider_pix.blue(), 10)));
		ui.spinBox_1->setValue(slider_pix.red());
		ui.spinBox_2->setValue(slider_pix.green());
		ui.spinBox_3->setValue(slider_pix.blue());
		forbid_change = 0;
	}

	void Color::color_remove()//自定义颜色清除
	{
		for (int flag = 0; flag < 24; flag++)//颜色存储清空
		{
			color_status[flag] = 0;
			color_red[flag] = 255;
			color_green[flag] = 255;
			color_blue[flag] = 255;
		}
		ui.pushButton_self_1->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[0], 10)).arg(QString::number(color_green[0], 10)).arg(QString::number(color_blue[0], 10)));
		ui.pushButton_self_2->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[1], 10)).arg(QString::number(color_green[1], 10)).arg(QString::number(color_blue[1], 10)));
		ui.pushButton_self_3->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[2], 10)).arg(QString::number(color_green[2], 10)).arg(QString::number(color_blue[2], 10)));
		ui.pushButton_self_4->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[3], 10)).arg(QString::number(color_green[3], 10)).arg(QString::number(color_blue[3], 10)));
		ui.pushButton_self_5->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[4], 10)).arg(QString::number(color_green[4], 10)).arg(QString::number(color_blue[4], 10)));
		ui.pushButton_self_6->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[5], 10)).arg(QString::number(color_green[5], 10)).arg(QString::number(color_blue[5], 10)));
		ui.pushButton_self_7->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[6], 10)).arg(QString::number(color_green[6], 10)).arg(QString::number(color_blue[6], 10)));
		ui.pushButton_self_8->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[7], 10)).arg(QString::number(color_green[7], 10)).arg(QString::number(color_blue[7], 10)));
		ui.pushButton_self_9->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[8], 10)).arg(QString::number(color_green[8], 10)).arg(QString::number(color_blue[8], 10)));
		ui.pushButton_self_10->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[9], 10)).arg(QString::number(color_green[9], 10)).arg(QString::number(color_blue[9], 10)));
		ui.pushButton_self_11->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[10], 10)).arg(QString::number(color_green[10], 10)).arg(QString::number(color_blue[10], 10)));
		ui.pushButton_self_12->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[11], 10)).arg(QString::number(color_green[11], 10)).arg(QString::number(color_blue[11], 10)));
		ui.pushButton_self_13->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[12], 10)).arg(QString::number(color_green[12], 10)).arg(QString::number(color_blue[12], 10)));
		ui.pushButton_self_14->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[13], 10)).arg(QString::number(color_green[13], 10)).arg(QString::number(color_blue[13], 10)));
		ui.pushButton_self_15->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[14], 10)).arg(QString::number(color_green[14], 10)).arg(QString::number(color_blue[14], 10)));
		ui.pushButton_self_16->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[15], 10)).arg(QString::number(color_green[15], 10)).arg(QString::number(color_blue[15], 10)));
		ui.pushButton_self_17->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[16], 10)).arg(QString::number(color_green[16], 10)).arg(QString::number(color_blue[16], 10)));
		ui.pushButton_self_18->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[17], 10)).arg(QString::number(color_green[17], 10)).arg(QString::number(color_blue[17], 10)));
		ui.pushButton_self_19->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[18], 10)).arg(QString::number(color_green[18], 10)).arg(QString::number(color_blue[18], 10)));
		ui.pushButton_self_20->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[19], 10)).arg(QString::number(color_green[19], 10)).arg(QString::number(color_blue[19], 10)));
		ui.pushButton_self_21->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[20], 10)).arg(QString::number(color_green[20], 10)).arg(QString::number(color_blue[20], 10)));
		ui.pushButton_self_22->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[21], 10)).arg(QString::number(color_green[21], 10)).arg(QString::number(color_blue[21], 10)));
		ui.pushButton_self_23->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[22], 10)).arg(QString::number(color_green[22], 10)).arg(QString::number(color_blue[22], 10)));
		ui.pushButton_self_24->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[23], 10)).arg(QString::number(color_green[23], 10)).arg(QString::number(color_blue[23], 10)));
		ofstream setting_file;
		QString file_color_output = FILE_COLOR_OUTPUT_FILE_PATH_FRONT_STRING;
		file_color_output += QString::number(resource_randomnumber, 10);
		file_color_output += FILE_COLOR_OUTPUT_FILE_PATH_BACK_STRING;
		string file_color_output_final = string((const char *)file_color_output.toLocal8Bit());
		setting_file.open(file_color_output_final, ios_base::out);//打开文件，在文件末尾添加内容，若不存在则创建
		if (!setting_file.is_open())//打开文件失败
		{

		}
		else
		{
			setting_file << "255 ";
			setting_file << "255 ";
			setting_file << "255 ";
		}
		for (int flag = 0; flag < 24; flag++)//颜色存储清空
		{
			setting_file << "0 ";
			setting_file << "255 ";
			setting_file << "255 ";
			setting_file << "255 ";
		}
	}

	void Color::color_add()
	{
		int full = 1;//是否没有标记为0的颜色
		for (int flag = 0; flag < 24; flag++)//寻找标记为0也就是没有被使用的自定义颜色
		{
			if (color_status[flag] == 0)//若存在，设置颜色，写入文件并退出循环
			{
				ifstream in_file;
				QString file_color_input = FILE_COLOR_OUTPUT_FILE_PATH_FRONT_STRING;
				file_color_input += QString::number(resource_randomnumber, 10);
				file_color_input += FILE_COLOR_OUTPUT_FILE_PATH_BACK_STRING;
				string file_color_input_final = string((const char *)file_color_input.toLocal8Bit());
				in_file.open(file_color_input_final, ios_base::in);//打开文件，若不存在则创建
				int setting_color[3];//读入文字当前颜色
				string temp;//临时存储读入的字符串
				in_file >> temp;//红
				setting_color[0] = atoi(temp.c_str());
				in_file >> temp;//绿
				setting_color[1] = atoi(temp.c_str());
				in_file >> temp;//蓝
				setting_color[2] = atoi(temp.c_str());
				in_file.close();
				ofstream out_file;//写入文件
				QString file_color_output = FILE_COLOR_OUTPUT_FILE_PATH_FRONT_STRING;
				file_color_output += QString::number(resource_randomnumber, 10);
				file_color_output += FILE_COLOR_OUTPUT_FILE_PATH_BACK_STRING;
				string file_color_output_final = string((const char *)file_color_output.toLocal8Bit());
				out_file.open(file_color_output_final, ios_base::out);//写入文字当前颜色
				out_file << setting_color[0] << " " << setting_color[1] << " " << setting_color[2] << " ";
				if (!out_file.is_open())//打开文件失败
				{

				}
				else//写入内容
				{
					color_status[flag] = 1;
					color_red[flag] = ui.spinBox_1->value();
					color_green[flag] = ui.spinBox_2->value();
					color_blue[flag] = ui.spinBox_3->value();
					for (int flag = 0; flag < 24; flag++)
					{
						out_file << color_status[flag] << " ";
						out_file << color_red[flag] << " ";
						out_file << color_green[flag] << " ";
						out_file << color_blue[flag] << " ";
					}
					ui.pushButton_self_1->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[0], 10)).arg(QString::number(color_green[0], 10)).arg(QString::number(color_blue[0], 10)));
					ui.pushButton_self_2->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[1], 10)).arg(QString::number(color_green[1], 10)).arg(QString::number(color_blue[1], 10)));
					ui.pushButton_self_3->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[2], 10)).arg(QString::number(color_green[2], 10)).arg(QString::number(color_blue[2], 10)));
					ui.pushButton_self_4->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[3], 10)).arg(QString::number(color_green[3], 10)).arg(QString::number(color_blue[3], 10)));
					ui.pushButton_self_5->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[4], 10)).arg(QString::number(color_green[4], 10)).arg(QString::number(color_blue[4], 10)));
					ui.pushButton_self_6->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[5], 10)).arg(QString::number(color_green[5], 10)).arg(QString::number(color_blue[5], 10)));
					ui.pushButton_self_7->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[6], 10)).arg(QString::number(color_green[6], 10)).arg(QString::number(color_blue[6], 10)));
					ui.pushButton_self_8->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[7], 10)).arg(QString::number(color_green[7], 10)).arg(QString::number(color_blue[7], 10)));
					ui.pushButton_self_9->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[8], 10)).arg(QString::number(color_green[8], 10)).arg(QString::number(color_blue[8], 10)));
					ui.pushButton_self_10->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[9], 10)).arg(QString::number(color_green[9], 10)).arg(QString::number(color_blue[9], 10)));
					ui.pushButton_self_11->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[10], 10)).arg(QString::number(color_green[10], 10)).arg(QString::number(color_blue[10], 10)));
					ui.pushButton_self_12->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[11], 10)).arg(QString::number(color_green[11], 10)).arg(QString::number(color_blue[11], 10)));
					ui.pushButton_self_13->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[12], 10)).arg(QString::number(color_green[12], 10)).arg(QString::number(color_blue[12], 10)));
					ui.pushButton_self_14->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[13], 10)).arg(QString::number(color_green[13], 10)).arg(QString::number(color_blue[13], 10)));
					ui.pushButton_self_15->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[14], 10)).arg(QString::number(color_green[14], 10)).arg(QString::number(color_blue[14], 10)));
					ui.pushButton_self_16->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[15], 10)).arg(QString::number(color_green[15], 10)).arg(QString::number(color_blue[15], 10)));
					ui.pushButton_self_17->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[16], 10)).arg(QString::number(color_green[16], 10)).arg(QString::number(color_blue[16], 10)));
					ui.pushButton_self_18->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[17], 10)).arg(QString::number(color_green[17], 10)).arg(QString::number(color_blue[17], 10)));
					ui.pushButton_self_19->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[18], 10)).arg(QString::number(color_green[18], 10)).arg(QString::number(color_blue[18], 10)));
					ui.pushButton_self_20->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[19], 10)).arg(QString::number(color_green[19], 10)).arg(QString::number(color_blue[19], 10)));
					ui.pushButton_self_21->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[20], 10)).arg(QString::number(color_green[20], 10)).arg(QString::number(color_blue[20], 10)));
					ui.pushButton_self_22->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[21], 10)).arg(QString::number(color_green[21], 10)).arg(QString::number(color_blue[21], 10)));
					ui.pushButton_self_23->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[22], 10)).arg(QString::number(color_green[22], 10)).arg(QString::number(color_blue[22], 10)));
					ui.pushButton_self_24->setStyleSheet(QString("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid rgb(128, 76, 71);}").arg(QString::number(color_red[23], 10)).arg(QString::number(color_green[23], 10)).arg(QString::number(color_blue[23], 10)));
					full = 0;//添加成功
					break;
					out_file.close();
				}
			}
		}
		if (full == 1)//添加失败
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("出错了哦……"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_COLOR_CANNOT_ADD_PICTURE_PATH_STRING);
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void Color::color_accept()
	{
		ofstream out_file;//写入文件
		ofstream setting_file;
		QString file_color_output = FILE_COLOR_OUTPUT_FILE_PATH_FRONT_STRING;
		file_color_output += QString::number(resource_randomnumber, 10);
		file_color_output += FILE_COLOR_OUTPUT_FILE_PATH_BACK_STRING;
		string file_color_output_final = string((const char *)file_color_output.toLocal8Bit());
		out_file.open(file_color_output_final, ios_base::out);//写入文字当前颜色
		out_file << ui.spinBox_1->value() << " " << ui.spinBox_2->value() << " " << ui.spinBox_3->value() << " ";
		for (int flag = 0; flag < 24; flag++)//写入颜色
		{
			out_file << color_status[flag] << " ";
			out_file << color_red[flag] << " ";
			out_file << color_green[flag] << " ";
			out_file << color_blue[flag] << " ";
		}
		out_file.close();
		QPalette edit_palette;//设置文本框颜色
		edit_palette.setColor(QPalette::Text, QColor(ui.spinBox_1->value(), ui.spinBox_2->value(), ui.spinBox_3->value(), 255));
		edit_palette.setColor(QPalette::Highlight, QColor(153, 86, 33, 255));
		textedit_font->setPalette(edit_palette);
		close_window_include_animation();//关闭颜色
	}

	void Color::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

