#ifndef __DAHUA_GENICAM_IGIGEINTERFACE_H__
#define __DAHUA_GENICAM_IGIGEINTERFACE_H__

#include "GenICam/Defs.h"
#include "GenICam/Camera.h"
#include "Infra/String.h"
#include "Memory/SharedPtr.h"

GENICAM_NAMESPACE_BEGIN

class IGigEInterface;
typedef Memory::TSharedPtr<IGigEInterface> IGigEInterfacePtr;

/// \~chinese
/// \brief 相机对象接口类
/// \defgroup GigEInterface  连接GigE相机的接口对象操作接口
/// @{

/// \~chinese
/// \brief Class IGigEInterface  GigE相机连接的接口对象提供的操作 
class GENICAM_API IGigEInterface
{
protected:
	~IGigEInterface(){}

public:
	/// \~chinese
	/// \brief GigE相机连接的接口对象构造函数，同一个cameraPtr对应的是同一个GigE相机连接的接口对象
	/// \param [in] cameraPtr  GigE相机智能指针对象
	static IGigEInterfacePtr getInstance(const ICameraPtr &cameraPtr);
    
	/// \~chinese
	/// \return 返回网卡描述信息
	virtual Infra::CString getDescription() const = 0;
	
	/// \~chinese
	/// \return 返回网卡的IP地址
	virtual Infra::CString getIpAddress() const = 0;
	
	/// \~chinese
	/// \return 返回网卡的子网掩码
	virtual Infra::CString getSubnetMask() const = 0;
	
	/// \~chinese
	/// \brief 返回网卡的网关
	/// \return 返回网卡的网关
	virtual Infra::CString getGateway() const = 0;
	
	/// \~chinese
	/// \return 返回网卡的Mac地址
	virtual Infra::CString getMacAddress() const = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif//__DAHUA_GENICAM_IGIGEINTERFACE_H__