#include "define.h"

namespace rem
{

	//ȫ�ֱ�������
	extern int find_dialog_mutex;//ֻ������1�����Ҵ���

	//��������������
	Find::Find(QWidget *parent) : QDialog(parent)
	{
		
		//�����ʼ��
		//���¹����õ��˳�������Ҫ�޸������д
		find_dialog_mutex--;//����Ĵ�����Ŀ����1
		totalrandomnumber = DIALOG_RANDOM_MIN_NUMBER + rand() % (DIALOG_RANDOM_MAX_NUMBER - DIALOG_RANDOM_MIN_NUMBER + 1);//����ָ��������Ա��������ͼƬ������ͼƬ��ʽ
		setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);//ȥ�����ڱ��������Ҵ��ڿ���ͨ������������Ŵ���С
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
		ui.pushButton_next->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_next_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_next_pressed.png);}");
		ui.pushButton_exit->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_exit_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_exit_pressed.png);}");
		ui.pushButton_last->setStyleSheet("QPushButton{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_last_normal.png);}""QPushButton:hover{border-image: url(:/picture_notepad/dialogicon/picture_notepad/icon/dialog_find_last_pressed.png);}");
	
		//ȥ���ı��򱳾�
		ui.lineEdit_main->setStyleSheet("background-color: rgb(255, 255, 255, 0);border:0px solid #e1e0e0;");
	
		//����
		connect(ui.pushButton_last, SIGNAL(clicked()), this, SLOT(find_text_last()));
		connect(ui.pushButton_next, SIGNAL(clicked()), this, SLOT(find_text_next()));

		//�رհ�ť
		connect(ui.pushButton_close_window, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));
		connect(ui.pushButton_exit, SIGNAL(clicked()), this, SLOT(close_window_include_animation()));

		//���ò��ҿ�������ɫ
		QPalette lineedit_palette;
		if (totalrandomnumber == 1)//�������������ɫ
		{
			lineedit_palette.setColor(QPalette::Text, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(255, 83, 185, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(255, 83, 185, 64));
		}
		else if (totalrandomnumber == 2)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(133, 153, 212, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(133, 153, 212, 64));
		}
		else if (totalrandomnumber == 3)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(222, 63, 235, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(222, 63, 235, 64));
		}
		else if (totalrandomnumber == 4)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(242, 153, 93, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(242, 153, 93, 64));
		}
		else if (totalrandomnumber == 5)
		{
			lineedit_palette.setColor(QPalette::Text, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::HighlightedText, QColor(71, 185, 78, 255));
			lineedit_palette.setColor(QPalette::Highlight, QColor(71, 185, 78, 64));
		}
		else
		{

		}
		ui.lineEdit_main->setPalette(lineedit_palette);

		//�˳�ʱ���ٸô��������ڴ�й©
		setAttribute(Qt::WA_DeleteOnClose);

		//������������Ч����������ʾ�࣬Ҫ����ʾ���ܿ�����������֮�����ڹر��࣬Ҫ����ʾ���ܹرգ����򿴲�������
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(WINDOW_ANIMATION_TIME_NUMBER);
		animation->setStartValue(WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER);
		animation->setEndValue(WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER);
		animation->start(QAbstractAnimation::DeleteWhenStopped);//����ʱ�ͷ��ڴ�
	}
	Find::~Find()
	{
		find_dialog_mutex++;//����Ĵ�����Ŀ����1
	}

	//���ó�Ա����
	void Find::set_dialog_information_path(QString information_path)
	{
		dialog_information_path = information_path;
	}

	void Find::set_textedit(QTextEdit *main_textedit)
	{
		textedit_find = main_textedit;
	}

	//����Ϊ����¼�������ʵ��ȥ���������󴰿ڵ��ƶ�
	//��������������ʱ��������Ӧ����Ϊtrue�����õ���ǰ������
	void Find::mousePressEvent(QMouseEvent *event)
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
	void Find::mouseMoveEvent(QMouseEvent *event)
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
	void Find::mouseReleaseEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		m_bPressed = false;
	}

	//�����¼�����������д�����ԭ�����еļ�����Ӧ�����ǵ��������������޸Ļس����Ĺ��ܣ���Ҫ����ԭ����esc���Ĺ���
	void Find::keyPressEvent(QKeyEvent *event)
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

	void Find::paintEvent(QPaintEvent *)
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
		dialog_information_path_temp = dialog_information_path;//��Ϊ���¼���ִ�ж�Σ����Բ���ֱ��ʹ��dialog_information_path�������ÿ���ַ������ۼӵ���·������
		dialog_information_path_temp += QString::number(totalrandomnumber, 10);//�������ת��Ϊ·���е�һ����
		dialog_information_path_temp += DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING;
		background_picture.load(filepath);
		margin_picture.load((QString)DIALOG_MARGIN_PICTURE_PATH_STRING);
		chara_picture.load(chara_path);
		information_picture.load(dialog_information_path_temp);
		background_painter.drawPixmap(0, 0, DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, background_picture);
		chara_painter.drawPixmap(0, 0, DIALOG_SIZE_HEIGHT_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, chara_picture);//���ͼƬʹ�������Σ����Ϳ��봰�ڿ��һ��
		information_painter.drawPixmap(DIALOG_INFORMATION_FIND_X_OFFSET_NUMBER, DIALOG_INFORMATION_FIND_Y_OFFSET_NUMBER, DIALOG_INFORMATION_FIND_WIDTH_NUMBER, DIALOG_INFORMATION_FIND_HEIGHT_NUMBER, information_picture);//ָ�����ֲ��ֵ�λ�ò���ͼ
		margin_painter.drawPixmap(0, 0, DIALOG_SIZE_WIDTH_NUMBER, DIALOG_SIZE_HEIGHT_NUMBER, margin_picture);//�����ʾ���ⱻͼƬ����
	}

	void Find::find_text_last()//��ǰ�����ı�
	{
		QString find_text = ui.lineEdit_main->text();//��Ҫ���ҵ��ı�
		bool is_success;//�ж��Ƿ���ҳɹ�
		//ö��������ֱ���

		if (ui.checkBox_1->isChecked() == false && ui.checkBox_2->isChecked() == false)//Ĭ��
		{
			is_success = textedit_find->find(find_text, QTextDocument::FindBackward);
		}
		else if (ui.checkBox_1->isChecked() == true && ui.checkBox_2->isChecked() == false)//���ִ�Сд
		{
			is_success = textedit_find->find(find_text, QTextDocument::FindBackward | QTextDocument::FindCaseSensitively);
		}
		else if (ui.checkBox_1->isChecked() == false && ui.checkBox_2->isChecked() == true)//ȫ��ƥ��
		{
			is_success = textedit_find->find(find_text, QTextDocument::FindBackward | QTextDocument::FindWholeWords);
		}
		else if (ui.checkBox_1->isChecked() == true && ui.checkBox_2->isChecked() == true)//���ִ�Сд��ȫ��ƥ��
		{
			is_success = textedit_find->find(find_text, QTextDocument::FindBackward | QTextDocument::FindCaseSensitively | QTextDocument::FindWholeWords);
		}
		else
		{
			is_success = false;
		}
		if (!is_success)
		{
			Help dialog;//��Ϣ��ʾ��
			dialog.setWindowTitle(tr("�Ҳ���Ŷ����"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_FIND_PICTURE_PATH_STRING);
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else
		{

		}
	}

	void Find::find_text_next()//�������ı�
	{
		QString find_text = ui.lineEdit_main->text();//��Ҫ���ҵ��ı�
		bool is_success;//�ж��Ƿ���ҳɹ�

		//ö��������ֱ���
		if (ui.checkBox_1->isChecked() == false && ui.checkBox_2->isChecked() == false)//Ĭ��
		{
			is_success = textedit_find->find(find_text);
		}
		else if (ui.checkBox_1->isChecked() == true && ui.checkBox_2->isChecked() == false)//���ִ�Сд
		{
			is_success = textedit_find->find(find_text, QTextDocument::FindCaseSensitively);
		}
		else if (ui.checkBox_1->isChecked() == false && ui.checkBox_2->isChecked() == true)//ȫ��ƥ��
		{
			is_success = textedit_find->find(find_text, QTextDocument::FindWholeWords);
		}
		else if (ui.checkBox_1->isChecked() == true && ui.checkBox_2->isChecked() == true)//���ִ�Сд��ȫ��ƥ��
		{
			is_success = textedit_find->find(find_text, QTextDocument::FindCaseSensitively | QTextDocument::FindWholeWords);
		}
		else
		{
			is_success = false;
		}
		if (!is_success)
		{
			Help dialog;//��Ϣ��ʾ��
			dialog.setWindowTitle(tr("�Ҳ���Ŷ����"));
			dialog.set_dialog_information_path(DIALOG_INFORMATION_CANNOT_FIND_PICTURE_PATH_STRING);
			dialog.exec();//���������һ�䣬�Ի����ڴ�����ᱻ��������
		}
		else
		{

		}
	}

	void Find::close_window_include_animation()//�����رմ��ڶ����Ĺرմ��ڷ���
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

