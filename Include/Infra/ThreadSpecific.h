//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef DAHUA3_THREAD_SPECIFIC_H__
#define DAHUA3_THREAD_SPECIFIC_H__

#include "Defs.h"


namespace Dahua {
namespace Infra {


struct ThreadSpecificInternal;

/// �߳�ר�д洢(�ֳ��̱߳��ش洢); TSS(Thread-Specific Storage), TLS(Thread Local Storage)
class INFRA_API CThreadSpecific
{
public:
	/// ���캯��; ���� TSS ����
	CThreadSpecific();

	/// ��������; �ͷ� TSS ����
	~CThreadSpecific();

	/// TSS �����Ƿ����
	bool valid();

	/// ���ô洢ֵ
	bool setValue(void const* value);

	/// ȡ�ô洢ֵ
	bool getValue(void** pvalue);

private:
	ThreadSpecificInternal* m_internal;
};


} // namespace Infra
} // namespace Dahua

#endif // DAHUA_THREAD_SPECIFIC_H__
