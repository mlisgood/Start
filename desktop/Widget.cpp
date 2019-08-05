#include "define.h"

namespace rem
{

	//����ȫ�ֱ���
	extern bool widget_mutex[7];

	//�����׼�����ռ�
	using std::wstring;

	//��������������
	Widget::Widget(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint | windowFlags());//ȥ�����ڱ������������������в�����ִ��ڣ�����ʼ������㡣���ﲻ��ʹ��Qt::SubWindow���ԣ������޷�������ק�¼�
		resize(DIALOG_WEDGIT_SIZE_WIDTH_NUMBER, DIALOG_WEDGIT_SIZE_HEIGHT_NUMBER);//������ǿ�Ƹ�Ϊ�˴�С
		setFixedSize(this->width(), this->height());//��ֹ�ı䴰�ڴ�С
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		setAttribute(Qt::WA_WState_WindowOpacitySet, true);//�ô�������ֱ������͸����
		setAttribute(Qt::WA_DeleteOnClose);//�˳�ʱ���ٸô��������ڴ�й©
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�

		//���ؽ��棬�����������Ա�����汻֮��Ļ�ͼ����
		ui.setupUi(this);

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�

		//����ȫ�ֵķ��²���
		this->setAcceptDrops(true);
	}
	Widget::~Widget()
	{
		//�������ļ���Ӧ�����޸�Ϊ��ֹ
		QSettings *write_setting = new QSettings(FILE_SETTING_STATIC_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		QString temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
		temp += QString::number(widget_id, 10);
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
		write_setting->setValue(temp, 0);
		delete write_setting;
		widget_mutex[widget_id] = true;//����ÿؼ�
	}

	//���ó�Ա����
	void Widget::set_attribute(bool on_top, int widget_id, int transparent, wstring program_path)//����ʹ�õ�ͼƬid�ʹ򿪳���·��
	{
		this->on_top = on_top;
		this->widget_id = widget_id;
		this->program_path = program_path;
		this->transparent = transparent;
		QString filepath = DIALOG_WIDGET_BACKGROUND_PICTURE_PATH_FRONT_STRING + QString::number(widget_id, 10);//����ͼƬ·��
		filepath += DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING;
		picture.load(filepath);
		
		//��ֹ�ٴ���һ���ô���
		widget_mutex[widget_id] = false;

		//�޸�����
		QSettings *setting_dynamic = new QSettings(FILE_SETTING_DYNAMIC_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		QString temp_path = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;//������ҪѰ�ҵ���������·��
		temp_path += QString::number(widget_id, 10);
		temp_path += FILE_SETTING_DYNAMIC_CATALOG_2_1_BACK_INNER_PATH_STRING;
		position[0] = setting_dynamic->value(temp_path).toInt();//��������
		temp_path = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;
		temp_path += QString::number(widget_id, 10);
		temp_path += FILE_SETTING_DYNAMIC_CATALOG_2_2_BACK_INNER_PATH_STRING;
		position[1] = setting_dynamic->value(temp_path).toInt();
		delete setting_dynamic;
		if (position[0] < 0 || position[1] < 0)
		{
			position[0] = 0;
			position[1] = 0;
		}
		else
		{

		}
		move(position[0], position[1]);//�޸Ĵ�����ʼ����

		//�����Ƿ������
		if (on_top)
		{
			setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);//����������ʾ����ǰ��
		}
		else
		{
			setWindowFlags(windowFlags()&~Qt::WindowStaysOnTopHint);//���ڲ���������ʾ����ǰ��
		}
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void Widget::mousePressEvent(QMouseEvent *event)
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
	void Widget::mouseMoveEvent(QMouseEvent *event)
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}

		//��ȡ���������ꡣ�ڽ���֮�󣬽�����д�붯̬��Ϣ�����ļ�
		position[0] = this->pos().x();
		position[1] = this->pos().y();
	}

	//���δ�����£�����Ӧ����Ϊfalse
	void Widget::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;

		//�ͷ����󣬼�¼���������겢д�������ļ�
		QSettings *write_setting = new QSettings(FILE_SETTING_DYNAMIC_PATH_STRING, QSettings::IniFormat);
		QString temp_path = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;//������ҪѰ�ҵ���������·��
		temp_path += QString::number(widget_id, 10);
		temp_path += FILE_SETTING_DYNAMIC_CATALOG_2_1_BACK_INNER_PATH_STRING;
		write_setting->setValue(temp_path, QString::number(position[0], 10));
		temp_path = FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING;
		temp_path += QString::number(widget_id, 10);
		temp_path += FILE_SETTING_DYNAMIC_CATALOG_2_2_BACK_INNER_PATH_STRING;
		write_setting->setValue(temp_path, QString::number(position[1], 10));
		delete write_setting;
	}

	//����¼���������������
	void Widget::mouseDoubleClickEvent(QMouseEvent *event) 
	{
		HINSTANCE return_value;//ָ������ֵ
		return_value = ShellExecute(NULL, L"open", program_path.c_str(), NULL, NULL, SW_SHOWNORMAL);//�򿪳���
		if (program_path != FILE_SETTING_OPEN_PATH_UNDEFINE_DEFAULT_STRING)
		{
			if (return_value >= (HINSTANCE)0 && return_value <= (HINSTANCE)31)//�޷���ָ������
			{
				Help dialog;//��Ϣ��ʾ��
				dialog.setWindowTitle(tr("����ʧ���ˣ�"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_START_PROGRAM_PATH_STRING);//��ʾ��Ϣ
				dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
			}
			else if (return_value >= (HINSTANCE)32)//�Ѿ��򿪣���������
			{

			}
			else//�����쳣���
			{

			}
		}
		else
		{

		}
	}

	//��ק�¼�
	void Widget::dragEnterEvent(QDragEnterEvent *event)
	{
		if (event->mimeData()->hasUrls())//��ֹ������ק�ı����е��������Urlʶ�����Ȼ��������
		{
			event->acceptProposedAction(); //������������ڲ������ϷŶ���
		}
		else
		{

		}
	}

	void Widget::dropEvent(QDropEvent *event)//�ͷ�ʱִ�еĲ���
	{
		QList<QUrl> urls = event->mimeData()->urls();
		QString file_name = urls.first().toLocalFile();//����ļ���
		file_name = (file_name).replace(tr("/"), tr("\\"));
		wstring transform_path = file_name.toStdWString();//��Qstringת��Ϊwstring����Ϊwstring����Unicode�ַ������������ת�����ᵼ������
		HINSTANCE return_value;//ָ������ֵ
		return_value = ShellExecute(NULL, L"open", transform_path.c_str(), NULL, NULL, SW_SHOWNORMAL);//�򿪳���
		if (transform_path != FILE_SETTING_OPEN_PATH_UNDEFINE_DEFAULT_STRING)
		{
			if (return_value >= (HINSTANCE)0 && return_value <= (HINSTANCE)31)//�޷���ָ������
			{
				Help dialog;//��Ϣ��ʾ��
				dialog.setWindowTitle(tr("����ʧ���ˣ�"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_START_PROGRAM_PATH_STRING);//��ʾ��Ϣ
				dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
			}
			else if (return_value >= (HINSTANCE)32)//�Ѿ��򿪣���������
			{

			}
			else//�����쳣���
			{

			}
		}
		else
		{

		}
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void Widget::keyPressEvent(QKeyEvent *event)
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

	void Widget::paintEvent(QPaintEvent *)
	{

		//����ͼƬ
		QPainter background_painter(this);
		background_painter.setOpacity((double)transparent / 10);
		background_painter.drawPixmap(0, 0, DIALOG_WEDGIT_SIZE_WIDTH_NUMBER, DIALOG_WEDGIT_SIZE_HEIGHT_NUMBER, picture);
	}

	void Widget::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

