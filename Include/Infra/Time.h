//
//  "$Id: Time.h 109610 2013-04-02 06:41:41Z qin_fenglin $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_TIME_WRAPPER_H__
#define __INFRA3_TIME_WRAPPER_H__

#include <string>
#include "Defs.h"
#include "String.h"
#include "Function.h"

namespace Dahua {
namespace Infra {

/// ʱ��ṹ
struct SystemTime
{
	int  year;		///< �ꡣ
	int  month;		///< �£�January = 1, February = 2, and so on.
	int  day;		///< �ա�
	int  wday;		///< ���ڣ�Sunday = 0, Monday = 1, and so on
	int  hour;		///< ʱ��
	int  minute;	///< �֡�
	int  second;	///< �롣
	int  isdst;		///< ����ʱ��ʶ��
};

/// \class CTime
/// \brief ʱ���࣬ʵ���˱���ʱ���ȡ�����㣬��ʽ�������ӡ�Ƚӿ�
/// CTime�ദ���ʱ�䶼�Ǳ���ʱ�䣬��GMTʱ��Ļ����ϼ���ʱ��ƫ�ơ�
class INFRA_API CTime : public SystemTime
{
public:
	/// ʱ���޸Ļص�����
	typedef TFunction1<bool, SystemTime> ModifyProc;

	/// ����˳���ʽ
	enum DateFormat
	{
		ymd,
		mdy,
		dmy
	};

	/// ��ʽ��ģʽѡ��
	enum FormatMask
	{
		fmGeneral = 0,		///< ָֻ���Ƿ���ʾ�Լ���ʼֵ
		fmSeparator = 1,	///< ָ���ָ���
		fmDateFormat = 2,	///< ָ��������˳��
		fmHourFormat = 4,	///< ָ��Сʱ��ʽ

		fmAll = fmSeparator | fmDateFormat | fmHourFormat	///< ָ�����и�ʽѡ��
	};

	/// ȱʡ���캯��
	CTime( );

	/// ���ʱ�乹�캯��
	CTime(uint64_t time);

	/// ��ͨʱ�乹�캯��
	CTime( int vyear, int vmonth, int vday, int vhour, int vmin, int vsec);

	/// �õ����ʱ�䣬���ʱ��ָ��GMT 1970-1-1 00:00:00 ��ĳ��ʱ�̾���������
	/// \return ���ʱ��
	uint64_t makeTime() const;

	/// �ֽ����ʱ��
	/// \param time ���ʱ��
	void breakTime(uint64_t time);

	/// ʱ�����
	/// \param seconds ���ڵ�����
	/// \return ���ں��µ�ʱ�����
	CTime operator +( int64_t seconds ) const;

	/// ʱ�����
	/// \param seconds ���ڵ�����
	/// \return ���ں��µ�ʱ�����
	CTime operator -( int64_t seconds ) const;

	/// ʱ�������
	/// \param time ��Ƚϵ�ʱ��
	/// \return �ȽϵĽ����Ϊ(*this - time)�õ�������
	int64_t operator -( const CTime& time ) const;

	/// ʱ�����
	/// \param seconds ���ڵ�����
	/// \return ������
	CTime& operator +=( int64_t seconds );

	/// ʱ�����
	/// \param seconds ���ڵ�����
	/// \return ������
	CTime& operator -=( int64_t seconds );

	/// ʱ��Ƚ�
	/// \param time ��Ƚϵ�ʱ��
	/// \return ��ȷ���true�����򷵻�false
	bool operator == (const CTime& time) const;

	/// ʱ��Ƚ�
	/// \param time ��Ƚϵ�ʱ��
	/// \return ���ȷ���true�����򷵻�false
	bool operator != (const CTime& time) const;

	/// ʱ��Ƚ�
	/// \param time ��Ƚϵ�ʱ��
	/// \return <����true�����򷵻�false
	bool operator < (const CTime& time) const;

	/// ʱ��Ƚ�
	/// \param time ��Ƚϵ�ʱ��
	/// \return <=����true�����򷵻�false
	bool operator <= (const CTime& time) const;

	/// ʱ��Ƚ�
	/// \param time ��Ƚϵ�ʱ��
	/// \return >����true�����򷵻�false
	bool operator > (const CTime& time) const;

	/// ʱ��Ƚ�
	/// \param time ��Ƚϵ�ʱ��
	/// \return >=����true�����򷵻�false
	bool operator >= (const CTime& time) const;

	/// ʱ���ʽ��
	/// \param buf �ַ������壬һ��Ҫ�㹻��
	/// \param format ��ʽ���ַ�������"yyyy-MM-dd HH:mm:ss tt"
	/// yy = �꣬�������� yyyy = �꣬������
	/// M = ��0��ʼ�� MM = 0��ʼ�� MMMM = ������
	/// d = ��0��ʼ�� dd = 0��ʼ��
	/// H = ��0��ʼ24Сʱ HH = 0��ʼ24Сʱ h = ��0��ʼ12Сʱ hh = 0��ʼ12Сʱ
	/// tt = ��ʾ���������
	/// \param mask ��ʽѡ�ָ�����ڷָ�����������˳��Сʱ��ʽ�Ƿ���ͳһ�ĸ�
	/// ʽ��������Ӧλ��0����ʾʹ��ͳһ��ʽ����1����ʾʹ��formatָ���ĸ�ʽ
	void format(char* buf, const char *format = "yyyy-MM-dd HH:mm:ss", int mask = fmGeneral) const;

	/// ʱ���ַ�������
	/// \param buf ������ַ�������
	/// \param format ��ʽ���ַ�������ʱֻ֧��Ĭ�ϵ�"yyyy-MM-dd HH:mm:ss"
	/// \param mask ��ʽѡ�ָ�����ڷָ�����������˳��Сʱ��ʽ�Ƿ���ͳһ�ĸ�
	/// ʽ��������Ӧλ��0����ʾʹ��ͳһ��ʽ����1����ʾʹ��formatָ���ĸ�ʽ
	/// \return �Ƿ�ɹ�
	bool parse(const char* buf, const char *format = "yyyy-MM-dd HH:mm:ss", int mask = fmGeneral);

	/// ������ʵ�ʵ�ȥȡ���ص�ǰϵͳʱ��,����ȷ�ͼ�ʱ
	/// ��linux�¶��̵߳���Ƶ�����ܻᵼ�½ϸ�cpu��������ʱ��������׼ȷ���ҵ��ò�Ƶ���ĳ���
	static CTime getCurrentTime();

	/// ���ر���ĵ�ǰ��ϵͳʱ�䣬�ڲ�����ȥˢ�±���ı��ص�ǰϵͳʱ��
	/// ���ڶ��߳�Ƶ����ӡ����ʵ��ʱ�侫�ȿ�����1sƫ�Χ�ڣ�����cpuռ���ʵ�
	static CTime getCurTimeForPrint();

	/// ���ñ��ص�ǰϵͳʱ��
	/// \param time �µ�ʱ��
	/// \param toleranceSeconds �ݲ��ʾ��������ʱ��͵�ǰ��������ڲ����޸�
	static void setCurrentTime(const CTime& time, int toleranceSeconds = 0);

	/// ���ñ��ص�ǰϵͳʱ�䲢�������óɹ����
	/// \param time �µ�ʱ��
	/// \param toleranceSeconds �ݲ��ʾ��������ʱ��͵�ǰ��������ڲ����޸�
	static bool setCurrentTimeEx(const CTime& time, int toleranceSeconds = 0);

	/// �õ���ϵͳ���������ڵĺ�����
	static uint64_t getCurrentMilliSecond();

	/// �õ���ϵͳ���������ڵ�΢����
	static uint64_t getCurrentMicroSecond();

	/// ����ʱ���ʽ����Ӱ��Format��������ַ�����ʽ����"yyyy-MM-dd HH:mm:ss"
	static void setFormatString(const char* format);

	/// ��ȡʱ���ʽ
	static const CString getFormatString();

	/// ��ȡ���ڸ�ʽ
	static DateFormat getDateFormat();

	/// ��ȡ��ǰ�Ƿ���12Сʱ��
	static bool get12Hour();

	/// ��ȡ���ڷָ��
	static char getSeparator();

	/// ע���޸�ʱ��ص�������������ϲ������setCurrentTime��ᱻͬ������
	/// \param proc ʱ���޸Ļص�����
	/// \return ע��ʱ���޸Ļص������Ƿ�ɹ�
	static bool attachModifyProc(ModifyProc proc);


	/// ����ʱ���ʽ����Ӱ��Format��������ַ�����ʽ����"yyyy-MM-dd HH:mm:ss"
	static void setFormat(const CString2& format);

	/// ��ȡʱ���ʽ
	static const CString2 getFormat();

	/// ��ȡUTC��׼ʱ��
	static uint64_t getCurrentUTCtime();

	/// ��ֹʱ�����Ż����ܡ�CTime�в�����ʱ��ת����Ҳ����ȡʱ��
	static int disableTimezone();

public:
	static const CTime minTime; ///< ��Ч����Сʱ��
	static const CTime maxTime; ///< ��Ч�����ʱ��

};

} // namespace Infra
} // namespace Dahua

#endif // __INFRA_TIME_WRAPPER_H__
