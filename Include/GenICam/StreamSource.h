#ifndef __DAHUA_GENICAM_ISTREAMSOURCE_H__
#define __DAHUA_GENICAM_ISTREAMSOURCE_H__

#include "Defs.h"
#include "Frame.h"
#include "Infra/Signal.h"

GENICAM_NAMESPACE_BEGIN

/// \~chinese
/// \brief 流对象接口类
/// \defgroup stream 流对象操作接口
/// @{

/// \~chinese
/// \brief Class IStreamSource 流对象接口
class GENICAM_API IStreamSource
{
protected:
	/// \~chinese
	/// \brief 析构函数
	virtual ~IStreamSource(){}
	
public:	

	enum EGrabStrategy
	{
		grabStrartegySequential  = 0,	///< \~chinese The images are processed in the order of their arrival
		grabStrartegyLatestImage = 1,   ///< \~chinese 获取最新的图片
		grabStrartegyUndefined   		///< \~chinese 未定义
	};

	/// \brief 设备流回调函数声明:每次回调送出一帧数据
	/// CFrame 回调时主动推送的帧对象
	typedef Infra::TSignal1<const CFrame&> Signal;
	typedef Signal::Proc Proc;

	/// \~chinese
	/// \brief 开始抓图
	/// \param [in] maxImagesGrabbed 允许最多的抓图数，达到指定抓图数后停止抓图，如果为0，表示忽略此参数连续抓图
	/// \param [in] strategy 抓图策略,默认按缓存队列中的顺序抓图
	/// \return 返回抓图是否成功
	virtual bool startGrabbing(uint64_t maxImagesGrabbed = 0,EGrabStrategy strategy = grabStrartegySequential) = 0;
					
	/// \~chinese
	/// \brief 停止抓图
	/// \return 返回停止抓图是否成功	
	virtual bool stopGrabbing() = 0;
							
	/// \~chinese
	/// \brief 是否正在抓图
	/// \return 返回是否成功
	virtual bool isGrabbing() = 0;
				
	/// \~chinese
	/// \brief 获取一帧图像，该接口不支持多线程调用
	/// \param [out] frame 一帧图像
	/// \param [in]  timeoutMS 获取一帧图像的超时时长,单位MS,当值为INFINITE时表示无限等待
	/// \return 返回是否成功
	virtual bool getFrame(CFrame &frame,uint32_t timeoutMS = INFINITE) const = 0;

	/// \~chinese
	/// \brief 注册数据帧回调函数。该异步获取帧机制和同步获取帧机制互斥，系统中两者只能选其一。
	/// \param [in] proc 数据帧回调函数，建议不要在该函数中处理耗时的操作，否则会阻塞后续数据帧的实时性
	/// \return 返回注册是否成功
	virtual bool attachGrabbing(Proc proc) = 0;

	/// \~chinese
	/// \brief 去注册数据帧回调函数
	/// \param [in] proc 去注册数据帧回调函数
	/// \return 返回去注册是否成功
	virtual bool detachGrabbing(Proc proc) = 0;
	
	/// \~chinese
    /// \brief 设置缓存个数,不能在拉流过程中设置
    /// \param [in]  nSize 缓存数量，可设置值：1,2,4,8,16,其余返回false
    /// \return 返回是否成功
    virtual bool setBufferCount(uint32_t nSize) = 0;
};

typedef Memory::TSharedPtr<IStreamSource> IStreamSourcePtr;
/// @}

GENICAM_NAMESPACE_END

#endif //__DAHUA_GENICAM_ISTREAMSOURCE_H__