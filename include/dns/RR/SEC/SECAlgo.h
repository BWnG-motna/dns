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


enum class SECAlgo : uint8_t
{
	INVALID                  =   0 ,
	RSA_MD5                  =   1 , // RFC 8624 - MUST NOT      / 128 bytes
	DSA_SHA1                 =   2 , // RFC 8624 - MUST NOT      /  64 bytes
	RSA_SHA1                 =   5 , // RFC 8624 - SHOULD NOT    / 128 bytes
	RSA_SHA1_NSEC3_SHA1      =   7 , // RFC 8624 - SHOULD NOT    / 128 bytes
	RSA_SHA256               =   8 , // RFC 8624 - MUST          / 256 bytes
	RSA_SHA512               =  10 , // RFC 8624 - SHOULD        / 512 bytes
	GOST_R_34_10_2011        =  12 , // RFC 8624 - NOT RECOMMAND / ?
	ECDSA_CURVE_P256_SHA256  =  13 , // RFC 8624 - MUST          /  64 bytes
	ECDSA_CURVE_P384_SHA384  =  14 , // RFC 8624 - SHOULD        /  86 bytes
	ED25519                  =  15 , // RFC 8624 - MUST          /  64 bytes
	ED448                    =  16 , // RFC 8624 - SHOULD        /  96 bytes
} ;


bool IsValidAlgo( SECAlgo const & algorithm ) ;
bool IsValidAlgo( uint8_t const & algorithmNumber ) ;

char const * ToString( SECAlgo const & algo ) ;


} // namespace SEC

} // namespace RR

} // namespace dns

} // namespace daniel