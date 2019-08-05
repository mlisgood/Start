#include "ExportClassLockSimple.h"
#include "DllLockSimple.h"

namespace rem
{
	Export_LockSimple_virtual_class* export_class_lock_simple(void)
	{
		return (Export_LockSimple_virtual_class*) new LockOpposite();//通过导出函数的形式导出指向派生类对象的基类指针，从而实现导出实际需要使用的类
	}
}