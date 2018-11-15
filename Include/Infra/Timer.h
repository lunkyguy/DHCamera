//
//  "$Id: Timer.h 130874 2013-08-09 00:50:14Z qin_fenglin $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef _INFRA3_TIMER_H_
#define _INFRA3_TIMER_H_

#include "Defs.h"
#include "Function.h"

namespace Dahua{
namespace Infra{

struct TimerInternal;

/// \class CTimer
/// \brief ��ƽ̨��ʱ����֧����ʱ�����ڡ��첽�ȶ��ֹ���ִ�з�ʽ
///
/// ÿ�ε��ö��Ǵ��̳߳���ȡһ���߳�ִ�У����Զ���Ķ�ʱ����ִ�в�����ֱ��Ӱ�죬
/// ����ͬһ����ʱ�����ϴε��û�û��ִ����ϣ����´ε��û�ʧ�ܡ�
/// \see CTimerManager
class INFRA_API CTimer
{
	CTimer(CTimer const&);
	CTimer& operator=(CTimer const&);

public:
	typedef TFunction1<void, unsigned long> Proc;

	/// ���캯��
	/// \param name ��ʱ������
	CTimer(const char * name);

	/// ��������
	virtual ~CTimer();

	/// ������ʱ��
	/// \param fun ��ʱ���ص�����
	/// \param delay ָ����������ʱ����ʱ����ã���λΪ���룬���Ϊ0��ʾ������ʼ����
	/// \param period ��ʱ�������ڣ�ָ�����ϴε��ö���ʱ����ٴε��ã���λΪ���룬
	///		   ���Ϊ0��ʾ�Ƿ����ڶ�ʱ������һ�ε�����Ϻ���Զ�ֹͣ��
	/// \param param �ص������������ڻص��������ǻᴫ���ص�������
	/// \param timeout �ص�����ִ�еĳ�ʱʱ�䣬���ʱ��ᱻ���ø��ص�ʱ�Ķ�ʱ���߳�,
	///        ����Ϊ��λ��0��ʾ������ʱ��Ĭ��ֵΪ1���ӡ�
	/// \return �ڷ���ʱ�Ķ�ʱ�����ϴε��û�û����ɵ�����·���false�������������true
	/// \note ����ʱ���������ڲ���������Ϊ0������ʵ���첽���á�
	bool start(Proc fun, uint32_t delay, uint32_t period, unsigned long param = 0, uint32_t timeout = 60000);

	/// �رն�ʱ��
	/// \param callNow ��ʱ��ֹͣʱͬʱ�ٵ���һ�»ص�������ֻ�Դ���ʱ�ķ����ڶ�ʱ����Ч��
	/// \return ��ʱ��û�п���������µ���ֹͣ�᷵��false
	bool stop(bool callNow = false);

	/// �õ���ʱ������
	const char* getName();

	/// ���ö�ʱ������
	/// \name �µĶ�ʱ������
	void setName(const char* name);

	/// �ж϶�ʱ���Ƿ���
	/// \note �����ڶ�ʱ���ڵ��ù�����Զ���״̬�ر�
	bool isStarted();

	/// �жϷ����ڶ�ʱ���Ƿ��Ѿ����ù�
	bool isCalled();

	/// �жϻص������Ƿ�����ִ��
	bool isRunning();

	/// �رն�ʱ�����ȴ���ֱ���ص����������ŷ��ء�
	/// \note һ�����û���������ʱ����ã�����Ҫ�ر�С�ģ���ֹ������
	bool stopAndWait();

	///\brief �������ö�ʱ��ִ������
	///\param [in] pertime ��Ҫ�������õ�ִ������
	void setPeriodTime(unsigned int pertime);

	///\brief ����ͳ��
	void enableStat(bool bStat=true);
private:
	TimerInternal* m_internal;
};


////////////////////////////////////////////////////////////////////////////////

struct TimerManagerInternal;

/// \class CTimerManager
/// \brief ��ʱ�������࣬ʹ�ø߾���ϵͳ��ʱ��������Ӧ�ö�ʱ������
///
/// �߾��ȶ�ʱ��ÿ�α�����ʱ���������Ӧ�ö�ʱ����״̬�������Ƿ������ص�������
/// �����ʱ��������Ҳ������Ӧ�ö�ʱ���ľ��ȡ�
/// - Win32ʹ�ö�ý�嶨ʱ��������Ϊ1ms
/// - pSOSʹ��tmdlTimer���������Ϊ1ms
/// - ucLinux2.4 ʹ��ϵͳ�źţ�����Ϊ10ms
/// \see CTimer
class INFRA_API CTimerManager
{
	CTimerManager();
	CTimerManager(CTimerManager const&);
	CTimerManager& operator=(CTimerManager const&);

public:
	/// ������ʱ���������
	static CTimerManager* instance();

	/// ��������
	~CTimerManager();

	/// ��ӡ�����߳���Ϣ
	void dumpTimers();

	/// �����̳߳ؿ����߳���
	bool limitIdlePooled(int count);

private:
	TimerManagerInternal* m_internal;
};

} // namespace Infra
} // namespace Dahua

#endif
