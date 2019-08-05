#include "define.h"

namespace rem
{

	//使用标准命名空间
	using std::string;

	//构造与析构函数
	LockSimpleAdd::LockSimpleAdd(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		resize(DIALOG_LOCK_SIZE_WIDTH_NUMBER, DIALOG_LOCK_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时会退出程序
		is_escape_pressed = false;//允许按下esc键退出程序
		for (int index = 0; index < DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER; index++)//初始化int型加密加减数量，默认均为0，加密默认最大值16
		{
			extra_digit_array[index] = 0;
		}
		extra_digit_array[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER] = DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER;

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
		ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_12.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_12.png);}");

		//信号函数
		connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(lock_file()));//加密文件
		connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(unlock_file()));//解密文件
		connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(digit_set()));//设置加减数量
		connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//返回上级界面

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
		ui.lineEdit->setPalette(global_text_palette);
		ui.spinBox_1->setPalette(global_text_palette);
		ui.spinBox_2->setPalette(global_text_palette);
		ui.progressBar->setPalette(global_text_palette);

		//进度条颜色
		progress_bar_change_color = false;//文件打开时进度条字体颜色未切换
		ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");

		//文本框只允许输入数字和字母
		QRegExp regexp("[a-fA-F0-9]+$");//正则表达式，只允许输入十六进制允许输入的字符
		validator = new QRegExpValidator(regexp, ui.lineEdit);//定义需要使用的模式
		ui.lineEdit->setValidator(validator);//应用模式

		//窗口启动动画效果
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存

	}
	LockSimpleAdd::~LockSimpleAdd()
	{
		delete timer;
		delete effect_1;
		delete effect_2;
		delete validator;
	}

	//设置成员函数
	void LockSimpleAdd::update_unlock_information(int direction, long long head_offset, long long tail_offset, int cycle, QString head_digit, bool have_head_digit, int *operate_count)//更新需要显示在界面上的信息，参数为：加密方向（1：顺序加密，2：倒序加密，3：双向加密），头部忽略字节，尾部忽略字节，循环周期，加密文件头部特征数字，是否有头部特征数字，加减数量
	{
		flag_array[0] = direction;//设置加密方向
		if (flag_array[0]==1)//加密方向：右
		{
			ui.radioButton_1->setChecked(true);
			ui.radioButton_2->setChecked(false);
		}
		else//加密方向：左
		{
			ui.radioButton_1->setChecked(false);
			ui.radioButton_2->setChecked(true);
		}
		digit_array[0] = head_offset;//加密起点
		ui.spinBox_1->setValue(head_offset);
		digit_array[1] = tail_offset;//加密终点
		ui.spinBox_2->setValue(tail_offset);
		extra_digit_array[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER] = cycle;//循环周期
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
		for (int index = 0; index < cycle; index++)
		{
			extra_digit_array[index] = operate_count[index];
		}
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void LockSimpleAdd::mousePressEvent(QMouseEvent *event)
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
	void LockSimpleAdd::mouseMoveEvent(QMouseEvent *event)
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
	void LockSimpleAdd::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉。这个窗口因为只有确认操作，本来不需要重写，但为了保持统一，还是进行了重写
	void LockSimpleAdd::keyPressEvent(QKeyEvent *event)
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

	void LockSimpleAdd::timer_timeout()//使用2个label用来容纳图片。首先指定一个长时间间隔用来显示图片，此时图片在下层label，上层label使用全透明图片，即将其忽略。时间到期后，改用切换图片透明度所使用的短时间间隔，同时开始修改透明度计数，下层label显示原始图片，不透明度逐渐减小；上层label显示切换后图片，不透明度逐渐增加。当上层label图片透明度为1时，切换结束，图片计数增加1，以新的长时间间隔重新开始下一计时循环
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

	void LockSimpleAdd::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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
		emit show_lock_simple_window();//发出显示上级窗口信号
		connect(animation_close, SIGNAL(finished()), this, SLOT(close()));
	}

	void LockSimpleAdd::lock_file()//加密文件
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
			if (ui.radioButton_1->isChecked())//存储int型标记信息
			{
				flag_array[0] = 1;
			}
			else
			{
				flag_array[0] = 2;
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
			digit_array[0] = ui.spinBox_1->value();//存储long long型数值信息。这里是头部处理起点
			digit_array[1] = ui.spinBox_2->value();//尾部处理起点
			Lock_add_file_thread *thread = new Lock_add_file_thread();//处理文件子线程
			connect(thread, &QThread::finished, thread, &QObject::deleteLater);//直接delete子线程极其容易出现各种问题，要想安全删除线程可以使用此方式
			connect(this, SIGNAL(send_data(string*, bool*, long long*, int*, int*, char*)), thread, SLOT(get_data(string*, bool*, long long*, int*, int*, char*)));
			connect(this, SIGNAL(send_target_class_point(Export_LockSimple_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockSimple_virtual_class *)));
			connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
			emit send_data(string_array, bool_array, digit_array, flag_array, extra_digit_array, char_array);//发送数据
			using export_class = Export_LockSimple_virtual_class * (*)(void);//定义指向导出函数的指针类型
			HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_READ_PATH_STRING);//动态加载dll，并且导出指定的类的对象指针，通过信号传递给子线程使用
			ui.progressBar->setVisible(true);//显示进度条
			ui.progressBar->setValue(0);//进度条初始值为0
			progress_bar_change_color = false;//开始加密时进度条字体颜色未切换
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");//设置进度条颜色
			if (dll_name != NULL)
			{
				emit send_dll_name(dll_name);//因为在子线程使用完dll之前不能卸载dll，故只能通过信号将dll名传递给子线程
				export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_simple");//通过导出指定的导出函数来导出需要的类
				if (get_class != NULL)
				{
					Export_LockSimple_virtual_class *target_class_object = get_class();//获得目标类的对象指针
					emit send_target_class_point(target_class_object);//发送dll导出类对象指针
					connect(target_class_object, SIGNAL(lock_simple_add_process(double)), this, SLOT(receive_lock_simple_add_process(double)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
					connect(target_class_object, SIGNAL(lock_simple_add_final(bool)), this, SLOT(receive_lock_simple_add_final(bool)));
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
		else if(*change_result_address)
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

	void LockSimpleAdd::unlock_file()//解密文件
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
			QString information_temp[9];//读取需要显示的内容
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
			information_temp[4] = begin_read->value(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING).toString();//文件后缀
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
			delete begin_read;
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
			if (ui.radioButton_1->isChecked())//存储int型标记信息
			{
				flag_array[0] = 1;
			}
			else
			{
				flag_array[0] = 2;
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
			string_array[0] = string((const char *)file_dialog_file_name.toLocal8Bit());//存储字符串信息。这里是文件路径
			string_array[1] = string((const char *)(file_information.fileName()).toLocal8Bit());//文件名
			string_array[2] = string((const char *)information_temp[1].toLocal8Bit());//输出解密文件前半部分不变路径
			string_array[3] = string((const char *)(FILE_SETTING_SUFFIX_INTERVAL_STRING + information_temp[5]).toLocal8Bit());//输出解密文件路径后缀
			string_array[4] = string((const char *)(information_temp[3] + FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING).toLocal8Bit());//输出历史文件路径
			string_array[5] = "";//输出密钥文件路径后缀，这里无需使用
			string_array[6] = "";//输出二进制密钥文件路径后缀，这里无需使用
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
			digit_array[0] = ui.spinBox_1->value();//存储long long型数值信息。这里是头部处理起点
			digit_array[1] = ui.spinBox_2->value();//尾部处理起点
			UnlockSimpleAddCheck dialog;//创建确认解密信息框
			is_continue = false;//设置是否需要在下一窗口执行完后继续操作
			dialog.set_information(&flag_array[0], &digit_array[0], &digit_array[1], &extra_digit_array[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER], &lineEdit_text, &bool_array[3], &is_continue, extra_digit_array);//设定初始值
			dialog.exec();
			if (is_continue)//在解密确认窗口点击确认，接下来进行解密操作
			{
				update_unlock_information(flag_array[0], digit_array[0], digit_array[1], extra_digit_array[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER], lineEdit_text, bool_array[3], extra_digit_array);//更新窗口内容
				Unlock_add_file_thread *thread = new Unlock_add_file_thread;//处理文件子线程
				connect(thread, &QThread::finished, thread, &QObject::deleteLater);//直接delete子线程极其容易出现各种问题，要想安全删除线程可以使用此方式
				connect(this, SIGNAL(send_data(string*, bool*, long long*, int*, int*, char*)), thread, SLOT(get_data(string*, bool*, long long*, int*, int*, char*)));
				connect(this, SIGNAL(send_target_class_point(Export_LockSimple_virtual_class *)), thread, SLOT(get_target_class_point(Export_LockSimple_virtual_class *)));
				connect(this, SIGNAL(send_dll_name(HINSTANCE)), thread, SLOT(get_dll_name(HINSTANCE)));
				emit send_data(string_array, bool_array, digit_array, flag_array, extra_digit_array, char_array);//发送数据
				using export_class = Export_LockSimple_virtual_class * (*)(void);//定义指向导出函数的指针类型
				HINSTANCE dll_name = LoadLibrary(FILE_DLL_FILE_READ_PATH_STRING);//动态加载dll，并且导出指定的类的对象指针，通过信号传递给子线程使用
				ui.progressBar->setVisible(true);//显示进度条
				ui.progressBar->setValue(0);//进度条初始值为0
				progress_bar_change_color = false;//开始加密时进度条字体颜色未切换
				ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");//设置进度条颜色
				if (dll_name != NULL)
				{
					emit send_dll_name(dll_name);//因为在子线程使用完dll之前不能卸载dll，故只能通过信号将dll名传递给子线程
					export_class get_class = (export_class)GetProcAddress(dll_name, "export_class_lock_simple");//通过导出指定的导出函数来导出需要的类
					if (get_class != NULL)
					{
						Export_LockSimple_virtual_class *target_class_object = get_class();//获得目标类的对象指针
						emit send_target_class_point(target_class_object);//发送dll导出类对象指针
						connect(target_class_object, SIGNAL(unlock_simple_add_process(double)), this, SLOT(receive_unlock_simple_add_process(double)));//该函数要求的条件：发送者需要继承QObject类并且类中含有Q_OBJECT宏
						connect(target_class_object, SIGNAL(unlock_simple_add_final(bool)), this, SLOT(receive_unlock_simple_add_final(bool)));
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
			else//在解密确认窗口点击取消，不进行任何操作
			{

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

	void LockSimpleAdd::digit_set()//加减数量设置
	{
		LockSimpleAddGetDigit dialog;
		dialog.set_information(extra_digit_array);
		dialog.exec();
	}

	void LockSimpleAdd::receive_lock_simple_add_process(double index)//取反加密文件进度条显示。参数为已处理部分比例
	{
		double progress_bar_value = (index * DIALOG_PROGRESSBAR_TIMES_NUMBER);//计算比例
		if (progress_bar_value > DIALOG_PROGRESSBAR_MAX_NUMBER)
		{
			progress_bar_value = DIALOG_PROGRESSBAR_MAX_NUMBER;
		}
		else
		{

		}
		if (progress_bar_value > DIALOG_PROGRESSBAR_CHANGE_FONT_COLOR_NUMBER && !progress_bar_change_color)//避免看不见数字
		{
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#F8F5E2;}QProgressBar::chunk{background-color:#461C0A;}");
			progress_bar_change_color = true;//保证只切换一次字体颜色
		}
		else
		{

		}
		ui.progressBar->setValue((int)progress_bar_value);//进度条显示
	}

	void LockSimpleAdd::receive_lock_simple_add_final(bool is_success)//取反加密文件结束。参数为dll导出类指针
	{
		ui.progressBar->setValue(0);//进度条显示最小值
		progress_bar_change_color = false;//保证只切换一次字体颜色
		ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");
		if (is_success == true)
		{

		}
		else
		{
			Help dialog;//显示程序信息
			dialog.set_dialog_information_path(DIALOG_INFORMATION_LOCK_FAIL_PATH_STRING);
			dialog.setWindowTitle(tr("处理失败了……"));
			dialog.exec();
		}
	}

	void LockSimpleAdd::receive_unlock_simple_add_process(double index)//取反加密文件进度条显示。参数为已处理部分比例
	{
		double progress_bar_value = (index * DIALOG_PROGRESSBAR_TIMES_NUMBER);//计算比例
		if (progress_bar_value > DIALOG_PROGRESSBAR_MAX_NUMBER)
		{
			progress_bar_value = DIALOG_PROGRESSBAR_MAX_NUMBER;
		}
		else
		{

		}
		if (progress_bar_value > DIALOG_PROGRESSBAR_CHANGE_FONT_COLOR_NUMBER && !progress_bar_change_color)//避免看不见数字
		{
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#F8F5E2;}QProgressBar::chunk{background-color:#461C0A;}");
			progress_bar_change_color = true;//保证只切换一次字体颜色
		}
		else
		{

		}
		ui.progressBar->setValue((int)progress_bar_value);//进度条显示
	}

	void LockSimpleAdd::receive_unlock_simple_add_final(bool is_success)//取反加密文件结束。参数为dll导出类指针
	{
		ui.progressBar->setValue(0);//进度条显示最小值
		progress_bar_change_color = false;//保证只切换一次字体颜色
		ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #461C0A;background-color: #00FFFFFF;text-align:center;color:#461C0A;}QProgressBar::chunk{background-color:#461C0A;}");
		if (is_success == true)
		{

		}
		else
		{
			Help dialog;//显示程序信息
			dialog.set_dialog_information_path(DIALOG_INFORMATION_UNLOCK_FAIL_PATH_STRING);
			dialog.setWindowTitle(tr("处理失败了……"));
			dialog.exec();
		}
	}

	//加密子线程类函数
	Lock_add_file_thread::Lock_add_file_thread()
	{

	}

	Lock_add_file_thread::~Lock_add_file_thread()
	{

	}

	void Lock_add_file_thread::get_data(string *string_array, bool *bool_array, long long *digit_array, int *flag_array, int *extra_digit_array, char *char_array)//获取全部数据，注意循环周期存储在extra_digit_array的最后一个单元
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
		this->digit_array[0] = digit_array[0];
		this->digit_array[1] = digit_array[1];
		this->extra_digit_array[0] = extra_digit_array[0];
		this->extra_digit_array[1] = extra_digit_array[1];
		this->extra_digit_array[2] = extra_digit_array[2];
		this->extra_digit_array[3] = extra_digit_array[3];
		this->extra_digit_array[4] = extra_digit_array[4];
		this->extra_digit_array[5] = extra_digit_array[5];
		this->extra_digit_array[6] = extra_digit_array[6];
		this->extra_digit_array[7] = extra_digit_array[7];
		this->extra_digit_array[8] = extra_digit_array[8];
		this->extra_digit_array[9] = extra_digit_array[9];
		this->extra_digit_array[10] = extra_digit_array[10];
		this->extra_digit_array[11] = extra_digit_array[11];
		this->extra_digit_array[12] = extra_digit_array[12];
		this->extra_digit_array[13] = extra_digit_array[13];
		this->extra_digit_array[14] = extra_digit_array[14];
		this->extra_digit_array[15] = extra_digit_array[15];
		this->flag_array[0] = flag_array[0];
		this->flag_array[1] = extra_digit_array[16];
		this->char_array = char_array;
	}

	void Lock_add_file_thread::get_target_class_point(Export_LockSimple_virtual_class *point)//获取dll导出类对象指针
	{
		this->target_class_point = point;
	}

	void Lock_add_file_thread::get_dll_name(HINSTANCE dll_name)//获取dll名
	{
		this->dll_name = dll_name;
	}

	void Lock_add_file_thread::run()//子线程主函数
	{
		mutex.lock();
		target_class_point->lock_add(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], bool_array[1], bool_array[2], string_array[5], string_array[6], string_array[7], flag_array[0], digit_array[0], digit_array[1], flag_array[1], bool_array[3], char_array, extra_digit_array);//加密文件并且返回是否成功。不能使用string，否则因为其会将'\0'作为结束标志，如果恰好有“00”字段则其后面的内容会被直接忽略
		FreeLibrary(dll_name);
		mutex.unlock();
		this->quit();//退出子线程
	}

	Unlock_add_file_thread::Unlock_add_file_thread()
	{

	}

	Unlock_add_file_thread::~Unlock_add_file_thread()
	{

	}

	void Unlock_add_file_thread::run()//子线程主函数
	{
		mutex.lock();
		target_class_point->unlock_add(string_array[0], string_array[1], string_array[2], string_array[3], bool_array[0], string_array[4], string_array[7], flag_array[0], digit_array[0], digit_array[1], flag_array[1], bool_array[3], char_array, extra_digit_array);//解密文件并且返回是否成功。不能使用string，否则因为其会将'\0'作为结束标志，如果恰好有“00”字段则其后面的内容会被直接忽略
		FreeLibrary(dll_name);
		mutex.unlock();
		this->quit();//退出子线程
	}
}

