//
//  "$Id$"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_PRINT_LOG_H__
#define __INFRA3_PRINT_LOG_H__

#include <stdio.h>
#include "Defs.h"
#include "Function.h"
#include "Thread.h"

//// log��ʽ"[Time]|Category|[Version]|Level|File|[Function]|Line|[Tid]|Content"

/// \defgroup PrintLog PrintLog
/// ��ӡ��Ϣ��¼�ȵȡ�
/// ��ӡ��Ϣ��trace, debug, info, warn, error, fatal��6�����𣬼�¼����ʽ������
/// ֱ�Ӵ�ӡ����׼�����Ҳ���Լ�¼���ļ����߷��͵�Զ����־��������Ŀǰֻ֧��
/// ��һ�ַ�ʽ��ÿ�д�ӡ��Ϣǰ�Զ�������ʱ��ʹ�ӡ���͵��ַ���������"12:54:12|info"
/// @{
namespace Dahua{
namespace Infra{

///��־�ȼ�, ͨ��setPrintLogLevel��������
enum LogLevel
{
	logLevelUnknown= 0, ///< δ֪��ӡ�ȼ�����
	logLevelFatal,	///< fatal�ȼ���������Ϊ�˵ȼ�ʱ����һ�ִ�ӡ�����fatal���������
	logLevelError,	///< error�ȼ���������Ϊ�˵ȼ�ʱ�������ִ�ӡ�����fatal��error���������
	logLevelWarn,	///< warn�ȼ���������Ϊ�˵ȼ�ʱ�������ִ�ӡ�����fatal��error��warn���������
	logLevelInfo,	///< info�ȼ���������Ϊ�˵ȼ�ʱ�������ִ�ӡ�����fatal��error��warn��info���������
	logLevelTrace,	///< Trace�ȼ���������Ϊ�˵ȼ�ʱ�������ִ�ӡ�����fatal��error��warn��info��trace���������
	logLevelDebug,	///< Debug�ȼ���������Ϊ�˵ȼ�ʱ���������ִ�ӡ��fatal��error��warn��info��trace��debug���������
};

//��ӡѡ��
struct PrintOptions
{
	char time; 		//�Ƿ��ӡʱ�䣬0��ӡ��1����ӡ��Ĭ�ϴ�ӡ
	char color; 	//�Ƿ��ӡ��ɫ��0��ӡ��1����ӡ��Ĭ�ϴ�ӡ
	char libName; 	//�Ƿ��ӡ������0��ӡ��1����ӡ��Ĭ�ϴ�ӡ
	char level; 	//�Ƿ��ӡ�ȼ���0��ӡ��1����ӡ��Ĭ�ϴ�ӡ
	char resv[28]; 	//����
};

/// ��ӡ����ص���������
/// ����ΪҪ��ӡ���ַ���
typedef TFunction1<void, char const*> LogPrinterProc;

/// �����ӡ�ص���������
typedef TFunction1<bool, char const*> PrintProc;

/// ���ô�ӡ������ص�����
/// \param [in] printer ����ص�����, Ϊ��ʱ���ô�ӡ�������׼����豸
/// \return �ɹ�����0, ʧ�ܷ���-1
int INFRA_API setLogPrinter(LogPrinterProc printer);

/// ���ô�ӡ�ļ��𣬸��ڸü���Ĵ�ӡ�������
///\param [in] level-��־�ȼ����μ� LogLevel ����
void INFRA_API setPrintLogLevel(int level);

/// ��ӡ���ÿ�������¼������Ϣ������nLevel����ֱ�ӵ���
/// \return ���ش�ӡ���ֽ���
int INFRA_API logLibName(int nLevel, const char* libName, const char* fmt, ...)
	__attribute__((format(printf, 3, 4)));

/// ��¼������Ϣ������6����ֱ�ӵ��ã�����ʵ��debgf��
/// \return ���ش�ӡ���ֽ���
int INFRA_API logDebug(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

/// ��¼������Ϣ������5����ֱ�ӵ��ã�����ʵ��tracef��
/// \return ���ش�ӡ���ֽ���
int INFRA_API logTrace(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

/// ��¼������Ϣ������4����ֱ�ӵ��ã�����ʵ��infof��
/// \return ���ش�ӡ���ֽ���
int INFRA_API logInfo(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

/// ��¼������Ϣ������3����ֱ�ӵ��ã�����ʵ��warnf��
/// \return ���ش�ӡ���ֽ���
int INFRA_API logWarn(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

/// ��¼������Ϣ������2����ֱ�ӵ��ã�����ʵ��errorf��
/// \return ���ش�ӡ���ֽ���
int INFRA_API logError(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

/// ��¼����������Ϣ������1����ֱ�ӵ��ã�����ʵ��fatalf��
/// \return ���ش�ӡ���ֽ���
int INFRA_API logFatal(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

/// ��16���ƺ��ַ���Ӧ�ķ�ʽ��ӡ�ڴ�����
/// \param pdat ���ݻ���ָ��
/// \param length ���ݻ��峤��
void INFRA_API dumpHex(uint8_t* pdat, size_t length = 512);

/// ע���ӡ������
bool INFRA_API attachPrint(PrintProc proc);

/// ע����ӡ������
bool INFRA_API detachPrint(PrintProc proc);

/// ���ô�ӡѡ��
/// \printOptions ��ӡѡ��μ�PrintOptions�ṹ��
void INFRA_API setPrintOptions(PrintOptions printOptions);

///������־��̬��������(-h����鿴����)��
///����˵����logfilter command usage:
///logfilter -loglevel [levelnum](0-no printlevel, 1-fatal, 2-error, 3-warn, 4-info, 5-trace, 6-debug): set log level;
///logfilter -logmodule [modulename] [on/off] #turn module's log on/off
///logfilter -logmoduleLevel[modulename][levelnum] #set module's loglevel
///logfilter -logtime [on/off] #turn log's time on/off
///logfilter -logthread [on/off] #turn log's thread on/off
///logfilter -logversion [on/off] #turn module svn version on/off
///logfilter -logpath [logpath/""] #logger module's log to logpath or cancel logger(by set path to "")
///logfiter -logsize [logsize] #log file max size limited to logsize Kbytes;
///\ param [in] argc --arg�����ĸ���
///\ param [in] argv---arg��������
void INFRA_API	setLogFilter(int argc, char * argv[]);

struct ModulePrintLevel{
	char module[256];
	Infra::LogLevel level;
};

///��ȡ����ģ�����־����
///\ param [in/out] moduleLlist --��־�б�ָ��
///\ param [out] len --��־�б���Ч����
void INFRA_API	getLogModules(ModulePrintLevel moduleLlist[256], int &len);

/// ��־���˴�����
///\ param [in] level--��־�ȼ�
///\ param [in] module--����־������ģ����
///\ param [in] file--����־�������ļ���
///\ param [in] func--����־�����ĺ�����
///\ param [in] line--����־�������к�
///\ param [in] svnversion ---��ģ��İ汾��
///\ param [in] fmt---��־��ʽ���Ʒ���������û�����־��Ϣ
int INFRA_API logFilter(int level, 
						const char* module, 
						const char *file,
						const char *func,
						int line,
						const char *svnversion, 
						const char *fmt, ...)__attribute__((format(printf, 7, 8)));

/// ��־ģ������ӿڣ�����������־ģ�����򿪵���Դ��
/// Ӧ�����ģ��ж�ػ��߳����˳���ʹ�á�
void INFRA_API logCleanup();


} // namespace Infra
} // namespace Dahua

//////////////////////////////////////////////////////////////////////////
// print message, controlled by messsage level

#undef debugf
#undef tracef
#undef infof
#undef warnf
#undef errorf
#undef fatalf
#undef tracepoint

#ifndef LOG_LIB_NAME
#define LOG_LIB_NAME "Unknown"
#endif

#ifndef LOG_LIB_VERSION
#define LOG_LIB_VERSION "Unknown"
#endif

#if !defined(_MSC_VER) || (_MSC_VER > 1300)

#define debugf(format, ...) \
	logFilter(Dahua::Infra::logLevelDebug, LOG_LIB_NAME,__FILE__, __FUNCTION__, __LINE__,  LOG_LIB_VERSION, format , ## __VA_ARGS__)
#define tracef(format, ...)\
	logFilter(Dahua::Infra::logLevelTrace, LOG_LIB_NAME,__FILE__, __FUNCTION__, __LINE__,  LOG_LIB_VERSION, format , ## __VA_ARGS__)
#define infof(format, ...) \
	logFilter(Dahua::Infra::logLevelInfo, LOG_LIB_NAME,__FILE__, __FUNCTION__, __LINE__,  LOG_LIB_VERSION, format , ## __VA_ARGS__)
#define warnf(format, ...) \
	logFilter(Dahua::Infra::logLevelWarn, LOG_LIB_NAME,__FILE__, __FUNCTION__, __LINE__,  LOG_LIB_VERSION, format , ## __VA_ARGS__)
#define errorf(format, ...) \
	logFilter(Dahua::Infra::logLevelError, LOG_LIB_NAME,__FILE__, __FUNCTION__, __LINE__,  LOG_LIB_VERSION, format , ## __VA_ARGS__)
#define fatalf(format, ...) \
	logFilter(Dahua::Infra::logLevelFatal, LOG_LIB_NAME,__FILE__, __FUNCTION__, __LINE__,  LOG_LIB_VERSION, format , ## __VA_ARGS__)


#define tracepoint()  debugf("tracepoint:\n")


/// ��ӡ��(����ǰ�̺߳ź�thisָ���ַ)
#define debugf_log_this(format, ...)	debugf("[%s:%d] this:%p tid:%d, " format, __FILE__, __LINE__, this,Dahua::Infra::CThread::getCurrentThreadID(), ## __VA_ARGS__)
#define tracef_log_this(format, ...)	tracef("[%s:%d] this:%p tid:%d, " format, __FILE__, __LINE__, this, Dahua::Infra::CThread::getCurrentThreadID(), ## __VA_ARGS__)
#define infof_log_this(format, ...)		infof("[%s:%d] this:%p tid:%d, " format, __FILE__, __LINE__, this,Dahua::Infra::CThread::getCurrentThreadID(), ## __VA_ARGS__)
#define warnf_log_this(format, ...)		warnf("[%s:%d] this:%p tid:%d, " format, __FILE__, __LINE__, this, Dahua::Infra::CThread::getCurrentThreadID(), ## __VA_ARGS__)
#define errorf_log_this(format, ...)	errorf("[%s:%d] this:%p tid:%d, " format, __FILE__, __LINE__, this, Dahua::Infra::CThread::getCurrentThreadID(), ## __VA_ARGS__)
#define fatalf_log_this(format, ...)	fatalf("[%s:%d] this:%p tid:%d, " format, __FILE__, __LINE__, this, Dahua::Infra::CThread::getCurrentThreadID(), ## __VA_ARGS__)

/// ��ӡ��(����ǰ�̺߳�)
#define debugf_log(format, ...) 		debugf("[%s:%d] tid:%d, " format,  __FILE__, __LINE__, Dahua::Infra::CThread::getCurrentThreadID(),  ## __VA_ARGS__)
#define tracef_log(format, ...)			tracef("[%s:%d] tid:%d, " format,  __FILE__, __LINE__, Dahua::Infra::CThread::getCurrentThreadID(),  ## __VA_ARGS__)
#define infof_log(format, ...)          infof("[%s:%d] tid:%d, " format,  __FILE__, __LINE__, Dahua::Infra::CThread::getCurrentThreadID(),  ## __VA_ARGS__)
#define warnf_log(format, ...)          warnf("[%s:%d] tid:%d, " format,  __FILE__, __LINE__, Dahua::Infra::CThread::getCurrentThreadID(),  ## __VA_ARGS__)
#define errorf_log(format, ...)         errorf("[%s:%d] tid:%d, " format,  __FILE__, __LINE__, Dahua::Infra::CThread::getCurrentThreadID(),  ## __VA_ARGS__)
#define fatalf_log(format, ...)         fatalf("[%s:%d] tid:%d, " format,  __FILE__, __LINE__, Dahua::Infra::CThread::getCurrentThreadID(),  ## __VA_ARGS__)

#else 

////// ����windowsƽ̨vc6(_MSC_VER <1300)��־��ӡ��
#define debugf		logDebug
#define tracef		logTrace
#define infof		logInfo
#define warnf		logWarn
#define errorf		logError
#define fatalf		logFatal
#define tracepoint	logDebug

/// ��ӡ��(����ǰ�̺߳ź�thisָ���ַ)
#define debugf_log_this		debugf
#define tracef_log_this		tracef
#define infof_log_this		infof
#define warnf_log_this		warnf
#define errorf_log_this		errorf
#define fatalf_log_this		fatalf

/// ��ӡ��(����ǰ�̺߳�)
#define debugf_log			debugf
#define tracef_log			tracef
#define infof_log			infof
#define warnf_log			warnf
#define errorf_log			errorf
#define fatalf_log			fatalf
#endif

#endif //__INFRA_PRINT_LOG_H__

