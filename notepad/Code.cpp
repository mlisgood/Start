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
	Code::Code(QWidget *parent) : QDialog(parent)
	{

		//�����ʼ��
		totalrandomnumber = DIALOG_RANDOM_MIN_NUMBER + rand() % (DIALOG_RANDOM_MAX_NUMBER - DIALOG_RANDOM_MIN_NUMBER + 1);//����ָ��������Ա��������ͼƬ������ͼƬ��ʽ
		setWindowFlags(Qt::FramelessWindowHint | windowFlags());//ȥ�����ڱ�����
		resize(DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER);//������ǿ�Ƹ�Ϊ�˴�С
		setFixedSize(this->width(), this->height());//��ֹ�ı䴰�ڴ�С
		setAttribute(Qt::WA_QuitOnClose, false);//�ô��ڹر�ʱ�����˳�����
		is_escape_pressed = false;//������esc���˳�����

		//ͼƬ·��
		//����ͼƬ·��
		filepath = DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING + QString::number(totalrandomnumber, 10);
		filepath += DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING;

		//���ͼƬ·��
		chara_path = DIALOG_CHARA_PICTURE_PATH_FRONT_STRING;
		QString chara_path_number = QString::number(totalrandomnumber, 10);//�������ת��Ϊ·���е�һ����
		chara_path += chara_path_number;
		chara_path += DIALOG_CHARA_PICTURE_PATH_BREAK_STRING;
		chara_path += QString::number(DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER + rand() % (DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER - DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER + 1), 10);//�ӵ�ǰϵ�е�3��ͼƬ����ѡȡһ�Ų����ӵ�·����
		chara_path += DIALOG_CHARA_PICTURE_PATH_BACK_STRING;

		//���ؽ��棬�����������Ա�����汻֮��Ļ�ͼ����
		ui.setupUi(this);

		//���ذ�ť��ʽ
		ui.pushButton_close_dialog->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_exit_pressed.png);}");
		ui.pushButton_accept_dialog->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_code_accept_pressed.png);}");

		//����������ɫ
		QPalette lineedit_palette;
		if (totalrandomnumber == 1)//�������������ɫ
		{
			lineedit_palette.setColor(QPalette::Text, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(255, 83, 185, 64));
		}
		else if (totalrandomnumber == 2)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(133, 153, 212, 64));
		}
		else if (totalrandomnumber == 3)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(222, 63, 235, 64));
		}
		else if (totalrandomnumber == 4)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(242, 153, 93, 64));
		}
		else if (totalrandomnumber == 5)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::WindowText, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(71, 185, 78, 64));
		}
		else
		{

		}
		ui.comboBox_1->setPalette(lineedit_palette);
		ui.label->setPalette(lineedit_palette);

		//������ʽ�ļ�������ֱ��ʹ���������ô����е���ʽ�ļ�����
		QString stylesheet_file_name = DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_STRING;
		stylesheet_file_name += QString::number(totalrandomnumber, 10);
		stylesheet_file_name += DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_BACK_STRING;
		QFile stylesheet_file(stylesheet_file_name);
		stylesheet_file.open(QFile::ReadOnly);
		ui.comboBox_1->setStyleSheet(stylesheet_file.readAll());
		stylesheet_file.close();

		//����label��ʽ
		ui.label->setWordWrap(true);//������

		//ȥ�������Կؼ����Ҽ��˵�
		QList<QScrollBar *> scroll_bar = this->findChildren<QScrollBar *>();//�����޷��ó��淽ʽ���combobox�Ĺ����������ʹ�ø÷�����������ͬ���Ϳؼ������в���
		foreach(QScrollBar *scroll_bar_style_control, scroll_bar)
		{
			scroll_bar_style_control->setContextMenuPolicy(Qt::NoContextMenu);
		}

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�

		//��Ͽ����ݸı�
		connect(ui.comboBox_1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(combobox_change(const QString &)));

		//�رհ�ť
		connect(ui.pushButton_close_window, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));
		connect(ui.pushButton_close_dialog, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));

		//ȷ����ť
		connect(ui.pushButton_accept_dialog, SIGNAL(clicked()), this, SLOT(dialog_accept()));
	}
	Code::~Code()
	{

	}

	//���ó�Ա����
	void Code::set_code_information(QString* code_information, QLabel *code_label_main_dialog, int status)//��ȡ������Ϣ���Ƿ��ڶ����Ʊ༭״̬
	{
		code_receive = code_information;//��������ڱ���
		code_label = code_label_main_dialog;//��������������Ϣ��ʾ��
		hex_status = status;//����������Ƿ��ڶ����Ʊ༭״̬
		QString code_receive_transform = *code_receive;
		ui.comboBox_1->setCurrentText(code_receive_transform);
		combobox_change(code_receive_transform);//�޸ı�������ʾ����
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void Code::mousePressEvent(QMouseEvent *event)
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
	void Code::mouseMoveEvent(QMouseEvent *event)
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
	void Code::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ������������Ϊֻ��ȷ�ϲ�������������Ҫ��д����Ϊ�˱���ͳһ�����ǽ�������д
	void Code::keyPressEvent(QKeyEvent *event)
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

	void Code::paintEvent(QPaintEvent *)
	{

		//���ƴ����õ���ͼƬ�����巽��������ָ��5�ֱ������֮���5���������ѡȡһ����ӳ�䵽����һ�ַ�����档�����Ƕ�Ӧ��ӳ���ϵ��[1,5]->��������[6,10]->���Σ�[11,15]->�ꥼ��[16,20]->�����,[21,25]->ǧҹ�����⣬֮�������ͼƬҲ�͹�������ʹ�õ�������йء�ÿ��������Ӧ3��ͼƬ��ÿ�����ѡȡ1�š�
		//���¹����õ��˳�������Ҫ�޸������д
		//����ͼƬ
		QString dialog_information_path_temp;//��ʱ�洢��ϢͼƬ·��
		QPainter background_painter(this);//����
		QPainter margin_painter(this);//�߿�
		QPainter chara_painter(this);//����
		QPainter information_painter(this);//����
		QPixmap background_picture;
		QPixmap margin_picture;
		QPixmap chara_picture;
		QPixmap information_picture;
		dialog_information_path_temp = DIALOG_INFORMATION_CODE_PICTURE_PATH_STRING;
		dialog_information_path_temp += QString::number(totalrandomnumber, 10);//�������ת��Ϊ·���е�һ����
		dialog_information_path_temp += DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING;
		background_picture.load(filepath);
		margin_picture.load((QString)DIALOG_MARGIN_PICTURE_PATH_STRING);
		chara_picture.load(chara_path);
		information_picture.load(dialog_information_path_temp);
		background_painter.drawPixmap(0, 0, DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, background_picture);
		chara_painter.drawPixmap(0, 0, DIALOG_SIZE_HEIGHT_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, chara_picture);//���ͼƬʹ�������Σ����Ϳ��봰�ڿ��һ��
		information_painter.drawPixmap(DIALOG_SIZE_HEIGHT_NUMBER, 0, DIALOG_SIZE_WIDTH_NUMBER - DIALOG_SIZE_HEIGHT_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, information_picture);//���ֲ���Ӧ�ô���ߵ�ͼƬ���ֵ��ұ�Ե��ʼ
		margin_painter.drawPixmap(0, 0, DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, margin_picture);//�����ʾ���ⱻͼƬ����
	}

	void Code::combobox_change(const QString &code_string)//��Ͽ�ѡ��
	{
		if (code_string == tr("Big5"))
		{
			ui.label->setText(tr("Big5�������������룬��ʹ�÷���������������õĵ��Ժ����ַ�����׼��"));
		}
		else if (code_string == tr("Big5-HKSCS"))
		{
			ui.label->setText(tr("Big5-HKSCS������۵���ʹ�õı��롣"));
		}
		else if (code_string == tr("CP949"))
		{
			ui.label->setText(tr("CP949��codepageϵ�е�һ�֣�֧�ֺ�����ĸ��"));
		}
		else if (code_string == tr("EUC-JP"))
		{
			ui.label->setText(tr("EUC-JP���������ձ�JISX0208���ɳ�JISC6226����JISX0212�ּ����ַ���"));
		}
		else if (code_string == tr("EUC-KR"))
		{
			ui.label->setText(tr("EUC-KR�������溫��KSX1001�ּ����ɳ�KSC5601�����ַ����˹����KSX2901���ɳ�KSC5861�����塣"));
		}
		else if (code_string == tr("GB18030"))
		{
			ui.label->setText(tr("GB18030���й���GB2312-1980��GB13000.1-1993֮������Ҫ�ĺ��ֱ����׼�����й������ϵͳ������ѭ�Ļ����Ա�׼֮һ��"));
		}
		else if (code_string == tr("HP-ROMAN8"))
		{
			ui.label->setText(tr("HP-ROMAN8��һ��8λ���ֽ��ַ����룬��Ҫ����HP-UX�����Hewlett-Packard�Լ�PCL���ݵĴ�ӡ���ϡ�"));
		}
		else if (code_string == tr("IBM 850"))
		{
			ui.label->setText(tr("IBM 850����CP850���������Һ͵�������Ҫ����ҳ��Ĭ��OEM����ҳ��֧��Latin-1���롣"));
		}
		else if (code_string == tr("IBM 866"))
		{
			ui.label->setText(tr("IBM 866����CP866������DOS��OS/2�����ڱ�д������Ľű��Ĵ���ҳ��֧��Cyril��ĸ��"));
		}
		else if (code_string == tr("IBM 874"))
		{
			ui.label->setText(tr("IBM 866����CP874��֧��̩����ĸ��"));
		}
		else if (code_string == tr("ISO 2022-JP"))
		{
			ui.label->setText(tr("ISO 2022-JP��ISO/IEC 2022ϵ�е�һ�֣��������ı��롣"));
		}
		else if (code_string == tr("ISO 8859-1"))
		{
			ui.label->setText(tr("ISO 8859-1��Latin-1������ŷ�������ã������·���������ĸ��"));
		}
		else if (code_string == tr("ISO 8859-2"))
		{
			ui.label->setText(tr("ISO 8859-2��Latin-2����¼��ŷ�ַ���"));
		}
		else if (code_string == tr("ISO 8859-3"))
		{
			ui.label->setText(tr("ISO 8859-3��Latin-3����¼��ŷ�ַ���"));
		}
		else if (code_string == tr("ISO 8859-4"))
		{
			ui.label->setText(tr("ISO 8859-4��Latin-4����¼��ŷ�ַ���"));
		}
		else if (code_string == tr("ISO 8859-5"))
		{
			ui.label->setText(tr("ISO 8859-5��Cyrillic����¼˹������ϵ�ַ���"));
		}
		else if (code_string == tr("ISO 8859-6"))
		{
			ui.label->setText(tr("ISO 8859-6��Arabic����¼��������ϵ�ַ���"));
		}
		else if (code_string == tr("ISO 8859-7"))
		{
			ui.label->setText(tr("ISO 8859-7��Greek����¼ϣ���ַ���"));
		}
		else if (code_string == tr("ISO 8859-8"))
		{
			ui.label->setText(tr("ISO 8859-8��Hebrew����¼�������ַ���"));
		}
		else if (code_string == tr("ISO 8859-9"))
		{
			ui.label->setText(tr("ISO 8859-9��Latin-5��Turkish����¼�������ַ���"));
		}
		else if (code_string == tr("ISO 8859-10"))
		{
			ui.label->setText(tr("ISO 8859-10��Latin-6��Nordic����¼��ŷ����Ҫָ˹������ά�ǰ뵺�����ַ���"));
		}
		else if (code_string == tr("ISO 8859-13"))
		{
			ui.label->setText(tr("ISO 8859-13��Latin-7����Ҫ���ǲ��޵ĺ���������ַ��ţ�Ҳ����һЩ��Latin-6����©������ά���ַ���"));
		}
		else if (code_string == tr("ISO 8859-14"))
		{
			ui.label->setText(tr("ISO 8859-14��Latin-8���˱��뽫Latin-1�е�ĳЩ���Ż�������������ַ���"));
		}
		else if (code_string == tr("ISO 8859-15"))
		{
			ui.label->setText(tr("ISO 8859-15��Latin-9���˱��뽫Latin-1�н����õ��ķ��Ż��ɵ�����©�ķ��ĺͷ�����ĸ�����Ұ�Ӣ������Ԫ֮��Ľ�Ǯ���Ż�����ŷ�˻��ҷ��š�"));
		}
		else if (code_string == tr("ISO 8859-16"))
		{
			ui.label->setText(tr("ISO 8859-16��Latin-10�����ǰ�������������޵�������������������������������Ｐ˹����������ȶ���ŷ�������ԡ�"));
		}
		else if (code_string == tr("Iscii-Bng"))
		{
			ui.label->setText(tr("Iscii-Bng��Iscii�����ʱ�׼��Ϣ���������һ�֡�"));
		}
		else if (code_string == tr("Iscii-Dev"))
		{
			ui.label->setText(tr("Iscii-Dev��Iscii�����ʱ�׼��Ϣ���������һ�֡�"));
		}
		else if (code_string == tr("Iscii-Gjr"))
		{
			ui.label->setText(tr("Iscii-Gjr��Iscii�����ʱ�׼��Ϣ���������һ�֡�"));
		}
		else if (code_string == tr("Iscii-Knd"))
		{
			ui.label->setText(tr("Iscii-Knd��Iscii�����ʱ�׼��Ϣ���������һ�֡�"));
		}
		else if (code_string == tr("Iscii-Mlm"))
		{
			ui.label->setText(tr("Iscii-Mlm��Iscii�����ʱ�׼��Ϣ���������һ�֡�"));
		}
		else if (code_string == tr("Iscii-Ori"))
		{
			ui.label->setText(tr("Iscii-Ori��Iscii�����ʱ�׼��Ϣ���������һ�֡�"));
		}
		else if (code_string == tr("Iscii-Pnj"))
		{
			ui.label->setText(tr("Iscii-Pnj��Iscii�����ʱ�׼��Ϣ���������һ�֡�"));
		}
		else if (code_string == tr("Iscii-Tlg"))
		{
			ui.label->setText(tr("Iscii-Tlg��Iscii�����ʱ�׼��Ϣ���������һ�֡�"));
		}
		else if (code_string == tr("Iscii-Tml"))
		{
			ui.label->setText(tr("Iscii-Tml��Iscii�����ʱ�׼��Ϣ���������һ�֡�"));
		}
		else if (code_string == tr("KOI8-R"))
		{
			ui.label->setText(tr("KOI8-R��KOI-8ϵ�е�˹��������8λԪ���룬�����Ｐ����������ʹ�á�"));
		}
		else if (code_string == tr("KOI8-U"))
		{
			ui.label->setText(tr("KOI8-U��KOI-8ϵ�е�˹��������8λԪ���룬���ڿ�����ʹ�á�"));
		}
		else if (code_string == tr("Macintosh"))
		{
			ui.label->setText(tr("�˱����޽��ܡ�"));
		}
		else if (code_string == tr("Shift-JIS"))
		{
			ui.label->setText(tr("Shift-JIS���ձ�����ϵͳ���õı�����˱���������ȫ�Ǽ����������ĸ��ƽ������Ƭ���������ż����ﺺ�֡�"));
		}
		else if (code_string == tr("TIS-620"))
		{
			ui.label->setText(tr("�˱����޽��ܡ�"));
		}
		else if (code_string == tr("TSCII"))
		{
			ui.label->setText(tr("TSCII��̩�׶�������Ϣ�����룬��һ����8λ�Ļ������ṩ̩�׶������ֻ��ı��롣"));
		}
		else if (code_string == tr("UTF-8"))
		{
			ui.label->setText(tr("UTF-8������룬��һ�����Unicode�Ŀɱ䳤���ַ����룬������ʾ���ġ�Ӣ�ġ����ĵȶ������ԡ��������ڲ�ʹ�õ�Ĭ�ϱ���Ҳ��UTF-8��"));
		}
		else if (code_string == tr("UTF-16"))
		{
			ui.label->setText(tr("UTF-16��Unicode��һ�ָ�ʽ���˱��뽫�󲿷��ַ�����2�ֽڵĳ��ȴ洢�����޷�����ASCII���롣"));
		}
		else if (code_string == tr("UTF-16BE"))
		{
			ui.label->setText(tr("UTF-16BE��BEָ����Big Endian����Unicode��һ�ָ�ʽ���˱��뽫�ַ����մ�β��ķ�ʽ�洢��ʹ�ô˱���ʱ�������ǰ������FEFF��ǣ��������򲻻���øñ�ǡ�"));
		}
		else if (code_string == tr("UTF-16LE"))
		{
			ui.label->setText(tr("UTF-16LE��LEָ����Little Endian����Unicode��һ�ָ�ʽ���˱��뽫�ַ�����Сβ��ķ�ʽ�洢��ʹ�ô˱���ʱ�������ǰ������FFFE��ǣ��������򲻻���øñ�ǡ�"));
		}
		else if (code_string == tr("UTF-32"))
		{
			ui.label->setText(tr("UTF-32��Unicode��һ�ָ�ʽ���˱��뽫�����ַ�����4�ֽڵĳ��ȴ洢��ռ�ÿռ�ǳ���"));
		}
		else if (code_string == tr("UTF-32BE"))
		{
			ui.label->setText(tr("UTF-32BE��BEָ����Big Endian����Unicode��һ�ָ�ʽ���˱��뽫�ַ����մ�β��ķ�ʽ�洢��ʹ�ô˱���ʱ�������ǰ������0000FEFF��ǣ��������򲻻���øñ�ǡ�"));
		}
		else if (code_string == tr("UTF-32LE"))
		{
			ui.label->setText(tr("UTF-32LE��LEָ����Little Endian����Unicode��һ�ָ�ʽ���˱��뽫�ַ�����Сβ��ķ�ʽ�洢��ʹ�ô˱���ʱ�������ǰ������0000FFFE��ǣ��������򲻻���øñ�ǡ�"));
		}
		else if (code_string == tr("Windows-1250"))
		{
			ui.label->setText(tr("Windows-1250��ANSI�����һ�֣�������ŷ������ĸ���˱���Ҳ����codepage�ķ��롣"));
		}
		else if (code_string == tr("Windows-1251"))
		{
			ui.label->setText(tr("Windows-1251��ANSI�����һ�֣�������˹��������ĸ���˱���Ҳ����codepage�ķ��롣"));
		}
		else if (code_string == tr("Windows-1252"))
		{
			ui.label->setText(tr("Windows-1252��ANSI�����һ�֣�������ŷ������ĸ���˱���Ҳ����codepage�ķ��롣"));
		}
		else if (code_string == tr("Windows-1253"))
		{
			ui.label->setText(tr("Windows-1253��ANSI�����һ�֣�����ϣ������ĸ���˱���Ҳ����codepage�ķ��롣"));
		}
		else if (code_string == tr("Windows-1254"))
		{
			ui.label->setText(tr("Windows-1254��ANSI�����һ�֣���������������ĸ���˱���Ҳ����codepage�ķ��롣"));
		}
		else if (code_string == tr("Windows-1255"))
		{
			ui.label->setText(tr("Windows-1255��ANSI�����һ�֣�����ϣ��������ĸ���˱���Ҳ����codepage�ķ��롣"));
		}
		else if (code_string == tr("Windows-1256"))
		{
			ui.label->setText(tr("Windows-1256��ANSI�����һ�֣���������������ĸ���˱���Ҳ����codepage�ķ��롣"));
		}
		else if (code_string == tr("Windows-1257"))
		{
			ui.label->setText(tr("Windows-1257��ANSI�����һ�֣�������ɳ���������ά���Ｐ����������ĸ���˱���Ҳ����codepage�ķ��롣"));
		}
		else if (code_string == tr("Windows-1258"))
		{
			ui.label->setText(tr("Windows-1257��ANSI�����һ�֣�����Խ����ĸ���˱���Ҳ����codepage�ķ��롣"));
		}
		else
		{
			ui.label->setText(tr("UTF-8������룬��һ�����Unicode�Ŀɱ䳤���ַ����룬������ʾ���ġ�Ӣ�ġ����ĵȶ������ԡ��������ڲ�ʹ�õ�Ĭ�ϱ���Ҳ��UTF-8��"));
		}
	}

	void Code::dialog_accept()//ȷ�ϲ���
	{
		QString information_code = ui.comboBox_1->currentText();//��ű�����Ϣ
		if (hex_status == WINDOW_TOOL_TOHEX_STATUS_YES_FLAG)//�ڶ����Ʊ༭״���£�ֻ�޸������ļ������ݸ����������ݣ������޸���������ʾ
		{

		}
		else
		{
			code_label->setText(information_code);//�޸������������Ϣ��ʾ
		}
		*code_receive = information_code;//��������Ϣ����������
		ofstream setting_file_code;//�������ļ�д����Ϣ
		QString file_code_input = FILE_CODE_OUTPUT_FILE_PATH_STRING;
		string file_code_input_final = string((const char *)file_code_input.toLocal8Bit());
		setting_file_code.open(file_code_input_final, ios_base::out);//���ļ������������򴴽�
		if (!setting_file_code.is_open())//���ļ�ʧ��
		{
			
		}
		else
		{
			string information_code_temp = string((const char *)information_code.toLocal8Bit());//ת��Ϊstring
			setting_file_code << information_code_temp;//д�������ļ�
			setting_file_code.close();
		}
		close_window_include_animation();//�رմ���
	}

	void Code::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

