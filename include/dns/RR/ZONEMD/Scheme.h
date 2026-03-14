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


enum class Scheme : uint8_t
{
	Reserved   =      0 , 
	Simple     =      1 ,

	// unassigned   :    2 ~ 239
	// private used :  240 ~ 254
	// reserved     :        255

} ; // enum class Scheme


bool IsValidScheme( uint8_t const & key ) ;


}   // namespace SVC

}   // namespace RR

}   // namespace dns

}   // namespace daniel