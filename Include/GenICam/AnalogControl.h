#ifndef __DAHUA_GENICAM_ANALOGCONTROL_H__
#define __DAHUA_GENICAM_ANALOGCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IAnalogControl;

typedef Memory::TSharedPtr<IAnalogControl> IAnalogControlPtr;

/// \ingroup config
/// @{

/// \~chinese
/// \brief Class IAnalogControl AnalogControl下属性操作类
class GENICAM_API IAnalogControl
{
public:
	virtual ~IAnalogControl() {}

public:
	/// \~chinese
	/// \brief 获取BlackLevelSelector属性操作对象，设置操作哪个白平衡
	/// \return 返回属性操作对象
	virtual CEnumNode blackLevelSelector() = 0;

	/// \~chinese
	/// \brief 获取BlackLevelAuto属性操作对象，设置自动白平衡
	/// \return 返回属性操作对象
	virtual CEnumNode blackLevelAuto() = 0;

	/// \~chinese
	/// \brief 获取BlackLevel属性操作对象，设置白平衡值
	/// \return 返回属性操作对象
	virtual CIntNode blackLevel() = 0;

	/// \~chinese
	/// \brief 获取GainAuto属性操作对象
	/// \return 返回属性操作对象
	virtual CEnumNode gainAuto() = 0;

	/// \~chinese
	/// \brief 获取GainRaw属性操作对象
	/// \return 返回属性操作对象
	virtual CDoubleNode gainRaw() = 0;

	/// \~chinese
	/// \brief 获取Gamma属性操作对象，设置Gamma值
	/// \return 返回属性操作对象
	virtual CDoubleNode gamma() = 0;

	/// \~chinese
	/// \brief 获取BalanceRatioSelector属性操作对象，设置操作哪个白平衡
	/// \return 返回属性操作对象
	virtual CEnumNode balanceRatioSelector() = 0;

	/// \~chinese
	/// \brief 获取BalanceWhiteAuto属性操作对象，设置自动白平衡
	/// \return 返回属性操作对象
	virtual CEnumNode balanceWhiteAuto() = 0;

	/// \~chinese
	/// \brief 获取BalanceRatio属性操作对象，设置白平衡值
	/// \return 返回属性操作对象
	virtual CDoubleNode balanceRatio() = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_ANALOGCONTROL_H__

