//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef INFRA3_ATOMIC_COUNT_H__
#define INFRA3_ATOMIC_COUNT_H__

#include "Detail/atomic_count.hpp"

namespace Dahua {
namespace Infra {


/// \brief ԭ�Ӽ�����
///	�ȼ���������:
///	\code
///		class CAtomicCount
///		{
///			CAtomicCount(CAtomicCount const&);
///			CAtomicCount& operator=(CAtomicCount const&);
///
///		public:
///			explicit CAtomicCount(long v);
///
///			long operator++();	// ǰ׺++
///
///			long operator--();	// ǰ׺--
///
///			operator long() const;
///
///			long get() const;
///
///			void set(long v);
///		};
///	\endcode
///
typedef Detail::atomic_count	CAtomicCount;


} // namespace Infra
} // namespace Dahua

#endif // INFRA_ATOMIC_COUNT_H__


