#ifndef __DAHUA_GENICAM_CFRAME_H__
#define __DAHUA_GENICAM_CFRAME_H__

#include "Defs.h"
#include "Memory/Block.h"
#include "Infra/Vector.h"
#include "Infra/String.h"
#include "PixelType.h"


GENICAM_NAMESPACE_BEGIN

/// \~chinese
/// \brief 数据帧对象接口
/// \defgroup Frame 数据帧操作接口 
/// @{

/// \~chinese
/// \brief Class CFrame 数据帧对象接口，帧的长、宽以及数据格式可从该对象中获取。
class GENICAM_API CFrame : public Memory::CBlock
{
public:	

	enum EPayloadType
	{
		payloadImage = 1,	            ///< \~chinese 图片
		payloadRawdata,					///< \~chinese 裸数据
		payloadFile,					///< \~chinese 文件
		payloadChunkData,				///< \~chinese 块数据
		payloadExtChunkData,			///< \~chinese 扩展块数据
		payloadDevSpecBase = 0x8000,    ///< \~chinese 设备特有
		payloadUndefined				///< \~chinese 未定义
	};
	
	/// \~chinese
	/// brief 空构造函数
	CFrame();
	
	/// \~chinese
	/// brief  帧对象构造函数
	/// \param [in] other 构造帧对象的原始数据块对象
	explicit CFrame(Memory::CBlock const& other);
	
	/// \~chinese
	/// \brief 帧深拷贝克隆接口
	/// \return 新的一帧对象
	CFrame clone();
	
	/// \~chinese
	/// \brief 外面不使用时需要调用此接口释放Image相关内存
	/// \return none
	void reset();
	
	/// brief 是否有效
	/// \return 返回该帧是否有效
	bool valid() const;
	
	/// \~chinese
	/// \brief 获取该帧图片数据的内存首地址
	/// \return 返回该帧图片数据的内存首地址
	const void * getImage() const;
			
	/// \~chinese
	/// \brief 获取数据帧状态
	/// \return 返回数据帧状态
	uint32_t getFrameStatus() const;

	/// \~chinese
	/// \brief 获取图片宽度
	/// \return 返回图片宽度
	uint32_t getImageWidth() const;
		
	/// \~chinese
	/// \brief 获取图片高度
	/// \return 返回图片高度
	uint32_t getImageHeight() const;
			
	/// \~chinese
	/// \brief 获取图片大小
	/// \return 返回图片大小
	uint32_t getImageSize() const;
			
	/// \~chinese
	/// \brief 获取图片像素格式
	/// \return 返回图片像素格式
	EPixelType getImagePixelFormat() const;
			 
	/// \~chinese
	/// \brief 获取图片时间戳
	/// \return 返回图片时间戳
	uint64_t getImageTimeStamp() const;
			 
	/// \~chinese
	/// \brief 获取图片对应的BlockId
	/// \return 返回图片对应的BlockId
	uint64_t getBlockId() const;
			
	/// \~chinese
	/// \brief 获取当前帧数据净荷类型
	/// \param [out] payloadTypes 当前帧数据类型种类集
	/// \return 返回当前帧数据净荷类型
	bool getPayLoadTypes(Infra::TVector<EPayloadType>& payloadTypes) const;
			
	/// \~chinese
	/// \brief 获取Buffer中包含的Chunk个数
	/// \return Chunk个数
	uint32_t getChunkCount() const;
	
	/// \~chinese
	/// \brief 获取Chunk数据
	/// \param [in] aIndex 索引ID
	/// \param [out] aID ChunkID
	/// \param [out] paramNames Chunk数据对应的属性名
	/// \return 是否成功
	bool getChunkDataByIndex(uint32_t aIndex, uint32_t &aID, Infra::TVector<Infra::CString>& paramNames) const;
};

/// @}

GENICAM_NAMESPACE_END

#endif //__DAHUA_GENICAM_CFRAME_H__

