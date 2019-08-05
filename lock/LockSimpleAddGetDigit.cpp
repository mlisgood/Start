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
	LockSimpleAddGetDigit::LockSimpleAddGetDigit(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����					
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�

		//����ͼƬ��Ϊ���ڱ���
		main_picture.load(DIALOG_BACKGROUND_LOCK_SIMPLE_ADD_GET_DIGIT_PATH_STRING);
		resize(main_picture.size());//���ڴ�С��ΪͼƬ��С

		//���ؽ���
		ui.setupUi(this);

		//�źź���
		connect(ui.pushButton_apply, SIGNAL(clicked()), this, SLOT(set_apply()));//������Ч
		connect(ui.pushButton_list_1, SIGNAL(clicked()), this, SLOT(add_item()));//�����Ŀ
		connect(ui.pushButton_list_4, SIGNAL(clicked()), this, SLOT(edit_item()));//�޸���Ŀ
		connect(ui.pushButton_list_2, SIGNAL(clicked()), this, SLOT(delete_item()));//ɾ����Ŀ
		connect(ui.pushButton_list_3, SIGNAL(clicked()), this, SLOT(delete_all_item()));//ɾ��ȫ����Ŀ
		connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(cancel_apply()));//ȡ������

		//���ð�ť��ʽ
		ui.pushButton_apply->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_10.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_10.png);}");
		ui.pushButton_cancel->setStyleSheet("QPushButton{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_normal_11.png);}""QPushButton:hover{border-image: url(:/icon/mainicon/picture_lock/icon/lock_button_pressed_11.png);}");

		//����������ɫ
		QPalette text_palette;
		text_palette.setColor(QPalette::Text, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::HighlightedText, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::WindowText, QColor(128, 76, 71, 255));
		text_palette.setColor(QPalette::Highlight, QColor(128, 76, 71, 64));
		ui.listWidget_1->setPalette(text_palette);
		ui.spinBox_1->setPalette(text_palette);
		ui.spinBox_2->setPalette(text_palette);

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
		}
		else//����ʧ�ܣ�ʹ������趨�õ�Ĭ������
		{

		}
	}
	LockSimpleAddGetDigit::~LockSimpleAddGetDigit()
	{
		
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void LockSimpleAddGetDigit::mousePressEvent(QMouseEvent *event)
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
	void LockSimpleAddGetDigit::mouseMoveEvent(QMouseEvent *event)
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
	void LockSimpleAddGetDigit::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void LockSimpleAddGetDigit::keyPressEvent(QKeyEvent *event)
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

	void LockSimpleAddGetDigit::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(0, 0, main_picture);//��ͼ��Ϊ���ڱ���
	}

	//���ó�Ա����
	void LockSimpleAddGetDigit::set_information(int *extra_digit_array)//������Ҫ��ʾ�ڽ����ϵ���Ϣ������Ϊ�����Ӽ�������ѭ����λ��Ŀ������
	{
		int_information[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER] = &extra_digit_array[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER];//���뵥Ԫ����
		ui.spinBox_2->setValue(*int_information[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER]);
		for (int index = 0; index < DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER; index++)//�������Ԫ�Ӽ�����
		{
			int_information[index] = &extra_digit_array[index];//������Ҫע���ʽ����Ϊʹ����intָ�����飬����Ӧ�ðѵ�ַ�������飬������ʹ��*int_information[index] = extra_digit_array[index]���ַ�ʽֱ�Ӹ�ֵ��������Ϊָ������û�г�ʼ��������û�е�ַ����ֵ��û�е�ַ��ָ�������Ұָ��������������ڴ���ʳ�ͻ������
		}
		for (int index = 0; index < *int_information[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER]; index++)//�������Ԫ�Ӽ�����
		{
			QString transform_result = QString::number((*(int_information[index])), 10);//�����Ԫ��������16�����б������Ҳ����ﵽ16������16��ָ������ĵ�ַ����ȫ����ֵ�����������ڴ���ʳ�ͻ�����⡣ֻ��Ҫ������ʾ���б��еĵ�Ԫ��Ŀ����
			if (transform_result != "")
			{
				ui.listWidget_1->addItem(transform_result);//������Ŀ��ӽ�listwidget
			}
			else
			{
				ui.listWidget_1->addItem(DIALOG_LOCK_SIMPLE_ADD_DEFAULT_UNIT_INSERT_STRING);
			}
		}
	}

	void LockSimpleAddGetDigit::add_item()
	{
		if (ui.listWidget_1->count() < DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER)//������Ŀ����
		{
			if (ui.spinBox_1->text() != "")
			{
				QString transform_result = QString::number(ui.spinBox_1->value(), 10);//��ת��һ�Σ���ȥ��������ͷ�ġ�0�����硰0028��ͨ��ȥ����Ϊ��28��
				ui.listWidget_1->addItem(transform_result);//����Ŀ��ӽ�listwidget
			}
			else
			{
				ui.listWidget_1->addItem(DIALOG_LOCK_SIMPLE_ADD_DEFAULT_UNIT_INSERT_STRING);
			}
		}
		else
		{

		}
	}

	void LockSimpleAddGetDigit::edit_item()
	{
		if (ui.listWidget_1->currentItem() != Q_NULLPTR)
		{
			QString transform_result = QString::number(ui.spinBox_1->value(), 10);//��ת��һ�Σ���ȥ��������ͷ�ġ�0�����硰0028��ͨ��ȥ����Ϊ��28��
			ui.listWidget_1->currentItem()->setText(transform_result);//�޸���Ŀ��ֵ
		}
	}

	void LockSimpleAddGetDigit::delete_item()
	{
		if (ui.listWidget_1->currentItem() != Q_NULLPTR)
		{
			QListWidgetItem *item = ui.listWidget_1->takeItem(ui.listWidget_1->currentRow());//ɾ����Ŀ
			delete item;//ɾ��ָ��
		}
		else
		{

		}
	}

	void LockSimpleAddGetDigit::delete_all_item()
	{
		int temp_count = ui.listWidget_1->count();//�����ʼʱ�����ֵ������һ������������ֱ�ӷŽ�ѭ����Ϊ�ж���������Ϊ��ѭ��������ÿ��ѭ����ʹ�����1
		for (int temp = 0; temp < temp_count; temp++)
		{
			QListWidgetItem *item = ui.listWidget_1->takeItem(0);//ע����ÿ��ɾ��������һ���Ϊÿɾ��һ���������Զ��Ƶ�����
			delete item;
		}
	}

	void LockSimpleAddGetDigit::set_apply()//������Ч
	{
		for (int index = 0; index < DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER; index++)//�Ȱ�����Ԫ�����㣬��ֹ�����б���Ԫ�ص���ĿС��ѭ����λ�������º��沿����Ȼ��֮ǰ���õ�ֵ�����
		{
			*int_information[index] = 0;
		}
		for (int index = 0; index < ui.listWidget_1->count(); index++)//�������Ԫ�Ӽ�����
		{
			bool is_success;
			*int_information[index] = (ui.listWidget_1->item(index)->text()).toInt(&is_success, 10);
			if (!is_success)//ת��ʧ��
			{
				*int_information[index] = 0;
			}
			else
			{

			}
		}
		*int_information[DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER] = ui.spinBox_2->value();//���뵥Ԫ����
		close_window_include_animation();//�رմ���
	}

	void LockSimpleAddGetDigit::cancel_apply()//����ȡ��
	{
		close_window_include_animation();//�رմ���
	}

	void LockSimpleAddGetDigit::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

