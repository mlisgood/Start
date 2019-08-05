#ifndef DEFINE_H
#define DEFINE_H

//ָ��ͷ�ļ�
#include <QtWidgets/QMainWindow>
#include <QtCore>
#include <QSplashScreen>
#include <QMouseEvent>
#include <QMainWindow>
#include <QPoint>
#include <QWidget>
#include <QString>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QFontDatabase>
#include <QScreen>
#include <QFileSystemModel>
#include <QScrollBar>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QUrl>
#include <QDrag>
#include <QPrinter>
#include <QPrinterInfo>
#include <QMutex>
#include <QThread>
#include <QTextCursor>
#include <qmovie.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include "ui_Notepad.h"
#include "ui_Help.h"
#include "ui_Save.h"
#include "ui_Find.h"
#include "ui_Replace.h"
#include "ui_Font.h"
#include "ui_Color.h"
#include "ui_File.h"
#include "ui_Code.h"
#include "ui_Print.h"
#include "ui_Setting.h"
#include "Notepad.h"
#include "Help.h"
#include "Save.h"
#include "Find.h"
#include "Replace.h"
#include "Font.h"
#include "Color.h"
#include "File.h"
#include "Code.h"
#include "Print.h"
#include "Setting.h"
#include "main.h"

//ָ�����Ի���
#pragma execution_character_set("utf-8")

//ȫ�ֳ���
#define FILE_FONT_DEFAULT_SIZE 9//Ĭ�������С
#define FILE_FONT_PATH_STRING ".\\font\\font_df_girl.ttf"//�����ļ�·��
#define REG_MENU_1 "HKEY_CLASSES_ROOT\\*\\shell\\Cup Of Notepad\\command"//�����Ҽ��˵�ע�����·��1
#define REG_MENU_2 "HKEY_CLASSES_ROOT\\*\\shell\\Cup Of Notepad"//�����Ҽ��˵�ע�����·��2
#define REG_MENU_NAME_PATH_STRING "Cup Of Notepad"//��ע���ʹ�õ��Ҽ��˵��������
#define REG_MENU_ICON_PATH_STRING "\\picture_notepad\\icon\\icon_menu.ico"//��ע���ʹ�õ��Ҽ��˵����ͼ���ļ�λ��
#define FILE_BIT_TO_KBIT 1024//Bת��ΪKB�ı���
#define FILE_DLL_FILE_READ_PATH_STRING L"FileReadAndWrite.dll"//�ļ���ȡdll�ļ�λ��
#define FILE_SETTING_TEXT_AND_BINARY_END_WRITE_STRING "#end#"//�������ô���д���ļ���׺ʱ������ʹ�õ��ַ�����ʶ
#define FILE_FONT_OUTPUT_FILE_PATH_FRONT_STRING ".\\setting_notepad\\font_setting_"//������������ļ��Ǻ�׺���䲿��
#define FILE_FONT_OUTPUT_FILE_PATH_BINARY_EXTRA_STRING "_b"//������������ļ�������ģʽ�Ǻ�׺���Ӳ���
#define FILE_FONT_OUTPUT_FILE_PATH_BACK_STRING ".txt"//������������ļ���׺
#define FILE_COLOR_OUTPUT_FILE_PATH_FRONT_STRING ".\\setting_notepad\\color_save_"//��ɫ��������ļ�ǰ׺���䲿��
#define FILE_COLOR_OUTPUT_FILE_PATH_BACK_STRING ".txt"//��ɫ��������ļ���׺
#define FILE_CODE_OUTPUT_FILE_PATH_STRING ".\\setting_notepad\\text_code.txt"//������������ļ�·��
#define FILE_SETTING_TEXT_OUTPUT_FILE_PATH_STRING ".\\setting_notepad\\setting_text.txt"//����������������ļ�1·��
#define FILE_SETTING_BINARY_OUTPUT_FILE_PATH_STRING ".\\setting_notepad\\setting_binary.txt"//����������������ļ�2·��
#define FILE_SETTING_OTHER_PATH_STRING ".\\setting_notepad\\setting_other.ini"//�������������ļ�
#define FILE_SETTING_CATALOG_1_INNER_PATH_STRING "/defaultopenmethod/type"//�������������ļ�Ŀ¼1�ļ���·��
#define FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING "/size/text"//�������������ļ�Ŀ¼2-1�ļ���·��
#define FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING "/size/binary"//�������������ļ�Ŀ¼2-2�ļ���·��
#define FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING "/boolvalue/changeline"//�������������ļ�Ŀ¼3_1�ļ���·��
#define FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING "/boolvalue/menu"//�������������ļ�Ŀ¼3_2�ļ���·��
#define FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING "/boolvalue/addblank"//�������������ļ�Ŀ¼3_3�ļ���·��
#define WINDOW_THREAD_WAIT_TIME_NUMBER 1//���߳�ÿ����һ�κ����ߵ�ʱ��
#define WINDOW_SIZE_WIDTH_NUMBER 1000//���ڿ��
#define WINDOW_SIZE_HEIGHT_NUMBER 600//���ڸ߶�
#define WINDOW_ANIMATION_TIME_NUMBER 300//�����͹رն�������ʱ��
#define WINDOW_ANIMATION_TRANSPRENT_TRANSPRENT_NUMBER 0.4//����͸��ģʽ͸����
#define WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER 1//���ڳ���ģʽ͸����
#define WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER 0//������ʧ͸����
#define WINDOW_SIZE_PICTURE_CHARA_WIDTH_NUMBER 421//����������
#define WINDOW_SIZE_PICTURE_CHARA_HEIGHT_NUMBER 600//��������߶�
#define WINDOW_TEXTEDIT_X_OFFSET_NUMBER 470//�ı������ƫ�ơ������ı�������ñ��ı���ʵ�ʵĴ�СҪ������Ϊ�˱�֤����ͼƬ����ʾЧ����
#define WINDOW_TEXTEDIT_Y_OFFSET_NUMBER 90//�ı�������ƫ��
#define WINDOW_TEXTEDIT_SIZE_WIDTH_NUMBER 480//�ı�����
#define WINDOW_TEXTEDIT_SIZE_HEIGHT_NUMBER 450//�ı���߶�
#define WINDOW_RANDOM_MAX_NUMBER 25//���ƴ��ڱ����õ�����������ֵ������ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define WINDOW_RANDOM_MIN_NUMBER 1//���ƴ��ڱ����õ����������Сֵ������ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define WINDOW_RANDOM_TIMER_CHARA_NORMAL_MAX_NUMBER 9000//�������ﳣ��״̬�¼�ʱ�����
#define WINDOW_RANDOM_TIMER_CHARA_NORMAL_MIN_NUMBER 5000//�������ﳣ��״̬�¼�ʱ�����
#define WINDOW_RANDOM_TIMER_CHARA_SPECIAL_NUMBER 60//������������״̬�¼�ʱ�����
#define WINDOW_SIZE_MARGIN_PICTURE_LEFT_WIDTH_NUMBER 425//���ڱ߽���߲��ֿ��
#define WINDOW_SIZE_MARGIN_PICTURE_LEFT_HEIGHT_NUMBER 600//���ڱ߽���߲��ָ߶�
#define WINDOW_SIZE_MARGIN_PICTURE_RIGHT_WIDTH_NUMBER 575//���ڱ߽��ұ߲��ֿ��
#define WINDOW_SIZE_MARGIN_PICTURE_RIGHT_HEIGHT_NUMBER 600//���ڱ߽��ұ߲��ָ߶�
#define WINDOW_BUTTON_CLOSE_WINDOW_WIDTH_NUMBER 25//���ڹرհ�ť���
#define WINDOW_BUTTON_CLOSE_WINDOW_HEIGHT_NUMBER 25//���ڹرհ�ť�߶�
#define WINDOW_PROGRESSBAR_MAX_VALUE_NUMBER 100//�����ڽ��������ֵ
#define WINDOW_DIALOG_TITLE_PATH_STRING " - һ�w�˥�ե�դ���`"//���ڱ����׺
#define WINDOW_SPLASH_PICTURE_PATH_FRONT_STRING ".\\picture_notepad\\splash\\splash.png"//��������ͼƬ·��
#define WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_start\\background\\background_"//����ͼƬ·���ķǺ�׺���ֵĲ��䲿��
#define WINDOW_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//����ͼƬ·���ĺ�׺����
#define WINDOW_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_start\\background_chara\\chara_"//����ͼƬ�ķǺ�׺���ֵĲ��䲿�֡�����ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define WINDOW_CHARA_PICTURE_PATH_BACK_STRING ".png"//����ͼƬ·���ĺ�׺���֣�����ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define WINDOW_CHARA_PICTURE_PATH_BREAK_STRING "_"//����ͼƬ·�����»��߲��֡�����ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define WINDOW_MARGIN_PICTURE_LEFT_PATH_STRING ".\\picture_start\\background_margin\\margin_left.png"//�߿�ͼƬ��߲���·��
#define WINDOW_MARGIN_PICTURE_RIGHT_PATH_STRING ".\\picture_notepad\\background_margin\\margin_right.png"//�߿�ͼƬ�ұ߲���·��
#define WINDOW_BUTTON_CLOSE_WINDOW_PATH_STRING ".\\picture_start\\icon\\window_close.png"//���ڹرհ�ť·��
#define WINDOW_BUTTON_HIDE_WINDOW_PATH_STRING ".\\picture_start\\icon\\window_hide.png"//������С����ť·��
#define WINDOW_TEXTEDIT_BACKGROUND_PICTURE_PATH_STRING ".\\picture_notepad\\background_text\\background_text_0"//�ı��򱳾�����·���ķǺ�׺���ֵĲ��䲿��
#define WINDOW_TEXTEDIT_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//�ı��򱳾�·���ĺ�׺����
#define WINDOW_CHARA_NORMAL_FLAG 1//�������ﳣ��״̬�±�־������ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define WINDOW_CHARA_SPECIAL_FLAG 0//������������״̬�±�־������ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define WINDOW_TOOL_TOHEX_STATUS_YES_FLAG 0//��ʾ��ǰ������ʮ������
#define WINDOW_TOOL_TOHEX_STATUS_NO_FLAG 1//��ʾ��ǰ�������ı��ַ�
#define DIALOG_SIZE_WIDTH_NUMBER 600//��Ϣ����
#define DIALOG_SIZE_HEIGHT_NUMBER 200//��Ϣ��߶�
#define DIALOG_FONT_SIZE_WIDTH_NUMBER 600//������Ϣ����
#define DIALOG_FONT_SIZE_HEIGHT_NUMBER 400//������Ϣ��߶�
#define DIALOG_COLOR_SIZE_WIDTH_NUMBER 600//ɫ����Ϣ����
#define DIALOG_COLOR_SIZE_HEIGHT_NUMBER 400//ɫ����Ϣ��߶�
#define DIALOG_SETTING_MAX_TEXT_SIZE_NUMBER 1024//�������ô����������һ�����ı���ʽ�����ļ������ݿ��С
#define DIALOG_SETTING_MIN_TEXT_SIZE_NUMBER 64//�������ô�����С����һ�����ı���ʽ�����ļ������ݿ��С
#define DIALOG_SETTING_MAX_BINARY_SIZE_NUMBER 32//�������ô����������һ���Զ����Ʒ�ʽ�����ļ������ݿ��С
#define DIALOG_SETTING_MIN_BINARY_SIZE_NUMBER 4//�������ô�����С����һ���Զ����Ʒ�ʽ�����ļ������ݿ��С
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_MARGIN_1_NUMBER 540//ɫ����Ϣ���Ҳཥ��ָ��ֱ�߲���1
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_MARGIN_2_NUMBER 81//ɫ����Ϣ���Ҳཥ��ָ��ֱ�߲���2
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_MARGIN_3_NUMBER 540//ɫ����Ϣ���Ҳཥ��ָ��ֱ�߲���3
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_MARGIN_4_NUMBER 229//ɫ����Ϣ���Ҳཥ��ָ��ֱ�߲���4
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_RECT_1_NUMBER 521//ɫ����Ϣ���Ҳཥ��ָ����״����1
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_RECT_2_NUMBER 81//ɫ����Ϣ���Ҳཥ��ָ����״����2
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_RECT_3_NUMBER 38//ɫ����Ϣ���Ҳཥ��ָ����״����3
#define DIALOG_COLOR_SIZE_RIGHT_PAINT_RECT_4_NUMBER 148//ɫ����Ϣ���Ҳཥ��ָ����״����4
#define DIALOG_COLOR_SLIDER_X_BEGIN_NUMBER 540//ɫ����Ϣ���Ҳཥ����ȡɫ����λ��
#define DIALOG_COLOR_SLIDER_Y_BEGIN_NUMBER 82//ɫ����Ϣ���Ҳཥ����ȡɫ������ʼλ��
#define DIALOG_RANDOM_MAX_NUMBER 5//������Ϣ�򱳾��õ�����������ֵ������ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define DIALOG_RANDOM_MIN_NUMBER 1//������Ϣ�򱳾��õ����������Сֵ������ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER 8//������Ϣ�����ͼƬ�õ�����������ֵ������ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER 1//������Ϣ�����ͼƬ�õ����������Сֵ������ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define DIALOG_INFORMATION_CANNOT_SAVE_NORMAL_RETURN_NUMBER 0//�޷��洢��ʾ��Ĭ��ֵ
#define DIALOG_INFORMATION_CANNOT_SAVE_SAVE_RETURN_NUMBER 1//�޷��洢��ʾ��Saveѡ���ֵ
#define DIALOG_INFORMATION_CANNOT_SAVE_DISCARD_RETURN_NUMBER 2//�޷��洢��ʾ��Discardѡ���ֵ
#define DIALOG_INFORMATION_FIND_WIDTH_NUMBER 400//���ҿ��ı���Ϣ���
#define DIALOG_INFORMATION_FIND_HEIGHT_NUMBER 100//���ҿ��ı���Ϣ�߶�
#define DIALOG_INFORMATION_FIND_X_OFFSET_NUMBER 200//���ҿ��ı���Ϣ������ʼλ��
#define DIALOG_INFORMATION_FIND_Y_OFFSET_NUMBER 50//���ҿ��ı���Ϣ������ʼλ��
#define DIALOG_INFORMATION_FILE_WIDTH_NUMBER 600//�ļ��򿪻򱣴���Ϣ�����ı���Ϣ���
#define DIALOG_INFORMATION_FILE_HEIGHT_NUMBER 30//�ļ��򿪻򱣴���Ϣ�����ı���Ϣ�߶�
#define DIALOG_INFORMATION_FILE_X_OFFSET_NUMBER 0//�ļ��򿪻򱣴���Ϣ���ı���Ϣ������ʼλ��
#define DIALOG_INFORMATION_FILE_Y_OFFSET_NUMBER 445//�ļ��򿪻򱣴���Ϣ���ı���Ϣ������ʼλ��
#define DIALOG_INFORMATION_FILE_HEAD_X_OFFSET_NUMBER 0//�ļ��򿪻򱣴���Ϣ��ͷ���ı���Ϣ������ʼλ��
#define DIALOG_INFORMATION_FILE_HEAD_Y_OFFSET_NUMBER 50//�ļ��򿪻򱣴���Ϣ��ͷ���ı���Ϣ������ʼλ��
#define DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_background\\background_"//��Ϣ�򱳾�·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//��Ϣ�򱳾�·���ĺ�׺����
#define DIALOG_FONT_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_notepad\\font_background\\background_"//������Ϣ�򱳾�·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_FONT_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//������Ϣ�򱳾�·���ĺ�׺����
#define DIALOG_COLOR_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_notepad\\font_background\\background_"//ɫ����Ϣ�򱳾�·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_COLOR_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//ɫ����Ϣ�򱳾�·���ĺ�׺����
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_notepad\\filedialog_background\\background_"//�򿪻򱣴��ļ���Ϣ�򱳾�·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//�򿪻򱣴��ļ���Ϣ�򱳾�·���ĺ�׺����
#define DIALOG_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_chara\\chara_0"//��Ϣ�����ͼƬ·���ķǺ�׺���ֵĲ��䲿�֡�����ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define DIALOG_CHARA_PICTURE_PATH_BREAK_STRING "_0"//��Ϣ�����ͼƬ·�����»��߲��֡�����ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define DIALOG_CHARA_PICTURE_PATH_BACK_STRING ".png"//��Ϣ�����ͼƬ·���ĺ�׺���֣�����ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define DIALOG_MARGIN_PICTURE_PATH_STRING ".\\picture_start\\warning_margin\\margin.png"//��Ϣ��߿�ͼƬ·��
#define DIALOG_FONT_MARGIN_PICTURE_PATH_STRING ".\\picture_notepad\\font_margin\\margin.png"//������Ϣ��߿�ͼƬ·��
#define DIALOG_COLOR_MARGIN_PICTURE_PATH_STRING ".\\picture_notepad\\font_margin\\margin.png"//ɫ����Ϣ��߿�ͼƬ·��
#define DIALOG_FILE_MARGIN_PICTURE_PATH_STRING ".\\picture_notepad\\filedialog_margin\\margin.png"//�ļ����뱣����Ϣ��߿�ͼƬ·��
#define DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_STRING ".\\style\\font_dialog\\font_"//������ʽ�ļ��ķǺ�׺���ֵĲ��䲿��
#define DIALOG_FILE_DIALOG_FONT_STYLESHEET_FILE_PATH_BACK_STRING ".qss"//������ʽ�ļ��ĺ�׺����
#define DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING ".png"//��Ϣ����ʾ��������·���ĺ�׺����
#define DIALOG_INFORMATION_HELP_PICTURE_PATH_STRING ".\\picture_notepad\\help_information\\information_"//����������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_CANNOT_READ_PICTURE_PATH_STRING ".\\picture_notepad\\cannot_read_information\\information_"//�޷���ȡ��ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_CANNOT_WRITE_PICTURE_PATH_STRING ".\\picture_notepad\\cannot_write_information\\information_"//�޷�д����ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_CANNOT_SAVE_PICTURE_PATH_STRING ".\\picture_notepad\\cannot_save_information\\information_"//�޷��洢��ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_CANNOT_FIND_PICTURE_PATH_STRING ".\\picture_notepad\\cannot_find_information\\information_"//����ʧ����ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_FIND_PICTURE_PATH_STRING ".\\picture_notepad\\find_information\\information_"//���ҿ�����·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_REPLACE_PICTURE_PATH_STRING ".\\picture_notepad\\replace_information\\information_"//�滻������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_REPLACE_ALL_PICTURE_PATH_STRING ".\\picture_notepad\\replace_all_information\\information_"//�滻��ȫ���滻����·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_TEXT_FILE_TOO_LARGE_SAVE_PICTURE_PATH_STRING ".\\picture_notepad\\file_too_large_save_information\\information_"//�ı��ļ������ܱ�����ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_TEXT_FILE_TOO_LARGE_LOAD_PICTURE_PATH_STRING ".\\picture_notepad\\file_too_large_load_information\\information_"//�ı��ļ������ܶ�ȡ��ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_BINARY_FILE_TOO_LARGE_LOAD_PICTURE_PATH_STRING ".\\picture_notepad\\file_binary_too_large_load_information\\information_"//�������ļ������ܶ�ȡ��ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_BINARY_FILE_TOO_LARGE_SAVE_PICTURE_PATH_STRING ".\\picture_notepad\\file_binary_too_large_save_information\\information_"//�������ļ������ܱ�����ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_FONT_PICTURE_PATH_STRING ".\\picture_notepad\\font_information\\information_"//����ѡ����ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_COLOR_PICTURE_PATH_STRING ".\\picture_notepad\\color_information\\information_"//ɫ��ѡ����ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_COLOR_CANNOT_ADD_PICTURE_PATH_STRING ".\\picture_notepad\\color_add_fail_information\\information_"//�޷�����Զ�����ɫ��ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_FILE_PICTURE_PATH_STRING ".\\picture_notepad\\filedialog_information\\information_"//�ļ��򿪻򱣴�ѡ����ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_FILE_HEAD_PICTURE_PATH_STRING ".\\picture_notepad\\filedialog_information\\informationhead_"//�ļ��򿪻򱣴�ѡ����ʾ��ͷ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_CODE_PICTURE_PATH_STRING ".\\picture_notepad\\code_information\\information_"//�����޸Ŀ�����·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_PRINT_PICTURE_PATH_STRING ".\\picture_notepad\\print_information\\information_"//��ӡ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_SETTING_PICTURE_PATH_STRING ".\\picture_notepad\\setting_information\\information_"//�������ÿ�����·���ķǺ�׺���ֵĲ��䲿��

#endif
