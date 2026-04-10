#pragma once

#include "Common.h"
#include "RData_NAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_DNAME : public RData_NAME
{

private :
	void Initialize() override ;

public :
	uint8_t const * GetTarget() const ;

public :
	 RData_DNAME( uint8_t const * pRef ) ;
	~RData_DNAME() ;

} ; // class RData_DNAME
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel