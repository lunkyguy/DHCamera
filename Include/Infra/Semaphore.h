//
//  "$Id: Semaphore.h 121830 2013-06-15 01:38:33Z sun_xiaohui $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_SEMAPHORE_H__
#define __INFRA3_SEMAPHORE_H__

#include "Defs.h"

namespace Dahua{
namespace Infra{

struct SemaphoreInternal;

/// \class CSemaphore
/// \brief ��ƽ̨�ź�����
class INFRA_API CSemaphore
{
	CSemaphore(CSemaphore const&);
	CSemaphore& operator=(CSemaphore const&);

public:
	/// ���캯�����ᴴ��ϵͳ�ź���
	/// \param initialCount �ź�����ʼ����
	explicit CSemaphore(int initialCount = 0);

	/// ����������������ϵͳ������
	~CSemaphore();

	/// �����ź�������������Ѿ����ٵ�0�����������õ��߳�
	/// \return ��ǰ�ź�������
	int pend();

	/// �����ź�������������Ǵ�0�ۼӣ��ỽ����ȴ����еĵ�һ���߳�
	/// \return ��ǰ�ź�������
	int post();
	
	/// �����ź�������������Ѿ����ٵ�0�����������õ��߳�, ֱ����ʱ
	/// \param timeout ��ʱʱ�䣬��λ������(ms)
	/// \return ��ǰ�ź�������, ����-1��ʾ��ʱ
	int pend(uint32_t timeout);

	/// ���Լ����ź���������ź����Ѿ�Ϊ0�������Ϸ���
	/// \return 0 ��ʾ�ź������ٳɹ���-1��ʾ�ź�������ʧ��
	/// ͨ��getLastError()�鿴�����
	int tryPend();

private:
	SemaphoreInternal* m_internal;
};

} // namespace Infra
} // namespace Dahua

#endif //__INFRA_SEMAPHORE_H__
//
// End of "$Id: Semaphore.h 121830 2013-06-15 01:38:33Z sun_xiaohui $"
//
