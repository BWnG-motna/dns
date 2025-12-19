#pragma once

#include "Common.h"
#include "RData_DNAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_CNAME : public RData_DNAME
{

public :
	RData_CNAME( uint8_t const * pRef ) ;

} ; // class RData_CNAME
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel