
#ifndef __DAHUA_BLOCK_H__
#define __DAHUA_BLOCK_H__

#include "SharedPtr.h"
#include "Infra/Function.h"
#include <Infra/Defs.h>

namespace Dahua {
namespace Memory {

/// �ͷ��ڴ�ص�����
/// \param[in] data     ��Ҫ�ͷŵ��ڴ�
typedef Infra::TFunction1<void, uint8_t*> FreeFunc; 

/// �����������ݺ���
/// \param[in] data     ���������ڴ�ָ�� ����ɾ�����ڴ�
typedef Infra::TFunction1<void, uint8_t*> UnInitExDataFunc;

/// ���ݹ�����
/// ���಻���������ڴ� ���е��ڴ�����ⲿ���ɣ������������
/// �ⲿ���������ͷŸ��ڴ�
class INFRA_API CBlock
{
public:
	
	/// ���캯��
	CBlock();
	
	/// ���ƹ��캯��
	CBlock(CBlock const& other);

	///  ��ֵ����
	CBlock& operator=(CBlock const& other);
	
	/// �������Ĺ��캯��
	/// \param[in] data      ����ָ�� ���ڴ���CBlock���йܣ��ⲿ�������ͷ�
	/// \param[in] size      ���ݴ�С
	/// \param[in] extraSize �������ݴ�С
	/// \param[in] freeCB    �ڴ��ͷź��� ��Ϊ�����ͷ�
	CBlock(uint8_t* data, uint32_t size, uint32_t extraSize = 0, FreeFunc freeCB = FreeFunc(), UnInitExDataFunc unInitCB = UnInitExDataFunc());
	
	/// ��������
	virtual ~CBlock(void);
	
	/// ��ȡ��������ָ��
	uint8_t* extraData() const;
	
	/// ��ȡ�������ݳ���
	uint32_t extraSize() const;
	
	/// ��ȡ����ָ��
	uint8_t* data() const;
	
	/// ��ȡ���ݴ�С
	uint32_t size() const;
	
	/// ��Ч���ж�
	bool valid() const;
	
	/// ��¡���� ��ȿ�������
	CBlock clone() const;
	
	/// ���ö���
	void reset();
	
	/// ���ö���
	/// \param[in] r ���ƶ���
	void reset(CBlock const& r);
	
private:
	
	struct Impl;
	Impl*  m_impl;
};

} // end of Memory
} // end of Dahua

#endif /// __DAHUA_BLOCK_H__
