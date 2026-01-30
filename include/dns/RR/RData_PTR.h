#pragma once

#include "Common.h"
#include "RData_NAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_PTR : public RData_NAME
{

public :
	uint8_t const * GetPTRDName() const ;

public :
	RData_PTR( uint8_t const * pRef ) ;

} ; // class RData_PTR
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel