#include "dns/EDNS0/EDNS0_OptCode.h"


bool daniel::dns::IsValidEDNS0_OptCode( uint16_t const & codeNo )
{
	switch( codeNo ) 
	{
		case     1 : // LLQ             =      1 , // Long Lived Queries
		case     2 : // UL              =      2 , // Update Lease
		case     3 : // NSID            =      3 , // Name Server Identifier
			return true ;

		case     5 : // DAU             =      5 , // DNSSEC algorithm understood
		case     6 : // DHU             =      6 , // DS Hash Understood
		case     7 : // N3U             =      7 , // NSEC3 Hash Understood
		case     8 : // ECS             =      8 , // edns-client-subnet ( ECS ) 
		case     9 : // EDNS_EXPIRE     =      9 , // EDNS EXPIRE ( RFC 7314 )
		case    10 : // COOKIE          =     10 , // COOKIE ( RFC 7873 )
		case    11 : // TCP_KEEPALIVE   =     11 , // edns-tcp-Keepalive ( RFC 7828 )
		case    12 : // PADDING         =     12 , // Padding ( RFC 7830 )
		case    13 : // CHAIN           =     13 , // CHAIN ( RFC 7901 )
		case    14 : // EDNS_KEY_TAG    =     14 , // ends-key-tag ( RFC 8145 )
		case    15 : // EDE             =     15 , // Extended DNS Error ( RFC 8914 )
			return true ;

		case    18 : // REPORT_CHANNEL  =     18 , // Report-Channel ( RFC 9567 )
		case    19 : // ZONEVERSION     =     19 , // ZONEVERSION ( RFC 9660 )
			return true ;

		case 20292 : // UmbrellaIdent   =  20292 , // Umbrella Ident
		case 26946 : // DeviceID        =  26946 , // Device ID
			return false ; 

		default :
			return false ;
	}
}
