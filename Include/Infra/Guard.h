//
//  "$Id: Guard.h 55347 2012-03-22 11:26:45Z qin_fenglin $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_GUARD_H__
#define __INFRA3_GUARD_H__

#include "Mutex.h"
#include "RecursiveMutex.h"
#include "ReadWriteMutex.h"

namespace Dahua{
namespace Infra{


/// \class CGuard
/// \brief �ػ����ࡣ
///
/// ����ʱ�Զ�����CMutex::Enter������ʱ�Զ�����CMutex::Leave�����ⲻ
/// ��Ե����������ʾ�����£�
/// \code
/// CMutex mutex;
/// int needProtect = 0;
/// void testAdd()
/// {
/// there:
/// 	if(needProtect % 2) // not protected
/// 	{
/// 		needProtect++;
/// 	}
/// 	else
/// 	{
/// 		return;
/// 	}
///
/// 	CGuard guard(mutex);
/// 	needProtect++;
/// 	goto there;	// will also bring ~CGuard(), thus mutex.leave()
/// }
/// void testSub()
/// {
///     needProtect--; // not protected
///
/// 	CGuard guard(mutex);
/// 	needProtect--;
/// }
/// \endcode

class CGuard
{
	CGuard(CGuard const&);
	CGuard& operator=(CGuard const&);

public:
	/// ���캯�����Զ�����CMutex::enter
	/// \param mutex ���������ã�CGuard����������������
	inline CGuard(CMutex& mutex)
		:m_mutex(mutex)
	{
		m_mutex.enter();
	};

	/// �����������Զ�����CMutex::leave
	inline ~CGuard()
	{
		m_mutex.leave();
	};

private:
	CMutex &m_mutex;	///< ��Ҫ�Զ����õĻ���������
};

////////////////////////////////////////////////////////////////////////////////

class CRecursiveGuard
{
	CRecursiveGuard(CRecursiveGuard const&);
	CRecursiveGuard& operator=(CRecursiveGuard const&);

public:
	/// ���캯�����Զ�����CMutex::enter
	/// \param mutex ���������ã�CGuard����������������
	inline CRecursiveGuard(CRecursiveMutex& mutex)
		:m_mutex(mutex)
	{
		m_mutex.enter();
	};

	/// �����������Զ�����CMutex::leave
	inline ~CRecursiveGuard()
	{
		m_mutex.leave();
	};

private:
	CRecursiveMutex &m_mutex;	///< ��Ҫ�Զ����õĻ���������
};

////////////////////////////////////////////////////////////////////////////////

/// ��д���Ķ���������
class CGuardReading
{
	CGuardReading(CGuardReading const&);
	CGuardReading& operator=(CGuardReading const&);

public:
	/// ���캯�����Զ����� CRwMutex::EnterReading
	/// \param mutex ���������ã�CGuard����������������
	inline CGuardReading(CReadWriteMutex& mutex)
		: m_mutex(mutex)
	{
		m_mutex.enterReading();
	};

	/// �����������Զ����� CReadWriteMutex::leave
	inline ~CGuardReading()
	{
		m_mutex.leave();
	};

private:
	CReadWriteMutex& m_mutex;	///< ��Ҫ�Զ����õĻ���������
};

////////////////////////////////////////////////////////////////////////////////

///  ��д����д��������
class CGuardWriting
{
	CGuardWriting(CGuardWriting const&);
	CGuardWriting& operator=(CGuardWriting const&);

public:
	/// ���캯�����Զ����� CReadWriteMutex::EnterWriting
	/// \param mutex ���������ã�CGuard����������������
	inline CGuardWriting(CReadWriteMutex& mutex)
		: m_mutex(mutex)
	{
		m_mutex.enterWriting();
	};

	/// �����������Զ����� CReadWriteMutex::leave
	inline ~CGuardWriting()
	{
		m_mutex.leave();
	};

private:
	CReadWriteMutex& m_mutex;	///< ��Ҫ�Զ����õĻ���������
};

} // namespace Infra
} // namespace Dahua

#endif //__INFRA_GUARD_H__
