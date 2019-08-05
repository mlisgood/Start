#include "ExportClassLockNormal.h"
#include "DllLockNormal.h"

namespace rem
{
	Export_LockSingle_virtual_class* export_class_lock_single(void)
	{
		return (Export_LockSingle_virtual_class*) new LockSingle();//通过导出函数的形式导出指向派生类对象的基类指针，从而实现导出实际需要使用的类
	}

	Export_LockDouble_virtual_class* export_class_lock_double(void)
	{
		return (Export_LockDouble_virtual_class*) new LockDouble();//通过导出函数的形式导出指向派生类对象的基类指针，从而实现导出实际需要使用的类
	}

	Export_HashCalculate_virtual_class* export_class_hash_calculate(void)
	{
		return (Export_HashCalculate_virtual_class*) new HashCalculate();//通过导出函数的形式导出指向派生类对象的基类指针，从而实现导出实际需要使用的类
	}
}