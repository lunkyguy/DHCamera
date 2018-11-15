//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_RECURSIVE_MUTEX_H__
#define __INFRA3_RECURSIVE_MUTEX_H__

#include "Defs.h"


namespace Dahua {
namespace Infra {

struct RecursiveMutexInternal;

/// \class CRecursiveMutex �ݹ���
class INFRA_API CRecursiveMutex
{
	CRecursiveMutex(CRecursiveMutex const&);
	CRecursiveMutex& operator=(CRecursiveMutex const&);

public:
	/// ���캯�����ᴴ��ϵͳ������
	CRecursiveMutex();

	/// ����������������ϵͳ������
	~CRecursiveMutex();

	/// �����ٽ�����
	/// \return �����Ƿ�ɹ�
	bool enter();

	/// �뿪�ٽ�����
	/// \return �����Ƿ�ɹ�
	bool leave();

private:
	RecursiveMutexInternal *m_internal;
};

} // namespace Infra
} // namespace Dahua

#endif //__INFRA_RECURSIVE_MUTEX_H__

//
// End of "$Id$"
//
