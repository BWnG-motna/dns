#include "dns/RR/SVC/SvcKey.h"


bool daniel::dns::RR::SVC::IsValidSvcKey( uint16_t const & key )
{
	switch( key )
	{
		case 0 :
		case 1 :
		case 2 :
		case 3 :
		case 4 :
		case 5 :
		case 6 :
			return true ;

		default : 
			return false ;
	}
}