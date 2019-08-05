#include "define.h"

namespace rem
{

	//ʹ�ñ�׼�����ռ�
	using std::string;
	using std::ifstream;
	using std::ofstream;
	using std::fstream;
	using std::ios_base;

	//��������������
	Setting::Setting(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		totalrandomnumber = DIALOG_RANDOM_MIN_NUMBER + rand() % (DIALOG_RANDOM_MAX_NUMBER - DIALOG_RANDOM_MIN_NUMBER + 1);//����ָ��������Ա��������ͼƬ������ͼƬ��ʽ
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		resize(DIALOG_FONT_SIZE_WIDTH_NUMBER, DIALOG_FONT_SIZE_HEIGHT_NUMBER);//������ǿ�Ƹ�Ϊ�˴�С
		setFixedSize(this->width(), this->height());//��ֹ�ı䴰�ڴ�С
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		is_escape_pressed = false;//������esc���˳�����

		//ͼƬ·��
		//����ͼƬ·��
		filepath = DIALOG_FONT_BACKGROUND_PICTURE_PATH_FRONT_STRING + QString::number(totalrandomnumber, 10);
		filepath += DIALOG_FONT_BACKGROUND_PICTURE_PATH_BACK_STRING;

		//���ؽ��棬�����������Ա�����汻֮��Ļ�ͼ����
		ui.setupUi(this);

		//���ذ�ť����ʾ����ʽ
		ui.pushButton_close_dialog->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_pressed.png);}");
		ui.pushButton_accept_dialog->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_pressed.png);}");

		//�б������ť
		connect(ui.pushButton_list_1, SIGNAL(clicked()), this, SLOT(list_1_button()));
		connect(ui.pushButton_list_2, SIGNAL(clicked()), this, SLOT(list_2_button()));
		connect(ui.pushButton_list_3, SIGNAL(clicked()), this, SLOT(list_3_button()));
		connect(ui.pushButton_list_4, SIGNAL(clicked()), this, SLOT(list_4_button()));
		connect(ui.pushButton_list_5, SIGNAL(clicked()), this, SLOT(list_5_button()));
		connect(ui.pushButton_list_6, SIGNAL(clicked()), this, SLOT(list_6_button()));

		//ȷ����ť
		connect(ui.pushButton_accept_dialog, SIGNAL(clicked()), this, SLOT(accept_button()));

		//�رհ�ť
		connect(ui.pushButton_close_window, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));
		connect(ui.pushButton_close_dialog, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));

		//����������ɫ
		QPalette lineedit_palette;
		if (totalrandomnumber == 1)//�������������ɫ
		{
			lineedit_palette.setColor(QPalette::Text, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(255, 83, 185, 64));
		}
		else if (totalrandomnumber == 2)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(133, 153, 212, 64));
		}
		else if (totalrandomnumber == 3)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(222, 63, 235, 64));
		}
		else if (totalrandomnumber == 4)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(242, 153, 93, 64));
		}
		else if (totalrandomnumber == 5)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(71, 185, 78, 64));
		}
		else
		{

		}
		ui.comboBox_1->setPalette(lineedit_palette);
		ui.spinBox_1->setPalette(lineedit_palette);
		ui.spinBox_2->setPalette(lineedit_palette);
		ui.listWidget_1->setPalette(lineedit_palette);
		ui.listWidget_2->setPalette(lineedit_palette);
		ui.lineEdit_1->setPalette(lineedit_palette);
		ui.lineEdit_2->setPalette(lineedit_palette);

		//������ʽ�ļ�
		QString stylesheet_file_name = DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_STRING;
		stylesheet_file_name += QString::number(totalrandomnumber, 10);
		stylesheet_file_name += DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_BACK_STRING;
		QFile stylesheet_file(stylesheet_file_name);
		stylesheet_file.open(QFile::ReadOnly);
		ui.comboBox_1->setStyleSheet(stylesheet_file.readAll());
		stylesheet_file.close();

		//ȥ�������Կؼ����Ҽ��˵�
		QList<QScrollBar *> scroll_bar = this->findChildren<QScrollBar *>();//�����޷��ó��淽ʽ���combobox�Ĺ����������ʹ�ø÷�����������ͬ���Ϳؼ������в���
		foreach(QScrollBar *scroll_bar_style_control, scroll_bar)
		{
			scroll_bar_style_control->setContextMenuPolicy(Qt::NoContextMenu);
		}

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�

		//���ÿؼ�����
		extern QString font_str;//��ΪlistWidget_1�ڲ��Ŀؼ������޷�ʹ��Ĭ���������ã���˱��뵥�����á�ע����Ϊû�������ռ�Ĺ�ϵ�������main�������涨���ȫ�ֱ������ܺ�find_dialog_mutexһ����������ж��壬����ᱻ����һ���¶����ȫ�ֱ���rem::font_str
		if (font_str != "")
		{
			QFont file_font(font_str, FILE_FONT_DEFAULT_SIZE);//����Ĭ������
			ui.listWidget_1->setFont(file_font);
			ui.listWidget_2->setFont(file_font);
		}
		else//����ʧ�ܣ�ʹ������趨�õ�Ĭ������
		{

		}
	}

	Setting::~Setting()
	{

	}

	//���ó�Ա����
	void Setting::set_textedit(QTextEdit *main_textedit)
	{
		textedit_main = main_textedit;
	}

	void Setting::set_setting_text_address(QStringList *main_list)//��ȡ�������ַ�����1��ַ
	{
		setting_text_address = main_list;
		ui.listWidget_1->addItems(*setting_text_address);//�����ʼ�����ܷ��ڹ��캯�����棬������Ϊ���캯����ִ�У��ȵ���ʼ����ϣ����ܽ��յ������洫����ֵ������ǰ��ʼ���Ѿ���ϣ�ָ�������Ϊָ���˿յ�ַ����������
	}

	void Setting::set_setting_binary_address(QStringList *main_list)//��ȡ�������ַ�����2��ַ
	{
		setting_binary_address = main_list;
		ui.listWidget_2->addItems(*setting_binary_address);
	}

	void Setting::set_setting_default_open_method_address(QString *main_string)//��ȡ�������ַ�����ַ
	{
		setting_default_open_method_address = main_string;
		if (*setting_default_open_method_address == tr("�ı���ʽ"))
		{
			ui.comboBox_1->setCurrentText(tr("�ı���ʽ"));
		}
		else if (*setting_default_open_method_address == tr("�����Ʒ�ʽ"))
		{
			ui.comboBox_1->setCurrentText(tr("�����Ʒ�ʽ"));
		}
		else
		{
			ui.comboBox_1->setCurrentText(tr("�ı���ʽ"));
		}
	}

	void Setting::set_setting_bool_value_address(bool *main_array_index, int index)//��ȡ������bool��������Ԫ�ص�ַ
	{
		setting_bool_value_address[index] = main_array_index;
		if (index == 0)//����ֿ��жϣ������п��ܶ����յ�ַ
		{
			if (*setting_bool_value_address[0] == true)
			{
				ui.checkBox_1->setCheckState(Qt::Checked);
			}
			else
			{
				ui.checkBox_1->setCheckState(Qt::Unchecked);
			}
		}
		else if (index == 1)
		{
			if (*setting_bool_value_address[1] == true)
			{
				ui.checkBox_2->setCheckState(Qt::Checked);
			}
			else
			{
				ui.checkBox_2->setCheckState(Qt::Unchecked);
			}
		}
		else if (index == 2)
		{
			if (*setting_bool_value_address[2] == true)
			{
				ui.checkBox_3->setCheckState(Qt::Checked);
			}
			else
			{
				ui.checkBox_3->setCheckState(Qt::Unchecked);
			}
		}
		else
		{

		}
	}

	void Setting::set_setting_size_address(int *main_array_index, int index)//��ȡ������int��������Ԫ�ص�ַ
	{
		setting_size_address[index] = main_array_index;
		if (index == 0)
		{
			ui.spinBox_1->setValue(*setting_size_address[index]);
		}
		else if (index == 1)
		{
			ui.spinBox_2->setValue(*setting_size_address[index]);
		}
		else
		{

		}
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void Setting::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bPressed = true;
			m_point = event->pos();
		}
	}
	//�������������£����ƶ�����λ��
	void Setting::mouseMoveEvent(QMouseEvent *event)
	{
		if (m_bPressed)
			move(event->pos() - m_point + pos());
	}

	//���δ�����£�����Ӧ����Ϊfalse
	void Setting::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ��������������޸Ļس����Ĺ��ܣ���Ҫ����ԭ����esc���Ĺ���
	void Setting::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Enter)
		{

		}
		else if (event->key() == Qt::Key_Escape)
		{
			if (!is_escape_pressed)//��ִ��һ�ΰ���esc�˳�
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

	void Setting::paintEvent(QPaintEvent *)
	{

		//���ƴ����õ���ͼƬ�����巽��������ָ��5�ֱ������֮���5���������ѡȡһ����ӳ�䵽����һ�ַ�����档�����Ƕ�Ӧ��ӳ���ϵ��[1,5]->��������[6,10]->���Σ�[11,15]->�ꥼ��[16,20]->�����,[21,25]->ǧҹ�����⣬֮�������ͼƬҲ�͹�������ʹ�õ�������йء�ÿ��������Ӧ3��ͼƬ��ÿ�����ѡȡ1�š�
		//���¹����õ��˳�������Ҫ�޸������д
		//����ͼƬ
		QPainter background_painter(this);//����
		QPainter margin_painter(this);//�߿�
		QPainter information_painter(this);//����
		QPixmap background_picture;
		QPixmap margin_picture;
		QPixmap information_picture;
		dialog_information_path = DIALOG_INFORMATION_SETTING_PICTURE_PATH_STRING;//������Ϣ
		dialog_information_path += QString::number(totalrandomnumber, 10);//�������ת��Ϊ·���е�һ����
		dialog_information_path += DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING;
		background_picture.load(filepath);
		margin_picture.load((QString)DIALOG_FONT_MARGIN_PICTURE_PATH_STRING);
		information_picture.load(dialog_information_path);
		background_painter.drawPixmap(0, 0, DIALOG_FONT_SIZE_WIDTH_NUMBER, DIALOG_FONT_SIZE_HEIGHT_NUMBER, background_picture);
		information_painter.drawPixmap(0, 0, DIALOG_FONT_SIZE_WIDTH_NUMBER, DIALOG_FONT_SIZE_HEIGHT_NUMBER, information_picture);//���ֲ���Ӧ�ô���ߵ�ͼƬ���ֵ��ұ�Ե��ʼ
		margin_painter.drawPixmap(0, 0, DIALOG_FONT_SIZE_WIDTH_NUMBER, DIALOG_FONT_SIZE_HEIGHT_NUMBER, margin_picture);//�����ʾ���ⱻͼƬ����
	}

	//�ۺ���
	//�б�ť����
	void Setting::list_1_button()//���
	{
		if (ui.lineEdit_1->text() != "")
		{
			ui.listWidget_1->addItem(ui.lineEdit_1->text());
		}
		else
		{

		}
	}

	void Setting::list_2_button()//ɾ��һ��
	{
		if (ui.listWidget_1->currentItem() != Q_NULLPTR)
		{
			QListWidgetItem *item = ui.listWidget_1->takeItem(ui.listWidget_1->currentRow());
			delete item;
		}
	}

	void Setting::list_3_button()//ɾ��ȫ��
	{
		int temp_count = ui.listWidget_1->count();//�����ʼʱ�����ֵ������һ������������ֱ�ӷŽ�ѭ����Ϊ�ж���������Ϊ��ѭ��������ÿ��ѭ����ʹ�����1
		for (int temp = 0; temp < temp_count; temp++)
		{
			QListWidgetItem *item = ui.listWidget_1->takeItem(0);//ע����ÿ��ɾ��������һ���Ϊÿɾ��һ���������Զ��Ƶ�����
			delete item;
		}
	}

	void Setting::list_4_button()//���
	{
		if (ui.lineEdit_2->text() != "")
		{
			ui.listWidget_2->addItem(ui.lineEdit_2->text());
		}
		else
		{

		}
	}

	void Setting::list_5_button()//ɾ��һ��
	{
		if (ui.listWidget_2->currentItem() != Q_NULLPTR)
		{
			QListWidgetItem *item = ui.listWidget_2->takeItem(ui.listWidget_2->currentRow());
			delete item;
		}
	}

	void Setting::list_6_button()//ɾ��ȫ��
	{
		int temp_count = ui.listWidget_2->count();
		for (int temp = 0; temp < temp_count; temp++)
		{
			QListWidgetItem *item = ui.listWidget_2->takeItem(0);
			delete item;
		}
	}

	void Setting::accept_button()//ȷ�ϲ���
	{
		*setting_default_open_method_address = ui.comboBox_1->currentText();//��ֵ��������
		*setting_size_address[0] = ui.spinBox_1->value();
		*setting_size_address[1] = ui.spinBox_2->value();
		if (ui.checkBox_1->isChecked())
		{
			*setting_bool_value_address[0] = true;
			textedit_main->setLineWrapMode(QTextEdit::WidgetWidth);//�����ڴ��ڲ����ĵ�ǰ����Զ�����
		}
		else
		{
			*setting_bool_value_address[0] = false;
			textedit_main->setLineWrapMode(QTextEdit::NoWrap);//��ֹ�Զ�����
		}
		if (ui.checkBox_2->isChecked())
		{
			*setting_bool_value_address[1] = true;
		}
		else
		{
			*setting_bool_value_address[1] = false;
		}
		if (ui.checkBox_3->isChecked())
		{
			*setting_bool_value_address[2] = true;
		}
		else
		{
			*setting_bool_value_address[2] = false;
		}
		(*setting_text_address).clear();//����ַ����б�
		(*setting_binary_address).clear();
		for (int temp = 0; temp < ui.listWidget_1->count(); temp++)
		{
			*setting_text_address << ui.listWidget_1->item(temp)->text();
		}
		for (int temp = 0; temp < ui.listWidget_2->count(); temp++)
		{
			*setting_binary_address << ui.listWidget_2->item(temp)->text();
		}
		ofstream setting_text_file;//����ļ�
		ofstream setting_binary_file;
		setting_text_file.open(FILE_SETTING_TEXT_OUTPUT_FILE_PATH_STRING, ios_base::out);//���ļ������������򴴽�
		setting_binary_file.open(FILE_SETTING_BINARY_OUTPUT_FILE_PATH_STRING, ios_base::out);
		if (!setting_text_file.is_open())//���ļ�ʧ��
		{

		}
		else//���������Ϣ
		{
			for (int temp = 0; temp < (*setting_text_address).count(); temp++)
			{
				setting_text_file << string((const char *)((*setting_text_address).at(temp)).toLocal8Bit());
				setting_text_file << " ";//��Ҫ����ո���Ϊ�ָ���
			}
			setting_text_file << FILE_SETTING_TEXT_AND_BINARY_END_WRITE_STRING;
			setting_text_file.close();
		}
		if (!setting_binary_file.is_open())//���ļ�ʧ��
		{

		}
		else//���������Ϣ
		{
			for (int temp = 0; temp < (*setting_binary_address).count(); temp++)
			{
				setting_binary_file << string((const char *)((*setting_binary_address).at(temp)).toLocal8Bit());
				setting_binary_file << " ";//��Ҫ����ո���Ϊ�ָ���
			}
			setting_binary_file << FILE_SETTING_TEXT_AND_BINARY_END_WRITE_STRING;
			setting_binary_file.close();
		}
		//д��ini�ļ�
		QSettings *setting_other = new QSettings(FILE_SETTING_OTHER_PATH_STRING, QSettings::IniFormat);
		setting_other->setValue(FILE_SETTING_CATALOG_1_INNER_PATH_STRING, *setting_default_open_method_address);
		setting_other->setValue(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING, QString::number(*setting_size_address[0], 10));
		setting_other->setValue(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING, QString::number(*setting_size_address[1], 10));
		setting_other->setValue(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING, QString::number(*setting_bool_value_address[0], 10));
		setting_other->setValue(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING, QString::number(*setting_bool_value_address[1], 10));
		setting_other->setValue(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING, QString::number(*setting_bool_value_address[2], 10));
		delete setting_other;

		//д��ע���
		QSettings *regedit_settings_1 = new QSettings(REG_MENU_1, QSettings::NativeFormat);
		QSettings *regedit_settings_2 = new QSettings(REG_MENU_2, QSettings::NativeFormat);
		if (*setting_bool_value_address[1] == true)//�Ƿ�����Ҽ��˵��������õ��˴��������������޸ģ����޸Ĵ˴�
		{
			QString reg_path = "\"" + QApplication::applicationFilePath();//��þ���·����ע��applicationDirPathֻ��ȡ·����applicationFilePath������������ļ���
			reg_path += "\" \"%1\"";
			regedit_settings_1->setValue(".", reg_path.replace("/", "\\"));//д��ע����ע��ע���ʹ�õ�·���ָ�����QT������෴��Ĭ��ֵ��һ�����ʾ
			regedit_settings_2->setValue(".", REG_MENU_NAME_PATH_STRING);
			reg_path = QApplication::applicationDirPath() + REG_MENU_ICON_PATH_STRING;
			regedit_settings_2->setValue(tr("icon"), reg_path.replace("/", "\\"));
			delete regedit_settings_1;
			delete regedit_settings_2;
		}
		else
		{
			regedit_settings_1->clear();//���ע�����
			regedit_settings_2->clear();
			delete regedit_settings_1;
			delete regedit_settings_2;
		}

		close_window_include_animation();
	}

	void Setting::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
	{

		//�������а�ť�����򶯻��������ǰ�ٴε����ť�����´�������
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(false);
		}
		QPropertyAnimation *animation_close = new QPropertyAnimation(this, "windowOpacity");
		animation_close->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//���ڹرն���Ч��
		animation_close->setStartValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation_close->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_close->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		connect(animation_close, SIGNAL(finished()), this, SLOT(close()));
	}
}

