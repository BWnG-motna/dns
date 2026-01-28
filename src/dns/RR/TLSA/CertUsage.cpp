#include "dns/RR/TLSA/CertUsage.h"


bool daniel::dns::RR::IsValidCertUsage( uint8_t const & certUsageNo )
{
	switch( certUsageNo )
	{
		case 0 : // PKIX_TA - CA Constraint
		case 1 : // PKIE_EE - Service Cerificate Constraint
		case 2 : // DANE_TA - Trust Anchor Assertion
		case 3 : // DANE_EE - Domain Issued Certificate
			return true ;

		default :
			return false ;
	}
}