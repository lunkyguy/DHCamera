#ifndef __DAHUA_GENICAM_DEVICECONTROL_H__
#define __DAHUA_GENICAM_DEVICECONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IDeviceControl;

typedef Memory::TSharedPtr<IDeviceControl> IDeviceControlPtr;

/// \ingroup config
/// @{

/// \~chinese
/// \brief Class IDeviceControl AcquisitionControl下属性操作类
class GENICAM_API IDeviceControl
{
public:
	virtual ~IDeviceControl() {}

public:

	/// \~chinese
	/// \brief 获取DeviceUserID属性操作对象，该对象可读写
	/// \return 返回属性操作对象
	virtual CStringNode deviceUserID() = 0;
};

/// @}
GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_DEVICECONTROL_H__
