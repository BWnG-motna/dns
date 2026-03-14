#include "dns/RR/SEC/SECHashAlgo.h"


bool daniel::dns::RR::SEC::IsValidHashAlgo( SECHashAlgo const & hashAlgo )
{
	using A = daniel::dns::RR::SEC::SECHashAlgo ;
	
	switch( hashAlgo )
	{
		case A::SHA1  :              
			return true ;

		default :
			return false ;     
	}
}


bool daniel::dns::RR::SEC::IsValidHashAlgo( uint8_t const & hashAlgo )
{
	switch( hashAlgo )
	{
		case 1 :
			return true ;

		default :
			return false ;
	}
}


char const * daniel::dns::RR::SEC::ToString( SECHashAlgo const & hashAlgo )
{
	using A = daniel::dns::RR::SEC::SECHashAlgo ;

	switch( hashAlgo )
	{
		case A::SHA1  :    
			return "RSA/MD5" ;

		default :
			return "UNKNOWN" ;    
	}
}


uint16_t daniel::dns::RR::SEC::GetHashAlgoLen( SECHashAlgo const & hashAlgo )
{
	using A = daniel::dns::RR::SEC::SECHashAlgo ;

	switch( hashAlgo )
	{
		case A::SHA1  :    
			return 20 ;

		default :
			return 0 ;    
	}
}