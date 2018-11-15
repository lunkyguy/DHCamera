#ifndef __DAHUA_GENICAM_IGIGECAMERA_H__
#define __DAHUA_GENICAM_IGIGECAMERA_H__

#include "GenICam/Defs.h"
#include "GenICam/Camera.h"
#include "Infra/String.h"
#include "Memory/SharedPtr.h"

GENICAM_NAMESPACE_BEGIN

class IGigECamera;
typedef Memory::TSharedPtr<IGigECamera> IGigECameraPtr;

/// \~chinese
/// \brief 相机对象接口类
/// \defgroup GigECamera  GigE相机对象操作接口
/// @{

/// \~chinese
/// \brief GigE相机信息
class GENICAM_API IGigECamera
{
protected:
	/// \~chinese
	/// \brief 析构函数
	~IGigECamera(){}

public: 
	/// \~chinese
	/// \brief GigE相机对象构造函数，同一个cameraPtr对应的是同一个GigE相机对象
	/// \param [in] cameraPtr  GigE相机智能指针对象,如果传入了其它非GigE相机类型，该接口返回空指针,表示无效
	static  IGigECameraPtr getInstance(const ICameraPtr &cameraPtr);
	
	/// \~chinese
	/// \brief 获取相机的ipAddress
	/// \return 返回ipAddress 相机的IP地址
	virtual Infra::CString getIpAddress() const = 0;

	/// \~chinese
	/// \brief 返回相机的子网掩码
	/// \return 返回subnetMask 相机的子网掩码
	virtual Infra::CString getSubnetMask() const = 0;

	/// \~chinese
	/// \brief 返回相机的网关
	/// \return 返回 subsetMask 相机的网关
	virtual Infra::CString getGateway() const = 0;

	/// \~chinese
	/// \brief 获取相机的 macAddress
	/// \return 返回macAddress 相机的Mac地址
	virtual Infra::CString getMacAddress() const = 0;
	
    /// \~chinese
	/// \brief  修改设备IP
	///1、调用该函数时如果newSubnetMask和newGateway都设置了有效值，则以此有效值为准;
	///2、调用该函数时如果newSubnetMask和newGateway都设置了NULL，则内部实现时用它所连接网卡的子网掩码和网关代替
	///3、调用该函数时如果newSubnetMask和newGateway两者中其中一个为NULL，另一个非NULL，则返回失败
	/// 该接口只针对通过网卡接入的设备，对于其余设备，调用此接口无意义
	/// \param [in] newIpAddress 新的IP地址信息
	/// \param [in] newSubnetMask 新的掩码信息
	/// \param [in] newGateway 新的网关信息
	/// \return 是否成功
	virtual bool forceIpAddress (const char* newIpAddress, const char* newSubnetMask = NULL, const char* newGateway = NULL) = 0;
	
};

/// @}

GENICAM_NAMESPACE_END

#endif//__DAHUA_GENICAM_IGIGECAMERA_H__