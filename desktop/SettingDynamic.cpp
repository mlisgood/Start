#include "define.h"

namespace rem
{

	//��������������
	SettingDynamic::SettingDynamic(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�

		//����ͼƬ��Ϊ���ڱ���
		main_picture.load(DIALOG_SETTING_DYNAMIC_BACKGROUND_PICTURE_PATH_STRING);
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
		ui.spinBox_cocoa_1->setPalette(text_palette);
		ui.spinBox_cocoa_2->setPalette(text_palette);
		ui.spinBox_chino_1->setPalette(text_palette);
		ui.spinBox_chino_2->setPalette(text_palette);
		ui.spinBox_rize_1->setPalette(text_palette);
		ui.spinBox_rize_2->setPalette(text_palette);
		ui.spinBox_syaro_1->setPalette(text_palette);
		ui.spinBox_syaro_2->setPalette(text_palette);
		ui.spinBox_chiya_1->setPalette(text_palette);
		ui.spinBox_chiya_2->setPalette(text_palette);
		ui.spinBox_maya_1->setPalette(text_palette);
		ui.spinBox_maya_2->setPalette(text_palette);
		ui.spinBox_megu_1->setPalette(text_palette);
		ui.spinBox_megu_2->setPalette(text_palette);


		//��ȡԤ�����ݣ��Դ�����ʾ���г�ʼ��
		QSettings *begin_read = new QSettings(FILE_SETTING_DYNAMIC_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		int position[WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER + 1][2];//λ��
		position[0][0] = begin_read->value(FILE_SETTING_DYNAMIC_CATALOG_1_1_INNER_PATH_STRING).toInt();
		position[0][1] = begin_read->value(FILE_SETTING_DYNAMIC_CATALOG_1_2_INNER_PATH_STRING).toInt();
		QString temp;//��ʱ�洢·��
		for (int index = 1; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER + 1; index++)
		{
			temp = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;
			temp += QString::number(index - 1, 10);
			temp += FILE_SETTING_DYNAMIC_CATALOG_2_1_BACK_INNER_PATH_STRING;
			position[index][0] = begin_read->value(temp).toInt();
			temp = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;
			temp += QString::number(index - 1, 10);
			temp += FILE_SETTING_DYNAMIC_CATALOG_2_2_BACK_INNER_PATH_STRING;
			position[index][1] = begin_read->value(temp).toInt();
		}
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER + 1; index++)
		{
			if (position[index][0] < 0)
			{
				position[index][0] = 0;
			}
			else
			{

			}
			if (position[index][1] < 0)
			{
				position[index][1] = 0;
			}
			else
			{

			}
		}
		delete begin_read;

		//���ý���
		ui.spinBox_main_1->setValue(position[0][0]);
		ui.spinBox_main_2->setValue(position[0][1]);
		ui.spinBox_cocoa_1->setValue(position[1][0]);
		ui.spinBox_cocoa_2->setValue(position[1][1]);
		ui.spinBox_chino_1->setValue(position[2][0]);
		ui.spinBox_chino_2->setValue(position[2][1]);
		ui.spinBox_rize_1->setValue(position[3][0]);
		ui.spinBox_rize_2->setValue(position[3][1]);
		ui.spinBox_syaro_1->setValue(position[4][0]);
		ui.spinBox_syaro_2->setValue(position[4][1]);
		ui.spinBox_chiya_1->setValue(position[5][0]);
		ui.spinBox_chiya_2->setValue(position[5][1]);
		ui.spinBox_maya_1->setValue(position[6][0]);
		ui.spinBox_maya_2->setValue(position[6][1]);
		ui.spinBox_megu_1->setValue(position[7][0]);
		ui.spinBox_megu_2->setValue(position[7][1]);

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

	SettingDynamic::~SettingDynamic()
	{

	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void SettingDynamic::mousePressEvent(QMouseEvent *event)
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
	void SettingDynamic::mouseMoveEvent(QMouseEvent *event)
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
	void SettingDynamic::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void SettingDynamic::keyPressEvent(QKeyEvent *event)
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

	void SettingDynamic::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//��ͼ��Ϊ���ڱ���
	}

	//�ۺ���
	void SettingDynamic::set_apply()//������Ч
	{

		//д��ini�ļ�
		QSettings *write_setting = new QSettings(FILE_SETTING_DYNAMIC_PATH_STRING, QSettings::IniFormat);
		int position_temp[WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER + 1][2];
		position_temp[0][0] = ui.spinBox_main_1->value();
		position_temp[0][1] = ui.spinBox_main_2->value();
		position_temp[1][0] = ui.spinBox_cocoa_1->value();
		position_temp[1][1] = ui.spinBox_cocoa_2->value();
		position_temp[2][0] = ui.spinBox_chino_1->value();
		position_temp[2][1] = ui.spinBox_chino_2->value();
		position_temp[3][0] = ui.spinBox_rize_1->value();
		position_temp[3][1] = ui.spinBox_rize_2->value();
		position_temp[4][0] = ui.spinBox_syaro_1->value();
		position_temp[4][1] = ui.spinBox_syaro_2->value();
		position_temp[5][0] = ui.spinBox_chiya_1->value();
		position_temp[5][1] = ui.spinBox_chiya_2->value();
		position_temp[6][0] = ui.spinBox_maya_1->value();
		position_temp[6][1] = ui.spinBox_maya_2->value();
		position_temp[7][0] = ui.spinBox_megu_1->value();
		position_temp[7][1] = ui.spinBox_megu_2->value();
		write_setting->setValue(FILE_SETTING_DYNAMIC_CATALOG_1_1_INNER_PATH_STRING, QString::number(position_temp[0][0], 10));
		write_setting->setValue(FILE_SETTING_DYNAMIC_CATALOG_1_2_INNER_PATH_STRING, QString::number(position_temp[0][1], 10));
		QString temp;//��ʱ�洢·��
		for (int index = 1; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER + 1; index++)
		{
			temp = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_DYNAMIC_CATALOG_2_1_BACK_INNER_PATH_STRING;
			write_setting->setValue(temp, QString::number(position_temp[index][0], 10));
			temp = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_DYNAMIC_CATALOG_2_2_BACK_INNER_PATH_STRING;
			write_setting->setValue(temp, QString::number(position_temp[index][1], 10));
		}
		delete write_setting;
		close_window_include_animation();//���ý���
	}

	void SettingDynamic::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

