#include "dns/RR/CERT/CertType.h"


bool daniel::dns::RR::CERT::IsValidCertType( uint16_t const & certTypeNo )
{
	switch( certTypeNo )
	{
		case 1 :           // PKIX
		case 2 :           // SPKI
		case 3 :           // PGP
		case 4 :           // IPKIX
		case 5 :           // ISPKI
		case 6 :           // IPGP
		case 7 :           // ACPKIX
		case 8 :           // IACPKIX
			return true ;

		case 253 :         // URI
		case 254 :         // OID
			return true ;

		default :
			return false ;
	}
}