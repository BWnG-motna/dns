#pragma once


#include "Common.h"


namespace daniel
{

namespace dns
{


enum class EDNS0_OptCode : uint16_t
{
	RESERVED        =      0 ,
	LLQ             =      1 , // Long Lived Queries
	UL              =      2 , // Update Lease
	NSID            =      3 , // Name Server Identifier

	DAU             =      5 , // DNSSEC algorithm understood
	DHU             =      6 , // DS Hash Understood
	N3U             =      7 , // NSEC3 Hash Understood
	ECS             =      8 , // edns-client-subnet ( ECS ) 
	EDNS_EXPIRE     =      9 , // EDNS EXPIRE ( RFC 7314 )
	COOKIE          =     10 , // COOKIE ( RFC 7873 )
	TCP_KEEPALIVE   =     11 , // edns-tcp-Keepalive ( RFC 7828 )
	PADDING         =     12 , // Padding ( RFC 7830 )
	CHAIN           =     13 , // CHAIN ( RFC 7901 )
	EDNS_KEY_TAG    =     14 , // ends-key-tag ( RFC 8145 )
	EDE             =     15 , // Extended DNS Error ( RFC 8914 )

	REPORT_CHANNEL  =     18 , // Report-Channel ( RFC 9567 )
	ZONEVERSION     =     19 , // ZONEVERSION ( RFC 9660 )

	UmbrellaIdent   =  20292 , // Umbrella Ident
	DeviceID        =  26946 , // Device ID

	ReservedFuture  =  65535 ,


} ; // enum class EDNS0_OptCode


bool IsValidEDNS0_OptCode( uint16_t const & codeNo ) ;

}   // namespace dns

}   // namespace daniel