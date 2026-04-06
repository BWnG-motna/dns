#pragma once

#include "Common.h"
#include "RData_NAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_NSAP_PTR : public RData_NAME
{

private :
	void Initialize() override ;

public :
	uint8_t const * GetPTRDName() const ;

public :
	 RData_NSAP_PTR( uint8_t const * pRef ) ;
	~RData_NSAP_PTR() ;

} ; // class RData_NSAP_PTR
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel