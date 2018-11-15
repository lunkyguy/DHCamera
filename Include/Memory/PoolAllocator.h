//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	�ο�"The C++ Programming Laguage (Special Edition)", by Bjarne Stroustrup��
//  ʵ�ֵ��ڴ�ģʽ�ڴ������

//	Revisions:
//  2007-8-9  wang_haifeng  Modification
//

#ifndef __INFRA_POOL_ALLOCATOR_H__
#define __INFRA_POOL_ALLOCATOR_H__

#include <cassert>
#include <new>
#include "Infra/Mutex.h"
#include "Detail/singleton_pool.h"
#include "Detail/MemPool.h"

// �ж�STL�Ƿ���ȷʵ���� deallocate
#if defined(_RWSTD_VER) || defined(__SGI_STL_PORT) || defined(__BORLANDC__)
 #define DAHUA_NO_PROPER_STL_DEALLOCATE
#endif



namespace Dahua {
namespace Memory {


////////////////////////////////////////////////////////////////////////////////

namespace Pool {

struct DefaultMutex
{
	Infra::CMutex m_mutex;
	void lock() {m_mutex.enter();}
	void unlock() {m_mutex.leave();}
};

struct NullMutex
{
	void lock() {}
	void unlock() {}
};

struct PoolAllocatorTag {};

} // namespace Pool

////////////////////////////////////////////////////////////////////////////////


/// \brief ����std:: alloctor������ڴ�ģʽ�ڴ������
///
/// - ֻ֧��list����, ��Ϊlist����ÿ��ֻ������ͷ�һ��һ�ֹ��Ľڵ�. ����deque,
/// ��Ԫ�ع��С��4Kʱ, ��Ĭ�ϵ�������Ծ��൱���ڴ��, ���ڵ���4Kʱ, ��������
/// �����͵Ĺ��, һ����Ԫ��ָ��, һ������ĸ������ò��÷�������, ��һ����Ԫ��,
/// ��ʱ�ſ��Կ����ڴ��.  ��vectorʹ�óع���ʵ��ûʲô����, ���ڴ�������Ҳ
/// �Ѿ������˶�̬���������, �����Ҫ���ڴ��ʵ��, ���������ش���.
template <typename T,
	typename PoolType = Detail::CMemPool,	// ָ���ڴ������
	typename Mutex = Pool::NullMutex,		// ָ��������, Detial::CMemPool �ڲ��Ѿ������������� NullMutex
	unsigned nextSize = 64,					// ÿ�η����������
	unsigned maxSize = 0>
class TPoolAllocator;


/// \brief TPoolAllocator��ƫ�ػ��汾
template<
	typename PoolType,
	typename Mutex,
	unsigned nextSize,
	unsigned maxSize>
class TPoolAllocator<void, PoolType, Mutex, nextSize, maxSize>
{
public:
	typedef void*       pointer;
	typedef const void* const_pointer;
	typedef void        value_type;
	template <class U> struct rebind {
		typedef TPoolAllocator<U, PoolType, Mutex, nextSize, maxSize> other;
	};
};


/// \brief ����std:: alloctor������ڴ�ģʽ�ڴ������
/// �����ڴ�ʹ��CMemPool���������Ǿ�̬���������Գ����������������뵽��ϵͳ�ڴ�һֱ�����ͷ�
template <typename T,
	typename PoolType,
	typename Mutex,
	unsigned nextSize,
	unsigned maxSize>
class TPoolAllocator
{
public:
	typedef Mutex mutex_type;
	typedef PoolType pool_type;
	static const unsigned next_size = nextSize;

	typedef T value_type;
	typedef T * pointer;
	typedef const T * const_pointer;
	typedef T & reference;
	typedef const T & const_reference;
	typedef size_t size_type;
	typedef std::ptrdiff_t difference_type;

	template <typename U>
	struct rebind
	{
		typedef TPoolAllocator<U, PoolType, Mutex, nextSize, maxSize> other;
	};

	TPoolAllocator()
	{}

	template <class U>
	TPoolAllocator(TPoolAllocator<U, PoolType, Mutex, nextSize, maxSize> const&)
	{}

	~TPoolAllocator()
	{}

	pointer address(reference x) const
	{ return &x; }

	const_pointer address(const_reference x) const
	{ return x; }

	bool operator==(const TPoolAllocator &) const
	{ return true; }

	bool operator!=(const TPoolAllocator &) const
	{ return false; }

	static pointer allocate(const size_type n)
	{
		typedef Detail::singleton_pool<Pool::PoolAllocatorTag, sizeof(T), PoolType, Mutex, nextSize, maxSize> SingletonPool;
		assert(n == 1);
		const pointer ret = static_cast<pointer>(SingletonPool::malloc());
		if (ret == 0)
		{
			throw std::bad_alloc();
		}
		return ret;
	}

	static pointer allocate(const size_type n, const void * const)
	{ return allocate(n); }

	static void deallocate(const pointer ptr, const size_type n)
	{
		typedef Detail::singleton_pool<Pool::PoolAllocatorTag, sizeof(T), PoolType, Mutex, nextSize, maxSize> SingletonPool;
#ifdef DAHUA_NO_PROPER_STL_DEALLOCATE
		if (ptr == 0 || n == 0) return;
#endif
		assert(n == 1);
		SingletonPool::free(ptr);
	}

	size_type max_size() const
	{
		return static_cast<size_type>(-1) / sizeof(T);
	}

	void construct(pointer ptr, const value_type& x)
	{
		new(ptr) T(x);
	}

	void destroy(pointer ptr)
	{
		ptr->~T();
		(void) ptr; // avoid unused variable warning
	}
};

} // namespace Memory
} // namespace Dahua

#endif // __INFRA_POOL_ALLOCATOR_H__

