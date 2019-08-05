#include "define.h"

namespace rem
{

	//使用标准命名空间
	using std::string;

	//导入crypto++命名空间
	using namespace CryptoPP;

	//构造与析构函数
	LockNormalHashCalculate::LockNormalHashCalculate(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		resize(DIALOG_LOCK_SIZE_WIDTH_NUMBER, DIALOG_LOCK_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		is_escape_pressed = false;//允许按下esc键退出程序

		//计时器
		timer_picture_count = DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER + rand() % (DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER - DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER + 1);//产生指定随机数。仅在构造函数中使用一次，以保证不会出现隐藏并打开窗口后背景因为重新绘图发生变化的问题
		timer_transparent_count = 0;//图片初始透明度设定
		timer_interval = DIALOG_LOCK_CHARA_PICTURE_COUNT_INTERVAL_NUMNER;//初始图片的轮播间隔为标准的切换图片间隔
		timer = new QTimer(this);//初始化计时器
		timer->setTimerType(Qt::PreciseTimer);//修改精度
		connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));//信号处理
		timer->start(timer_interval);

		//加载界面，必须放在最后以避免界面被之后的绘图覆盖
		ui.setupUi(this);

		//按钮
		ui.pushButton_1->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_19.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_19.png);}");
		ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_18.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_18.png);}");
		ui.pushButton_3->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_3.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_3.png);}");
		ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_20.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_20.png);}");

		//信号函数
		connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(file_explore()));//加密文件
		connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(calculate_file()));//解密文件
		connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//返回上级界面
		connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(check_file()));//生成密钥
		connect(ui.comboBox_1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change_method(const QString &)));
		connect(ui.comboBox_2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change_type(const QString &)));

		//退出时销毁该窗口以免内存泄漏
		setAttribute(Qt::WA_DeleteOnClose);

		//图片初始化
		effect_1 = new QGraphicsOpacityEffect(this);//特效
		effect_2 = new QGraphicsOpacityEffect(this);
		effect_1->setOpacity(1 - timer_transparent_count);
		effect_2->setOpacity(0);
		QPixmap background_picture;//绘制未切换时的背景图片
		QString background_path = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//临时存储原始背景图片路径
		background_path += QString::number(timer_picture_count, 10);//第一张图片使用随机数
		background_path += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
		background_picture.load(background_path);//加载背景图片
		ui.label_chara_1->setGraphicsEffect(effect_1);//后面使用人物图片
		ui.label_chara_1->setPixmap(background_picture);
		ui.label_chara_2->setGraphicsEffect(effect_2);//前面使用全透明图片
		ui.label_chara_2->setPixmap(QPixmap(DIALOG_BACKGROUND_CHARA_TRANSPARENT_PICTURE_PATH_STRING));

		//设置文字颜色
		QPalette global_text_palette;
		global_text_palette.setColor(QPalette::Text, QColor(70, 28, 10, 255));
		global_text_palette.setColor(QPalette::HighlightedText, QColor(70, 28, 10, 255));
		global_text_palette.setColor(QPalette::WindowText, QColor(70, 28, 10, 255));
		global_text_palette.setColor(QPalette::Highlight, QColor(70, 28, 10, 64));
		ui.comboBox_1->setPalette(global_text_palette);
		ui.comboBox_2->setPalette(global_text_palette);
		ui.lineEdit_1->setPalette(global_text_palette);
		ui.lineEdit_2->setPalette(global_text_palette);

		//文本框只允许输入数字和字母
		QRegExp regexp("[a-fA-F0-9]+$");//正则表达式，只允许输入十六进制允许输入的字符
		validator = new QRegExpValidator(regexp, ui.lineEdit_2);//定义需要使用的模式
		ui.lineEdit_2->setValidator(validator);//应用模式

		//窗口启动动画效果
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存

		//去掉关联性控件的右键菜单
		QList<QScrollBar *> scroll_bar = this->findChildren<QScrollBar *>();//由于无法用常规方式获得combobox的滚动条，因此使用该方法查找所有同类型控件并进行操作
		foreach(QScrollBar *scroll_bar_style_control, scroll_bar)
		{
			scroll_bar_style_control->setContextMenuPolicy(Qt::NoContextMenu);
		}
	}
	LockNormalHashCalculate::~LockNormalHashCalculate()
	{
		delete timer;
		delete effect_1;
		delete effect_2;
		delete validator;
	}

	//设置成员函数
	void LockNormalHashCalculate::set_method(QString method)//设置加密方式，参数为加密方式
	{
		this->method = method;
		ui.comboBox_1->setCurrentText(method);//设置主界面中的加密方法
		combobox_change_type(DIALOG_HASH_CALCULATOR_TYPE_STRING);
		if (method == tr("MD4"))
		{
			ui.comboBox_2->setEnabled(false);
			ui.lineEdit_2->setMaxLength(MD4::DIGESTSIZE * 2);
		}
		else if (method == tr("MD5"))
		{
			ui.comboBox_2->setEnabled(false);
			ui.lineEdit_2->setMaxLength(MD5::DIGESTSIZE * 2);
		}
		else if (method == tr("SHA-1"))
		{
			ui.comboBox_2->setEnabled(false);
			ui.lineEdit_2->setMaxLength(SHA1::DIGESTSIZE * 2);
		}
		else if (method == tr("SHA-2"))
		{
			ui.comboBox_2->setEnabled(true);
			ui.lineEdit_2->setMaxLength(SHA224::DIGESTSIZE * 2);
		}
		else if (method == tr("SHA-3"))
		{
			ui.comboBox_2->setEnabled(true);
			ui.lineEdit_2->setMaxLength(SHA3_224::DIGESTSIZE * 2);
		}
		else if (method == tr("Keccak"))
		{
			ui.comboBox_2->setEnabled(true);
			ui.lineEdit_2->setMaxLength(Keccak_224::DIGESTSIZE * 2);
		}
		else
		{
			ui.comboBox_2->setEnabled(false);
			ui.lineEdit_2->setMaxLength(MD4::DIGESTSIZE * 2);
		}
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void LockNormalHashCalculate::mousePressEvent(QMouseEvent *event)
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
	void LockNormalHashCalculate::mouseMoveEvent(QMouseEvent *event)
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
	void LockNormalHashCalculate::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉。这个窗口因为只有确认操作，本来不需要重写，但为了保持统一，还是进行了重写
	void LockNormalHashCalculate::keyPressEvent(QKeyEvent *event)
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

	void LockNormalHashCalculate::timer_timeout()//使用2个label用来容纳图片。首先指定一个长时间间隔用来显示图片，此时图片在下层label，上层label使用全透明图片，即将其忽略。时间到期后，改用切换图片透明度所使用的短时间间隔，同时开始修改透明度计数，下层label显示原始图片，不透明度逐渐减小；上层label显示切换后图片，不透明度逐渐增加。当上层label图片透明度为1时，切换结束，图片计数增加1，以新的长时间间隔重新开始下一计时循环
	{
		if (timer_interval == DIALOG_LOCK_CHARA_PICTURE_COUNT_INTERVAL_NUMNER)//最大间隔时间到期，说明应该切换图片
		{
			timer_interval = DIALOG_LOCK_CHARA_PICTURE_TRANSPARENT_COUNT_INTERVAL_NUMNER;//切换为透明度更改间隔
			timer_transparent_count = DIALOG_LOCK_CHARA_PICTURE_TRANSPARENT_COUNT_MEASURE_NUMNER;
			effect_1->setOpacity(1 - timer_transparent_count);
			effect_2->setOpacity(timer_transparent_count);
			QPixmap background_picture_back;//绘制原始图片
			QString background_path_back = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//临时存储原始背景图片路径
			background_path_back += QString::number(timer_picture_count, 10);
			background_path_back += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
			background_picture_back.load(background_path_back);//加载图片
			QPixmap background_picture_next;//绘制切换后图片
			QString background_path_next = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//临时存储切换后背景图片路径
			if (timer_picture_count + 1 >= DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER + 1)//超出图片顺序最大数范围
			{
				background_path_next += QString::number(DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER, 10);
			}
			else
			{
				background_path_next += QString::number(timer_picture_count + 1, 10);
			}
			background_path_next += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
			background_picture_next.load(background_path_next);//加载背景图片
			ui.label_chara_1->setGraphicsEffect(effect_1);//后面使用原始图片
			ui.label_chara_1->setPixmap(background_picture_back);
			ui.label_chara_2->setGraphicsEffect(effect_2);//前面使用切换后图片
			ui.label_chara_2->setPixmap(background_picture_next);
			timer->start(timer_interval);//按照透明度切换的时间间隔继续启动计时器
		}
		else
		{
			if (timer_transparent_count >= 1)//结束一次切换
			{
				timer_transparent_count = 0;
				timer_interval = DIALOG_LOCK_CHARA_PICTURE_COUNT_INTERVAL_NUMNER;
				if (timer_picture_count + 1 >= DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER + 1)//图片计数超出范围
				{
					timer_picture_count = 1;
				}
				else
				{
					timer_picture_count += 1;
				}
				effect_1->setOpacity(1 - timer_transparent_count);
				effect_2->setOpacity(0);
				QPixmap background_picture;//绘制未切换时的背景图片
				QString background_path = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//临时存储原始背景图片路径
				background_path += QString::number(timer_picture_count, 10);
				background_path += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
				background_picture.load(background_path);//加载背景图片
				ui.label_chara_1->setGraphicsEffect(effect_1);//后面使用人物图片
				ui.label_chara_1->setPixmap(background_picture);
				ui.label_chara_2->setGraphicsEffect(effect_2);//前面使用全透明图片
				ui.label_chara_2->setPixmap(QPixmap(DIALOG_BACKGROUND_CHARA_TRANSPARENT_PICTURE_PATH_STRING));
				timer->start(timer_interval);
			}
			else//透明度没有达到指定大小
			{
				timer_transparent_count += DIALOG_LOCK_CHARA_PICTURE_TRANSPARENT_COUNT_MEASURE_NUMNER;
				effect_1->setOpacity(1 - timer_transparent_count);
				effect_2->setOpacity(timer_transparent_count);
				QPixmap background_picture_back;//绘制原始图片
				QString background_path_back = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//临时存储原始背景图片路径
				background_path_back += QString::number(timer_picture_count, 10);
				background_path_back += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
				background_picture_back.load(background_path_back);//加载图片
				QPixmap background_picture_next;//绘制切换后图片
				QString background_path_next = DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING;//临时存储切换后背景图片路径
				if (timer_picture_count + 1 >= DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER + 1)//超出图片顺序最大数范围
				{
					background_path_next += QString::number(DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER, 10);
				}
				else
				{
					background_path_next += QString::number(timer_picture_count + 1, 10);
				}
				background_path_next += DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING;
				background_picture_next.load(background_path_next);//加载背景图片
				ui.label_chara_1->setGraphicsEffect(effect_1);//后面使用原始图片
				ui.label_chara_1->setPixmap(background_picture_back);
				ui.label_chara_2->setGraphicsEffect(effect_2);//前面使用切换后图片
				ui.label_chara_2->setPixmap(background_picture_next);
				timer->start(timer_interval);
			}
		}
	}

	void LockNormalHashCalculate::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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
		emit show_lock_normal_window();//发出显示上级窗口信号
		connect(animation_close, SIGNAL(finished()), this, SLOT(close()));
	}

	void LockNormalHashCalculate::combobox_change_method(const QString &combobox_string)//设置加密方式，参数为加密方式
	{
		if (combobox_string == tr("MD4"))
		{
			ui.comboBox_2->setEnabled(false);
			method = tr("MD4");
			ui.lineEdit_2->setMaxLength(MD4::DIGESTSIZE * 2);
		}
		else if (combobox_string == tr("MD5"))
		{
			ui.comboBox_2->setEnabled(false);
			method = tr("MD5");
			ui.lineEdit_2->setMaxLength(MD5::DIGESTSIZE * 2);
		}
		else if (combobox_string == tr("SHA-1"))
		{
			ui.comboBox_2->setEnabled(false);
			method = tr("SHA-1");
			ui.lineEdit_2->setMaxLength(SHA1::DIGESTSIZE * 2);
		}
		else if (combobox_string == tr("SHA-2"))
		{
			ui.comboBox_2->setEnabled(true);
			method = tr("SHA-2");
			if (ui.comboBox_2->currentText() == tr("224"))
			{
				ui.lineEdit_2->setMaxLength(SHA224::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("256"))
			{
				ui.lineEdit_2->setMaxLength(SHA256::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("384"))
			{
				ui.lineEdit_2->setMaxLength(SHA384::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("512"))
			{
				ui.lineEdit_2->setMaxLength(SHA512::DIGESTSIZE * 2);
			}
			else
			{
				ui.lineEdit_2->setMaxLength(SHA224::DIGESTSIZE * 2);
			}
		}
		else if (combobox_string == tr("SHA-3"))
		{
			ui.comboBox_2->setEnabled(true);
			method = tr("SHA-3");
			if (ui.comboBox_2->currentText() == tr("224"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_224::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("256"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_256::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("384"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_384::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("512"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_512::DIGESTSIZE * 2);
			}
			else
			{
				ui.lineEdit_2->setMaxLength(SHA3_224::DIGESTSIZE * 2);
			}
		}
		else if (combobox_string == tr("Keccak"))
		{
			ui.comboBox_2->setEnabled(true);
			method = tr("Keccak");
			if (ui.comboBox_2->currentText() == tr("224"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_224::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("256"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_256::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("384"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_384::DIGESTSIZE * 2);
			}
			else if (ui.comboBox_2->currentText() == tr("512"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_512::DIGESTSIZE * 2);
			}
			else
			{
				ui.lineEdit_2->setMaxLength(Keccak_224::DIGESTSIZE * 2);
			}
		}
		else
		{
			ui.comboBox_2->setEnabled(false);
			method = tr("MD4");
			ui.lineEdit_2->setMaxLength(MD4::DIGESTSIZE * 2);
		}
	}

	void LockNormalHashCalculate::combobox_change_type(const QString &combobox_string)//组合框内容更改后处理
	{
		calculate_type = combobox_string;
		if (method == tr("SHA-2"))
		{
			if (calculate_type == tr("224"))
			{
				ui.lineEdit_2->setMaxLength(SHA224::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("256"))
			{
				ui.lineEdit_2->setMaxLength(SHA256::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("384"))
			{
				ui.lineEdit_2->setMaxLength(SHA384::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("512"))
			{
				ui.lineEdit_2->setMaxLength(SHA512::DIGESTSIZE * 2);
			}
			else
			{
				ui.lineEdit_2->setMaxLength(SHA224::DIGESTSIZE * 2);
			}
		}
		else if (method == tr("SHA-3"))
		{
			if (calculate_type == tr("224"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_224::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("256"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_256::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("384"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_384::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("512"))
			{
				ui.lineEdit_2->setMaxLength(SHA3_512::DIGESTSIZE * 2);
			}
			else
			{
				ui.lineEdit_2->setMaxLength(SHA3_224::DIGESTSIZE * 2);
			}
		}
		else if (method == tr("Keccak"))
		{
			if (calculate_type == tr("224"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_224::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("256"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_256::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("384"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_384::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("512"))
			{
				ui.lineEdit_2->setMaxLength(Keccak_512::DIGESTSIZE * 2);
			}
			else
			{
				ui.lineEdit_2->setMaxLength(Keccak_224::DIGESTSIZE * 2);
			}
		}
		else
		{
			if (calculate_type == tr("224"))
			{
				ui.lineEdit_2->setMaxLength(SHA224::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("256"))
			{
				ui.lineEdit_2->setMaxLength(SHA256::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("384"))
			{
				ui.lineEdit_2->setMaxLength(SHA384::DIGESTSIZE * 2);
			}
			else if (calculate_type == tr("512"))
			{
				ui.lineEdit_2->setMaxLength(SHA512::DIGESTSIZE * 2);
			}
			else
			{
				ui.lineEdit_2->setMaxLength(SHA224::DIGESTSIZE * 2);
			}
		}
	}

	void LockNormalHashCalculate::calculate_file()//计算散列值
	{

		//读取配置文件信息
		QSettings *begin_read = new QSettings(FILE_SET_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		QString information_temp[2];//临时存放读取结果
		information_temp[0] = begin_read->value(FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING).toString();
		if (information_temp[0].length() == 0)
		{
			information_temp[0] = FILE_SETTING_CATALOG_PATH_DEFAULT_STRING;
		}
		else
		{

		}
		information_temp[1] = begin_read->value(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING).toString();//布尔值
		if (information_temp[1] == "0")//是否输出历史文件
		{
			bool_array[0] = false;
		}
		else
		{
			bool_array[0] = true;
		}
		if (information_temp[0] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
		{
			information_temp[0] = FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING;
		}
		else
		{

		}
		delete begin_read;
		string_array[2] = string((const char *)(information_temp[0] + FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING).toLocal8Bit());//历史文件后半部分路径
		HashCalculate_file_thread *thread = new HashCalculate_file_thread();//处理文件子线程
		connect(thread, &QThread::finished, thread, &QObject::deleteLater);//直接delete子线程极其容易出现各种问题，要想安全删除线程可以使用此方式
		connect(this, SIGNAL(send_data(string*, bool*, char*, QString, QString)), thread, SLOT(get_data(string*, bool*, char*, QString, QString)));
		connect(this, SIGNAL(send_target_class_point(Export_HashCalculate_virtual_class *)), thread, SLOT(get_target_class_point(Export_HashCalculate_virtual_class *)));
		connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
		emit send_data(string_array, bool_array, result, calculate_type, method);//发送数据
		using export_class = Export_HashCalculate_virtual_class * (*)(void);//定义指向导出函数的指针类型
		HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//动态加载dll，并且导出指定的类的对象指针，通过信号传递给子线程使用
		if (dll_name != NULL)
		{
			emit send_dll_name(dll_name);//因为在子线程使用完dll之前不能卸载dll，故只能通过信号将dll名传递给子线程
			export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_hash_calculate");//通过导出指定的导出函数来导出需要的类
			if (get_class != NULL)
			{
				Export_HashCalculate_virtual_class *target_class_object = get_class();//获得目标类的对象指针
				emit send_target_class_point(target_class_object);//发送dll导出类对象指针
				QString file_path = ui.lineEdit_1->text();//检查文件路径合法性
				QFileInfo file_information(file_path);//获取文件信息
				if (file_information.isFile())//该文件存在
				{
					ui.lineEdit_1->setText(file_path);
					string_array[0] = string((const char *)file_path.toLocal8Bit());//文件路径
					string_array[1] = string((const char *)(file_information.fileName()).toLocal8Bit());//文件名
					if (method == tr("MD4"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_MD4_final(int)), this, SLOT(receive_hash_calculate_final(int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					}
					else if (method == tr("MD5"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_MD5_final(int)), this, SLOT(receive_hash_calculate_final(int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					}
					else if (method == tr("SHA-1"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_SHA1_final(int)), this, SLOT(receive_hash_calculate_final(int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					}
					else if (method == tr("SHA-2"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_SHA2_final(int)), this, SLOT(receive_hash_calculate_final(int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					}
					else if (method == tr("SHA-3"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_SHA3_final(int)), this, SLOT(receive_hash_calculate_final(int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					}
					else if (method == tr("Keccak"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_Keccak_final(int)), this, SLOT(receive_hash_calculate_final(int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					}
					else
					{
						connect(target_class_object, SIGNAL(hash_calculate_MD4_final(int)), this, SLOT(receive_hash_calculate_final(int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					}
					thread->start();//开始子线程
				}
				else
				{
					Help dialog;//显示程序信息
					dialog.set_dialog_information_path(DIALOG_INFORMATION_KEYFILE_CANNOT_OPEN_PATH_STRING);
					dialog.setWindowTitle(tr("打开文件失败！"));
					dialog.exec();
				}
			}
			else
			{

			}
		}
		else
		{

		}
	}

	void LockNormalHashCalculate::check_file()//校验文件
	{
		//读取配置文件信息
		QSettings *begin_read = new QSettings(FILE_SET_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		QString information_temp[2];//临时存放读取结果
		information_temp[0] = begin_read->value(FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING).toString();
		if (information_temp[0].length() == 0)
		{
			information_temp[0] = FILE_SETTING_CATALOG_PATH_DEFAULT_STRING;
		}
		else
		{

		}
		information_temp[1] = begin_read->value(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING).toString();//布尔值
		if (information_temp[1] == "0")//是否输出历史文件
		{
			bool_array[0] = false;
		}
		else
		{
			bool_array[0] = true;
		}
		if (information_temp[1] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
		{
			information_temp[1] = FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING;
		}
		else
		{

		}
		delete begin_read;
		string_array[2] = string((const char *)(information_temp[0] + FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING).toLocal8Bit());//历史文件后半部分路径
		HashCalculate_file_thread *thread = new HashCalculate_file_thread();//处理文件子线程
		connect(thread, &QThread::finished, thread, &QObject::deleteLater);//直接delete子线程极其容易出现各种问题，要想安全删除线程可以使用此方式
		connect(this, SIGNAL(send_data(string*, bool*, char*, QString, QString)), thread, SLOT(get_data(string*, bool*, char*, QString, QString)));
		connect(this, SIGNAL(send_target_class_point(Export_HashCalculate_virtual_class *)), thread, SLOT(get_target_class_point(Export_HashCalculate_virtual_class *)));
		connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
		emit send_data(string_array, bool_array, result, calculate_type, method);//发送数据
		using export_class = Export_HashCalculate_virtual_class * (*)(void);//定义指向导出函数的指针类型
		HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//动态加载dll，并且导出指定的类的对象指针，通过信号传递给子线程使用
		if (dll_name != NULL)
		{
			emit send_dll_name(dll_name);//因为在子线程使用完dll之前不能卸载dll，故只能通过信号将dll名传递给子线程
			export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_hash_calculate");//通过导出指定的导出函数来导出需要的类
			if (get_class != NULL)
			{
				Export_HashCalculate_virtual_class *target_class_object = get_class();//获得目标类的对象指针
				emit send_target_class_point(target_class_object);//发送dll导出类对象指针
				QString file_path = ui.lineEdit_1->text();//检查文件路径合法性
				QFileInfo file_information(file_path);//获取文件信息
				if (file_information.isFile())//该文件存在
				{
					ui.lineEdit_1->setText(file_path);
					string_array[0] = string((const char *)file_path.toLocal8Bit());//文件路径
					string_array[1] = string((const char *)(file_information.fileName()).toLocal8Bit());//文件名
					if (method == tr("MD4"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_MD4_final(int)), this, SLOT(receive_hash_calculate_final_check(int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					}
					else if (method == tr("MD5"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_MD5_final(int)), this, SLOT(receive_hash_calculate_final_check(int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					}
					else if (method == tr("SHA-1"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_SHA1_final(int)), this, SLOT(receive_hash_calculate_final_check(int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					}
					else if (method == tr("SHA-2"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_SHA2_final(int)), this, SLOT(receive_hash_calculate_final_check(int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					}
					else if (method == tr("SHA-3"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_SHA3_final(int)), this, SLOT(receive_hash_calculate_final_check(int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					}
					else if (method == tr("Keccak"))
					{
						connect(target_class_object, SIGNAL(hash_calculate_Keccak_final(int)), this, SLOT(receive_hash_calculate_final_check(int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					}
					else
					{
						connect(target_class_object, SIGNAL(hash_calculate_MD4_final(int)), this, SLOT(receive_hash_calculate_final_check(int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					}
					thread->start();//开始子线程
				}
				else
				{
					Help dialog;//显示程序信息
					dialog.set_dialog_information_path(DIALOG_INFORMATION_KEYFILE_CANNOT_OPEN_PATH_STRING);
					dialog.setWindowTitle(tr("打开文件失败！"));
					dialog.exec();
				}
			}
			else
			{

			}
		}
		else
		{

		}
	}

	void LockNormalHashCalculate::file_explore()
	{
		File dialog;//这个窗口是从Notepad.exe直接引用的，没有进行任何修改，因此File类的调用方式会比较麻烦
		dialog.setWindowTitle(tr("选择文件"));
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
		if (file_information.isFile() && *change_result_address)//该文件存在
		{
			ui.lineEdit_1->setText(file_dialog_file_name);
			string_array[0] = string((const char *)file_dialog_file_name.toLocal8Bit());//文件路径
			string_array[1] = string((const char *)(file_information.fileName()).toLocal8Bit());//文件名
		}
		else if (*change_result_address)
		{
			Help dialog;//显示程序信息
			dialog.set_dialog_information_path(DIALOG_INFORMATION_KEYFILE_CANNOT_OPEN_PATH_STRING);
			dialog.setWindowTitle(tr("打开文件失败！"));
			dialog.exec();
		}
		else
		{

		}
	}

	void LockNormalHashCalculate::receive_hash_calculate_final(int length)//计算结束。参数为结果长度
	{
		QByteArray result_string(result, length);//将结果转化为QBytearray
		result_string.toUpper();
		ui.lineEdit_2->setText(ui.lineEdit_2->text().toUpper());
		ui.lineEdit_2->setText((QString)result_string);//主界面显示计算的结果。注意QByteArray可以直接转化成QString
	}

	void LockNormalHashCalculate::receive_hash_calculate_final_check(int length)//计算结束，并进行比对。参数为结果长度
	{
		QByteArray result_string(result, length);//将结果转化为QBytearray
		result_string.toUpper();
		ui.lineEdit_2->setText(ui.lineEdit_2->text().toUpper());
		int correct_length;//正确长度
		if (method == tr("MD4"))
		{
			correct_length = MD4::DIGESTSIZE * 2;
		}
		else if (method == tr("MD5"))
		{
			correct_length = MD5::DIGESTSIZE * 2;
		}
		else if (method == tr("SHA-1"))
		{
			correct_length = SHA1::DIGESTSIZE * 2;
		}
		else if (method == tr("SHA-2"))
		{
			if (ui.comboBox_2->currentText() == tr("224"))
			{
				correct_length=SHA224::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("256"))
			{
				correct_length=SHA256::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("384"))
			{
				correct_length = SHA384::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("512"))
			{
				correct_length = SHA512::DIGESTSIZE * 2;
			}
			else
			{
				correct_length = SHA224::DIGESTSIZE * 2;
			}
		}
		else if (method == tr("SHA-3"))
		{
			if (ui.comboBox_2->currentText() == tr("224"))
			{
				correct_length = SHA3_224::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("256"))
			{
				correct_length = SHA3_256::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("384"))
			{
				correct_length = SHA3_384::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("512"))
			{
				correct_length = SHA3_512::DIGESTSIZE * 2;
			}
			else
			{
				correct_length = SHA3_224::DIGESTSIZE * 2;
			}
		}
		else if (method == tr("Keccak"))
		{
			if (ui.comboBox_2->currentText() == tr("224"))
			{
				correct_length = Keccak_224::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("256"))
			{
				correct_length = Keccak_256::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("384"))
			{
				correct_length = Keccak_384::DIGESTSIZE * 2;
			}
			else if (ui.comboBox_2->currentText() == tr("512"))
			{
				correct_length = Keccak_512::DIGESTSIZE * 2;
			}
			else
			{
				correct_length = Keccak_224::DIGESTSIZE * 2;
			}
		}
		else
		{
			correct_length = MD4::DIGESTSIZE * 2;
		}
		if (ui.lineEdit_2->text().length() != correct_length)
		{
			Help dialog;//显示程序信息
			dialog.set_dialog_information_path(DIALOG_INFORMATION_HASH_CHECK_WRONG_HASH_STRING);
			dialog.setWindowTitle(tr("出了点问题的说……"));
			dialog.exec();
		}
		else
		{
			if (ui.lineEdit_2->text() == (QString)result_string)//结果比对
			{
				Help dialog;//显示程序信息
				dialog.set_dialog_information_path(DIALOG_INFORMATION_HASH_CHECK_CORRECT_STRING);
				dialog.setWindowTitle(tr("校验成功啦！"));
				dialog.exec();
			}
			else
			{
				Help dialog;//显示程序信息
				dialog.set_dialog_information_path(DIALOG_INFORMATION_HASH_CHECK_INCORRECT_STRING);
				dialog.setWindowTitle(tr("出了点问题的说……"));
				dialog.exec();
			}
		}
	}

	//子线程
	HashCalculate_file_thread::HashCalculate_file_thread()//子线程
	{

	}

	HashCalculate_file_thread::~HashCalculate_file_thread()//子线程
	{

	}

	void HashCalculate_file_thread::get_data(string *string_array, bool *bool_array, char *result, QString calculate_type, QString method)//获取全部数据
	{
		this->string_array[0] = string_array[0];//历史文件路径
		this->string_array[1] = string_array[1];//密钥文件路径
		this->string_array[2] = string_array[2];//二进制密钥文件路径
		this->bool_array[0] = bool_array[0];//是否输出历史文件
		this->method = method;//加密方法
		this->calculate_type = calculate_type;//加密方法
		this->result = result;//结果
	}


	void HashCalculate_file_thread::run()//子线程主函数
	{
		mutex.lock();
		if (method == tr("MD4"))//MD4
		{
			target_class_point->hash_calculate_MD4(string_array[0], string_array[1], result, bool_array[0], string_array[2]);
		}
		else if (method == tr("MD5"))//MD5
		{
			target_class_point->hash_calculate_MD5(string_array[0], string_array[1], result, bool_array[0], string_array[2]);
		}
		else if (method == tr("SHA-1"))//SHA-1
		{
			target_class_point->hash_calculate_SHA1(string_array[0], string_array[1], result, bool_array[0], string_array[2]);
		}
		else if (method == tr("SHA-2"))//SHA-2
		{
			target_class_point->hash_calculate_SHA2(string_array[0], string_array[1], result, bool_array[0], string_array[2], string((const char *)calculate_type.toLocal8Bit()));
		}
		else if (method == tr("SHA-3"))//SHA-3
		{
			target_class_point->hash_calculate_SHA3(string_array[0], string_array[1], result, bool_array[0], string_array[2], string((const char *)calculate_type.toLocal8Bit()));
		}
		else if (method == tr("Keccak"))//Keccak
		{
			target_class_point->hash_calculate_Keccak(string_array[0], string_array[1], result, bool_array[0], string_array[2], string((const char *)calculate_type.toLocal8Bit()));
		}
		else
		{
			target_class_point->hash_calculate_MD4(string_array[0], string_array[1], result, bool_array[0], string_array[2]);
		}
		FreeLibrary(dll_name);
		mutex.unlock();
		this->quit();//退出子线程
	}

	void HashCalculate_file_thread::get_target_class_point(Export_HashCalculate_virtual_class *point)//获取dll导出类对象指针
	{
		this->target_class_point = point;
	}

	void HashCalculate_file_thread::get_dll_name(HINSTANCE dll_name)//获取dll名
	{
		this->dll_name = dll_name;
	}
}

