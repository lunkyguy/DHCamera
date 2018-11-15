//
//  "$Id$"
//
//  Copyright (c)1992-2050, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __MEMORY_ATOMIC_REF_COUNTER__
#define __MEMORY_ATOMIC_REF_COUNTER__


#include <Infra/Defs.h>


namespace Dahua {
namespace Memory {


/// ����ǿ�����õļ�������, ����ʵ��ǿ����������ָ��
class CRefCount
{
	/// ��ֹ���ƹ����븳ֵ����
	CRefCount(CRefCount const&);
	CRefCount& operator=(CRefCount const&);

public:
	/// ���캯��, ����ֵ����ʼΪ1
	CRefCount();

	/// ��������
	~CRefCount();

	/// ǿ���ü���ֵ��1, ��Ӱ�������ü���ֵ
	/// \retval ���ز�����ļ���ֵ
	int32_t incStrong();

	/// ǿ���ü���ֵ��1, ��Ӱ�������ü���ֵ
	/// \retval ���ز�����ļ���ֵ
	int32_t decStrong();

	/// ����ǿ���ü�����Ϊ0ʱ��1
	/// \retval ���ز�����ļ���ֵ
	int32_t tryIncStrong();

	/// ȡ��ǰǿ���ü���ֵ
	int32_t getStrong();

	/// �����ü���ֵ��1, ��Ӱ��ǿ���ü���ֵ
	/// \retval ���ز�����ļ���ֵ
	int32_t incWeak();

	/// �����ü���ֵ��1, ��Ӱ��ǿ���ü���ֵ
	/// \retval ���ز�����ļ���ֵ
	int32_t decWeak();

	/// ȡ��ǰ�����ü���ֵ
	/// \retval ���ز�����ļ���ֵ
	int32_t getWeak();

private:
	int32_t m_internal[8];	///< �ڲ���Ա, 32�ֽ�
};


} // namespace Memory
} // namespace Dahua

#endif // __MEMORY_ATOMIC_REF_COUNTER__


