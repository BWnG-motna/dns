#pragma once

#include "Common.h"
#include "RData_NAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_MD : public RData_NAME
{

private :
	void Initalize() override ;

public :
	uint8_t const * GetMadName() const ;

public :
	 RData_MD( uint8_t const * pRef ) ;
	~RData_MD() ;

} ; // class RData_MD
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel