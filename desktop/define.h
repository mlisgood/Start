#ifndef DEFINE_H
#define DEFINE_H

//ͷ�ļ�
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
#include <QTimer>
#include <QScrollBar>
#include <QFontDatabase>
#include <QFileSystemModel>
#include <QPropertyAnimation>
#include <QDateTime>
#include <QFontDatabase>
#include <QScreen>
#include <QDrag>
#include <QUrl>
#include <QMimeData>
#include <string>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include <math.h>
#include "ui_Desktop.h"
#include "ui_Help.h"
#include "ui_File.h"
#include "ui_Widget.h"
#include "ui_Setting.h"
#include "ui_SettingDynamic.h"
#include "ui_SettingOther.h"
#include "Desktop.h"
#include "Help.h"
#include "File.h"
#include "Widget.h"
#include "Setting.h"
#include "SettingDynamic.h"
#include "SettingOther.h"

//���Ի���
#pragma execution_character_set("utf-8")

//ȫ�ֳ���
#define REG_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"//���򿪻���������Ҫ��ע�����
#define PROGRAM_SYSTEM_TRAY_ICON_PATH_STRING ".\\picture_desktop\\icon\\icon_system_tray.png"//ϵͳ����ͼ��
#define PROGRAM_SYSTEM_TRAY_TIP_STRING "wusa-desktop"//ϵͳ������ʾ
#define FILE_FONT_DEFAULT_SIZE 9//Ĭ�������С
#define FILE_FONT_PATH_STRING ".\\font\\font_df_girl.ttf"//�����ļ�·��
#define FILE_SETTING_STATIC_PATH_STRING ".\\setting_desktop\\setting_static.ini"//��̬��Ϣ�����ļ�
#define FILE_SETTING_DYNAMIC_PATH_STRING ".\\setting_desktop\\setting_dynamic.ini"//��̬��Ϣ�����ļ�
#define FILE_SETTING_OPEN_PATH_UNDEFINE_DEFAULT_STRING L"null"//�����ļ��򿪳���Ϊ��ʱĬ���ַ���
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_1_STRING "/mainwindow"//��̬��Ϣ�����ļ�Ŀ¼ͷ��1�ļ���·��
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_HEAD_2_STRING "/subwindow"//��̬��Ϣ�����ļ�Ŀ¼ͷ��2ǰ�벿���ļ���·��
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_1_STRING "/is_hide"//��̬��Ϣ�����ļ�Ŀ¼β��1�ļ���·��
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_2_STRING "/time_interval"//��̬��Ϣ�����ļ�Ŀ¼β��2�ļ���·��
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_3_STRING "/is_on_top"//��̬��Ϣ�����ļ�Ŀ¼β��3�ļ���·��
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_4_STRING "/transparent"//��̬��Ϣ�����ļ�Ŀ¼β��4�ļ���·��
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_5_STRING "/auto_run"//��̬��Ϣ�����ļ�Ŀ¼β��5�ļ���·��
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_6_STRING "/is_enable"//��̬��Ϣ�����ļ�Ŀ¼β��6�ļ���·��
#define FILE_SETTING_STATIC_CATALOG_INNER_PATH_TAIL_7_STRING "/path"//��̬��Ϣ�����ļ�Ŀ¼β��7�ļ���·��
#define FILE_SETTING_DYNAMIC_CATALOG_1_1_INNER_PATH_STRING "/mainposition/main_x"//��̬��Ϣ�����ļ�Ŀ¼1_1�ļ���·��
#define FILE_SETTING_DYNAMIC_CATALOG_1_2_INNER_PATH_STRING "/mainposition/main_y"//��̬��Ϣ�����ļ�Ŀ¼1_2�ļ���·��
#define FILE_SETTING_DYNAMIC_CATALOG_2_FRONT_INNER_PATH_STRING "/subposition/sub_"//��̬��Ϣ�����ļ�Ŀ¼2ǰ�벿���ļ���·��
#define FILE_SETTING_DYNAMIC_CATALOG_2_1_BACK_INNER_PATH_STRING "_x"//��̬��Ϣ�����ļ�Ŀ¼2_1��벿���ļ���·��
#define FILE_SETTING_DYNAMIC_CATALOG_2_2_BACK_INNER_PATH_STRING "_y"//��̬��Ϣ�����ļ�Ŀ¼2_2��벿���ļ���·��
#define WINDOW_ANIMATION_TIME_NUMBER 300//�����͹رն�������ʱ��
#define WINDOW_ANIMATION_HIDE_NUMBER 1//��������ʱ��͸����
#define WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER 0//������ʧ͸����
#define WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER 1//���ڳ���͸����
#define WINDOW_SIZE_WIDTH_NUMBER 160//���ڿ��
#define WINDOW_SIZE_HEIGHT_NUMBER 160//���ڸ߶�
#define WINDOW_SIZE_SIDE_LENGTH_NUMBER 100//���ش��ڱ߳�
#define WINDOW_RANDOM_MAX_NUMBER 7//���ƴ��ڱ����õ�����������ֵ
#define WINDOW_RANDOM_MIN_NUMBER 1//���ƴ��ڱ����õ����������Сֵ
#define WINDOW_RANDOM_WIDGET_AMOUNT_MAX_NUMBER 7//���ؼ���Ŀ������Ҫ�޸ĸ����ԣ�����Ӧ�ļ�Ҳ��Ҫ���޸�
#define WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\mainwindow_background\\bg_"//����ͼƬ·���ķǺ�׺���ֵĲ��䲿��
#define WINDOW_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//����ͼƬ·���ĺ�׺����
#define WINDOW_BACKGROUND_UP_HIDE_PICTURE_PATH_STRING ".\\picture_desktop\\mainwindow_background\\bg_hide_up.png"//����״̬��Ļ�Ϸ�����ͼƬ·��
#define WINDOW_BACKGROUND_DOWN_HIDE_PICTURE_PATH_STRING ".\\picture_desktop\\mainwindow_background\\bg_hide_down.png"//����״̬��Ļ�·�����ͼƬ·��
#define WINDOW_BACKGROUND_LEFT_HIDE_PICTURE_PATH_STRING ".\\picture_desktop\\mainwindow_background\\bg_hide_left.png"//����״̬��Ļ��߱���ͼƬ·��
#define WINDOW_BACKGROUND_RIGHT_HIDE_PICTURE_PATH_STRING ".\\picture_desktop\\mainwindow_background\\bg_hide_right.png"//����״̬��Ļ�ұ߱���ͼƬ·��
#define DIALOG_WEDGIT_SIZE_WIDTH_NUMBER 72//���������
#define DIALOG_WEDGIT_SIZE_HEIGHT_NUMBER 80//���������
#define DIALOG_SIZE_WIDTH_NUMBER 600//��Ϣ����
#define DIALOG_SIZE_HEIGHT_NUMBER 200//��Ϣ��߶�
#define DIALOG_RANDOM_MAX_NUMBER 5//������Ϣ�򱳾��õ�����������ֵ
#define DIALOG_RANDOM_MIN_NUMBER 1//������Ϣ�򱳾��õ����������Сֵ
#define DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER 8//������Ϣ�����ͼƬ�õ�����������ֵ
#define DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER 1//������Ϣ�����ͼƬ�õ����������Сֵ
#define DIALOG_INFORMATION_FILE_WIDTH_NUMBER 600//�ļ��򿪻򱣴���Ϣ�����ı���Ϣ���
#define DIALOG_INFORMATION_FILE_HEIGHT_NUMBER 30//�ļ��򿪻򱣴���Ϣ�����ı���Ϣ�߶�
#define DIALOG_INFORMATION_FILE_X_OFFSET_NUMBER 0//�ļ��򿪻򱣴���Ϣ���ı���Ϣ������ʼλ��
#define DIALOG_INFORMATION_FILE_Y_OFFSET_NUMBER 445//�ļ��򿪻򱣴���Ϣ���ı���Ϣ������ʼλ��
#define DIALOG_INFORMATION_FILE_HEAD_X_OFFSET_NUMBER 0//�ļ��򿪻򱣴���Ϣ��ͷ���ı���Ϣ������ʼλ��
#define DIALOG_INFORMATION_FILE_HEAD_Y_OFFSET_NUMBER 50//�ļ��򿪻򱣴���Ϣ��ͷ���ı���Ϣ������ʼλ��
#define DIALOG_SETTING_TRANSPARENT_CHANGE_MIN_NUMBER 0//���ý�����С͸����
#define DIALOG_SETTING_TRANSPARENT_CHANGE_MAX_NUMBER 10//���ý������͸����
#define DIALOG_SETTING_TRANSPARENT_CHANGE_UNIT_NUMBER 1//���ý���ÿ��͸���ȸı���
#define DIALOG_SETTING_PATH_DEFAULT_STRING "null"//���ý���·��Ĭ���ַ���
#define DIALOG_WIDGET_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\desktop_widget_background\\bg_"//�ؼ�����ͼƬ·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_WIDGET_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//�ؼ�����ͼƬ·���ĺ�׺����
#define DIALOG_SETTING_WIDGET_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\setting_widget_background\\bg_"//���ý���ؼ�����ͼƬ·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_SETTING_WIDGET_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//���ý���ؼ�����ͼƬ·���ĺ�׺����
#define DIALOG_SETTING_STATIC_BACKGROUND_PICTURE_PATH_STRING ".\\picture_desktop\\setting_static_background\\dialog.png"//��̬���ý��汳��ͼƬ·��
#define DIALOG_SETTING_DYNAMIC_BACKGROUND_PICTURE_PATH_STRING ".\\picture_desktop\\setting_dynamic_background\\dialog.png"//��̬���ý��汳��ͼƬ·��
#define DIALOG_SETTING_OTHER_BACKGROUND_PICTURE_PATH_STRING ".\\picture_desktop\\setting_other_background\\dialog.png"//�������ý��汳��ͼƬ·��
#define DIALOG_INFORMATION_HELP_PATH_STRING ".\\picture_desktop\\help_information\\information_"//��Ϣ����ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_MARGIN_PICTURE_PATH_STRING ".\\picture_start\\warning_margin\\margin.png"//��Ϣ��߿�ͼƬ·��
#define DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_background\\background_"//��Ϣ�򱳾�·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//��Ϣ�򱳾�·���ĺ�׺����
#define DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING ".png"//��Ϣ����ʾ��������·���ĺ�׺����
#define DIALOG_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_chara\\chara_0"//��Ϣ�����ͼƬ·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_CHARA_PICTURE_PATH_BREAK_STRING "_0"//��Ϣ�����ͼƬ·�����»��߲���
#define DIALOG_CHARA_PICTURE_PATH_BACK_STRING ".png"//��Ϣ�����ͼƬ·���ĺ�׺����
#define DIALOG_INFORMATION_OPEN_MORE_THAN_ONE_PATH_STRING ".\\picture_desktop\\open_more_than_one_information\\information_"//�࿪������ֹ��ʾ��Ϣ
#define DIALOG_INFORMATION_FILE_PICTURE_PATH_STRING ".\\picture_desktop\\filedialog_information\\information_"//�ļ��򿪻򱣴�ѡ����ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_FILE_HEAD_PICTURE_PATH_STRING ".\\picture_desktop\\filedialog_information\\informationhead_"//�ļ��򿪻򱣴�ѡ����ʾ��ͷ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\filedialog_background\\background_"//�򿪻򱣴��ļ���Ϣ�򱳾�·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//�򿪻򱣴��ļ���Ϣ�򱳾�·���ĺ�׺����
#define DIALOG_FILE_MARGIN_PICTURE_PATH_STRING ".\\picture_desktop\\filedialog_margin\\margin.png"//�ļ����뱣����Ϣ��߿�ͼƬ·��
#define DIALOG_INFORMATION_CANNOT_START_PROGRAM_PATH_STRING ".\\picture_desktop\\cannot_start_program_information\\information_"//�޷��򿪳�����ʾ��Ϣ
#define DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING ".\\picture_desktop\\wrong_file_or_path_information\\information_"//���ô��ڲ����ڵ��ļ���·��������ʾ��Ϣ

#endif