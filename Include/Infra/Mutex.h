//
//  "$Id: Mutex.h 120119 2013-06-04 11:12:32Z sun_xiaohui $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_MUTEX_H__
#define __INFRA3_MUTEX_H__

#include "Defs.h"
//lint -save -e1509

namespace Dahua{
namespace Infra{

struct MutexInternal;

/// \class CMutex
class INFRA_API CMutex
{
	CMutex(CMutex const&);
	CMutex& operator=(CMutex const&);

public:
	/// ���캯�����ᴴ��ϵͳ������
	CMutex();

	/// ����������������ϵͳ������
	~CMutex();

	/// �����ٽ�����
	/// \return �����Ƿ�ɹ�
	bool enter();
	
	/// ���Խ����ٽ������Ѿ���ռ��ֱ�ӷ��أ����ȴ���
    /// \return�����ٽ����Ƿ�ɹ�
    bool tryEnter();

	/// �뿪�ٽ�����
	/// \return �����Ƿ�ɹ�
	bool leave();

private:
	MutexInternal *m_internal;
};

} // namespace Infra
} // namespace Dahua
#endif //__INFRA_MUTEX_H__

//
// End of "$Id: Mutex.h 120119 2013-06-04 11:12:32Z sun_xiaohui $"
//
