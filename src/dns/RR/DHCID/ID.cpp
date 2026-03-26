#include "dns/RR/DHCID/ID.h"


bool daniel::dns::RR::DHCID::IsValidId( uint16_t const & id )
{
	switch( id )
	{
		case 0x0000 : // htype( 1 byte ) + chaddr( hardware address ) - DHCPv4
		case 0x0001 : // type + identifier                            - DHCPv4		
			
		case 0x0002 : // DUID ( DHCPv6 client identifier or DHCPv4's DUID )
			return true ;

		default :
			return false ;     
	}
}