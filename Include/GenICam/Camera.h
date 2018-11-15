#ifndef __DAHUA_GENICAM_ICAMERA_H__
#define __DAHUA_GENICAM_ICAMERA_H__

#include "Defs.h"
#include "Frame.h"
#include "Memory/SharedPtr.h"
#include "StreamSource.h"

GENICAM_NAMESPACE_BEGIN

/// \~chinese
/// \brief 相机对象接口类
/// \defgroup Camera 相机共用操作接口
/// @{

/// \~chinese
/// \brief Class ICamera 相机对象接口类，表示一台相机，所有协议类型都可共用的接口。该实例对象可通过CSystem获取
class GENICAM_API ICamera
{
protected:
	/// \~chinese
	/// \brief 析构函数
	virtual ~ICamera(){}
	
public:

	enum ECameraAccessPermission
	{
		accessPermissionExclusive = 1, ///< \~chinese 独占访问权限
		accessPermissionControl,       ///< \~chinese 非独占可读访问权限
		accessPermissionUndefined      ///< \~chinese 未定义访问权限
	};
	
	enum ECameraType
	{
		typeGige = 0,	///< \~chinese GIGE相机
		typeU3v = 1,	///< \~chinese USB3.0相机
		typeUndefined	///< \~chinese 未知类型
	};
	
	/// \~chinese
	/// \brief  得到相机类型
	/// \return 返回相机类型
	virtual int32_t getType() const = 0;
	
	/// \~chinese
	/// \brief  获取相机名称
	/// \return 返回相机名称
	virtual const char * getName() = 0;
	
	/// \~chinese
	/// \brief  获取相机的唯一标识.
	/// \return 唯一标识相机的字符串.
	virtual const char * getKey()  = 0;
	
    /// \~chinese
	/// \brief  连接设备
	/// 与相机建立连接关系，如Gige Vision协议的相机即是获得控制权限、创建控制通道
	/// \param [in] accessPermission 打开相机控制通道时默认为control access 权限
	/// \return 是否连接成功
	virtual bool connect(ECameraAccessPermission accessPermission = accessPermissionControl) = 0;
		
	/// \~chinese
	/// \brief 断开连接
	/// 断开与相机的连接关系，如Gige Vision协议的相机即是释放控制权限、销毁控制通道
	/// \return 是否断开成功 
	virtual bool disConnect() = 0;
		
	/// \~chinese
	/// \brief 判断相机当前是否处于已连接状态
	/// \return 是否已连接
	virtual bool isConnected() = 0;
		      								
	/// \~chinese
	/// \brief  获取相机所属的接口名
	/// \return 设备所属的接口名
	virtual const char * getInterfaceName()  = 0;

	/// \~chinese
	/// \brief  获取相机所连接的接口类型
	/// \return 相机所连接的接口类型
	virtual int32_t getInterfaceType() const = 0;
	
	/// \~chinese
	/// \brief 下载相机描述XML文件
	/// 下载相机描述文件，并保存到指定路径
	/// \param [in] aFullFilename 文件要保存的路径
	/// \return 是否下载成功
	virtual bool downLoadGenICamXML(const char* aFullFilename) = 0;

	/// 读用户自定义数据。相机内部保留32768字节用于用户存储自定义数据（此功能针对大华相机，其它品牌相机无此功能）。
	/// \param [out] pBuffer 数据缓冲的指针。
	/// \param [in] dwCount 期望读出的字节数
	/// \return 返回用户实际读取到的字节数
	virtual size_t readUserPrivateData(void* pBuffer, size_t dwCount) = 0;

	/// 写用户自定义数据。和readUserPrivateData对应
	/// \param [in] pBuffer 数据缓冲的指针。
	/// \param [in] dwCount 期望写入的字节数
	/// \return 返回用户实际写入的字节数
	virtual size_t writeUserPrivateData(const void *pBuffer, size_t dwCount) = 0;
	
	/// \~chinese
	/// \brief 获取相机制造厂商名称
	/// \return 返回相机制造厂商名称
	virtual const char * getVendorName() = 0;
	
	/// \~chinese
	/// \brief 获取相机型号
	/// \return 返回相机型号
	virtual const char * getModelName() = 0;

	/// \~chinese
	/// \brief 获取相机序列号
	/// \return 返回相机序列号
	virtual const char * getSerialNumber() = 0;
	
};

typedef Memory::TSharedPtr<ICamera> ICameraPtr;
/// @}

GENICAM_NAMESPACE_END

#endif//__DAHUA_GENICAM_ICAMERA_H__
