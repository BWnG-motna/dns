#include "dns/RR/SEC/SECDigest.h"


bool daniel::dns::RR::IsValidDigest( SECDigest const & digest )
{
	switch( digest )
	{
		case SECDigest::SHA1 :
		case SECDigest::SHA256 :
		case SECDigest::GOST_R_34_11_94 :
		case SECDigest::SHA384 :
			return true ;

		default :
			return false ;

	}

}


bool daniel::dns::RR::IsValidDigest( uint8_t const & digestNumber )
{
	switch( digestNumber )
	{
		case 1 :
		case 2 :
		case 3 :
		case 4 :
			return true ;

		default :
			return false ;
	}
}


char const * daniel::dns::RR::ToString( SECDigest const & digest )
{
	switch( digest )
	{
		case SECDigest::SHA1 :
			return "SHA-1" ;

		case SECDigest::SHA256 :
			return "SHA-256" ;

		case SECDigest::GOST_R_34_11_94 :
			return "GOST R 34.11-94" ;

		case SECDigest::SHA384 :
			return "SHA-384" ;

		default :
			return nullptr ;
	}
}


int16_t daniel::dns::RR::GetDigestLen( SECDigest const & digest )
{
	switch( digest )
	{
		case SECDigest::SHA1 :
			return 20 ;

		case SECDigest::SHA256 :
			return 32 ;

		case SECDigest::GOST_R_34_11_94 :
			return 32 ;

		case SECDigest::SHA384 :
			return 48 ;

		default :
			return -1 ;
	}
}