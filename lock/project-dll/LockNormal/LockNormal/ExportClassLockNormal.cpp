#include "ExportClassLockNormal.h"
#include "DllLockNormal.h"

namespace rem
{
	Export_LockSingle_virtual_class* export_class_lock_single(void)
	{
		return (Export_LockSingle_virtual_class*) new LockSingle();//ͨ��������������ʽ����ָ�����������Ļ���ָ�룬�Ӷ�ʵ�ֵ���ʵ����Ҫʹ�õ���
	}

	Export_LockDouble_virtual_class* export_class_lock_double(void)
	{
		return (Export_LockDouble_virtual_class*) new LockDouble();//ͨ��������������ʽ����ָ�����������Ļ���ָ�룬�Ӷ�ʵ�ֵ���ʵ����Ҫʹ�õ���
	}

	Export_HashCalculate_virtual_class* export_class_hash_calculate(void)
	{
		return (Export_HashCalculate_virtual_class*) new HashCalculate();//ͨ��������������ʽ����ָ�����������Ļ���ָ�룬�Ӷ�ʵ�ֵ���ʵ����Ҫʹ�õ���
	}
}