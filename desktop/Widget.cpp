#include "define.h"

namespace rem
{

	//引用全局变量
	extern bool widget_mutex[7];

	//导入标准命名空间
	using std::wstring;

	//构造与析构函数
	Widget::Widget(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint | windowFlags());//去掉窗口标题栏，并且任务栏中不会出现窗口，窗口始终在最顶层。这里不能使用Qt::SubWindow属性，否则无法接收拖拽事件
		resize(DIALOG_WEDGIT_SIZE_WIDTH_NUMBER, DIALOG_WEDGIT_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		setAttribute(Qt::WA_WState_WindowOpacitySet, true);//该窗口允许直接设置透明度
		setAttribute(Qt::WA_DeleteOnClose);//退出时销毁该窗口以免内存泄漏
		is_escape_pressed = false;//默认未按下esc键以退出

		//加载界面，必须放在最后以避免界面被之后的绘图覆盖
		ui.setupUi(this);

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存

		//启用全局的放下操作
		this->setAcceptDrops(true);
	}
	Widget::~Widget()
	{
		//将配置文件相应内容修改为禁止
		QSettings *write_setting = new QSettings(FILE_SETTING_STATIC_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		QString temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(widget_id, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		write_setting->setValue(temp, 0);
		delete write_setting;
		widget_mutex[widget_id] = true;//允许该控件
	}

	//设置成员变量
	void Widget::set_attribute(bool on_top, int widget_id, int transparent, wstring program_path)//设置使用的图片id和打开程序路径
	{
		this->on_top = on_top;
		this->widget_id = widget_id;
		this->program_path = program_path;
		this->transparent = transparent;
		QString filepath = DIALOG_WIDGET_BACKGROUND_PICTURE_PATH_FRONT_STRING + QString::number(widget_id, 10);//背景图片路径
		filepath += DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING;
		picture.load(filepath);
		
		//禁止再创建一个该窗口
		widget_mutex[widget_id] = false;

		//修改坐标
		QSettings *setting_dynamic = new QSettings(FILE_SETTING_DYNAMIC_PATH_STRING, QSettings::IniFormat);//读取ini文件中的信息
		QString temp_path = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;//定义需要寻找的内容所在路径
		temp_path += QString::number(widget_id, 10);
		temp_path += FILE_SETTING_DYNAMIC_CATALOG_2_1_BACK_INNER_PATH_STRING;
		position[0] = setting_dynamic->value(temp_path).toInt();//修正坐标
		temp_path = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;
		temp_path += QString::number(widget_id, 10);
		temp_path += FILE_SETTING_DYNAMIC_CATALOG_2_2_BACK_INNER_PATH_STRING;
		position[1] = setting_dynamic->value(temp_path).toInt();
		delete setting_dynamic;
		if (position[0] < 0 || position[1] < 0)
		{
			position[0] = 0;
			position[1] = 0;
		}
		else
		{

		}
		move(position[0], position[1]);//修改窗口起始坐标

		//设置是否在最顶层
		if (on_top)
		{
			setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);//窗口总是显示在最前面
		}
		else
		{
			setWindowFlags(windowFlags()&~Qt::WindowStaysOnTopHint);//窗口不会总是显示在最前面
		}
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void Widget::mousePressEvent(QMouseEvent *event)
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
	void Widget::mouseMoveEvent(QMouseEvent *event)
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}

		//获取主界面坐标。在结束之后，将坐标写入动态信息配置文件
		position[0] = this->pos().x();
		position[1] = this->pos().y();
	}

	//鼠标未被按下，则相应变量为false
	void Widget::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;

		//释放鼠标后，记录主界面坐标并写入配置文件
		QSettings *write_setting = new QSettings(FILE_SETTING_DYNAMIC_PATH_STRING, QSettings::IniFormat);
		QString temp_path = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;//定义需要寻找的内容所在路径
		temp_path += QString::number(widget_id, 10);
		temp_path += FILE_SETTING_DYNAMIC_CATALOG_2_1_BACK_INNER_PATH_STRING;
		write_setting->setValue(temp_path, QString::number(position[0], 10));
		temp_path = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;
		temp_path += QString::number(widget_id, 10);
		temp_path += FILE_SETTING_DYNAMIC_CATALOG_2_2_BACK_INNER_PATH_STRING;
		write_setting->setValue(temp_path, QString::number(position[1], 10));
		delete write_setting;
	}

	//鼠标事件，用于启动程序
	void Widget::mouseDoubleClickEvent(QMouseEvent *event) 
	{
		HINSTANCE return_value;//指定返回值
		return_value = ShellExecute(NULL, L"open", program_path.c_str(), NULL, NULL, SW_SHOWNORMAL);//打开程序
		if (program_path != FILE_SETTING_OPEN_PATH_UNDEFINE_DEFAULT_STRING)
		{
			if (return_value >= (HINSTANCE)0 && return_value <= (HINSTANCE)31)//无法打开指定程序
			{
				Help dialog;//信息提示框
				dialog.setWindowTitle(tr("程序失踪了！"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_START_PROGRAM_PATH_STRING);//提示信息
				dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
			}
			else if (return_value >= (HINSTANCE)32)//已经打开，正常运行
			{

			}
			else//其他异常情况
			{

			}
		}
		else
		{

		}
	}

	//拖拽事件
	void Widget::dragEnterEvent(QDragEnterEvent *event)
	{
		if (event->mimeData()->hasUrls())//防止出现拖拽文本框中的文字造成Url识别出错，然后程序崩溃
		{
			event->acceptProposedAction(); //可以在这个窗口部件上拖放对象
		}
		else
		{

		}
	}

	void Widget::dropEvent(QDropEvent *event)//释放时执行的操作
	{
		QList<QUrl> urls = event->mimeData()->urls();
		QString file_name = urls.first().toLocalFile();//获得文件名
		file_name = (file_name).replace(tr("/"), tr("\\"));
		wstring transform_path = file_name.toStdWString();//将Qstring转化为wstring，因为wstring就是Unicode字符串，因此这样转化不会导致乱码
		HINSTANCE return_value;//指定返回值
		return_value = ShellExecute(NULL, L"open", transform_path.c_str(), NULL, NULL, SW_SHOWNORMAL);//打开程序
		if (transform_path != FILE_SETTING_OPEN_PATH_UNDEFINE_DEFAULT_STRING)
		{
			if (return_value >= (HINSTANCE)0 && return_value <= (HINSTANCE)31)//无法打开指定程序
			{
				Help dialog;//信息提示框
				dialog.setWindowTitle(tr("程序失踪了！"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_START_PROGRAM_PATH_STRING);//提示信息
				dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
			}
			else if (return_value >= (HINSTANCE)32)//已经打开，正常运行
			{

			}
			else//其他异常情况
			{

			}
		}
		else
		{

		}
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void Widget::keyPressEvent(QKeyEvent *event)
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

	void Widget::paintEvent(QPaintEvent *)
	{

		//绘制图片
		QPainter background_painter(this);
		background_painter.setOpacity((double)transparent / 10);
		background_painter.drawPixmap(0, 0, DIALOG_WEDGIT_SIZE_WIDTH_NUMBER, DIALOG_WEDGIT_SIZE_HEIGHT_NUMBER, picture);
	}

	void Widget::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

