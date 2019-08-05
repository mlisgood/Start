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
#include <QSplashScreen>
#include <string>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include "ui_DesktopOmake.h"
#include "ui_Help.h"
#include "ui_File.h"
#include "DesktopOmake.h"
#include "Help.h"
#include "File.h"

//���Ի���
#pragma execution_character_set("utf-8")

//ȫ�ֳ���
#define FILE_FONT_DEFAULT_SIZE 9//Ĭ�������С
#define FILE_FONT_PATH_STRING ".\\font\\font_df_girl.ttf"//�����ļ�·��
#define FILE_SETTING_STATIC_PATH_STRING ".\\setting_desktop\\setting_static.ini"//��̬��Ϣ�����ļ�
#define WINDOW_SIZE_WIDTH_NUMBER 1000//��������
#define WINDOW_SIZE_HEIGHT_NUMBER 600//������߶�
#define WINDOW_WORD_PICTURE_X_OFFSET_NUMBER 447//����ͼƬ����ƫ��
#define WINDOW_WORD_PICTURE_Y_OFFSET_NUMBER 0//����ͼƬ����ƫ��
#define WINDOW_WORD_PICTURE_SIZE_WIDTH_NUMBER 480//��������
#define WINDOW_WORD_PICTURE_SIZE_HEIGHT_NUMBER 73//������߶�
#define WINDOW_ANIMATION_TIME_NUMBER 300//�����͹رն�������ʱ��
#define WINDOW_ANIMATION_HIDE_NUMBER 1//��������ʱ��͸����
#define WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER 0//������ʧ͸����
#define WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER 1//���ڳ���͸����
#define WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\program_desktopomake\\main_background\\dialog.png"//����ͼƬ·��
#define WINDOW_WORD_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\program_desktopomake\\word_background\\word.png"//����ͼƬ·��
#define WINDOW_SPLASH_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\program_desktopomake\\splash_picture\\splash.png"//��������ͼƬ·��
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
#define DIALOG_INFORMATION_HELP_PATH_STRING ".\\picture_desktop\\help_information\\information_"//��Ϣ����ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_MARGIN_PICTURE_PATH_STRING ".\\picture_start\\warning_margin\\margin.png"//��Ϣ��߿�ͼƬ·��
#define DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_background\\background_"//��Ϣ�򱳾�·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//��Ϣ�򱳾�·���ĺ�׺����
#define DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING ".png"//��Ϣ����ʾ��������·���ĺ�׺����
#define DIALOG_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_chara\\chara_0"//��Ϣ�����ͼƬ·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_CHARA_PICTURE_PATH_BREAK_STRING "_0"//��Ϣ�����ͼƬ·�����»��߲���
#define DIALOG_CHARA_PICTURE_PATH_BACK_STRING ".png"//��Ϣ�����ͼƬ·���ĺ�׺����
#define DIALOG_INFORMATION_FILE_PICTURE_PATH_STRING ".\\picture_desktop\\filedialog_information\\information_"//�ļ��򿪻򱣴�ѡ����ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_FILE_HEAD_PICTURE_PATH_STRING ".\\picture_desktop\\filedialog_information\\informationhead_"//�ļ��򿪻򱣴�ѡ����ʾ��ͷ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_desktop\\filedialog_background\\background_"//�򿪻򱣴��ļ���Ϣ�򱳾�·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//�򿪻򱣴��ļ���Ϣ�򱳾�·���ĺ�׺����
#define DIALOG_FILE_MARGIN_PICTURE_PATH_STRING ".\\picture_desktop\\filedialog_margin\\margin.png"//�ļ����뱣����Ϣ��߿�ͼƬ·��
#define DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING ".\\picture_desktop\\program_desktopomake\\wrong_picture_file\\information_"//��ͼƬ������ʾ��Ϣ

#endif