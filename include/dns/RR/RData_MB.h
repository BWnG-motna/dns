#pragma once

#include "Common.h"
#include "RData_DNAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_MB : public RData_DNAME
{

public :
	RData_MB( uint8_t const * pRef ) ;

} ; // class RData_MB
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel