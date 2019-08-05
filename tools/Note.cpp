#include "define.h"

namespace rem
{

	//��������������
	Note::Note(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		totalrandomnumber = DIALOG_NOTE_BACKGROUND_PICTURE_RANDOM_MIN_NUMBER + rand() % (DIALOG_NOTE_BACKGROUND_PICTURE_RANDOM_MAX_NUMBER - DIALOG_NOTE_BACKGROUND_PICTURE_RANDOM_MIN_NUMBER + 1);//����ָ��������Ա��������ͼƬ��ʽ
		setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint | windowFlags());//ȥ�����ڱ������������������в�����ִ���
		resize(DIALOG_SIZE_HEIGHT_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER);//������ǿ�Ƹ�Ϊ�˴�С
		setAttribute(Qt::WA_TranslucentBackground, true);//ʹ�ò����򴰿ڣ���ͼƬ͸��������ֽ�
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		setAttribute(Qt::WA_DeleteOnClose);//�˳�ʱ���ٸô��������ڴ�й©
		is_escape_pressed = false;//Ĭ��δ����esc�����˳�
		on_top = true;//��ʼʱ�������

		//����ͼƬ·��
		filepath = DIALOG_NOTE_BACKGROUND_PICTURE_FRONT_STRING + QString::number(totalrandomnumber, 10);
		filepath += DIALOG_NOTE_BACKGROUND_PICTURE_BACK_STRING;

		//���ؽ��棬�����������Ա�����汻֮��Ļ�ͼ����
		ui.setupUi(this);

		//���ø��ı�
		ui.textEdit_main->setAcceptRichText(false);

		//ȥ���ı��򱳾�������ֱ�����ûᵼ�����ֳ���һҳ���ֹ������󣬱������������������Ϊƽ����ʽ����ȥ���ı��򱳾��ͱ߽磬��Ϊ���Ʊ���
		ui.textEdit_main->setStyleSheet("background-color: rgb(255, 255, 255, 0);border:0px solid #e1e0e0;");

		//������ɫ
		QPalette text_palette;
		switch (totalrandomnumber)//�������ֺ�Highlight��ɫ
		{
		case 1:

			text_palette.setColor(QPalette::Text, QColor(255, 111, 111, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(255, 111, 111, 255));
			text_palette.setColor(QPalette::Highlight, QColor(255, 111, 111, 64));
			break;

		case 2:

			text_palette.setColor(QPalette::Text, QColor(91, 166, 222, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(91, 166, 222, 255));
			text_palette.setColor(QPalette::Highlight, QColor(91, 166, 222, 64));
			break;

		case 3:

			text_palette.setColor(QPalette::Text, QColor(151, 47, 151, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(151, 47, 151, 255));
			text_palette.setColor(QPalette::Highlight, QColor(151, 47, 151, 64));
			break;

		case 4:

			text_palette.setColor(QPalette::Text, QColor(250, 125, 0, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(250, 125, 0, 255));
			text_palette.setColor(QPalette::Highlight, QColor(250, 125, 0, 64));
			break;

		case 5:

			text_palette.setColor(QPalette::Text, QColor(100, 200, 20, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(100, 200, 20, 255));
			text_palette.setColor(QPalette::Highlight, QColor(100, 200, 20, 64));
			break;

		case 6:

			text_palette.setColor(QPalette::Text, QColor(255, 111, 111, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(255, 111, 111, 255));
			text_palette.setColor(QPalette::Highlight, QColor(255, 111, 111, 64));
			break;

		case 7:

			text_palette.setColor(QPalette::Text, QColor(250, 125, 0, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(250, 125, 0, 255));
			text_palette.setColor(QPalette::Highlight, QColor(250, 125, 0, 64));
			break;

		case 8:

			text_palette.setColor(QPalette::Text, QColor(91, 166, 222, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(91, 166, 222, 255));
			text_palette.setColor(QPalette::Highlight, QColor(91, 166, 222, 64));
			break;

		case 9:

			text_palette.setColor(QPalette::Text, QColor(100, 200, 20, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(100, 200, 20, 255));
			text_palette.setColor(QPalette::Highlight, QColor(100, 200, 20, 64));
			break;

		case 10:

			text_palette.setColor(QPalette::Text, QColor(151, 47, 151, 255));
			text_palette.setColor(QPalette::HighlightedText, QColor(151, 47, 151, 255));
			text_palette.setColor(QPalette::Highlight, QColor(151, 47, 151, 64));
			break;
		}
		ui.textEdit_main->setPalette(text_palette);

		//ȥ�������Կؼ����Ҽ��˵�
		ui.textEdit_main->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
		ui.textEdit_main->horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}
	Note::~Note()
	{

	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void Note::mousePressEvent(QMouseEvent *event)
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
	void Note::mouseMoveEvent(QMouseEvent *event)
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
	void Note::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ������������Ϊֻ��ȷ�ϲ�������������Ҫ��д����Ϊ�˱���ͳһ�����ǽ�������д
	void Note::keyPressEvent(QKeyEvent *event)
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
		else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_S))
		{
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
		}
		else
		{

		}
	}

	void Note::paintEvent(QPaintEvent *)
	{

		//���ƴ����õ���ͼƬ�����巽��������ָ��5�ֱ������֮���5���������ѡȡһ����ӳ�䵽����һ�ַ�����档�����Ƕ�Ӧ��ӳ���ϵ��[1,5]->��������[6,10]->���Σ�[11,15]->�ꥼ��[16,20]->�����,[21,25]->ǧҹ�����⣬֮�������ͼƬҲ�͹�������ʹ�õ�������йء�ÿ��������Ӧ3��ͼƬ��ÿ�����ѡȡ1�š�
		//���¹����õ��˳�������Ҫ�޸������д
		//����ͼƬ
		QPainter background_painter(this);//����
		QPixmap background_picture;
		background_picture.load(filepath);
		background_painter.drawPixmap(0, 0, DIALOG_SIZE_HEIGHT_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, background_picture);
	}

	//��������
	void Note::set_font(QString font)//�޸�����
	{
		ui.textEdit_main->setFont(QFont(font, 15, QFont::Normal, false));
	}

	//�ۺ���
	void Note::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

