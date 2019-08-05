#ifndef SOUND_RECORD
#define SOUND_RECORD

#include "define.h"

namespace rem
{
	class SoundRecord : public QDialog
	{
		Q_OBJECT

	private:

		Ui::SoundRecordClass ui;//����
		QPoint m_point;//��¼���������ƶ�����
		QPixmap main_picture;//��Ҫ�����Ա�����Ϊ���ڵ�ͼƬ
		QAudioFormat audio_format;//¼����ʽ
		QAudioInput *audio_input;//¼����
		QAudioDeviceInfo device_info_set_final;//¼���豸
		QString setting_string[3];//�����ļ��ַ�����Ϣ
		QFile output_file;//������ļ�
		bool m_bPressed;//ȷ�������Ƿ񱻰���
		bool is_save;//ȷ���Ƿ񱣴�
		bool is_wrong;//ȷ���Ƿ����
		bool on_top;//ȷ���Ƿ�λ�����
		bool is_escape_pressed;//�������ΰ���һ���˳�����������¸ü���ɹرն���ѭ��

	protected:

		void paintEvent(QPaintEvent *);//���Ʊ���ͼ��

	public:

		//��������������
		SoundRecord(QWidget *parent = Q_NULLPTR);
		~SoundRecord();

		//����¼������ڴ����ƶ�
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseDoubleClickEvent(QMouseEvent *event);

		//�����¼���������Ӧ��ݼ�
		void keyPressEvent(QKeyEvent *event);

		//�ۺ���
		public slots:

			void close_window_include_animation();//�����رմ��ڶ����Ĺرմ��ڷ���
			void new_file();//�½�
			void save_file();//����
	};

	struct WAVHEADER//���ڽ�ԭʼ��Ƶ����raw��Ϊwav�Ľṹ�塣��׼WAV�ļ�ͷһ��44�ֽڣ����������չ��Ϣ�����ڴ���Ŀ
	{
		//RIFFͷ
		char RiffName[4];//�̶�Ϊ��RIFF��
		unsigned long nRiffLength;//�����ļ���С��ͷ��44�ֽڼ�����Ƶ���ݴ�С��-8��Riffname��nRIFFLengthռ�õ��ֽ�����
		//�������ͱ�ʶ��
		char WavName[4];//�����ļ���ʶ����WAVE��
		//��ʽ���еĿ�ͷ
		char FmtName[4];//ע������Ҫ��һ���ո�������4���ֽڣ�����fmt��
		unsigned long nFmtLength;//��ʾ��ʽ���п����ݴ�С��ͨ��Ϊ16��Ϊ18ʱ��ʾ��ʽ���п������и�����Ϣ������չ���С-nAppendMessage����һЩ����Ƴɵ�wav��ʽ�к�����2���ֽڣ�������18ʱ��nFmtLength-18��������nAppendMessage���棩��Ϊ��չ����Ϣ������ռ���ֽ���
		//��ʽ���еĿ�����
		unsigned short nAudioFormat;//���뷽ʽ��ֵΪ1ʱ����ʾ����Ϊ����PCM���룬����1ʱ��ʾ��ѹ���ı��룩
		unsigned short nChannleNumber;//��Ƶͨ����Ŀ��1�C��ͨ������������2�C˫ͨ����������
		unsigned long nSampleRate;//����Ƶ�ʣ�ÿ����������
		unsigned long nBytesPerSecond;//�������ݴ������ʣ�ÿ��ƽ���ֽ��������ɡ�����Ƶ��*��Ƶͨ����*ÿ�β����õ�������λ��/8�����м���
		unsigned short nBytesPerSample;//���ݿ���뵥λ��ÿ��������Ҫ���ֽ�����
		unsigned short nBitsPerSample;//ÿ�β����õ�����������λ��ֵ��Qt�������ᵽһ������Ϊ8��16����һЩϵͳ����֧�ָ��ߵ�����λ����һ���ȡֵ8��16��24��
		//��չ��
		//unsigned nAppendMessage;//��չ���С����չ��Ϣ����ѡ��������nFmtLength��ֵ�ж��Ƿ����
		//AppendMessageData;//��չ����Ϣ���ݣ���չ��Ϣ����ѡ��������nFmtLength��ֵ�ж��Ƿ����
		//Fact�飨��ѡ����Ŀǰ��Ϊ�Ǵ�����չ��ͻ����Fact��
		//FactName;//Fact������fact������������һ��Fact�飬�˿�Ŀǰ���Ƿ�nFmtLength�����Ƿ���ڣ�����չ��Ϣһ��
		//nFactLength;//Fact�����ݳ��ȣ�һ��ȡֵΪ4
		//FactData;//Fact������
		//���ݿ��еĿ�ͷ
		char DATANAME[4];//���ݿ��ʶ����data��
		unsigned long nDataLength;//�����ļ�����Ƶ���ݴ�С���ɡ������������ֽ���/���ݿ��п������ܴ�С�����м���
	};
}

#endif