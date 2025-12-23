#pragma once

#include "Common.h"
#include "RData_DNAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_MG : public RData_DNAME
{

public :
	uint8_t const * GetMgmName() const ;

public :
	RData_MG( uint8_t const * pRef ) ;

} ; // class RData_MG
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel