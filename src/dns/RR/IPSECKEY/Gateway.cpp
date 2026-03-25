#include "dns/RR/IPSECKEY/Gateway.h"


bool daniel::dns::RR::IPSECKEY::IsValidGateway( uint8_t const & gatewayNo )
{
	switch( gatewayNo )
	{
		case 0 : // NoGateway
		case 1 : // IPv4
		case 2 : // IPv6          
		case 3 : // FQDN
			return true ;

		default :
			return false ;     
	}
}


bool daniel::dns::RR::IPSECKEY::IsFixedLen( Gateway const & gateway )
{
	switch( gateway )
	{
		case Gateway::NoGateway :
		case Gateway::IPv4 :
		case Gateway::IPv6 :
			return true ;

		case Gateway::FQDN :
			return false ;

		default :
			return true ;
	}	
}


uint16_t daniel::dns::RR::IPSECKEY::GetFixedLen( Gateway const & gateway )
{
	switch( gateway )
	{
		case Gateway::NoGateway :
			return 0 ;
			
		case Gateway::IPv4 :
			return 4 ;

		case Gateway::IPv6 :
			return 16 ;

		case Gateway::FQDN :
			return 0 ;

		default :
			return 0 ;
	}	
}