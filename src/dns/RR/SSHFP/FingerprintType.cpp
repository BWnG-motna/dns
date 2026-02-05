#include "dns/RR/SSHFP/FingerprintType.h"


bool daniel::dns::RR::SSHFP::IsValidFingerprintType( uint8_t const & fingerprintType )
{
	switch( fingerprintType )
	{
		case 1 :  // SHA1
		case 2 :  // SHA256
			return true ;

		default : 
			return false ;
	}
}