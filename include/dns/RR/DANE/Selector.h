#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace DANE
{


enum class Selector : uint8_t
{
	FullCert   =    0 , // Full certificate - X.509 entire certificate - DER encoding
	PublicKey  =    1 , // Public key only ( normal )

	INVALID    =  255 ,

} ; // enum class Selector 


bool IsValidSelector( uint8_t const & selectorNo ) ;


}   // namespace DANE

}   // namespace RR

}   // namespace dns

}   // namespace daniel