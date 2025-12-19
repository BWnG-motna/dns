#pragma once

#include "Common.h"
#include "RData_DNAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_MD : public RData_DNAME
{

public :
	RData_MD( uint8_t const * pRef ) ;

} ; // class RData_MD
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel