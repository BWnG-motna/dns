#pragma once

#include "Common.h"


namespace daniel
{
	
namespace dns
{
	
enum class QClass : uint16_t
{
	IN   =    1 , // the internet
	CS   =    2 , // the CSNET class ( Obsolete - used only for examples in some obsolete RFCs )
	CH   =    3 , // the CHAOS class
	HS   =    4 , // Hesiod [ Dyer 87 ]

	ALL  =  255 , // any class

} ; // enum class QClass


char const * ToString( QClass const & qclass ) ;

}   // namespace dns

}   // namespace daniel