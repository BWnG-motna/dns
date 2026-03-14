#pragma once


#include "Common.h"


namespace daniel
{

namespace dns
{


enum class EDNS0_OptCode : uint16_t
{
	RESERVED        =      0 ,
	LLQ             =      1 ,
	UL              =      2 , // Update Lease
	NSID            =      3 ,

	DAU             =      5 ,
	DHU             =      6 ,
	N3U             =      7 ,
	CLINET_SUBNET   =      8 ,
	EXPIRE          =      9 ,
	COOKIE          =     10 ,
	TCP_KEEPALIVE   =     11 ,
	PADDING         =     12 ,
	CHAIN           =     13 ,
	KEYTAG          =     14 ,
	EDE             =     15 ,  // Extended DNS Error

	REPORT_CHANNEL  =     18 ,
	ZONEVERSION     =     19 ,

	UmbrellaIdent   =  20292 ,
	DeviceID        =  26946 ,


} ; // enum class EDNS0_OptCode


bool IsValidEDNS0_OptCode( uint16_t const & codeNo ) ;

}   // namespace dns

}   // namespace daniel