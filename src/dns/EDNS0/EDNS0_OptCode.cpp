#include "dns/EDNS0/EDNS0_OptCode.h"


bool daniel::dns::IsValidEDNS0_OptCode( uint16_t const & codeNo )
{
	switch( codeNo ) 
	{
		case 1 :
		case 2 :
		case 3 :
			return true ;

		case 5 :
		case 6 :
		case 7 :
		case 8 :
		case 9 :
		case 10 :
		case 11 :
		case 12 :
		case 13 :
		case 14 :
		case 15 :
			return true ;

		case 18 :
		case 19 :
			return true ;

		case 20292 :
		case 26946 :
			return false ; 

		default :
			return false ;
	}
}
