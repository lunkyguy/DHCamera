
#ifndef __DAHUA_INFRA_ALLOCATOR_H__
#define __DAHUA_INFRA_ALLOCATOR_H__

#include <stddef.h> /// for size_t
#include "Defs.h"

namespace Dahua {
namespace Infra {

/// �ڴ������ �����Զ���STL����
class INFRA_API CAllocator
{
public:
	
	/// \brief �����ڴ�
	/// \param[in] size �ڴ��С
	/// \retval �ڴ�ָ��
	static void* allocate(size_t size);
	
	/// \brief ���������ڴ�
	/// \param[in] mem      ԭ�ڴ�ָ��
	/// \param[in] old_size ԭ�ڴ��С
	/// \param[in] new_size ���ڴ��С
	/// \retval �ڴ�ָ��
	static void* reallocate(void* mem, size_t old_size, size_t new_size);
	
	/// \brief �ͷ��ڴ�
	/// \param[in] mem      ԭ�ڴ�ָ��
	/// \param[in] size     �ڴ��С
	static void dealocate(void* mem, size_t size);
};

} // end of Infra
} // end of Dahua

#endif // end of __DAHUA_INFRA_ALLOCATOR_H__
