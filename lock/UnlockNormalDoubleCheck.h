#ifndef UNLOCKNORMALDOUBLECHECK_H
#define UNLOCKNORMALDOUBLECHECK_H

#include "define.h"

namespace rem
{
	class UnlockNormalDoubleCheck : public QDialog
	{
		Q_OBJECT

	private:

		Ui::UnlockNormalDoubleCheckClass ui;//窗口
		QPoint m_point;//记录坐标用于移动窗口
		QPixmap main_picture;//需要绘制以便于作为窗口的图片
		QString *char_point_information;//从加密主界面得到的char指针型信息，包括：加密文件头部特征数字
		QString char_point_information_data;//从加密主界面得到的char指针型信息，包括：加密文件头部特征数字
		QString *key;//从加密主界面得到的密钥信息
		QString key_data;//从加密主界面得到的密钥信息
		QString key_type;//从加密主界面得到的密钥类型信息
		QString method;//从加密主界面得到的加密方法信息
		int bool_information_data_int;//从加密主界面得到的布尔型信息，包括：是否有头部特征数字。为了便于读取文件，使用int类型
		int *key_size;//从加密主界面得到的int型信息，包括：密钥大小
		int key_size_data;//从加密主界面得到的int型信息，包括：密钥大小
		bool m_bPressed;//确定窗口是否被按下
		bool is_escape_pressed;//用于屏蔽按下一次退出键后继续按下该键造成关闭动画循环
		bool *bool_information;//从加密主界面得到的布尔型信息，包括：是否有头部特征数字
		bool bool_information_data;//从加密主界面得到的布尔型信息，包括：是否有头部特征数字
		bool *is_continue;//主界面在执行完另一界面后是否继续下面的操作

	protected:

		void paintEvent(QPaintEvent *); //绘制背景图像

	public:

		//构造与析构函数
		UnlockNormalDoubleCheck(QWidget *parent = Q_NULLPTR);
		~UnlockNormalDoubleCheck();

		//设置成员函数
		void set_information(QString key_type, QString method, QString *key, QString *head_digit, bool *have_head_digit, bool *is_continue, int *key_size);//设置需要显示在界面上的信息，参数为：密钥类型，加密方法，由二进制数据转化为文本的密钥，加密文件头部特征数字，是否有头部特征数字，是否确认解密，密钥大小
		void set_information_data(QString key, QString head_digit, bool have_head_digit, int key_size);//设置需要显示在界面上的信息，但不再传入指针，供之后使用。如果在之后使用指针传递，则会造成指针指向的地址改变，那么在确认后无法修改主窗口中相关属性的值

		//鼠标事件，用于窗口移动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		//键盘事件，用于修改回车键的默认退出功能
		void keyPressEvent(QKeyEvent *event);

		public slots:
		
			void set_apply();//设置生效
			void cancel_apply();//设置取消
			void import_set();//导入设置
			void close_window_include_animation();//包含关闭窗口动画的关闭窗口方法
	};
}

#endif