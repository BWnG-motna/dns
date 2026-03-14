#include "dns/RR/SEC/SECAlgo.h"


bool daniel::dns::RR::SEC::IsValidAlgo( SECAlgo const & algorithm )
{
	using A = daniel::dns::RR::SEC::SECAlgo ;
	
	switch( algorithm )
	{
		case A::RSA_MD5  :              
		case A::DSA_SHA1 :                 
		case A::RSA_SHA1 :                 
		case A::RSA_SHA1_NSEC3_SHA1 :    
		case A::RSA_SHA256 :              
		case A::RSA_SHA512 :              
		case A::GOST_R_34_10_2011 :        
		case A::ECDSA_CURVE_P256_SHA256 :  
		case A::ECDSA_CURVE_P384_SHA384 : 
		case A::ED25519 :                 
		case A::ED448 :
			return true ;

		default :
			return false ;     
	}
}


bool daniel::dns::RR::SEC::IsValidAlgo( uint8_t const & algorithmNumber )
{
	switch( algorithmNumber )
	{
		case 1 :
		case 2 :
		case 5 :
		case 7 :
		case 8 :
		case 10 :
		case 12 :
		case 13 :
		case 14 :
		case 15 :
		case 16 :
			return true ;

		default :
			return false ;
	}
}


char const * daniel::dns::RR::SEC::ToString( SECAlgo const & algo )
{
	using A = daniel::dns::RR::SEC::SECAlgo ;

	switch( algo )
	{
		case A::RSA_MD5  :    
			return "RSA/MD5" ;

		case A::DSA_SHA1 :
			return "DSA/SHA-1" ;

		case A::RSA_SHA1 :
			return "RSA/SHA-1" ;

		case A::RSA_SHA1_NSEC3_SHA1 :
			return "RSA/SHA-1 - NSEC3/SHA-1" ;

		case A::RSA_SHA256 :
			return "RSA/SHA-256" ;

		case A::RSA_SHA512 :
			return "RSA/SHA-512" ;

		case A::GOST_R_34_10_2011 :
			return "GOST R 34.10-2001" ;

		case A::ECDSA_CURVE_P256_SHA256 :  
			return "ECDSA Curve P-256 / SHA-256" ;

		case A::ECDSA_CURVE_P384_SHA384 : 
			return "ECDSA Curve P-384 / SHA-384" ;

		case A::ED25519 :
			return "ED25519" ;

		case A::ED448 :
			return "ED448" ;

		default :
			return "UNKNOWN" ;    
	}
}