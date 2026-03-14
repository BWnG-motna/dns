#include "dns/RR/ZONEMD/Scheme.h"


bool daniel::dns::RR::ZONEMD::IsValidScheme( uint8_t const & schemeNo )
{
	switch( schemeNo )
	{
		case 1 : // simple
			return true ;

		default : 
			return false ;
	}
}