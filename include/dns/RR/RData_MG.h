#pragma once

#include "Common.h"
#include "RData_NAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_MG : public RData_NAME
{

public :
	uint8_t const * GetMgmName() const ;

public :
	RData_MG( uint8_t const * pRef ) ;

} ; // class RData_MG
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel