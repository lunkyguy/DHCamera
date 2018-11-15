#ifndef __DAHUA_GENICAM_TRANSPORTLAYERCONTROL_H__
#define __DAHUA_GENICAM_TRANSPORTLAYERCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class ITransportLayerControl;

typedef Memory::TSharedPtr<ITransportLayerControl> ITransportLayerControlPtr;

/// \ingroup config
/// @{

/// \~chinese
/// \brief Class ITransportLayerControl TransportLayerControl下属性操作类
class GENICAM_API ITransportLayerControl
{
public:
	virtual ~ITransportLayerControl() {}

public:
	/// \~chinese
	/// \brief 获取GevSCPD属性操作对象，设置包发送间隔
	/// \return 返回属性操作对象
	virtual CIntNode gevSCPD() = 0;

	/// \~chinese
	/// \brief 获取GevCurrentIPConfigurationDHCP属性操作对象，是否启用DHCP
	/// \return 返回属性操作对象
	virtual CBoolNode gevCurrentIPConfigurationDHCP() = 0;

	/// \~chinese
	/// \brief 获取GevCurrentIPConfigurationPersistentIP属性操作对象，是否启用静态IP
	/// \return 返回属性操作对象
	virtual CBoolNode gevCurrentIPConfigurationPersistentIP() = 0;

	/// \~chinese
	/// \brief 获取GevPersistentIPAddress属性操作对象，设置静态IP地址
	/// \return 返回属性操作对象
	virtual CStringNode gevPersistentIPAddress() = 0;

	/// \~chinese
	/// \brief 获取GevPersistentSubnetMask属性操作对象，设置静态IP子网掩码
	/// \return 返回属性操作对象
	virtual CStringNode gevPersistentSubnetMask() = 0;

	/// \~chinese
	/// \brief 获取GevPersistentDefaultGateway属性操作对象，设置静态IP网关
	/// \return 返回属性操作对象
	virtual CStringNode gevPersistentDefaultGateway() = 0;

    /// \~chinese
    /// \brief 获取GevGVCPHeartbeatDisable属性操作对象，是否停用GVCP Heartbeat
    /// \return 返回属性操作对象
    virtual CBoolNode gevGVCPHeartbeatDisable() = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_TRANSPORTLAYERCONTROL_H__

