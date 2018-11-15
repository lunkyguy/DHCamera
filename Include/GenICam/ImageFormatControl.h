#ifndef __DAHUA_GENICAM_IMAGEFORMATCONTROL_H__
#define __DAHUA_GENICAM_IMAGEFORMATCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IImageFormatControl;

typedef Memory::TSharedPtr<IImageFormatControl> IImageFormatControlPtr;

/// \ingroup config
/// @{

/// \~chinese
/// \brief Class IImageFormatControl ImageFormatControl下属性操作类
class GENICAM_API IImageFormatControl
{
public:
	virtual ~IImageFormatControl() {}

public:
	/// \~chinese
	/// \brief 获取Height属性操作对象
	/// \return 返回属性操作对象
	virtual CIntNode height() = 0;

	/// \~chinese
	/// \brief 获取Width属性操作对象
	/// \return 返回属性操作对象
	virtual CIntNode width() = 0;

	/// \~chinese
	/// \brief 获取OffsetX属性操作对象
	/// \return 返回属性操作对象
	virtual CIntNode offsetX() = 0;

	/// \~chinese
	/// \brief 获取OffsetY属性操作对象
	/// \return 返回属性操作对象
	virtual CIntNode offsetY() = 0;

	/// \~chinese
	/// \brief 获取PixelFormat属性操作对象
	/// \return 返回属性操作对象
	virtual CEnumNode pixelFormat() = 0;

	/// \~chinese
	/// \brief 获取ReverseX属性操作对象，设置是否翻转图像X轴
	/// \return 返回属性操作对象
	virtual CBoolNode reverseX() = 0;

	/// \~chinese
	/// \brief 获取ReverseY属性操作对象，设置是否翻转图像Y轴
	/// \return 返回属性操作对象
	virtual CBoolNode reverseY() = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_IMAGEFORMATCONTROL_H__
