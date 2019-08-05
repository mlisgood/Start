#include "define.h"

namespace rem
{

	//使用标准命名空间
	using std::string;

	//导入crypto++命名空间
	using namespace CryptoPP;

	//构造与析构函数
	LockNormalDoubleKey::LockNormalDoubleKey(QWidget *parent) : QDialog(parent)
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
		ui.pushButton_1->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_1.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_1.png);}");
		ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_2.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_2.png);}");
		ui.pushButton_3->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_3.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_3.png);}");
		ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_15.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_15.png);}");

		//信号函数
		connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(lock_file()));//加密文件
		connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(unlock_file()));//解密文件
		connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//返回上级界面
		connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(set_key()));//生成密钥
		connect(ui.comboBox_1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change_method(const QString &)));
		connect(ui.comboBox_2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change_size(const QString &)));

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
		ui.lineEdit->setPalette(global_text_palette);

		//文本框只允许输入数字和字母
		QRegExp regexp("[a-fA-F0-9]+$");//正则表达式，只允许输入十六进制允许输入的字符
		validator_1 = new QRegExpValidator(regexp, ui.lineEdit);//定义需要使用的模式
		validator_2 = new QRegExpValidator(regexp, ui.lineEdit_1);//定义需要使用的模式
		validator_3 = new QRegExpValidator(regexp, ui.lineEdit_2);//定义需要使用的模式
		ui.lineEdit->setValidator(validator_1);//应用模式
		ui.lineEdit_1->setValidator(validator_2);
		ui.lineEdit_2->setValidator(validator_3);
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
	LockNormalDoubleKey::~LockNormalDoubleKey()
	{
		delete timer;
		delete effect_1;
		delete effect_2;
		delete validator_1;
		delete validator_2;
		delete validator_3;
	}

	//设置成员函数
	void LockNormalDoubleKey::update_lock_information(QString head_digit, bool have_head_digit, QString key)//更新加密前需要显示在界面上的信息，参数为：加密文件头部特征数字，是否有头部特征数字，密钥
	{
		bool_array[2] = have_head_digit;//是否有头部特征数字
		if (have_head_digit)//有头部特征数字
		{
			ui.checkBox->setChecked(true);
			QString head_digit_text = head_digit;//转换其为十六进制编码并重新赋给字符数组
			head_digit_text = head_digit_text.toUpper();//转换为大写
			QByteArray head_digit_bytearray = head_digit_text.toLatin1();//转换为QByteArray，转换为支持ASCII的字符集即可
			for (int index = 0; index < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER; index++)//检查QByteArray是否有8个元素，如果不够就插入预置字符
			{
				if (head_digit_bytearray.length() < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER)
				{
					head_digit_bytearray.insert(0, DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_CHAR);
				}
				else//否则跳出循环
				{
					break;
				}
			}
			head_digit_text = head_digit_bytearray;//修改lineEdit的内容
			ui.lineEdit->setText(head_digit_text);//设置显示内容
			head_digit_bytearray = QByteArray::fromHex(head_digit_bytearray);//转化为16进制编码
			memmove(char_array, head_digit_bytearray.data(), DIALOG_SIMPLE_LOCK_LINEEDIT_TRANSFORM_LENGTH_NUMBER);//直接复制内存。这里用char[]相对麻烦，但是不能用char*，因为这会导致传递时子线程槽函数接收时，在该函数运行完后子线程的相关成员指向空值；也不能用string，否则因为其以'\0'作为结尾标志，如果未转化时的字符串中含有“00”，则其后面的字符会被全部忽略
		}
		else
		{
			ui.checkBox->setChecked(false);
			ui.lineEdit->setText("");//设置显示内容
		}
		ui.lineEdit_1->setText(key);
	}

	void LockNormalDoubleKey::update_unlock_information(QString head_digit, bool have_head_digit, QString key)//更新解密前需要显示在界面上的信息，参数为：加密文件头部特征数字，是否有头部特征数字，密钥
	{
		bool_array[2] = have_head_digit;//是否有头部特征数字
		if (have_head_digit)//有头部特征数字
		{
			ui.checkBox->setChecked(true);
			QString head_digit_text = head_digit;//转换其为十六进制编码并重新赋给字符数组
			head_digit_text = head_digit_text.toUpper();//转换为大写
			QByteArray head_digit_bytearray = head_digit_text.toLatin1();//转换为QByteArray，转换为支持ASCII的字符集即可
			for (int index = 0; index < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER; index++)//检查QByteArray是否有8个元素，如果不够就插入预置字符
			{
				if (head_digit_bytearray.length() < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER)
				{
					head_digit_bytearray.insert(0, DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_CHAR);
				}
				else//否则跳出循环
				{
					break;
				}
			}
			head_digit_text = head_digit_bytearray;//修改lineEdit的内容
			ui.lineEdit->setText(head_digit_text);//设置显示内容
			head_digit_bytearray = QByteArray::fromHex(head_digit_bytearray);//转化为16进制编码
			memmove(char_array, head_digit_bytearray.data(), DIALOG_SIMPLE_LOCK_LINEEDIT_TRANSFORM_LENGTH_NUMBER);//直接复制内存。这里用char[]相对麻烦，但是不能用char*，因为这会导致传递时子线程槽函数接收时，在该函数运行完后子线程的相关成员指向空值；也不能用string，否则因为其以'\0'作为结尾标志，如果未转化时的字符串中含有“00”，则其后面的字符会被全部忽略
		}
		else
		{
			ui.checkBox->setChecked(false);
			ui.lineEdit->setText("");//设置显示内容
		}
		ui.lineEdit_2->setText(key);
	}

	void LockNormalDoubleKey::set_method(QString method)//设置加密方式，参数为加密方式
	{
		this->method = method;
		ui.comboBox_1->setCurrentText(method);//设置主界面中的加密方法
		if (method == tr("RSA"))
		{
			combobox_change_size(QString::number(DIALOG_LOCK_NORMAL_DOUBLE_DEFAULE_SIZE_NUMBER, 10));
		}
		else if (method == tr("ECC"))
		{
			combobox_change_size(DIALOG_LOCK_NORMAL_DOUBLE_DEFAULE_CURVE_TYPE_STRING);
		}
		else
		{
			combobox_change_size(QString::number(DIALOG_LOCK_NORMAL_DOUBLE_DEFAULE_SIZE_NUMBER, 10));
		}
		ui.comboBox_2->clear();
		QStringList combobox_list;
		if (method == tr("RSA"))
		{
			combobox_list << tr("1024") << tr("1536") << tr("2048") << tr("2560") << tr("3072") << tr("3584") << tr("4096") << tr("4608") << tr("5120") << tr("5632") << tr("6144");
		}
		else if (method == tr("ECC"))
		{
			combobox_list << tr("secp112r1") << tr("secp112r2") << tr("secp128r1") << tr("secp128r2") << tr("secp160r1") << tr("secp160k1") << tr("secp160r2") << tr("secp192k1") << tr("secp224r1") << tr("secp224k1") << tr("secp256k1") << tr("secp384r1") << tr("secp521r1");
		}
		else
		{
			combobox_list << tr("1024") << tr("1536") << tr("2048") << tr("2560") << tr("3072") << tr("3584") << tr("4096") << tr("4608") << tr("5120") << tr("5632") << tr("6144");
		}
		ui.comboBox_2->addItems(combobox_list);
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void LockNormalDoubleKey::mousePressEvent(QMouseEvent *event)
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
	void LockNormalDoubleKey::mouseMoveEvent(QMouseEvent *event)
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
	void LockNormalDoubleKey::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉。这个窗口因为只有确认操作，本来不需要重写，但为了保持统一，还是进行了重写
	void LockNormalDoubleKey::keyPressEvent(QKeyEvent *event)
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

	void LockNormalDoubleKey::timer_timeout()//使用2个label用来容纳图片。首先指定一个长时间间隔用来显示图片，此时图片在下层label，上层label使用全透明图片，即将其忽略。时间到期后，改用切换图片透明度所使用的短时间间隔，同时开始修改透明度计数，下层label显示原始图片，不透明度逐渐减小；上层label显示切换后图片，不透明度逐渐增加。当上层label图片透明度为1时，切换结束，图片计数增加1，以新的长时间间隔重新开始下一计时循环
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

	void LockNormalDoubleKey::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

	void LockNormalDoubleKey::combobox_change_method(const QString &combobox_string)//设置加密方式，参数为加密方式
	{
		if (combobox_string == tr("RSA"))
		{
			method = tr("RSA");
		}
		else if (combobox_string == tr("ECC"))
		{
			method = tr("ECC");
		}
		else
		{
			method = tr("RSA");
		}
		ui.comboBox_2->clear();
		QStringList combobox_list;
		if (method == tr("RSA"))
		{
			combobox_list << tr("1024") << tr("1536") << tr("2048") << tr("2560") << tr("3072") << tr("3584") << tr("4096") << tr("4608") << tr("5120") << tr("5632") << tr("6144");
		}
		else if (method == tr("ECC"))
		{
			combobox_list << tr("secp112r1") << tr("secp112r2") << tr("secp128r1") << tr("secp128r2") << tr("secp160r1") << tr("secp160k1") << tr("secp160r2") << tr("secp192k1") << tr("secp224r1") << tr("secp224k1") << tr("secp256k1") << tr("secp384r1") << tr("secp521r1");
		}
		else
		{
			combobox_list << tr("1024") << tr("1536") << tr("2048") << tr("2560") << tr("3072") << tr("3584") << tr("4096") << tr("4608") << tr("5120") << tr("5632") << tr("6144");
		}
		ui.comboBox_2->addItems(combobox_list);
	}

	void LockNormalDoubleKey::combobox_change_size(const QString &combobox_string)//组合框内容更改后处理
	{

		//设置允许输入的密钥长度
		if (method == tr("RSA"))
		{
			bool is_transform_success;//QString转int是否成功
			size = combobox_string.toInt(&is_transform_success, 10);
			if (!is_transform_success)
			{
				size = DIALOG_LOCK_NORMAL_DOUBLE_DEFAULE_SIZE_NUMBER;
			}
			else
			{

			}
		}
		else if (method == "ECC")
		{
			curve_type = ui.comboBox_2->currentText();
		}
		else
		{
			bool is_transform_success;//QString转int是否成功
			size = combobox_string.toInt(&is_transform_success, 10);
			if (!is_transform_success)
			{
				size = DIALOG_LOCK_NORMAL_DOUBLE_DEFAULE_SIZE_NUMBER;
			}
			else
			{

			}
		}
	}

	void LockNormalDoubleKey::lock_file()//加密文件
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
			
			//读取配置文件信息
			QSettings *begin_read = new QSettings(FILE_SET_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
			QString information_temp[11];//读取需要显示的内容
			information_temp[0] = begin_read->value(FILE_SETTING_CATALOG_1_1_INNER_PATH_STRING).toString();//文件夹路径
			information_temp[1] = begin_read->value(FILE_SETTING_CATALOG_1_2_INNER_PATH_STRING).toString();
			information_temp[2] = begin_read->value(FILE_SETTING_CATALOG_1_3_INNER_PATH_STRING).toString();
			information_temp[3] = begin_read->value(FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING).toString();
			for (int index = 0; index <= 3; index++)//处理配置文件丢失的情况
			{
				if (information_temp[index].length() == 0)
				{
					information_temp[index] = FILE_SETTING_CATALOG_PATH_DEFAULT_STRING;
				}
				else
				{

				}
			}
			information_temp[4] = begin_read->value(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING).toString();//生成文件后缀
			information_temp[5] = begin_read->value(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING).toString();
			if (information_temp[4].length() == 0)
			{
				information_temp[4] = FILE_SETTING_SUFFIX_LOCK_DEFAULT_STRING;
			}
			else
			{

			}
			if (information_temp[5].length() == 0)
			{
				information_temp[5] = FILE_SETTING_SUFFIX_UNLOCK_DEFAULT_STRING;
			}
			else
			{

			}
			information_temp[6] = begin_read->value(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING).toString();//布尔值
			information_temp[7] = begin_read->value(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING).toString();//布尔值
			information_temp[8] = begin_read->value(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING).toString();//布尔值
			if (information_temp[6] == "0")//是否输出历史文件
			{
				bool_array[0] = false;
			}
			else
			{
				bool_array[0] = true;
			}
			if (information_temp[7] == "0")//是否输出密钥文件
			{
				bool_array[1] = false;
			}
			else
			{
				bool_array[1] = true;
			}
			if (information_temp[8] == "0")//是否输出二进制密钥文件
			{
				bool_array[2] = false;
			}
			else
			{
				bool_array[2] = true;
			}
			if (ui.checkBox->isChecked())//是否有头部特征数字
			{
				bool_array[3] = true;
			}
			else
			{
				bool_array[3] = false;
			}
			if (information_temp[0] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)//处理默认情况
			{
				information_temp[0] = FILE_OUTPUT_FILE_LOCK_FRONT_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[1] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
			{
				information_temp[1] = FILE_OUTPUT_FILE_UNLOCK_FRONT_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[2] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
			{
				information_temp[2] = FILE_TEMP_FILE_FRONT_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[3] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
			{
				information_temp[3] = FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING;
			}
			else
			{

			}
			information_temp[9] = begin_read->value(FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING).toString();//密钥文件后缀
			information_temp[10] = begin_read->value(FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING).toString();
			if (information_temp[9].length() == 0)
			{
				information_temp[9] = FILE_OUTPUT_FILE_KEY_BACK_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[10].length() == 0)
			{
				information_temp[10] = FILE_OUTPUT_FILE_KEY_BINARY_BACK_PATH_STRING;
			}
			else
			{

			}
			delete begin_read;
			string_array[0] = string((const char *)file_dialog_file_name.toLocal8Bit());//存储字符串信息。这里是文件路径
			string_array[1] = string((const char *)(file_information.fileName()).toLocal8Bit());//文件名
			string_array[2] = string((const char *)information_temp[0].toLocal8Bit());//输出加密文件前半部分不变路径
			string_array[3] = string((const char *)(FILE_SETTING_SUFFIX_INTERVAL_STRING + information_temp[4]).toLocal8Bit());//输出加密文件路径后缀
			string_array[4] = string((const char *)(information_temp[3] + FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING).toLocal8Bit());//输出历史文件路径
			string_array[5] = string((const char *)(FILE_SETTING_SUFFIX_INTERVAL_STRING + information_temp[9]).toLocal8Bit());//输出密钥文件路径后缀
			string_array[6] = string((const char *)(FILE_SETTING_SUFFIX_INTERVAL_STRING + information_temp[10]).toLocal8Bit());//输出二进制密钥文件路径后缀
			string_array[7] = string((const char *)information_temp[2].toLocal8Bit());//临时文件夹位置
			QString lineEdit_text = ui.lineEdit->text().toLatin1();//获取输入框内容，转换为支持ASCII的字符集即可
			lineEdit_text = lineEdit_text.toUpper();//转换为大写
			QByteArray head_digit_bytearray = lineEdit_text.toLatin1();//转换为QByteArray，转换为支持ASCII的字符集即可
			if (bool_array[3])//需要加入特征数字
			{
				for (int index = 0; index < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER; index++)//检查QByteArray是否有8个元素，如果不够就插入预置字符
				{
					if (head_digit_bytearray.length() < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER)
					{
						head_digit_bytearray.insert(0, DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_CHAR);
					}
					else//否则跳出循环
					{
						break;
					}
				}
				lineEdit_text = head_digit_bytearray;//修改lineEdit的内容
				ui.lineEdit->setText(lineEdit_text);
				head_digit_bytearray = QByteArray::fromHex(head_digit_bytearray);//转化为16进制编码
				memmove(char_array, head_digit_bytearray.data(), DIALOG_SIMPLE_LOCK_LINEEDIT_TRANSFORM_LENGTH_NUMBER);//直接复制内存。这里用char[]相对麻烦，但是不能用char*，因为这会导致传递时子线程槽函数接收时，在该函数运行完后子线程的相关成员指向空值；也不能用string，否则因为其以'\0'作为结尾标志，如果未转化时的字符串中含有“00”，则其后面的字符会被全部忽略
			}
			else
			{
				
			}
			key_size = ui.lineEdit_1->text().length();
			QString key_text = ui.lineEdit_1->text().toLatin1();//获取公钥输入框内容，转换为支持ASCII的字符集即可
			key_text = key_text.toUpper();//转换为大写
			ui.lineEdit_1->setText(key_text);
			UnlockNormalDoubleCheck dialog;//创建确认解密信息框
			is_continue = false;//设置是否需要在下一窗口执行完后继续操作
			dialog.setWindowTitle(tr("加密信息"));
			dialog.set_information(FILE_PUBLIC_KEY_TYPE_STRING, method, &key_text, &lineEdit_text, &bool_array[3], &is_continue, &key_size);//设定初始值
			dialog.exec();
			if (is_continue)//在解密确认窗口点击确认，接下来进行解密操作
			{
				if (key_text.length() != key_size)
				{
					Help dialog;//显示程序信息
					dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_LENGTH_KEY_PATH_STRING);
					dialog.setWindowTitle(tr("加密失败了……"));
					dialog.exec();
				}
				else
				{
					update_lock_information(lineEdit_text, bool_array[3], key_text);//更新窗口内容
					QByteArray key_bytearray = key_text.toLatin1();//将密钥文本转化为二进制数据并赋值
					key_bytearray = QByteArray::fromHex(key_bytearray);//转化为16进制编码
					memmove(public_key, key_bytearray.data(), key_size / 2);//直接复制内存
					Lock_double_file_thread *thread = new Lock_double_file_thread();//处理文件子线程
					connect(thread, &QThread::finished, thread, &QObject::deleteLater);//直接delete子线程极其容易出现各种问题，要想安全删除线程可以使用此方式
					connect(this, SIGNAL(send_data(string*, bool*, char*, char*, int, QString)), thread, SLOT(get_data(string*, bool*, char*, char*, int, QString)));
					connect(this, SIGNAL(send_target_class_point(Export_LockDouble_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockDouble_virtual_class *)));
					connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
					emit send_data(string_array, bool_array, char_array, public_key, key_size, method);//发送数据
					using export_class = Export_LockDouble_virtual_class * (*)(void);//定义指向导出函数的指针类型
					HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//动态加载dll，并且导出指定的类的对象指针，通过信号传递给子线程使用
					if (dll_name != NULL)
					{
						emit send_dll_name(dll_name);//因为在子线程使用完dll之前不能卸载dll，故只能通过信号将dll名传递给子线程
						export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_double");//通过导出指定的导出函数来导出需要的类
						if (get_class != NULL)
						{
							Export_LockDouble_virtual_class *target_class_object = get_class();//获得目标类的对象指针
							emit send_target_class_point(target_class_object);//发送dll导出类对象指针
							if (method == tr("RSA"))
							{
								connect(target_class_object, SIGNAL(lock_RSA_out_of_range()), this, SLOT(receive_lock_out_of_range()));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
								connect(target_class_object, SIGNAL(lock_RSA_wrong_key()), this, SLOT(receive_lock_wrong_key()));
								connect(target_class_object, SIGNAL(lock_RSA_final(bool)), this, SLOT(receive_lock_final(bool)));
							}
							else if (method == tr("ECC"))
							{
								connect(target_class_object, SIGNAL(lock_ECC_out_of_range()), this, SLOT(receive_lock_out_of_range()));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
								connect(target_class_object, SIGNAL(lock_ECC_wrong_key()), this, SLOT(receive_lock_wrong_key()));
								connect(target_class_object, SIGNAL(lock_ECC_final(bool)), this, SLOT(receive_lock_final(bool)));
							}
							else
							{
								connect(target_class_object, SIGNAL(lock_RSA_out_of_range()), this, SLOT(receive_lock_out_of_range()));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
								connect(target_class_object, SIGNAL(lock_RSA_wrong_key()), this, SLOT(receive_lock_wrong_key()));
								connect(target_class_object, SIGNAL(lock_RSA_final(bool)), this, SLOT(receive_lock_final(bool)));
							}
						}
						else
						{

						}
					}
					else
					{

					}
					thread->start();//开始子线程
				}
			}
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

	void LockNormalDoubleKey::unlock_file()//解密文件
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

			//读取配置文件信息
			QSettings *begin_read = new QSettings(FILE_SET_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
			QString information_temp[11];//读取需要显示的内容
			information_temp[0] = begin_read->value(FILE_SETTING_CATALOG_1_1_INNER_PATH_STRING).toString();//文件夹路径
			information_temp[1] = begin_read->value(FILE_SETTING_CATALOG_1_2_INNER_PATH_STRING).toString();
			information_temp[2] = begin_read->value(FILE_SETTING_CATALOG_1_3_INNER_PATH_STRING).toString();
			information_temp[3] = begin_read->value(FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING).toString();
			for (int index = 0; index <= 3; index++)//处理配置文件丢失的情况
			{
				if (information_temp[index].length() == 0)
				{
					information_temp[index] = FILE_SETTING_CATALOG_PATH_DEFAULT_STRING;
				}
				else
				{

				}
			}
			information_temp[4] = begin_read->value(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING).toString();//生成文件后缀
			information_temp[5] = begin_read->value(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING).toString();
			if (information_temp[4].length() == 0)
			{
				information_temp[4] = FILE_SETTING_SUFFIX_LOCK_DEFAULT_STRING;
			}
			else
			{

			}
			if (information_temp[5].length() == 0)
			{
				information_temp[5] = FILE_SETTING_SUFFIX_UNLOCK_DEFAULT_STRING;
			}
			else
			{

			}
			information_temp[6] = begin_read->value(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING).toString();//布尔值
			information_temp[7] = begin_read->value(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING).toString();//布尔值
			information_temp[8] = begin_read->value(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING).toString();//布尔值
			if (information_temp[6] == "0")//是否输出历史文件
			{
				bool_array[0] = false;
			}
			else
			{
				bool_array[0] = true;
			}
			if (information_temp[7] == "0")//是否输出密钥文件
			{
				bool_array[1] = false;
			}
			else
			{
				bool_array[1] = true;
			}
			if (information_temp[8] == "0")//是否输出二进制密钥文件
			{
				bool_array[2] = false;
			}
			else
			{
				bool_array[2] = true;
			}
			if (ui.checkBox->isChecked())//是否有头部特征数字
			{
				bool_array[3] = true;
			}
			else
			{
				bool_array[3] = false;
			}
			if (information_temp[0] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)//处理默认情况
			{
				information_temp[0] = FILE_OUTPUT_FILE_LOCK_FRONT_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[1] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
			{
				information_temp[1] = FILE_OUTPUT_FILE_UNLOCK_FRONT_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[2] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
			{
				information_temp[2] = FILE_TEMP_FILE_FRONT_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[3] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
			{
				information_temp[3] = FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING;
			}
			else
			{

			}
			information_temp[9] = begin_read->value(FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING).toString();//密钥文件后缀
			information_temp[10] = begin_read->value(FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING).toString();
			if (information_temp[9].length() == 0)
			{
				information_temp[9] = FILE_OUTPUT_FILE_KEY_BACK_PATH_STRING;
			}
			else
			{

			}
			if (information_temp[10].length() == 0)
			{
				information_temp[10] = FILE_OUTPUT_FILE_KEY_BINARY_BACK_PATH_STRING;
			}
			else
			{

			}
			delete begin_read;
			string_array[0] = string((const char *)file_dialog_file_name.toLocal8Bit());//存储字符串信息。这里是文件路径
			string_array[1] = string((const char *)(file_information.fileName()).toLocal8Bit());//文件名
			string_array[2] = string((const char *)information_temp[1].toLocal8Bit());//输出解密文件前半部分不变路径
			string_array[3] = string((const char *)(FILE_SETTING_SUFFIX_INTERVAL_STRING + information_temp[5]).toLocal8Bit());//输出解密文件路径后缀
			string_array[4] = string((const char *)(information_temp[3] + FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING).toLocal8Bit());//输出历史文件路径
			string_array[5] = string((const char *)(FILE_SETTING_SUFFIX_INTERVAL_STRING + information_temp[9]).toLocal8Bit());//输出密钥文件路径后缀
			string_array[6] = string((const char *)(FILE_SETTING_SUFFIX_INTERVAL_STRING + information_temp[10]).toLocal8Bit());//输出二进制密钥文件路径后缀
			string_array[7] = string((const char *)information_temp[2].toLocal8Bit());//临时文件夹位置
			QString lineEdit_text = ui.lineEdit->text().toLatin1();//获取输入框内容，转换为支持ASCII的字符集即可
			lineEdit_text = lineEdit_text.toUpper();//转换为大写
			QByteArray head_digit_bytearray = lineEdit_text.toLatin1();//转换为QByteArray，转换为支持ASCII的字符集即可
			if (bool_array[3])//需要加入特征数字
			{
				for (int index = 0; index < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER; index++)//检查QByteArray是否有8个元素，如果不够就插入预置字符
				{
					if (head_digit_bytearray.length() < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER)
					{
						head_digit_bytearray.insert(0, DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_CHAR);
					}
					else//否则跳出循环
					{
						break;
					}
				}
				lineEdit_text = head_digit_bytearray;//修改lineEdit的内容
				ui.lineEdit->setText(lineEdit_text);
				head_digit_bytearray = QByteArray::fromHex(head_digit_bytearray);//转化为16进制编码
				memmove(char_array, head_digit_bytearray.data(), DIALOG_SIMPLE_LOCK_LINEEDIT_TRANSFORM_LENGTH_NUMBER);//直接复制内存。这里用char[]相对麻烦，但是不能用char*，因为这会导致传递时子线程槽函数接收时，在该函数运行完后子线程的相关成员指向空值；也不能用string，否则因为其以'\0'作为结尾标志，如果未转化时的字符串中含有“00”，则其后面的字符会被全部忽略
			}
			else
			{

			}
			key_size = ui.lineEdit_2->text().length();
			QString key_text = ui.lineEdit_2->text().toLatin1();//获取公钥输入框内容，转换为支持ASCII的字符集即可
			key_text = key_text.toUpper();//转换为大写
			ui.lineEdit_2->setText(key_text); 
			UnlockNormalDoubleCheck dialog;//创建确认解密信息框
			is_continue = false;//设置是否需要在下一窗口执行完后继续操作
			dialog.set_information(FILE_PRIVATE_KEY_TYPE_STRING, method, &key_text, &lineEdit_text, &bool_array[3], &is_continue, &key_size);//设定初始值
			dialog.setWindowTitle(tr("解密信息"));
			dialog.exec();
			if (is_continue)//在解密确认窗口点击确认，接下来进行解密操作
			{
				if (key_text.length() != key_size)
				{
					Help dialog;//显示程序信息
					dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_LENGTH_KEY_PATH_STRING);
					dialog.setWindowTitle(tr("加密失败了……"));
					dialog.exec();
				}
				else
				{
					update_unlock_information(lineEdit_text, bool_array[3], key_text);//更新窗口内容
					QByteArray key_bytearray = key_text.toLatin1();//将密钥文本转化为二进制数据并赋值
					key_bytearray = QByteArray::fromHex(key_bytearray);//转化为16进制编码
					memmove(private_key, key_bytearray.data(), key_size / 2);//直接复制内存
					Unlock_double_file_thread *thread = new Unlock_double_file_thread();//处理文件子线程
					connect(thread, &QThread::finished, thread, &QObject::deleteLater);//直接delete子线程极其容易出现各种问题，要想安全删除线程可以使用此方式
					connect(this, SIGNAL(send_data(string*, bool*, char*, char*, int, QString)), thread, SLOT(get_data(string*, bool*, char*, char*, int, QString)));
					connect(this, SIGNAL(send_target_class_point(Export_LockDouble_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockDouble_virtual_class *)));
					connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
					emit send_data(string_array, bool_array, char_array, private_key, key_size, method);//发送数据
					using export_class = Export_LockDouble_virtual_class * (*)(void);//定义指向导出函数的指针类型
					HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//动态加载dll，并且导出指定的类的对象指针，通过信号传递给子线程使用
					if (dll_name != NULL)
					{
						emit send_dll_name(dll_name);//因为在子线程使用完dll之前不能卸载dll，故只能通过信号将dll名传递给子线程
						export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_double");//通过导出指定的导出函数来导出需要的类
						if (get_class != NULL)
						{
							Export_LockDouble_virtual_class *target_class_object = get_class();//获得目标类的对象指针
							emit send_target_class_point(target_class_object);//发送dll导出类对象指针
							if (method == tr("RSA"))
							{
								connect(target_class_object, SIGNAL(unlock_RSA_out_of_range()), this, SLOT(receive_unlock_out_of_range()));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
								connect(target_class_object, SIGNAL(unlock_RSA_wrong_key()), this, SLOT(receive_unlock_wrong_key()));
								connect(target_class_object, SIGNAL(unlock_RSA_final(bool)), this, SLOT(receive_unlock_final(bool)));
							}
							else if (method == tr("ECC"))
							{
								connect(target_class_object, SIGNAL(unlock_ECC_out_of_range()), this, SLOT(receive_unlock_out_of_range()));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
								connect(target_class_object, SIGNAL(unlock_ECC_wrong_key()), this, SLOT(receive_unlock_wrong_key()));
								connect(target_class_object, SIGNAL(unlock_ECC_final(bool)), this, SLOT(receive_unlock_final(bool)));
							}
							else
							{
								connect(target_class_object, SIGNAL(unlock_RSA_out_of_range()), this, SLOT(receive_unlock_out_of_range()));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
								connect(target_class_object, SIGNAL(unlock_RSA_wrong_key()), this, SLOT(receive_unlock_wrong_key()));
								connect(target_class_object, SIGNAL(unlock_RSA_final(bool)), this, SLOT(receive_unlock_final(bool)));
							}
						}
						else
						{

						}
					}
					else
					{

					}
					thread->start();//开始子线程
				}
			}
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

	void LockNormalDoubleKey::set_key()//设置密钥
	{
		//读取配置文件信息
		QSettings *begin_read = new QSettings(FILE_SET_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		QString information_temp[6];//读取需要显示的内容
		information_temp[0] = begin_read->value(FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING).toString();
		if (information_temp[0].length() == 0)
		{
			information_temp[0] = FILE_SETTING_CATALOG_PATH_DEFAULT_STRING;
		}
		else
		{

		}
		information_temp[1] = begin_read->value(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING).toString();//布尔值
		information_temp[2] = begin_read->value(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING).toString();//布尔值
		information_temp[3] = begin_read->value(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING).toString();//布尔值
		if (information_temp[1] == "0")//是否输出历史文件
		{
			bool_array[0] = false;
		}
		else
		{
			bool_array[0] = true;
		}
		if (information_temp[2] == "0")//是否输出密钥文件
		{
			bool_array[1] = false;
		}
		else
		{
			bool_array[1] = true;
		}
		if (information_temp[3] == "0")//是否输出二进制密钥文件
		{
			bool_array[2] = false;
		}
		else
		{
			bool_array[2] = true;
		}
		if (ui.checkBox->isChecked())//是否有头部特征数字
		{
			bool_array[3] = true;
		}
		else
		{
			bool_array[3] = false;
		}
		if (information_temp[0] == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)//处理默认情况
		{
			information_temp[0] = FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING;
		}
		else
		{

		}
		information_temp[4] = begin_read->value(FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING).toString();//密钥文件后缀
		information_temp[5] = begin_read->value(FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING).toString();
		if (information_temp[4].length() == 0)
		{
			information_temp[4] = FILE_OUTPUT_FILE_KEY_BACK_PATH_STRING;
		}
		else
		{

		}
		if (information_temp[5].length() == 0)
		{
			information_temp[5] = FILE_OUTPUT_FILE_KEY_BINARY_BACK_PATH_STRING;
		}
		else
		{

		}
		delete begin_read;
		string_array[4] = string((const char *)(information_temp[0] + FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING).toLocal8Bit());//输出历史文件路径
		string_array[5] = string((const char *)(FILE_SETTING_SUFFIX_INTERVAL_STRING + information_temp[4]).toLocal8Bit());//输出密钥文件路径后缀
		string_array[6] = string((const char *)(FILE_SETTING_SUFFIX_INTERVAL_STRING + information_temp[5]).toLocal8Bit());//输出二进制密钥文件路径后缀
		QString lineEdit_text = ui.lineEdit->text().toLatin1();//获取输入框内容，转换为支持ASCII的字符集即可
		lineEdit_text = lineEdit_text.toUpper();//转换为大写
		QByteArray head_digit_bytearray = lineEdit_text.toLatin1();//转换为QByteArray，转换为支持ASCII的字符集即可
		if (bool_array[3])//需要加入特征数字
		{
			for (int index = 0; index < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER; index++)//检查QByteArray是否有8个元素，如果不够就插入预置字符
			{
				if (head_digit_bytearray.length() < DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER)
				{
					head_digit_bytearray.insert(0, DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_CHAR);
				}
				else//否则跳出循环
				{
					break;
				}
			}
			lineEdit_text = head_digit_bytearray;//修改lineEdit的内容
			ui.lineEdit->setText(lineEdit_text);
			head_digit_bytearray = QByteArray::fromHex(head_digit_bytearray);//转化为16进制编码
			memmove(char_array, head_digit_bytearray.data(), DIALOG_SIMPLE_LOCK_LINEEDIT_TRANSFORM_LENGTH_NUMBER);//直接复制内存。这里用char[]相对麻烦，但是不能用char*，因为这会导致传递时子线程槽函数接收时，在该函数运行完后子线程的相关成员指向空值；也不能用string，否则因为其以'\0'作为结尾标志，如果未转化时的字符串中含有“00”，则其后面的字符会被全部忽略
		}
		else
		{

		}
		File dialog;//这个窗口是从Notepad.exe引用的，调用方式比较麻烦
		dialog.setWindowTitle(tr("保存密钥文件"));
		QString file_dialog_file_name = QDir::currentPath() + tr("\\") + FILE_LOCK_DOUBLE_KEY_DEFAULT_NAME_STRING;//当前路径加上默认文件名，用于获得被打开的文件名。需要注意路径后面需要加上斜杠
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//确定是否需要修改路径，只有点击确定才会修改
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//传入存放文件路径的变量
		dialog.set_file_dialog_status_address(change_result_address);//传入存放是否需要修改路径的变量
		dialog.set_button_save_or_open(1);
		dialog.set_current_path(QDir::currentPath());//传入工作路径
		dialog.exec();
		if (change_result)
		{
			QFileInfo file_information(file_dialog_file_name);//获取文件信息
			QString file_path = file_information.absolutePath();//获取绝对路径供之后分析使用
			QFileInfo file_path_information(file_path);//绝对路径信息
			if (file_information.isFile()|| file_path_information.isDir())//该文件存在，将覆盖文件；或该文件不存在，但路径正确，即新建文件
			{
				file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));//获得文件名
				Lock_double_get_key_thread *thread = new Lock_double_get_key_thread();//处理文件子线程
				connect(thread, &QThread::finished, thread, &QObject::deleteLater);//直接delete子线程极其容易出现各种问题，要想安全删除线程可以使用此方式
				connect(this, SIGNAL(send_key_data(string*, bool*, char*, char*, char*, QString, int, QString, string)), thread, SLOT(get_key_data(string*, bool*, char*, char*, char*, QString, int, QString, string)));
				connect(this, SIGNAL(send_target_class_point(Export_LockDouble_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockDouble_virtual_class *)));
				connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
				emit send_key_data(string_array, bool_array, char_array, public_key, private_key, method, size, curve_type, string((const char *)file_dialog_file_name.toLocal8Bit()));//发送数据
				using export_class = Export_LockDouble_virtual_class * (*)(void);//定义指向导出函数的指针类型
				HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_NORMAL_READ_PATH_STRING);//动态加载dll，并且导出指定的类的对象指针，通过信号传递给子线程使用
				if (dll_name != NULL)
				{
					emit send_dll_name(dll_name);//因为在子线程使用完dll之前不能卸载dll，故只能通过信号将dll名传递给子线程
					export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_double");//通过导出指定的导出函数来导出需要的类
					if (get_class != NULL)
					{
						Export_LockDouble_virtual_class *target_class_object = get_class();//获得目标类的对象指针
						if (method == tr("RSA"))
						{
							connect(target_class_object, SIGNAL(set_key_RSA_final(int, int)), this, SLOT(set_key_final(int, int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
						}
						else if (method == tr("ECC"))
						{
							connect(target_class_object, SIGNAL(set_key_ECC_final(int, int)), this, SLOT(set_key_final(int, int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
						}
						else
						{
							connect(target_class_object, SIGNAL(set_key_RSA_final(int, int)), this, SLOT(set_key_final(int, int)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
						}
						emit send_target_class_point(target_class_object);//发送dll导出类对象指针
					}
					else
					{

					}
				}
				else
				{

				}
				thread->start();//开始子线程
			}
			else//文件路径非法
			{
				Help dialog;//信息提示框
				dialog.setWindowTitle(tr("出错了……"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_SAVE_STRING);//提示信息
				dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
			}
		}
		else
		{

		}
	}

	void LockNormalDoubleKey::set_key_final(int public_key_length, int private_key_length)//设置密钥完毕，参数为公钥和私钥长度
	{
		QByteArray public_key_hex_string(public_key, public_key_length / 2);//将密钥转化为QBytearray
		public_key_hex_string = public_key_hex_string.toHex().toUpper();//获得十六进制数据，转换为大写
		QByteArray private_key_hex_string(private_key, private_key_length / 2);//将密钥转化为QBytearray
		private_key_hex_string = private_key_hex_string.toHex().toUpper();//获得十六进制数据，转换为大写
		ui.lineEdit_1->setText((QString)public_key_hex_string);//主界面显示生成的密钥。注意QByteArray可以直接转化成QString
		ui.lineEdit_2->setText((QString)private_key_hex_string);//主界面显示生成的密钥
	}

	void LockNormalDoubleKey::receive_lock_wrong_key()//RSA加密文件内容超出范围
	{
		Help dialog;//显示程序信息
		dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_KEY_STRING);
		dialog.setWindowTitle(tr("密钥出错了！"));
		dialog.exec();
	}

	void LockNormalDoubleKey::receive_lock_out_of_range()//RSA加密密钥过短或文件内容超出范围
	{
		Help dialog;//显示程序信息
		dialog.set_dialog_information_path(DIALOG_INFORMATION_OUT_OF_RANGE_STRING);
		dialog.setWindowTitle(tr("加密过程出现了问题……"));
		dialog.exec();
	}

	void LockNormalDoubleKey::receive_lock_final(bool is_success)//RSA加密结束。参数为dll导出类指针
	{
		if (is_success == true)
		{
			QByteArray key_hex_string(public_key, key_size / 2);//将密钥转化为QBytearray
			key_hex_string = key_hex_string.toHex().toUpper();//获得十六进制数据，转换为大写
			ui.lineEdit_1->setText(key_hex_string);//主界面显示生成的密钥
		}
		else
		{
			Help dialog;//显示程序信息
			dialog.set_dialog_information_path(DIALOG_INFORMATION_LOCK_FAIL_PATH_STRING);
			dialog.setWindowTitle(tr("处理失败了……"));
			dialog.exec();
		}
	}

	void LockNormalDoubleKey::receive_unlock_wrong_key()//RSA解密文件内容超出范围
	{
		receive_lock_wrong_key();
	}

	void LockNormalDoubleKey::receive_unlock_out_of_range()//RSA解密密文长度不正确
	{
		Help dialog;//显示程序信息
		dialog.set_dialog_information_path(DIALOG_INFORMATION_UNLOCK_OUT_OF_RANGE_STRING);
		dialog.setWindowTitle(tr("解密过程出现了问题……"));
		dialog.exec();
	}

	void LockNormalDoubleKey::receive_unlock_final(bool is_success)//RSA解密结束。参数为dll导出类指针
	{
		if (is_success == true)
		{
			QByteArray key_hex_string(private_key, key_size / 2);//将密钥转化为QBytearray
			key_hex_string = key_hex_string.toHex().toUpper();//获得十六进制数据，转换为大写
			ui.lineEdit_2->setText(key_hex_string);//主界面显示生成的密钥
		}
		else
		{
			Help dialog;//显示程序信息
			dialog.set_dialog_information_path(DIALOG_INFORMATION_UNLOCK_FAIL_PATH_STRING);
			dialog.setWindowTitle(tr("处理失败了……"));
			dialog.exec();
		}
	}

	Lock_double_get_key_thread::Lock_double_get_key_thread()//子线程
	{

	}

	Lock_double_get_key_thread::~Lock_double_get_key_thread()//子线程
	{

	}

	void Lock_double_get_key_thread::get_key_data(string *string_array, bool *bool_array, char *char_array, char *public_key, char *private_key, QString method, int size, QString curve_type, string output_path)//获取全部数据
	{
		this->string_array[0] = string_array[4];//历史文件路径
		this->string_array[1] = string_array[5];//密钥文件路径
		this->string_array[2] = string_array[6];//二进制密钥文件路径
		this->char_array = char_array;//头部特征数字
		this->bool_array[0] = bool_array[0];//是否输出历史文件
		this->bool_array[1] = bool_array[1];//是否输出密钥文件
		this->bool_array[2] = bool_array[2];//是否输出二进制文件
		this->bool_array[3] = bool_array[3];//是否输出头部特征数字
		this->method = method;//加密方法
		this->curve_type = curve_type;//曲线类型
		this->size = size;//密钥长度
		this->output_path = output_path;
		this->public_key = public_key;
		this->private_key = private_key;
	}


	void Lock_double_get_key_thread::run()//子线程主函数
	{
		mutex.lock();
		if (method == tr("RSA"))//RSA加密
		{
			target_class_point->set_key_RSA(public_key, private_key, size, bool_array[0], string_array[0], bool_array[1], bool_array[2], string_array[1], string_array[2], bool_array[3], char_array, output_path);
		}
		else if (method == tr("ECC"))//RSA加密
		{
			target_class_point->set_key_ECC(public_key, private_key, string((const char *)curve_type.toLocal8Bit()), bool_array[0], string_array[0], bool_array[1], bool_array[2], string_array[1], string_array[2], bool_array[3], char_array, output_path);
		}
		else
		{
			target_class_point->set_key_RSA(public_key, private_key, size, bool_array[0], string_array[0], bool_array[1], bool_array[2], string_array[1], string_array[2], bool_array[3], char_array, output_path);
		}
		FreeLibrary(dll_name);
		mutex.unlock();
		this->quit();//退出子线程
	}

	void Lock_double_get_key_thread::get_target_class_point(Export_LockDouble_virtual_class *point)//获取dll导出类对象指针
	{
		this->target_class_point = point;
	}

	void Lock_double_get_key_thread::get_dll_name(HINSTANCE dll_name)//获取dll名
	{
		this->dll_name = dll_name;
	}

	//加密子线程类函数
	Lock_double_file_thread::Lock_double_file_thread()
	{

	}

	Lock_double_file_thread::~Lock_double_file_thread()
	{

	}

	void Lock_double_file_thread::get_data(string *string_array, bool *bool_array, char *char_array, char *key, int size, QString method)//获取全部数据
	{
		this->string_array[0] = string_array[0];
		this->string_array[1] = string_array[1];
		this->string_array[2] = string_array[2];
		this->string_array[3] = string_array[3];
		this->string_array[4] = string_array[4];
		this->string_array[5] = string_array[5];
		this->string_array[6] = string_array[6];
		this->string_array[7] = string_array[7];
		this->bool_array[0] = bool_array[0];
		this->bool_array[1] = bool_array[1];
		this->bool_array[2] = bool_array[2];
		this->bool_array[3] = bool_array[3];
		this->char_array = char_array;
		this->key = key;
		this->size = size;
		this->method = method;
	}

	void Lock_double_file_thread::get_target_class_point(Export_LockDouble_virtual_class *point)//获取dll导出类对象指针
	{
		this->target_class_point = point;
	}

	void Lock_double_file_thread::get_dll_name(HINSTANCE dll_name)//获取dll名
	{
		this->dll_name = dll_name;
	}

	void Lock_double_file_thread::run()//子线程主函数
	{
		mutex.lock();
		if (method == tr("RSA"))//DES加密
		{
			target_class_point->lock_RSA(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[3], char_array, key, size);//加密文件并且返回是否成功。不能使用string，否则因为其会将'\0'作为结束标志，如果恰好有“00”字段则其后面的内容会被直接忽略。由于DES加密需要补足不足一个加密单位的部分，故选择不加密最后不足一个加密单位的数据块，否则会造成明文和密文长度不相同
		}
		else if(method==tr("ECC"))
		{
			target_class_point->lock_ECC(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[3], char_array, key, size);//加密文件并且返回是否成功。不能使用string，否则因为其会将'\0'作为结束标志，如果恰好有“00”字段则其后面的内容会被直接忽略。由于DES加密需要补足不足一个加密单位的部分，故选择不加密最后不足一个加密单位的数据块，否则会造成明文和密文长度不相同
		}
		else
		{
			target_class_point->lock_RSA(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[3], char_array, key, size);//加密文件并且返回是否成功。不能使用string，否则因为其会将'\0'作为结束标志，如果恰好有“00”字段则其后面的内容会被直接忽略。由于DES加密需要补足不足一个加密单位的部分，故选择不加密最后不足一个加密单位的数据块，否则会造成明文和密文长度不相同
		}
		FreeLibrary(dll_name);
		mutex.unlock();
		this->quit();//退出子线程
	}

	Unlock_double_file_thread::Unlock_double_file_thread()
	{

	}

	Unlock_double_file_thread::~Unlock_double_file_thread()
	{

	}

	void Unlock_double_file_thread::run()//子线程主函数
	{
		mutex.lock();
		if (method == tr("RSA"))//RSA解密
		{
			target_class_point->unlock_RSA(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[3], char_array, key, size);//加密文件并且返回是否成功。不能使用string，否则因为其会将'\0'作为结束标志，如果恰好有“00”字段则其后面的内容会被直接忽略。由于DES加密需要补足不足一个加密单位的部分，故选择不加密最后不足一个加密单位的数据块，否则会造成明文和密文长度不相同
		}
		else if (method == tr("ECC"))//ECC解密
		{
			target_class_point->unlock_ECC(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[3], char_array, key, size);//加密文件并且返回是否成功。不能使用string，否则因为其会将'\0'作为结束标志，如果恰好有“00”字段则其后面的内容会被直接忽略。由于DES加密需要补足不足一个加密单位的部分，故选择不加密最后不足一个加密单位的数据块，否则会造成明文和密文长度不相同
		}
		else
		{

		}
		FreeLibrary(dll_name);
		mutex.unlock();
		this->quit();//退出子线程
	}
}

