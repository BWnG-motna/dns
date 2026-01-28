#include "dns/RR/TLSA/MatchingType.h"


bool daniel::dns::RR::IsValidMatchingType( uint8_t const & matchingTypeNo )
{
	switch( matchingTypeNo )
	{
		case 0 : // EXACT  - Full data ( no hash )
		case 1 : // SHA256 - SHA-256 hash
		case 2 : // SHA512 - SHA-512 hash
			return true ;

		default :
			return false ;
	}
}