#include "define.h"

namespace rem
{

	//����ȫ�ֱ���
	extern int counter_mutex;

	//��������������
	ToolsSet::ToolsSet(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�

		//����ͼƬ��Ϊ���ڱ���
		main_picture.load(DIALOG_TOOLS_SET_BACKGROUND_PICTURE_PATH_STRING);
		resize(main_picture.size());//���ڴ�С��ΪͼƬ��С

		//���ؽ���
		ui.setupUi(this);
		
		//����������ɫ
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::WindowText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::Highlight, QColor(70, 28, 10, 64));
		ui.comboBox_1->setPalette(text_palette);
		ui.comboBox_2->setPalette(text_palette);
		ui.lineedit_program_1->setPalette(text_palette);
		ui.lineedit_program_2->setPalette(text_palette);
		ui.lineedit_program_3->setPalette(text_palette);
		ui.lineedit_program_4->setPalette(text_palette);
		ui.lineedit_program_5->setPalette(text_palette);
		ui.lineedit_program_6->setPalette(text_palette);
		ui.lineedit_program_7->setPalette(text_palette);
		ui.lineedit_program_8->setPalette(text_palette);
		ui.spinBox_1->setPalette(text_palette);
		ui.spinBox_2->setPalette(text_palette);
		
		//���������
		read_font();

		//ȥ�������Կؼ����Ҽ��˵�
		QList<QScrollBar *> scroll_bar = this->findChildren<QScrollBar *>();//�����޷��ó��淽ʽ���combobox�Ĺ����������ʹ�ø÷�����������ͬ���Ϳؼ������в���
		foreach(QScrollBar *scroll_bar_style_control, scroll_bar)
		{
			scroll_bar_style_control->setContextMenuPolicy(Qt::NoContextMenu);
		}

		//��ȡԤ�����ݣ��Դ�����ʾ���г�ʼ��
		QSettings *begin_read = new QSettings(FILE_SETTING_MAINWINDOW_STYLE_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		QString combobox_1_index;//������һ��combobox������
		combobox_1_index = (begin_read->value(FILE_SETTING_CATALOG_1_INNER_PATH_STRING)).toString();
		if (combobox_1_index == "1")//������ʼ��
		{
			ui.comboBox_1->setCurrentText(tr("ħ����Ů������"));
		}
		else if (combobox_1_index == "2")
		{
			ui.comboBox_1->setCurrentText(tr("���`����`������"));
		}
		else if (combobox_1_index == "3")
		{
			ui.comboBox_1->setCurrentText(tr("����ʩ`���ޥ�"));
		}
		else if (combobox_1_index == "4")
		{
			ui.comboBox_1->setCurrentText(tr("�Щ`���`���`���ᥰ"));
		}
		else
		{
			ui.comboBox_1->setCurrentText(tr("ħ����Ů������"));
		}
		QString program_path[8];//����·��
		program_path[0] = (begin_read->value(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING)).toString();
		program_path[1] = (begin_read->value(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING)).toString();
		program_path[2] = (begin_read->value(FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING)).toString();
		program_path[3] = (begin_read->value(FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING)).toString();
		program_path[4] = (begin_read->value(FILE_SETTING_CATALOG_2_5_INNER_PATH_STRING)).toString();
		program_path[5] = (begin_read->value(FILE_SETTING_CATALOG_2_6_INNER_PATH_STRING)).toString();
		program_path[6] = (begin_read->value(FILE_SETTING_CATALOG_2_7_INNER_PATH_STRING)).toString();
		program_path[7] = (begin_read->value(FILE_SETTING_CATALOG_2_8_INNER_PATH_STRING)).toString();
		ui.lineedit_program_1->setText(program_path[0]);//��ݼ����������ʼ��
		ui.lineedit_program_2->setText(program_path[1]);
		ui.lineedit_program_3->setText(program_path[2]);
		ui.lineedit_program_4->setText(program_path[3]);
		ui.lineedit_program_5->setText(program_path[4]);
		ui.lineedit_program_6->setText(program_path[5]);
		ui.lineedit_program_7->setText(program_path[6]);
		ui.lineedit_program_8->setText(program_path[7]);
		if (program_path[0].length()==0)//��ʼֵ���ã����������ļ���ʧ
		{
			ui.lineedit_program_1->setText(tr("null"));
		}
		else
		{

		}
		if (program_path[1].length() == 0)
		{
			ui.lineedit_program_2->setText(tr("null"));
		}
		else
		{

		}
		if (program_path[2].length() == 0)
		{
			ui.lineedit_program_3->setText(tr("null"));
		}
		else
		{

		}
		if (program_path[3].length() == 0)
		{
			ui.lineedit_program_4->setText(tr("null"));
		}
		else
		{

		}
		if (program_path[4].length() == 0)
		{
			ui.lineedit_program_5->setText(tr("null"));
		}
		else
		{

		}
		if (program_path[5].length() == 0)
		{
			ui.lineedit_program_6->setText(tr("null"));
		}
		else
		{

		}
		if (program_path[6].length() == 0)
		{
			ui.lineedit_program_7->setText(tr("null"));
		}
		else
		{

		}
		if (program_path[7].length() == 0)
		{
			ui.lineedit_program_8->setText(tr("null"));
		}
		else
		{

		}
		bool temp_transform_status_x;//�ַ���ת��Ϊ�����Ƿ�ɹ�
		bool temp_transform_status_y;
		QString temp_transform_string_x = (begin_read->value(FILE_SETTING_CATALOG_5_1_INNER_PATH_STRING)).toString();
		QString temp_transform_string_y = (begin_read->value(FILE_SETTING_CATALOG_5_2_INNER_PATH_STRING)).toString();
		int position_x = temp_transform_string_x.toInt(&temp_transform_status_x, 10);//ת��Ϊ����
		int position_y = temp_transform_string_y.toInt(&temp_transform_status_y, 10);
		if (temp_transform_status_x&&temp_transform_status_y)//ת��ʧ����ǿ�ƽ�����תΪ0
		{

		}
		else
		{
			position_x = 0;
			position_y = 0;
		}
		ui.spinBox_1->setValue(position_x);//��ʼ�����ʼ��
		ui.spinBox_2->setValue(position_y);
		QString note_font;//��ǩ����
		note_font = (begin_read->value(FILE_SETTING_CATALOG_4_INNER_PATH_STRING)).toString();
		ui.comboBox_2->setCurrentText(note_font);//��ǩ�����ʼ��
		QString autorun_status;//�Ƿ񿪻�������
		autorun_status = (begin_read->value(FILE_SETTING_CATALOG_3_INNER_PATH_STRING)).toString();
		if (autorun_status == "1")
		{
			ui.checkBox->setChecked(true);
		}
		else if (autorun_status == "0")
		{
			ui.checkBox->setChecked(false);
		}
		else
		{
			ui.checkBox->setChecked(false);
		}

		delete begin_read;

		//�źź���
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//������Ч
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//ȡ������
		connect(ui.pushButton_choose_1, SIGNAL(clicked()), this, SLOT(pushButton_choose_1_apply()));//ѡ��·����ť
		connect(ui.pushButton_choose_2, SIGNAL(clicked()), this, SLOT(pushButton_choose_2_apply()));
		connect(ui.pushButton_choose_3, SIGNAL(clicked()), this, SLOT(pushButton_choose_3_apply()));
		connect(ui.pushButton_choose_4, SIGNAL(clicked()), this, SLOT(pushButton_choose_4_apply()));
		connect(ui.pushButton_choose_5, SIGNAL(clicked()), this, SLOT(pushButton_choose_5_apply()));
		connect(ui.pushButton_choose_6, SIGNAL(clicked()), this, SLOT(pushButton_choose_6_apply()));
		connect(ui.pushButton_choose_7, SIGNAL(clicked()), this, SLOT(pushButton_choose_7_apply()));
		connect(ui.pushButton_choose_8, SIGNAL(clicked()), this, SLOT(pushButton_choose_8_apply()));
		connect(ui.pushButton_choose_9, SIGNAL(clicked()), this, SLOT(pushButton_choose_9_apply()));
		connect(ui.pushButton_choose_10, SIGNAL(clicked()), this, SLOT(pushButton_choose_10_apply()));
		connect(ui.pushButton_choose_11, SIGNAL(clicked()), this, SLOT(pushButton_choose_11_apply()));
		connect(ui.pushButton_choose_12, SIGNAL(clicked()), this, SLOT(pushButton_choose_12_apply()));
		connect(ui.pushButton_choose_13, SIGNAL(clicked()), this, SLOT(pushButton_choose_13_apply()));
		connect(ui.pushButton_choose_14, SIGNAL(clicked()), this, SLOT(pushButton_choose_14_apply()));
		connect(ui.pushButton_choose_15, SIGNAL(clicked()), this, SLOT(pushButton_choose_15_apply()));
		connect(ui.pushButton_choose_16, SIGNAL(clicked()), this, SLOT(pushButton_choose_16_apply()));

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}

	ToolsSet::~ToolsSet()
	{

	}

	//��ʼ����
	void ToolsSet::read_font()//��ȡϵͳ�������岢������Ͽ�
	{
		QFontDatabase combobox_fontdatabase;
		foreach(const QString &font_name, combobox_fontdatabase.families())
		{
			ui.comboBox_2->addItem(font_name);
		}
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void ToolsSet::mousePressEvent(QMouseEvent *event)
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
	//�������������£����ƶ�����λ��
	void ToolsSet::mouseMoveEvent(QMouseEvent *event)
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}
	}

	//���δ�����£�����Ӧ����Ϊfalse
	void ToolsSet::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void ToolsSet::keyPressEvent(QKeyEvent *event)
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

	void ToolsSet::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(WINDOW_BACKGROUND_PAINT_START_X_NUMBER, WINDOW_BACKGROUND_PAINT_START_Y_NUMBER, main_picture);//��ͼ��Ϊ���ڱ���
	}

	//�ۺ���
	void ToolsSet::set_apply()//������Ч
	{

		//д��ini�ļ�
		QSettings *write_setting = new QSettings(FILE_SETTING_MAINWINDOW_STYLE_PATH_STRING, QSettings::IniFormat);
		QString background_picture = ui.comboBox_1->currentText();//����ͼƬ
		if (background_picture == tr("ħ����Ů������"))
		{
			write_setting->setValue(FILE_SETTING_CATALOG_1_INNER_PATH_STRING, "1");
		}
		else if (background_picture == tr("���`����`������"))
		{
			write_setting->setValue(FILE_SETTING_CATALOG_1_INNER_PATH_STRING, "2");
		}
		else if (background_picture == tr("����ʩ`���ޥ�"))
		{
			write_setting->setValue(FILE_SETTING_CATALOG_1_INNER_PATH_STRING, "3");
		}
		else if (background_picture == tr("�Щ`���`���`���ᥰ"))
		{
			write_setting->setValue(FILE_SETTING_CATALOG_1_INNER_PATH_STRING, "4");
		}
		else
		{
			write_setting->setValue(FILE_SETTING_CATALOG_1_INNER_PATH_STRING, "1");
		}
		write_setting->setValue(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING, ui.lineedit_program_1->text());//������
		write_setting->setValue(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING, ui.lineedit_program_2->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING, ui.lineedit_program_3->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING, ui.lineedit_program_4->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_5_INNER_PATH_STRING, ui.lineedit_program_5->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_6_INNER_PATH_STRING, ui.lineedit_program_6->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_7_INNER_PATH_STRING, ui.lineedit_program_7->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_8_INNER_PATH_STRING, ui.lineedit_program_8->text());
		QString application_name = QApplication::applicationName();//�Ƿ��Զ�����
		QSettings *regedit_settings = new QSettings(REG_RUN, QSettings::NativeFormat);//�޸�ע���
		if (ui.checkBox->isChecked())//�Ƿ��Զ�����
		{
			QString application_path = QApplication::applicationFilePath();//��þ���·��
			regedit_settings->setValue(application_name, application_path.replace("/", "\\"));//д��ע����ע��ע���ʹ�õ�·���ָ�����QT������෴
			write_setting->setValue(FILE_SETTING_CATALOG_3_INNER_PATH_STRING, "1");
		}
		else
		{
			regedit_settings->remove(application_name);//ɾ��ע�����
			write_setting->setValue(FILE_SETTING_CATALOG_3_INNER_PATH_STRING, "0");
		}
		write_setting->setValue(FILE_SETTING_CATALOG_4_INNER_PATH_STRING, ui.comboBox_2->currentText());//����
		write_setting->setValue(FILE_SETTING_CATALOG_5_1_INNER_PATH_STRING, QString::number(ui.spinBox_1->value(), 10));//��ʼλ������
		write_setting->setValue(FILE_SETTING_CATALOG_5_2_INNER_PATH_STRING, QString::number(ui.spinBox_2->value(), 10));
		delete regedit_settings;
		delete write_setting;
		close_window_include_animation();//���ý���
	}

	void ToolsSet::pushButton_choose_1_apply()//ѡ��·����ť
	{
		File dialog;//��������Ǵ�Notepad.exeֱ�����õģ�û�н����κ��޸ģ����File��ĵ��÷�ʽ��Ƚ��鷳
		dialog.setWindowTitle(tr("ѡ�����"));
		QString file_dialog_file_name = QDir::currentPath();//��ǰ·�������ڻ�ñ��򿪵��ļ�·��
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//ȷ���Ƿ���Ҫ�޸�·����ֻ�е��ȷ���Ż��޸�
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//�������ļ�·���ı���
		dialog.set_file_dialog_status_address(change_result_address);//�������Ƿ���Ҫ�޸�·���ı���
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//���빤��·��
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//��ȡ�ļ���Ϣ
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//���ļ�����
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_1->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//��Ϣ��ʾ��
			dialog.setWindowTitle(tr("�ļ����ļ�·��������"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//��ʾ��Ϣ
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else
		{

		}
	}

	void ToolsSet::pushButton_choose_2_apply()//ѡ��·����ť
	{
		File dialog;//��������Ǵ�Notepad.exeֱ�����õģ�û�н����κ��޸ģ����File��ĵ��÷�ʽ��Ƚ��鷳
		dialog.setWindowTitle(tr("ѡ�����"));
		QString file_dialog_file_name = QDir::currentPath();//��ǰ·�������ڻ�ñ��򿪵��ļ�·��
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//ȷ���Ƿ���Ҫ�޸�·����ֻ�е��ȷ���Ż��޸�
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//�������ļ�·���ı���
		dialog.set_file_dialog_status_address(change_result_address);//�������Ƿ���Ҫ�޸�·���ı���
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//���빤��·��
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//��ȡ�ļ���Ϣ
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//���ļ�����
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_2->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//��Ϣ��ʾ��
			dialog.setWindowTitle(tr("�ļ����ļ�·��������"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//��ʾ��Ϣ
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else
		{

		}
	}

	void ToolsSet::pushButton_choose_3_apply()//ѡ��·����ť
	{
		File dialog;//��������Ǵ�Notepad.exeֱ�����õģ�û�н����κ��޸ģ����File��ĵ��÷�ʽ��Ƚ��鷳
		dialog.setWindowTitle(tr("ѡ�����"));
		QString file_dialog_file_name = QDir::currentPath();//��ǰ·�������ڻ�ñ��򿪵��ļ�·��
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//ȷ���Ƿ���Ҫ�޸�·����ֻ�е��ȷ���Ż��޸�
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//�������ļ�·���ı���
		dialog.set_file_dialog_status_address(change_result_address);//�������Ƿ���Ҫ�޸�·���ı���
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//���빤��·��
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//��ȡ�ļ���Ϣ
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//���ļ�����
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_3->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//��Ϣ��ʾ��
			dialog.setWindowTitle(tr("�ļ����ļ�·��������"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//��ʾ��Ϣ
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else
		{

		}
	}

	void ToolsSet::pushButton_choose_4_apply()//ѡ��·����ť
	{
		File dialog;//��������Ǵ�Notepad.exeֱ�����õģ�û�н����κ��޸ģ����File��ĵ��÷�ʽ��Ƚ��鷳
		dialog.setWindowTitle(tr("ѡ�����"));
		QString file_dialog_file_name = QDir::currentPath();//��ǰ·�������ڻ�ñ��򿪵��ļ�·��
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//ȷ���Ƿ���Ҫ�޸�·����ֻ�е��ȷ���Ż��޸�
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//�������ļ�·���ı���
		dialog.set_file_dialog_status_address(change_result_address);//�������Ƿ���Ҫ�޸�·���ı���
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//���빤��·��
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//��ȡ�ļ���Ϣ
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//���ļ�����
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_4->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//��Ϣ��ʾ��
			dialog.setWindowTitle(tr("�ļ����ļ�·��������"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//��ʾ��Ϣ
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else
		{

		}
	}

	void ToolsSet::pushButton_choose_5_apply()//ѡ��·����ť
	{
		File dialog;//��������Ǵ�Notepad.exeֱ�����õģ�û�н����κ��޸ģ����File��ĵ��÷�ʽ��Ƚ��鷳
		dialog.setWindowTitle(tr("ѡ�����"));
		QString file_dialog_file_name = QDir::currentPath();//��ǰ·�������ڻ�ñ��򿪵��ļ�·��
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//ȷ���Ƿ���Ҫ�޸�·����ֻ�е��ȷ���Ż��޸�
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//�������ļ�·���ı���
		dialog.set_file_dialog_status_address(change_result_address);//�������Ƿ���Ҫ�޸�·���ı���
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//���빤��·��
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//��ȡ�ļ���Ϣ
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//���ļ�����
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_5->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//��Ϣ��ʾ��
			dialog.setWindowTitle(tr("�ļ����ļ�·��������"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//��ʾ��Ϣ
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else
		{

		}
	}

	void ToolsSet::pushButton_choose_6_apply()//ѡ��·����ť
	{
		File dialog;//��������Ǵ�Notepad.exeֱ�����õģ�û�н����κ��޸ģ����File��ĵ��÷�ʽ��Ƚ��鷳
		dialog.setWindowTitle(tr("ѡ�����"));
		QString file_dialog_file_name = QDir::currentPath();//��ǰ·�������ڻ�ñ��򿪵��ļ�·��
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//ȷ���Ƿ���Ҫ�޸�·����ֻ�е��ȷ���Ż��޸�
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//�������ļ�·���ı���
		dialog.set_file_dialog_status_address(change_result_address);//�������Ƿ���Ҫ�޸�·���ı���
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//���빤��·��
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//��ȡ�ļ���Ϣ
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//���ļ�����
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_6->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//��Ϣ��ʾ��
			dialog.setWindowTitle(tr("�ļ����ļ�·��������"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//��ʾ��Ϣ
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else
		{

		}
	}

	void ToolsSet::pushButton_choose_7_apply()//ѡ��·����ť
	{
		File dialog;//��������Ǵ�Notepad.exeֱ�����õģ�û�н����κ��޸ģ����File��ĵ��÷�ʽ��Ƚ��鷳
		dialog.setWindowTitle(tr("ѡ�����"));
		QString file_dialog_file_name = QDir::currentPath();//��ǰ·�������ڻ�ñ��򿪵��ļ�·��
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//ȷ���Ƿ���Ҫ�޸�·����ֻ�е��ȷ���Ż��޸�
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//�������ļ�·���ı���
		dialog.set_file_dialog_status_address(change_result_address);//�������Ƿ���Ҫ�޸�·���ı���
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//���빤��·��
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//��ȡ�ļ���Ϣ
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//���ļ�����
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_7->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//��Ϣ��ʾ��
			dialog.setWindowTitle(tr("�ļ����ļ�·��������"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//��ʾ��Ϣ
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else
		{

		}
	}

	void ToolsSet::pushButton_choose_8_apply()//ѡ��·����ť
	{
		File dialog;//��������Ǵ�Notepad.exeֱ�����õģ�û�н����κ��޸ģ����File��ĵ��÷�ʽ��Ƚ��鷳
		dialog.setWindowTitle(tr("ѡ�����"));
		QString file_dialog_file_name = QDir::currentPath();//��ǰ·�������ڻ�ñ��򿪵��ļ�·��
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//ȷ���Ƿ���Ҫ�޸�·����ֻ�е��ȷ���Ż��޸�
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//�������ļ�·���ı���
		dialog.set_file_dialog_status_address(change_result_address);//�������Ƿ���Ҫ�޸�·���ı���
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//���빤��·��
		dialog.exec();
		QFileInfo file_information(file_dialog_file_name);//��ȡ�ļ���Ϣ
		if ((file_information.isDir() || file_information.isFile()) && *change_result_address)//���ļ�����
		{
			file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));
			ui.lineedit_program_8->setText(file_dialog_file_name);
		}
		else if (*change_result_address)
		{
			Help dialog;//��Ϣ��ʾ��
			dialog.setWindowTitle(tr("�ļ����ļ�·��������"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//��ʾ��Ϣ
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else
		{

		}
	}

	void ToolsSet::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

	void ToolsSet::pushButton_choose_9_apply()//���·��
	{
		ui.lineedit_program_1->setText("null");
	}

	void ToolsSet::pushButton_choose_10_apply()//���·��
	{
		ui.lineedit_program_2->setText("null");
	}

	void ToolsSet::pushButton_choose_11_apply()//���·��
	{
		ui.lineedit_program_3->setText("null");
	}

	void ToolsSet::pushButton_choose_12_apply()//���·��
	{
		ui.lineedit_program_4->setText("null");
	}

	void ToolsSet::pushButton_choose_13_apply()//���·��
	{
		ui.lineedit_program_5->setText("null");
	}

	void ToolsSet::pushButton_choose_14_apply()//���·��
	{
		ui.lineedit_program_6->setText("null");
	}

	void ToolsSet::pushButton_choose_15_apply()//���·��
	{
		ui.lineedit_program_7->setText("null");
	}

	void ToolsSet::pushButton_choose_16_apply()//���·��
	{
		ui.lineedit_program_8->setText("null");
	}
}

