#include "define.h"

namespace rem
{

	//��������������
	Setting::Setting(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�

		//����ͼƬ��Ϊ���ڱ���
		main_picture.load(DIALOG_SETTING_STATIC_BACKGROUND_PICTURE_PATH_STRING);
		resize(main_picture.size());//���ڴ�С��ΪͼƬ��С

		//�������ͼƬ
		QString temp_picture_string;
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER; index++)
		{
			temp_picture_string = DIALOG_SETTING_WIDGET_BACKGROUND_PICTURE_PATH_FRONT_STRING;
			temp_picture_string += QString::number(index, 10);
			temp_picture_string += DIALOG_SETTING_WIDGET_BACKGROUND_PICTURE_PATH_BACK_STRING;
			widget_picture[index].load(temp_picture_string);
		}

		//���ؽ���
		ui.setupUi(this);

		//����������ɫ
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(232, 114, 162, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(232, 114, 162, 255));
		text_palette.setColor(QPalette::WindowText, QColor(232, 114, 162, 255));
		text_palette.setColor(QPalette::Highlight, QColor(232, 114, 162, 64));
		ui.lineedit_cocoa->setPalette(text_palette);
		ui.lineedit_chino->setPalette(text_palette);
		ui.lineedit_rize->setPalette(text_palette);
		ui.lineedit_syaro->setPalette(text_palette);
		ui.lineedit_chiya->setPalette(text_palette);
		ui.lineedit_maya->setPalette(text_palette);
		ui.lineedit_megu->setPalette(text_palette);

		//��ȡԤ�����ݣ��Դ�����ʾ���г�ʼ��
		QSettings *begin_read = new QSettings(FILE_SETTING_STATIC_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		bool check_box_bool[WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER][2];//checkbox����
		QString lineedit_string[WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER];//lineedit����
		QString temp;//��ȡ·��
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER; index++)
		{
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
			int temp_bool = begin_read->value(temp).toInt();
			if (temp_bool == 1)
			{
				check_box_bool[index][0] = true;
			}
			else
			{
				check_box_bool[index][0] = false;
			}
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
			temp_bool = begin_read->value(temp).toInt();
			if (temp_bool == 1)
			{
				check_box_bool[index][1] = true;
			}
			else
			{
				check_box_bool[index][1] = false;
			}
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_7_STRING;
			lineedit_string[index] = begin_read->value(temp).toString();
			if (lineedit_string[index].length() == 0)
			{
				lineedit_string[index] = DIALOG_SETTING_PATH_DEFAULT_STRING;
			}
			else
			{

			}
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_4_STRING;
			picture_digit[index] = begin_read->value(temp).toInt();
			if (picture_digit[index] < 0)
			{
				picture_digit[index] = 0;
			}
			else
			{

			}
		}
		delete begin_read;

		//���ý���
		if (check_box_bool[0][0])
		{
			ui.checkBox_cocoa_1->setChecked(true);
		}
		else
		{
			ui.checkBox_cocoa_1->setChecked(false);
		}
		if (check_box_bool[0][1])
		{
			ui.checkBox_cocoa_2->setChecked(true);
		}
		else
		{
			ui.checkBox_cocoa_2->setChecked(false);
		}
		if (check_box_bool[1][0])
		{
			ui.checkBox_chino_1->setChecked(true);
		}
		else
		{
			ui.checkBox_chino_1->setChecked(false);
		}
		if (check_box_bool[1][1])
		{
			ui.checkBox_chino_2->setChecked(true);
		}
		else
		{
			ui.checkBox_chino_2->setChecked(false);
		}
		if (check_box_bool[2][0])
		{
			ui.checkBox_rize_1->setChecked(true);
		}
		else
		{
			ui.checkBox_rize_1->setChecked(false);
		}
		if (check_box_bool[2][1])
		{
			ui.checkBox_rize_2->setChecked(true);
		}
		else
		{
			ui.checkBox_rize_2->setChecked(false);
		}
		if (check_box_bool[3][0])
		{
			ui.checkBox_syaro_1->setChecked(true);
		}
		else
		{
			ui.checkBox_syaro_1->setChecked(false);
		}
		if (check_box_bool[3][1])
		{
			ui.checkBox_syaro_2->setChecked(true);
		}
		else
		{
			ui.checkBox_syaro_2->setChecked(false);
		}
		if (check_box_bool[4][0])
		{
			ui.checkBox_chiya_1->setChecked(true);
		}
		else
		{
			ui.checkBox_chiya_1->setChecked(false);
		}
		if (check_box_bool[4][1])
		{
			ui.checkBox_chiya_2->setChecked(true);
		}
		else
		{
			ui.checkBox_chiya_2->setChecked(false);
		}
		if (check_box_bool[5][0])
		{
			ui.checkBox_maya_1->setChecked(true);
		}
		else
		{
			ui.checkBox_maya_1->setChecked(false);
		}
		if (check_box_bool[5][1])
		{
			ui.checkBox_maya_2->setChecked(true);
		}
		else
		{
			ui.checkBox_maya_2->setChecked(false);
		}
		if (check_box_bool[6][0])
		{
			ui.checkBox_megu_1->setChecked(true);
		}
		else
		{
			ui.checkBox_megu_1->setChecked(false);
		}
		if (check_box_bool[6][1])
		{
			ui.checkBox_megu_2->setChecked(true);
		}
		else
		{
			ui.checkBox_megu_2->setChecked(false);
		}
		ui.lineedit_cocoa->setText(lineedit_string[0]);
		ui.lineedit_chino->setText(lineedit_string[1]);
		ui.lineedit_rize->setText(lineedit_string[2]);
		ui.lineedit_syaro->setText(lineedit_string[3]);
		ui.lineedit_chiya->setText(lineedit_string[4]);
		ui.lineedit_maya->setText(lineedit_string[5]);
		ui.lineedit_megu->setText(lineedit_string[6]);


		//�źź���
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//������Ч
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//ȡ������
		connect(ui.pushButton_cocoa_1, SIGNAL(clicked()), this, SLOT(pushButton_select_1()));//ѡ��·����ť
		connect(ui.pushButton_chino_1, SIGNAL(clicked()), this, SLOT(pushButton_select_2()));
		connect(ui.pushButton_rize_1, SIGNAL(clicked()), this, SLOT(pushButton_select_3()));
		connect(ui.pushButton_syaro_1, SIGNAL(clicked()), this, SLOT(pushButton_select_4()));
		connect(ui.pushButton_chiya_1, SIGNAL(clicked()), this, SLOT(pushButton_select_5()));
		connect(ui.pushButton_maya_1, SIGNAL(clicked()), this, SLOT(pushButton_select_6()));
		connect(ui.pushButton_megu_1, SIGNAL(clicked()), this, SLOT(pushButton_select_7()));
		connect(ui.pushButton_cocoa_2, SIGNAL(clicked()), this, SLOT(pushButton_delete_1()));//ɾ��·����ť
		connect(ui.pushButton_chino_2, SIGNAL(clicked()), this, SLOT(pushButton_delete_2()));
		connect(ui.pushButton_rize_2, SIGNAL(clicked()), this, SLOT(pushButton_delete_3()));
		connect(ui.pushButton_syaro_2, SIGNAL(clicked()), this, SLOT(pushButton_delete_4()));
		connect(ui.pushButton_chiya_2, SIGNAL(clicked()), this, SLOT(pushButton_delete_5()));
		connect(ui.pushButton_maya_2, SIGNAL(clicked()), this, SLOT(pushButton_delete_6()));
		connect(ui.pushButton_megu_2, SIGNAL(clicked()), this, SLOT(pushButton_delete_7()));
		connect(ui.pushButton_t_cocoa_1, SIGNAL(clicked()), this, SLOT(pushButton_transparent_down_1()));//͸���ȼ��ٰ�ť
		connect(ui.pushButton_t_chino_1, SIGNAL(clicked()), this, SLOT(pushButton_transparent_down_2()));
		connect(ui.pushButton_t_rize_1, SIGNAL(clicked()), this, SLOT(pushButton_transparent_down_3()));
		connect(ui.pushButton_t_syaro_1, SIGNAL(clicked()), this, SLOT(pushButton_transparent_down_4()));
		connect(ui.pushButton_t_chiya_1, SIGNAL(clicked()), this, SLOT(pushButton_transparent_down_5()));
		connect(ui.pushButton_t_maya_1, SIGNAL(clicked()), this, SLOT(pushButton_transparent_down_6()));
		connect(ui.pushButton_t_megu_1, SIGNAL(clicked()), this, SLOT(pushButton_transparent_down_7()));
		connect(ui.pushButton_t_cocoa_2, SIGNAL(clicked()), this, SLOT(pushButton_transparent_up_1()));//͸�������Ӱ�ť
		connect(ui.pushButton_t_chino_2, SIGNAL(clicked()), this, SLOT(pushButton_transparent_up_2()));
		connect(ui.pushButton_t_rize_2, SIGNAL(clicked()), this, SLOT(pushButton_transparent_up_3()));
		connect(ui.pushButton_t_syaro_2, SIGNAL(clicked()), this, SLOT(pushButton_transparent_up_4()));
		connect(ui.pushButton_t_chiya_2, SIGNAL(clicked()), this, SLOT(pushButton_transparent_up_5()));
		connect(ui.pushButton_t_maya_2, SIGNAL(clicked()), this, SLOT(pushButton_transparent_up_6()));
		connect(ui.pushButton_t_megu_2, SIGNAL(clicked()), this, SLOT(pushButton_transparent_up_7()));

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}

	Setting::~Setting()
	{

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
		else
		{

		}
	}
	//�������������£����ƶ�����λ��
	void Setting::mouseMoveEvent(QMouseEvent *event)
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
	void Setting::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
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
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//��ͼ��Ϊ���ڱ���
		painter.setOpacity((double)picture_digit[0] / 10);
		painter.drawPixmap(ui.label_0->x(), ui.label_0->y(), widget_picture[0]);//��ͼ��Ϊ���ڱ���
		painter.setOpacity((double)picture_digit[1] / 10);
		painter.drawPixmap(ui.label_1->x(), ui.label_1->y(), widget_picture[1]);
		painter.setOpacity((double)picture_digit[2] / 10);
		painter.drawPixmap(ui.label_2->x(), ui.label_2->y(), widget_picture[2]);
		painter.setOpacity((double)picture_digit[3] / 10);
		painter.drawPixmap(ui.label_3->x(), ui.label_3->y(), widget_picture[3]);
		painter.setOpacity((double)picture_digit[4] / 10);
		painter.drawPixmap(ui.label_4->x(), ui.label_4->y(), widget_picture[4]);
		painter.setOpacity((double)picture_digit[5] / 10);
		painter.drawPixmap(ui.label_5->x(), ui.label_5->y(), widget_picture[5]);
		painter.setOpacity((double)picture_digit[6] / 10);
		painter.drawPixmap(ui.label_6->x(), ui.label_6->y(), widget_picture[6]);
	}

	//�ۺ���
	void Setting::set_apply()//������Ч
	{

		//д��ini�ļ�
		QSettings *write_setting = new QSettings(FILE_SETTING_STATIC_PATH_STRING, QSettings::IniFormat);
		QString temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(0, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		if (ui.checkBox_cocoa_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(1, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		if (ui.checkBox_chino_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(2, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		if (ui.checkBox_rize_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(3, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		if (ui.checkBox_syaro_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(4, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		if (ui.checkBox_chiya_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(5, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		if (ui.checkBox_maya_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(6, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		if (ui.checkBox_megu_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(0, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		if (ui.checkBox_cocoa_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(1, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		if (ui.checkBox_chino_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(2, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		if (ui.checkBox_rize_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(3, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		if (ui.checkBox_syaro_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(4, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		if (ui.checkBox_chiya_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(5, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		if (ui.checkBox_maya_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(6, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		if (ui.checkBox_megu_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		QString transform_string[7];
		transform_string[0] = ui.lineedit_cocoa->text();
		transform_string[1] = ui.lineedit_chino->text();
		transform_string[2] = ui.lineedit_rize->text();
		transform_string[3] = ui.lineedit_syaro->text();
		transform_string[4] = ui.lineedit_chiya->text();
		transform_string[5] = ui.lineedit_maya->text();
		transform_string[6] = ui.lineedit_megu->text();
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER; index++)
		{
			if (transform_string[index].length() == 0)
			{
				transform_string[index] = DIALOG_SETTING_PATH_DEFAULT_STRING;
			}
			else
			{

			}
		}
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER; index++)
		{
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_7_STRING;
			write_setting->setValue(temp, transform_string[index]);
		}
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER; index++)
		{
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_4_STRING;
			write_setting->setValue(temp, QString::number(picture_digit[index], 10));
		}
		delete write_setting;
		close_window_include_animation();//���ý���
	}

	void Setting::pushButton_select_1()//ѡ��·����ť
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
			ui.lineedit_cocoa->setText(file_dialog_file_name);
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

	void Setting::pushButton_select_2()//ѡ��·����ť
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
			ui.lineedit_chino->setText(file_dialog_file_name);
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

	void Setting::pushButton_select_3()//ѡ��·����ť
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
			ui.lineedit_rize->setText(file_dialog_file_name);
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

	void Setting::pushButton_select_4()//ѡ��·����ť
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
			ui.lineedit_syaro->setText(file_dialog_file_name);
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

	void Setting::pushButton_select_5()//ѡ��·����ť
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
			ui.lineedit_chiya->setText(file_dialog_file_name);
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

	void Setting::pushButton_select_6()//ѡ��·����ť
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
			ui.lineedit_maya->setText(file_dialog_file_name);
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

	void Setting::pushButton_select_7()//ѡ��·����ť
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
			ui.lineedit_megu->setText(file_dialog_file_name);
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

	void Setting::pushButton_delete_1()//���·��
	{
		ui.lineedit_cocoa->setText(DIALOG_SETTING_PATH_DEFAULT_STRING);
	}

	void Setting::pushButton_delete_2()//���·��
	{
		ui.lineedit_chino->setText(DIALOG_SETTING_PATH_DEFAULT_STRING);
	}

	void Setting::pushButton_delete_3()//���·��
	{
		ui.lineedit_rize->setText(DIALOG_SETTING_PATH_DEFAULT_STRING);
	}

	void Setting::pushButton_delete_4()//���·��
	{
		ui.lineedit_syaro->setText(DIALOG_SETTING_PATH_DEFAULT_STRING);
	}

	void Setting::pushButton_delete_5()//���·��
	{
		ui.lineedit_chiya->setText(DIALOG_SETTING_PATH_DEFAULT_STRING);
	}

	void Setting::pushButton_delete_6()//���·��
	{
		ui.lineedit_maya->setText(DIALOG_SETTING_PATH_DEFAULT_STRING);
	}

	void Setting::pushButton_delete_7()//���·��
	{
		ui.lineedit_megu->setText(DIALOG_SETTING_PATH_DEFAULT_STRING);
	}

	void Setting::pushButton_transparent_down_1()//͸���ȼ���
	{
		if (picture_digit[0] > DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER)
		{
			picture_digit[0] -= DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[0] = DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_down_2()//͸���ȼ���
	{
		if (picture_digit[1] > DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER)
		{
			picture_digit[1] -= DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[1] = DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_down_3()//͸���ȼ���
	{
		if (picture_digit[2] > DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER)
		{
			picture_digit[2] -= DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[2] = DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_down_4()//͸���ȼ���
	{
		if (picture_digit[3] > DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER)
		{
			picture_digit[3] -= DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[3] = DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_down_5()//͸���ȼ���
	{
		if (picture_digit[4] > DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER)
		{
			picture_digit[4] -= DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[4] = DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER;
		}
		repaint();
	}


	void Setting::pushButton_transparent_down_6()//͸���ȼ���
	{
		if (picture_digit[5] > DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER)
		{
			picture_digit[5] -= DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[5] = DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_down_7()//͸���ȼ���
	{
		if (picture_digit[6] > DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER)
		{
			picture_digit[6] -= DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[6] = DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_up_1()//͸��������
	{
		if (picture_digit[0] < DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER)
		{
			picture_digit[0] += DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[0] = DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_up_2()//͸��������
	{
		if (picture_digit[1] < DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER)
		{
			picture_digit[1] += DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[1] = DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_up_3()//͸��������
	{
		if (picture_digit[2] < DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER)
		{
			picture_digit[2] += DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[2] = DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_up_4()//͸��������
	{
		if (picture_digit[3] < DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER)
		{
			picture_digit[3] += DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[3] = DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_up_5()//͸��������
	{
		if (picture_digit[4] < DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER)
		{
			picture_digit[4] += DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[4] = DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER;
		}
		repaint();
	}


	void Setting::pushButton_transparent_up_6()//͸��������
	{
		if (picture_digit[5] < DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER)
		{
			picture_digit[5] += DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[5] = DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER;
		}
		repaint();
	}

	void Setting::pushButton_transparent_up_7()//͸��������
	{
		if (picture_digit[6] < DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER)
		{
			picture_digit[6] += DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER;
		}
		else
		{
			picture_digit[6] = DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER;
		}
		repaint();
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

