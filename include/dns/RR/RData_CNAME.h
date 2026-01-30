#pragma once

#include "Common.h"
#include "RData_NAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_CNAME : public RData_NAME
{

public :
	uint8_t const * GetCNAME() const ;

public :
	RData_CNAME( uint8_t const * pRef ) ;

} ; // class RData_CNAME
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel