#include "define.h"

namespace rem
{
	
	//引用全局变量
	extern int counter_mutex;

	//构造与析构函数
	CounterSet::CounterSet(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序					
		counter_mutex--;//允许的计时器窗口的数目减少1
		is_escape_pressed = false;//默认未按下esc键以退出

		//加载图片作为窗口背景
		main_picture.load(DIALOG_COUNTER_SET_BACKGROUND_PICTURE_PATH_STRING);
		resize(main_picture.size());//窗口大小改为图片大小

		//加载界面
		ui.setupUi(this);
		
		//加载单选框分组
		radioButton_type = new QButtonGroup(this);
		radioButton_type->addButton(ui.radioButton_type_1);
		radioButton_type->addButton(ui.radioButton_type_2);
		radioButton_voice = new QButtonGroup(this);
		radioButton_voice->addButton(ui.radioButton_voice_1);
		radioButton_voice->addButton(ui.radioButton_voice_2);
		radioButton_voice->addButton(ui.radioButton_voice_3);
		radioButton_voice->addButton(ui.radioButton_voice_4);
		radioButton_voice->addButton(ui.radioButton_voice_5);
		radioButton_dialog = new QButtonGroup(this);
		radioButton_dialog->addButton(ui.radioButton_dialog_1);
		radioButton_dialog->addButton(ui.radioButton_dialog_2);

		//按钮初始状态
		ui.radioButton_type_1->setChecked(true);
		ui.radioButton_voice_1->setChecked(true);
		ui.radioButton_dialog_1->setChecked(true);

		//信号函数
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//设置生效
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//取消设置

		//设置文字颜色
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::WindowText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::Highlight, QColor(70, 28, 10, 64));
		ui.spinBox_hour->setPalette(text_palette);
		ui.spinBox_minute->setPalette(text_palette);
		ui.spinBox_second->setPalette(text_palette);

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}
	CounterSet::~CounterSet()
	{
		counter_mutex++;//防止点退出键时无法再次进入该窗口
		delete radioButton_type;
		delete radioButton_voice;
		delete radioButton_dialog;
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void CounterSet::mousePressEvent(QMouseEvent *event)
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
	void CounterSet::mouseMoveEvent(QMouseEvent *event)
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
	void CounterSet::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void CounterSet::keyPressEvent(QKeyEvent *event)
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

	void CounterSet::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(WINDOW_BACKGROUND_PAINT_START_X_NUMBER, WINDOW_BACKGROUND_PAINT_START_Y_NUMBER, main_picture);//画图作为窗口背景
	}

	void CounterSet::set_apply()//设置生效
	{
		Counter *dialog = new Counter;//计时器采用非模态窗口
		QAbstractButton *radioButton_type_clicked = qobject_cast<QAbstractButton *> (radioButton_type->checkedButton());//确定每个组中被选中的单选框，返回的是对象
		QAbstractButton *radioButton_voice_clicked = qobject_cast<QAbstractButton *> (radioButton_voice->checkedButton());
		QAbstractButton *radioButton_dialog_clicked = qobject_cast<QAbstractButton *> (radioButton_dialog->checkedButton());
		QString a = radioButton_type_clicked->objectName();
		if (!QString::compare(radioButton_type_clicked->objectName(), "radioButton_type_1", Qt::CaseSensitive))//判断对象名是否相等，并且比较时区分大小写。注意字符串比较，相等时返回的值为0。传递单选框组1的数据
		{
			dialog->set_setting_information(0, 1);//传入数据，接受的数据用数组表示，数组索引表示单选框组或者数字选择框的序号，元素值表示单选框组被选中的单选框的序号或者数字选择框的值
		}
		else if (!QString::compare(radioButton_type_clicked->objectName(), "radioButton_type_2", Qt::CaseSensitive))
		{
			dialog->set_setting_information(0, 2);
		}
		else
		{
			dialog->set_setting_information(0, 1);
		}
		dialog->set_setting_information(1, ui.spinBox_hour->value());//传递三个数字选择框的数据
		dialog->set_setting_information(2, ui.spinBox_minute->value());
		dialog->set_setting_information(3, ui.spinBox_second->value());
		if (!QString::compare(radioButton_voice_clicked->objectName(), "radioButton_voice_1", Qt::CaseSensitive))//传递单选框组2的数据
		{
			dialog->set_setting_information(4, 1);
		}
		else if (!QString::compare(radioButton_voice_clicked->objectName(), "radioButton_voice_2", Qt::CaseSensitive))
		{
			dialog->set_setting_information(4, 2);
		}
		else if (!QString::compare(radioButton_voice_clicked->objectName(), "radioButton_voice_3", Qt::CaseSensitive))
		{
			dialog->set_setting_information(4, 3);
		}
		else if (!QString::compare(radioButton_voice_clicked->objectName(), "radioButton_voice_4", Qt::CaseSensitive))
		{
			dialog->set_setting_information(4, 4);
		}
		else if (!QString::compare(radioButton_voice_clicked->objectName(), "radioButton_voice_5", Qt::CaseSensitive))
		{
			dialog->set_setting_information(4, 5);
		}
		else
		{
			dialog->set_setting_information(4, 1);
		}
		if (!QString::compare(radioButton_dialog_clicked->objectName(), "radioButton_dialog_1", Qt::CaseSensitive))//传递单选框组3的数据
		{
			dialog->set_setting_information(5, 1);
		}
		else if (!QString::compare(radioButton_dialog_clicked->objectName(), "radioButton_dialog_2", Qt::CaseSensitive))
		{
			dialog->set_setting_information(5, 2);
		}
		dialog->set_beginning_value();//设置初始值
		close_window_include_animation();//设置完毕后关闭设置窗口并启动计时器
		dialog->setModal(false);//指定为非模态对话框
		dialog->show();
	}

	void CounterSet::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

