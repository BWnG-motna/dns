#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{


enum class MatchingType : uint8_t
{
	EXACT   =   0 ,  // Full data ( no hash )
	SHA256  =   1 ,  // SHA-256 hash
	SHA512  =   2 ,  // SHA-512 hash

} ; // enum class MatchingType 


bool IsValidMatchingType( uint8_t const & matchingTypeNo ) ;


}   // namespace RR

}   // namespace dns

}   // namespace daniel