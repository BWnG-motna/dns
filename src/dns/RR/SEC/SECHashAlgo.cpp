#include "dns/RR/SEC/SECHashAlgo.h"


bool daniel::dns::RR::IsValidHashAlgo( SECHashAlgo const & hashAlgo )
{
	using A = daniel::dns::RR::SECHashAlgo ;
	
	switch( hashAlgo )
	{
		case A::SHA1  :              
			return true ;

		default :
			return false ;     
	}
}


bool daniel::dns::RR::IsValidHashAlgo( uint8_t const & hashAlgo )
{
	switch( hashAlgo )
	{
		case 1 :
			return true ;

		default :
			return false ;
	}
}


char const * daniel::dns::RR::ToString( SECHashAlgo const & hashAlgo )
{
	using A = daniel::dns::RR::SECHashAlgo ;

	switch( hashAlgo )
	{
		case A::SHA1  :    
			return "RSA/MD5" ;

		default :
			return "UNKNOWN" ;    
	}
}


uint16_t daniel::dns::RR::GetHashAlgoLen( SECHashAlgo const & hashAlgo )
{
	using A = daniel::dns::RR::SECHashAlgo ;

	switch( hashAlgo )
	{
		case A::SHA1  :    
			return 20 ;

		default :
			return 0 ;    
	}
}