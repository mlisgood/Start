#include "ExportClassLockSimple.h"
#include "DllLockSimple.h"

namespace rem
{
	Export_LockSimple_virtual_class* export_class_lock_simple(void)
	{
		return (Export_LockSimple_virtual_class*) new LockOpposite();//ͨ��������������ʽ����ָ�����������Ļ���ָ�룬�Ӷ�ʵ�ֵ���ʵ����Ҫʹ�õ���
	}
}