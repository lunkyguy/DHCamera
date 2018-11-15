//
//  "$Id: MemPool.h 16503 2010-11-26 02:23:15Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA_MEM_POOL_H__
#define __INFRA_MEM_POOL_H__

#include "../Defs.h"

namespace Dahua {
namespace Memory {
namespace Detail {

struct MemPoolInternal;

/// \class CMemPool ���̰߳�ȫ���ڴ����; ���ṩ���ⲿʹ��, ���Բ�д�ӿ�˵��
class MEMORY_API CMemPool
{
	CMemPool(CMemPool const&);				// copy protection
	CMemPool& operator=(CMemPool const&);	// assign protection
public:
	CMemPool(unsigned int sz, unsigned int inc);
	~CMemPool();
	void* malloc();
	void free(void *b);
private:
	MemPoolInternal	*m_internal;
};

} // namespace Detail
} // namespace Memory
} // namespace Dahua

#endif // __INFRA_MEM_POOL_H__
