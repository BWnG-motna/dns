#pragma once

#include "Common.h"
#include "RData_DNAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_NS : public RData_DNAME
{

public :
	uint8_t const * GetNSDName() const ;

public :
	RData_NS( uint8_t const * pRef ) ;

} ; // class RData_NS
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel