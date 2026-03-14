#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace APL
{


enum class AddressFamily : uint16_t
{

	IPv4      =      1 , // IPv4
	IPv6      =      2 , // IPv6
	Invalid   =  65535 ,

} ; // enum class AddrFamily


bool IsValidAddressFamily( uint16_t const & addrFamilyNo ) ;


}   // namespace APL

}   // namespace RR

}   // namespace dns

}   // namespace daniel