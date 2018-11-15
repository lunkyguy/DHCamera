#ifndef __DAHUA_GENICAM_USERSETCONTROL_H__
#define __DAHUA_GENICAM_USERSETCONTROL_H__

#include "Defs.h"
#include "ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IUserSetControl;

typedef Memory::TSharedPtr<IUserSetControl> IUserSetControlPtr;

/// \ingroup config
/// @{

/// \~chinese
/// \brief Class IUserSetControl UserSetControl下属性操作类
class GENICAM_API IUserSetControl
{
public:
	virtual ~IUserSetControl() {}

public:
	enum EConfigSet
	{
		userSet1 = 1,			///< 【读写】相机配置集合1
		userSet2 = 2,			///< 【读写】相机配置集合2
		userSetInvalid
	};

public:
	/// \~chinese
	/// \brief 恢复相机默认配置
	/// \return 成功返回true，否则返回false
	virtual bool restoreDefault() = 0;

	/// \~chinese
	/// \brief 设置相机当前配置，并生效且下次以该配置启动
	/// \param [in] configSet 要设置的配置集合
	/// \return 成功返回true，否则返回false
	virtual bool setCurrentUserSet(EConfigSet configSet = userSet1) = 0;

	/// \~chinese
	/// \brief 保存相机当前配置到某配置集合，如userSet1
	/// \param [in] configSet 要保存到的配置集合
	/// \return 成功返回true，否则返回false
	virtual bool saveUserSet(EConfigSet configSet = userSet1) = 0;

	/// \~chinese
	/// \brief 获取相机当前配置集合
	/// \return 返回配置集合枚举值
	virtual EConfigSet getCurrentUserSet() = 0;

	/// \~chinese
	/// \brief 获取相机当前UserSet相关是否可用
	/// \return 可用返回true，否则返回false
	virtual bool isAvailable() const = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_USERSETCONTROL_H__
