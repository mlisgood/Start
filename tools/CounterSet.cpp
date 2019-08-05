#include "define.h"

namespace rem
{
	
	//����ȫ�ֱ���
	extern int counter_mutex;

	//��������������
	CounterSet::CounterSet(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����					
		counter_mutex--;//����ļ�ʱ�����ڵ���Ŀ����1
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�

		//����ͼƬ��Ϊ���ڱ���
		main_picture.load(DIALOG_COUNTER_SET_BACKGROUND_PICTURE_PATH_STRING);
		resize(main_picture.size());//���ڴ�С��ΪͼƬ��С

		//���ؽ���
		ui.setupUi(this);
		
		//���ص�ѡ�����
		radioButton_type = new QButtonGroup(this);
		radioButton_type->addButton(ui.radioButton_type_1);
		radioButton_type->addButton(ui.radioButton_type_2);
		radioButton_voice = new QButtonGroup(this);
		radioButton_voice->addButton(ui.radioButton_voice_1);
		radioButton_voice->addButton(ui.radioButton_voice_2);
		radioButton_voice->addButton(ui.radioButton_voice_3);
		radioButton_voice->addButton(ui.radioButton_voice_4);
		radioButton_voice->addButton(ui.radioButton_voice_5);
		radioButton_dialog = new QButtonGroup(this);
		radioButton_dialog->addButton(ui.radioButton_dialog_1);
		radioButton_dialog->addButton(ui.radioButton_dialog_2);

		//��ť��ʼ״̬
		ui.radioButton_type_1->setChecked(true);
		ui.radioButton_voice_1->setChecked(true);
		ui.radioButton_dialog_1->setChecked(true);

		//�źź���
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//������Ч
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));//ȡ������

		//����������ɫ
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::WindowText, QColor(70, 28, 10, 255));
		text_palette.setColor(QPalette::Highlight, QColor(70, 28, 10, 64));
		ui.spinBox_hour->setPalette(text_palette);
		ui.spinBox_minute->setPalette(text_palette);
		ui.spinBox_second->setPalette(text_palette);

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}
	CounterSet::~CounterSet()
	{
		counter_mutex++;//��ֹ���˳���ʱ�޷��ٴν���ô���
		delete radioButton_type;
		delete radioButton_voice;
		delete radioButton_dialog;
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void CounterSet::mousePressEvent(QMouseEvent *event)
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
	void CounterSet::mouseMoveEvent(QMouseEvent *event)
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
	void CounterSet::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void CounterSet::keyPressEvent(QKeyEvent *event)
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

	void CounterSet::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(WINDOW_BACKGROUND_PAINT_START_X_NUMBER, WINDOW_BACKGROUND_PAINT_START_Y_NUMBER, main_picture);//��ͼ��Ϊ���ڱ���
	}

	void CounterSet::set_apply()//������Ч
	{
		Counter *dialog = new Counter;//��ʱ�����÷�ģ̬����
		QAbstractButton *radioButton_type_clicked = qobject_cast<QAbstractButton *> (radioButton_type->checkedButton());//ȷ��ÿ�����б�ѡ�еĵ�ѡ�򣬷��ص��Ƕ���
		QAbstractButton *radioButton_voice_clicked = qobject_cast<QAbstractButton *> (radioButton_voice->checkedButton());
		QAbstractButton *radioButton_dialog_clicked = qobject_cast<QAbstractButton *> (radioButton_dialog->checkedButton());
		QString a = radioButton_type_clicked->objectName();
		if (!QString::compare(radioButton_type_clicked->objectName(), "radioButton_type_1", Qt::CaseSensitive))//�ж϶������Ƿ���ȣ����ұȽ�ʱ���ִ�Сд��ע���ַ����Ƚϣ����ʱ���ص�ֵΪ0�����ݵ�ѡ����1������
		{
			dialog->set_setting_information(0, 1);//�������ݣ����ܵ������������ʾ������������ʾ��ѡ�����������ѡ������ţ�Ԫ��ֵ��ʾ��ѡ���鱻ѡ�еĵ�ѡ�����Ż�������ѡ����ֵ
		}
		else if (!QString::compare(radioButton_type_clicked->objectName(), "radioButton_type_2", Qt::CaseSensitive))
		{
			dialog->set_setting_information(0, 2);
		}
		else
		{
			dialog->set_setting_information(0, 1);
		}
		dialog->set_setting_information(1, ui.spinBox_hour->value());//������������ѡ��������
		dialog->set_setting_information(2, ui.spinBox_minute->value());
		dialog->set_setting_information(3, ui.spinBox_second->value());
		if (!QString::compare(radioButton_voice_clicked->objectName(), "radioButton_voice_1", Qt::CaseSensitive))//���ݵ�ѡ����2������
		{
			dialog->set_setting_information(4, 1);
		}
		else if (!QString::compare(radioButton_voice_clicked->objectName(), "radioButton_voice_2", Qt::CaseSensitive))
		{
			dialog->set_setting_information(4, 2);
		}
		else if (!QString::compare(radioButton_voice_clicked->objectName(), "radioButton_voice_3", Qt::CaseSensitive))
		{
			dialog->set_setting_information(4, 3);
		}
		else if (!QString::compare(radioButton_voice_clicked->objectName(), "radioButton_voice_4", Qt::CaseSensitive))
		{
			dialog->set_setting_information(4, 4);
		}
		else if (!QString::compare(radioButton_voice_clicked->objectName(), "radioButton_voice_5", Qt::CaseSensitive))
		{
			dialog->set_setting_information(4, 5);
		}
		else
		{
			dialog->set_setting_information(4, 1);
		}
		if (!QString::compare(radioButton_dialog_clicked->objectName(), "radioButton_dialog_1", Qt::CaseSensitive))//���ݵ�ѡ����3������
		{
			dialog->set_setting_information(5, 1);
		}
		else if (!QString::compare(radioButton_dialog_clicked->objectName(), "radioButton_dialog_2", Qt::CaseSensitive))
		{
			dialog->set_setting_information(5, 2);
		}
		dialog->set_beginning_value();//���ó�ʼֵ
		close_window_include_animation();//������Ϻ�ر����ô��ڲ�������ʱ��
		dialog->setModal(false);//ָ��Ϊ��ģ̬�Ի���
		dialog->show();
	}

	void CounterSet::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

