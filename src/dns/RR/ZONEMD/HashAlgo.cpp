#include "dns/RR/ZONEMD/HashAlgo.h"


bool daniel::dns::RR::ZONEMD::IsValidHashAlgo( uint8_t const & schemeNo )
{
	switch( schemeNo )
	{
		case 1 : // SHA-384
		case 2 : // SHA-512
			return true ;

		default : 
			return false ;
	}
}