#include "dns/RR/DANE/Selector.h"


bool daniel::dns::RR::DANE::IsValidSelector( uint8_t const & selectorNo )
{
	switch( selectorNo )
	{
		case 0 : // FullCert  - Full certificate - X.509 entire certificate - DER encoding
		case 1 : // PublicKey - Public key only ( normal )
			return true ;

		default :
			return false ;
	}
}