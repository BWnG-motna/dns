#include "dns/RR/IPSECKEY/Algorithm.h"


bool daniel::dns::RR::IPSECKEY::IsValidAlgorithm( uint8_t const & algorithmNo )
{
	switch( algorithmNo )
	{
		case 0 : // No public key
		case 1 : // DSA
		case 2 : // RSA          
		case 3 : // 
			return true ;

		default :
			return false ;     
	}
}