#include "define.h"

namespace rem
{

	//ȫ�ֱ�������
	extern bool widget_mutex[7] = { true,true,true,true,true,true,true };//ֻ������1���Ӵ��ڡ�ע��ʹ��ȫ�ֱ���ʱ���������������Ƕ��嶼������ͷ�ļ��У�������Ҫ��extern��ȫ�ֱ���ֻ�ܶ���1�Σ�Ҳ���Ǹ���ֵ1�Σ�����Ҫ�õ�����ļ��о���������

	//�����׼�����ռ�
	using std::wstring;

	//�������������
	Desktop::Desktop(QWidget *parent) : QMainWindow(parent)
	{
		setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint | windowFlags());//ȥ�����ڱ������������������в�����ִ��ڣ�����ʼ�������
		resize(WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_HEIGHT_NUMBER);//������ǿ�Ƹ�Ϊ�˴�С
		setFixedSize(this->width(), this->height());//��ֹ�ı䴰�ڴ�С
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, true);//�ô��ڹر�ʱ���˳�����
		setAttribute(Qt::WA_WState_WindowOpacitySet, true);//�ô�������ֱ������͸����
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�
		is_hide = false;//������û�б�����
		move_enable = true;//�ƶ�ʱ������¼�������ļ�

		ui.setupUi(this);

		//�޸�����
		QSettings *setting_dynamic = new QSettings(FILE_SETTING_DYNAMIC_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		position[0] = setting_dynamic->value(FILE_SETTING_DYNAMIC_CATALOG_1_1_INNER_PATH_STRING).toInt();//��������
		position[1] = setting_dynamic->value(FILE_SETTING_DYNAMIC_CATALOG_1_2_INNER_PATH_STRING).toInt();
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

		//��̬��Ϣ��ȡ
		QSettings *setting_static = new QSettings(FILE_SETTING_STATIC_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		QString temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_1_STRING;
		int is_hide_available_temp = setting_static->value(temp).toInt();
		if (is_hide_available_temp == 1)
		{
			is_hide_available = true;
		}
		else
		{
			is_hide_available = false;
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_2_STRING;
		timer_interval_number = setting_static->value(temp).toInt();
		if (timer_interval_number < 0)
		{
			timer_interval_number = 0;
		}
		else
		{

		}
		timer_interval_number *= 1000;//��ת��Ϊ����
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
		int is_on_top_temp = setting_static->value(temp).toInt();
		if (is_on_top_temp == 1)
		{
			on_top = true;
		}
		else
		{
			on_top = false;
		}
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_4_STRING;
		transparent = setting_static->value(temp).toDouble();
		if (transparent < 0)
		{
			transparent = 0;
		}
		else
		{

		}
		transparent /= 10;//����10������QT��׼ʹ�ø�͸����
		temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING;
		temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_5_STRING;
		int auto_run_temp = setting_static->value(temp).toInt();
		autorun = false;//�Ƿ�������
		if (auto_run_temp == 1)
		{
			autorun = true;
		}
		else
		{
			autorun = false;
		}

		//�ؼ����Զ�ȡ
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER; index++)
		{
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
			int temp_bool = setting_static->value(temp).toInt();
			if (temp_bool == 1)
			{
				widget_is_enable[index] = true;
			}
			else
			{
				widget_is_enable[index] = false;
			}
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING;
			temp_bool = setting_static->value(temp).toInt();
			if (temp_bool == 1)
			{
				widget_is_on_top[index] = true;
			}
			else
			{
				widget_is_on_top[index] = false;
			}
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_4_STRING;
			widget_transparent[index] = setting_static->value(temp).toInt();
			if (widget_transparent[index] < 0)
			{
				widget_transparent[index] = 0;
			}
			else
			{

			}
			temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(index, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_7_STRING;
			QString temp_path = setting_static->value(temp).toString();
			widget_path[index] = temp_path.toStdWString();//��Qstringת��Ϊwstring����Ϊwstring����Unicode�ַ������������ת�����ᵼ������
		}
		delete setting_static;

		//�����Ƿ������
		if (on_top)
		{
			setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);//����������ʾ����ǰ��
		}
		else
		{
			setWindowFlags(windowFlags()&~Qt::WindowStaysOnTopHint);//���ڲ���������ʾ����ǰ��
		}

		//�������
		for (int index = 0; index < WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER; index++)
		{
			if (widget_is_enable[index])
			{
				Widget *dialog = new Widget;//��ģ̬����
				dialog->set_attribute(widget_is_on_top[index], index, widget_transparent[index], widget_path[index]);//���ó�ʼֵ
				dialog->setModal(false);//ָ��Ϊ��ģ̬�Ի���
				dialog->show();
			}
			else
			{

			}
		}

		//�������������
		QString application_name = QApplication::applicationName();//�����������ʱ����Ƿ񿪻��Զ�����
		QSettings *regedit_settings_begin = new QSettings(REG_RUN, QSettings::NativeFormat);//�޸�ע���
		if (autorun)//�Ƿ��Զ�����
		{
			QString application_path = QApplication::applicationFilePath();//��þ���·��
			regedit_settings_begin->setValue(application_name, application_path.replace("/", "\\"));//д��ע����ע��ע���ʹ�õ�·���ָ�����QT������෴
		}
		else
		{
			regedit_settings_begin->remove(application_name);//ɾ��ע�����
		}
		delete regedit_settings_begin;

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(transparent);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�

		//�����ڼ�����ϵͳ����
		system_tray_icon = new QSystemTrayIcon(this);
		QIcon icon_picture = QIcon(PROGRAM_SYSTEM_TRAY_ICON_PATH_STRING);
		system_tray_icon->setIcon(icon_picture);//ͼ��
		system_tray_icon->setToolTip(PROGRAM_SYSTEM_TRAY_TIP_STRING);//��ʾ
		create_system_tray_menu_action();//��Ӳ˵����ܣ���Ϊ��Ӳ˵�����Ҫ��Ӷ�����˱�������Ӷ�������Ӳ˵����������Ϊ��Ӳ˵�ʱ��û��Ϊ���������ڴ�ռ������
		create_system_tray_menu();//��Ӳ˵�
		system_tray_icon->show();//��ʾ����
		connect(system_tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(system_tray_icon_clicked(QSystemTrayIcon::ActivationReason)));//�����źź���
	
		//��ʱ������
		time_counter = new QTimer(this);//����һ����ʱ������Ϊ֮�����ͷź�������˼�ʹ��ʹ��Ҳ��Ҫ����һ��
		time_counter->setTimerType(Qt::PreciseTimer);//�޸ľ���
		if (is_hide_available == true)//���ò�������ع��ܺ����ʹ��
		{
			time_counter->setInterval(timer_interval_number);//���ü�ʱ���
			time_counter->start();//��ʼʱ����Ҫ������ʱ��
			connect(time_counter, SIGNAL(timeout()), this, SLOT(time_hide_animation_disappear()));//��ʱ�����ڴ����ı�ͼƬ
		}
		else
		{

		}

		//���ر���ͼƬ
		randnumber = WINDOW_RANDOM_MIN_NUMBER + rand() % (WINDOW_RANDOM_MAX_NUMBER - WINDOW_RANDOM_MIN_NUMBER + 1);//����һ����������֣���������������������ı�����ÿ����ʾ�����棬������ֶ��ᷢ���仯
		background_path = WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING;//��ʱ�洢����ͼƬ·��
		background_path += QString::number(randnumber, 10);
		background_path += WINDOW_BACKGROUND_PICTURE_PATH_BACK_STRING;
		background_picture.load(background_path);//���ر���ͼƬ
}

	Desktop::~Desktop()
	{
		delete system_tray_icon;
		delete system_tray_menu;
		delete action_static_set;
		delete action_dynamic_set;
		delete action_auto_start_set;
		delete action_help;
		delete action_exit;
		delete time_counter;
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ�����ꡣ���⣬���ز����Ĵ���Ҳ�ڴ˴�����
	void Desktop::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bPressed = true;
			m_point = event->pos();
		}
		else
		{

		}
		if (is_hide_available)//���ò�������ع��ܺ����ʹ��
		{
			time_counter->stop();//ֹͣ��ʱ����ֻ������ͷ�֮������¿�ʼ��ʱ����ֹ�ƶ����������ص��������
			if (is_hide)//���ڱ����أ����Ҳ����ڽ�ͼ��ϵ�ʱ����Ҫ��ʾ
			{
				move_enable = false;//��ֹ��¼��������������ܻ�ƫ��λ��
				is_hide = false;//�����������ʾ�¼�
				QPropertyAnimation *animation_show_disappear = new QPropertyAnimation(this, "windowOpacity");//���ش�����ʧ����
				animation_show_disappear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
				animation_show_disappear->setStartValue(transparent);
				animation_show_disappear->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
				animation_show_disappear->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
				connect(animation_show_disappear, SIGNAL(finished()), this, SLOT(show_animation_appear()));
			}
			else//δ�����أ������յ����ʾ�¼�
			{

			}
		}
		else
		{

		}
	}

	void Desktop::mouseMoveEvent(QMouseEvent *event)//�������������£����ƶ�����λ��
	{
		if (m_bPressed)
		{
			move(event->pos() - m_point + pos());
		}
		else
		{

		}

		//��ȡ���������ꡣ�ڽ���֮�󣬽�����д�붯̬��Ϣ�����ļ�
		if (move_enable)
		{
			position[0] = this->pos().x();
			position[1] = this->pos().y();
		}
		else
		{

		}
	}

	void Desktop::mouseReleaseEvent(QMouseEvent *event)//���δ�����£�����Ӧ����Ϊfalse
	{
		Q_UNUSED(event);
		m_bPressed = false;
		if (is_hide_available)//���ò�������ع��ܺ����ʹ��
		{
			time_counter->start();//���¿�ʼ��ʱ
		}
		else
		{

		}

		//�ͷ����󣬼�¼���������겢д�������ļ�
		QSettings *write_setting = new QSettings(FILE_SETTING_DYNAMIC_PATH_STRING, QSettings::IniFormat);
		write_setting->setValue(FILE_SETTING_DYNAMIC_CATALOG_1_1_INNER_PATH_STRING, QString::number(position[0], 10));
		write_setting->setValue(FILE_SETTING_DYNAMIC_CATALOG_1_2_INNER_PATH_STRING, QString::number(position[1], 10));
		delete write_setting;
	}


	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void Desktop::keyPressEvent(QKeyEvent *event)
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

		//�ؼ�
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_Q))
		{
			key_press_method(0);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_W))
		{
			key_press_method(1);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_E))
		{
			key_press_method(2);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_A))
		{
			key_press_method(3);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_S))
		{
			key_press_method(4);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_D))
		{
			key_press_method(5);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_F))
		{
			key_press_method(6);
		}
		else
		{

		}
	}

	void Desktop::paintEvent(QPaintEvent *)//���Ʊ���ͼ��
	{
		QPainter background_painter(this);//����
		background_painter.drawPixmap(0, 0, background_picture.size().width(), background_picture.size().height(), background_picture);//���Ʊ���ͼƬ
	}

	//ϵͳ����
	void Desktop::create_system_tray_menu()//ϵͳ���̲˵�
	{
		system_tray_menu = new QMenu(this);
		system_tray_menu->addAction(action_static_set);//������þ�̬���Թ���
		system_tray_menu->addAction(action_dynamic_set);//������ö�̬���Թ���
		system_tray_menu->addAction(action_auto_start_set);//������ÿ�������������
		system_tray_menu->addSeparator();//���ӷָ���
		system_tray_menu->addAction(action_help);//�����Ϣ����
		system_tray_menu->addSeparator();//���ӷָ���
		system_tray_menu->addAction(action_exit);//����˳�����
		system_tray_icon->setContextMenu(system_tray_menu);//�Ѳ˵���������ͼ��
	}

	void Desktop::create_system_tray_menu_action()//ϵͳ���̲˵�����
	{
		action_static_set = new QAction(QObject::tr("��������   "), this);//���ù���
		connect(action_static_set, SIGNAL(triggered()), this, SLOT(show_system_tray_action_set_static()));
		action_dynamic_set = new QAction(QObject::tr("��������   "), this);//���ù���
		connect(action_dynamic_set, SIGNAL(triggered()), this, SLOT(show_system_tray_action_set_dynamic()));
		action_auto_start_set = new QAction(QObject::tr("��������   "), this);//���ù���
		connect(action_auto_start_set, SIGNAL(triggered()), this, SLOT(show_system_tray_action_set_other()));
		action_help = new QAction(QObject::tr("������Ϣ   "), this);//��Ϣ����
		connect(action_help, SIGNAL(triggered()), this, SLOT(show_system_tray_action_help()));
		action_exit = new QAction(QObject::tr("�˳�����   "), this);//�˳�����
		connect(action_exit, SIGNAL(triggered()), this, SLOT(show_system_tray_action_exit()));
	}

	//�ۺ���
	void Desktop::system_tray_icon_clicked(QSystemTrayIcon::ActivationReason reason)
	{
		switch (reason)
		{
		case QSystemTrayIcon::Trigger://����������ʾ�˵�

			break;

		case QSystemTrayIcon::DoubleClick://�����Ƿ���ʼ�ն������л�

			if (on_top == false)
			{
				setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);//����������ʾ����ǰ��
				on_top = true;
			}
			else
			{
				setWindowFlags(windowFlags()&~Qt::WindowStaysOnTopHint);//���ڲ���������ʾ����ǰ��
				on_top = false;
			}
			show();//�����������һ�������⣬���細����Զ�޷���ʾ
			break;

		default:

			break;
		}
	}

	void Desktop::show_system_tray_action_set_static()//�˵��������ù���
	{
		Setting dialog;//�޸������ļ�
		dialog.exec();
	}

	void Desktop::show_system_tray_action_set_dynamic()//�˵��������ù���
	{
		SettingDynamic dialog;//�޸������ļ�
		dialog.exec();
	}

	void Desktop::show_system_tray_action_set_other()//�˵���������������
	{
		SettingOther dialog;//�޸������ļ�
		dialog.exec();
	}

	void Desktop::show_system_tray_action_help()//ϵͳ���̲˵���Ϣ����
	{
		Help dialog;//��ʾ������Ϣ
		dialog.set_dialog_information_path(DIALOG_INFORMATION_HELP_PATH_STRING);
		dialog.exec();
	}

	void Desktop::show_system_tray_action_exit()//ϵͳ���̲˵��˳�����
	{
		close_window_include_animation();//�رմ��ڲ��˳�����
	}

	void Desktop::time_hide_animation_disappear()//���ع��̼�ʱ��������ʧ��������
	{
		QPropertyAnimation *animation_hide_disappear = new QPropertyAnimation(this, "windowOpacity");//��������ʧ����
		animation_hide_disappear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_hide_disappear->setStartValue(transparent);
		animation_hide_disappear->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_hide_disappear->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		connect(animation_hide_disappear, SIGNAL(finished()), this, SLOT(time_hide_animation_appear()));
	}

	void Desktop::time_hide_animation_appear()//���ع��̼�ʱ�����ڳ��ֶ�������
	{
	
		//�������ش����ƶ��ķ��򡣸��߼��ǣ��������ش���������Ļ�����x��y�����ϵľ��룬ȡ����Ļ�ܿ�ȱ�ֵ��ӽ�����Ϊx��y�������غ��ƶ���ͬ��x��y�����ϵ���Ļ��Ե���������ֻ���������߼���
		QScreen *screen = QGuiApplication::primaryScreen();//��ȡ�ֱ���
		QRect rect = screen->availableGeometry();
		screen_resolution[0] = rect.width();
		screen_resolution[1] = rect.height();
		int hidewindow_x;
		int hidewindow_y;
		int mainwindow_x = position[0] + WINDOW_SIZE_WIDTH_NUMBER / 2;//��ȡ���������ĵ�
		int mainwindow_y = position[1] + WINDOW_SIZE_WIDTH_NUMBER / 2;
		double ratio_x = ((double)mainwindow_x - (double)screen_resolution[0] / 2) / ((double)screen_resolution[0] / 2);//ȡ��Ļ���ĵ���Ϊ�ο�����x�����ϣ�����������x�����ȥ��Ļ���ĵ�����õ��õ�����Ļ���ĵ��x���룬������Ļ���ĵ�x����õ�������Ļ���ĵ�����x���룬��ֵԽ�����x����Խ�󣬸õ���x����������Ļ��ԵԽ����ͬ���������y�����ϵı�ֵ��ȡ�Ͻ�����Ϊ�ƶ�����
		double ratio_y = ((double)mainwindow_y - (double)screen_resolution[1] / 2) / ((double)screen_resolution[1] / 2);
		double abs_ratio_x = abs(ratio_x);
		double abs_ratio_y = abs(ratio_y);

		//�������ش������ꡣע���ƶ�����Եʱ������Ҫ������������Ϊ������겢�������ش��ڵ��������ꡣ�õ�ͼƬλ�ú󣬼���ָ��ͼƬ
		if (ratio_y >= 0 && ratio_x >= 0)//���������ĵ�����Ļ���·�
		{
			if (abs_ratio_y >= abs_ratio_x)//y�����ϸ������ƶ�����Ļ�±�Ե
			{
				hidewindow_x = mainwindow_x - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = screen_resolution[1] - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_DOWN_HIDE_PICTURE_PATH_STRING);
			}
			else//x�����ϸ������ƶ�����Ļ�ұ�Ե
			{
				hidewindow_x = screen_resolution[0] - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = mainwindow_y - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_RIGHT_HIDE_PICTURE_PATH_STRING);
			}
		}
		else if (ratio_y >= 0 && ratio_x < 0)//���������ĵ�����Ļ���·�
		{
			if (abs_ratio_y >= abs_ratio_x)//y�����ϸ������ƶ�����Ļ�±�Ե
			{
				hidewindow_x = mainwindow_x - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = screen_resolution[1] - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_DOWN_HIDE_PICTURE_PATH_STRING);
			}
			else//x�����ϸ������ƶ�����Ļ���Ե
			{
				hidewindow_x = 0 - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = mainwindow_y - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_LEFT_HIDE_PICTURE_PATH_STRING);
			}
		}
		else if (ratio_y < 0 && ratio_x >= 0)//���������ĵ�����Ļ���Ϸ�
		{
			if (abs_ratio_y >= abs_ratio_x)//y�����ϸ������ƶ�����Ļ�ϱ�Ե
			{
				hidewindow_x = mainwindow_x - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = 0 - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_UP_HIDE_PICTURE_PATH_STRING);
			}
			else//x�����ϸ������ƶ�����Ļ�ұ�Ե
			{
				hidewindow_x = screen_resolution[0] - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = mainwindow_y - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_RIGHT_HIDE_PICTURE_PATH_STRING);
			}
		}
		else//���������ĵ�����Ļ���Ϸ�
		{
			if (abs_ratio_y >= abs_ratio_x)//y�����ϸ������ƶ�����Ļ�ϱ�Ե
			{
				hidewindow_x = mainwindow_x - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = 0 - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_UP_HIDE_PICTURE_PATH_STRING);
			}
			else//x�����ϸ������ƶ�����Ļ���Ե
			{
				hidewindow_x = 0 - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				hidewindow_y = mainwindow_y - WINDOW_SIZE_SIDE_LENGTH_NUMBER / 2;
				background_picture.load(WINDOW_BACKGROUND_LEFT_HIDE_PICTURE_PATH_STRING);
			}
		}
		background_picture = background_picture.scaled(QSize(WINDOW_SIZE_SIDE_LENGTH_NUMBER, WINDOW_SIZE_SIDE_LENGTH_NUMBER), Qt::KeepAspectRatio);//�ض���ͼƬ��С
		resize(background_picture.size());//�ض��崰�ڴ�С
		move(hidewindow_x, hidewindow_y);//���ݼ������������ֵ�ƶ����ش���
		update();
		setWindowOpacity(transparent);//�������ش���͸����
		QPropertyAnimation *animation_hide_appear = new QPropertyAnimation(this, "windowOpacity");//��������ʧ����
		animation_hide_appear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_hide_appear->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_hide_appear->setEndValue(transparent);
		animation_hide_appear->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		connect(animation_hide_appear, SIGNAL(finished()), this, SLOT(time_hide_repaint()));
		time_hide_repaint();
	}

	void Desktop::time_hide_repaint()//���ع��̼�ʱ�����ڻ��ƴ��ں���
	{
		time_counter->stop();//����رռ�ʱ������������ѭ����ʱ
		is_hide = true;//����Ϊ�����ڱ����أ����Լ������յ����ʾ�¼�
	}

	void Desktop::show_animation_appear()//��ʾ���̳��ֶ�������
	{
		move_enable = true;//�����¼
		randnumber = WINDOW_RANDOM_MIN_NUMBER + rand() % (WINDOW_RANDOM_MAX_NUMBER - WINDOW_RANDOM_MIN_NUMBER + 1);//����һ����������֣���������������������ı�����ÿ����ʾ�����棬������ֶ��ᷢ���仯
		background_path = WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING;//��ʱ�洢����ͼƬ·��
		background_path += QString::number(randnumber, 10);
		background_path += WINDOW_BACKGROUND_PICTURE_PATH_BACK_STRING;
		background_picture.load(background_path);//���ر���ͼƬ
		resize(WINDOW_SIZE_WIDTH_NUMBER, WINDOW_SIZE_HEIGHT_NUMBER);//������ǿ�Ƹ�Ϊ�˴�С
		move(position[0], position[1]);//�޸Ĵ�����ʼ����
		update();
		setWindowOpacity(transparent);
		QPropertyAnimation *animation_show_appear = new QPropertyAnimation(this, "windowOpacity");//��������ʧ����
		animation_show_appear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_show_appear->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_show_appear->setEndValue(transparent);
		animation_show_appear->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		QPoint mouse_position(position[0] + WINDOW_SIZE_WIDTH_NUMBER / 2, position[1] + WINDOW_SIZE_HEIGHT_NUMBER / 2);//�޸����λ�ã��������������ʱ��˲�Ƶ����λ�ã��ǳ�����г
		QCursor::setPos(mouse_position);
	}

	//��������
	void Desktop::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
	{

		//�������а�ť�����򶯻��������ǰ�ٴε����ť�����´�������
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(false);
		}
		QPropertyAnimation *animation_close = new QPropertyAnimation(this, "windowOpacity");
		animation_close->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//���ڹرն���Ч��
		animation_close->setStartValue(transparent);
		animation_close->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_close->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		connect(animation_close, SIGNAL(finished()), this, SLOT(close()));
	}

	void Desktop::key_press_method(int widget_id)//�����¼�����
	{
		if (widget_mutex[widget_id])
		{

			//�������ļ���Ӧ�����޸�Ϊ��������������
			QSettings *write_setting = new QSettings(FILE_SETTING_STATIC_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
			QString temp = FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING;
			temp += QString::number(widget_id, 10);
			temp += FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING;
			write_setting->setValue(temp, 1);
			delete write_setting;
			Widget *dialog = new Widget;//��ģ̬����
			dialog->set_attribute(widget_is_on_top[widget_id], widget_id, widget_transparent[widget_id], widget_path[widget_id]);//���ó�ʼֵ
			dialog->setModal(false);//ָ��Ϊ��ģ̬�Ի���
			dialog->show();
		}
		else
		{

		}
	}
}

