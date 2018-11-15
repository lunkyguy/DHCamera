//
//  "$Id: Version.h 55347 2012-03-22 11:26:45Z qin_fenglin $"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_VERSION_H__
#define __INFRA3_VERSION_H__

#include "Infra/Defs.h"
#include "Infra/Time.h"

namespace Dahua {
namespace Infra {

/// \brief �汾��
///
/// �汾�������ͳһ����CVersion��ÿ�������Ӧ�ö�����Եİ汾�ṹ���󣬲��ṩ
/// ���ʽӿڡ�������ɵ�ʱ��õ���������İ汾��Ϣ����ӡ��������������ױ��Ӧ��
/// ����汾��ƥ��������һ��ʹ�á�ÿ�����ҲӦ�ø����޸��ṩ��ȷ�İ汾��Ϣ��
/// �汾������򵥵�ʹ�÷������������������ʱ����ӡ����������İ汾��Ϣ��
/// \code
/// int main(int argc, char * argv[])
/// {
///		CVersion appVersion("Application", 1, 0, 0, "$Rev: 23572 $", __DATE__);
///		appVersion.dump();
/// 	......
/// }
/// \endcode
class INFRA_API CVersion
{
public:
	char	name[32];	///< �������
	int		major;		///< ���汾�ţ��ܹ��䶯ʱ����
	int		minor;		///< �ΰ汾�ţ��ӿڱ仯������ȱ������ʱ����
	int		revision;	///< �޶��汾�ţ�ȱ������ʱ����
	int		svn;		///< svn�汾�ţ���¼����3�汾�ű��ʱ��Ӧ��svn�汾��
	SystemTime date;	///< �������ڣ�ʹ��__DATE__��

	static	SystemTime appDate;	///< Ӧ�ó����������

	/// ���캯�����汾����һ����Ϊȫ�ֶ�����
	CVersion(const char* name, int major, int minor, int revision, const char* svnString, const char* dateString);

	/// �汾��Ϣ��ӡ
	void print() const;

	/// ����Ӧ�ó���������ڣ�Ӧ��Main�����������ã����ú�ſɻ�ȡ
	static void setAppDate(const char* dateString);

};

} // namespace Infra
} // namespace Dahua

#endif //__INFRA_VERSION_H__


