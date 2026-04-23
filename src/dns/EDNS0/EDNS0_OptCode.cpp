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


char const * daniel::dns::GetMeaningOfOptCode( uint16_t const & codeNo )
{
	switch( codeNo ) 
	{
		case 1 : 
			return "Long Lived Queries" ;

		case 2 : 
			return "Update Lease" ;

		case 3 :
			return "Name Server Identifier" ;

		case 5 :
			return "DNSSEC algorithm understood" ;

		case 6 :
			return "DS Hash Understood" ;

		case 7 :
			return "NSEC3 Hash Understood" ;

		case 8 :
			return "edns-client-subnet" ;

		case 9 :
			return "EDNS EXPIRE" ;

		case 10 :
			return "COOKIE" ;

		case 11 :
			return "edns-tcp-Keepalive" ;

		case 12 :
			return "padding" ;

		case 13 :
			return "CHAIN" ;

		case 14 :
			return "ends-key-tag" ;

		case 15 :
			return "Extended DNS Error" ;

		case 18 :
			return "Report-Channel" ;

		case 19 :
			return "ZONEVERSION" ;

		case 20292 :
			return "Umbrella Ident" ;

		case 26946 :
			return "Device ID" ; 

		default :
			return "Unknown" ;
	}
}


char const * daniel::dns::GetMeaningOfOptCode( EDNS0_OptCode const & code )
{
	switch( code ) 
	{
		case EDNS0_OptCode::LLQ : 
			return "Long Lived Queries" ;

		case EDNS0_OptCode::UL : 
			return "Update Lease" ;

		case EDNS0_OptCode::NSID :
			return "Name Server Identifier" ;

		case EDNS0_OptCode::DAU :
			return "DNSSEC algorithm understood" ;

		case EDNS0_OptCode::DHU :
			return "DS Hash Understood" ;

		case EDNS0_OptCode::N3U :
			return "NSEC3 Hash Understood" ;

		case EDNS0_OptCode::ECS :
			return "edns-client-subnet" ;

		case EDNS0_OptCode::EDNS_EXPIRE :
			return "EDNS EXPIRE" ;

		case EDNS0_OptCode::COOKIE :
			return "COOKIE" ;

		case EDNS0_OptCode::TCP_KEEPALIVE :
			return "edns-tcp-Keepalive" ;

		case EDNS0_OptCode::PADDING :
			return "padding" ;

		case EDNS0_OptCode::CHAIN :
			return "CHAIN" ;

		case EDNS0_OptCode::EDNS_KEY_TAG :
			return "ends-key-tag" ;

		case EDNS0_OptCode::EDE :
			return "Extended DNS Error" ;

		case EDNS0_OptCode::REPORT_CHANNEL :
			return "Report-Channel" ;

		case EDNS0_OptCode::ZONEVERSION :
			return "ZONEVERSION" ;

		case EDNS0_OptCode::UmbrellaIdent :
			return "Umbrella Ident" ;

		case EDNS0_OptCode::DeviceID :
			return "Device ID" ; 

		default :
			return "Unknown" ;
	}
}