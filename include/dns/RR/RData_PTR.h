#pragma once

#include "Common.h"
#include "RData_NAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_PTR : public RData_NAME
{

private :
	void Initalize() override ;

public :
	uint8_t const * GetPTRDName() const ;

public :
	 RData_PTR( uint8_t const * pRef ) ;
	~RData_PTR() ;

} ; // class RData_PTR
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel