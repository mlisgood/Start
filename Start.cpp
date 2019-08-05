#include "define.h"

namespace rem
{

	//构造与析构函数
	Start::Start(QWidget *parent) : QMainWindow(parent)
	{

		//常规初始化
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);//去掉窗口标题栏并且窗口可以通过点击任务栏放大缩小
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, true);//该窗口关闭时会退出程序
		setAttribute(Qt::WA_WState_WindowOpacitySet, true);//该窗口允许直接设置透明度
		is_escape_pressed = false;//默认未按下esc键以退出

		//加载图片
		main_pixmap.load(WINDOW_START_BACKGROUND_PICTURE_PATH_STRING);
		resize(main_pixmap.size());

		//加载界面，必须放在最后以避免界面被之后的绘图覆盖
		ui.setupUi(this);
	
		//信号函数
		connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(item1_clicked()));//item1
		connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(item2_clicked()));//item2
		connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(item3_clicked()));//item3
		connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(item4_clicked()));//item4
		connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(item5_clicked()));//item5

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}
	Start::~Start()
	{

	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void Start::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bPressed = true;
			m_point = event->pos();
		}
	}
	//若鼠标左键被按下，则移动窗体位置
	void Start::mouseMoveEvent(QMouseEvent *event)
	{
		if (m_bPressed)
			move(event->pos() - m_point + pos());
	}

	//鼠标未被按下，则相应变量为false
	void Start::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);

		m_bPressed = false;
	}

	void Start::paintEvent(QPaintEvent *)
	{

		//绘制背景
		QPainter background_painter(this);
		background_painter.drawPixmap(0, 0, main_pixmap.width(), main_pixmap.height(), main_pixmap);
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void Start::keyPressEvent(QKeyEvent *event)
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

	//按钮事件
	//Item1_notepad
	void Start::item1_clicked()//指定按钮被点击
	{

		//如果找到相应程序，则将其打开，然后关闭该程序；否则，不关闭该程序，并且出现提示窗口
		HINSTANCE return_value;//指定返回值
		return_value = ShellExecute(NULL, L"open", L".\\Notepad.exe", NULL, NULL, SW_SHOWNORMAL);//打开程序
		if (return_value == (HINSTANCE)0)//内存不足
		{
			Filemissing dialog;//显示提示框
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_1_FLAG);//使用状态1
			dialog.setWindowTitle(tr("程序失踪了！"));
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else if (return_value >= (HINSTANCE)1 && return_value <= (HINSTANCE)31)//其余情况直接统一处理为无法打开指定程序
		{
			Filemissing dialog;//显示提示框
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_2_FLAG);//使用状态2
			dialog.setWindowTitle(tr("程序失踪了！"));
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else if (return_value >= (HINSTANCE)32)//已经打开，正常运行
		{

		}
		else//其他异常情况
		{

		}
	}

	void Start::item2_clicked()//指定按钮被点击
	{

		//如果找到相应程序，则将其打开，然后关闭该程序；否则，不关闭该程序，并且出现提示窗口
		HINSTANCE return_value;//指定返回值
		return_value = ShellExecute(NULL, L"open", L".\\Tools.exe", NULL, NULL, SW_SHOWNORMAL);//打开程序
		if (return_value == (HINSTANCE)0)//内存不足
		{
			Filemissing dialog;//显示提示框
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_1_FLAG);//使用状态1
			dialog.setWindowTitle(tr("程序失踪了！"));
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else if (return_value >= (HINSTANCE)1 && return_value <= (HINSTANCE)31)//其余情况直接统一处理为无法打开指定程序
		{
			Filemissing dialog;//显示提示框
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_2_FLAG);//使用状态2
			dialog.setWindowTitle(tr("程序失踪了！"));
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else if (return_value >= (HINSTANCE)32)//已经打开，正常运行
		{

		}
		else//其他异常情况
		{

		}
	}

	void Start::item3_clicked()//指定按钮被点击
	{

		//如果找到相应程序，则将其打开，然后关闭该程序；否则，不关闭该程序，并且出现提示窗口
		HINSTANCE return_value;//指定返回值
		return_value = ShellExecute(NULL, L"open", L".\\Lock.exe", NULL, NULL, SW_SHOWNORMAL);//打开程序
		if (return_value == (HINSTANCE)0)//内存不足
		{
			Filemissing dialog;//显示提示框
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_1_FLAG);//使用状态1
			dialog.setWindowTitle(tr("程序失踪了！"));
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else if (return_value >= (HINSTANCE)1 && return_value <= (HINSTANCE)31)//其余情况直接统一处理为无法打开指定程序
		{
			Filemissing dialog;//显示提示框
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_2_FLAG);//使用状态2
			dialog.setWindowTitle(tr("程序失踪了！"));
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else if (return_value >= (HINSTANCE)32)//已经打开，正常运行
		{

		}
		else//其他异常情况
		{

		}
	}

	void Start::item4_clicked()//指定按钮被点击
	{

		//如果找到相应程序，则将其打开，然后关闭该程序；否则，不关闭该程序，并且出现提示窗口
		HINSTANCE return_value;//指定返回值
		return_value = ShellExecute(NULL, L"open", L".\\Desktop.exe", NULL, NULL, SW_SHOWNORMAL);//打开程序
		if (return_value == (HINSTANCE)0)//内存不足
		{
			Filemissing dialog;//显示提示框
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_1_FLAG);//使用状态1
			dialog.setWindowTitle(tr("程序失踪了！"));
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else if (return_value >= (HINSTANCE)1 && return_value <= (HINSTANCE)31)//其余情况直接统一处理为无法打开指定程序
		{
			Filemissing dialog;//显示提示框
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_2_FLAG);//使用状态2
			dialog.setWindowTitle(tr("程序失踪了！"));
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else if (return_value >= (HINSTANCE)32)//已经打开，正常运行
		{

		}
		else//其他异常情况
		{

		}
	}

	void Start::item5_clicked()//指定按钮被点击
	{
		copy_files(FILE_COPY_SOURCE_1_PATH_STRING, FILE_COPY_TARGET_1_PATH_STRING);
		copy_files(FILE_COPY_SOURCE_2_PATH_STRING, FILE_COPY_TARGET_2_PATH_STRING);
		copy_files(FILE_COPY_SOURCE_3_PATH_STRING, FILE_COPY_TARGET_3_PATH_STRING);
		copy_files(FILE_COPY_SOURCE_4_PATH_STRING, FILE_COPY_TARGET_4_PATH_STRING);
	}

	//其他功能
	bool Start::copy_files(const QString &source_dir, const QString &target_dir)//拷贝文件夹
	{
		QDir sourceDir(source_dir);
		QDir targetDir(target_dir);
		if (!targetDir.exists())//目标目录不存在则创建
		{
			if (!targetDir.mkdir(targetDir.absolutePath()))
			{
				return false;
			}
			else
			{

			}
		}
		else
		{

		}
		QFileInfoList fileInfoList = sourceDir.entryInfoList();
		foreach(QFileInfo fileInfo, fileInfoList)
		{
			if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			{
				continue;
			}
			else
			{

			}
			if (fileInfo.isDir())//当为目录时，递归进行copy
			{
				if (!copy_files(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName())))
				{
					return false;
				}
				else
				{

				}
			}
			else//存在文件则先将其删除
			{
				if (targetDir.exists(fileInfo.fileName()))
				{
					targetDir.remove(fileInfo.fileName());
				}
				else
				{

				}
				if (!QFile::copy(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName())))//复制文件
				{
					return false;
				}
				else
				{

				}
			}
		}
		return true;
	}

	void Start::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

