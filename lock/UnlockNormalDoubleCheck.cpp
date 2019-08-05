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
	UnlockNormalDoubleCheck::UnlockNormalDoubleCheck(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序					
		is_escape_pressed = false;//默认未按下esc键以退出

		//加载图片作为窗口背景
		main_picture.load(DIALOG_BACKGROUND_UNLOCK_NORMAL_DOUBLE_CHECK_PATH_STRING);
		resize(main_picture.size());//窗口大小改为图片大小

		//加载界面
		ui.setupUi(this);

		//信号函数
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//设置生效
		connect(ui.pushButton_import, SIGNAL(clicked()), this, SLOT(import_set()));//导入设置
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(cancel_apply()));//取消设置

		//设置按钮样式
		ui.pushButton_import->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_14.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_14.png);}");

		//设置文字颜色
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::WindowText, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::Highlight, QColor(128, 76, 71, 64));
		ui.lineEdit_show_1->setPalette(text_palette);
		ui.lineEdit_show_2->setPalette(text_palette);
		ui.lineEdit_show_3->setPalette(text_palette);

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}
	UnlockNormalDoubleCheck::~UnlockNormalDoubleCheck()
	{
		
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void UnlockNormalDoubleCheck::mousePressEvent(QMouseEvent *event)
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
	void UnlockNormalDoubleCheck::mouseMoveEvent(QMouseEvent *event)
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
	void UnlockNormalDoubleCheck::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void UnlockNormalDoubleCheck::keyPressEvent(QKeyEvent *event)
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

	void UnlockNormalDoubleCheck::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//画图作为窗口背景
	}

	//设置成员函数
	void UnlockNormalDoubleCheck::set_information(QString key_type, QString method, QString *key, QString *head_digit, bool *have_head_digit, bool *is_continue, int *key_size)//设置需要显示在界面上的信息，参数为：密钥类型，加密方法，由二进制数据转化为文本的密钥，加密文件头部特征数字，是否有头部特征数字，是否确认解密，密钥大小
	{
		char_point_information = head_digit;//头部特征数字
		bool_information = have_head_digit;//是否有头部特征数字
		this->is_continue = is_continue;//如果点击确认，主界面接下来进行解密操作，否则不执行任何操作
		if (*bool_information)//有头部特征数字
		{
			ui.lineEdit_show_3->setText(*head_digit);//显示特征数字
		}
		else
		{
			ui.lineEdit_show_3->setText(DIALOG_LOCK_SIMPLE_DIRECTION_NO_HEAD_DIGIT_STRING);//显示无特征数字信息
		}
		this->key = key;
		this->key_type = key_type;//密钥类型
		this->key_size = key_size;//密钥大小
		this->method = method;//加密方法
		ui.lineEdit_show_1->setText(*key);
		ui.lineEdit_show_2->setText(QString::number(*key_size, 10));
		set_information_data(*key, *head_digit, *have_head_digit, *key_size);//先将数据存入该类自带的成员变量中，如果导入密钥文件再更新
		if (key_type == FILE_PUBLIC_KEY_TYPE_STRING)
		{
			ui.pushButton_apply->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_16.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_16.png);}");
			ui.pushButton_cancel->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_17.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_17.png);}");
		}
		else
		{
			ui.pushButton_apply->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_5.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_5.png);}");
			ui.pushButton_cancel->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_6.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_6.png);}");
		}
	}

	void UnlockNormalDoubleCheck::set_information_data(QString key, QString head_digit, bool have_head_digit, int key_size)//设置需要显示在界面上的信息，但不再传入指针，供之后使用。如果在之后使用指针传递，则会造成指针指向的地址改变，那么在确认后无法修改主窗口中相关属性的值
	{
		char_point_information_data = head_digit;//头部特征数字
		bool_information_data = have_head_digit;//是否有头部特征数字
		key_size_data = key_size;
		key_data = key;
		if (bool_information_data)//有头部特征数字
		{
			ui.lineEdit_show_3->setText(head_digit);//显示特征数字
		}
		else
		{
			ui.lineEdit_show_3->setText(DIALOG_LOCK_SIMPLE_DIRECTION_NO_HEAD_DIGIT_STRING);//显示无特征数字信息
		}
		ui.lineEdit_show_1->setText(key);
		ui.lineEdit_show_2->setText(QString::number(key_size, 10));
	}

	void UnlockNormalDoubleCheck::set_apply()//设置生效
	{
		*char_point_information = char_point_information_data;//将得到的值传给指针，以便于修改主界面相关变量的值
		*bool_information = bool_information_data;
		*key = key_data;
		*key_size = key_size_data;
		*is_continue = true;//点击确认，主界面接下来进行解密操作
		close_window_include_animation();//关闭窗口
	}

	void UnlockNormalDoubleCheck::cancel_apply()//设置取消
	{
		*is_continue = false;//点击取消，不执行任何操作
		close_window_include_animation();//关闭窗口
	}

	void UnlockNormalDoubleCheck::import_set()//导入设置
	{
		File dialog;//使用带有指定后缀过滤的打开文件窗口
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
			string file_path = string((const char *)file_dialog_file_name.toLocal8Bit());//QString转string
			ifstream keyfile(file_path, ios_base::in | ios_base::binary | ios_base::beg);//打开二进制密钥文件
			if (!keyfile.is_open())//文件打开失败
			{
				Help dialog;//显示程序信息
				dialog.set_dialog_information_path(DIALOG_INFORMATION_KEYFILE_CANNOT_OPEN_PATH_STRING);
				dialog.setWindowTitle(tr("打开文件失败！"));
				dialog.exec();
			}
			else
			{
				char* magic_number = new char[FILE_KEYFILE_MAGIC_NUMBER_STRING_SIZE_NUMBER];//读取魔术数字
				keyfile.read(magic_number, FILE_KEYFILE_MAGIC_NUMBER_STRING_SIZE_NUMBER);
				QByteArray magic_number_hex_string(magic_number, FILE_KEYFILE_MAGIC_NUMBER_STRING_SIZE_NUMBER);//存放加密文件头部魔法数字的十六进制数据
				magic_number_hex_string = magic_number_hex_string.toHex().toUpper();//获得十六进制数据，转换为大写
				if (magic_number_hex_string != FILE_KEY_FILE_MAGIC_NUMBER_HEX_STRING)//不和密钥文件对应的魔术数字相匹配
				{
					Help dialog;//显示程序信息
					dialog.set_dialog_information_path(DIALOG_INFORMATION_OPEN_WRONG_KEYFILE_PATH_STRING);
					dialog.setWindowTitle(tr("打开了错误的文件……"));
					dialog.exec();
				}
				else
				{
					int seek_offset = FILE_KEYFILE_MAGIC_NUMBER_STRING_SIZE_NUMBER;//文件指针偏移量
					seek_offset += FILE_KEYFILR_INTERVAL_NUMBER_HEX_STRING_SIZE_NUMBER;//分隔符
					keyfile.clear();//清空文件流，否则可能无法定位
					keyfile.seekg(seek_offset, ios_base::beg);//移动文件指针
					int type_number_digit;//加密类型
					keyfile.read((char*)&type_number_digit, sizeof(int));//读取加密类型
					seek_offset += sizeof(int);
					if (type_number_digit != FILE_KEY_WRITE_BINARY_TYPE_9_NUMBER && key_type == FILE_PUBLIC_KEY_TYPE_STRING && method == tr("RSA") || type_number_digit != FILE_KEY_WRITE_BINARY_TYPE_10_NUMBER && key_type == FILE_PRIVATE_KEY_TYPE_STRING && method == tr("RSA") || type_number_digit != FILE_KEY_WRITE_BINARY_TYPE_11_NUMBER && key_type == FILE_PUBLIC_KEY_TYPE_STRING && method == tr("ECC") || type_number_digit != FILE_KEY_WRITE_BINARY_TYPE_12_NUMBER && key_type == FILE_PRIVATE_KEY_TYPE_STRING && method == tr("ECC"))//不是正确的加密类型
					{
						Help dialog;//显示程序信息
						dialog.set_dialog_information_path(DIALOG_INFORMATION_OPEN_WRONG_KEYFILE_PATH_STRING);
						dialog.setWindowTitle(tr("打开了错误的文件……"));
						dialog.exec();
					}
					else
					{
						seek_offset += FILE_KEYFILR_INTERVAL_NUMBER_HEX_STRING_SIZE_NUMBER;//分隔符
						keyfile.clear();//清空文件流，否则可能无法定位
						keyfile.seekg(seek_offset, ios_base::beg);//移动文件指针
						int key_size;//密钥大小
						keyfile.read((char*)&key_size, sizeof(int));//读取密钥大小
						seek_offset += sizeof(int);
						char *key_number = new char[key_size / 2];//读取密钥数据。注意十六进制码的长度只有一半
						keyfile.read(key_number, key_size / 2);
						QByteArray key_number_hex_string(key_number, key_size / 2);//存放密钥内容十六进制位
						key_number_hex_string = key_number_hex_string.toHex().toUpper();//获得十六进制数据，转换为大写
						key_data = key_number_hex_string;
						seek_offset += key_size / 2;//分隔符	
						seek_offset += FILE_KEYFILR_INTERVAL_NUMBER_HEX_STRING_SIZE_NUMBER;//分隔符
						keyfile.clear();//清空文件流，否则可能无法定位
						keyfile.seekg(seek_offset, ios_base::beg);//移动文件指针
						keyfile.read((char*)&bool_information_data_int, sizeof(int));//读取是否有头部特征数字的判断量
						if (bool_information_data_int != 0)
						{
							seek_offset += sizeof(int);
							keyfile.clear();
							bool_information_data = true;
							char head_number[FILE_KEYFILE_HEAD_NUMBER_STRING_SIZE_NUMBER + 1] = {0};//读取特征数字。这里需要注意，如果特征数字为全空即“00000000”的时候，使用动态数组则会出现数组长度为0的情况，因此需要用固定长度的char数组
							keyfile.read(head_number, FILE_KEYFILE_HEAD_NUMBER_STRING_SIZE_NUMBER);
							QByteArray head_number_hex_string(head_number, FILE_KEYFILE_HEAD_NUMBER_STRING_SIZE_NUMBER);//存放加密文件头部魔法数字的十六进制数据
							head_number_hex_string = head_number_hex_string.toHex().toUpper();//获得十六进制数据，转换为大写
							char_point_information_data = head_number_hex_string;
						}
						else
						{
							bool_information_data = false;
							char_point_information_data = DIALOG_LOCK_SIMPLE_DIRECTION_NO_HEAD_DIGIT_STRING;
						}
						keyfile.close();
						set_information_data(key_data, char_point_information_data, bool_information_data, key_size);//传递修改后信息，此时不能再用指针传值，否则会造成相应变量指向地址的改变
					}
				}
				delete magic_number;
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

	void UnlockNormalDoubleCheck::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

