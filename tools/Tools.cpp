#include "define.h"

namespace rem
{

	//ȫ�ֱ�������
	extern int counter_mutex = 1;//ֻ������1����ʱ�����ڡ�ע��ʹ��ȫ�ֱ���ʱ���������������Ƕ��嶼������ͷ�ļ��У�������Ҫ��extern��ȫ�ֱ���ֻ�ܶ���1�Σ�Ҳ���Ǹ���ֵ1�Σ�����Ҫ�õ�����ļ��о���������
	extern int sound_record_mutex = 1;//ֻ������1��¼������
	
	//�����׼�����ռ�
	using std::string;
	using std::wstring;

	Tools::Tools(QWidget *parent) : QMainWindow(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint | windowFlags());//ȥ�����ڱ������������������в�����ִ��ڣ�����ʼ�������
		on_top = true;//����ʼ���ڶ���
		is_hide = false;//���ڴ��ڳ���״̬δ������
		screenshot_end_mouse_event_disable = false;//û������������¼�
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, true);//�ô��ڹر�ʱ���˳�����
		setAttribute(Qt::WA_WState_WindowOpacitySet, true);//�ô�������ֱ������͸����
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�
		QSettings *begin_read = new QSettings(FILE_SETTING_MAINWINDOW_STYLE_PATH_STRING, QSettings::IniFormat);//��ȡini�ļ��е���Ϣ
		setting_picture_mainpicture= begin_read->value(FILE_SETTING_CATALOG_1_INNER_PATH_STRING).toString();//����
		setting_function_program[0] = begin_read->value(FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING).toString();//���еĳ���
		setting_function_program[1] = begin_read->value(FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING).toString();
		setting_function_program[2] = begin_read->value(FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING).toString();
		setting_function_program[3] = begin_read->value(FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING).toString();
		setting_function_program[4] = begin_read->value(FILE_SETTING_CATALOG_2_5_INNER_PATH_STRING).toString();
		setting_function_program[5] = begin_read->value(FILE_SETTING_CATALOG_2_6_INNER_PATH_STRING).toString();
		setting_function_program[6] = begin_read->value(FILE_SETTING_CATALOG_2_7_INNER_PATH_STRING).toString();
		setting_function_program[7] = begin_read->value(FILE_SETTING_CATALOG_2_8_INNER_PATH_STRING).toString();
		setting_font_font = begin_read->value(FILE_SETTING_CATALOG_4_INNER_PATH_STRING).toString();//��ǩ��������
		bool status_temp[2];//��ʱ����ֵ���ж��Ƿ�ת���ɹ�
		x_position = begin_read->value(FILE_SETTING_CATALOG_5_1_INNER_PATH_STRING).toString().toInt(&status_temp[0], 10);//�޸�λ��
		y_position = begin_read->value(FILE_SETTING_CATALOG_5_2_INNER_PATH_STRING).toString().toInt(&status_temp[1], 10);
		if (status_temp[0] == true && status_temp[1] == true)//������ת��ʧ����ǿ�Ƹ�Ϊ0
		{

		}
		else
		{
			x_position = 0;
			y_position = 0;
		}
		move(x_position, y_position);//�޸Ĵ�����ʼ����
		bool autorun = begin_read->value(FILE_SETTING_CATALOG_3_INNER_PATH_STRING).toBool();//�Ƿ񿪻�������
		delete begin_read;
		QSettings *begin_read_extra = new QSettings(FILE_SETTING_MAINWINDOW_STYLE_EXTRA_PATH_STRING, QSettings::IniFormat);//��ȡ����ini�ļ��е���Ϣ
		setting_extra_index[0] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_1_1_INNER_PATH_STRING).toString();//ֱ�ӽ���Ϣȫ�����룬֮���ٽ��д���
		setting_extra_index[1] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_1_2_INNER_PATH_STRING).toString();
		setting_extra_index[2] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_2_1_INNER_PATH_STRING).toString();
		setting_extra_index[3] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_2_2_INNER_PATH_STRING).toString();
		setting_extra_index[4] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_2_3_INNER_PATH_STRING).toString();
		setting_extra_index[5] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_2_4_INNER_PATH_STRING).toString();
		setting_extra_index[6] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_2_5_INNER_PATH_STRING).toString();
		setting_extra_index[7] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_2_6_INNER_PATH_STRING).toString();
		setting_extra_index[8] = begin_read_extra->value(FILE_EXTRA_SETTING_CATALOG_2_7_INNER_PATH_STRING).toString();
		delete begin_read_extra;
		QString application_name = QApplication::applicationName();//�����������ʱ����Ƿ񿪻��Զ�����
		QSettings *regedit_settings_begin = new QSettings(REG_RUN, QSettings::NativeFormat);//�޸�ע���
		if (autorun == true)//�Ƿ��Զ�����
		{
			QString application_path = QApplication::applicationFilePath();//��þ���·��
			regedit_settings_begin->setValue(application_name, application_path.replace("/", "\\"));//д��ע����ע��ע���ʹ�õ�·���ָ�����QT������෴
		}
		else
		{
			regedit_settings_begin->remove(application_name);//ɾ��ע�����
		}
		delete regedit_settings_begin;

		//���ؽ���
		ui.setupUi(this);

		//ͼƬ����
		if (setting_picture_mainpicture == tr("1"))//���������ļ���ȡͼƬ�����ҽ����ڱ�������Ϊ������Ŀ
		{
			main_picture_normal_hole_path = WINDOW_PICTURE_BACKGROUND_INDEX_1_PATH_STRING;
			setWindowTitle(WINDOW_DIALOG_TITLE_INDEX_1_PATH_STRING);
		}
		else if (setting_picture_mainpicture == tr("2"))
		{
			main_picture_normal_hole_path = WINDOW_PICTURE_BACKGROUND_INDEX_2_PATH_STRING;
			setWindowTitle(WINDOW_DIALOG_TITLE_INDEX_2_PATH_STRING);
		}
		else if (setting_picture_mainpicture == tr("3"))
		{
			main_picture_normal_hole_path = WINDOW_PICTURE_BACKGROUND_INDEX_3_PATH_STRING;
			setWindowTitle(WINDOW_DIALOG_TITLE_INDEX_3_PATH_STRING);
		}
		else if (setting_picture_mainpicture == tr("4"))
		{
			main_picture_normal_hole_path = WINDOW_PICTURE_BACKGROUND_INDEX_4_PATH_STRING;
			setWindowTitle(WINDOW_DIALOG_TITLE_INDEX_4_PATH_STRING);
		}
		else
		{
			main_picture_normal_hole_path = WINDOW_PICTURE_BACKGROUND_INDEX_1_PATH_STRING;
			setWindowTitle(WINDOW_DIALOG_TITLE_INDEX_1_PATH_STRING);
		}
		if (setting_extra_index[1] == tr("150*250"))
		{
			main_picture_normal_hole_path += WINDOW_PICTURE_BACKGROUND_INDEX_1_MIDDLE_PATH_STRING;
		}
		else if (setting_extra_index[1] == tr("100*167"))
		{
			main_picture_normal_hole_path += WINDOW_PICTURE_BACKGROUND_INDEX_2_MIDDLE_PATH_STRING;
		}
		else if (setting_extra_index[1] == tr("75*125"))
		{
			main_picture_normal_hole_path += WINDOW_PICTURE_BACKGROUND_INDEX_3_MIDDLE_PATH_STRING;
		}
		else if (setting_extra_index[1] == tr("50*83"))
		{
			main_picture_normal_hole_path += WINDOW_PICTURE_BACKGROUND_INDEX_4_MIDDLE_PATH_STRING;
		}
		else
		{
			main_picture_normal_hole_path += WINDOW_PICTURE_BACKGROUND_INDEX_2_MIDDLE_PATH_STRING;
		}
		main_picture_normal_hole_path += WINDOW_PICTURE_BACKGROUND_INDEX_PATH_BACK_STRING;
		main_picture.load(main_picture_normal_hole_path);
		resize(main_picture.size());//���ڴ�С��ΪͼƬ��С
		if (setting_extra_index[4] == tr("���؄e���������ȥ���"))//��������ͼƬ
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_1_PATH_STRING;
		}
		else if (setting_extra_index[4] == tr("���؄e���ƥ��åԩ`"))
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_2_PATH_STRING;
		}
		else if (setting_extra_index[4] == tr("���؄e���ʤ�"))
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_3_PATH_STRING;
		}
		else if (setting_extra_index[4] == tr("����ͨ��ħ����Ů������"))
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_4_PATH_STRING;
		}
		else if (setting_extra_index[4] == tr("����ͨ�����`����`������"))
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_5_PATH_STRING;
		}
		else if (setting_extra_index[4] == tr("����ͨ������ʩ`���ޥ�"))
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_6_PATH_STRING;
		}
		else if (setting_extra_index[4] == tr("����ͨ���Щ`���`���`���ᥰ"))
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_7_PATH_STRING;
		}
		else
		{
			main_picture_hide_hole_path = WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_1_PATH_STRING;
		}
		if (setting_extra_index[5] == tr("����ͨ��Ϊ150*250�����؄e��Ϊ100*100"))
		{
			main_picture_hide_hole_path += WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_1_MIDDLE_PATH_STRING;
		}
		else if (setting_extra_index[5] == tr("����ͨ��Ϊ100*167�����؄e��Ϊ75*75"))
		{
			main_picture_hide_hole_path += WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_2_MIDDLE_PATH_STRING;
		}
		else if (setting_extra_index[5] == tr("����ͨ��Ϊ75*125�����؄e��Ϊ50*50"))
		{
			main_picture_hide_hole_path += WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_3_MIDDLE_PATH_STRING;
		}
		else if (setting_extra_index[5] == tr("����ͨ��Ϊ50*83�����؄e��Ϊ25*25"))
		{
			main_picture_hide_hole_path += WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_4_MIDDLE_PATH_STRING;
		}
		else
		{
			main_picture_hide_hole_path += WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_3_MIDDLE_PATH_STRING;
		}
		main_picture_hide_hole_path += WINDOW_PICTURE_BACKGROUND_INDEX_PATH_BACK_STRING;

		//����͸����
		bool transform_transparent_temp;//ת���Ƿ�ɹ�����ʱ�ж���
		animation_transparent_number = setting_extra_index[0].toInt(&transform_transparent_temp, 10);//���ڳ�ʼ͸���ȴ������ļ���ȡ
		animation_transparent_number /= 10;
		if (!transform_transparent_temp)
		{
			animation_transparent_number = 1;
		}
		else
		{

		}
		setWindowOpacity(animation_transparent_number);
		animation_transparent_hide_number = setting_extra_index[8].toInt(&transform_transparent_temp, 10);//���ش���ʱ����͸����
		animation_transparent_hide_number /= 10;
		if (!transform_transparent_temp)
		{
			animation_transparent_hide_number = 1;
		}
		else
		{

		}

		//���ü�ʱ�����
		bool transform_timer_temp;//ת���Ƿ�ɹ�����ʱ�ж���
		timer_interval_number = setting_extra_index[3].toInt(&transform_timer_temp, 10)*1000;//��ʱ�������ע�ⵥλ�Ǻ���
		if (!transform_timer_temp)
		{
			timer_interval_number = 1;
		}
		else
		{

		}
		
		//�������ش���λ��
		bool position_temp[2];//��ʱ����ֵ���ж��Ƿ�ת���ɹ�
		extra_x_position = setting_extra_index[6].toInt(&position_temp[0], 10);
		extra_y_position = setting_extra_index[7].toInt(&position_temp[1], 10);
		if (position_temp[0] == true && position_temp[1] == true)
		{

		}
		else
		{
			extra_x_position = 0;
			extra_y_position = 0;
		}

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(animation_transparent_number);
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
		if (setting_extra_index[2] == tr("1"))//���ò�������ع��ܺ����ʹ��
		{
			time_counter->setInterval(timer_interval_number);//���ü�ʱ���
			time_counter->start();//��ʼʱ����Ҫ������ʱ��
			connect(time_counter, SIGNAL(timeout()), this, SLOT(time_hide_animation_disappear()));//��ʱ�����ڴ����ı�ͼƬ
		}
		else
		{

		}
	}

	Tools::~Tools()
	{
		delete system_tray_icon;
		delete system_tray_menu;
		delete action_set;
		delete action_set_extra;
		delete action_set_sound_record;
		delete action_help;
		delete action_exit;
		delete time_counter;
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ�����ꡣ���⣬���ز����Ĵ���Ҳ�ڴ˴�����
	void Tools::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bPressed = true;
			m_point = event->pos();
		}
		else
		{

		}
		if (setting_extra_index[2] == tr("1"))//���ò�������ع��ܺ����ʹ��
		{
			time_counter->stop();//ֹͣ��ʱ����ֻ������ͷ�֮������¿�ʼ��ʱ����ֹ�ƶ����������ص��������
			if (is_hide && !screenshot_end_mouse_event_disable)//���ڱ����أ����Ҳ����ڽ�ͼ��ϵ�ʱ����Ҫ��ʾ
			{
				is_hide = false;//�����������ʾ�¼�
				QPropertyAnimation *animation_show_disappear = new QPropertyAnimation(this, "windowOpacity");//���ش�����ʧ����
				animation_show_disappear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
				animation_show_disappear->setStartValue(animation_transparent_hide_number);
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

	//�������������£����ƶ�����λ��
	void Tools::mouseMoveEvent(QMouseEvent *event)
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
	void Tools::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
		if (setting_extra_index[2] == tr("1"))//���ò�������ع��ܺ����ʹ��
		{
			time_counter->start();//���¿�ʼ��ʱ
		}
		else
		{

		}
	}

	//�����¼�
	void Tools::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.drawPixmap(WINDOW_BACKGROUND_PAINT_START_X_NUMBER, WINDOW_BACKGROUND_PAINT_START_Y_NUMBER, main_picture);//��ͼ��Ϊ���ڱ���
	}

	//�����¼���������Ӧ��ݼ�
	void Tools::keyPressEvent(QKeyEvent *event)
	{

		//ctrl����ĸ������ϣ��Ȱ�����ĸ���ٰ���ctrl����Ч������8������������
		if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_1))
		{
			run_program(1);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_2))
		{
			run_program(2);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_3))
		{
			run_program(3);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_4))
		{
			run_program(4);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_5))
		{
			run_program(5);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_6))
		{
			run_program(6);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_7))
		{
			run_program(7);
		}
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_8))
		{
			run_program(8);
		}

		//��ͼ����
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_S))
		{
			Screenshot dialog;//�������ڽ�ͼ�Ĵ���
			connect(&dialog, &Screenshot::finish, this, &Tools::screenshot_success);//��ͼ�ɹ��������źŲ����ء����ָ�ʽ���źŴ�ֵ��Ҫ���ڲ�ͬ�ļ�֮��Ĵ���
			connect(&dialog, &Screenshot::close_window, this, &Tools::screenshot_fail);//��ͼʧ�ܣ������źŲ����ء����ָ�ʽ���źŴ�ֵ��Ҫ���ڲ�ͬ�ļ�֮��Ĵ���
			QPropertyAnimation *animation_hide = new QPropertyAnimation(this, "windowOpacity");
			animation_hide->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
			if (is_hide == true)
			{
				animation_hide->setStartValue(animation_transparent_hide_number);
			}
			else
			{
				animation_hide->setStartValue(animation_transparent_number);
			}
			animation_hide->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
			animation_hide->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
			connect(animation_hide, SIGNAL(finished()), this, SLOT(hide()));//���ش���
			dialog.exec();
		}

		//��ʱ������
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_C))
		{
			if (counter_mutex == 1)
			{
				CounterSet dialog;//������ʱ������
				dialog.exec();
			}
			else
			{

			}
		}

		//��ǩ����
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_E))
		{
			Note *dialog = new Note;//������ǩ
			dialog->set_font(setting_font_font);//��������
			dialog->setModal(false);//ָ��Ϊ��ģ̬�Ի���
			dialog->show();
		}

		//¼������
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_D))
		{
			if (sound_record_mutex == 1)
			{
				SoundRecord *dialog = new SoundRecord;//¼�����ڲ��÷�ģ̬����
				dialog->setModal(false);//ָ��Ϊ��ģ̬�Ի���
				dialog->show();
			}
			else
			{

			}
		}

		//�ػ�����
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_U))
		{
			bool shut_down_success = shutdown_or_reboot(1);//ִ�йػ�����
			if (!shut_down_success)
			{
				Help dialog;//��Ϣ��ʾ��
				dialog.setWindowTitle(tr("ʧ���ˣ�"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_SHUTDOWN_OR_RESTART_PATH_STRING);//��ʾ��Ϣ
				dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
			}
			else
			{

			}
		}

		//��������
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_R))
		{
			bool shut_down_success = shutdown_or_reboot(2);//ִ����������
			if (!shut_down_success)
			{
				Help dialog;//��Ϣ��ʾ��
				dialog.setWindowTitle(tr("ʧ���ˣ�"));
				dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_SHUTDOWN_OR_RESTART_PATH_STRING);//��ʾ��Ϣ
				dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
			}
			else
			{

			}
		}

		//�˳�����
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

	//ϵͳ����
	void Tools::create_system_tray_menu()//ϵͳ���̲˵�
	{
		system_tray_menu = new QMenu(this);
		system_tray_menu->addAction(action_set);//������ù���
		system_tray_menu->addAction(action_set_extra);//��Ӹ߼����ù���
		system_tray_menu->addAction(action_set_sound_record);//���¼�����ù���
		system_tray_menu->addSeparator();//���ӷָ���
		system_tray_menu->addAction(action_help);//�����Ϣ����
		system_tray_menu->addSeparator();//���ӷָ���
		system_tray_menu->addAction(action_exit);//����˳�����
		system_tray_icon->setContextMenu(system_tray_menu);//�Ѳ˵���������ͼ��
	}

	void Tools::create_system_tray_menu_action()//ϵͳ���̲˵�����
	{
		action_set = new QAction(QObject::tr("��������   "), this);//���ù���
		connect(action_set, SIGNAL(triggered()), this, SLOT(show_system_tray_action_set()));
		action_set_extra = new QAction(QObject::tr("�߼�����   "), this);//���ù���
		connect(action_set_extra, SIGNAL(triggered()), this, SLOT(show_system_tray_action_set_extra()));
		action_set_sound_record = new QAction(QObject::tr("¼������   "), this);//���ù���
		connect(action_set_sound_record, SIGNAL(triggered()), this, SLOT(show_system_tray_action_set_sound_record()));
		action_help = new QAction(QObject::tr("������Ϣ   "), this);//��Ϣ����
		connect(action_help, SIGNAL(triggered()), this, SLOT(show_system_tray_action_help()));
		action_exit = new QAction(QObject::tr("�˳�����   "), this);//�˳�����
		connect(action_exit, SIGNAL(triggered()), this, SLOT(show_system_tray_action_exit()));
	}

	//�ۺ���
	void Tools::system_tray_icon_clicked(QSystemTrayIcon::ActivationReason reason)
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

	void Tools::show_system_tray_action_set()//ϵͳ���̲˵����ù���
	{
		ToolsSet dialog;//�޸������ļ�
		dialog.exec();
	}

	void Tools::show_system_tray_action_set_extra()//ϵͳ���̲˵��߼����ù���
	{
		ToolsSetExtra dialog;//�޸������ļ�
		dialog.exec();
	}

	void Tools::show_system_tray_action_set_sound_record()//ϵͳ¼���˵��߼����ù���
	{
		SoundRecordSet dialog;//�޸������ļ�
		dialog.exec();
	}

	void Tools::show_system_tray_action_help()//ϵͳ���̲˵���Ϣ����
	{
		Help dialog;//��ʾ������Ϣ
		dialog.set_dialog_information_path(DIALOG_INFORMATION_HELP_PATH_STRING);
		dialog.exec();
	}

	void Tools::show_system_tray_action_exit()//ϵͳ���̲˵��˳�����
	{
		close_window_include_animation();//�رմ��ڲ��˳�����
	}

	void Tools::screenshot_fail()//��ͼʧ��
	{
		show();//����ʾ�ٲ��Ŷ���
		screenshot_end_mouse_event_disable = true;//��������������������������л�����ʾ״̬���¼��������������������֮ǰ����ֵ����������������������ʧȻ����ֵ�����
		setWindowOpacity(animation_transparent_number);//͸����ǿ�Ƹ�Ϊ������͸����
		main_picture.load(main_picture_normal_hole_path);//ǿ�ƽ������汳����Ϊδ����״̬
		resize(main_picture.size());
		move(extra_x_position, extra_y_position);//�޸Ĵ�����ʼ����
		update();
		QPropertyAnimation *animation_show = new QPropertyAnimation(this, "windowOpacity");
		animation_show->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_show->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_show->setEndValue(animation_transparent_number);
		animation_show->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		time_counter->stop();//����֮ǰ�������������Σ���ǿ���������ж�����ʱ�������������������������������Զ����غ������������������ʱ��ͼ������ͼ����������������ص�����
		time_counter->start();
	}

	void Tools::screenshot_success(QPoint pt1, QPoint pt2)//��ͼ�ɹ������������ڷ������ź�
	{

		//�����ͼ�����ڴ��ڸ���������������Ҫ�ֱ�����ʼ�����겻�����Ǹ��������������п����Ǹ�����ע��QPixmapʼ�������Ͻǵĵ���Ϊ���ε���ʼ��
		if ((pt2.x() - pt1.x()) > 1 && (pt2.y() - pt1.y()) > 1)//����ʼ��Ϊԭ�㡣��Ϊ��Ļ�������ǰ������Ͻ�Ϊԭ�㿪ʼ����ģ�y��������Ϊ���ģ�����Ҳ�������ַ�ʽ������Ҫͬʱ������Ϊ�߿�ȥ����1�����أ�����2������Ϊ���λ����յ�û�а����յ����ڵ���һȦ���أ�����ȥ���������������ľ���ֵС�ڵ���2�������֮������Ϊ��������Ĺ�ϵ����Ҫ����1���ص���������һ���ޣ��������⴦��
		{
			screenshot_picture = QPixmap::grabWindow(QApplication::desktop()->winId(), pt1.x() + 1, pt1.y() + 1, pt2.x() - pt1.x() - 2 + 1, pt2.y() - pt1.y() - 2 + 1);//���ؽ�ͼͼƬ��������ΪҪȥ����ͼ�߿����Խ�ͼ��ȼ�����2����
			QClipboard *clipborder = QApplication::clipboard();//����ͼд�������
			clipborder->setPixmap(screenshot_picture);
		}
		else if ((pt2.x() - pt1.x()) < -1 && (pt2.y() - pt1.y()) < -1)//�������ޣ�ԭ��ʼ�����ֹ������������λ�����һ���޵�����෴����˽�����������껥��
		{
			screenshot_picture = QPixmap::grabWindow(QApplication::desktop()->winId(), pt2.x() + 1, pt2.y() + 1, pt1.x() - pt2.x() - 2 + 1, pt1.y() - pt2.y() - 2 + 1);
			QClipboard *clipborder = QApplication::clipboard();
			clipborder->setPixmap(screenshot_picture);
		}
		else if ((pt2.x() - pt1.x()) > 1 && (pt2.y() - pt1.y()) < -1)//�ڶ����ޣ���Ҫ����ѡ����ʼ�㡣���Ͻǵĵ�������ǣ�(pt1.x(),pt2.y())
		{
			screenshot_picture = QPixmap::grabWindow(QApplication::desktop()->winId(), pt1.x() + 1, pt2.y() + 1, pt2.x() - pt1.x() - 2 + 1, pt1.y() - pt2.y() - 2 + 1);
			QClipboard *clipborder = QApplication::clipboard();
			clipborder->setPixmap(screenshot_picture);
		}
		else if ((pt2.x() - pt1.x()) < -1 && (pt2.y() - pt1.y()) > 1)//�������ޣ���Ҫ����ѡ����ʼ�㡣���Ͻǵĵ�������ǣ�(pt2.x(),pt1.y())
		{
			screenshot_picture = QPixmap::grabWindow(QApplication::desktop()->winId(), pt2.x() + 1, pt1.y() + 1, pt1.x() - pt2.x() - 2 + 1, pt2.y() - pt1.y() - 2 + 1);
			QClipboard *clipborder = QApplication::clipboard();
			clipborder->setPixmap(screenshot_picture);
		}
		else//���µ����һ�����ܽص�ͼ��ֱ�Ӱ�ʧ�ܴ���
		{

		}
		show();//����ʾ�ٲ��Ŷ���
		screenshot_end_mouse_event_disable = true;//��������������������������л�����ʾ״̬���¼��������������������֮ǰ����ֵ����������������������ʧȻ����ֵ�����
		setWindowOpacity(animation_transparent_number);//͸����ǿ�Ƹ�Ϊ������͸����
		main_picture.load(main_picture_normal_hole_path);//ǿ�ƽ������汳����Ϊδ����״̬
		resize(main_picture.size());
		move(extra_x_position, extra_y_position);//�޸Ĵ�����ʼ����
		update();
		QPropertyAnimation *animation_show = new QPropertyAnimation(this, "windowOpacity");
		animation_show->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_show->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_show->setEndValue(animation_transparent_number);
		animation_show->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		time_counter->stop();//����֮ǰ�������������Σ���ǿ���������ж�����ʱ�������������������������������Զ����غ������������������ʱ��ͼ������ͼ����������������ص�����
		time_counter->start();
	}

	void Tools::close_and_exit()//�ʹ������رմ��ڷ���һ��ʹ��
	{
		close();
		delete system_tray_icon;//ʹ��exit()֮��ϵͳ�������������������˱�����������
		delete system_tray_menu;
		delete action_set;
		delete action_set_extra;
		delete action_help;
		delete action_exit;
		delete time_counter;
		exit(0);
	}

	//��������
	void Tools::run_program(int index)//�����ⲿ���򡣸ú�������Ҫ������ں����Ĳ�����Ŀ��������ѡ������壨1����ڲ��������ǳ���Ŀ�꣨2����ڲ���������ֱ�Ӵ�
	{
		HINSTANCE return_value;//ָ������ֵ
		wstring transform_path= setting_function_program[index - 1].toStdWString();//��Qstringת��Ϊwstring������ת�����ᵼ������
		return_value = ShellExecute(NULL, L"open", transform_path.c_str(), NULL, NULL, SW_SHOWNORMAL);//�򿪳���
		if (setting_function_program[index - 1] != FILE_SETTING_CATALOG_2_UNDEFINE_DEFAULT_STRING)
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
	}

	bool Tools::shutdown_or_reboot(int status)//�ػ�������
	{
		HANDLE flag_get;
		TOKEN_PRIVILEGES privilege_get;
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &flag_get))//��ȡ���̱�־����ȡʧ�����˳�����
		{
			return false;
		}
		else
		{

		}
		if (status == 1)
		{

		}
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privilege_get.Privileges[0].Luid);//��ȡ�ػ���Ȩ��LUID
		privilege_get.PrivilegeCount = 1;
		privilege_get.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(flag_get, false, &privilege_get, 0, (PTOKEN_PRIVILEGES)NULL, 0);//��ȡ������̵Ĺػ���Ȩ
		if (GetLastError() != ERROR_SUCCESS)
		{
			return false;
		}
		else
		{

		}
		if (status == 1)
		{
			if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0))//�رռ����
			{
				return false;
			}
			else
			{
				close_window_include_animation();
				return true;
			}
		}
		else if (status == 2)
		{
			if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0))//���������
			{
				return false;	
			}
			else
			{
				close_window_include_animation();
				return true;
			}
		}
		else
		{
			if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0))//�رռ����
			{
				return false;
			}
			else
			{
				close_window_include_animation();
				return true;
			}
		}
	}

	void Tools::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
	{

		//�������а�ť�����򶯻��������ǰ�ٴε����ť�����´�������
		QList<QPushButton *> push_button = this->findChildren<QPushButton *>();
		foreach(QPushButton *push_button_disable, push_button)
		{
			push_button_disable->setEnabled(false);
		}
		QPropertyAnimation *animation_close = new QPropertyAnimation(this, "windowOpacity");
		animation_close->setDuration(WINDOW_ANIMATION_TIME_NUMBER);//���ڹرն���Ч��
		if (is_hide == true)
		{
			animation_close->setStartValue(animation_transparent_hide_number);
		}
		else
		{
			animation_close->setStartValue(animation_transparent_number);
		}
		animation_close->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_close->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		connect(animation_close, SIGNAL(finished()), this, SLOT(close_and_exit()));
	}

	void Tools::time_hide_animation_disappear()//���ع��̼�ʱ��������ʧ��������
	{
		QPropertyAnimation *animation_hide_disappear = new QPropertyAnimation(this, "windowOpacity");//��������ʧ����
		animation_hide_disappear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_hide_disappear->setStartValue(animation_transparent_number);
		animation_hide_disappear->setEndValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_hide_disappear->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		connect(animation_hide_disappear, SIGNAL(finished()), this, SLOT(time_hide_animation_appear()));
	}

	void Tools::time_hide_animation_appear()//���ع��̼�ʱ�����ڳ��ֶ�������
	{
		main_picture.load(main_picture_hide_hole_path);//�Ȼ��ñ�����Ȼ�󲥷Ŷ���
		resize(main_picture.size());
		move(extra_x_position, extra_y_position);//�޸Ĵ�����ʼ����
		update();
		setWindowOpacity(animation_transparent_hide_number);
		QPropertyAnimation *animation_hide_appear = new QPropertyAnimation(this, "windowOpacity");//��������ʧ����
		animation_hide_appear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_hide_appear->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_hide_appear->setEndValue(animation_transparent_hide_number);
		animation_hide_appear->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
		connect(animation_hide_appear, SIGNAL(finished()), this, SLOT(time_hide_repaint()));
	}

	void Tools::time_hide_repaint()//���ع��̼�ʱ�����ڻ��ƴ��ں���
	{
		time_counter->stop();//����رռ�ʱ������������ѭ����ʱ
		is_hide = true;//����Ϊ�����ڱ����أ����Լ������յ����ʾ�¼�
		screenshot_end_mouse_event_disable = false;//�������������¼�
	}

	void Tools::show_animation_appear()//��ʾ���̳��ֶ�������
	{
		main_picture.load(main_picture_normal_hole_path);//ͬ����Ҫ�Ȼ���������֮������ʾ����
		resize(main_picture.size());
		move(x_position, y_position);//�޸Ĵ�����ʼ����
		update();
		setWindowOpacity(animation_transparent_number);
		QPropertyAnimation *animation_show_appear = new QPropertyAnimation(this, "windowOpacity");//��������ʧ����
		animation_show_appear->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation_show_appear->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation_show_appear->setEndValue(animation_transparent_number);
		animation_show_appear->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}
}

