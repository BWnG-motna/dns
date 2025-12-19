#pragma once

#include "Common.h"
#include "RData_DNAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_PTR : public RData_DNAME
{

public :
	RData_PTR( uint8_t const * pRef ) ;

} ; // class RData_PTR
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel