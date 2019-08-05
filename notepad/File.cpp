#include "define.h"

namespace rem
{

	//构造与析构函数
	File::File(QWidget *parent) : QDialog(parent)
	{

		//常规初始化
		totalrandomnumber = DIALOG_RANDOM_MIN_NUMBER + rand() % (DIALOG_RANDOM_MAX_NUMBER - DIALOG_RANDOM_MIN_NUMBER + 1);//产生指定随机数以便决定背景图片和人物图片样式
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏
		resize(DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_WIDTH_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		is_escape_pressed = false;//允许按下esc键退出程序

		//设置图片路径
		dialog_information_path_temp = DIALOG_INFORMATION_FILE_PICTURE_PATH_STRING + QString::number(totalrandomnumber, 10);//文字信息图片路径
		dialog_information_path_temp += DIALOG_FILE_BACKGROUND_PICTURE_PATH_BACK_STRING;
		dialog_information_head_path_temp = DIALOG_INFORMATION_FILE_HEAD_PICTURE_PATH_STRING + QString::number(totalrandomnumber, 10);//文字头部信息图片路径
		dialog_information_head_path_temp += DIALOG_FILE_BACKGROUND_PICTURE_PATH_BACK_STRING;
		filepath_background = DIALOG_FILE_BACKGROUND_PICTURE_PATH_FRONT_STRING + QString::number(totalrandomnumber, 10);//背景信息图片路径
		filepath_background += DIALOG_FILE_BACKGROUND_PICTURE_PATH_BACK_STRING;


		//加载界面，必须放在最后以避免界面被之后的绘图覆盖
		ui.setupUi(this);

		//加载按钮样式
		ui.pushButton_exit->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_filedialog_exit_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_filedialog_exit_pressed.png);}");

		//连接处理函数
		connect(ui.treeView_file, SIGNAL(clicked(QModelIndex)), this, SLOT(get_tree_view_selected_file_name(QModelIndex)));//信号函数设置，用于点击树状图时获得文件路径
		connect(ui.textEdit_name, SIGNAL(textChanged(const QString &)), this, SLOT(get_text_edit_file_name()));//信号函数设置，用于文本框改变时获得文件路径
		connect(ui.pushButton_open, SIGNAL(clicked()), this, SLOT(open_or_save_button()));//打开或者保存按钮
		connect(ui.treeView_file, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(open_or_save_branch()));//双击树状图分支实现和按下打开或保存按钮同样的功能，但需要判断是否为路径

		//关闭按钮
		connect(ui.pushButton_close_window, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));
		connect(ui.pushButton_exit, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));

		//设置文字颜色
		QPalette total_palette;
		if (totalrandomnumber == 1)//决定相关文字颜色
		{
			total_palette.setColor(QPalette::Text, QColor(255, 83, 185, 255));
			total_palette.setColor(QPalette::HighlightedText, QColor(255, 83, 185, 255));
			total_palette.setColor(QPalette::Highlight, QColor(255, 83, 185, 64));
		}
		else if (totalrandomnumber == 2)
		{
			total_palette.setColor(QPalette::Text, QColor(133, 153, 212, 255));
			total_palette.setColor(QPalette::HighlightedText, QColor(133, 153, 212, 255));
			total_palette.setColor(QPalette::Highlight, QColor(133, 153, 212, 64));
		}
		else if (totalrandomnumber == 3)
		{
			total_palette.setColor(QPalette::Text, QColor(222, 63, 235, 255));
			total_palette.setColor(QPalette::HighlightedText, QColor(222, 63, 235, 255));
			total_palette.setColor(QPalette::Highlight, QColor(222, 63, 235, 64));
		}
		else if (totalrandomnumber == 4)
		{
			total_palette.setColor(QPalette::Text, QColor(242, 153, 93, 255));
			total_palette.setColor(QPalette::HighlightedText, QColor(242, 153, 93, 255));
			total_palette.setColor(QPalette::Highlight, QColor(242, 153, 93, 64));
		}
		else if (totalrandomnumber == 5)
		{
			total_palette.setColor(QPalette::Text, QColor(71, 185, 78, 255));
			total_palette.setColor(QPalette::HighlightedText, QColor(71, 185, 78, 255));
			total_palette.setColor(QPalette::Highlight, QColor(71, 185, 78, 64));
		}
		else
		{

		}
		ui.textEdit_name->setPalette(total_palette);
		ui.treeView_file->setPalette(total_palette);

		//去掉关联性控件的右键菜单
		ui.treeView_file->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
		ui.treeView_file->horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}
	File::~File()
	{
		delete file_tree;
	}

	//设置成员变量
	void File::set_button_save_or_open(int status)//设置按钮
	{
		open_or_save = status;
		if (status == 0)
		{
			ui.pushButton_open->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_filedialog_open_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_filedialog_open_pressed.png);}");
		}
		else if (status == 1)
		{
			ui.pushButton_open->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_filedialog_save_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_filedialog_save_pressed.png);}");
		}
		else
		{

		}
	}

	void File::set_file_path_address(QString *path)//设置文件名地址
	{
		file_path = path;
		file_path_show = *file_path;
		file_path_show = (file_path_show).replace(tr("/"), tr("\\"));//替换路径中的指定字符
		ui.textEdit_name->setText(file_path_show);
	}

	void File::set_file_dialog_status_address(bool *status)//设置窗口参数地址
	{
		file_dialog_status = status;
		*file_dialog_status = false;
	}

	void File::set_current_path(QString object_string)//传入当前工作路径
	{
		current_path = object_string;

		//文件目录
		file_tree = new QFileSystemModel;//为file_tree申请空间，否则将会是一个空指针
		file_tree->setReadOnly(true);//设置不能修改，否则双击会变成重命名
		file_tree->setRootPath("");//根目录默认
		ui.treeView_file->setModel(file_tree);//设置树状图是用的显示模型是文件目录
		ui.treeView_file->header()->setStretchLastSection(true);//树状图头部设置
		ui.treeView_file->header()->setSortIndicator(0, Qt::AscendingOrder);//按文件类型排序
		ui.treeView_file->header()->setSortIndicatorShown(true);
		ui.treeView_file->header()->hide();//隐藏表头
		QModelIndex index = file_tree->index(current_path);
		ui.treeView_file->expand(index);//当前项展开
		ui.treeView_file->scrollTo(index);//定位到当前项
		ui.treeView_file->resizeColumnToContents(0);
		ui.treeView_file->setColumnWidth(0, 250);//设置列宽
		ui.treeView_file->setColumnWidth(1, 0);
		ui.treeView_file->setColumnWidth(2, 100);
		ui.treeView_file->setColumnWidth(3, 100);
		extern QString font_str;//因为treeView内部的控件字体无法使用默认字体设置，因此必须单独设置。注意因为没有命名空间的关系，这个在main函数外面定义的全局变量不能和find_dialog_mutex一样在外面进行定义，否则会被当成一个新定义的全局变量rem::font_str
		if (font_str != "")
		{
			QFont file_font(font_str, FILE_FONT_DEFAULT_SIZE);//设置默认字体
			ui.treeView_file->setFont(file_font);
		}
		else//加载失败，使用软件设定好的默认字体
		{

		}
	}
	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void File::mousePressEvent(QMouseEvent *event)
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
	void File::mouseMoveEvent(QMouseEvent *event)
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
	void File::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉，因此这里除了修改回车键的功能，还要加上原来的esc键的功能
	void File::keyPressEvent(QKeyEvent *event)
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

	void File::paintEvent(QPaintEvent *)
	{

		//绘制窗口用到的图片。具体方法：首先指派5种背景风格。之后从5组随机数中选取一个，映射到其中一种风格上面。以下是对应的映射关系：[1,5]->ココア，[6,10]->チノ，[11,15]->リゼ，[16,20]->シャロ,[21,25]->千夜。此外，之后的其他图片也和构建背景使用的随机数有关。每个背景对应3张图片，每次随机选取1张。
		//以下功能用到了常量，如要修改最好重写
		//绘制图片
		QPainter background_painter(this);//背景
		QPainter margin_painter(this);//边框
		QPainter information_painter(this);//文字
		QPainter information_head_painter(this);//文字头部
		QPixmap background_picture;
		QPixmap margin_picture;
		QPixmap information_picture;
		QPixmap information_head_picture;
		background_picture.load(filepath_background);
		margin_picture.load((QString)DIALOG_FILE_MARGIN_PICTURE_PATH_STRING);
		information_picture.load(dialog_information_path_temp);
		information_head_picture.load(dialog_information_head_path_temp);
		background_painter.drawPixmap(0, 0, DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_WIDTH_NUMBER, background_picture);
		information_painter.drawPixmap(DIALOG_INFORMATION_FILE_X_OFFSET_NUMBER, DIALOG_INFORMATION_FILE_Y_OFFSET_NUMBER, DIALOG_INFORMATION_FILE_WIDTH_NUMBER, DIALOG_INFORMATION_FILE_HEIGHT_NUMBER, information_picture);//文字部分应该从左边的图片部分的右边缘开始
		information_head_painter.drawPixmap(DIALOG_INFORMATION_FILE_HEAD_X_OFFSET_NUMBER, DIALOG_INFORMATION_FILE_HEAD_Y_OFFSET_NUMBER, DIALOG_INFORMATION_FILE_WIDTH_NUMBER, DIALOG_INFORMATION_FILE_HEIGHT_NUMBER, information_head_picture);//文字部分应该从左边的图片部分的右边缘开始
		margin_painter.drawPixmap(0, 0, DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_WIDTH_NUMBER, margin_picture);//最后显示以免被图片覆盖
	}

	void File::get_tree_view_selected_file_name(const QModelIndex &index)//文件路径
	{
		if (file_tree->fileInfo(index).isDir())//是路径
		{
			if (open_or_save == 0)//打开
			{

			}
			else if (open_or_save == 1)//保存
			{
				QString file_name = file_tree->filePath(index);//是路径则加上文件名
				file_name += tr("/未命名.txt");
				file_name = (file_name).replace(tr("/"), tr("\\"));//替换路径中的指定字符
				file_name = (file_name).replace(tr("\\\\"), tr("\\"));//根目录下由于其自带一个"\\"，会导致实际显示两个"\"，因此需要将其替换
				*file_path = file_name;
			}
			else
			{

			}
		}
		else
		{
			QString file_name = file_tree->filePath(index);//是路径则加上文件名
			file_name = (file_name).replace(tr("/"), tr("\\"));//替换路径中的指定字符
			file_name = (file_name).replace(tr("\\\\"), tr("\\"));//根目录下由于其自带一个"\\"，会导致实际显示两个"\"，因此需要将其替换
			*file_path = file_name;
		}
		file_path_show = *file_path;
		ui.textEdit_name->setText(file_path_show);
	}

	void File::get_text_edit_file_name()//文件路径文本框信息改变时获得文件路径
	{
		*file_path = ui.textEdit_name->text();
		*file_path = (*file_path).replace(tr("/"), tr("\\"));//替换路径中的指定字符
	}

	void File::open_or_save_button()//打开或者保存按钮
	{
		*file_dialog_status = true;
		close_window_include_animation();
	}

	void File::open_or_save_branch()//分支双击
	{
		QModelIndex current_index = ui.treeView_file->currentIndex();//获取当前被选项
		if (!current_index.isValid())//不是合法路径
		{

		}
		else
		{
			if (file_tree->fileInfo(current_index).isDir())//是路径
			{

			}
			else//是文件
			{
				*file_dialog_status = true;
				close_window_include_animation();
			}
		}
	}

	void File::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

