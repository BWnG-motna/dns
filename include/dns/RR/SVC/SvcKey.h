#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace SVC
{


enum class SvcKey : uint16_t
{
	mandatory       =      0 ,  // Mandatory keys that must be present ( list of uint16_t keys )
	alpn            =      1 ,  // Supported ALPN protocol identifiers ( length-prefixed strings )
	no_default_alpn =      2 ,  // Disables default ALPN ( value must be empty, length == 0 )
	port            =      3 ,  // Service port number ( uint16_t, network byte order )
	ipv4hint        =      4 ,  // IPv4 address hints (  4-byte addresses repeated )
	ech             =      5 ,  // Encrypted Client Hello configurations ( ECHConfigList )
	ipv6hint        =      6 ,  // IPv6 address hints ( 16-byte addresses repeated ) 

	reserved        =  65535 ,  // Reserved, MUST NOT be used

} ; // enum class SvcKey


bool IsValidSvcKey( uint16_t const & key ) ;


}   // namespace SVC

}   // namespace RR

}   // namespace dns

}   // namespace daniel