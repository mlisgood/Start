#include "define.h"

namespace rem
{

	//ȫ�ֱ�������
	extern int find_dialog_mutex = 1;//ֻ������1�����Ҵ��ڡ�ע��ʹ��ȫ�ֱ���ʱ���������������Ƕ��嶼����Ҫ��ͷ�ļ��У�������Ҫ��extern��ȫ�ֱ���ֻ�ܶ���1�Σ�Ҳ���Ǹ���ֵ1�Σ�����Ҫ�õ�����ļ��о���������

	//ʹ�ñ�׼�����ռ�
	using std::string;
	using std::ifstream;
	using std::ofstream;
	using std::fstream;
	using std::ios_base;

	//��������������
	Notepad::Notepad(QWidget *parent) : QMainWindow(parent)
	{

		//�����ʼ��
		//���¹����õ��˳�������Ҫ�޸������д
		randnumber = WINDOW_RANDOM_MIN_NUMBER + rand() % (WINDOW_RANDOM_MAX_NUMBER - WINDOW_RANDOM_MIN_NUMBER + 1);//����ָ������������ڹ��캯����ʹ��һ�Σ��Ա�֤����������ز��򿪴��ں󱳾���Ϊ���»�ͼ�����仯������
		setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);//ȥ�����ڱ��������Ҵ��ڿ���ͨ������������Ŵ���С
		resize(WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_HEIGHT_NUMBER);//������ǿ�Ƹ�Ϊ�˴�С
		setFixedSize(this->width(), this->height());//��ֹ�ı䴰�ڴ�С
		setAttribute(Qt::WA_QuitOnClose, true);//�ô���Ϊ�����ڣ��ر�ʱֱ���˳�����
		hex_status = WINDOW_TOOL_TOHEX_STATUS_NO_FLAG;//Ĭ�ϲ���ʮ������ģʽ
		if (randnumber >= 1 && randnumber <= 5)//��������ͼ���Լ����������ɫ
		{
			chara_randnumber = 1 + rand() % (5 - 1 + 1);
			font_randnumber = 1;
		}
		else if (randnumber >= 6 && randnumber <= 10)
		{
			chara_randnumber = 6 + rand() % (10 - 6 + 1);
			font_randnumber = 2;
		}
		else if (randnumber >= 11 && randnumber <= 15)
		{
			chara_randnumber = 11 + rand() % (15 - 11 + 1);
			font_randnumber = 3;
		}
		else if (randnumber >= 16 && randnumber <= 20)
		{
			chara_randnumber = 16 + rand() % (20 - 16 + 1);
			font_randnumber = 4;
		}
		else if (randnumber >= 21 && randnumber <= 25)
		{
			chara_randnumber = 21 + rand() % (25 - 21 + 1);
			font_randnumber = 5;
		}
		else
		{

		}

		//��ʼ����ʱ��
		chara_picture_timer = new QTimer(this);//����һ����ʱ��
		chara_picture_timer->setTimerType(Qt::PreciseTimer);//�޸ľ���
		connect(chara_picture_timer, SIGNAL(timeout()), this, SLOT(timer_chara_picture_timeout()));//��ʱ�����ڴ���
		timer_interval_number = WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER + rand() % (WINDOW_RANDOM_TIMER_CHARA_NORMAL_MAX_NUMBER - WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER + 1);//��ʼ����ʱ�����ȡֵ��֮ǰѡȡ�����䵱��
		timer_chara_status = WINDOW_CHARA_NORMAL_FLAG;//��ʼ��״̬Ϊ����״̬
		timer_chara_status_address = &timer_chara_status;//���ü�ʱ��״̬��ַ
		chara_picture_timer->start(timer_interval_number);//��ʼ����ʱ��

		//��ʼ������ͼ��
		//���¹����õ��˳�������Ҫ�޸������д
		chara_path_normal = WINDOW_CHARA_PICTURE_PATH_FRONT_STRING;//�������󳣹�״̬
		chara_path_normal += QString::number(chara_randnumber, 10);//�������ת��Ϊ·���е�һ����
		chara_path_normal += WINDOW_CHARA_PICTURE_PATH_BREAK_STRING;
		chara_path_close_eye = chara_path_normal;//��Ҫ�л���ͼƬ�������۾����ϵ�״̬��ǰ�벿��·���ͳ���״̬��һ��
		chara_path_normal += tr("01");
		chara_path_close_eye += tr("02");
		chara_path_normal += WINDOW_CHARA_PICTURE_PATH_BACK_STRING;
		chara_path_close_eye += WINDOW_CHARA_PICTURE_PATH_BACK_STRING;
		chara_picture_label = new QLabel(this);//���������������߽��Ȼ��ƣ�������Ḳ�����߽�
		margin_picture_label = new QLabel(this);
		chara_picture_label->setGeometry(0, 0, WINDOW_SIZE_PICTURE_CHARA_WIDTH_NUMBER, WINDOW_SIZE_PICTURE_CHARA_HEIGHT_NUMBER);//����label�ı߽�
		margin_picture_label->setGeometry(0, 0, WINDOW_SIZE_MARGIN_PICTURE_LEFT_WIDTH_NUMBER, WINDOW_SIZE_MARGIN_PICTURE_LEFT_HEIGHT_NUMBER);
		chara_picture.load(chara_path_normal);//��������ͼƬ�������ȼ��أ�֮��ÿ��ʹ�ö������¼��صķ��������Ч��
		chara_picture_extra.load(chara_path_close_eye);//������������״̬ͼƬ
		if (timer_chara_status == WINDOW_CHARA_NORMAL_FLAG)//ͨ������״̬���ж���ӳ�䵽ָ��ͼƬ����
		{
			chara_picture_label->setPixmap(chara_picture);
		}
		else if (timer_chara_status == WINDOW_CHARA_SPECIAL_FLAG)
		{
			chara_picture_label->setPixmap(chara_picture_extra);
		}
		else
		{
			chara_picture_label->setPixmap(chara_picture);
		}
		margin_picture.load((QString)WINDOW_MARGIN_PICTURE_LEFT_PATH_STRING);
		margin_picture_label->setPixmap(margin_picture);//���߽�

		//���ؽ��棬�����������Ա�����汻֮��Ļ�ͼ����
		ui.setupUi(this);

		//ȥ���ı��򱳾�������ֱ�����ûᵼ�����ֳ���һҳ���ֹ������󣬱������������������Ϊƽ����ʽ����ȥ���ı��򱳾��ͱ߽磬��Ϊ���Ʊ���
		ui.textEdit_main->setStyleSheet("background-color: rgb(255, 255, 255, 0);border:0px solid #e1e0e0;");

		//����ʵ��
		connect(ui.textEdit_main, SIGNAL(cursorPositionChanged()), this, SLOT(text_line_and_col()));//�ı�����������������Ļ�ȡ
		connect(ui.textEdit_main, SIGNAL(textChanged()), this, SLOT(set_not_save_status()));//����δ������
		connect(ui.pushButton_close_windows, SIGNAL(clicked()), this, SLOT(close_dialog()));//�رմ��ڰ�ť
		connect(ui.pushButton_tool_06, SIGNAL(clicked()), this, SLOT(textedit_copy()));//����
		connect(ui.pushButton_tool_07, SIGNAL(clicked()), this, SLOT(textedit_paste()));//ճ��
		connect(ui.pushButton_tool_08, SIGNAL(clicked()), this, SLOT(textedit_cut()));//����
		connect(ui.pushButton_tool_09, SIGNAL(clicked()), this, SLOT(textedit_undo()));//����
		connect(ui.pushButton_tool_10, SIGNAL(clicked()), this, SLOT(textedit_redo()));//����
		connect(ui.pushButton_tool_13, SIGNAL(clicked()), this, SLOT(textedit_font()));//����
		connect(ui.pushButton_tool_14, SIGNAL(clicked()), this, SLOT(textedit_color()));//��ɫ
		connect(ui.pushButton_tool_18, SIGNAL(clicked()), this, SLOT(textedit_help()));//������Ϣ
		connect(ui.pushButton_tool_01, SIGNAL(clicked()), this, SLOT(textedit_new()));//�½�
		connect(ui.pushButton_tool_02, SIGNAL(clicked()), this, SLOT(textedit_open()));//��
		connect(ui.pushButton_tool_03, SIGNAL(clicked()), this, SLOT(textedit_save()));//����
		connect(ui.pushButton_tool_04, SIGNAL(clicked()), this, SLOT(textedit_saveas()));//���Ϊ
		connect(ui.pushButton_tool_11, SIGNAL(clicked()), this, SLOT(textedit_find()));//����
		connect(ui.pushButton_tool_12, SIGNAL(clicked()), this, SLOT(textedit_replace()));//�滻
		connect(ui.pushButton_tool_05, SIGNAL(clicked()), this, SLOT(textedit_tohex()));//ʮ������ת��
		connect(ui.pushButton_tool_15, SIGNAL(clicked()), this, SLOT(textedit_code()));//����ת��
		connect(ui.pushButton_tool_16, SIGNAL(clicked()), this, SLOT(textedit_print()));//��ӡ
		connect(ui.pushButton_tool_17, SIGNAL(clicked()), this, SLOT(textedit_setting()));//����

		//��ʼ����ʾ
		ui.label_filestatus->setText(tr("��:1  ��:0"));//��������ʾ
		ui.label_filename->setText(tr("δ����"));//�ļ�����ʾ
		ui.label_savestatus->setText(tr("�ѱ���"));//����״̬��ʾ
		QPalette label_palette;
		QPalette text_palette;
		if (randnumber >= 1 && randnumber <= 5)//��������ͼ���Լ����������ɫ��labelʹ��WindowText�������ʹ��Text���ı��༭����Ҫʹ��Highlight
		{
			label_palette.setColor(QPalette::WindowText, QColor(255, 83, 185, 255));
			label_palette.setColor(QPalette::HighlightedText, QColor(255, 83, 185, 255));
			label_palette.setColor(QPalette::Highlight, QColor(255, 83, 185, 64));
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #FF53B9;background-color: #00FFFFFF;text-align:center;color:#FF53B9;}QProgressBar::chunk{background-color:#FF53B9;}");
		}
		else if (randnumber >= 6 && randnumber <= 10)
		{
			label_palette.setColor(QPalette::WindowText, QColor(133, 153, 212, 255));
			label_palette.setColor(QPalette::HighlightedText, QColor(133, 153, 212, 255));
			label_palette.setColor(QPalette::Highlight, QColor(133, 153, 212, 64));
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #8599D4;background-color: #00FFFFFF;text-align:center;color:#8599D4;}QProgressBar::chunk{background-color:#8599D4;}");
		}
		else if (randnumber >= 11 && randnumber <= 15)
		{
			label_palette.setColor(QPalette::WindowText, QColor(222, 63, 235, 255));
			label_palette.setColor(QPalette::HighlightedText, QColor(222, 63, 235, 255));
			label_palette.setColor(QPalette::Highlight, QColor(222, 63, 235, 64));
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #DE3FEB;background-color: #00FFFFFF;text-align:center;color:#DE3FEB;}QProgressBar::chunk{background-color:#DE3FEB;}");
		}
		else if (randnumber >= 16 && randnumber <= 20)
		{
			label_palette.setColor(QPalette::WindowText, QColor(242, 153, 93, 255));
			label_palette.setColor(QPalette::HighlightedText, QColor(242, 153, 93, 255));
			label_palette.setColor(QPalette::Highlight, QColor(242, 153, 93, 64));
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #F2995D;background-color: #00FFFFFF;text-align:center;color:#F2995D;}QProgressBar::chunk{background-color:#F2995D;}");
		}
		else if (randnumber >= 21 && randnumber <= 25)
		{
			label_palette.setColor(QPalette::WindowText, QColor(71, 185, 78, 255));
			label_palette.setColor(QPalette::HighlightedText, QColor(71, 185, 78, 255));
			label_palette.setColor(QPalette::Highlight, QColor(71, 185, 78, 64));
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #47B94E;background-color: #00FFFFFF;text-align:center;color:#47B94E;}QProgressBar::chunk{background-color:#47B94E;}");
		}
		else
		{

		}
		ui.label_filename->setPalette(label_palette);
		ui.label_filestatus->setPalette(label_palette);
		ui.label_code->setPalette(label_palette);
		ui.label_savestatus->setPalette(label_palette);
		ui.label_file_read_advance->setPalette(label_palette);

		//��������ʼ��
		ui.progressBar->setVisible(false);//��������ʼ���ɼ�
		ui.label_file_read_advance->setText(tr("���ڻ�ȡ�ļ���Ϣ����"));//��������ʼ�ı�
		ui.label_file_read_advance->setVisible(false);//������ʾ��ʼ���ɼ�
		progress_bar_change_color = false;//����������δ�л���ɫ

		//��ʼ�������ļ���Ϣ
		setting_file_read();

		//���ø��ı�
		ui.textEdit_main->setAcceptRichText(false);

		//ȥ�������Կؼ����Ҽ��˵�
		ui.textEdit_main->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
		ui.textEdit_main->horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);

		//��ק�¼���ʼ��
		ui.textEdit_main->setAcceptDrops(false);//����textEdit�ؼ�Ĭ�ϵķ��²���
		setAcceptDrops(true);//����ȫ�ֵķ��²���

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}
	Notepad::~Notepad()
	{
		delete chara_picture_timer;
		delete chara_picture_label;
		delete margin_picture_label;
	}

	//��ʼ����
	void Notepad::setting_file_read()//�����ļ���ȡ
	{
		setting_file_font_read();//����
		ifstream setting_file_color;//��ɫ
		QString file_color_input = FILE_COLOR_OUTPUT_FILE_PATH_FRONT_STRING;
		file_color_input += QString::number(font_randnumber, 10);
		file_color_input += FILE_COLOR_OUTPUT_FILE_PATH_BACK_STRING;
		string file_color_input_final = string((const char *)file_color_input.toLocal8Bit());
		setting_file_color.open(file_color_input_final, ios_base::in);//���ļ�
		if (!setting_file_color.is_open())//���ļ�ʧ��
		{
			QPalette text_palette;//������ɫ
			text_palette.setColor(QPalette::Text, QColor(0, 0, 0, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(0, 0, 0, 255));
			text_palette.setColor(QPalette::Highlight, QColor(0, 0, 0, 64));
			ui.textEdit_main->setPalette(text_palette);
		}
		else
		{
			int setting_color[3];//��ʼ������
			string temp;//��ʱ�洢������ַ���
			setting_file_color >> temp;//��
			setting_color[0] = atoi(temp.c_str());
			setting_file_color >> temp;//��
			setting_color[1] = atoi(temp.c_str());
			setting_file_color >> temp;//��
			setting_color[2] = atoi(temp.c_str());
			QPalette text_palette;//������ɫ
			text_palette.setColor(QPalette::Text, QColor(setting_color[0], setting_color[1], setting_color[2], 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(setting_color[0], setting_color[1], setting_color[2], 255));
			text_palette.setColor(QPalette::Highlight, QColor(setting_color[0], setting_color[1], setting_color[2], 64));
			ui.textEdit_main->setPalette(text_palette);
			setting_file_color.close();
		}
		ifstream setting_file_code;//����
		setting_file_code.open(FILE_CODE_OUTPUT_FILE_PATH_STRING, ios_base::in);//���ļ�
		if (!setting_file_code.is_open())//���ļ�ʧ��
		{
			code_undefine = tr("UTF-8");//���ﲻ��ʹ����ʱ����������ȵ��ú���������ϣ���ʱ�����ᱻ�ͷţ�ָ���ָ��յ�ַ���Ӷ�����
		}
		else
		{
			string information_code_temp;
			setting_file_code >> information_code_temp;//��ȡ�ļ�����
			code_undefine = QString(QString::fromLocal8Bit(information_code_temp.c_str()));
			setting_file_code.close();
		}
		text_code = &code_undefine;
		ui.label_code->setText(*text_code);
		ifstream setting_text_file;//�������ã���Ϊ�˺����ڹ��캯�����棬���Ҽ��˵��򿪴���ĺ���set_args_string����ʱ��Ҫ�磬���ڴ˴���ȡ�ļ�
		ifstream setting_binary_file;
		setting_text_file.open(FILE_SETTING_TEXT_OUTPUT_FILE_PATH_STRING, ios_base::in);//���ļ�
		setting_binary_file.open(FILE_SETTING_BINARY_OUTPUT_FILE_PATH_STRING, ios_base::in);
		if (!setting_text_file.is_open())//���ļ�ʧ��
		{
			setting_text << tr("txt") << tr("ini") << tr("inf") << tr("bat") << tr("reg");//Ĭ��ֵ
			setting_binary << tr("exe") << tr("dll");
		}
		else
		{
			string temp_string;//��ʱ�ַ���
			for (int maxsize = 0; maxsize < 100; maxsize++)
			{
				setting_text_file >> temp_string;
				if (temp_string != ""&&temp_string != FILE_SETTING_TEXT_AND_BINARY_END_WRITE_STRING)//��ȡ���ַ�����Ϊ�ջ��β��־
				{
					setting_text << QString(QString::fromLocal8Bit(temp_string.c_str()));
				}
				else
				{
					break;
				}
			}
			for (int maxsize = 0; maxsize < 100; maxsize++)
			{
				setting_binary_file >> temp_string;
				if (temp_string != ""&&temp_string != FILE_SETTING_TEXT_AND_BINARY_END_WRITE_STRING)//��ȡ���ַ�����Ϊ�ջ��β��־
				{
					setting_binary << QString(QString::fromLocal8Bit(temp_string.c_str()));
				}
				else
				{
					break;
				}
			}
			setting_text_file.close();//�ر��ļ�
			setting_binary_file.close();
		}
		setting_text_address = &setting_text;//��õ�ַ
		setting_binary_address = &setting_binary;
		QSettings *setting_other_file = new QSettings(FILE_SETTING_OTHER_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		setting_default_open_method = (setting_other_file->value(FILE_SETTING_CATALOG_1_INNER_PATH_STRING)).toString();
		if (setting_default_open_method != tr("�ı���ʽ") && setting_default_open_method != tr("�����Ʒ�ʽ"))
		{
			setting_default_open_method = tr("�ı���ʽ");
		}
		else
		{

		}
		setting_default_open_method_address = &setting_default_open_method;
		setting_size[0] = (setting_other_file->value(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING)).toInt();
		setting_size[1] = (setting_other_file->value(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING)).toInt();
		if (setting_size[0]<DIALOG_SETTING_MIN_TEXT_SIZE_NUMBER || setting_size[0]>DIALOG_SETTING_MAX_TEXT_SIZE_NUMBER)//spinbox������Χ�趨������ȡʧ��
		{
			setting_size[0] = DIALOG_SETTING_MIN_TEXT_SIZE_NUMBER;
		}
		else
		{

		}
		if (setting_size[1]<DIALOG_SETTING_MIN_BINARY_SIZE_NUMBER || setting_size[1]>DIALOG_SETTING_MAX_BINARY_SIZE_NUMBER)
		{
			setting_size[0] = DIALOG_SETTING_MIN_BINARY_SIZE_NUMBER;
		}
		else
		{

		}
		setting_size_address[0] = &setting_size[0];
		setting_size_address[1] = &setting_size[1];
		setting_bool_value[0] = (setting_other_file->value(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING)).toBool();//��ȡʧ��ʱ������ݳ�ʼֵ����ǿ��ת��������0����1����˲���Ҫ���д���
		setting_bool_value[1] = (setting_other_file->value(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING)).toBool();
		setting_bool_value[2] = (setting_other_file->value(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING)).toBool();
		setting_bool_value_address[0] = &setting_bool_value[0];
		setting_bool_value_address[1] = &setting_bool_value[1];
		setting_bool_value_address[2] = &setting_bool_value[2];
		if (*setting_bool_value_address[0] == true)
		{
			ui.textEdit_main->setLineWrapMode(QTextEdit::WidgetWidth);//�����ڴ��ڲ����ĵ�ǰ����Զ�����
		}
		else
		{
			ui.textEdit_main->setLineWrapMode(QTextEdit::NoWrap);//��ֹ�Զ�����
		}
		delete setting_other_file;
		QSettings *regedit_settings_1 = new QSettings(REG_MENU_1, QSettings::NativeFormat);//д��ע���
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
	}

	void Notepad::setting_file_font_read()//���������ļ���ȡ����Ϊ�����ļ���֮��Ҳ���õ�����˵�������һ������
	{
		ifstream setting_file;
		QString file_font_input = FILE_FONT_OUTPUT_FILE_PATH_FRONT_STRING;
		file_font_input += QString::number(font_randnumber, 10);
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_YES_FLAG)//������ģʽ����Ҫ��ȡ����������ļ�
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
			ui.textEdit_main->setFont(QFont(tr("����"), 9, QFont::Normal, false));
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
			bool information_size_receive;//ת���Ƿ�ɹ��ķ���ֵ
			int size_digit = QString(QString::fromLocal8Bit(information_size.c_str())).toInt(&information_size_receive);//ת���ߴ�Ϊ��ֵ
			QString type_transform = QString(QString::fromLocal8Bit(information_type.c_str()));//ת���ַ�����ʽ
			if (information_size_receive == false)//�޶�����ѡ��Χ
			{
				size_digit = 1;
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
			if (type_transform == tr("����"))//��������
			{
				ui.textEdit_main->setFont(QFont(QString(QString::fromLocal8Bit(information_font.c_str())), size_digit, QFont::Normal, false));
			}
			else if (type_transform == tr("����"))
			{
				ui.textEdit_main->setFont(QFont(QString(QString::fromLocal8Bit(information_font.c_str())), size_digit, QFont::Bold, false));
			}
			else if (type_transform == tr("��б"))
			{
				ui.textEdit_main->setFont(QFont(QString(QString::fromLocal8Bit(information_font.c_str())), size_digit, QFont::Normal, true));
			}
			else if (type_transform == tr("������б"))
			{
				ui.textEdit_main->setFont(QFont(QString(QString::fromLocal8Bit(information_font.c_str())), size_digit, QFont::Bold, true));
			}
			else
			{
				ui.textEdit_main->setFont(QFont(QString(QString::fromLocal8Bit(information_font.c_str())), size_digit, QFont::Normal, false));
			}
			setting_file.close();
		}
	}

	//��Ա��������
	void Notepad::set_args_string(string object_string)//��ȡͨ���Ҽ��˵��ȷ�ʽ�򿪳���ʱ�����Ŀ���ļ�·��
	{
		args_string = object_string;

		//����������
		QString args_string_result;//���ղ���
		args_string_result = QString(QString::fromLocal8Bit(args_string.c_str()));//stringתqstring
		if (!args_string_result.isEmpty())//��ȡ�ļ�
		{
			QFileInfo args_file_info(args_string_result);//��ȡ�ļ���׺�Ա���ָ���򿪷�ʽ
			QString file_suffix = args_file_info.suffix();
			if ((*setting_text_address).contains(file_suffix))//�ı���ʽ
			{
				hex_status = WINDOW_TOOL_TOHEX_STATUS_NO_FLAG;
				ui.pushButton_tool_05->setStyleSheet("border-image:url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_1.png);");//�ı䰴ť��ʽ		
			}
			else if ((*setting_binary_address).contains(file_suffix))
			{
				hex_status = WINDOW_TOOL_TOHEX_STATUS_YES_FLAG;
				ui.pushButton_tool_05->setStyleSheet("border-image:url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_2.png);");//�ı䰴ť��ʽ
			}
			else
			{
				if (*setting_default_open_method_address == tr("�ı���ʽ"))
				{
					hex_status = WINDOW_TOOL_TOHEX_STATUS_NO_FLAG;
					ui.pushButton_tool_05->setStyleSheet("border-image:url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_1.png);");//�ı䰴ť��ʽ
				}
				else if (*setting_default_open_method_address == tr("�����Ʒ�ʽ"))
				{
					hex_status = WINDOW_TOOL_TOHEX_STATUS_YES_FLAG;
					ui.pushButton_tool_05->setStyleSheet("border-image:url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_2.png);");//�ı䰴ť��ʽ
				}
				else
				{
					hex_status = WINDOW_TOOL_TOHEX_STATUS_NO_FLAG;
					ui.pushButton_tool_05->setStyleSheet("border-image:url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_1.png);");//�ı䰴ť��ʽ
				}
			}
			file_load(args_string_result);
		}
		else
		{

		}
	}

	void Notepad::set_current_path(QString object_string)//�����ļ��򿪻򱣴洰��ʹ�õ�·��
	{
		file_dialog_file_name = object_string;
	}

	//�����¼���������Ӧ��ݼ�
	void Notepad::keyPressEvent(QKeyEvent *event)
	{
		//ctrl����ĸ������ϣ��Ȱ�����ĸ���ٰ���ctrl����Ч
		if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_N))//�½�
		{
			textedit_new();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_O))//��
		{
			textedit_open();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_S))//����
		{
			textedit_save();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_D))//���Ϊ
		{
			textedit_saveas();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_P))//��ӡ
		{
			textedit_print();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_B))//�ı�ģʽ/������ģʽ�л�
		{
			textedit_tohex();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_F))//����
		{
			textedit_find();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_H))//�滻
		{
			textedit_replace();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_T))//��������
		{
			textedit_font();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_R))//��ɫ����
		{
			textedit_color();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_E))//��������
		{
			textedit_code();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_G))//��������
		{
			textedit_setting();
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_I))//������Ϣ
		{
			textedit_help();
		}
		else
		{

		}
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	void Notepad::mousePressEvent(QMouseEvent *event)//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
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

	void Notepad::mouseMoveEvent(QMouseEvent *event)//�������������£����ƶ�����λ��
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}
	}

	void Notepad::mouseReleaseEvent(QMouseEvent *event)//���δ�����£�����Ӧ����Ϊfalse
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//��ק�¼�
	void Notepad::dragEnterEvent(QDragEnterEvent *e)
	{
		if (e->mimeData()->hasUrls())//��ֹ������ק�ı����е��������Urlʶ�����Ȼ��������
		{
			e->acceptProposedAction(); //������������ڲ������ϷŶ���
		}
		else
		{

		}
	}
	
	void Notepad::dropEvent(QDropEvent *e)//�ͷ�ʱִ�еĲ���
	{
		QList<QUrl> urls = e->mimeData()->urls();
		QString file_name = urls.first().toLocalFile();//����ļ���
		file_dialog_file_name = file_name;//���빤��·�����ں����򿪻򱣴��ļ�����չ��·����ʼ��
		file_dialog_file_name_address = &file_dialog_file_name;//���빤��·�����ں����򿪻򱣴��ļ�������ʾ·����ʼ��������ʹ��file_name����Ϊ��Ϊ��ʱ����
		file_name = (file_name).replace(tr("/"), tr("\\"));//�滻·���е�ָ���ַ�
		file_load(file_name);//�����ļ�
	}

	void Notepad::paintEvent(QPaintEvent *)//�����¼�
	{

		//���ƴ��ڱ��������巽��������ָ��5�ֱ������֮���5���������ѡȡһ����ӳ�䵽����һ�ַ�����档�����Ƕ�Ӧ��ӳ���ϵ��[1,5]->��������[6,10]->���Σ�[11,15]->�ꥼ��[16,20]->�����,[21,25]->ǧҹ�����⣬֮�������ͼƬҲ�͹�������ʹ�õ�������йء�
		QString backrandnumber;//��������ͼƬ�Ĳ���
		//���¹����õ��˳�������Ҫ�޸������д
		if (randnumber >= 1 && randnumber <= 5)
		{
			backrandnumber = "1";
		}
		else if (randnumber >= 6 && randnumber <= 10)
		{
			backrandnumber = "2";
		}
		else if (randnumber >= 11 && randnumber <= 15)
		{
			backrandnumber = "3";
		}
		else if (randnumber >= 16 && randnumber <= 20)
		{
			backrandnumber = "4";
		}
		else if (randnumber >= 21 && randnumber <= 25)
		{
			backrandnumber = "5";
		}
		else
		{

		}

		//���Ʊ������ı��򱳾����ұ߽߱�
		QString filepath;//����ͼƬ·��
		QString texteditbackground;//�ı��򱳾�ͼƬ·��
		filepath = WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING + backrandnumber;
		filepath += WINDOW_BACKGROUND_PICTURE_PATH_BACK_STRING;
		texteditbackground = WINDOW_TEXTEDIT_BACKGROUND_PICTURE_PATH_STRING + backrandnumber;
		texteditbackground += WINDOW_TEXTEDIT_BACKGROUND_PICTURE_PATH_BACK_STRING;
		QPainter background_painter(this);
		QPainter margin_right_painter(this);
		QPainter textedit_painter(this);
		QPixmap background_picture;
		QPixmap margin_right_picture;
		QPixmap textedit_picture;
		background_picture.load(filepath);
		margin_right_picture.load((QString)WINDOW_MARGIN_PICTURE_RIGHT_PATH_STRING);
		textedit_picture.load(texteditbackground);
		background_painter.drawPixmap(0, 0, WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_HEIGHT_NUMBER, background_picture);
		margin_right_painter.drawPixmap(WINDOW_SIZE_MARGIN_PICTURE_LEFT_WIDTH_NUMBER, 0, WINDOW_SIZE_MARGIN_PICTURE_RIGHT_WIDTH_NUMBER, WINDOW_SIZE_MARGIN_PICTURE_LEFT_HEIGHT_NUMBER, margin_right_picture);//�����ͼƬ�߽�ĩβ��λ�û��ұ߽߱磬��Ϊ��Ҫʹ��UI�ؼ�������ұ߲���ֻ�ܻ�һ�Σ��������ɿؼ�ʧЧ
		textedit_painter.drawPixmap(WINDOW_TEXTEDIT_X_OFFSET_NUMBER, WINDOW_TEXTEDIT_Y_OFFSET_NUMBER, WINDOW_TEXTEDIT_SIZE_WIDTH_NUMBER, WINDOW_TEXTEDIT_SIZE_HEIGHT_NUMBER, textedit_picture);
	}

	//��ʱ�����ڴ�����
	void Notepad::timer_chara_picture_timeout()
	{
		chara_picture_timer->stop();
		if (timer_chara_status == WINDOW_CHARA_NORMAL_FLAG)
		{
			timer_chara_status = WINDOW_CHARA_SPECIAL_FLAG;
		}
		else if (timer_chara_status == WINDOW_CHARA_SPECIAL_FLAG)
		{
			timer_chara_status = WINDOW_CHARA_NORMAL_FLAG;
		}

		//��������ͼ������߽�
		if (timer_chara_status == WINDOW_CHARA_NORMAL_FLAG)//ͨ������״̬���ж���ӳ�䵽ָ��ͼƬ����
		{
			chara_picture_label->setPixmap(chara_picture);
			timer_interval_number = WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER + rand() % (WINDOW_RANDOM_TIMER_CHARA_NORMAL_MAX_NUMBER - WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER + 1);//��ʱ�������������۾�������ʱ��
		}
		else if (timer_chara_status == WINDOW_CHARA_SPECIAL_FLAG)
		{
			chara_picture_label->setPixmap(chara_picture_extra);
			timer_interval_number = WINDOW_RANDOM_TIMER_CHARA_SPECIAL_NUMBER;//��ʱ�����������������۾����ϵ�ʱ��
		}
		else
		{
			chara_picture_label->setPixmap(chara_picture);
			timer_interval_number = WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER + rand() % (WINDOW_RANDOM_TIMER_CHARA_NORMAL_MAX_NUMBER - WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER + 1);
		}
		margin_picture.load((QString)WINDOW_MARGIN_PICTURE_LEFT_PATH_STRING);
		margin_picture_label->setPixmap(margin_picture);//���߽�
		chara_picture_timer->setInterval(timer_interval_number);
		chara_picture_timer->start();
	}

	//��ʾ������ڵ�����������
	void Notepad::text_line_and_col()
	{
		QTextCursor textCursor = ui.textEdit_main->textCursor();//��������
		int linenumber = textCursor.blockNumber();//��ȡ��������������Իس����б𣬲�����ʾ����������
		int colnumber = textCursor.columnNumber();//��ù������
		ui.label_filestatus->setText(tr("��:%1  ��:%2").arg(linenumber + 1).arg(colnumber));//������0��ʼ�������Ҫ����1
	}

	//��������ʵ��
	void Notepad::textedit_copy()//����
	{
		ui.textEdit_main->copy();
	}

	void Notepad::textedit_paste()//ճ��
	{
		ui.textEdit_main->paste();
	}

	void Notepad::textedit_cut()//����
	{
		ui.textEdit_main->cut();
	}

	void Notepad::textedit_undo()//����
	{
		ui.textEdit_main->undo();
	}

	void Notepad::textedit_redo()//����
	{
		ui.textEdit_main->redo();
	}

	void Notepad::textedit_font()//����
	{
		Font dialog;//��Ϣ��ʾ��
		dialog.set_textedit(ui.textEdit_main);//�����ı����ַ
		dialog.set_resource_random_number(font_randnumber, hex_status);//������Դ�ļ�ʹ�õ�������ʹ���ģʽ
		dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
	}

	void Notepad::textedit_color()//��ɫ
	{
		Color dialog;//��Ϣ��ʾ��
		dialog.set_textedit(ui.textEdit_main);//�����ı����ַ
		dialog.set_resource_random_number(font_randnumber);//������Դ�ļ�ʹ�õ������
		dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
	}

	void Notepad::textedit_help()//������Ϣ
	{
		Help dialog;//��Ϣ��ʾ��
		dialog.setWindowTitle(tr("������"));
		dialog.set_dialog_information_path(DIALOG_INFORMATION_HELP_PICTURE_PATH_STRING);
		dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
	}

	void Notepad::textedit_new()//�½�
	{
		if (save_status())
		{
			ui.textEdit_main->clear();
			set_file_name("");
			ui.label_filename->setText(tr("δ����"));//�ļ�����ʾ
			QString dialog_title_name = (tr("δ����"));//���ڱ���
			dialog_title_name += WINDOW_DIALOG_TITLE_PATH_STRING;
			setWindowTitle(dialog_title_name);
			if (hex_status == WINDOW_TOOL_TOHEX_STATUS_YES_FLAG)//���ݴ���ʽ���±�����ʾ������
			{
				ui.label_code->setText(tr("����������"));//�޸������������Ϣ��ʾ
			}
			else
			{
				ui.label_code->setText(*text_code);//�޸������������Ϣ��ʾ
			}
			setting_file_font_read();//���ض�Ӧ�����ļ�
		}
		else
		{

		}
	}

	void Notepad::textedit_open()//��
	{
		if (save_status())
		{
			File dialog;//��Ϣ��ʾ��
			dialog.setWindowTitle(tr("���ļ�"));
			file_dialog_file_name = current_file_name;
			file_dialog_file_name_address = &file_dialog_file_name;//���õ�ַ
			file_dialog_status_address = &file_dialog_status;
			dialog.set_file_path_address(file_dialog_file_name_address);//�������ļ�·���ı���
			dialog.set_file_dialog_status_address(file_dialog_status_address);//�������ļ��򿪻򱣴洰�ڵ�״̬�ı���
			dialog.set_button_save_or_open(0);
			dialog.set_current_path(file_dialog_file_name);//���빤��·��
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
			if (file_dialog_status == true)
			{
				if (!file_dialog_file_name.isEmpty())
				{
					file_load(file_dialog_file_name);
				}
				else
				{
					Help dialog;//��Ϣ��ʾ��
					dialog.setWindowTitle(tr("�д���Ŷ����"));
					dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_READ_PICTURE_PATH_STRING);
					dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
				}
			}
			else
			{

			}
		}
		else
		{

		}
	}

	bool Notepad::textedit_save()//����
	{
		if (current_file_name.isEmpty())//�����ǰ�ļ�û���ļ���
		{
			return textedit_saveas();
		}
		else
		{
			return file_save(current_file_name);
		}
	}

	bool Notepad::textedit_saveas()//���Ϊ
	{
		File dialog;//��Ϣ��ʾ��
		dialog.setWindowTitle(tr("�����ļ�"));
		file_dialog_file_name = current_file_name;
		file_dialog_file_name_address = &file_dialog_file_name;//���õ�ַ
		file_dialog_status_address = &file_dialog_status;
		dialog.set_file_path_address(file_dialog_file_name_address);//�������ļ�·���ı���
		dialog.set_file_dialog_status_address(file_dialog_status_address);//�������ļ��򿪻򱣴洰�ڵ�״̬�ı���
		dialog.set_button_save_or_open(1);
		dialog.set_current_path(file_dialog_file_name);//���빤��·��
		dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		if (file_dialog_status == true)
		{
			if (file_dialog_file_name.isEmpty())
			{
				Help dialog;//��Ϣ��ʾ��
				dialog.setWindowTitle(tr("�д���Ŷ����"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_WRITE_PICTURE_PATH_STRING);
				dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
				return false;
			}
			else
			{
				return file_save(file_dialog_file_name);
			}
		}
		else
		{
			return false;
		}
	}

	void Notepad::textedit_find()//����
	{
		if (find_dialog_mutex == 1)//ֻ����û�в��ҶԻ���ʱ���ܴ���
		{
			Find *dialog = new Find;//��Ϣ��ʾ��
			dialog->set_dialog_information_path(DIALOG_INFORMATION_FIND_PICTURE_PATH_STRING);
			dialog->set_textedit(ui.textEdit_main);
			dialog->setModal(false);
			dialog->show();//���÷�ģ̬�Ի���ע���ģ̬���ڲ���ֱ���ö��󴴽�����Ҫ��new����������������˳�
		}
		else
		{

		}
		
	}

	void Notepad::textedit_replace()//�滻
	{
		if (find_dialog_mutex == 1)//ֻ����û�в��ҶԻ���ʱ���ܴ���
		{
			Replace *dialog = new Replace;//��Ϣ��ʾ��
			dialog->set_dialog_information_path(DIALOG_INFORMATION_REPLACE_PICTURE_PATH_STRING);
			dialog->set_textedit(ui.textEdit_main);
			dialog->setModal(false);
			dialog->show();//���÷�ģ̬�Ի���ע���ģ̬���ڲ���ֱ���ö��󴴽�����Ҫ��new����������������˳�
		}
		else
		{

		}

	}

	void Notepad::textedit_tohex()//ʮ������ת��
	{
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_NO_FLAG)
		{
			hex_status = WINDOW_TOOL_TOHEX_STATUS_YES_FLAG;
			ui.pushButton_tool_05->setStyleSheet("border-image:url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_2.png);");//�ı䰴ť��ʽ
		}
		else
		{
			hex_status = WINDOW_TOOL_TOHEX_STATUS_NO_FLAG;
			ui.pushButton_tool_05->setStyleSheet("border-image:url(:/picture_notepad/toolicon/picture_notepad/icon/tool_05_1.png);");//�ı䰴ť��ʽ
		}
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_YES_FLAG)//���ݴ���ʽ���±�����ʾ������
		{
			ui.label_code->setText(tr("����������"));//�޸������������Ϣ��ʾ
		}
		else
		{
			ui.label_code->setText(*text_code);//�޸������������Ϣ��ʾ
		}
		setting_file_font_read();//�����л�
	}

	void Notepad::textedit_code()//����ת��
	{
		Code dialog;
		dialog.set_code_information(text_code, ui.label_code, hex_status);
		dialog.exec();
	}

	void Notepad::textedit_setting()//��������
	{
		Setting dialog;
		dialog.set_textedit(ui.textEdit_main);//����ָ�봫�ݲ���
		dialog.set_setting_text_address(setting_text_address);
		dialog.set_setting_binary_address(setting_binary_address);
		dialog.set_setting_default_open_method_address(setting_default_open_method_address);
		dialog.set_setting_bool_value_address(setting_bool_value_address[0], 0);
		dialog.set_setting_bool_value_address(setting_bool_value_address[1], 1);
		dialog.set_setting_bool_value_address(setting_bool_value_address[2], 2);
		dialog.set_setting_size_address(setting_size_address[0], 0);
		dialog.set_setting_size_address(setting_size_address[1], 1);
		dialog.exec();
	}

	void Notepad::textedit_print()//��ӡ
	{
		Print dialog;
		dialog.set_textedit(ui.textEdit_main);//�������������
		dialog.set_timer(chara_picture_timer);
		dialog.set_label_chara(chara_picture_label);
		dialog.set_label_margin(margin_picture_label);
		dialog.set_chara_path(chara_path_normal);
		dialog.set_flag(timer_chara_status_address);
		dialog.exec();
	}

	void Notepad::file_load(QString name)//�����ļ��������õ��˴�����������Ҫ�޸������д
	{
		QFile file(name);
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_NO_FLAG)//����ʮ������ģʽ
		{
			if (!file.open(QFile::ReadOnly | QFile::Text))
			{
				Help dialog;//��Ϣ��ʾ��
				dialog.setWindowTitle(tr("�д���Ŷ����"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_READ_PICTURE_PATH_STRING);
				dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
			}
			else
			{

				set_file_name(name);
				ui.label_filename->setText(name);//�ļ�����ʾ
				QString dialog_title_name = name;//���ڱ���
				dialog_title_name += WINDOW_DIALOG_TITLE_PATH_STRING;
				setWindowTitle(dialog_title_name);
				file.close();
				File_read_text_thread *thread = new File_read_text_thread();//�������߳�
				connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
				connect(this, SIGNAL(send_file_name(QString)), thread, SLOT(get_file_name(QString)));//�ź����Ӻ�������Ӧ�÷�����ͬʱ�����������ĵط�����Ҫ��֤��������߳���������ǰ�õ����в��������⣬�źź����Ͳۺ�������Ĳ���ֻд���ͣ���д�����������ұ���ʹ��ָ�����
				connect(this, SIGNAL(send_file_size(int)), thread, SLOT(get_file_size(int)));
				connect(this, SIGNAL(send_file_code(QString)), thread, SLOT(get_file_code(QString)));
				emit send_file_name(name);//�����źţ������̴߳����ļ���
				emit send_file_size(*setting_size_address[0]);//�����źţ������̴߳���һ�δ����ļ����С
				emit send_file_code(*text_code);//�����źţ������̴߳����ļ�����
				ui.label_file_read_advance->setText(tr("���ڻ�ȡ�ļ���Ϣ����"));//��ʾԤ���������Ϣ
				ui.label_file_read_advance->setVisible(true);//��ʾ������ʾ
				progress_bar_change_color = false;//�ļ���ʱ������������ɫδ�л�
				ui.textEdit_main->clear();//����ı�����
				connect(thread, SIGNAL(send_data(QString, bool)), this, SLOT(get_data_t_r(QString, bool)));//�������̷߳��صĲ���
				connect(thread, SIGNAL(send_index(long long, long long)), this, SLOT(get_index_t_r(long long, long long)));
				connect(thread, SIGNAL(send_advance_final()), this, SLOT(get_advance_final_t_r()));
				connect(thread, SIGNAL(send_final()), this, SLOT(get_final_t_r()));
				thread->start();//��ʼ���̡߳�һ������ǰ��3��connect�������棬�����и��ʱ�������ִ�������̣߳�connect������û����ȡ���߳�������źž��Ѿ��������ˣ�Ȼ����ղ�������ɲۺ����޷�����
			}
		}
		else//��ʮ������ģʽ
		{
			if (!file.open(QFile::ReadOnly))
			{
				Help dialog;//��Ϣ��ʾ��
				dialog.setWindowTitle(tr("�д���Ŷ����"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_READ_PICTURE_PATH_STRING);
				dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
			}
			else
			{
				ui.label_code->setText("����������");
				set_file_name(name);
				ui.label_filename->setText(name);//�ļ�����ʾ
				QString dialog_title_name = name;//���ڱ���
				dialog_title_name += WINDOW_DIALOG_TITLE_PATH_STRING;
				setWindowTitle(dialog_title_name);
				file.close();
				File_read_binary_thread *thread = new File_read_binary_thread();//�������߳�
				connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
				connect(this, SIGNAL(send_file_name(QString)), thread, SLOT(get_file_name(QString)));//�ź����Ӻ�������Ӧ�÷�����ͬʱ�����������ĵط�����Ҫ��֤��������߳���������ǰ�õ����в��������⣬�źź����Ͳۺ�������Ĳ���ֻд���ͣ���д�����������ұ���ʹ��ָ�����
				connect(this, SIGNAL(send_file_size(int)), thread, SLOT(get_file_size(int)));
				connect(this, SIGNAL(send_file_addspace(bool)), thread, SLOT(get_file_addspace(bool)));
				emit send_file_name(name);//�����źţ������̴߳����ļ���
				emit send_file_size(*setting_size_address[1]);//�����źţ������̴߳���һ�δ����ļ����С
				emit send_file_addspace(*setting_bool_value_address[2]);//�����źţ������̴߳��ݾ����Ƿ���ӿո��ַ��Ĳ���ֵ
				ui.progressBar->setVisible(true);//��ʾ������
				ui.progressBar->setValue(0);//��������ʼֵΪ0
				progress_bar_change_color = false;//�ļ���ʱ������������ɫδ�л�
				if (randnumber >= 1 && randnumber <= 5)//������������ɫ��ʼ��
				{
					ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #FF53B9;background-color: #00FFFFFF;text-align:center;color:#FF53B9;}QProgressBar::chunk{background-color:#FF53B9;}");
				}
				else if (randnumber >= 6 && randnumber <= 10)
				{
					ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #8599D4;background-color: #00FFFFFF;text-align:center;color:#8599D4;}QProgressBar::chunk{background-color:#8599D4;}");
				}
				else if (randnumber >= 11 && randnumber <= 15)
				{
					ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #DE3FEB;background-color: #00FFFFFF;text-align:center;color:#DE3FEB;}QProgressBar::chunk{background-color:#DE3FEB;}");
				}
				else if (randnumber >= 16 && randnumber <= 20)
				{
					ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #F2995D;background-color: #00FFFFFF;text-align:center;color:#F2995D;}QProgressBar::chunk{background-color:#F2995D;}");
				}
				else if (randnumber >= 21 && randnumber <= 25)
				{
					ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #47B94E;background-color: #00FFFFFF;text-align:center;color:#47B94E;}QProgressBar::chunk{background-color:#47B94E;}");
				}
				else
				{

				}
				ui.textEdit_main->clear();//����ı�����
				connect(thread, SIGNAL(send_data(QString, bool)), this, SLOT(get_data_b_r(QString, bool)));//�������̷߳��صĲ���
				connect(thread, SIGNAL(send_index(long long, long long)), this, SLOT(get_index_b_r(long long, long long)));
				connect(thread, SIGNAL(send_final()), this, SLOT(get_final_b_r()));
				thread->start();//��ʼ���̡߳�һ������ǰ��3��connect�������棬�����и��ʱ�������ִ�������̣߳�connect������û����ȡ���߳�������źž��Ѿ��������ˣ�Ȼ����ղ�������ɲۺ����޷�����
			}
		}
		setting_file_font_read();//���ض�Ӧ�����ļ�
	}

	bool Notepad::save_status()//�ж��Ƿ���Ҫ����
	{
		if (ui.textEdit_main->document()->isModified())//�ж��ļ��Ƿ��޸�
		{
			Save dialog;//�����ʾ��
			dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_SAVE_PICTURE_PATH_STRING);
			dialog.set_return_number(DIALOG_INFORMATION_CANNOT_SAVE_NORMAL_RETURN_NUMBER);//Ԥ�Ȼ�ԭ����ֵ
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
			if (dialog.get_return_number() == DIALOG_INFORMATION_CANNOT_SAVE_NORMAL_RETURN_NUMBER)//ȡ��
			{
				return false;
			}
			else if (dialog.get_return_number() == DIALOG_INFORMATION_CANNOT_SAVE_SAVE_RETURN_NUMBER)//����
			{
				
				return textedit_save();
			}
			else if (dialog.get_return_number() == DIALOG_INFORMATION_CANNOT_SAVE_DISCARD_RETURN_NUMBER)//���ԣ���������
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}

	bool Notepad::file_save(QString name)//ʵ�ʱ��湦�ܡ������õ��˴�����������Ҫ�޸������д
	{
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_NO_FLAG)//����ʮ������ģʽ
		{
			QFile file(name);
			if (!file.open(QFile::WriteOnly | QFile::Text))
			{
				Help dialog;//��Ϣ��ʾ��
				dialog.setWindowTitle(tr("�д���Ŷ����"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_WRITE_PICTURE_PATH_STRING);
				dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
				return false;
			}
			else
			{
				set_file_name(name);
				ui.label_filename->setText(name);//�ļ�����ʾ
				QString dialog_title_name = name;//���ڱ���
				dialog_title_name += WINDOW_DIALOG_TITLE_PATH_STRING;
				setWindowTitle(dialog_title_name);
				file.close();
				File_write_text_thread *thread = new File_write_text_thread();//�������߳�
				connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
				connect(this, SIGNAL(send_file_name(QString)), thread, SLOT(get_file_name(QString)));//�ź����Ӻ�������Ӧ�÷�����ͬʱ�����������ĵط�����Ҫ��֤��������߳���������ǰ�õ����в��������⣬�źź����Ͳۺ�������Ĳ���ֻд���ͣ���д�����������ұ���ʹ��ָ�����
				connect(this, SIGNAL(send_file_output(QString)), thread, SLOT(get_file_output(QString)));
				connect(this, SIGNAL(send_file_code(QString)), thread, SLOT(get_file_code(QString)));
				emit send_file_name(name);//�����źţ������̴߳����ļ���
				emit send_file_output(ui.textEdit_main->toPlainText());//�����źţ������̴߳�����Ҫ������ı�
				ui.label_file_read_advance->setText(tr("���ڱ����ļ�����"));//��ʾ������Ϣ
				ui.label_file_read_advance->setVisible(true);//��ʾ������ʾ
				emit send_file_code(*text_code);//�����źţ������̴߳����ļ�����
				progress_bar_change_color = false;//�ļ���ʱ������������ɫδ�л�
				connect(thread, SIGNAL(send_final()), this, SLOT(get_final_t_w()));
				thread->start();//��ʼ���̡߳�һ������ǰ��3��connect�������棬�����и��ʱ�������ִ�������̣߳�connect������û����ȡ���߳�������źž��Ѿ��������ˣ�Ȼ����ղ�������ɲۺ����޷�����
				return true;
			}
		}
		else
		{
			QFile file(name);
			if (!file.open(QFile::WriteOnly))
			{
				Help dialog;//��Ϣ��ʾ��
				dialog.setWindowTitle(tr("�д���Ŷ����"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_WRITE_PICTURE_PATH_STRING);
				dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
				return false;
			}
			else
			{
				set_file_name(name);
				ui.label_filename->setText(name);//�ļ�����ʾ
				QString dialog_title_name = name;//���ڱ���
				dialog_title_name += WINDOW_DIALOG_TITLE_PATH_STRING;
				setWindowTitle(dialog_title_name);
				file.close();
				File_write_binary_thread *thread = new File_write_binary_thread();//�������߳�
				connect(thread, &QThread::finished, thread, &QObject::deleteLater);//ֱ��delete���̼߳������׳��ָ������⣬Ҫ�밲ȫɾ���߳̿���ʹ�ô˷�ʽ
				connect(this, SIGNAL(send_file_name(QString)), thread, SLOT(get_file_name(QString)));//�ź����Ӻ�������Ӧ�÷�����ͬʱ�����������ĵط�����Ҫ��֤��������߳���������ǰ�õ����в��������⣬�źź����Ͳۺ�������Ĳ���ֻд���ͣ���д�����������ұ���ʹ��ָ�����
				connect(this, SIGNAL(send_file_output(QString)), thread, SLOT(get_file_output(QString)));
				emit send_file_name(name);//�����źţ������̴߳����ļ���
				emit send_file_output(ui.textEdit_main->toPlainText());//�����źţ������̴߳�����Ҫ������ı�
				ui.label_file_read_advance->setText(tr("���ڱ����ļ�����"));//��ʾ������Ϣ
				ui.label_file_read_advance->setVisible(true);//��ʾ������ʾ
				progress_bar_change_color = false;//�ļ���ʱ������������ɫδ�л�
				connect(thread, SIGNAL(send_final()), this, SLOT(get_final_b_w()));
				thread->start();//��ʼ���̡߳�һ������ǰ��3��connect�������棬�����и��ʱ�������ִ�������̣߳�connect������û����ȡ���߳�������źž��Ѿ��������ˣ�Ȼ����ղ�������ɲۺ����޷�����
				return true;
			}
		}
	}

	void Notepad::set_file_name(QString name)//�����ļ�������ʼ���ı����޸�״̬
	{
		current_file_name = name;
		ui.textEdit_main->document()->setModified(false);//�����ı����޸�״̬Ϊδ�޸�
		ui.label_savestatus->setText(tr("�ѱ���"));
		this->setWindowModified(false);
		name.isEmpty() ? this->setWindowFilePath("new.txt") : this->setWindowFilePath(name);
	}

	void Notepad::close_dialog()//�رմ��ڰ�ť
	{
		if (save_status())
		{
			close_window_include_animation();//�رմ��ڲ����˳�����
		}
		else
		{

		}
	}

	void Notepad::set_not_save_status()//����δ������
	{
		if (ui.textEdit_main->document()->isModified())//������жϣ���ֹ�������ó������ܻص���ʼ״̬ȴ��ʾδ�����״��
		{
			ui.label_savestatus->setText(tr("δ����"));
		}
		else
		{
			ui.label_savestatus->setText(tr("�ѱ���"));
		}
	}

	void Notepad::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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
	
	//File_read_text_thread������߳����ݽ���
	void Notepad::get_data_t_r(QString data, bool status)//��ʾ���ݣ�status�����Ƿ�Ϊ���һ��
	{
		char *transform_final;//QStringתchar*����ñ�������
		QByteArray transform = (*text_code).toLocal8Bit();
		transform_final = transform.data();
		ui.label_code->setText(*text_code);
		ui.textEdit_main->insertPlainText(data);
		if (status)//���һ����Ҫ��������
		{
			ui.textEdit_main->document()->setModified(false);//�����ı����޸�״̬Ϊδ�޸�
			ui.label_savestatus->setText(tr("�ѱ���"));
		}
		else
		{

		}
	}

	void Notepad::get_index_t_r(long long index, long long total_size)//��������ʾ
	{
		double progress_bar_value = (((double)index / (double)total_size)*100);//�������
		if (progress_bar_value > 100)
		{
			progress_bar_value = 100;
		}
		else
		{

		}
		if (progress_bar_value > 50 && !progress_bar_change_color)//���⿴��������
		{
			if (randnumber >= 1 && randnumber <= 5)
			{
				ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #FF53B9;background-color: #00FFFFFF;text-align:center;color:#F8EBF4;}QProgressBar::chunk{background-color:#FF53B9;}");
			}
			else if (randnumber >= 6 && randnumber <= 10)
			{
				ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #8599D4;background-color: #00FFFFFF;text-align:center;color:#EDECF7;}QProgressBar::chunk{background-color:#8599D4;}");
			}
			else if (randnumber >= 11 && randnumber <= 15)
			{
				ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #DE3FEB;background-color: #00FFFFFF;text-align:center;color:#F0E5F7;}QProgressBar::chunk{background-color:#DE3FEB;}");
			}
			else if (randnumber >= 16 && randnumber <= 20)
			{
				ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #F2995D;background-color: #00FFFFFF;text-align:center;color:#FBEDE4;}QProgressBar::chunk{background-color:#F2995D;}");
			}
			else if (randnumber >= 21 && randnumber <= 25)
			{
				ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #47B94E;background-color: #00FFFFFF;text-align:center;color:#EEF2EB;}QProgressBar::chunk{background-color:#47B94E;}");
			}
			else
			{

			}
			progress_bar_change_color = true;//��ֻ֤�л�һ��������ɫ
		}
		else
		{

		}
		ui.progressBar->setValue((int)progress_bar_value);//��������ʾ
	}

	void Notepad::get_advance_final_t_r()//���ؽ�����ʾ����ʾ������
	{
		ui.label_file_read_advance->setVisible(false);//���ؽ�����ʾ
		ui.progressBar->setValue(0);//��������ֵ��ʼ��
		if (randnumber >= 1 && randnumber <= 5)//������������ɫ��ʼ��
		{
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #FF53B9;background-color: #00FFFFFF;text-align:center;color:#FF53B9;}QProgressBar::chunk{background-color:#FF53B9;}");
		}
		else if (randnumber >= 6 && randnumber <= 10)
		{
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #8599D4;background-color: #00FFFFFF;text-align:center;color:#8599D4;}QProgressBar::chunk{background-color:#8599D4;}");
		}
		else if (randnumber >= 11 && randnumber <= 15)
		{
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #DE3FEB;background-color: #00FFFFFF;text-align:center;color:#DE3FEB;}QProgressBar::chunk{background-color:#DE3FEB;}");
		}
		else if (randnumber >= 16 && randnumber <= 20)
		{
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #F2995D;background-color: #00FFFFFF;text-align:center;color:#F2995D;}QProgressBar::chunk{background-color:#F2995D;}");
		}
		else if (randnumber >= 21 && randnumber <= 25)
		{
			ui.progressBar->setStyleSheet("QProgressBar{border: 1px solid #47B94E;background-color: #00FFFFFF;text-align:center;color:#47B94E;}QProgressBar::chunk{background-color:#47B94E;}");
		}
		else
		{

		}
		ui.progressBar->setVisible(true);//��ʾ������
	}

	void Notepad::get_final_t_r()//����
	{
		ui.progressBar->setValue((int)WINDOW_PROGRESSBAR_MAX_VALUE_NUMBER);//��������ʾ���ֵ
		ui.progressBar->setVisible(false);//���ؽ�����
	}

	//File_write_text_thread������߳����ݽ���
	void Notepad::get_final_t_w()//����
	{
		ui.label_file_read_advance->setVisible(false);//���ؽ�����ʾ
	}

	//File_read_binary_thread������߳����ݽ���
	void Notepad::get_data_b_r(QString data, bool status)//��ʾ���ݣ�status�����Ƿ�Ϊ���һ��
	{
		ui.textEdit_main->insertPlainText(data);
		if (status)//���һ����Ҫ��������
		{
			ui.textEdit_main->document()->setModified(false);//�����ı����޸�״̬Ϊδ�޸�
			ui.label_savestatus->setText(tr("�ѱ���"));
		}
		else
		{

		}
	}

	void Notepad::get_index_b_r(long long index, long long total_size)//��������ʾ
	{
		get_index_t_r(index, total_size);//�Ͷ�ȡ�ı��ļ�һ��
	}

	void Notepad::get_final_b_r()//����
	{
		get_final_t_r();
	}

	void Notepad::get_final_b_w()//���ؽ�����ʾ
	{
		get_final_t_w();
	}

	//���߳��ຯ��
	File_read_text_thread::File_read_text_thread()//���캯��
	{
		
	}

	File_read_text_thread::~File_read_text_thread()//��������
	{

	}

	void File_read_text_thread::get_file_name(QString file_name)//��ȡ�ļ���
	{
		this->file_name = file_name;//��Ϊ��ĳ�Ա�������Ͳ�������ͬ����˱�����thisָ��
	}

	void File_read_text_thread::get_file_size(int file_size)//��ȡһ�δ����ļ����С
	{
		this->file_size = file_size;
	}

	void File_read_text_thread::get_file_code(QString file_code)//��ȡһ�δ����ļ����С
	{
		this->file_code = file_code;
	}

	void File_read_text_thread::run()//���߳�������
	{
		mutex.lock();//�������
		QFile sourcefile(file_name);
		if (!sourcefile.open(QFile::ReadOnly | QFile::Text))//�ڶ��δ��ļ�������޷��򿪾Ͳ�������ʾ����Ϊ֮ǰһ���Ѿ���������ʾ
		{

		}
		else
		{
			QTextStream sourcefile_textstream(&sourcefile);
			QTextStream *sourcefile_textstream_address = &sourcefile_textstream;//QTextStream����ֱ�Ӱ�ֵ���ݣ�Ҳ����ʹ�����ô��ݣ����ǿ�����ָ�봫��
			char* transform_final;//QStringתchar*
			QByteArray transform = (file_code).toLocal8Bit();
			transform_final = transform.data();
			sourcefile_textstream.setCodec(transform_final);//���ñ���
			long long total_time = 0;//֮���ȡ�ļ��ܹ���Ҫѭ���Ĵ��������������ʵ�ʴ��������һ��
			long long total_size = 0;//�ļ��ܴ�С
			int once_size = 0;//��ĳһ�ζ�ȡʱ��õĿ��С
			for (total_time = 0;; total_time++)//�ȶ�ȡһ���ļ�������ַ�����Ϣ��Ϣ
			{
				QString temp_string = sourcefile_textstream.read(file_size*FILE_BIT_TO_KBIT);//��ȡָsend_advance_final�����С���ļ��ֽڣ�Ȼ�����ʵ���ֽ�������Ϊ���һ�δ󲿷�����¶�ȡ���ַ�������ﵽ��Ӧ�Ŀ��С������ͬʱ���ܵĴ���������м�¼
				once_size = temp_string.size();
				total_size += once_size;
				if (once_size < file_size*FILE_BIT_TO_KBIT)
				{
					break;
				}
				else
				{

				}
			}
			emit send_advance_final();//�ļ���ȡ���ַ���Ŀ������ϣ������ź�
			sourcefile_textstream.seek(0);//ָ�����¶��嵽�ļ���ͷ���ڽ�������ʵ�ʶ�ȡ
			typedef QString(*FUNCPROC)(QTextStream*, int);//�궨�庯��ָ�����ͣ��Զ�������ΪFUNCPROC
			HINSTANCE dll_name;//��ʽ����dll�ļ�
			dll_name = LoadLibrary(FILE_DLL_FILE_READ_PATH_STRING);//����dll�ļ�������Ϊ���ַ�����
			if (dll_name != NULL)
			{
				FUNCPROC file_read_text_func = (FUNCPROC)GetProcAddress(dll_name, "file_read_text");//���dll�к�������ַ����file_read_text_func���������
				if (file_read_text_func != NULL)
				{
					for (long long temp_time = 1; temp_time <= total_time; temp_time++)//ʹ��ѭ����ȡ�ļ����ݣ����������һ��
					{
						QString return_string = file_read_text_func(sourcefile_textstream_address, file_size);//�������ԣ�ֱ�ӽ�return_string�ұ߲���ȫ��д��emit����ᵼ�´���
						Sleep(WINDOW_THREAD_WAIT_TIME_NUMBER);//���߳�����һ��ʱ�䣬�������й��쵼�����߳̿���
						emit send_data(return_string, false);
						emit send_index(file_size*temp_time*FILE_BIT_TO_KBIT, total_size);
					}
					QString return_string;//���һ����Ϊ�źŵ�ԭ�򵥶�����
					return_string = file_read_text_func(sourcefile_textstream_address, file_size);
					Sleep(WINDOW_THREAD_WAIT_TIME_NUMBER);//���߳�����һ��ʱ�䣬�������й��쵼�����߳̿���
					emit send_data(return_string, true);
					emit send_index(file_size*((total_time + 1)*FILE_BIT_TO_KBIT), total_size);
					emit send_final();//�������
				}
				else
				{

				}
				FreeLibrary(dll_name);//ж��dll�ļ���ע������ͼ���dll�ļ���ͬ
			}
			else
			{

			}
			sourcefile.close();
		}
		mutex.unlock();//����
		this->quit();//�˳����߳�
	}

	File_write_text_thread::File_write_text_thread()//���캯��
	{

	}

	File_write_text_thread::~File_write_text_thread()//��������
	{

	}

	void File_write_text_thread::get_file_output(QString file_output)//����ļ���Ҫ���������
	{
		this->file_output = file_output;
	}

	void File_write_text_thread::run()
	{
		mutex.lock();//�������
		QFile outputfile(file_name);
		QTextStream outputfile_textstream(&outputfile);
		QTextStream *outputfile_textstream_address = &outputfile_textstream;//QTextStream����ֱ�Ӱ�ֵ���ݣ�Ҳ����ʹ�����ô��ݣ����ǿ�����ָ�봫��
		char* transform_final;//QStringתchar*
		QByteArray transform = file_code.toLocal8Bit();
		transform_final = transform.data();
		outputfile_textstream.setCodec(transform_final);//���ñ���
		if (!outputfile.open(QFile::WriteOnly | QFile::Text))//�ڶ��δ��ļ�������޷��򿪾Ͳ�������ʾ����Ϊ֮ǰһ���Ѿ���������ʾ
		{

		}
		else
		{
			typedef void(*FUNCPROC)(QTextStream*, QString);//�궨�庯��ָ�����ͣ��Զ�������ΪFUNCPROC
			HINSTANCE dll_name;//��ʽ����dll�ļ�
			dll_name = LoadLibrary(FILE_DLL_FILE_READ_PATH_STRING);//����dll�ļ�������Ϊ���ַ�����
			if (dll_name != NULL)
			{
				FUNCPROC file_write_text_func = (FUNCPROC)GetProcAddress(dll_name, "file_write_text");//���dll�к�������ַ����file_read_text_func���������
				if (file_write_text_func != NULL)
				{
					file_write_text_func(outputfile_textstream_address, file_output);
					Sleep(WINDOW_THREAD_WAIT_TIME_NUMBER);//���߳�����һ��ʱ�䣬�������й��쵼�����߳̿���
					emit send_final();//�������
				}
				else
				{
					
				}
				FreeLibrary(dll_name);//ж��dll�ļ���ע������ͼ���dll�ļ���ͬ
			}
			else
			{

			}
			outputfile.close();
		}
		mutex.unlock();//����
		this->quit();//�˳����߳�
	}

	File_read_binary_thread::File_read_binary_thread()//���캯��
	{

	}

	File_read_binary_thread::~File_read_binary_thread()//��������
	{

	}

	void File_read_binary_thread::get_file_addspace(bool file_addspace)//��ȡ�Ƿ���ӿո�Ĳ���ֵ
	{
		this->file_addspace = file_addspace;
	}

	void File_read_binary_thread::run()//���߳�������
	{
		mutex.lock();//�������
		QFile sourcefile(file_name);
		if (!sourcefile.open(QFile::ReadOnly))//�ڶ��δ��ļ�������޷��򿪾Ͳ�������ʾ����Ϊ֮ǰһ���Ѿ���������ʾ
		{

		}
		else
		{
			QDataStream sourcefile_datastream(&sourcefile);
			QDataStream *sourcefile_datastream_address = &sourcefile_datastream;//QTextStream����ֱ�Ӱ�ֵ���ݣ�Ҳ����ʹ�����ô��ݣ����ǿ�����ָ�봫��
			long long total_size = sourcefile.size();//�ļ��ܴ�С
			long long total_time = (long long)(sourcefile.size() / file_size/ FILE_BIT_TO_KBIT);//֮���ȡ�ļ��ܹ���Ҫѭ���Ĵ��������������ʵ�ʴ��������һ��
			typedef QString(*FUNCPROC)(QDataStream*, int, bool);//�궨�庯��ָ�����ͣ��Զ�������ΪFUNCPROC
			HINSTANCE dll_name;//��ʽ����dll�ļ�
			dll_name = LoadLibrary(FILE_DLL_FILE_READ_PATH_STRING);//����dll�ļ�������Ϊ���ַ�����
			if (dll_name != NULL)
			{
				FUNCPROC file_read_binary_func = (FUNCPROC)GetProcAddress(dll_name, "file_read_binary");//���dll�к�������ַ����file_read_text_func���������
				if (file_read_binary_func != NULL)
				{
					for (long long temp_time = 1; temp_time <= total_time; temp_time++)//ʹ��ѭ����ȡ�ļ����ݣ����������һ��
					{
						QString return_string = file_read_binary_func(sourcefile_datastream_address, file_size*FILE_BIT_TO_KBIT, file_addspace);//�������ԣ�ֱ�ӽ�return_string�ұ߲���ȫ��д��emit����ᵼ�´���ע����С�ĵ�λ��dll�ļ�����û�г��Ա��ʣ���Ҫ�����ﴦ��
						Sleep(WINDOW_THREAD_WAIT_TIME_NUMBER);//���߳�����һ��ʱ�䣬�������й��쵼�����߳̿���
						emit send_data(return_string, false);
						emit send_index(file_size*temp_time*FILE_BIT_TO_KBIT, total_size);
					}
					QString return_string;//���һ����Ϊ�źŵ�ԭ�򵥶�����
					return_string = file_read_binary_func(sourcefile_datastream_address, total_size - file_size * total_time*FILE_BIT_TO_KBIT, file_addspace);//���ڶ�ȡԭʼ�����Ǵ���char*�ģ�����̬�����char*���ݻ��г�ʼ�������ݣ������һ��Ҫ���ƺô�С�������ļ�ĩβ������������
					Sleep(WINDOW_THREAD_WAIT_TIME_NUMBER);//���߳�����һ��ʱ�䣬�������й��쵼�����߳̿���
					emit send_data(return_string, true);
					emit send_index(file_size*((total_time + 1)*FILE_BIT_TO_KBIT), total_size);
					emit send_final();//�������
				}
				else
				{

				}
				FreeLibrary(dll_name);//ж��dll�ļ���ע������ͼ���dll�ļ���ͬ
			}
			else
			{

			}
			sourcefile.close();
		}
		mutex.unlock();//����
		this->quit();//�˳����߳�
	}

	File_write_binary_thread::File_write_binary_thread()//���캯��
	{

	}

	File_write_binary_thread::~File_write_binary_thread()//��������
	{

	}

	void File_write_binary_thread::get_file_output(QString file_output)//����ļ���Ҫ���������
	{
		this->file_output = file_output;
	}

	void File_write_binary_thread::run()
	{
		mutex.lock();//�������
		QFile outputfile(file_name);
		QDataStream outputfile_datastream(&outputfile);
		QDataStream *outputfile_datastream_address = &outputfile_datastream;//QTextStream����ֱ�Ӱ�ֵ���ݣ�Ҳ����ʹ�����ô��ݣ����ǿ�����ָ�봫��
		if (!outputfile.open(QFile::WriteOnly))//�ڶ��δ��ļ�������޷��򿪾Ͳ�������ʾ����Ϊ֮ǰһ���Ѿ���������ʾ
		{

		}
		else
		{
			typedef void(*FUNCPROC)(QDataStream*, QString);//�궨�庯��ָ�����ͣ��Զ�������ΪFUNCPROC
			HINSTANCE dll_name;//��ʽ����dll�ļ�
			dll_name = LoadLibrary(FILE_DLL_FILE_READ_PATH_STRING);//����dll�ļ�������Ϊ���ַ�����
			if (dll_name != NULL)
			{
				FUNCPROC file_write_binary_func = (FUNCPROC)GetProcAddress(dll_name, "file_write_binary");//���dll�к�������ַ����file_read_text_func���������
				if (file_write_binary_func != NULL)
				{
					file_write_binary_func(outputfile_datastream_address, file_output);
					Sleep(WINDOW_THREAD_WAIT_TIME_NUMBER);//���߳�����һ��ʱ�䣬�������й��쵼�����߳̿���
					emit send_final();//�������
				}
				else
				{

				}
				FreeLibrary(dll_name);//ж��dll�ļ���ע������ͼ���dll�ļ���ͬ
			}
			else
			{

			}
			outputfile.close();
		}
		mutex.unlock();//����
		this->quit();//�˳����߳�
	}
}

