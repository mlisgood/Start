#include "define.h"

namespace rem
{

	//使用标准命名空间
	using std::string;

	//构造与析构函数
	Print::Print(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		totalrandomnumber = DIALOG_RANDOM_MIN_NUMBER + rand() % (DIALOG_RANDOM_MAX_NUMBER - DIALOG_RANDOM_MIN_NUMBER + 1);//产生指定随机数以便决定背景图片和人物图片样式
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		resize(DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		is_escape_pressed = false;//允许按下esc键退出程序

		//图片路径
		//背景图片路径
		filepath = DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING + QString::number(totalrandomnumber, 10);
		filepath += DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING;

		//左侧图片路径
		chara_path = DIALOG_CHARA_PICTURE_PATH_FRONT_STRING;
		QString chara_path_number = QString::number(totalrandomnumber, 10);//将随机数转化为路径中的一部分
		chara_path += chara_path_number;
		chara_path += DIALOG_CHARA_PICTURE_PATH_BREAK_STRING;
		chara_path += QString::number(DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER + rand() % (DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER - DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER + 1), 10);//从当前系列的3张图片当中选取一张并增加到路径中
		chara_path += DIALOG_CHARA_PICTURE_PATH_BACK_STRING;

		//加载界面，必须放在最后以避免界面被之后的绘图覆盖
		ui.setupUi(this);

		//加载按钮样式
		ui.pushButton_close_dialog->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_pressed.png);}");
		ui.pushButton_accept_dialog->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_pressed.png);}");

		//设置文字颜色
		QPalette lineedit_palette;
		if (totalrandomnumber == 1)//决定相关文字颜色
		{
			lineedit_palette.setColor(QPalette::Text, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(255, 83, 185, 64));
		}
		else if (totalrandomnumber == 2)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(133, 153, 212, 64));
		}
		else if (totalrandomnumber == 3)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(222, 63, 235, 64));
		}
		else if (totalrandomnumber == 4)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(242, 153, 93, 64));
		}
		else if (totalrandomnumber == 5)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(71, 185, 78, 64));
		}
		else
		{

		}
		ui.comboBox_printer->setPalette(lineedit_palette);
		ui.comboBox_size->setPalette(lineedit_palette);
		ui.spinBox_up->setPalette(lineedit_palette);
		ui.spinBox_down->setPalette(lineedit_palette);
		ui.spinBox_left->setPalette(lineedit_palette);
		ui.spinBox_right->setPalette(lineedit_palette);

		//加载样式文件，这里直接使用字体设置窗口中的样式文件即可
		QString stylesheet_file_name = DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_STRING;
		stylesheet_file_name += QString::number(totalrandomnumber, 10);
		stylesheet_file_name += DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_BACK_STRING;
		QFile stylesheet_file_1(stylesheet_file_name);
		QFile stylesheet_file_2(stylesheet_file_name);
		stylesheet_file_1.open(QFile::ReadOnly);
		stylesheet_file_2.open(QFile::ReadOnly);
		ui.comboBox_printer->setStyleSheet(stylesheet_file_1.readAll());
		ui.comboBox_size->setStyleSheet(stylesheet_file_2.readAll());
		stylesheet_file_1.close();
		stylesheet_file_2.close();

		//设置初始打印机选项
		QStringList printer_name_list;//打印机设备名称
		printer_name_list = QPrinterInfo::availablePrinterNames();//获取系统可用打印机名称
		foreach(QString printer_name, printer_name_list)
		{
			ui.comboBox_printer->addItem(printer_name);
		}
		QString size_string;//由于页面尺寸选项过多，为方便起见直接使用代码写入
		for (int temp = 0; temp < 11; temp++)
		{
			size_string = tr("A") + QString::number(temp, 10);
			ui.comboBox_size->addItem(size_string);
		}
		for (int temp = 0; temp < 11; temp++)
		{
			size_string = tr("B") + QString::number(temp, 10);
			ui.comboBox_size->addItem(size_string);
		}
		ui.comboBox_size->addItem(tr("C5E"));
		ui.comboBox_size->addItem(tr("Comm10E"));
		ui.comboBox_size->addItem(tr("DLE"));
		ui.comboBox_size->addItem(tr("Executive"));
		ui.comboBox_size->addItem(tr("Folio"));
		ui.comboBox_size->addItem(tr("Ledger"));
		ui.comboBox_size->addItem(tr("Legal"));
		ui.comboBox_size->addItem(tr("Letter"));
		ui.comboBox_size->addItem(tr("Tabloid"));
		ui.comboBox_size->addItem(tr("Custom"));
		ui.comboBox_size->addItem(tr("A3Extra"));
		ui.comboBox_size->addItem(tr("A4Extra"));
		ui.comboBox_size->addItem(tr("A4Plus"));
		ui.comboBox_size->addItem(tr("A4Small"));
		ui.comboBox_size->addItem(tr("A5Extra"));
		ui.comboBox_size->addItem(tr("B5Extra"));
		for (int temp = 0; temp < 11; temp++)
		{
			size_string = tr("JisB") + QString::number(temp, 10);
			ui.comboBox_size->addItem(size_string);
		}
		ui.comboBox_size->addItem(tr("AnsiA"));
		ui.comboBox_size->addItem(tr("AnsiB"));
		ui.comboBox_size->addItem(tr("AnsiC"));
		ui.comboBox_size->addItem(tr("AnsiD"));
		ui.comboBox_size->addItem(tr("AnsiE"));
		ui.comboBox_size->addItem(tr("LegalExtra"));
		ui.comboBox_size->addItem(tr("LetterExtra"));
		ui.comboBox_size->addItem(tr("LetterPlus"));
		ui.comboBox_size->addItem(tr("LetterSmall"));
		ui.comboBox_size->addItem(tr("TabloidExtra"));
		ui.comboBox_size->addItem(tr("ArchA"));
		ui.comboBox_size->addItem(tr("ArchB"));
		ui.comboBox_size->addItem(tr("ArchC"));
		ui.comboBox_size->addItem(tr("ArchD"));
		ui.comboBox_size->addItem(tr("ArchE"));
		ui.comboBox_size->addItem(tr("Imperial7x9"));
		ui.comboBox_size->addItem(tr("Imperial8x10"));
		ui.comboBox_size->addItem(tr("Imperial9x11"));
		ui.comboBox_size->addItem(tr("Imperial9x12"));
		ui.comboBox_size->addItem(tr("Imperial10x11"));
		ui.comboBox_size->addItem(tr("Imperial10x13"));
		ui.comboBox_size->addItem(tr("Imperial10x14"));
		ui.comboBox_size->addItem(tr("Imperial12x11"));
		ui.comboBox_size->addItem(tr("Imperial15x11"));
		ui.comboBox_size->addItem(tr("ExecutiveStandard"));
		ui.comboBox_size->addItem(tr("Note"));
		ui.comboBox_size->addItem(tr("Quarto"));
		ui.comboBox_size->addItem(tr("Statement"));
		ui.comboBox_size->addItem(tr("SuperA"));
		ui.comboBox_size->addItem(tr("SuperB"));
		ui.comboBox_size->addItem(tr("Postcard"));
		ui.comboBox_size->addItem(tr("DoublePostcard"));
		ui.comboBox_size->addItem(tr("Prc16K"));
		ui.comboBox_size->addItem(tr("Prc32K"));
		ui.comboBox_size->addItem(tr("Prc32KBig"));
		ui.comboBox_size->addItem(tr("FanFoldUS"));
		ui.comboBox_size->addItem(tr("FanFoldGerman"));
		ui.comboBox_size->addItem(tr("FanFoldGermanLegal"));
		ui.comboBox_size->addItem(tr("EnvelopeB4"));
		ui.comboBox_size->addItem(tr("EnvelopeB5"));
		ui.comboBox_size->addItem(tr("EnvelopeB6"));
		for (int temp = 0; temp < 8; temp++)
		{
			size_string = tr("EnvelopeC") + QString::number(temp, 10);
			ui.comboBox_size->addItem(size_string);
		}
		ui.comboBox_size->addItem(tr("EnvelopeC65"));
		ui.comboBox_size->addItem(tr("EnvelopeDL"));
		for (int temp = 9; temp < 13; temp++)
		{
			size_string = tr("Envelope") + QString::number(temp, 10);
			ui.comboBox_size->addItem(size_string);
		}
		ui.comboBox_size->addItem(tr("Envelope14"));
		ui.comboBox_size->addItem(tr("EnvelopeMonarch"));
		ui.comboBox_size->addItem(tr("EnvelopePersonal"));
		ui.comboBox_size->addItem(tr("EnvelopeChou3"));
		ui.comboBox_size->addItem(tr("EnvelopeChou4"));
		ui.comboBox_size->addItem(tr("EnvelopeInvite"));
		ui.comboBox_size->addItem(tr("EnvelopeItalian"));
		ui.comboBox_size->addItem(tr("EnvelopeKaku2"));
		ui.comboBox_size->addItem(tr("EnvelopeKaku3"));
		for (int temp = 1; temp < 11; temp++)
		{
			size_string = tr("EnvelopePrc") + QString::number(temp, 10);
			ui.comboBox_size->addItem(size_string);
		}
		ui.comboBox_size->addItem(tr("EnvelopeYou4"));
		ui.comboBox_size->setCurrentText(tr("A4"));//默认纸张大小

		//去掉关联性控件的右键菜单
		QList<QScrollBar *> scroll_bar = this->findChildren<QScrollBar *>();//由于无法用常规方式获得combobox的滚动条，因此使用该方法查找所有同类型控件并进行操作
		foreach(QScrollBar *scroll_bar_style_control, scroll_bar)
		{
			scroll_bar_style_control->setContextMenuPolicy(Qt::NoContextMenu);
		}

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存

		//关闭按钮
		connect(ui.pushButton_close_window, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));
		connect(ui.pushButton_close_dialog, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));

		//确定按钮
		connect(ui.pushButton_accept_dialog, SIGNAL(clicked()), this, SLOT(dialog_accept()));

		//绘制窗口用到的图片。具体方法：首先指派5种背景风格。之后从5组随机数中选取一个，映射到其中一种风格上面。以下是对应的映射关系：[1,5]->ココア，[6,10]->チノ，[11,15]->リゼ，[16,20]->シャロ,[21,25]->千夜。此外，之后的其他图片也和构建背景使用的随机数有关。每个背景对应3张图片，每次随机选取1张。
		//以下功能用到了常量，如要修改最好重写
		//绘制图片
		QString dialog_information_path_temp;//临时存储信息图片路径
		QPixmap background_picture;
		QPixmap margin_picture;
		QPixmap chara_picture;
		QPixmap information_picture;
		dialog_information_path_temp = DIALOG_INFORMATION_PRINT_PICTURE_PATH_STRING;
		dialog_information_path_temp += QString::number(totalrandomnumber, 10);//将随机数转化为路径中的一部分
		dialog_information_path_temp += DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING;
		background_picture.load(filepath);
		margin_picture.load((QString)DIALOG_MARGIN_PICTURE_PATH_STRING);
		chara_picture.load(chara_path);
		information_picture.load(dialog_information_path_temp);
		ui.label_pixmap_background->setPixmap(background_picture);//不能使用painter，因为在打印时出现由打印过程产生的其他窗口的时候，该界面响应paintEvent事件时会使所有图片无法显示，此时主界面和其他非模态子窗口因为此模态窗口的原因无法响应该事件，不会出现此情况。目前用setpixmap方法进行规避。label已经按顺序在界面文件中放置
		ui.label_pixmap_chara->setPixmap(chara_picture);
		ui.label_pixmap_information->setPixmap(information_picture);
		ui.label_pixmap_margin->setPixmap(margin_picture);
	}
	Print::~Print()
	{

	}

	//设置成员变量
	void Print::set_textedit(QTextEdit *main_textedit)//获取文本框地址
	{
		textedit_print = main_textedit;
	}

	void Print::set_timer(QTimer *main_timer)//获取主界面计时器地址
	{
		timer_print = main_timer;
	}

	void Print::set_label_chara(QLabel *main_label)//获取主界面人物形象标签地址
	{
		label_chara_print = main_label;
	}

	void Print::set_label_margin(QLabel *main_label)//获取主界面左侧边界标签地址
	{
		label_margin_print = main_label;
	}

	void Print::set_chara_path(QString main_chara_path)//获取主界面人物形象正常状态路径
	{
		chara_path_print = main_chara_path;
	}

	void Print::set_flag(int *main_flag)//获取主界面计时器状态
	{
		flag_print = main_flag;
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void Print::mousePressEvent(QMouseEvent *event)
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
	void Print::mouseMoveEvent(QMouseEvent *event)
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
	void Print::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉。这个窗口因为只有确认操作，本来不需要重写，但为了保持统一，还是进行了重写
	void Print::keyPressEvent(QKeyEvent *event)
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

	void Print::dialog_accept()//确认操作
	{
		timer_print->stop();//经过运行，发现在打印时出现有打印过程产生的其他窗口的时候，如果停留在其他窗口上，主界面左侧通过计时器绘制的图片会在下一个计时周期消失。目前只能通过停止主界面计时器解决
		QPixmap chara_temp;//主界面重绘以免引起冲突
		QPixmap margin_temp;
		chara_temp.load(chara_path_print);
		margin_temp.load((QString)WINDOW_MARGIN_PICTURE_LEFT_PATH_STRING);
		label_chara_print->setPixmap(chara_temp);//人物形象
		label_margin_print->setPixmap(margin_temp);//左侧边界
		QPrinter printer;//创建打印机对象
		printer.setPrinterName(ui.comboBox_printer->currentText());//打印机名称
		int index = ui.comboBox_printer->currentIndex();//页面尺寸设置，按选项序号分别设置枚举类型
		switch (index)//设置页面尺寸
		{
		case 0:
			printer.setPageSize(QPageSize(QPageSize::A0));
			break;
		case 1:
			printer.setPageSize(QPageSize(QPageSize::A1));
			break;
		case 2:
			printer.setPageSize(QPageSize(QPageSize::A2));
			break;
		case 3:
			printer.setPageSize(QPageSize(QPageSize::A3));
			break;
		case 4:
			printer.setPageSize(QPageSize(QPageSize::A4));
			break;
		case 5:
			printer.setPageSize(QPageSize(QPageSize::A5));
			break;
		case 6:
			printer.setPageSize(QPageSize(QPageSize::A6));
			break;
		case 7:
			printer.setPageSize(QPageSize(QPageSize::A7));
			break;
		case 8:
			printer.setPageSize(QPageSize(QPageSize::A8));
			break;
		case 9:
			printer.setPageSize(QPageSize(QPageSize::A9));
			break;
		case 10:
			printer.setPageSize(QPageSize(QPageSize::B0));
			break;
		case 11:
			printer.setPageSize(QPageSize(QPageSize::B1));
			break;
		case 12:
			printer.setPageSize(QPageSize(QPageSize::B2));
			break;
		case 13:
			printer.setPageSize(QPageSize(QPageSize::B3));
			break;
		case 14:
			printer.setPageSize(QPageSize(QPageSize::B4));
			break;
		case 15:
			printer.setPageSize(QPageSize(QPageSize::B5));
			break;
		case 16:
			printer.setPageSize(QPageSize(QPageSize::B6));
			break;
		case 17:
			printer.setPageSize(QPageSize(QPageSize::B7));
			break;
		case 18:
			printer.setPageSize(QPageSize(QPageSize::B8));
			break;
		case 19:
			printer.setPageSize(QPageSize(QPageSize::B9));
			break;
		case 20:
			printer.setPageSize(QPageSize(QPageSize::B10));
			break;
		case 21:
			printer.setPageSize(QPageSize(QPageSize::C5E));
			break;
		case 22:
			printer.setPageSize(QPageSize(QPageSize::Comm10E));
			break;
		case 23:
			printer.setPageSize(QPageSize(QPageSize::DLE));
			break;
		case 24:
			printer.setPageSize(QPageSize(QPageSize::Executive));
			break;
		case 25:
			printer.setPageSize(QPageSize(QPageSize::Folio));
			break;
		case 26:
			printer.setPageSize(QPageSize(QPageSize::Ledger));
			break;
		case 27:
			printer.setPageSize(QPageSize(QPageSize::Legal));
			break;
		case 28:
			printer.setPageSize(QPageSize(QPageSize::Letter));
			break;
		case 29:
			printer.setPageSize(QPageSize(QPageSize::Tabloid));
			break;
		case 30:
			printer.setPageSize(QPageSize(QPageSize::Custom));
			break;
		case 31:
			printer.setPageSize(QPageSize(QPageSize::A10));
			break;
		case 32:
			printer.setPageSize(QPageSize(QPageSize::A3Extra));
			break;
		case 33:
			printer.setPageSize(QPageSize(QPageSize::A4Extra));
			break;
		case 34:
			printer.setPageSize(QPageSize(QPageSize::A4Plus));
			break;
		case 35:
			printer.setPageSize(QPageSize(QPageSize::A4Small));
			break;
		case 36:
			printer.setPageSize(QPageSize(QPageSize::A5Extra));
			break;
		case 37:
			printer.setPageSize(QPageSize(QPageSize::B5Extra));
			break;
		case 38:
			printer.setPageSize(QPageSize(QPageSize::JisB0));
			break;
		case 39:
			printer.setPageSize(QPageSize(QPageSize::JisB1));
			break;
		case 40:
			printer.setPageSize(QPageSize(QPageSize::JisB2));
			break;
		case 41:
			printer.setPageSize(QPageSize(QPageSize::JisB3));
			break;
		case 42:
			printer.setPageSize(QPageSize(QPageSize::JisB4));
			break;
		case 43:
			printer.setPageSize(QPageSize(QPageSize::JisB5));
			break;
		case 44:
			printer.setPageSize(QPageSize(QPageSize::JisB6));
			break;
		case 45:
			printer.setPageSize(QPageSize(QPageSize::JisB7));
			break;
		case 46:
			printer.setPageSize(QPageSize(QPageSize::JisB8));
			break;
		case 47:
			printer.setPageSize(QPageSize(QPageSize::JisB9));
			break;
		case 48:
			printer.setPageSize(QPageSize(QPageSize::JisB10));
			break;
		case 49:
			printer.setPageSize(QPageSize(QPageSize::AnsiA));
			break;
		case 50:
			printer.setPageSize(QPageSize(QPageSize::AnsiB));
			break;
		case 51:
			printer.setPageSize(QPageSize(QPageSize::AnsiC));
			break;
		case 52:
			printer.setPageSize(QPageSize(QPageSize::AnsiD));
			break;
		case 53:
			printer.setPageSize(QPageSize(QPageSize::AnsiE));
			break;
		case 54:
			printer.setPageSize(QPageSize(QPageSize::LegalExtra));
			break;
		case 55:
			printer.setPageSize(QPageSize(QPageSize::LetterExtra));
			break;
		case 56:
			printer.setPageSize(QPageSize(QPageSize::LetterPlus));
			break;
		case 57:
			printer.setPageSize(QPageSize(QPageSize::LetterSmall));
			break;
		case 58:
			printer.setPageSize(QPageSize(QPageSize::TabloidExtra));
			break;
		case 59:
			printer.setPageSize(QPageSize(QPageSize::ArchA));
			break;
		case 60:
			printer.setPageSize(QPageSize(QPageSize::ArchB));
			break;
		case 61:
			printer.setPageSize(QPageSize(QPageSize::ArchC));
			break;
		case 62:
			printer.setPageSize(QPageSize(QPageSize::ArchD));
			break;
		case 63:
			printer.setPageSize(QPageSize(QPageSize::ArchE));
			break;
		case 64:
			printer.setPageSize(QPageSize(QPageSize::Imperial7x9));
			break;
		case 65:
			printer.setPageSize(QPageSize(QPageSize::Imperial8x10));
			break;
		case 66:
			printer.setPageSize(QPageSize(QPageSize::Imperial9x11));
			break;
		case 67:
			printer.setPageSize(QPageSize(QPageSize::Imperial9x12));
			break;
		case 68:
			printer.setPageSize(QPageSize(QPageSize::Imperial10x11));
			break;
		case 69:
			printer.setPageSize(QPageSize(QPageSize::Imperial10x13));
			break;
		case 70:
			printer.setPageSize(QPageSize(QPageSize::Imperial10x14));
			break;
		case 71:
			printer.setPageSize(QPageSize(QPageSize::Imperial12x11));
			break;
		case 72:
			printer.setPageSize(QPageSize(QPageSize::Imperial15x11));
			break;
		case 73:
			printer.setPageSize(QPageSize(QPageSize::ExecutiveStandard));
			break;
		case 74:
			printer.setPageSize(QPageSize(QPageSize::Note));
			break;
		case 75:
			printer.setPageSize(QPageSize(QPageSize::Quarto));
			break;
		case 76:
			printer.setPageSize(QPageSize(QPageSize::Statement));
			break;
		case 77:
			printer.setPageSize(QPageSize(QPageSize::SuperA));
			break;
		case 78:
			printer.setPageSize(QPageSize(QPageSize::SuperB));
			break;
		case 79:
			printer.setPageSize(QPageSize(QPageSize::Postcard));
			break;
		case 80:
			printer.setPageSize(QPageSize(QPageSize::DoublePostcard));
			break;
		case 81:
			printer.setPageSize(QPageSize(QPageSize::Prc16K));
			break;
		case 82:
			printer.setPageSize(QPageSize(QPageSize::Prc32K));
			break;
		case 83:
			printer.setPageSize(QPageSize(QPageSize::Prc32KBig));
			break;
		case 84:
			printer.setPageSize(QPageSize(QPageSize::FanFoldUS));
			break;
		case 85:
			printer.setPageSize(QPageSize(QPageSize::FanFoldGerman));
			break;
		case 86:
			printer.setPageSize(QPageSize(QPageSize::FanFoldGermanLegal));
			break;
		case 87:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeB4));
			break;
		case 88:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeB5));
			break;
		case 89:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeB6));
			break;
		case 90:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeC0));
			break;
		case 91:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeC1));
			break;
		case 92:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeC2));
			break;
		case 93:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeC3));
			break;
		case 94:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeC4));
			break;
		case 95:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeC5));
			break;
		case 96:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeC6));
			break;
		case 97:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeC7));
			break;
		case 98:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeC65));
			break;
		case 99:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeDL));
			break;
		case 100:
			printer.setPageSize(QPageSize(QPageSize::Envelope9));
			break;
		case 101:
			printer.setPageSize(QPageSize(QPageSize::Envelope10));
			break;
		case 102:
			printer.setPageSize(QPageSize(QPageSize::Envelope11));
			break;
		case 103:
			printer.setPageSize(QPageSize(QPageSize::Envelope12));
			break;
		case 104:
			printer.setPageSize(QPageSize(QPageSize::Envelope14));
			break;
		case 105:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeMonarch));
			break;
		case 106:
			printer.setPageSize(QPageSize(QPageSize::EnvelopePersonal));
			break;
		case 107:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeChou3));
			break;
		case 108:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeChou4));
			break;
		case 109:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeInvite));
			break;
		case 110:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeItalian));
			break;
		case 111:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeKaku2));
			break;
		case 112:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeKaku3));
			break;
		case 113:
			printer.setPageSize(QPageSize(QPageSize::EnvelopePrc1));
			break;
		case 114:
			printer.setPageSize(QPageSize(QPageSize::EnvelopePrc2));
			break;
		case 115:
			printer.setPageSize(QPageSize(QPageSize::EnvelopePrc3));
			break;
		case 116:
			printer.setPageSize(QPageSize(QPageSize::EnvelopePrc4));
			break;
		case 117:
			printer.setPageSize(QPageSize(QPageSize::EnvelopePrc5));
			break;
		case 118:
			printer.setPageSize(QPageSize(QPageSize::EnvelopePrc6));
			break;
		case 119:
			printer.setPageSize(QPageSize(QPageSize::EnvelopePrc7));
			break;
		case 120:
			printer.setPageSize(QPageSize(QPageSize::EnvelopePrc8));
			break;
		case 121:
			printer.setPageSize(QPageSize(QPageSize::EnvelopePrc9));
			break;
		case 122:
			printer.setPageSize(QPageSize(QPageSize::EnvelopePrc10));
			break;
		case 123:
			printer.setPageSize(QPageSize(QPageSize::EnvelopeYou4));
			break;
		default:
			printer.setPageSize(QPageSize(QPageSize::A4));
			break;
		}
		printer.setPageMargins(QMarginsF(ui.spinBox_left->value(), ui.spinBox_up->value(), ui.spinBox_right->value(), ui.spinBox_down->value()));//设置页边距
		if (ui.radioButton_1->isChecked())//设置纸张方向
		{
			printer.setPageOrientation(QPageLayout::Landscape);//横向
		}
		else
		{
			printer.setPageOrientation(QPageLayout::Portrait);//纵向
		}
		textedit_print->print(&printer);//打印
		close_window_include_animation();//关闭窗口
		chara_temp.load(chara_path_print);//主界面重绘并重新设置计时器参数以免引起冲突
		margin_temp.load((QString)WINDOW_MARGIN_PICTURE_LEFT_PATH_STRING);
		label_chara_print->setPixmap(chara_temp);//人物形象
		label_margin_print->setPixmap(margin_temp);//左侧边界
		*flag_print = WINDOW_CHARA_NORMAL_FLAG;
		timer_print->setInterval(WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER + rand() % (WINDOW_RANDOM_TIMER_CHARA_NORMAL_MAX_NUMBER - WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER + 1));
		timer_print->start();
	}

	void Print::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

