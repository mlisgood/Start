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
	LockSimpleAddGetDigit::LockSimpleAddGetDigit(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序					
		is_escape_pressed = false;//默认未按下esc键以退出

		//加载图片作为窗口背景
		main_picture.load(DIALOG_BACKGROUND_LOCK_SIMPLE_ADD_GET_DIGIT_PATH_STRING);
		resize(main_picture.size());//窗口大小改为图片大小

		//加载界面
		ui.setupUi(this);

		//信号函数
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//设置生效
		connect(ui.pushButton_list_1, SIGNAL(clicked()), this, SLOT(add_item()));//添加项目
		connect(ui.pushButton_list_4, SIGNAL(clicked()), this, SLOT(edit_item()));//修改项目
		connect(ui.pushButton_list_2, SIGNAL(clicked()), this, SLOT(delete_item()));//删除项目
		connect(ui.pushButton_list_3, SIGNAL(clicked()), this, SLOT(delete_all_item()));//删除全部项目
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(cancel_apply()));//取消设置

		//设置按钮样式
		ui.pushButton_apply->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_10.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_10.png);}");
		ui.pushButton_cancel->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_11.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_11.png);}");

		//设置文字颜色
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::WindowText, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::Highlight, QColor(128, 76, 71, 64));
		ui.listWidget_1->setPalette(text_palette);
		ui.spinBox_1->setPalette(text_palette);
		ui.spinBox_2->setPalette(text_palette);

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存

		//设置控件字体
		extern QString font_str;//因为listWidget_1内部的控件字体无法使用默认字体设置，因此必须单独设置。注意因为没有命名空间的关系，这个在main函数外面定义的全局变量不能和find_dialog_mutex一样在外面进行定义，否则会被当成一个新定义的全局变量rem::font_str
		if (font_str != "")
		{
			QFont file_font(font_str, FILE_FONT_DEFAULT_SIZE);//设置默认字体
			ui.listWidget_1->setFont(file_font);
		}
		else//加载失败，使用软件设定好的默认字体
		{

		}
	}
	LockSimpleAddGetDigit::~LockSimpleAddGetDigit()
	{
		
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void LockSimpleAddGetDigit::mousePressEvent(QMouseEvent *event)
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
	void LockSimpleAddGetDigit::mouseMoveEvent(QMouseEvent *event)
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
	void LockSimpleAddGetDigit::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void LockSimpleAddGetDigit::keyPressEvent(QKeyEvent *event)
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

	void LockSimpleAddGetDigit::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//画图作为窗口背景
	}

	//设置成员函数
	void LockSimpleAddGetDigit::set_information(int *extra_digit_array)//设置需要显示在界面上的信息，参数为包含加减数量和循环单位数目的数组
	{
		int_information[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER] = &extra_digit_array[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER];//传入单元数量
		ui.spinBox_2->setValue(*int_information[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER]);
		for (int index = 0; index < DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER; index++)//传入各单元加减数量
		{
			int_information[index] = &extra_digit_array[index];//这里需要注意格式。因为使用了int指针数组，所以应该把地址赋给数组，而不是使用*int_information[index] = extra_digit_array[index]这种方式直接赋值，否则因为指针数组没有初始化，导致没有地址，赋值给没有地址的指针而出现野指针的情况，会出现内存访问冲突的问题
		}
		for (int index = 0; index < *int_information[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER]; index++)//传入各单元加减数量
		{
			QString transform_result = QString::number((*(int_information[index])), 10);//如果单元数量不足16，那列表的数量也不会达到16，但是16个指针数组的地址必须全部赋值，否则会出现内存访问冲突的问题。只需要控制显示在列表中的单元数目即可
			if (transform_result != "")
			{
				ui.listWidget_1->addItem(transform_result);//将各项目添加进listwidget
			}
			else
			{
				ui.listWidget_1->addItem(DIALOG_LOCK_SIMPLE_ADD_DEFAULT_UNIT_INSERT_STRING);
			}
		}
	}

	void LockSimpleAddGetDigit::add_item()
	{
		if (ui.listWidget_1->count() < DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER)//限制项目数量
		{
			if (ui.spinBox_1->text() != "")
			{
				QString transform_result = QString::number(ui.spinBox_1->value(), 10);//先转换一次，以去除整数开头的“0”，如“0028”通过去除成为“28”
				ui.listWidget_1->addItem(transform_result);//将项目添加进listwidget
			}
			else
			{
				ui.listWidget_1->addItem(DIALOG_LOCK_SIMPLE_ADD_DEFAULT_UNIT_INSERT_STRING);
			}
		}
		else
		{

		}
	}

	void LockSimpleAddGetDigit::edit_item()
	{
		if (ui.listWidget_1->currentItem() != Q_NULLPTR)
		{
			QString transform_result = QString::number(ui.spinBox_1->value(), 10);//先转换一次，以去除整数开头的“0”，如“0028”通过去除成为“28”
			ui.listWidget_1->currentItem()->setText(transform_result);//修改项目数值
		}
	}

	void LockSimpleAddGetDigit::delete_item()
	{
		if (ui.listWidget_1->currentItem() != Q_NULLPTR)
		{
			QListWidgetItem *item = ui.listWidget_1->takeItem(ui.listWidget_1->currentRow());//删除项目
			delete item;//删除指针
		}
		else
		{

		}
	}

	void LockSimpleAddGetDigit::delete_all_item()
	{
		int temp_count = ui.listWidget_1->count();//必须初始时候将这个值赋给另一个变量，不能直接放进循环作为判断条件，因为在循环过程中每次循环会使其减少1
		for (int temp = 0; temp < temp_count; temp++)
		{
			QListWidgetItem *item = ui.listWidget_1->takeItem(0);//注意是每次删除最上面一项，因为每删除一项，其余项会自动移到上面
			delete item;
		}
	}

	void LockSimpleAddGetDigit::set_apply()//设置生效
	{
		for (int index = 0; index < DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER; index++)//先把数组元素清零，防止出现列表中元素的数目小于循环单位数，导致后面部分仍然是之前设置的值的情况
		{
			*int_information[index] = 0;
		}
		for (int index = 0; index < ui.listWidget_1->count(); index++)//传入各单元加减数量
		{
			bool is_success;
			*int_information[index] = (ui.listWidget_1->item(index)->text()).toInt(&is_success, 10);
			if (!is_success)//转化失败
			{
				*int_information[index] = 0;
			}
			else
			{

			}
		}
		*int_information[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER] = ui.spinBox_2->value();//传入单元数量
		close_window_include_animation();//关闭窗口
	}

	void LockSimpleAddGetDigit::cancel_apply()//设置取消
	{
		close_window_include_animation();//关闭窗口
	}

	void LockSimpleAddGetDigit::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

