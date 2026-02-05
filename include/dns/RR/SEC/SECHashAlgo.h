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


enum class SECHashAlgo : uint8_t
{
	INVALID =   0 ,
	SHA1    =   1 , // 20 bytes
} ;


bool IsValidHashAlgo( SECHashAlgo const & hashAlgo ) ;
bool IsValidHashAlgo( uint8_t     const & hashAlgo ) ;

char const * ToString( SECHashAlgo const & hashAlgo ) ;

uint16_t GetHashAlgoLen( SECHashAlgo const & hashAlgo ) ;


} // namespace SEC

} // namespace RR

} // namespace dns

} // namespace daniel