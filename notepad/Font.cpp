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
	Font::Font(QWidget *parent) : QDialog(parent)
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
		ui.pushButton_close_dialog->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_font_exit_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_font_exit_pressed.png);}");
		ui.pushButton_accept_dialog->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_font_accept_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_font_accept_pressed.png);}");
		ui.label_sample->setStyleSheet("QLabel{border:2px solid rgb(128, 76, 71);}");

		//���������
		read_font();

		//���Ӵ�����
		connect(ui.comboBox_1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change(const QString &)));
		connect(ui.comboBox_2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change(const QString &)));
		connect(ui.comboBox_3, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change(const QString &)));
		connect(ui.comboBox_4, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change(const QString &)));

		//ȷ����ť
		connect(ui.pushButton_accept_dialog, SIGNAL(clicked()), this, SLOT(font_change()));

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
		ui.comboBox_2->setPalette(lineedit_palette);
		ui.comboBox_3->setPalette(lineedit_palette);
		ui.comboBox_4->setPalette(lineedit_palette);
		ui.label_sample->setPalette(lineedit_palette);

		//������ʽ�ļ�
		QString stylesheet_file_name = DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_STRING;
		stylesheet_file_name += QString::number(totalrandomnumber, 10);
		stylesheet_file_name += DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_BACK_STRING;
		QFile stylesheet_file_1(stylesheet_file_name);
		QFile stylesheet_file_2(stylesheet_file_name);
		QFile stylesheet_file_3(stylesheet_file_name);
		QFile stylesheet_file_4(stylesheet_file_name);
		stylesheet_file_1.open(QFile::ReadOnly);
		stylesheet_file_2.open(QFile::ReadOnly);
		stylesheet_file_3.open(QFile::ReadOnly);
		stylesheet_file_4.open(QFile::ReadOnly);
		ui.comboBox_1->setStyleSheet(stylesheet_file_1.readAll());
		ui.comboBox_2->setStyleSheet(stylesheet_file_2.readAll());
		ui.comboBox_3->setStyleSheet(stylesheet_file_3.readAll());
		ui.comboBox_4->setStyleSheet(stylesheet_file_4.readAll());
		stylesheet_file_1.close();
		stylesheet_file_2.close();
		stylesheet_file_3.close();
		stylesheet_file_4.close();

		//ȥ�������Կؼ����Ҽ��˵�
		QList<QScrollBar *> scroll_bar = this->findChildren<QScrollBar *>();//�����޷��ó��淽ʽ���combobox�Ĺ����������ʹ�ø÷�����������ͬ���Ϳؼ������в���
		foreach(QScrollBar *scroll_bar_style_control, scroll_bar)
		{
			scroll_bar_style_control->setContextMenuPolicy(Qt::NoContextMenu);
		}

		//��Ͽ���������
		ui.comboBox_3->setValidator(new QIntValidator(1, 200, this));//ֻ��������ָ����Χ������

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}

	Font::~Font()
	{

	}

	//��ʼ����
	void Font::read_font()//��ȡϵͳ�������岢������Ͽ�
	{
		QFontDatabase combobox_fontdatabase;
		foreach(const QString &font_name, combobox_fontdatabase.families())
		{
			ui.comboBox_1->addItem(font_name);
		}
	}

	//���ó�Ա����
	void Font::set_textedit(QTextEdit *main_textedit)
	{
		textedit_font = main_textedit;
	}

	void Font::set_resource_random_number(int number, int status)//��ȡ��Դ�ļ���Ҫ����ֵ����
	{
		resource_randomnumber = number;
		hex_status = status;
		ifstream setting_file;//����
		QString file_font_input = FILE_FONT_OUTPUT_FILE_PATH_FRONT_STRING;
		file_font_input += QString::number(resource_randomnumber, 10);
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_YES_FLAG)//������ģʽ��Ҫ��������������ļ�
		{
			file_font_input += FILE_FONT_OUTPUT_FILE_PATH_BINARY_EXTRA_STRING;
		}
		else
		{

		}
		file_font_input += FILE_FONT_OUTPUT_FILE_PATH_BACK_STRING;
		string file_font_input_final = string((const char *)file_font_input.toLocal8Bit());
		setting_file.open(file_font_input_final, ios_base::in);//���ļ�
		if (!setting_file.is_open())//���ļ�ʧ��
		{
			ui.comboBox_1->setCurrentText(tr("����"));
			ui.comboBox_2->setCurrentText(tr("����"));
			ui.comboBox_3->setCurrentText(tr("9"));
			ui.label_sample->setFont(QFont(tr("����"), 9, QFont::Normal, false));
			ui.label_sample->setText(tr("����������Ҫ����������"));
		}
		else//����������Ϣ
		{
			string information_font;//����
			string information_type;//����
			string information_size;//�ߴ�
			string information_throw;//��ȥ���õ��ַ���
			setting_file >> information_throw;//��ȡ�ļ����ݣ����ļ������ʱ�Դ��Ŀո���ͻس���ɸѡ�����ַ�����Ȼ����������Ҫ��
			setting_file >> information_throw;
			setting_file.get();//���ַ������ڿո��ַ���ͣ�£����޷�ɾ���ո��ַ������û����һ����������ַ�����ͷ�����һ���ո�
			getline(setting_file, information_font, '\n');
			setting_file >> information_throw;
			setting_file >> information_throw;
			setting_file.get();
			getline(setting_file, information_type, '\n');
			setting_file >> information_throw;
			setting_file >> information_throw;
			setting_file.get();
			getline(setting_file, information_size, '\n');
			setting_file.close();
			bool information_size_recieve;//ת���Ƿ�ɹ��ķ���ֵ
			int size_digit = QString(QString::fromLocal8Bit(information_size.c_str())).toInt(&information_size_recieve);//ת���ߴ�Ϊ��ֵ
			QString type_transform = QString(QString::fromLocal8Bit(information_type.c_str()));//ת���ַ�����ʽ
			if (information_size_recieve == false)//�޶�����ѡ��Χ
			{
				size_digit = 9;
			}
			else
			{
				if (size_digit < 1)
				{
					size_digit = 1;
				}
				else if (size_digit > 200)
				{
					size_digit = 200;
				}
				else
				{

				}
			}
			setting_file.close();
			QString information_font_final = QString(QString::fromLocal8Bit(information_font.c_str()));
			QString information_type_final = QString(QString::fromLocal8Bit(information_type.c_str()));
			QString information_size_final = QString(QString::fromLocal8Bit(information_size.c_str()));
			ui.comboBox_1->setCurrentText(information_font_final);
			ui.comboBox_2->setCurrentText(information_type_final);
			ui.comboBox_3->setCurrentText(information_size_final);
			QString combobox_2_text = ui.comboBox_2->currentText();
			QString sample_string;//Ҫ��ʾ����Ϣ
			bool combobox_3_recieve;//ת���Ƿ�ɹ��ķ���ֵ
			int combobox_3_digit = ui.comboBox_3->currentText().toInt(&combobox_3_recieve);
			if (combobox_3_recieve == false)//�޶�����ѡ��Χ
			{
				combobox_3_digit = 9;
			}
			else
			{
				if (combobox_3_digit < 1)
				{
					combobox_3_digit = 1;
				}
				else if (combobox_3_digit > 200)
				{
					combobox_3_digit = 200;
				}
				else
				{

				}
			}
			if (combobox_2_text == tr("����"))//��������
			{
				ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal, false));
			}
			else if (combobox_2_text == tr("����"))
			{
				ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Bold, false));
			}
			else if (combobox_2_text == tr("��б"))
			{
				ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal, true));
			}
			else if (combobox_2_text == tr("������б"))
			{
				ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Bold, true));
			}
			else
			{
				ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal));
			}
			ui.label_sample->setText(tr("����������Ҫ����������"));
		}
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void Font::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bPressed = true;
			m_point = event->pos();
		}
	}
	//�������������£����ƶ�����λ��
	void Font::mouseMoveEvent(QMouseEvent *event)
	{
		if (m_bPressed)
			move(event->pos() - m_point + pos());
	}

	//���δ�����£�����Ӧ����Ϊfalse
	void Font::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ��������������޸Ļس����Ĺ��ܣ���Ҫ����ԭ����esc���Ĺ���
	void Font::keyPressEvent(QKeyEvent *event)
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

	void Font::paintEvent(QPaintEvent *)
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
		dialog_information_path = DIALOG_INFORMATION_FONT_PICTURE_PATH_STRING;//������Ϣ
		dialog_information_path += QString::number(totalrandomnumber, 10);//�������ת��Ϊ·���е�һ����
		dialog_information_path += DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING;
		background_picture.load(filepath);
		margin_picture.load((QString)DIALOG_FONT_MARGIN_PICTURE_PATH_STRING);
		information_picture.load(dialog_information_path);
		background_painter.drawPixmap(0, 0, DIALOG_FONT_SIZE_WIDTH_NUMBER, DIALOG_FONT_SIZE_HEIGHT_NUMBER, background_picture);
		information_painter.drawPixmap(0, 0, DIALOG_FONT_SIZE_WIDTH_NUMBER, DIALOG_FONT_SIZE_HEIGHT_NUMBER, information_picture);//���ֲ���Ӧ�ô���ߵ�ͼƬ���ֵ��ұ�Ե��ʼ
		margin_painter.drawPixmap(0, 0, DIALOG_FONT_SIZE_WIDTH_NUMBER, DIALOG_FONT_SIZE_HEIGHT_NUMBER, margin_picture);//�����ʾ���ⱻͼƬ����
	}

	//��Ͽ�ѡ��
	//���¹����õ��˳�������Ҫ�޸������д
	void Font::combobox_change(const QString &)
	{
		QString combobox_2_text = ui.comboBox_2->currentText();
		QString sample_string;//Ҫ��ʾ����Ϣ
		bool combobox_3_recieve;//ת���Ƿ�ɹ��ķ���ֵ
		int combobox_3_digit = ui.comboBox_3->currentText().toInt(&combobox_3_recieve);
		if (combobox_3_recieve == false)//�޶�����ѡ��Χ
		{
			combobox_3_digit = 9;
		}
		else
		{
			if (combobox_3_digit < 1)
			{
				combobox_3_digit = 1;
				ui.comboBox_3->setCurrentText("1");
			}
			else if (combobox_3_digit > 200)
			{
				combobox_3_digit = 200;
			}
			else
			{

			}
		}
		if (ui.comboBox_4->currentText() == tr("��������"))//������������
		{
			sample_string = tr("����������Ҫ����������");
		}
		else if (ui.comboBox_4->currentText() == tr("English"))
		{
			sample_string = tr("Is the order a rabbit?");
		}
		else if (ui.comboBox_4->currentText() == tr("�ձ��Z"))
		{
			sample_string = tr("��ע�ĤϤ������Ǥ�����");
		}
		else
		{
			sample_string = tr("����������Ҫ����������");
		}
		if (combobox_2_text == tr("����"))//��������
		{
			ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal, false));
		}
		else if (combobox_2_text == tr("����"))
		{
			ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Bold, false));
		}
		else if (combobox_2_text == tr("��б"))
		{
			ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal, true));
		}
		else if (combobox_2_text == tr("������б"))
		{
			ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Bold, true));
		}
		else
		{
			ui.label_sample->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal));
		}
		ui.label_sample->setText(sample_string);
	}
	void Font::font_change()
	{
		QString combobox_2_text = ui.comboBox_2->currentText();
		QString temp_string;//��ʱ�洢Ҫ��ʾ����Ϣ
		QString sample_string;//Ҫ��ʾ����Ϣ
		bool combobox_3_recieve;//ת���Ƿ�ɹ��ķ���ֵ
		int combobox_3_digit = ui.comboBox_3->currentText().toInt(&combobox_3_recieve);
		if (combobox_3_recieve == false)//�޶�����ѡ��Χ
		{
			combobox_3_digit = 9;
		}
		else
		{
			if (combobox_3_digit < 1)
			{
				combobox_3_digit = 9;
			}
			else if (combobox_3_digit > 200)
			{
				combobox_3_digit = 9;
			}
			else
			{

			}
		}
		if (combobox_2_text == tr("����"))//��������
		{
			textedit_font->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal, false));
		}
		else if (combobox_2_text == tr("����"))
		{
			textedit_font->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Bold, false));
		}
		else if (combobox_2_text == tr("��б"))
		{
			textedit_font->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal, true));
		}
		else if (combobox_2_text == tr("������б"))
		{
			textedit_font->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Bold, true));
		}
		else
		{
			textedit_font->setFont(QFont(ui.comboBox_1->currentText(), combobox_3_digit, QFont::Normal));
		}
		ofstream setting_file;//��������ļ�
		QString file_font_output = FILE_FONT_OUTPUT_FILE_PATH_FRONT_STRING;
		file_font_output += QString::number(resource_randomnumber, 10);
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_YES_FLAG)//������ģʽ��Ҫ��������������ļ�
		{
			file_font_output += FILE_FONT_OUTPUT_FILE_PATH_BINARY_EXTRA_STRING;
		}
		else
		{

		}
		file_font_output += FILE_FONT_OUTPUT_FILE_PATH_BACK_STRING;
		string file_font_out_put_final = string((const char *)file_font_output.toLocal8Bit());
		setting_file.open(file_font_out_put_final, ios_base::out);//���ļ������������򴴽�
		if (!setting_file.is_open())//���ļ�ʧ��
		{

		}
		else//���������Ϣ
		{
			setting_file << "font = " << string((const char *)(ui.comboBox_1->currentText()).toLocal8Bit()) << "\n";
			setting_file << "type = " << string((const char *)combobox_2_text.toLocal8Bit()) << "\n";
			setting_file << "size = " << combobox_3_digit << "\n";
			setting_file.close();
		}
		close_window_include_animation();
	}

	void Font::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

