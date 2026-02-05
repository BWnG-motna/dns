#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace SEC
{


enum class SECDigest : uint8_t
{
	Reserved        =   0 , // Prohibited use
	SHA1            =   1 , // 20 octets
	SHA256          =   2 , // 32 octets
	GOST_R_34_11_94 =   3 , // 32 octets
	SHA384          =   4 , // 48 octets
	INVALID         = 255 ,
} ;


bool IsValidDigest( SECDigest const & digest ) ;
bool IsValidDigest( uint8_t   const & digestNumber ) ;

int16_t GetDigestLen( SECDigest const & digest ) ;

char const * ToString( SECDigest const & digest ) ;


} // namespace SEC

} // namespace RR

} // namespace dns

} // namespace daniel