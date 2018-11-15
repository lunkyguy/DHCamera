/// \mainpage
/// \~chinese
/// \htmlinclude mainpage_chs.html
/// \~english
/// \htmlinclude mainpage_eng.html

#ifndef __MV_CAMERA_H__
#define __MV_CAMERA_H__
#include "IntTypes.h"

/**
*  @brief  动态库导入导出定义
*/
#ifdef _MSC_VER
	#ifdef GENICAM_API_DLL_BUILD
		#define  GENICAM_API _declspec(dllexport)
	#elif defined GENICAM_API_DLL_USE
		#define  GENICAM_API _declspec(dllimport)
	#else
		#define GENICAM_API
	#endif
#elif defined __GNUC__
	#define GENICAM_API __attribute__((dllexport))
#else
	#define GENICAM_API
#endif

#if (defined (_WIN32) || defined(WIN64))
	#define CALL_METHOD __stdcall
#elif defined __GNUC__
	#define CALL_METHOD __attribute__((__stdcall))
#else
	#define CALL_METHOD
#endif // end #if (defined (_WIN32) || defined(WIN64))

#define MAX_PARAM_CNT         1000
#define MAX_STRING_LENTH      256
#define MAX_PAYLOAD_TYPE_CNT  20

#ifdef __cplusplus
extern "C" {
#endif 

/// \~chinese
/// \brief 图像格式
/// \defgroup ImageFormat 图像格式

/// \~english
/// \brief Image Format
/// \defgroup ImageFormat Image Format
/// @{

//===================================================
// PIXEL FORMATS
//===================================================
// Indicate if pixel is monochrome or RGB

#define GVSP_PIX_MONO                           0x01000000
#define GVSP_PIX_RGB                            0x02000000 // deprecated in version 1.1
#define GVSP_PIX_COLOR                          0x02000000
#define GVSP_PIX_CUSTOM                         0x80000000
#define GVSP_PIX_COLOR_MASK                     0xFF000000

// Indicate effective number of bits occupied by the pixel (including padding).
// This can be used to compute amount of memory required to store an image.
#define GVSP_PIX_OCCUPY1BIT                     0x00010000
#define GVSP_PIX_OCCUPY2BIT                     0x00020000
#define GVSP_PIX_OCCUPY4BIT                     0x00040000
#define GVSP_PIX_OCCUPY8BIT                     0x00080000
#define GVSP_PIX_OCCUPY12BIT                    0x000C0000
#define GVSP_PIX_OCCUPY16BIT                    0x00100000
#define GVSP_PIX_OCCUPY24BIT                    0x00180000
#define GVSP_PIX_OCCUPY32BIT                    0x00200000
#define GVSP_PIX_OCCUPY36BIT                    0x00240000
#define GVSP_PIX_OCCUPY48BIT                    0x00300000
#define GVSP_PIX_EFFECTIVE_PIXEL_SIZE_MASK      0x00FF0000
#define GVSP_PIX_EFFECTIVE_PIXEL_SIZE_SHIFT     16

// Pixel ID: lower 16-bit of the pixel formats
#define GVSP_PIX_ID_MASK                        0x0000FFFF
#define GVSP_PIX_COUNT                          0x46 // next Pixel ID available

//max length of attribute name
#define MAX_ATTR_NAME_LEN 1024

enum EPixelType
{
	// Undefined pixel type
	pixelTypeUndefined = -1,

	// Mono Format
	gvspPixelMono1p = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY1BIT | 0x0037),
	gvspPixelMono2p = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY2BIT | 0x0038),
	gvspPixelMono4p = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY4BIT | 0x0039),
	gvspPixelMono8 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x0001),
	gvspPixelMono8S = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x0002),
	gvspPixelMono10 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0003),
	gvspPixelMono10Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0004),
	gvspPixelMono12 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0005),
	gvspPixelMono12Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0006),
	gvspPixelMono14 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0025),
	gvspPixelMono16 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0007),

	// Bayer Format
	gvspPixelBayGR8 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x0008),
	gvspPixelBayRG8 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x0009),
	gvspPixelBayGB8 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x000A),
	gvspPixelBayBG8 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY8BIT | 0x000B),
	gvspPixelBayGR10 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x000C),
	gvspPixelBayRG10 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x000D),
	gvspPixelBayGB10 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x000E),
	gvspPixelBayBG10 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x000F),
	gvspPixelBayGR12 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0010),
	gvspPixelBayRG12 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0011),
	gvspPixelBayGB12 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0012),
	gvspPixelBayBG12 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0013),
	gvspPixelBayGR10Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0026),
	gvspPixelBayRG10Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0027),
	gvspPixelBayGB10Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0028),
	gvspPixelBayBG10Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x0029),
	gvspPixelBayGR12Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x002A),
	gvspPixelBayRG12Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x002B),
	gvspPixelBayGB12Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x002C),
	gvspPixelBayBG12Packed = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY12BIT | 0x002D),
	gvspPixelBayGR16 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x002E),
	gvspPixelBayRG16 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x002F),
	gvspPixelBayGB16 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0030),
	gvspPixelBayBG16 = (GVSP_PIX_MONO | GVSP_PIX_OCCUPY16BIT | 0x0031),

	// RGB Format
	gvspPixelRGB8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0014),
	gvspPixelBGR8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0015),
	gvspPixelRGBA8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY32BIT | 0x0016),
	gvspPixelBGRA8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY32BIT | 0x0017),
	gvspPixelRGB10 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0018),
	gvspPixelBGR10 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0019),
	gvspPixelRGB12 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x001A),
	gvspPixelBGR12 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x001B),
	gvspPixelRGB16 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0033),
	gvspPixelRGB10V1Packed = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY32BIT | 0x001C),
	gvspPixelRGB10P32 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY32BIT | 0x001D),
	gvspPixelRGB12V1Packed = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY36BIT | 0X0034),
	gvspPixelRGB565P = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0035),
	gvspPixelBGR565P = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0X0036),

	// YVR Format
	gvspPixelYUV411_8_UYYVYY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY12BIT | 0x001E),
	gvspPixelYUV422_8_UYVY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x001F),
	gvspPixelYUV422_8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0032),
	gvspPixelYUV8_UYV = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0020),
	gvspPixelYCbCr8CbYCr = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x003A),
	gvspPixelYCbCr422_8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x003B),
	gvspPixelYCbCr422_8_CbYCrY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0043),
	gvspPixelYCbCr411_8_CbYYCrYY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY12BIT | 0x003C),
	gvspPixelYCbCr601_8_CbYCr = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x003D),
	gvspPixelYCbCr601_422_8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x003E),
	gvspPixelYCbCr601_422_8_CbYCrY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0044),
	gvspPixelYCbCr601_411_8_CbYYCrYY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY12BIT | 0x003F),
	gvspPixelYCbCr709_8_CbYCr = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0040),
	gvspPixelYCbCr709_422_8 = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0041),
	gvspPixelYCbCr709_422_8_CbYCrY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY16BIT | 0x0045),
	gvspPixelYCbCr709_411_8_CbYYCrYY = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY12BIT | 0x0042),

	// RGB Planar
	gvspPixelRGB8Planar = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY24BIT | 0x0021),
	gvspPixelRGB10Planar = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0022),
	gvspPixelRGB12Planar = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0023),
	gvspPixelRGB16Planar = (GVSP_PIX_COLOR | GVSP_PIX_OCCUPY48BIT | 0x0024)
};

/// @}



typedef enum GENICAM_ECameraAccessPermission
{
	accessPermissionExclusive = 1, ///< \~chinese 独占访问权限        ///< \~english Exclusive Access Permission
	accessPermissionControl,       ///< \~chinese 非独占可读访问权限  ///< \~english Non-Exclusive Access Permission
	accessPermissionUndefined      ///< \~chinese 未定义访问权限      ///< \~english Undefined Access Permission
}GENICAM_ECameraAccessPermission;

///< \~chinese
///枚举：协议类型
///< \~english
///enumeration: protocol type
typedef	enum GENICAM_EProtocolType
{
	typeGige = 0,	///< \~chinese GigE协议        ///< \~english GigE Vision Protocol
	typeUsb3 = 1,	///< \~chinese USB3.0协议      ///< \~english USB3.0 Vision Protocol
	typeCL   = 2,	///< \~chinese CAMERALINK协议  ///< \~english Camera Link Protocol
	typeAll	        ///< \~chinese 忽略协议类型，设备发现传入此类型时，表示需发现所有接口下的设备   ///< \~english ALL Supported Protocol
}GENICAM_EProtocolType;

/// \~chinese
/// \brief 相机对象接口类
/// \defgroup Camera 相机共用操作接口

/// \~english
/// \brief Camera Instance Interface Class
/// \defgroup Camera Camera Instance Common Interface

/// @{
/// \~chinese
/// 通用相机对象
/// 32位系统下128字节
/// \~english
/// universal camera object
/// 128 bytes in 32-bit system
typedef struct GENICAM_Camera
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;
	
	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t	(*addRef)(struct GENICAM_Camera *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer	
	int32_t(*release)(struct GENICAM_Camera *thiz);
	
	/// \~chinese
	/// \brief  得到相机类型
	/// \param [in] thiz 本接口指针
	/// \return 成功则返回0，否则返回-1
	/// \~english
	/// \brief  get Camera Type
	/// \param [in] thiz this pointer
	/// \return Success:0, Failure:-1
	int32_t (*getType)(struct GENICAM_Camera *thiz);
	
	/// \~chinese
	/// \brief  获取相机名称
	/// \param [in] thiz 本接口指针
	/// \return 成功返回相机名称，否则返回NULL
	/// \~english
	/// \brief  get Camera Name
	/// \param [in] thiz this pointer
	/// \return Success:Camera Name, Failure:NULL
	const char* (*getName)(struct GENICAM_Camera *thiz);
	
	/// \~chinese
	/// \brief  获取相机的唯一标识.
	/// \param [in] thiz 本接口指针
	/// \return 成功返回唯一标识相机的字符串，失败返回NULL
	/// \~english
	/// \brief  get Camera Unique Key
	/// \param [in] thiz this pointer
	/// \return Success:Camera Name, Failure:NULL
	const char* (*getKey)(struct GENICAM_Camera *thiz);
	
    /// \~chinese
	/// \brief  连接设备
	/// 与相机建立连接关系，如Gige Vision协议的相机即是获得控制权限、创建控制通道
	/// \param [in] thiz 本接口指针
	/// \param [in] accessPermission 目前只支持accessPermissionControl权限，调用该接口时传入此类权限
	/// \retval < 0 连接设备失败
	/// \retval 0   连接设备成功
	/// \~english
	/// \brief  connect to camera
	/// get the control permission of camera, and create the control channel
	/// \param [in] thiz this pointer
	/// \param [in] accessPermission only accessPermissionControl supported currently
	/// \retval < 0 connection failed
	/// \retval 0   connection successful
	int32_t (*connect)(struct GENICAM_Camera *thiz,GENICAM_ECameraAccessPermission accessPermission);
		
	/// \~chinese
	/// \brief 断开连接
	/// 断开与相机的连接关系，如Gige Vision协议的相机即是释放控制权限、销毁控制通道
	/// \param [in] thiz 本接口指针
	/// \retval < 0 断开设备失败
	/// \retval 0   断开设备成功
	/// \~english
	/// \brief disconnect camera
	/// release the control permission of camera, and distroy the control channel
	/// \param [in] thiz this pointer
	/// \retval < 0 disconnection failed
	/// \retval 0   disconnection successful
	int32_t (*disConnect)(struct GENICAM_Camera *thiz);
		
	/// \~chinese
	/// \brief 判断相机当前是否处于已连接状态
	/// \param [in] thiz 本接口指针
	/// \retval < 0 设备处于断开状态
	/// \retval 0   设备处于连接状态
	/// \~english
	/// \brief check the camera is connected or not
	/// \param [in] thiz this pointer
	/// \retval < 0 camera is disconnected
	/// \retval 0   camera is connected
	int32_t (*isConnected)(struct GENICAM_Camera *thiz);
		      								
	/// \~chinese
	/// \brief  获取相机所属的接口名
	/// \param [in] thiz 本接口指针
	/// \return 成功返回设备所属的接口名，否则返回NULL
	/// \~english
	/// \brief  get the name of interface whice is connect to camera
	/// \param [in] thiz this pointer
	/// \return Success:Interface Name, Failure:NULL
	const char* (*getInterfaceName)(struct GENICAM_Camera *thiz);

	/// \~chinese
	/// \brief  获取相机所连接的接口类型
	/// \param [in] thiz 本接口指针
	/// \return 返回相机所连接的接口类型
	/// \~english
	/// \brief  get the type of interface which is connect to camera
	/// \param [in] thiz  this pointer
	/// \return the type of interface
	int32_t (*getInterfaceType)(struct GENICAM_Camera *thiz);
	
	/// \~chinese
	/// \brief 下载相机描述XML文件
	/// 下载相机描述文件，并保存到指定路径
	/// \param [in] thiz 本接口指针
	/// \param [in] aFullFilename 文件要保存的路径
	/// \retval < 0 下载XML失败
	/// \retval 0   下载XML成功
	/// \~english
	/// \brief download camera discription XML file
	/// download camera discription file, and save the file to specified path
	/// \param [in] thiz this pointer
	/// \param [in] aFullFilename full path name of the downloaded xml file
	/// \retval < 0 download failed
	/// \retval 0   download successful
	int32_t (*downLoadGenICamXML)(struct GENICAM_Camera *thiz,const char* aFullFilename);

	/// \~chinese
	/// \brief 获取相机制造厂商名称
	/// \param [in] thiz 本接口指针
	/// \return 返回厂商名称
	/// \~english
	/// \brief get camera's vendor
	/// \param [in] thiz this pointer
	/// \return camera's vendor, return NULL if failed
	const char* (*getVendorName)(struct GENICAM_Camera *thiz);
	
	/// \~chinese
	/// \brief 获取相机的型号
	/// \param [in] thiz 本接口指针
	/// \return 返回相机型号
	/// \~english
	/// \brief get camera's model name
	/// \param [in] thiz this pointer
	/// \return camera's model name, return NULL if failed
	const char* (*getModelName)(struct GENICAM_Camera *thiz);

	/// \~chinese
	/// \brief 获取相机的序列号
	/// \param [in] thiz 本接口指针
	/// \return 返回相机的序列号
	/// \~english
	/// \brief get camera's serial number
	/// \param [in] thiz this pointer
	/// \return camera's serial number, return NULL if failed
	const char* (*getSerialNumber)(struct GENICAM_Camera *thiz);
	
	uint32_t		reserved[17];	///< \~chinese 保留  	///< \~english reserved field
}GENICAM_Camera;
/// @}


/// \~chinese
/// \brief 发现设备、创建常用属性对象
/// \defgroup System 设备发现、属性常用对象创建和事件订阅对象创建接口
/// \~english
/// \brief discover camera, and create common property instance
/// \defgroup System discover camera, create common property instance
/// @{
/// \~chinese
/// 全局单例系统对象
/// 32位系统下128字节
/// \~english
/// Global singleton system object
/// 128 bytes in 32-bit system
typedef struct GENICAM_System
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;
	
	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t	(*addRef)(struct GENICAM_System *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_System *thiz);
	
	/// \~chinese
	/// \brief 发现指定接口类型可达的设备
	/// \param [in] thiz 本接口指针
	/// \param [out] ppCameraList 指定接口类型所有在线设备对象列表,该内存在函数内部申请，但需外部传入一个一维指针有效地址指向该设备列表
	/// \param [out] pCameraCnt  发现的设备个数
	/// \param [in]  interfaceType  接口类型，当传入的是typeAll时，表示目前所有已支持的协议类型设备都会被发现
	/// \retval < 0 发现设备失败
	/// \retval 0   发现设备成功
	/// \~english
	/// \brief discover camera with specified interface type
	/// \param [in] thiz this pointer
	/// \param [out] ppCameraList camera instance list of specified interface type. memory is allocated in the function, but need a pointer which point to the camera list as a input parameter.
	/// \param [out] pCameraCnt  the count of discovered camera
	/// \param [in]  interfaceType  interface type.when "typeAll" specified, all supported protocol type camera will be discovered
	/// \retval < 0 discovery failed
	/// \retval 0   discovery successful
	int32_t (*discovery)(struct GENICAM_System *thiz, GENICAM_Camera **ppCameraList, uint32_t *pCameraCnt, GENICAM_EProtocolType interfaceType);
	
	/// \~chinese
	/// \brief 根据相机的key获取 Camera 对象指针
	/// \param [in] thiz 本接口指针
	/// \param [in] pCameraKey 相机的key
	/// \return 返回Camera指针,若传入的pCameraKey不存在或者非法，则返回空指针
	/// \~english
	/// \brief get the pointer of camera instance by camera key
	/// \param [in] thiz this pointer
	/// \param [in] pCameraKey camera key
	/// \return Success:camera pointer, Failure:NULL
	GENICAM_Camera* (*getCamera)(struct GENICAM_System *thiz,const char * pCameraKey);

	/// \~chinese
	/// \brief 获取版本信息
	/// \param [in] thiz 本接口指针
	/// \return 版本信息，失败时返回NULL
	/// \~english
	/// \brief get version info
	/// \param [in] thiz this pointer
	/// \return Success:version info, Failure:NULL
	const char* (*getVersion)(struct GENICAM_System *thiz);
	
	uint32_t		reserved[26];	///< 保留	///< \~english reserved field
}GENICAM_System;

/// \~chinese
/// 创建系统对象，全局唯一
///
/// \param [out] ppSystem 输出参数，返回的是系统对象的指针
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create system object, Globally unique
///
/// \param [out] ppSystem output parameter, return pointer of the system object
/// \retval < 0 create failed
/// \retval 0   create successful
GENICAM_API int32_t  CALL_METHOD GENICAM_getSystemInstance(GENICAM_System** ppSystem);
/// @}


/// \~chinese
/// \brief 数据帧对象接口
/// \defgroup Frame 数据帧操作接口
/// \~english 
/// \brief data frame object interface
/// \brief data frame operation interface
/// @{
typedef enum GENICAM_EPayloadType
{
	payloadImage = 1,	            ///< \~chinese 图片         \~english Image
	payloadRawdata,					///< \~chinese 裸数据       \~english Raw Data
	payloadFile,					///< \~chinese 文件         \~english File
	payloadChunkData,				///< \~chinese 块数据       \~english Chunk Data
	payloadExtChunkData,			///< \~chinese 扩展块数据   \~english Ext Chunk Data
	payloadDevSpecBase = 0x8000,    ///< \~chinese 设备特有     \~english Device specific payload type
	payloadUndefined				///< \~chinese 未定义		\~english Undefined
}GENICAM_EPayloadType;

/// \~chinese
///数据帧对象
/// 32位系统下128字节
/// \~english
/// data frame object
/// 128 bytes in 32-bit system
typedef struct GENICAM_Frame
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 帧深拷贝克隆接口
	/// \param [in] thiz 本接口指针
	/// \return 新的一帧对象
	/// \~english
	/// \brief frame deep copy clone interface
	/// \return new frame object
	struct GENICAM_Frame* (*clone)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 外面不使用时需要调用此接口释放Image相关内存
	/// \param [in] thiz 本接口指针
	/// \return none
	/// \~english
	/// \brief call this interface to free Image memory when no used externally
	/// \param [in] thiz this pointer
	/// \return none
	void (*reset)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// brief 是否有效
	/// \param [in] thiz 本接口指针
	/// \retval < 0 该帧无效
	/// \retval 0   该帧有效
	/// \~english
	/// brief check frame valid or not
	/// \param [in] thiz this pointer
	/// \retval < 0 frame invalid
	/// \retval 0   frame valid
	int32_t (*valid)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取该帧图片数据的内存首地址
	/// \param [in] thiz 本接口指针
	/// \return 返回该帧图片数据的内存首地址
	/// \~english
	/// \brief get the data's address of frame image in memory  
	/// \param [in] thiz this pointer
	/// \return the data's address of frame image in memory  
	const void* (*getImage)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取数据帧状态
	/// \param [in] thiz 本接口指针
	/// \return 返回数据帧状态
	/// \~english
	/// \brief get the data frame status
	/// \param [in] thiz this pointer
	/// \return the data frame status
	uint32_t (*getFrameStatus)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取图片宽度
	/// \param [in] thiz 本接口指针
	/// \return 返回图片宽度，失败时为0
	/// \~english
	/// \brief get the width of image
	/// \param [in] thiz this pointer
	/// \return the width of image, return 0 when failed
	uint32_t (*getImageWidth)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取图片高度
	/// \param [in] thiz 本接口指针
	/// \return 返回图片高度，失败时为0
	/// \~english 
	/// \brief get the height of image
	/// \param [in] thiz this pointer
	/// \return the height of image, return 0 when failed
	uint32_t (*getImageHeight)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取图片大小
	/// \param [in] thiz 本接口指针
	/// \return 返回图片大小，失败时为0
	/// \~english
	/// \brief get the size of image
	/// \param [in] thiz this pointer
	/// \return the size of image, return 0 when failed
	uint32_t (*getImageSize)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取图片像素格式
	/// \param [in] thiz 本接口指针
	/// \return 返回图片像素格式
	/// \~english
	/// \brief get image pixel format
	/// \param [in] thiz this pointer
	/// \return image pixel format
	enum EPixelType (*getImagePixelFormat)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取图片时间戳
	/// \param [in] thiz 本接口指针
	/// \return 返回图片时间戳，失败时为0
	/// \~english
	/// \brief get image time stamp
	/// \param [in] thiz this pointer
	/// return image time stamp, return 0 when failed
	uint64_t (*getImageTimeStamp)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取图片对应的BlockId
	/// \param [in] thiz 本接口指针
	/// \return 返回图片对应的BlockId，失败时为0
	/// \~english
	/// \brief get the image's block ID
	/// \param [in] thiz this pointer
	/// \return the image's block ID, return 0 when failed 
	uint64_t (*getBlockId)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取当前帧数据净荷类型
	/// \param [in] thiz 本接口指针
	/// \param [in/out] pPayloadTypeList 当前帧数据类型种类集，最大种类不超过MAX_PAYLOAD_TYPE_CNT，该内存外部分配
	/// \param [in/out] pTypeCnt 入参时为数组的实际长度;出参时为当前帧数据类型的实际个数，最大不超过20
	/// \return 返回当前帧数据净荷类型
	/// \~english
	/// \brief get pay load type of current frame
	/// \param [in] thiz this pointer
	/// \param [in/out] pPayloadTypeList pay load type list of current frame, maximum type can't surpass MAX_PAYLOAD_TYPE_CNT, this memory allocated by	external
	/// \param [in/out] pTypeCnt the size of array when input;the number of the current frame's data types when output, maximum type can't surpass 20
	/// \return pay load type of current frame
	int32_t(*getPayLoadTypes)(struct GENICAM_Frame *thiz, GENICAM_EPayloadType aPayloadTypeList[MAX_PAYLOAD_TYPE_CNT], uint32_t *pTypeCnt);

	/// \~chinese
	/// \brief 获取Buffer中包含的Chunk个数
	/// \param [in] thiz 本接口指针
	/// \return Chunk个数
	/// \~english
	/// \brief get the number of chunk in buffer
	/// \param [in] thiz this pointer
	/// \return the number of chunk
	uint32_t (*getChunkCount)(struct GENICAM_Frame *thiz);

	/// \~chinese
	/// \brief 获取Chunk数据
	/// \param [in] thiz 本接口指针
	/// \param [in] aIndex 索引ID
	/// \param [out] pID ChunkID
	/// \param [in/out] aRefParamList Chunk数据对应的属性名,该内存外部分配，接口约定ChunkID对应的参数列表最大不超过MAX_PARAM_CNT个，每个属性的字符长度不超过MAX_STRING_LENTH。
	/// \param [in/out] pParamCnt Chunk对应的属性个数，入参时为最大的参数个数，出参时为实际的参数个数
	/// \return 是否成功
	/// \~english
	/// \brief get chunk data
	/// \param [in] thiz this pointer
	/// \param [in] aIndex index ID
	/// \param [out] pID ChunkID
	/// \param [in/out] aRefParamList Chunk data's property name, this memory allocated by	external, Chunk ID's property list can't surpass MAX_PARAM_CNT, each property's characters can't surpass MAX_STRING_LENTH
	/// \param [in/out] pParamCnt the number of chunk's property, maximum parameter's number when input, real parameter's number when output
	/// \return success or fail
	int32_t (*getChunkDataByIndex)(struct GENICAM_Frame *thiz,uint32_t aIndex, uint32_t *pID,
		char aRefParamList[MAX_PARAM_CNT][MAX_STRING_LENTH], uint32_t *pParamCnt);

	uint32_t  reserved[15];	///< \~chinese 保留  	///< \~english reserved field
}GENICAM_Frame;
/// @}


/// \~chinese
/// \brief 流对象接口类
/// \defgroup stream 流对象操作接口
/// \~english
/// \brief stream object interface class
/// \defgroup stream stream object operation interface 
/// @{
typedef enum  GENICAM_EGrabStrategy
{
	grabStrartegySequential = 0,	///< \~chinese 按到达顺序处理图片	///< \~english The images are processed in the order of their arrival
	grabStrartegyLatestImage = 1,   ///< \~chinese 获取最新的图片		///< \~english get latest image
	grabStrartegyUndefined   		///< \~chinese 未定义				///< \~english undefined
}GENICAM_EGrabStrategy;

/// \~chinese
/// \brief 设备流回调函数声明:每次回调送出一帧数据
/// GENICAM_Frame 回调时主动推送的帧对象,外部用完该帧后需要释放
/// \~english
/// \brief frame invoke function defination : every time get a frame, this function will be invoked
/// GENICAM_Frame frame instance. invoke function must release the frame instance when finish using it.
typedef void(*callbackFun)(GENICAM_Frame* pFrame);

/// \~chinese
/// \brief GENICAM_StreamSource 流对象
/// 32位系统下128字节
/// \~english
/// \brief GENICAM_StreamSource stream object
/// 128 bytes in 32-bit system
typedef struct GENICAM_StreamSource
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_StreamSource *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_StreamSource *thiz);

	/// \~chinese
	/// \brief 开始抓图
	/// \param [in] thiz 本接口指针
	/// \param [in] maxImagesGrabbed 允许最多的抓图数，达到指定抓图数后停止抓图，如果为0，表示忽略此参数，会连续抓图
	/// \param [in] strategy 抓图策略
	/// \return 返回抓图是否成功，0表示成功，-1表示失败
	/// \~english
	/// \brief start grab image
	/// \param [in] thiz this pointer
	/// \param [in] maxImagesGrabbed allowed maximum number of grab images,stop grab image when arrive maxImagesGrabbed, if parameter is 0, ignore this parameter and grab image continuous
	/// \param [in] strategy grab strategy
	/// \return success:0, fail:-1
	int32_t (*startGrabbing)(struct GENICAM_StreamSource *thiz, uint64_t maxImagesGrabbed, GENICAM_EGrabStrategy strategy);

	/// \~chinese
	/// \brief 停止抓图
	/// \param [in] thiz 本接口指针
	/// \return 返回停止抓图是否成功，0表示成功，-1表示失败	
	/// \~english
	/// \brief stop grab image
	/// \param [in] thiz this pointer
	/// \return success:0, fail:-1
	int32_t (*stopGrabbing)(struct GENICAM_StreamSource *thiz);

	/// \~chinese
	/// \brief 是否正在抓图
	/// \param [in] thiz 本接口指针
	/// \return 返回是否处于拉流状态，0表示处于拉流状态，-1表示非拉流状态
	/// \~english 
	/// \brief whether grabbing image 
	/// \param [in] thiz this pointer
	/// \return grabbing or not grabbing, 0 means is grabbing, -1 means is not grabbing
	int32_t (*isGrabbing)(struct GENICAM_StreamSource *thiz);

	/// \~chinese
	/// \brief 获取一帧图像，该接口不支持多线程调用
	/// \param [in] thiz 本接口指针
	/// \param [out] ppFrame 一帧图像,内存由函数内部分配，用完该帧后需要显示调用GENICAM_Frame release接口显示释放
	/// \param [in]  timeoutMS 获取一帧图像的超时时长,单位MS,当值为INFINITE时表示无限等待
	/// \return 返回是否成功，0表示成功，-1表示失败
	/// \~english
	/// \brief get a frame image, and this interface non support multi-threading
	/// \param [in] thiz this pointer
	/// \param [out] ppFrame a frame image, memory by allocated in function, call GENICAM_Frame release free memory when use up the frame image
	/// \param [in]  timeoutMS the time out of get a frame image, unit is millisecond, wait forever when value is INFINITE 
	/// \return success:0, fail:-1
	int32_t (*getFrame)(struct GENICAM_StreamSource *thiz, GENICAM_Frame **ppFrame, uint32_t timeoutMS);

	/// \~chinese
	/// \brief 注册数据帧回调函数。该异步获取帧机制和同步获取帧机制互斥，系统中两者只能选其一。
	/// \brief 只能处理一个回调函数
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 数据帧回调函数，建议不要在该函数中处理耗时的操作，否则会阻塞后续数据帧的实时性
	/// \return 返回注册是否成功，0表示成功，-1表示失败
	/// \~english
	/// \brief register data frame callback function, the asynchronous method oppose the synchronization method, system just choose one of them   
	/// \brief only callback one function 
	/// \param [in] thiz this pointer
	/// \param [in] proc data frame callback function,suggest don't process time-consuming operation, because it will block the follow-up data frame 
	/// \return success:0, fail:-1
	int32_t (*attachGrabbing)(struct GENICAM_StreamSource *thiz, callbackFun proc);

	/// \~chinese
	/// \brief 去注册数据帧回调函数
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 去注册数据帧回调函数
	/// \return 返回去注册是否成功，0表示成功，-1表示失败
	/// \~english
	/// \brief	register data frame callback function
	/// \param [in] thiz this pointer
	/// \param [in] proc register data frame callback function
	/// \return success:0, fail:-1
	int32_t (*detachGrabbing)(struct GENICAM_StreamSource *thiz, callbackFun proc);

	uint32_t  reserved[23];	///< \~chinese 保留  	///< \~english reserved field

}GENICAM_StreamSource;

/// \~chinese
/// 流对象参数
/// 32位系统下128字节
/// \~english
/// stream object parameter
/// 128 bytes in 32-bit system
typedef struct GENICAM_StreamSourceInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象		///< \~english camera object
	uint32_t channelId;         ///< \~chinese 通道号		///< \~english number of channel
	uint32_t reserved[30];	    ///< \~chinese 保留			///< \~english reserved field
} GENICAM_StreamSourceInfo;

/// \~chinese
/// 创建流通道对象，该对象由外部调用该接口创建，释放时调用release接口
///
/// \param [in] pStreamSourceInfo 创建流对象的参数
/// \param [out] ppStreamSource   返回的流对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create stream channel object, this object create by external call, call release interface free it
/// \param [in] pStreamSourceInfo create parameter of stream object
/// \param [out] ppStreamSource   return stream object
/// \retval < 0 create failed
/// \retval 0   create successful
GENICAM_API int32_t CALL_METHOD GENICAM_createStreamSource(const GENICAM_StreamSourceInfo* pStreamSourceInfo
										, GENICAM_StreamSource** ppStreamSource);
										
/// @}


typedef enum EVType
{
	offLine,   ///< \~chinese 设备离线通知    ///< \~english camera offline notification
	onLine     ///< \~chinese 设备在线通知    ///< \~english camera online notification
}EVType;

/// \~chinese
/// \brief 事件注册回调对象接口类
/// \defgroup Event 相机事件订阅注册与去注册接口
/// \~english
/// \brief event register callback function interface class
/// \defgroup Event register camera event subscription and register interface 
/// @{
/// \~chinese
/// 连接事件参数封装
/// \~english
/// connection event parameters encapsulation
typedef struct GENICAM_SConnectArg
{
	EVType m_event;  		///< \~chinese 事件类型    ///< \~english event type
	uint32_t reserve[15]; 	///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_SConnectArg;

/// \~chinese
/// 参数更新事件参数封装
/// \~english
/// parameters updating event encapsulation
typedef struct GENICAM_SParamUpdataArg
{
	int32_t isPoll; 					                 ///< \~chinese 是否是定时更新,1表示是定时更新，0表示非定时更新   ///< \~english update periodically or not. 1 : update periodically, 0 : not update periodically
	uint32_t reserve[10];		                         ///< \~chinese 预留字段                 ///< \~english reserved field
	char paramNames[MAX_PARAM_CNT][MAX_STRING_LENTH];    ///< \~chinese 更新的参数名称集合,约定更新的参数不超过1000个，每个参数的字符串长度不超过256  ///< \~english array of parameter's name which need to update. the array's max size is 1000. and the max length of parameter's name is 255.
	uint32_t referenceParamCnt;                          ///< \~chinese 更新的参数个数           ///< \~english the count of parameter which need to update
}GENICAM_SParamUpdataArg;

/// \~chinese
///枚举：流事件状态
/// \~english
/// enumeration:stream event status
typedef enum GENICAM_EEventStatus
{
	streamEventNormal = 1,      ///< \~chinese 正常流事件		///< \~english normal stream event
	streamEventLostFrame = 2,   ///< \~chinese 丢帧事件		    ///< \~english lost frame event
	streamEventLostPacket = 3,  ///< \~chinese 丢包事件		    ///< \~english lost packet event
	streamEventImageError       ///< \~chinese 图像错误事件		///< \~english error image event
}GENICAM_EEventStatus;

/// \~chinese
/// 流事件参数封装
/// \~english
/// stream event parameters encapsulation
typedef struct GENICAM_SStreamArg
{
	uint32_t     channel;					 ///< \~chinese 流通道号         ///< \~english channel no.
	uint64_t     blockID;					 ///< \~chinese 流数据BlockID    ///< \~english block ID
	uint64_t     timestamp;					 ///< \~chinese 时间戳           ///< \~english event timestamp
	GENICAM_EEventStatus eStreamEventStatus; ///< \~chinese 流事件状态码     ///< \~english stream event status
	uint32_t	 status;					 ///< \~chinese 事件状态错误码   ///< \~english status error no.
	uint32_t reserve[9];					 ///< \~chinese 预留字段         ///< \~english reserved field
}GENICAM_SStreamArg;

/// \~chinese
/// \brief 设备连接状态事件回调函数声明
/// \~english
/// \brief camera connection status event call back function declaration
typedef void (*connectCallBack)(const GENICAM_SConnectArg* pConnectArg);

/// \~chinese
/// \brief 参数更新事件回调函数声明
/// \~english
/// \brief camera parameter update event call back function declaration
typedef void (*paramUpdateCallBack)(const GENICAM_SParamUpdataArg* pParamUpdateArg);

/// \~chinese
/// \brief 设备流事件回调函数声明
/// \~english
/// \brief stream event call back function declaration
typedef void (*streamCallBack)(const GENICAM_SStreamArg* pStreamArg);

/// \~chinese
/// 事件订阅对象
/// 32位系统下128字节
/// \~english
/// event subscribe object
/// 128 bytes in 32-bit system
typedef struct GENICAM_EventSubscribe
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t(*addRef)(struct GENICAM_EventSubscribe *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t(*release)(struct GENICAM_EventSubscribe *thiz);

	/// \~chinese
	/// \brief  设备连接状态事件回调注册,只支持一个回调函数有效
	/// \param [in] thiz 本接口指针
	/// \param [in] proc  设备连接状态事件回调注册函数
	/// \return 注册是否成功
	/// \~english
	/// \brief  regist call back function of camera connection status event. only one call back function is supported.
	/// \param [in] thiz this pointer
	/// \param [in] proc  call back function of camera connection status event
	/// \return the result of registration
	int32_t(*subscribeConnectArgs)(struct GENICAM_EventSubscribe *thiz, const connectCallBack proc);

	/// \~chinese
	/// \brief  设备连接状态事件回调去注册
	/// \param [in] thiz 本接口指针
	/// \param [in] proc  设备连接状态事件回调去注册函数
	/// \return 去注册是否成功
	/// \~english
	/// \brief  unregist call back function of camera connection status event.
	/// \param [in] thiz this pointer
	/// \param [in] proc  call back function of camera connection status event
	/// \return the result of unregistration
	int32_t(*unsubscribeConnectArgs)(struct GENICAM_EventSubscribe *thiz, const connectCallBack proc);

	/// \~chinese
	/// \brief  参数更新事件回调注册,只支持一个回调函数有效
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 参数更新注册的事件回调函数
	/// \return 注册是否成功
	/// \~english
	/// \brief  regist call back function of parameter update event. only one call back function is supported.
	/// \param [in] thiz this pointer
	/// \param [in] proc  call back function of parameter update event
	/// \return the result of registration
	int32_t (*subscribeParamUpdate)(struct GENICAM_EventSubscribe *thiz, const paramUpdateCallBack proc);

	/// \~chinese
	/// \brief  参数更新事件回调去注册
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 参数更新事件去注册的回调函数
	/// \return 去注册是否成功
	/// \~english
	/// \brief  unregist call back function of parameter update event.
	/// \param [in] thiz this pointer
	/// \param [in] proc  call back function of parameter update event
	/// \return the result of unregistration
	int32_t (*unsubscribeParamUpdate)(struct GENICAM_EventSubscribe *thiz, const paramUpdateCallBack proc);

	/// \~chinese
	/// \brief  流通道事件回调注册,只支持一个回调函数有效
	/// \param [in] thiz 本接口指针
	/// \param [in] proc 流通道事件回调注册函数
	/// \return 注册是否成功
	/// \~english
	/// \brief  regist call back function of stream channel event. only one call back function is supported.
	/// \param [in] thiz this pointer
	/// \param [in] proc  call back function of tream channel event
	/// \return the result of registration
	int32_t (*subscribeStreamArg)(struct GENICAM_EventSubscribe *thiz, const streamCallBack proc);

	/// \~chinese
	/// \brief  流通道事件回调去注册
	/// \param [in] thiz 本接口指针
	/// \param [in] proc  流通道事件回调去注册函数
	/// \return 去注册是否成功
	/// \~english
	/// \brief  unregist call back function of stream channel event.
	/// \param [in] thiz this pointer
	/// \param [in] proc  call back function of tream channel event
	/// \return the result of unregistration
	int32_t (*unsubscribeStreamArg)(struct GENICAM_EventSubscribe *thiz, const streamCallBack proc);

	uint32_t reserve[23];					 ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_EventSubscribe;

/// \~chinese
/// 事件订阅对象参数
/// 32位系统下128字节
/// \~english
/// event subscribe info object
/// 128 bytes in 32-bit system
typedef struct GENICAM_EventSubscribeInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_EventSubscribeInfo;

/// \~chinese
/// 创建事件订阅对象
/// \param [in] pEventSubscribeInfo  创建事件订阅对象的参数
/// \param [out] ppEventSubscribe    返回的事件订阅对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create event subscribe object
/// \param [in] pEventSubscribeInfo  event subscribe info object
/// \param [out] ppEventSubscribe    event subscribe object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t  CALL_METHOD GENICAM_createEventSubscribe(const GENICAM_EventSubscribeInfo* pEventSubscribeInfo,
													GENICAM_EventSubscribe** ppEventSubscribe);
/// @}


/// \~chinese
/// \brief 相机对象接口类
/// \defgroup GigECamera  GigE相机对象操作接口
/// \~english
/// \brief	camera object interface class
/// \defgroup GigECamera  GigECamera object operation interface
/// @{
/// \~chinese													
/// \brief GiGE相机特殊接口
/// 32位系统下128字节
/// \~english
/// \brief GigE camera object
/// 128 bytes in 32-bit system
typedef struct GENICAM_GigECamera
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t(*addRef)(struct GENICAM_GigECamera *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t(*release)(struct GENICAM_GigECamera *thiz);

	/// \~chinese
	/// \brief 获取相机的ipAddress
	/// \param [in] thiz 本接口指针
	/// \return 返回ipAddress 相机的IP地址，失败返回NULL
	/// \~english
	/// \brief	get camera's ipAddress
	/// \param [in] thiz this pointer
	/// \return return camera's ipAddress, return NULL if failed 
	const char* (*getIpAddress)(struct GENICAM_GigECamera *thiz);

	/// \~chinese
	/// \brief 返回相机的子网掩码
	/// \param [in] thiz 本接口指针
	/// \return 返回subnetMask 相机的子网掩码，失败返回NULL
	/// \~english
	/// \brief return camera's subnetMask
	/// \param [in] thiz this pointer
	/// \return camera's subnetMask, return NULL if failed
	const char* (*getSubnetMask)(struct GENICAM_GigECamera *thiz);

	/// \~chinese
	/// \brief 返回相机的网关
	/// \param [in] thiz 本接口指针
	/// \return 返回 subsetMask 相机的网关，失败返回NULL
	/// \~english
	/// \brief return camera's gateway
	/// \param [in] thiz this pointer
	/// \return camera's gateway, return NULL if failed
	const char*  (*getGateway)(struct GENICAM_GigECamera *thiz);

	/// \~chinese
	/// \brief 获取相机的 macAddress
	/// \param [in] thiz 本接口指针
	/// \return 返回macAddress 相机的Mac地址，失败返回NULL
	/// \~english
	/// \brief get camera's macAddress
	/// \param [in] thiz this pointer
	/// \return camera's macAddress, return NULL if failed
	const char*  (*getMacAddress)(struct GENICAM_GigECamera *thiz);

	/// \~chinese
	/// \brief  修改设备IP	
	/// \brief 1、调用该函数时如果newSubnetMask和newGateway都设置了有效值，则以此有效值为准;
	/// \brief 2、调用该函数时如果newSubnetMask和newGateway都设置了NULL，则内部实现时用它所连接网卡的子网掩码和网关代替
	/// \brief 3、调用该函数时如果newSubnetMask和newGateway两者中其中一个为NULL，另一个非NULL，则返回失败
	/// \brief 该接口只针对通过网卡接入的设备，对于其余设备，调用此接口无意义，直接返回失败
	/// \param [in] thiz 本接口指针
	/// \param [in] newIpAddress 新的IP地址信息
	/// \param [in] newSubnetMask 新的掩码信息
	/// \param [in] newGateway 新的网关信息
	/// \retval < 0 修改IP失败
	/// \retval 0   修改IP成功
	/// \~english
	/// \brief  modify device IP	
	/// \brief 1、callback this function if newSubnetMask and newGateway's value are effective and the value is correct
	/// \brief 2、callback this function if newSubnetMask and newGateway's value are NULL and the value will be replaced by internal realise
	/// \brief 3、callback this function if newSubnetMask or newGateway's value is NULL, another one is not NULL, then return failed
	/// \brief the interface only aim at connect device by network card, as for other device, callback this function is meaningless and return failed
	/// \param [in] thiz this pointer
	/// \param [in] newIpAddress new ip address 
	/// \param [in] newSubnetMask new subnetMask
	/// \param [in] newGateway new Gateway
	/// \retval < 0 modify ip failed
	/// \retval 0   modify ip success
	int32_t (*forceIpAddress)(struct GENICAM_GigECamera *thiz,const char* newIpAddress, const char* newSubnetMask, const char* newGateway);

	uint32_t reserve[24];					 ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_GigECamera;

/// \~chinese
/// 创建GigECamera对象参数
/// 32位系统下128字节
/// \~english
/// create GigE camera object's info object
/// 128 bytes in 32-bit system
typedef struct GENICAM_GigECameraInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_GigECameraInfo;

/// \~chinese
/// 创建GiGE设备对象
/// \param [in] pGigECameraInfo 创建GiGE设备对象的参数
/// \param [out] ppGigECamera GigECamera 对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create GigE camera object
/// \param [in]  pGigECameraInfo GigE camera info object
/// \param [out] ppGigECamera    GigE camera object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createGigECamera(GENICAM_GigECameraInfo* pGigECameraInfo
													, GENICAM_GigECamera** ppGigECamera);
/// @}


/// \~chinese
/// \brief 相机对象接口类
/// \defgroup GigEInterface  连接GigE相机的接口对象操作接口
/// \~english
/// \brief camera object interface class
/// \defgroup GigEInterface  connect GigECamera's interface operation object interface
/// @{
typedef struct GENICAM_GigEInterface
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t(*addRef)(struct GENICAM_GigEInterface *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t(*release)(struct GENICAM_GigEInterface *thiz);

	/// \~chinese
	/// \param [in] thiz 本接口指针
	/// \return 返回网卡描述信息，失败返回NULL
	/// \~english
	/// \param [in] thiz this pointer
	/// \return return network card description information, return NULL if failed
	const char * (*getDescription)(struct GENICAM_GigEInterface *thiz);

	/// \~chinese
	/// \param [in] thiz 本接口指针
	/// \return 返回网卡的IP地址，失败返回NULL
	/// \~english
	/// \param [in] thiz this pointer
	/// \return return network card's IpAddress, return NULL if failed
	const char * (*getIpAddress)(struct GENICAM_GigEInterface *thiz);

	/// \~chinese
	/// \param [in] thiz 本接口指针
	/// \return 返回网卡的子网掩码，失败返回NULL
	/// \~english
	/// \param [in] thiz this pointer
	/// \return return subnetMask, return NULL if failed
	const char * (*getSubnetMask)(struct GENICAM_GigEInterface *thiz);

	/// \~chinese
	/// \brief 返回网卡的网关
	/// \param [in] thiz 本接口指针
	/// \return 返回网卡的网关，失败返回NULL
	/// \~english
	/// \brief return Gateway
	/// \param [in] thiz this pointer
	/// \return return Gateway, return NULL if failed
	const char * (*getGateway)(struct GENICAM_GigEInterface *thiz);

	/// \~chinese
	/// \param [in] thiz 本接口指针
	/// \return 返回网卡的Mac地址，失败返回NULL
	/// \~english
	/// \param [in] thiz this pointer
	/// \return return macAddress, return NULL if failed
	const char * (*getMacAddress)(struct GENICAM_GigEInterface *thiz);

	uint32_t reserve[24];					 ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_GigEInterface;

/// \~chinese
/// 创建GiGE设备接口对象参数
/// 32位系统下128字节
/// \~english
/// create GigE camera interface object 
/// 128 bytes in 32-bit system
typedef struct GENICAM_GigEInterfaceInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_GigEInterfaceInfo;

/// \~chinese
/// 创建GiGE设备接口对象
/// \param [in] pGigEInterfaceInfo 创建GiGE设备对象的参数
/// \param [out] ppGigEInterface GigE Camera 所连接的接口对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create GigE camera interface object
/// \param [in] pGigEInterfaceInfo parameter used to create GigE camera object
/// \param [out] ppGigEInterface interface ojbect which connect the GigE Camera
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createGigEInterface(GENICAM_GigEInterfaceInfo*pGigEInterfaceInfo
									, GENICAM_GigEInterface** ppGigEInterface);
/// @}


// 配置参数相关的接口

/// \~chinese
/// \brief 常用参数对象接口
/// \defgroup config 属性配置相关操作接口
/// \~english
/// \brief common parameter object interface
/// \defgroup config property configure operation interface 
/// @{

/// \~chinese
/// \brief Class IIntNode 整型属性操作类
/// 32位系统下128字节
/// \~english
/// \brief Class IIntNode integer property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_IntNode
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_IntNode *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_IntNode *thiz);

	/// \~chinese
	/// \brief 获取属性值
	/// \param [in] thiz 本接口指针
	/// \param [out] pVal 获取到的属性值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get property value
	/// \param [in] thiz this pointer
	/// \param [out] pVal the property value get
	/// \return success:0, fail:-1
	int32_t (*getValue)(struct GENICAM_IntNode *thiz, int64_t* pVal);

	/// \~chinese
	/// \brief 设置属性值
	/// \param [in] thiz 本接口指针
	/// \param [in] val 待设置的属性值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief set the property's value
	/// \param [in] thiz this pointer
	/// \param [in] val stand by set of property's value 
	/// \return success:0, fail:-1
	int32_t (*setValue)(struct GENICAM_IntNode *thiz, int64_t val);

	/// \~chinese
	/// \brief 获取属性可设最小值
	/// \param [in] thiz 本接口指针
	/// \param [out] pMinVal 获取到的属性最小值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get minimum property's value can be set up
	/// \param [in] thiz this pointer
	/// \param [out] pMinVal the minimum property's value
	/// \return success:0, fail:-1
	int32_t (*getMinVal)(struct GENICAM_IntNode *thiz, int64_t* pMinVal);

	/// \~chinese
	/// \brief 获取属性可设最大值
	/// \param [in] thiz 本接口指针
	/// \param [out] pMaxVal 获取到的属性最大值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get maximum property's value
	/// \param [in] thiz this pointer
	/// \param [out] pMaxVal the maximum property's value
	/// \return success:0, fail:-1
	int32_t (*getMaxVal)(struct GENICAM_IntNode *thiz, int64_t* pMaxVal);

	/// \~chinese
	/// \brief 判断属性是否有效
	/// \param [in] thiz 本接口指针
	/// \return 0表示有效，-1表示无效
	/// \~english
	/// \brief judge validity of the property
	/// \param [in] thiz this pointer
	/// \return valid:0, invalid:-1
	int32_t (*isValid)(struct GENICAM_IntNode *thiz);

	uint32_t reserve[24];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_IntNode;


/// \~chinese
/// 创建整数节点类型信息
/// 32位系统下128 + 1024 字节
/// \~english
/// create int node type's info
/// 128 + 1024  bytes in 32-bit system
typedef struct GENICAM_IntNodeInfo
{
	GENICAM_Camera* pCamera;	        ///< \~chinese 相机对象    ///< \~english camera object
	char attrName[MAX_ATTR_NAME_LEN];   ///< \~chinese 属性名称    ///< \~english attribute name
	uint32_t reserved[31];	            ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_IntNodeInfo;

/// \~chinese
/// 创建整数节点类型对象
/// \param [in] pIntNodeInfo 创建整数节点类型信息
/// \param [out] ppIntNode   整数类型对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create int node type object
/// \param [in]  pIntNodeInfo parameter used to create int node type object
/// \param [out] ppIntNode    integer node type object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createIntNode(GENICAM_IntNodeInfo* pIntNodeInfo
	, GENICAM_IntNode** ppIntNode);


/// \~chinese
/// \brief Class IDoubleNode 浮点数属性操作类
/// 32位系统下128字节
/// \~english
/// \brief Class IDoubleNode float property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_DoubleNode
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_DoubleNode *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_DoubleNode *thiz);

	/// \~chinese
	/// \brief 获取属性值
	/// \param [in] thiz 本接口指针
	/// \param [out] pVal 获取到的属性值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get property's value
	/// \param [in] thiz this pointer
	/// \param [out] pVal the property's value
	/// \return success:0, fail:-1
	int32_t (*getValue)(struct GENICAM_DoubleNode *thiz, double* pVal);

	/// \~chinese
	/// \brief 设置属性值
	/// \param [in] thiz 本接口指针
	/// \param [in] val 待设置的属性值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief set property's value
	/// \param [in] thiz this pointer
	/// \param [in] val stand by set property's value
	/// \return success:0, fail:-1
	int32_t (*setValue)(struct GENICAM_DoubleNode *thiz, double val);

	/// \~chinese
	/// \brief 获取属性可设最小值
	/// \param [in] thiz 本接口指针
	/// \param [out] pMinVal 获取到的属性最小值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get minimum property's value can be set up
	/// \param [in] thiz this pointer
	/// \param [out] pMinVal the minimum property's value
	/// \return success:0, fail:-1
	int32_t (*getMinVal)(struct GENICAM_DoubleNode *thiz, double* pMinVal);

	/// \~chinese
	/// \brief 获取属性可设最大值
	/// \param [in] thiz 本接口指针
	/// \param [out] pMaxVal 获取到的属性最大值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get maximum property's value
	/// \param [in] thiz this pointer
	/// \param [out] pMaxVal the maximum property's value
	/// \return success:0, fail:-1
	int32_t (*getMaxVal)(struct GENICAM_DoubleNode *thiz, double* pMaxVal);

	/// \~chinese
	/// \brief 判断属性是否有效
	/// \param [in] thiz 本接口指针
	/// \return 0表示有效，-1表示无效
	/// \~english
	/// \brief judge validity of the property
	/// \param [in] thiz this pointer
	/// \return valid:0, invalid:-1
	int32_t (*isValid)(struct GENICAM_DoubleNode *thiz);

	uint32_t reserve[24];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_DoubleNode;


/// \~chinese
/// 创建浮点数节点类型信息
/// 32位系统下128 + 1024 字节
/// \~english
/// create double node type's info
/// 128 + 1024 bytes in 32-bit system
typedef struct GENICAM_DoubleNodeInfo
{
	GENICAM_Camera* pCamera;	        ///< \~chinese 相机对象    ///< \~english camera object
	char attrName[MAX_ATTR_NAME_LEN];   ///< \~chinese 属性名称    ///< \~english attribute name
	uint32_t reserved[31];	            ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_DoubleNodeInfo;

/// \~chinese
/// 创建浮点数节点类型对象
/// \param [in]  pDoubleNodeInfo 创建浮点数节点类型信息
/// \param [out] ppDoubleNode   浮点数类型对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create double node type object
/// \param [in]  pDoubleNodeInfo parameter used to create double node type object
/// \param [out] ppDoubleNode       double node type object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createDoubleNode(GENICAM_DoubleNodeInfo* pDoubleNodeInfo
	, GENICAM_DoubleNode** ppDoubleNode);

/// \~chinese
/// \brief Class IEnumNode 枚举型属性操作类
/// 32位系统下128字节
/// \~english
/// \brief Class IEnumNode EnumNode property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_EnumNode
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_EnumNode *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_EnumNode *thiz);

	/// \~chinese
	/// \brief 获取枚举属性symbol值
	/// \param [in] thiz 本接口指针
	/// \param [in/out] pVal  获取到的属性值,约定字符串长度最大为256，该内存由外部分配
	/// \param [in/out] pMaxCnt 输入的字符串长度，出参时为实际的字符串长度
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get enum property symbol's value
	/// \param [in] thiz this pointer
	/// \param [in/out] pVal  the property's value that the length can't surpass 256, this memory allocated by external
	/// \param [in/out] pMaxCnt the length of input chars, real length of chars when output
	/// \return success:0, fail:-1
	int32_t (*getValueSymbol)(struct GENICAM_EnumNode *thiz, char* pVal, uint32_t *pMaxCnt);

	/// \~chinese
	/// \brief 设置枚举属性symbol值
	/// \param [in] thiz 本接口指针
	/// \param [in] strSymbolName 待设置的属性值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief set enum property symbol's value
	/// \param [in] thiz this pointer
	/// \param [in] strSymbolName stand by set property's value
	/// \return success:0, fail:-1
	int32_t (*setValueBySymbol)(struct GENICAM_EnumNode *thiz,const char* strSymbolName);

	/// \~chinese
	/// \brief 获取枚举属性可设置的symbol值列表
	/// \param [in] thiz 本接口指针
	/// \param [out] ppSymbolList  获取到的可设置的symbol值列表，字符长度最长为256
	/// \param [out] ppSymbolList  获取到的可设置的symbol个数,最多为1000个
	/// \return 返回属性当前可设置symbol值列表
	/// \~english
	/// \brief get enum property that can be set symbol's value list
	/// \param [in] thiz this pointer
	/// \param [out] ppSymbolList  get the symbol's value list, maximum length of chars is 256
	/// \param [out] ppSymbolList  the number of can be get the symbol's value list, maximum number is 1000
	/// \return return current property that can be set 
 	int32_t (*getEnumSymbolList)(struct GENICAM_EnumNode *thiz,char **ppSymbolList, uint32_t *pSymbolCnt);

	/// \~chinese
	/// \brief 判断属性是否有效
	/// \param [in] thiz 本接口指针
	/// \return 0表示有效，-1表示无效
	/// \~english
	/// \brief judge validity of the property
	/// \param [in] thiz this pointer
	/// \return valid:0, invalid:-1
	int32_t (*isValid)(struct GENICAM_EnumNode *thiz);

	uint32_t reserve[25];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_EnumNode;


/// \~chinese
/// 创建枚举节点类型信息
/// 32位系统下128 + 1024 字节
/// \~english
/// create enum node type's info
/// 128 + 1024 bytes in 32-bit system
typedef struct GENICAM_EnumNodeInfo
{
	GENICAM_Camera* pCamera;	        ///< \~chinese 相机对象    ///< \~english camera object
	char attrName[MAX_ATTR_NAME_LEN];   ///< \~chinese 属性名称    ///< \~english attribute name
	uint32_t reserved[31];	            ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_EnumNodeInfo;

/// \~chinese
/// 创建枚举节点类型对象
/// \param [in]  pEnumNodeInfo 创建枚举节点类型信息
/// \param [out] ppEnumNode    枚举类型对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create enum node type object
/// \param [in]  pEnumNodeInfo parameter used to create enum node type object
/// \param [out] ppEnumNode    enum node type object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createEnumNode(GENICAM_EnumNodeInfo* pEnumNodeInfo
	, GENICAM_EnumNode** ppEnumNode);


/// \~chinese
/// \brief Class IBoolNode 布尔型属性操作类
/// 32位系统下128字节
/// \~english
/// \brief Class IBoolNode BoolNode property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_BoolNode
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_BoolNode *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_BoolNode *thiz);

	/// \~chinese
	/// \brief 获取属性值
	/// \param [in] thiz 本接口指针
	/// \param [out] pVal 获取到的属性值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief get property's value
	/// \param [in] thiz this pointer
	/// \param [out] pVal property's value 
	/// \return success:0, fail:-1
	int32_t (*getValue)(struct GENICAM_BoolNode *thiz,uint32_t *pVal);

	/// \~chinese
	/// \brief 设置属性值
	/// \param [in] thiz 本接口指针
	/// \param [in] val 待设置的属性值
	/// \return 成功返回0，失败返回-1
	/// \~english
	/// \brief set the property
	/// \param [in] thiz this pointer
	/// \param [in] val stand by the set property
	/// \return success:0, fail:-1	
	int32_t (*setValue)(struct GENICAM_BoolNode *thiz, uint32_t val);

	/// \~chinese
	/// \brief 判断属性是否有效
	/// \param [in] thiz 本接口指针
	/// \return 0表示有效，-1表示无效
	/// \~english
	/// \brief judge validity of the property
	/// \param [in] thiz this pointer
	/// \return valid:0, invalid:-1
	int32_t (*isValid)(struct GENICAM_BoolNode *thiz);

	uint32_t reserve[26];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_BoolNode;


/// \~chinese
/// 创建布尔节点类型信息
/// 32位系统下128 + 1024 字节
/// \~english
/// create bool node type's info
/// 128 + 1024 bytes in 32-bit system
typedef struct GENICAM_BoolNodeInfo
{
	GENICAM_Camera* pCamera;	        ///< \~chinese 相机对象    ///< \~english camera object
	char attrName[MAX_ATTR_NAME_LEN];   ///< \~chinese 属性名称    ///< \~english attribute name
	uint32_t reserved[31];	            ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_BoolNodeInfo;

/// \~chinese
/// 创建布尔节点类型对象
/// \param [in]  pBoolNodeInfo 创建布尔节点类型信息
/// \param [out] ppBoolNode    布尔类型对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create Bool node type object
/// \param [in]  pBoolNodeInfo parameter used to create bool node type object
/// \param [out] ppBoolNode    bool node type object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createBoolNode(GENICAM_BoolNodeInfo* pBoolNodeInfo
	, GENICAM_BoolNode** ppBoolNode);


/// \~chinese
/// \brief GENICAM_CmdNode 命令型属性操作类
/// 32位系统下128字节
/// \~english
/// \brief GENICAM_CmdNode CmdNode property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_CmdNode
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_CmdNode *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_CmdNode *thiz);

	/// \~chinese
	/// \brief 执行命令类型属性
	/// \param [in] thiz 本接口指针
	/// \return 成功返回0，失败返回-1
	/// \~english 
	/// \brief execute command property
	/// \param [in] thiz this pointer
	/// \return success:0, fail:-1
	int32_t (*execute)(struct GENICAM_CmdNode *thiz);

	/// \~chinese
	/// \brief 判断属性是否有效
	/// \param [in] thiz 本接口指针
	/// \return 0表示有效，-1表示无效
	/// \~english
	/// \brief judge validity of the property
	/// \param [in] thiz this pointer
	/// \return valid:0, invalid:-1
	int32_t (*isValid)(struct GENICAM_CmdNode *thiz);

	uint32_t reserve[27];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_CmdNode;

/// \~chinese
/// 创建命令节点类型信息
/// 32位系统下128 + 1024 字节
/// \~english
/// create command node type's info
/// 128 + 1024 bytes in 32-bit system
typedef struct GENICAM_CmdNodeInfo
{
	GENICAM_Camera* pCamera;	        ///< \~chinese 相机对象    ///< \~english camera object
	char attrName[MAX_ATTR_NAME_LEN];   ///< \~chinese 属性名称    ///< \~english attribute name
	uint32_t reserved[31];	            ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_CmdNodeInfo;

/// \~chinese
/// 创建命令节点类型对象
/// \param [in]  pCmdNodeInfo 创建命令节点类型信息
/// \param [out] ppCmdNode    命令类型对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create command node type object
/// \param [in]  pCmdNodeInfo parameter used to create command node type object
/// \param [out] ppCmdNode    command node type object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createCmdNode(GENICAM_CmdNodeInfo* pCmdNodeInfo
	, GENICAM_CmdNode** ppCmdNode);


/// \~chinese
/// \brief GENICAM_StringNode string属性操作类
/// 32位系统下128字节
/// \~english
/// \brief GENICAM_StringNode string property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_StringNode
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_StringNode *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_StringNode *thiz);

	/// \~chinese
	/// \brief 获取属性值
	/// \param [in] thiz 本接口指针
	/// \param [in/out] pOutStr 获取到的属性值，约定字符最大长度为256,该内存由外部分配
	/// \param [in/out] pMaxCnt 入参时为输入内存的长度，出参时为实际的字符长度
	/// \return 成功返回0，否则-1
	/// \~english
	/// \brief get property's value
	/// \param [in] thiz this pointer
	/// \param [in/out] pOutStr the property's value that the length can't surpass 256, this memory allocated by external
	/// \param [in/out] pMaxCnt the length of input memory when input, real length of chars when output
	/// \return success:0, fail:-1	
	int32_t (*getValue)(struct GENICAM_StringNode *thiz,char*pOutStr,uint32_t *pMaxCnt);

	/// \~chinese
	/// \brief 设置属性值
	/// \param [in] thiz 本接口指针
	/// \param [in] pInStr 待输入的属性值
	/// \return 成功则返回0，否则返回-1
	/// \~english
	/// \brief set the property
	/// \param [in] thiz this pointer
	/// \param [in] pInStr stand by the input property
	/// \return success:0, fail:-1	
	int32_t (*setValue)(struct GENICAM_StringNode *thiz, const char *pInStr);

	/// \~chinese
	/// \brief 判断属性是否有效
	/// \param [in] thiz 本接口指针
	/// \return 0表示有效，-1表示无效
	/// \~english
	/// \brief judge validity of the property
	/// \param [in] thiz this pointer
	/// \return valid:0, invalid:-1
	int32_t (*isValid)(struct GENICAM_StringNode *thiz);

	uint32_t reserve[26];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_StringNode;


/// \~chinese
/// 创建字符串节点类型信息
/// 32位系统下128 + 1024 字节
/// \~english
/// create string node type's info
/// 128 + 1024 bytes in 32-bit system
typedef struct GENICAM_StringNodeInfo
{
	GENICAM_Camera* pCamera;	        ///< \~chinese 相机对象    ///< \~english camera object
	char attrName[MAX_ATTR_NAME_LEN];   ///< \~chinese 属性名称    ///< \~english attribute name
	uint32_t reserved[31];	            ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_StringNodeInfo;

/// \~chinese
/// 创建字符串节点类型对象
/// \param [in]  pStringNodeInfo 创建字符串节点类型信息
/// \param [out] ppStringNode    字符串类型对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create string node type object
/// \param [in]  pStringNodeInfo parameter used to create string node type object
/// \param [out] ppStringNode    string node type object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createStringNode(GENICAM_StringNodeInfo* pStringNodeInfo
	, GENICAM_StringNode** ppStringNode);



/// \~chinese
/// \brief AcquisitionControl下属性操作类
/// \~english
/// \brief AcquisitionControl's property operation class
typedef struct GENICAM_AcquisitionControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t(*addRef)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t(*release)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取AcquisitionFrameCount属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get AcquisitionFrameCount's property operation class
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*acquisitionFrameCount)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取AcquisitionFrameRate属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get AcquisitionFrameRate property's operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_DoubleNode (*acquisitionFrameRate)(struct GENICAM_AcquisitionControl *thiz);


	/// \~chinese
	/// \brief 获取AcquisitionFrameRateEnable使能属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get AcquisitionFrameRateEnable property's operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_BoolNode(*acquisitionFrameRateEnable)(struct GENICAM_AcquisitionControl *thiz);


	/// \~chinese
	/// \brief 获取AcquisitionFrameRate属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get AcquisitionFrameRate property's operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*acquisitionMode)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取ExposureAuto属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get ExposureAuto property's operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*exposureAuto)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取ExposureMode属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get ExposureMode property's operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*exposureMode)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取ExposureTime属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get ExposureTime property's operation object
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_DoubleNode (*exposureTime)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取TriggerActivation属性操作对象，设置触发上升沿下降沿
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get TriggerActivation property's operation object,set trigger by rising edge or falling edge
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*triggerActivation)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取TriggerDelay属性操作对象，设置软触发延时
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get TriggerDelay property operation object, set soft trigger delay
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_DoubleNode (*triggerDelay)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取TriggerMode属性操作对象，设置开启/关闭软触发
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get TriggerMode property operation object, set on/off soft trigger
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*triggerMode)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取TriggerSelector属性操作对象，设置开启/关闭软触发
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get TriggerSelector property operation object, set on/off soft trigger
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*triggerSelector)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取TriggerSource属性操作对象，设置内部/外部触发
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL	
	/// \~english
	/// \brief get TriggerSource property operation object, set internal/external trigger
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*triggerSource)(struct GENICAM_AcquisitionControl *thiz);

	/// \~chinese
	/// \brief 获取TriggerSoftware属性操作对象，执行内部软触发
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象,失败返回NULL
	/// \~english
	/// \brief get TriggerSoftware property operation object, execute internal soft trigger
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_CmdNode (*triggerSoftware)(struct GENICAM_AcquisitionControl *thiz);

	uint32_t reserve[17];					 ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_AcquisitionControl;

/// \~chinese
/// 创建属性节点AcquisitionControl信息
/// 32位系统下128字节
/// \~english
/// create parameter node AcquisitionControl's info
/// 128 bytes in 32-bit system
typedef struct GENICAM_AcquisitionControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	   	///< \~chinese 保留        ///< \~english reserved field
} GENICAM_AcquisitionControlInfo;

/// \~chinese
/// 创建属性节点AcquisitionControl
/// \param [in]  pAcquisitionControlInfo 创建属性节点AcquisitionControl对象的参数
/// \param [out] ppAcquisitionControl 属性节点AcquisitionControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create parameter node AcquisitionControl
/// \param [in]  pAcquisitionControlInfo the parameter of AcquisitionControl object which need to be create as parameter node
/// \param [out] ppAcquisitionControl    parameter node of AcquisitionControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createAcquisitionControl(GENICAM_AcquisitionControlInfo*pAcquisitionControlInfo,
																	GENICAM_AcquisitionControl** ppAcquisitionControl);

typedef enum GENICAM_EConfigSet 
{
	userSet1 = 1,			///< \~chinese 【读写】相机配置集合1    ///< \~english user set 1
	userSet2 = 2,			///< \~chinese 【读写】相机配置集合2    ///< \~english user set 2
	userSetInvalid
}GENICAM_EConfigSet;

/// \~chinese
/// \brief UserSetControl下属性操作类
typedef struct GENICAM_UserSetControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_UserSetControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_UserSetControl *thiz);

	/// \~chinese
	/// \brief 恢复相机默认配置
	/// \param [in] thiz 本接口指针
	/// \return 成功返回0，否则返回-1
	/// \~english
	/// \brief restore default
	/// \param [in] thiz this pointer
	/// \return success:0, fail:-1
	int32_t (*restoreDefault)(struct GENICAM_UserSetControl *thiz);

	/// \~chinese
	/// \brief 设置相机当前配置，并生效且下次以该配置启动
	/// \param [in] thiz 本接口指针
	/// \param [in] configSet 要设置的配置集合
	/// \return 成功返回0，否则返回-1
	/// \~english
	/// \brief set camera current configuration and next time to start with the configuration
	/// \param [in] thiz this pointer
	/// \param [in] configSet configuration set 
	/// \return success:0, fail:-1
	int32_t (*setCurrentUserSet)(struct GENICAM_UserSetControl *thiz, GENICAM_EConfigSet configSet);

	/// \~chinese
	/// \brief 保存相机当前配置到某配置集合，如userSet1
	/// \param [in] thiz 本接口指针
	/// \param [in] configSet 要保存到的配置集合
	/// \return 成功返回0，否则返回-1
	/// \~english
	/// \brief save current configuration set like as userSet1
	/// \param [in] thiz this pointer
	/// \param [in] configSet to save the configuration of the collection
	/// \return success:0, fail:-1
	int32_t (*saveUserSet)(struct GENICAM_UserSetControl *thiz, GENICAM_EConfigSet configSet);

	/// \~chinese
	/// \brief 获取相机当前配置集合
	/// \param [in] thiz 本接口指针
	/// \return 返回配置集合枚举值
	/// \~english
	/// \brief get current user set
	/// \param [in] thiz this pointer
	/// \return configuration set enumeration value
	GENICAM_EConfigSet (*getCurrentUserSet)(struct GENICAM_UserSetControl *thiz);

	/// \~chinese
	/// \brief 获取相机当前UserSet相关是否可用
	/// \param [in] thiz 本接口指针
	/// \return 可用返回0，否则返回-1
	/// \~english
	/// \brief get current user set whether available
	/// \param [in] thiz this pointer
	/// \return available:0, not available:-1
	int32_t (*isAvailable)(struct GENICAM_UserSetControl *thiz);

	uint32_t reserve[24];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_UserSetControl;

/// \~chinese
/// 创建属性节点UserSetControl信息
/// 32位系统下128字节
/// \~english
/// create parameter node UserSetControl's info
/// 128 bytes in 32-bit system
typedef struct GENICAM_UserSetControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_UserSetControlInfo;

/// \~chinese
/// 创建属性节点UserSetControl
/// \param [in]  pUserSetControlInfo 创建属性节点UserSetControl对象的参数
/// \param [out] ppUserSetControl 属性节点UserSetControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create parameter node UserSetControl
/// \param [in]  pUserSetControlInfo the parameter of UserSetControl object which need to be create as parameter node
/// \param [out] ppUserSetControl    parameter node of UserSetControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createUserSetControl(GENICAM_UserSetControlInfo* pUserSetControlInfo
										, GENICAM_UserSetControl** ppUserSetControl);


/// \~chinese
/// \brief ISPControl下属性操作类
/// \~english
/// \brief ISPControl's property operation class
typedef struct GENICAM_ISPControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// \brief 获取Brightness属性操作对象，设置亮度
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Brightness property operation object, set the brightness
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*brightness)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// \brief 获取Sharpness属性操作对象，设置锐度
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Sharpness property operation object, set sharpness
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*sharpness)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// \brief 获取SharpnessAuto属性操作对象，设置是否自动锐度
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get SharpnessAuto property operation object, whether set auto sharpness
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_BoolNode (*sharpnessAuto)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// \brief 获取SharpnessEnable属性操作对象，设置是否开启锐度
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english 
	/// \brief get SharpnessEnable property operation object, whether set auto sharpness
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*sharpnessEnable)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// \brief 获取Contrast属性操作对象，设置对比度
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Contrast property operation object, set contrast
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*contrast)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// \brief 获取Hue属性操作对象，设置色度
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Hue property operation object, set chroma
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*hue)(struct GENICAM_ISPControl *thiz);

	/// \~chinese
	/// \brief 获取Saturation属性操作对象，设置饱和度
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Saturation property operation object, set saturation
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*saturation)(struct GENICAM_ISPControl *thiz);

	uint32_t reserved[22];	   ///< \~chinese 保留    ///< \~english reserved field

}GENICAM_ISPControl;

/// \~chinese
/// 创建属性节点信息
/// 32位系统下128字节
/// \~english
/// create parameter node info
/// 128 bytes in 32-bit system
typedef struct GENICAM_ISPControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_ISPControlInfo;

/// \~chinese
/// 创建属性节点
/// \param [in]  pISPControlInfo 创建属性节点ISPControl对象的参数
/// \param [out] ppISPControl 属性节点ISPControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create parameter node
/// \param [in]  pISPControlInfo the parameter of ISPControl object which need to be create as parameter node
/// \param [out] ppISPControl    parameter node of ISPControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createISPControl(GENICAM_ISPControlInfo* pISPControlInfo
				, GENICAM_ISPControl** ppISPControl);


/// \~chinese
/// \brief AnalogControl下属性操作类
/// 32位系统下128字节
/// \~english
/// \brief AnalogControl's property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_AnalogControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_AnalogControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_AnalogControl *thiz);

	/// \~chinese
	/// \brief 获取BlackLevelSelector属性操作对象，设置操作哪个白平衡
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BalanceWhiteAuto property operation object, set auto white balance
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*blackLevelSelector)(struct GENICAM_AnalogControl *thiz);

	/// \~chinese
	/// \brief 获取BlackLevelAuto属性操作对象，设置自动白平衡
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BalanceWhiteAuto property operation object, set auto white balance
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*blackLevelAuto)(struct GENICAM_AnalogControl *thiz);

	/// \~chinese
	/// \brief 获取BlackLevel属性操作对象，设置白平衡值
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BalanceWhiteAuto property operation object, set auto white balance
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*blackLevel)(struct GENICAM_AnalogControl *thiz);

	/// \~chinese
	/// \brief 获取GainAuto属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BalanceWhiteAuto property operation object, set auto white balance
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*gainAuto)(struct GENICAM_AnalogControl *thiz);

	/// \~chinese
	/// \brief 获取GainRaw属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BalanceWhiteAuto property operation object, set auto white balance
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_DoubleNode (*gainRaw)(struct GENICAM_AnalogControl *thiz);

	/// \~chinese
	/// \brief 获取Gamma属性操作对象，设置Gamma值
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BalanceWhiteAutoproperty operation object, set auto white balance
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_DoubleNode (*gamma)(struct GENICAM_AnalogControl *thiz);
	
	/// \~chinese
	/// \brief 获取BalanceRatioSelector属性操作对象，设置操作哪个白平衡
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BalanceWhiteAuto property operation object, set auto white balance
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*balanceRatioSelector)(struct GENICAM_AnalogControl *thiz);
	
	/// \~chinese
	/// \brief 获取BalanceWhiteAuto属性操作对象，设置自动白平衡
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BalanceWhiteAuto property operation object, set auto white balance
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode (*balanceWhiteAuto)(struct GENICAM_AnalogControl *thiz);
	
	/// \~chinese
	/// \brief 获取BalanceRatioSelector属性操作对象，设置操作哪个白平衡
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get BalanceRatioSelector property operation object, set which the white balance can be operated
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_DoubleNode (*balanceRatio)(struct GENICAM_AnalogControl *thiz);
	
	uint32_t reserve[20];					 ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_AnalogControl;

/// \~chinese
/// 创建属性节点信息
/// 32位系统下128字节
/// \~english
/// create parameter node info
/// 128 bytes in 32-bit system
typedef struct GENICAM_AnalogControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_AnalogControlInfo;

/// \~chinese
/// 创建属性节点
/// \param [in]  pAnalogControlInfo 创建属性节点AnalogControl对象的参数
/// \param [out] ppAnalogControl    属性节点AnalogControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create parameter node
/// \param [in]  pAnalogControlInfo the parameter of AnalogControl object which need to be create as parameter node
/// \param [out] ppAnalogControl    parameter node of AnalogControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t  CALL_METHOD GENICAM_createAnalogControl(GENICAM_AnalogControlInfo* pAnalogControlInfo
						, GENICAM_AnalogControl** ppAnalogControl);


/// \~chinese
/// \brief DeviceControl下属性操作类
/// 32位系统下128字节
/// \~english
/// \brief DeviceControl's property operation calss
/// 128 bytes in 32-bit system
typedef struct GENICAM_DeviceControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_DeviceControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_DeviceControl *thiz);

	/// \~chinese
	/// \brief 获取DeviceUserID属性操作对象，该对象可读写
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get DeviceUserID's property operation object that can read and write 
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_StringNode (*deviceUserID)(struct GENICAM_DeviceControl *thiz);

	uint32_t reserve[28];    ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_DeviceControl;

/// \~chinese
/// 创建属性节点信息
/// 32位系统下128字节
/// \~english
/// create parameter node info
/// 128 bytes in 32-bit system
typedef struct GENICAM_DeviceControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_DeviceControlInfo;

/// \~chinese
/// 创建属性节点
/// \param [in]  pDeviceControlInfo 创建属性节点DeviceControl对象的参数
/// \param [out] ppDeviceControl    属性节点DeviceControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create parameter node
/// \param [in]  pDeviceControlInfo the parameter of DeviceControl object which need to be create as parameter node
/// \param [out] ppDeviceControl    parameter node of DeviceControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createDeviceControl(GENICAM_DeviceControlInfo* pDeviceControlInfo
									, GENICAM_DeviceControl** ppDeviceControl);


/// \~chinese
/// \brief DigitalIOControl下属性操作类
/// 32位系统下128字节
/// \~english
/// \brief DigitalIOControl's property operation calss
/// 128 bytes in 32-bit system
typedef struct GENICAM_DigitalIOControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t(*addRef)(struct GENICAM_DigitalIOControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t(*release)(struct GENICAM_DigitalIOControl *thiz);

	/// \~chinese
	/// \brief 获取LineSelector属性操作对象，该对象可读写
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get LineSelector's property operation object that can read and write 
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode(*lineSelector)(struct GENICAM_DigitalIOControl *thiz);

	/// \~chinese
	/// \brief 获取LineDebouncerTimeAbs属性操作对象，该对象可读
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get LineDebouncerTimeAbs's property operation object that can read and write 
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_DoubleNode(*lineDebouncerTimeAbs)(struct GENICAM_DigitalIOControl *thiz);

	/// \~chinese
	/// \brief 获取UserOutputSelector属性操作对象，该对象可读写
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get UserOutputSelector's property operation object that can read and write 
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_EnumNode(*userOutputSelector)(struct GENICAM_DigitalIOControl *thiz);

	/// \~chinese
	/// \brief 获取UserOutputValue属性操作对象，该对象可读写
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get UserOutputValue's property operation object that can read and write 
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_BoolNode(*userOutputValue)(struct GENICAM_DigitalIOControl *thiz);


	uint32_t reserve[25];    ///< \~chinese 预留字段    ///< \~english reserved field
}GENICAM_DigitalIOControl;

/// \~chinese
/// 创建属性节点信息
/// 32位系统下128字节
/// \~english
/// create parameter node info
/// 128 bytes in 32-bit system
typedef struct GENICAM_DigitalIOControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_DigitalIOControlInfo;

/// \~chinese
/// 创建属性节点
/// \param [in]  pDigitalIOControlInfo 创建属性节点DigitalIOControl对象的参数
/// \param [out] ppDigitalIOControl    属性节点DigitalIOControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create parameter node
/// \param [in]  pDigitalIOControlInfo the parameter of DigitalIOControl object which need to be create as parameter node
/// \param [out] ppDigitalIOControl    parameter node of DigitalIOControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createDigitalIOControl(GENICAM_DigitalIOControlInfo* pDigitalIOControlInfo
	, GENICAM_DigitalIOControl** ppDigitalIOControl);


/// \~chinese
/// \brief TransportLayerControl下属性操作类
/// 32位系统下128字节
/// \~english
/// \brief TransportLayerControl's property operation class 
/// 128 bytes in 32-bit system
typedef struct GENICAM_TransportLayerControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_TransportLayerControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_TransportLayerControl *thiz);

	/// \~chinese
	/// \brief 获取GevSCPD属性操作对象，设置包发送间隔
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get GevSCPD property operation object, set sending interval 
	/// \param [in] thiz this pointer
	/// \return success:return property operation object, fail:return NULL
	GENICAM_IntNode (*gevSCPD)(struct GENICAM_TransportLayerControl *thiz);

	uint32_t reserve[28];    ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_TransportLayerControl;

/// \~chinese
/// 创建属性节点信息
/// 32位系统下128字节
/// \~english
/// create parameter node info
/// 128 bytes in 32-bit system
typedef struct GENICAM_TransportLayerControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_TransportLayerControlInfo;

/// \~chinese
/// 创建属性节点
/// \param [in]  pTransportControlInfo 创建属性节点TransportLayerControl对象的参数
/// \param [out] ppTransportControl   属性节点TransportLayerControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create parameter node
/// \param [in]  pTransportControlInfo the parameter of TransportLayerControl object which need to be create as parameter node
/// \param [out] ppTransportControl    parameter node of TransportLayerControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t CALL_METHOD GENICAM_createTransportLayerControl(GENICAM_TransportLayerControlInfo* pTransportControlInfo
								, GENICAM_TransportLayerControl** ppTransportControl);


/// \~chinese
/// \brief ImageFormatControl下属性操作类
/// 32位系统下128字节
/// \~english
/// \brief ImageFormatControl's property operation class
/// 128 bytes in 32-bit system
typedef struct GENICAM_ImageFormatControl
{
	/// \~chinese
	/// 底层私有数据
	/// \~english
	/// private data
	void *priv;

	/// \~chinese
	/// 增加接口引用
	/// \param [in] thiz 本接口指针
	/// \~english
	/// increase the interface reference
	/// \param [in] thiz this pointer
	int32_t (*addRef)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// 释放接口
	/// \param [in] thiz 本接口指针
	/// \~english
	/// release interface
	/// \param [in] thiz this pointer
	int32_t (*release)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// \brief 获取Height属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Height property operation object
	/// \param [in] thiz this pointer
	/// \return success:property's object, fail:NULL
	GENICAM_IntNode (*height)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// \brief 获取Width属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get Width property operation object
	/// \param [in] thiz this pointer
	/// \return success:property's object, fail:NULL
	GENICAM_IntNode (*width)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// \brief 获取OffsetX属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get OffsetX property operation object
	/// \param [in] thiz this pointer
	/// \return success:property's object, fail:NULL
	GENICAM_IntNode (*offsetX)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// \brief 获取OffsetY属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get OffsetY property operation object
	/// \param [in] thiz this pointer
	/// \return success:property's object, fail:NULL
	GENICAM_IntNode (*offsetY)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// \brief 获取PixelFormat属性操作对象
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get PixelFormat property operation object
	/// \param [in] thiz this pointer
	/// \return success:property's object, fail:NULL
	GENICAM_EnumNode (*pixelFormat)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// \brief 获取ReverseX属性操作对象，设置是否翻转图像X轴
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get ReverseX property's operation object, set up whether reverse X 
	/// \param [in] thiz this pointer
	/// \return property operation object,return NULL if failed
	GENICAM_BoolNode (*reverseX)(struct GENICAM_ImageFormatControl *thiz);

	/// \~chinese
	/// \brief 获取ReverseY属性操作对象，设置是否翻转图像Y轴
	/// \param [in] thiz 本接口指针
	/// \return 返回属性操作对象，失败返回NULL
	/// \~english
	/// \brief get ReverseY property's operation object, set up whether reverse Y 
	/// \param [in] thiz this pointer
	/// \return property operation object,return NULL if failed
	GENICAM_BoolNode (*reverseY)(struct GENICAM_ImageFormatControl *thiz);

	uint32_t reserve[22];					 ///< \~chinese 预留字段    ///< \~english reserved field

}GENICAM_ImageFormatControl;

/// \~chinese
/// 创建属性节点信息
/// 32位系统下128字节
/// \~english
/// create parameter node info
/// 128 bytes in 32-bit system
typedef struct GENICAM_ImageFormatControlInfo
{
	GENICAM_Camera*  pCamera;	///< \~chinese 相机对象    ///< \~english camera object
	uint32_t reserved[31];	    ///< \~chinese 保留        ///< \~english reserved field
} GENICAM_ImageFormatControlInfo;

/// \~chinese
/// 创建属性节点
/// \param [in]  pImageFormatControlInfo 创建属性节点ImageFormatControl对象的参数
/// \param [out] ppImageFormatControl    属性节点ImageFormatControl对象
/// \retval < 0 创建失败
/// \retval 0   创建成功
/// \~english
/// create parameter node
/// \param [in]  pImageFormatControlInfo the parameter of ImageFormatControl object which need to be create as parameter node
/// \param [out] ppImageFormatControl    parameter node of ImageFormatControl object
/// \retval < 0 create failed
/// \retval 0   create successfully
GENICAM_API int32_t  CALL_METHOD GENICAM_createImageFormatControl(GENICAM_ImageFormatControlInfo* pImageFormatControlInfo,
												GENICAM_ImageFormatControl** ppImageFormatControl);

/// @}


#ifdef __cplusplus
}
#endif 

#endif