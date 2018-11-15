//
//  "$Id: Types.h 16720 2010-12-01 09:51:53Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef __DAHUA3_TYPES_H__
#define __DAHUA3_TYPES_H__

#include "IntTypes.h"
////////////////////////////////////////////////////////////////////////////////

// WIN32 Dynamic Link Library
#ifdef _MSC_VER

/// 废弃INTERFACE_API的使用，每个模块DLL应该定义自己的XXX_API，请参考INFRA_API的定义
#ifdef _DLL_BUILD
	#define  INTERFACE_API _declspec(dllexport)
#elif defined _DLL_USE
	#define  INTERFACE_API _declspec(dllimport)
#else
	#define INTERFACE_API
#endif

#else
	#define INTERFACE_API
#endif

#if (defined (WIN32) || defined(WIN64))
#   define CALLMETHOD __stdcall
#else
#	define CALLMETHOD
#endif // end #if (defined (WIN32) || defined(WIN64))

#ifdef __GNUC__
#define INFINITE            0xFFFFFFFF  // Infinite timeout
#endif

/// IP 地址结构
typedef union tagMvSIpAddress
{
	uint8_t		c[4];
	uint16_t	s[2];
	uint32_t	l;
}IpAddress;

//////////////////////////////////////////////////////////////////////////
/// 系统时间定义
typedef struct tagMvSSystemTime
{
	int32_t  year;		///< 年。
	int32_t  month;		///< 月，January = 1, February = 2, and so on.
	int32_t  day;		///< 日。
	int32_t  wday;		///< 星期，Sunday = 0, Monday = 1, and so on
	int32_t  hour;		///< 时。
	int32_t  minute;	///< 分。
	int32_t  second;	///< 秒。
	int32_t  isdst;		///< 夏令时标识。
}MvSSystemTime;	


/// 点
typedef struct tagMvSPoint
{
	int x;
	int y;
} MvSPoint;

/// 2D点结构体定义
typedef struct tagMvSPoint2Di32
{
	int32_t		x;
	int32_t		y;
} MvSPoint2Di32;

typedef struct tagMvSPoint2Di16
{
	int16_t		x;
	int16_t		y;
} MvSPoint2Di16;

typedef struct tagMvSPoint2Df32
{
	float		x;
	float		y;
} MvSPoint2Df32;

/// 3D点结构体定义
typedef struct tagMvSPoint3Di32
{
	int32_t		x;
	int32_t		y;
	int32_t		z;
} MvSPoint3Di32;

typedef struct tagMvSPoint3Di16
{
	int16_t		x;
	int16_t		y;
	int16_t		z;
} MvSPoint3Di16;

typedef struct tagMvSPoint3Df32
{
	float		x;
	float		y;
	float		z;
} MvSPoint3Df32;
	
/// 矩形
typedef struct tagMvSRect
{
	int left;
	int top;
	int right;
	int bottom;
} MvSRect;

/// 尺寸
typedef struct tagMvSSize
{
	int w;
	int h;
} MvSSize;

/// 颜色
typedef struct tagMvSColor
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} MvSColor;

/// 直线
typedef struct tagMvSLine
{
	MvSPoint start;
	MvSPoint end;
} MvSLine;

typedef struct tagMvSLinePA
{
	MvSPoint2Df32   point;
	float           angle;
}MvSLinePA;

/// 时间段结构
typedef struct tagMvSTimeSection
{
	int enable;			///< 使能
	int startHour;		///< 开始时间:小时
	int	startMinute;	///< 开始时间:分钟
	int	startSecond;	///< 开始时间:秒钟
	int	endHour;		///< 结束时间:小时
	int	endMinute;		///< 结束时间:分钟
	int	endSecond;		///< 结束时间:秒钟
}MvSTimeSection;




/// 二维线段线段定义
//////////////////////////////////////////////////////////////////////////
typedef struct tagMvSLineSeg2Di32
{
	MvSPoint2Di32		pt1;
	MvSPoint2Di32    	pt2;
} MvSLineSeg2Di32;

typedef struct tagMvSLineSeg2Df32
{
	MvSPoint2Df32		pt1;
	MvSPoint2Df32		pt2;
} MvSLineSeg2Df32;

//尺寸定义
/////////////////////////////////////////////////////////////////////////////////
typedef struct tagMvSSizei32
{
	int32_t		width;							///< 宽
	int32_t		height;							///< 高
} MvSSizei32;

typedef struct tagMvSSizef32
{
	float		width;							///< 浮点宽高
	float		height;
} MvSSizef32;
/////////////////////////////////////////////////////////////////////////////////////

//矩形框结构体
//////////////////////////////////////////////////////////////////////////////////
typedef struct tagMvSRect2Di32
{
	MvSPoint2Di32		ul;	//左上
	MvSPoint2Di32		lr;	//右下
} MvSRect2Di32;

typedef struct tagMvSRect2Df32
{
	MvSPoint2Df32	ul;	//左上
	MvSPoint2Df32	lr;	//右下
} MvSRect2Df32;

/*矩形*/
typedef struct tagMvSRectangle 
{
	float							cx;								///< 中心x
	float							cy;								///< 中心y			
	float							lx;								///< x方向长
	float							ly;								///< y方向长		
	float							ra;								///< 旋转角度
	float							ska;							///< 斜切角度
}MvSRectangle;

/*圆*/
typedef struct tagMvSCircle
{
	float							cx;
	float							cy;
	float							radius;							///< 半径
} MvSCircle;

/*椭圆*/
typedef struct tagMvSEllipse
{
	float							cx;								///< 中心x
	float							cy;								///< 中心y
	float							rx;								///< x轴系数
	float							ry;								///< y轴系数
	float							ra;								///< 旋转角度
	float							ska;							///< 斜切角度
}MvSEllipse;

///32位程序128个字节
typedef union tagMvUGraphObj
{
	MvSRectangle		rect;						           ///< type == 0
	MvSCircle			circle;								   ///< type == 1
	MvSEllipse			ellipse;							   ///< type == 2
	int32_t reserved[32];
}MvUGraphObj;

///< 任意目标
typedef struct tagMvSGraphBase
{
	int32_t				type;															///< 目标类型
	MvUGraphObj			graph;															///< 目标数据
}MvSGraphBase;

//////////////////////////////////////////////////////////////
/*图像结构体定义*/
typedef struct tagMvSImage
{
	int32_t							type;							//图像格式，见PublicDefine.h中MvsImgType
	int32_t							dataType;						//存储类型，见PublicDefine.h中MvsImgDataType
	int32_t							width;							//传入图像数据宽度
	int32_t							height;							//传入图像数据高度
	MvSRect							roi;							//有效数据区域
	uint8_t							*imageData;						//图像数据指针	
	uint8_t							*mask;							//图像掩膜，0 (MVS_NULL)表示没有掩膜
	int32_t							*reserved[22];					// 预留字段1
}MvSImage;

#endif// __DAHUA_TYPES_H__

