#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace IPSECKEY
{


enum class Gateway : uint8_t
{
	NoGateway  =    0 ,
	IPv4       =    1 ,
	IPv6       =    2 ,
	FQDN       =    3 ,
	Invalid    =  255 ,

} ; // enum class Gateway 


bool IsValidGateway( uint8_t const & gatewayNo ) ;
bool IsFixedLen( Gateway const & gateway ) ;
uint16_t GetFixedLen( Gateway const & gateway ) ;

}   // namespace IPSECKEY

}   // namespace RR

}   // namespace dns

}   // namespace daniel