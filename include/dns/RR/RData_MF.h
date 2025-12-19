#pragma once

#include "Common.h"
#include "RData_DNAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_MF : public RData_DNAME
{

public :
	RData_MF( uint8_t const * pRef ) ;

} ; // class RData_MF
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel