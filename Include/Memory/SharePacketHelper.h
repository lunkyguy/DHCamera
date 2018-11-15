
#ifndef __DAHUA_MEMORY_SHAREPACKETHELPER_H__
#define __DAHUA_MEMORY_SHAREPACKETHELPER_H__

#include "Memory/Packet.h"
#include <string>

namespace Dahua{
namespace Memory{

/// ��������
struct BaseArg
{
	BaseArg(uint32_t argType) : type(argType) {}

	uint32_t type;
};

/// �ڴ�ز���
struct SharePacketArg : public BaseArg
{
	enum
	{
		MAP_POOL,    ///< ӳ�乲���ڴ�(Ӧ�ý���ʹ��)
		INIT_POOL     ///< ��ʼ�������ڴ�(�ػ�����ʹ��)
	};

	SharePacketArg(int type = MAP_POOL) : BaseArg(type) {}

	uint32_t     poolSize;    ///< �ڴ�ش�С
	std::string  poolType;   ///< "ShareMemory" or "AvMemory"
	uint32_t     pageSize;  ///< ҳ��С(buddy�㷨�й�, һ�����������С�ڴ�)
	uint32_t     orderNum; ///< order����(buddy�㷨�йأ�һ�������������ڴ�=(2^(order - 1))*pageSize)
	uint32_t     debugMode;  ///< ����ģʽ 0�������汾  1:����ұ�Խ��  2:������Խ��
};

class MEMORY_API CSharePacketHelper
{
public:

	/// ��ȡʵ��
	static CSharePacketHelper* instance();

	/// \��ԭʼ���ݰ�����һ�����ڷ��͵�������Ϣ��
	/// \param pkt [in] ԭʼ���ݰ�
	/// \return ������ϢCPacket
	/// \note �Ƿ�ɹ���CPacket��valid�ӿ�У��
	CPacket toDescribePacket(const CPacket& pkt);

	/// \��������Ϣ����ԭ��ԭʼ���ݰ�
	/// \param pkt [in] ������Ϣ��
	/// \return ԭʼ���ݰ�
	/// \note �Ƿ�ɹ���CPacket��valid�ӿ�У��
	CPacket toOriginalPacket(const CPacket& pkt);

	/// \��ʼ�������ڴ�
	/// \param [in] arg ��ʼ���ڴ�Ĳ���
	/// \retval true �ɹ� false ʧ��
	bool initSharePacket(BaseArg * arg);

};


} // namespace Memory
} // namespace Dahua


#endif // end of __DAHUA_MEMORY_SHAREPACKETHELPER_H__

