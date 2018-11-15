//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __DAHUA_MEMORY_BUFFER_H__
#define __DAHUA_MEMORY_BUFFER_H__

#include <stddef.h>		// for size_t
#include "Infra/Defs.h"
#include "Defs.h"

namespace Dahua {
namespace Memory {

/// �ɶ�̬���������ݻ�����
class MEMORY_API CBuffer
{
	/// ��ֹ���ƹ���͸�ֵ����
	CBuffer(CBuffer const&);
	CBuffer& operator=(CBuffer const&);

public:
	/// ���캯��
	CBuffer();

	/// ��������
	~CBuffer();

	/// ׷������, ���ԭ������������, ������ڴ����·����Լ��ڴ渴�Ʋ���
	/// \param buffer ׷�ӵ�����ָ��
	/// \param length ׷�ӵ����ݳ���
	/// \return ʵ��д�������
	size_t putBuffer(uint8_t* buffer, size_t length);

	/// ȡ���ݵ�ַ
	uint8_t* getBuffer() const;

	/// ȡ��Ч���ݳ���
	size_t size() const;

	/// ������Ч���ݳ���, ���ԭ������������, ������ڴ����·����Լ��ڴ渴�Ʋ���
	/// \param size �µ���Ч���ݳ���
	void resize(size_t size);

	/// ȡ��������
	size_t capacity() const;

	/// Ԥ���仺������, ���ԭ������������, ������ڴ����·����Լ��ڴ渴�Ʋ���
	/// \param capacity �µĻ�������
	void reserve(size_t capacity);

	/// �ͷŻ���,����Ϊ����ʱ�ĳ�ʼ״̬
	void reset();

	/// ����ÿ�ζ�̬�����Ĵ�С
	void setIncreasedSize(size_t increase);

private:
	struct BufferInternal;
	BufferInternal* m_internal;
};

} // namespace Memory
} // namespace Dahua

#endif	// __DAHUA_MEMORY_BUFFER_H__

