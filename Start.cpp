#include "define.h"

namespace rem
{

	//��������������
	Start::Start(QWidget *parent) : QMainWindow(parent)
	{

		//�����ʼ��
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);//ȥ�����ڱ��������Ҵ��ڿ���ͨ������������Ŵ���С
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, true);//�ô��ڹر�ʱ���˳�����
		setAttribute(Qt::WA_WState_WindowOpacitySet, true);//�ô�������ֱ������͸����
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�

		//����ͼƬ
		main_pixmap.load(WINDOW_START_BACKGROUND_PICTURE_PATH_STRING);
		resize(main_pixmap.size());

		//���ؽ��棬�����������Ա�����汻֮��Ļ�ͼ����
		ui.setupUi(this);
	
		//�źź���
		connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(item1_clicked()));//item1
		connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(item2_clicked()));//item2
		connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(item3_clicked()));//item3
		connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(item4_clicked()));//item4
		connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(item5_clicked()));//item5

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}
	Start::~Start()
	{

	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void Start::mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bPressed = true;
			m_point = event->pos();
		}
	}
	//�������������£����ƶ�����λ��
	void Start::mouseMoveEvent(QMouseEvent *event)
	{
		if (m_bPressed)
			move(event->pos() - m_point + pos());
	}

	//���δ�����£�����Ӧ����Ϊfalse
	void Start::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);

		m_bPressed = false;
	}

	void Start::paintEvent(QPaintEvent *)
	{

		//���Ʊ���
		QPainter background_painter(this);
		background_painter.drawPixmap(0, 0, main_pixmap.width(), main_pixmap.height(), main_pixmap);
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ�
	void Start::keyPressEvent(QKeyEvent *event)
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

	//��ť�¼�
	//Item1_notepad
	void Start::item1_clicked()//ָ����ť�����
	{

		//����ҵ���Ӧ��������򿪣�Ȼ��رոó��򣻷��򣬲��رոó��򣬲��ҳ�����ʾ����
		HINSTANCE return_value;//ָ������ֵ
		return_value = ShellExecute(NULL, L"open", L".\\Notepad.exe", NULL, NULL, SW_SHOWNORMAL);//�򿪳���
		if (return_value == (HINSTANCE)0)//�ڴ治��
		{
			Filemissing dialog;//��ʾ��ʾ��
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_1_FLAG);//ʹ��״̬1
			dialog.setWindowTitle(tr("����ʧ���ˣ�"));
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else if (return_value >= (HINSTANCE)1 && return_value <= (HINSTANCE)31)//�������ֱ��ͳһ����Ϊ�޷���ָ������
		{
			Filemissing dialog;//��ʾ��ʾ��
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_2_FLAG);//ʹ��״̬2
			dialog.setWindowTitle(tr("����ʧ���ˣ�"));
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else if (return_value >= (HINSTANCE)32)//�Ѿ��򿪣���������
		{

		}
		else//�����쳣���
		{

		}
	}

	void Start::item2_clicked()//ָ����ť�����
	{

		//����ҵ���Ӧ��������򿪣�Ȼ��رոó��򣻷��򣬲��رոó��򣬲��ҳ�����ʾ����
		HINSTANCE return_value;//ָ������ֵ
		return_value = ShellExecute(NULL, L"open", L".\\Tools.exe", NULL, NULL, SW_SHOWNORMAL);//�򿪳���
		if (return_value == (HINSTANCE)0)//�ڴ治��
		{
			Filemissing dialog;//��ʾ��ʾ��
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_1_FLAG);//ʹ��״̬1
			dialog.setWindowTitle(tr("����ʧ���ˣ�"));
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else if (return_value >= (HINSTANCE)1 && return_value <= (HINSTANCE)31)//�������ֱ��ͳһ����Ϊ�޷���ָ������
		{
			Filemissing dialog;//��ʾ��ʾ��
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_2_FLAG);//ʹ��״̬2
			dialog.setWindowTitle(tr("����ʧ���ˣ�"));
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else if (return_value >= (HINSTANCE)32)//�Ѿ��򿪣���������
		{

		}
		else//�����쳣���
		{

		}
	}

	void Start::item3_clicked()//ָ����ť�����
	{

		//����ҵ���Ӧ��������򿪣�Ȼ��رոó��򣻷��򣬲��رոó��򣬲��ҳ�����ʾ����
		HINSTANCE return_value;//ָ������ֵ
		return_value = ShellExecute(NULL, L"open", L".\\Lock.exe", NULL, NULL, SW_SHOWNORMAL);//�򿪳���
		if (return_value == (HINSTANCE)0)//�ڴ治��
		{
			Filemissing dialog;//��ʾ��ʾ��
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_1_FLAG);//ʹ��״̬1
			dialog.setWindowTitle(tr("����ʧ���ˣ�"));
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else if (return_value >= (HINSTANCE)1 && return_value <= (HINSTANCE)31)//�������ֱ��ͳһ����Ϊ�޷���ָ������
		{
			Filemissing dialog;//��ʾ��ʾ��
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_2_FLAG);//ʹ��״̬2
			dialog.setWindowTitle(tr("����ʧ���ˣ�"));
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else if (return_value >= (HINSTANCE)32)//�Ѿ��򿪣���������
		{

		}
		else//�����쳣���
		{

		}
	}

	void Start::item4_clicked()//ָ����ť�����
	{

		//����ҵ���Ӧ��������򿪣�Ȼ��رոó��򣻷��򣬲��رոó��򣬲��ҳ�����ʾ����
		HINSTANCE return_value;//ָ������ֵ
		return_value = ShellExecute(NULL, L"open", L".\\Desktop.exe", NULL, NULL, SW_SHOWNORMAL);//�򿪳���
		if (return_value == (HINSTANCE)0)//�ڴ治��
		{
			Filemissing dialog;//��ʾ��ʾ��
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_1_FLAG);//ʹ��״̬1
			dialog.setWindowTitle(tr("����ʧ���ˣ�"));
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else if (return_value >= (HINSTANCE)1 && return_value <= (HINSTANCE)31)//�������ֱ��ͳһ����Ϊ�޷���ָ������
		{
			Filemissing dialog;//��ʾ��ʾ��
			dialog.set_dialog_information_status(DIALOG_INFORMATION_STATUS_2_FLAG);//ʹ��״̬2
			dialog.setWindowTitle(tr("����ʧ���ˣ�"));
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else if (return_value >= (HINSTANCE)32)//�Ѿ��򿪣���������
		{

		}
		else//�����쳣���
		{

		}
	}

	void Start::item5_clicked()//ָ����ť�����
	{
		copy_files(FILE_COPY_SOURCE_1_PATH_STRING, FILE_COPY_TARGET_1_PATH_STRING);
		copy_files(FILE_COPY_SOURCE_2_PATH_STRING, FILE_COPY_TARGET_2_PATH_STRING);
		copy_files(FILE_COPY_SOURCE_3_PATH_STRING, FILE_COPY_TARGET_3_PATH_STRING);
		copy_files(FILE_COPY_SOURCE_4_PATH_STRING, FILE_COPY_TARGET_4_PATH_STRING);
	}

	//��������
	bool Start::copy_files(const QString &source_dir, const QString &target_dir)//�����ļ���
	{
		QDir sourceDir(source_dir);
		QDir targetDir(target_dir);
		if (!targetDir.exists())//Ŀ��Ŀ¼�������򴴽�
		{
			if (!targetDir.mkdir(targetDir.absolutePath()))
			{
				return false;
			}
			else
			{

			}
		}
		else
		{

		}
		QFileInfoList fileInfoList = sourceDir.entryInfoList();
		foreach(QFileInfo fileInfo, fileInfoList)
		{
			if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			{
				continue;
			}
			else
			{

			}
			if (fileInfo.isDir())//��ΪĿ¼ʱ���ݹ����copy
			{
				if (!copy_files(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName())))
				{
					return false;
				}
				else
				{

				}
			}
			else//�����ļ����Ƚ���ɾ��
			{
				if (targetDir.exists(fileInfo.fileName()))
				{
					targetDir.remove(fileInfo.fileName());
				}
				else
				{

				}
				if (!QFile::copy(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName())))//�����ļ�
				{
					return false;
				}
				else
				{

				}
			}
		}
		return true;
	}

	void Start::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

