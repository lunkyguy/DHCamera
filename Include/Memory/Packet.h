//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __DAHUA_MEMORY_PACKET_H__
#define __DAHUA_MEMORY_PACKET_H__

#include <stddef.h>		// for size_t
#include "Infra/Defs.h"
#include "Infra/Function.h"
#include "Defs.h"

namespace Dahua {
namespace Memory {

////////////////////////////////////////////////////////////////////////////////

struct PacketInternal;

/// \�ͷ��Զ����ڴ�ĺ���ָ��
typedef Infra::TFunction2<void, void*, size_t> FreeMemFunc;

/// \class CPacket
/// \brief ���ݰ��������
class MEMORY_API CPacket
{
public:
  	/// ���캯��������һ����Ч�İ�����Ҫ��ֵ����ʹ�á��������ڸ���Ч����ֵ��
	/// ʹԭ���İ��������ü����ݼ���
	CPacket();

	/// ���캯��
	/// \param data  ����ָ��
	/// \param len 	  ���ݳ���
	/// \param func  �ͷź���(�ձ�ʾ���ͷ�)
	CPacket(void* data, size_t len, FreeMemFunc func = FreeMemFunc());

  	/// ���캯��������һ������ʹ�õİ�
	/// \param dataSize ����İ���������Ч���ݻ�����ֽ�����
	/// \param extraSize ��չ���ݻ����ֽ���
	explicit CPacket(size_t dataSize, size_t extraSize = 0);

	/// �������캯������ɰ��������ü�������
	CPacket(const CPacket& other);

	/// �Ӵ���й���С����С�����ô���еľֲ��ڴ棬�����������ȷ������һ����Ч��
	/// \param hugePacket �����õĴ��
	/// \param offset �����õ��ڴ��ڴ���е���ʼ�ֽ���
	/// \param size �����õ��ڴ��ֽ���
	CPacket(const CPacket& hugePacket, size_t offset, size_t size, size_t extraSize);

	/// ��ֵ��������أ���ɰ��������ü�������
	CPacket& operator=(const CPacket& other);

	/// ������������ɶ԰��������ü����ݼ�
	virtual ~CPacket();

	/// ���ð����ָ�Ϊ��Ч��
	void reset();

	/// �ж��Ƿ�Ϊ��Ч��
	bool valid() const;

	/// �ӵ�ǰ�������ָ��ƫ�ƴ�׷�����ݣ�ͬʱ�Զ�������Ч���ݳ��ȡ�����ô˺�����
	/// ������ݣ���һ�����ǰӦ�ý���Ч���ݳ�������Ϊ0��
	/// \param buffer ׷�ӵ�����ָ��
	/// \param length ׷�ӵ����ݳ���
	/// \return ʵ��д������ݣ����С��length����ʾ����������ʣ���������Ҫ���������д���
	size_t putBuffer(void* buffer, size_t length);

	/// �õ����������ʼλ�õ�ָ��
	uint8_t* getBuffer() const;

	/// �õ�������Ч���ݳ���, ��������չ���ݴ�С
	size_t size() const;

	/// ���ð�����Ч���ݳ��ȣ����������İ�����Ч�����ǰ�����ʱ�Ĵ�С��
	/// \param size �µĳ��ȣ����ᳬ������������
	/// \return ���ز����Ƿ�ɹ�
	bool resize(size_t size);

	/// �õ���ռ�ÿռ�Ĵ�С�����ڲ�ҳ����룬���ܱ�������Դ�
	size_t capacity() const;

	/// �õ���չ���ݻ����ַ
	void* getExtraData() const;

	/// �õ���չ���ݳ���
	size_t getExtraSize() const;

	///\ brief �������ݰ�
	explicit CPacket(uint32_t size, FreeMemFunc fun, void *arg, size_t extraSize = 0);
private:
	PacketInternal* m_internal;
};

////////////////////////////////////////////////////////////////////////////////

struct PacketManagerInternal;

/// \class CPacketManager
/// \brief ��������
/// \see CPacket
class MEMORY_API CPacketManager
{
	CPacketManager();
	CPacketManager(CPacketManager const&);
	CPacketManager& operator=(CPacketManager const&);

public:
	/// �ڴ���亯�����ͣ�����ΪҪ������ڴ��С������Ϊ������ڴ��ַ
	typedef Infra::TFunction1<void*, size_t> AllocProc;

	/// �ڴ��ͷź������ͣ������� malloc ��õ�ָ��
	typedef Infra::TFunction1<void, void*> FreeProc;

	/// �ڴ渴�ƺ������ͣ���һ������ΪĿ�ĵ�ַ���ڶ�������ΪԴ��ַ������������Ϊ�ֽ���
	typedef Infra::TFunction3<void*, void*, const void*, size_t> CopyProc;

	/// �ڴ�������
	enum Policy
	{
		policyDefault = 0,	///< ����ƽ̨�趨Ϊϵͳȱʡֵ, x86 ƽ̨Ϊ policySystem������ƽ̨Ϊ policyPool
		policySystem,		///< ÿ������ռ䶼����MemoryOperator.malloc���ͷŵ���MemoryOperator.free
		policyPool,			///< �ڴ��ģʽ��һ���Է���ô�οռ��ÿ������ʱ���������ڴ��
		policyPoolSystem,	///< �������ڴ�ʹ���ڴ�أ���չ���ݡ�PacketInternal ʹ��ϵͳ�ڴ棻��Ҫ���ڼ����������������
		policySharePool,	///< ����̹����ڴ��ģʽ

		policyCount
	};

	/// �ڴ��ģʽ�Ĳ���
	struct PoolParameter
	{
		size_t		totalSize;	///< �ڴ�����ֽ��������ڶ����ԭ��ʵ��������������һ�㡣ȱʡֵΪ8M Bytes
		size_t		chunkSize;	///< �ڴ�������ֽ�����������2^nK �ֽڣ�Ҳ���ܹ����뵽���ڴ�����С��λ��ȱʡֵΪ1K Bytes
		size_t		alignSize;	///< CPacket�������������������ֽ���������Ϊ2^n �ֽڡ�ȱʡֵΪ 4 Bytes
	};

	/// �Զ����ڴ��������
	struct MemoryOperator
	{
		AllocProc	malloc;		///< �ڴ����������ڴ�����뺯����ȱʡΪ ::malloc
		FreeProc	free;		///< �ڴ����������ڴ���ͷź�����ȱʡΪ ::free
		CopyProc	memcpy;		///< �ڴ����������ڴ�֮��ĸ��ƺ�����ȱʡ ::memcpy
	};

	/// ���ð����������ԣ���Ҫ�ڵ�������֮ǰ���ã�����ʹ��ȱʡ�����á�
	/// \param policy [in] �ڴ�������
	/// \param memop [in] �Զ����ڴ����������ΪNULLʱʹ��ȱ�ٺ���
	/// \param param [in] �ڴ�ز��Ե����ò�����ΪNULLʱʹ��ȱʡ����
	static void config(Policy policy = policyDefault, MemoryOperator* memop = NULL, PoolParameter* param = NULL);

	/// ��ȡ�ڴ�ط�����ܵ��ڴ�ռ����ʼ��ַ
	uint8_t*  getPoolBuffer();

	/// �������������
	static CPacketManager* instance();

	/// ����������
	~CPacketManager();

	/// �ӹ�����ڴ��������ڴ��
	void* malloc(size_t size);

	/// �ͷ��ڴ��
	void free(void*);

	/// �ڴ渴�ƣ����Դ��Ŀ�궼�ڹ�����ڴ淶Χ�ڣ�ʹ������ʱָ�����ڴ渴�ƺ���
	void* memcpy(void* dest, const void* src, size_t size);

	/// �õ�������ڴ����ֽ��������ֵ����ȱʡֵ����config���ú��ֵ��
	size_t getBufferSize();

	/// �õ�������ڴ�ʣ���ֽ������ǰ�2^nҳ��������ͳ�Ƶģ����ܻ���û�����GetPacket
	/// ʱ�����bytesֵ�ۼӵĽ��Ҫ��
	size_t getFreeSize();

	/// ��ӡ�ڴ�ڵ��״̬�������ڵ���
	void dumpNodes();

private:
	PacketManagerInternal* m_internal;
};

} // namespace Memory
} // namespace Dahua

#endif	// __DAHUA_MEMORY_PACKET_H__

