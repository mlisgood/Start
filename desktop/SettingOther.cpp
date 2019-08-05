#include "define.h"

namespace rem
{

	//��������������
	SettingOther::SettingOther(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�

		//����ͼƬ��Ϊ���ڱ���
		main_picture.load(DIALOG_SETTING_OTHER_BACKGROUND_PICTURE_PATH_STRING);
		resize(main_picture.size());//���ڴ�С��ΪͼƬ��С

		//���ؽ���
		ui.setupUi(this);

		//����������ɫ
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(232, 114, 162, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(232, 114, 162, 255));
		text_palette.setColor(QPalette::WindowText, QColor(232, 114, 162, 255));
		text_palette.setColor(QPalette::Highlight, QColor(232, 114, 162, 64));
		ui.spinBox_main_1->setPalette(text_palette);
		ui.spinBox_main_2->setPalette(text_palette);

		//��ȡԤ�����ݣ��Դ�����ʾ���г�ʼ��
		QSettings *begin_read = new QSettings(FILE_SETTING_STATIC_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		QString temp;//��ȡ·��
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_5_STRING;
		int auto_run_temp = begin_read->value(temp).toInt();
		if (auto_run_temp == 1)
		{
			ui.checkBox_1->setChecked(true);
		}
		else
		{
			ui.checkBox_1->setChecked(false);
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_1_STRING;
		int is_hide_temp= begin_read->value(temp).toInt();
		if (is_hide_temp == 1)
		{
			ui.checkBox_2->setChecked(true);
		}
		else
		{
			ui.checkBox_2->setChecked(false);
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_2_STRING;
		int time_interval_temp = begin_read->value(temp).toInt();
		ui.spinBox_main_1->setValue(time_interval_temp);
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_4_STRING;
		int transparent_temp = begin_read->value(temp).toInt();
		ui.spinBox_main_2->setValue(transparent_temp);
		delete begin_read;

		//�źź���
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//������Ч
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//ȡ������

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}

	SettingOther::~SettingOther()
	{

	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void SettingOther::mousePressEvent(QMouseEvent *event)
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
	void SettingOther::mouseMoveEvent(QMouseEvent *event)
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
	void SettingOther::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void SettingOther::keyPressEvent(QKeyEvent *event)
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

	void SettingOther::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//��ͼ��Ϊ���ڱ���
	}

	//�ۺ���
	void SettingOther::set_apply()//������Ч
	{

		//д��ini�ļ�
		QSettings *write_setting = new QSettings(FILE_SETTING_STATIC_PATH_STRING, QSettings::IniFormat);
		QString temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_5_STRING;
		if (ui.checkBox_1->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_1_STRING;
		if (ui.checkBox_2->isChecked())
		{
			write_setting->setValue(temp, "1");
		}
		else
		{
			write_setting->setValue(temp, "0");
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_2_STRING;
		write_setting->setValue(temp, ui.spinBox_main_1->value());
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_4_STRING;
		write_setting->setValue(temp, ui.spinBox_main_2->value());
		delete write_setting;
		QString application_name = QApplication::applicationName();//�����������ʱ����Ƿ񿪻��Զ�����
		QSettings *regedit_settings_begin = new QSettings(REG_RUN, QSettings::NativeFormat);//�޸�ע���
		if (ui.checkBox_1->isChecked())//�Ƿ��Զ�����
		{
			QString application_path = QApplication::applicationFilePath();//��þ���·��
			regedit_settings_begin->setValue(application_name, application_path.replace("/", "\\"));//д��ע����ע��ע���ʹ�õ�·���ָ�����QT������෴
		}
		else
		{
			regedit_settings_begin->remove(application_name);//ɾ��ע�����
		}
		close_window_include_animation();//���ý���
	}

	void SettingOther::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

