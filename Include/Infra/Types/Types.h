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

/// ����INTERFACE_API��ʹ�ã�ÿ��ģ��DLLӦ�ö����Լ���XXX_API����ο�INFRA_API�Ķ���
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

/// IP ��ַ�ṹ
typedef union tagMvSIpAddress
{
	uint8_t		c[4];
	uint16_t	s[2];
	uint32_t	l;
}IpAddress;

//////////////////////////////////////////////////////////////////////////
/// ϵͳʱ�䶨��
typedef struct tagMvSSystemTime
{
	int32_t  year;		///< �ꡣ
	int32_t  month;		///< �£�January = 1, February = 2, and so on.
	int32_t  day;		///< �ա�
	int32_t  wday;		///< ���ڣ�Sunday = 0, Monday = 1, and so on
	int32_t  hour;		///< ʱ��
	int32_t  minute;	///< �֡�
	int32_t  second;	///< �롣
	int32_t  isdst;		///< ����ʱ��ʶ��
}MvSSystemTime;	


/// ��
typedef struct tagMvSPoint
{
	int x;
	int y;
} MvSPoint;

/// 2D��ṹ�嶨��
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

/// 3D��ṹ�嶨��
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
	
/// ����
typedef struct tagMvSRect
{
	int left;
	int top;
	int right;
	int bottom;
} MvSRect;

/// �ߴ�
typedef struct tagMvSSize
{
	int w;
	int h;
} MvSSize;

/// ��ɫ
typedef struct tagMvSColor
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} MvSColor;

/// ֱ��
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

/// ʱ��νṹ
typedef struct tagMvSTimeSection
{
	int enable;			///< ʹ��
	int startHour;		///< ��ʼʱ��:Сʱ
	int	startMinute;	///< ��ʼʱ��:����
	int	startSecond;	///< ��ʼʱ��:����
	int	endHour;		///< ����ʱ��:Сʱ
	int	endMinute;		///< ����ʱ��:����
	int	endSecond;		///< ����ʱ��:����
}MvSTimeSection;




/// ��ά�߶��߶ζ���
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

//�ߴ綨��
/////////////////////////////////////////////////////////////////////////////////
typedef struct tagMvSSizei32
{
	int32_t		width;							///< ��
	int32_t		height;							///< ��
} MvSSizei32;

typedef struct tagMvSSizef32
{
	float		width;							///< ������
	float		height;
} MvSSizef32;
/////////////////////////////////////////////////////////////////////////////////////

//���ο�ṹ��
//////////////////////////////////////////////////////////////////////////////////
typedef struct tagMvSRect2Di32
{
	MvSPoint2Di32		ul;	//����
	MvSPoint2Di32		lr;	//����
} MvSRect2Di32;

typedef struct tagMvSRect2Df32
{
	MvSPoint2Df32	ul;	//����
	MvSPoint2Df32	lr;	//����
} MvSRect2Df32;

/*����*/
typedef struct tagMvSRectangle 
{
	float							cx;								///< ����x
	float							cy;								///< ����y			
	float							lx;								///< x����
	float							ly;								///< y����		
	float							ra;								///< ��ת�Ƕ�
	float							ska;							///< б�нǶ�
}MvSRectangle;

/*Բ*/
typedef struct tagMvSCircle
{
	float							cx;
	float							cy;
	float							radius;							///< �뾶
} MvSCircle;

/*��Բ*/
typedef struct tagMvSEllipse
{
	float							cx;								///< ����x
	float							cy;								///< ����y
	float							rx;								///< x��ϵ��
	float							ry;								///< y��ϵ��
	float							ra;								///< ��ת�Ƕ�
	float							ska;							///< б�нǶ�
}MvSEllipse;

///32λ����128���ֽ�
typedef union tagMvUGraphObj
{
	MvSRectangle		rect;						           ///< type == 0
	MvSCircle			circle;								   ///< type == 1
	MvSEllipse			ellipse;							   ///< type == 2
	int32_t reserved[32];
}MvUGraphObj;

///< ����Ŀ��
typedef struct tagMvSGraphBase
{
	int32_t				type;															///< Ŀ������
	MvUGraphObj			graph;															///< Ŀ������
}MvSGraphBase;

//////////////////////////////////////////////////////////////
/*ͼ��ṹ�嶨��*/
typedef struct tagMvSImage
{
	int32_t							type;							//ͼ���ʽ����PublicDefine.h��MvsImgType
	int32_t							dataType;						//�洢���ͣ���PublicDefine.h��MvsImgDataType
	int32_t							width;							//����ͼ�����ݿ��
	int32_t							height;							//����ͼ�����ݸ߶�
	MvSRect							roi;							//��Ч��������
	uint8_t							*imageData;						//ͼ������ָ��	
	uint8_t							*mask;							//ͼ����Ĥ��0 (MVS_NULL)��ʾû����Ĥ
	int32_t							*reserved[22];					// Ԥ���ֶ�1
}MvSImage;

#endif// __DAHUA_TYPES_H__

