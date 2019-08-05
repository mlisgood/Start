#include "define.h"

namespace rem
{

	//全局变量声明
	extern int find_dialog_mutex;//只允许创建1个查找窗口

	//构造与析构函数
	Find::Find(QWidget *parent) : QDialog(parent)
	{
		
		//常规初始化
		//以下功能用到了常量，如要修改最好重写
		find_dialog_mutex--;//允许的窗口数目减少1
		totalrandomnumber = DIALOG_RANDOM_MIN_NUMBER + rand() % (DIALOG_RANDOM_MAX_NUMBER - DIALOG_RANDOM_MIN_NUMBER + 1);//产生指定随机数以便决定背景图片和人物图片样式
		setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);//去掉窗口标题栏并且窗口可以通过点击任务栏放大缩小
		resize(DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER);//将窗口强制改为此大小
		setFixedSize(this->width(), this->height());//禁止改变窗口大小
		setAttribute(Qt::WA_QuitOnClose, false);//该窗口关闭时不会退出程序
		is_escape_pressed = false;//允许按下esc键退出程序

		//图片路径
		//背景图片路径
		filepath = DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING + QString::number(totalrandomnumber, 10);
		filepath += DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING;

		//左侧图片路径
		chara_path = DIALOG_CHARA_PICTURE_PATH_FRONT_STRING;
		QString chara_path_number = QString::number(totalrandomnumber, 10);//将随机数转化为路径中的一部分
		chara_path += chara_path_number;
		chara_path += DIALOG_CHARA_PICTURE_PATH_BREAK_STRING;
		chara_path += QString::number(DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER + rand() % (DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER - DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER + 1), 10);//从当前系列的3张图片当中选取一张并增加到路径中
		chara_path += DIALOG_CHARA_PICTURE_PATH_BACK_STRING;

		//加载界面，必须放在最后以避免界面被之后的绘图覆盖
		ui.setupUi(this);

		//加载按钮样式
		ui.pushButton_next->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_next_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_next_pressed.png);}");
		ui.pushButton_exit->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_exit_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_exit_pressed.png);}");
		ui.pushButton_last->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_last_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_last_pressed.png);}");
	
		//去除文本框背景
		ui.lineEdit_main->setStyleSheet("background-color: rgb(255, 255, 255, 0);border:0px solid #e1e0e0;");
	
		//查找
		connect(ui.pushButton_last, SIGNAL(clicked()), this, SLOT(find_text_last()));
		connect(ui.pushButton_next, SIGNAL(clicked()), this, SLOT(find_text_next()));

		//关闭按钮
		connect(ui.pushButton_close_window, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));
		connect(ui.pushButton_exit, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));

		//设置查找框文字颜色
		QPalette lineedit_palette;
		if (totalrandomnumber == 1)//决定相关文字颜色
		{
			lineedit_palette.setColor(QPalette::Text, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(255, 83, 185, 64));
		}
		else if (totalrandomnumber == 2)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(133, 153, 212, 64));
		}
		else if (totalrandomnumber == 3)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(222, 63, 235, 64));
		}
		else if (totalrandomnumber == 4)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(242, 153, 93, 64));
		}
		else if (totalrandomnumber == 5)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(71, 185, 78, 64));
		}
		else
		{

		}
		ui.lineEdit_main->setPalette(lineedit_palette);

		//退出时销毁该窗口以免内存泄漏
		setAttribute(Qt::WA_DeleteOnClose);

		//窗口启动动画效果。窗口显示类，要先显示才能看到动画；反之，窗口关闭类，要先显示才能关闭，否则看不到动画
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//结束时释放内存
	}
	Find::~Find()
	{
		find_dialog_mutex++;//允许的窗口数目增加1
	}

	//设置成员变量
	void Find::set_dialog_information_path(QString information_path)
	{
		dialog_information_path = information_path;
	}

	void Find::set_textedit(QTextEdit *main_textedit)
	{
		textedit_find = main_textedit;
	}

	//以下为鼠标事件，可以实现去掉标题栏后窗口的移动
	//当鼠标左键被按下时，设置相应变量为true，并得到当前点坐标
	void Find::mousePressEvent(QMouseEvent *event)
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
	void Find::mouseMoveEvent(QMouseEvent *event)
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
	void Find::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//键盘事件，由于是重写，会把原来所有的键盘响应都覆盖掉，因此这里除了修改回车键的功能，还要加上原来的esc键的功能
	void Find::keyPressEvent(QKeyEvent *event)
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

	void Find::paintEvent(QPaintEvent *)
	{

		//绘制窗口用到的图片。具体方法：首先指派5种背景风格。之后从5组随机数中选取一个，映射到其中一种风格上面。以下是对应的映射关系：[1,5]->ココア，[6,10]->チノ，[11,15]->リゼ，[16,20]->シャロ,[21,25]->千夜。此外，之后的其他图片也和构建背景使用的随机数有关。每个背景对应3张图片，每次随机选取1张。
		//以下功能用到了常量，如要修改最好重写
		//绘制图片
		QString dialog_information_path_temp;//临时存储信息图片路径
		QPainter background_painter(this);//背景
		QPainter margin_painter(this);//边框
		QPainter chara_painter(this);//人物
		QPainter information_painter(this);//文字
		QPixmap background_picture;
		QPixmap margin_picture;
		QPixmap chara_picture;
		QPixmap information_picture;
		dialog_information_path_temp = dialog_information_path;//因为该事件会执行多次，所以不能直接使用dialog_information_path，会造成每次字符串的累加导致路径错误
		dialog_information_path_temp += QString::number(totalrandomnumber, 10);//将随机数转化为路径中的一部分
		dialog_information_path_temp += DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING;
		background_picture.load(filepath);
		margin_picture.load((QString)DIALOG_MARGIN_PICTURE_PATH_STRING);
		chara_picture.load(chara_path);
		information_picture.load(dialog_information_path_temp);
		background_painter.drawPixmap(0, 0, DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, background_picture);
		chara_painter.drawPixmap(0, 0, DIALOG_SIZE_HEIGHT_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, chara_picture);//左侧图片使用正方形，长和宽与窗口宽度一致
		information_painter.drawPixmap(DIALOG_INFORMATION_FIND_X_OFFSET_NUMBER, DIALOG_INFORMATION_FIND_Y_OFFSET_NUMBER, DIALOG_INFORMATION_FIND_WIDTH_NUMBER, DIALOG_INFORMATION_FIND_HEIGHT_NUMBER, information_picture);//指定文字部分的位置并绘图
		margin_painter.drawPixmap(0, 0, DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, margin_picture);//最后显示以免被图片覆盖
	}

	void Find::find_text_last()//向前查找文本
	{
		QString find_text = ui.lineEdit_main->text();//需要查找的文本
		bool is_success;//判断是否查找成功
		//枚举情况并分别处理

		if (ui.checkBox_1->isChecked() == false && ui.checkBox_2->isChecked() == false)//默认
		{
			is_success = textedit_find->find(find_text, QTextDocument::FindBackward);
		}
		else if (ui.checkBox_1->isChecked() == true && ui.checkBox_2->isChecked() == false)//区分大小写
		{
			is_success = textedit_find->find(find_text, QTextDocument::FindBackward | QTextDocument::FindCaseSensitively);
		}
		else if (ui.checkBox_1->isChecked() == false && ui.checkBox_2->isChecked() == true)//全词匹配
		{
			is_success = textedit_find->find(find_text, QTextDocument::FindBackward | QTextDocument::FindWholeWords);
		}
		else if (ui.checkBox_1->isChecked() == true && ui.checkBox_2->isChecked() == true)//区分大小写且全词匹配
		{
			is_success = textedit_find->find(find_text, QTextDocument::FindBackward | QTextDocument::FindCaseSensitively | QTextDocument::FindWholeWords);
		}
		else
		{
			is_success = false;
		}
		if (!is_success)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("找不到哦……"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_FIND_PICTURE_PATH_STRING);
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void Find::find_text_next()//向后查找文本
	{
		QString find_text = ui.lineEdit_main->text();//需要查找的文本
		bool is_success;//判断是否查找成功

		//枚举情况并分别处理
		if (ui.checkBox_1->isChecked() == false && ui.checkBox_2->isChecked() == false)//默认
		{
			is_success = textedit_find->find(find_text);
		}
		else if (ui.checkBox_1->isChecked() == true && ui.checkBox_2->isChecked() == false)//区分大小写
		{
			is_success = textedit_find->find(find_text, QTextDocument::FindCaseSensitively);
		}
		else if (ui.checkBox_1->isChecked() == false && ui.checkBox_2->isChecked() == true)//全词匹配
		{
			is_success = textedit_find->find(find_text, QTextDocument::FindWholeWords);
		}
		else if (ui.checkBox_1->isChecked() == true && ui.checkBox_2->isChecked() == true)//区分大小写且全词匹配
		{
			is_success = textedit_find->find(find_text, QTextDocument::FindCaseSensitively | QTextDocument::FindWholeWords);
		}
		else
		{
			is_success = false;
		}
		if (!is_success)
		{
			Help dialog;//信息提示框
			dialog.setWindowTitle(tr("找不到哦……"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_FIND_PICTURE_PATH_STRING);
			dialog.exec();//如果不加这一句，对话框在创建后会被立即析构
		}
		else
		{

		}
	}

	void Find::close_window_include_animation()//包含关闭窗口动画的关闭窗口方法
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

