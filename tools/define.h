#ifndef DEFINE_H
#define DEFINE_H

//ָ��ͷ�ļ�
#include <QtWidgets/QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QString>
#include <QDesktopWidget>
#include <QDialog>
#include <QPoint>
#include <QDesktopWidget>
#include <QPen>
#include <QBrush>
#include <QClipboard>
#include <QButtonGroup>
#include <QSound>
#include <QTimer>
#include <QScrollBar>
#include <QFontDatabase>
#include <QFileSystemModel>
#include <QPropertyAnimation>
#include <QAudioInput>
#include <QDateTime>
#include <QFontDatabase>
#include <QAudioEncoderSettings>
#include <string>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include "ui_Tools.h"
#include "ui_Help.h"
#include "ui_Screenshot.h"
#include "ui_CounterSet.h"
#include "ui_Counter.h"
#include "ui_Note.h"
#include "ui_ToolsSet.h"
#include "ui_File.h"
#include "ui_ToolsSetExtra.h"
#include "ui_SoundRecordSet.h"
#include "ui_SoundRecord.h"
#include "Tools.h"
#include "Help.h"
#include "Screenshot.h"
#include "CounterSet.h"
#include "Counter.h"
#include "Note.h"
#include "ToolsSet.h"
#include "File.h"
#include "ToolsSetExtra.h"
#include "SoundRecordSet.h"
#include "SoundRecord.h"

//ָ�����Ի���
#pragma execution_character_set("utf-8")

//ȫ�ֳ���
#define REG_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"//���򿪻���������Ҫ��ע�����
#define PROGRAM_SYSTEM_TRAY_ICON_PATH_STRING ".\\picture_tools\\icon\\icon_system_tray.png"//ϵͳ����ͼ��
#define PROGRAM_SYSTEM_TRAY_TIP_STRING "wusa-tools"//ϵͳ������ʾ
#define FILE_FONT_DEFAULT_SIZE 9//Ĭ�������С
#define FILE_FONT_PATH_STRING ".\\font\\font_df_girl.ttf"//�����ļ�·��
#define FILE_SETTING_MAINWINDOW_STYLE_PATH_STRING ".\\setting_tools\\mainwindow_style.ini"//�����ڷ�����������ļ�
#define FILE_SETTING_MAINWINDOW_STYLE_EXTRA_PATH_STRING ".\\setting_tools\\mainwindow_style_extra.ini"//�����ڷ�����������ļ�
#define FILE_SETTING_SOUND_RECORD_PATH_STRING ".\\setting_tools\\sound_record.ini"//¼�����������ļ�
#define FILE_SOUND_RECORD_TIME_FORMAT_STRING "yyyy-MM-dd hh-mm-ss-zzz ddd"//¼������ļ�ʱ���ʽ
#define FILE_SOUND_RECORD_BACK_PATH_STRING ".wav"//¼������ļ���׺
#define FILE_SETTING_CATALOG_2_UNDEFINE_DEFAULT_STRING "null"//�����ļ�Ŀ¼2δ����ʱ��Ĭ��ֵ
#define FILE_SETTING_CATALOG_1_INNER_PATH_STRING "/picture/mainpicture"//�����ļ�Ŀ¼1�ļ���·��
#define FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING "/function/program1"//�����ļ�Ŀ¼2-1�ļ���·��
#define FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING "/function/program2"//�����ļ�Ŀ¼2-2�ļ���·��
#define FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING "/function/program3"//�����ļ�Ŀ¼2-3�ļ���·��
#define FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING "/function/program4"//�����ļ�Ŀ¼2-4�ļ���·��
#define FILE_SETTING_CATALOG_2_5_INNER_PATH_STRING "/function/program5"//�����ļ�Ŀ¼2-5�ļ���·��
#define FILE_SETTING_CATALOG_2_6_INNER_PATH_STRING "/function/program6"//�����ļ�Ŀ¼2-6�ļ���·��
#define FILE_SETTING_CATALOG_2_7_INNER_PATH_STRING "/function/program7"//�����ļ�Ŀ¼2-7�ļ���·��
#define FILE_SETTING_CATALOG_2_8_INNER_PATH_STRING "/function/program8"//�����ļ�Ŀ¼2-8�ļ���·��
#define FILE_SETTING_CATALOG_3_INNER_PATH_STRING "/autorun/autorun"//�����ļ�Ŀ¼3�ļ���·��
#define FILE_SETTING_CATALOG_4_INNER_PATH_STRING "/font/font"//�����ļ�Ŀ¼4�ļ���·��
#define FILE_SETTING_CATALOG_5_1_INNER_PATH_STRING "/position/x"//�����ļ�Ŀ¼5-1�ļ���·��
#define FILE_SETTING_CATALOG_5_2_INNER_PATH_STRING "/position/y"//�����ļ�Ŀ¼5-2�ļ���·��
#define FILE_EXTRA_SETTING_CATALOG_1_1_INNER_PATH_STRING "/background/transparent"//���Ӹ߼����������ļ�Ŀ¼1-1�ļ���·��
#define FILE_EXTRA_SETTING_CATALOG_1_2_INNER_PATH_STRING "/background/size"//���Ӹ߼����������ļ�Ŀ¼1-2�ļ���·��
#define FILE_EXTRA_SETTING_CATALOG_2_1_INNER_PATH_STRING "/backgroundhide/isactive"//���Ӹ߼����������ļ�Ŀ¼2-1�ļ���·��
#define FILE_EXTRA_SETTING_CATALOG_2_2_INNER_PATH_STRING "/backgroundhide/waittime"//���Ӹ߼����������ļ�Ŀ¼2-2�ļ���·��
#define FILE_EXTRA_SETTING_CATALOG_2_3_INNER_PATH_STRING "/backgroundhide/background"//���Ӹ߼����������ļ�Ŀ¼2-3�ļ���·��
#define FILE_EXTRA_SETTING_CATALOG_2_4_INNER_PATH_STRING "/backgroundhide/size"//���Ӹ߼����������ļ�Ŀ¼2-4�ļ���·��
#define FILE_EXTRA_SETTING_CATALOG_2_5_INNER_PATH_STRING "/backgroundhide/x"//���Ӹ߼����������ļ�Ŀ¼2-5�ļ���·��
#define FILE_EXTRA_SETTING_CATALOG_2_6_INNER_PATH_STRING "/backgroundhide/y"//���Ӹ߼����������ļ�Ŀ¼2-6�ļ���·��
#define FILE_EXTRA_SETTING_CATALOG_2_7_INNER_PATH_STRING "/backgroundhide/transparent"//���Ӹ߼����������ļ�Ŀ¼2-7�ļ���·��
#define FILE_SOUND_RECORD_SETTING_CATALOG_1_INNER_PATH_STRING "/machine/value"//¼�����������ļ�Ŀ¼1�ļ���·��
#define FILE_SOUND_RECORD_SETTING_CATALOG_2_INNER_PATH_STRING "/trackmodel/value"//¼�����������ļ�Ŀ¼2�ļ���·��
#define FILE_SOUND_RECORD_SETTING_CATALOG_3_INNER_PATH_STRING "/path/value"//¼�����������ļ�Ŀ¼3�ļ���·��
#define FILE_SETTING_PATH_DEFAULT_SHOW_STRING "#default#"//¼�������ļ�·����Ĭ����ʾֵ
#define FILE_SETTING_PATH_DEFAULT_STRING ".\\soundrecord\\"//¼�������ļ�·����Ĭ��ֵ
#define WINDOW_ANIMATION_TIME_NUMBER 300//�����͹رն�������ʱ��
#define WINDOW_ANIMATION_TRANSPRENT_TRANSPRENT_NUMBER 0.4//����͸��ģʽ͸����
#define WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER 1//���ڳ���ģʽ͸����
#define WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER 0//������ʧ͸����
#define WINDOW_BACKGROUND_PAINT_START_X_NUMBER 0//����ͼƬ������ʼ�������
#define WINDOW_BACKGROUND_PAINT_START_Y_NUMBER 0//����ͼƬ������ʼ��������
#define WINDOW_DIALOG_TITLE_INDEX_1_PATH_STRING "ħ����Ů������ - һ�w�˥�ե�դ���`"//���ڱ���1
#define WINDOW_DIALOG_TITLE_INDEX_2_PATH_STRING "���`����`������ - һ�w�˥�ե�դ���`"//���ڱ���2
#define WINDOW_DIALOG_TITLE_INDEX_3_PATH_STRING "����ʩ`���ޥ� - һ�w�˥�ե�դ���`"//���ڱ���3
#define WINDOW_DIALOG_TITLE_INDEX_4_PATH_STRING "�Щ`���`���`���ᥰ - һ�w�˥�ե�դ���`"//���ڱ���4
#define WINDOW_PICTURE_BACKGROUND_INDEX_1_PATH_STRING ".\\picture_tools\\background\\background_1_"//����ͼƬ1�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_INDEX_2_PATH_STRING ".\\picture_tools\\background\\background_2_"//����ͼƬ2�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_INDEX_3_PATH_STRING ".\\picture_tools\\background\\background_3_"//����ͼƬ3�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_INDEX_4_PATH_STRING ".\\picture_tools\\background\\background_4_"//����ͼƬ4�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_INDEX_1_MIDDLE_PATH_STRING "1"//����ͼƬ�ߴ�1�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_INDEX_2_MIDDLE_PATH_STRING "2"//����ͼƬ�ߴ�2�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_INDEX_3_MIDDLE_PATH_STRING "3"//����ͼƬ�ߴ�3�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_INDEX_4_MIDDLE_PATH_STRING "4"//����ͼƬ�ߴ�4�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_1_PATH_STRING ".\\picture_tools\\background_extra\\background_1_"//���ⱳ��ͼƬ1�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_2_PATH_STRING ".\\picture_tools\\background_extra\\background_2_"//���ⱳ��ͼƬ2�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_3_PATH_STRING ".\\picture_tools\\background_extra\\background_3_"//���ⱳ��ͼƬ3�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_4_PATH_STRING ".\\picture_tools\\background_extra\\background_4_"//���ⱳ��ͼƬ4�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_5_PATH_STRING ".\\picture_tools\\background_extra\\background_5_"//���ⱳ��ͼƬ5�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_6_PATH_STRING ".\\picture_tools\\background_extra\\background_6_"//���ⱳ��ͼƬ6�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_7_PATH_STRING ".\\picture_tools\\background_extra\\background_7_"//���ⱳ��ͼƬ7�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_1_MIDDLE_PATH_STRING "1"//���ⱳ��ͼƬ�ߴ�1�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_2_MIDDLE_PATH_STRING "2"//���ⱳ��ͼƬ�ߴ�2�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_3_MIDDLE_PATH_STRING "3"//���ⱳ��ͼƬ�ߴ�3�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_EXTRA_INDEX_4_MIDDLE_PATH_STRING "4"//���ⱳ��ͼƬ�ߴ�4�Ǻ�׺���䲿��
#define WINDOW_PICTURE_BACKGROUND_INDEX_PATH_BACK_STRING ".png"//����ͼƬ��׺����
#define DIALOG_SIZE_WIDTH_NUMBER 600//��Ϣ����
#define DIALOG_SIZE_HEIGHT_NUMBER 200//��Ϣ��߶�
#define DIALOG_COUNTER_SIZE_WIDTH_NUMBER 290//��ʱ�����
#define DIALOG_COUNTER_SIZE_HEIGHT_NUMBER 60//��ʱ���߶�
#define DIALOG_RANDOM_MAX_NUMBER 5//������Ϣ�򱳾��õ�����������ֵ
#define DIALOG_RANDOM_MIN_NUMBER 1//������Ϣ�򱳾��õ����������Сֵ
#define DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER 8//������Ϣ�����ͼƬ�õ�����������ֵ
#define DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER 1//������Ϣ�����ͼƬ�õ����������Сֵ
#define DIALOG_NOTE_BACKGROUND_PICTURE_RANDOM_MAX_NUMBER 10//���Ʊ�ǩ����ͼƬ�õ�����������ֵ
#define DIALOG_NOTE_BACKGROUND_PICTURE_RANDOM_MIN_NUMBER 1//���Ʊ�ǩ����ͼƬ�õ����������Сֵ
#define DIALOG_COUNTER_NUMBER_PICTURE_START_X_NUMBER 50//��ʱ��ʱ��ͼƬ������ʼ�������
#define DIALOG_COUNTER_NUMBER_PICTURE_START_Y_NUMBER 27//��ʱ��ʱ��ͼƬ������ʼ��������
#define DIALOG_COUNTER_NUMBER_PICTURE_WIDTH 20//��ʱ��ʱ��ͼƬ���
#define DIALOG_COUNTER_INTERVAL_NUMBER 1000//��ʱ����ʱ���
#define DIALOG_TIME_COUNTER_END_VOICE_MAX_NUMBER 5//��ʱ�����ڲ�������������������ֵ
#define DIALOG_TIME_COUNTER_END_VOICE_MIN_NUMBER 1//��ʱ�����ڲ������������������Сֵ
#define DIALOG_INFORMATION_FILE_WIDTH_NUMBER 600//�ļ��򿪻򱣴���Ϣ�����ı���Ϣ���
#define DIALOG_INFORMATION_FILE_HEIGHT_NUMBER 30//�ļ��򿪻򱣴���Ϣ�����ı���Ϣ�߶�
#define DIALOG_INFORMATION_FILE_X_OFFSET_NUMBER 0//�ļ��򿪻򱣴���Ϣ���ı���Ϣ������ʼλ��
#define DIALOG_INFORMATION_FILE_Y_OFFSET_NUMBER 445//�ļ��򿪻򱣴���Ϣ���ı���Ϣ������ʼλ��
#define DIALOG_INFORMATION_FILE_HEAD_X_OFFSET_NUMBER 0//�ļ��򿪻򱣴���Ϣ��ͷ���ı���Ϣ������ʼλ��
#define DIALOG_INFORMATION_FILE_HEAD_Y_OFFSET_NUMBER 50//�ļ��򿪻򱣴���Ϣ��ͷ���ı���Ϣ������ʼλ��
#define DIALOG_SOUND_RECORD_NUMBER_PICTURE_WIDTH_NUMBER 140//¼������ͼƬ���
#define DIALOG_SOUND_RECORD_NUMBER_PICTURE_HEIGHT_NUMBER 200//¼������ͼƬ�߶�
#define DIALOG_SETTING_SOUND_RECORD_RATE_DEFAULT_NUMBER 48000//¼�����ô���Ĭ�ϲ���Ƶ��
#define DIALOG_SETTING_SOUND_RECORD_BIT_DEFAULT_NUMBER 16//¼�����ô���Ĭ������λ��
#define DIALOG_SCREENSHOT_EDGE_ALPHA_NUMBER 100//��ͼ������Χ�ǽ�ͼ������ɫ��͸����
#define DIALOG_SCREENSHOT_RECT_RED_NUMBER 0//��ͼ���ڽ�ͼ������α߿���ɫR����
#define DIALOG_SCREENSHOT_RECT_GREEN_NUMBER 150//��ͼ���ڽ�ͼ������α߿���ɫG����
#define DIALOG_SCREENSHOT_RECT_BLUE_NUMBER 255//��ͼ���ڽ�ͼ������α߿���ɫB����
#define DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING ".png"//��Ϣ����ʾ��������·���ĺ�׺����
#define DIALOG_MARGIN_PICTURE_PATH_STRING ".\\picture_start\\warning_margin\\margin.png"//��Ϣ��߿�ͼƬ·��
#define DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_background\\background_"//��Ϣ�򱳾�·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//��Ϣ�򱳾�·���ĺ�׺����
#define DIALOG_TOOLS_SET_BACKGROUND_PICTURE_PATH_STRING ".\\picture_tools\\tools_set_dialog\\dialog.png"//����������ÿ򱳾�·��
#define DIALOG_TOOLS_SET_EXTRA_BACKGROUND_PICTURE_PATH_STRING ".\\picture_tools\\tools_set_extra_dialog\\dialog.png"//��������������ÿ򱳾�·��
#define DIALOG_TOOLS_SOUND_RECORD_SET_BACKGROUND_PICTURE_PATH_STRING ".\\picture_tools\\sound_record_set_dialog\\dialog.png"//�������¼�����ÿ򱳾�·��
#define DIALOG_COUNTER_SET_BACKGROUND_PICTURE_PATH_STRING ".\\picture_tools\\counter_set_dialog\\dialog.png"//��ʱ�����ÿ򱳾�·��
#define DIALOG_COUNTER_BACKGROUND_PICTURE_PATH_STRING ".\\picture_tools\\counter_dialog\\dialog.png"//��ʱ������·��
#define DIALOG_COUNTER_NUMBER_PICTURE_PATH_FRONT_STRING ".\\picture_tools\\counter_number\\time_"//��ʱ������ͼƬ�Ǻ�׺���ֵĲ��䲿��
#define DIALOG_COUNTER_NUMBER_PICTURE_PATH_BACK_STRING ".png"//��ʱ������ͼƬ��׺����
#define DIALOG_COUNTER_COLON_PICTURE_PATH_STRING ".\\picture_tools\\counter_number\\time_colon.png"//��ʱ���ָ���ͼƬ·��
#define DIALOG_SOUND_RECORD_BACKGROUND_PICTURE_PATH_STRING ".\\picture_tools\\sound_record_dialog\\dialog.png"//¼�����ڱ���·��
#define DIALOG_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_chara\\chara_0"//��Ϣ�����ͼƬ·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_CHARA_PICTURE_PATH_BREAK_STRING "_0"//��Ϣ�����ͼƬ·�����»��߲���
#define DIALOG_CHARA_PICTURE_PATH_BACK_STRING ".png"//��Ϣ�����ͼƬ·���ĺ�׺����
#define DIALOG_INFORMATION_OPEN_MORE_THAN_ONE_PATH_STRING ".\\picture_tools\\open_more_than_one_information\\information_"//�࿪������ֹ��ʾ��Ϣ
#define DIALOG_INFORMATION_CANNOT_START_PROGRAM_PATH_STRING ".\\picture_tools\\cannot_start_program_information\\information_"//�޷��򿪳�����ʾ��Ϣ
#define DIALOG_INFORMATION_CANNOT_SHUTDOWN_OR_RESTART_PATH_STRING ".\\picture_tools\\cannot_shutdown_or_restart_information\\information_"//�޷��ػ�����������ʾ��Ϣ
#define DIALOG_INFORMATION_HELP_PATH_STRING ".\\picture_tools\\help_information\\information_"//������Ϣ������ʾ��Ϣ
#define DIALOG_INFORMATION_WRONG_DEVICE_PATH_STRING ".\\picture_tools\\wrong_device_information\\information_"//����¼���豸ʧ�ܴ�����ʾ��Ϣ
#define DIALOG_INFORMATION_WRONG_SOUND_FILE_SAVE_PATH_STRING ".\\picture_tools\\wrong_sound_save_path_information\\information_"//¼�������ļ�·����������ʾ��Ϣ
#define DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING ".\\picture_tools\\wrong_file_or_path_information\\information_"//���ô��ڲ����ڵ��ļ���·��������ʾ��Ϣ
#define DIALOG_NOTE_BACKGROUND_PICTURE_FRONT_STRING ".\\picture_tools\\note_background\\background_"//��ǩ�������ڵķǺ�׺���ֵĲ��䲿��
#define DIALOG_NOTE_BACKGROUND_PICTURE_BACK_STRING ".png"//��ǩ�������ڵĺ�׺����
#define DIALOG_INFORMATION_FILE_PICTURE_PATH_STRING ".\\picture_tools\\filedialog_information\\information_"//�ļ��򿪻򱣴�ѡ����ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_FILE_HEAD_PICTURE_PATH_STRING ".\\picture_tools\\filedialog_information\\informationhead_"//�ļ��򿪻򱣴�ѡ����ʾ��ͷ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_tools\\filedialog_background\\background_"//�򿪻򱣴��ļ���Ϣ�򱳾�·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//�򿪻򱣴��ļ���Ϣ�򱳾�·���ĺ�׺����
#define DIALOG_FILE_MARGIN_PICTURE_PATH_STRING ".\\picture_tools\\filedialog_margin\\margin.png"//�ļ����뱣����Ϣ��߿�ͼƬ·��
#define DIALOG_TIME_COUNTER_END_VOICE_FRONT_STRING ".\\sound\\time_counter_end_voice\\voice_"//��ʱ�����ڲ�������·���ķǺ�׺����
#define DIALOG_TIME_COUNTER_END_VOICE_BREAK_STRING "_"//��ʱ�����ڲ�������·�����»��߲���
#define DIALOG_TIME_COUNTER_END_VOICE_BACK_STRING ".wav"//��ʱ�����ڲ�������·���ĺ�׺����

#endif