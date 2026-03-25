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


enum class Algorithm : uint8_t
{
	NoPKey   =    0 ,
	DSA      =    1 ,
	RSA      =    2 ,
	EDDSA    =    3 , 
	Invalid  =  255 ,

} ; // enum class Algorithm 


bool IsValidAlgorithm( uint8_t const & algorithmNo ) ;


}   // namespace IPSECKEY

}   // namespace RR

}   // namespace dns

}   // namespace daniel