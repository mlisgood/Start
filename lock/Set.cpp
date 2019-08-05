#include "define.h"

namespace rem
{

	//ʹ�ñ�׼�����ռ�
	using std::string;
	using std::wstring;
	using std::ifstream;
	using std::ofstream;
	using std::fstream;
	using std::ios_base;

	//��������������
	Set::Set(QWidget *parent) : QDialog(parent)
	{
		
		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�

		//����ͼƬ��Ϊ���ڱ���
		main_picture.load(DIALOG_BACKGROUND_SET_PATH_STRING);
		resize(main_picture.size());//���ڴ�С��ΪͼƬ��С

		//���ؽ���
		ui.setupUi(this);
		
		//���ð�ť��ʽ
		ui.pushButton_1->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_7.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_7.png);}");
		ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_7.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_7.png);}");
		ui.pushButton_3->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_7.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_7.png);}");
		ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_8.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_8.png);}");
		ui.pushButton_5->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_7.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_7.png);}");
		ui.pushButton_6->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_9.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_9.png);}");
		ui.pushButton_7->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_10.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_10.png);}");
		ui.pushButton_8->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_11.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_11.png);}");

		//����������ɫ
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::WindowText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::Highlight, QColor(70, 28, 10, 64));
		ui.lineEdit_1->setPalette(text_palette);
		ui.lineEdit_2->setPalette(text_palette);
		ui.lineEdit_3->setPalette(text_palette);
		ui.lineEdit_4->setPalette(text_palette);
		ui.lineEdit_5->setPalette(text_palette);
		ui.lineEdit_6->setPalette(text_palette);
		ui.lineEdit_7->setPalette(text_palette);
		ui.lineEdit_8->setPalette(text_palette);
		
		//��ȡԤ�����ݣ��Դ�����ʾ���г�ʼ��
		QSettings *begin_read = new QSettings(FILE_SET_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		QString information_temp[11];//��ȡ��Ҫ��ʾ������
		information_temp[0] = begin_read->value(FILE_SETTING_CATALOG_1_1_INNER_PATH_STRING).toString();//�ļ���·��
		information_temp[1] = begin_read->value(FILE_SETTING_CATALOG_1_2_INNER_PATH_STRING).toString();
		information_temp[2] = begin_read->value(FILE_SETTING_CATALOG_1_3_INNER_PATH_STRING).toString();
		information_temp[3] = begin_read->value(FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING).toString();
		for (int index = 0; index <= 3; index++)//���������ļ���ʧ�����
		{
			if (information_temp[index].length() == 0)
			{
				information_temp[index] = FILE_SETTING_CATALOG_PATH_DEFAULT_STRING;
			}
			else
			{

			}
		}
		ui.lineEdit_5->setText(information_temp[0]);
		ui.lineEdit_6->setText(information_temp[1]);
		ui.lineEdit_7->setText(information_temp[2]);
		ui.lineEdit_8->setText(information_temp[3]);
		information_temp[4] = begin_read->value(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING).toString();//�����ļ���׺
		information_temp[5] = begin_read->value(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING).toString();
		if (information_temp[4].length() == 0)
		{
			information_temp[4] = FILE_SETTING_SUFFIX_LOCK_DEFAULT_STRING;
		}
		else
		{

		}
		if (information_temp[5].length() == 0)
		{
			information_temp[5] = FILE_SETTING_SUFFIX_UNLOCK_DEFAULT_STRING;
		}
		else
		{

		}
		ui.lineEdit_1->setText(information_temp[4]);
		ui.lineEdit_2->setText(information_temp[5]);
		information_temp[6] = begin_read->value(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING).toString();//����ֵ
		information_temp[7] = begin_read->value(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING).toString();
		information_temp[8] = begin_read->value(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING).toString();
		if (information_temp[6] == "0")
		{
			ui.checkBox1->setChecked(false);
		}
		else//˳������û�������ļ������
		{
			ui.checkBox1->setChecked(true);
		}
		if (information_temp[7] == "0")
		{
			ui.checkBox2->setChecked(false);
		}
		else//˳������û�������ļ������
		{
			ui.checkBox2->setChecked(true);
		}
		if (information_temp[8] == "0")
		{
			ui.checkBox3->setChecked(false);
		}
		else//˳������û�������ļ������
		{
			ui.checkBox3->setChecked(true);
		}
		information_temp[9] = begin_read->value(FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING).toString();//��Կ�ļ��ļ���׺
		information_temp[10] = begin_read->value(FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING).toString();
		if (information_temp[9].length() == 0)
		{
			information_temp[9] = FILE_OUTPUT_FILE_KEY_BACK_PATH_STRING;
		}
		else
		{

		}
		if (information_temp[10].length() == 0)
		{
			information_temp[10] = FILE_OUTPUT_FILE_KEY_BINARY_BACK_PATH_STRING;
		}
		else
		{

		}
		ui.lineEdit_3->setText(information_temp[9]);
		ui.lineEdit_4->setText(information_temp[10]);
		delete begin_read;

		//�źź���
		connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(open_path_lock()));//�򿪼����ļ�·��
		connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(open_path_unlock()));//�򿪽����ļ�·��
		connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(open_path_temp()));//����ʱ�ļ�·��
		connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(delete_temp()));//ɾ����ʱ�ļ�
		connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(open_path_history()));//����ʷ�ļ�·��
		connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(delete_history()));//�����ʷ�ļ�
		connect(ui.pushButton_9, SIGNAL(clicked()), this, SLOT(get_path_lock()));//��ü����ļ�·������
		connect(ui.pushButton_10, SIGNAL(clicked()), this, SLOT(get_path_unlock()));//��ý����ļ�·������
		connect(ui.pushButton_11, SIGNAL(clicked()), this, SLOT(get_path_temp()));//�����ʱ�ļ�·������
		connect(ui.pushButton_12, SIGNAL(clicked()), this, SLOT(get_path_history()));//�����ʱ�ļ�·������
		connect(ui.pushButton_7, SIGNAL(clicked()), this, SLOT(set_apply()));//������Ч
		connect(ui.pushButton_8, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//�رմ���

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}

	Set::~Set()
	{

	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void Set::mousePressEvent(QMouseEvent *event)
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
	void Set::mouseMoveEvent(QMouseEvent *event)
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
	void Set::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void Set::keyPressEvent(QKeyEvent *event)
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

	void Set::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//��ͼ��Ϊ���ڱ���
	}

	//�������ܺ���
	bool Set::delete_files(QString path)//ɾ���ļ�����ȫ���ļ����������ļ��С�����Ϊ�ļ���·��
	{
		if (path.isEmpty())//���ַ���
		{
			return false;
		}
		else
		{

		}
		QDir remove_dir(path);//��ö�Ӧ�ļ���·��
		if (!remove_dir.exists())//·��������
		{
			return false;
		}
		else
		{

		}
		remove_dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);//���ù�����
		QFileInfoList file_remove_list = remove_dir.entryInfoList();//��ȡ���е��ļ���Ϣ
		foreach(QFileInfo file, file_remove_list)//�����ļ���Ϣ
		{
			if (file.isFile())//������ļ�����ɾ��
			{
				file.dir().remove(file.fileName());
			}
			else//�������ļ��У���������
			{
				
			}
		}
		return true;
	}

	//�ۺ���
	void Set::open_path_lock()//�򿪼����ļ�·��
	{
		run_path(ui.lineEdit_5->text(), FILE_OUTPUT_FILE_LOCK_FRONT_PATH_STRING);
	}

	void Set::open_path_unlock()//�򿪽����ļ�·��
	{
		run_path(ui.lineEdit_6->text(), FILE_OUTPUT_FILE_UNLOCK_FRONT_PATH_STRING);
	}

	void Set::open_path_temp()//����ʱ�ļ�·��
	{
		run_path(ui.lineEdit_7->text(), FILE_TEMP_FILE_FRONT_PATH_STRING);
	}

	void Set::open_path_history()//����ʷ�ļ�·��
	{
		run_path(ui.lineEdit_8->text(), FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING);
	}

	void Set::get_path_lock()//��ü����ļ�·������
	{
		set_save_path(ui.lineEdit_5);//��ȡ�ļ�·�����޸�label��ʾ
	}

	void Set::get_path_unlock()//��ý����ļ�·������
	{
		set_save_path(ui.lineEdit_6);//��ȡ�ļ�·�����޸�label��ʾ
	}

	void Set::get_path_temp()//�����ʱ�ļ�·������
	{
		set_save_path(ui.lineEdit_7);//��ȡ�ļ�·�����޸�label��ʾ
	}

	void Set::get_path_history()//�����ʷ�ļ�·������
	{
		set_save_path(ui.lineEdit_8);//��ȡ�ļ�·�����޸�label��ʾ
	}

	void Set::delete_temp()//ɾ����ʱ�ļ�
	{
		QString temp_path = ui.lineEdit_7->text();//��ʱ�ļ���·��
		if (temp_path == FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)//Ĭ��·��
		{
			temp_path = FILE_TEMP_FILE_FRONT_PATH_STRING;
		}
		else
		{
			
		}
		if (delete_files(temp_path))//ɾ���ɹ�
		{
			
		}
		else
		{
			Help dialog;//��Ϣ��ʾ��
			dialog.setWindowTitle(tr("�����ˣ�"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_DELETE_FAIL_PATH_STRING);//��ʾ��Ϣ
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
	}

	void Set::delete_history()//�����ʷ�ļ�
	{
		QString full_history_path = ui.lineEdit_8->text();//��ʷ�ļ�·��
		if (full_history_path != FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)
		{
			full_history_path += FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING;
		}
		else
		{
			full_history_path = FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING;
			full_history_path += FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING;//����ֱ����ӡ��ַ��������൱��ָ�룬�����ӻᱨ�������������ָ��
		}
		string full_history_path_string = string((const char *)full_history_path.toLocal8Bit());//QStringתstring
		ofstream keyfile(full_history_path_string, ios_base::out | ios_base::beg);//����ʷ�ļ���Ȼ��ֱ�ӹرգ�����������Զ����ļ��������
		keyfile << "";//���ļ�дһ���յ��ַ���
		keyfile.close();
	}

	void Set::run_path(QString path, QString default_path)//����Ӧ·�����ú�������Ҫ������ں����Ĳ�����Ŀ��������ѡ������壨1����ڲ��������ǳ���Ŀ�꣨2����ڲ���������ֱ�Ӵ򿪡��������ļ�·����Ĭ��·��
	{
		HINSTANCE return_value;//ָ������ֵ
		wstring transform_path;//ָ������ľ���·��
		if (path != FILE_SETTING_CATALOG_PATH_DEFAULT_STRING)//����Ĭ��ֵ
		{
			transform_path = path.toStdWString();//��Qstringת��Ϊwstring������ת�����ᵼ�����룬��Ϊwstring�����֧��Unicode����
		}
		else
		{
			transform_path = default_path.toStdWString();
		}
		return_value = ShellExecute(NULL, L"open", transform_path.c_str(), NULL, NULL, SW_SHOWNORMAL);//�򿪳���
		if (return_value >= (HINSTANCE)0 && return_value <= (HINSTANCE)31)//�޷���ָ������
		{
			Help dialog;//��Ϣ��ʾ��
			dialog.setWindowTitle(tr("�����ˣ�"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_OPEN_PATH_STRING);//��ʾ��Ϣ
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else if (return_value >= (HINSTANCE)32)//�Ѿ��򿪣���������
		{

		}
		else//�����쳣���
		{

		}
	}

	//·����Ϣ��ȡ
	void Set::set_save_path(QLineEdit *lineEdit)//���ļ��򿪽����ȡ·����Ϣ������Ϊ����ʾ��QLineEdit
	{
		File_only_path dialog;//��������Ǵ�Notepad.exe���õģ����÷�ʽ�Ƚ��鷳
		dialog.setWindowTitle(tr("ѡ��·��"));
		QString file_dialog_file_name = QDir::currentPath();//��ǰ·�������ڻ�ñ��򿪵��ļ�·��
		QFileInfo file_information(file_dialog_file_name);//��ȡ�ļ���Ϣ
		if (file_information.isFile())//���ļ�����
		{
			file_dialog_file_name = file_information.path();//ֻȡ�ļ�·��
		}
		else
		{

		}
		QString *file_dialog_file_name_address = &file_dialog_file_name;
		bool change_result = false;//ȷ���Ƿ���Ҫ�޸�·����ֻ�е��ȷ���Ż��޸�
		bool *change_result_address = &change_result;
		dialog.set_file_path_address(file_dialog_file_name_address);//�������ļ�·���ı���
		dialog.set_file_dialog_status_address(change_result_address);//�������Ƿ���Ҫ�޸�·���ı���
		dialog.set_button_save_or_open(0);
		dialog.set_current_path(QDir::currentPath());//���빤��·��
		dialog.exec();
		if (change_result)
		{
			QFileInfo file_information(file_dialog_file_name);//��ȡ�ļ���Ϣ
			if (file_information.isFile())//���ļ�����
			{
				file_dialog_file_name = file_information.absoluteDir().absolutePath();//ֻȡ�ļ�·��
				file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));//����ļ�·��
				lineEdit->setText(file_dialog_file_name);//������ʾ�ı�
			}
			else if(!file_information.isDir())
			{
				Help dialog;//��Ϣ��ʾ��
				dialog.setWindowTitle(tr("�ļ����ļ�·��������"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING);//��ʾ��Ϣ
				dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
			}
			else
			{
				file_dialog_file_name = (file_dialog_file_name).replace(tr("/"), tr("\\"));//����ļ�·��
				lineEdit->setText(file_dialog_file_name);//������ʾ�ı�
			}
		}
		else
		{

		}
	}

	void Set::set_apply()//������Ч
	{

		//д��ini�ļ�
		QSettings *write_setting = new QSettings(FILE_SET_PATH_STRING, QSettings::IniFormat);
		write_setting->setValue(FILE_SETTING_CATALOG_1_1_INNER_PATH_STRING, ui.lineEdit_5->text());
		write_setting->setValue(FILE_SETTING_CATALOG_1_2_INNER_PATH_STRING, ui.lineEdit_6->text());
		write_setting->setValue(FILE_SETTING_CATALOG_1_3_INNER_PATH_STRING, ui.lineEdit_7->text());
		write_setting->setValue(FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING, ui.lineEdit_8->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING, ui.lineEdit_1->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING, ui.lineEdit_2->text());
		if (ui.checkBox1->isChecked())//����QCheckBox�Ƿ񱻹�ѡ��ȷ�������ini�ļ���ֵ
		{
			write_setting->setValue(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING, "1");
		}
		else
		{
			write_setting->setValue(FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING, "0");
		}
		if (ui.checkBox2->isChecked())
		{
			write_setting->setValue(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING, "1");
		}
		else
		{
			write_setting->setValue(FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING, "0");
		}
		if (ui.checkBox3->isChecked())
		{
			write_setting->setValue(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING, "1");
		}
		else
		{
			write_setting->setValue(FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING, "0");
		}
		write_setting->setValue(FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING, ui.lineEdit_3->text());
		write_setting->setValue(FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING, ui.lineEdit_4->text());
		delete write_setting;
		close_window_include_animation();//���ý���
	}

	void Set::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

