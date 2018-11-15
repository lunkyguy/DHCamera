#ifndef __DAHUA_GENICAM_ISPCONTROL_H__
#define __DAHUA_GENICAM_ISPCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IISPControl;

typedef Memory::TSharedPtr<IISPControl> IISPControlPtr;

/// \ingroup config
/// @{

/// \~chinese
/// \brief Class IISPControl ISPControl下属性操作类
class GENICAM_API IISPControl
{
public:
	virtual ~IISPControl() {}

public:
	/// \~chinese
	/// \brief 获取Brightness属性操作对象，设置亮度
	/// \return 返回属性操作对象
	virtual CIntNode brightness() = 0;

	/// \~chinese
	/// \brief 获取Sharpness属性操作对象，设置锐度
	/// \return 返回属性操作对象
	virtual CIntNode sharpness() = 0;

	/// \~chinese
	/// \brief 获取SharpnessAuto属性操作对象，设置是否自动锐度
	/// \return 返回属性操作对象
	virtual CBoolNode sharpnessAuto() = 0;

	/// \~chinese
	/// \brief 获取SharpnessEnable属性操作对象，设置是否开启锐度
	/// \return 返回属性操作对象
	virtual CEnumNode sharpnessEnable() = 0;

	/// \~chinese
	/// \brief 获取Contrast属性操作对象，设置对比度
	/// \return 返回属性操作对象
	virtual CIntNode contrast() = 0;

	/// \~chinese
	/// \brief 获取Hue属性操作对象，设置色度
	/// \return 返回属性操作对象
	virtual CIntNode hue() = 0;

	/// \~chinese
	/// \brief 获取Saturation属性操作对象，设置饱和度
	/// \return 返回属性操作对象
	virtual CIntNode saturation() = 0;


	/// \~chinese
	/// \brief 获取DigitalShift属性操作对象，设置DigitalShif
	/// \return 返回属性操作对象
	virtual CIntNode digitalshift() = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_ISPCONTROL_H__
