#include "dns/RR/SSHFP/Algorithm.h"


bool daniel::dns::RR::SSHFP::IsValidAlgorithm( uint8_t const & algorithmNumber )
{
	switch( algorithmNumber )
	{
		case 1 :  // RSA
		case 2 :  // DSA
		case 3 :  // ECDSA
		case 4 :  // ED25519
		case 6 :  // ED448
			return true ;

		default : 
			return false ;
	}
}