#ifndef __DAHUA_GENICAM_CSYSTEM_H__
#define __DAHUA_GENICAM_CSYSTEM_H__

#include "Defs.h"
#include "Camera.h"
#include "StreamSource.h"
#include "ParameterNode.h"
#include "AcquisitionControl.h"
#include "AnalogControl.h"
#include "ImageFormatControl.h"
#include "ISPControl.h"
#include "UserSetControl.h"
#include "DeviceControl.h"
#include "TransportLayerControl.h"
#include "DigitalIOControl.h"

#include "EventSubscribe.h"

GENICAM_NAMESPACE_BEGIN

/// \~chinese
/// \brief 发现设备、创建常用属性对象
/// \defgroup System 设备发现、属性常用对象创建和事件订阅对象创建接口
/// @{

/// \~chinese
/// \brief Class CSystem 枚举主机所有物理接口可达的在线相机、属性常用对象创建、事件订阅对象创建及获取SDK版本信息
class GENICAM_API CSystem
{
public:
	///枚举：物理接口类型
	enum EInterfaceType
	{
		typeGige = 0,	///< \~chinese 网卡接口类型
		typeUsb3 = 1,	///< \~chinese USB3.0接口类型	
		typeCL   = 2,	///< \~chinese CAMERALINK接口类型
		typeAll	        ///< \~chinese 忽略接口类型，设备发现传入此类型时，表示需发现所有接口下的设备
	};
	
	/// \~chinese
    /// \brief CSystem单例获取接口
    /// \return CSystem单例对象的指针
	static CSystem& getInstance();

	/// \~chinese
	/// \brief 发现指定接口类型可达的设备
	/// \param [out] vCameraPtrList 指定接口类型所有在线设备对象列表,当interfaceType = typeAll 时，发现所有接口下的在线设备
	/// \param [in]  interfaceType  接口类型
	/// \return 是否成功
	bool discovery(Infra::TVector<ICameraPtr>& vCameraPtrList, EInterfaceType interfaceType = typeAll);

	/// \~chinese
	/// \brief 根据 Camera key "厂商:序列号" 获取 Camera 智能指针
	/// \param [in] pCameraKey 相机的key
	/// \return Camera 智能指针,若传入的pCameraKey不存在或者非法，则返回空智能指针对象
	ICameraPtr getCameraPtr(const char * pCameraKey) const;
	
	/// \~chinese
	/// \brief 创建流对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \param [in] channelId 流通道号，默认为0通道
	/// \return 流智能指针对象
	IStreamSourcePtr createStreamSource(const ICameraPtr &cameraPtr, uint16_t channelId = 0);

	/// \~chinese
	/// \brief 创建事件订阅对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return 事件订阅对象
	IEventSubscribePtr createEventSubscribe(const ICameraPtr &cameraPtr);

	/// \~chinese
	/// \brief 创建AcquisitionControl对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return AcquisitionControl智能指针对象
	IAcquisitionControlPtr createAcquisitionControl(const ICameraPtr &cameraPtr);

	/// \~chinese
	/// \brief 创建AnalogControl对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return AnalogControl智能指针对象
	IAnalogControlPtr createAnalogControl(const ICameraPtr &cameraPtr);

	/// \~chinese
	/// \brief 创建ISPControl对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return ISPControl智能指针对象
	IISPControlPtr createISPControl(const ICameraPtr &cameraPtr);

	/// \~chinese
	/// \brief 创建ImageFormatControl对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return ImageFormatControl智能指针对象
	IImageFormatControlPtr createImageFormatControl(const ICameraPtr &cameraPtr);

	/// \~chinese
	/// \brief 创建UserSetControl对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return UserSetControl智能指针对象
	IUserSetControlPtr createUserSetControl(const ICameraPtr &cameraPtr);

	/// \~chinese
	/// \brief 创建DeviceControl对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return DeviceControl智能指针对象
	IDeviceControlPtr createDeviceControl(const ICameraPtr &cameraPtr);
	 
	/// \~chinese
	/// \brief 创建TransportLayerControl对象
	/// \param [in] cameraPtr 相机智能指针对象
	/// \return TransportLayerControl智能指针对象
	ITransportLayerControlPtr createTransportLayerControl(const ICameraPtr &cameraPtr);

    /// \~chinese
    /// \brief 创建DigitalIOControl对象
    /// \param [in] cameraPtr 相机智能指针对象
    /// \return DigitalIOControl智能指针对象
    IDigitalIOControlPtr createDigitalIOControl(const ICameraPtr &cameraPtr);

	/// \~chinese
	/// \brief 获取版本信息
	/// \return 版本信息
	const char* getVersion() const;

private:
	/// \~chinese
	/// \brief 构造函数
	CSystem();
	
	/// \~chinese
	/// \brief 拷贝构造函数
	CSystem(const CSystem&); 
	
	/// \~chinese
	/// \brief 赋值函数
	CSystem& operator = (const CSystem&);

	/// \~chinese
	/// \brief 析构函数
	~CSystem();
	
	class Impl;
	Impl *m_pImpl;
};

/// @}

GENICAM_NAMESPACE_END

#endif//__DAHUA_GENICAM_CSYSTEM_H__
