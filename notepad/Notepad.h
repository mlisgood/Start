#ifndef NOTEPAD_H
#define NOTEPAD_H

#include "define.h"

namespace rem
{

	//ʹ�ñ�׼�����ռ�
	using std::string;

	class Notepad : public QMainWindow
	{
		Q_OBJECT

	private:

		Ui::NotepadClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QTimer *chara_picture_timer;//��ʾ����ͼ���ʱ��
		QPixmap chara_picture;//��������ͼƬ
		QPixmap chara_picture_extra;//������������״̬ͼƬ
		QPixmap margin_picture;//���߽�ͼƬ
		QLabel *chara_picture_label;//����ͼ����ʾ�õ��ı�ǩ
		QLabel *margin_picture_label;//�߿�ͼ����ʾ�õ��ı�ǩ
		QStringList setting_text;//���������ı����ͺ�׺
		QStringList *setting_text_address;//���������ı����ͺ�׺��ַ
		QStringList setting_binary;//�������ö��������ͺ�׺
		QStringList *setting_binary_address;//�������ö��������ͺ�׺��ַ
		QString dialog_information;//��ʾ����Ϣ����
		QString current_file_name;//��ǰ�ļ���
		QString file_dialog_file_name;//���ڴ��뱣���ļ����ڴ�����ļ���
		QString *file_dialog_file_name_address;//���ڴ��뱣���ļ����ڴ�����ļ�����ַ
		QString *text_code;//�ļ�����
		QString code_undefine;//�ļ�����Ĭ��ֵ
		QString chara_path_normal;//����������ͨ
		QString chara_path_close_eye;//���������л�
		QString setting_default_open_method;//�������ô��ļ�Ĭ�Ϸ�ʽ
		QString *setting_default_open_method_address;//�������ô��ļ�Ĭ�Ϸ�ʽ��ַ
		string args_string;//�������ڲ���
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool file_dialog_status;//ȷ�����뱣���ļ��������Ƿ�ѡ��򿪻򱣴��ļ���falseΪ�˳���trueΪ�򿪻򱣴�
		bool *file_dialog_status_address;//ȷ�����뱣���ļ��������Ƿ�ѡ��򿪻򱣴��ļ��ж�����ַ
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��
		bool setting_bool_value[3];//�������ò���ֵ���ֱ��ʾ�������ô��ڵ�����ѡ��
		bool *setting_bool_value_address[3];//�������ò���ֵ��ַ
		int chara_randnumber;//��ʾ����ͼ�������
		int randnumber;//���ڻ�ͼ�������
		int font_randnumber;//�����ɫ���ļ�������ʹ�õ������
		int timer_interval_number;//��ʱ�����ʱ��
		int timer_chara_status;//��������״̬��������ʱ�����ʱ�䳤��
		int *timer_chara_status_address;//��������״̬��ַ
		int hex_status;//�����Ƿ���ʮ������״̬
		int setting_size[2];//�������ô����ļ����С���ֱ��ʾtext��binary
		int *setting_size_address[2];//�������ô����ļ����С��ַ
		int progress_bar_change_color;//�����������Ƿ��Ѿ��л���ɫ

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//��������������
		Notepad(QWidget *parent = Q_NULLPTR);
		~Notepad();

		//�����ļ�����
		void setting_file_read();//�����ļ���ȡ
		void setting_file_font_read();//���������ļ���ȡ����Ϊ�����ļ���֮��Ҳ���õ�����˵�������һ������

		//��Ա��������
		void set_args_string(string object_string);//��ȡͨ���Ҽ��˵��ȷ�ʽ�򿪳���ʱ�����Ŀ���ļ�·��
		void set_current_path(QString object_string);//�����ļ��򿪻򱣴洰��ʹ�õ�·��

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//�����¼���������Ӧ��ݼ�
		void keyPressEvent(QKeyEvent *event);

		//��ק�¼���������ק���ļ�
		void dragEnterEvent(QDragEnterEvent *e);
		void dropEvent(QDropEvent *e);

		//���ܺ���
		bool file_save(QString name);//ʵ�ʵı��湦�ܡ������õ��˴�����������Ҫ�޸������д
		bool save_status();//�Ƿ���Ҫ����
		void file_load(QString name);//�����ļ��������õ��˴�����������Ҫ�޸������д
		void set_file_name(QString name);//�����ļ�������ʼ���ı����޸�״̬

	signals:

		void send_file_name(QString file_name);//�����ļ���
		void send_file_size(int file_size);//����һ�δ����ļ����С
		void send_file_code(QString file_code);//�����ļ�����
		void send_file_output(QString file_output);//�����ļ���Ҫ���������
		void send_file_addspace(bool file_addspace);//�����Ƿ���ӿո�Ĳ���ֵ

	public slots:

		void timer_chara_picture_timeout();//�����ʱ�������¼�����������ʱ������
		void text_line_and_col();//�ı�������������������
		void close_dialog();//�رմ��ڰ�ť
		void set_not_save_status();//����δ������

		//�����
		void textedit_copy();//����
		void textedit_paste();//ճ��
		void textedit_cut();//����
		void textedit_undo();//����
		void textedit_redo();//����
		void textedit_font();//����
		void textedit_color();//��ɫ
		void textedit_help();//������Ϣ
		void textedit_new();//�½�
		void textedit_open();//��
		bool textedit_save();//����
		bool textedit_saveas();//���Ϊ
		void textedit_find();//����
		void textedit_replace();//�滻
		void textedit_tohex();//ʮ������ת��
		void textedit_code();//����ת��
		void textedit_setting();//��������
		void textedit_print();//��ӡ

		//�رն���
		void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���

		//File_read_text_thread������߳����ݽ���
		void get_data_t_r(QString data, bool status);//��ʾ���ݣ�status�����Ƿ�Ϊ���һ��
		void get_index_t_r(long long index, long long total_size);//��������ʾ
		void get_advance_final_t_r();//���ؽ�����ʾ����ʾ������
		void get_final_t_r();//���ؽ�����

		//File_write_text_thread������߳����ݽ���
		void get_final_t_w();//���ؽ�����ʾ

		//File_read_binary_thread������߳����ݽ���
		void get_data_b_r(QString data, bool status);//��ʾ���ݣ�status�����Ƿ�Ϊ���һ��
		void get_index_b_r(long long index, long long total_size);//��������ʾ
		void get_final_b_r();//���ؽ�����

		//File_write_text_thread������߳����ݽ���
		void get_final_b_w();//���ؽ�����ʾ
	};

	class File_read_text_thread : public QThread//��ȡ�ı��ļ����߳�
	{
		Q_OBJECT

	protected:

		QMutex mutex;//������
		QString data;//������
		QString file_name;//�ļ���
		QString file_code;//�ļ�����
		char *data_transform;//��ȡ��δת��������
		int index;//�Ѵ����С
		int file_size;//һ�δ����ļ����С

	private:

		void run();//���߳�������

	public:

		File_read_text_thread();//���캯��
		~File_read_text_thread();//��������

	signals:

		void send_data(QString data, bool status);//�������̵߳���������status�����Ƿ�Ϊ���һ��
		void send_index(long long index, long long total_size);//�������߳��Ѵ����С��ͬʱ�����ܴ�С���ڼ������
		void send_advance_final();//�ļ�Ԥ�������
		void send_final();//�ļ��������

	public slots:

		void get_file_name(QString file_name);//��ȡ�ļ���
		void get_file_size(int file_size);//��ȡһ�δ����ļ����С
		void get_file_code(QString file_code);//��ȡ�ļ�����
	};

	class File_write_text_thread : public File_read_text_thread//�����ı��ļ����̣߳�����Ҫ�ټ̳�QThread����Ϊ�����Ѿ��̳�
	{
		Q_OBJECT

	private:

		QString file_output;//��Ҫд���ļ�������
		void run();//���߳�������

	public:

		File_write_text_thread();//���캯��
		~File_write_text_thread();//��������

	signals:

		void send_final();//�ļ��������

	public slots:

		void get_file_output(QString file_output);//����ļ���Ҫ���������
	};

	class File_read_binary_thread : public File_read_text_thread//��ȡ�������ļ����߳�
	{
		Q_OBJECT

	private:

		bool file_addspace;//�����Ƿ����ո�Ĳ���ֵ
		void run();//���߳�������

	public:

		File_read_binary_thread();//���캯��
		~File_read_binary_thread();//��������

	signals:

		void send_data(QString data, bool status);//�������̵߳���������status�����Ƿ�Ϊ���һ��
		void send_index(long long index, long long total_size);//�������߳��Ѵ����С��ͬʱ�����ܴ�С���ڼ������
		void send_advance_final();//�ļ�Ԥ�������
		void send_final();//�ļ��������

	public slots:

		void get_file_addspace(bool file_addspace);//��ȡ�Ƿ���ӿո�Ĳ���ֵ
	};

	class File_write_binary_thread : public File_read_text_thread//�����ı��ļ����̣߳�����Ҫ�ټ̳�QThread����Ϊ�����Ѿ��̳�
	{
		Q_OBJECT

	private:

		QString file_output;//��Ҫд���ļ�������
		void run();//���߳�������

	public:

		File_write_binary_thread();//���캯��
		~File_write_binary_thread();//��������

	signals:

		void send_final();//�ļ��������

	public slots:

		void get_file_output(QString file_output);//����ļ���Ҫ���������
	};
}
#endif