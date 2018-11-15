//
//  "$Id: Support.h 20211 2011-02-24 02:50:44Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_SYSTEM_H__
#define __INFRA3_SYSTEM_H__

#include "Defs.h"

namespace Dahua {
namespace Infra {

/// \defgroup System System
/// һЩϵͳ��ظ���������
/// @{

/// ϵͳ���ýӿ�,���ַ�������ʽ����ϵͳ����
int INFRA_API systemCall(const char* command);


///	\ ��ȡ��ǰ����id
uint64_t INFRA_API getCurrectProcessID();


/// @} end of group

} // namespace Infra
} // namespace Dahua

#endif //__INFRA_SUPPORT_H__


