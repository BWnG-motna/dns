#pragma once

#include "Common.h"
#include "RData_NAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_MB : public RData_NAME
{

public :
	uint8_t const * GetMadName() const ;

public :
	RData_MB( uint8_t const * pRef ) ;

} ; // class RData_MB
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel