//
//  "$Id$"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __DAHUA_INFRA_STRING_H__
#define __DAHUA_INFRA_STRING_H__

#include "Defs.h"
#include "CString.h"
#include "Detail/flex_string.h"

////////////////////////////////////////////////////////////////////////////////
// �� std::basic_string �ӿ���ȫ���ݵ��ַ���������

namespace Dahua {
namespace Infra {

// ����CStirng��std::string���ַ������º���Ӧ��ֱ��ʹ��CString������
#ifdef _WIN32
typedef CString CString2;
#else
typedef std::string CString2;
#endif // WIN32

typedef flex_string<
	wchar_t,
	std::char_traits<wchar_t>,
	std::allocator<wchar_t>,
	SmallStringOpt<AllocatorStringStorage<wchar_t, std::allocator<wchar_t> >, 31>
> CWString;

/// ��С�ַ����࣬sizeof(CMiniString)�̶�Ϊsizeof(void *)
typedef flex_string<
	char,
	std::char_traits<char>,
	std::allocator<char>,
	MiniStringStorage<char, std::allocator<char> >
> CMiniString;

} // namespace Infra
} // namespace Dahua


#endif// __DAHUA_INFRA_STRING_H__


