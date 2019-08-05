#ifndef DEFINE_H
#define DEFINE_H

//����Ҫ��ͷ�ļ�

#include <QtWidgets/QMainWindow>
#include <QtCore>
#include <QSplashScreen> 
#include <QThread>
#include <QMouseEvent>
#include <QMainWindow>
#include <QPoint>
#include <QWidget>
#include <QString>
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QFontDatabase>
#include <QFileSystemModel>
#include <QDir>
#include <QScrollBar>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include "ui_Start.h"
#include "ui_Filemissing.h"
#include "Start.h"
#include "Filemissing.h"
#include "main.h" 

//ָ�����Ի���
#pragma execution_character_set("utf-8")

//����Ҫ�ĳ���

#define FILE_FONT_DEFAULT_SIZE 9//Ĭ�������С
#define FILE_FONT_PATH_STRING ".\\font\\font_df_girl.ttf"//�����ļ�·��
#define FILE_COPY_SOURCE_1_PATH_STRING ".\\default_setting\\setting_desktop"//���������ļ�Դ�ļ���1·��
#define FILE_COPY_SOURCE_2_PATH_STRING ".\\default_setting\\setting_lock"//���������ļ�Դ�ļ���2·��
#define FILE_COPY_SOURCE_3_PATH_STRING ".\\default_setting\\setting_notepad"//���������ļ�Դ�ļ���3·��
#define FILE_COPY_SOURCE_4_PATH_STRING ".\\default_setting\\setting_tools"//���������ļ�Դ�ļ���4·��
#define FILE_COPY_TARGET_1_PATH_STRING ".\\setting_desktop"//���������ļ�Ŀ���ļ���1·��
#define FILE_COPY_TARGET_2_PATH_STRING ".\\setting_lock"//���������ļ�Ŀ���ļ���2·��
#define FILE_COPY_TARGET_3_PATH_STRING ".\\setting_notepad"//���������ļ�Ŀ���ļ���3·��
#define FILE_COPY_TARGET_4_PATH_STRING ".\\setting_tools"//���������ļ�Ŀ���ļ���4·��
#define WINDOW_ANIMATION_TIME_NUMBER 300//�����͹رն�������ʱ��
#define WINDOW_ANIMATION_TRANSPRENT_TRANSPRENT_NUMBER 0.4//����͸��ģʽ͸����
#define WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER 1//���ڳ���ģʽ͸����
#define WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER 0//������ʧ͸����
#define WINDOW_START_BACKGROUND_PICTURE_PATH_STRING ".\\picture_start\\window_start_background\\dialog.png"
#define DIALOG_SIZE_WIDTH_NUMBER 600//��ʾ����
#define DIALOG_SIZE_HEIGHT_NUMBER 200//��ʾ��߶�
#define DIALOG_RANDOM_MAX_NUMBER 5//������ʾ�򱳾��õ�����������ֵ������ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define DIALOG_RANDOM_MIN_NUMBER 1//������ʾ�򱳾��õ����������Сֵ������ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER 8//������ʾ�����ͼƬ�õ�����������ֵ������ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER 1//������ʾ�����ͼƬ�õ����������Сֵ������ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define DIALOG_INFORMATION_STATUS_1_FLAG 1//��ʾ����ʾ��Ϣ1
#define DIALOG_INFORMATION_STATUS_2_FLAG 2//��ʾ����ʾ��Ϣ2
#define DIALOG_INFORMATION_STATUS_3_FLAG 3//��ʾ����ʾ��Ϣ3
#define DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_background\\background_"//��ʾ�򱳾�·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//��ʾ�򱳾�·���ĺ�׺����
#define DIALOG_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_chara\\chara_0"//��ʾ�����ͼƬ·���ķǺ�׺���ֵĲ��䲿�֡�����ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define DIALOG_CHARA_PICTURE_PATH_BREAK_STRING "_0"//��ʾ�����ͼƬ·�����»��߲��֡�����ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define DIALOG_CHARA_PICTURE_PATH_BACK_STRING ".png"//��ʾ�����ͼƬ·���ĺ�׺���֣�����ط��������Ĺ���ʹ���˳�������Ҫ�޸������д��ع���
#define DIALOG_MARGIN_PICTURE_PATH_STRING ".\\picture_start\\warning_margin\\margin.png"//��ʾ��߿�ͼƬ·��
#define DIALOG_INFORMATION_1_PICTURE_PATH_STRING ".\\picture_start\\warning_information\\information_1_"//��ʾ����ʾ����1����·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_2_PICTURE_PATH_STRING ".\\picture_start\\warning_information\\information_2_"//��ʾ����ʾ����2����·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_3_PICTURE_PATH_STRING ".\\picture_start\\warning_information\\information_3_"//��ʾ����ʾ����3����·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING ".png"//��ʾ����ʾ��������·���ĺ�׺����
#define DIALOG_SET_BACKGROUND_PICTURE_PATH_STRING ".\\picture_start\\set_dialog\\dialog.png"
#define DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING ".\\picture_start\\wrong_file_or_path_information\\information_"//���ô��ڲ����ڵ��ļ���·��������ʾ��Ϣ
#define DIALOG_INFORMATION_FILE_PICTURE_PATH_STRING ".\\picture_start\\filedialog_information\\information_"//�ļ��򿪻򱣴�ѡ����ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_FILE_HEAD_PICTURE_PATH_STRING ".\\picture_start\\filedialog_information\\informationhead_"//�ļ��򿪻򱣴�ѡ����ʾ��ͷ������·���ķǺ�׺���ֵĲ��䲿��

#endif
