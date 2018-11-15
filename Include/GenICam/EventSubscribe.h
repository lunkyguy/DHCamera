#ifndef __DAHUA_GENICAM_IEVENTSUBSCRIBE_H__
#define __DAHUA_GENICAM_IEVENTSUBSCRIBE_H__

#include "Defs.h"
#include "Memory/SharedPtr.h"
#include "Infra/Function.h"
#include "Infra/Vector.h"
#include "Infra/String.h"

GENICAM_NAMESPACE_BEGIN

/// 连接事件参数封装
struct SConnectArg
{
	enum EVType
	{
		offLine,   ///< 设备离线通知 
		onLine     ///< 设备在线通知 
	};
	EVType m_event;  ///< 事件类型
	uint32_t reserve[15]; ///< 预留字段
};

/// 参数更新事件参数封装
struct SParamUpdataArg
{
	bool isPoll; 					   ///< 是否是定时更新
	uint32_t reserve[10];		           ///< 预留字段
	Infra::TVector<Infra::CString>  paramNames; ///< 更新的参数名称集合
};

///枚举：流事件状态
enum EEventStatus
{
	streamEventNormal = 1, ///< \~chinese 正常流事件
	streamEventLostFrame = 2, ///< \~chinese 丢帧事件
	streamEventLostPacket = 3,///< \~chinese 丢包事件
	streamEventImageError ///< \~chinese 图像错误事件
};

/// 流事件参数封装
struct SStreamArg
{
	uint32_t     channel;            ///< 流通道号
	uint64_t     blockID;            ///< 流数据BlockID
	uint64_t     timestamp;          ///< 时间戳
	EEventStatus eStreamEventStatus; ///< 流事件状态码
	uint32_t	 status;			 ///< 事件状态错误码
	uint32_t reserve[9];			 ///< 预留字段
};

/// \brief 设备连接状态事件回调函数声明
typedef Infra::TFunction1<void, const SConnectArg&> ConnectArgProc;

/// \brief 参数更新事件回调函数声明
typedef Infra::TFunction1<void, const SParamUpdataArg&> ParamUpdataProc;

/// \brief 设备流事件回调函数声明
typedef Infra::TFunction1<void, const SStreamArg&> StreamArgProc;

/// \~chinese
/// \brief 事件注册回调对象接口类
/// \defgroup Event 相机事件订阅注册与去注册接口
/// @{

/// \~chinese
/// \brief Class IEventSubscribe 事件注册回调对象接口类，其中包括设备状态事件、流通到事件及参数更新事件
class GENICAM_API IEventSubscribe
{
public:
	/// \~chinese
	/// \brief 析构函数
	virtual ~IEventSubscribe(){}

public:
	/// \brief  设备连接状态事件回调注册
	/// \param [in] proc  设备连接状态事件回调注册函数
	/// \return 注册是否成功
	virtual bool subscribeConnectArgs(ConnectArgProc const& proc) = 0;

	/// \brief  设备连接状态事件回调去注册
	/// \param [in] proc  设备连接状态事件回调去注册函数
	/// \return 去注册是否成功
	virtual bool unsubscribeConnectArgs(ConnectArgProc const& proc) = 0;

	/// \~chinese
	/// \brief  参数更新事件回调注册
	/// \param [in] proc 参数更新注册的事件回调函数
	/// \return 注册是否成功
	virtual bool subscribeParamUpdate(ParamUpdataProc const& proc) = 0;

	/// \brief  参数更新事件回调去注册
	/// \param [in] proc 参数更新事件去注册的回调函数
	/// \return 去注册是否成功
	virtual bool unsubscribeParamUpdate(ParamUpdataProc const& proc) = 0;

	/// \brief  流通道事件回调注册
	/// \param [in] proc 流通道事件回调注册函数
	/// \return 注册是否成功
	virtual bool subscribeStreamArg(StreamArgProc const& proc) = 0;

	/// \brief  流通道事件回调去注册
	/// \param [in] proc  流通道事件回调去注册函数
	/// \return 去注册是否成功
	virtual bool unsubscribeStreamArg(StreamArgProc const& proc) = 0;
};

typedef Memory::TSharedPtr<IEventSubscribe> IEventSubscribePtr;
/// @}

GENICAM_NAMESPACE_END
#endif //__DAHUA_GENICAM_IEVENTSUBSCRIBE_H__