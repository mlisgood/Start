#ifndef DEFINE_H
#define DEFINE_H

//ͷ�ļ�
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QFileInfo>
#include <QByteArray>
#include <QFile>
#include <QPropertyAnimation>
#include <QThread>
#include <QMutex>
#include <QDir>
#include <QFileSystemModel>
#include <QScrollBar>
#include <QFontDatabase>
#include <QSettings>
#include <string>
#include <tchar.h>
#include <fstream>
#include <windows.h>
#include <shellapi.h>
#include <des.h>
#include <aes.h>
#include <md4.h>
#include <md5.h>
#include <sha.h>
#include <sha3.h>
#include <keccak.h>
#include "ExportClassLockSimple.h"
#include "ExportClassLockNormal.h"
#include "ui_Lock.h"
#include "ui_Help.h"
#include "ui_LockSimpleOpposite.h"
#include "ui_LockSimple.h"
#include "ui_LockNormal.h"
#include "ui_LockNormalSingleKey.h"
#include "ui_LockNormalDoubleKey.h"
#include "ui_File.h"
#include "ui_UnlockSimpleOppositeCheck.h"
#include "ui_UnlockSimpleAddCheck.h"
#include "ui_UnlockNormalSingleCheck.h"
#include "ui_UnlockNormalDoubleCheck.h"
#include "ui_LockNormalHashCalculate.h"
#include "ui_Set.h"
#include "ui_LockSimpleAdd.h"
#include "ui_LockSimpleAddGetDigit.h"
#include "ui_UnlockSimpleAddCheckDigit.h"
#include "Lock.h"
#include "Help.h"
#include "LockSimpleOpposite.h"
#include "LockSimple.h"
#include "LockNormal.h"
#include "LockNormalSingleKey.h"
#include "LockNormalDoubleKey.h"
#include "LockNormalHashCalculate.h"
#include "File.h"
#include "UnlockSimpleOppositeCheck.h"
#include "UnlockSimpleAddCheck.h"
#include "UnlockNormalSingleCheck.h"
#include "UnlockNormalDoubleCheck.h"
#include "Set.h"
#include "LockSimpleAdd.h"
#include "LockSimpleAddGetDigit.h"
#include "UnlockSimpleAddCheckDigit.h"

//���п�
#pragma comment(lib,"cryptlib.lib")//����crypto++���п�

//���Ի���
#pragma execution_character_set("utf-8")

//ȫ�ֳ���
#define FILE_FONT_DEFAULT_SIZE 9//Ĭ�������С
#define FILE_FONT_PATH_STRING ".\\font\\font_df_girl.ttf"//�����ļ�·��
#define FILE_KEY_WRITE_BINARY_TYPE_1_NUMBER 1//��������Կ�ļ���������1����ȡ������Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_2_NUMBER 2//��������Կ�ļ���������2���򵥼Ӽ�����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_3_NUMBER 3//��������Կ�ļ���������3��DES����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_4_NUMBER 4//��������Կ�ļ���������4��2-key 3DES����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_5_NUMBER 5//��������Կ�ļ���������5��3-key 3DES����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_6_NUMBER 6//��������Կ�ļ���������6��AES-128����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_7_NUMBER 7//��������Կ�ļ���������7��AES-192����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_8_NUMBER 8//��������Կ�ļ���������8��AES-256����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_9_NUMBER 9//��������Կ�ļ���������9��RSA��Կ����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_10_NUMBER 10//��������Կ�ļ���������10��RSA˽Կ����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_11_NUMBER 11//��������Կ�ļ���������11��ECC��Կ����Ӧ����
#define FILE_KEY_WRITE_BINARY_TYPE_12_NUMBER 12//��������Կ�ļ���������12��ECC˽Կ����Ӧ����
#define FILE_KEY_AES_MIDDLE_KEY_LENGTH 24//AES-192��Ӧ��Կ����
#define FILE_KEYFILE_MAGIC_NUMBER_STRING_SIZE_NUMBER 8//��Կ�ļ�ͷ��ħ�����ֶ�Ӧʮ������������ռ��С
#define FILE_KEYFILR_INTERVAL_NUMBER_HEX_STRING_SIZE_NUMBER 8//��Կ�ļ��ָ�����Ӧʮ������������ռ��С
#define FILE_KEYFILR_INTERVAL_SHORT_NUMBER_HEX_STRING_SIZE_NUMBER 4//��Կ�ļ��̷ָ�����Ӧʮ������������ռ��С
#define FILE_KEYFILE_HEAD_NUMBER_STRING_SIZE_NUMBER 4//��Կ�ļ�������ͷ���������ֶ�Ӧʮ������������ռ��С
#define FILE_OUTPUT_FILE_LOCK_FRONT_PATH_STRING ".\\target_lock"//Ĭ����������ļ�ǰ�벿�ֲ���·��
#define FILE_OUTPUT_FILE_UNLOCK_FRONT_PATH_STRING ".\\target_unlock"//Ĭ����������ļ�ǰ�벿�ֲ���·��
#define FILE_OUTPUT_FILE_KEY_BACK_PATH_STRING "key.txt"//�����Կ�ļ�·����׺
#define FILE_OUTPUT_FILE_KEY_BINARY_BACK_PATH_STRING "keyfile"//Ĭ�������������Կ�ļ�·����׺
#define FILE_OUTPUT_FILE_HISTORY_FRONT_PATH_STRING ".\\history"//Ĭ�������ʷ��Ϣ�ļ�ǰ�벿�ֲ���·��
#define FILE_OUTPUT_FILE_HISTORY_BACK_PATH_STRING "\\history.txt"//�����ʷ��Ϣ�ļ�·����׺
#define FILE_TEMP_FILE_FRONT_PATH_STRING ".\\tempfile"//Ĭ����ʱ�ļ�·����ǰ�벿��
#define FILE_DLL_FILE_READ_PATH_STRING L"LockSimple.dll"//�򵥼��ܶ�ȡdll�ļ�λ��
#define FILE_DLL_FILE_NORMAL_READ_PATH_STRING L"LockNormal.dll"//������ܶ�ȡdll�ļ�λ��
#define FILE_LOCK_DOUBLE_KEY_DEFAULT_NAME_STRING "δ����"//�ǶԳƼ�����Կ�ļ�Ĭ���ļ���
#define FILE_SET_PATH_STRING ".\\setting_lock\\setting.ini"//���������ļ�·��
#define FILE_SETTING_CATALOG_1_1_INNER_PATH_STRING "/path/lock"//�����ļ�Ŀ¼1-1�ļ���·��
#define FILE_SETTING_CATALOG_1_2_INNER_PATH_STRING "/path/unlock"//�����ļ�Ŀ¼1-2�ļ���·��
#define FILE_SETTING_CATALOG_1_3_INNER_PATH_STRING "/path/temp"//�����ļ�Ŀ¼1-3�ļ���·��
#define FILE_SETTING_CATALOG_1_4_INNER_PATH_STRING "/path/history"//�����ļ�Ŀ¼1-4�ļ���·��
#define FILE_SETTING_CATALOG_2_1_INNER_PATH_STRING "/suffix/lock"//�����ļ�Ŀ¼2-1�ļ���·��
#define FILE_SETTING_CATALOG_2_2_INNER_PATH_STRING "/suffix/unlock"//�����ļ�Ŀ¼2-2�ļ���·��
#define FILE_SETTING_CATALOG_2_3_INNER_PATH_STRING "/suffix/text"//�����ļ�Ŀ¼2-3�ļ���·��
#define FILE_SETTING_CATALOG_2_4_INNER_PATH_STRING "/suffix/binary"//�����ļ�Ŀ¼2-4�ļ���·��
#define FILE_SETTING_CATALOG_3_1_INNER_PATH_STRING "/boolvalue/history"//�����ļ�Ŀ¼3-1�ļ���·��
#define FILE_SETTING_CATALOG_3_2_INNER_PATH_STRING "/boolvalue/textkey"//�����ļ�Ŀ¼3-2�ļ���·��
#define FILE_SETTING_CATALOG_3_3_INNER_PATH_STRING "/boolvalue/binarykey"//�����ļ�Ŀ¼3-3�ļ���·��
#define FILE_SETTING_CATALOG_PATH_DEFAULT_STRING "#default#"//�����ļ�·��Ĭ��ֵ
#define FILE_SETTING_SUFFIX_LOCK_DEFAULT_STRING "lock"//�����ļ������ļ���׺Ĭ��ֵ
#define FILE_SETTING_SUFFIX_UNLOCK_DEFAULT_STRING "unlock"//�����ļ������ļ���׺Ĭ��ֵ
#define FILE_SETTING_SUFFIX_INTERVAL_STRING "."//�����ļ������ļ���׺�ָ���
#define FILE_KEY_FILE_MAGIC_NUMBER_HEX_STRING "57555341FFFF4C46"//��������Կ�ļ�ͷ��ħ�����ֶ�Ӧʮ���������ݣ���������Ϊ��WUSAxxLF������xx����ʮ�������롰FFFF����䣩
#define FILE_PUBLIC_KEY_TYPE_STRING "public"//�ǶԳƼ��ܹ�Կ��Կ��������
#define FILE_PRIVATE_KEY_TYPE_STRING "private"//�ǶԳƼ���˽Կ��Կ��������
#define WINDOW_SIZE_WIDTH_NUMBER 400//���ڿ��
#define WINDOW_SIZE_HEIGHT_NUMBER 400//���ڸ߶�
#define WINDOW_RANDOM_MAX_NUMBER 8//���ƴ��ڱ����õ�����������ֵ
#define WINDOW_RANDOM_MIN_NUMBER 1//���ƴ��ڱ����õ����������Сֵ
#define WINDOW_ANIMATION_TIME_NUMBER 300//�����͹رն�������ʱ��
#define WINDOW_ANIMATION_TRANSPRENT_TRANSPRENT_NUMBER 0.4//����͸��ģʽ͸����
#define WINDOW_ANIMATION_TRANSPRENT_NORMAL_NUMBER 1//���ڳ���ģʽ͸����
#define WINDOW_ANIMATION_TRANSPRENT_DISAPPEAR_NUMBER 0//������ʧ͸����
#define WINDOW_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_lock\\background\\background_"//����ͼƬ·���ķǺ�׺���ֵĲ��䲿��
#define WINDOW_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//����ͼƬ·���ĺ�׺����
#define WINDOW_BACKGROUND_MARGIN_PICTURE_PATH_STRING ".\\picture_lock\\background_margin\\margin.png"//�߿�ͼƬ·��
#define DIALOG_SIZE_WIDTH_NUMBER 600//��Ϣ����
#define DIALOG_SIZE_HEIGHT_NUMBER 200//��Ϣ��߶�
#define DIALOG_LOCK_SIZE_WIDTH_NUMBER 400//���ܽ��ܴ��ڿ��
#define DIALOG_LOCK_SIZE_HEIGHT_NUMBER 600//���ܽ��ܴ��ڸ߶�
#define DIALOG_LOCK_BACKGROUND_OFFSET_X_NUMBER 0//���ܽ��ܴ��ڷ����ﱳ��ͼ�������ƫ��
#define DIALOG_LOCK_BACKGROUND_OFFSET_Y_NUMBER 400//���ܽ��ܴ��ڷ����ﱳ��ͼ��������ƫ��
#define DIALOG_RANDOM_MAX_NUMBER 5//������Ϣ�򱳾��õ�����������ֵ
#define DIALOG_RANDOM_MIN_NUMBER 1//������Ϣ�򱳾��õ����������Сֵ
#define DIALOG_CHARA_PICTURE_RANDOM_MAX_NUMBER 8//������Ϣ�����ͼƬ�õ�����������ֵ
#define DIALOG_CHARA_PICTURE_RANDOM_MIN_NUMBER 1//������Ϣ�����ͼƬ�õ����������Сֵ
#define DIALOG_LOCK_CHARA_PICTURE_COUNT_INTERVAL_NUMNER 5000//���ܽ��ܴ�������ͼƬ�ֲ����
#define DIALOG_LOCK_CHARA_PICTURE_TRANSPARENT_COUNT_INTERVAL_NUMNER 50//���ܽ��ܴ�������ͼƬ͸�����л�ʱ����
#define DIALOG_LOCK_CHARA_PICTURE_TRANSPARENT_COUNT_MEASURE_NUMNER 0.05//���ܽ��ܴ�������ͼƬ͸�����л�����
#define DIALOG_INFORMATION_FILE_WIDTH_NUMBER 600//�ļ��򿪻򱣴���Ϣ�����ı���Ϣ���
#define DIALOG_INFORMATION_FILE_HEIGHT_NUMBER 30//�ļ��򿪻򱣴���Ϣ�����ı���Ϣ�߶�
#define DIALOG_INFORMATION_FILE_X_OFFSET_NUMBER 0//�ļ��򿪻򱣴���Ϣ���ı���Ϣ������ʼλ��
#define DIALOG_INFORMATION_FILE_Y_OFFSET_NUMBER 445//�ļ��򿪻򱣴���Ϣ���ı���Ϣ������ʼλ��
#define DIALOG_INFORMATION_FILE_HEAD_X_OFFSET_NUMBER 0//�ļ��򿪻򱣴���Ϣ��ͷ���ı���Ϣ������ʼλ��
#define DIALOG_INFORMATION_FILE_HEAD_Y_OFFSET_NUMBER 50//�ļ��򿪻򱣴���Ϣ��ͷ���ı���Ϣ������ʼλ��
#define DIALOG_LOCK_CHARA_PICTURE_MIN_NUMBER 1//���ܽ��ܴ�������ͼƬ�ֲ���С���
#define DIALOG_LOCK_CHARA_PICTURE_MAX_NUMBER 8//���ܽ��ܴ�������ͼƬ�ֲ�������
#define DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_NUMBER 8//�򵥼����ı������������Ԫ�������Ŀ
#define DIALOG_SIMPLE_LOCK_LINEEDIT_TRANSFORM_LENGTH_NUMBER 4//�򵥼����ı���ת��Ϊ16�������ݺ�ռ�ÿռ�
#define DIALOG_PROGRESSBAR_TIMES_NUMBER 100//���ܴ��ڽ���������
#define DIALOG_PROGRESSBAR_MAX_NUMBER 100//���ܴ��ڽ��������ֵ
#define DIALOG_PROGRESSBAR_CHANGE_FONT_COLOR_NUMBER 50//���ܴ��ڽ������л�������ɫʱ����ֵ
#define DIALOG_LOCK_SIMPLE_ADD_MAX_UNIT_NUMBER 16//�Ӽ��������ѭ����Ԫ��Ŀ
#define DIALOG_LOCK_NORMAL_DOUBLE_DEFAULE_SIZE_NUMBER 1024//RSA����Ĭ����Կ����
#define DIALOG_SIMPLE_LOCK_LINEEDIT_DEFAULT_INSERT_CHAR '0'//�򵥼����ı���Ԫ�ع���ʱĬ�ϲ�����ַ�
#define DIALOG_LOCK_SIMPLE_DIRECTION_RIGHT_STRING "right"//����˳�������ַ�����˳��
#define DIALOG_LOCK_SIMPLE_DIRECTION_LEFT_STRING "left"//����˳�������ַ���������
#define DIALOG_LOCK_SIMPLE_DIRECTION_RIGHT_AND_LEFT_STRING "right and left"//����˳�������ַ�����˫��
#define DIALOG_LOCK_SIMPLE_DIRECTION_NO_HEAD_DIGIT_STRING "null"//��ͷ������������ʾ
#define DIALOG_INFORMATION_PICTURE_PATH_BACK_STRING ".png"//��Ϣ����ʾ��������·���ĺ�׺����
#define DIALOG_INFORMATION_HELP_PATH_STRING ".\\picture_lock\\help_information\\information_"//��Ϣ����ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_LOCK_FAIL_PATH_STRING ".\\picture_lock\\lock_fail_information\\information_"//ȡ������ʧ����ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_UNLOCK_FAIL_PATH_STRING ".\\picture_lock\\unlock_fail_information\\information_"//ȡ������ʧ����ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_KEYFILE_CANNOT_OPEN_PATH_STRING ".\\picture_lock\\keyfile_cannot_open_information\\information_"//�޷�����Կ�ļ���ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_OPEN_WRONG_KEYFILE_PATH_STRING ".\\picture_lock\\open_wrong_keyfile_information\\information_"//�򿪴������Կ�ļ���ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_CANNOT_OPEN_PATH_STRING ".\\picture_lock\\cannot_open_path_information\\information_"//���ý���򿪴�����ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_DELETE_FAIL_PATH_STRING ".\\picture_lock\\delete_fail_information\\information_"//���ý���ɾ��ʧ����ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_WRONG_KEY_PATH_STRING ".\\picture_lock\\wrong_key_information\\information_"//���������Կ������ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_WRONG_LENGTH_KEY_PATH_STRING ".\\picture_lock\\wrong_length_key_information\\information_"//���������Կ���Ȳ���ȷ��ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_CANNOT_SAVE_STRING ".\\picture_lock\\cannot_save_information\\information_"//��������޷�������ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_WRONG_KEY_STRING ".\\picture_lock\\lock_normal_wrong_key_information\\information_"//���������Կ������ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_OUT_OF_RANGE_STRING ".\\picture_lock\\lock_normal_out_of_range_information\\information_"//���������Կ���̻�ԭ�ĳ�����Χ��ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_UNLOCK_OUT_OF_RANGE_STRING ".\\picture_lock\\unlock_normal_out_of_range_information\\information_"//������ܽ������ĳ��Ȳ���ȷ��ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_HASH_CHECK_CORRECT_STRING ".\\picture_lock\\hash_check_correct\\information_"//�������У��ɹ���ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_HASH_CHECK_INCORRECT_STRING ".\\picture_lock\\hash_check_incorrect\\information_"//�������У��ʧ����ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_INFORMATION_HASH_CHECK_WRONG_HASH_STRING ".\\picture_lock\\hash_check_wrong_hash\\information_"//�������У����Ϣ����ȷ��ʾ��������·���ķǺ�׺���䲿��
#define DIALOG_MARGIN_PICTURE_PATH_STRING ".\\picture_start\\warning_margin\\margin.png"//��Ϣ��߿�ͼƬ·��
#define DIALOG_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_background\\background_"//��Ϣ�򱳾�·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//��Ϣ�򱳾�·���ĺ�׺����
#define DIALOG_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_start\\warning_chara\\chara_0"//��Ϣ�����ͼƬ·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_CHARA_PICTURE_PATH_BREAK_STRING "_0"//��Ϣ�����ͼƬ·�����»��߲���
#define DIALOG_CHARA_PICTURE_PATH_BACK_STRING ".png"//��Ϣ�����ͼƬ·���ĺ�׺����
#define DIALOG_BACKGROUND_CHARA_PICTURE_PATH_FRONT_STRING ".\\picture_lock\\background\\background_real_"//���ܴ��ڿ��л����ﱳ��ͼƬ·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_BACKGROUND_CHARA_PICTURE_PATH_BACK_STRING ".png"//���ܴ��ڿ��л����ﱳ��ͼƬ·���ĺ�׺����
#define DIALOG_BACKGROUND_CHARA_TRANSPARENT_PICTURE_PATH_STRING ".\\picture_lock\\background\\transparent.png"//���ܴ��ڿ��л����ﱳ��ͼƬȫ͸��ͼƬ·��
#define DIALOG_LOCK_MARGIN_PICTURE_PATH_STRING ".\\picture_lock\\lock_margin\\margin.png"//���ܴ��ڱ߿�ͼƬ·��
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_FRONT_STRING ".\\picture_lock\\filedialog_background\\background_"//�򿪻򱣴��ļ���Ϣ�򱳾�·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_FILE_BACKGROUND_PICTURE_PATH_BACK_STRING ".png"//�򿪻򱣴��ļ���Ϣ�򱳾�·���ĺ�׺����
#define DIALOG_INFORMATION_WRONG_FILE_OR_PATH_STRING ".\\picture_lock\\wrong_file_or_path_information\\information_"//���ô��ڲ����ڵ��ļ���·��������ʾ��Ϣ
#define DIALOG_INFORMATION_FILE_PICTURE_PATH_STRING ".\\picture_lock\\filedialog_information\\information_"//�ļ��򿪻򱣴�ѡ����ʾ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_INFORMATION_FILE_HEAD_PICTURE_PATH_STRING ".\\picture_lock\\filedialog_information\\informationhead_"//�ļ��򿪻򱣴�ѡ����ʾ��ͷ������·���ķǺ�׺���ֵĲ��䲿��
#define DIALOG_FILE_MARGIN_PICTURE_PATH_STRING ".\\picture_lock\\filedialog_margin\\margin.png"//�ļ����뱣����Ϣ��߿�ͼƬ·��
#define DIALOG_INFORATION_FILE_KEYFILE_FILTER_STRING "*.keyfile"//�򿪻򱣴���Կ�ļ���Ϣ�����������
#define DIALOG_BACKGROUND_UNLOCK_SIMPLE_OPPOSITE_CHECK_PATH_STRING ".\\picture_lock\\unlock_is_use_binary_key_file_dialog\\dialog.png"//�򵥽���ȷ�Ͽ򱳾�·��
#define DIALOG_BACKGROUND_UNLOCK_NORMAL_SINGLE_CHECK_PATH_STRING ".\\picture_lock\\unlock_normal_single_is_use_binary_key_file_dialog\\dialog.png"//����ԳƼ��ܽ���ȷ�Ͽ򱳾�·��
#define DIALOG_BACKGROUND_UNLOCK_NORMAL_DOUBLE_CHECK_PATH_STRING ".\\picture_lock\\unlock_normal_double_is_use_binary_key_file_dialog\\dialog.png"//����ǶԳƼ��ܽ���ȷ�Ͽ򱳾�·��
#define DIALOG_BACKGROUND_LOCK_SIMPLE_ADD_GET_DIGIT_PATH_STRING ".\\picture_lock\\lock_get_digit_set_dialog\\dialog.png"//���ܻ�ȡ�Ӽ��������汳��·��
#define DIALOG_BACKGROUND_UNLOCK_SIMPLE_ADD_SET_DIGIT_PATH_STRING ".\\picture_lock\\unlock_simple_add_digit_dialog\\dialog.png"//���ܼӼ�����ȷ�Ͽ򱳾�·��
#define DIALOG_BACKGROUND_SET_PATH_STRING ".\\picture_lock\\set_dialog\\dialog.png"//���ý��汳��·��
#define DIALOG_LOCK_SIMPLE_ADD_DEFAULT_UNIT_INSERT_STRING "0"//�Ӽ�����ѭ����ԪĬ�ϼӼ�����
#define DIALOG_LOCK_NORMAL_DOUBLE_DEFAULE_CURVE_TYPE_STRING "secp112r1"//ECC����Ĭ����������
#define DIALOG_HASH_CALCULATOR_TYPE_STRING "224"//ɢ��ֵ����Ĭ������
#define DIALOG_LOCK_NORMAL_DES_DESCRIPTION_STRING "DES�����ݼ��ܱ�׼����1976�걻�������������Ĺ��ұ�׼��ȷ��Ϊ�������ϴ����׼����һ��ʹ��56λ��Կ�ĶԳ��㷨��ʣ��8λ������żУ�顣������ʹ�õ���Կ���̣������Ѿ�����һ�ְ�ȫ�ļ��ܷ�������2001�꣬DES��Ϊһ����׼�Ѿ����߼����ܱ�׼(AES)��ȡ�������⣬DES�Ѿ�������Ϊ���ұ�׼�Ƽ�Э�ἴǰ���ұ�׼�ֵ�һ����׼��"//������ܹ���DES���ܵ�����
#define DIALOG_LOCK_NORMAL_DES_EDE2_DESCRIPTION_STRING "3DES��һ�ֶԳ��㷨���൱���Ƕ�ÿ�����ݿ�Ӧ���������ݼ��ܱ�׼(DES)�㷨��ΪӦ��ԭ��DES�������Կ���ȹ��̱�����ױ������ƽ�����⣬3DES�ṩ��һ����Լ򵥵ķ�������ͨ������DES����Կ�������������ƵĹ��������㷨ʹ��112λ��Կ����ȫ�Խϼ򵥵�Ӧ��DES���ε�ǿ�ȸߣ����Է�����;����������"//������ܹ���DES-EDE2���ܵ�����
#define DIALOG_LOCK_NORMAL_DES_EDE3_DESCRIPTION_STRING "3DES��һ�ֶԳ��㷨���൱���Ƕ�ÿ�����ݿ�Ӧ���������ݼ��ܱ�׼(DES)�㷨��ΪӦ��ԭ��DES�������Կ���ȹ��̱�����ױ������ƽ�����⣬3DES�ṩ��һ����Լ򵥵ķ�������ͨ������DES����Կ�������������ƵĹ��������㷨ʹ��168λ��Կ����2-Key 3DES��ȣ���ȫ�Ը��ߡ�"//������ܹ���DES-EDE3���ܵ�����
#define DIALOG_LOCK_NORMAL_AES_MIN_DESCRIPTION_STRING "AES���߼����ܱ�׼���ֳ�Rijndael���ܷ��������������������õ�һ��������ܱ�׼�������׼�������ԭ�ȵ�DES���Ѿ����෽�����ҹ�Ϊȫ������ʹ�á�2006�꣬�߼����ܱ�׼�ѳ�Ϊ�Գ���Կ�����������е��㷨֮һ�����㷨ʹ��128λ��Կ��"//������ܹ���AES_MIN���ܵ�����
#define DIALOG_LOCK_NORMAL_AES_MIDDLE_DESCRIPTION_STRING "AES���߼����ܱ�׼���ֳ�Rijndael���ܷ��������������������õ�һ��������ܱ�׼�������׼�������ԭ�ȵ�DES���Ѿ����෽�����ҹ�Ϊȫ������ʹ�á�2006�꣬�߼����ܱ�׼�ѳ�Ϊ�Գ���Կ�����������е��㷨֮һ�����㷨ʹ��192λ��Կ��"//������ܹ���AES_MIDDLE���ܵ�����
#define DIALOG_LOCK_NORMAL_AES_MAX_DESCRIPTION_STRING "AES���߼����ܱ�׼���ֳ�Rijndael���ܷ��������������������õ�һ��������ܱ�׼�������׼�������ԭ�ȵ�DES���Ѿ����෽�����ҹ�Ϊȫ������ʹ�á�2006�꣬�߼����ܱ�׼�ѳ�Ϊ�Գ���Կ�����������е��㷨֮һ�����㷨ʹ��256λ��Կ��"//������ܹ���AES_MAX���ܵ�����
#define DIALOG_LOCK_NORMAL_RSA_DESCRIPTION_STRING "RSA��1977����Ron Rivest��Adi Shamir��Leonard Adlemanһ�������һ�ַǶԳƼ����㷨�����㷨�Ŀɿ��Խ����ڶԼ��������������ֽ���������ϡ�����ǰΪֹ�������ϻ�û���κοɿ��Ĺ���RSA�㷨�ķ�ʽ��"//������ܹ���RSA���ܵ�����
#define DIALOG_LOCK_NORMAL_ECC_DESCRIPTION_STRING "ECC����Բ��������ѧ����һ�ֻ�����Բ������ѧ�Ĺ�����Կ�����㷨����Բ����������ѧ�е�ʹ������1985����Neal Koblitz��Victor Miller�ֱ��������ġ��䰲ȫ����������Բ������ɢ����������������ϡ���ĳЩ����£�����������RSAһ��ķ���ʹ�ø�С����Կ�����ṩ�൱�Ļ���ߵȼ��İ�ȫ�ԡ�"//������ܹ���ECC���ܵ�����
#define DIALOG_LOCK_NORMAL_MD4_DESCRIPTION_STRING "MD4����ʡ��ѧԺ����Ronald Rivest��1990����Ƶ�һ����ϢժҪ�㷨������һ������������Ϣ�����Ե�����ɢ�к�����ʵ�֣���ժҪ����Ϊ128λ������㷨Ӱ���˺������㷨��MD5��SHA����ȡ�ĿǰMD4�ѱ���̭��"//������ܹ���MD4������
#define DIALOG_LOCK_NORMAL_MD5_DESCRIPTION_STRING "MD5����������ѧ��Ronald Linn Rivest��ƣ���1992�깫��������ȡ��MD4�㷨�����㷨���Բ�����һ��128λ��ɢ��ֵ������ȷ����Ϣ��������һ�¡�2004�꣬MD5��֤ʵ�޷���ֹ��ײ����˲������ڰ�ȫ����֤����SSL������Կ��֤��������ǩ������;����ǰ��MD5�㷨�����ձ顢�ȶ������ٵ��ص㣬�Թ㷺Ӧ������ͨ���ݵĴ���������"//������ܹ���MD5������
#define DIALOG_LOCK_NORMAL_SHA1_DESCRIPTION_STRING "SHA-1����ȫɢ���㷨1����һ������ɢ�к������������Ұ�ȫ����ƣ������������ұ�׼�����о���(NIST)����Ϊ�������ݴ����׼(FIPS)��SHA-1��������һ������Ϊ��ϢժҪ��160λɢ��ֵ��2005�꣬���������Ա�����˶�SHA-1����Ч������������������㷨���ܲ�����ȫ�����ܼ���ʹ�á�Ŀǰ��SHA-1�Ѿ�������Ϊ�ɵ����г����ʽ𡢳��������Դ�Ĺ����ߡ�"//������ܹ���SHA1������
#define DIALOG_LOCK_NORMAL_SHA2_DESCRIPTION_STRING "SHA-2����ȫɢ���㷨2����һ�����������Ұ�ȫ���з�������ɢ�к����㷨��׼�������������ұ�׼�����о���(NIST)��2001�귢��������SHA�㷨֮һ����SHA-1�ĺ���ߡ�"//������ܹ���SHA2������
#define DIALOG_LOCK_NORMAL_SHA3_DESCRIPTION_STRING "SHA-3����ȫɢ���㷨3��֮ǰ��ΪKeccak�㷨�����㷨��2015��8��5�����������ұ�׼�����о���(NIST)ͨ��FIPS 202��ʽ����SHA-3��������ȡ��SHA-2����ΪSHA-2��ǰ��û�г������Ե����㡣���ڶ�MD5��SHA-0��SHA-1���ֳɹ����ƽ⣬NIST��Ϊ��Ҫһ����֮ǰ�㷨��ͬ�ģ����滻�ļ���ɢ���㷨��Ҳ�������ڵ�SHA-3����2015��8��SHA3������ɱ�׼��ʱ��NIST����������㷨����׼��SHA3��ԭ�ȵ�Keccak�����������ˡ���Ϊ���ڻ���һЩ�ط����������㷨���ã����ʹ��ʱ��Ҫ�ر�ע�⡣"//������ܹ���SHA3������
#define DIALOG_LOCK_NORMAL_KECCAK_DESCRIPTION_STRING "Keccak��SHA-3��ǰ����2015��8��SHA3������ɱ�׼��ʱ��NIST����������㷨����׼��SHA3��ԭ�ȵ�Keccak�����������ˡ���Ϊ���ڻ���һЩ�ط����������㷨���ã����ʹ��ʱ��Ҫ�ر�ע�⡣"//������ܹ���Keccak������


#endif