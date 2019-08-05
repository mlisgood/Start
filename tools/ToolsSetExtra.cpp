#include "define.h"

namespace rem
{

	//����ȫ�ֱ���
	extern int counter_mutex;

	//��������������
	ToolsSetExtra::ToolsSetExtra(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�

		//����ͼƬ��Ϊ���ڱ���
		main_picture.load(DIALOG_TOOLS_SET_EXTRA_BACKGROUND_PICTURE_PATH_STRING);
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
		ui.comboBox_3->setPalette(text_palette);
		ui.spinBox_1->setPalette(text_palette);
		ui.spinBox_2->setPalette(text_palette);
		ui.spinBox_3->setPalette(text_palette);
		ui.spinBox_4->setPalette(text_palette);
		ui.spinBox_5->setPalette(text_palette);
		

		//ȥ�������Կؼ����Ҽ��˵�
		QList<QScrollBar *> scroll_bar = this->findChildren<QScrollBar *>();//�����޷��ó��淽ʽ���combobox�Ĺ����������ʹ�ø÷�����������ͬ���Ϳؼ������в���
		foreach(QScrollBar *scroll_bar_style_control, scroll_bar)
		{
			scroll_bar_style_control->setContextMenuPolicy(Qt::NoContextMenu);
		}

		//��ȡԤ�����ݣ��Դ�����ʾ���г�ʼ��
		QSettings *begin_read = new QSettings(FILE_SETTING_MAINWINDOW_STYLE_EXTRA_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		QString combobox_index[3];//��ȡcombobox��Ҫ������
		combobox_index[0] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_1_2_INNER_PATH_STRING)).toString();
		combobox_index[1] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_2_3_INNER_PATH_STRING)).toString();
		combobox_index[2] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_2_4_INNER_PATH_STRING)).toString();
		ui.comboBox_1->setCurrentText(combobox_index[0]);//��������
		ui.comboBox_2->setCurrentText(combobox_index[1]);
		ui.comboBox_3->setCurrentText(combobox_index[2]);
		QString spinbox_index[5];//��ȡspinbox��Ҫ������
		spinbox_index[0] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_1_1_INNER_PATH_STRING)).toString();
		spinbox_index[1] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_2_2_INNER_PATH_STRING)).toString();
		spinbox_index[2] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_2_5_INNER_PATH_STRING)).toString();
		spinbox_index[3] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_2_6_INNER_PATH_STRING)).toString();
		spinbox_index[4] = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_2_7_INNER_PATH_STRING)).toString();
		bool temp_transform_status[5];//�ַ���ת��Ϊ�����Ƿ�ɹ�
		int spinbox_index_transform[5];//spinbox��ȡ��ʵ��ת��������
		spinbox_index_transform[0] = spinbox_index[0].toInt(&temp_transform_status[0], 10);//ת��Ϊ����
		spinbox_index_transform[1] = spinbox_index[1].toInt(&temp_transform_status[1], 10);
		spinbox_index_transform[2] = spinbox_index[2].toInt(&temp_transform_status[2], 10);
		spinbox_index_transform[3] = spinbox_index[3].toInt(&temp_transform_status[3], 10);
		spinbox_index_transform[4] = spinbox_index[4].toInt(&temp_transform_status[4], 10);
		if (!temp_transform_status[0])//���������ת��ʧ�ܣ���ǿ�Ƹ�ΪĬ��ֵ
		{
			spinbox_index_transform[0] = 10;
		}
		else
		{

		}
		if (!temp_transform_status[1])
		{
			spinbox_index_transform[1] = 1;
		}
		else
		{

		}
		if (!temp_transform_status[2])
		{
			spinbox_index_transform[2] = 0;
		}
		else
		{

		}
		if (!temp_transform_status[3])
		{
			spinbox_index_transform[3] = 0;
		}
		else
		{

		}
		if (!temp_transform_status[4])
		{
			spinbox_index_transform[4] = 10;
		}
		else
		{

		}
		ui.spinBox_1->setValue(spinbox_index_transform[0]);
		ui.spinBox_2->setValue(spinbox_index_transform[1]);
		ui.spinBox_3->setValue(spinbox_index_transform[2]);
		ui.spinBox_4->setValue(spinbox_index_transform[3]);
		ui.spinBox_5->setValue(spinbox_index_transform[4]);
		QString checkbox_index;//��ȡcheckbox��Ҫ������
		checkbox_index = (begin_read->value(FILE_EXTRA_SETTING_CATALOG_2_1_INNER_PATH_STRING)).toString();
		if (checkbox_index == tr("1"))
		{
			ui.checkBox->setChecked(true);
		}
		else if (checkbox_index == tr("0"))
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

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}

	ToolsSetExtra::~ToolsSetExtra()
	{

	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void ToolsSetExtra::mousePressEvent(QMouseEvent *event)
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
	void ToolsSetExtra::mouseMoveEvent(QMouseEvent *event)
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
	void ToolsSetExtra::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void ToolsSetExtra::keyPressEvent(QKeyEvent *event)
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

	void ToolsSetExtra::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(WINDOW_BACKGROUND_PAINT_START_X_NUMBER, WINDOW_BACKGROUND_PAINT_START_Y_NUMBER, main_picture);//��ͼ��Ϊ���ڱ���
	}

	//�ۺ���
	void ToolsSetExtra::set_apply()//������Ч
	{

		//д��ini�ļ�
		QSettings *write_setting = new QSettings(FILE_SETTING_MAINWINDOW_STYLE_EXTRA_PATH_STRING, QSettings::IniFormat);
		QString combobox_index[3];//д��combobox������
		combobox_index[0] = ui.comboBox_1->currentText();
		combobox_index[1] = ui.comboBox_2->currentText();
		combobox_index[2] = ui.comboBox_3->currentText();
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_1_2_INNER_PATH_STRING, combobox_index[0]);
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_3_INNER_PATH_STRING, combobox_index[1]);
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_4_INNER_PATH_STRING, combobox_index[2]);
		QString spinbox_index[5];//д��spinbox������
		spinbox_index[0] = QString::number(ui.spinBox_1->value(), 10);
		spinbox_index[1] = QString::number(ui.spinBox_2->value(), 10);
		spinbox_index[2] = QString::number(ui.spinBox_3->value(), 10);
		spinbox_index[3] = QString::number(ui.spinBox_4->value(), 10);
		spinbox_index[4] = QString::number(ui.spinBox_5->value(), 10);
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_1_1_INNER_PATH_STRING, spinbox_index[0]);
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_2_INNER_PATH_STRING, spinbox_index[1]);
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_5_INNER_PATH_STRING, spinbox_index[2]);
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_6_INNER_PATH_STRING, spinbox_index[3]);
		write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_7_INNER_PATH_STRING, spinbox_index[4]);
		if (ui.checkBox->isChecked())//д��checkbox������
		{
			write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_1_INNER_PATH_STRING, tr("1"));
		}
		else
		{
			write_setting->setValue(FILE_EXTRA_SETTING_CATALOG_2_1_INNER_PATH_STRING, tr("0"));
		}
		delete write_setting;
		close_window_include_animation();//���ý���
	}

	void ToolsSetExtra::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

