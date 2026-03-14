#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace ZONEMD
{


enum class HashAlgo : uint8_t
{
	Reserved   =      0 , 
	SHA384     =      1 ,
	SHA512     =      2 ,

	// unassigned   :    3 ~ 239
	// private used :  240 ~ 254
	// reserved     :        255

} ; // enum class Scheme


bool IsValidHashAlgo( uint8_t const & key ) ;


}   // namespace SVC

}   // namespace RR

}   // namespace dns

}   // namespace daniel