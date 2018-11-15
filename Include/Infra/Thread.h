//
//  "$Id: Thread.h 107129 2013-03-20 10:29:35Z qin_fenglin $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef _INFRA3_THREAD_H_
#define _INFRA3_THREAD_H_

#include <string>
#include "Defs.h"
#include "String.h"
#include "Function.h"

namespace Dahua{
namespace Infra{

struct ThreadInternal;

/// \class CThread
/// \brief ��ƽ̨�߳���; �ṩ�̳з�ʽ�����߳�
/// \see CThreadManager
class INFRA_API CThread
{
	CThread(CThread const&);
	CThread& operator=(CThread const&);

public:
	enum Priority
	{
		priorTop = 1,
		priorBottom = 127,
		priorDefault = 64,
	};

	enum Policy
	{
		policyNormal = 0,		///< ��ͨ�߳�
		policyRealtime = 1		///< ʵʱ�߳�
	};

	/// ���캯������û�д���ϵͳ�߳�
	/// \param name �߳������ַ��������Ʋ�һ���ᴫ������ϵͳ����CThreadManager
	///		   �����߳�ʱ���õ���
	/// \param priority �߳����ȼ���ֵԽС��ʾ���ȼ�Խ�ߣ��ᱻת���ɶ�Ӧ����ϵͳ
	///        ƽ̨�����ȼ���ȡֵpriorTop��priorBottom��Ĭ��ֵpriorDefault��
	/// \param policy �̵߳��Ȳ���
	/// \param stackSize Ϊ�߳�ָ���Ķ�ջ��С���������0����С��ƽ̨Ҫ������ֵ��
	///        ��ʹ��ƽ̨ȱʡֵ��
	CThread(const char* name, int priority = priorDefault, int policy = policyNormal, int stackSize = 0);

	/// ��������������̻߳���ִ�У��������߳�
	virtual ~CThread();

	/// �߳�ִ���壬��һ���麯�����������߳��������ش˺�����ʵ�ָ��Ե���Ϊ��
	virtual void threadProc() = 0;

	/// �����߳�
	bool createThread();

	/// �����̣߳������˳���־���̵߳�ִ������Ҫ�ڸ��˳����ж������־��
	bool destroyThread();

	/// ��ֹ�̣߳��������̲߳�ͬ���������ɲ���ϵͳǿ�������̣߳�����֤�û����ݰ�ȫ��
	bool terminateThread();

	/// ȡ���̣߳������߳��˳���־����������ʽ�����ȴ��߳̽���
	bool cancelThread();

	/// �ж��߳��Ѿ�������������ִ��
	bool isThreadOver();

	/// �õ��߳�ID
	int	getThreadID();

	/// �����߳�����
	/// \param name �µ��߳�����
	void setThreadName(const char * name);

	/// �׽��ֹ���ӿڣ���pSOS����ϵͳ����ϵͳ�ӿڷ��ع���õ���һ�������׽���
	/// ������������ϵͳ��ֱ�ӷ��ش�����׽���
	/// \param socket ��Ҫ�����ԭʼ�׽���
	/// \return �����������׽���
	int shareSocket(int socket);

	/// ���ó�ʱʱ��
	/// \param milliSeconds ��ʱ������������Ϊ0��ʾ�������
	void setTimeout(int milliSeconds);

	/// ���ó�ʱʱ�䣬��Ҫ�����Ż��̳�����ʵ�֣������ظ���ȡ��ǰʱ��Ŀ���
	/// \param [in] milliSeconds ����ʱ��(�Ժ����)
	/// \param [in] now ��ǰʱ��(�Ժ����)
	void setTimeout(int milliSeconds, uint64_t now);

	/// �ж��Ƿ�ʱ��Ҳ�����жϴ����һ��SetTimeout����ε���IsTimeout��ʱ����
	/// �Ƿ��Ѿ��ڳ�ʱʱ��֮�⡣�������ӿ�Ŀ�����ṩ���û����Ӻ͵����̵߳ķ�����
	/// CThread�ಢ��������Ƿ�ʱ���߳�ִ�����κθ�Ԥ��CThreadManager��ӡ����
	/// �߳�״̬ʱ���������ӿڡ�
	bool isTimeout();

	/// �߳��˳���־, �߳�����������־�˳�
	bool looping() const;

	/// �õ������̵߳�ID��������ĳ���̶߳����ID����һ����̬������
	static int getCurrentThreadID();

	/// ���õ�ǰ�̳߳�ʱʱ��
	/// \param milliSeconds ��ʱ������������Ϊ0��ʾ�������
	static bool setCurrentTimeout(int milliSeconds);

	/// �õ����߳�����һ��ʱ��
	/// \param milliSeconds ���������ĺ�����
	static void sleep(int milliSeconds);

	/// ���ڵ����߳�CPU���أ�����ϳ����������ռ��CPU��Ӱ�������̣߳������й���ǰ��ʹ�á�
	/// \param ռ��CPU��ʱ�䣬ȡֵ1~100��1��ʾ�����ٶȣ�100��ʾ�����ٶȡ�
	/// \note linux�ڲ�ʹ���ź�ʵ�֣����Ҫ��֤������̲�Ӧ����select֮��ᱻ�źŻ��ѵĺ������á�
	static void load(int percent);


private:
	ThreadInternal* m_internal;
};

////////////////////////////////////////////////////////////////////////////////

struct ThreadLiteInternal;

/// \class CThreadLite
/// \brief ��ƽ̨�߳���; �ṩ��Ϸ�ʽ�����߳�
/// \see CThreadManager
class INFRA_API CThreadLite : public CThread
{
	CThreadLite(CThreadLite const&);
	CThreadLite& operator=(CThreadLite const&);

public:
	/// �߳�ִ����, ����Ϊ�̶߳��������
	typedef TFunction1<void, CThreadLite&> ThreadProc;

	/// ���캯������û�д���ϵͳ�߳�
	/// \param proc �߳��庯��
	/// \param name �߳������ַ��������Ʋ�һ���ᴫ������ϵͳ����CThreadManager
	///		   �����߳�ʱ���õ���
	/// \param priority �߳����ȼ���ֵԽС��ʾ���ȼ�Խ�ߣ��ᱻת���ɶ�Ӧ����ϵͳ
	///        ƽ̨�����ȼ���ȡֵpriorTop��priorBottom��Ĭ��ֵpriorDefault��
	/// \param policy �̵߳��Ȳ���
	/// \param stackSize Ϊ�߳�ָ���Ķ�ջ��С���������0����С��ƽ̨Ҫ������ֵ��
	///        ��ʹ��ƽ̨ȱʡֵ��
	CThreadLite(ThreadProc proc, const char* name, int priority = priorDefault, int policy = policyNormal, int stackSize = 0);

	/// ��������������̻߳���ִ�У��������߳�
	virtual ~CThreadLite();

private:
	/// �߳�ִ����
	virtual void threadProc();

	ThreadLiteInternal	*m_internal;
};

////////////////////////////////////////////////////////////////////////////////

struct ThreadManagerInternal;

/// \class IThreadManager
/// \brief �̹߳�����
/// \see CThread
class INFRA_API CThreadManager
{
	CThreadManager();
	CThreadManager(CThreadManager const&);
	CThreadManager& operator=(CThreadManager const&);

public:
	/// ����
	static CThreadManager* instance();

	/// ��������
	~CThreadManager();

	/// ע�����̣߳�ֻ�������߳��е��ã���������ʾ�����̵߳���Ϣ��Ҳ���Կ������߳���Ϣ
	void registerMainThread();

	/// ��ӡ�����߳���Ϣ
	void dumpThreads();

	/// ͨ���߳�id��ȡ�߳�����
	/// \param [in] id �߳�id
	/// \name [out] �߳�����
	/// \return true �ɹ�
	/// \return false ʧ��
	bool getThreadNameByID(int32_t id, CString& name);

	/// �õ���ʱ���߳�����
	bool getTimeOutThreads(CString2& names);

	///\brief �̶߳������Ƿ��Ѵ��ڴ��߳�
	///\param [in] id ��Ҫ�����߳�id
	///\return TRUE��ʾ���߳��ڶ����У������ʾ������
	bool hasThread(int id);

private:
	ThreadManagerInternal* m_internal;
};

} // namespace Infra
} // namespace Dahua

#endif //_INFRA_THREAD_H_

