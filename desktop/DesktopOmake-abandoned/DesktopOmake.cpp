#include "define.h"

namespace rem
{

	//构造和析构函数
	DesktopOmake::DesktopOmake(QWidget *parent) : QMainWindow(parent)
	{
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏，并且任务栏中不会出现窗口
		resize(WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_TranslucentBackground, true);//使用不规则窗口，以图片透明与否来分界
		setAttribute(Qt::WA_QuitOnClose, true);//该窗口关闭时会退出程序
		setAttribute(Qt::WA_WState_WindowOpacitySet, true);//该窗口允许直接设置透明度
		is_escape_pressed = false;//默认未按下esc键以退出
		value_resize = 0;//设置初值
		value_rotate = 0;
		color.setRgb(255, 255, 255);
		background_enable = true;

		ui.setupUi(this);

		//加载背景图片
		background_picture.load(WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING);//加载背景图片
		word_picture.load(WINDOW_WORD_PICTURE_PATH_FRONT_STRING);//加载文字图片

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存

		//设置QLabel
		ui.scrollArea->setWidget(ui.label_picture);
		ui.scrollArea->viewport()->setStyleSheet("background-color:transparent;");
		ui.label_picture->setAlignment(Qt::AlignCenter);//居中显示

		//信号函数
		connect(ui.slider_resize, SIGNAL(valueChanged(int)), this, SLOT(slider_resize_change(int)));
		connect(ui.slider_rotate, SIGNAL(valueChanged(int)), this, SLOT(slider_rotate_change(int)));
		connect(ui.slider_bg_r, SIGNAL(valueChanged(int)), this, SLOT(slider_color_red_change(int)));
		connect(ui.slider_bg_g, SIGNAL(valueChanged(int)), this, SLOT(slider_color_green_change(int)));
		connect(ui.slider_bg_b, SIGNAL(valueChanged(int)), this, SLOT(slider_color_blue_change(int)));
		connect(ui.spinBox_1, SIGNAL(valueChanged(int)), this, SLOT(spinbox_1_change(int)));
		connect(ui.spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(spinbox_2_change(int)));
		connect(ui.spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(spinbox_3_change(int)));
		connect(ui.spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(spinbox_4_change(int)));
		connect(ui.spinBox_5, SIGNAL(valueChanged(int)), this, SLOT(spinbox_5_change(int)));

		//启用全局的放下操作
		this->setAcceptDrops(true);
}

	DesktopOmake::~DesktopOmake()
	{

	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标。此外，隐藏部件的处理也在此处进行
	void DesktopOmake::mousePressEvent(QMouseEvent *event)
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

	void DesktopOmake::mouseMoveEvent(QMouseEvent *event)//若鼠标左键被按下，则移动窗体位置
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}
	}

	void DesktopOmake::mouseReleaseEvent(QMouseEvent *event)//鼠标未被按下，则相应变量为false
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//拖拽事件
	void DesktopOmake::dragEnterEvent(QDragEnterEvent *event)
	{
		if (event->mimeData()->hasUrls())//防止出现拖拽文本框中的文字造成Url识别出错，然后程序崩溃
		{
			event->acceptProposedAction(); //可以在这个窗口部件上拖放对象
		}
		else
		{

		}
	}

	void DesktopOmake::dropEvent(QDropEvent *event)//释放时执行的操作
	{
		QList<QUrl> urls = event->mimeData()->urls();
		QString file_name = urls.first().toLocalFile();//获得文件名
		if (!picture_image.load(file_name))
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("有错误的说！"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//提示信息
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{
			ui.label_picture->setPixmap(QPixmap::fromImage(picture_image));
		}
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉
	void DesktopOmake::keyPressEvent(QKeyEvent *event)
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

	void DesktopOmake::paintEvent(QPaintEvent *)//绘制背景图像
	{
		QPainter background_painter(this);//背景
		background_painter.drawPixmap(0, 0, background_picture.size().width(), background_picture.size().height(), background_picture);//绘制背景图片
		if (background_enable)
		{
			background_painter.setBrush(QBrush(color, Qt::SolidPattern));//设置画刷形式 
			background_painter.drawRect(ui.label_background->x(), ui.label_background->y(), ui.label_background->width() - 1, ui.label_background->height() - 1);
		}
		else
		{

		}
		background_painter.drawPixmap(WINDOW_WORD_PICTURE_X_OFFSET_NUMBER, WINDOW_WORD_PICTURE_Y_OFFSET_NUMBER, WINDOW_WORD_PICTURE_SIZE_WIDTH_NUMBER, WINDOW_WORD_PICTURE_SIZE_HEIGHT_NUMBER, word_picture);//绘制背景图片
	}

	//其他功能
	void DesktopOmake::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

	//槽函数
	void DesktopOmake::slider_resize_change(int value)//图片尺寸改变
	{
		value_resize = (double)value / 100;
		QMatrix matrix;//用于旋转图片
		matrix.rotate(value_rotate);
		temp_image = picture_image.scaled(picture_image.width()*value_resize, picture_image.height()*value_resize, Qt::KeepAspectRatio);
		temp_image = temp_image.transformed(matrix);
		ui.label_picture->setPixmap(QPixmap::fromImage(temp_image));
		disconnect(ui.spinBox_1, SIGNAL(valueChanged(int)), this, SLOT(spinbox_1_change(int)));
		ui.spinBox_1->setValue(value);
		connect(ui.spinBox_1, SIGNAL(valueChanged(int)), this, SLOT(spinbox_1_change(int)));
	}

	void DesktopOmake::slider_rotate_change(int value)//图片角度改变
	{
		value_rotate = value;
		QMatrix matrix;//用于旋转图片
		matrix.rotate(value_rotate);
		temp_image = picture_image.scaled(picture_image.width()*value_resize, picture_image.height()*value_resize, Qt::KeepAspectRatio, Qt::FastTransformation);
		temp_image = temp_image.transformed(matrix);
		ui.label_picture->setPixmap(QPixmap::fromImage(temp_image));
		disconnect(ui.spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(spinbox_2_change(int)));
		ui.spinBox_2->setValue(value);
		connect(ui.spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(spinbox_2_change(int)));
	}

	void DesktopOmake::slider_color_red_change(int value)//图片颜色分量（红）改变
	{
		color.setRed(value);
		repaint();
		disconnect(ui.spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(spinbox_3_change(int)));
		ui.spinBox_3->setValue(value);
		connect(ui.spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(spinbox_3_change(int)));
	}

	void DesktopOmake::slider_color_green_change(int value)//图片颜色分量（绿）改变
	{
		color.setGreen(value);
		repaint();
		disconnect(ui.spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(spinbox_4_change(int)));
		ui.spinBox_4->setValue(value);
		connect(ui.spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(spinbox_4_change(int)));
	}

	void DesktopOmake::slider_color_blue_change(int value)//图片颜色分量（蓝）改变
	{
		color.setBlue(value);
		repaint();
		disconnect(ui.spinBox_5, SIGNAL(valueChanged(int)), this, SLOT(spinbox_5_change(int)));
		ui.spinBox_5->setValue(value);
		connect(ui.spinBox_5, SIGNAL(valueChanged(int)), this, SLOT(spinbox_5_change(int)));
	}

	void DesktopOmake::spinbox_1_change(int value)//spinbox改变
	{
		value_resize = (double)value / 100;
		QMatrix matrix;//用于旋转图片
		matrix.rotate(value_rotate);
		temp_image = picture_image.scaled(picture_image.width()*value_resize, picture_image.height()*value_resize, Qt::KeepAspectRatio, Qt::FastTransformation);
		temp_image = temp_image.transformed(matrix);
		ui.label_picture->setPixmap(QPixmap::fromImage(temp_image));
		disconnect(ui.slider_resize, SIGNAL(valueChanged(int)), this, SLOT(slider_resize_change(int)));
		ui.slider_resize->setValue(value);
		connect(ui.slider_resize, SIGNAL(valueChanged(int)), this, SLOT(slider_resize_change(int)));
	}

	void DesktopOmake::spinbox_2_change(int value)//spinbox改变
	{
		value_rotate = value;
		QMatrix matrix;//用于旋转图片
		matrix.rotate(value_rotate);
		temp_image = picture_image.scaled(picture_image.width()*value_resize, picture_image.height()*value_resize, Qt::KeepAspectRatio);
		temp_image = temp_image.transformed(matrix);
		ui.label_picture->setPixmap(QPixmap::fromImage(temp_image));
		disconnect(ui.slider_rotate, SIGNAL(valueChanged(int)), this, SLOT(slider_rotate_change(int)));
		ui.slider_rotate->setValue(value);
		connect(ui.slider_rotate, SIGNAL(valueChanged(int)), this, SLOT(slider_rotate_change(int)));
	}

	void DesktopOmake::spinbox_3_change(int value)//spinbox改变
	{
		color.setRed(value);
		repaint();
		disconnect(ui.slider_bg_r, SIGNAL(valueChanged(int)), this, SLOT(slider_color_red_change(int)));
		ui.slider_bg_r->setValue(value);
		connect(ui.slider_bg_r, SIGNAL(valueChanged(int)), this, SLOT(slider_color_red_change(int)));
	}

	void DesktopOmake::spinbox_4_change(int value)//spinbox改变
	{
		color.setGreen(value);
		repaint();
		disconnect(ui.slider_bg_g, SIGNAL(valueChanged(int)), this, SLOT(slider_color_green_change(int)));
		ui.slider_bg_g->setValue(value);
		connect(ui.slider_bg_g, SIGNAL(valueChanged(int)), this, SLOT(slider_color_green_change(int)));
	}

	void DesktopOmake::spinbox_5_change(int value)//spinbox改变
	{
		color.setBlue(value);
		repaint();
		disconnect(ui.slider_bg_b, SIGNAL(valueChanged(int)), this, SLOT(slider_color_blue_change(int)));
		ui.slider_bg_b->setValue(value);
		connect(ui.slider_bg_b, SIGNAL(valueChanged(int)), this, SLOT(slider_color_blue_change(int)));
	}
}

