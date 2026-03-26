#include "dns/RR/DHCID/DigestType.h"


bool daniel::dns::RR::DHCID::IsValidDigestType( uint8_t const & type )
{
	switch( type )
	{
		case 1 : // SHA-256
			return true ;

		default :
			return false ;     
	}
}