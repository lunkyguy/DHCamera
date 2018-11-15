//
//  "$Id: ComPtr.h 23677 2011-04-18 07:37:15Z wang_haifeng $"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:	�������ָ����
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA_OBJECT_SMART_PTR_H__
#define __INFRA_OBJECT_SMART_PTR_H__


#include <stddef.h>
#include "Infra/Assert.h"
#include "Defs.h"
#include "Detail/smartptr_detail.h"

namespace Dahua {
namespace Memory {


/// ��������ü���������ָ����ģ��
template<class T>
class TSmartObjectPtr
{
#if defined(_MSC_VER) && (_MSC_VER < 1300)
public:
#else
	template<class Y> friend class TSmartObjectPtr;
#endif

	T* m_ptr;

	typedef TSmartObjectPtr<T> this_type;

	class null_type;

public:
	typedef T	element_type;
	typedef T	value_type;
	typedef T*	pointer;


	/// �չ��캯��; ʵ�ִ� NULL �� TSmartObjectPtr ����ʽת��
	/// \param [in] ptr ���ҽ���ptrΪNULLʱ, �ù��캯���Żᱻ����
	TSmartObjectPtr(null_type* ptr = NULL)
		: m_ptr(NULL)
	{
	}

	/// ���캯��; �ǿ�ָ�빹�캯��
	template<class Y> explicit TSmartObjectPtr(Y* ptr)
		: m_ptr(ptr)
	{
	}

	template<class Y> TSmartObjectPtr(TSmartObjectPtr<Y> const& rhs)
		: m_ptr(rhs.m_ptr)
	{
		addObjectRef(m_ptr);
	}

	TSmartObjectPtr(TSmartObjectPtr const& rhs)
		: m_ptr(rhs.m_ptr)
	{
		addObjectRef(m_ptr);
	}

	template<class Y> TSmartObjectPtr(TSmartObjectPtr<Y> const& rhs, Detail::static_cast_tag)
		: m_ptr(static_cast<T*>(rhs.m_ptr))
	{
		addObjectRef(m_ptr);
	}

	template<class Y> TSmartObjectPtr(TSmartObjectPtr<Y> const& rhs, Detail::const_cast_tag)
		: m_ptr(const_cast<T*>(rhs.m_ptr))
	{
		addObjectRef(m_ptr);
	}

	template<class Y> TSmartObjectPtr(TSmartObjectPtr<Y> const& rhs, Detail::dynamic_cast_tag)
		: m_ptr(dynamic_cast<T*>(rhs.m_ptr))
	{
		addObjectRef(m_ptr);
	}

	~TSmartObjectPtr()
	{
		releaseObject(m_ptr);
	}

	void swap(TSmartObjectPtr& rhs)
	{
		if (&rhs != this)
		{
			element_type* p = rhs.m_ptr;
			rhs.m_ptr = m_ptr;
			m_ptr = p;
		}
	}

	void reset()
	{
		this_type().swap(*this);
	}

	template<class Y> void reset(Y* ptr)
	{
		this_type(ptr).swap(*this);
	}

	template<class Y> void reset(TSmartObjectPtr<Y> const& rhs)
	{
		this_type(rhs).swap(*this);
	}

	TSmartObjectPtr& operator=(TSmartObjectPtr const& rhs)
	{
		if (&rhs != this) this_type(rhs).swap(*this);
		return *this;
	}

	element_type* operator->() const
	{
		DAHUA_ASSERT(m_ptr != NULL);
		return m_ptr;
	}

	element_type& operator*() const
	{
		DAHUA_ASSERT(m_ptr != NULL);
		return *m_ptr;
	}

	element_type* get() const
	{
		return m_ptr;
	}

	// implicit conversion to "bool"

	typedef T* this_type::*unspecified_bool_type;

	operator unspecified_bool_type() const // never throws
	{
		return m_ptr == NULL ? 0 : &this_type::m_ptr;
	}

	bool operator!() const // never throws
	{
		return m_ptr == NULL;
	}

};	// TSmartObjectPtr

} // namespace Memory

// �Ƚ�

template<class T, class U> inline bool operator==(Memory::TSmartObjectPtr<T> const& a, Memory::TSmartObjectPtr<U> const& b)
{
	return a.get() == b.get();
}

template<class T, class U> inline bool operator!=(Memory::TSmartObjectPtr<T> const& a, Memory::TSmartObjectPtr<U> const& b)
{
	return a.get() != b.get();
}

template<class T, class U> inline bool operator<(Memory::TSmartObjectPtr<T> const& a, Memory::TSmartObjectPtr<U> const& b)
{
	return a.get() < b.get();
}

template<class T, class U> inline bool operator<=(Memory::TSmartObjectPtr<T> const& a, Memory::TSmartObjectPtr<U> const& b)
{
	return a.get() <= b.get();
}

template<class T, class U> inline bool operator>(Memory::TSmartObjectPtr<T> const& a, Memory::TSmartObjectPtr<U> const& b)
{
	return a.get() > b.get();
}

template<class T, class U> inline bool operator>=(Memory::TSmartObjectPtr<T> const& a, Memory::TSmartObjectPtr<U> const& b)
{
	return a.get() >= b.get();
}

// ����

template<class T> inline void swap(Memory::TSmartObjectPtr<T>& a, Memory::TSmartObjectPtr<T>& b)
{
	a.swap(b);
}

// ת��

template<class T, class U> Memory::TSmartObjectPtr<T> inline static_pointer_cast(Memory::TSmartObjectPtr<U> const& r)
{
	return Memory::TSmartObjectPtr<T>(r, Memory::Detail::static_cast_tag());
}

template<class T, class U> Memory::TSmartObjectPtr<T> inline const_pointer_cast(Memory::TSmartObjectPtr<U> const& r)
{
	return Memory::TSmartObjectPtr<T>(r, Memory::Detail::const_cast_tag());
}

template<class T, class U> Memory::TSmartObjectPtr<T> inline dynamic_pointer_cast(Memory::TSmartObjectPtr<U> const& r)
{
	return Memory::TSmartObjectPtr<T>(r, Memory::Detail::dynamic_cast_tag());
}

// get_pointer(p) is a generic way to say p.get()

template<class T> inline T * get_pointer(Memory::TSmartObjectPtr<T> const & p)
{
	return p.get();
}

} // namespace Dahua

#endif // __INFRA_OBJECT_SMART_PTR_H__

