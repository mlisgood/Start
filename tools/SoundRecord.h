#ifndef SOUND_RECORD
#define SOUND_RECORD

#include "define.h"

namespace rem
{
	class SoundRecord : public QDialog
	{
		Q_OBJECT

	private:

		Ui::SoundRecordClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QPixmap main_picture;//需要绘制以便于作为窗口的图片
		QAudioFormat audio_format;//录音格式
		QAudioInput *audio_input;//录音流
		QAudioDeviceInfo device_info_set_final;//录音设备
		QString setting_string[3];//配置文件字符串信息
		QFile output_file;//保存的文件
		bool m_bPressed;//确定窗口是否被按下
		bool is_save;//确定是否保存
		bool is_wrong;//确定是否出错
		bool on_top;//确定是否位于最顶层
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环

	protected:

		void paintEvent(QPaintEvent *);//绘制背景图像

	public:

		//构造与析构函数
		SoundRecord(QWidget *parent = Q_NULLPTR);
		~SoundRecord();

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseDoubleClickEvent(QMouseEvent *event);

		//键盘事件，用于响应快捷键
		void keyPressEvent(QKeyEvent *event);

		//槽函数
		public slots:

			void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
			void new_file();//新建
			void save_file();//保存
	};

	struct WAVHEADER//用于将原始音频数据raw改为wav的结构体。标准WAV文件头一共44字节，如果包含扩展信息则会多于此数目
	{
		//RIFF头
		char RiffName[4];//固定为“RIFF”
		unsigned long nRiffLength;//整个文件大小（头部44字节加上音频数据大小）-8（Riffname和nRIFFLength占用的字节数）
		//数据类型标识符
		char WavName[4];//波形文件标识符“WAVE”
		//格式块中的块头
		char FmtName[4];//注意这里要加一个空格以满足4个字节，即“fmt”
		unsigned long nFmtLength;//表示格式块中块数据大小，通常为16，为18时表示格式块中块数据有附加信息（即扩展域大小-nAppendMessage），一些软件制成的wav格式中含有这2个字节，当大于18时，nFmtLength-18（或者用nAppendMessage代替）即为扩展域信息数据所占的字节数
		//格式块中的块数据
		unsigned short nAudioFormat;//编码方式（值为1时，表示数据为线性PCM编码，大于1时表示有压缩的编码）
		unsigned short nChannleNumber;//音频通道数目，1–单通道（声道），2–双通道（声道）
		unsigned long nSampleRate;//采样频率（每秒样本数）
		unsigned long nBytesPerSecond;//波形数据传输速率（每秒平均字节数），由“采样频率*音频通道数*每次采样得到的样本位数/8”进行计算
		unsigned short nBytesPerSample;//数据块对齐单位（每个采样需要的字节数）
		unsigned short nBitsPerSample;//每次采样得到的样本数据位数值（Qt助手中提到一般设置为8或16，有一些系统可能支持更高的数据位数，一般可取值8、16、24）
		//扩展域
		//unsigned nAppendMessage;//扩展域大小，扩展信息（可选），根据nFmtLength的值判断是否存在
		//AppendMessageData;//扩展域信息数据，扩展信息（可选），根据nFmtLength的值判断是否存在
		//Fact块（可选）。目前认为是存在扩展域就会存在Fact块
		//FactName;//Fact块名“fact”，表面这是一个Fact块，此块目前由是否nFmtLength决定是否存在，与扩展信息一致
		//nFactLength;//Fact块数据长度，一般取值为4
		//FactData;//Fact块数据
		//数据块中的块头
		char DATANAME[4];//数据块标识符“data”
		unsigned long nDataLength;//整个文件中音频数据大小，由“采样数据总字节数/数据块中块数据总大小”进行计算
	};
}

#endif