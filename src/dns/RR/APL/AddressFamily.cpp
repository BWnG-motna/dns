#include "dns/RR/APL/AddressFamily.h"


bool daniel::dns::RR::APL::IsValidAddressFamily( uint16_t const & addrFamilyNo )
{
	switch( addrFamilyNo )
	{
		case 0 : // IPv4
		case 1 : // IPv6
			return true ;

		default :
			return false ;
	}
}