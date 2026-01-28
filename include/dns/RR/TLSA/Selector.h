#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{


enum class Selector : uint8_t
{
	FullCert  = 0 , // Full certificate - X.509 entire certificate - DER encoding
	PublicKey = 1 , // Public key only ( normal )

} ; // enum class Selector 


bool IsValidSelector( uint8_t const & selectorNo ) ;


}   // namespace RR

}   // namespace dns

}   // namespace daniel