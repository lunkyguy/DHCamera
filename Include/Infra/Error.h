//
//  "$Id: Error.h 106479 2013-03-18 05:55:07Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef __INFRA3_ERROR_H__
#define __INFRA3_ERROR_H__

#include "String.h"
#include "Defs.h"

namespace Dahua {

/////////////////////////////////////////////////////////////////////////
// Error Number Define For
enum InfraError
{
	// �� linux ���ݵĴ����
	errorPERM		= 1,	///< Operation not permitted
	errorNOFILE		= 2,	///< No such file or directory
	errorNOENT		= 2,
	errorSRCH		= 3,	///< No such process
	errorINTR		= 4,	///< Interrupted function call
	errorIO			= 5,	///< Input/output error
	errorNXIO		= 6,	///< No such device or address
	error2BIG		= 7,	///< Arg list too long
	errorNOEXEC		= 8,	///< Exec format error
	errorBADF		= 9,	///< Bad file descriptor
	errorCHILD		= 10,	///< No child processes
	errorAGAIN		= 11,	///< Resource temporarily unavailable
	errorNOMEM		= 12,	///< Not enough space
	errorACCES		= 13,	///< Permission denied
	errorFAULT		= 14,	///< Bad address
	errorBUSY		= 16,	///< strerror reports "Resource device"
	errorEXIST		= 17,	///< File exists
	errorXDEV		= 18,	///< Improper link (cross-device link?)
	errorNODEV		= 19,	///< No such device
	errorNOTDIR		= 20,	///< Not a directory
	errorISDIR		= 21,	///< Is a directory
	errorINVAL		= 22,	///< Invalid argument
	errorNFILE		= 23,	///< Too many open files in system
	errorMFILE		= 24,	///< Too many open files
	errorNOTTY		= 25,	///< Inappropriate I/O control operation
	errorFBIG		= 27,	///< File too large
	errorNOSPC		= 28,	///< No space left on device
	errorSPIPE		= 29,	///< Invalid seek (seek on a pipe?)
	errorROFS		= 30,	///< Read-only file system
	errorMLINK		= 31,	///< Too many links
	errorPIPE		= 32,	///< Broken pipe
	errorDOM		= 33,	///< Domain error (math functions)
	errorRANGE		= 34,	///< Result too large (possibly too small)
	errorDEADLOCK	= 36,	///< Resource deadlock avoided (non-Cyg)
	errorDEADLK		= 36,
	errorNAMETOOLONG= 38,	///< Filename too long (91 in Cyg?)
	errorNOLCK		= 39,	///< No locks available (46 in Cyg?)
	errorNOSYS		= 40,	///< Function not implemented (88 in Cyg?)
	errorNOTEMPTY	= 41,	///< Directory not empty (90 in Cyg?)
	errorILSEQ		= 42,	///< Illegal byte sequence


	// Infra ��������
	infraErrorNoFound				= 0x10000000,	///< û���ҵ�ָ���Ķ���
	infraErrorExist					= 0x10000001,	///< �����Ѿ�����
	infraErrorFull					= 0x10000002,	///< �����ﵽ��������
	infraErrorEmptyProc				= 0x10000003,	///< ��������ĺ���ָ��Ϊ�գ�û������
	infraErrorNotInTimeSection		= 0x10000004,	///< ����ʱ�����
	infraErrorPalInterfaceEmpty		= 0x10000005,	///< PAL �ӿ�δʵ��
	infraErrorPalCallFailed			= 0x10000006,	///< PAL �ӿڵ���ʧ��
	infraErrorThreadIsRunning		= 0x10000007,	///< �߳���������
	infraErrorThreadNotExist		= 0x10000008,	///< �̲߳�����
	infraErrorThreadNotManaged		= 0x10000009,	///< �߳�δ������
	infraErrorTlsOutOfIndexes		= 0x1000000a,	///< TLS ��������ȷ
	infraErrorTimerNotStarted		= 0x1000000b,	///< ��ʱ��δ����
	infraErrorTimerIsRunning		= 0x1000000c,	///< ��ʱ����������
	infraErrorPacketNoFree			= 0x1000000d,	///< Packet �ڴ�ռ䲻��
	infraErrorModifySysTimeFailed	= 0x1000000e,	///< ֱ���޸�ϵͳʱ��ʧ��
	infraErrorSyncRtcTimeFailed		= 0x1000000f,	///< �޸�ʱ��ʱRTCʱ��ͬ��ʧ�ܻ��߻ص�����(һ������ͬ��rtcʱ��)ʧ��
};

namespace Infra {

	/// ����ϵͳ��������ʱ�����õ����߳����һ������
	/// ������ڲ��߼�����ʱ��Ӧ�õ��ô˽ӿڸ��ݲ�ͬԭ�����ô���š�����ǵ���
	/// ϵͳ����������������������ʱ��ҲӦ�ý�(errno)��ֵ����Ϊ��ǰ����
	INFRA_API void setLastError(int eno);

	/// ��ȡ�����߳����һ������ʹ��linux���ݴ����롣
	INFRA_API int getLastError();

	/// ���ô������Ӧ�Ĵ����ַ���
	INFRA_API void setErrMsg(int eno, const char* message);

	/// ���ݴ������ȡ�����ַ�����
	INFRA_API const char* getErrMsg(int eno);

	/// ���ô������Ӧ�Ĵ����ַ���
	INFRA_API void setErrorMessage(int eno, CString2 const& message);

	/// ���ݴ������ȡ�����ַ�����
	INFRA_API CString2 getErrorMessage(int eno);

} // namespace Infra
} // namespace Dahua

#endif //__INFRA_ERROR_H__
