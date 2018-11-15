#ifndef __DAHUA_GENICAM_ACQUISITIONCONTROL_H__
#define __DAHUA_GENICAM_ACQUISITIONCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IAcquisitionControl;

typedef Memory::TSharedPtr<IAcquisitionControl> IAcquisitionControlPtr;

/// \ingroup config
/// @{

/// \~chinese
/// \brief Class IAcquisitionControl AcquisitionControl下属性操作类
class GENICAM_API IAcquisitionControl
{
public:
	virtual ~IAcquisitionControl() {}

public:
	/// \~chinese
	/// \brief 获取AcquisitionFrameCount属性操作对象
	/// \return 返回属性操作对象
	virtual CIntNode acquisitionFrameCount() = 0;

	/// \~chinese
	/// \brief 获取AcquisitionFrameRate属性操作对象
	/// \return 返回属性操作对象
	virtual CDoubleNode acquisitionFrameRate() = 0;

	/// \~chinese
	/// \brief 获取AcquisitionFrameRate属性操作对象
	/// \return 返回属性操作对象
	virtual CEnumNode acquisitionMode() = 0;

	/// \~chinese
	/// \brief 获取ExposureAuto属性操作对象
	/// \return 返回属性操作对象
	virtual CEnumNode exposureAuto() = 0;

	/// \~chinese
	/// \brief 获取ExposureMode属性操作对象
	/// \return 返回属性操作对象
	virtual CEnumNode exposureMode() = 0;

	/// \~chinese
	/// \brief 获取ExposureTime属性操作对象
	/// \return 返回属性操作对象
	virtual CDoubleNode exposureTime() = 0;

	/// \~chinese
	/// \brief 获取TriggerActivation属性操作对象，设置触发上升沿下降沿
	/// \return 返回属性操作对象
	virtual CEnumNode triggerActivation() = 0;

	/// \~chinese
	/// \brief 获取TriggerDelay属性操作对象，设置软触发延时
	/// \return 返回属性操作对象
	virtual CDoubleNode triggerDelay() = 0;

	/// \~chinese
	/// \brief 获取TriggerMode属性操作对象，设置开启/关闭软触发
	/// \return 返回属性操作对象
	virtual CEnumNode triggerMode() = 0;

	/// \~chinese
	/// \brief 获取TriggerSelector属性操作对象，设置开启/关闭软触发
	/// \return 返回属性操作对象
	virtual CEnumNode triggerSelector() = 0;

	/// \~chinese
	/// \brief 获取TriggerSource属性操作对象，设置内部/外部触发
	/// \return 返回属性操作对象
	virtual CEnumNode triggerSource() = 0;

	/// \~chinese
	/// \brief 获取TriggerSoftware属性操作对象，执行内部软触发
	/// \return 返回属性操作对象
	virtual CCmdNode triggerSoftware() = 0;

	/// \~chinese
	/// \brief 获取AcquisitionFrameRateEnable使能属性操作对象
	/// \return 返回属性操作对象
	virtual CBoolNode acquisitionFrameRateEnable() = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_ACQUISITIONCONTROL_H__
