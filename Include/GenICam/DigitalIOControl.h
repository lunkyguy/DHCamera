#ifndef __DAHUA_GENICAM_DIGITALIOCONTROL_H__
#define __DAHUA_GENICAM_DIGITALIOCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IDigitalIOControl;

typedef Memory::TSharedPtr<IDigitalIOControl> IDigitalIOControlPtr;

/// \ingroup config
/// @{

/// \~chinese
/// \brief Class IDigitalIOControl DigitalIOControl下属性操作类
class GENICAM_API IDigitalIOControl
{
public:
    virtual ~IDigitalIOControl() {}

public:
	/// \~chinese
	/// \brief 获取LineSelector属性操作对象
	/// \return 返回属性操作对象
    virtual CEnumNode lineSelector() = 0;

	/// \~chinese
	/// \brief 获取LineDebouncerTimeAbs属性操作对象
	/// \return 返回属性操作对象
	virtual CDoubleNode lineDebouncerTimeAbs() = 0;

	/// \~chinese
	/// \brief 获取UserOutputSelector属性操作对象
	/// \return 返回属性操作对象
	virtual CEnumNode userOutputSelector() = 0;

	/// \~chinese
	/// \brief 获取UserOutputValue属性操作对象
	/// \return 返回属性操作对象
	virtual CBoolNode userOutputValue() = 0;

};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_DIGITALIOCONTROL_H__
